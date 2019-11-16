#ifndef ENVELOPES_H
#define ENVELOPES_H

#define NOT_TRIGGERED 0
#define ATTACK_MODE 1
#define DECAY_MODE 2
#define SUSTAIN_MODE 3
#define RELEASE_MODE 4

void UpdateEnvelope(void);
void UART_PrintADSR();

#endif
