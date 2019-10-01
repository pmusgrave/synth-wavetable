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
uint16_t envelope_multiplier = 0;

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
    TxDMA_SetSrcAddress(0, (void *) SPI_RX_FIFO_RD_PTR);
	TxDMA_SetDstAddress(0, (void *) I2S_TX_FIFO_0_PTR);
    //TxDMA_SetSrcAddress(1, (void *) output_buffer2);
	//TxDMA_SetDstAddress(1, (void *) I2S_TX_FIFO_0_PTR);
    TxDMA_SetInterruptCallback(TxDMA_Done_Interrupt);
    TxDMA_ChEnable();

	/* Validate descriptor */
    TxDMA_ValidateDescriptor(0);
    TxDMA_ValidateDescriptor(1);
    
    /* Start interrupts */
    //isr_TxDMADone_StartEx(TxDMA_Done_Interrupt);
    //isr_TxDMADone_Enable();
    CyIntEnable(CYDMA_INTR_NUMBER);
    
    freq = 1000;
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
        index += v1.freq; //* lfo_multiplier)>>8;
        index2 += v2.freq;
        index3 += v3.freq;
        index4 += v4.freq;
        index5 += v5.freq;
        index6 += v6.freq;
        index7 += v7.freq;
        index8 += v8.freq;
        
        /*int32_t value = base_sq[((index)>>8) & 0xFFF];
        + ((base_sine[(index2>>8) & 0xFFF]))
        + (base_sine[(index3>>8) & 0xFFF])
        + (base_sine[(index4>>8) & 0xFFF])
        + (base_sine[(index5>>8) & 0xFFF])
        + (base_sine[(index6>>8) & 0xFFF])
        + (base_sine[(index7>>8) & 0xFFF])
        + (base_sine[(index8>>8) & 0xFFF])
        */
        
        uint32_t sq_portion = ((base_sq[(index>>8) & 0xFFF] * v1.env_multiplier)>>8) * ((65535-waveshape)>>8)
        + ((base_sq[(index2>>8) & 0xFFF] * v2.env_multiplier)>>8) * ((65535-waveshape)>>8)
        + ((base_sq[(index3>>8) & 0xFFF] * v3.env_multiplier)>>8) * ((65535-waveshape)>>8)
        + ((base_sq[(index4>>8) & 0xFFF] * v4.env_multiplier)>>8) * ((65535-waveshape)>>8)
        + ((base_sq[(index5>>8) & 0xFFF] * v5.env_multiplier)>>8) * ((65535-waveshape)>>8)
        + ((base_sq[(index6>>8) & 0xFFF] * v6.env_multiplier)>>8) * ((65535-waveshape)>>8)
        + ((base_sq[(index7>>8) & 0xFFF] * v7.env_multiplier)>>8) * ((65535-waveshape)>>8)
        + ((base_sq[(index8>>8) & 0xFFF] * v8.env_multiplier)>>8) * ((65535-waveshape)>>8);
        
        uint32_t sine_portion = ((base_sine[(index>>8) & 0xFFF] * v1.env_multiplier)>>8) * (waveshape>>8)
        + ((base_sine[(index2>>8) & 0xFFF] * v2.env_multiplier)>>8) * (waveshape>>8)
        + ((base_sine[(index3>>8) & 0xFFF] * v3.env_multiplier)>>8) * (waveshape>>8)
        + ((base_sine[(index4>>8) & 0xFFF] * v4.env_multiplier)>>8) * (waveshape>>8)
        + ((base_sine[(index5>>8) & 0xFFF] * v5.env_multiplier)>>8) * (waveshape>>8)
        + ((base_sine[(index6>>8) & 0xFFF] * v6.env_multiplier)>>8) * (waveshape>>8)
        + ((base_sine[(index7>>8) & 0xFFF] * v7.env_multiplier)>>8) * (waveshape>>8)
        + ((base_sine[(index8>>8) & 0xFFF] * v8.env_multiplier)>>8) * (waveshape>>8);
        //buffer[i] = value;
        
        //int8_t sine_portion = (base_sine[(index>>8) & 0xFFF] * waveshape>>6)>>8;
        //uint8_t sq_portion = (base_sq[((index)>>8) & 0xFFF] * (65535-waveshape)>>6)>>8;
        buffer[i] = sine_portion + sq_portion;//((value + 8*AMPLITUDE) * 2*AMPLITUDE) / (32*AMPLITUDE);
        
        ///2 + buffer[i-1]/2;// + buffer[i-2]/3;
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
