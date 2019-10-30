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

extern const float midi_notes[88];

void Receive_MIDI(SPI_HandleTypeDef* hspi, uint8_t* spi_rx_buffer);

#endif
