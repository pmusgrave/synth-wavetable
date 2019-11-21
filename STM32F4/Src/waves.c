#include "waves.h"
#include "globals.h"
#include <math.h>
#include <stdint.h>

const float inv_voices = 1.0/VOICES;

void init_wavetable(){
    generate_base_sine(base_sine);
    generate_base_pos_saw(base_pos_saw);
    generate_base_neg_saw(base_neg_saw);
    generate_base_tri(base_tri);
    generate_base_sq(base_sq);
    generate_lfo_sine(lfo_sine);
}

void generate_base_sine(uint8_t* buffer){
  for(int i = 0; i < SAMPLE_SIZE; i++){
    double delta = 2*M_PI/SAMPLE_SIZE;
    double x = delta * i;
    buffer[i] = (AMPLITUDE/2) * sin(x) + (AMPLITUDE/2);
  }
}

void generate_base_pos_saw(uint8_t* buffer){
  for(int i = 0; i < SAMPLE_SIZE; i++){
    buffer[i] = (AMPLITUDE * i)/SAMPLE_SIZE;
  }
}

void generate_base_neg_saw(uint8_t* buffer){
  for(int i = 0; i < SAMPLE_SIZE; i++){
    buffer[(int)SAMPLE_SIZE-i-1] = (AMPLITUDE * i)/SAMPLE_SIZE;
  }
}

void generate_base_tri(uint8_t* buffer){
  for(int i = 0; i < SAMPLE_SIZE/2; i++){
    buffer[i] = (AMPLITUDE * 2*i)/SAMPLE_SIZE;
  }
  for(int i = SAMPLE_SIZE/2; i < SAMPLE_SIZE; i++){
    buffer[i] = (AMPLITUDE * 2*(SAMPLE_SIZE-i))/SAMPLE_SIZE;
  }
}

void generate_base_sq(uint8_t* buffer){
  for(int i = 0; i < SAMPLE_SIZE; i++){
    if(i < SAMPLE_SIZE/2){
      buffer[i] = AMPLITUDE;
    }
    else{
      buffer[i] = 0;
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
