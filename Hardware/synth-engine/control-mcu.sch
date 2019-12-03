EESchema Schematic File Version 4
LIBS:synth-wavetable-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
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
L dac:CY8C4246AZI-L445 U1
U 1 1 5DDBF5D6
P 2850 3050
F 0 "U1" H 2850 5337 60  0000 C CNN
F 1 "CY8C4246AZI-L445" H 2850 5231 60  0000 C CNN
F 2 "SparkFun-DigitalIC:TQFP64" H 2900 3000 60  0001 C CNN
F 3 "" H 2900 3000 60  0000 C CNN
	1    2850 3050
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5DDBF5DD
P 1400 1400
F 0 "R2" H 1470 1446 50  0000 L CNN
F 1 "10k" H 1470 1355 50  0000 L CNN
F 2 "SparkFun-Passives:0805" V 1330 1400 50  0001 C CNN
F 3 "~" H 1400 1400 50  0001 C CNN
	1    1400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1550 1400 1600
Wire Wire Line
	1400 1600 1600 1600
Text Label 1050 1600 0    50   ~ 0
XRES
Wire Wire Line
	1050 1700 1600 1700
Wire Wire Line
	1050 1600 1400 1600
Connection ~ 1400 1600
Text Label 1050 1700 0    50   ~ 0
SCLK
Text Label 1050 1800 0    50   ~ 0
SDAT
Wire Wire Line
	1050 1800 1600 1800
$Comp
L power:GNDD #PWR07
U 1 1 5DDBF601
P 950 3050
F 0 "#PWR07" H 950 2800 50  0001 C CNN
F 1 "GNDD" H 954 2895 50  0000 C CNN
F 2 "" H 950 3050 50  0001 C CNN
F 3 "" H 950 3050 50  0001 C CNN
	1    950  3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5DDBF607
P 1250 2900
F 0 "C8" H 1342 2946 50  0000 L CNN
F 1 "0.1uF" H 1342 2855 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 1250 2900 50  0001 C CNN
F 3 "~" H 1250 2900 50  0001 C CNN
	1    1250 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5DDBF60E
P 950 2900
F 0 "C4" H 1042 2946 50  0000 L CNN
F 1 "1uF" H 1042 2855 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 950 2900 50  0001 C CNN
F 3 "~" H 950 2900 50  0001 C CNN
	1    950  2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2800 1250 2800
Wire Wire Line
	950  3000 1250 3000
Wire Wire Line
	950  2750 950  2800
Connection ~ 950  2800
Wire Wire Line
	950  3050 950  3000
Connection ~ 950  3000
$Comp
L power:GNDD #PWR02
U 1 1 5DDBF621
P 650 3500
F 0 "#PWR02" H 650 3250 50  0001 C CNN
F 1 "GNDD" H 654 3345 50  0000 C CNN
F 2 "" H 650 3500 50  0001 C CNN
F 3 "" H 650 3500 50  0001 C CNN
	1    650  3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5DDBF627
P 950 3350
F 0 "C5" H 1042 3396 50  0000 L CNN
F 1 "0.1uF" H 1042 3305 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 950 3350 50  0001 C CNN
F 3 "~" H 950 3350 50  0001 C CNN
	1    950  3350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5DDBF62E
P 650 3350
F 0 "C1" H 742 3396 50  0000 L CNN
F 1 "1uF" H 742 3305 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 650 3350 50  0001 C CNN
F 3 "~" H 650 3350 50  0001 C CNN
	1    650  3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	650  3250 950  3250
Wire Wire Line
	650  3450 950  3450
Wire Wire Line
	650  3200 650  3250
Connection ~ 650  3250
Wire Wire Line
	650  3500 650  3450
Connection ~ 650  3450
$Comp
L power:GNDD #PWR05
U 1 1 5DDBF641
P 850 3900
F 0 "#PWR05" H 850 3650 50  0001 C CNN
F 1 "GNDD" H 854 3745 50  0000 C CNN
F 2 "" H 850 3900 50  0001 C CNN
F 3 "" H 850 3900 50  0001 C CNN
	1    850  3900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5DDBF647
P 1150 3750
F 0 "C7" H 1242 3796 50  0000 L CNN
F 1 "0.1uF" H 1242 3705 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 1150 3750 50  0001 C CNN
F 3 "~" H 1150 3750 50  0001 C CNN
	1    1150 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5DDBF64E
P 850 3750
F 0 "C3" H 942 3796 50  0000 L CNN
F 1 "1uF" H 942 3705 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 850 3750 50  0001 C CNN
F 3 "~" H 850 3750 50  0001 C CNN
	1    850  3750
	1    0    0    -1  
$EndComp
Connection ~ 1150 3650
Connection ~ 1150 3850
Wire Wire Line
	850  3650 1150 3650
Wire Wire Line
	850  3850 1150 3850
Wire Wire Line
	850  3600 850  3650
Connection ~ 850  3650
Wire Wire Line
	850  3900 850  3850
Connection ~ 850  3850
Wire Wire Line
	1600 3850 1600 3750
$Comp
L power:GNDD #PWR08
U 1 1 5DDBF664
P 1050 3950
F 0 "#PWR08" H 1050 3700 50  0001 C CNN
F 1 "GNDD" H 1200 3950 50  0000 C CNN
F 2 "" H 1050 3950 50  0001 C CNN
F 3 "" H 1050 3950 50  0001 C CNN
	1    1050 3950
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C9
U 1 1 5DDBF66A
P 1350 4100
F 0 "C9" H 1258 4146 50  0000 R CNN
F 1 "0.1uF" H 1258 4055 50  0000 R CNN
F 2 "SparkFun-Passives:0805" H 1350 4100 50  0001 C CNN
F 3 "~" H 1350 4100 50  0001 C CNN
	1    1350 4100
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5DDBF671
P 1050 4100
F 0 "C6" H 958 4146 50  0000 R CNN
F 1 "1uF" H 958 4055 50  0000 R CNN
F 2 "SparkFun-Passives:0805" H 1050 4100 50  0001 C CNN
F 3 "~" H 1050 4100 50  0001 C CNN
	1    1050 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1050 4200 1350 4200
Wire Wire Line
	1050 4000 1350 4000
Wire Wire Line
	1050 4250 1050 4200
Connection ~ 1050 4200
Wire Wire Line
	1050 3950 1050 4000
Connection ~ 1050 4000
Wire Wire Line
	1600 4200 1600 4150
Connection ~ 1350 4200
Wire Wire Line
	1600 4000 1600 4050
Connection ~ 1350 4000
Wire Wire Line
	1150 3850 1600 3850
Wire Wire Line
	1150 3650 1600 3650
Wire Wire Line
	1350 4000 1600 4000
Wire Wire Line
	1350 4200 1600 4200
$Comp
L Device:C_Small C10
U 1 1 5DDBF686
P 1450 4650
F 0 "C10" H 1358 4696 50  0000 R CNN
F 1 "1uF" H 1358 4605 50  0000 R CNN
F 2 "SparkFun-Passives:0805" H 1450 4650 50  0001 C CNN
F 3 "~" H 1450 4650 50  0001 C CNN
	1    1450 4650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1450 4550 1450 4450
Wire Wire Line
	1450 4450 1600 4450
$Comp
L power:GNDD #PWR014
U 1 1 5DDBF68F
P 1450 4750
F 0 "#PWR014" H 1450 4500 50  0001 C CNN
F 1 "GNDD" H 1454 4595 50  0000 C CNN
F 2 "" H 1450 4750 50  0001 C CNN
F 3 "" H 1450 4750 50  0001 C CNN
	1    1450 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5DDBF695
P 1150 5400
F 0 "R1" V 943 5400 50  0000 C CNN
F 1 "1MEG" V 1034 5400 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 1080 5400 50  0001 C CNN
F 3 "~" H 1150 5400 50  0001 C CNN
	1    1150 5400
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5DDBF69C
P 800 5950
F 0 "C2" H 892 5996 50  0000 L CNN
F 1 "22pF" H 892 5905 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 800 5950 50  0001 C CNN
F 3 "~" H 800 5950 50  0001 C CNN
	1    800  5950
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C11
U 1 1 5DDBF6A3
P 1450 5950
F 0 "C11" H 1542 5996 50  0000 L CNN
F 1 "22pF" H 1542 5905 50  0000 L CNN
F 2 "SparkFun-Passives:0805" H 1450 5950 50  0001 C CNN
F 3 "~" H 1450 5950 50  0001 C CNN
	1    1450 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5DDBF6AA
P 1150 5750
F 0 "Y1" H 1150 6018 50  0000 C CNN
F 1 "16MHz" H 1150 5927 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_HC49-SD_HandSoldering" H 1150 5750 50  0001 C CNN
F 3 "~" H 1150 5750 50  0001 C CNN
	1    1150 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 5400 1450 5400
Wire Wire Line
	1450 5850 1450 5750
Connection ~ 1450 5400
Wire Wire Line
	1450 5400 1300 5400
Wire Wire Line
	1300 5750 1450 5750
Connection ~ 1450 5750
Wire Wire Line
	1450 5750 1450 5400
Wire Wire Line
	1000 5400 800  5400
Wire Wire Line
	800  5400 800  5750
$Comp
L power:GNDD #PWR03
U 1 1 5DDBF6BA
P 800 6050
F 0 "#PWR03" H 800 5800 50  0001 C CNN
F 1 "GNDD" H 804 5895 50  0000 C CNN
F 2 "" H 800 6050 50  0001 C CNN
F 3 "" H 800 6050 50  0001 C CNN
	1    800  6050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR015
U 1 1 5DDBF6C0
P 1450 6050
F 0 "#PWR015" H 1450 5800 50  0001 C CNN
F 1 "GNDD" H 1454 5895 50  0000 C CNN
F 2 "" H 1450 6050 50  0001 C CNN
F 3 "" H 1450 6050 50  0001 C CNN
	1    1450 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 5750 800  5750
Connection ~ 800  5750
Wire Wire Line
	800  5750 800  5850
Wire Wire Line
	1600 5300 800  5300
Wire Wire Line
	800  5300 800  5400
Connection ~ 800  5400
Wire Wire Line
	1600 2850 1550 2850
Wire Wire Line
	1550 2850 1550 2800
Connection ~ 1250 2800
Wire Wire Line
	1600 2950 1550 2950
Wire Wire Line
	1550 2950 1550 3000
Connection ~ 1250 3000
Wire Wire Line
	1250 2800 1550 2800
Wire Wire Line
	1250 3000 1550 3000
Connection ~ 950  3250
Wire Wire Line
	950  3250 1600 3250
Connection ~ 950  3450
Wire Wire Line
	950  3450 1300 3450
Wire Wire Line
	1300 3350 1600 3350
Wire Wire Line
	1300 3450 1300 3350
$Comp
L power:GNDD #PWR011
U 1 1 5DDBF6E1
P 1200 7250
F 0 "#PWR011" H 1200 7000 50  0001 C CNN
F 1 "GNDD" V 1204 7140 50  0000 R CNN
F 2 "" H 1200 7250 50  0001 C CNN
F 3 "" H 1200 7250 50  0001 C CNN
	1    1200 7250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1200 7250 950  7250
Wire Wire Line
	1050 7000 1050 7150
Wire Wire Line
	1050 7150 950  7150
Text Label 1200 7350 2    50   ~ 0
XRES
Wire Wire Line
	1200 7450 950  7450
Text Label 1200 7450 2    50   ~ 0
SCLK
Text Label 1200 7550 2    50   ~ 0
SDAT
Wire Wire Line
	1200 7550 950  7550
Wire Wire Line
	950  7350 1200 7350
$Comp
L Device:R R3
U 1 1 5DDBF6FD
P 2500 7050
F 0 "R3" V 2293 7050 50  0000 C CNN
F 1 "280" V 2384 7050 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 2430 7050 50  0001 C CNN
F 3 "~" H 2500 7050 50  0001 C CNN
	1    2500 7050
	0    1    1    0   
$EndComp
$Comp
L Device:D D1
U 1 1 5DDBF704
P 2750 6900
F 0 "D1" V 2704 6979 50  0000 L CNN
F 1 "D" V 2795 6979 50  0000 L CNN
F 2 "SparkFun-Passives:1210" H 2750 6900 50  0001 C CNN
F 3 "~" H 2750 6900 50  0001 C CNN
	1    2750 6900
	0    1    1    0   
$EndComp
$Comp
L Isolator:4N28 U2
U 1 1 5DDBF70B
P 3300 6850
F 0 "U2" H 3300 7175 50  0000 C CNN
F 1 "4N28" H 3300 7084 50  0000 C CNN
F 2 "SparkFun-AnalogIC:DIL-08" H 3100 6650 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83725/4n25.pdf" H 3300 6850 50  0001 L CNN
	1    3300 6850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR017
U 1 1 5DDBF712
P 3650 7000
F 0 "#PWR017" H 3650 6750 50  0001 C CNN
F 1 "GNDD" H 3654 6845 50  0000 C CNN
F 2 "" H 3650 7000 50  0001 C CNN
F 3 "" H 3650 7000 50  0001 C CNN
	1    3650 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 7000 3650 6950
Wire Wire Line
	3650 6950 3600 6950
$Comp
L Device:R R4
U 1 1 5DDBF71A
P 3800 6650
F 0 "R4" H 3730 6604 50  0000 R CNN
F 1 "280" H 3730 6695 50  0000 R CNN
F 2 "SparkFun-Passives:0805" V 3730 6650 50  0001 C CNN
F 3 "~" H 3800 6650 50  0001 C CNN
	1    3800 6650
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR016
U 1 1 5DDBF721
P 3650 6400
F 0 "#PWR016" H 3650 6250 50  0001 C CNN
F 1 "+5V" H 3665 6573 50  0000 C CNN
F 2 "" H 3650 6400 50  0001 C CNN
F 3 "" H 3650 6400 50  0001 C CNN
	1    3650 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 6400 3650 6450
Wire Wire Line
	3650 6750 3600 6750
Wire Wire Line
	3800 6500 3800 6450
Wire Wire Line
	3800 6450 3650 6450
Connection ~ 3650 6450
Wire Wire Line
	3650 6450 3650 6750
Wire Wire Line
	3600 6850 3800 6850
Wire Wire Line
	3800 6800 3800 6850
Connection ~ 3800 6850
Wire Wire Line
	3800 6850 4100 6850
Text Label 4100 6850 0    50   ~ 0
MIDI_IN
Wire Wire Line
	2150 6750 2750 6750
Connection ~ 2750 6750
Wire Wire Line
	2750 6750 3000 6750
Wire Wire Line
	3000 6950 2950 6950
Wire Wire Line
	2950 6950 2950 7050
Wire Wire Line
	2950 7050 2750 7050
Wire Wire Line
	2750 7050 2650 7050
Connection ~ 2750 7050
Wire Wire Line
	2350 7050 2250 7050
Wire Wire Line
	2250 7050 2250 6850
Wire Wire Line
	2250 6850 2150 6850
$Comp
L Device:R R5
U 1 1 5DDBF73D
P 5050 6850
F 0 "R5" V 4843 6850 50  0000 C CNN
F 1 "R" V 4934 6850 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 4980 6850 50  0001 C CNN
F 3 "~" H 5050 6850 50  0001 C CNN
	1    5050 6850
	0    1    1    0   
$EndComp
Text Label 4550 6850 0    50   ~ 0
MIDI_OUT
Wire Wire Line
	4550 6850 4900 6850
$Comp
L dk_Transistors-Bipolar-BJT-Single:2N3904 Q1
U 1 1 5DDBF74F
P 5400 6850
F 0 "Q1" H 5588 6903 60  0000 L CNN
F 1 "2N3904" H 5588 6797 60  0000 L CNN
F 2 "SparkFun-DiscreteSemi:SOT23-3" H 5600 7050 60  0001 L CNN
F 3 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=LSSGP072.PDF" H 5600 7150 60  0001 L CNN
F 4 "2N3904CS-ND" H 5600 7250 60  0001 L CNN "Digi-Key_PN"
F 5 "2N3904" H 5600 7350 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 5600 7450 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 5600 7550 60  0001 L CNN "Family"
F 8 "https://my.centralsemi.com/get_document.php?cmp=1&mergetype=pd&mergepath=pd&pdf_id=LSSGP072.PDF" H 5600 7650 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/central-semiconductor-corp/2N3904/2N3904CS-ND/4806876" H 5600 7750 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V TO-92" H 5600 7850 60  0001 L CNN "Description"
F 11 "Central Semiconductor Corp" H 5600 7950 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5600 8050 60  0001 L CNN "Status"
	1    5400 6850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR018
U 1 1 5DDBF756
P 5500 7050
F 0 "#PWR018" H 5500 6800 50  0001 C CNN
F 1 "GNDD" H 5504 6895 50  0000 C CNN
F 2 "" H 5500 7050 50  0001 C CNN
F 3 "" H 5500 7050 50  0001 C CNN
	1    5500 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5DDBF763
P 5800 6450
F 0 "R6" V 5700 6450 50  0000 C CNN
F 1 "220" V 5800 6450 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 5730 6450 50  0001 C CNN
F 3 "~" H 5800 6450 50  0001 C CNN
	1    5800 6450
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5DDBF76A
P 5800 6550
F 0 "R7" V 5900 6550 50  0000 C CNN
F 1 "220" V 5800 6550 50  0000 C CNN
F 2 "SparkFun-Passives:0805" V 5730 6550 50  0001 C CNN
F 3 "~" H 5800 6550 50  0001 C CNN
	1    5800 6550
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR019
U 1 1 5DDBF771
P 5550 6400
F 0 "#PWR019" H 5550 6250 50  0001 C CNN
F 1 "+5V" H 5565 6573 50  0000 C CNN
F 2 "" H 5550 6400 50  0001 C CNN
F 3 "" H 5550 6400 50  0001 C CNN
	1    5550 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 6400 5550 6450
Wire Wire Line
	5550 6450 5650 6450
Wire Wire Line
	5500 6650 5500 6550
Wire Wire Line
	5500 6550 5650 6550
$Comp
L power:GNDD #PWR013
U 1 1 5DDBF7C1
P 1450 2450
F 0 "#PWR013" H 1450 2200 50  0001 C CNN
F 1 "GNDD" H 1454 2295 50  0000 C CNN
F 2 "" H 1450 2450 50  0001 C CNN
F 3 "" H 1450 2450 50  0001 C CNN
	1    1450 2450
	-1   0    0    -1  
$EndComp
Text Label 6650 3850 2    50   ~ 0
attack
Text Label 6650 3950 2    50   ~ 0
decay
Text Label 6650 4050 2    50   ~ 0
sustain
Text Label 6650 4150 2    50   ~ 0
release
Text Label 6650 4250 2    50   ~ 0
lfo_rate
Text Label 6650 4350 2    50   ~ 0
lfo_depth
Text Label 4100 1300 0    50   ~ 0
MIDI_IN
Text Label 4100 3500 0    50   ~ 0
MIDI_OUT
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5DD89DFF
P 1950 6750
F 0 "J3" H 1870 6967 50  0000 C CNN
F 1 "MIDI_IN" H 1870 6876 50  0000 C CNN
F 2 "SparkFun-Connectors:1X02" H 1950 6750 50  0001 C CNN
F 3 "~" H 1950 6750 50  0001 C CNN
	1    1950 6750
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5DD8C3FF
P 6150 6450
F 0 "J4" H 6229 6442 50  0000 L CNN
F 1 "MIDI_OUT" H 6229 6351 50  0000 L CNN
F 2 "SparkFun-Connectors:1X02" H 6150 6450 50  0001 C CNN
F 3 "~" H 6150 6450 50  0001 C CNN
	1    6150 6450
	1    0    0    -1  
$EndComp
Wire Notes Line
	1800 6050 1800 7400
Wire Notes Line
	1800 7400 6650 7400
Wire Notes Line
	6650 7400 6650 6050
Wire Notes Line
	6650 6050 1800 6050
Text Notes 2100 6150 0    50   ~ 0
MIDI
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 5DD98071
P 750 7350
F 0 "J1" H 670 7767 50  0000 C CNN
F 1 "SWD_programming" H 670 7676 50  0000 C CNN
F 2 "SparkFun-Connectors:1X05" H 750 7350 50  0001 C CNN
F 3 "~" H 750 7350 50  0001 C CNN
	1    750  7350
	-1   0    0    -1  
$EndComp
Text Label 6650 3450 2    50   ~ 0
osc1_tune
Text Label 6650 3550 2    50   ~ 0
osc1_waveshape
Text Label 6650 3650 2    50   ~ 0
osc2_tune
Text Label 6650 3750 2    50   ~ 0
osc2_waveshape
Text HLabel 4100 5400 2    50   Output ~ 0
UART_TX
Text HLabel 4100 5300 2    50   Input ~ 0
UART_RX
Wire Wire Line
	1450 2350 1600 2350
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY0101
U 1 1 5DDD3D34
P 1400 1250
F 0 "#SUPPLY0101" H 1400 1250 50  0001 L BNN
F 1 "3.3V" H 1400 1424 50  0000 C CNN
F 2 "" H 1400 1250 50  0001 C CNN
F 3 "" H 1400 1250 50  0001 C CNN
	1    1400 1250
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY0102
U 1 1 5DDD5545
P 950 2750
F 0 "#SUPPLY0102" H 950 2750 50  0001 L BNN
F 1 "3.3V" H 950 2924 50  0000 C CNN
F 2 "" H 950 2750 50  0001 C CNN
F 3 "" H 950 2750 50  0001 C CNN
	1    950  2750
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY0103
U 1 1 5DDD6153
P 650 3200
F 0 "#SUPPLY0103" H 650 3200 50  0001 L BNN
F 1 "3.3V" H 650 3374 50  0000 C CNN
F 2 "" H 650 3200 50  0001 C CNN
F 3 "" H 650 3200 50  0001 C CNN
	1    650  3200
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY0104
U 1 1 5DDD61F4
P 850 3600
F 0 "#SUPPLY0104" H 850 3600 50  0001 L BNN
F 1 "3.3V" H 1000 3650 50  0000 C CNN
F 2 "" H 850 3600 50  0001 C CNN
F 3 "" H 850 3600 50  0001 C CNN
	1    850  3600
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY0105
U 1 1 5DDD6380
P 1050 4250
F 0 "#SUPPLY0105" H 1050 4250 50  0001 L BNN
F 1 "3.3V" H 1050 4424 50  0000 C CNN
F 2 "" H 1050 4250 50  0001 C CNN
F 3 "" H 1050 4250 50  0001 C CNN
	1    1050 4250
	-1   0    0    1   
$EndComp
$Comp
L SparkFun-Aesthetics:3.3V #SUPPLY0106
U 1 1 5DDD845B
P 1050 7000
F 0 "#SUPPLY0106" H 1050 7000 50  0001 L BNN
F 1 "3.3V" H 1050 7174 50  0000 C CNN
F 2 "" H 1050 7000 50  0001 C CNN
F 3 "" H 1050 7000 50  0001 C CNN
	1    1050 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2450 1450 2450
Wire Wire Line
	1150 2250 1600 2250
Wire Wire Line
	1150 2150 1250 2150
Wire Wire Line
	1250 2150 1250 2050
Wire Wire Line
	1250 2050 1450 2050
Wire Wire Line
	1450 2050 1450 2350
Wire Wire Line
	1150 2350 1350 2350
Wire Wire Line
	1350 2350 1350 2150
Wire Wire Line
	1350 2150 1550 2150
Text HLabel 6650 3450 2    50   Input ~ 0
osc1_tune
Text HLabel 6650 3550 2    50   Input ~ 0
osc1_waveshape
Text HLabel 6650 3650 2    50   Input ~ 0
osc2_tune
Text HLabel 6650 3750 2    50   Input ~ 0
osc2_waveshape
Text HLabel 6650 3850 2    50   Input ~ 0
attack
Text HLabel 6650 3950 2    50   Input ~ 0
decay
Text HLabel 6650 4050 2    50   Input ~ 0
sustain
Text HLabel 6650 4150 2    50   Input ~ 0
release
Text HLabel 6650 4250 2    50   Input ~ 0
lfo_rate
Text HLabel 6650 4350 2    50   Input ~ 0
lfo_depth
Text HLabel 6650 4450 2    50   Input ~ 0
global_lfo_rate
Text HLabel 6650 4550 2    50   Input ~ 0
global_lfo_depth
Text Label 6650 4450 2    50   ~ 0
global_lfo_rate
Text Label 6650 4550 2    50   ~ 0
global_lfo_depth
Text Label 4100 2200 0    50   ~ 0
attack
Text Label 4100 3900 0    50   ~ 0
decay
Text Label 4100 4000 0    50   ~ 0
sustain
Text Label 4100 4100 0    50   ~ 0
release
Text Label 4100 4200 0    50   ~ 0
lfo_rate
Text Label 4100 4300 0    50   ~ 0
lfo_depth
Text Label 4100 3400 0    50   ~ 0
osc1_tune
Text Label 4100 3300 0    50   ~ 0
osc1_waveshape
Text Label 4100 3200 0    50   ~ 0
osc2_tune
Text Label 4100 3100 0    50   ~ 0
osc2_waveshape
Text Label 4100 4400 0    50   ~ 0
global_lfo_rate
Text Label 4100 4500 0    50   ~ 0
global_lfo_depth
Text Notes 4750 2800 0    50   ~ 0
GPIOs need to be changed!
Text HLabel 4100 1100 2    50   BiDi ~ 0
FREQ_CTRL
Text HLabel 4100 2900 2    50   BiDi ~ 0
mod1
Text HLabel 4100 2800 2    50   BiDi ~ 0
mod2
Text HLabel 4100 2700 2    50   BiDi ~ 0
mod3
Text HLabel 4100 2600 2    50   BiDi ~ 0
mod4
Text HLabel 4100 2000 2    50   BiDi ~ 0
mod5
Text HLabel 4100 1900 2    50   BiDi ~ 0
mod6
Text HLabel 4100 5000 2    50   BiDi ~ 0
mod7
Text HLabel 4100 4900 2    50   BiDi ~ 0
mod8
$Comp
L power:VBUS #PWR0121
U 1 1 5DE5C7FD
P 1550 2100
F 0 "#PWR0121" H 1550 1950 50  0001 C CNN
F 1 "VBUS" H 1565 2273 50  0000 C CNN
F 2 "" H 1550 2100 50  0001 C CNN
F 3 "" H 1550 2100 50  0001 C CNN
	1    1550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2100 1550 2150
Connection ~ 1550 2150
Wire Wire Line
	1550 2150 1600 2150
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5DE792F8
P 950 2250
F 0 "J2" H 870 2567 50  0000 C CNN
F 1 "Conn_01x04" H 870 2476 50  0000 C CNN
F 2 "SparkFun-Connectors:1X04" H 950 2250 50  0001 C CNN
F 3 "~" H 950 2250 50  0001 C CNN
	1    950  2250
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
