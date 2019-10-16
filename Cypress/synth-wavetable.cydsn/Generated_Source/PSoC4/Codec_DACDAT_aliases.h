/*******************************************************************************
* File Name: Codec_DACDAT.h  
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

#if !defined(CY_PINS_Codec_DACDAT_ALIASES_H) /* Pins Codec_DACDAT_ALIASES_H */
#define CY_PINS_Codec_DACDAT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Codec_DACDAT_0			(Codec_DACDAT__0__PC)
#define Codec_DACDAT_0_PS		(Codec_DACDAT__0__PS)
#define Codec_DACDAT_0_PC		(Codec_DACDAT__0__PC)
#define Codec_DACDAT_0_DR		(Codec_DACDAT__0__DR)
#define Codec_DACDAT_0_SHIFT	(Codec_DACDAT__0__SHIFT)
#define Codec_DACDAT_0_INTR	((uint16)((uint16)0x0003u << (Codec_DACDAT__0__SHIFT*2u)))

#define Codec_DACDAT_INTR_ALL	 ((uint16)(Codec_DACDAT_0_INTR))
#define Codec_DACDAT_PSOC_I2S_SDTO			(Codec_DACDAT__PSOC_I2S_SDTO__PC)
#define Codec_DACDAT_PSOC_I2S_SDTO_PS		(Codec_DACDAT__PSOC_I2S_SDTO__PS)
#define Codec_DACDAT_PSOC_I2S_SDTO_PC		(Codec_DACDAT__PSOC_I2S_SDTO__PC)
#define Codec_DACDAT_PSOC_I2S_SDTO_DR		(Codec_DACDAT__PSOC_I2S_SDTO__DR)
#define Codec_DACDAT_PSOC_I2S_SDTO_SHIFT	(Codec_DACDAT__PSOC_I2S_SDTO__SHIFT)
#define Codec_DACDAT_PSOC_I2S_SDTO_INTR	((uint16)((uint16)0x0003u << (Codec_DACDAT__0__SHIFT*2u)))


#endif /* End Pins Codec_DACDAT_ALIASES_H */


/* [] END OF FILE */
