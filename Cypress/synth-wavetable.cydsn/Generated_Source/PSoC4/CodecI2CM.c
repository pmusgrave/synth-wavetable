/***************************************************************************//**
* \file CodecI2CM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CodecI2CM_PVT.h"

#if (CodecI2CM_SCB_MODE_I2C_INC)
    #include "CodecI2CM_I2C_PVT.h"
#endif /* (CodecI2CM_SCB_MODE_I2C_INC) */

#if (CodecI2CM_SCB_MODE_EZI2C_INC)
    #include "CodecI2CM_EZI2C_PVT.h"
#endif /* (CodecI2CM_SCB_MODE_EZI2C_INC) */

#if (CodecI2CM_SCB_MODE_SPI_INC || CodecI2CM_SCB_MODE_UART_INC)
    #include "CodecI2CM_SPI_UART_PVT.h"
#endif /* (CodecI2CM_SCB_MODE_SPI_INC || CodecI2CM_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 CodecI2CM_scbMode = CodecI2CM_SCB_MODE_UNCONFIG;
    uint8 CodecI2CM_scbEnableWake;
    uint8 CodecI2CM_scbEnableIntr;

    /* I2C configuration variables */
    uint8 CodecI2CM_mode;
    uint8 CodecI2CM_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * CodecI2CM_rxBuffer;
    uint8  CodecI2CM_rxDataBits;
    uint32 CodecI2CM_rxBufferSize;

    volatile uint8 * CodecI2CM_txBuffer;
    uint8  CodecI2CM_txDataBits;
    uint32 CodecI2CM_txBufferSize;

    /* EZI2C configuration variables */
    uint8 CodecI2CM_numberOfAddr;
    uint8 CodecI2CM_subAddrSize;
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** CodecI2CM_initVar indicates whether the CodecI2CM 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the CodecI2CM_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  CodecI2CM_Init() function can be called before the 
*  CodecI2CM_Start() or CodecI2CM_Enable() function.
*/
uint8 CodecI2CM_initVar = 0u;


#if (! (CodecI2CM_SCB_MODE_I2C_CONST_CFG || \
        CodecI2CM_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * CodecI2CM_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent CodecI2CM_Enable() call.
    */
    uint16 CodecI2CM_IntrTxMask = 0u;
#endif /* (! (CodecI2CM_SCB_MODE_I2C_CONST_CFG || \
              CodecI2CM_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (CodecI2CM_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_CodecI2CM_CUSTOM_INTR_HANDLER)
    void (*CodecI2CM_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_CodecI2CM_CUSTOM_INTR_HANDLER) */
#endif /* (CodecI2CM_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void CodecI2CM_ScbEnableIntr(void);
static void CodecI2CM_ScbModeStop(void);
static void CodecI2CM_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: CodecI2CM_Init
****************************************************************************//**
*
*  Initializes the CodecI2CM component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  CodecI2CM_I2CInit, CodecI2CM_SpiInit, 
*  CodecI2CM_UartInit or CodecI2CM_EzI2CInit.
*
*******************************************************************************/
void CodecI2CM_Init(void)
{
#if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    if (CodecI2CM_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        CodecI2CM_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (CodecI2CM_SCB_MODE_I2C_CONST_CFG)
    CodecI2CM_I2CInit();

#elif (CodecI2CM_SCB_MODE_SPI_CONST_CFG)
    CodecI2CM_SpiInit();

#elif (CodecI2CM_SCB_MODE_UART_CONST_CFG)
    CodecI2CM_UartInit();

#elif (CodecI2CM_SCB_MODE_EZI2C_CONST_CFG)
    CodecI2CM_EzI2CInit();

#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: CodecI2CM_Enable
****************************************************************************//**
*
*  Enables CodecI2CM component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  CodecI2CM_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The CodecI2CM configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured CodecI2CM”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void CodecI2CM_Enable(void)
{
#if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!CodecI2CM_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        CodecI2CM_CTRL_REG |= CodecI2CM_CTRL_ENABLED;

        CodecI2CM_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        CodecI2CM_ScbModePostEnable();
    }
#else
    CodecI2CM_CTRL_REG |= CodecI2CM_CTRL_ENABLED;

    CodecI2CM_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    CodecI2CM_ScbModePostEnable();
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: CodecI2CM_Start
****************************************************************************//**
*
*  Invokes CodecI2CM_Init() and CodecI2CM_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  CodecI2CM_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void CodecI2CM_Start(void)
{
    if (0u == CodecI2CM_initVar)
    {
        CodecI2CM_Init();
        CodecI2CM_initVar = 1u; /* Component was initialized */
    }

    CodecI2CM_Enable();
}


/*******************************************************************************
* Function Name: CodecI2CM_Stop
****************************************************************************//**
*
*  Disables the CodecI2CM component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function CodecI2CM_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void CodecI2CM_Stop(void)
{
#if (CodecI2CM_SCB_IRQ_INTERNAL)
    CodecI2CM_DisableInt();
#endif /* (CodecI2CM_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    CodecI2CM_ScbModeStop();

    /* Disable SCB IP */
    CodecI2CM_CTRL_REG &= (uint32) ~CodecI2CM_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    CodecI2CM_SetTxInterruptMode(CodecI2CM_NO_INTR_SOURCES);

#if (CodecI2CM_SCB_IRQ_INTERNAL)
    CodecI2CM_ClearPendingInt();
#endif /* (CodecI2CM_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: CodecI2CM_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void CodecI2CM_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = CodecI2CM_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~CodecI2CM_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (CodecI2CM_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    CodecI2CM_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: CodecI2CM_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void CodecI2CM_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = CodecI2CM_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~CodecI2CM_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (CodecI2CM_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    CodecI2CM_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (CodecI2CM_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: CodecI2CM_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void CodecI2CM_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_CodecI2CM_CUSTOM_INTR_HANDLER)
        CodecI2CM_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_CodecI2CM_CUSTOM_INTR_HANDLER) */
    }
#endif /* (CodecI2CM_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: CodecI2CM_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void CodecI2CM_ScbEnableIntr(void)
{
#if (CodecI2CM_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != CodecI2CM_scbEnableIntr)
        {
            CodecI2CM_EnableInt();
        }

    #else
        CodecI2CM_EnableInt();

    #endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (CodecI2CM_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: CodecI2CM_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void CodecI2CM_ScbModePostEnable(void)
{
#if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!CodecI2CM_CY_SCBIP_V1)
    if (CodecI2CM_SCB_MODE_SPI_RUNTM_CFG)
    {
        CodecI2CM_SpiPostEnable();
    }
    else if (CodecI2CM_SCB_MODE_UART_RUNTM_CFG)
    {
        CodecI2CM_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!CodecI2CM_CY_SCBIP_V1) */

#elif (CodecI2CM_SCB_MODE_SPI_CONST_CFG)
    CodecI2CM_SpiPostEnable();

#elif (CodecI2CM_SCB_MODE_UART_CONST_CFG)
    CodecI2CM_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: CodecI2CM_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void CodecI2CM_ScbModeStop(void)
{
#if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    if (CodecI2CM_SCB_MODE_I2C_RUNTM_CFG)
    {
        CodecI2CM_I2CStop();
    }
    else if (CodecI2CM_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        CodecI2CM_EzI2CStop();
    }
#if (!CodecI2CM_CY_SCBIP_V1)
    else if (CodecI2CM_SCB_MODE_SPI_RUNTM_CFG)
    {
        CodecI2CM_SpiStop();
    }
    else if (CodecI2CM_SCB_MODE_UART_RUNTM_CFG)
    {
        CodecI2CM_UartStop();
    }
#endif /* (!CodecI2CM_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (CodecI2CM_SCB_MODE_I2C_CONST_CFG)
    CodecI2CM_I2CStop();

#elif (CodecI2CM_SCB_MODE_EZI2C_CONST_CFG)
    CodecI2CM_EzI2CStop();

#elif (CodecI2CM_SCB_MODE_SPI_CONST_CFG)
    CodecI2CM_SpiStop();

#elif (CodecI2CM_SCB_MODE_UART_CONST_CFG)
    CodecI2CM_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: CodecI2CM_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void CodecI2CM_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[CodecI2CM_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!CodecI2CM_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!CodecI2CM_CY_SCBIP_V1) */
        
        uint32 hsiomSel[CodecI2CM_SCB_PINS_NUMBER] = 
        {
            CodecI2CM_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            CodecI2CM_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (CodecI2CM_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (CodecI2CM_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < CodecI2CM_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = CodecI2CM_PIN_DM_ALG_HIZ;
        }

        if ((CodecI2CM_SCB_MODE_I2C   == mode) ||
            (CodecI2CM_SCB_MODE_EZI2C == mode))
        {
        #if (CodecI2CM_RX_SCL_MOSI_PIN)
            hsiomSel[CodecI2CM_RX_SCL_MOSI_PIN_INDEX] = CodecI2CM_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [CodecI2CM_RX_SCL_MOSI_PIN_INDEX] = CodecI2CM_PIN_DM_OD_LO;
        #elif (CodecI2CM_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[CodecI2CM_RX_WAKE_SCL_MOSI_PIN_INDEX] = CodecI2CM_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [CodecI2CM_RX_WAKE_SCL_MOSI_PIN_INDEX] = CodecI2CM_PIN_DM_OD_LO;
        #else
        #endif /* (CodecI2CM_RX_SCL_MOSI_PIN) */
        
        #if (CodecI2CM_TX_SDA_MISO_PIN)
            hsiomSel[CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_PIN_DM_OD_LO;
        #endif /* (CodecI2CM_TX_SDA_MISO_PIN) */
        }
    #if (!CodecI2CM_CY_SCBIP_V1)
        else if (CodecI2CM_SCB_MODE_SPI == mode)
        {
        #if (CodecI2CM_RX_SCL_MOSI_PIN)
            hsiomSel[CodecI2CM_RX_SCL_MOSI_PIN_INDEX] = CodecI2CM_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (CodecI2CM_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[CodecI2CM_RX_WAKE_SCL_MOSI_PIN_INDEX] = CodecI2CM_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (CodecI2CM_RX_SCL_MOSI_PIN) */
        
        #if (CodecI2CM_TX_SDA_MISO_PIN)
            hsiomSel[CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (CodecI2CM_TX_SDA_MISO_PIN) */
        
        #if (CodecI2CM_CTS_SCLK_PIN)
            hsiomSel[CodecI2CM_CTS_SCLK_PIN_INDEX] = CodecI2CM_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (CodecI2CM_CTS_SCLK_PIN) */

            if (CodecI2CM_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[CodecI2CM_RX_SCL_MOSI_PIN_INDEX] = CodecI2CM_PIN_DM_DIG_HIZ;
                pinsDm[CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                pinsDm[CodecI2CM_CTS_SCLK_PIN_INDEX] = CodecI2CM_PIN_DM_DIG_HIZ;

            #if (CodecI2CM_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[CodecI2CM_RTS_SS0_PIN_INDEX] = CodecI2CM_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [CodecI2CM_RTS_SS0_PIN_INDEX] = CodecI2CM_PIN_DM_DIG_HIZ;
            #endif /* (CodecI2CM_RTS_SS0_PIN) */

            #if (CodecI2CM_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= CodecI2CM_TX_SDA_MISO_PIN_MASK;
            #endif /* (CodecI2CM_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[CodecI2CM_RX_SCL_MOSI_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                pinsDm[CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_PIN_DM_DIG_HIZ;
                pinsDm[CodecI2CM_CTS_SCLK_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;

            #if (CodecI2CM_RTS_SS0_PIN)
                hsiomSel [CodecI2CM_RTS_SS0_PIN_INDEX] = CodecI2CM_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [CodecI2CM_RTS_SS0_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                pinsInBuf |= CodecI2CM_RTS_SS0_PIN_MASK;
            #endif /* (CodecI2CM_RTS_SS0_PIN) */

            #if (CodecI2CM_SS1_PIN)
                hsiomSel [CodecI2CM_SS1_PIN_INDEX] = CodecI2CM_SS1_HSIOM_SEL_SPI;
                pinsDm   [CodecI2CM_SS1_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                pinsInBuf |= CodecI2CM_SS1_PIN_MASK;
            #endif /* (CodecI2CM_SS1_PIN) */

            #if (CodecI2CM_SS2_PIN)
                hsiomSel [CodecI2CM_SS2_PIN_INDEX] = CodecI2CM_SS2_HSIOM_SEL_SPI;
                pinsDm   [CodecI2CM_SS2_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                pinsInBuf |= CodecI2CM_SS2_PIN_MASK;
            #endif /* (CodecI2CM_SS2_PIN) */

            #if (CodecI2CM_SS3_PIN)
                hsiomSel [CodecI2CM_SS3_PIN_INDEX] = CodecI2CM_SS3_HSIOM_SEL_SPI;
                pinsDm   [CodecI2CM_SS3_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                pinsInBuf |= CodecI2CM_SS3_PIN_MASK;
            #endif /* (CodecI2CM_SS3_PIN) */

                /* Disable input buffers */
            #if (CodecI2CM_RX_SCL_MOSI_PIN)
                pinsInBuf |= CodecI2CM_RX_SCL_MOSI_PIN_MASK;
            #elif (CodecI2CM_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= CodecI2CM_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (CodecI2CM_RX_SCL_MOSI_PIN) */

            #if (CodecI2CM_CTS_SCLK_PIN)
                pinsInBuf |= CodecI2CM_CTS_SCLK_PIN_MASK;
            #endif /* (CodecI2CM_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (CodecI2CM_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (CodecI2CM_TX_SDA_MISO_PIN)
                hsiomSel[CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_PIN_DM_OD_LO;
            #endif /* (CodecI2CM_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (CodecI2CM_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (CodecI2CM_RX_SCL_MOSI_PIN)
                    hsiomSel[CodecI2CM_RX_SCL_MOSI_PIN_INDEX] = CodecI2CM_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [CodecI2CM_RX_SCL_MOSI_PIN_INDEX] = CodecI2CM_PIN_DM_DIG_HIZ;
                #elif (CodecI2CM_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[CodecI2CM_RX_WAKE_SCL_MOSI_PIN_INDEX] = CodecI2CM_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [CodecI2CM_RX_WAKE_SCL_MOSI_PIN_INDEX] = CodecI2CM_PIN_DM_DIG_HIZ;
                #else
                #endif /* (CodecI2CM_RX_SCL_MOSI_PIN) */
                }

                if (0u != (CodecI2CM_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (CodecI2CM_TX_SDA_MISO_PIN)
                    hsiomSel[CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [CodecI2CM_TX_SDA_MISO_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= CodecI2CM_TX_SDA_MISO_PIN_MASK;
                #endif /* (CodecI2CM_TX_SDA_MISO_PIN) */
                }

            #if !(CodecI2CM_CY_SCBIP_V0 || CodecI2CM_CY_SCBIP_V1)
                if (CodecI2CM_UART_MODE_STD == subMode)
                {
                    if (0u != (CodecI2CM_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (CodecI2CM_CTS_SCLK_PIN)
                        hsiomSel[CodecI2CM_CTS_SCLK_PIN_INDEX] = CodecI2CM_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [CodecI2CM_CTS_SCLK_PIN_INDEX] = CodecI2CM_PIN_DM_DIG_HIZ;
                    #endif /* (CodecI2CM_CTS_SCLK_PIN) */
                    }

                    if (0u != (CodecI2CM_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (CodecI2CM_RTS_SS0_PIN)
                        hsiomSel[CodecI2CM_RTS_SS0_PIN_INDEX] = CodecI2CM_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [CodecI2CM_RTS_SS0_PIN_INDEX] = CodecI2CM_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= CodecI2CM_RTS_SS0_PIN_MASK;
                    #endif /* (CodecI2CM_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(CodecI2CM_CY_SCBIP_V0 || CodecI2CM_CY_SCBIP_V1) */
            }
        }
    #endif /* (!CodecI2CM_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (CodecI2CM_RX_SCL_MOSI_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_RX_SCL_MOSI_HSIOM_REG,
                                       CodecI2CM_RX_SCL_MOSI_HSIOM_MASK,
                                       CodecI2CM_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[CodecI2CM_RX_SCL_MOSI_PIN_INDEX]);

        CodecI2CM_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[CodecI2CM_RX_SCL_MOSI_PIN_INDEX]);

        #if (!CodecI2CM_CY_SCBIP_V1)
            CodecI2CM_SET_INP_DIS(CodecI2CM_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         CodecI2CM_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & CodecI2CM_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!CodecI2CM_CY_SCBIP_V1) */
    
    #elif (CodecI2CM_RX_WAKE_SCL_MOSI_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       CodecI2CM_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       CodecI2CM_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[CodecI2CM_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        CodecI2CM_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[CodecI2CM_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        CodecI2CM_SET_INP_DIS(CodecI2CM_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     CodecI2CM_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & CodecI2CM_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        CodecI2CM_SET_INCFG_TYPE(CodecI2CM_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        CodecI2CM_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        CodecI2CM_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        CodecI2CM_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (CodecI2CM_RX_WAKE_SCL_MOSI_PIN) */

    #if (CodecI2CM_TX_SDA_MISO_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_TX_SDA_MISO_HSIOM_REG,
                                       CodecI2CM_TX_SDA_MISO_HSIOM_MASK,
                                       CodecI2CM_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[CodecI2CM_TX_SDA_MISO_PIN_INDEX]);

        CodecI2CM_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[CodecI2CM_TX_SDA_MISO_PIN_INDEX]);

    #if (!CodecI2CM_CY_SCBIP_V1)
        CodecI2CM_SET_INP_DIS(CodecI2CM_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     CodecI2CM_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & CodecI2CM_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!CodecI2CM_CY_SCBIP_V1) */
    #endif /* (CodecI2CM_RX_SCL_MOSI_PIN) */

    #if (CodecI2CM_CTS_SCLK_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_CTS_SCLK_HSIOM_REG,
                                       CodecI2CM_CTS_SCLK_HSIOM_MASK,
                                       CodecI2CM_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[CodecI2CM_CTS_SCLK_PIN_INDEX]);

        CodecI2CM_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[CodecI2CM_CTS_SCLK_PIN_INDEX]);

        CodecI2CM_SET_INP_DIS(CodecI2CM_uart_cts_spi_sclk_INP_DIS,
                                     CodecI2CM_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & CodecI2CM_CTS_SCLK_PIN_MASK)));
    #endif /* (CodecI2CM_CTS_SCLK_PIN) */

    #if (CodecI2CM_RTS_SS0_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_RTS_SS0_HSIOM_REG,
                                       CodecI2CM_RTS_SS0_HSIOM_MASK,
                                       CodecI2CM_RTS_SS0_HSIOM_POS,
                                       hsiomSel[CodecI2CM_RTS_SS0_PIN_INDEX]);

        CodecI2CM_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[CodecI2CM_RTS_SS0_PIN_INDEX]);

        CodecI2CM_SET_INP_DIS(CodecI2CM_uart_rts_spi_ss0_INP_DIS,
                                     CodecI2CM_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & CodecI2CM_RTS_SS0_PIN_MASK)));
    #endif /* (CodecI2CM_RTS_SS0_PIN) */

    #if (CodecI2CM_SS1_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_SS1_HSIOM_REG,
                                       CodecI2CM_SS1_HSIOM_MASK,
                                       CodecI2CM_SS1_HSIOM_POS,
                                       hsiomSel[CodecI2CM_SS1_PIN_INDEX]);

        CodecI2CM_spi_ss1_SetDriveMode((uint8) pinsDm[CodecI2CM_SS1_PIN_INDEX]);

        CodecI2CM_SET_INP_DIS(CodecI2CM_spi_ss1_INP_DIS,
                                     CodecI2CM_spi_ss1_MASK,
                                     (0u != (pinsInBuf & CodecI2CM_SS1_PIN_MASK)));
    #endif /* (CodecI2CM_SS1_PIN) */

    #if (CodecI2CM_SS2_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_SS2_HSIOM_REG,
                                       CodecI2CM_SS2_HSIOM_MASK,
                                       CodecI2CM_SS2_HSIOM_POS,
                                       hsiomSel[CodecI2CM_SS2_PIN_INDEX]);

        CodecI2CM_spi_ss2_SetDriveMode((uint8) pinsDm[CodecI2CM_SS2_PIN_INDEX]);

        CodecI2CM_SET_INP_DIS(CodecI2CM_spi_ss2_INP_DIS,
                                     CodecI2CM_spi_ss2_MASK,
                                     (0u != (pinsInBuf & CodecI2CM_SS2_PIN_MASK)));
    #endif /* (CodecI2CM_SS2_PIN) */

    #if (CodecI2CM_SS3_PIN)
        CodecI2CM_SET_HSIOM_SEL(CodecI2CM_SS3_HSIOM_REG,
                                       CodecI2CM_SS3_HSIOM_MASK,
                                       CodecI2CM_SS3_HSIOM_POS,
                                       hsiomSel[CodecI2CM_SS3_PIN_INDEX]);

        CodecI2CM_spi_ss3_SetDriveMode((uint8) pinsDm[CodecI2CM_SS3_PIN_INDEX]);

        CodecI2CM_SET_INP_DIS(CodecI2CM_spi_ss3_INP_DIS,
                                     CodecI2CM_spi_ss3_MASK,
                                     (0u != (pinsInBuf & CodecI2CM_SS3_PIN_MASK)));
    #endif /* (CodecI2CM_SS3_PIN) */
    }

#endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (CodecI2CM_CY_SCBIP_V0 || CodecI2CM_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: CodecI2CM_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void CodecI2CM_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (CodecI2CM_CTRL_REG & CodecI2CM_CTRL_EC_AM_MODE)) &&
            (0u == (CodecI2CM_I2C_CTRL_REG & CodecI2CM_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            CodecI2CM_CTRL_REG &= ~CodecI2CM_CTRL_EC_AM_MODE;
            CodecI2CM_CTRL_REG |=  CodecI2CM_CTRL_EC_AM_MODE;
        }

        CodecI2CM_I2C_SLAVE_CMD_REG = CodecI2CM_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (CodecI2CM_CY_SCBIP_V0 || CodecI2CM_CY_SCBIP_V1) */


/* [] END OF FILE */
