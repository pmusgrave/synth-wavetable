#include <project.h>
#include "Codec.h"
#include "AudioControl.h"
#include "waves.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"

extern uint8 outBuffer[];
int32_t pot_value;

int main()
{
    UART_Start();
    LED_Write(1);
    
    UART_UartPutString("\r\n\r\n\r\n********************\r\n");
    UART_UartPutString("PMA Wavetable Synth\r\n");
    UART_UartPutString("********************\r\n");
	InitAudioPath();
    UART_UartPutString("Audio path initialized...\r\n");
    
    init_wavetable();
    UART_UartPutString("Wavetable initialized...\r\n");
    
    
    ADC_Start();
    ADC_StartConvert();
    isr_ADC_EOC_StartEx(ADC_EOC);
    //ADC_DMA_SetInterruptCallback(ADC_DMA_DoneInterrupt);
    //ADC_DMA_Start((void*)ADC_SAR_CHAN0_RESULT_PTR, &pot_value);
    
    /* Configure CPU/DMA to be in round robin mode while accessing memory */
	//CY_SET_REG32((void *) 0x40100038, CY_GET_REG32((void *) 0x40100038) | 0x22222222);     
	
    CodecI2CM_Start();	
	if(Codec_Init() == 0)
	{
    	UART_UartPutString("Codec comm works!... \r\n");
        Codec_Activate();
	}
	else
	{
		UART_UartPutString("Codec comm DOESN'T work!... \r\n");
	}
    
    I2S_Start();
    isr_I2S_underflow_StartEx(I2SUnderflow);
    CyGlobalIntEnable;
	CyIntSetPriority(CYDMA_INTR_NUMBER, 0);
    	
    //int index = 0;
    ProcessAudioOut();
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
