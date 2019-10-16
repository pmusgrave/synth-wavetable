/*******************************************************************************
* File Name: Codec_LRC.h  
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

#if !defined(CY_PINS_Codec_LRC_ALIASES_H) /* Pins Codec_LRC_ALIASES_H */
#define CY_PINS_Codec_LRC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Codec_LRC_0			(Codec_LRC__0__PC)
#define Codec_LRC_0_PS		(Codec_LRC__0__PS)
#define Codec_LRC_0_PC		(Codec_LRC__0__PC)
#define Codec_LRC_0_DR		(Codec_LRC__0__DR)
#define Codec_LRC_0_SHIFT	(Codec_LRC__0__SHIFT)
#define Codec_LRC_0_INTR	((uint16)((uint16)0x0003u << (Codec_LRC__0__SHIFT*2u)))

#define Codec_LRC_INTR_ALL	 ((uint16)(Codec_LRC_0_INTR))
#define Codec_LRC_PSOC_I2S_LRCLK			(Codec_LRC__PSOC_I2S_LRCLK__PC)
#define Codec_LRC_PSOC_I2S_LRCLK_PS		(Codec_LRC__PSOC_I2S_LRCLK__PS)
#define Codec_LRC_PSOC_I2S_LRCLK_PC		(Codec_LRC__PSOC_I2S_LRCLK__PC)
#define Codec_LRC_PSOC_I2S_LRCLK_DR		(Codec_LRC__PSOC_I2S_LRCLK__DR)
#define Codec_LRC_PSOC_I2S_LRCLK_SHIFT	(Codec_LRC__PSOC_I2S_LRCLK__SHIFT)
#define Codec_LRC_PSOC_I2S_LRCLK_INTR	((uint16)((uint16)0x0003u << (Codec_LRC__0__SHIFT*2u)))


#endif /* End Pins Codec_LRC_ALIASES_H */


/* [] END OF FILE */
