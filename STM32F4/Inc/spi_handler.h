#ifndef SPI_HANDLER_H
#define SPI_HANDLER_H

#include "globals.h"

struct byte_queue {
  uint8_t head;
  uint8_t tail;
  uint8_t queue[MAX_QUEUE_SIZE];
};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
uint8_t SPI_ReceiveByte(void);
void enqueue_byte(uint8_t);
uint8_t dequeue_byte(void);

#endif
