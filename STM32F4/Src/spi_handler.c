#include "main.h"
#include "globals.h"
#include "spi_handler.h"

struct byte_queue spi_byte_queue;
uint8_t spi_flag = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  //spi_flag = 1;
  //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET);
}

uint8_t SPI_ReceiveByte(){
  uint8_t rx_buffer = 0;
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET);
  //if(spi_flag){
  //    spi_flag = 0;

  if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6) == GPIO_PIN_RESET){
      
    HAL_SPI_Receive(&hspi5, &rx_buffer, 1, HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1, &rx_buffer, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET);
    // MIDI_flag = 1;
    //}
   }

  return rx_buffer;
}

void enqueue_byte (uint8_t byte) {
  spi_byte_queue.queue[spi_byte_queue.head++] = byte;
}

uint8_t dequeue_byte(void) {
  return spi_byte_queue.queue[spi_byte_queue.tail++];
}
