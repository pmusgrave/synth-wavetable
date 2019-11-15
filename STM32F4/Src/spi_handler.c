#include "main.h"
#include "globals.h"
#include "spi_handler.h"

struct byte_queue spi_byte_queue;
uint8_t rx_buffer;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  if(HAL_SPI_GetState(&hspi5) == HAL_SPI_STATE_READY){
    HAL_SPI_Receive(&hspi5, &rx_buffer, 1, 500);
    HAL_UART_Transmit(&huart1, &rx_buffer, 1, 100);
  }
  rx_buffer = 0;

  __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}

void enqueue_byte (uint8_t byte) {
  spi_byte_queue.queue[spi_byte_queue.head++] = byte;
}

uint8_t dequeue_byte(void) {
  return spi_byte_queue.queue[spi_byte_queue.tail++];
}
