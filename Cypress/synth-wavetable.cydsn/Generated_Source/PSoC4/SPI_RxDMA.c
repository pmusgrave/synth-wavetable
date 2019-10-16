/*******************************************************************************
* File Name: SPI_RxDMA.h
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

#include "SPI_RxDMA.h"

uint8 SPI_RxDMA_initVar = 0u;


/*******************************************************************************
* Function Name: SPI_RxDMA_Start
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
void SPI_RxDMA_Start(void * srcAddress, void * dstAddress)
{
    if(0u == SPI_RxDMA_initVar)
    {
        SPI_RxDMA_Init();
        SPI_RxDMA_initVar = 1u;
    }
    CyDmaEnable();
    SPI_RxDMA_SetSrcAddress(0, srcAddress);
    SPI_RxDMA_SetDstAddress(0, dstAddress);
    SPI_RxDMA_ValidateDescriptor(0);
    SPI_RxDMA_ChEnable();
}


/*******************************************************************************
* Function Name: SPI_RxDMA_Init
********************************************************************************
*
* Summary:
*  Initializes the DMA channel based on the parameters set in the component
*  customizer. It is not necessary to call SPI_RxDMA_Init() because the
*  SPI_RxDMA_Start() API calls this function, which is the preferred method
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
void SPI_RxDMA_Init(void)
{
    CYDMA_CH_CTL_BASE.ctl[SPI_RxDMA_CHANNEL] = SPI_RxDMA_CHANNEL_CFG;
    CYDMA_DESCR_BASE.descriptor[SPI_RxDMA_CHANNEL][0].ctl = SPI_RxDMA_DESCR0_CFG;
    CYDMA_DESCR_BASE.descriptor[SPI_RxDMA_CHANNEL][1].ctl = SPI_RxDMA_DESCR1_CFG;

    /* If the Generate IRQ option is selected for descriptor 0 or 1, set the
    * channel bit field in the DMA interrupt mask register.
    */
    #if (0u != ((SPI_RxDMA_DESCR0_CFG | SPI_RxDMA_DESCR1_CFG) & CYDMA_GENERATE_IRQ))
        CYDMA_INTR_MASK_REG |= SPI_RxDMA_CHANNEL_MASK;
    #endif /* (0u != ((SPI_RxDMA_DESCR0_CFG | SPI_RxDMA_DESCR1_CFG) & CYDMA_GENERATE_IRQ)) */
}


/* [] END OF FILE */
