#ifndef DAC_H
#define DAC_H

#include "globals.h"
#include <stdint.h>

void InitDac(I2C_HandleTypeDef* i2c_handle);
void UpdateDacVolume(uint8_t volume);
void UpdateDacAttenuation(uint8_t attenuation);
void DacPowerDown(void);
void DacUpdateSampleRate(uint8_t rate);

/* Clock Rates */
#define RATE_48KHZ                                  0x00
#define RATE_44KHZ                                  0x01
#define RATE_32KHZ                                  0x02

#define RATE_16KHZ                                  0x03
#define RATE_8KHZ                                   0x04
#define RATE_11KHZ                                  0x05
#define RATE_22KHZ                                  0x06
#define RATE_88KHZ                                  0x07
#define RATE_96KHZ                                  0x08

#define BUS_CLOCK_DIVIDE_BY_8                        0x07
#define BUS_CLOCK_DIVIDE_BY_16                       0x0F
#define BUS_CLOCK_DIVIDE_BY_2                        0x01

#define ANALOG_AUX_INPUT                             0

#define SAMPLING_RATE_96KHZ                          96000
#define SAMPLING_RATE_88KHZ                          88200
#define SAMPLING_RATE_48KHZ                          48000
#define SAMPLING_RATE_32KHZ                          32000
#define SAMPLING_RATE_44KHZ                          44100

#define DAC_MAX_VOLUME_VALUE                 0xFF
#define DAC_MIN_VOLUME_VALUE                 0x00
#define DAC_MAXIMUM_ATTENUATION              0xFF

/*******************************************************************************
* DAC definitions
********************************************************************************/

// Chip Address 1 pin
#ifndef DAC_CAD1
#define DAC_CAD1 0
#endif

// Chip Address 0 pin
#ifndef DAC_CAD0
#define DAC_CAD0 0
#endif

#define DAC_I2C_ADDR (0b0010000 + (DAC_CAD1<<1) + DAC_CAD0)

#define DAC_OUT_VOL_0dB		0xFF
#define DAC_OUT_VOL_MAX		0xFB  // Lowered by -2 dB to avoid clipping issue
#define DAC_OUT_VOL_MUTE	0x00

#define PDN_NORMAL          1
#define PDN_POWER_DN_RST    0

/**************************************************************************************************
* Register Addresses for DAC I2C Interface
**************************************************************************************************/
#define DAC_CTRL_1                            (0x00)
#define DAC_CTRL_2                            (0x01)
#define DAC_CTRL_3                            (0x02)
#define DAC_LCH_ATT                           (0x03)
#define DAC_RCH_ATT                           (0x04)
#define DAC_CTRL_4                            (0x05)
#define DAC_CTRL_5                            (0x06)
#define DAC_CTRL_6                            (0x07)
#define DAC_CTRL_7                            (0x08)
#define DAC_CTRL_8                            (0x09)

#define DAC_RESET_WAIT_DELAY				(100)	 /* in milli seconds */

typedef struct DacConfig
{
    uint8_t address;
    uint8_t value;
} DacRegister;

extern uint8_t dacInit;

#endif /* #ifndef DAC_H */

/* [] END OF FILE */
