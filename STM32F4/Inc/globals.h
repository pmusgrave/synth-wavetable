#ifndef GLOBALS_H
#define GLOBALS_H

#include "main.h"

#define DDS_SCALE_FACTOR 89.4745833
#define VOICES 16
#define MAX_QUEUE_SIZE 255

extern SPI_HandleTypeDef hspi5;
extern UART_HandleTypeDef huart1;
extern const float inv_voices;
extern volatile uint32_t envelope_index[];
extern volatile float envelope[];
extern volatile uint8_t env_state[];
extern volatile uint8_t note_on[];
extern volatile uint8_t note_freq[];
extern volatile uint32_t phase_accumulator[VOICES];
extern uint16_t output_val;
extern uint8_t* waveshape1;
extern uint8_t* waveshape2;
extern volatile uint32_t lfo_phase_accumulator[];
extern volatile uint16_t lfo_freq[];
extern volatile uint8_t lfo[];
extern volatile uint8_t global_lfo;
extern volatile uint8_t global_lfo_freq;
extern volatile uint32_t global_lfo_phase_accumulator;
extern uint8_t attack;
extern uint8_t decay;
extern uint8_t sustain;
extern uint8_t release;

// probably need to refactor these SPI flags
/* extern volatile uint8_t note_on_flag; */
/* extern volatile uint8_t note_off_flag; */
/* extern volatile uint8_t attack_cc_flag; */
/* extern volatile uint8_t decay_cc_flag; */
/* extern volatile uint8_t sustain_cc_flag; */
/* extern volatile uint8_t release_cc_flag; */

extern volatile uint8_t update_value_flag;
extern uint8_t spi_flag;
extern struct byte_queue spi_byte_queue;
extern uint8_t rx_buffer;

extern volatile struct midi_msg current_midi_msg;
extern struct msg_queue  midi_msg_queue;
extern volatile uint8_t MIDI_flag;

#endif
