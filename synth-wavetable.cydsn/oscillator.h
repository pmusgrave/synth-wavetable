#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include "project.h"
    
void EnableAllOscillators(void);
void DisableAllOscillators(void);
void EnableSingleOscillator(void (*osc_enable_function)(void));
void DisableSingleOscillator(void (*osc_disable_function)(void));
double Quantize(float);
void DispatchNote(uint8 note);
void NoteOff(uint8 note);

#endif
/* [] END OF FILE */
