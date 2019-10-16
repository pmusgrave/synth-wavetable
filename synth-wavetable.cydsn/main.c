#include <project.h>
#include "Codec.h"
#include "AudioControl.h"
#include "waves.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"

#include "oscillator.h"

#define SPI_CMD_FREQ 1
#define SPI_CMD_ENV 2

uint32_t sample;
int8 masterTxBuffer[BUFFER_SIZE] = {1};
int8 masterRxBuffer[BUFFER_SIZE] = {0};

uint8_t current_env_mode = 0;
uint16_t attack_freq = 0;
uint16_t decay_freq = 0;
uint16_t sustain_freq = 0;
uint16_t release_freq = 0;
uint16_t waveshape = 0;
    
struct voice v1 = {0,0,0,0,0};
struct voice v2 = {0,0,0,0,0};
struct voice v3 = {0,0,0,0,0};
struct voice v4 = {0,0,0,0,0};
struct voice v5 = {0,0,0,0,0};
struct voice v6 = {0,0,0,0,0};
struct voice v7 = {0,0,0,0,0};
struct voice v8 = {0,0,0,0,0};

/*******************************************************************************
* USB and MIDI stuff
* references Cypress MIDI code examples
*******************************************************************************/
#define DEVICE                  (0u)
#define MIDI_MSG_SIZE           (4u)

/*MIDI Message Fields */
#define MIDI_MSG_TYPE           (0u)
#define MIDI_NOTE_NUMBER        (1u)
#define MIDI_NOTE_VELOCITY      (2u)

/* Identity Reply message */
const uint8 CYCODE MIDI_IDENTITY_REPLY[] = {
    0xF0u,      /* SysEx */
    0x7Eu,      /* Non-real time */
    0x7Fu,      /* ID of target device (7F - "All Call") */
    0x06u,      /* Sub-ID#1 - General Information */
    0x02u,      /* Sub-ID#2 - Identity Reply */
    0x7Du,      /* Manufacturer's ID: 7D - Educational Use */
    0xB4u, 0x04u,               /* Family code */
    0x32u, 0xD2u,               /* Model number */
    0x01u, 0x00u, 0x00u, 0x00u, /* Version number */
    /*0xF7         End of SysEx automatically appended */
};

/* Need for Identity Reply message */
volatile uint8 USB_MIDI1_InqFlags;

volatile uint8 usbActivityCounter = 0u;

uint8 inqFlagsOld = 0u;

uint8 midiMsg[MIDI_MSG_SIZE];   
char buff[32];//output UART buffer

// volatile uint8_t MIDI_RX_flag = 0;
void ProcessUSBMIDI();
void ProcessSpiToFpga();
void UART_PrintNumber(int32_t);

/*******************************************************************************
* main
*******************************************************************************/
int main() {
    LED_Write(1);
    //UART_Start();
    //TxByteCounter_Start();
    //isr_trigger_StartEx(envelope_trigger_interrupt);
    
    //UART_UartPutString("\r\n\r\n\r\n********************\r\n");
    //UART_UartPutString("PMA Wavetable Synth\r\n");
    //UART_UartPutString("********************\r\n");
	InitAudioPath();
    //UART_UartPutString("Audio path initialized...\r\n");
    
    init_wavetable();
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
    //SPI_SpiUartClearRxBuffer();
    //UART_UartPutString("SPI initialized... \r\n");
    
    CodecI2CM_Start();	
	if(Codec_Init() == 0) {
    	//UART_UartPutString("Codec comm works!... \r\n");
        Codec_Activate();
	}
	else {
		//UART_UartPutString("Codec comm DOESN'T work!... \r\n");
	}
    
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
    
    //FillBufferFromFPGA(output_buffer);
    CyGlobalIntEnable;

    SPI_RxDMA_Start((void *)SPI_RX_FIFO_RD_PTR, (void *)masterRxBuffer);
    SPI_TxDMA_Start((void *)masterTxBuffer, (void *)SPI_TX_FIFO_WR_PTR);
    //SPI_RxDMA_SetInterruptCallback(SPI_RxDMA_Done_Interrupt);
    //SPI_TxDMA_SetInterruptCallback(SPI_TxDMA_Done_Interrupt);
    //I2STxDMA_Start(output_buffer, (void *)I2S_TX_FIFO_0_PTR);
        
    for(;;) {
        ProcessSpiToFpga();
        ProcessUSBMIDI();
        ProcessVoice(&v1);
        /*ProcessVoice(&v2);
        ProcessVoice(&v3);
        ProcessVoice(&v4);
        ProcessVoice(&v5);
        ProcessVoice(&v6);
        ProcessVoice(&v7);
        ProcessVoice(&v8);*/
        if(update_ADC_flag){
            attack_freq = ADC_GetResult16(0);
            decay_freq = ADC_GetResult16(1);
            sustain_freq = ADC_GetResult16(2);
            release_freq = ADC_GetResult16(3);
            //attack_freq = 52275;
            //attack_freq = 60;
            update_ADC_flag = 0;
        }
    }
}

//void UART_PrintNumber(int32_t number){
    //char string[30];
    //sprintf(string, "%d\n",number);
    //UART_UartPutString(string);
//}

void ProcessSpiToFpga(){
    static uint8_t spi_byte_counter;
    
    /* Check whether data exchange has been finished. RxDmaM and RxDmaS are 
    * configured to set an interrupt when they finish transferring all data
    * elements.
    */
    if(0u == (CyDmaGetInterruptSourceMasked() ^ (SPI_RxDMA_CHANNEL_MASK)))// | RxDmaS_CHANNEL_MASK)))
    {
        /* Once asserted, interrupt bits remain high until cleared. */
        CyDmaClearInterruptSource(SPI_RxDMA_CHANNEL_MASK);// | RxDmaS_CHANNEL_MASK);

        /* Reset receive buffers. */
        memset((void *) masterRxBuffer, 0, BUFFER_SIZE);
        //memset((void *) slaveRxBuffer,  0, BUFFER_SIZE);
        
        // this byte counting method needs to be more flexible to allow
        // sending different types of commands. Refactor.
        // Could fill a larger buffer and let DMA handle it, I suppose.
        switch(spi_byte_counter){
        case 0:
            masterTxBuffer[0] = SPI_CMD_FREQ;
            spi_byte_counter++;
            break;
        case 1:
            masterTxBuffer[0] = (uint8_t)(v1.freq>>8);
            spi_byte_counter++;
            break;
        case 2:
            masterTxBuffer[0] = (uint8_t)(v1.freq);
            spi_byte_counter++;
            break;
        case 3:
            masterTxBuffer[0] = SPI_CMD_ENV;
            spi_byte_counter++;
            break;
        case 4:
            masterTxBuffer[0] = (uint8_t)(v1.env_multiplier);
            spi_byte_counter = 0;
            break;
        default:
            spi_byte_counter = 0;
            break;
        }
        
        CyDelay(2);
        
        /* Re-enable transfer. TxDmaM controls the number of bytes to be sent
        * to the slave and correspondingly the number of bytes returned by the
        * slave. Therefore it is configured to be invalidated when it
        * finishes a transfer.
        */
        SPI_TxDMA_ValidateDescriptor(0);
        SPI_TxDMA_ChEnable();
    }
}

void ProcessUSBMIDI(){
    /*******************************************************************************
    * USB AND MIDI STUFF
    * references Cypress USB MIDI code examples
    *******************************************************************************/
    
    if(0u != USB_IsConfigurationChanged()){
        if(0u != USB_GetConfiguration())   // Initialize IN endpoints when device configured
        {
            USB_MIDI_Init(); // Enable output endpoint
        }
    }            
    
    /* Service USB MIDI when device is configured */
    if(0u != USB_GetConfiguration())    
    {
        /* Call this API from UART RX ISR for Auto DMA mode */
        #if(!USB_EP_MANAGEMENT_DMA_AUTO) 
            USB_MIDI_IN_Service();
        #endif
        /* In Manual EP Memory Management mode OUT_EP_Service() 
        *  may have to be called from main foreground or from OUT EP ISR
        */
        #if(!USB_EP_MANAGEMENT_DMA_AUTO) 
            USB_MIDI_OUT_Service();
        #endif

        /* Sending Identity Reply Universal System Exclusive message 
         * back to computer */
        if(0u != (USB_MIDI1_InqFlags & USB_INQ_IDENTITY_REQ_FLAG))
        {
            USB_PutUsbMidiIn(sizeof(MIDI_IDENTITY_REPLY), (uint8 *)MIDI_IDENTITY_REPLY, USB_MIDI_CABLE_00);
            USB_MIDI1_InqFlags &= ~USB_INQ_IDENTITY_REQ_FLAG;
        }
    }
}


/*******************************************************************************
* Function Name: USB_callbackLocalMidiEvent
********************************************************************************
* Summary: Local processing of the USB MIDI out-events.
* References: Cypress code examples, 
* and https://community.cypress.com/message/144752#144752
*******************************************************************************/
void USB_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg) CYREENTRANT
{
    uint8 note;
    
    /* Support General System On/Off Message. */
    /*
    if((0u == (USB_MIDI1_InqFlags & USB_INQ_SYSEX_FLAG)) \
            && (0u != (inqFlagsOld & USB_INQ_SYSEX_FLAG)))
    {
        if(midiMsg[USB_EVENT_BYTE0] == USB_MIDI_SYSEX_GEN_MESSAGE)
        {
            if(midiMsg[USB_EVENT_BYTE1] == USB_MIDI_SYSEX_SYSTEM_ON)
            {
                MIDI_PWR_Write(0u); 
            }
            else if(midiMsg[USB_EVENT_BYTE1] == USB_MIDI_SYSEX_SYSTEM_OFF)
            {
                MIDI_PWR_Write(1u); 
            }
        }
    }
    */
    inqFlagsOld = USB_MIDI1_InqFlags;
    cable = cable;
    
    if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_NOTE_ON)
    {
        note = midiMsg[USB_EVENT_BYTE1];
        DispatchNote(note);
        LED_Write(0);
    }
    else if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_NOTE_OFF)
    {
        note = midiMsg[USB_EVENT_BYTE1];
        NoteOff(note);
        
        //trigger_flag = 0;
        //current_env_mode = RELEASE_MODE;
        LED_Write(1);
    }
}    


/*******************************************************************************
* Function Name: USB_MIDI1_ProcessUsbOut_EntryCallback
********************************************************************************
* Summary:  Turn the LED_OutA on at the beginning of the function
* USB_MIDI1_ProcessUsbOut() when data comes to be put in the UART1 out
* buffer.
* 
*******************************************************************************/
void USB_MIDI1_ProcessUsbOut_EntryCallback(void)
{
    //LED_OutA_Write(1);
}


/*******************************************************************************
* Function Name: USB_MIDI1_ProcessUsbOut_ExitCallback
********************************************************************************
* Summary:  Turn the LED_OutA off at the end of the function  
* USB_MIDI1_ProcessUsbOut() when data is put in the UART1 out-buffer.
* 
*******************************************************************************/
void USB_MIDI1_ProcessUsbOut_ExitCallback(void)
{
    //LED_OutA_Write(0);
}

/*******************************************************************************
* Function Name: MIDI1_UART_RXISR_EntryCallback
********************************************************************************
* Summary:  Turn the LED_InA on at the beginning of the MIDI1_UART_RXISR ISR  
* when data comes to UART1 to be put in the USBFS_MIDI IN endpoint
* buffer.
*
*******************************************************************************/
void MIDI1_UART_RXISR_EntryCallback(void)
{
    /* These LEDs indicate MIDI input activity */
    //LED_InA_Write(1);
}


/*******************************************************************************
* Function Name: MIDI1_UART_RXISR_ExitCallback
********************************************************************************
* Summary:  Turn the LED_InA off at the end of the MIDI1_UART_RXISR ISR  
* when data is put in the USBFS_MIDI IN endpoint buffer.
*
*******************************************************************************/
void MIDI1_UART_RXISR_ExitCallback(void)
{
    #if (USB_EP_MANAGEMENT_DMA_AUTO) 
        USB_MIDI_IN_Service();
    #endif /* (USB_EP_MANAGEMENT_DMA_AUTO) */
    
    //LED_InA_Write(0);
}
/* [] END OF FILE */
