#ifndef GLOBALS_H
#define GLOBALS_H

#include "main.h"

#define DDS_SCALE_FACTOR 89.4745833
#define VOICES 16

extern SPI_HandleTypeDef hspi5;
extern UART_HandleTypeDef huart1;
extern volatile uint32_t envelope_index[];
extern volatile float envelope[];
extern volatile uint8_t env_state[];
extern volatile uint8_t note_on[];
extern volatile uint8_t note_freq[];
extern volatile uint32_t lfo_phase_accumulator[];
extern volatile uint16_t lfo_freq[];
extern volatile uint8_t lfo[];
extern uint8_t attack;
extern uint8_t decay;
extern uint8_t sustain;
extern uint8_t release;

extern struct byte_queue spi_byte_queue;
extern uint8_t rx_buffer;

#endif
