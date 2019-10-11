/*******************************************************************************
* File Name: Interrupts.h
*
* Version 1.0
*
*  Description: Interrupts.h provides prototype for all the external interrupt 
*               service routines present in the project
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

#ifndef INTERRUPTS_H
	#define INTERRUPTS_H
		
	#include "cytypes.h"

    CY_ISR_PROTO(ADC_EOC);
	CY_ISR_PROTO(I2S_FIFO_DMA_REQ);
    CY_ISR_PROTO(TxBufferDMADone_Interrupt);
    CY_ISR_PROTO(I2SUnderflow);
    CY_ISR_PROTO(I2STxDone);
    CY_ISR_PROTO(SPIDone);
    CY_ISR_PROTO(SPI_RxDMA_Done_Interrupt);
    CY_ISR_PROTO(SPI_TxDMA_Done_Interrupt);
    CY_ISR_PROTO(TxDMA_1_Done_Interrupt);
    CY_ISR_PROTO(envelope_trigger_interrupt);

#endif

/* [] END OF FILE */
