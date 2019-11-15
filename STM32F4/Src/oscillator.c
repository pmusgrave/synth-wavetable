#include "oscillator.h"
#include "main.h"
#include "globals.h"
#include "midi.h"
#include "waves.h"

volatile uint8_t update_value_flag = 0;
volatile uint32_t phase_accumulator[VOICES] = {0};
volatile uint8_t output_val = 0;

void UpdateOutputValue() {
  float val = 0;
  output_val = 0;
  for(int i = 0; i < VOICES; i++) {
    phase_accumulator[i] += (uint32_t)(midi_notes[note_freq[i]]*DDS_SCALE_FACTOR);
    val += ((base_sine[(phase_accumulator[i]>>10)%4096] + 0*base_pos_saw[(phase_accumulator[i]>>10)%4096]) * envelope[i] * lfo[i]) / (2*AMPLITUDE_SQUARED);
  }

  output_val = (uint8_t) (val / VOICES);
}
