#include "waves.h"
#include <math.h>
#include <stdint.h>

void init_wavetable(){   
    generate_base_sine(base_sine);
    //generate_base_pos_saw(base_pos_saw);
    //generate_base_neg_saw(base_neg_saw);
    //generate_base_tri(base_tri);
    //generate_base_sq(base_sq);

    generate_lfo_sine(lfo_sine);
}

void generate_base_sine(uint16_t* buffer){
  for(int i = 0; i < N; i++){
    double delta = 2*M_PI/N;
    double x = delta * i;
    buffer[i] = (65536/2) * sin(x) + (65536/2);
  }
}

void generate_base_pos_saw(int8_t* buffer){
  for(int i = 0; i < N; i++){
    buffer[i] = (AMPLITUDE * i)/N;
  }
}

void generate_base_neg_saw(int8_t* buffer){
  for(int i = 0; i < N; i++){
    buffer[(int)N-i-1] = (AMPLITUDE * i)/N;
  }
}

void generate_base_tri(int8_t* buffer){
  for(int i = 0; i < N/2; i++){
    buffer[i] = (AMPLITUDE * 2*i)/N;
  }
  for(int i = N/2; i < N; i++){
    buffer[i] = (AMPLITUDE * 2*(N-i))/N;
  }
}

void generate_base_sq(int8_t* buffer){
  for(int i = 0; i < N; i++){
    if(i < N/2){
      buffer[i] = AMPLITUDE;
    }
    else{
      buffer[i] = -AMPLITUDE;
    }
  }
}

void generate_lfo_sine(uint8_t* buffer){
    for(int i = 0; i < 256; i++){
        double delta = 2*M_PI/256;
        double x = delta * i;
        buffer[i] = sin(x) * 126 + 126;
    }
}
/* [] END OF FILE */
