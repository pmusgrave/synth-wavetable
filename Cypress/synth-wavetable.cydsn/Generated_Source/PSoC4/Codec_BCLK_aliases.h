/*******************************************************************************
* File Name: Codec_BCLK.h  
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

#if !defined(CY_PINS_Codec_BCLK_ALIASES_H) /* Pins Codec_BCLK_ALIASES_H */
#define CY_PINS_Codec_BCLK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Codec_BCLK_0			(Codec_BCLK__0__PC)
#define Codec_BCLK_0_PS		(Codec_BCLK__0__PS)
#define Codec_BCLK_0_PC		(Codec_BCLK__0__PC)
#define Codec_BCLK_0_DR		(Codec_BCLK__0__DR)
#define Codec_BCLK_0_SHIFT	(Codec_BCLK__0__SHIFT)
#define Codec_BCLK_0_INTR	((uint16)((uint16)0x0003u << (Codec_BCLK__0__SHIFT*2u)))

#define Codec_BCLK_INTR_ALL	 ((uint16)(Codec_BCLK_0_INTR))
#define Codec_BCLK_PSOC_I2S_BCLK			(Codec_BCLK__PSOC_I2S_BCLK__PC)
#define Codec_BCLK_PSOC_I2S_BCLK_PS		(Codec_BCLK__PSOC_I2S_BCLK__PS)
#define Codec_BCLK_PSOC_I2S_BCLK_PC		(Codec_BCLK__PSOC_I2S_BCLK__PC)
#define Codec_BCLK_PSOC_I2S_BCLK_DR		(Codec_BCLK__PSOC_I2S_BCLK__DR)
#define Codec_BCLK_PSOC_I2S_BCLK_SHIFT	(Codec_BCLK__PSOC_I2S_BCLK__SHIFT)
#define Codec_BCLK_PSOC_I2S_BCLK_INTR	((uint16)((uint16)0x0003u << (Codec_BCLK__0__SHIFT*2u)))


#endif /* End Pins Codec_BCLK_ALIASES_H */


/* [] END OF FILE */
