#include <project.h>

extern uint16_t freq;
extern uint16_t freq2;
extern uint16_t freq3;
extern uint16_t freq4;
extern uint16_t freq5;
extern uint16_t freq;
extern uint16_t freq7;
extern uint16_t freq8;
extern uint32_t lfo_freq;
extern uint16_t lfo_multiplier;
extern uint16_t envelope_multiplier;
extern uint8_t attack_mode;
extern uint8_t decay_mode;
extern uint8_t sustain_mode;
extern uint8_t release_mode;

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
