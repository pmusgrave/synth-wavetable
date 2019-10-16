/*******************************************************************************
* File Name: CodecI2CM_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_CodecI2CM_SCBCLK_H)
#define CY_CLOCK_CodecI2CM_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void CodecI2CM_SCBCLK_StartEx(uint32 alignClkDiv);
#define CodecI2CM_SCBCLK_Start() \
    CodecI2CM_SCBCLK_StartEx(CodecI2CM_SCBCLK__PA_DIV_ID)

#else

void CodecI2CM_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void CodecI2CM_SCBCLK_Stop(void);

void CodecI2CM_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CodecI2CM_SCBCLK_GetDividerRegister(void);
uint8  CodecI2CM_SCBCLK_GetFractionalDividerRegister(void);

#define CodecI2CM_SCBCLK_Enable()                         CodecI2CM_SCBCLK_Start()
#define CodecI2CM_SCBCLK_Disable()                        CodecI2CM_SCBCLK_Stop()
#define CodecI2CM_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    CodecI2CM_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define CodecI2CM_SCBCLK_SetDivider(clkDivider)           CodecI2CM_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define CodecI2CM_SCBCLK_SetDividerValue(clkDivider)      CodecI2CM_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define CodecI2CM_SCBCLK_DIV_ID     CodecI2CM_SCBCLK__DIV_ID

#define CodecI2CM_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define CodecI2CM_SCBCLK_CTRL_REG   (*(reg32 *)CodecI2CM_SCBCLK__CTRL_REGISTER)
#define CodecI2CM_SCBCLK_DIV_REG    (*(reg32 *)CodecI2CM_SCBCLK__DIV_REGISTER)

#define CodecI2CM_SCBCLK_CMD_DIV_SHIFT          (0u)
#define CodecI2CM_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define CodecI2CM_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define CodecI2CM_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define CodecI2CM_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << CodecI2CM_SCBCLK_CMD_DISABLE_SHIFT))
#define CodecI2CM_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << CodecI2CM_SCBCLK_CMD_ENABLE_SHIFT))

#define CodecI2CM_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define CodecI2CM_SCBCLK_DIV_FRAC_SHIFT (3u)
#define CodecI2CM_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define CodecI2CM_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define CodecI2CM_SCBCLK_DIV_REG        (*(reg32 *)CodecI2CM_SCBCLK__REGISTER)
#define CodecI2CM_SCBCLK_ENABLE_REG     CodecI2CM_SCBCLK_DIV_REG
#define CodecI2CM_SCBCLK_DIV_FRAC_MASK  CodecI2CM_SCBCLK__FRAC_MASK
#define CodecI2CM_SCBCLK_DIV_FRAC_SHIFT (16u)
#define CodecI2CM_SCBCLK_DIV_INT_MASK   CodecI2CM_SCBCLK__DIVIDER_MASK
#define CodecI2CM_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_CodecI2CM_SCBCLK_H) */

/* [] END OF FILE */
