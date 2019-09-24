#include <project.h>
#include "Codec.h"
#include "AudioControl.h"
#include "waves.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"

int main() {
    UART_Start();
    LED_Write(1);
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
    
    /* Configure CPU/DMA to be in round robin mode while accessing memory */
	CY_SET_REG32((void *) 0x40100038, CY_GET_REG32((void *) 0x40100038) | 0x22222222);     
	
    CodecI2CM_Start();	
	if(Codec_Init() == 0) {
    	UART_UartPutString("Codec comm works!... \r\n");
        Codec_Activate();
	}
	else {
		UART_UartPutString("Codec comm DOESN'T work!... \r\n");
	}
    
    I2S_Start();
    I2S_TX_CH0_ACTL_REG |= I2S_FIFO0_LVL;
    isr_I2S_underflow_StartEx(I2SUnderflow);
    
    CyGlobalIntEnable;
	CyIntSetPriority(CYDMA_INTR_NUMBER, 0);
    
    //TxDMA_ctrl_Write(0);
    ProcessAudioOut(outBuffer, &buffer_index);
    
    for(;;) {
        //char string[30];
        //sprintf(string, "%lu\n",TxByteCounter_ReadCounter());
        //UART_UartPutString(string);
        
        if(FIFO_DMA_REQ_FLAG){
            FIFO_DMA_REQ_FLAG = 0;
        }
        
        if(DMA_done_flag){
            //TxDMA_ctrl_Write(~TxDMA_ctrl_Read());
            //TxDMA_count_ctrl_Write(~TxDMA_count_ctrl_Read());
            
            
            
            //if(DMA_counter % 2 != 0){
                DMA_done_flag = 0;
                ProcessAudioOut(outBuffer, &buffer_index);
                //TxDMA_ChEnable();
                //LED_Write(~LED_Read());
            //}
            //else{
            //    DMA_done_flag = 0;
            //    TxDMA_ChEnable();
            //    ProcessAudioOut(outBuffer2, &buffer_index2);
            //}
        }
        
        if(update_ADC_flag){
            freq = ADC_GetResult16(0);
        }
    }
}

/* [] END OF FILE */
