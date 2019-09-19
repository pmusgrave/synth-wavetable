/*******************************************************************************
* File Name: AudioControl.c
*
* Version 1.0
*
*  Description: This file contains the Audio signal path configuration and 
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
#include <AudioOut.h>
#include <Codec.h>
#include <Config.h>
#include <project.h>
#include <Interrupts.h>

uint8 newRate = RATE_48KHZ;
extern uint8 asyncready;


extern CYBIT outPlaying;

extern CYBIT inPlaying;



uint8 audioClkConfigured = 0;
uint8 setRate = FREQUENCY_NOT_SET; 
uint8 newRate;

/*******************************************************************************
* Function Name: InitAudioPath
********************************************************************************
* Summary:
*       This function sets up the XTAL, DMA and starts USB, I2S and interrupts
*        to get the part configured for the audio signal paths
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void InitAudioPath(void)
{    
    /* Set the default Audio clock rate to 48 kHz */
	AudioClkSel_Write(RATE_48KHZ);
    
	/* Enable DMA */
	CyDmaEnable();
	
	InitializeAudioOutPath();

	/* Set TX FIFO trigger to 2 bytes (half-empty) to increase timing margin */
    I2S_TX_AUX_CONTROL_REG = I2S_TX_AUX_CONTROL_REG | FIFO_HALF_EMPTY_MASK;
}
 
/* [] END OF FILE */
