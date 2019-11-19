EESchema Schematic File Version 4
LIBS:power
LIBS:74xx
LIBS:synth_psoc-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 650  650  800  700 
U 5C356C07
F0 "Power" 60
F1 "power.sch" 60
$EndSheet
$Sheet
S 9800 3700 600  800 
U 5C357081
F0 "Mixer and Effects" 60
F1 "mixer.sch" 60
F2 "osc1" I L 9800 3750 60 
F3 "osc2" I L 9800 3850 60 
F4 "osc3" I L 9800 3950 60 
F5 "osc4" I L 9800 4050 60 
F6 "lfo_freq_in" O L 9800 4300 60 
F7 "lfo_freq_out" I L 9800 4400 60 
F8 "mcu_delay_in" O R 10400 4100 60 
F9 "mcu_delay_out" I R 10400 4200 60 
$EndSheet
$Sheet
S 950  2400 1850 5100
U 5C5CADB1
F0 "Connectors" 60
F1 "connectors.sch" 60
F2 "osc1_freq_wiper" O R 2800 4450 60 
F3 "osc1_pwm_wiper" O R 2800 4550 60 
F4 "osc1_speed" O R 2800 4650 60 
F5 "freq_in_1" I R 2800 2500 60 
F6 "freq_out_1" O R 2800 2700 60 
F7 "envelope_pwm_bypass_in_1" I R 2800 4750 60 
F8 "envelope_pwm_bypass_out_1" O R 2800 4850 60 
F9 "osc1_repeat" O R 2800 4950 60 
F10 "osc1_quant" O R 2800 5050 60 
F11 "osc2_freq_wiper" O R 2800 5250 60 
F12 "osc2_pwm_wiper" O R 2800 5350 60 
F13 "osc2_speed" O R 2800 5450 60 
F14 "freq_in_2" I R 2800 2800 60 
F15 "freq_out_2" O R 2800 3000 60 
F16 "envelope_pwm_bypass_in_2" I R 2800 5550 60 
F17 "envelope_pwm_bypass_out_2" O R 2800 5650 60 
F18 "osc2_repeat" O R 2800 5750 60 
F19 "osc2_quant" O R 2800 5850 60 
F20 "osc3_freq_wiper" O R 2800 6050 60 
F21 "osc3_pwm_wiper" O R 2800 6150 60 
F22 "osc3_speed" O R 2800 6250 60 
F23 "freq_in_3" I R 2800 3100 60 
F24 "freq_out_3" O R 2800 3300 60 
F25 "envelope_pwm_bypass_in_3" I R 2800 6350 60 
F26 "envelope_pwm_bypass_out_3" O R 2800 6450 60 
F27 "osc3_repeat" O R 2800 6550 60 
F28 "osc3_quant" O R 2800 6650 60 
F29 "osc4_freq_wiper" O R 2800 6850 60 
F30 "osc4_pwm_wiper" O R 2800 6950 60 
F31 "osc4_speed" O R 2800 7050 60 
F32 "freq_in_4" I R 2800 3400 60 
F33 "freq_out_4" O R 2800 3600 60 
F34 "envelope_pwm_bypass_in_4" I R 2800 7150 60 
F35 "envelope_pwm_bypass_out_4" O R 2800 7250 60 
F36 "osc4_repeat" O R 2800 7350 60 
F37 "osc4_quant" O R 2800 7450 60 
F38 "freq_fb_1" I R 2800 2600 60 
F39 "freq_fb_2" I R 2800 2900 60 
F40 "freq_fb_3" I R 2800 3200 60 
F41 "freq_fb_4" I R 2800 3500 60 
F42 "lfo_in_1" O L 950 2550 60 
F43 "lfo_out_1" I L 950 2650 60 
F44 "lfo_in_2" O L 950 2750 60 
F45 "lfo_out_2" I L 950 2850 60 
F46 "lfo_in_3" O L 950 2950 60 
F47 "lfo_out_3" I L 950 3050 60 
F48 "lfo_in_4" O L 950 3150 60 
F49 "lfo_out_4" I L 950 3250 60 
F50 "osc1_hold" O R 2800 4350 60 
F51 "osc2_hold" O R 2800 5150 60 
F52 "osc3_hold" O R 2800 5950 60 
F53 "osc4_hold" O R 2800 6750 60 
$EndSheet
Text Label 10550 5450 0    60   ~ 0
lfo_in_1
Text Label 10550 5550 0    60   ~ 0
lfo_out_1
Text Label 10550 5650 0    60   ~ 0
lfo_in_2
Text Label 10550 5750 0    60   ~ 0
lfo_out_2
Text Label 10550 5850 0    60   ~ 0
lfo_in_3
Text Label 10550 5950 0    60   ~ 0
lfo_out_3
Text Label 10550 6050 0    60   ~ 0
lfo_in_4
Text Label 10550 6150 0    60   ~ 0
lfo_out_4
Wire Wire Line
	10550 5450 10300 5450
Wire Wire Line
	10300 5550 10550 5550
Wire Wire Line
	10550 5650 10300 5650
Wire Wire Line
	10300 5750 10550 5750
Wire Wire Line
	10550 5850 10300 5850
Wire Wire Line
	10300 5950 10550 5950
Wire Wire Line
	10550 6050 10300 6050
Wire Wire Line
	10550 6150 10300 6150
$Sheet
S 9650 4850 650  1600
U 5C35738C
F0 "LFO Modulation and Routing" 60
F1 "lfo.sch" 60
F2 "lfo1" O R 10300 4950 60 
F3 "lfo2" O R 10300 5050 60 
F4 "lfo3" O R 10300 5150 60 
F5 "lfo4" O R 10300 5250 60 
F6 "lfo_in_1" O R 10300 5450 60 
F7 "lfo_out_1" I R 10300 5550 60 
F8 "lfo_in_2" O R 10300 5650 60 
F9 "lfo_out_2" I R 10300 5750 60 
F10 "lfo_in_3" O R 10300 5850 60 
F11 "lfo_out_3" I R 10300 5950 60 
F12 "lfo_in_4" O R 10300 6050 60 
F13 "lfo_out_4" I R 10300 6150 60 
F14 "lfo_freq_in" O R 10300 6250 60 
F15 "lfo_freq_out" I R 10300 6350 60 
$EndSheet
Text Label 10550 6350 0    60   ~ 0
lfo_freq_out
Text Label 10550 6250 0    60   ~ 0
lfo_freq_in
Wire Wire Line
	10550 6350 10300 6350
Wire Wire Line
	10300 6250 10550 6250
Text Label 9700 4300 2    60   ~ 0
lfo_freq_in
Text Label 9700 4400 2    60   ~ 0
lfo_freq_out
Wire Wire Line
	9700 4300 9800 4300
Wire Wire Line
	9700 4400 9800 4400
Text Label 10550 4100 0    60   ~ 0
mcu_delay_in
Text Label 10550 4200 0    60   ~ 0
mcu_delay_out
Wire Wire Line
	10550 4100 10400 4100
Wire Wire Line
	10400 4200 10550 4200
$Sheet
S 3650 2450 1450 5050
U 5C3546FC
F0 "Control" 60
F1 "control-mcu.sch" 60
F2 "osc1_freq_wiper" I L 3650 4450 60 
F3 "osc1_pwm_wiper" I L 3650 4550 60 
F4 "osc2_freq_wiper" I L 3650 5250 60 
F5 "osc2_pwm_wiper" I L 3650 5350 60 
F6 "osc3_freq_wiper" I L 3650 6050 60 
F7 "osc3_pwm_wiper" I L 3650 6150 60 
F8 "osc4_freq_wiper" I L 3650 6850 60 
F9 "osc4_pwm_wiper" I L 3650 6950 60 
F10 "osc1_speed" I L 3650 4650 60 
F11 "osc2_speed" I L 3650 5450 60 
F12 "osc3_speed" I L 3650 6250 60 
F13 "osc4_speed" I L 3650 7050 60 
F14 "osc1_quant" I L 3650 5050 60 
F15 "osc2_quant" I L 3650 5850 60 
F16 "osc3_quant" I L 3650 6650 60 
F17 "osc4_quant" I L 3650 7450 60 
F18 "osc1_repeat" I L 3650 4950 60 
F19 "osc2_repeat" I L 3650 5750 60 
F20 "osc3_repeat" I L 3650 6550 60 
F21 "osc4_repeat" I L 3650 7350 60 
F22 "envelope_pwm_bypass_in_1" O L 3650 4750 60 
F23 "envelope_pwm_bypass_in_2" O L 3650 5550 60 
F24 "envelope_pwm_bypass_in_3" O L 3650 6350 60 
F25 "envelope_pwm_bypass_in_4" O L 3650 7150 60 
F26 "envelope_pwm_bypass_out_1" I L 3650 4850 60 
F27 "envelope_pwm_bypass_out_2" I L 3650 5650 60 
F28 "envelope_pwm_bypass_out_3" I L 3650 6450 60 
F29 "envelope_pwm_bypass_out_4" I L 3650 7250 60 
F30 "osc1_hold" I L 3650 4350 60 
F31 "osc2_hold" I L 3650 5150 60 
F32 "osc3_hold" I L 3650 5950 60 
F33 "osc4_hold" I L 3650 6750 60 
$EndSheet
$Sheet
S 6150 1550 2150 1450
U 5DDAFB2F
F0 "Audio Engine" 50
F1 "audio-engine.sch" 50
$EndSheet
$EndSCHEMATC
