#include <project.h>
#include "AudioControl.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"
#include "midi.h"
#include "spi_master.h"

/*******************************************************************************
* main
*******************************************************************************/
int main() {
    LED_Write(1);
    isr_trigger_StartEx(envelope_trigger_interrupt);
    
    CC_Timer_Start();
    isr_MIDI_CC_TimerDone_StartEx(MIDI_CC_TimerDone);

    uint16_t attack = 0;
    uint16_t decay = 0;
    uint16_t sustain = 0;
    uint16_t release = 0;
    uint16_t waveshape = 0;
    ADC_Start();
    ADC_StartConvert();
    isr_ADC_EOC_StartEx(ADC_EOC);
    
    SpiInit();
    
    // Init USB and MIDI
    // references Cypress USB MIDI code example
    USB_Start(DEVICE, USB_DWR_VDDD_OPERATION); 
    MIDI1_UART_Start();
    //MIDI_RX_StartEx(MIDI_RX_VECT);
    //UART_UartPutString("USB MIDI initialized...\r\n");
    
    for(uint32_t i = 0; i < 10000; i++){
        CyGlobalIntDisable;
        ProcessUSBMIDI();
        CyGlobalIntEnable;
        CyDelayUs(100);
    }
    
    CyGlobalIntEnable;
    
    SPI_RxDMA_Start((void *)SPI_RX_FIFO_RD_PTR, (void *)masterRxBuffer);
    SPI_TxDMA_Start((void *)masterTxBuffer, (void *)SPI_TX_FIFO_WR_PTR);
    
    struct midi_msg test0 = {USB_MIDI_NOTE_ON, 42, 127, 0};
    struct midi_msg test1 = {USB_MIDI_NOTE_OFF, 42, 127, 0};
    struct midi_msg test2 = {USB_MIDI_NOTE_ON, 43, 127, 0};
    struct midi_msg test3 = {USB_MIDI_NOTE_OFF, 43, 127, 0};
    struct midi_msg test4 = {USB_MIDI_NOTE_ON, 44, 127, 0};
    struct midi_msg test5 = {USB_MIDI_NOTE_OFF, 44, 127, 0};

    uint8_t init_msg[14] = {"Hello world!\n"};
    for(int i = 0; i < 14; i++){
        ProcessSpiTx(init_msg[i]);   
    }
    
    for(;;) {
        ProcessUSBMIDI();
        
        if(trigger_flag) {
            if((midi_msg_queue.head != midi_msg_queue.tail)){// && (CTS_Read() == 0)){
                struct midi_msg current_msg = dequeue();
                ProcessSpiTx(current_msg.byte0);
                ProcessSpiTx(current_msg.byte1);
                ProcessSpiTx(current_msg.byte2);
                ProcessSpiTx(' ');
            }
            else {
                for(int i = 0; i < 14; i++){
                    ProcessSpiTx(init_msg[i]);   
                }
            }
        }
        else{
            for(int i = 0; i < 15; i++){
                ProcessSpiTx(init_msg[i]);
                CyDelay(2);
            }
            
            if((midi_msg_queue.head != midi_msg_queue.tail)){// && (CTS_Read() == 0)){
                struct midi_msg current_msg = dequeue();
                ProcessSpiTx(current_msg.byte0);
                ProcessSpiTx(current_msg.byte1);
                ProcessSpiTx(current_msg.byte2);
            }
            else {
                ProcessSpiTx('\n');
                enqueue(test0);
                enqueue(test1);
                enqueue(test2);
                enqueue(test3);
                enqueue(test4);
                enqueue(test5);
            }
        }
        
        if(update_ADC_flag){
            attack = ADC_GetResult16(0);
            decay = ADC_GetResult16(1);
            sustain = ADC_GetResult16(2);
            release = ADC_GetResult16(3);

            update_ADC_flag = 0;
        }
        
        if(MIDI_CC_update_flag) {
            MIDI_CC_update_flag = 0;
            
            struct midi_msg attack_cc = {
                0x14,
                (uint8_t)(attack>>4),
                0,
                0
            };
            
            struct midi_msg decay_cc = {
                0x15,
                (uint8_t)(decay>>4),
                0,
                0
            };
            
            struct midi_msg sustain_cc = {
                0x16,
                (uint8_t)(sustain>>4),
                0,
                0
            };
            
            struct midi_msg release_cc = {
                0x17,
                (uint8_t)(release>>4),
                0,
                0
            };
            
            enqueue(attack_cc);
            enqueue(decay_cc);
            enqueue(sustain_cc);
            enqueue(release_cc);
            
            Green_LED_Write(~Green_LED_Read());
        }
    }
}

/* [] END OF FILE */
