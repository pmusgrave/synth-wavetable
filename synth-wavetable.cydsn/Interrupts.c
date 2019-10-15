/*******************************************************************************
* File Name: Interrupts.c
*
* Version 1.0
*
*  Description: This file contains interrupt service routines for all the interrupts
*               in the system
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
#include <Config.h>
#include <project.h>
#include <Interrupts.h>
#include "waves.h"
#include "globals.h"

volatile uint8_t DMA_done_flag = 0;
volatile uint8_t DMA_counter = 0;
volatile int8_t* current_buffer;
volatile uint8_t FIFO_DMA_REQ_FLAG = 0;
volatile uint8_t update_ADC_flag = 0;
volatile uint8_t trigger_flag = 0;

CY_ISR(ADC_EOC) {
    //UART_UartPutString("ADC EOC\r\n");
    update_ADC_flag = 1;
    //freq = 2000;
}

CY_ISR(I2STxDone){
    //UART_UartPutString("DMA done\r\n");
    //CyGlobalIntDisable;
    DMA_done_flag = 1;
    DMA_counter++;
    
    LED_Write(0);
}

CY_ISR(SPI_RxDMA_Done_Interrupt){
    /* Reset receive buffers. */
    memcpy((void *)current_buffer, masterRxBuffer, BUFFER_SIZE);
    
    /* Re-enable transfer. TxDmaM controls the number of bytes to be sent
    * to the slave and correspondingly the number of bytes returned by the
    * slave. Therefore it is configured to be invalidated when it
    * finishes a transfer.
    */
    SPI_TxDMA_ValidateDescriptor(0);
    SPI_TxDMA_ChEnable();
    //I2STxDMA_ValidateDescriptor(0);
    //I2STxDMA_ChEnable();
    
    //LED_Write(~LED_Read());
    //SPI_reset_Write(~SPI_reset_Read());
}

CY_ISR(SPI_TxDMA_Done_Interrupt){
    //LED_Write(~LED_Read());
    //SPI_reset_Write(~SPI_reset_Read());
}

CY_ISR(I2SUnderflow) {
    //UART_UartPutString("I2S undeflow\r\n");    
}

CY_ISR(envelope_trigger_interrupt){
    //UART_UartPutString("env trig\r\n");
}

/* [] END OF FILE */
