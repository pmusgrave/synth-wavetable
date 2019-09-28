#include "project.h"
#include "oscillator.h"
#include "waves.h"
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



void ProcessVoice(struct voice* v) {
    switch((*v).current_env_mode){
    case ATTACK_MODE:
        (*v).env_index += attack_freq;
        (*v).env_multiplier = base_pos_saw[((*v).env_index>>20) & 0xFFF]; // using pos saw wave here, but should rename to linear ramp or something
        if((*v).env_multiplier > 120) {
            (*v).env_multiplier  = 127;
            (*v).current_env_mode = DECAY_MODE;
        }
        break;
    case DECAY_MODE:
        (*v).env_index -= decay_freq;
        (*v).env_multiplier = base_pos_saw[((*v).env_index>>20) & 0xFFF];
        if((*v).env_multiplier < base_pos_saw[(sustain_freq) & 0xFFF]) {
            (*v).env_multiplier = base_pos_saw[(sustain_freq) & 0xFFF];
            (*v).current_env_mode = SUSTAIN_MODE;
        }
        break;
    case SUSTAIN_MODE:
        (*v).env_multiplier = base_pos_saw[(sustain_freq) & 0xFFF];
        break;
    case RELEASE_MODE:
        (*v).env_index -= release_freq;
        (*v).env_multiplier = base_pos_saw[((*v).env_index>>20) & 0xFFF];
        if((*v).env_multiplier < 10) {
            (*v).env_multiplier = 0;
            (*v).env_index = 0;
            (*v).current_env_mode = NOT_TRIGGERED;
        }
        break;
    }
}

void DispatchNote(uint8 note) {
    freq = music_notes[note-21] * 20;
    
    if(v1.current_env_mode == NOT_TRIGGERED){
        v1.freq = freq;
        v1.note_index = note;
        v1.current_env_mode = SUSTAIN_MODE;
        return;
    }
    else if(v2.current_env_mode == NOT_TRIGGERED){
        v2.freq = freq;
        v2.note_index = note;
        v2.current_env_mode = SUSTAIN_MODE;
        return;
    }
    else if(v3.current_env_mode == NOT_TRIGGERED){
        v3.freq = freq;
        v3.note_index = note;
        v3.current_env_mode = SUSTAIN_MODE;
        return;
    }
    else if(v4.current_env_mode == NOT_TRIGGERED){
        v4.freq = freq;
        v4.note_index = note;
        v4.current_env_mode = SUSTAIN_MODE;
        return;
    }
}

void NoteOff(uint8 note){
    if(v1.note_index == note){
        v1.current_env_mode = NOT_TRIGGERED;
        v1.env_multiplier = 0;
    }
    else if(v2.note_index == note){
        v2.current_env_mode = NOT_TRIGGERED;
        v2.env_multiplier = 0;
    }
    else if(v3.note_index == note){
        v3.current_env_mode = NOT_TRIGGERED;
        v3.env_multiplier = 0;
    }
    else if(v4.note_index == note){
        v4.current_env_mode = NOT_TRIGGERED;
        v4.env_multiplier = 0;
    }
}

/* [] END OF FILE */
