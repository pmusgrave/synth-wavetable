#include "oscillator.h"
#include "main.h"
#include "globals.h"
#include "midi.h"
#include "waves.h"

volatile uint8_t update_value_flag = 0;
volatile uint32_t phase_accumulator[VOICES] = {0};
uint16_t output_val = 0;
uint8_t* waveshape1 = base_sine;
uint8_t* waveshape2 = base_sine;

void update_output_value() {
  float val = 0;
  output_val = 0;
  for(int i = 0; i < VOICES; i++) {
    phase_accumulator[i] += (uint32_t)(midi_notes[note_freq[i]]*DDS_SCALE_FACTOR);
    val += ((waveshape1[(phase_accumulator[i]>>10)%4096] + waveshape2[(phase_accumulator[i]>>10)%4096]) * envelope[i]) / (2*AMPLITUDE);
  }

  output_val = (uint16_t) (val / VOICES);
}
