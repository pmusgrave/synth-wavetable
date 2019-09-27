#include "project.h"
#include "oscillator.h"
#include "globals.h"

double music_notes[99] = {
    9.0110625,
    9.5484495,
    10.11532725,
    10.7149725,
    11.35393875,
    12.02894925,
    12.74328075,
    13.50021,
    14.30301375,
    15.15496875,
    16.056075,
    17.00960925,
    18.022125,
    19.09362225,
    20.2306545,
    21.43322175,
    22.7078775,
    24.0578985,
    25.4865615,
    27.00369675,
    28.60930425,
    30.3099375,
    32.11215,
    34.02249525,
    36.04425,
    38.1872445,
    40.45803225,
    42.86316675,
    45.41247825,
    48.11252025,
    50.973123,
    54.00411675,
    57.21533175,
    60.619875,
    64.2243,
    68.04171375,
    72.0885,
    76.374489,
    80.9160645,
    85.72961025,
    90.8249565,
    96.2250405,
    101.9495228,
    108.0115103,
    114.4339403,
    121.2364733,
    128.4486,
    136.0834275,
    144.177,
    152.748978,
    161.832129,
    171.4559438,
    181.6531898,
    192.4533578,
    203.8957688,
    216.0197438,
    228.8678805,
    242.4762233,
    256.8939233,
    272.1701318,
    288.354,
    305.5012328,
    323.6675348,
    342.9118875,
    363.3031028,
    384.9067155,
    407.7948143,
    432.0427643,
    457.7324843,
    484.9524465,
    513.7878465,
    544.3402635,
    576.708,
    611.0024655,
    647.3317928,
    685.823775,
    726.6062055,
    769.813431,
    815.5896285,
    864.0855285,
    915.4682453,
    969.904893,
    1027.575693,
    1088.680527,
    1153.416,
    1222.001654,
    1294.666862,
    1371.650827,
    1453.212411,
    1539.623585,
    1631.17598,
    1728.171057,
    1830.933214,
    1939.806509,
    2055.154663,
    2177.361054,
    2306.832,
    2444.003309,
    2589.330448
};


// this is a square wave with 50% duty cycle
//main_osc_PWM_WriteCompare((uint16) (65535/freq)/2);

// this is pulse width modulation, although the 2000 does not make any sense.
// wasn't getting good results with 65535/pulse_width?
// fix this later

void EnableAllOscillators(){
    
}

void DisableAllOscillators(){
    
}


// I don't think these have to be separate functions,
// unless I want to do something more complicated than execute the function pointer.
// It might be good to check the state of the oscillator before calling the
// enable function? Otherwise, I could probably get rid of this function
// and the disable single oscillator function.
void EnableSingleOscillator(void (*osc_enable_function)(void)){
    (*osc_enable_function)();
}

void DisableSingleOscillator(void (*osc_disable_function)(void)){
    (*osc_disable_function)();
}

double Quantize(float unquantized_freq){
    // music_notes frequencies are based on 
    // the equal tempered scale found here:
    // http://pages.mtu.edu/~suits/notefreqs.html
    
    // These are converted from music note frequencies 
    // to the appropriate ADC values: 
    // 65535/(200000/music_note)
    
    // This is done ahead of time to reduce computation.
    
    double quantized_freq = 0;

    for (int i = 0; i < 99; i++){
        if(unquantized_freq >= music_notes[i]){
            quantized_freq = music_notes[i];
        }
    }
    
    return quantized_freq;
}

void DispatchNote(uint8 note){
    // MIDI note values correspond to the music_notes array offset
    // by 21. So MIDI note 21 should use music_notes[0].

    /*
    struct button buttons[4] = {Osc_0_Button, Osc_1_Button, Osc_2_Button, Osc_3_Button};
    struct oscillator oscillators[4] = {Osc_0, Osc_1, Osc_2, Osc_3};
    
    for(int i = 0; i < 4; i++){
        if (buttons[i].MIDI_triggered == 0){
            oscillators[i].freq = Quantize(note - 21);
            buttons[i].MIDI_triggered = 1;
            return;
        }
    }
    */
    
    /*
    if (Osc_2_Button.MIDI_triggered == 1 && Osc_3_Button.MIDI_triggered == 0){
        Osc_3.freq = music_notes[note - 21];
        Osc_3_Button.MIDI_triggered = 1;
    }
    
    if (Osc_1_Button.MIDI_triggered == 1 && Osc_2_Button.MIDI_triggered == 0){
        Osc_2.freq = music_notes[note - 21];
        Osc_2_Button.MIDI_triggered = 1;
    }
    
    if (Osc_0_Button.MIDI_triggered == 1 && Osc_1_Button.MIDI_triggered == 0){
        Osc_1.freq = music_notes[note - 21];
        Osc_1_Button.MIDI_triggered = 1;
    }
    
    if (Osc_0_Button.MIDI_triggered == 0){
        Osc_0.freq = music_notes[note - 21];
        Osc_0_Button.MIDI_triggered = 1;
    }
    */
    freq = music_notes[note-21] * 100;
}

void NoteOff(uint8 note){
    //struct button buttons[4] = {Osc_0_Button, Osc_1_Button, Osc_2_Button, Osc_3_Button};
    //struct oscillator oscillators[4] = {Osc_0, Osc_1, Osc_2, Osc_3};
    /*
    for(int i = 0; i < 4; i++){
        if (oscillators[i].freq == Quantize(note - 21)){
            buttons[i].MIDI_triggered = 0;
            return;
        }
    }
    */
    
    /*
    if ((int)Osc_3.freq == (int)music_notes[note - 21]){
        Osc_3_Button.MIDI_triggered = 0;
    }
    if ((int)Osc_2.freq == (int)music_notes[note - 21]){
        Osc_2_Button.MIDI_triggered = 0;
    }
    if ((int)Osc_1.freq == (int)music_notes[note - 21]){
        Osc_1_Button.MIDI_triggered = 0;
    }
    if ((int)Osc_0.freq == (int)music_notes[note - 21]){
        Osc_0_Button.MIDI_triggered = 0;
    }
    */
}

/* [] END OF FILE */
