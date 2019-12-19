#ifndef I2C_H
#define I2C_H

#include "globals.h"
#include <stdint.h>

#define DELAY_COUNT 200

void I2C_WriteToSlave(I2C_HandleTypeDef* i2c_handle, uint8_t address, uint8_t* writeBuffer, uint8_t length);
void I2C_ReadFromSlave(I2C_HandleTypeDef* i2c_handle, uint8_t address, uint8_t startIndex, uint8_t length, uint8_t *readBuffer);
void SetMaxI2CBusSpeed(void);             /* Set I2C Bus speed to I2C_MAX_BUS_SPEED value */
void SetMinI2CBusSpeed(void);             /* Set I2C Bus speed to I2C_MIN_BUS_SPEED value */
#endif

/* Constants for I2C  */
#define I2C_BUS_SPEED_50KHZ                    0
#define I2C_BUS_SPEED_100KHZ                   1
#define I2C_BUS_SPEED_400KHZ                   2
#define I2C_DELAY_COUNT                        200

#define I2C_DIVIDER_400KHZ_OPERATION           8  /* I2C block clock divider for 400KHz operation when HFCLK = 48MHz */
#define I2C_DIVIDER_100KHZ_OPERATION           30 /* I2C block clock divider for 100KHz operation when HFCLK = 48MHz */
#define I2C_DIVIDER_50KHZ_OPERATION            60 /* I2C block clock divider for 50KHz operation when HFCLK = 48MHz */
#define I2C_DIVIDER_25KHZ_OPERATION            120/* I2C block clock divider for 50KHz operation when HFCLK = 48MHz */

