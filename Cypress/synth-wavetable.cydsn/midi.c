#include "midi.h"

/*******************************************************************************
* USB AND MIDI STUFF
* references Cypress USB MIDI code examples
*******************************************************************************/
uint8 midiMsg[MIDI_MSG_SIZE];
struct msg_queue midi_msg_queue;

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

void ProcessUSBMIDI(){
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
    //uint8 note;
    
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

    
    //ProcessSpiTx(midiMsg);
    
    if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_NOTE_ON)
    {
        // note = midiMsg[USB_EVENT_BYTE1];
        // DispatchNote(note);
        LED_Write(0);
        struct midi_msg current_msg = {
            midiMsg[USB_EVENT_BYTE0],
            midiMsg[USB_EVENT_BYTE1],
            midiMsg[USB_EVENT_BYTE2],
            midiMsg[USB_EVENT_BYTE3]
        };
        enqueue(current_msg);
    }
    else if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_NOTE_OFF)
    {
        // note = midiMsg[USB_EVENT_BYTE1];
        // NoteOff(note);
        
        //trigger_flag = 0;
        //current_env_mode = RELEASE_MODE;
        LED_Write(1);
        struct midi_msg current_msg = {
            midiMsg[USB_EVENT_BYTE0],
            midiMsg[USB_EVENT_BYTE1],
            midiMsg[USB_EVENT_BYTE2],
            midiMsg[USB_EVENT_BYTE3]
        };
        enqueue(current_msg);
    }
}    


void enqueue (struct midi_msg midi_msg) {
    midi_msg_queue.queue[midi_msg_queue.head++] = midi_msg;
}

struct midi_msg dequeue(void) {
    return midi_msg_queue.queue[midi_msg_queue.tail++];   
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