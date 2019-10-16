/*******************************************************************************
* File Name: SPI_TxDMA.h
* Version 1.0
*
* Description:
*  This file contains all of the channel DMA API functions.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_TxDMA.h"

uint8 SPI_TxDMA_initVar = 0u;


/*******************************************************************************
* Function Name: SPI_TxDMA_Start
********************************************************************************
*
* Summary:
*  Calls Init() to configure the DMA channel based on the customizer settings if
*  the channel has not been initialized before.
*  Sets source and destination address, validates descriptor 0 and enables the
*  channel. After calling this function the DMA channel is active and waiting
*  for a trigger.
*
* Parameters:
*  srcAddress: Address of DMA transfer source for descriptor 0.
*  dstAddress: Address of DMA transfer destination for descriptor 0.
*                   
* Return:
*  None.
*
*******************************************************************************/
void SPI_TxDMA_Start(void * srcAddress, void * dstAddress)
{
    if(0u == SPI_TxDMA_initVar)
    {
        SPI_TxDMA_Init();
        SPI_TxDMA_initVar = 1u;
    }
    CyDmaEnable();
    SPI_TxDMA_SetSrcAddress(0, srcAddress);
    SPI_TxDMA_SetDstAddress(0, dstAddress);
    SPI_TxDMA_ValidateDescriptor(0);
    SPI_TxDMA_ChEnable();
}


/*******************************************************************************
* Function Name: SPI_TxDMA_Init
********************************************************************************
*
* Summary:
*  Initializes the DMA channel based on the parameters set in the component
*  customizer. It is not necessary to call SPI_TxDMA_Init() because the
*  SPI_TxDMA_Start() API calls this function, which is the preferred method
*  to begin component operation.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  The first descriptor is set to descriptor 0. This function should not be
*  called while the channel is enabled. All settings will be reset to their
*  initial values.
*
*******************************************************************************/
void SPI_TxDMA_Init(void)
{
    CYDMA_CH_CTL_BASE.ctl[SPI_TxDMA_CHANNEL] = SPI_TxDMA_CHANNEL_CFG;
    CYDMA_DESCR_BASE.descriptor[SPI_TxDMA_CHANNEL][0].ctl = SPI_TxDMA_DESCR0_CFG;
    CYDMA_DESCR_BASE.descriptor[SPI_TxDMA_CHANNEL][1].ctl = SPI_TxDMA_DESCR1_CFG;

    /* If the Generate IRQ option is selected for descriptor 0 or 1, set the
    * channel bit field in the DMA interrupt mask register.
    */
    #if (0u != ((SPI_TxDMA_DESCR0_CFG | SPI_TxDMA_DESCR1_CFG) & CYDMA_GENERATE_IRQ))
        CYDMA_INTR_MASK_REG |= SPI_TxDMA_CHANNEL_MASK;
    #endif /* (0u != ((SPI_TxDMA_DESCR0_CFG | SPI_TxDMA_DESCR1_CFG) & CYDMA_GENERATE_IRQ)) */
}


/* [] END OF FILE */
