#include <project.h>
#include "Codec.h"
#include "AudioControl.h"
#include "sinewaves.h"

extern uint8 outBuffer[];

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
    
    /* Configure CPU/DMA to be in round robin mode while accessing memory */
	CY_SET_REG32((void *) 0x40100038, CY_GET_REG32((void *) 0x40100038) | 0x22222222);     
	
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
    CyGlobalIntEnable;
	CyIntSetPriority(CYDMA_INTR_NUMBER, 0);
    	
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
