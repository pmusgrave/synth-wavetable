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
#include "waves.h"
#include "globals.h"

uint16_t freq;
uint16_t freq2;
uint16_t freq3;
uint16_t freq4;
uint16_t freq5;
uint16_t freq6;
uint16_t freq7;
uint16_t freq8;
uint32_t lfo_freq;
uint16_t lfo_multiplier = 1;

CYBIT outPlaying = 0;
int8_t output_buffer[OUT_BUFSIZE];
int8_t output_buffer2[OUT_BUFSIZE];
uint32_t buffer_index;
uint32_t buffer_index2;
extern CYBIT audioClkConfigured;

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
    TxDMA_SetNumDataElements(1, OUT_BUFSIZE);
    TxDMA_SetSrcAddress(0, (void *) output_buffer);
	TxDMA_SetDstAddress(0, (void *) I2S_TX_FIFO_0_PTR);
    TxDMA_SetSrcAddress(1, (void *) output_buffer2);
	TxDMA_SetDstAddress(1, (void *) I2S_TX_FIFO_0_PTR);
    TxDMA_SetInterruptCallback(TxDMA_Done_Interrupt);
    TxDMA_ChEnable();

	/* Validate descriptor */
    TxDMA_ValidateDescriptor(0);
    TxDMA_ValidateDescriptor(1);
    
    /* Start interrupts */
    //isr_TxDMADone_StartEx(TxDMA_Done_Interrupt);
    //isr_TxDMADone_Enable();
    CyIntEnable(CYDMA_INTR_NUMBER);
    
    freq = 100;
    freq2 = 200;
    freq3 = 300;
    freq4 = 400;
    freq5 = 500;
    freq6 = 600;
    freq7 = 700;
    freq8 = 800;
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

void ProcessAudioOut(int8_t* buffer) 
{
    static uint32_t index;
    static uint32_t index2;
    static uint32_t index3;
    static uint32_t index4;
    static uint32_t index5;
    static uint32_t index6;
    static uint32_t index7;
    static uint32_t index8;
    
    static uint32_t lfo_index;
    lfo_index += lfo_freq;
    lfo_multiplier = lfo_sine[(lfo_index>>8) % 256];
    
    //*index = *index + freq;
    //buffer[0] = base_sine[((*index)>>10)%N];
    for(int i = 0; i < OUT_BUFSIZE; i++){
        index += (freq * lfo_multiplier)>>8;/*
        index2 += freq2;
        index3 += freq3;
        index4 += freq4;
        index5 += freq5;
        index6 += freq6;
        index7 += freq7;
        index8 += freq8;
        */
        
        int32_t value = base_sine[((index)>>8) & 0xFFF];/*
        + ((base_sine[(index2>>8) & 0xFFF]))
        + (base_sine[(index3>>8) & 0xFFF])
        + (base_sine[(index4>>8) & 0xFFF])
        + (base_sine[(index5>>8) & 0xFFF])
        + (base_sine[(index6>>8) & 0xFFF])
        + (base_sine[(index7>>8) & 0xFFF])
        + (base_sine[(index8>>8) & 0xFFF])
        */
        
        buffer[i] = value;
        
        //int8_t sine_portion = (value * lfo_multiplier)>>8;
        //uint8_t sq_portion = (base_sq[((index)>>8) & 0xFFF] * (255-lfo_multiplier))>>8;
        //buffer[i] = sine_portion + sq_portion;//((value + 8*AMPLITUDE) * 2*AMPLITUDE) / (32*AMPLITUDE);
        
        ///2 + buffer[i-1]/2;// + buffer[i-2]/3;
        
        //char string[30];
        //sprintf(string, "%d\n",lfo_multiplier);
        //UART_UartPutString(string);
    }
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
    //
    //if(outPlaying)
    //{       
        //UART_UartPutString("Stopping I2S\r\n");
        I2S_DisableTx();     /* Stop I2S Transmit (Mute), I2S output clocks still active */
        
        CyDelayUs(20); /* Provide enough time for DMA to transfer the last audio samples completely to I2S TX FIFO */
   
        /* Stop / Disable DMA - Needed to reset to start of chain */
        TxDMA_ChDisable();
		
		/* Make DMA transaction count zero */ 
        CYDMA_DESCR_BASE.descriptor[TxDMA_CHANNEL][0].status &= 0xFFFF0000;
		
        /* Disable power to speaker output */
        Codec_PowerOffControl(CODEC_POWER_CTRL_OUTPD);
    //}    
}

/* [] END OF FILE */
