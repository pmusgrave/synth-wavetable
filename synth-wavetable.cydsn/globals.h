#include <project.h>
#include "oscillator.h"

#define     BUFFER_SIZE        32

/* LED control defines. LED is active low. */
#define     LED_ON              0
#define     LED_OFF             1

extern uint32_t sample;


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
extern uint16_t attack_freq;
extern uint16_t decay_freq;
extern uint16_t sustain_freq;
extern uint16_t release_freq;
extern uint16_t waveshape;

struct voice v1;
struct voice v2;
struct voice v3;
struct voice v4;
struct voice v5;
struct voice v6;
struct voice v7;
struct voice v8;

extern volatile uint8_t DMA_done_flag;
extern volatile uint8_t DMA_counter;
extern volatile uint8_t FIFO_DMA_REQ_FLAG;
extern volatile uint8_t update_ADC_flag;
extern volatile uint8_t trigger_flag;

extern int8_t output_buffer[];
extern int8_t output_buffer2[];
extern uint32_t buffer_index;
extern uint32_t buffer_index2;


// move these into envelope header file later
#define NOT_TRIGGERED 0
#define ATTACK_MODE 1
#define DECAY_MODE 2
#define SUSTAIN_MODE 3
#define RELEASE_MODE 4
extern uint8_t current_env_mode;

/* [] END OF FILE */
