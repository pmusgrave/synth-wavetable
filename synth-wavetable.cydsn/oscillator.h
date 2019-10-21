#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include "project.h"
    
struct voice {
    uint32_t env_index;
    uint16_t env_multiplier;
    uint8_t current_env_mode;
    uint16_t freq;
    uint8_t note_index;
    uint8_t MIDI_note_status;
    uint8_t MIDI_velocity;
};

void EnableAllOscillators(void);
void DisableAllOscillators(void);
void EnableSingleOscillator(void (*osc_enable_function)(void));
void DisableSingleOscillator(void (*osc_disable_function)(void));
double Quantize(float);
void DispatchNote(uint8* midi_msg);
void NoteOff(uint8* midi_msg);

void ProcessVoice(struct voice* v);

#endif
/* [] END OF FILE */
