#include <project.h>
#include "Codec.h"
#include "AudioControl.h"
#include "waves.h"
#include "Interrupts.h"
#include "AudioOut.h"
#include "globals.h"

uint8_t current_env_mode = 0;

int main() {
    UART_Start();
    TxByteCounter_Start();
    isr_trigger_StartEx(envelope_trigger_interrupt);
    uint16_t attack_freq = 0;
    uint16_t decay_freq = 0;
    uint16_t sustain_freq = 0;
    uint16_t release_freq = 0;
    
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
    
    ProcessAudioOut(output_buffer);
    ProcessAudioOut(output_buffer2);
    
    for(;;) {
        if(DMA_done_flag){
            DMA_done_flag = 0;
            if(DMA_counter % 2 == 0){
                CyGlobalIntEnable;
                //UART_UartPutString("0\r\n");
                ProcessAudioOut(output_buffer2);
            }
            else {
                CyGlobalIntEnable;
                //UART_UartPutString("1\r\n");
                ProcessAudioOut(output_buffer);
            }
        }

        if(update_ADC_flag){
            /*
            freq = ADC_GetResult16(0);
            freq2 = ADC_GetResult16(1);
            freq3 = ADC_GetResult16(2);
            lfo_freq = ADC_GetResult16(3);
            */
            attack_freq = 65535 - ADC_GetResult16(0);
            decay_freq = 65535 - ADC_GetResult16(1);
            sustain_freq = ADC_GetResult16(2);
            release_freq = 65535 - ADC_GetResult16(3);
        }
        
        static uint32_t env_index;
        if(trigger_flag && current_env_mode == ATTACK_MODE){
            env_index += attack_freq;
            envelope_multiplier = base_pos_saw[(env_index>>20) & 0xFFF]; // using pos saw wave here, but should rename to linear ramp or something
            if(envelope_multiplier > 120) {
                envelope_multiplier = 127;
                current_env_mode = DECAY_MODE;
            }
        }
        else if(trigger_flag && current_env_mode == DECAY_MODE){
            env_index -= decay_freq;
            envelope_multiplier = base_pos_saw[(env_index>>20) & 0xFFF];
            if(envelope_multiplier < base_pos_saw[(sustain_freq) & 0xFFF]) {
                envelope_multiplier = base_pos_saw[(sustain_freq) & 0xFFF];
                current_env_mode = SUSTAIN_MODE;
            }
        }
        else if(trigger_flag && current_env_mode == SUSTAIN_MODE){
            envelope_multiplier = base_pos_saw[(sustain_freq) & 0xFFF];
        }
        else if(trigger_flag && current_env_mode == RELEASE_MODE){
            env_index -= release_freq;
            envelope_multiplier = base_pos_saw[(env_index>>20) & 0xFFF];
            if(envelope_multiplier < 10) {
                envelope_multiplier = 0;
                env_index = 0;
                current_env_mode = NOT_TRIGGERED;
                trigger_flag = 0;
            }
        }
        else if (!trigger_flag){
            envelope_multiplier = 0;
            env_index = 0;
        }
        
        CyDelayUs(5);
        //char string[30];
        //sprintf(string, "%d\n",envelope_multiplier);
        //UART_UartPutString(string);
    }
}

/* [] END OF FILE */
