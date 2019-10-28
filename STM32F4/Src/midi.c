#include "midi.h"
#include <stdint.h>

const uint16_t midi_notes[127] = {
  275,
  291,
  309,
  327,
  346,
  367,
  389,
  412,
  437,
  462,
  490,
  519,
  550,
  583,
  617,
  654,
  693,
  734,
  778,
  824,
  873,
  925,
  980,
  1038,
  1100,
  1165,
  1235,
  1308,
  1386,
  1468,
  1556,
  1648,
  1746,
  1850,
  1960,
  2077,
  2200,
  2331,
  2469,
  2616,
  2772,
  2937,
  3111,
  3296,
  3492,
  3700,
  3920,
  4153,
  4400,
  4662,
  4939,
  5233,
  5544,
  5873,
  6223,
  6593,
  6985,
  7400,
  7840,
  8306,
  8800,
  9323,
  9878,
  10465,
  11087,
  11747,
  12445,
  13185,
  13969,
  14800,
  15680,
  16612,
  17600,
  18647,
  19755,
  20930,
  22175,
  23493,
  24890,
  26370,
  27938,
  29600,
  31360,
  33224,
  35200,
  37293,
  39511,
  41860
};

void Receive_MIDI(SPI_HandleTypeDef* hspi, uint8_t* spi_rx_buffer) {
  //  if(!HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_6) &&
  //     HAL_SPI_GetState(hspi) == HAL_SPI_STATE_READY){
    uint8_t data = 0xAB;
    HAL_SPI_TransmitReceive_IT(hspi, &data, spi_rx_buffer, 3);
    //  }
}
