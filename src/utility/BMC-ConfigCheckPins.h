/*
See https://www.RoxXxtar.com/bmc for more details
Copyright (c) 2020 RoxXxtar.com
See BMC Documentation for License
See LICENSE file in the project root for full license information.
*/

#ifndef BMC_CONFIG_CHECK_PINS_H
#define BMC_CONFIG_CHECK_PINS_H


#ifndef BMC_MAX_PAGES
  #define BMC_MAX_PAGES 1
#endif

#ifndef BMC_MAX_PAGES
  #undef BMC_MAX_PAGES
  #define BMC_MAX_PAGES 1
#endif

#ifndef BMC_MAX_MUX_IN
  #define BMC_MAX_MUX_IN 0
#endif

#ifndef BMC_MAX_MUX_IN_ANALOG
  #define BMC_MAX_MUX_IN_ANALOG 0
#endif

#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 0
#if defined(BMC_BUTTON_1_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=1 && defined(BMC_BUTTON_1_X) && defined(BMC_BUTTON_1_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 1

#if defined(BMC_BUTTON_2_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_BUTTON_2_X) && defined(BMC_BUTTON_2_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 2

#if defined(BMC_BUTTON_3_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=3 && defined(BMC_BUTTON_3_X) && defined(BMC_BUTTON_3_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 3

#if defined(BMC_BUTTON_4_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_BUTTON_4_X) && defined(BMC_BUTTON_4_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 4

#if defined(BMC_BUTTON_5_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=5 && defined(BMC_BUTTON_5_X) && defined(BMC_BUTTON_5_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 5

#if defined(BMC_BUTTON_6_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_BUTTON_6_X) && defined(BMC_BUTTON_6_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 6

#if defined(BMC_BUTTON_7_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=7 && defined(BMC_BUTTON_7_X) && defined(BMC_BUTTON_7_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 7

#if defined(BMC_BUTTON_8_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_BUTTON_8_X) && defined(BMC_BUTTON_8_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 8

#if defined(BMC_BUTTON_9_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=9 && defined(BMC_BUTTON_9_X) && defined(BMC_BUTTON_9_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 9

#if defined(BMC_BUTTON_10_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_BUTTON_10_X) && defined(BMC_BUTTON_10_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 10

#if defined(BMC_BUTTON_11_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=11 && defined(BMC_BUTTON_11_X) && defined(BMC_BUTTON_11_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 11

#if defined(BMC_BUTTON_12_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_BUTTON_12_X) && defined(BMC_BUTTON_12_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 12

#if defined(BMC_BUTTON_13_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=13 && defined(BMC_BUTTON_13_X) && defined(BMC_BUTTON_13_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 13

#if defined(BMC_BUTTON_14_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_BUTTON_14_X) && defined(BMC_BUTTON_14_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 14

#if defined(BMC_BUTTON_15_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=15 && defined(BMC_BUTTON_15_X) && defined(BMC_BUTTON_15_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 15

#if defined(BMC_BUTTON_16_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_BUTTON_16_X) && defined(BMC_BUTTON_16_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 16

#if defined(BMC_BUTTON_17_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=17 && defined(BMC_BUTTON_17_X) && defined(BMC_BUTTON_17_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 17

#if defined(BMC_BUTTON_18_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_BUTTON_18_X) && defined(BMC_BUTTON_18_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 18

#if defined(BMC_BUTTON_19_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=19 && defined(BMC_BUTTON_19_X) && defined(BMC_BUTTON_19_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 19

#if defined(BMC_BUTTON_20_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_BUTTON_20_X) && defined(BMC_BUTTON_20_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 20

#if defined(BMC_BUTTON_21_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=21 && defined(BMC_BUTTON_21_X) && defined(BMC_BUTTON_21_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 21

#if defined(BMC_BUTTON_22_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_BUTTON_22_X) && defined(BMC_BUTTON_22_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 22

#if defined(BMC_BUTTON_23_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=23 && defined(BMC_BUTTON_23_X) && defined(BMC_BUTTON_23_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 23

#if defined(BMC_BUTTON_24_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_BUTTON_24_X) && defined(BMC_BUTTON_24_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 24

#if defined(BMC_BUTTON_25_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=25 && defined(BMC_BUTTON_25_X) && defined(BMC_BUTTON_25_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 25

#if defined(BMC_BUTTON_26_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_BUTTON_26_X) && defined(BMC_BUTTON_26_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 26

#if defined(BMC_BUTTON_27_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=27 && defined(BMC_BUTTON_27_X) && defined(BMC_BUTTON_27_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 27

#if defined(BMC_BUTTON_28_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_BUTTON_28_X) && defined(BMC_BUTTON_28_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 28

#if defined(BMC_BUTTON_29_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=29 && defined(BMC_BUTTON_29_X) && defined(BMC_BUTTON_29_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 29

#if defined(BMC_BUTTON_30_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_BUTTON_30_X) && defined(BMC_BUTTON_30_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 30

#if defined(BMC_BUTTON_31_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=31 && defined(BMC_BUTTON_31_X) && defined(BMC_BUTTON_31_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 31

#if defined(BMC_BUTTON_32_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_BUTTON_32_X) && defined(BMC_BUTTON_32_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 32

#if defined(BMC_BUTTON_33_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=33 && defined(BMC_BUTTON_33_X) && defined(BMC_BUTTON_33_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 33

#if defined(BMC_BUTTON_34_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_BUTTON_34_X) && defined(BMC_BUTTON_34_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 34

#if defined(BMC_BUTTON_35_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=35 && defined(BMC_BUTTON_35_X) && defined(BMC_BUTTON_35_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 35

#if defined(BMC_BUTTON_36_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_BUTTON_36_X) && defined(BMC_BUTTON_36_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 36

#if defined(BMC_BUTTON_37_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=37 && defined(BMC_BUTTON_37_X) && defined(BMC_BUTTON_37_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 37

#if defined(BMC_BUTTON_38_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_BUTTON_38_X) && defined(BMC_BUTTON_38_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 38

#if defined(BMC_BUTTON_39_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=39 && defined(BMC_BUTTON_39_X) && defined(BMC_BUTTON_39_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 39

#if defined(BMC_BUTTON_40_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_BUTTON_40_X) && defined(BMC_BUTTON_40_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 40

#if defined(BMC_BUTTON_41_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=41 && defined(BMC_BUTTON_41_X) && defined(BMC_BUTTON_41_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 41

#if defined(BMC_BUTTON_42_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_BUTTON_42_X) && defined(BMC_BUTTON_42_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 42

#if defined(BMC_BUTTON_43_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=43 && defined(BMC_BUTTON_43_X) && defined(BMC_BUTTON_43_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 43

#if defined(BMC_BUTTON_44_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_BUTTON_44_X) && defined(BMC_BUTTON_44_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 44

#if defined(BMC_BUTTON_45_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=45 && defined(BMC_BUTTON_45_X) && defined(BMC_BUTTON_45_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 45

#if defined(BMC_BUTTON_46_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_BUTTON_46_X) && defined(BMC_BUTTON_46_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 46

#if defined(BMC_BUTTON_47_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=47 && defined(BMC_BUTTON_47_X) && defined(BMC_BUTTON_47_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 47

#if defined(BMC_BUTTON_48_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_BUTTON_48_X) && defined(BMC_BUTTON_48_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 48

#if defined(BMC_BUTTON_49_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=49 && defined(BMC_BUTTON_49_X) && defined(BMC_BUTTON_49_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 49

#if defined(BMC_BUTTON_50_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_BUTTON_50_X) && defined(BMC_BUTTON_50_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 50

#if defined(BMC_BUTTON_51_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=51 && defined(BMC_BUTTON_51_X) && defined(BMC_BUTTON_51_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 51

#if defined(BMC_BUTTON_52_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_BUTTON_52_X) && defined(BMC_BUTTON_52_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 52

#if defined(BMC_BUTTON_53_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=53 && defined(BMC_BUTTON_53_X) && defined(BMC_BUTTON_53_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 53

#if defined(BMC_BUTTON_54_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_BUTTON_54_X) && defined(BMC_BUTTON_54_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 54

#if defined(BMC_BUTTON_55_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=55 && defined(BMC_BUTTON_55_X) && defined(BMC_BUTTON_55_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 55

#if defined(BMC_BUTTON_56_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_BUTTON_56_X) && defined(BMC_BUTTON_56_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 56

#if defined(BMC_BUTTON_57_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=57 && defined(BMC_BUTTON_57_X) && defined(BMC_BUTTON_57_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 57

#if defined(BMC_BUTTON_58_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_BUTTON_58_X) && defined(BMC_BUTTON_58_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 58

#if defined(BMC_BUTTON_59_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=59 && defined(BMC_BUTTON_59_X) && defined(BMC_BUTTON_59_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 59

#if defined(BMC_BUTTON_60_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_BUTTON_60_X) && defined(BMC_BUTTON_60_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 60

#if defined(BMC_BUTTON_61_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=61 && defined(BMC_BUTTON_61_X) && defined(BMC_BUTTON_61_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 61

#if defined(BMC_BUTTON_62_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_BUTTON_62_X) && defined(BMC_BUTTON_62_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 62

#if defined(BMC_BUTTON_63_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=63 && defined(BMC_BUTTON_63_X) && defined(BMC_BUTTON_63_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 63

#if defined(BMC_BUTTON_64_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_BUTTON_64_X) && defined(BMC_BUTTON_64_Y)
#ifdef BMC_MAX_BUTTONS
#undef BMC_MAX_BUTTONS
#endif
#define BMC_MAX_BUTTONS 64

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 0
#if defined(BMC_LED_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && defined(BMC_LED_1_X) && defined(BMC_LED_1_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 1

#if defined(BMC_LED_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_LED_2_X) && defined(BMC_LED_2_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 2

#if defined(BMC_LED_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && defined(BMC_LED_3_X) && defined(BMC_LED_3_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 3

#if defined(BMC_LED_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_LED_4_X) && defined(BMC_LED_4_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 4

#if defined(BMC_LED_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && defined(BMC_LED_5_X) && defined(BMC_LED_5_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 5

#if defined(BMC_LED_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_LED_6_X) && defined(BMC_LED_6_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 6

#if defined(BMC_LED_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && defined(BMC_LED_7_X) && defined(BMC_LED_7_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 7

#if defined(BMC_LED_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_LED_8_X) && defined(BMC_LED_8_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 8

#if defined(BMC_LED_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && defined(BMC_LED_9_X) && defined(BMC_LED_9_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 9

#if defined(BMC_LED_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_LED_10_X) && defined(BMC_LED_10_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 10

#if defined(BMC_LED_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && defined(BMC_LED_11_X) && defined(BMC_LED_11_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 11

#if defined(BMC_LED_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_LED_12_X) && defined(BMC_LED_12_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 12

#if defined(BMC_LED_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && defined(BMC_LED_13_X) && defined(BMC_LED_13_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 13

#if defined(BMC_LED_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_LED_14_X) && defined(BMC_LED_14_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 14

#if defined(BMC_LED_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && defined(BMC_LED_15_X) && defined(BMC_LED_15_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 15

#if defined(BMC_LED_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_LED_16_X) && defined(BMC_LED_16_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 16

#if defined(BMC_LED_17_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && defined(BMC_LED_17_X) && defined(BMC_LED_17_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 17

#if defined(BMC_LED_18_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && defined(BMC_LED_18_X) && defined(BMC_LED_18_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 18

#if defined(BMC_LED_19_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && defined(BMC_LED_19_X) && defined(BMC_LED_19_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 19

#if defined(BMC_LED_20_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && defined(BMC_LED_20_X) && defined(BMC_LED_20_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 20

#if defined(BMC_LED_21_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && defined(BMC_LED_21_X) && defined(BMC_LED_21_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 21

#if defined(BMC_LED_22_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && defined(BMC_LED_22_X) && defined(BMC_LED_22_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 22

#if defined(BMC_LED_23_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && defined(BMC_LED_23_X) && defined(BMC_LED_23_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 23

#if defined(BMC_LED_24_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && defined(BMC_LED_24_X) && defined(BMC_LED_24_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 24

#if defined(BMC_LED_25_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && defined(BMC_LED_25_X) && defined(BMC_LED_25_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 25

#if defined(BMC_LED_26_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && defined(BMC_LED_26_X) && defined(BMC_LED_26_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 26

#if defined(BMC_LED_27_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && defined(BMC_LED_27_X) && defined(BMC_LED_27_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 27

#if defined(BMC_LED_28_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && defined(BMC_LED_28_X) && defined(BMC_LED_28_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 28

#if defined(BMC_LED_29_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && defined(BMC_LED_29_X) && defined(BMC_LED_29_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 29

#if defined(BMC_LED_30_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && defined(BMC_LED_30_X) && defined(BMC_LED_30_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 30

#if defined(BMC_LED_31_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && defined(BMC_LED_31_X) && defined(BMC_LED_31_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 31

#if defined(BMC_LED_32_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && defined(BMC_LED_32_X) && defined(BMC_LED_32_Y)
#ifdef BMC_MAX_LEDS
#undef BMC_MAX_LEDS
#endif
#define BMC_MAX_LEDS 32

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 0
#if defined(BMC_POT_1_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=1) && defined(BMC_POT_1_X) && defined(BMC_POT_1_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 1

#if defined(BMC_POT_2_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=2) && defined(BMC_POT_2_X) && defined(BMC_POT_2_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 2

#if defined(BMC_POT_3_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=3) && defined(BMC_POT_3_X) && defined(BMC_POT_3_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 3

#if defined(BMC_POT_4_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=4) && defined(BMC_POT_4_X) && defined(BMC_POT_4_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 4

#if defined(BMC_POT_5_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=5) && defined(BMC_POT_5_X) && defined(BMC_POT_5_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 5

#if defined(BMC_POT_6_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=6) && defined(BMC_POT_6_X) && defined(BMC_POT_6_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 6

#if defined(BMC_POT_7_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=7) && defined(BMC_POT_7_X) && defined(BMC_POT_7_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 7

#if defined(BMC_POT_8_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=8) && defined(BMC_POT_8_X) && defined(BMC_POT_8_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 8

#if defined(BMC_POT_9_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=9) && defined(BMC_POT_9_X) && defined(BMC_POT_9_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 9

#if defined(BMC_POT_10_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=10) && defined(BMC_POT_10_X) && defined(BMC_POT_10_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 10

#if defined(BMC_POT_11_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=11) && defined(BMC_POT_11_X) && defined(BMC_POT_11_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 11

#if defined(BMC_POT_12_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=12) && defined(BMC_POT_12_X) && defined(BMC_POT_12_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 12

#if defined(BMC_POT_13_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=13) && defined(BMC_POT_13_X) && defined(BMC_POT_13_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 13

#if defined(BMC_POT_14_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=14) && defined(BMC_POT_14_X) && defined(BMC_POT_14_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 14

#if defined(BMC_POT_15_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=15) && defined(BMC_POT_15_X) && defined(BMC_POT_15_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 15

#if defined(BMC_POT_16_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=16) && defined(BMC_POT_16_X) && defined(BMC_POT_16_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 16

#if defined(BMC_POT_17_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=17) && defined(BMC_POT_17_X) && defined(BMC_POT_17_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 17

#if defined(BMC_POT_18_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=18) && defined(BMC_POT_18_X) && defined(BMC_POT_18_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 18

#if defined(BMC_POT_19_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=19) && defined(BMC_POT_19_X) && defined(BMC_POT_19_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 19

#if defined(BMC_POT_20_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=20) && defined(BMC_POT_20_X) && defined(BMC_POT_20_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 20

#if defined(BMC_POT_21_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=21) && defined(BMC_POT_21_X) && defined(BMC_POT_21_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 21

#if defined(BMC_POT_22_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=22) && defined(BMC_POT_22_X) && defined(BMC_POT_22_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 22

#if defined(BMC_POT_23_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=23) && defined(BMC_POT_23_X) && defined(BMC_POT_23_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 23

#if defined(BMC_POT_24_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=24) && defined(BMC_POT_24_X) && defined(BMC_POT_24_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 24

#if defined(BMC_POT_25_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=25) && defined(BMC_POT_25_X) && defined(BMC_POT_25_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 25

#if defined(BMC_POT_26_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=26) && defined(BMC_POT_26_X) && defined(BMC_POT_26_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 26

#if defined(BMC_POT_27_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=27) && defined(BMC_POT_27_X) && defined(BMC_POT_27_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 27

#if defined(BMC_POT_28_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=28) && defined(BMC_POT_28_X) && defined(BMC_POT_28_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 28

#if defined(BMC_POT_29_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=29) && defined(BMC_POT_29_X) && defined(BMC_POT_29_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 29

#if defined(BMC_POT_30_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=30) && defined(BMC_POT_30_X) && defined(BMC_POT_30_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 30

#if defined(BMC_POT_31_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=31) && defined(BMC_POT_31_X) && defined(BMC_POT_31_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 31

#if defined(BMC_POT_32_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=32) && defined(BMC_POT_32_X) && defined(BMC_POT_32_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 32

#if defined(BMC_POT_33_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=33) && defined(BMC_POT_33_X) && defined(BMC_POT_33_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 33

#if defined(BMC_POT_34_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=34) && defined(BMC_POT_34_X) && defined(BMC_POT_34_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 34

#if defined(BMC_POT_35_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=35) && defined(BMC_POT_35_X) && defined(BMC_POT_35_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 35

#if defined(BMC_POT_36_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=36) && defined(BMC_POT_36_X) && defined(BMC_POT_36_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 36

#if defined(BMC_POT_37_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=37) && defined(BMC_POT_37_X) && defined(BMC_POT_37_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 37

#if defined(BMC_POT_38_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=38) && defined(BMC_POT_38_X) && defined(BMC_POT_38_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 38

#if defined(BMC_POT_39_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=39) && defined(BMC_POT_39_X) && defined(BMC_POT_39_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 39

#if defined(BMC_POT_40_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=40) && defined(BMC_POT_40_X) && defined(BMC_POT_40_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 40

#if defined(BMC_POT_41_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=41) && defined(BMC_POT_41_X) && defined(BMC_POT_41_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 41

#if defined(BMC_POT_42_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=42) && defined(BMC_POT_42_X) && defined(BMC_POT_42_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 42

#if defined(BMC_POT_43_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=43) && defined(BMC_POT_43_X) && defined(BMC_POT_43_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 43

#if defined(BMC_POT_44_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=44) && defined(BMC_POT_44_X) && defined(BMC_POT_44_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 44

#if defined(BMC_POT_45_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=45) && defined(BMC_POT_45_X) && defined(BMC_POT_45_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 45

#if defined(BMC_POT_46_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=46) && defined(BMC_POT_46_X) && defined(BMC_POT_46_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 46

#if defined(BMC_POT_47_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=47) && defined(BMC_POT_47_X) && defined(BMC_POT_47_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 47

#if defined(BMC_POT_48_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=48) && defined(BMC_POT_48_X) && defined(BMC_POT_48_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 48

#if defined(BMC_POT_49_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=49) && defined(BMC_POT_49_X) && defined(BMC_POT_49_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 49

#if defined(BMC_POT_50_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=50) && defined(BMC_POT_50_X) && defined(BMC_POT_50_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 50

#if defined(BMC_POT_51_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=51) && defined(BMC_POT_51_X) && defined(BMC_POT_51_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 51

#if defined(BMC_POT_52_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=52) && defined(BMC_POT_52_X) && defined(BMC_POT_52_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 52

#if defined(BMC_POT_53_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=53) && defined(BMC_POT_53_X) && defined(BMC_POT_53_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 53

#if defined(BMC_POT_54_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=54) && defined(BMC_POT_54_X) && defined(BMC_POT_54_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 54

#if defined(BMC_POT_55_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=55) && defined(BMC_POT_55_X) && defined(BMC_POT_55_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 55

#if defined(BMC_POT_56_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=56) && defined(BMC_POT_56_X) && defined(BMC_POT_56_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 56

#if defined(BMC_POT_57_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=57) && defined(BMC_POT_57_X) && defined(BMC_POT_57_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 57

#if defined(BMC_POT_58_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=58) && defined(BMC_POT_58_X) && defined(BMC_POT_58_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 58

#if defined(BMC_POT_59_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=59) && defined(BMC_POT_59_X) && defined(BMC_POT_59_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 59

#if defined(BMC_POT_60_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=60) && defined(BMC_POT_60_X) && defined(BMC_POT_60_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 60

#if defined(BMC_POT_61_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=61) && defined(BMC_POT_61_X) && defined(BMC_POT_61_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 61

#if defined(BMC_POT_62_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=62) && defined(BMC_POT_62_X) && defined(BMC_POT_62_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 62

#if defined(BMC_POT_63_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=63) && defined(BMC_POT_63_X) && defined(BMC_POT_63_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 63

#if defined(BMC_POT_64_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=64) && defined(BMC_POT_64_X) && defined(BMC_POT_64_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 64

#if defined(BMC_POT_65_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=65) && defined(BMC_POT_65_X) && defined(BMC_POT_65_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 65

#if defined(BMC_POT_66_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=66) && defined(BMC_POT_66_X) && defined(BMC_POT_66_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 66

#if defined(BMC_POT_67_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=67) && defined(BMC_POT_67_X) && defined(BMC_POT_67_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 67

#if defined(BMC_POT_68_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=68) && defined(BMC_POT_68_X) && defined(BMC_POT_68_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 68

#if defined(BMC_POT_69_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=69) && defined(BMC_POT_69_X) && defined(BMC_POT_69_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 69

#if defined(BMC_POT_70_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=70) && defined(BMC_POT_70_X) && defined(BMC_POT_70_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 70

#if defined(BMC_POT_71_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=71) && defined(BMC_POT_71_X) && defined(BMC_POT_71_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 71

#if defined(BMC_POT_72_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=72) && defined(BMC_POT_72_X) && defined(BMC_POT_72_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 72

#if defined(BMC_POT_73_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=73) && defined(BMC_POT_73_X) && defined(BMC_POT_73_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 73

#if defined(BMC_POT_74_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=74) && defined(BMC_POT_74_X) && defined(BMC_POT_74_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 74

#if defined(BMC_POT_75_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=75) && defined(BMC_POT_75_X) && defined(BMC_POT_75_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 75

#if defined(BMC_POT_76_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=76) && defined(BMC_POT_76_X) && defined(BMC_POT_76_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 76

#if defined(BMC_POT_77_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=77) && defined(BMC_POT_77_X) && defined(BMC_POT_77_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 77

#if defined(BMC_POT_78_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=78) && defined(BMC_POT_78_X) && defined(BMC_POT_78_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 78

#if defined(BMC_POT_79_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=79) && defined(BMC_POT_79_X) && defined(BMC_POT_79_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 79

#if defined(BMC_POT_80_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=80) && defined(BMC_POT_80_X) && defined(BMC_POT_80_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 80

#if defined(BMC_POT_81_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=81) && defined(BMC_POT_81_X) && defined(BMC_POT_81_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 81

#if defined(BMC_POT_82_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=82) && defined(BMC_POT_82_X) && defined(BMC_POT_82_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 82

#if defined(BMC_POT_83_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=83) && defined(BMC_POT_83_X) && defined(BMC_POT_83_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 83

#if defined(BMC_POT_84_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=84) && defined(BMC_POT_84_X) && defined(BMC_POT_84_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 84

#if defined(BMC_POT_85_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=85) && defined(BMC_POT_85_X) && defined(BMC_POT_85_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 85

#if defined(BMC_POT_86_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=86) && defined(BMC_POT_86_X) && defined(BMC_POT_86_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 86

#if defined(BMC_POT_87_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=87) && defined(BMC_POT_87_X) && defined(BMC_POT_87_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 87

#if defined(BMC_POT_88_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=88) && defined(BMC_POT_88_X) && defined(BMC_POT_88_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 88

#if defined(BMC_POT_89_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=89) && defined(BMC_POT_89_X) && defined(BMC_POT_89_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 89

#if defined(BMC_POT_90_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=90) && defined(BMC_POT_90_X) && defined(BMC_POT_90_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 90

#if defined(BMC_POT_91_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=91) && defined(BMC_POT_91_X) && defined(BMC_POT_91_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 91

#if defined(BMC_POT_92_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=92) && defined(BMC_POT_92_X) && defined(BMC_POT_92_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 92

#if defined(BMC_POT_93_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=93) && defined(BMC_POT_93_X) && defined(BMC_POT_93_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 93

#if defined(BMC_POT_94_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=94) && defined(BMC_POT_94_X) && defined(BMC_POT_94_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 94

#if defined(BMC_POT_95_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=95) && defined(BMC_POT_95_X) && defined(BMC_POT_95_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 95

#if defined(BMC_POT_96_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=96) && defined(BMC_POT_96_X) && defined(BMC_POT_96_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 96

#if defined(BMC_POT_97_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=97) && defined(BMC_POT_97_X) && defined(BMC_POT_97_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 97

#if defined(BMC_POT_98_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=98) && defined(BMC_POT_98_X) && defined(BMC_POT_98_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 98

#if defined(BMC_POT_99_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=99) && defined(BMC_POT_99_X) && defined(BMC_POT_99_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 99

#if defined(BMC_POT_100_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=100) && defined(BMC_POT_100_X) && defined(BMC_POT_100_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 100

#if defined(BMC_POT_101_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=101) && defined(BMC_POT_101_X) && defined(BMC_POT_101_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 101

#if defined(BMC_POT_102_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=102) && defined(BMC_POT_102_X) && defined(BMC_POT_102_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 102

#if defined(BMC_POT_103_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=103) && defined(BMC_POT_103_X) && defined(BMC_POT_103_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 103

#if defined(BMC_POT_104_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=104) && defined(BMC_POT_104_X) && defined(BMC_POT_104_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 104

#if defined(BMC_POT_105_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=105) && defined(BMC_POT_105_X) && defined(BMC_POT_105_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 105

#if defined(BMC_POT_106_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=106) && defined(BMC_POT_106_X) && defined(BMC_POT_106_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 106

#if defined(BMC_POT_107_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=107) && defined(BMC_POT_107_X) && defined(BMC_POT_107_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 107

#if defined(BMC_POT_108_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=108) && defined(BMC_POT_108_X) && defined(BMC_POT_108_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 108

#if defined(BMC_POT_109_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=109) && defined(BMC_POT_109_X) && defined(BMC_POT_109_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 109

#if defined(BMC_POT_110_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=110) && defined(BMC_POT_110_X) && defined(BMC_POT_110_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 110

#if defined(BMC_POT_111_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=111) && defined(BMC_POT_111_X) && defined(BMC_POT_111_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 111

#if defined(BMC_POT_112_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=112) && defined(BMC_POT_112_X) && defined(BMC_POT_112_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 112

#if defined(BMC_POT_113_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=113) && defined(BMC_POT_113_X) && defined(BMC_POT_113_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 113

#if defined(BMC_POT_114_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=114) && defined(BMC_POT_114_X) && defined(BMC_POT_114_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 114

#if defined(BMC_POT_115_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=115) && defined(BMC_POT_115_X) && defined(BMC_POT_115_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 115

#if defined(BMC_POT_116_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=116) && defined(BMC_POT_116_X) && defined(BMC_POT_116_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 116

#if defined(BMC_POT_117_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=117) && defined(BMC_POT_117_X) && defined(BMC_POT_117_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 117

#if defined(BMC_POT_118_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=118) && defined(BMC_POT_118_X) && defined(BMC_POT_118_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 118

#if defined(BMC_POT_119_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=119) && defined(BMC_POT_119_X) && defined(BMC_POT_119_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 119

#if defined(BMC_POT_120_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=120) && defined(BMC_POT_120_X) && defined(BMC_POT_120_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 120

#if defined(BMC_POT_121_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=121) && defined(BMC_POT_121_X) && defined(BMC_POT_121_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 121

#if defined(BMC_POT_122_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=122) && defined(BMC_POT_122_X) && defined(BMC_POT_122_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 122

#if defined(BMC_POT_123_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=123) && defined(BMC_POT_123_X) && defined(BMC_POT_123_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 123

#if defined(BMC_POT_124_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=124) && defined(BMC_POT_124_X) && defined(BMC_POT_124_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 124

#if defined(BMC_POT_125_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=125) && defined(BMC_POT_125_X) && defined(BMC_POT_125_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 125

#if defined(BMC_POT_126_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=126) && defined(BMC_POT_126_X) && defined(BMC_POT_126_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 126

#if defined(BMC_POT_127_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG>=127) && defined(BMC_POT_127_X) && defined(BMC_POT_127_Y)
#ifdef BMC_MAX_POTS
#undef BMC_MAX_POTS
#endif
#define BMC_MAX_POTS 127

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 0
#if defined(BMC_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_ENCODER_1B_PIN) && defined(BMC_ENCODER_1_X) && defined(BMC_ENCODER_1_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 1

#if defined(BMC_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_ENCODER_2B_PIN) && defined(BMC_ENCODER_2_X) && defined(BMC_ENCODER_2_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 2

#if defined(BMC_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_ENCODER_3B_PIN) && defined(BMC_ENCODER_3_X) && defined(BMC_ENCODER_3_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 3

#if defined(BMC_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_ENCODER_4B_PIN) && defined(BMC_ENCODER_4_X) && defined(BMC_ENCODER_4_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 4

#if defined(BMC_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_ENCODER_5B_PIN) && defined(BMC_ENCODER_5_X) && defined(BMC_ENCODER_5_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 5

#if defined(BMC_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_ENCODER_6B_PIN) && defined(BMC_ENCODER_6_X) && defined(BMC_ENCODER_6_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 6

#if defined(BMC_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_ENCODER_7B_PIN) && defined(BMC_ENCODER_7_X) && defined(BMC_ENCODER_7_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 7

#if defined(BMC_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_ENCODER_8B_PIN) && defined(BMC_ENCODER_8_X) && defined(BMC_ENCODER_8_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 8

#if defined(BMC_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_ENCODER_9B_PIN) && defined(BMC_ENCODER_9_X) && defined(BMC_ENCODER_9_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 9

#if defined(BMC_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_ENCODER_10B_PIN) && defined(BMC_ENCODER_10_X) && defined(BMC_ENCODER_10_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 10

#if defined(BMC_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_ENCODER_11B_PIN) && defined(BMC_ENCODER_11_X) && defined(BMC_ENCODER_11_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 11

#if defined(BMC_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_ENCODER_12B_PIN) && defined(BMC_ENCODER_12_X) && defined(BMC_ENCODER_12_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 12

#if defined(BMC_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_ENCODER_13B_PIN) && defined(BMC_ENCODER_13_X) && defined(BMC_ENCODER_13_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 13

#if defined(BMC_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_ENCODER_14B_PIN) && defined(BMC_ENCODER_14_X) && defined(BMC_ENCODER_14_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 14

#if defined(BMC_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_ENCODER_15B_PIN) && defined(BMC_ENCODER_15_X) && defined(BMC_ENCODER_15_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 15

#if defined(BMC_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_ENCODER_16B_PIN) && defined(BMC_ENCODER_16_X) && defined(BMC_ENCODER_16_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 16

#if defined(BMC_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_ENCODER_17B_PIN) && defined(BMC_ENCODER_17_X) && defined(BMC_ENCODER_17_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 17

#if defined(BMC_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_ENCODER_18B_PIN) && defined(BMC_ENCODER_18_X) && defined(BMC_ENCODER_18_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 18

#if defined(BMC_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_ENCODER_19B_PIN) && defined(BMC_ENCODER_19_X) && defined(BMC_ENCODER_19_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 19

#if defined(BMC_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_ENCODER_20B_PIN) && defined(BMC_ENCODER_20_X) && defined(BMC_ENCODER_20_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 20

#if defined(BMC_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_ENCODER_21B_PIN) && defined(BMC_ENCODER_21_X) && defined(BMC_ENCODER_21_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 21

#if defined(BMC_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_ENCODER_22B_PIN) && defined(BMC_ENCODER_22_X) && defined(BMC_ENCODER_22_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 22

#if defined(BMC_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_ENCODER_23B_PIN) && defined(BMC_ENCODER_23_X) && defined(BMC_ENCODER_23_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 23

#if defined(BMC_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_ENCODER_24B_PIN) && defined(BMC_ENCODER_24_X) && defined(BMC_ENCODER_24_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 24

#if defined(BMC_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_ENCODER_25B_PIN) && defined(BMC_ENCODER_25_X) && defined(BMC_ENCODER_25_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 25

#if defined(BMC_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_ENCODER_26B_PIN) && defined(BMC_ENCODER_26_X) && defined(BMC_ENCODER_26_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 26

#if defined(BMC_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_ENCODER_27B_PIN) && defined(BMC_ENCODER_27_X) && defined(BMC_ENCODER_27_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 27

#if defined(BMC_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_ENCODER_28B_PIN) && defined(BMC_ENCODER_28_X) && defined(BMC_ENCODER_28_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 28

#if defined(BMC_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_ENCODER_29B_PIN) && defined(BMC_ENCODER_29_X) && defined(BMC_ENCODER_29_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 29

#if defined(BMC_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_ENCODER_30B_PIN) && defined(BMC_ENCODER_30_X) && defined(BMC_ENCODER_30_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 30

#if defined(BMC_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_ENCODER_31B_PIN) && defined(BMC_ENCODER_31_X) && defined(BMC_ENCODER_31_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 31

#if defined(BMC_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_ENCODER_32B_PIN) && defined(BMC_ENCODER_32_X) && defined(BMC_ENCODER_32_Y)
#ifdef BMC_MAX_ENCODERS
#undef BMC_MAX_ENCODERS
#endif
#define BMC_MAX_ENCODERS 32

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 0
#if defined(BMC_GLOBAL_LED_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && defined(BMC_GLOBAL_LED_1_X) && defined(BMC_GLOBAL_LED_1_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 1

#if defined(BMC_GLOBAL_LED_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_GLOBAL_LED_2_X) && defined(BMC_GLOBAL_LED_2_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 2

#if defined(BMC_GLOBAL_LED_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && defined(BMC_GLOBAL_LED_3_X) && defined(BMC_GLOBAL_LED_3_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 3

#if defined(BMC_GLOBAL_LED_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_GLOBAL_LED_4_X) && defined(BMC_GLOBAL_LED_4_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 4

#if defined(BMC_GLOBAL_LED_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && defined(BMC_GLOBAL_LED_5_X) && defined(BMC_GLOBAL_LED_5_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 5

#if defined(BMC_GLOBAL_LED_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_GLOBAL_LED_6_X) && defined(BMC_GLOBAL_LED_6_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 6

#if defined(BMC_GLOBAL_LED_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && defined(BMC_GLOBAL_LED_7_X) && defined(BMC_GLOBAL_LED_7_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 7

#if defined(BMC_GLOBAL_LED_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_GLOBAL_LED_8_X) && defined(BMC_GLOBAL_LED_8_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 8

#if defined(BMC_GLOBAL_LED_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && defined(BMC_GLOBAL_LED_9_X) && defined(BMC_GLOBAL_LED_9_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 9

#if defined(BMC_GLOBAL_LED_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_GLOBAL_LED_10_X) && defined(BMC_GLOBAL_LED_10_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 10

#if defined(BMC_GLOBAL_LED_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && defined(BMC_GLOBAL_LED_11_X) && defined(BMC_GLOBAL_LED_11_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 11

#if defined(BMC_GLOBAL_LED_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_GLOBAL_LED_12_X) && defined(BMC_GLOBAL_LED_12_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 12

#if defined(BMC_GLOBAL_LED_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && defined(BMC_GLOBAL_LED_13_X) && defined(BMC_GLOBAL_LED_13_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 13

#if defined(BMC_GLOBAL_LED_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_GLOBAL_LED_14_X) && defined(BMC_GLOBAL_LED_14_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 14

#if defined(BMC_GLOBAL_LED_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && defined(BMC_GLOBAL_LED_15_X) && defined(BMC_GLOBAL_LED_15_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 15

#if defined(BMC_GLOBAL_LED_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_GLOBAL_LED_16_X) && defined(BMC_GLOBAL_LED_16_Y)
#ifdef BMC_MAX_GLOBAL_LEDS
#undef BMC_MAX_GLOBAL_LEDS
#endif
#define BMC_MAX_GLOBAL_LEDS 16

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 0
#if defined(BMC_GLOBAL_BUTTON_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && defined(BMC_GLOBAL_BUTTON_1_X) && defined(BMC_GLOBAL_BUTTON_1_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 1

#if defined(BMC_GLOBAL_BUTTON_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_GLOBAL_BUTTON_2_X) && defined(BMC_GLOBAL_BUTTON_2_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 2

#if defined(BMC_GLOBAL_BUTTON_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && defined(BMC_GLOBAL_BUTTON_3_X) && defined(BMC_GLOBAL_BUTTON_3_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 3

#if defined(BMC_GLOBAL_BUTTON_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_GLOBAL_BUTTON_4_X) && defined(BMC_GLOBAL_BUTTON_4_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 4

#if defined(BMC_GLOBAL_BUTTON_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && defined(BMC_GLOBAL_BUTTON_5_X) && defined(BMC_GLOBAL_BUTTON_5_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 5

#if defined(BMC_GLOBAL_BUTTON_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_GLOBAL_BUTTON_6_X) && defined(BMC_GLOBAL_BUTTON_6_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 6

#if defined(BMC_GLOBAL_BUTTON_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && defined(BMC_GLOBAL_BUTTON_7_X) && defined(BMC_GLOBAL_BUTTON_7_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 7

#if defined(BMC_GLOBAL_BUTTON_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_GLOBAL_BUTTON_8_X) && defined(BMC_GLOBAL_BUTTON_8_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 8

#if defined(BMC_GLOBAL_BUTTON_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && defined(BMC_GLOBAL_BUTTON_9_X) && defined(BMC_GLOBAL_BUTTON_9_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 9

#if defined(BMC_GLOBAL_BUTTON_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_GLOBAL_BUTTON_10_X) && defined(BMC_GLOBAL_BUTTON_10_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 10

#if defined(BMC_GLOBAL_BUTTON_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && defined(BMC_GLOBAL_BUTTON_11_X) && defined(BMC_GLOBAL_BUTTON_11_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 11

#if defined(BMC_GLOBAL_BUTTON_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_GLOBAL_BUTTON_12_X) && defined(BMC_GLOBAL_BUTTON_12_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 12

#if defined(BMC_GLOBAL_BUTTON_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && defined(BMC_GLOBAL_BUTTON_13_X) && defined(BMC_GLOBAL_BUTTON_13_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 13

#if defined(BMC_GLOBAL_BUTTON_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_GLOBAL_BUTTON_14_X) && defined(BMC_GLOBAL_BUTTON_14_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 14

#if defined(BMC_GLOBAL_BUTTON_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && defined(BMC_GLOBAL_BUTTON_15_X) && defined(BMC_GLOBAL_BUTTON_15_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 15

#if defined(BMC_GLOBAL_BUTTON_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_GLOBAL_BUTTON_16_X) && defined(BMC_GLOBAL_BUTTON_16_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 16

#if defined(BMC_GLOBAL_BUTTON_17_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && defined(BMC_GLOBAL_BUTTON_17_X) && defined(BMC_GLOBAL_BUTTON_17_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 17

#if defined(BMC_GLOBAL_BUTTON_18_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && defined(BMC_GLOBAL_BUTTON_18_X) && defined(BMC_GLOBAL_BUTTON_18_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 18

#if defined(BMC_GLOBAL_BUTTON_19_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && defined(BMC_GLOBAL_BUTTON_19_X) && defined(BMC_GLOBAL_BUTTON_19_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 19

#if defined(BMC_GLOBAL_BUTTON_20_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && defined(BMC_GLOBAL_BUTTON_20_X) && defined(BMC_GLOBAL_BUTTON_20_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 20

#if defined(BMC_GLOBAL_BUTTON_21_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && defined(BMC_GLOBAL_BUTTON_21_X) && defined(BMC_GLOBAL_BUTTON_21_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 21

#if defined(BMC_GLOBAL_BUTTON_22_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && defined(BMC_GLOBAL_BUTTON_22_X) && defined(BMC_GLOBAL_BUTTON_22_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 22

#if defined(BMC_GLOBAL_BUTTON_23_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && defined(BMC_GLOBAL_BUTTON_23_X) && defined(BMC_GLOBAL_BUTTON_23_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 23

#if defined(BMC_GLOBAL_BUTTON_24_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && defined(BMC_GLOBAL_BUTTON_24_X) && defined(BMC_GLOBAL_BUTTON_24_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 24

#if defined(BMC_GLOBAL_BUTTON_25_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && defined(BMC_GLOBAL_BUTTON_25_X) && defined(BMC_GLOBAL_BUTTON_25_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 25

#if defined(BMC_GLOBAL_BUTTON_26_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && defined(BMC_GLOBAL_BUTTON_26_X) && defined(BMC_GLOBAL_BUTTON_26_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 26

#if defined(BMC_GLOBAL_BUTTON_27_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && defined(BMC_GLOBAL_BUTTON_27_X) && defined(BMC_GLOBAL_BUTTON_27_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 27

#if defined(BMC_GLOBAL_BUTTON_28_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && defined(BMC_GLOBAL_BUTTON_28_X) && defined(BMC_GLOBAL_BUTTON_28_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 28

#if defined(BMC_GLOBAL_BUTTON_29_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && defined(BMC_GLOBAL_BUTTON_29_X) && defined(BMC_GLOBAL_BUTTON_29_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 29

#if defined(BMC_GLOBAL_BUTTON_30_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && defined(BMC_GLOBAL_BUTTON_30_X) && defined(BMC_GLOBAL_BUTTON_30_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 30

#if defined(BMC_GLOBAL_BUTTON_31_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && defined(BMC_GLOBAL_BUTTON_31_X) && defined(BMC_GLOBAL_BUTTON_31_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 31

#if defined(BMC_GLOBAL_BUTTON_32_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && defined(BMC_GLOBAL_BUTTON_32_X) && defined(BMC_GLOBAL_BUTTON_32_Y)
#ifdef BMC_MAX_GLOBAL_BUTTONS
#undef BMC_MAX_GLOBAL_BUTTONS
#endif
#define BMC_MAX_GLOBAL_BUTTONS 32

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 0
#if defined(BMC_GLOBAL_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_GLOBAL_ENCODER_1B_PIN) && defined(BMC_GLOBAL_ENCODER_1_X) && defined(BMC_GLOBAL_ENCODER_1_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 1

#if defined(BMC_GLOBAL_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_GLOBAL_ENCODER_2B_PIN) && defined(BMC_GLOBAL_ENCODER_2_X) && defined(BMC_GLOBAL_ENCODER_2_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 2

#if defined(BMC_GLOBAL_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_GLOBAL_ENCODER_3B_PIN) && defined(BMC_GLOBAL_ENCODER_3_X) && defined(BMC_GLOBAL_ENCODER_3_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 3

#if defined(BMC_GLOBAL_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_GLOBAL_ENCODER_4B_PIN) && defined(BMC_GLOBAL_ENCODER_4_X) && defined(BMC_GLOBAL_ENCODER_4_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 4

#if defined(BMC_GLOBAL_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_GLOBAL_ENCODER_5B_PIN) && defined(BMC_GLOBAL_ENCODER_5_X) && defined(BMC_GLOBAL_ENCODER_5_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 5

#if defined(BMC_GLOBAL_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_GLOBAL_ENCODER_6B_PIN) && defined(BMC_GLOBAL_ENCODER_6_X) && defined(BMC_GLOBAL_ENCODER_6_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 6

#if defined(BMC_GLOBAL_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_GLOBAL_ENCODER_7B_PIN) && defined(BMC_GLOBAL_ENCODER_7_X) && defined(BMC_GLOBAL_ENCODER_7_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 7

#if defined(BMC_GLOBAL_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_GLOBAL_ENCODER_8B_PIN) && defined(BMC_GLOBAL_ENCODER_8_X) && defined(BMC_GLOBAL_ENCODER_8_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 8

#if defined(BMC_GLOBAL_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_GLOBAL_ENCODER_9B_PIN) && defined(BMC_GLOBAL_ENCODER_9_X) && defined(BMC_GLOBAL_ENCODER_9_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 9

#if defined(BMC_GLOBAL_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_GLOBAL_ENCODER_10B_PIN) && defined(BMC_GLOBAL_ENCODER_10_X) && defined(BMC_GLOBAL_ENCODER_10_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 10

#if defined(BMC_GLOBAL_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_GLOBAL_ENCODER_11B_PIN) && defined(BMC_GLOBAL_ENCODER_11_X) && defined(BMC_GLOBAL_ENCODER_11_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 11

#if defined(BMC_GLOBAL_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_GLOBAL_ENCODER_12B_PIN) && defined(BMC_GLOBAL_ENCODER_12_X) && defined(BMC_GLOBAL_ENCODER_12_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 12

#if defined(BMC_GLOBAL_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_GLOBAL_ENCODER_13B_PIN) && defined(BMC_GLOBAL_ENCODER_13_X) && defined(BMC_GLOBAL_ENCODER_13_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 13

#if defined(BMC_GLOBAL_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_GLOBAL_ENCODER_14B_PIN) && defined(BMC_GLOBAL_ENCODER_14_X) && defined(BMC_GLOBAL_ENCODER_14_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 14

#if defined(BMC_GLOBAL_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_GLOBAL_ENCODER_15B_PIN) && defined(BMC_GLOBAL_ENCODER_15_X) && defined(BMC_GLOBAL_ENCODER_15_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 15

#if defined(BMC_GLOBAL_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_GLOBAL_ENCODER_16B_PIN) && defined(BMC_GLOBAL_ENCODER_16_X) && defined(BMC_GLOBAL_ENCODER_16_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 16

#if defined(BMC_GLOBAL_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_GLOBAL_ENCODER_17B_PIN) && defined(BMC_GLOBAL_ENCODER_17_X) && defined(BMC_GLOBAL_ENCODER_17_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 17

#if defined(BMC_GLOBAL_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_GLOBAL_ENCODER_18B_PIN) && defined(BMC_GLOBAL_ENCODER_18_X) && defined(BMC_GLOBAL_ENCODER_18_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 18

#if defined(BMC_GLOBAL_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_GLOBAL_ENCODER_19B_PIN) && defined(BMC_GLOBAL_ENCODER_19_X) && defined(BMC_GLOBAL_ENCODER_19_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 19

#if defined(BMC_GLOBAL_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_GLOBAL_ENCODER_20B_PIN) && defined(BMC_GLOBAL_ENCODER_20_X) && defined(BMC_GLOBAL_ENCODER_20_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 20

#if defined(BMC_GLOBAL_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_GLOBAL_ENCODER_21B_PIN) && defined(BMC_GLOBAL_ENCODER_21_X) && defined(BMC_GLOBAL_ENCODER_21_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 21

#if defined(BMC_GLOBAL_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_GLOBAL_ENCODER_22B_PIN) && defined(BMC_GLOBAL_ENCODER_22_X) && defined(BMC_GLOBAL_ENCODER_22_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 22

#if defined(BMC_GLOBAL_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_GLOBAL_ENCODER_23B_PIN) && defined(BMC_GLOBAL_ENCODER_23_X) && defined(BMC_GLOBAL_ENCODER_23_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 23

#if defined(BMC_GLOBAL_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_GLOBAL_ENCODER_24B_PIN) && defined(BMC_GLOBAL_ENCODER_24_X) && defined(BMC_GLOBAL_ENCODER_24_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 24

#if defined(BMC_GLOBAL_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_GLOBAL_ENCODER_25B_PIN) && defined(BMC_GLOBAL_ENCODER_25_X) && defined(BMC_GLOBAL_ENCODER_25_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 25

#if defined(BMC_GLOBAL_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_GLOBAL_ENCODER_26B_PIN) && defined(BMC_GLOBAL_ENCODER_26_X) && defined(BMC_GLOBAL_ENCODER_26_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 26

#if defined(BMC_GLOBAL_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_GLOBAL_ENCODER_27B_PIN) && defined(BMC_GLOBAL_ENCODER_27_X) && defined(BMC_GLOBAL_ENCODER_27_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 27

#if defined(BMC_GLOBAL_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_GLOBAL_ENCODER_28B_PIN) && defined(BMC_GLOBAL_ENCODER_28_X) && defined(BMC_GLOBAL_ENCODER_28_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 28

#if defined(BMC_GLOBAL_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_GLOBAL_ENCODER_29B_PIN) && defined(BMC_GLOBAL_ENCODER_29_X) && defined(BMC_GLOBAL_ENCODER_29_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 29

#if defined(BMC_GLOBAL_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_GLOBAL_ENCODER_30B_PIN) && defined(BMC_GLOBAL_ENCODER_30_X) && defined(BMC_GLOBAL_ENCODER_30_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 30

#if defined(BMC_GLOBAL_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_GLOBAL_ENCODER_31B_PIN) && defined(BMC_GLOBAL_ENCODER_31_X) && defined(BMC_GLOBAL_ENCODER_31_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 31

#if defined(BMC_GLOBAL_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_GLOBAL_ENCODER_32B_PIN) && defined(BMC_GLOBAL_ENCODER_32_X) && defined(BMC_GLOBAL_ENCODER_32_Y)
#ifdef BMC_MAX_GLOBAL_ENCODERS
#undef BMC_MAX_GLOBAL_ENCODERS
#endif
#define BMC_MAX_GLOBAL_ENCODERS 32

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 0
#if defined(BMC_GLOBAL_POT_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && defined(BMC_GLOBAL_POT_1_X) && defined(BMC_GLOBAL_POT_1_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 1

#if defined(BMC_GLOBAL_POT_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_GLOBAL_POT_2_X) && defined(BMC_GLOBAL_POT_2_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 2

#if defined(BMC_GLOBAL_POT_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && defined(BMC_GLOBAL_POT_3_X) && defined(BMC_GLOBAL_POT_3_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 3

#if defined(BMC_GLOBAL_POT_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_GLOBAL_POT_4_X) && defined(BMC_GLOBAL_POT_4_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 4

#if defined(BMC_GLOBAL_POT_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && defined(BMC_GLOBAL_POT_5_X) && defined(BMC_GLOBAL_POT_5_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 5

#if defined(BMC_GLOBAL_POT_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_GLOBAL_POT_6_X) && defined(BMC_GLOBAL_POT_6_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 6

#if defined(BMC_GLOBAL_POT_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && defined(BMC_GLOBAL_POT_7_X) && defined(BMC_GLOBAL_POT_7_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 7

#if defined(BMC_GLOBAL_POT_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_GLOBAL_POT_8_X) && defined(BMC_GLOBAL_POT_8_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 8

#if defined(BMC_GLOBAL_POT_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && defined(BMC_GLOBAL_POT_9_X) && defined(BMC_GLOBAL_POT_9_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 9

#if defined(BMC_GLOBAL_POT_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_GLOBAL_POT_10_X) && defined(BMC_GLOBAL_POT_10_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 10

#if defined(BMC_GLOBAL_POT_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && defined(BMC_GLOBAL_POT_11_X) && defined(BMC_GLOBAL_POT_11_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 11

#if defined(BMC_GLOBAL_POT_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_GLOBAL_POT_12_X) && defined(BMC_GLOBAL_POT_12_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 12

#if defined(BMC_GLOBAL_POT_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && defined(BMC_GLOBAL_POT_13_X) && defined(BMC_GLOBAL_POT_13_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 13

#if defined(BMC_GLOBAL_POT_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_GLOBAL_POT_14_X) && defined(BMC_GLOBAL_POT_14_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 14

#if defined(BMC_GLOBAL_POT_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && defined(BMC_GLOBAL_POT_15_X) && defined(BMC_GLOBAL_POT_15_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 15

#if defined(BMC_GLOBAL_POT_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_GLOBAL_POT_16_X) && defined(BMC_GLOBAL_POT_16_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 16

#if defined(BMC_GLOBAL_POT_17_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && defined(BMC_GLOBAL_POT_17_X) && defined(BMC_GLOBAL_POT_17_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 17

#if defined(BMC_GLOBAL_POT_18_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && defined(BMC_GLOBAL_POT_18_X) && defined(BMC_GLOBAL_POT_18_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 18

#if defined(BMC_GLOBAL_POT_19_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && defined(BMC_GLOBAL_POT_19_X) && defined(BMC_GLOBAL_POT_19_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 19

#if defined(BMC_GLOBAL_POT_20_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && defined(BMC_GLOBAL_POT_20_X) && defined(BMC_GLOBAL_POT_20_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 20

#if defined(BMC_GLOBAL_POT_21_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && defined(BMC_GLOBAL_POT_21_X) && defined(BMC_GLOBAL_POT_21_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 21

#if defined(BMC_GLOBAL_POT_22_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && defined(BMC_GLOBAL_POT_22_X) && defined(BMC_GLOBAL_POT_22_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 22

#if defined(BMC_GLOBAL_POT_23_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && defined(BMC_GLOBAL_POT_23_X) && defined(BMC_GLOBAL_POT_23_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 23

#if defined(BMC_GLOBAL_POT_24_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && defined(BMC_GLOBAL_POT_24_X) && defined(BMC_GLOBAL_POT_24_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 24

#if defined(BMC_GLOBAL_POT_25_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && defined(BMC_GLOBAL_POT_25_X) && defined(BMC_GLOBAL_POT_25_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 25

#if defined(BMC_GLOBAL_POT_26_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && defined(BMC_GLOBAL_POT_26_X) && defined(BMC_GLOBAL_POT_26_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 26

#if defined(BMC_GLOBAL_POT_27_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && defined(BMC_GLOBAL_POT_27_X) && defined(BMC_GLOBAL_POT_27_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 27

#if defined(BMC_GLOBAL_POT_28_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && defined(BMC_GLOBAL_POT_28_X) && defined(BMC_GLOBAL_POT_28_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 28

#if defined(BMC_GLOBAL_POT_29_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && defined(BMC_GLOBAL_POT_29_X) && defined(BMC_GLOBAL_POT_29_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 29

#if defined(BMC_GLOBAL_POT_30_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && defined(BMC_GLOBAL_POT_30_X) && defined(BMC_GLOBAL_POT_30_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 30

#if defined(BMC_GLOBAL_POT_31_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && defined(BMC_GLOBAL_POT_31_X) && defined(BMC_GLOBAL_POT_31_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 31

#if defined(BMC_GLOBAL_POT_32_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && defined(BMC_GLOBAL_POT_32_X) && defined(BMC_GLOBAL_POT_32_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 32

#if defined(BMC_GLOBAL_POT_33_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=33 && defined(BMC_GLOBAL_POT_33_X) && defined(BMC_GLOBAL_POT_33_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 33

#if defined(BMC_GLOBAL_POT_34_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=34 && defined(BMC_GLOBAL_POT_34_X) && defined(BMC_GLOBAL_POT_34_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 34

#if defined(BMC_GLOBAL_POT_35_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=35 && defined(BMC_GLOBAL_POT_35_X) && defined(BMC_GLOBAL_POT_35_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 35

#if defined(BMC_GLOBAL_POT_36_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=36 && defined(BMC_GLOBAL_POT_36_X) && defined(BMC_GLOBAL_POT_36_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 36

#if defined(BMC_GLOBAL_POT_37_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=37 && defined(BMC_GLOBAL_POT_37_X) && defined(BMC_GLOBAL_POT_37_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 37

#if defined(BMC_GLOBAL_POT_38_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=38 && defined(BMC_GLOBAL_POT_38_X) && defined(BMC_GLOBAL_POT_38_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 38

#if defined(BMC_GLOBAL_POT_39_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=39 && defined(BMC_GLOBAL_POT_39_X) && defined(BMC_GLOBAL_POT_39_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 39

#if defined(BMC_GLOBAL_POT_40_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=40 && defined(BMC_GLOBAL_POT_40_X) && defined(BMC_GLOBAL_POT_40_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 40

#if defined(BMC_GLOBAL_POT_41_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=41 && defined(BMC_GLOBAL_POT_41_X) && defined(BMC_GLOBAL_POT_41_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 41

#if defined(BMC_GLOBAL_POT_42_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=42 && defined(BMC_GLOBAL_POT_42_X) && defined(BMC_GLOBAL_POT_42_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 42

#if defined(BMC_GLOBAL_POT_43_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=43 && defined(BMC_GLOBAL_POT_43_X) && defined(BMC_GLOBAL_POT_43_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 43

#if defined(BMC_GLOBAL_POT_44_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=44 && defined(BMC_GLOBAL_POT_44_X) && defined(BMC_GLOBAL_POT_44_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 44

#if defined(BMC_GLOBAL_POT_45_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=45 && defined(BMC_GLOBAL_POT_45_X) && defined(BMC_GLOBAL_POT_45_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 45

#if defined(BMC_GLOBAL_POT_46_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=46 && defined(BMC_GLOBAL_POT_46_X) && defined(BMC_GLOBAL_POT_46_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 46

#if defined(BMC_GLOBAL_POT_47_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=47 && defined(BMC_GLOBAL_POT_47_X) && defined(BMC_GLOBAL_POT_47_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 47

#if defined(BMC_GLOBAL_POT_48_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=48 && defined(BMC_GLOBAL_POT_48_X) && defined(BMC_GLOBAL_POT_48_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 48

#if defined(BMC_GLOBAL_POT_49_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=49 && defined(BMC_GLOBAL_POT_49_X) && defined(BMC_GLOBAL_POT_49_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 49

#if defined(BMC_GLOBAL_POT_50_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=50 && defined(BMC_GLOBAL_POT_50_X) && defined(BMC_GLOBAL_POT_50_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 50

#if defined(BMC_GLOBAL_POT_51_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=51 && defined(BMC_GLOBAL_POT_51_X) && defined(BMC_GLOBAL_POT_51_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 51

#if defined(BMC_GLOBAL_POT_52_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=52 && defined(BMC_GLOBAL_POT_52_X) && defined(BMC_GLOBAL_POT_52_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 52

#if defined(BMC_GLOBAL_POT_53_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=53 && defined(BMC_GLOBAL_POT_53_X) && defined(BMC_GLOBAL_POT_53_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 53

#if defined(BMC_GLOBAL_POT_54_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=54 && defined(BMC_GLOBAL_POT_54_X) && defined(BMC_GLOBAL_POT_54_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 54

#if defined(BMC_GLOBAL_POT_55_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=55 && defined(BMC_GLOBAL_POT_55_X) && defined(BMC_GLOBAL_POT_55_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 55

#if defined(BMC_GLOBAL_POT_56_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=56 && defined(BMC_GLOBAL_POT_56_X) && defined(BMC_GLOBAL_POT_56_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 56

#if defined(BMC_GLOBAL_POT_57_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=57 && defined(BMC_GLOBAL_POT_57_X) && defined(BMC_GLOBAL_POT_57_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 57

#if defined(BMC_GLOBAL_POT_58_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=58 && defined(BMC_GLOBAL_POT_58_X) && defined(BMC_GLOBAL_POT_58_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 58

#if defined(BMC_GLOBAL_POT_59_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=59 && defined(BMC_GLOBAL_POT_59_X) && defined(BMC_GLOBAL_POT_59_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 59

#if defined(BMC_GLOBAL_POT_60_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=60 && defined(BMC_GLOBAL_POT_60_X) && defined(BMC_GLOBAL_POT_60_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 60

#if defined(BMC_GLOBAL_POT_61_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=61 && defined(BMC_GLOBAL_POT_61_X) && defined(BMC_GLOBAL_POT_61_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 61

#if defined(BMC_GLOBAL_POT_62_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=62 && defined(BMC_GLOBAL_POT_62_X) && defined(BMC_GLOBAL_POT_62_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 62

#if defined(BMC_GLOBAL_POT_63_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=63 && defined(BMC_GLOBAL_POT_63_X) && defined(BMC_GLOBAL_POT_63_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 63

#if defined(BMC_GLOBAL_POT_64_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=64 && defined(BMC_GLOBAL_POT_64_X) && defined(BMC_GLOBAL_POT_64_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 64

#if defined(BMC_GLOBAL_POT_65_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=65 && defined(BMC_GLOBAL_POT_65_X) && defined(BMC_GLOBAL_POT_65_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 65

#if defined(BMC_GLOBAL_POT_66_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=66 && defined(BMC_GLOBAL_POT_66_X) && defined(BMC_GLOBAL_POT_66_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 66

#if defined(BMC_GLOBAL_POT_67_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=67 && defined(BMC_GLOBAL_POT_67_X) && defined(BMC_GLOBAL_POT_67_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 67

#if defined(BMC_GLOBAL_POT_68_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=68 && defined(BMC_GLOBAL_POT_68_X) && defined(BMC_GLOBAL_POT_68_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 68

#if defined(BMC_GLOBAL_POT_69_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=69 && defined(BMC_GLOBAL_POT_69_X) && defined(BMC_GLOBAL_POT_69_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 69

#if defined(BMC_GLOBAL_POT_70_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=70 && defined(BMC_GLOBAL_POT_70_X) && defined(BMC_GLOBAL_POT_70_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 70

#if defined(BMC_GLOBAL_POT_71_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=71 && defined(BMC_GLOBAL_POT_71_X) && defined(BMC_GLOBAL_POT_71_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 71

#if defined(BMC_GLOBAL_POT_72_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=72 && defined(BMC_GLOBAL_POT_72_X) && defined(BMC_GLOBAL_POT_72_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 72

#if defined(BMC_GLOBAL_POT_73_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=73 && defined(BMC_GLOBAL_POT_73_X) && defined(BMC_GLOBAL_POT_73_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 73

#if defined(BMC_GLOBAL_POT_74_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=74 && defined(BMC_GLOBAL_POT_74_X) && defined(BMC_GLOBAL_POT_74_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 74

#if defined(BMC_GLOBAL_POT_75_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=75 && defined(BMC_GLOBAL_POT_75_X) && defined(BMC_GLOBAL_POT_75_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 75

#if defined(BMC_GLOBAL_POT_76_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=76 && defined(BMC_GLOBAL_POT_76_X) && defined(BMC_GLOBAL_POT_76_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 76

#if defined(BMC_GLOBAL_POT_77_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=77 && defined(BMC_GLOBAL_POT_77_X) && defined(BMC_GLOBAL_POT_77_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 77

#if defined(BMC_GLOBAL_POT_78_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=78 && defined(BMC_GLOBAL_POT_78_X) && defined(BMC_GLOBAL_POT_78_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 78

#if defined(BMC_GLOBAL_POT_79_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=79 && defined(BMC_GLOBAL_POT_79_X) && defined(BMC_GLOBAL_POT_79_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 79

#if defined(BMC_GLOBAL_POT_80_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=80 && defined(BMC_GLOBAL_POT_80_X) && defined(BMC_GLOBAL_POT_80_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 80

#if defined(BMC_GLOBAL_POT_81_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=81 && defined(BMC_GLOBAL_POT_81_X) && defined(BMC_GLOBAL_POT_81_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 81

#if defined(BMC_GLOBAL_POT_82_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=82 && defined(BMC_GLOBAL_POT_82_X) && defined(BMC_GLOBAL_POT_82_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 82

#if defined(BMC_GLOBAL_POT_83_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=83 && defined(BMC_GLOBAL_POT_83_X) && defined(BMC_GLOBAL_POT_83_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 83

#if defined(BMC_GLOBAL_POT_84_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=84 && defined(BMC_GLOBAL_POT_84_X) && defined(BMC_GLOBAL_POT_84_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 84

#if defined(BMC_GLOBAL_POT_85_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=85 && defined(BMC_GLOBAL_POT_85_X) && defined(BMC_GLOBAL_POT_85_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 85

#if defined(BMC_GLOBAL_POT_86_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=86 && defined(BMC_GLOBAL_POT_86_X) && defined(BMC_GLOBAL_POT_86_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 86

#if defined(BMC_GLOBAL_POT_87_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=87 && defined(BMC_GLOBAL_POT_87_X) && defined(BMC_GLOBAL_POT_87_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 87

#if defined(BMC_GLOBAL_POT_88_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=88 && defined(BMC_GLOBAL_POT_88_X) && defined(BMC_GLOBAL_POT_88_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 88

#if defined(BMC_GLOBAL_POT_89_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=89 && defined(BMC_GLOBAL_POT_89_X) && defined(BMC_GLOBAL_POT_89_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 89

#if defined(BMC_GLOBAL_POT_90_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=90 && defined(BMC_GLOBAL_POT_90_X) && defined(BMC_GLOBAL_POT_90_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 90

#if defined(BMC_GLOBAL_POT_91_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=91 && defined(BMC_GLOBAL_POT_91_X) && defined(BMC_GLOBAL_POT_91_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 91

#if defined(BMC_GLOBAL_POT_92_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=92 && defined(BMC_GLOBAL_POT_92_X) && defined(BMC_GLOBAL_POT_92_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 92

#if defined(BMC_GLOBAL_POT_93_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=93 && defined(BMC_GLOBAL_POT_93_X) && defined(BMC_GLOBAL_POT_93_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 93

#if defined(BMC_GLOBAL_POT_94_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=94 && defined(BMC_GLOBAL_POT_94_X) && defined(BMC_GLOBAL_POT_94_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 94

#if defined(BMC_GLOBAL_POT_95_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=95 && defined(BMC_GLOBAL_POT_95_X) && defined(BMC_GLOBAL_POT_95_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 95

#if defined(BMC_GLOBAL_POT_96_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=96 && defined(BMC_GLOBAL_POT_96_X) && defined(BMC_GLOBAL_POT_96_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 96

#if defined(BMC_GLOBAL_POT_97_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=97 && defined(BMC_GLOBAL_POT_97_X) && defined(BMC_GLOBAL_POT_97_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 97

#if defined(BMC_GLOBAL_POT_98_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=98 && defined(BMC_GLOBAL_POT_98_X) && defined(BMC_GLOBAL_POT_98_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 98

#if defined(BMC_GLOBAL_POT_99_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=99 && defined(BMC_GLOBAL_POT_99_X) && defined(BMC_GLOBAL_POT_99_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 99

#if defined(BMC_GLOBAL_POT_100_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=100 && defined(BMC_GLOBAL_POT_100_X) && defined(BMC_GLOBAL_POT_100_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 100

#if defined(BMC_GLOBAL_POT_101_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=101 && defined(BMC_GLOBAL_POT_101_X) && defined(BMC_GLOBAL_POT_101_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 101

#if defined(BMC_GLOBAL_POT_102_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=102 && defined(BMC_GLOBAL_POT_102_X) && defined(BMC_GLOBAL_POT_102_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 102

#if defined(BMC_GLOBAL_POT_103_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=103 && defined(BMC_GLOBAL_POT_103_X) && defined(BMC_GLOBAL_POT_103_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 103

#if defined(BMC_GLOBAL_POT_104_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=104 && defined(BMC_GLOBAL_POT_104_X) && defined(BMC_GLOBAL_POT_104_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 104

#if defined(BMC_GLOBAL_POT_105_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=105 && defined(BMC_GLOBAL_POT_105_X) && defined(BMC_GLOBAL_POT_105_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 105

#if defined(BMC_GLOBAL_POT_106_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=106 && defined(BMC_GLOBAL_POT_106_X) && defined(BMC_GLOBAL_POT_106_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 106

#if defined(BMC_GLOBAL_POT_107_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=107 && defined(BMC_GLOBAL_POT_107_X) && defined(BMC_GLOBAL_POT_107_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 107

#if defined(BMC_GLOBAL_POT_108_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=108 && defined(BMC_GLOBAL_POT_108_X) && defined(BMC_GLOBAL_POT_108_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 108

#if defined(BMC_GLOBAL_POT_109_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=109 && defined(BMC_GLOBAL_POT_109_X) && defined(BMC_GLOBAL_POT_109_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 109

#if defined(BMC_GLOBAL_POT_110_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=110 && defined(BMC_GLOBAL_POT_110_X) && defined(BMC_GLOBAL_POT_110_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 110

#if defined(BMC_GLOBAL_POT_111_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=111 && defined(BMC_GLOBAL_POT_111_X) && defined(BMC_GLOBAL_POT_111_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 111

#if defined(BMC_GLOBAL_POT_112_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=112 && defined(BMC_GLOBAL_POT_112_X) && defined(BMC_GLOBAL_POT_112_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 112

#if defined(BMC_GLOBAL_POT_113_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=113 && defined(BMC_GLOBAL_POT_113_X) && defined(BMC_GLOBAL_POT_113_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 113

#if defined(BMC_GLOBAL_POT_114_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=114 && defined(BMC_GLOBAL_POT_114_X) && defined(BMC_GLOBAL_POT_114_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 114

#if defined(BMC_GLOBAL_POT_115_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=115 && defined(BMC_GLOBAL_POT_115_X) && defined(BMC_GLOBAL_POT_115_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 115

#if defined(BMC_GLOBAL_POT_116_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=116 && defined(BMC_GLOBAL_POT_116_X) && defined(BMC_GLOBAL_POT_116_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 116

#if defined(BMC_GLOBAL_POT_117_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=117 && defined(BMC_GLOBAL_POT_117_X) && defined(BMC_GLOBAL_POT_117_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 117

#if defined(BMC_GLOBAL_POT_118_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=118 && defined(BMC_GLOBAL_POT_118_X) && defined(BMC_GLOBAL_POT_118_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 118

#if defined(BMC_GLOBAL_POT_119_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=119 && defined(BMC_GLOBAL_POT_119_X) && defined(BMC_GLOBAL_POT_119_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 119

#if defined(BMC_GLOBAL_POT_120_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=120 && defined(BMC_GLOBAL_POT_120_X) && defined(BMC_GLOBAL_POT_120_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 120

#if defined(BMC_GLOBAL_POT_121_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=121 && defined(BMC_GLOBAL_POT_121_X) && defined(BMC_GLOBAL_POT_121_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 121

#if defined(BMC_GLOBAL_POT_122_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=122 && defined(BMC_GLOBAL_POT_122_X) && defined(BMC_GLOBAL_POT_122_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 122

#if defined(BMC_GLOBAL_POT_123_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=123 && defined(BMC_GLOBAL_POT_123_X) && defined(BMC_GLOBAL_POT_123_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 123

#if defined(BMC_GLOBAL_POT_124_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=124 && defined(BMC_GLOBAL_POT_124_X) && defined(BMC_GLOBAL_POT_124_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 124

#if defined(BMC_GLOBAL_POT_125_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=125 && defined(BMC_GLOBAL_POT_125_X) && defined(BMC_GLOBAL_POT_125_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 125

#if defined(BMC_GLOBAL_POT_126_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=126 && defined(BMC_GLOBAL_POT_126_X) && defined(BMC_GLOBAL_POT_126_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 126

#if defined(BMC_GLOBAL_POT_127_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=127 && defined(BMC_GLOBAL_POT_127_X) && defined(BMC_GLOBAL_POT_127_Y)
#ifdef BMC_MAX_GLOBAL_POTS
#undef BMC_MAX_GLOBAL_POTS
#endif
#define BMC_MAX_GLOBAL_POTS 127

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 0
#if defined(BMC_PWM_LED_1_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=1 && defined(BMC_PWM_LED_1_X) && defined(BMC_PWM_LED_1_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 1

#if defined(BMC_PWM_LED_2_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=2 && defined(BMC_PWM_LED_2_X) && defined(BMC_PWM_LED_2_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 2

#if defined(BMC_PWM_LED_3_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=3 && defined(BMC_PWM_LED_3_X) && defined(BMC_PWM_LED_3_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 3

#if defined(BMC_PWM_LED_4_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=4 && defined(BMC_PWM_LED_4_X) && defined(BMC_PWM_LED_4_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 4

#if defined(BMC_PWM_LED_5_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=5 && defined(BMC_PWM_LED_5_X) && defined(BMC_PWM_LED_5_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 5

#if defined(BMC_PWM_LED_6_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=6 && defined(BMC_PWM_LED_6_X) && defined(BMC_PWM_LED_6_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 6

#if defined(BMC_PWM_LED_7_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=7 && defined(BMC_PWM_LED_7_X) && defined(BMC_PWM_LED_7_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 7

#if defined(BMC_PWM_LED_8_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=8 && defined(BMC_PWM_LED_8_X) && defined(BMC_PWM_LED_8_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 8

#if defined(BMC_PWM_LED_9_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=9 && defined(BMC_PWM_LED_9_X) && defined(BMC_PWM_LED_9_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 9

#if defined(BMC_PWM_LED_10_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=10 && defined(BMC_PWM_LED_10_X) && defined(BMC_PWM_LED_10_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 10

#if defined(BMC_PWM_LED_11_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=11 && defined(BMC_PWM_LED_11_X) && defined(BMC_PWM_LED_11_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 11

#if defined(BMC_PWM_LED_12_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=12 && defined(BMC_PWM_LED_12_X) && defined(BMC_PWM_LED_12_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 12

#if defined(BMC_PWM_LED_13_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=13 && defined(BMC_PWM_LED_13_X) && defined(BMC_PWM_LED_13_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 13

#if defined(BMC_PWM_LED_14_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=14 && defined(BMC_PWM_LED_14_X) && defined(BMC_PWM_LED_14_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 14

#if defined(BMC_PWM_LED_15_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=15 && defined(BMC_PWM_LED_15_X) && defined(BMC_PWM_LED_15_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 15

#if defined(BMC_PWM_LED_16_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=16 && defined(BMC_PWM_LED_16_X) && defined(BMC_PWM_LED_16_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 16

#if defined(BMC_PWM_LED_17_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=17 && defined(BMC_PWM_LED_17_X) && defined(BMC_PWM_LED_17_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 17

#if defined(BMC_PWM_LED_18_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=18 && defined(BMC_PWM_LED_18_X) && defined(BMC_PWM_LED_18_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 18

#if defined(BMC_PWM_LED_19_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=19 && defined(BMC_PWM_LED_19_X) && defined(BMC_PWM_LED_19_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 19

#if defined(BMC_PWM_LED_20_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=20 && defined(BMC_PWM_LED_20_X) && defined(BMC_PWM_LED_20_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 20

#if defined(BMC_PWM_LED_21_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=21 && defined(BMC_PWM_LED_21_X) && defined(BMC_PWM_LED_21_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 21

#if defined(BMC_PWM_LED_22_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=22 && defined(BMC_PWM_LED_22_X) && defined(BMC_PWM_LED_22_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 22

#if defined(BMC_PWM_LED_23_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=23 && defined(BMC_PWM_LED_23_X) && defined(BMC_PWM_LED_23_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 23

#if defined(BMC_PWM_LED_24_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=24 && defined(BMC_PWM_LED_24_X) && defined(BMC_PWM_LED_24_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 24

#if defined(BMC_PWM_LED_25_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=25 && defined(BMC_PWM_LED_25_X) && defined(BMC_PWM_LED_25_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 25

#if defined(BMC_PWM_LED_26_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=26 && defined(BMC_PWM_LED_26_X) && defined(BMC_PWM_LED_26_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 26

#if defined(BMC_PWM_LED_27_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=27 && defined(BMC_PWM_LED_27_X) && defined(BMC_PWM_LED_27_Y)
#ifdef BMC_MAX_PWM_LEDS
#undef BMC_MAX_PWM_LEDS
#endif
#define BMC_MAX_PWM_LEDS 27

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 0
#if defined(BMC_DEFAULT_PIXEL_COLOR_1) && defined(BMC_PIXEL_1_X) && defined(BMC_PIXEL_1_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 1

#if defined(BMC_DEFAULT_PIXEL_COLOR_2) && defined(BMC_PIXEL_2_X) && defined(BMC_PIXEL_2_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 2

#if defined(BMC_DEFAULT_PIXEL_COLOR_3) && defined(BMC_PIXEL_3_X) && defined(BMC_PIXEL_3_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 3

#if defined(BMC_DEFAULT_PIXEL_COLOR_4) && defined(BMC_PIXEL_4_X) && defined(BMC_PIXEL_4_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 4

#if defined(BMC_DEFAULT_PIXEL_COLOR_5) && defined(BMC_PIXEL_5_X) && defined(BMC_PIXEL_5_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 5

#if defined(BMC_DEFAULT_PIXEL_COLOR_6) && defined(BMC_PIXEL_6_X) && defined(BMC_PIXEL_6_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 6

#if defined(BMC_DEFAULT_PIXEL_COLOR_7) && defined(BMC_PIXEL_7_X) && defined(BMC_PIXEL_7_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 7

#if defined(BMC_DEFAULT_PIXEL_COLOR_8) && defined(BMC_PIXEL_8_X) && defined(BMC_PIXEL_8_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 8

#if defined(BMC_DEFAULT_PIXEL_COLOR_9) && defined(BMC_PIXEL_9_X) && defined(BMC_PIXEL_9_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 9

#if defined(BMC_DEFAULT_PIXEL_COLOR_10) && defined(BMC_PIXEL_10_X) && defined(BMC_PIXEL_10_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 10

#if defined(BMC_DEFAULT_PIXEL_COLOR_11) && defined(BMC_PIXEL_11_X) && defined(BMC_PIXEL_11_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 11

#if defined(BMC_DEFAULT_PIXEL_COLOR_12) && defined(BMC_PIXEL_12_X) && defined(BMC_PIXEL_12_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 12

#if defined(BMC_DEFAULT_PIXEL_COLOR_13) && defined(BMC_PIXEL_13_X) && defined(BMC_PIXEL_13_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 13

#if defined(BMC_DEFAULT_PIXEL_COLOR_14) && defined(BMC_PIXEL_14_X) && defined(BMC_PIXEL_14_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 14

#if defined(BMC_DEFAULT_PIXEL_COLOR_15) && defined(BMC_PIXEL_15_X) && defined(BMC_PIXEL_15_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 15

#if defined(BMC_DEFAULT_PIXEL_COLOR_16) && defined(BMC_PIXEL_16_X) && defined(BMC_PIXEL_16_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 16

#if defined(BMC_DEFAULT_PIXEL_COLOR_17) && defined(BMC_PIXEL_17_X) && defined(BMC_PIXEL_17_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 17

#if defined(BMC_DEFAULT_PIXEL_COLOR_18) && defined(BMC_PIXEL_18_X) && defined(BMC_PIXEL_18_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 18

#if defined(BMC_DEFAULT_PIXEL_COLOR_19) && defined(BMC_PIXEL_19_X) && defined(BMC_PIXEL_19_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 19

#if defined(BMC_DEFAULT_PIXEL_COLOR_20) && defined(BMC_PIXEL_20_X) && defined(BMC_PIXEL_20_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 20

#if defined(BMC_DEFAULT_PIXEL_COLOR_21) && defined(BMC_PIXEL_21_X) && defined(BMC_PIXEL_21_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 21

#if defined(BMC_DEFAULT_PIXEL_COLOR_22) && defined(BMC_PIXEL_22_X) && defined(BMC_PIXEL_22_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 22

#if defined(BMC_DEFAULT_PIXEL_COLOR_23) && defined(BMC_PIXEL_23_X) && defined(BMC_PIXEL_23_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 23

#if defined(BMC_DEFAULT_PIXEL_COLOR_24) && defined(BMC_PIXEL_24_X) && defined(BMC_PIXEL_24_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 24

#if defined(BMC_DEFAULT_PIXEL_COLOR_25) && defined(BMC_PIXEL_25_X) && defined(BMC_PIXEL_25_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 25

#if defined(BMC_DEFAULT_PIXEL_COLOR_26) && defined(BMC_PIXEL_26_X) && defined(BMC_PIXEL_26_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 26

#if defined(BMC_DEFAULT_PIXEL_COLOR_27) && defined(BMC_PIXEL_27_X) && defined(BMC_PIXEL_27_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 27

#if defined(BMC_DEFAULT_PIXEL_COLOR_28) && defined(BMC_PIXEL_28_X) && defined(BMC_PIXEL_28_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 28

#if defined(BMC_DEFAULT_PIXEL_COLOR_29) && defined(BMC_PIXEL_29_X) && defined(BMC_PIXEL_29_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 29

#if defined(BMC_DEFAULT_PIXEL_COLOR_30) && defined(BMC_PIXEL_30_X) && defined(BMC_PIXEL_30_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 30

#if defined(BMC_DEFAULT_PIXEL_COLOR_31) && defined(BMC_PIXEL_31_X) && defined(BMC_PIXEL_31_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 31

#if defined(BMC_DEFAULT_PIXEL_COLOR_32) && defined(BMC_PIXEL_32_X) && defined(BMC_PIXEL_32_Y)
#ifdef BMC_MAX_PIXELS
#undef BMC_MAX_PIXELS
#endif
#define BMC_MAX_PIXELS 32

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 0
#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_1) && defined(BMC_RGB_PIXEL_1_X) && defined(BMC_RGB_PIXEL_1_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 1

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_2) && defined(BMC_RGB_PIXEL_2_X) && defined(BMC_RGB_PIXEL_2_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 2

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_3) && defined(BMC_RGB_PIXEL_3_X) && defined(BMC_RGB_PIXEL_3_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 3

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_4) && defined(BMC_RGB_PIXEL_4_X) && defined(BMC_RGB_PIXEL_4_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 4

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_5) && defined(BMC_RGB_PIXEL_5_X) && defined(BMC_RGB_PIXEL_5_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 5

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_6) && defined(BMC_RGB_PIXEL_6_X) && defined(BMC_RGB_PIXEL_6_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 6

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_7) && defined(BMC_RGB_PIXEL_7_X) && defined(BMC_RGB_PIXEL_7_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 7

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_8) && defined(BMC_RGB_PIXEL_8_X) && defined(BMC_RGB_PIXEL_8_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 8

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_9) && defined(BMC_RGB_PIXEL_9_X) && defined(BMC_RGB_PIXEL_9_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 9

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_10) && defined(BMC_RGB_PIXEL_10_X) && defined(BMC_RGB_PIXEL_10_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 10

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_11) && defined(BMC_RGB_PIXEL_11_X) && defined(BMC_RGB_PIXEL_11_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 11

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_12) && defined(BMC_RGB_PIXEL_12_X) && defined(BMC_RGB_PIXEL_12_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 12

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_13) && defined(BMC_RGB_PIXEL_13_X) && defined(BMC_RGB_PIXEL_13_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 13

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_14) && defined(BMC_RGB_PIXEL_14_X) && defined(BMC_RGB_PIXEL_14_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 14

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_15) && defined(BMC_RGB_PIXEL_15_X) && defined(BMC_RGB_PIXEL_15_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 15

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_16) && defined(BMC_RGB_PIXEL_16_X) && defined(BMC_RGB_PIXEL_16_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 16

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_17) && defined(BMC_RGB_PIXEL_17_X) && defined(BMC_RGB_PIXEL_17_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 17

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_18) && defined(BMC_RGB_PIXEL_18_X) && defined(BMC_RGB_PIXEL_18_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 18

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_19) && defined(BMC_RGB_PIXEL_19_X) && defined(BMC_RGB_PIXEL_19_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 19

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_20) && defined(BMC_RGB_PIXEL_20_X) && defined(BMC_RGB_PIXEL_20_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 20

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_21) && defined(BMC_RGB_PIXEL_21_X) && defined(BMC_RGB_PIXEL_21_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 21

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_22) && defined(BMC_RGB_PIXEL_22_X) && defined(BMC_RGB_PIXEL_22_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 22

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_23) && defined(BMC_RGB_PIXEL_23_X) && defined(BMC_RGB_PIXEL_23_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 23

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_24) && defined(BMC_RGB_PIXEL_24_X) && defined(BMC_RGB_PIXEL_24_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 24

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_25) && defined(BMC_RGB_PIXEL_25_X) && defined(BMC_RGB_PIXEL_25_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 25

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_26) && defined(BMC_RGB_PIXEL_26_X) && defined(BMC_RGB_PIXEL_26_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 26

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_27) && defined(BMC_RGB_PIXEL_27_X) && defined(BMC_RGB_PIXEL_27_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 27

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_28) && defined(BMC_RGB_PIXEL_28_X) && defined(BMC_RGB_PIXEL_28_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 28

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_29) && defined(BMC_RGB_PIXEL_29_X) && defined(BMC_RGB_PIXEL_29_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 29

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_30) && defined(BMC_RGB_PIXEL_30_X) && defined(BMC_RGB_PIXEL_30_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 30

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_31) && defined(BMC_RGB_PIXEL_31_X) && defined(BMC_RGB_PIXEL_31_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 31

#if defined(BMC_DEFAULT_RGB_PIXEL_COLOR_32) && defined(BMC_RGB_PIXEL_32_X) && defined(BMC_RGB_PIXEL_32_Y)
#ifdef BMC_MAX_RGB_PIXELS
#undef BMC_MAX_RGB_PIXELS
#endif
#define BMC_MAX_RGB_PIXELS 32

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 0
#if defined(BMC_NL_RELAY_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && defined(BMC_NL_RELAY_1_X) && defined(BMC_NL_RELAY_1_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 1

#if defined(BMC_NL_RELAY_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_NL_RELAY_2_X) && defined(BMC_NL_RELAY_2_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 2

#if defined(BMC_NL_RELAY_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && defined(BMC_NL_RELAY_3_X) && defined(BMC_NL_RELAY_3_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 3

#if defined(BMC_NL_RELAY_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_NL_RELAY_4_X) && defined(BMC_NL_RELAY_4_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 4

#if defined(BMC_NL_RELAY_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && defined(BMC_NL_RELAY_5_X) && defined(BMC_NL_RELAY_5_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 5

#if defined(BMC_NL_RELAY_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_NL_RELAY_6_X) && defined(BMC_NL_RELAY_6_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 6

#if defined(BMC_NL_RELAY_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && defined(BMC_NL_RELAY_7_X) && defined(BMC_NL_RELAY_7_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 7

#if defined(BMC_NL_RELAY_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_NL_RELAY_8_X) && defined(BMC_NL_RELAY_8_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 8

#if defined(BMC_NL_RELAY_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && defined(BMC_NL_RELAY_9_X) && defined(BMC_NL_RELAY_9_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 9

#if defined(BMC_NL_RELAY_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_NL_RELAY_10_X) && defined(BMC_NL_RELAY_10_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 10

#if defined(BMC_NL_RELAY_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && defined(BMC_NL_RELAY_11_X) && defined(BMC_NL_RELAY_11_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 11

#if defined(BMC_NL_RELAY_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_NL_RELAY_12_X) && defined(BMC_NL_RELAY_12_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 12

#if defined(BMC_NL_RELAY_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && defined(BMC_NL_RELAY_13_X) && defined(BMC_NL_RELAY_13_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 13

#if defined(BMC_NL_RELAY_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_NL_RELAY_14_X) && defined(BMC_NL_RELAY_14_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 14

#if defined(BMC_NL_RELAY_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && defined(BMC_NL_RELAY_15_X) && defined(BMC_NL_RELAY_15_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 15

#if defined(BMC_NL_RELAY_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_NL_RELAY_16_X) && defined(BMC_NL_RELAY_16_Y)
#ifdef BMC_MAX_NL_RELAYS
#undef BMC_MAX_NL_RELAYS
#endif
#define BMC_MAX_NL_RELAYS 16

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 0
#if defined(BMC_L_RELAY_1A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_L_RELAY_1B_PIN) && defined(BMC_L_RELAY_1_X) && defined(BMC_L_RELAY_1_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 1

#if defined(BMC_L_RELAY_2A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_L_RELAY_2B_PIN) && defined(BMC_L_RELAY_2_X) && defined(BMC_L_RELAY_2_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 2

#if defined(BMC_L_RELAY_3A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_L_RELAY_3B_PIN) && defined(BMC_L_RELAY_3_X) && defined(BMC_L_RELAY_3_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 3

#if defined(BMC_L_RELAY_4A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_L_RELAY_4B_PIN) && defined(BMC_L_RELAY_4_X) && defined(BMC_L_RELAY_4_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 4

#if defined(BMC_L_RELAY_5A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_L_RELAY_5B_PIN) && defined(BMC_L_RELAY_5_X) && defined(BMC_L_RELAY_5_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 5

#if defined(BMC_L_RELAY_6A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_L_RELAY_6B_PIN) && defined(BMC_L_RELAY_6_X) && defined(BMC_L_RELAY_6_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 6

#if defined(BMC_L_RELAY_7A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_L_RELAY_7B_PIN) && defined(BMC_L_RELAY_7_X) && defined(BMC_L_RELAY_7_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 7

#if defined(BMC_L_RELAY_8A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_L_RELAY_8B_PIN) && defined(BMC_L_RELAY_8_X) && defined(BMC_L_RELAY_8_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 8

#if defined(BMC_L_RELAY_9A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && defined(BMC_L_RELAY_9B_PIN) && defined(BMC_L_RELAY_9_X) && defined(BMC_L_RELAY_9_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 9

#if defined(BMC_L_RELAY_10A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && defined(BMC_L_RELAY_10B_PIN) && defined(BMC_L_RELAY_10_X) && defined(BMC_L_RELAY_10_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 10

#if defined(BMC_L_RELAY_11A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && defined(BMC_L_RELAY_11B_PIN) && defined(BMC_L_RELAY_11_X) && defined(BMC_L_RELAY_11_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 11

#if defined(BMC_L_RELAY_12A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && defined(BMC_L_RELAY_12B_PIN) && defined(BMC_L_RELAY_12_X) && defined(BMC_L_RELAY_12_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 12

#if defined(BMC_L_RELAY_13A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && defined(BMC_L_RELAY_13B_PIN) && defined(BMC_L_RELAY_13_X) && defined(BMC_L_RELAY_13_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 13

#if defined(BMC_L_RELAY_14A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && defined(BMC_L_RELAY_14B_PIN) && defined(BMC_L_RELAY_14_X) && defined(BMC_L_RELAY_14_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 14

#if defined(BMC_L_RELAY_15A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && defined(BMC_L_RELAY_15B_PIN) && defined(BMC_L_RELAY_15_X) && defined(BMC_L_RELAY_15_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 15

#if defined(BMC_L_RELAY_16A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && defined(BMC_L_RELAY_16B_PIN) && defined(BMC_L_RELAY_16_X) && defined(BMC_L_RELAY_16_Y)
#ifdef BMC_MAX_L_RELAYS
#undef BMC_MAX_L_RELAYS
#endif
#define BMC_MAX_L_RELAYS 16

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_BUTTON_LED_MERGE 0
#if BMC_MAX_LEDS > 0 && BMC_MAX_BUTTONS > 1
#if BMC_MAX_LEDS > 0 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_LED_MERGE_1_LED) && defined(BMC_BUTTON_LED_MERGE_1_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 1
#if BMC_MAX_LEDS > 1 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_LED_MERGE_2_LED) && defined(BMC_BUTTON_LED_MERGE_2_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 2
#if BMC_MAX_LEDS > 2 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_LED_MERGE_3_LED) && defined(BMC_BUTTON_LED_MERGE_3_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 3
#if BMC_MAX_LEDS > 3 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_LED_MERGE_4_LED) && defined(BMC_BUTTON_LED_MERGE_4_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 4
#if BMC_MAX_LEDS > 4 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_LED_MERGE_5_LED) && defined(BMC_BUTTON_LED_MERGE_5_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 5
#if BMC_MAX_LEDS > 5 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_LED_MERGE_6_LED) && defined(BMC_BUTTON_LED_MERGE_6_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 6
#if BMC_MAX_LEDS > 6 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_LED_MERGE_7_LED) && defined(BMC_BUTTON_LED_MERGE_7_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 7
#if BMC_MAX_LEDS > 7 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_LED_MERGE_8_LED) && defined(BMC_BUTTON_LED_MERGE_8_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 8
#if BMC_MAX_LEDS > 8 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_LED_MERGE_9_LED) && defined(BMC_BUTTON_LED_MERGE_9_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 9
#if BMC_MAX_LEDS > 9 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_LED_MERGE_10_LED) && defined(BMC_BUTTON_LED_MERGE_10_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 10
#if BMC_MAX_LEDS > 10 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_LED_MERGE_11_LED) && defined(BMC_BUTTON_LED_MERGE_11_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 11
#if BMC_MAX_LEDS > 11 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_LED_MERGE_12_LED) && defined(BMC_BUTTON_LED_MERGE_12_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 12
#if BMC_MAX_LEDS > 12 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_LED_MERGE_13_LED) && defined(BMC_BUTTON_LED_MERGE_13_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 13
#if BMC_MAX_LEDS > 13 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_LED_MERGE_14_LED) && defined(BMC_BUTTON_LED_MERGE_14_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 14
#if BMC_MAX_LEDS > 14 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_LED_MERGE_15_LED) && defined(BMC_BUTTON_LED_MERGE_15_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 15
#if BMC_MAX_LEDS > 15 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_LED_MERGE_16_LED) && defined(BMC_BUTTON_LED_MERGE_16_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 16
#if BMC_MAX_LEDS > 16 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_LED_MERGE_17_LED) && defined(BMC_BUTTON_LED_MERGE_17_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 17
#if BMC_MAX_LEDS > 17 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_LED_MERGE_18_LED) && defined(BMC_BUTTON_LED_MERGE_18_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 18
#if BMC_MAX_LEDS > 18 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_LED_MERGE_19_LED) && defined(BMC_BUTTON_LED_MERGE_19_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 19
#if BMC_MAX_LEDS > 19 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_LED_MERGE_20_LED) && defined(BMC_BUTTON_LED_MERGE_20_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 20
#if BMC_MAX_LEDS > 20 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_LED_MERGE_21_LED) && defined(BMC_BUTTON_LED_MERGE_21_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 21
#if BMC_MAX_LEDS > 21 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_LED_MERGE_22_LED) && defined(BMC_BUTTON_LED_MERGE_22_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 22
#if BMC_MAX_LEDS > 22 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_LED_MERGE_23_LED) && defined(BMC_BUTTON_LED_MERGE_23_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 23
#if BMC_MAX_LEDS > 23 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_LED_MERGE_24_LED) && defined(BMC_BUTTON_LED_MERGE_24_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 24
#if BMC_MAX_LEDS > 24 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_LED_MERGE_25_LED) && defined(BMC_BUTTON_LED_MERGE_25_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 25
#if BMC_MAX_LEDS > 25 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_LED_MERGE_26_LED) && defined(BMC_BUTTON_LED_MERGE_26_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 26
#if BMC_MAX_LEDS > 26 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_LED_MERGE_27_LED) && defined(BMC_BUTTON_LED_MERGE_27_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 27
#if BMC_MAX_LEDS > 27 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_LED_MERGE_28_LED) && defined(BMC_BUTTON_LED_MERGE_28_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 28
#if BMC_MAX_LEDS > 28 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_LED_MERGE_29_LED) && defined(BMC_BUTTON_LED_MERGE_29_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 29
#if BMC_MAX_LEDS > 29 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_LED_MERGE_30_LED) && defined(BMC_BUTTON_LED_MERGE_30_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 30
#if BMC_MAX_LEDS > 30 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_LED_MERGE_31_LED) && defined(BMC_BUTTON_LED_MERGE_31_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 31
#if BMC_MAX_LEDS > 31 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_LED_MERGE_32_LED) && defined(BMC_BUTTON_LED_MERGE_32_BTN)
#undef BMC_MAX_BUTTON_LED_MERGE
#define BMC_MAX_BUTTON_LED_MERGE 32
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#define BMC_MAX_BUTTON_PIXEL_MERGE 0
#if BMC_MAX_PIXELS > 0 && BMC_MAX_BUTTONS > 1
#if BMC_MAX_PIXELS > 0 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_PIXEL_MERGE_1_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_1_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 1
#if BMC_MAX_PIXELS > 1 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_PIXEL_MERGE_2_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_2_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 2
#if BMC_MAX_PIXELS > 2 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_PIXEL_MERGE_3_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_3_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 3
#if BMC_MAX_PIXELS > 3 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_PIXEL_MERGE_4_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_4_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 4
#if BMC_MAX_PIXELS > 4 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_PIXEL_MERGE_5_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_5_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 5
#if BMC_MAX_PIXELS > 5 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_PIXEL_MERGE_6_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_6_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 6
#if BMC_MAX_PIXELS > 6 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_PIXEL_MERGE_7_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_7_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 7
#if BMC_MAX_PIXELS > 7 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_PIXEL_MERGE_8_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_8_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 8
#if BMC_MAX_PIXELS > 8 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_PIXEL_MERGE_9_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_9_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 9
#if BMC_MAX_PIXELS > 9 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_PIXEL_MERGE_10_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_10_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 10
#if BMC_MAX_PIXELS > 10 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_PIXEL_MERGE_11_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_11_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 11
#if BMC_MAX_PIXELS > 11 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_PIXEL_MERGE_12_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_12_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 12
#if BMC_MAX_PIXELS > 12 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_PIXEL_MERGE_13_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_13_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 13
#if BMC_MAX_PIXELS > 13 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_PIXEL_MERGE_14_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_14_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 14
#if BMC_MAX_PIXELS > 14 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_PIXEL_MERGE_15_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_15_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 15
#if BMC_MAX_PIXELS > 15 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_PIXEL_MERGE_16_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_16_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 16
#if BMC_MAX_PIXELS > 16 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_PIXEL_MERGE_17_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_17_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 17
#if BMC_MAX_PIXELS > 17 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_PIXEL_MERGE_18_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_18_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 18
#if BMC_MAX_PIXELS > 18 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_PIXEL_MERGE_19_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_19_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 19
#if BMC_MAX_PIXELS > 19 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_PIXEL_MERGE_20_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_20_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 20
#if BMC_MAX_PIXELS > 20 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_PIXEL_MERGE_21_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_21_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 21
#if BMC_MAX_PIXELS > 21 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_PIXEL_MERGE_22_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_22_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 22
#if BMC_MAX_PIXELS > 22 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_PIXEL_MERGE_23_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_23_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 23
#if BMC_MAX_PIXELS > 23 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_PIXEL_MERGE_24_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_24_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 24
#if BMC_MAX_PIXELS > 24 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_PIXEL_MERGE_25_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_25_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 25
#if BMC_MAX_PIXELS > 25 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_PIXEL_MERGE_26_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_26_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 26
#if BMC_MAX_PIXELS > 26 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_PIXEL_MERGE_27_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_27_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 27
#if BMC_MAX_PIXELS > 27 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_PIXEL_MERGE_28_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_28_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 28
#if BMC_MAX_PIXELS > 28 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_PIXEL_MERGE_29_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_29_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 29
#if BMC_MAX_PIXELS > 29 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_PIXEL_MERGE_30_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_30_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 30
#if BMC_MAX_PIXELS > 30 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_PIXEL_MERGE_31_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_31_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 31
#if BMC_MAX_PIXELS > 31 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_PIXEL_MERGE_32_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_32_BTN)
#undef BMC_MAX_BUTTON_PIXEL_MERGE
#define BMC_MAX_BUTTON_PIXEL_MERGE 32
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 0
#if BMC_MAX_RGB_PIXELS > 0 && BMC_MAX_BUTTONS > 1
#if BMC_MAX_RGB_PIXELS > 0 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_1_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_1_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 1
#if BMC_MAX_RGB_PIXELS > 1 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_2_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_2_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 2
#if BMC_MAX_RGB_PIXELS > 2 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_3_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_3_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 3
#if BMC_MAX_RGB_PIXELS > 3 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_4_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_4_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 4
#if BMC_MAX_RGB_PIXELS > 4 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_5_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_5_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 5
#if BMC_MAX_RGB_PIXELS > 5 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_6_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_6_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 6
#if BMC_MAX_RGB_PIXELS > 6 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_7_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_7_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 7
#if BMC_MAX_RGB_PIXELS > 7 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_8_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_8_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 8
#if BMC_MAX_RGB_PIXELS > 8 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_9_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_9_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 9
#if BMC_MAX_RGB_PIXELS > 9 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_10_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_10_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 10
#if BMC_MAX_RGB_PIXELS > 10 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_11_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_11_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 11
#if BMC_MAX_RGB_PIXELS > 11 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_12_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_12_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 12
#if BMC_MAX_RGB_PIXELS > 12 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_13_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_13_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 13
#if BMC_MAX_RGB_PIXELS > 13 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_14_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_14_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 14
#if BMC_MAX_RGB_PIXELS > 14 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_15_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_15_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 15
#if BMC_MAX_RGB_PIXELS > 15 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_16_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_16_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 16
#if BMC_MAX_RGB_PIXELS > 16 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_17_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_17_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 17
#if BMC_MAX_RGB_PIXELS > 17 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_18_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_18_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 18
#if BMC_MAX_RGB_PIXELS > 18 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_19_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_19_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 19
#if BMC_MAX_RGB_PIXELS > 19 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_20_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_20_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 20
#if BMC_MAX_RGB_PIXELS > 20 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_21_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_21_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 21
#if BMC_MAX_RGB_PIXELS > 21 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_22_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_22_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 22
#if BMC_MAX_RGB_PIXELS > 22 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_23_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_23_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 23
#if BMC_MAX_RGB_PIXELS > 23 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_24_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_24_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 24
#if BMC_MAX_RGB_PIXELS > 24 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_25_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_25_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 25
#if BMC_MAX_RGB_PIXELS > 25 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_26_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_26_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 26
#if BMC_MAX_RGB_PIXELS > 26 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_27_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_27_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 27
#if BMC_MAX_RGB_PIXELS > 27 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_28_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_28_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 28
#if BMC_MAX_RGB_PIXELS > 28 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_29_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_29_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 29
#if BMC_MAX_RGB_PIXELS > 29 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_30_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_30_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 30
#if BMC_MAX_RGB_PIXELS > 30 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_31_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_31_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 31
#if BMC_MAX_RGB_PIXELS > 31 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_32_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_32_BTN)
#undef BMC_MAX_BUTTON_RGB_PIXEL_MERGE
#define BMC_MAX_BUTTON_RGB_PIXEL_MERGE 32
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#define BMC_MAX_ENCODER_MERGE 0
#if BMC_MAX_ENCODERS > 0 && BMC_MAX_BUTTONS > 1
#if BMC_MAX_ENCODERS > 0 && BMC_MAX_BUTTONS > 0 && defined(BMC_ENCODER_MERGE_1_ENC) && defined(BMC_ENCODER_MERGE_1_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 1
#if BMC_MAX_ENCODERS > 1 && BMC_MAX_BUTTONS > 1 && defined(BMC_ENCODER_MERGE_2_ENC) && defined(BMC_ENCODER_MERGE_2_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 2
#if BMC_MAX_ENCODERS > 2 && BMC_MAX_BUTTONS > 2 && defined(BMC_ENCODER_MERGE_3_ENC) && defined(BMC_ENCODER_MERGE_3_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 3
#if BMC_MAX_ENCODERS > 3 && BMC_MAX_BUTTONS > 3 && defined(BMC_ENCODER_MERGE_4_ENC) && defined(BMC_ENCODER_MERGE_4_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 4
#if BMC_MAX_ENCODERS > 4 && BMC_MAX_BUTTONS > 4 && defined(BMC_ENCODER_MERGE_5_ENC) && defined(BMC_ENCODER_MERGE_5_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 5
#if BMC_MAX_ENCODERS > 5 && BMC_MAX_BUTTONS > 5 && defined(BMC_ENCODER_MERGE_6_ENC) && defined(BMC_ENCODER_MERGE_6_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 6
#if BMC_MAX_ENCODERS > 6 && BMC_MAX_BUTTONS > 6 && defined(BMC_ENCODER_MERGE_7_ENC) && defined(BMC_ENCODER_MERGE_7_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 7
#if BMC_MAX_ENCODERS > 7 && BMC_MAX_BUTTONS > 7 && defined(BMC_ENCODER_MERGE_8_ENC) && defined(BMC_ENCODER_MERGE_8_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 8
#if BMC_MAX_ENCODERS > 8 && BMC_MAX_BUTTONS > 8 && defined(BMC_ENCODER_MERGE_9_ENC) && defined(BMC_ENCODER_MERGE_9_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 9
#if BMC_MAX_ENCODERS > 9 && BMC_MAX_BUTTONS > 9 && defined(BMC_ENCODER_MERGE_10_ENC) && defined(BMC_ENCODER_MERGE_10_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 10
#if BMC_MAX_ENCODERS > 10 && BMC_MAX_BUTTONS > 10 && defined(BMC_ENCODER_MERGE_11_ENC) && defined(BMC_ENCODER_MERGE_11_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 11
#if BMC_MAX_ENCODERS > 11 && BMC_MAX_BUTTONS > 11 && defined(BMC_ENCODER_MERGE_12_ENC) && defined(BMC_ENCODER_MERGE_12_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 12
#if BMC_MAX_ENCODERS > 12 && BMC_MAX_BUTTONS > 12 && defined(BMC_ENCODER_MERGE_13_ENC) && defined(BMC_ENCODER_MERGE_13_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 13
#if BMC_MAX_ENCODERS > 13 && BMC_MAX_BUTTONS > 13 && defined(BMC_ENCODER_MERGE_14_ENC) && defined(BMC_ENCODER_MERGE_14_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 14
#if BMC_MAX_ENCODERS > 14 && BMC_MAX_BUTTONS > 14 && defined(BMC_ENCODER_MERGE_15_ENC) && defined(BMC_ENCODER_MERGE_15_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 15
#if BMC_MAX_ENCODERS > 15 && BMC_MAX_BUTTONS > 15 && defined(BMC_ENCODER_MERGE_16_ENC) && defined(BMC_ENCODER_MERGE_16_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 16
#if BMC_MAX_ENCODERS > 16 && BMC_MAX_BUTTONS > 16 && defined(BMC_ENCODER_MERGE_17_ENC) && defined(BMC_ENCODER_MERGE_17_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 17
#if BMC_MAX_ENCODERS > 17 && BMC_MAX_BUTTONS > 17 && defined(BMC_ENCODER_MERGE_18_ENC) && defined(BMC_ENCODER_MERGE_18_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 18
#if BMC_MAX_ENCODERS > 18 && BMC_MAX_BUTTONS > 18 && defined(BMC_ENCODER_MERGE_19_ENC) && defined(BMC_ENCODER_MERGE_19_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 19
#if BMC_MAX_ENCODERS > 19 && BMC_MAX_BUTTONS > 19 && defined(BMC_ENCODER_MERGE_20_ENC) && defined(BMC_ENCODER_MERGE_20_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 20
#if BMC_MAX_ENCODERS > 20 && BMC_MAX_BUTTONS > 20 && defined(BMC_ENCODER_MERGE_21_ENC) && defined(BMC_ENCODER_MERGE_21_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 21
#if BMC_MAX_ENCODERS > 21 && BMC_MAX_BUTTONS > 21 && defined(BMC_ENCODER_MERGE_22_ENC) && defined(BMC_ENCODER_MERGE_22_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 22
#if BMC_MAX_ENCODERS > 22 && BMC_MAX_BUTTONS > 22 && defined(BMC_ENCODER_MERGE_23_ENC) && defined(BMC_ENCODER_MERGE_23_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 23
#if BMC_MAX_ENCODERS > 23 && BMC_MAX_BUTTONS > 23 && defined(BMC_ENCODER_MERGE_24_ENC) && defined(BMC_ENCODER_MERGE_24_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 24
#if BMC_MAX_ENCODERS > 24 && BMC_MAX_BUTTONS > 24 && defined(BMC_ENCODER_MERGE_25_ENC) && defined(BMC_ENCODER_MERGE_25_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 25
#if BMC_MAX_ENCODERS > 25 && BMC_MAX_BUTTONS > 25 && defined(BMC_ENCODER_MERGE_26_ENC) && defined(BMC_ENCODER_MERGE_26_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 26
#if BMC_MAX_ENCODERS > 26 && BMC_MAX_BUTTONS > 26 && defined(BMC_ENCODER_MERGE_27_ENC) && defined(BMC_ENCODER_MERGE_27_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 27
#if BMC_MAX_ENCODERS > 27 && BMC_MAX_BUTTONS > 27 && defined(BMC_ENCODER_MERGE_28_ENC) && defined(BMC_ENCODER_MERGE_28_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 28
#if BMC_MAX_ENCODERS > 28 && BMC_MAX_BUTTONS > 28 && defined(BMC_ENCODER_MERGE_29_ENC) && defined(BMC_ENCODER_MERGE_29_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 29
#if BMC_MAX_ENCODERS > 29 && BMC_MAX_BUTTONS > 29 && defined(BMC_ENCODER_MERGE_30_ENC) && defined(BMC_ENCODER_MERGE_30_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 30
#if BMC_MAX_ENCODERS > 30 && BMC_MAX_BUTTONS > 30 && defined(BMC_ENCODER_MERGE_31_ENC) && defined(BMC_ENCODER_MERGE_31_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 31
#if BMC_MAX_ENCODERS > 31 && BMC_MAX_BUTTONS > 31 && defined(BMC_ENCODER_MERGE_32_ENC) && defined(BMC_ENCODER_MERGE_32_BTN)
#undef BMC_MAX_ENCODER_MERGE
#define BMC_MAX_ENCODER_MERGE 32
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#define BMC_MAX_AUX_JACKS 0
#if BMC_MAX_POTS > 0 && BMC_MAX_BUTTONS > 1
#if BMC_MAX_POTS > 0 && BMC_MAX_BUTTONS >= 2 && defined(BMC_AUX_JACK_1_POT) && defined(BMC_AUX_JACK_1_BTN) && defined(BMC_AUX_JACK_1_BTN_EN)
#undef BMC_MAX_AUX_JACKS
#define BMC_MAX_AUX_JACKS 1
#if BMC_MAX_POTS > 1 && BMC_MAX_BUTTONS >= 4 && defined(BMC_AUX_JACK_2_POT) && defined(BMC_AUX_JACK_2_BTN) && defined(BMC_AUX_JACK_2_BTN_EN)
#undef BMC_MAX_AUX_JACKS
#define BMC_MAX_AUX_JACKS 2
#if BMC_MAX_POTS > 2 && BMC_MAX_BUTTONS >= 6 && defined(BMC_AUX_JACK_3_POT) && defined(BMC_AUX_JACK_3_BTN) && defined(BMC_AUX_JACK_3_BTN_EN)
#undef BMC_MAX_AUX_JACKS
#define BMC_MAX_AUX_JACKS 3
#if BMC_MAX_POTS > 3 && BMC_MAX_BUTTONS >= 8 && defined(BMC_AUX_JACK_4_POT) && defined(BMC_AUX_JACK_4_BTN) && defined(BMC_AUX_JACK_4_BTN_EN)
#undef BMC_MAX_AUX_JACKS
#define BMC_MAX_AUX_JACKS 4
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_BI_LED_MERGE 0
#if BMC_MAX_LEDS >= 2
#if BMC_MAX_LEDS >= 2  && defined(BMC_BI_LED_MERGE_1_LED) && defined(BMC_BI_LED_MERGE_1_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 1
#if BMC_MAX_LEDS >= 4  && defined(BMC_BI_LED_MERGE_2_LED) && defined(BMC_BI_LED_MERGE_2_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 2
#if BMC_MAX_LEDS >= 6  && defined(BMC_BI_LED_MERGE_3_LED) && defined(BMC_BI_LED_MERGE_3_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 3
#if BMC_MAX_LEDS >= 8  && defined(BMC_BI_LED_MERGE_4_LED) && defined(BMC_BI_LED_MERGE_4_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 4
#if BMC_MAX_LEDS >= 10  && defined(BMC_BI_LED_MERGE_5_LED) && defined(BMC_BI_LED_MERGE_5_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 5
#if BMC_MAX_LEDS >= 12  && defined(BMC_BI_LED_MERGE_6_LED) && defined(BMC_BI_LED_MERGE_6_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 6
#if BMC_MAX_LEDS >= 14  && defined(BMC_BI_LED_MERGE_7_LED) && defined(BMC_BI_LED_MERGE_7_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 7
#if BMC_MAX_LEDS >= 16  && defined(BMC_BI_LED_MERGE_8_LED) && defined(BMC_BI_LED_MERGE_8_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 8
#if BMC_MAX_LEDS >= 18  && defined(BMC_BI_LED_MERGE_9_LED) && defined(BMC_BI_LED_MERGE_9_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 9
#if BMC_MAX_LEDS >= 20  && defined(BMC_BI_LED_MERGE_10_LED) && defined(BMC_BI_LED_MERGE_10_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 10
#if BMC_MAX_LEDS >= 22  && defined(BMC_BI_LED_MERGE_11_LED) && defined(BMC_BI_LED_MERGE_11_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 11
#if BMC_MAX_LEDS >= 24  && defined(BMC_BI_LED_MERGE_12_LED) && defined(BMC_BI_LED_MERGE_12_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 12
#if BMC_MAX_LEDS >= 26  && defined(BMC_BI_LED_MERGE_13_LED) && defined(BMC_BI_LED_MERGE_13_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 13
#if BMC_MAX_LEDS >= 28  && defined(BMC_BI_LED_MERGE_14_LED) && defined(BMC_BI_LED_MERGE_14_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 14
#if BMC_MAX_LEDS >= 30  && defined(BMC_BI_LED_MERGE_15_LED) && defined(BMC_BI_LED_MERGE_15_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 15
#if BMC_MAX_LEDS >= 32  && defined(BMC_BI_LED_MERGE_16_LED) && defined(BMC_BI_LED_MERGE_16_LED2)
#undef BMC_MAX_BI_LED_MERGE
#define BMC_MAX_BI_LED_MERGE 16
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_RGB_LED_MERGE 0
#if BMC_MAX_LEDS >= 3
#if BMC_MAX_LEDS >= 3  && defined(BMC_RGB_LED_MERGE_1_LED) && defined(BMC_RGB_LED_MERGE_1_LED2) && defined(BMC_RGB_LED_MERGE_1_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 1
#if BMC_MAX_LEDS >= 6  && defined(BMC_RGB_LED_MERGE_2_LED) && defined(BMC_RGB_LED_MERGE_2_LED2) && defined(BMC_RGB_LED_MERGE_2_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 2
#if BMC_MAX_LEDS >= 9  && defined(BMC_RGB_LED_MERGE_3_LED) && defined(BMC_RGB_LED_MERGE_3_LED2) && defined(BMC_RGB_LED_MERGE_3_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 3
#if BMC_MAX_LEDS >= 12  && defined(BMC_RGB_LED_MERGE_4_LED) && defined(BMC_RGB_LED_MERGE_4_LED2) && defined(BMC_RGB_LED_MERGE_4_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 4
#if BMC_MAX_LEDS >= 15  && defined(BMC_RGB_LED_MERGE_5_LED) && defined(BMC_RGB_LED_MERGE_5_LED2) && defined(BMC_RGB_LED_MERGE_5_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 5
#if BMC_MAX_LEDS >= 18  && defined(BMC_RGB_LED_MERGE_6_LED) && defined(BMC_RGB_LED_MERGE_6_LED2) && defined(BMC_RGB_LED_MERGE_6_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 6
#if BMC_MAX_LEDS >= 21  && defined(BMC_RGB_LED_MERGE_7_LED) && defined(BMC_RGB_LED_MERGE_7_LED2) && defined(BMC_RGB_LED_MERGE_7_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 7
#if BMC_MAX_LEDS >= 24  && defined(BMC_RGB_LED_MERGE_8_LED) && defined(BMC_RGB_LED_MERGE_8_LED2) && defined(BMC_RGB_LED_MERGE_8_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 8
#if BMC_MAX_LEDS >= 27  && defined(BMC_RGB_LED_MERGE_9_LED) && defined(BMC_RGB_LED_MERGE_9_LED2) && defined(BMC_RGB_LED_MERGE_9_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 9
#if BMC_MAX_LEDS >= 30  && defined(BMC_RGB_LED_MERGE_10_LED) && defined(BMC_RGB_LED_MERGE_10_LED2) && defined(BMC_RGB_LED_MERGE_10_LED3)
#undef BMC_MAX_RGB_LED_MERGE
#define BMC_MAX_RGB_LED_MERGE 10
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_BI_GLOBAL_LED_MERGE 0
#if BMC_MAX_GLOBAL_LEDS >= 2
#if BMC_MAX_GLOBAL_LEDS >= 2  && defined(BMC_BI_GLOBAL_LED_MERGE_1_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_1_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 1
#if BMC_MAX_GLOBAL_LEDS >= 4  && defined(BMC_BI_GLOBAL_LED_MERGE_2_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_2_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 2
#if BMC_MAX_GLOBAL_LEDS >= 6  && defined(BMC_BI_GLOBAL_LED_MERGE_3_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_3_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 3
#if BMC_MAX_GLOBAL_LEDS >= 8  && defined(BMC_BI_GLOBAL_LED_MERGE_4_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_4_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 4
#if BMC_MAX_GLOBAL_LEDS >= 10  && defined(BMC_BI_GLOBAL_LED_MERGE_5_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_5_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 5
#if BMC_MAX_GLOBAL_LEDS >= 12  && defined(BMC_BI_GLOBAL_LED_MERGE_6_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_6_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 6
#if BMC_MAX_GLOBAL_LEDS >= 14  && defined(BMC_BI_GLOBAL_LED_MERGE_7_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_7_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 7
#if BMC_MAX_GLOBAL_LEDS >= 16  && defined(BMC_BI_GLOBAL_LED_MERGE_8_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_8_LED2)
#undef BMC_MAX_BI_GLOBAL_LED_MERGE
#define BMC_MAX_BI_GLOBAL_LED_MERGE 8
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_RGB_GLOBAL_LED_MERGE 0
#if BMC_MAX_GLOBAL_LEDS >= 3
#if BMC_MAX_GLOBAL_LEDS >= 3  && defined(BMC_RGB_GLOBAL_LED_MERGE_1_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_1_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_1_LED3)
#undef BMC_MAX_RGB_GLOBAL_LED_MERGE
#define BMC_MAX_RGB_GLOBAL_LED_MERGE 1
#if BMC_MAX_GLOBAL_LEDS >= 6  && defined(BMC_RGB_GLOBAL_LED_MERGE_2_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_2_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_2_LED3)
#undef BMC_MAX_RGB_GLOBAL_LED_MERGE
#define BMC_MAX_RGB_GLOBAL_LED_MERGE 2
#if BMC_MAX_GLOBAL_LEDS >= 9  && defined(BMC_RGB_GLOBAL_LED_MERGE_3_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_3_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_3_LED3)
#undef BMC_MAX_RGB_GLOBAL_LED_MERGE
#define BMC_MAX_RGB_GLOBAL_LED_MERGE 3
#if BMC_MAX_GLOBAL_LEDS >= 12  && defined(BMC_RGB_GLOBAL_LED_MERGE_4_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_4_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_4_LED3)
#undef BMC_MAX_RGB_GLOBAL_LED_MERGE
#define BMC_MAX_RGB_GLOBAL_LED_MERGE 4
#if BMC_MAX_GLOBAL_LEDS >= 15  && defined(BMC_RGB_GLOBAL_LED_MERGE_5_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_5_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_5_LED3)
#undef BMC_MAX_RGB_GLOBAL_LED_MERGE
#define BMC_MAX_RGB_GLOBAL_LED_MERGE 5
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_BI_PWM_LED_MERGE 0
#if BMC_MAX_PWM_LEDS >= 2
#if BMC_MAX_PWM_LEDS >= 2  && defined(BMC_BI_PWM_LED_MERGE_1_LED) && defined(BMC_BI_PWM_LED_MERGE_1_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 1
#if BMC_MAX_PWM_LEDS >= 4  && defined(BMC_BI_PWM_LED_MERGE_2_LED) && defined(BMC_BI_PWM_LED_MERGE_2_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 2
#if BMC_MAX_PWM_LEDS >= 6  && defined(BMC_BI_PWM_LED_MERGE_3_LED) && defined(BMC_BI_PWM_LED_MERGE_3_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 3
#if BMC_MAX_PWM_LEDS >= 8  && defined(BMC_BI_PWM_LED_MERGE_4_LED) && defined(BMC_BI_PWM_LED_MERGE_4_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 4
#if BMC_MAX_PWM_LEDS >= 10  && defined(BMC_BI_PWM_LED_MERGE_5_LED) && defined(BMC_BI_PWM_LED_MERGE_5_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 5
#if BMC_MAX_PWM_LEDS >= 12  && defined(BMC_BI_PWM_LED_MERGE_6_LED) && defined(BMC_BI_PWM_LED_MERGE_6_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 6
#if BMC_MAX_PWM_LEDS >= 14  && defined(BMC_BI_PWM_LED_MERGE_7_LED) && defined(BMC_BI_PWM_LED_MERGE_7_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 7
#if BMC_MAX_PWM_LEDS >= 16  && defined(BMC_BI_PWM_LED_MERGE_8_LED) && defined(BMC_BI_PWM_LED_MERGE_8_LED2)
#undef BMC_MAX_BI_PWM_LED_MERGE
#define BMC_MAX_BI_PWM_LED_MERGE 8
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_RGB_PWM_LED_MERGE 0
#if BMC_MAX_PWM_LEDS >= 3
#if BMC_MAX_PWM_LEDS >= 3  && defined(BMC_RGB_PWM_LED_MERGE_1_LED) && defined(BMC_RGB_PWM_LED_MERGE_1_LED2) && defined(BMC_RGB_PWM_LED_MERGE_1_LED3)
#undef BMC_MAX_RGB_PWM_LED_MERGE
#define BMC_MAX_RGB_PWM_LED_MERGE 1
#if BMC_MAX_PWM_LEDS >= 6  && defined(BMC_RGB_PWM_LED_MERGE_2_LED) && defined(BMC_RGB_PWM_LED_MERGE_2_LED2) && defined(BMC_RGB_PWM_LED_MERGE_2_LED3)
#undef BMC_MAX_RGB_PWM_LED_MERGE
#define BMC_MAX_RGB_PWM_LED_MERGE 2
#if BMC_MAX_PWM_LEDS >= 9  && defined(BMC_RGB_PWM_LED_MERGE_3_LED) && defined(BMC_RGB_PWM_LED_MERGE_3_LED2) && defined(BMC_RGB_PWM_LED_MERGE_3_LED3)
#undef BMC_MAX_RGB_PWM_LED_MERGE
#define BMC_MAX_RGB_PWM_LED_MERGE 3
#if BMC_MAX_PWM_LEDS >= 12  && defined(BMC_RGB_PWM_LED_MERGE_4_LED) && defined(BMC_RGB_PWM_LED_MERGE_4_LED2) && defined(BMC_RGB_PWM_LED_MERGE_4_LED3)
#undef BMC_MAX_RGB_PWM_LED_MERGE
#define BMC_MAX_RGB_PWM_LED_MERGE 4
#if BMC_MAX_PWM_LEDS >= 15  && defined(BMC_RGB_PWM_LED_MERGE_5_LED) && defined(BMC_RGB_PWM_LED_MERGE_5_LED2) && defined(BMC_RGB_PWM_LED_MERGE_5_LED3)
#undef BMC_MAX_RGB_PWM_LED_MERGE
#define BMC_MAX_RGB_PWM_LED_MERGE 5
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_RELAY_L_MERGE 0
#if BMC_MAX_L_RELAYS >= 2
#if BMC_MAX_L_RELAYS >= 2  && defined(BMC_RELAY_L_MERGE_1_RELAY) && defined(BMC_RELAY_L_MERGE_1_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 1
#if BMC_MAX_L_RELAYS >= 4  && defined(BMC_RELAY_L_MERGE_2_RELAY) && defined(BMC_RELAY_L_MERGE_2_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 2
#if BMC_MAX_L_RELAYS >= 6  && defined(BMC_RELAY_L_MERGE_3_RELAY) && defined(BMC_RELAY_L_MERGE_3_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 3
#if BMC_MAX_L_RELAYS >= 8  && defined(BMC_RELAY_L_MERGE_4_RELAY) && defined(BMC_RELAY_L_MERGE_4_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 4
#if BMC_MAX_L_RELAYS >= 10  && defined(BMC_RELAY_L_MERGE_5_RELAY) && defined(BMC_RELAY_L_MERGE_5_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 5
#if BMC_MAX_L_RELAYS >= 12  && defined(BMC_RELAY_L_MERGE_6_RELAY) && defined(BMC_RELAY_L_MERGE_6_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 6
#if BMC_MAX_L_RELAYS >= 14  && defined(BMC_RELAY_L_MERGE_7_RELAY) && defined(BMC_RELAY_L_MERGE_7_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 7
#if BMC_MAX_L_RELAYS >= 16  && defined(BMC_RELAY_L_MERGE_8_RELAY) && defined(BMC_RELAY_L_MERGE_8_RELAY2)
#undef BMC_MAX_RELAY_L_MERGE
#define BMC_MAX_RELAY_L_MERGE 8
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#define BMC_MAX_RELAY_NL_MERGE 0
#if BMC_MAX_NL_RELAYS >= 2
#if BMC_MAX_NL_RELAYS >= 2  && defined(BMC_RELAY_NL_MERGE_1_RELAY) && defined(BMC_RELAY_NL_MERGE_1_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 1
#if BMC_MAX_NL_RELAYS >= 4  && defined(BMC_RELAY_NL_MERGE_2_RELAY) && defined(BMC_RELAY_NL_MERGE_2_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 2
#if BMC_MAX_NL_RELAYS >= 6  && defined(BMC_RELAY_NL_MERGE_3_RELAY) && defined(BMC_RELAY_NL_MERGE_3_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 3
#if BMC_MAX_NL_RELAYS >= 8  && defined(BMC_RELAY_NL_MERGE_4_RELAY) && defined(BMC_RELAY_NL_MERGE_4_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 4
#if BMC_MAX_NL_RELAYS >= 10  && defined(BMC_RELAY_NL_MERGE_5_RELAY) && defined(BMC_RELAY_NL_MERGE_5_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 5
#if BMC_MAX_NL_RELAYS >= 12  && defined(BMC_RELAY_NL_MERGE_6_RELAY) && defined(BMC_RELAY_NL_MERGE_6_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 6
#if BMC_MAX_NL_RELAYS >= 14  && defined(BMC_RELAY_NL_MERGE_7_RELAY) && defined(BMC_RELAY_NL_MERGE_7_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 7
#if BMC_MAX_NL_RELAYS >= 16  && defined(BMC_RELAY_NL_MERGE_8_RELAY) && defined(BMC_RELAY_NL_MERGE_8_RELAY2)
#undef BMC_MAX_RELAY_NL_MERGE
#define BMC_MAX_RELAY_NL_MERGE 8
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
