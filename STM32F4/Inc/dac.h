#ifndef DAC_H
#define DAC_H

#include "globals.h"
#include <stdint.h>

#define DAC_I2C_ADDR			(0x1A)

/**************************************************************************************************
 * Register Addresses for Dac I2C Interface
 **************************************************************************************************/
#define DAC_REG_DP_MODE_SELECT                (0x02)  /*DSD/PCM SELECTION*/
#define DAC_REG_DIGITAL_FILTER_SETTING_SD     (0x01)
#define DAC_REG_DIGITAL_FILTER_SETTING_SLOW   (0x02)
#define DAC_REG_AUTO_MAN_MODE_SETTING         (0x00)
#define DAC_REG_INTERFACE_SET                 (0x00)
#define DAC_REG_LCH_VOLUME                    (0x03)
#define DAC_REG_RCH_VOLUME                    (0x04)
#define DAC_REG_SOUND_QUALITY                 (0x08)
#define DAC_REG_MUTE                          (0x01)
#define DAC_REG_RESET                         (0x00)

/**************************************************************************************************
 * Bit number locations within each Register Address
 **************************************************************************************************/
#define DAC_BIT_DP_MODE_SELECT                (7)
#define DAC_BIT_DIGITAL_FILTER_SETTING_SD     (5)
#define DAC_BIT_DIGITAL_FILTER_SETTING_SLOW   (0)
#define DAC_BIT_AUTO_MAN_MODE_SETTING         (7)
#define DAC_BIT_INTERFACE_SET                 (1)
#define DAC_BIT_LCH_VOLUME                    (0)
#define DAC_BIT_RCH_VOLUME                    (0)
#define DAC_BIT_SOUND_QUALITY                 (0)
#define DAC_BIT_MUTE                          (0)

/**************************************************************************************************
 * Bit values for desired initial settings
 **************************************************************************************************/
#define DAC_DATA_DP_MODE_SELECT                (0)
#define DAC_DATA_DIGITAL_FILTER_SETTING_SD     (0)
#define DAC_DATA_DIGITAL_FILTER_SETTING_SLOW   (0)
#define DAC_DATA_AUTO_MAN_MODE_SETTING         (1)
#define DAC_DATA_INTERFACE_SET                 (010)
#define DAC_DATA_LCH_VOLUME                    (0xFF)
#define DAC_DATA_RCH_VOLUME                    (0XFF)
#define DAC_DATA_SOUND_QUALITY                 (00)
#define DAC_DATA_MUTE                          (0)

#define DAC_RESET_WAIT_DELAY				(10)	 /* in milli seconds */

#define DAC_HP_DEFAULT_VOLUME				(0)
#define DAC_HP_VOLUME_MAX					(255) 	/* 256 levels including MUTE, 0.5dB steps */
#define DAC_HP_MUTE_VALUE					(0x2F) 	/* Writing <= 0x2F mutes the headphone output */

/* Value format: bit[0] - BOSR, bit[4:1] - SR[3:0] */
#define DAC_SRATE_NORMAL_48KHZ_256FS		(0x00) 	/* BOSR = 0 for 256fs and SRx = 0b0000 for 48 KHz in Normal mode */
#define DAC_SRATE_NORMAL_44KHZ_256FS		(0x20) 	/* BOSR = 0 for 256fs and SRx = 0b1000 for 44.1 KHz in Normal mode */

#define DAC_DEF_SAMPLING_RATE				DAC_SRATE_NORMAL_48KHZ_256FS
#define DAC_DEF_ANALOG_CTRL				(DAC_ANALOG_CTRL_INSEL | DAC_ANALOG_CTRL_DACSEL | DAC_ANALOG_CTRL_SIDETONE)
#define DAC_DEF_DIGITAL_CTRL				(DAC_DIGITAL_CTRL_HPOR)
#define DAC_DEF_POWER_CTRL				(DAC_POWER_CTRL_CLKOUTPD | DAC_POWER_CTRL_OSCPD | DAC_POWER_CTRL_LINEINPD)
#define DAC_CTRL_RESET                    (0b00000000)

uint8_t Dac_Init(I2C_HandleTypeDef*);
uint8_t Dac_SelectMicInputToADC(void);
uint8_t Dac_AdjustBothHeadphoneVolume(uint8_t volume);
uint8_t Dac_MuteMic(_Bool isMuteOrUnmute);
uint8_t Dac_SetMicBoost(_Bool micBoost);
uint8_t Dac_SetSamplingRate(uint8_t srCtrlField);
uint8_t Dac_Activate(void);
uint8_t Dac_Deactivate(void);
uint8_t Dac_ResetOverI2C(void);
uint8_t Dac_SendData(uint8_t regAddr, uint16_t data);
uint8_t Dac_PowerOffControl(uint32_t powerOffMask);
uint8_t Dac_PowerOnControl(uint32_t powerOnMask);

#endif /* #ifndef DAC_H */

/* [] END OF FILE */
