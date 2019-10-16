/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
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

#if !defined(CY_SCB_I2C_PVT_CodecI2CM_H)
#define CY_SCB_I2C_PVT_CodecI2CM_H

#include "CodecI2CM_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 CodecI2CM_state; /* Current state of I2C FSM */

#if(CodecI2CM_I2C_SLAVE_CONST)
    extern volatile uint8 CodecI2CM_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * CodecI2CM_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  CodecI2CM_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  CodecI2CM_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * CodecI2CM_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  CodecI2CM_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  CodecI2CM_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  CodecI2CM_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   CodecI2CM_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (CodecI2CM_I2C_SLAVE_CONST) */

#if(CodecI2CM_I2C_MASTER_CONST)
    extern volatile uint16 CodecI2CM_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  CodecI2CM_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * CodecI2CM_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  CodecI2CM_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  CodecI2CM_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * CodecI2CM_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  CodecI2CM_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  CodecI2CM_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  CodecI2CM_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (CodecI2CM_I2C_MASTER_CONST) */

#if (CodecI2CM_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*CodecI2CM_customAddressHandler) (void);
#endif /* (CodecI2CM_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(CodecI2CM_SCB_MODE_I2C_CONST_CFG)
    void CodecI2CM_I2CInit(void);
#endif /* (CodecI2CM_SCB_MODE_I2C_CONST_CFG) */

void CodecI2CM_I2CStop(void);
void CodecI2CM_I2CFwBlockReset(void);

void CodecI2CM_I2CSaveConfig(void);
void CodecI2CM_I2CRestoreConfig(void);

#if(CodecI2CM_I2C_MASTER_CONST)
    void CodecI2CM_I2CReStartGeneration(void);
#endif /* (CodecI2CM_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_CodecI2CM_H) */


/* [] END OF FILE */
