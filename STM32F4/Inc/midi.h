#ifndef MIDI_H
#define MIDI_H

#include "main.h"
#include "globals.h"
#include <stdint.h>

#define MIDI_NOTE_ON 0x90
#define MIDI_NOTE_OFF 0x80
#define ATTACK_CC 0x14
#define DECAY_CC 0x15
#define SUSTAIN_CC 0x16
#define RELEASE_CC 0x17

struct midi_msg {
  uint8_t byte0;
  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
};

struct msg_queue {
  uint8_t head;
  uint8_t tail;
  struct midi_msg queue[MAX_QUEUE_SIZE];
};

extern const float midi_notes[88];

void Receive_MIDI(SPI_HandleTypeDef* hspi, uint8_t* spi_rx_buffer);
void enqueue(struct midi_msg midi_msg);
struct midi_msg dequeue(void);

#endif
