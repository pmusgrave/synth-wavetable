#ifndef SINEWAVES_H
#define SINEWAVES_H

#include <stdlib.h>
#include <stdint.h>

#define SAMPLE_SIZE (4096)
#define AMPLITUDE (255) // divide by number of voices here?
#define AMPLITUDE_SQUARED (65025)

uint8_t base_sine[SAMPLE_SIZE];
uint8_t base_pos_saw[SAMPLE_SIZE];
uint8_t base_neg_saw[SAMPLE_SIZE];
uint8_t base_tri[SAMPLE_SIZE];
uint8_t base_sq[SAMPLE_SIZE];

uint8_t lfo_sine[256];

void init_wavetable(void);
void generate_base_sine(uint8_t*);
void generate_base_pos_saw(uint8_t*);
void generate_base_neg_saw(uint8_t*);
void generate_base_tri(uint8_t*);
void generate_base_sq(uint8_t*);

void generate_lfo_sine(uint8_t *);

#endif
/* [] END OF FILE */
