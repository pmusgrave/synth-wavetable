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
    /*
    SPI_RxDMA_Start((void *)SPI_RX_FIFO_RD_PTR, (void *)masterRxBuffer);
    SPI_TxDMA_Start((void *)masterTxBuffer, (void *)SPI_TX_FIFO_WR_PTR);
    SPI_RxDMA_SetInterruptCallback(SPI_RxDMA_Done_Interrupt);
    SPI_TxDMA_SetInterruptCallback(SPI_TxDMA_Done_Interrupt);
    isr_SPIDone_StartEx(SPIDone);
    isr_SPIDone_Enable();
    //I2STxDMA_Start(output_buffer, (void *)I2S_TX_FIFO_0_PTR);
    
    
    I2STxDMA_Init();
	I2STxDMA_SetNumDataElements(0, OUT_BUFSIZE);
    I2STxDMA_SetNumDataElements(1, OUT_BUFSIZE);
    I2STxDMA_SetSrcAddress(0, (void *) SPI_RX_FIFO_RD_PTR);
    //I2STxDMA_SetSrcAddress(0, (void *) output_buffer);
	I2STxDMA_SetDstAddress(0, (void *) I2S_TX_FIFO_0_PTR);
    //I2STxDMA_SetSrcAddress(1, (void *) output_buffer2);
	//I2STxDMA_SetDstAddress(1, (void *) I2S_TX_FIFO_0_PTR);
    I2STxDMA_SetInterruptCallback(I2STxDone);
    I2STxDMA_ChEnable();
    */
    
    /* Start other DMA channels to begin data transfer. */
    
    
	/* Validate descriptor */
    //I2STxDMA_ValidateDescriptor(0);
    //I2STxDMA_ValidateDescriptor(1);
    //SPI_RxDMA_ValidateDescriptor(0);
    
    /* Start interrupts */
    //isr_I2STxDone_StartEx(I2STxDone);
    //isr_I2STxDone_Enable();
    //CyIntEnable(CYDMA_INTR_NUMBER);
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
        //I2S_DisableTx();     /* Stop I2S Transmit (Mute), I2S output clocks still active */
        
        //CyDelayUs(20); /* Provide enough time for DMA to transfer the last audio samples completely to I2S TX FIFO */
   
        /* Stop / Disable DMA - Needed to reset to start of chain */
        //I2STxDMA_ChDisable();
		
		/* Make DMA transaction count zero */ 
        //CYDMA_DESCR_BASE.descriptor[I2STxDMA_CHANNEL][0].status &= 0xFFFF0000;
		
        /* Disable power to speaker output */
        //Codec_PowerOffControl(CODEC_POWER_CTRL_OUTPD);
    //}    
}

/* [] END OF FILE */
