/*******************************************************************************
* File Name: Codec_MCLK.h  
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

#if !defined(CY_PINS_Codec_MCLK_ALIASES_H) /* Pins Codec_MCLK_ALIASES_H */
#define CY_PINS_Codec_MCLK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Codec_MCLK_0			(Codec_MCLK__0__PC)
#define Codec_MCLK_0_PS		(Codec_MCLK__0__PS)
#define Codec_MCLK_0_PC		(Codec_MCLK__0__PC)
#define Codec_MCLK_0_DR		(Codec_MCLK__0__DR)
#define Codec_MCLK_0_SHIFT	(Codec_MCLK__0__SHIFT)
#define Codec_MCLK_0_INTR	((uint16)((uint16)0x0003u << (Codec_MCLK__0__SHIFT*2u)))

#define Codec_MCLK_INTR_ALL	 ((uint16)(Codec_MCLK_0_INTR))
#define Codec_MCLK_PSOC_I2S_MCLK			(Codec_MCLK__PSOC_I2S_MCLK__PC)
#define Codec_MCLK_PSOC_I2S_MCLK_PS		(Codec_MCLK__PSOC_I2S_MCLK__PS)
#define Codec_MCLK_PSOC_I2S_MCLK_PC		(Codec_MCLK__PSOC_I2S_MCLK__PC)
#define Codec_MCLK_PSOC_I2S_MCLK_DR		(Codec_MCLK__PSOC_I2S_MCLK__DR)
#define Codec_MCLK_PSOC_I2S_MCLK_SHIFT	(Codec_MCLK__PSOC_I2S_MCLK__SHIFT)
#define Codec_MCLK_PSOC_I2S_MCLK_INTR	((uint16)((uint16)0x0003u << (Codec_MCLK__0__SHIFT*2u)))


#endif /* End Pins Codec_MCLK_ALIASES_H */


/* [] END OF FILE */
