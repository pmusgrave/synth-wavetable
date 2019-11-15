#ifndef USB_MIDI_H
#define USB_MIDI_H

/*******************************************************************************
* USB and MIDI stuff
* references Cypress MIDI code examples
*******************************************************************************/
#include <project.h>
#define DEVICE                  (0u)
#define MIDI_MSG_SIZE           (4u)

/*MIDI Message Fields */
#define MIDI_MSG_TYPE           (0u)
#define MIDI_NOTE_NUMBER        (1u)
#define MIDI_NOTE_VELOCITY      (2u)

#define MAX_QUEUE_SIZE 255
    
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

// volatile uint8_t MIDI_RX_flag = 0;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void enqueue(struct midi_msg midi_msg);
struct midi_msg dequeue(void);
void ProcessUSBMIDI(void);

#endif
/* [] END OF FILE */
