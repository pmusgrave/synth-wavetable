#include <project.h>
#include "Codec.h"
#include "AudioControl.h"
#include "waves.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"

int main() {
    UART_Start();
    TxByteCounter_Start();
    
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
    
    CodecI2CM_Start();	
	if(Codec_Init() == 0) {
    	UART_UartPutString("Codec comm works!... \r\n");
        Codec_Activate();
	}
	else {
		UART_UartPutString("Codec comm DOESN'T work!... \r\n");
	}
    
    I2S_Start();
    I2S_EnableTx(); /* Unmute the TX output */ 
    isr_I2S_underflow_StartEx(I2SUnderflow);
    
    CyGlobalIntEnable;
    
    ProcessAudioOut(output_buffer, &buffer_index);
    ProcessAudioOut(output_buffer2, &buffer_index);
    
    for(;;) {
        if(DMA_done_flag){
            DMA_done_flag = 0;
            if(DMA_counter % 2 == 0){
                CyGlobalIntEnable;
                //UART_UartPutString("0\r\n");
                ProcessAudioOut(output_buffer2, &buffer_index);
            }
            else {
                CyGlobalIntEnable;
                //UART_UartPutString("1\r\n");
                ProcessAudioOut(output_buffer, &buffer_index);
            }
        }

        if(update_ADC_flag){
            freq = ADC_GetResult16(0);
            freq2 = ADC_GetResult16(1);
        }
    }
}

/* [] END OF FILE */
