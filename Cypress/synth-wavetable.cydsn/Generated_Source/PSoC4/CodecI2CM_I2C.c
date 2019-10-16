/***************************************************************************//**
* \file CodecI2CM_I2C.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CodecI2CM_PVT.h"
#include "CodecI2CM_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 CodecI2CM_state;  /* Current state of I2C FSM */

#if(CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const CodecI2CM_I2C_INIT_STRUCT CodecI2CM_configI2C =
    {
        CodecI2CM_I2C_MODE,
        CodecI2CM_I2C_OVS_FACTOR_LOW,
        CodecI2CM_I2C_OVS_FACTOR_HIGH,
        CodecI2CM_I2C_MEDIAN_FILTER_ENABLE,
        CodecI2CM_I2C_SLAVE_ADDRESS,
        CodecI2CM_I2C_SLAVE_ADDRESS_MASK,
        CodecI2CM_I2C_ACCEPT_ADDRESS,
        CodecI2CM_I2C_WAKE_ENABLE,
        CodecI2CM_I2C_BYTE_MODE_ENABLE,
        CodecI2CM_I2C_DATA_RATE,
        CodecI2CM_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: CodecI2CM_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the CodecI2CM for I2C operation.
    *
    *  This function is intended specifically to be used when the CodecI2CM 
    *  configuration is set to “Unconfigured CodecI2CM” in the customizer. 
    *  After initializing the CodecI2CM in I2C mode using this function, 
    *  the component can be enabled using the CodecI2CM_Start() or 
    * CodecI2CM_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void CodecI2CM_I2CInit(const CodecI2CM_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            CodecI2CM_SetPins(CodecI2CM_SCB_MODE_I2C, CodecI2CM_DUMMY_PARAM,
                                     CodecI2CM_DUMMY_PARAM);

            /* Store internal configuration */
            CodecI2CM_scbMode       = (uint8) CodecI2CM_SCB_MODE_I2C;
            CodecI2CM_scbEnableWake = (uint8) config->enableWake;
            CodecI2CM_scbEnableIntr = (uint8) CodecI2CM_SCB_IRQ_INTERNAL;

            CodecI2CM_mode          = (uint8) config->mode;
            CodecI2CM_acceptAddr    = (uint8) config->acceptAddr;

        #if (CodecI2CM_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            CodecI2CM_SET_I2C_CFG_SDA_FILT_TRIM(CodecI2CM_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (CodecI2CM_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((CodecI2CM_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= CodecI2CM_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (CodecI2CM_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                CodecI2CM_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = CodecI2CM_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                CodecI2CM_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = CodecI2CM_DIGITAL_FILTER_ENABLE;
            }

        #if (!CodecI2CM_CY_SCBIP_V0)
            locEnableWake = (CodecI2CM_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!CodecI2CM_CY_SCBIP_V0) */

            /* Configure I2C interface */
            CodecI2CM_CTRL_REG     = CodecI2CM_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            CodecI2CM_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            CodecI2CM_GET_CTRL_EC_AM_MODE (locEnableWake);

            CodecI2CM_I2C_CTRL_REG = CodecI2CM_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    CodecI2CM_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    CodecI2CM_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    CodecI2CM_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            CodecI2CM_RX_CTRL_REG      = CodecI2CM_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                CodecI2CM_I2C_RX_CTRL;
            CodecI2CM_RX_FIFO_CTRL_REG = CodecI2CM_CLEAR_REG;

            /* Set default address and mask */
            CodecI2CM_RX_MATCH_REG    = ((CodecI2CM_I2C_SLAVE) ?
                                                (CodecI2CM_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 CodecI2CM_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (CodecI2CM_CLEAR_REG));


            /* Configure TX direction */
            CodecI2CM_TX_CTRL_REG      = CodecI2CM_I2C_TX_CTRL;
            CodecI2CM_TX_FIFO_CTRL_REG = CodecI2CM_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (CodecI2CM_ISR_NUMBER);
            CyIntSetPriority(CodecI2CM_ISR_NUMBER, CodecI2CM_ISR_PRIORITY);
            (void) CyIntSetVector(CodecI2CM_ISR_NUMBER, &CodecI2CM_I2C_ISR);

            /* Configure interrupt sources */
        #if(!CodecI2CM_CY_SCBIP_V1)
            CodecI2CM_INTR_SPI_EC_MASK_REG = CodecI2CM_NO_INTR_SOURCES;
        #endif /* (!CodecI2CM_CY_SCBIP_V1) */

            CodecI2CM_INTR_I2C_EC_MASK_REG = CodecI2CM_NO_INTR_SOURCES;
            CodecI2CM_INTR_RX_MASK_REG     = CodecI2CM_NO_INTR_SOURCES;
            CodecI2CM_INTR_TX_MASK_REG     = CodecI2CM_NO_INTR_SOURCES;

            CodecI2CM_INTR_SLAVE_MASK_REG  = ((CodecI2CM_I2C_SLAVE) ?
                            (CodecI2CM_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             CodecI2CM_I2C_INTR_SLAVE_MASK) : (CodecI2CM_CLEAR_REG));

            CodecI2CM_INTR_MASTER_MASK_REG = CodecI2CM_NO_INTR_SOURCES;

            /* Configure global variables */
            CodecI2CM_state = CodecI2CM_I2C_FSM_IDLE;

            /* Internal slave variables */
            CodecI2CM_slStatus        = 0u;
            CodecI2CM_slRdBufIndex    = 0u;
            CodecI2CM_slWrBufIndex    = 0u;
            CodecI2CM_slOverFlowCount = 0u;

            /* Internal master variables */
            CodecI2CM_mstrStatus     = 0u;
            CodecI2CM_mstrRdBufIndex = 0u;
            CodecI2CM_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: CodecI2CM_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void CodecI2CM_I2CInit(void)
    {
    #if(CodecI2CM_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        CodecI2CM_SET_I2C_CFG_SDA_FILT_TRIM(CodecI2CM_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (CodecI2CM_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        CodecI2CM_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        CodecI2CM_CTRL_REG     = CodecI2CM_I2C_DEFAULT_CTRL;
        CodecI2CM_I2C_CTRL_REG = CodecI2CM_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        CodecI2CM_RX_CTRL_REG      = CodecI2CM_I2C_DEFAULT_RX_CTRL;
        CodecI2CM_RX_FIFO_CTRL_REG = CodecI2CM_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        CodecI2CM_RX_MATCH_REG     = CodecI2CM_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        CodecI2CM_TX_CTRL_REG      = CodecI2CM_I2C_DEFAULT_TX_CTRL;
        CodecI2CM_TX_FIFO_CTRL_REG = CodecI2CM_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (CodecI2CM_ISR_NUMBER);
        CyIntSetPriority(CodecI2CM_ISR_NUMBER, CodecI2CM_ISR_PRIORITY);
    #if(!CodecI2CM_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(CodecI2CM_ISR_NUMBER, &CodecI2CM_I2C_ISR);
    #endif /* (CodecI2CM_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!CodecI2CM_CY_SCBIP_V1)
        CodecI2CM_INTR_SPI_EC_MASK_REG = CodecI2CM_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!CodecI2CM_CY_SCBIP_V1) */

        CodecI2CM_INTR_I2C_EC_MASK_REG = CodecI2CM_I2C_DEFAULT_INTR_I2C_EC_MASK;
        CodecI2CM_INTR_SLAVE_MASK_REG  = CodecI2CM_I2C_DEFAULT_INTR_SLAVE_MASK;
        CodecI2CM_INTR_MASTER_MASK_REG = CodecI2CM_I2C_DEFAULT_INTR_MASTER_MASK;
        CodecI2CM_INTR_RX_MASK_REG     = CodecI2CM_I2C_DEFAULT_INTR_RX_MASK;
        CodecI2CM_INTR_TX_MASK_REG     = CodecI2CM_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        CodecI2CM_state = CodecI2CM_I2C_FSM_IDLE;

    #if(CodecI2CM_I2C_SLAVE)
        /* Internal slave variable */
        CodecI2CM_slStatus        = 0u;
        CodecI2CM_slRdBufIndex    = 0u;
        CodecI2CM_slWrBufIndex    = 0u;
        CodecI2CM_slOverFlowCount = 0u;
    #endif /* (CodecI2CM_I2C_SLAVE) */

    #if(CodecI2CM_I2C_MASTER)
    /* Internal master variable */
        CodecI2CM_mstrStatus     = 0u;
        CodecI2CM_mstrRdBufIndex = 0u;
        CodecI2CM_mstrWrBufIndex = 0u;
    #endif /* (CodecI2CM_I2C_MASTER) */
    }
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: CodecI2CM_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void CodecI2CM_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    CodecI2CM_I2C_MASTER_CMD_REG = 0u;
    CodecI2CM_I2C_SLAVE_CMD_REG  = 0u;
    
    CodecI2CM_state = CodecI2CM_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: CodecI2CM_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void CodecI2CM_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    CodecI2CM_CTRL_REG &= (uint32) ~CodecI2CM_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    CodecI2CM_I2C_MASTER_CMD_REG = 0u;
    CodecI2CM_I2C_SLAVE_CMD_REG  = 0u;

    CodecI2CM_DISABLE_AUTO_DATA;

    CodecI2CM_SetTxInterruptMode(CodecI2CM_NO_INTR_SOURCES);
    CodecI2CM_SetRxInterruptMode(CodecI2CM_NO_INTR_SOURCES);
    
#if(CodecI2CM_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    CodecI2CM_ClearTxInterruptSource    (CodecI2CM_INTR_TX_ALL);
    CodecI2CM_ClearRxInterruptSource    (CodecI2CM_INTR_RX_ALL);
    CodecI2CM_ClearSlaveInterruptSource (CodecI2CM_INTR_SLAVE_ALL);
    CodecI2CM_ClearMasterInterruptSource(CodecI2CM_INTR_MASTER_ALL);
#endif /* (CodecI2CM_CY_SCBIP_V0) */

    CodecI2CM_state = CodecI2CM_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    CodecI2CM_CTRL_REG |= (uint32) CodecI2CM_CTRL_ENABLED;
}


#if(CodecI2CM_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: CodecI2CM_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables CodecI2CM_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void CodecI2CM_I2CSaveConfig(void)
    {
    #if (!CodecI2CM_CY_SCBIP_V0)
        #if (CodecI2CM_I2C_MULTI_MASTER_SLAVE_CONST && CodecI2CM_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (CodecI2CM_CTRL_REG & CodecI2CM_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                CodecI2CM_Stop();
                CodecI2CM_CTRL_REG |= CodecI2CM_CTRL_EC_AM_MODE;
                CodecI2CM_Enable();
            }
        #endif /* (CodecI2CM_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (CodecI2CM_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            CodecI2CM_SCBCLK_Stop();
        #endif /* (CodecI2CM_SCB_CLK_INTERNAL) */
    #endif /* (!CodecI2CM_CY_SCBIP_V0) */

        CodecI2CM_SetI2CExtClkInterruptMode(CodecI2CM_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: CodecI2CM_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables CodecI2CM_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void CodecI2CM_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        CodecI2CM_SetI2CExtClkInterruptMode(CodecI2CM_NO_INTR_SOURCES);

    #if (!CodecI2CM_CY_SCBIP_V0)
        #if (CodecI2CM_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            CodecI2CM_SCBCLK_Start();
        #endif /* (CodecI2CM_SCB_CLK_INTERNAL) */
    #endif /* (!CodecI2CM_CY_SCBIP_V0) */
    }
#endif /* (CodecI2CM_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
