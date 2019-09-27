#include <project.h>
#include "Codec.h"
#include "AudioControl.h"
#include "waves.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"

#include "oscillator.h"


uint8_t current_env_mode = 0;

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

int main() {
    UART_Start();
    TxByteCounter_Start();
    isr_trigger_StartEx(envelope_trigger_interrupt);
    uint16_t attack_freq = 0;
    uint16_t decay_freq = 0;
    uint16_t sustain_freq = 0;
    uint16_t release_freq = 0;
    
    UART_UartPutString("\r\n\r\n\r\n********************\r\n");
    UART_UartPutString("PMA Wavetable Synth\r\n");
    UART_UartPutString("********************\r\n");
	InitAudioPath();
    UART_UartPutString("Audio path initialized...\r\n");
    
    init_wavetable();
    UART_UartPutString("Wavetable initialized...\r\n");
    
    // Init USB and MIDI
    // references Cypress USB MIDI code example
    USB_Start(DEVICE, USB_DWR_VDDD_OPERATION); 
    //MIDI1_UART_Start();
    //MIDI_RX_StartEx(MIDI_RX_VECT);
    UART_UartPutString("USB MIDI initialized...\r\n");
    
    ADC_Start();
    ADC_StartConvert();
    isr_ADC_EOC_StartEx(ADC_EOC);
    
    CodecI2CM_Start();	
	if(Codec_Init() == 0) {
    	UART_UartPutString("Codec comm works!... \r\n");
        Codec_Activate();
	}
	else {
		UART_UartPutString("Codec comm DOESN'T work!... \r\n");
	}
    
    I2S_Start();
    I2S_EnableTx(); /* Unmute the TX output */ 
    isr_I2S_underflow_StartEx(I2SUnderflow);
    
    CyGlobalIntEnable;
    
    ProcessAudioOut(output_buffer);
    ProcessAudioOut(output_buffer2);
    
    for(;;) {
        if(DMA_done_flag){
            DMA_done_flag = 0;
            if(DMA_counter % 2 == 0){
                CyGlobalIntEnable;
                //UART_UartPutString("0\r\n");
                ProcessAudioOut(output_buffer2);
            }
            else {
                CyGlobalIntEnable;
                //UART_UartPutString("1\r\n");
                ProcessAudioOut(output_buffer);
            }
        }

        if(update_ADC_flag){
            /*
            freq = ADC_GetResult16(0);
            freq2 = ADC_GetResult16(1);
            freq3 = ADC_GetResult16(2);
            lfo_freq = ADC_GetResult16(3);
            */
            attack_freq = 65535 - ADC_GetResult16(0);
            decay_freq = 65535 - ADC_GetResult16(1);
            sustain_freq = ADC_GetResult16(2);
            release_freq = 65535 - ADC_GetResult16(3);
        }
        
        static uint32_t env_index;
        if(trigger_flag && current_env_mode == ATTACK_MODE){
            env_index += attack_freq;
            envelope_multiplier = base_pos_saw[(env_index>>18) & 0xFFF]; // using pos saw wave here, but should rename to linear ramp or something
            if(envelope_multiplier > 120) {
                envelope_multiplier = 127;
                current_env_mode = DECAY_MODE;
            }
        }
        else if(trigger_flag && current_env_mode == DECAY_MODE){
            env_index -= decay_freq;
            envelope_multiplier = base_pos_saw[(env_index>>18) & 0xFFF];
            if(envelope_multiplier < base_pos_saw[(sustain_freq) & 0xFFF]) {
                envelope_multiplier = base_pos_saw[(sustain_freq) & 0xFFF];
                current_env_mode = SUSTAIN_MODE;
            }
        }
        else if(trigger_flag && current_env_mode == SUSTAIN_MODE){
            envelope_multiplier = base_pos_saw[(sustain_freq) & 0xFFF];
        }
        else if(trigger_flag && current_env_mode == RELEASE_MODE){
            env_index -= release_freq;
            envelope_multiplier = base_pos_saw[(env_index>>18) & 0xFFF];
            if(envelope_multiplier < 10) {
                envelope_multiplier = 0;
                env_index = 0;
                current_env_mode = NOT_TRIGGERED;
                trigger_flag = 0;
            }
        }
        else if (!trigger_flag){
            envelope_multiplier = 0;
            env_index = 0;
        }
        
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
        
        //CyDelayUs(5);
        //char string[30];
        //sprintf(string, "%d\n",envelope_multiplier);
        //UART_UartPutString(string);
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
        UART_UartPutString("note on\r\n");
        
        trigger_flag = 1;
        current_env_mode = SUSTAIN_MODE;
        LED_Write(1);
    }
    else if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_NOTE_OFF)
    {
        note = midiMsg[USB_EVENT_BYTE1];
        //NoteOff(note);
        UART_UartPutString("note off\r\n");
        
        trigger_flag = 0;
        current_env_mode = NOT_TRIGGERED;
        LED_Write(0);
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
