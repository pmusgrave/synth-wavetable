#include "i2c.h"
#include "globals.h"
#include <stdint.h>

void I2C_WriteToSlave(I2C_HandleTypeDef* i2c_handle, uint8_t address, uint8_t* writeBuffer, uint8_t length) {
  //while (HAL_I2C_GetState(i2c_handle) != HAL_OK)
  //  ;

  //HAL_I2C_Master_Transmit(i2c_handle, address, writeBuffer, 8, 100);
  //count = DELAY_COUNT;
  //HAL_Delay(100);

  for (int i = 0; i < length; i++) {
    HAL_I2C_Master_Transmit(i2c_handle, address, writeBuffer+i, 8, 100);
  }
}


/*******************************************************************************
 * Function Name: I2C_ReadFromSlave
 ********************************************************************************
 * Summary:
 *      This function reads length number of bytes of data from the I2C slave
 *      device starting from the Index specified by the bStartIndex, the data read
 *      would be stored in the abI2CBuffer
 *
 * Parameters:
 *  address - I2C slave address
 *  startIndex - Start Index of the Slave buffer from where data is to be read
 *  length - and the length of the data to be read
 *  readBuffer - Pointer to buffer which would hold the I2S read data
 *
 * Return:
 *  Comes out of the function if the read is successful, otherwise just stays
 *  in the function (blocking call)
 *
 *******************************************************************************/
void I2C_ReadFromSlave(I2C_HandleTypeDef* i2c_handle, uint8_t address, uint8_t startIndex, uint8_t length, uint8_t *readBuffer)
{
	uint8_t count;
  uint8_t status;

  /* Set the Read pointer to bStartIndex on the slave buffer */
  I2C_WriteToSlave(i2c_handle, address, &startIndex, 1);

  HAL_Delay(1);

  // come back to this later
  /*
    do
    {

    I2C_Master_I2CMasterClearStatus();


    I2C_Master_I2CMasterReadBuf(address, readBuffer, length, I2C_Master_I2C_MODE_COMPLETE_XFER);

    count = DELAY_COUNT;

    status = 0;


    while ((status & (I2C_Master_I2C_MSTAT_RD_CMPLT | I2C_Master_I2C_MSTAT_ERR_MASK)) == 0)
    {
    status = I2C_Master_I2CMasterStatus();

    if(count == 0)
    {
    break;
    }
    else;
    {
    count--;
    }

    CyDelayUs(length);
    }


    }while ((status != I2C_Master_I2C_MSTAT_RD_CMPLT));
  */
}

/* [] END OF FILE */
