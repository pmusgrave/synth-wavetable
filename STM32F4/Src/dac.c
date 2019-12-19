#include "dac.h"
#include "globals.h"
#include <stdbool.h>
#include <stdint.h>

#define I2C_WRITE_OPERATION		(0x00)

static I2C_HandleTypeDef* hi2c;

DacRegister DacWrite;
uint8_t dacInit = 0;

extern volatile uint8_t USB_currentVolume[];
extern volatile uint8_t USB_currentMute;

/*******************************************************************************
 * Function Name: InitDac
 ********************************************************************************
 * Summary: Initializes the dac as per the datasheet to enable
 *          audio output DAC (with volume control support enabled) and audio input
 *          ADC
 *
 * Parameters:
 *  void
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void InitDac(I2C_HandleTypeDef* i2c_handle)
{
  hi2c = i2c_handle;

  // Make sure DAC is reset
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
  // '“L” time of 150ns or more is needed to reset the DAC.'  1 us should be fine.
  HAL_Delay(DAC_RESET_WAIT_DELAY);

  // Power on DAC
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
  HAL_Delay(DAC_RESET_WAIT_DELAY + 100);

  DacWrite.address = DAC_CTRL_1;
  DacWrite.value = 0b10000111;
  // I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
  HAL_I2C_Mem_Write(hi2c, DAC_I2C_ADDR, DacWrite.address, 8, &DacWrite.value, 8, HAL_MAX_DELAY);

  DacWrite.address = DAC_CTRL_2;
  DacWrite.value = 0b00100010;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
  HAL_I2C_Mem_Write(hi2c, DAC_I2C_ADDR, DacWrite.address, 8, &DacWrite.value, 8, HAL_MAX_DELAY);

  DacWrite.address = DAC_CTRL_3;
  DacWrite.value = 0b00000000;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
  HAL_I2C_Mem_Write(hi2c, DAC_I2C_ADDR, DacWrite.address, 8, &DacWrite.value, 8, HAL_MAX_DELAY);

  DacWrite.address = DAC_LCH_ATT;
  DacWrite.value = 0xE9;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
  HAL_I2C_Mem_Write(hi2c, DAC_I2C_ADDR, DacWrite.address, 8, &DacWrite.value, 8, HAL_MAX_DELAY);

  DacWrite.address = DAC_RCH_ATT;
  DacWrite.value = 0xE1;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
  HAL_I2C_Mem_Write(hi2c, DAC_I2C_ADDR, DacWrite.address, 8, &DacWrite.value, 8, HAL_MAX_DELAY);

  DacWrite.address = DAC_CTRL_4;
  DacWrite.value = 0b00000000;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
  HAL_I2C_Mem_Write(hi2c, DAC_I2C_ADDR, DacWrite.address, 8, &DacWrite.value, 8, HAL_MAX_DELAY);

  DacWrite.address = DAC_CTRL_7;
  DacWrite.value = 0b00000000;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
  HAL_I2C_Mem_Write(hi2c, DAC_I2C_ADDR, DacWrite.address, 8, &DacWrite.value, 8, HAL_MAX_DELAY);

  // /Testing

  /* Lower gain to avoid clipping issue */
  //DacWrite.value = AK4558_OUT_VOL_MAX;

  //DacWrite.address = AK4558_LOUT_VOL;
  //I2C_WriteToSlave(AK4558_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));

  //DacWrite.address = AK4558_ROUT_VOL;
  //I2C_WriteToSlave(AK4558_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));

  // Set sample rate to 512*fs
  // I think this is only for when dac is Master mode?
  //DacWrite.address = DAC_REG_MASTER_MODE_CTRL;
  //DacWrite.value = DAC_DEF_MASTER_MODE_CTRL;
  //I2C_WriteToSlave(WM8776_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));

  //UpdateDacVolume(255);


  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);

  dacInit = true;
}

/*******************************************************************************
 * Function Name: UpdateDacVolume
 ********************************************************************************
 * Summary: Updates the actual dac volume control with the volume parameter
 *          passed
 *
 * Parameters:
 *  volume - value of volume to be written to the dac register
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void UpdateDacVolume(uint8_t volume)
{
  uint8_t volumeMapper;
  /* Change from -127 to +127 range to 0 to 255 range */
  volume += 127;

  /* Remap from volume control to 8-bit attenuation */
  volumeMapper = 255 - (volume);

  volumeMapper = (USB_currentMute | (volume == 255)) ? \
    DAC_MAXIMUM_ATTENUATION : volumeMapper;
  UpdateDacAttenuation(volumeMapper);
}

/*******************************************************************************
 * Function Name: UpdateDacAttenuation
 ********************************************************************************
 * Summary: Updates the actual DAC DAC attenuator with the attenuation parameter
 *          passed
 *
 * Parameters:
 *  attenuation - value of attenuation to be written to the DAC register
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void UpdateDacAttenuation(uint8_t attenuation)
{
  // Analog attenuation headphone left
  DacWrite.address = DAC_LCH_ATT;
  DacWrite.value = attenuation;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));

  // Analog attenuation headphone right
  DacWrite.address = DAC_RCH_ATT;
  DacWrite.value = attenuation;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));

  // Master analog attenuation
  //DacWrite.address = DAC_REG_HP_MASTER_ATTENUATION;
  //DacWrite.value = attenuation;
  //I2C_WriteToSlave(DAC_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
}


/*******************************************************************************
 * Function Name: DacPowerDown
 ********************************************************************************
 * Summary: Powers down dac through I2C
 *
 * Parameters:
 *  None
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void DacPowerDown(void)
{
  //DacWrite.address = DAC_REG_POWER_CTRL;
  //DacWrite.value = DAC_POWER_DOWN;
  //I2C_WriteToSlave(WM8776_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
}


/*******************************************************************************
 * Function Name: DacUpdateSampleRate
 ********************************************************************************
 * Summary: Updates DAC's sample rate through I2C.  With DAC in Manual mode,
 *          THD is better, but we need to set DFS manually.
 *
 * Parameters:
 *  uint
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void DacUpdateSampleRate(uint8_t rate)
{
  // Control 2
  //DacWrite.address = DAC_REG_MASTER_MODE_CTRL;

  switch (rate)
    {
		case RATE_8KHZ:
		case RATE_11KHZ:
    case RATE_16KHZ:
		case RATE_22KHZ:
      // Not in our descriptors, so should never happen
      //Mute_LED_Write(true);
      while(1);

    case RATE_32KHZ:
		case RATE_44KHZ:
		case RATE_48KHZ:
      //DacWrite.value = DAC_ADCRATE | DAC_DACRATE;
			break;

    case RATE_88KHZ:
		case RATE_96KHZ:
      DacWrite.value = 0x22;
			break;
		default:
			break;
    }

  //I2C_WriteToSlave(WM8776_I2C_ADDR, &DacWrite.address, sizeof(DacWrite));
}

/* [] END OF FILE */
