EESchema Schematic File Version 4
LIBS:synth-wavetable-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_02x12_Odd_Even J8
U 1 1 5DDCF210
P 5550 3950
F 0 "J8" H 5600 4667 50  0000 C CNN
F 1 "Conn_02x12_Odd_Even" H 5600 4576 50  0000 C CNN
F 2 "SparkFun-Connectors:2X12" H 5550 3950 50  0001 C CNN
F 3 "~" H 5550 3950 50  0001 C CNN
	1    5550 3950
	1    0    0    -1  
$EndComp
Text Label 5350 3950 2    50   ~ 0
attack
Text Label 5350 4050 2    50   ~ 0
decay
Text Label 5850 3550 0    50   ~ 0
sustain
Text Label 8950 3850 2    50   ~ 0
release
Text Label 8950 3950 2    50   ~ 0
lfo_rate
Text Label 8950 4050 2    50   ~ 0
lfo_depth
Text Label 5350 3550 2    50   ~ 0
osc1_tune
Text Label 5350 3650 2    50   ~ 0
osc1_waveshape
Text Label 5350 3750 2    50   ~ 0
osc2_tune
Text Label 5350 3850 2    50   ~ 0
osc2_waveshape
$Comp
L power:+3.3V #PWR0121
U 1 1 5DDD170E
P 4950 3400
F 0 "#PWR0121" H 4950 3250 50  0001 C CNN
F 1 "+3.3V" H 4965 3573 50  0000 C CNN
F 2 "" H 4950 3400 50  0001 C CNN
F 3 "" H 4950 3400 50  0001 C CNN
	1    4950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3400 4950 3450
Wire Wire Line
	4950 3450 5350 3450
Wire Wire Line
	6250 3500 6250 3450
Wire Wire Line
	6250 3450 5850 3450
$Comp
L power:GND #PWR0123
U 1 1 5DDD1795
P 6300 4150
F 0 "#PWR0123" H 6300 3900 50  0001 C CNN
F 1 "GND" H 6305 3977 50  0000 C CNN
F 2 "" H 6300 4150 50  0001 C CNN
F 3 "" H 6300 4150 50  0001 C CNN
	1    6300 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 4150 5850 4150
$Comp
L power:+3.3V #PWR0124
U 1 1 5DDD17B1
P 4950 4150
F 0 "#PWR0124" H 4950 4000 50  0001 C CNN
F 1 "+3.3V" H 4965 4323 50  0000 C CNN
F 2 "" H 4950 4150 50  0001 C CNN
F 3 "" H 4950 4150 50  0001 C CNN
	1    4950 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4150 5350 4150
Text Label 8950 4150 2    50   ~ 0
global_lfo_rate
Text Label 8950 4250 2    50   ~ 0
global_lfo_depth
Text Label 8950 3550 2    50   ~ 0
attack
Text Label 8950 3650 2    50   ~ 0
decay
Text Label 8950 3150 2    50   ~ 0
osc1_tune
Text Label 8950 3250 2    50   ~ 0
osc1_waveshape
Text Label 8950 3350 2    50   ~ 0
osc2_tune
Text Label 8950 3450 2    50   ~ 0
osc2_waveshape
Text Label 8950 3750 2    50   ~ 0
sustain
Text HLabel 8950 3150 2    50   Output ~ 0
osc1_tune
Text HLabel 8950 3250 2    50   Output ~ 0
osc1_waveshape
Text HLabel 8950 3350 2    50   Output ~ 0
osc2_tune
Text HLabel 8950 3450 2    50   Output ~ 0
osc2_waveshape
Text HLabel 8950 3550 2    50   Output ~ 0
attack
Text HLabel 8950 3650 2    50   Output ~ 0
decay
Text HLabel 8950 3750 2    50   Output ~ 0
sustain
Text HLabel 8950 3850 2    50   Output ~ 0
release
Text HLabel 8950 3950 2    50   Output ~ 0
lfo_rate
Text HLabel 8950 4050 2    50   Output ~ 0
lfo_depth
Text HLabel 8950 4150 2    50   Output ~ 0
global_lfo_rate
Text HLabel 8950 4250 2    50   Output ~ 0
global_lfo_depth
$EndSCHEMATC
