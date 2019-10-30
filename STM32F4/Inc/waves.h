#ifndef SINEWAVES_H
#define SINEWAVES_H

#include <stdlib.h>
#include <stdint.h>

#define N 4096
#define AMPLITUDE (126) // divide by number of voices here?

uint8_t base_sine[N];
uint8_t base_pos_saw[N];
uint8_t base_neg_saw[N];
uint8_t base_tri[N];
uint8_t base_sq[N];

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
