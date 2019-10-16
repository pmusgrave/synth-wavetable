/*******************************************************************************
* File Name: MIDI1_UART_IntClock.h
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

#if !defined(CY_CLOCK_MIDI1_UART_IntClock_H)
#define CY_CLOCK_MIDI1_UART_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void MIDI1_UART_IntClock_StartEx(uint32 alignClkDiv);
#define MIDI1_UART_IntClock_Start() \
    MIDI1_UART_IntClock_StartEx(MIDI1_UART_IntClock__PA_DIV_ID)

#else

void MIDI1_UART_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void MIDI1_UART_IntClock_Stop(void);

void MIDI1_UART_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 MIDI1_UART_IntClock_GetDividerRegister(void);
uint8  MIDI1_UART_IntClock_GetFractionalDividerRegister(void);

#define MIDI1_UART_IntClock_Enable()                         MIDI1_UART_IntClock_Start()
#define MIDI1_UART_IntClock_Disable()                        MIDI1_UART_IntClock_Stop()
#define MIDI1_UART_IntClock_SetDividerRegister(clkDivider, reset)  \
    MIDI1_UART_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define MIDI1_UART_IntClock_SetDivider(clkDivider)           MIDI1_UART_IntClock_SetDividerRegister((clkDivider), 1u)
#define MIDI1_UART_IntClock_SetDividerValue(clkDivider)      MIDI1_UART_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define MIDI1_UART_IntClock_DIV_ID     MIDI1_UART_IntClock__DIV_ID

#define MIDI1_UART_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define MIDI1_UART_IntClock_CTRL_REG   (*(reg32 *)MIDI1_UART_IntClock__CTRL_REGISTER)
#define MIDI1_UART_IntClock_DIV_REG    (*(reg32 *)MIDI1_UART_IntClock__DIV_REGISTER)

#define MIDI1_UART_IntClock_CMD_DIV_SHIFT          (0u)
#define MIDI1_UART_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define MIDI1_UART_IntClock_CMD_DISABLE_SHIFT      (30u)
#define MIDI1_UART_IntClock_CMD_ENABLE_SHIFT       (31u)

#define MIDI1_UART_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << MIDI1_UART_IntClock_CMD_DISABLE_SHIFT))
#define MIDI1_UART_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << MIDI1_UART_IntClock_CMD_ENABLE_SHIFT))

#define MIDI1_UART_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define MIDI1_UART_IntClock_DIV_FRAC_SHIFT (3u)
#define MIDI1_UART_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define MIDI1_UART_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define MIDI1_UART_IntClock_DIV_REG        (*(reg32 *)MIDI1_UART_IntClock__REGISTER)
#define MIDI1_UART_IntClock_ENABLE_REG     MIDI1_UART_IntClock_DIV_REG
#define MIDI1_UART_IntClock_DIV_FRAC_MASK  MIDI1_UART_IntClock__FRAC_MASK
#define MIDI1_UART_IntClock_DIV_FRAC_SHIFT (16u)
#define MIDI1_UART_IntClock_DIV_INT_MASK   MIDI1_UART_IntClock__DIVIDER_MASK
#define MIDI1_UART_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_MIDI1_UART_IntClock_H) */

/* [] END OF FILE */
