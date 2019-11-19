EESchema Schematic File Version 4
LIBS:power
LIBS:74xx
LIBS:synth_psoc-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 1900 900  2    60   ~ 0
osc1_freq_wiper
Text Label 1900 1100 2    60   ~ 0
osc1_pwm_wiper
Text Label 1900 1300 2    60   ~ 0
osc1_speed
Text Label 2850 900  0    60   ~ 0
osc2_freq_wiper
Text Label 2850 1100 0    60   ~ 0
osc2_pwm_wiper
Text Label 2850 1300 0    60   ~ 0
osc2_speed
Text Label 1900 3000 2    60   ~ 0
osc3_freq_wiper
Text Label 1900 3200 2    60   ~ 0
osc3_pwm_wiper
Text Label 1900 3400 2    60   ~ 0
osc3_speed
Text Label 2800 3000 0    60   ~ 0
osc4_freq_wiper
Text Label 2800 3200 0    60   ~ 0
osc4_pwm_wiper
Text Label 2800 3400 0    60   ~ 0
osc4_speed
Text Label 2800 3800 0    60   ~ 0
envelope_pwm_bypass_in_4
Text Label 1900 3800 2    60   ~ 0
envelope_pwm_bypass_in_3
Text Label 2850 1700 0    60   ~ 0
envelope_pwm_bypass_in_2
Text Label 1900 1700 2    60   ~ 0
envelope_pwm_bypass_in_1
Text Label 2800 3900 0    60   ~ 0
envelope_pwm_bypass_out_4
Text Label 1900 3900 2    60   ~ 0
envelope_pwm_bypass_out_3
Text Label 2850 1800 0    60   ~ 0
envelope_pwm_bypass_out_2
Text Label 1900 1800 2    60   ~ 0
envelope_pwm_bypass_out_1
Text Label 1900 1600 2    60   ~ 0
osc1_repeat
Text Label 2850 1600 0    60   ~ 0
osc2_repeat
Text Label 1900 3700 2    60   ~ 0
osc3_repeat
Text Label 2800 3700 0    60   ~ 0
osc4_repeat
Text Label 5700 4850 0    60   ~ 0
freq_in_1
Text Label 5700 5550 0    60   ~ 0
freq_in_2
Text Label 5700 6200 0    60   ~ 0
freq_in_3
Text Label 5700 6850 0    60   ~ 0
freq_in_4
Text Label 5700 5050 0    60   ~ 0
freq_out_1
Text Label 5700 5750 0    60   ~ 0
freq_out_2
Text Label 5700 6400 0    60   ~ 0
freq_out_3
Text Label 5700 7050 0    60   ~ 0
freq_out_4
$Comp
L +5V #PWR0116
U 1 1 5C5CBE8C
P 1900 750
F 0 "#PWR0116" H 1900 600 50  0001 C CNN
F 1 "+5V" H 1900 890 50  0000 C CNN
F 2 "" H 1900 750 50  0001 C CNN
F 3 "" H 1900 750 50  0001 C CNN
	1    1900 750 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR0117
U 1 1 5C5CBFC0
P 2850 750
F 0 "#PWR0117" H 2850 600 50  0001 C CNN
F 1 "+5V" H 2850 890 50  0000 C CNN
F 2 "" H 2850 750 50  0001 C CNN
F 3 "" H 2850 750 50  0001 C CNN
	1    2850 750 
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR0118
U 1 1 5C5CC0B3
P 1900 2850
F 0 "#PWR0118" H 1900 2700 50  0001 C CNN
F 1 "+5V" H 1900 2990 50  0000 C CNN
F 2 "" H 1900 2850 50  0001 C CNN
F 3 "" H 1900 2850 50  0001 C CNN
	1    1900 2850
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR0119
U 1 1 5C5CC16C
P 2800 2850
F 0 "#PWR0119" H 2800 2700 50  0001 C CNN
F 1 "+5V" H 2800 2990 50  0000 C CNN
F 2 "" H 2800 2850 50  0001 C CNN
F 3 "" H 2800 2850 50  0001 C CNN
	1    2800 2850
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR0120
U 1 1 5C5CC347
P 1900 1900
F 0 "#PWR0120" H 1900 1650 50  0001 C CNN
F 1 "GND" H 1900 1750 50  0000 C CNN
F 2 "" H 1900 1900 50  0001 C CNN
F 3 "" H 1900 1900 50  0001 C CNN
	1    1900 1900
	0    1    1    0   
$EndComp
$Comp
L GND #PWR0121
U 1 1 5C5CC7AC
P 2850 1900
F 0 "#PWR0121" H 2850 1650 50  0001 C CNN
F 1 "GND" H 2850 1750 50  0000 C CNN
F 2 "" H 2850 1900 50  0001 C CNN
F 3 "" H 2850 1900 50  0001 C CNN
	1    2850 1900
	0    -1   1    0   
$EndComp
$Comp
L GND #PWR0122
U 1 1 5C5CC9CC
P 1900 4000
F 0 "#PWR0122" H 1900 3750 50  0001 C CNN
F 1 "GND" H 1900 3850 50  0000 C CNN
F 2 "" H 1900 4000 50  0001 C CNN
F 3 "" H 1900 4000 50  0001 C CNN
	1    1900 4000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR0123
U 1 1 5C5CCA12
P 2800 4000
F 0 "#PWR0123" H 2800 3750 50  0001 C CNN
F 1 "GND" H 2800 3850 50  0000 C CNN
F 2 "" H 2800 4000 50  0001 C CNN
F 3 "" H 2800 4000 50  0001 C CNN
	1    2800 4000
	0    -1   1    0   
$EndComp
Text Label 8000 1200 2    60   ~ 0
osc1_freq_wiper
Text Label 8000 1300 2    60   ~ 0
osc1_pwm_wiper
Text Label 8000 1400 2    60   ~ 0
osc1_speed
Text Label 8000 1800 2    60   ~ 0
envelope_pwm_bypass_in_1
Text Label 8000 1900 2    60   ~ 0
envelope_pwm_bypass_out_1
Text Label 8000 2000 2    60   ~ 0
osc1_repeat
Text Label 8000 2100 2    60   ~ 0
osc1_quant
Text Label 8000 1500 2    60   ~ 0
freq_in_1
Text Label 8000 1700 2    60   ~ 0
freq_out_1
Text HLabel 8300 1200 2    60   Output ~ 0
osc1_freq_wiper
Text HLabel 8300 1300 2    60   Output ~ 0
osc1_pwm_wiper
Text HLabel 8300 1400 2    60   Output ~ 0
osc1_speed
Text HLabel 8300 1500 2    60   Input ~ 0
freq_in_1
Text HLabel 8300 1700 2    60   Output ~ 0
freq_out_1
Text HLabel 8300 1800 2    60   Input ~ 0
envelope_pwm_bypass_in_1
Text HLabel 8300 1900 2    60   Output ~ 0
envelope_pwm_bypass_out_1
Text HLabel 8300 2000 2    60   Output ~ 0
osc1_repeat
Text HLabel 8300 2100 2    60   Output ~ 0
osc1_quant
Text Label 8000 2250 2    60   ~ 0
osc2_freq_wiper
Text Label 8000 2350 2    60   ~ 0
osc2_pwm_wiper
Text Label 8000 2450 2    60   ~ 0
osc2_speed
Text Label 8000 2850 2    60   ~ 0
envelope_pwm_bypass_in_2
Text Label 8000 2950 2    60   ~ 0
envelope_pwm_bypass_out_2
Text Label 8000 3050 2    60   ~ 0
osc2_repeat
Text Label 8000 3150 2    60   ~ 0
osc2_quant
Text Label 8000 2550 2    60   ~ 0
freq_in_2
Text Label 8000 2750 2    60   ~ 0
freq_out_2
Text HLabel 8300 2250 2    60   Output ~ 0
osc2_freq_wiper
Text HLabel 8300 2350 2    60   Output ~ 0
osc2_pwm_wiper
Text HLabel 8300 2450 2    60   Output ~ 0
osc2_speed
Text HLabel 8300 2550 2    60   Input ~ 0
freq_in_2
Text HLabel 8300 2750 2    60   Output ~ 0
freq_out_2
Text HLabel 8300 2850 2    60   Input ~ 0
envelope_pwm_bypass_in_2
Text HLabel 8300 2950 2    60   Output ~ 0
envelope_pwm_bypass_out_2
Text HLabel 8300 3050 2    60   Output ~ 0
osc2_repeat
Text HLabel 8300 3150 2    60   Output ~ 0
osc2_quant
Text Label 8000 3350 2    60   ~ 0
osc3_freq_wiper
Text Label 8000 3450 2    60   ~ 0
osc3_pwm_wiper
Text Label 8000 3550 2    60   ~ 0
osc3_speed
Text Label 8000 3950 2    60   ~ 0
envelope_pwm_bypass_in_3
Text Label 8000 4050 2    60   ~ 0
envelope_pwm_bypass_out_3
Text Label 8000 4150 2    60   ~ 0
osc3_repeat
Text Label 8000 4250 2    60   ~ 0
osc3_quant
Text Label 8000 3650 2    60   ~ 0
freq_in_3
Text Label 8000 3850 2    60   ~ 0
freq_out_3
Text HLabel 8300 3350 2    60   Output ~ 0
osc3_freq_wiper
Text HLabel 8300 3450 2    60   Output ~ 0
osc3_pwm_wiper
Text HLabel 8300 3550 2    60   Output ~ 0
osc3_speed
Text HLabel 8300 3650 2    60   Input ~ 0
freq_in_3
Text HLabel 8300 3850 2    60   Output ~ 0
freq_out_3
Text HLabel 8300 3950 2    60   Input ~ 0
envelope_pwm_bypass_in_3
Text HLabel 8300 4050 2    60   Output ~ 0
envelope_pwm_bypass_out_3
Text HLabel 8300 4150 2    60   Output ~ 0
osc3_repeat
Text HLabel 8300 4250 2    60   Output ~ 0
osc3_quant
Text HLabel 8300 4450 2    60   Output ~ 0
osc4_freq_wiper
Text HLabel 8300 4550 2    60   Output ~ 0
osc4_pwm_wiper
Text HLabel 8300 4650 2    60   Output ~ 0
osc4_speed
Text HLabel 8300 4750 2    60   Input ~ 0
freq_in_4
Text HLabel 8300 4950 2    60   Output ~ 0
freq_out_4
Text HLabel 8300 5050 2    60   Input ~ 0
envelope_pwm_bypass_in_4
Text HLabel 8300 5150 2    60   Output ~ 0
envelope_pwm_bypass_out_4
Text HLabel 8300 5250 2    60   Output ~ 0
osc4_repeat
Text HLabel 8300 5350 2    60   Output ~ 0
osc4_quant
Text Label 8000 4450 2    60   ~ 0
osc4_freq_wiper
Text Label 8000 4550 2    60   ~ 0
osc4_pwm_wiper
Text Label 8000 4650 2    60   ~ 0
osc4_speed
Text Label 8000 5050 2    60   ~ 0
envelope_pwm_bypass_in_4
Text Label 8000 5150 2    60   ~ 0
envelope_pwm_bypass_out_4
Text Label 8000 5250 2    60   ~ 0
osc4_repeat
Text Label 8000 5350 2    60   ~ 0
osc4_quant
Text Label 8000 4750 2    60   ~ 0
freq_in_4
Text Label 8000 4950 2    60   ~ 0
freq_out_4
Text Label 5700 4950 0    60   ~ 0
freq_fb_1
Text Label 5700 5650 0    60   ~ 0
freq_fb_2
Text Label 5700 6300 0    60   ~ 0
freq_fb_3
Text Label 5700 6950 0    60   ~ 0
freq_fb_4
Text Label 8000 1600 2    60   ~ 0
freq_fb_1
Text HLabel 8300 1600 2    60   Input ~ 0
freq_fb_1
Text Label 8000 2650 2    60   ~ 0
freq_fb_2
Text HLabel 8300 2650 2    60   Input ~ 0
freq_fb_2
Text Label 8000 3750 2    60   ~ 0
freq_fb_3
Text HLabel 8300 3750 2    60   Input ~ 0
freq_fb_3
Text Label 8000 4850 2    60   ~ 0
freq_fb_4
Text HLabel 8300 4850 2    60   Input ~ 0
freq_fb_4
$Comp
L +5V #PWR0124
U 1 1 5C63883F
P 1900 1000
F 0 "#PWR0124" H 1900 850 50  0001 C CNN
F 1 "+5V" H 1900 1140 50  0000 C CNN
F 2 "" H 1900 1000 50  0001 C CNN
F 3 "" H 1900 1000 50  0001 C CNN
	1    1900 1000
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR0125
U 1 1 5C63885A
P 1900 1200
F 0 "#PWR0125" H 1900 1050 50  0001 C CNN
F 1 "+5V" H 1900 1340 50  0000 C CNN
F 2 "" H 1900 1200 50  0001 C CNN
F 3 "" H 1900 1200 50  0001 C CNN
	1    1900 1200
	0    -1   -1   0   
$EndComp
Text Label 1900 1500 2    60   ~ 0
osc1_hold
$Comp
L GND #PWR0126
U 1 1 5C6388C2
P 1900 2000
F 0 "#PWR0126" H 1900 1750 50  0001 C CNN
F 1 "GND" H 1900 1850 50  0000 C CNN
F 2 "" H 1900 2000 50  0001 C CNN
F 3 "" H 1900 2000 50  0001 C CNN
	1    1900 2000
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR0127
U 1 1 5C638972
P 2850 1000
F 0 "#PWR0127" H 2850 850 50  0001 C CNN
F 1 "+5V" H 2850 1140 50  0000 C CNN
F 2 "" H 2850 1000 50  0001 C CNN
F 3 "" H 2850 1000 50  0001 C CNN
	1    2850 1000
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR0128
U 1 1 5C63898D
P 2850 1200
F 0 "#PWR0128" H 2850 1050 50  0001 C CNN
F 1 "+5V" H 2850 1340 50  0000 C CNN
F 2 "" H 2850 1200 50  0001 C CNN
F 3 "" H 2850 1200 50  0001 C CNN
	1    2850 1200
	0    1    -1   0   
$EndComp
Text Label 2850 1500 0    60   ~ 0
osc2_hold
$Comp
L GND #PWR0129
U 1 1 5C6389D7
P 2850 2000
F 0 "#PWR0129" H 2850 1750 50  0001 C CNN
F 1 "GND" H 2850 1850 50  0000 C CNN
F 2 "" H 2850 2000 50  0001 C CNN
F 3 "" H 2850 2000 50  0001 C CNN
	1    2850 2000
	0    -1   1    0   
$EndComp
$Comp
L +5V #PWR0130
U 1 1 5C638A27
P 1900 3100
F 0 "#PWR0130" H 1900 2950 50  0001 C CNN
F 1 "+5V" H 1900 3240 50  0000 C CNN
F 2 "" H 1900 3100 50  0001 C CNN
F 3 "" H 1900 3100 50  0001 C CNN
	1    1900 3100
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR0131
U 1 1 5C638A9A
P 1900 3300
F 0 "#PWR0131" H 1900 3150 50  0001 C CNN
F 1 "+5V" H 1900 3440 50  0000 C CNN
F 2 "" H 1900 3300 50  0001 C CNN
F 3 "" H 1900 3300 50  0001 C CNN
	1    1900 3300
	0    -1   -1   0   
$EndComp
Text Label 1900 3600 2    60   ~ 0
osc3_hold
$Comp
L GND #PWR0132
U 1 1 5C638ADC
P 1900 4100
F 0 "#PWR0132" H 1900 3850 50  0001 C CNN
F 1 "GND" H 1900 3950 50  0000 C CNN
F 2 "" H 1900 4100 50  0001 C CNN
F 3 "" H 1900 4100 50  0001 C CNN
	1    1900 4100
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR0133
U 1 1 5C638BD0
P 2800 3100
F 0 "#PWR0133" H 2800 2950 50  0001 C CNN
F 1 "+5V" H 2800 3240 50  0000 C CNN
F 2 "" H 2800 3100 50  0001 C CNN
F 3 "" H 2800 3100 50  0001 C CNN
	1    2800 3100
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR0134
U 1 1 5C638BE7
P 2800 3300
F 0 "#PWR0134" H 2800 3150 50  0001 C CNN
F 1 "+5V" H 2800 3440 50  0000 C CNN
F 2 "" H 2800 3300 50  0001 C CNN
F 3 "" H 2800 3300 50  0001 C CNN
	1    2800 3300
	0    1    -1   0   
$EndComp
Text Label 2800 3600 0    60   ~ 0
osc4_hold
$Comp
L GND #PWR0135
U 1 1 5C638C2E
P 2800 4100
F 0 "#PWR0135" H 2800 3850 50  0001 C CNN
F 1 "GND" H 2800 3950 50  0000 C CNN
F 2 "" H 2800 4100 50  0001 C CNN
F 3 "" H 2800 4100 50  0001 C CNN
	1    2800 4100
	0    -1   1    0   
$EndComp
$Comp
L Conn_01x05 J13
U 1 1 5C639754
P 5500 5050
F 0 "J13" H 5500 5350 50  0000 C CNN
F 1 "Conn_01x05" H 5500 4750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 5500 5050 50  0001 C CNN
F 3 "" H 5500 5050 50  0001 C CNN
	1    5500 5050
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x05 J14
U 1 1 5C6397E0
P 5500 5750
F 0 "J14" H 5500 6050 50  0000 C CNN
F 1 "Conn_01x05" H 5500 5450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 5500 5750 50  0001 C CNN
F 3 "" H 5500 5750 50  0001 C CNN
	1    5500 5750
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x05 J15
U 1 1 5C63986E
P 5500 6400
F 0 "J15" H 5500 6700 50  0000 C CNN
F 1 "Conn_01x05" H 5500 6100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 5500 6400 50  0001 C CNN
F 3 "" H 5500 6400 50  0001 C CNN
	1    5500 6400
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x05 J16
U 1 1 5C6398B4
P 5500 7050
F 0 "J16" H 5500 7350 50  0000 C CNN
F 1 "Conn_01x05" H 5500 6750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 5500 7050 50  0001 C CNN
F 3 "" H 5500 7050 50  0001 C CNN
	1    5500 7050
	-1   0    0    -1  
$EndComp
Text Label 5700 5150 0    60   ~ 0
lfo_in_1
Text Label 5700 5250 0    60   ~ 0
lfo_out_1
Text Label 5700 5850 0    60   ~ 0
lfo_in_2
Text Label 5700 5950 0    60   ~ 0
lfo_out_2
Text Label 5700 6500 0    60   ~ 0
lfo_in_3
Text Label 5700 6600 0    60   ~ 0
lfo_out_3
Text Label 5700 7150 0    60   ~ 0
lfo_in_4
Text Label 5700 7250 0    60   ~ 0
lfo_out_4
Text Label 8050 5650 2    60   ~ 0
lfo_in_1
Text Label 8050 5750 2    60   ~ 0
lfo_out_1
Text Label 8050 5850 2    60   ~ 0
lfo_in_2
Text Label 8050 5950 2    60   ~ 0
lfo_out_2
Text Label 8050 6050 2    60   ~ 0
lfo_in_3
Text Label 8050 6150 2    60   ~ 0
lfo_out_3
Text Label 8050 6250 2    60   ~ 0
lfo_in_4
Text Label 8050 6350 2    60   ~ 0
lfo_out_4
Text HLabel 8250 5650 2    60   Output ~ 0
lfo_in_1
Text HLabel 8250 5750 2    60   Input ~ 0
lfo_out_1
Text HLabel 8250 5850 2    60   Output ~ 0
lfo_in_2
Text HLabel 8250 5950 2    60   Input ~ 0
lfo_out_2
Text HLabel 8250 6050 2    60   Output ~ 0
lfo_in_3
Text HLabel 8250 6150 2    60   Input ~ 0
lfo_out_3
Text HLabel 8250 6250 2    60   Output ~ 0
lfo_in_4
Text HLabel 8250 6350 2    60   Input ~ 0
lfo_out_4
Text Label 1900 1400 2    60   ~ 0
osc1_quant
Text Label 2850 1400 0    60   ~ 0
osc2_quant
Text Label 1900 3500 2    60   ~ 0
osc3_quant
Text Label 2800 3500 0    60   ~ 0
osc4_quant
$Comp
L Conn_02x13_Odd_Even J9
U 1 1 5C747DA8
P 2350 1400
F 0 "J9" H 2400 2100 50  0000 C CNN
F 1 "Conn_02x13_Odd_Even" H 2400 700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x13_Pitch2.54mm" H 2350 1400 50  0001 C CNN
F 3 "" H 2350 1400 50  0001 C CNN
	1    2350 1400
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x13_Odd_Even J8
U 1 1 5C747E14
P 2300 3500
F 0 "J8" H 2350 4200 50  0000 C CNN
F 1 "Conn_02x13_Odd_Even" H 2350 2800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x13_Pitch2.54mm" H 2300 3500 50  0001 C CNN
F 3 "" H 2300 3500 50  0001 C CNN
	1    2300 3500
	1    0    0    -1  
$EndComp
Text HLabel 8300 750  2    60   Output ~ 0
osc1_hold
Text HLabel 8300 850  2    60   Output ~ 0
osc2_hold
Text HLabel 8300 950  2    60   Output ~ 0
osc3_hold
Text HLabel 8300 1050 2    60   Output ~ 0
osc4_hold
Text Label 8000 750  2    60   ~ 0
osc1_hold
Text Label 8000 850  2    60   ~ 0
osc2_hold
Text Label 8000 950  2    60   ~ 0
osc3_hold
Text Label 8000 1050 2    60   ~ 0
osc4_hold
Wire Wire Line
	1900 750  1900 800 
Wire Wire Line
	1900 800  2150 800 
Wire Wire Line
	2150 900  1900 900 
Wire Wire Line
	1900 1000 2150 1000
Wire Wire Line
	2150 1100 1900 1100
Wire Wire Line
	1900 1200 2150 1200
Wire Wire Line
	2150 1500 1900 1500
Wire Wire Line
	1900 1600 2150 1600
Wire Wire Line
	1900 1700 2150 1700
Wire Wire Line
	2150 1800 1900 1800
Wire Wire Line
	1900 1900 2150 1900
Wire Wire Line
	2150 2000 1900 2000
Wire Wire Line
	2650 800  2850 800 
Wire Wire Line
	2850 800  2850 750 
Wire Wire Line
	2850 900  2650 900 
Wire Wire Line
	2650 1000 2850 1000
Wire Wire Line
	2850 1100 2650 1100
Wire Wire Line
	2650 1200 2850 1200
Wire Wire Line
	2850 1500 2650 1500
Wire Wire Line
	2650 1600 2850 1600
Wire Wire Line
	2650 1700 2850 1700
Wire Wire Line
	2850 1800 2650 1800
Wire Wire Line
	2650 1900 2850 1900
Wire Wire Line
	2650 2000 2850 2000
Wire Wire Line
	2100 2900 1900 2900
Wire Wire Line
	1900 2900 1900 2850
Wire Wire Line
	1900 3000 2100 3000
Wire Wire Line
	1900 3100 2100 3100
Wire Wire Line
	2100 3200 1900 3200
Wire Wire Line
	1900 3300 2100 3300
Wire Wire Line
	2100 3600 1900 3600
Wire Wire Line
	1900 3700 2100 3700
Wire Wire Line
	2100 3800 1900 3800
Wire Wire Line
	1900 3900 2100 3900
Wire Wire Line
	2100 4000 1900 4000
Wire Wire Line
	2100 4100 1900 4100
Wire Wire Line
	2600 2900 2800 2900
Wire Wire Line
	2800 2900 2800 2850
Wire Wire Line
	2800 3000 2600 3000
Wire Wire Line
	2600 3100 2800 3100
Wire Wire Line
	2800 3200 2600 3200
Wire Wire Line
	2600 3300 2800 3300
Wire Wire Line
	2800 3600 2600 3600
Wire Wire Line
	2600 3700 2800 3700
Wire Wire Line
	2600 3800 2800 3800
Wire Wire Line
	2800 3900 2600 3900
Wire Wire Line
	2600 4000 2800 4000
Wire Wire Line
	2600 4100 2800 4100
Wire Wire Line
	8300 1200 8000 1200
Wire Wire Line
	8000 1300 8300 1300
Wire Wire Line
	8300 1400 8000 1400
Wire Wire Line
	8000 1500 8300 1500
Wire Wire Line
	8300 1700 8000 1700
Wire Wire Line
	8000 1800 8300 1800
Wire Wire Line
	8300 1900 8000 1900
Wire Wire Line
	8000 2000 8300 2000
Wire Wire Line
	8300 2100 8000 2100
Wire Wire Line
	8300 2250 8000 2250
Wire Wire Line
	8000 2350 8300 2350
Wire Wire Line
	8300 2450 8000 2450
Wire Wire Line
	8000 2550 8300 2550
Wire Wire Line
	8300 2750 8000 2750
Wire Wire Line
	8000 2850 8300 2850
Wire Wire Line
	8300 2950 8000 2950
Wire Wire Line
	8000 3050 8300 3050
Wire Wire Line
	8300 3150 8000 3150
Wire Wire Line
	8300 3350 8000 3350
Wire Wire Line
	8000 3450 8300 3450
Wire Wire Line
	8300 3550 8000 3550
Wire Wire Line
	8000 3650 8300 3650
Wire Wire Line
	8300 3850 8000 3850
Wire Wire Line
	8000 3950 8300 3950
Wire Wire Line
	8300 4050 8000 4050
Wire Wire Line
	8000 4150 8300 4150
Wire Wire Line
	8300 4250 8000 4250
Wire Wire Line
	8000 4450 8300 4450
Wire Wire Line
	8300 4550 8000 4550
Wire Wire Line
	8000 4650 8300 4650
Wire Wire Line
	8300 4750 8000 4750
Wire Wire Line
	8000 4950 8300 4950
Wire Wire Line
	8300 5050 8000 5050
Wire Wire Line
	8000 5150 8300 5150
Wire Wire Line
	8300 5250 8000 5250
Wire Wire Line
	8000 5350 8300 5350
Wire Wire Line
	1900 1300 2150 1300
Wire Wire Line
	2850 1300 2650 1300
Wire Wire Line
	1900 3400 2100 3400
Wire Wire Line
	2800 3400 2600 3400
Wire Wire Line
	8300 1600 8000 1600
Wire Wire Line
	8000 2650 8300 2650
Wire Wire Line
	8300 3750 8000 3750
Wire Wire Line
	8300 4850 8000 4850
Wire Wire Line
	8050 5650 8250 5650
Wire Wire Line
	8050 5750 8250 5750
Wire Wire Line
	8250 5850 8050 5850
Wire Wire Line
	8050 5950 8250 5950
Wire Wire Line
	8250 6050 8050 6050
Wire Wire Line
	8050 6150 8250 6150
Wire Wire Line
	8250 6250 8050 6250
Wire Wire Line
	8050 6350 8250 6350
Wire Wire Line
	2150 1400 1900 1400
Wire Wire Line
	2850 1400 2650 1400
Wire Wire Line
	2100 3500 1900 3500
Wire Wire Line
	2800 3500 2600 3500
Wire Wire Line
	8300 750  8000 750 
Wire Wire Line
	8000 850  8300 850 
Wire Wire Line
	8300 950  8000 950 
Wire Wire Line
	8000 1050 8300 1050
$EndSCHEMATC
