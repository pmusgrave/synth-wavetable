#include "r2rdac.h"
#include "main.h"

void Update_R2R_DAC() {
  /*
  ((output_val>>0)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
  ((output_val>>1)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
  ((output_val>>2)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
  ((output_val>>3)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
  ((output_val>>4)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
  ((output_val>>5)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
  ((output_val>>6)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
  ((output_val>>7)&0x0001)==1 ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
  */
}