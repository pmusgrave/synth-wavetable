#ifndef SINEWAVES_H
#define SINEWAVES_H
    
#include <stdlib.h>
#include <project.h>
#include <AudioControl.h>
    
#define FS 48000 // samples/second
#define BASE_FREQ 200 // Hz
#define N (FS / BASE_FREQ)
#define AMPLITUDE 127
    
int8_t base_sine[(int)N];
//int8_t base_pos_saw[(int)N];
//int8_t base_neg_saw[(int)N];
//int8_t base_tri[(int)N];
//int8_t base_sq[(int)N];

void init_wavetable(void);
void generate_base_sine(uint8_t*);
void generate_base_pos_saw(int8_t*);
void generate_base_neg_saw(int8_t*);
void generate_base_tri(int8_t*);
void generate_base_sq(int8_t*);

#endif
/* [] END OF FILE */
