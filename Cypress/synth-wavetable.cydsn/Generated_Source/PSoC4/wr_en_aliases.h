/*******************************************************************************
* File Name: wr_en.h  
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

#if !defined(CY_PINS_wr_en_ALIASES_H) /* Pins wr_en_ALIASES_H */
#define CY_PINS_wr_en_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define wr_en_0			(wr_en__0__PC)
#define wr_en_0_PS		(wr_en__0__PS)
#define wr_en_0_PC		(wr_en__0__PC)
#define wr_en_0_DR		(wr_en__0__DR)
#define wr_en_0_SHIFT	(wr_en__0__SHIFT)
#define wr_en_0_INTR	((uint16)((uint16)0x0003u << (wr_en__0__SHIFT*2u)))

#define wr_en_INTR_ALL	 ((uint16)(wr_en_0_INTR))


#endif /* End Pins wr_en_ALIASES_H */


/* [] END OF FILE */
