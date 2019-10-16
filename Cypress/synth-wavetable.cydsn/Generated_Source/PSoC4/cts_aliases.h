/*******************************************************************************
* File Name: cts.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_cts_ALIASES_H) /* Pins cts_ALIASES_H */
#define CY_PINS_cts_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define cts_0			(cts__0__PC)
#define cts_0_PS		(cts__0__PS)
#define cts_0_PC		(cts__0__PC)
#define cts_0_DR		(cts__0__DR)
#define cts_0_SHIFT	(cts__0__SHIFT)
#define cts_0_INTR	((uint16)((uint16)0x0003u << (cts__0__SHIFT*2u)))

#define cts_INTR_ALL	 ((uint16)(cts_0_INTR))


#endif /* End Pins cts_ALIASES_H */


/* [] END OF FILE */
