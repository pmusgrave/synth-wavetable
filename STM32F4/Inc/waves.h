#ifndef SINEWAVES_H
#define SINEWAVES_H

#include <stdlib.h>
#include <stdint.h>

#define FS 48000 // samples/second
#define N 4096
#define VOICES 1
#define AMPLITUDE (126/VOICES) // divide by number of voices here?


uint16_t base_sine[(int)N];
//int8_t base_pos_saw[(int)N];
//int8_t base_neg_saw[(int)N];
//int8_t base_tri[(int)N];
//int8_t base_sq[(int)N];

uint8_t lfo_sine[256];

void init_wavetable(void);
void generate_base_sine(uint16_t*);
void generate_base_pos_saw(int8_t*);
void generate_base_neg_saw(int8_t*);
void generate_base_tri(int8_t*);
void generate_base_sq(int8_t*);

void generate_lfo_sine(uint8_t *);

#endif
/* [] END OF FILE */
