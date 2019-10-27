#ifndef MIDI_H
#define MIDI_H

#include "main.h"
#include <stdint.h>

#define MIDI_NOTE_ON 0x90
#define MIDI_NOTE_OFF 0x80

struct midi_note_msg {
  uint8_t command;
  uint8_t note;
  uint8_t velocity;
};

extern const uint16_t midi_notes[127];

void Receive_MIDI(SPI_HandleTypeDef* hspi);

#endif
