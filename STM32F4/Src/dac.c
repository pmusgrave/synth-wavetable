#include "dac.h"
#include "globals.h"
#include <stdbool.h>
#include <stdint.h>

#define I2C_WRITE_OPERATION		(0x00)

I2C_HandleTypeDef* hi2c;

//static uint16_t Dac_analogPathSetting = DAC_DEF_ANALOG_CTRL;
//uint32 Dac_powerControlSetting = DAC_DEF_POWER_CTRL;

/*******************************************************************************
* Function Name: Dac_Init
********************************************************************************
* Summary:
*   Initializes the codec with default settings.
*
*
* Parameters:
*	None
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR
*
*******************************************************************************/
uint8_t Dac_Init(I2C_HandleTypeDef* i2c_handle)
{
  hi2c = i2c_handle;

  //PDN_Write(0);
  //CyDelay(10);
  //PDN_Write(1);
  //CSN_Write(0);

  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);

	uint8_t ret = 0;

  if(hi2c){
    ret = Dac_ResetOverI2C();
    //CyDelay(DAC_RESET_WAIT_DELAY);
    HAL_Delay(DAC_RESET_WAIT_DELAY);

    ret = Dac_SendData(DAC_REG_INTERFACE_SET, 0b10000111);
  }

	return ret;
}

/*******************************************************************************
* Function Name: Dac_SendData
********************************************************************************
* Summary:
*   Low level API to send data to codec over I2C.
*
*
* Parameters:  
*	regAddr - Address of the codec register to be updated
*	data - 16-bit data to be updated in the register
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error                       
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST    
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK               
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress  
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR 
*
*******************************************************************************/
uint8_t Dac_SendData(uint8_t regAddr, uint16_t data)
{
  uint8_t temp = 0;
  uint8_t byte = I2C_WRITE_OPERATION;
  if(hi2c){
    temp = HAL_I2C_Master_Transmit(hi2c, DAC_I2C_ADDR, &byte, 8, 100);
    //    if(temp == HAL_OK) {
      byte = ((regAddr << 0x01) | ((data>>8) & 0x01));
      temp = HAL_I2C_Master_Transmit(hi2c, DAC_I2C_ADDR, &byte, 8, 100);
      //if(temp == HAL_OK) {
        byte = (data&0xFF);
        temp = HAL_I2C_Master_Transmit(hi2c, DAC_I2C_ADDR, &byte, 8, 100);
        //}
        // }
  }

  return temp;

  /*
  temp = DacI2CM_I2CMasterSendStart(DAC_I2C_ADDR, I2C_WRITE_OPERATION);

	if(temp == DacI2CM_I2C_MSTR_NO_ERROR)
	{
		temp = DacI2CM_I2CMasterWriteByte(((regAddr << 0x01) | (HI8(data) & 0x01)));

		if(temp == DacI2CM_I2C_MSTR_NO_ERROR)
		{
			temp = DacI2CM_I2CMasterWriteByte(LO8(data));

			if(temp == DacI2CM_I2C_MSTR_NO_ERROR)
			{
				temp = DacI2CM_I2CMasterSendStop();
			}
		}
	}

	return temp;
  */
}

/*******************************************************************************
* Function Name: Dac_SetSamplingRate
********************************************************************************
* Summary:
*   This function sets the sampling rate of the codec. Note that the codec must be deactivated 
*	before configuring the sample rate.
*
*
* Parameters:  
*	srCtrlField - Sampling control register settings 
*					
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error                       
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST    
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK               
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress  
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR 
*
*******************************************************************************
uint8_t Dac_SetSamplingRate(uint8_t srCtrlField)
{		
	 This function modifies the BOSR & SR bits of sampling rate control register.
     * srCtrlField : bit[0] - BOSR, bit[1:4] - SR.
     
    return Dac_SendData(DAC_REG_SAMPLING_CTRL, srCtrlField);;
}
*/

/*******************************************************************************
* Function Name: Dac_AdjustBothHeadphoneVolume
********************************************************************************
* Summary:
*   This function updates the volume of both the left and right channels of the
* 	headphone output.
*
*
* Parameters:  
*	volume - 0 - Mute
*			 1 to DAC_HP_VOLUME_MAX levels
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error                       
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST    
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK               
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress  
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR 
*
*******************************************************************************

uint8_t Dac_AdjustBothHeadphoneVolume(uint8_t volume)
{
	if(volume > DAC_HP_VOLUME_MAX)
	{
		volume = DAC_HP_VOLUME_MAX;
	}
	
	return Dac_SendData(DAC_REG_LCH_VOLUME, (volume + (DAC_LHPOUT_BOTH + DAC_LHPOUT_LZCEN + DAC_HP_MUTE_VALUE)));
}


*******************************************************************************
* Function Name: Dac_Activate
********************************************************************************
* Summary:
*   Activates the codec - This function is called in conjunction with Dac_Deactivate API
*	after successful configuration update of the codec.
*
*
* Parameters:  
*	None
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error                       
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST    
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK               
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress  
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR 
*
*******************************************************************************
uint8_t Dac_Activate(void)
{
	return Dac_SendData(DAC_REG_ACTIVATE, DAC_CTRL_ACTIVATE); 
}
*/
/*******************************************************************************
* Function Name: Dac_Deactivate
********************************************************************************
* Summary:
*   Deactivates the DAC - the configuration is retained, just the DAC input/outputs are
*	disabled. The function should be called before changing any setting in the codec over I2C
*
*
* Parameters:  
*	None
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error                       
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST    
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK               
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress  
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR 
*
*******************************************************************************
uint8_t Dac_Deactivate(void)
{
	return Dac_SendData(DAC_REG_ACTIVATE, DAC_CTRL_DEACTIVATE); 
}
*/

/*******************************************************************************
* Function Name: Dac_ResetOverI2C
********************************************************************************
* Summary:
*   Resets the codec by sending an I2C command
*
* Parameters:  
*	None
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error                       
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST    
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK               
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress  
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR 
*
*******************************************************************************/
uint8_t Dac_ResetOverI2C(void)
{
	return Dac_SendData(DAC_REG_RESET, DAC_CTRL_RESET);
}

/*******************************************************************************
* Function Name: Dac_PowerOffControl
********************************************************************************
* Summary:
*   Disables power for various blocks in the codec
*
*
* Parameters:  
*	powerOffMask - Bit(s) mask for the power off control 
*                   Refer to bit settings available for DAC_REG_POWER_CTRL in 
*                   Dac.h
*
* Return:
*   uint8_t - I2C master transaction error status
*				DacI2CM_I2C_MSTR_NO_ERROR - Function complete without error                       
*				DacI2CM_I2C_MSTR_ERR_ARB_LOST - Master lost arbitration: INTR_MASTER_I2C_ARB_LOST    
*				DacI2CM_I2C_MSTR_ERR_LB_NAK - Last Byte NACKed: INTR_MASTER_I2C_NACK               
*				DacI2CM_I2C_MSTR_NOT_READY - Master on the bus or Slave operation is in progress  
*				DacI2CM_I2C_MSTR_BUS_BUSY - Bus is busy, process not started
*				DacI2CM_I2C_MSTR_ERR_ABORT_START - Slave was addressed before master begin Start
*				DacI2CM_I2C_MSTR_ERR_BUS_ERR - Bus error has: INTR_MASTER_I2C_BUS_ERROR 
*
*******************************************************************************/

/* [] END OF FILE */
