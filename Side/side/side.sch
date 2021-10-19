EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L power:GND #PWR0101
U 1 1 616EA850
P 7300 2650
F 0 "#PWR0101" H 7300 2400 50  0001 C CNN
F 1 "GND" H 7305 2477 50  0000 C CNN
F 2 "" H 7300 2650 50  0001 C CNN
F 3 "" H 7300 2650 50  0001 C CNN
	1    7300 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 616EB208
P 5350 2450
F 0 "#PWR0102" H 5350 2200 50  0001 C CNN
F 1 "GND" H 5355 2277 50  0000 C CNN
F 2 "" H 5350 2450 50  0001 C CNN
F 3 "" H 5350 2450 50  0001 C CNN
	1    5350 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0103
U 1 1 616EB387
P 7300 2350
F 0 "#PWR0103" H 7300 2200 50  0001 C CNN
F 1 "+3.3V" H 7315 2523 50  0000 C CNN
F 2 "" H 7300 2350 50  0001 C CNN
F 3 "" H 7300 2350 50  0001 C CNN
	1    7300 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 616EB505
P 5550 2350
F 0 "#PWR0104" H 5550 2200 50  0001 C CNN
F 1 "+5V" H 5565 2523 50  0000 C CNN
F 2 "" H 5550 2350 50  0001 C CNN
F 3 "" H 5550 2350 50  0001 C CNN
	1    5550 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2350 5950 2350
Wire Wire Line
	7300 2350 6700 2350
Wire Wire Line
	6700 2650 7300 2650
NoConn ~ 5950 2550
NoConn ~ 5950 2650
NoConn ~ 5950 2850
NoConn ~ 5950 2950
Wire Wire Line
	5500 3450 5950 3450
Wire Wire Line
	5500 3350 5950 3350
Text Label 5500 3350 0    50   ~ 0
Analogue_1
Text Label 5500 3450 0    50   ~ 0
Analogue_0
$Comp
L power:GND #PWR0105
U 1 1 616F01C4
P 7800 2400
F 0 "#PWR0105" H 7800 2150 50  0001 C CNN
F 1 "GND" H 7805 2227 50  0000 C CNN
F 2 "" H 7800 2400 50  0001 C CNN
F 3 "" H 7800 2400 50  0001 C CNN
	1    7800 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 616F0805
P 7800 2800
F 0 "#PWR0106" H 7800 2650 50  0001 C CNN
F 1 "+5V" H 7815 2973 50  0000 C CNN
F 2 "" H 7800 2800 50  0001 C CNN
F 3 "" H 7800 2800 50  0001 C CNN
	1    7800 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3850 9350 3850
Wire Wire Line
	8900 3750 9350 3750
Wire Wire Line
	9350 3450 8900 3450
Wire Wire Line
	9350 3350 8900 3350
Text Label 9350 3850 2    50   ~ 0
SDA
Text Label 9350 3750 2    50   ~ 0
SCL
Text Label 9350 4050 2    50   ~ 0
Digital_1
Wire Wire Line
	9350 3650 8900 3650
Wire Wire Line
	9350 3550 8900 3550
Text Label 9350 3650 2    50   ~ 0
PWM_1
Text Label 9350 3550 2    50   ~ 0
PWM_2
Wire Wire Line
	7950 3750 8400 3750
Wire Wire Line
	7950 3650 8400 3650
Text Label 7950 3650 0    50   ~ 0
Analogue_1
Text Label 7950 3750 0    50   ~ 0
Analogue_0
Wire Wire Line
	7950 3550 8400 3550
Text Label 7950 3550 0    50   ~ 0
Digital_2
$Comp
L power:GND #PWR0107
U 1 1 616F5568
P 7750 4050
F 0 "#PWR0107" H 7750 3800 50  0001 C CNN
F 1 "GND" H 7755 3877 50  0000 C CNN
F 2 "" H 7750 4050 50  0001 C CNN
F 3 "" H 7750 4050 50  0001 C CNN
	1    7750 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 616F5A38
P 8050 3350
F 0 "#PWR0108" H 8050 3200 50  0001 C CNN
F 1 "+5V" H 8065 3523 50  0000 C CNN
F 2 "" H 8050 3350 50  0001 C CNN
F 3 "" H 8050 3350 50  0001 C CNN
	1    8050 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 616F5B83
P 7800 3350
F 0 "#PWR0109" H 7800 3200 50  0001 C CNN
F 1 "+3.3V" H 7815 3523 50  0000 C CNN
F 2 "" H 7800 3350 50  0001 C CNN
F 3 "" H 7800 3350 50  0001 C CNN
	1    7800 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 4050 8400 4050
Wire Wire Line
	8400 3450 7800 3450
Wire Wire Line
	7800 3450 7800 3350
Wire Wire Line
	8050 3350 8400 3350
Text Label 7150 3150 2    50   ~ 0
PWM_2
Wire Wire Line
	7150 3150 6700 3150
Wire Wire Line
	7150 3250 6700 3250
Text Label 7150 2850 2    50   ~ 0
Digital_2
Text Label 7150 2950 2    50   ~ 0
Digital_1
Text Label 7150 3050 2    50   ~ 0
Digital_0
Text Label 7150 3350 2    50   ~ 0
SCL
Text Label 7150 3450 2    50   ~ 0
SDA
Wire Wire Line
	7150 2850 6700 2850
Wire Wire Line
	7150 2950 6700 2950
Wire Wire Line
	7150 3050 6700 3050
Wire Wire Line
	6700 3350 7150 3350
Wire Wire Line
	6700 3450 7150 3450
NoConn ~ 6700 2550
NoConn ~ 6700 2450
$Comp
L Device:Photon U1
U 1 1 616E9343
P 6200 2200
F 0 "U1" H 6325 2315 50  0000 C CNN
F 1 "Photon" H 6325 2224 50  0000 C CNN
F 2 "Socket:Photon" H 6200 2200 50  0001 C CNN
F 3 "" H 6200 2200 50  0001 C CNN
	1    6200 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3550 7150 3550
Wire Wire Line
	6700 3650 7150 3650
Text Label 7150 3550 2    50   ~ 0
D+
Text Label 7150 3650 2    50   ~ 0
D-
Wire Wire Line
	8400 2600 7950 2600
Wire Wire Line
	8400 2700 7950 2700
Text Label 7950 2600 0    50   ~ 0
D+
Text Label 7950 2700 0    50   ~ 0
D-
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 616EC106
P 8600 2600
F 0 "J2" H 8680 2642 50  0000 L CNN
F 1 "Micro_USB_Breakout" H 8680 2551 50  0000 L CNN
F 2 "Socket:Adafruit_Micro_USB_Breakout_copy" H 8680 2505 50  0001 L CNN
F 3 "~" H 8600 2600 50  0001 C CNN
	1    8600 2600
	1    0    0    -1  
$EndComp
NoConn ~ 8400 2500
Wire Wire Line
	8400 2400 7800 2400
Wire Wire Line
	7800 2800 8400 2800
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J1
U 1 1 616EE07C
P 8600 3650
F 0 "J1" H 8650 4167 50  0000 C CNN
F 1 "Conn_02x08_Odd_Even" H 8650 4076 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x08_P2.54mm_Vertical" H 8600 3650 50  0001 C CNN
F 3 "~" H 8600 3650 50  0001 C CNN
	1    8600 3650
	1    0    0    -1  
$EndComp
Text Label 7150 2750 2    50   ~ 0
Digital_3
Wire Wire Line
	7150 2750 6700 2750
Text Label 9350 3950 2    50   ~ 0
Digital_3
Wire Wire Line
	9350 3950 8900 3950
Text Label 5500 3250 0    50   ~ 0
Digital_4
Wire Wire Line
	5500 3250 5950 3250
Text Label 5500 3150 0    50   ~ 0
Digital_5
Wire Wire Line
	5500 3150 5950 3150
Text Label 5500 2750 0    50   ~ 0
PWM_3
Wire Wire Line
	5500 2750 5950 2750
Text Label 9350 3350 2    50   ~ 0
Digital_4
Wire Wire Line
	9350 4050 8900 4050
Text Label 9350 3450 2    50   ~ 0
Digital_5
Wire Wire Line
	7950 3950 8400 3950
Text Label 7150 3250 2    50   ~ 0
PWM_1
Wire Wire Line
	5350 2450 5950 2450
NoConn ~ 5950 3050
Wire Wire Line
	7950 3850 8400 3850
Text Label 7950 3850 0    50   ~ 0
PWM_3
Text Label 7950 3950 0    50   ~ 0
Digital_0
$EndSCHEMATC
