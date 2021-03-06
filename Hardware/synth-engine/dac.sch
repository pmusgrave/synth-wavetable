EESchema Schematic File Version 4
LIBS:synth-wavetable-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
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
L dac:AK4490 U9
U 1 1 5DD48AC0
P 4350 4050
F 0 "U9" V 4300 4000 60  0000 L CNN
F 1 "AK4490" V 4400 3900 60  0000 L CNN
F 2 "SparkFun-DigitalIC:LQFP-48" H 4400 3800 60  0001 C CNN
F 3 "" H 4400 3800 60  0000 C CNN
	1    4350 4050
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C62
U 1 1 5DD49A01
P 3900 2700
F 0 "C62" V 3671 2700 50  0000 C CNN
F 1 "0.1uF" V 3762 2700 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 3900 2700 50  0001 C CNN
F 3 "~" H 3900 2700 50  0001 C CNN
	1    3900 2700
	0    1    1    0   
$EndComp
$Comp
L Device:CP1_Small C61
U 1 1 5DD49A9E
P 3900 2350
F 0 "C61" V 4128 2350 50  0000 C CNN
F 1 "10uF" V 4037 2350 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 3900 2350 50  0001 C CNN
F 3 "~" H 3900 2350 50  0001 C CNN
	1    3900 2350
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C64
U 1 1 5DD49CA7
P 4200 2700
F 0 "C64" V 3971 2700 50  0000 C CNN
F 1 "0.1uF" V 4062 2700 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 4200 2700 50  0001 C CNN
F 3 "~" H 4200 2700 50  0001 C CNN
	1    4200 2700
	0    1    1    0   
$EndComp
$Comp
L Device:CP1_Small C63
U 1 1 5DD49CE2
P 4200 2350
F 0 "C63" V 3972 2350 50  0000 C CNN
F 1 "10uF" V 4063 2350 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 4200 2350 50  0001 C CNN
F 3 "~" H 4200 2350 50  0001 C CNN
	1    4200 2350
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C66
U 1 1 5DD49D6A
P 4550 2700
F 0 "C66" V 4321 2700 50  0000 C CNN
F 1 "0.1uF" V 4412 2700 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 4550 2700 50  0001 C CNN
F 3 "~" H 4550 2700 50  0001 C CNN
	1    4550 2700
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C70
U 1 1 5DD49D90
P 4850 2650
F 0 "C70" V 4621 2650 50  0000 C CNN
F 1 "0.1uF" V 4712 2650 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 4850 2650 50  0001 C CNN
F 3 "~" H 4850 2650 50  0001 C CNN
	1    4850 2650
	0    1    1    0   
$EndComp
$Comp
L Device:CP1_Small C65
U 1 1 5DD49EFF
P 4550 2350
F 0 "C65" V 4778 2350 50  0000 C CNN
F 1 "220uF" V 4687 2350 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 4550 2350 50  0001 C CNN
F 3 "~" H 4550 2350 50  0001 C CNN
	1    4550 2350
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP1_Small C69
U 1 1 5DD49F43
P 4850 2350
F 0 "C69" V 4622 2350 50  0000 C CNN
F 1 "10uF" V 4713 2350 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 4850 2350 50  0001 C CNN
F 3 "~" H 4850 2350 50  0001 C CNN
	1    4850 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 2850 3850 2800
Wire Wire Line
	3850 2800 3800 2800
Wire Wire Line
	3800 2800 3800 2700
Wire Wire Line
	3950 2850 3950 2800
Wire Wire Line
	3950 2800 4000 2800
Wire Wire Line
	4000 2800 4000 2700
Wire Wire Line
	3800 2700 3800 2350
Connection ~ 3800 2700
Wire Wire Line
	4000 2700 4000 2350
Connection ~ 4000 2700
Wire Wire Line
	3800 2050 3800 2350
Connection ~ 3800 2350
Wire Wire Line
	4150 2850 4150 2800
Wire Wire Line
	4150 2800 4100 2800
Wire Wire Line
	4100 2800 4100 2700
Wire Wire Line
	4250 2850 4250 2800
Wire Wire Line
	4250 2800 4300 2800
Wire Wire Line
	4300 2800 4300 2700
Wire Wire Line
	4300 2700 4300 2350
Connection ~ 4300 2700
Wire Wire Line
	4100 2700 4100 2350
Connection ~ 4100 2700
Wire Wire Line
	4450 2850 4450 2700
Wire Wire Line
	4450 2700 4450 2350
Connection ~ 4450 2700
Wire Wire Line
	4450 2850 4550 2850
Connection ~ 4450 2850
Wire Wire Line
	4650 2850 4750 2850
Wire Wire Line
	4650 2850 4650 2700
Connection ~ 4650 2850
Wire Wire Line
	4650 2700 4650 2350
Connection ~ 4650 2700
Connection ~ 4750 2850
Wire Wire Line
	4750 2650 4750 2350
Connection ~ 4750 2650
Wire Wire Line
	4750 2650 4750 2850
Wire Wire Line
	4850 2850 4850 2750
Wire Wire Line
	4850 2750 4950 2750
Wire Wire Line
	4950 2750 4950 2650
Wire Wire Line
	4950 2650 4950 2350
Connection ~ 4950 2650
$Comp
L power:GNDD #PWR0104
U 1 1 5DD4E451
P 3250 3500
F 0 "#PWR0104" H 3250 3250 50  0001 C CNN
F 1 "GNDD" V 3254 3390 50  0000 R CNN
F 2 "" H 3250 3500 50  0001 C CNN
F 3 "" H 3250 3500 50  0001 C CNN
	1    3250 3500
	0    1    1    0   
$EndComp
$Comp
L power:GNDD #PWR0105
U 1 1 5DD4E69A
P 3850 5300
F 0 "#PWR0105" H 3850 5050 50  0001 C CNN
F 1 "GNDD" H 3854 5145 50  0000 C CNN
F 2 "" H 3850 5300 50  0001 C CNN
F 3 "" H 3850 5300 50  0001 C CNN
	1    3850 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0108
U 1 1 5DD4E80D
P 4150 5300
F 0 "#PWR0108" H 4150 5050 50  0001 C CNN
F 1 "GNDD" H 4154 5145 50  0000 C CNN
F 2 "" H 4150 5300 50  0001 C CNN
F 3 "" H 4150 5300 50  0001 C CNN
	1    4150 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C67
U 1 1 5DD4F455
P 4550 5600
F 0 "C67" V 4321 5600 50  0000 C CNN
F 1 "0.1uF" V 4412 5600 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 4550 5600 50  0001 C CNN
F 3 "~" H 4550 5600 50  0001 C CNN
	1    4550 5600
	0    1    1    0   
$EndComp
$Comp
L Device:CP1_Small C68
U 1 1 5DD4F45B
P 4550 5950
F 0 "C68" V 4778 5950 50  0000 C CNN
F 1 "220uF" V 4687 5950 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 4550 5950 50  0001 C CNN
F 3 "~" H 4550 5950 50  0001 C CNN
	1    4550 5950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4550 5300 4450 5300
Wire Wire Line
	4650 5300 4750 5300
Wire Wire Line
	4450 5600 4450 5300
Connection ~ 4450 5300
Wire Wire Line
	4650 5600 4650 5300
Connection ~ 4650 5300
Wire Wire Line
	4450 5950 4450 5600
Connection ~ 4450 5600
Wire Wire Line
	4650 5950 4650 5600
Connection ~ 4650 5600
$Comp
L Device:C_Small C71
U 1 1 5DD5436B
P 4850 5600
F 0 "C71" V 4621 5600 50  0000 C CNN
F 1 "0.1uF" V 4712 5600 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 4850 5600 50  0001 C CNN
F 3 "~" H 4850 5600 50  0001 C CNN
	1    4850 5600
	0    1    1    0   
$EndComp
$Comp
L Device:CP1_Small C72
U 1 1 5DD5439B
P 4850 5950
F 0 "C72" V 4622 5950 50  0000 C CNN
F 1 "10uF" V 4713 5950 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 4850 5950 50  0001 C CNN
F 3 "~" H 4850 5950 50  0001 C CNN
	1    4850 5950
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 5950 4750 5600
Wire Wire Line
	4750 5600 4750 5300
Connection ~ 4750 5600
Connection ~ 4750 5300
Wire Wire Line
	4850 5300 4850 5400
Wire Wire Line
	4850 5400 4950 5400
Wire Wire Line
	4950 5400 4950 5600
Wire Wire Line
	4950 5600 4950 5950
Connection ~ 4950 5600
$Comp
L Device:C_Small C73
U 1 1 5DD56E79
P 5600 3850
F 0 "C73" H 5508 3804 50  0000 R CNN
F 1 "0.1uF" H 5508 3895 50  0000 R CNN
F 2 "SparkFun-Passives:0805" H 5600 3850 50  0001 C CNN
F 3 "~" H 5600 3850 50  0001 C CNN
	1    5600 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5500 3700 5500 3750
Wire Wire Line
	5500 3900 5500 3950
Wire Wire Line
	5500 4100 5500 4150
Wire Wire Line
	5500 4300 5500 4350
Wire Wire Line
	5600 3750 5500 3750
Connection ~ 5500 3750
Wire Wire Line
	5500 3750 5500 3800
Wire Wire Line
	5600 3950 5500 3950
Connection ~ 5500 3950
Wire Wire Line
	5500 3950 5500 4000
$Comp
L Device:C_Small C74
U 1 1 5DD5A002
P 5600 4250
F 0 "C74" H 5508 4204 50  0000 R CNN
F 1 "0.1uF" H 5508 4295 50  0000 R CNN
F 2 "SparkFun-Passives:0805" H 5600 4250 50  0001 C CNN
F 3 "~" H 5600 4250 50  0001 C CNN
	1    5600 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	5600 4150 5500 4150
Connection ~ 5500 4150
Wire Wire Line
	5500 4150 5500 4200
Wire Wire Line
	5600 4350 5500 4350
Connection ~ 5500 4350
Wire Wire Line
	5500 4350 5500 4400
$Comp
L Device:CP1_Small C75
U 1 1 5DD5B479
P 5950 3850
F 0 "C75" H 6041 3896 50  0000 L CNN
F 1 "10uF" H 6041 3805 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 5950 3850 50  0001 C CNN
F 3 "~" H 5950 3850 50  0001 C CNN
	1    5950 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3750 5950 3750
Connection ~ 5600 3750
Wire Wire Line
	5600 3950 5950 3950
Connection ~ 5600 3950
$Comp
L Device:CP1_Small C76
U 1 1 5DD5F7C4
P 5950 4250
F 0 "C76" H 5859 4204 50  0000 R CNN
F 1 "10uF" H 5859 4295 50  0000 R CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 5950 4250 50  0001 C CNN
F 3 "~" H 5950 4250 50  0001 C CNN
	1    5950 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 4150 5600 4150
Connection ~ 5600 4150
Wire Wire Line
	5600 4350 5950 4350
Connection ~ 5600 4350
$Comp
L power:+3.3VA #PWR0109
U 1 1 5DD63162
P 4300 2050
F 0 "#PWR0109" H 4300 1900 50  0001 C CNN
F 1 "+3.3VA" H 4315 2223 50  0000 C CNN
F 2 "" H 4300 2050 50  0001 C CNN
F 3 "" H 4300 2050 50  0001 C CNN
	1    4300 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2050 4300 2350
Connection ~ 4300 2350
$Comp
L power:+5V #PWR0111
U 1 1 5DD657D8
P 4450 1800
F 0 "#PWR0111" H 4450 1650 50  0001 C CNN
F 1 "+5V" H 4465 1973 50  0000 C CNN
F 2 "" H 4450 1800 50  0001 C CNN
F 3 "" H 4450 1800 50  0001 C CNN
	1    4450 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1800 4450 2350
Connection ~ 4450 2350
$Comp
L power:+5V #PWR0114
U 1 1 5DD66485
P 5950 3700
F 0 "#PWR0114" H 5950 3550 50  0001 C CNN
F 1 "+5V" H 6050 3750 50  0000 C CNN
F 2 "" H 5950 3700 50  0001 C CNN
F 3 "" H 5950 3700 50  0001 C CNN
	1    5950 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3700 5950 3750
Connection ~ 5950 3750
$Comp
L power:+5V #PWR0115
U 1 1 5DD67828
P 5950 4400
F 0 "#PWR0115" H 5950 4250 50  0001 C CNN
F 1 "+5V" H 5850 4450 50  0000 C CNN
F 2 "" H 5950 4400 50  0001 C CNN
F 3 "" H 5950 4400 50  0001 C CNN
	1    5950 4400
	-1   0    0    1   
$EndComp
Connection ~ 5950 4350
Wire Wire Line
	5950 4350 5950 4400
$Comp
L power:+5V #PWR0110
U 1 1 5DD69850
P 4400 5950
F 0 "#PWR0110" H 4400 5800 50  0001 C CNN
F 1 "+5V" V 4415 6078 50  0000 L CNN
F 2 "" H 4400 5950 50  0001 C CNN
F 3 "" H 4400 5950 50  0001 C CNN
	1    4400 5950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 5950 4450 5950
Connection ~ 4450 5950
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY020
U 1 1 5DD4A95E
P 3800 2050
F 0 "#SUPPLY020" H 3800 2050 50  0001 L BNN
F 1 "3.3V" H 3800 2224 50  0000 C CNN
F 2 "" H 3800 2050 50  0001 C CNN
F 3 "" H 3800 2050 50  0001 C CNN
	1    3800 2050
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY021
U 1 1 5DD6B81F
P 3950 5300
F 0 "#SUPPLY021" H 3950 5300 50  0001 L BNN
F 1 "3.3V" H 4000 5550 50  0000 C CNN
F 2 "" H 3950 5300 50  0001 C CNN
F 3 "" H 3950 5300 50  0001 C CNN
	1    3950 5300
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY022
U 1 1 5DD6C780
P 4050 5300
F 0 "#SUPPLY022" H 4050 5300 50  0001 L BNN
F 1 "3.3V" H 4000 5550 50  0000 C CNN
F 2 "" H 4050 5300 50  0001 C CNN
F 3 "" H 4050 5300 50  0001 C CNN
	1    4050 5300
	-1   0    0    1   
$EndComp
Text HLabel 4050 2850 1    50   BiDi ~ 0
MCLK
Text HLabel 3250 3600 0    50   BiDi ~ 0
PDN
Text HLabel 3250 3700 0    50   BiDi ~ 0
I2S_BCLK
Text HLabel 3250 3800 0    50   BiDi ~ 0
I2S_SDA
Text HLabel 3250 3900 0    50   BiDi ~ 0
I2S_LRCLK
Text HLabel 3250 4000 0    50   BiDi ~ 0
I2S_WCLK
Text HLabel 3250 4100 0    50   BiDi ~ 0
CSN
Text HLabel 2050 4200 0    50   BiDi ~ 0
I2C_SCL
Text HLabel 2050 4300 0    50   BiDi ~ 0
I2C_SDA
Text HLabel 3250 4400 0    50   BiDi ~ 0
DIF0
Text HLabel 3250 4500 0    50   BiDi ~ 0
DIF1
Text HLabel 3250 4600 0    50   BiDi ~ 0
DIF2
Text HLabel 4250 5600 3    50   BiDi ~ 0
CAD1
Wire Wire Line
	4250 5600 4250 5300
$Comp
L Device:R R60
U 1 1 5DD990DD
P 2400 3850
F 0 "R60" H 2250 3900 50  0000 L CNN
F 1 "2.2k" V 2400 3750 50  0000 L CNN
F 2 "SparkFun-Passives:0805" V 2330 3850 50  0001 C CNN
F 3 "~" H 2400 3850 50  0001 C CNN
	1    2400 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R61
U 1 1 5DD99194
P 2500 3850
F 0 "R61" H 2570 3896 50  0000 L CNN
F 1 "2.2k" V 2500 3750 50  0000 L CNN
F 2 "SparkFun-Passives:0805" V 2430 3850 50  0001 C CNN
F 3 "~" H 2500 3850 50  0001 C CNN
	1    2500 3850
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY019
U 1 1 5DD9B51B
P 2500 3700
F 0 "#SUPPLY019" H 2500 3700 50  0001 L BNN
F 1 "3.3V" H 2550 3850 50  0000 C CNN
F 2 "" H 2500 3700 50  0001 C CNN
F 3 "" H 2500 3700 50  0001 C CNN
	1    2500 3700
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY018
U 1 1 5DD9B54C
P 2400 3700
F 0 "#SUPPLY018" H 2400 3700 50  0001 L BNN
F 1 "3.3V" H 2350 3850 50  0000 C CNN
F 2 "" H 2400 3700 50  0001 C CNN
F 3 "" H 2400 3700 50  0001 C CNN
	1    2400 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 4200 2400 4200
Wire Wire Line
	2050 4300 2500 4300
Wire Wire Line
	2400 4000 2400 4200
Connection ~ 2400 4200
Wire Wire Line
	2400 4200 3250 4200
Wire Wire Line
	2500 4000 2500 4300
Connection ~ 2500 4300
Wire Wire Line
	2500 4300 3250 4300
$Comp
L Amplifier_Operational:NJM4580 U10
U 1 1 5DDAA060
P 8150 2950
F 0 "U10" H 8150 3317 50  0000 C CNN
F 1 "NJM4580" H 8150 3226 50  0000 C CNN
F 2 "SparkFun-DigitalIC:SO08" H 8150 2950 50  0001 C CNN
F 3 "http://www.njr.com/semicon/PDF/NJM4580_E.pdf" H 8150 2950 50  0001 C CNN
	1    8150 2950
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:NJM4580 U10
U 3 1 5DDAA1AA
P 7450 1500
F 0 "U10" H 7408 1546 50  0000 L CNN
F 1 "NJM4580" H 7408 1455 50  0000 L CNN
F 2 "SparkFun-DigitalIC:SO08" H 7450 1500 50  0001 C CNN
F 3 "http://www.njr.com/semicon/PDF/NJM4580_E.pdf" H 7450 1500 50  0001 C CNN
	3    7450 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5DDAA4E2
P 7350 1800
F 0 "#PWR0118" H 7350 1550 50  0001 C CNN
F 1 "GND" H 7355 1627 50  0000 C CNN
F 2 "" H 7350 1800 50  0001 C CNN
F 3 "" H 7350 1800 50  0001 C CNN
	1    7350 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+15V #PWR0117
U 1 1 5DDAC34C
P 7350 1200
F 0 "#PWR0117" H 7350 1050 50  0001 C CNN
F 1 "+15V" H 7365 1373 50  0000 C CNN
F 2 "" H 7350 1200 50  0001 C CNN
F 3 "" H 7350 1200 50  0001 C CNN
	1    7350 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5DDAE836
P 4100 2050
F 0 "#PWR0107" H 4100 1800 50  0001 C CNN
F 1 "GND" H 4100 1900 50  0000 C CNN
F 2 "" H 4100 2050 50  0001 C CNN
F 3 "" H 4100 2050 50  0001 C CNN
	1    4100 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4100 2050 4100 2350
Connection ~ 4100 2350
$Comp
L power:GNDD #PWR0106
U 1 1 5DDB6C04
P 4000 2150
F 0 "#PWR0106" H 4000 1900 50  0001 C CNN
F 1 "GNDD" H 4000 2050 50  0000 C CNN
F 2 "" H 4000 2150 50  0001 C CNN
F 3 "" H 4000 2150 50  0001 C CNN
	1    4000 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 2150 4000 2350
Connection ~ 4000 2350
$Comp
L power:GND #PWR0113
U 1 1 5DDBB125
P 4750 2100
F 0 "#PWR0113" H 4750 1850 50  0001 C CNN
F 1 "GND" H 4750 1950 50  0000 C CNN
F 2 "" H 4750 2100 50  0001 C CNN
F 3 "" H 4750 2100 50  0001 C CNN
	1    4750 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4750 2100 4750 2350
Connection ~ 4750 2350
$Comp
L power:GND #PWR0116
U 1 1 5DDBD675
P 6050 4050
F 0 "#PWR0116" H 6050 3800 50  0001 C CNN
F 1 "GND" H 6050 3900 50  0000 C CNN
F 2 "" H 6050 4050 50  0001 C CNN
F 3 "" H 6050 4050 50  0001 C CNN
	1    6050 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6050 4050 5950 4050
Wire Wire Line
	5950 4050 5950 3950
Connection ~ 5950 3950
Wire Wire Line
	5950 4050 5950 4150
Connection ~ 5950 4050
Connection ~ 5950 4150
$Comp
L power:GND #PWR0112
U 1 1 5DDC47DB
P 4700 6100
F 0 "#PWR0112" H 4700 5850 50  0001 C CNN
F 1 "GND" H 4700 5950 50  0000 C CNN
F 2 "" H 4700 6100 50  0001 C CNN
F 3 "" H 4700 6100 50  0001 C CNN
	1    4700 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 6100 4700 5950
Wire Wire Line
	4700 5950 4750 5950
Connection ~ 4750 5950
Wire Wire Line
	4700 5950 4650 5950
Connection ~ 4700 5950
Connection ~ 4650 5950
Text GLabel 6700 2400 0    50   Input ~ 0
VREF
$Comp
L Device:R R62
U 1 1 5DDCF2E5
P 6650 2850
F 0 "R62" V 6443 2850 50  0000 C CNN
F 1 "1.5k" V 6534 2850 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 6580 2850 50  0001 C CNN
F 3 "~" H 6650 2850 50  0001 C CNN
	1    6650 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R R66
U 1 1 5DDCF35B
P 6950 2600
F 0 "R66" H 6880 2554 50  0000 R CNN
F 1 "1.5k" H 6880 2645 50  0000 R CNN
F 2 "SparkFun-Passives:0805" V 6880 2600 50  0001 C CNN
F 3 "~" H 6950 2600 50  0001 C CNN
	1    6950 2600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R68
U 1 1 5DDCF3CE
P 7300 2850
F 0 "R68" V 7507 2850 50  0000 C CNN
F 1 "390R" V 7416 2850 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 7230 2850 50  0001 C CNN
F 3 "~" H 7300 2850 50  0001 C CNN
	1    7300 2850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C79
U 1 1 5DDCF483
P 7600 2600
F 0 "C79" H 7692 2646 50  0000 L CNN
F 1 "1.0nF" H 7692 2555 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 7600 2600 50  0001 C CNN
F 3 "~" H 7600 2600 50  0001 C CNN
	1    7600 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C77
U 1 1 5DDCF4E1
P 7050 3050
F 0 "C77" H 7142 3096 50  0000 L CNN
F 1 "2.2nF" H 7142 3005 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 7050 3050 50  0001 C CNN
F 3 "~" H 7050 3050 50  0001 C CNN
	1    7050 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R63
U 1 1 5DDCF553
P 6650 3600
F 0 "R63" V 6857 3600 50  0000 C CNN
F 1 "1.5k" V 6766 3600 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 6580 3600 50  0001 C CNN
F 3 "~" H 6650 3600 50  0001 C CNN
	1    6650 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R70
U 1 1 5DDCF5A7
P 7500 3250
F 0 "R70" V 7293 3250 50  0000 C CNN
F 1 "390R" V 7384 3250 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 7430 3250 50  0001 C CNN
F 3 "~" H 7500 3250 50  0001 C CNN
	1    7500 3250
	0    1    -1   0   
$EndComp
$Comp
L Device:C_Small C81
U 1 1 5DDCF609
P 7950 3250
F 0 "C81" V 7721 3250 50  0000 C CNN
F 1 "1.0nF" V 7812 3250 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 7950 3250 50  0001 C CNN
F 3 "~" H 7950 3250 50  0001 C CNN
	1    7950 3250
	0    1    -1   0   
$EndComp
$Comp
L Device:R R72
U 1 1 5DDD16DB
P 7700 3600
F 0 "R72" V 7493 3600 50  0000 C CNN
F 1 "1.5k" V 7584 3600 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 7630 3600 50  0001 C CNN
F 3 "~" H 7700 3600 50  0001 C CNN
	1    7700 3600
	0    1    -1   0   
$EndComp
Wire Wire Line
	6800 2850 6950 2850
Wire Wire Line
	6950 2750 6950 2850
Connection ~ 6950 2850
Wire Wire Line
	6950 2850 7050 2850
Wire Wire Line
	7050 2950 7050 2850
Connection ~ 7050 2850
Wire Wire Line
	7050 2850 7150 2850
Wire Wire Line
	7050 3150 7050 3250
Wire Wire Line
	7050 3250 7350 3250
Wire Wire Line
	7450 2850 7600 2850
Wire Wire Line
	7600 2700 7600 2850
Connection ~ 7600 2850
Wire Wire Line
	7600 2850 7850 2850
Wire Wire Line
	7650 3250 7750 3250
Wire Wire Line
	7850 3050 7750 3050
Wire Wire Line
	7750 3050 7750 3250
Connection ~ 7750 3250
Wire Wire Line
	7750 3250 7850 3250
Wire Wire Line
	8450 2950 8500 2950
Wire Wire Line
	7850 3600 8500 3600
Wire Wire Line
	7550 3600 6800 3600
Wire Wire Line
	6700 2400 6950 2400
Wire Wire Line
	7600 2400 7600 2500
Wire Wire Line
	6950 2450 6950 2400
Connection ~ 6950 2400
Wire Wire Line
	6950 2400 7600 2400
Wire Wire Line
	5500 3500 6450 3500
Wire Wire Line
	5500 3600 6500 3600
$Comp
L Amplifier_Operational:NJM4580 U10
U 2 1 5DE1F686
P 8150 5150
F 0 "U10" H 8150 5517 50  0000 C CNN
F 1 "NJM4580" H 8150 5426 50  0000 C CNN
F 2 "SparkFun-DigitalIC:SO08" H 8150 5150 50  0001 C CNN
F 3 "http://www.njr.com/semicon/PDF/NJM4580_E.pdf" H 8150 5150 50  0001 C CNN
	2    8150 5150
	1    0    0    1   
$EndComp
Text GLabel 6700 5700 0    50   Input ~ 0
VREF
$Comp
L Device:R R65
U 1 1 5DE1F68D
P 6650 5250
F 0 "R65" V 6443 5250 50  0000 C CNN
F 1 "1.5k" V 6534 5250 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 6580 5250 50  0001 C CNN
F 3 "~" H 6650 5250 50  0001 C CNN
	1    6650 5250
	0    1    -1   0   
$EndComp
$Comp
L Device:R R67
U 1 1 5DE1F693
P 6950 5500
F 0 "R67" H 6880 5454 50  0000 R CNN
F 1 "1.5k" H 6880 5545 50  0000 R CNN
F 2 "SparkFun-Passives:0805" V 6880 5500 50  0001 C CNN
F 3 "~" H 6950 5500 50  0001 C CNN
	1    6950 5500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R69
U 1 1 5DE1F699
P 7300 5250
F 0 "R69" V 7507 5250 50  0000 C CNN
F 1 "390R" V 7416 5250 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 7230 5250 50  0001 C CNN
F 3 "~" H 7300 5250 50  0001 C CNN
	1    7300 5250
	0    -1   1    0   
$EndComp
$Comp
L Device:C_Small C80
U 1 1 5DE1F69F
P 7600 5500
F 0 "C80" H 7692 5546 50  0000 L CNN
F 1 "1.0nF" H 7692 5455 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 7600 5500 50  0001 C CNN
F 3 "~" H 7600 5500 50  0001 C CNN
	1    7600 5500
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C78
U 1 1 5DE1F6A5
P 7050 5050
F 0 "C78" H 7142 5096 50  0000 L CNN
F 1 "2.2nF" H 7142 5005 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 7050 5050 50  0001 C CNN
F 3 "~" H 7050 5050 50  0001 C CNN
	1    7050 5050
	1    0    0    1   
$EndComp
$Comp
L Device:R R64
U 1 1 5DE1F6AB
P 6650 4500
F 0 "R64" V 6857 4500 50  0000 C CNN
F 1 "1.5k" V 6766 4500 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 6580 4500 50  0001 C CNN
F 3 "~" H 6650 4500 50  0001 C CNN
	1    6650 4500
	0    1    -1   0   
$EndComp
$Comp
L Device:R R71
U 1 1 5DE1F6B1
P 7500 4850
F 0 "R71" V 7293 4850 50  0000 C CNN
F 1 "390R" V 7384 4850 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 7430 4850 50  0001 C CNN
F 3 "~" H 7500 4850 50  0001 C CNN
	1    7500 4850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C82
U 1 1 5DE1F6B7
P 7950 4850
F 0 "C82" V 7721 4850 50  0000 C CNN
F 1 "1.0nF" V 7812 4850 50  0000 C CNN
F 2 "SparkFun-Passives:0805" H 7950 4850 50  0001 C CNN
F 3 "~" H 7950 4850 50  0001 C CNN
	1    7950 4850
	0    1    1    0   
$EndComp
$Comp
L Device:R R73
U 1 1 5DE1F6BD
P 7700 4500
F 0 "R73" V 7493 4500 50  0000 C CNN
F 1 "1.5k" V 7584 4500 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 7630 4500 50  0001 C CNN
F 3 "~" H 7700 4500 50  0001 C CNN
	1    7700 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 5250 6950 5250
Wire Wire Line
	6950 5350 6950 5250
Connection ~ 6950 5250
Wire Wire Line
	6950 5250 7050 5250
Wire Wire Line
	7050 5150 7050 5250
Connection ~ 7050 5250
Wire Wire Line
	7050 5250 7150 5250
Wire Wire Line
	7050 4950 7050 4850
Wire Wire Line
	7050 4850 7350 4850
Wire Wire Line
	7450 5250 7600 5250
Wire Wire Line
	7600 5400 7600 5250
Connection ~ 7600 5250
Wire Wire Line
	7600 5250 7850 5250
Wire Wire Line
	7650 4850 7750 4850
Wire Wire Line
	7850 5050 7750 5050
Wire Wire Line
	7750 5050 7750 4850
Connection ~ 7750 4850
Wire Wire Line
	7750 4850 7850 4850
Wire Wire Line
	8450 5150 8500 5150
Wire Wire Line
	8500 5150 8500 4850
Wire Wire Line
	8500 4850 8050 4850
Wire Wire Line
	7850 4500 8500 4500
Wire Wire Line
	8500 4500 8500 4850
Connection ~ 8500 4850
Wire Wire Line
	7550 4500 6800 4500
Wire Wire Line
	6700 5700 6950 5700
Wire Wire Line
	7600 5700 7600 5600
Wire Wire Line
	6950 5650 6950 5700
Connection ~ 6950 5700
Wire Wire Line
	6950 5700 7600 5700
Wire Wire Line
	5500 4500 6500 4500
Wire Wire Line
	5500 4600 6450 4600
Wire Wire Line
	6450 4600 6450 5250
Wire Wire Line
	6450 5250 6500 5250
Wire Wire Line
	6500 2850 6450 2850
Wire Wire Line
	6450 2850 6450 3500
$Comp
L Device:CP1_Small C83
U 1 1 5DE53407
P 8950 3600
F 0 "C83" V 9178 3600 50  0000 C CNN
F 1 "CP1_Small" V 9087 3600 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 8950 3600 50  0001 C CNN
F 3 "~" H 8950 3600 50  0001 C CNN
	1    8950 3600
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP1_Small C84
U 1 1 5DE5355D
P 8950 5150
F 0 "C84" V 9178 5150 50  0000 C CNN
F 1 "CP1_Small" V 9087 5150 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 8950 5150 50  0001 C CNN
F 3 "~" H 8950 5150 50  0001 C CNN
	1    8950 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8850 3600 8500 3600
Connection ~ 8500 3600
Wire Wire Line
	8850 5150 8500 5150
Connection ~ 8500 5150
$Comp
L Device:R R74
U 1 1 5DE5F4ED
P 9250 3850
F 0 "R74" H 9320 3896 50  0000 L CNN
F 1 "100k" H 9320 3805 50  0000 L CNN
F 2 "SparkFun-Passives:0805" V 9180 3850 50  0001 C CNN
F 3 "~" H 9250 3850 50  0001 C CNN
	1    9250 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R75
U 1 1 5DE5F5ED
P 9250 5400
F 0 "R75" H 9320 5446 50  0000 L CNN
F 1 "100k" H 9320 5355 50  0000 L CNN
F 2 "SparkFun-Passives:0805" V 9180 5400 50  0001 C CNN
F 3 "~" H 9250 5400 50  0001 C CNN
	1    9250 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 5150 9250 5150
Wire Wire Line
	9250 5150 9250 5250
Wire Wire Line
	9050 3600 9250 3600
Wire Wire Line
	9250 3600 9250 3700
$Comp
L power:GND #PWR0120
U 1 1 5DE67BD1
P 9250 5550
F 0 "#PWR0120" H 9250 5300 50  0001 C CNN
F 1 "GND" H 9250 5400 50  0000 C CNN
F 2 "" H 9250 5550 50  0001 C CNN
F 3 "" H 9250 5550 50  0001 C CNN
	1    9250 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5DE67C34
P 9250 4000
F 0 "#PWR0119" H 9250 3750 50  0001 C CNN
F 1 "GND" H 9250 3850 50  0000 C CNN
F 2 "" H 9250 4000 50  0001 C CNN
F 3 "" H 9250 4000 50  0001 C CNN
	1    9250 4000
	1    0    0    -1  
$EndComp
Text HLabel 9800 3600 2    50   Output ~ 0
AOUT_L
Text HLabel 9800 5150 2    50   Output ~ 0
AOUT_R
Wire Wire Line
	9800 3600 9250 3600
Connection ~ 9250 3600
Wire Wire Line
	9800 5150 9250 5150
Connection ~ 9250 5150
Text Notes 9650 4200 0    50   ~ 0
I think I  could DC couple this\nand remove coupling caps\nbecause filters will be biased\nto the same VREF (?)
Wire Wire Line
	8500 3600 8500 3250
Wire Wire Line
	8500 2950 8500 3250
Connection ~ 8500 3250
Wire Wire Line
	8500 3250 8050 3250
$EndSCHEMATC
