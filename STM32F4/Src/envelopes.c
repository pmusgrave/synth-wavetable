#include "globals.h"
#include "envelopes.h"
#include "waves.h"
#include "midi.h"

volatile uint32_t envelope_index[VOICES] = {0};
volatile float envelope[VOICES] = {0};
volatile uint8_t env_state[VOICES];
volatile uint8_t note_on[88] = {0};
volatile uint8_t note_freq[VOICES] = {0};
uint8_t attack = 255;
uint8_t decay = 255;
uint8_t sustain = 200;
uint8_t release = 255;

void update_envelope() {
  for(int i = 0; i < VOICES; i++){
    //if(note_on[i] == MIDI_NOTE_OFF){
    //  env_state[i] = RELEASE_MODE;
    //}

    switch(env_state[i]){
    case NOT_TRIGGERED:
      envelope_index[i] = 0;
      envelope[i] = 0;
      break;
    case ATTACK_MODE:
      //    if((UINT32_MAX - envelope_index) < DDS_SCALE_FACTOR){
      if(envelope_index[i] <= 4200000) {
        envelope_index[i] += (uint32_t)(attack * DDS_SCALE_FACTOR);
        envelope[i] = base_pos_saw[(envelope_index[i]>>10)%4096];
      }
      else {
        // env_state++;
        envelope_index[i] = 0;
        env_state[i] = DECAY_MODE;
      }
      break;
    case DECAY_MODE:
      if(base_neg_saw[(envelope_index[i]>>10)%4096] >= sustain){
        envelope_index[i] += (uint32_t)(decay * DDS_SCALE_FACTOR);
        envelope[i] = base_neg_saw[(envelope_index[i]>>10)%4096];
      }
      else {
        //envelope_index[i] = 0;
        env_state[i]++;
        //env_state[i] = RELEASE_MODE;
      }
      break;
    case SUSTAIN_MODE:
      //env_state[i]++;
      break;
    case RELEASE_MODE:
      //      if((UINT32_MAX - envelope_index) < DDS_SCALE_FACTOR){
      if(envelope_index[i] <= 4200000){
        envelope_index[i] += (uint32_t)(release * DDS_SCALE_FACTOR);
        envelope[i] = base_neg_saw[(envelope_index[i]>>10)%4096];
      }
      else {
        env_state[i] = NOT_TRIGGERED;
        note_on[i] = MIDI_NOTE_OFF;
        envelope_index[i] = 0;
        envelope[i] = 0;
        lfo_phase_accumulator[i] = 0;
        lfo[i] = 0;
      }
      break;
    }
  }
}


void UART_PrintADSR(UART_HandleTypeDef* huart){
  uint8_t uart_tx_buffer;
  uart_tx_buffer = attack;
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
  uart_tx_buffer = ' ';
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
  uart_tx_buffer = decay;
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
  uart_tx_buffer = ' ';
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
  uart_tx_buffer = sustain;
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
  uart_tx_buffer = ' ';
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
  uart_tx_buffer = release;
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
  uart_tx_buffer = '\n';
  HAL_UART_Transmit(huart, &uart_tx_buffer, 1, 50);
}
