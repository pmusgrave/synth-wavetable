/*******************************************************************************
* File Name: AudioOut.c
*
* Version 1.0
*
*  Description: This file contains the Audio Out path configuration and 
*               processing code
*
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

#include <AudioControl.h>
#include <Interrupts.h>
#include <AudioControl.h>
#include <Config.h>
#include <AudioOut.h>
#include <project.h>
#include <Codec.h>
#include <math.h>
#include "sinewaves.h"

extern uint8 outBuffer[];

CYBIT resetTx = 0;
CYBIT outPlaying = 0;
uint16 outLevel = 0;
uint16 outUsbCount = 0;
uint16 outUsbShadow = 0;
uint8 outBuffer[OUT_BUFSIZE];
uint16 outBufIndex = 0;
extern CYBIT audioClkConfigured;

#if(USBFS_EP_MM == USBFS__EP_DMAAUTO)   
	extern uint8 outRam[];  
#endif

/*******************************************************************************
* Function Name: InitializeAudioOutPath
********************************************************************************
* Summary:
*       This function initializes all the associated DMAs for the Audio OUT
*       path
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void InitializeAudioOutPath(void)
{
    TxDMA_Init();
	TxDMA_SetNumDataElements(0, OUT_BUFSIZE);
    TxDMA_SetSrcAddress(0, (void *) outBuffer);
	TxDMA_SetDstAddress(0, (void *) I2S_TX_FIFO_0_PTR);
    
	/* Validate descriptor */
    TxDMA_ValidateDescriptor(0);
    
    for(int i = 0; i < OUT_BUFSIZE; i++){
        outBuffer[i] = base_sine[i];
    }
    /* Start interrupts */
    isr_TxDMADone_StartEx(TxDMADone_Interrupt);
    isr_TxDMADone_Enable();
}

/*******************************************************************************
* Function Name: ProcessAudioOut
********************************************************************************
* Summary:
*        Handle audio out data, setup USB DMA and trigger the DMA to transfer 
*        audio samples from SRAM USB endpoint memory to SRAM audio circular 
*        buffer. The API also starts the I2S transmit when USB audio out streaming 
*        is active
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/

void ProcessAudioOut(void) 
{
    //UART_UartPutString("Processing audio output...\r\n");
    static int index;
    
    for(int i = 0; i < OUT_BUFSIZE; i++){
        index = index + 1;
        if(index >= N - 1){
          index = 0;
        }
        outBuffer[i] = base_sine[(int)index];
        //outBuffer[OUT_BUFSIZE + i] = base_sine[(int)index];
        
        //char string[30];
        //sprintf(string, "%d\n",outBuffer[i]);
        //UART_UartPutString(string);
    }
            
	/* Enable power to speaker output */
    Codec_PowerOnControl(CODEC_POWER_CTRL_OUTPD);
    
	TxDMA_ChEnable();            
    
    I2S_EnableTx(); /* Unmute the TX output */       
}


/*******************************************************************************
* Function Name: Stop_I2S_Tx
********************************************************************************
* Summary:
*        This function stops the I2S data transmission by disabling the I2S and 
*        transmit DMA.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Stop_I2S_Tx(void) CYREENTRANT
{
    UART_UartPutString("Stopping I2S\r\n");
    if(outPlaying)
    {       
        I2S_DisableTx();     /* Stop I2S Transmit (Mute), I2S output clocks still active */
        
        CyDelayUs(20); /* Provide enough time for DMA to transfer the last audio samples completely to I2S TX FIFO */
   
        /* Stop / Disable DMA - Needed to reset to start of chain */
        TxDMA_ChDisable();
		
		/* Make DMA transaction count zero */ 
        CYDMA_DESCR_BASE.descriptor[TxDMA_CHANNEL][0].status &= 0xFFFF0000;
		
        /* Disable power to speaker output */
        Codec_PowerOffControl(CODEC_POWER_CTRL_OUTPD);
        
        resetTx = 1;
        outLevel = 0;
        outUsbShadow = 0;
        outPlaying = 0;
    }    
}

/* [] END OF FILE */
