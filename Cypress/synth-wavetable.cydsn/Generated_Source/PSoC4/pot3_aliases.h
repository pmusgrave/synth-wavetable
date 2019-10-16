/*******************************************************************************
* File Name: pot3.h  
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

#if !defined(CY_PINS_pot3_ALIASES_H) /* Pins pot3_ALIASES_H */
#define CY_PINS_pot3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pot3_0			(pot3__0__PC)
#define pot3_0_PS		(pot3__0__PS)
#define pot3_0_PC		(pot3__0__PC)
#define pot3_0_DR		(pot3__0__DR)
#define pot3_0_SHIFT	(pot3__0__SHIFT)
#define pot3_0_INTR	((uint16)((uint16)0x0003u << (pot3__0__SHIFT*2u)))

#define pot3_INTR_ALL	 ((uint16)(pot3_0_INTR))


#endif /* End Pins pot3_ALIASES_H */


/* [] END OF FILE */
