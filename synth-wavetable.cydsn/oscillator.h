#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include "project.h"
    
struct voice {
    uint32_t env_index;
    uint16_t env_multiplier;
    uint8_t current_env_mode;
    int freq;
    uint8_t note_index;
};

void EnableAllOscillators(void);
void DisableAllOscillators(void);
void EnableSingleOscillator(void (*osc_enable_function)(void));
void DisableSingleOscillator(void (*osc_disable_function)(void));
double Quantize(float);
void DispatchNote(uint8 note);
void NoteOff(uint8 note);

void ProcessVoice(struct voice* v);

#endif
/* [] END OF FILE */
