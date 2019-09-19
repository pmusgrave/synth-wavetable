#ifndef SINEWAVES_H
#define SINEWAVES_H
    
#include <stdlib.h>
#include <project.h>
#include <AudioControl.h>
    
#define FS 48000 // samples/second
#define BASE_FREQ 100 // Hz
#define N (FS / BASE_FREQ)
    
double base_sine[N];
double base_pos_saw[N];
double base_neg_saw[N];
double base_tri[N];
double base_sq[N];

void init_wavetable(void);
void generate_base_sine(double*);
void generate_base_pos_saw(double*);
void generate_base_neg_saw(double*);
void generate_base_tri(double*);
void generate_base_sq(double*);
void output(double*, double);

#endif
/* [] END OF FILE */
