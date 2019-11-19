EESchema Schematic File Version 4
LIBS:synth-wavetable-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
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
L MCU_ST_STM32F4:STM32F429VETx U?
U 1 1 5DDC7DCC
P 3700 4000
F 0 "U?" H 3700 4050 50  0000 C CNN
F 1 "STM32F429VETx" H 3700 3950 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_14x14mm_P0.5mm" H 3000 1400 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00071990.pdf" H 3700 4000 50  0001 C CNN
	1    3700 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5DD6DEE5
P 3650 6950
F 0 "#PWR?" H 3650 6700 50  0001 C CNN
F 1 "GNDD" H 3654 6795 50  0000 C CNN
F 2 "" H 3650 6950 50  0001 C CNN
F 3 "" H 3650 6950 50  0001 C CNN
	1    3650 6950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD6DF42
P 3900 6800
F 0 "#PWR?" H 3900 6550 50  0001 C CNN
F 1 "GND" H 3905 6627 50  0000 C CNN
F 2 "" H 3900 6800 50  0001 C CNN
F 3 "" H 3900 6800 50  0001 C CNN
	1    3900 6800
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY?
U 1 1 5DD8E80C
P 2950 1150
F 0 "#SUPPLY?" H 2950 1150 50  0001 L BNN
F 1 "3.3V" H 2950 1324 50  0000 C CNN
F 2 "" H 2950 1150 50  0001 C CNN
F 3 "" H 2950 1150 50  0001 C CNN
	1    2950 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6800 3500 6850
Wire Wire Line
	3500 6850 3600 6850
Wire Wire Line
	3800 6850 3800 6800
Wire Wire Line
	3700 6800 3700 6850
Connection ~ 3700 6850
Wire Wire Line
	3700 6850 3800 6850
Wire Wire Line
	3600 6800 3600 6850
Connection ~ 3600 6850
Wire Wire Line
	3600 6850 3650 6850
Wire Wire Line
	3650 6850 3650 6950
Connection ~ 3650 6850
Wire Wire Line
	3650 6850 3700 6850
Wire Wire Line
	3500 1300 3500 1250
Wire Wire Line
	3500 1250 3600 1250
Wire Wire Line
	4000 1250 4000 1300
Wire Wire Line
	3900 1300 3900 1250
Connection ~ 3900 1250
Wire Wire Line
	3900 1250 4000 1250
Wire Wire Line
	3800 1300 3800 1250
Connection ~ 3800 1250
Wire Wire Line
	3800 1250 3900 1250
Wire Wire Line
	3700 1300 3700 1250
Connection ~ 3700 1250
Wire Wire Line
	3600 1300 3600 1250
Connection ~ 3600 1250
Wire Wire Line
	3600 1250 3700 1250
$Comp
L Device:C_Small C?
U 1 1 5DD8EF72
P 3500 1150
F 0 "C?" H 3450 1200 50  0000 L CNN
F 1 "0.1uF" H 3400 1400 50  0000 L CNN
F 2 "" H 3500 1150 50  0001 C CNN
F 3 "~" H 3500 1150 50  0001 C CNN
	1    3500 1150
	1    0    0    -1  
$EndComp
Connection ~ 3500 1250
$Comp
L Device:C_Small C?
U 1 1 5DD9006B
P 3600 1150
F 0 "C?" H 3550 1200 50  0000 L CNN
F 1 "0.1uF" H 3500 1350 50  0000 L CNN
F 2 "" H 3600 1150 50  0001 C CNN
F 3 "~" H 3600 1150 50  0001 C CNN
	1    3600 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DD90081
P 3700 1150
F 0 "C?" H 3650 1200 50  0000 L CNN
F 1 "0.1uF" H 3600 1400 50  0000 L CNN
F 2 "" H 3700 1150 50  0001 C CNN
F 3 "~" H 3700 1150 50  0001 C CNN
	1    3700 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DD9009D
P 3800 1150
F 0 "C?" H 3750 1200 50  0000 L CNN
F 1 "0.1uF" H 3700 1350 50  0000 L CNN
F 2 "" H 3800 1150 50  0001 C CNN
F 3 "~" H 3800 1150 50  0001 C CNN
	1    3800 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DD900B7
P 3900 1150
F 0 "C?" H 3850 1200 50  0000 L CNN
F 1 "0.1uF" H 3800 1400 50  0000 L CNN
F 2 "" H 3900 1150 50  0001 C CNN
F 3 "~" H 3900 1150 50  0001 C CNN
	1    3900 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DD900D3
P 4000 1150
F 0 "C?" H 3950 1200 50  0000 L CNN
F 1 "0.1uF" H 3900 1350 50  0000 L CNN
F 2 "" H 4000 1150 50  0001 C CNN
F 3 "~" H 4000 1150 50  0001 C CNN
	1    4000 1150
	1    0    0    -1  
$EndComp
Connection ~ 4000 1250
Wire Wire Line
	3700 1250 3800 1250
Wire Wire Line
	2950 1150 2950 1250
Wire Wire Line
	2950 1250 3150 1250
$Comp
L power:GNDD #PWR?
U 1 1 5DD9048C
P 4100 1000
F 0 "#PWR?" H 4100 750 50  0001 C CNN
F 1 "GNDD" V 4104 890 50  0000 R CNN
F 2 "" H 4100 1000 50  0001 C CNN
F 3 "" H 4100 1000 50  0001 C CNN
	1    4100 1000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 1000 4000 1000
Wire Wire Line
	3500 1000 3500 1050
Wire Wire Line
	3600 1050 3600 1000
Connection ~ 3600 1000
Wire Wire Line
	3600 1000 3500 1000
Wire Wire Line
	3700 1050 3700 1000
Connection ~ 3700 1000
Wire Wire Line
	3700 1000 3600 1000
Wire Wire Line
	3800 1050 3800 1000
Connection ~ 3800 1000
Wire Wire Line
	3800 1000 3700 1000
Wire Wire Line
	3900 1050 3900 1000
Connection ~ 3900 1000
Wire Wire Line
	3900 1000 3800 1000
Wire Wire Line
	4000 1050 4000 1000
Connection ~ 4000 1000
Wire Wire Line
	4000 1000 3900 1000
$Comp
L Device:C_Small C?
U 1 1 5DD929A5
P 3400 1150
F 0 "C?" H 3350 1200 50  0000 L CNN
F 1 "0.1uF" H 3300 1350 50  0000 L CNN
F 2 "" H 3400 1150 50  0001 C CNN
F 3 "~" H 3400 1150 50  0001 C CNN
	1    3400 1150
	1    0    0    -1  
$EndComp
Connection ~ 3400 1250
Wire Wire Line
	3400 1250 3500 1250
Wire Wire Line
	3400 1300 3400 1250
Wire Wire Line
	3500 1000 3400 1000
Wire Wire Line
	3400 1000 3400 1050
Connection ~ 3500 1000
$Comp
L Device:C_Small C?
U 1 1 5DD939E7
P 5000 1500
F 0 "C?" H 4850 1550 50  0000 L CNN
F 1 "0.1uF" H 4750 1450 50  0000 L CNN
F 2 "" H 5000 1500 50  0001 C CNN
F 3 "~" H 5000 1500 50  0001 C CNN
	1    5000 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DD93A1D
P 5150 1500
F 0 "C?" H 5242 1546 50  0000 L CNN
F 1 "1uF" H 5242 1455 50  0000 L CNN
F 2 "" H 5150 1500 50  0001 C CNN
F 3 "~" H 5150 1500 50  0001 C CNN
	1    5150 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1300 4100 1250
$Comp
L power:GND #PWR?
U 1 1 5DD94B9B
P 5150 1600
F 0 "#PWR?" H 5150 1350 50  0001 C CNN
F 1 "GND" H 5155 1427 50  0000 C CNN
F 2 "" H 5150 1600 50  0001 C CNN
F 3 "" H 5150 1600 50  0001 C CNN
	1    5150 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD971D0
P 5000 1600
F 0 "#PWR?" H 5000 1350 50  0001 C CNN
F 1 "GND" H 5005 1427 50  0000 C CNN
F 2 "" H 5000 1600 50  0001 C CNN
F 3 "" H 5000 1600 50  0001 C CNN
	1    5000 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DD9A45C
P 3150 1150
F 0 "C?" H 3150 1200 50  0000 L CNN
F 1 "10uF" H 3150 1100 50  0000 L CNN
F 2 "" H 3150 1150 50  0001 C CNN
F 3 "~" H 3150 1150 50  0001 C CNN
	1    3150 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1000 3150 1000
Wire Wire Line
	3150 1000 3150 1050
Connection ~ 3400 1000
Connection ~ 3150 1250
Wire Wire Line
	3150 1250 3400 1250
Wire Wire Line
	5150 1250 5150 1400
Wire Wire Line
	4100 1250 5000 1250
Wire Wire Line
	5000 1250 5000 1400
Connection ~ 5000 1250
Wire Wire Line
	5000 1250 5150 1250
$EndSCHEMATC
