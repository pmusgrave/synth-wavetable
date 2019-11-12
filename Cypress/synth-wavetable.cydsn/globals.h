#include <project.h>
#include "oscillator.h"

#define     BUFFER_SIZE        1

/* LED control defines. LED is active low. */
#define     LED_ON              0
#define     LED_OFF             1

extern uint32_t sample;
extern int8_t masterTxBuffer[BUFFER_SIZE];
extern int8_t masterRxBuffer[BUFFER_SIZE];
extern volatile int8_t* current_buffer;

extern uint32_t lfo_freq;
extern uint16_t lfo_multiplier;
extern uint16_t envelope_multiplier;
extern uint16_t attack_freq;
extern uint16_t decay_freq;
extern uint16_t sustain_freq;
extern uint16_t release_freq;
extern uint16_t waveshape;

extern volatile uint8_t DMA_done_flag;
extern volatile uint8_t DMA_counter;
extern volatile uint8_t FIFO_DMA_REQ_FLAG;
extern volatile uint8_t update_ADC_flag;
extern volatile uint8_t trigger_flag;

extern int8_t output_buffer[];
extern int8_t output_buffer2[];
extern uint32_t buffer_index;
extern uint32_t buffer_index2;

/* [] END OF FILE */
