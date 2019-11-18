#include "lfo.h"
#include "globals.h"
#include "waves.h"

volatile uint32_t lfo_phase_accumulator[VOICES] = {0};
volatile uint16_t lfo_freq[VOICES] = {0};
volatile uint8_t lfo[VOICES] = {0};
volatile uint8_t global_lfo = 0;
volatile uint8_t global_lfo_freq = 1;
volatile uint32_t global_lfo_phase_accumulator = 0;

void update_lfos() {
  for(int i = 0; i < VOICES; i++) {
    lfo_phase_accumulator[i] += (uint32_t)(lfo_freq[i] * (DDS_SCALE_FACTOR/10));
    lfo[i] = base_tri[(lfo_phase_accumulator[i]>>10)%4096];
    // lfo[i] = 255;
  }

  global_lfo_phase_accumulator += (uint32_t)(global_lfo_freq * (DDS_SCALE_FACTOR/10));
  global_lfo = base_tri[(global_lfo_phase_accumulator>>10)%4096];
}
