#ifndef SINEWAVES_H
#define SINEWAVES_H
    
#include <stdlib.h>
#include <project.h>
#include <AudioControl.h>
    
#define FS 48000 // samples/second
#define BASE_FREQ 20 // Hz
#define N (FS / BASE_FREQ)
#define AMPLITUDE 127
    
//double base_sine[(int)N];
//double base_pos_saw[(int)N];
//double base_neg_saw[(int)N];
//double base_tri[(int)N];
double base_sq[(int)N];

void init_wavetable(void);
void generate_base_sine(double*);
void generate_base_pos_saw(double*);
void generate_base_neg_saw(double*);
void generate_base_tri(double*);
void generate_base_sq(double*);
void output(double*, double);

#endif
/* [] END OF FILE */
