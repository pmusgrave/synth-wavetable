/*******************************************************************************
* File Name: new_sample.h  
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

#if !defined(CY_PINS_new_sample_ALIASES_H) /* Pins new_sample_ALIASES_H */
#define CY_PINS_new_sample_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define new_sample_0			(new_sample__0__PC)
#define new_sample_0_PS		(new_sample__0__PS)
#define new_sample_0_PC		(new_sample__0__PC)
#define new_sample_0_DR		(new_sample__0__DR)
#define new_sample_0_SHIFT	(new_sample__0__SHIFT)
#define new_sample_0_INTR	((uint16)((uint16)0x0003u << (new_sample__0__SHIFT*2u)))

#define new_sample_INTR_ALL	 ((uint16)(new_sample_0_INTR))


#endif /* End Pins new_sample_ALIASES_H */


/* [] END OF FILE */
