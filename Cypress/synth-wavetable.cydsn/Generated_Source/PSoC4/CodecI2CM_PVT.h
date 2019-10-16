/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_CodecI2CM_H)
#define CY_SCB_PVT_CodecI2CM_H

#include "CodecI2CM.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define CodecI2CM_SetI2CExtClkInterruptMode(interruptMask) CodecI2CM_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define CodecI2CM_ClearI2CExtClkInterruptSource(interruptMask) CodecI2CM_CLEAR_INTR_I2C_EC(interruptMask)
#define CodecI2CM_GetI2CExtClkInterruptSource()                (CodecI2CM_INTR_I2C_EC_REG)
#define CodecI2CM_GetI2CExtClkInterruptMode()                  (CodecI2CM_INTR_I2C_EC_MASK_REG)
#define CodecI2CM_GetI2CExtClkInterruptSourceMasked()          (CodecI2CM_INTR_I2C_EC_MASKED_REG)

#if (!CodecI2CM_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define CodecI2CM_SetSpiExtClkInterruptMode(interruptMask) \
                                                                CodecI2CM_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define CodecI2CM_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                CodecI2CM_CLEAR_INTR_SPI_EC(interruptMask)
    #define CodecI2CM_GetExtSpiClkInterruptSource()                 (CodecI2CM_INTR_SPI_EC_REG)
    #define CodecI2CM_GetExtSpiClkInterruptMode()                   (CodecI2CM_INTR_SPI_EC_MASK_REG)
    #define CodecI2CM_GetExtSpiClkInterruptSourceMasked()           (CodecI2CM_INTR_SPI_EC_MASKED_REG)
#endif /* (!CodecI2CM_CY_SCBIP_V1) */

#if(CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void CodecI2CM_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (CodecI2CM_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_CodecI2CM_CUSTOM_INTR_HANDLER)
    extern cyisraddress CodecI2CM_customIntrHandler;
#endif /* !defined (CY_REMOVE_CodecI2CM_CUSTOM_INTR_HANDLER) */
#endif /* (CodecI2CM_SCB_IRQ_INTERNAL) */

extern CodecI2CM_BACKUP_STRUCT CodecI2CM_backup;

#if(CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 CodecI2CM_scbMode;
    extern uint8 CodecI2CM_scbEnableWake;
    extern uint8 CodecI2CM_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 CodecI2CM_mode;
    extern uint8 CodecI2CM_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * CodecI2CM_rxBuffer;
    extern uint8   CodecI2CM_rxDataBits;
    extern uint32  CodecI2CM_rxBufferSize;

    extern volatile uint8 * CodecI2CM_txBuffer;
    extern uint8   CodecI2CM_txDataBits;
    extern uint32  CodecI2CM_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 CodecI2CM_numberOfAddr;
    extern uint8 CodecI2CM_subAddrSize;
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (CodecI2CM_SCB_MODE_I2C_CONST_CFG || \
        CodecI2CM_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 CodecI2CM_IntrTxMask;
#endif /* (! (CodecI2CM_SCB_MODE_I2C_CONST_CFG || \
              CodecI2CM_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define CodecI2CM_SCB_MODE_I2C_RUNTM_CFG     (CodecI2CM_SCB_MODE_I2C      == CodecI2CM_scbMode)
    #define CodecI2CM_SCB_MODE_SPI_RUNTM_CFG     (CodecI2CM_SCB_MODE_SPI      == CodecI2CM_scbMode)
    #define CodecI2CM_SCB_MODE_UART_RUNTM_CFG    (CodecI2CM_SCB_MODE_UART     == CodecI2CM_scbMode)
    #define CodecI2CM_SCB_MODE_EZI2C_RUNTM_CFG   (CodecI2CM_SCB_MODE_EZI2C    == CodecI2CM_scbMode)
    #define CodecI2CM_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (CodecI2CM_SCB_MODE_UNCONFIG == CodecI2CM_scbMode)

    /* Defines wakeup enable */
    #define CodecI2CM_SCB_WAKE_ENABLE_CHECK       (0u != CodecI2CM_scbEnableWake)
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!CodecI2CM_CY_SCBIP_V1)
    #define CodecI2CM_SCB_PINS_NUMBER    (7u)
#else
    #define CodecI2CM_SCB_PINS_NUMBER    (2u)
#endif /* (!CodecI2CM_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_CodecI2CM_H) */


/* [] END OF FILE */
