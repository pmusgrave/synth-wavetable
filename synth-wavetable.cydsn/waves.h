#ifndef SINEWAVES_H
#define SINEWAVES_H
    
#include <stdlib.h>
#include <project.h>
#include <AudioControl.h>
    
#define FS 48000 // samples/second
#define BASE_FREQ 40 // Hz
#define N (FS / BASE_FREQ)
#define AMPLITUDE 127
    
int8_t base_sine[(int)N];
//uint8_t base_pos_saw[(int)N];
//uint8_t base_neg_saw[(int)N];
//uint8_t base_tri[(int)N];
//uint8_t base_sq[(int)N];

void init_wavetable(void);
void generate_base_sine(int8_t*);
void generate_base_pos_saw(uint8_t*);
void generate_base_neg_saw(uint8_t*);
void generate_base_tri(uint8_t*);
void generate_base_sq(uint8_t*);

#endif
/* [] END OF FILE */
