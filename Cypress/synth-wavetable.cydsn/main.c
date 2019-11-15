#include <project.h>
#include "AudioControl.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"
#include "midi.h"

uint32_t sample;
int8_t masterTxBuffer[BUFFER_SIZE] = {0};
int8_t masterRxBuffer[BUFFER_SIZE] = {0};
  
uint16_t attack_freq = 0;
uint16_t decay_freq = 0;
uint16_t sustain_freq = 0;
uint16_t release_freq = 0;
uint16_t waveshape = 0;

char buff[32];//output UART buffer

void ProcessSpiTx(uint8_t);
void UART_PrintNumber(int32_t);

/*******************************************************************************
* main
*******************************************************************************/
int main() {
    LED_Write(1);
    //UART_Start();
    //TxByteCounter_Start();
    //SPIByteCounter_Start();
    isr_trigger_StartEx(envelope_trigger_interrupt);
    
    CC_Timer_Start();
    isr_MIDI_CC_TimerDone_StartEx(MIDI_CC_TimerDone);
    
    //UART_UartPutString("\r\n\r\n\r\n********************\r\n");
    //UART_UartPutString("PMA Wavetable Synth\r\n");
    //UART_UartPutString("********************\r\n");
	InitAudioPath();
    //UART_UartPutString("Audio path initialized...\r\n");
    
    //init_wavetable();
    //UART_UartPutString("Wavetable initialized...\r\n");
    
    ADC_Start();
    ADC_StartConvert();
    isr_ADC_EOC_StartEx(ADC_EOC);
    
    SPI_Start();
    SPI_SpiUartWriteTxData(0u);
    while(0u == SPI_SpiUartGetRxBufferSize())
    {
        /* Wait for the first byte exchange. */
    }
    SPI_SpiUartClearRxBuffer();
    //UART_UartPutString("SPI initialized... \r\n");
    
    /*
    CodecI2CM_Start();	
	if(Codec_Init() == 0) {
    	//UART_UartPutString("Codec comm works!... \r\n");
        Codec_Activate();
	}
	else {
		//UART_UartPutString("Codec comm DOESN'T work!... \r\n");
	}
    */
    
    //I2S_Start();
    //I2S_EnableTx(); /* Unmute the TX output */ 
    //isr_I2S_underflow_StartEx(I2SUnderflow);
    
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
        
        for(int i = 0; i < 14; i++){
            ProcessSpiTx(init_msg[i]);   
        }
        
        if(trigger_flag) {
            if((midi_msg_queue.head != midi_msg_queue.tail)){// && (CTS_Read() == 0)){
                //struct midi_msg current_msg = dequeue();
                //ProcessSpiTx(current_msg.byte0);
                //ProcessSpiTx(current_msg.byte1);
                //ProcessSpiTx(current_msg.byte2);
                //ProcessSpiTx('\n');
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
            attack_freq = ADC_GetResult16(0);
            decay_freq = ADC_GetResult16(1);
            sustain_freq = ADC_GetResult16(2);
            release_freq = ADC_GetResult16(3);
            
            //attack_freq = 52275;
            //attack_freq = 60;
            update_ADC_flag = 0;
        }
        
        if(MIDI_CC_update_flag) {
            MIDI_CC_update_flag = 0;
            
            struct midi_msg attack_cc = {
                0x14,
                attack_freq>>4,
                0,
                0
            };
            
            struct midi_msg decay_cc = {
                0x15,
                decay_freq>>4,
                0,
                0
            };
            
            struct midi_msg sustain_cc = {
                0x16,
                sustain_freq>>4,
                0,
                0
            };
            
            struct midi_msg release_cc = {
                0x17,
                release_freq>>4,
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

void ProcessSpiTx(uint8_t byte){
    /* Check whether data exchange has been finished. RxDmaM and RxDmaS are 
    * configured to set an interrupt when they finish transferring all data
    * elements.
    */
    uint8_t complete = 0;
    // blocking here is probably not a good permanent solution, but it helps
    // prevent missed MIDI messages for now.
    // the better solution is most likely a queue of MIDI messages 
    while(!complete){ 
        if(0u == (CyDmaGetInterruptSourceMasked() ^ (SPI_RxDMA_CHANNEL_MASK)))// | RxDmaS_CHANNEL_MASK)))
        {
            /* Once asserted, interrupt bits remain high until cleared. */
            CyDmaClearInterruptSource(SPI_RxDMA_CHANNEL_MASK);// | RxDmaS_CHANNEL_MASK);

            /* Reset receive buffers. */
            memset((void *) masterRxBuffer, 0, BUFFER_SIZE);
            //memset((void *) slaveRxBuffer,  0, BUFFER_SIZE);
            
            SPI_start_Write(0);
            CyDelay(10);
            masterTxBuffer[0] = byte;
            /*
            masterTxBuffer[0] = midi_note.byte0;
            masterTxBuffer[1] = midi_note.byte1;
            masterTxBuffer[2] = midi_note.byte2;
            */
            
            /* Re-enable transfer. TxDmaM controls the number of bytes to be sent
            * to the slave and correspondingly the number of bytes returned by the
            * slave. Therefore it is configured to be invalidated when it
            * finishes a transfer.
            */
            SPI_TxDMA_ValidateDescriptor(0);
            SPI_TxDMA_ChEnable();
            complete = 1;
            SPI_start_Write(1);
            CyDelay(10);
        }
    }
}

//void UART_PrintNumber(int32_t number){
    //char string[30];
    //sprintf(string, "%d\n",number);
    //UART_UartPutString(string);
//}



/* [] END OF FILE */
