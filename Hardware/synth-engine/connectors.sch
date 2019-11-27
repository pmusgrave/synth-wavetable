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
Wire Wire Line
	4950 3400 4950 3450
Wire Wire Line
	4950 3450 5350 3450
Wire Wire Line
	6250 3500 6250 3450
Wire Wire Line
	6250 3450 5850 3450
Text HLabel 5350 3550 0    50   Output ~ 0
osc1_tune
Text HLabel 5350 3650 0    50   Output ~ 0
osc1_waveshape
Text HLabel 5350 3750 0    50   Output ~ 0
osc2_tune
Text HLabel 5350 3850 0    50   Output ~ 0
osc2_waveshape
Text HLabel 5350 3950 0    50   Output ~ 0
attack
Text HLabel 5350 4050 0    50   Output ~ 0
decay
Text HLabel 5850 3550 2    50   Output ~ 0
sustain
Text HLabel 5850 3650 2    50   Output ~ 0
release
Text HLabel 5850 3750 2    50   Output ~ 0
lfo_rate
Text HLabel 5850 3850 2    50   Output ~ 0
lfo_depth
Text HLabel 5850 3950 2    50   Output ~ 0
global_lfo_rate
Text HLabel 5850 4050 2    50   Output ~ 0
global_lfo_depth
Text HLabel 5350 4150 0    50   BiDi ~ 0
filter_freq
Text HLabel 5850 4150 2    50   BiDi ~ 0
filter_resonance
$Comp
L power:GND #PWR0122
U 1 1 5DE076CA
P 6250 3500
F 0 "#PWR0122" H 6250 3250 50  0001 C CNN
F 1 "GND" H 6255 3327 50  0000 C CNN
F 2 "" H 6250 3500 50  0001 C CNN
F 3 "" H 6250 3500 50  0001 C CNN
	1    6250 3500
	1    0    0    -1  
$EndComp
Text HLabel 5350 4250 0    50   BiDi ~ 0
mod1
Text HLabel 5850 4250 2    50   BiDi ~ 0
mod2
Text HLabel 5350 4350 0    50   BiDi ~ 0
mod3
Text HLabel 5850 4350 2    50   BiDi ~ 0
mod4
Text HLabel 5350 4450 0    50   BiDi ~ 0
mod5
Text HLabel 5850 4450 2    50   BiDi ~ 0
mod6
Text HLabel 5350 4550 0    50   BiDi ~ 0
mod7
Text HLabel 5850 4550 2    50   BiDi ~ 0
mod8
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY0107
U 1 1 5DE1F03B
P 4950 3400
F 0 "#SUPPLY0107" H 4950 3400 50  0001 L BNN
F 1 "3.3V" H 4950 3574 50  0000 C CNN
F 2 "" H 4950 3400 50  0001 C CNN
F 3 "" H 4950 3400 50  0001 C CNN
	1    4950 3400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
