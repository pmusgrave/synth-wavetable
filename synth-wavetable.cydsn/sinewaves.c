#include <project.h>
#include <AudioControl.h>
#include "sinewaves.h"
#include <math.h>

void init_wavetable(){   
    //double * base_sine = malloc(((int)N) * sizeof(double)); // one period's worth of samples at freq
    //double * base_pos_saw = malloc(((int)N) * sizeof(double));
    //double * base_neg_saw = malloc(((int)N) * sizeof(double));
    //double * base_tri = malloc(((int)N) * sizeof(double));
    //double * base_sq = malloc(((int)N) * sizeof(double)); // probably makes no sense to store this many samples of a square wave
    
    generate_base_sine(base_sine);
    generate_base_pos_saw(base_pos_saw);
    generate_base_neg_saw(base_neg_saw);
    generate_base_tri(base_tri);
    generate_base_sq(base_sq);
}

void generate_base_sine(double* buffer){
  double amplitude = 127;

  for(int i = 0; i < N; i++){
    double delta = 2*M_PI/N;
    double x = delta * i;
    buffer[i] = amplitude * sin(x);
  }
}

void generate_base_pos_saw(double* buffer){
  double amplitude = 128;

  for(int i = 0; i < N; i++){
    buffer[i] = amplitude * (i/N);
  }
}

void generate_base_neg_saw(double* buffer){
  double amplitude = 128;

  for(int i = 0; i < N; i++){
    buffer[(int)N-i-1] = amplitude * (i/N);
  }
}

void generate_base_tri(double* buffer){
  double amplitude = 128;

  for(int i = 0; i < N/2; i++){
    buffer[i] = amplitude * (2*i/N);
  }
  for(int i = N/2; i < N; i++){
    buffer[i] = amplitude * (2*(N-i)/N);
  }
}

void generate_base_sq(double* buffer){
  double amplitude = 128;

  for(int i = 0; i < N; i++){
    if(i < N/2){
      buffer[i] = amplitude;
    }
    else{
      buffer[i] = 0;
    }
  }
}
/* [] END OF FILE */
