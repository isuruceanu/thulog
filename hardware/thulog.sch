EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:thulog-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "1 jul 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY2313A-S IC1
U 1 1 53AD6CF0
P 5100 3700
F 0 "IC1" H 4250 4650 60  0000 C CNN
F 1 "ATTINY2313A-S" H 5900 2850 60  0000 C CNN
F 2 "SO20" H 4100 2850 60  0001 C CNN
F 3 "" H 5100 3700 60  0000 C CNN
	1    5100 3700
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P2
U 1 1 53AD6D1E
P 8500 4050
F 0 "P2" V 8450 4050 50  0000 C CNN
F 1 "USB" V 8550 4050 50  0000 C CNN
F 2 "" H 8500 4050 60  0000 C CNN
F 3 "" H 8500 4050 60  0000 C CNN
	1    8500 4050
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P1
U 1 1 53AD6D39
P 7350 3450
F 0 "P1" V 7300 3450 60  0000 C CNN
F 1 "ISP" V 7400 3450 60  0000 C CNN
F 2 "" H 7350 3450 60  0000 C CNN
F 3 "" H 7350 3450 60  0000 C CNN
	1    7350 3450
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 53AD6D63
P 2800 3750
F 0 "C1" H 2800 3850 40  0000 L CNN
F 1 "C" H 2806 3665 40  0000 L CNN
F 2 "~" H 2838 3600 30  0000 C CNN
F 3 "~" H 2800 3750 60  0000 C CNN
	1    2800 3750
	1    0    0    -1  
$EndComp
$Comp
L QUARTZCMS4 X1
U 1 1 53AD6D9F
P 3150 3400
F 0 "X1" H 3150 3550 60  0000 C CNN
F 1 "QUARTZCMS4" H 3150 3250 60  0000 C CNN
F 2 "~" H 3150 3400 60  0000 C CNN
F 3 "~" H 3150 3400 60  0000 C CNN
	1    3150 3400
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 53AD6DBD
P 6600 2000
F 0 "K1" V 6550 2000 50  0000 C CNN
F 1 "DHT" V 6650 2000 40  0000 C CNN
F 2 "" H 6600 2000 60  0000 C CNN
F 3 "" H 6600 2000 60  0000 C CNN
	1    6600 2000
	0    -1   -1   0   
$EndComp
$Comp
L ZENER D2
U 1 1 53AD6DDF
P 7400 4500
F 0 "D2" H 7400 4600 50  0000 C CNN
F 1 "ZENER" H 7400 4400 40  0000 C CNN
F 2 "~" H 7400 4500 60  0000 C CNN
F 3 "~" H 7400 4500 60  0000 C CNN
	1    7400 4500
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 53AD6E10
P 6850 4000
F 0 "R2" V 6930 4000 40  0000 C CNN
F 1 "68" V 6850 4000 40  0000 C CNN
F 2 "~" V 6780 4000 30  0000 C CNN
F 3 "~" H 6850 4000 30  0000 C CNN
	1    6850 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6450 4000 6600 4000
$Comp
L R R3
U 1 1 53AD6E43
P 6850 4100
F 0 "R3" V 6930 4100 40  0000 C CNN
F 1 "68" V 6850 4100 40  0000 C CNN
F 2 "~" V 6780 4100 30  0000 C CNN
F 3 "~" H 6850 4100 30  0000 C CNN
	1    6850 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6450 4100 6600 4100
Text Label 7000 5700 0    60   ~ 0
GND
Text Label 7050 5700 1    60   ~ 0
GND
Text GLabel 7650 5550 3    60   Input ~ 0
GND
$Comp
L LED D1
U 1 1 53AD6DAE
P 7250 2750
F 0 "D1" H 7250 2850 50  0000 C CNN
F 1 "LED" H 7250 2650 50  0000 C CNN
F 2 "~" H 7250 2750 60  0000 C CNN
F 3 "~" H 7250 2750 60  0000 C CNN
	1    7250 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 5400 8150 5400
Wire Wire Line
	7100 4100 8150 4100
Wire Wire Line
	7400 4100 7400 4300
Wire Wire Line
	7400 5400 7400 4700
$Comp
L ZENER D3
U 1 1 53AD6F7F
P 7650 4500
F 0 "D3" H 7650 4600 50  0000 C CNN
F 1 "ZENER" H 7650 4400 40  0000 C CNN
F 2 "~" H 7650 4500 60  0000 C CNN
F 3 "~" H 7650 4500 60  0000 C CNN
	1    7650 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 4000 8150 4000
Wire Wire Line
	7650 4000 7650 4300
Wire Wire Line
	7650 4700 7650 5550
Connection ~ 7400 5400
$Comp
L R R4
U 1 1 53AD6FAD
P 7900 4550
F 0 "R4" V 7980 4550 40  0000 C CNN
F 1 "R" V 7907 4551 40  0000 C CNN
F 2 "~" V 7830 4550 30  0000 C CNN
F 3 "~" H 7900 4550 30  0000 C CNN
	1    7900 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4100 7900 4300
Wire Wire Line
	8150 5400 8150 4200
Connection ~ 7650 5400
Wire Wire Line
	7900 4800 7900 5400
Connection ~ 7900 5400
Connection ~ 7900 4100
Connection ~ 7400 4100
Connection ~ 7650 4000
Text GLabel 7950 3900 0    60   Input ~ 0
VCC
Wire Wire Line
	8150 3900 7950 3900
Wire Wire Line
	5100 4700 5100 5400
Wire Wire Line
	3750 3400 3450 3400
Wire Wire Line
	3750 3200 2800 3200
Wire Wire Line
	2800 3200 2800 3550
Wire Wire Line
	2800 3400 2850 3400
$Comp
L C C2
U 1 1 53AD70D0
P 3600 3750
F 0 "C2" H 3600 3850 40  0000 L CNN
F 1 "C" H 3606 3665 40  0000 L CNN
F 2 "~" H 3638 3600 30  0000 C CNN
F 3 "~" H 3600 3750 60  0000 C CNN
	1    3600 3750
	1    0    0    -1  
$EndComp
Connection ~ 2800 3400
Wire Wire Line
	3600 3550 3600 3400
Connection ~ 3600 3400
Wire Wire Line
	2800 3950 2800 4250
Wire Wire Line
	2800 4250 3600 4250
Wire Wire Line
	3600 4250 3600 3950
Wire Wire Line
	3200 4250 3200 5400
Connection ~ 5100 5400
Connection ~ 3200 4250
Text GLabel 6900 3200 0    60   Input ~ 0
GND
Wire Wire Line
	6800 3700 7000 3700
Wire Wire Line
	6450 3600 7000 3600
Wire Wire Line
	6450 3500 7000 3500
Wire Wire Line
	6450 3400 7000 3400
Text GLabel 3400 2900 0    60   Input ~ 0
RESET
Wire Wire Line
	3400 2900 3750 2900
Text GLabel 6900 3300 0    60   Input ~ 0
RESET
Wire Wire Line
	6900 3300 7000 3300
Wire Wire Line
	6450 2900 6600 2900
Wire Wire Line
	6600 2900 6600 2350
Text GLabel 6700 2650 3    60   Input ~ 0
GND
Wire Wire Line
	6500 2350 6500 2500
Wire Wire Line
	6500 2500 5100 2500
Wire Wire Line
	5100 2500 5100 2600
Text GLabel 5700 2250 1    60   Input ~ 0
VCC
Wire Wire Line
	5700 2250 5700 2500
Connection ~ 5700 2500
Wire Wire Line
	6700 2350 6700 2650
Text GLabel 6800 3700 0    60   Input ~ 0
VCC
Wire Wire Line
	7000 3200 6900 3200
$Comp
L C C3
U 1 1 53AD7582
P 2850 1600
F 0 "C3" H 2850 1700 40  0000 L CNN
F 1 "C" H 2856 1515 40  0000 L CNN
F 2 "~" H 2888 1450 30  0000 C CNN
F 3 "~" H 2850 1600 60  0000 C CNN
	1    2850 1600
	1    0    0    -1  
$EndComp
$Comp
L CP1 C4
U 1 1 53AD7591
P 3150 1600
F 0 "C4" H 3200 1700 50  0000 L CNN
F 1 "CP1" H 3200 1500 50  0000 L CNN
F 2 "~" H 3150 1600 60  0000 C CNN
F 3 "~" H 3150 1600 60  0000 C CNN
	1    3150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1800 2850 2050
Wire Wire Line
	2850 2050 3150 2050
Wire Wire Line
	3150 2050 3150 1800
Wire Wire Line
	2850 1400 2850 1150
Wire Wire Line
	2850 1150 3150 1150
Wire Wire Line
	3150 1150 3150 1400
Text GLabel 3000 950  1    60   Input ~ 0
VCC
Wire Wire Line
	3000 950  3000 1150
Connection ~ 3000 1150
Text GLabel 3000 2250 3    60   Input ~ 0
GND
Wire Wire Line
	3000 2250 3000 2050
Connection ~ 3000 2050
$Comp
L R R1
U 1 1 53AD6ECE
P 6850 3000
F 0 "R1" V 6930 3000 40  0000 C CNN
F 1 "R" V 6857 3001 40  0000 C CNN
F 2 "~" V 6780 3000 30  0000 C CNN
F 3 "~" H 6850 3000 30  0000 C CNN
	1    6850 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6450 3000 6600 3000
Wire Wire Line
	7100 3000 7250 3000
Wire Wire Line
	7250 3000 7250 2950
Wire Wire Line
	7250 2550 7250 2450
Wire Wire Line
	7250 2450 6700 2450
Connection ~ 6700 2450
$EndSCHEMATC
