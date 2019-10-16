/*******************************************************************************
* File Name: trigger.h  
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

#if !defined(CY_PINS_trigger_ALIASES_H) /* Pins trigger_ALIASES_H */
#define CY_PINS_trigger_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define trigger_0			(trigger__0__PC)
#define trigger_0_PS		(trigger__0__PS)
#define trigger_0_PC		(trigger__0__PC)
#define trigger_0_DR		(trigger__0__DR)
#define trigger_0_SHIFT	(trigger__0__SHIFT)
#define trigger_0_INTR	((uint16)((uint16)0x0003u << (trigger__0__SHIFT*2u)))

#define trigger_INTR_ALL	 ((uint16)(trigger_0_INTR))


#endif /* End Pins trigger_ALIASES_H */


/* [] END OF FILE */
