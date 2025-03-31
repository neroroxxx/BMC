/*
See https://www.RoxXxtar.com/bmc for more details
Copyright (c) 2025 RoxXxtar.com
See BMC Documentation for License
See LICENSE file in the project root for full license information.
*/

#ifndef BMC_CONFIG_CHECK_PINS_H
#define BMC_CONFIG_CHECK_PINS_H


#ifndef BMC_MAX_PAGES
  #define BMC_MAX_PAGES 1
#endif


#ifndef BMC_MAX_MUX_GPIO
  #define BMC_MAX_MUX_GPIO 0
#endif

#ifndef BMC_MAX_MUX_IN
  #define BMC_MAX_MUX_IN 0
#endif

#ifndef BMC_MAX_MUX_OUT
  #define BMC_MAX_MUX_OUT 0
#endif

#ifndef BMC_MAX_MUX_IN_ANALOG
  #define BMC_MAX_MUX_IN_ANALOG 0
#endif

#ifndef BMC_MAX_MUX_IN_KEYPAD
  #define BMC_MAX_MUX_IN_KEYPAD 0
#endif

#ifndef BMC_MAX_BUTTON_EVENTS
  #define BMC_MAX_BUTTON_EVENTS 0
#endif

// *******************************************
// *** BUTTONS start
// *******************************************

#ifdef BMC_MAX_BUTTONS
  #undef BMC_MAX_BUTTONS
#endif

#define BMC_MAX_BUTTONS 0

#if defined(BMC_DEVICE_UI_BUTTON_1) && BMC_MAX_BUTTONS == 0 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 1
#endif

#if defined(BMC_DEVICE_UI_BUTTON_2) && defined(BMC_DEVICE_UI_BUTTON_1) && BMC_MAX_BUTTONS == 1 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 2
#endif

#if defined(BMC_DEVICE_UI_BUTTON_3) && defined(BMC_DEVICE_UI_BUTTON_2) && BMC_MAX_BUTTONS == 2 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 3
#endif

#if defined(BMC_DEVICE_UI_BUTTON_4) && defined(BMC_DEVICE_UI_BUTTON_3) && BMC_MAX_BUTTONS == 3 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 4
#endif

#if defined(BMC_DEVICE_UI_BUTTON_5) && defined(BMC_DEVICE_UI_BUTTON_4) && BMC_MAX_BUTTONS == 4 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 5
#endif

#if defined(BMC_DEVICE_UI_BUTTON_6) && defined(BMC_DEVICE_UI_BUTTON_5) && BMC_MAX_BUTTONS == 5 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 6
#endif

#if defined(BMC_DEVICE_UI_BUTTON_7) && defined(BMC_DEVICE_UI_BUTTON_6) && BMC_MAX_BUTTONS == 6 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 7
#endif

#if defined(BMC_DEVICE_UI_BUTTON_8) && defined(BMC_DEVICE_UI_BUTTON_7) && BMC_MAX_BUTTONS == 7 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 8
#endif

#if defined(BMC_DEVICE_UI_BUTTON_9) && defined(BMC_DEVICE_UI_BUTTON_8) && BMC_MAX_BUTTONS == 8 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 9
#endif

#if defined(BMC_DEVICE_UI_BUTTON_10) && defined(BMC_DEVICE_UI_BUTTON_9) && BMC_MAX_BUTTONS == 9 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 10
#endif

#if defined(BMC_DEVICE_UI_BUTTON_11) && defined(BMC_DEVICE_UI_BUTTON_10) && BMC_MAX_BUTTONS == 10 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 11
#endif

#if defined(BMC_DEVICE_UI_BUTTON_12) && defined(BMC_DEVICE_UI_BUTTON_11) && BMC_MAX_BUTTONS == 11 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 12
#endif

#if defined(BMC_DEVICE_UI_BUTTON_13) && defined(BMC_DEVICE_UI_BUTTON_12) && BMC_MAX_BUTTONS == 12 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 13
#endif

#if defined(BMC_DEVICE_UI_BUTTON_14) && defined(BMC_DEVICE_UI_BUTTON_13) && BMC_MAX_BUTTONS == 13 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 14
#endif

#if defined(BMC_DEVICE_UI_BUTTON_15) && defined(BMC_DEVICE_UI_BUTTON_14) && BMC_MAX_BUTTONS == 14 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 15
#endif

#if defined(BMC_DEVICE_UI_BUTTON_16) && defined(BMC_DEVICE_UI_BUTTON_15) && BMC_MAX_BUTTONS == 15 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 16
#endif

#if defined(BMC_DEVICE_UI_BUTTON_17) && defined(BMC_DEVICE_UI_BUTTON_16) && BMC_MAX_BUTTONS == 16 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 17
#endif

#if defined(BMC_DEVICE_UI_BUTTON_18) && defined(BMC_DEVICE_UI_BUTTON_17) && BMC_MAX_BUTTONS == 17 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 18
#endif

#if defined(BMC_DEVICE_UI_BUTTON_19) && defined(BMC_DEVICE_UI_BUTTON_18) && BMC_MAX_BUTTONS == 18 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 19
#endif

#if defined(BMC_DEVICE_UI_BUTTON_20) && defined(BMC_DEVICE_UI_BUTTON_19) && BMC_MAX_BUTTONS == 19 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 20
#endif

#if defined(BMC_DEVICE_UI_BUTTON_21) && defined(BMC_DEVICE_UI_BUTTON_20) && BMC_MAX_BUTTONS == 20 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 21
#endif

#if defined(BMC_DEVICE_UI_BUTTON_22) && defined(BMC_DEVICE_UI_BUTTON_21) && BMC_MAX_BUTTONS == 21 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 22
#endif

#if defined(BMC_DEVICE_UI_BUTTON_23) && defined(BMC_DEVICE_UI_BUTTON_22) && BMC_MAX_BUTTONS == 22 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 23
#endif

#if defined(BMC_DEVICE_UI_BUTTON_24) && defined(BMC_DEVICE_UI_BUTTON_23) && BMC_MAX_BUTTONS == 23 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 24
#endif

#if defined(BMC_DEVICE_UI_BUTTON_25) && defined(BMC_DEVICE_UI_BUTTON_24) && BMC_MAX_BUTTONS == 24 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 25
#endif

#if defined(BMC_DEVICE_UI_BUTTON_26) && defined(BMC_DEVICE_UI_BUTTON_25) && BMC_MAX_BUTTONS == 25 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 26
#endif

#if defined(BMC_DEVICE_UI_BUTTON_27) && defined(BMC_DEVICE_UI_BUTTON_26) && BMC_MAX_BUTTONS == 26 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 27
#endif

#if defined(BMC_DEVICE_UI_BUTTON_28) && defined(BMC_DEVICE_UI_BUTTON_27) && BMC_MAX_BUTTONS == 27 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 28
#endif

#if defined(BMC_DEVICE_UI_BUTTON_29) && defined(BMC_DEVICE_UI_BUTTON_28) && BMC_MAX_BUTTONS == 28 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 29
#endif

#if defined(BMC_DEVICE_UI_BUTTON_30) && defined(BMC_DEVICE_UI_BUTTON_29) && BMC_MAX_BUTTONS == 29 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 30
#endif

#if defined(BMC_DEVICE_UI_BUTTON_31) && defined(BMC_DEVICE_UI_BUTTON_30) && BMC_MAX_BUTTONS == 30 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 31
#endif

#if defined(BMC_DEVICE_UI_BUTTON_32) && defined(BMC_DEVICE_UI_BUTTON_31) && BMC_MAX_BUTTONS == 31 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 32
#endif

#if defined(BMC_DEVICE_UI_BUTTON_33) && defined(BMC_DEVICE_UI_BUTTON_32) && BMC_MAX_BUTTONS == 32 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 33
#endif

#if defined(BMC_DEVICE_UI_BUTTON_34) && defined(BMC_DEVICE_UI_BUTTON_33) && BMC_MAX_BUTTONS == 33 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 34
#endif

#if defined(BMC_DEVICE_UI_BUTTON_35) && defined(BMC_DEVICE_UI_BUTTON_34) && BMC_MAX_BUTTONS == 34 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 35
#endif

#if defined(BMC_DEVICE_UI_BUTTON_36) && defined(BMC_DEVICE_UI_BUTTON_35) && BMC_MAX_BUTTONS == 35 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 36
#endif

#if defined(BMC_DEVICE_UI_BUTTON_37) && defined(BMC_DEVICE_UI_BUTTON_36) && BMC_MAX_BUTTONS == 36 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 37
#endif

#if defined(BMC_DEVICE_UI_BUTTON_38) && defined(BMC_DEVICE_UI_BUTTON_37) && BMC_MAX_BUTTONS == 37 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 38
#endif

#if defined(BMC_DEVICE_UI_BUTTON_39) && defined(BMC_DEVICE_UI_BUTTON_38) && BMC_MAX_BUTTONS == 38 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 39
#endif

#if defined(BMC_DEVICE_UI_BUTTON_40) && defined(BMC_DEVICE_UI_BUTTON_39) && BMC_MAX_BUTTONS == 39 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 40
#endif

#if defined(BMC_DEVICE_UI_BUTTON_41) && defined(BMC_DEVICE_UI_BUTTON_40) && BMC_MAX_BUTTONS == 40 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 41
#endif

#if defined(BMC_DEVICE_UI_BUTTON_42) && defined(BMC_DEVICE_UI_BUTTON_41) && BMC_MAX_BUTTONS == 41 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 42
#endif

#if defined(BMC_DEVICE_UI_BUTTON_43) && defined(BMC_DEVICE_UI_BUTTON_42) && BMC_MAX_BUTTONS == 42 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 43
#endif

#if defined(BMC_DEVICE_UI_BUTTON_44) && defined(BMC_DEVICE_UI_BUTTON_43) && BMC_MAX_BUTTONS == 43 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 44
#endif

#if defined(BMC_DEVICE_UI_BUTTON_45) && defined(BMC_DEVICE_UI_BUTTON_44) && BMC_MAX_BUTTONS == 44 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 45
#endif

#if defined(BMC_DEVICE_UI_BUTTON_46) && defined(BMC_DEVICE_UI_BUTTON_45) && BMC_MAX_BUTTONS == 45 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 46
#endif

#if defined(BMC_DEVICE_UI_BUTTON_47) && defined(BMC_DEVICE_UI_BUTTON_46) && BMC_MAX_BUTTONS == 46 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 47
#endif

#if defined(BMC_DEVICE_UI_BUTTON_48) && defined(BMC_DEVICE_UI_BUTTON_47) && BMC_MAX_BUTTONS == 47 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 48
#endif

#if defined(BMC_DEVICE_UI_BUTTON_49) && defined(BMC_DEVICE_UI_BUTTON_48) && BMC_MAX_BUTTONS == 48 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 49
#endif

#if defined(BMC_DEVICE_UI_BUTTON_50) && defined(BMC_DEVICE_UI_BUTTON_49) && BMC_MAX_BUTTONS == 49 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 50
#endif

#if defined(BMC_DEVICE_UI_BUTTON_51) && defined(BMC_DEVICE_UI_BUTTON_50) && BMC_MAX_BUTTONS == 50 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 51
#endif

#if defined(BMC_DEVICE_UI_BUTTON_52) && defined(BMC_DEVICE_UI_BUTTON_51) && BMC_MAX_BUTTONS == 51 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 52
#endif

#if defined(BMC_DEVICE_UI_BUTTON_53) && defined(BMC_DEVICE_UI_BUTTON_52) && BMC_MAX_BUTTONS == 52 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 53
#endif

#if defined(BMC_DEVICE_UI_BUTTON_54) && defined(BMC_DEVICE_UI_BUTTON_53) && BMC_MAX_BUTTONS == 53 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 54
#endif

#if defined(BMC_DEVICE_UI_BUTTON_55) && defined(BMC_DEVICE_UI_BUTTON_54) && BMC_MAX_BUTTONS == 54 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 55
#endif

#if defined(BMC_DEVICE_UI_BUTTON_56) && defined(BMC_DEVICE_UI_BUTTON_55) && BMC_MAX_BUTTONS == 55 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 56
#endif

#if defined(BMC_DEVICE_UI_BUTTON_57) && defined(BMC_DEVICE_UI_BUTTON_56) && BMC_MAX_BUTTONS == 56 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 57
#endif

#if defined(BMC_DEVICE_UI_BUTTON_58) && defined(BMC_DEVICE_UI_BUTTON_57) && BMC_MAX_BUTTONS == 57 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 58
#endif

#if defined(BMC_DEVICE_UI_BUTTON_59) && defined(BMC_DEVICE_UI_BUTTON_58) && BMC_MAX_BUTTONS == 58 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 59
#endif

#if defined(BMC_DEVICE_UI_BUTTON_60) && defined(BMC_DEVICE_UI_BUTTON_59) && BMC_MAX_BUTTONS == 59 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 60
#endif

#if defined(BMC_DEVICE_UI_BUTTON_61) && defined(BMC_DEVICE_UI_BUTTON_60) && BMC_MAX_BUTTONS == 60 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 61
#endif

#if defined(BMC_DEVICE_UI_BUTTON_62) && defined(BMC_DEVICE_UI_BUTTON_61) && BMC_MAX_BUTTONS == 61 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 62
#endif

#if defined(BMC_DEVICE_UI_BUTTON_63) && defined(BMC_DEVICE_UI_BUTTON_62) && BMC_MAX_BUTTONS == 62 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 63
#endif

#if defined(BMC_DEVICE_UI_BUTTON_64) && defined(BMC_DEVICE_UI_BUTTON_63) && BMC_MAX_BUTTONS == 63 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 64
#endif

#if defined(BMC_DEVICE_UI_BUTTON_65) && defined(BMC_DEVICE_UI_BUTTON_64) && BMC_MAX_BUTTONS == 64 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 65
#endif

#if defined(BMC_DEVICE_UI_BUTTON_66) && defined(BMC_DEVICE_UI_BUTTON_65) && BMC_MAX_BUTTONS == 65 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 66
#endif

#if defined(BMC_DEVICE_UI_BUTTON_67) && defined(BMC_DEVICE_UI_BUTTON_66) && BMC_MAX_BUTTONS == 66 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 67
#endif

#if defined(BMC_DEVICE_UI_BUTTON_68) && defined(BMC_DEVICE_UI_BUTTON_67) && BMC_MAX_BUTTONS == 67 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 68
#endif

#if defined(BMC_DEVICE_UI_BUTTON_69) && defined(BMC_DEVICE_UI_BUTTON_68) && BMC_MAX_BUTTONS == 68 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 69
#endif

#if defined(BMC_DEVICE_UI_BUTTON_70) && defined(BMC_DEVICE_UI_BUTTON_69) && BMC_MAX_BUTTONS == 69 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 70
#endif

#if defined(BMC_DEVICE_UI_BUTTON_71) && defined(BMC_DEVICE_UI_BUTTON_70) && BMC_MAX_BUTTONS == 70 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 71
#endif

#if defined(BMC_DEVICE_UI_BUTTON_72) && defined(BMC_DEVICE_UI_BUTTON_71) && BMC_MAX_BUTTONS == 71 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 72
#endif

#if defined(BMC_DEVICE_UI_BUTTON_73) && defined(BMC_DEVICE_UI_BUTTON_72) && BMC_MAX_BUTTONS == 72 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 73
#endif

#if defined(BMC_DEVICE_UI_BUTTON_74) && defined(BMC_DEVICE_UI_BUTTON_73) && BMC_MAX_BUTTONS == 73 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 74
#endif

#if defined(BMC_DEVICE_UI_BUTTON_75) && defined(BMC_DEVICE_UI_BUTTON_74) && BMC_MAX_BUTTONS == 74 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 75
#endif

#if defined(BMC_DEVICE_UI_BUTTON_76) && defined(BMC_DEVICE_UI_BUTTON_75) && BMC_MAX_BUTTONS == 75 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 76
#endif

#if defined(BMC_DEVICE_UI_BUTTON_77) && defined(BMC_DEVICE_UI_BUTTON_76) && BMC_MAX_BUTTONS == 76 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 77
#endif

#if defined(BMC_DEVICE_UI_BUTTON_78) && defined(BMC_DEVICE_UI_BUTTON_77) && BMC_MAX_BUTTONS == 77 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 78
#endif

#if defined(BMC_DEVICE_UI_BUTTON_79) && defined(BMC_DEVICE_UI_BUTTON_78) && BMC_MAX_BUTTONS == 78 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 79
#endif

#if defined(BMC_DEVICE_UI_BUTTON_80) && defined(BMC_DEVICE_UI_BUTTON_79) && BMC_MAX_BUTTONS == 79 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 80
#endif

#if defined(BMC_DEVICE_UI_BUTTON_81) && defined(BMC_DEVICE_UI_BUTTON_80) && BMC_MAX_BUTTONS == 80 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 81
#endif

#if defined(BMC_DEVICE_UI_BUTTON_82) && defined(BMC_DEVICE_UI_BUTTON_81) && BMC_MAX_BUTTONS == 81 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 82
#endif

#if defined(BMC_DEVICE_UI_BUTTON_83) && defined(BMC_DEVICE_UI_BUTTON_82) && BMC_MAX_BUTTONS == 82 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 83
#endif

#if defined(BMC_DEVICE_UI_BUTTON_84) && defined(BMC_DEVICE_UI_BUTTON_83) && BMC_MAX_BUTTONS == 83 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 84
#endif

#if defined(BMC_DEVICE_UI_BUTTON_85) && defined(BMC_DEVICE_UI_BUTTON_84) && BMC_MAX_BUTTONS == 84 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 85
#endif

#if defined(BMC_DEVICE_UI_BUTTON_86) && defined(BMC_DEVICE_UI_BUTTON_85) && BMC_MAX_BUTTONS == 85 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 86
#endif

#if defined(BMC_DEVICE_UI_BUTTON_87) && defined(BMC_DEVICE_UI_BUTTON_86) && BMC_MAX_BUTTONS == 86 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 87
#endif

#if defined(BMC_DEVICE_UI_BUTTON_88) && defined(BMC_DEVICE_UI_BUTTON_87) && BMC_MAX_BUTTONS == 87 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 88
#endif

#if defined(BMC_DEVICE_UI_BUTTON_89) && defined(BMC_DEVICE_UI_BUTTON_88) && BMC_MAX_BUTTONS == 88 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 89
#endif

#if defined(BMC_DEVICE_UI_BUTTON_90) && defined(BMC_DEVICE_UI_BUTTON_89) && BMC_MAX_BUTTONS == 89 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 90
#endif

#if defined(BMC_DEVICE_UI_BUTTON_91) && defined(BMC_DEVICE_UI_BUTTON_90) && BMC_MAX_BUTTONS == 90 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 91
#endif

#if defined(BMC_DEVICE_UI_BUTTON_92) && defined(BMC_DEVICE_UI_BUTTON_91) && BMC_MAX_BUTTONS == 91 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 92
#endif

#if defined(BMC_DEVICE_UI_BUTTON_93) && defined(BMC_DEVICE_UI_BUTTON_92) && BMC_MAX_BUTTONS == 92 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 93
#endif

#if defined(BMC_DEVICE_UI_BUTTON_94) && defined(BMC_DEVICE_UI_BUTTON_93) && BMC_MAX_BUTTONS == 93 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 94
#endif

#if defined(BMC_DEVICE_UI_BUTTON_95) && defined(BMC_DEVICE_UI_BUTTON_94) && BMC_MAX_BUTTONS == 94 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 95
#endif

#if defined(BMC_DEVICE_UI_BUTTON_96) && defined(BMC_DEVICE_UI_BUTTON_95) && BMC_MAX_BUTTONS == 95 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 96
#endif

#if defined(BMC_DEVICE_UI_BUTTON_97) && defined(BMC_DEVICE_UI_BUTTON_96) && BMC_MAX_BUTTONS == 96 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 97
#endif

#if defined(BMC_DEVICE_UI_BUTTON_98) && defined(BMC_DEVICE_UI_BUTTON_97) && BMC_MAX_BUTTONS == 97 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 98
#endif

#if defined(BMC_DEVICE_UI_BUTTON_99) && defined(BMC_DEVICE_UI_BUTTON_98) && BMC_MAX_BUTTONS == 98 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 99
#endif

#if defined(BMC_DEVICE_UI_BUTTON_100) && defined(BMC_DEVICE_UI_BUTTON_99) && BMC_MAX_BUTTONS == 99 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 100
#endif

#if defined(BMC_DEVICE_UI_BUTTON_101) && defined(BMC_DEVICE_UI_BUTTON_100) && BMC_MAX_BUTTONS == 100 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 101
#endif

#if defined(BMC_DEVICE_UI_BUTTON_102) && defined(BMC_DEVICE_UI_BUTTON_101) && BMC_MAX_BUTTONS == 101 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 102
#endif

#if defined(BMC_DEVICE_UI_BUTTON_103) && defined(BMC_DEVICE_UI_BUTTON_102) && BMC_MAX_BUTTONS == 102 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 103
#endif

#if defined(BMC_DEVICE_UI_BUTTON_104) && defined(BMC_DEVICE_UI_BUTTON_103) && BMC_MAX_BUTTONS == 103 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 104
#endif

#if defined(BMC_DEVICE_UI_BUTTON_105) && defined(BMC_DEVICE_UI_BUTTON_104) && BMC_MAX_BUTTONS == 104 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 105
#endif

#if defined(BMC_DEVICE_UI_BUTTON_106) && defined(BMC_DEVICE_UI_BUTTON_105) && BMC_MAX_BUTTONS == 105 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 106
#endif

#if defined(BMC_DEVICE_UI_BUTTON_107) && defined(BMC_DEVICE_UI_BUTTON_106) && BMC_MAX_BUTTONS == 106 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 107
#endif

#if defined(BMC_DEVICE_UI_BUTTON_108) && defined(BMC_DEVICE_UI_BUTTON_107) && BMC_MAX_BUTTONS == 107 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 108
#endif

#if defined(BMC_DEVICE_UI_BUTTON_109) && defined(BMC_DEVICE_UI_BUTTON_108) && BMC_MAX_BUTTONS == 108 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 109
#endif

#if defined(BMC_DEVICE_UI_BUTTON_110) && defined(BMC_DEVICE_UI_BUTTON_109) && BMC_MAX_BUTTONS == 109 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 110
#endif

#if defined(BMC_DEVICE_UI_BUTTON_111) && defined(BMC_DEVICE_UI_BUTTON_110) && BMC_MAX_BUTTONS == 110 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 111
#endif

#if defined(BMC_DEVICE_UI_BUTTON_112) && defined(BMC_DEVICE_UI_BUTTON_111) && BMC_MAX_BUTTONS == 111 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 112
#endif

#if defined(BMC_DEVICE_UI_BUTTON_113) && defined(BMC_DEVICE_UI_BUTTON_112) && BMC_MAX_BUTTONS == 112 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 113
#endif

#if defined(BMC_DEVICE_UI_BUTTON_114) && defined(BMC_DEVICE_UI_BUTTON_113) && BMC_MAX_BUTTONS == 113 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 114
#endif

#if defined(BMC_DEVICE_UI_BUTTON_115) && defined(BMC_DEVICE_UI_BUTTON_114) && BMC_MAX_BUTTONS == 114 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 115
#endif

#if defined(BMC_DEVICE_UI_BUTTON_116) && defined(BMC_DEVICE_UI_BUTTON_115) && BMC_MAX_BUTTONS == 115 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 116
#endif

#if defined(BMC_DEVICE_UI_BUTTON_117) && defined(BMC_DEVICE_UI_BUTTON_116) && BMC_MAX_BUTTONS == 116 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 117
#endif

#if defined(BMC_DEVICE_UI_BUTTON_118) && defined(BMC_DEVICE_UI_BUTTON_117) && BMC_MAX_BUTTONS == 117 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 118
#endif

#if defined(BMC_DEVICE_UI_BUTTON_119) && defined(BMC_DEVICE_UI_BUTTON_118) && BMC_MAX_BUTTONS == 118 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 119
#endif

#if defined(BMC_DEVICE_UI_BUTTON_120) && defined(BMC_DEVICE_UI_BUTTON_119) && BMC_MAX_BUTTONS == 119 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 120
#endif

#if defined(BMC_DEVICE_UI_BUTTON_121) && defined(BMC_DEVICE_UI_BUTTON_120) && BMC_MAX_BUTTONS == 120 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 121
#endif

#if defined(BMC_DEVICE_UI_BUTTON_122) && defined(BMC_DEVICE_UI_BUTTON_121) && BMC_MAX_BUTTONS == 121 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 122
#endif

#if defined(BMC_DEVICE_UI_BUTTON_123) && defined(BMC_DEVICE_UI_BUTTON_122) && BMC_MAX_BUTTONS == 122 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 123
#endif

#if defined(BMC_DEVICE_UI_BUTTON_124) && defined(BMC_DEVICE_UI_BUTTON_123) && BMC_MAX_BUTTONS == 123 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 124
#endif

#if defined(BMC_DEVICE_UI_BUTTON_125) && defined(BMC_DEVICE_UI_BUTTON_124) && BMC_MAX_BUTTONS == 124 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 125
#endif

#if defined(BMC_DEVICE_UI_BUTTON_126) && defined(BMC_DEVICE_UI_BUTTON_125) && BMC_MAX_BUTTONS == 125 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 126
#endif

#if defined(BMC_DEVICE_UI_BUTTON_127) && defined(BMC_DEVICE_UI_BUTTON_126) && BMC_MAX_BUTTONS == 126 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 127
#endif

#if defined(BMC_DEVICE_UI_BUTTON_128) && defined(BMC_DEVICE_UI_BUTTON_127) && BMC_MAX_BUTTONS == 127 
  #ifdef BMC_MAX_BUTTONS
    #undef BMC_MAX_BUTTONS
  #endif

  #define BMC_MAX_BUTTONS 128
#endif

// *******************************************
// *** BUTTONS end
// *******************************************

// *******************************************
// *** GLOBAL_BUTTONS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_BUTTONS
  #undef BMC_MAX_GLOBAL_BUTTONS
#endif

#define BMC_MAX_GLOBAL_BUTTONS 0

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_1) && BMC_MAX_GLOBAL_BUTTONS == 0 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_2) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_1) && BMC_MAX_GLOBAL_BUTTONS == 1 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_3) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_2) && BMC_MAX_GLOBAL_BUTTONS == 2 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_4) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_3) && BMC_MAX_GLOBAL_BUTTONS == 3 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_5) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_4) && BMC_MAX_GLOBAL_BUTTONS == 4 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_6) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_5) && BMC_MAX_GLOBAL_BUTTONS == 5 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_7) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_6) && BMC_MAX_GLOBAL_BUTTONS == 6 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_8) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_7) && BMC_MAX_GLOBAL_BUTTONS == 7 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_9) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_8) && BMC_MAX_GLOBAL_BUTTONS == 8 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_10) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_9) && BMC_MAX_GLOBAL_BUTTONS == 9 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_11) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_10) && BMC_MAX_GLOBAL_BUTTONS == 10 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_12) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_11) && BMC_MAX_GLOBAL_BUTTONS == 11 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_13) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_12) && BMC_MAX_GLOBAL_BUTTONS == 12 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_14) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_13) && BMC_MAX_GLOBAL_BUTTONS == 13 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_15) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_14) && BMC_MAX_GLOBAL_BUTTONS == 14 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_16) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_15) && BMC_MAX_GLOBAL_BUTTONS == 15 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_17) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_16) && BMC_MAX_GLOBAL_BUTTONS == 16 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_18) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_17) && BMC_MAX_GLOBAL_BUTTONS == 17 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_19) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_18) && BMC_MAX_GLOBAL_BUTTONS == 18 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_20) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_19) && BMC_MAX_GLOBAL_BUTTONS == 19 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_21) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_20) && BMC_MAX_GLOBAL_BUTTONS == 20 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_22) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_21) && BMC_MAX_GLOBAL_BUTTONS == 21 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_23) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_22) && BMC_MAX_GLOBAL_BUTTONS == 22 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_24) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_23) && BMC_MAX_GLOBAL_BUTTONS == 23 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_25) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_24) && BMC_MAX_GLOBAL_BUTTONS == 24 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_26) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_25) && BMC_MAX_GLOBAL_BUTTONS == 25 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_27) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_26) && BMC_MAX_GLOBAL_BUTTONS == 26 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_28) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_27) && BMC_MAX_GLOBAL_BUTTONS == 27 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_29) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_28) && BMC_MAX_GLOBAL_BUTTONS == 28 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_30) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_29) && BMC_MAX_GLOBAL_BUTTONS == 29 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_31) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_30) && BMC_MAX_GLOBAL_BUTTONS == 30 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_32) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_31) && BMC_MAX_GLOBAL_BUTTONS == 31 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_33) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_32) && BMC_MAX_GLOBAL_BUTTONS == 32 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_34) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_33) && BMC_MAX_GLOBAL_BUTTONS == 33 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_35) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_34) && BMC_MAX_GLOBAL_BUTTONS == 34 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_36) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_35) && BMC_MAX_GLOBAL_BUTTONS == 35 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_37) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_36) && BMC_MAX_GLOBAL_BUTTONS == 36 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_38) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_37) && BMC_MAX_GLOBAL_BUTTONS == 37 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_39) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_38) && BMC_MAX_GLOBAL_BUTTONS == 38 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_40) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_39) && BMC_MAX_GLOBAL_BUTTONS == 39 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_41) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_40) && BMC_MAX_GLOBAL_BUTTONS == 40 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_42) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_41) && BMC_MAX_GLOBAL_BUTTONS == 41 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_43) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_42) && BMC_MAX_GLOBAL_BUTTONS == 42 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_44) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_43) && BMC_MAX_GLOBAL_BUTTONS == 43 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_45) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_44) && BMC_MAX_GLOBAL_BUTTONS == 44 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_46) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_45) && BMC_MAX_GLOBAL_BUTTONS == 45 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_47) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_46) && BMC_MAX_GLOBAL_BUTTONS == 46 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_48) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_47) && BMC_MAX_GLOBAL_BUTTONS == 47 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_49) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_48) && BMC_MAX_GLOBAL_BUTTONS == 48 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_50) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_49) && BMC_MAX_GLOBAL_BUTTONS == 49 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_51) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_50) && BMC_MAX_GLOBAL_BUTTONS == 50 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_52) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_51) && BMC_MAX_GLOBAL_BUTTONS == 51 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_53) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_52) && BMC_MAX_GLOBAL_BUTTONS == 52 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_54) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_53) && BMC_MAX_GLOBAL_BUTTONS == 53 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_55) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_54) && BMC_MAX_GLOBAL_BUTTONS == 54 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_56) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_55) && BMC_MAX_GLOBAL_BUTTONS == 55 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_57) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_56) && BMC_MAX_GLOBAL_BUTTONS == 56 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_58) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_57) && BMC_MAX_GLOBAL_BUTTONS == 57 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_59) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_58) && BMC_MAX_GLOBAL_BUTTONS == 58 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_60) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_59) && BMC_MAX_GLOBAL_BUTTONS == 59 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_61) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_60) && BMC_MAX_GLOBAL_BUTTONS == 60 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_62) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_61) && BMC_MAX_GLOBAL_BUTTONS == 61 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_63) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_62) && BMC_MAX_GLOBAL_BUTTONS == 62 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_64) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_63) && BMC_MAX_GLOBAL_BUTTONS == 63 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 64
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_65) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_64) && BMC_MAX_GLOBAL_BUTTONS == 64 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 65
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_66) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_65) && BMC_MAX_GLOBAL_BUTTONS == 65 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 66
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_67) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_66) && BMC_MAX_GLOBAL_BUTTONS == 66 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 67
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_68) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_67) && BMC_MAX_GLOBAL_BUTTONS == 67 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 68
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_69) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_68) && BMC_MAX_GLOBAL_BUTTONS == 68 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 69
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_70) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_69) && BMC_MAX_GLOBAL_BUTTONS == 69 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 70
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_71) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_70) && BMC_MAX_GLOBAL_BUTTONS == 70 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 71
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_72) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_71) && BMC_MAX_GLOBAL_BUTTONS == 71 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 72
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_73) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_72) && BMC_MAX_GLOBAL_BUTTONS == 72 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 73
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_74) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_73) && BMC_MAX_GLOBAL_BUTTONS == 73 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 74
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_75) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_74) && BMC_MAX_GLOBAL_BUTTONS == 74 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 75
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_76) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_75) && BMC_MAX_GLOBAL_BUTTONS == 75 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 76
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_77) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_76) && BMC_MAX_GLOBAL_BUTTONS == 76 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 77
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_78) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_77) && BMC_MAX_GLOBAL_BUTTONS == 77 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 78
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_79) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_78) && BMC_MAX_GLOBAL_BUTTONS == 78 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 79
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_80) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_79) && BMC_MAX_GLOBAL_BUTTONS == 79 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 80
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_81) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_80) && BMC_MAX_GLOBAL_BUTTONS == 80 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 81
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_82) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_81) && BMC_MAX_GLOBAL_BUTTONS == 81 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 82
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_83) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_82) && BMC_MAX_GLOBAL_BUTTONS == 82 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 83
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_84) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_83) && BMC_MAX_GLOBAL_BUTTONS == 83 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 84
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_85) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_84) && BMC_MAX_GLOBAL_BUTTONS == 84 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 85
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_86) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_85) && BMC_MAX_GLOBAL_BUTTONS == 85 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 86
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_87) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_86) && BMC_MAX_GLOBAL_BUTTONS == 86 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 87
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_88) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_87) && BMC_MAX_GLOBAL_BUTTONS == 87 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 88
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_89) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_88) && BMC_MAX_GLOBAL_BUTTONS == 88 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 89
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_90) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_89) && BMC_MAX_GLOBAL_BUTTONS == 89 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 90
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_91) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_90) && BMC_MAX_GLOBAL_BUTTONS == 90 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 91
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_92) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_91) && BMC_MAX_GLOBAL_BUTTONS == 91 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 92
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_93) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_92) && BMC_MAX_GLOBAL_BUTTONS == 92 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 93
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_94) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_93) && BMC_MAX_GLOBAL_BUTTONS == 93 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 94
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_95) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_94) && BMC_MAX_GLOBAL_BUTTONS == 94 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 95
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_96) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_95) && BMC_MAX_GLOBAL_BUTTONS == 95 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 96
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_97) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_96) && BMC_MAX_GLOBAL_BUTTONS == 96 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 97
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_98) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_97) && BMC_MAX_GLOBAL_BUTTONS == 97 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 98
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_99) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_98) && BMC_MAX_GLOBAL_BUTTONS == 98 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 99
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_100) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_99) && BMC_MAX_GLOBAL_BUTTONS == 99 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 100
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_101) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_100) && BMC_MAX_GLOBAL_BUTTONS == 100 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 101
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_102) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_101) && BMC_MAX_GLOBAL_BUTTONS == 101 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 102
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_103) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_102) && BMC_MAX_GLOBAL_BUTTONS == 102 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 103
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_104) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_103) && BMC_MAX_GLOBAL_BUTTONS == 103 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 104
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_105) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_104) && BMC_MAX_GLOBAL_BUTTONS == 104 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 105
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_106) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_105) && BMC_MAX_GLOBAL_BUTTONS == 105 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 106
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_107) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_106) && BMC_MAX_GLOBAL_BUTTONS == 106 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 107
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_108) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_107) && BMC_MAX_GLOBAL_BUTTONS == 107 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 108
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_109) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_108) && BMC_MAX_GLOBAL_BUTTONS == 108 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 109
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_110) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_109) && BMC_MAX_GLOBAL_BUTTONS == 109 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 110
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_111) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_110) && BMC_MAX_GLOBAL_BUTTONS == 110 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 111
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_112) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_111) && BMC_MAX_GLOBAL_BUTTONS == 111 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 112
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_113) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_112) && BMC_MAX_GLOBAL_BUTTONS == 112 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 113
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_114) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_113) && BMC_MAX_GLOBAL_BUTTONS == 113 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 114
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_115) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_114) && BMC_MAX_GLOBAL_BUTTONS == 114 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 115
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_116) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_115) && BMC_MAX_GLOBAL_BUTTONS == 115 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 116
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_117) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_116) && BMC_MAX_GLOBAL_BUTTONS == 116 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 117
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_118) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_117) && BMC_MAX_GLOBAL_BUTTONS == 117 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 118
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_119) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_118) && BMC_MAX_GLOBAL_BUTTONS == 118 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 119
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_120) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_119) && BMC_MAX_GLOBAL_BUTTONS == 119 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 120
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_121) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_120) && BMC_MAX_GLOBAL_BUTTONS == 120 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 121
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_122) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_121) && BMC_MAX_GLOBAL_BUTTONS == 121 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 122
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_123) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_122) && BMC_MAX_GLOBAL_BUTTONS == 122 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 123
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_124) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_123) && BMC_MAX_GLOBAL_BUTTONS == 123 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 124
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_125) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_124) && BMC_MAX_GLOBAL_BUTTONS == 124 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 125
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_126) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_125) && BMC_MAX_GLOBAL_BUTTONS == 125 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 126
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_127) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_126) && BMC_MAX_GLOBAL_BUTTONS == 126 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 127
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BUTTON_128) && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_127) && BMC_MAX_GLOBAL_BUTTONS == 127 
  #ifdef BMC_MAX_GLOBAL_BUTTONS
    #undef BMC_MAX_GLOBAL_BUTTONS
  #endif

  #define BMC_MAX_GLOBAL_BUTTONS 128
#endif

// *******************************************
// *** GLOBAL_BUTTONS end
// *******************************************

// *******************************************
// *** LEDS start
// *******************************************

#ifdef BMC_MAX_LEDS
  #undef BMC_MAX_LEDS
#endif

#define BMC_MAX_LEDS 0

#if defined(BMC_DEVICE_UI_LED_1) && BMC_MAX_LEDS == 0 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 1
#endif

#if defined(BMC_DEVICE_UI_LED_2) && defined(BMC_DEVICE_UI_LED_1) && BMC_MAX_LEDS == 1 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 2
#endif

#if defined(BMC_DEVICE_UI_LED_3) && defined(BMC_DEVICE_UI_LED_2) && BMC_MAX_LEDS == 2 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 3
#endif

#if defined(BMC_DEVICE_UI_LED_4) && defined(BMC_DEVICE_UI_LED_3) && BMC_MAX_LEDS == 3 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 4
#endif

#if defined(BMC_DEVICE_UI_LED_5) && defined(BMC_DEVICE_UI_LED_4) && BMC_MAX_LEDS == 4 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 5
#endif

#if defined(BMC_DEVICE_UI_LED_6) && defined(BMC_DEVICE_UI_LED_5) && BMC_MAX_LEDS == 5 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 6
#endif

#if defined(BMC_DEVICE_UI_LED_7) && defined(BMC_DEVICE_UI_LED_6) && BMC_MAX_LEDS == 6 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 7
#endif

#if defined(BMC_DEVICE_UI_LED_8) && defined(BMC_DEVICE_UI_LED_7) && BMC_MAX_LEDS == 7 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 8
#endif

#if defined(BMC_DEVICE_UI_LED_9) && defined(BMC_DEVICE_UI_LED_8) && BMC_MAX_LEDS == 8 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 9
#endif

#if defined(BMC_DEVICE_UI_LED_10) && defined(BMC_DEVICE_UI_LED_9) && BMC_MAX_LEDS == 9 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 10
#endif

#if defined(BMC_DEVICE_UI_LED_11) && defined(BMC_DEVICE_UI_LED_10) && BMC_MAX_LEDS == 10 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 11
#endif

#if defined(BMC_DEVICE_UI_LED_12) && defined(BMC_DEVICE_UI_LED_11) && BMC_MAX_LEDS == 11 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 12
#endif

#if defined(BMC_DEVICE_UI_LED_13) && defined(BMC_DEVICE_UI_LED_12) && BMC_MAX_LEDS == 12 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 13
#endif

#if defined(BMC_DEVICE_UI_LED_14) && defined(BMC_DEVICE_UI_LED_13) && BMC_MAX_LEDS == 13 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 14
#endif

#if defined(BMC_DEVICE_UI_LED_15) && defined(BMC_DEVICE_UI_LED_14) && BMC_MAX_LEDS == 14 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 15
#endif

#if defined(BMC_DEVICE_UI_LED_16) && defined(BMC_DEVICE_UI_LED_15) && BMC_MAX_LEDS == 15 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 16
#endif

#if defined(BMC_DEVICE_UI_LED_17) && defined(BMC_DEVICE_UI_LED_16) && BMC_MAX_LEDS == 16 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 17
#endif

#if defined(BMC_DEVICE_UI_LED_18) && defined(BMC_DEVICE_UI_LED_17) && BMC_MAX_LEDS == 17 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 18
#endif

#if defined(BMC_DEVICE_UI_LED_19) && defined(BMC_DEVICE_UI_LED_18) && BMC_MAX_LEDS == 18 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 19
#endif

#if defined(BMC_DEVICE_UI_LED_20) && defined(BMC_DEVICE_UI_LED_19) && BMC_MAX_LEDS == 19 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 20
#endif

#if defined(BMC_DEVICE_UI_LED_21) && defined(BMC_DEVICE_UI_LED_20) && BMC_MAX_LEDS == 20 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 21
#endif

#if defined(BMC_DEVICE_UI_LED_22) && defined(BMC_DEVICE_UI_LED_21) && BMC_MAX_LEDS == 21 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 22
#endif

#if defined(BMC_DEVICE_UI_LED_23) && defined(BMC_DEVICE_UI_LED_22) && BMC_MAX_LEDS == 22 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 23
#endif

#if defined(BMC_DEVICE_UI_LED_24) && defined(BMC_DEVICE_UI_LED_23) && BMC_MAX_LEDS == 23 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 24
#endif

#if defined(BMC_DEVICE_UI_LED_25) && defined(BMC_DEVICE_UI_LED_24) && BMC_MAX_LEDS == 24 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 25
#endif

#if defined(BMC_DEVICE_UI_LED_26) && defined(BMC_DEVICE_UI_LED_25) && BMC_MAX_LEDS == 25 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 26
#endif

#if defined(BMC_DEVICE_UI_LED_27) && defined(BMC_DEVICE_UI_LED_26) && BMC_MAX_LEDS == 26 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 27
#endif

#if defined(BMC_DEVICE_UI_LED_28) && defined(BMC_DEVICE_UI_LED_27) && BMC_MAX_LEDS == 27 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 28
#endif

#if defined(BMC_DEVICE_UI_LED_29) && defined(BMC_DEVICE_UI_LED_28) && BMC_MAX_LEDS == 28 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 29
#endif

#if defined(BMC_DEVICE_UI_LED_30) && defined(BMC_DEVICE_UI_LED_29) && BMC_MAX_LEDS == 29 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 30
#endif

#if defined(BMC_DEVICE_UI_LED_31) && defined(BMC_DEVICE_UI_LED_30) && BMC_MAX_LEDS == 30 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 31
#endif

#if defined(BMC_DEVICE_UI_LED_32) && defined(BMC_DEVICE_UI_LED_31) && BMC_MAX_LEDS == 31 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 32
#endif

#if defined(BMC_DEVICE_UI_LED_33) && defined(BMC_DEVICE_UI_LED_32) && BMC_MAX_LEDS == 32 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 33
#endif

#if defined(BMC_DEVICE_UI_LED_34) && defined(BMC_DEVICE_UI_LED_33) && BMC_MAX_LEDS == 33 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 34
#endif

#if defined(BMC_DEVICE_UI_LED_35) && defined(BMC_DEVICE_UI_LED_34) && BMC_MAX_LEDS == 34 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 35
#endif

#if defined(BMC_DEVICE_UI_LED_36) && defined(BMC_DEVICE_UI_LED_35) && BMC_MAX_LEDS == 35 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 36
#endif

#if defined(BMC_DEVICE_UI_LED_37) && defined(BMC_DEVICE_UI_LED_36) && BMC_MAX_LEDS == 36 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 37
#endif

#if defined(BMC_DEVICE_UI_LED_38) && defined(BMC_DEVICE_UI_LED_37) && BMC_MAX_LEDS == 37 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 38
#endif

#if defined(BMC_DEVICE_UI_LED_39) && defined(BMC_DEVICE_UI_LED_38) && BMC_MAX_LEDS == 38 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 39
#endif

#if defined(BMC_DEVICE_UI_LED_40) && defined(BMC_DEVICE_UI_LED_39) && BMC_MAX_LEDS == 39 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 40
#endif

#if defined(BMC_DEVICE_UI_LED_41) && defined(BMC_DEVICE_UI_LED_40) && BMC_MAX_LEDS == 40 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 41
#endif

#if defined(BMC_DEVICE_UI_LED_42) && defined(BMC_DEVICE_UI_LED_41) && BMC_MAX_LEDS == 41 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 42
#endif

#if defined(BMC_DEVICE_UI_LED_43) && defined(BMC_DEVICE_UI_LED_42) && BMC_MAX_LEDS == 42 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 43
#endif

#if defined(BMC_DEVICE_UI_LED_44) && defined(BMC_DEVICE_UI_LED_43) && BMC_MAX_LEDS == 43 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 44
#endif

#if defined(BMC_DEVICE_UI_LED_45) && defined(BMC_DEVICE_UI_LED_44) && BMC_MAX_LEDS == 44 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 45
#endif

#if defined(BMC_DEVICE_UI_LED_46) && defined(BMC_DEVICE_UI_LED_45) && BMC_MAX_LEDS == 45 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 46
#endif

#if defined(BMC_DEVICE_UI_LED_47) && defined(BMC_DEVICE_UI_LED_46) && BMC_MAX_LEDS == 46 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 47
#endif

#if defined(BMC_DEVICE_UI_LED_48) && defined(BMC_DEVICE_UI_LED_47) && BMC_MAX_LEDS == 47 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 48
#endif

#if defined(BMC_DEVICE_UI_LED_49) && defined(BMC_DEVICE_UI_LED_48) && BMC_MAX_LEDS == 48 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 49
#endif

#if defined(BMC_DEVICE_UI_LED_50) && defined(BMC_DEVICE_UI_LED_49) && BMC_MAX_LEDS == 49 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 50
#endif

#if defined(BMC_DEVICE_UI_LED_51) && defined(BMC_DEVICE_UI_LED_50) && BMC_MAX_LEDS == 50 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 51
#endif

#if defined(BMC_DEVICE_UI_LED_52) && defined(BMC_DEVICE_UI_LED_51) && BMC_MAX_LEDS == 51 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 52
#endif

#if defined(BMC_DEVICE_UI_LED_53) && defined(BMC_DEVICE_UI_LED_52) && BMC_MAX_LEDS == 52 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 53
#endif

#if defined(BMC_DEVICE_UI_LED_54) && defined(BMC_DEVICE_UI_LED_53) && BMC_MAX_LEDS == 53 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 54
#endif

#if defined(BMC_DEVICE_UI_LED_55) && defined(BMC_DEVICE_UI_LED_54) && BMC_MAX_LEDS == 54 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 55
#endif

#if defined(BMC_DEVICE_UI_LED_56) && defined(BMC_DEVICE_UI_LED_55) && BMC_MAX_LEDS == 55 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 56
#endif

#if defined(BMC_DEVICE_UI_LED_57) && defined(BMC_DEVICE_UI_LED_56) && BMC_MAX_LEDS == 56 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 57
#endif

#if defined(BMC_DEVICE_UI_LED_58) && defined(BMC_DEVICE_UI_LED_57) && BMC_MAX_LEDS == 57 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 58
#endif

#if defined(BMC_DEVICE_UI_LED_59) && defined(BMC_DEVICE_UI_LED_58) && BMC_MAX_LEDS == 58 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 59
#endif

#if defined(BMC_DEVICE_UI_LED_60) && defined(BMC_DEVICE_UI_LED_59) && BMC_MAX_LEDS == 59 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 60
#endif

#if defined(BMC_DEVICE_UI_LED_61) && defined(BMC_DEVICE_UI_LED_60) && BMC_MAX_LEDS == 60 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 61
#endif

#if defined(BMC_DEVICE_UI_LED_62) && defined(BMC_DEVICE_UI_LED_61) && BMC_MAX_LEDS == 61 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 62
#endif

#if defined(BMC_DEVICE_UI_LED_63) && defined(BMC_DEVICE_UI_LED_62) && BMC_MAX_LEDS == 62 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 63
#endif

#if defined(BMC_DEVICE_UI_LED_64) && defined(BMC_DEVICE_UI_LED_63) && BMC_MAX_LEDS == 63 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 64
#endif

#if defined(BMC_DEVICE_UI_LED_65) && defined(BMC_DEVICE_UI_LED_64) && BMC_MAX_LEDS == 64 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 65
#endif

#if defined(BMC_DEVICE_UI_LED_66) && defined(BMC_DEVICE_UI_LED_65) && BMC_MAX_LEDS == 65 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 66
#endif

#if defined(BMC_DEVICE_UI_LED_67) && defined(BMC_DEVICE_UI_LED_66) && BMC_MAX_LEDS == 66 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 67
#endif

#if defined(BMC_DEVICE_UI_LED_68) && defined(BMC_DEVICE_UI_LED_67) && BMC_MAX_LEDS == 67 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 68
#endif

#if defined(BMC_DEVICE_UI_LED_69) && defined(BMC_DEVICE_UI_LED_68) && BMC_MAX_LEDS == 68 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 69
#endif

#if defined(BMC_DEVICE_UI_LED_70) && defined(BMC_DEVICE_UI_LED_69) && BMC_MAX_LEDS == 69 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 70
#endif

#if defined(BMC_DEVICE_UI_LED_71) && defined(BMC_DEVICE_UI_LED_70) && BMC_MAX_LEDS == 70 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 71
#endif

#if defined(BMC_DEVICE_UI_LED_72) && defined(BMC_DEVICE_UI_LED_71) && BMC_MAX_LEDS == 71 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 72
#endif

#if defined(BMC_DEVICE_UI_LED_73) && defined(BMC_DEVICE_UI_LED_72) && BMC_MAX_LEDS == 72 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 73
#endif

#if defined(BMC_DEVICE_UI_LED_74) && defined(BMC_DEVICE_UI_LED_73) && BMC_MAX_LEDS == 73 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 74
#endif

#if defined(BMC_DEVICE_UI_LED_75) && defined(BMC_DEVICE_UI_LED_74) && BMC_MAX_LEDS == 74 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 75
#endif

#if defined(BMC_DEVICE_UI_LED_76) && defined(BMC_DEVICE_UI_LED_75) && BMC_MAX_LEDS == 75 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 76
#endif

#if defined(BMC_DEVICE_UI_LED_77) && defined(BMC_DEVICE_UI_LED_76) && BMC_MAX_LEDS == 76 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 77
#endif

#if defined(BMC_DEVICE_UI_LED_78) && defined(BMC_DEVICE_UI_LED_77) && BMC_MAX_LEDS == 77 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 78
#endif

#if defined(BMC_DEVICE_UI_LED_79) && defined(BMC_DEVICE_UI_LED_78) && BMC_MAX_LEDS == 78 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 79
#endif

#if defined(BMC_DEVICE_UI_LED_80) && defined(BMC_DEVICE_UI_LED_79) && BMC_MAX_LEDS == 79 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 80
#endif

#if defined(BMC_DEVICE_UI_LED_81) && defined(BMC_DEVICE_UI_LED_80) && BMC_MAX_LEDS == 80 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 81
#endif

#if defined(BMC_DEVICE_UI_LED_82) && defined(BMC_DEVICE_UI_LED_81) && BMC_MAX_LEDS == 81 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 82
#endif

#if defined(BMC_DEVICE_UI_LED_83) && defined(BMC_DEVICE_UI_LED_82) && BMC_MAX_LEDS == 82 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 83
#endif

#if defined(BMC_DEVICE_UI_LED_84) && defined(BMC_DEVICE_UI_LED_83) && BMC_MAX_LEDS == 83 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 84
#endif

#if defined(BMC_DEVICE_UI_LED_85) && defined(BMC_DEVICE_UI_LED_84) && BMC_MAX_LEDS == 84 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 85
#endif

#if defined(BMC_DEVICE_UI_LED_86) && defined(BMC_DEVICE_UI_LED_85) && BMC_MAX_LEDS == 85 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 86
#endif

#if defined(BMC_DEVICE_UI_LED_87) && defined(BMC_DEVICE_UI_LED_86) && BMC_MAX_LEDS == 86 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 87
#endif

#if defined(BMC_DEVICE_UI_LED_88) && defined(BMC_DEVICE_UI_LED_87) && BMC_MAX_LEDS == 87 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 88
#endif

#if defined(BMC_DEVICE_UI_LED_89) && defined(BMC_DEVICE_UI_LED_88) && BMC_MAX_LEDS == 88 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 89
#endif

#if defined(BMC_DEVICE_UI_LED_90) && defined(BMC_DEVICE_UI_LED_89) && BMC_MAX_LEDS == 89 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 90
#endif

#if defined(BMC_DEVICE_UI_LED_91) && defined(BMC_DEVICE_UI_LED_90) && BMC_MAX_LEDS == 90 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 91
#endif

#if defined(BMC_DEVICE_UI_LED_92) && defined(BMC_DEVICE_UI_LED_91) && BMC_MAX_LEDS == 91 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 92
#endif

#if defined(BMC_DEVICE_UI_LED_93) && defined(BMC_DEVICE_UI_LED_92) && BMC_MAX_LEDS == 92 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 93
#endif

#if defined(BMC_DEVICE_UI_LED_94) && defined(BMC_DEVICE_UI_LED_93) && BMC_MAX_LEDS == 93 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 94
#endif

#if defined(BMC_DEVICE_UI_LED_95) && defined(BMC_DEVICE_UI_LED_94) && BMC_MAX_LEDS == 94 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 95
#endif

#if defined(BMC_DEVICE_UI_LED_96) && defined(BMC_DEVICE_UI_LED_95) && BMC_MAX_LEDS == 95 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 96
#endif

#if defined(BMC_DEVICE_UI_LED_97) && defined(BMC_DEVICE_UI_LED_96) && BMC_MAX_LEDS == 96 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 97
#endif

#if defined(BMC_DEVICE_UI_LED_98) && defined(BMC_DEVICE_UI_LED_97) && BMC_MAX_LEDS == 97 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 98
#endif

#if defined(BMC_DEVICE_UI_LED_99) && defined(BMC_DEVICE_UI_LED_98) && BMC_MAX_LEDS == 98 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 99
#endif

#if defined(BMC_DEVICE_UI_LED_100) && defined(BMC_DEVICE_UI_LED_99) && BMC_MAX_LEDS == 99 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 100
#endif

#if defined(BMC_DEVICE_UI_LED_101) && defined(BMC_DEVICE_UI_LED_100) && BMC_MAX_LEDS == 100 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 101
#endif

#if defined(BMC_DEVICE_UI_LED_102) && defined(BMC_DEVICE_UI_LED_101) && BMC_MAX_LEDS == 101 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 102
#endif

#if defined(BMC_DEVICE_UI_LED_103) && defined(BMC_DEVICE_UI_LED_102) && BMC_MAX_LEDS == 102 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 103
#endif

#if defined(BMC_DEVICE_UI_LED_104) && defined(BMC_DEVICE_UI_LED_103) && BMC_MAX_LEDS == 103 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 104
#endif

#if defined(BMC_DEVICE_UI_LED_105) && defined(BMC_DEVICE_UI_LED_104) && BMC_MAX_LEDS == 104 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 105
#endif

#if defined(BMC_DEVICE_UI_LED_106) && defined(BMC_DEVICE_UI_LED_105) && BMC_MAX_LEDS == 105 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 106
#endif

#if defined(BMC_DEVICE_UI_LED_107) && defined(BMC_DEVICE_UI_LED_106) && BMC_MAX_LEDS == 106 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 107
#endif

#if defined(BMC_DEVICE_UI_LED_108) && defined(BMC_DEVICE_UI_LED_107) && BMC_MAX_LEDS == 107 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 108
#endif

#if defined(BMC_DEVICE_UI_LED_109) && defined(BMC_DEVICE_UI_LED_108) && BMC_MAX_LEDS == 108 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 109
#endif

#if defined(BMC_DEVICE_UI_LED_110) && defined(BMC_DEVICE_UI_LED_109) && BMC_MAX_LEDS == 109 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 110
#endif

#if defined(BMC_DEVICE_UI_LED_111) && defined(BMC_DEVICE_UI_LED_110) && BMC_MAX_LEDS == 110 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 111
#endif

#if defined(BMC_DEVICE_UI_LED_112) && defined(BMC_DEVICE_UI_LED_111) && BMC_MAX_LEDS == 111 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 112
#endif

#if defined(BMC_DEVICE_UI_LED_113) && defined(BMC_DEVICE_UI_LED_112) && BMC_MAX_LEDS == 112 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 113
#endif

#if defined(BMC_DEVICE_UI_LED_114) && defined(BMC_DEVICE_UI_LED_113) && BMC_MAX_LEDS == 113 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 114
#endif

#if defined(BMC_DEVICE_UI_LED_115) && defined(BMC_DEVICE_UI_LED_114) && BMC_MAX_LEDS == 114 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 115
#endif

#if defined(BMC_DEVICE_UI_LED_116) && defined(BMC_DEVICE_UI_LED_115) && BMC_MAX_LEDS == 115 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 116
#endif

#if defined(BMC_DEVICE_UI_LED_117) && defined(BMC_DEVICE_UI_LED_116) && BMC_MAX_LEDS == 116 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 117
#endif

#if defined(BMC_DEVICE_UI_LED_118) && defined(BMC_DEVICE_UI_LED_117) && BMC_MAX_LEDS == 117 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 118
#endif

#if defined(BMC_DEVICE_UI_LED_119) && defined(BMC_DEVICE_UI_LED_118) && BMC_MAX_LEDS == 118 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 119
#endif

#if defined(BMC_DEVICE_UI_LED_120) && defined(BMC_DEVICE_UI_LED_119) && BMC_MAX_LEDS == 119 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 120
#endif

#if defined(BMC_DEVICE_UI_LED_121) && defined(BMC_DEVICE_UI_LED_120) && BMC_MAX_LEDS == 120 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 121
#endif

#if defined(BMC_DEVICE_UI_LED_122) && defined(BMC_DEVICE_UI_LED_121) && BMC_MAX_LEDS == 121 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 122
#endif

#if defined(BMC_DEVICE_UI_LED_123) && defined(BMC_DEVICE_UI_LED_122) && BMC_MAX_LEDS == 122 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 123
#endif

#if defined(BMC_DEVICE_UI_LED_124) && defined(BMC_DEVICE_UI_LED_123) && BMC_MAX_LEDS == 123 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 124
#endif

#if defined(BMC_DEVICE_UI_LED_125) && defined(BMC_DEVICE_UI_LED_124) && BMC_MAX_LEDS == 124 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 125
#endif

#if defined(BMC_DEVICE_UI_LED_126) && defined(BMC_DEVICE_UI_LED_125) && BMC_MAX_LEDS == 125 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 126
#endif

#if defined(BMC_DEVICE_UI_LED_127) && defined(BMC_DEVICE_UI_LED_126) && BMC_MAX_LEDS == 126 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 127
#endif

#if defined(BMC_DEVICE_UI_LED_128) && defined(BMC_DEVICE_UI_LED_127) && BMC_MAX_LEDS == 127 
  #ifdef BMC_MAX_LEDS
    #undef BMC_MAX_LEDS
  #endif

  #define BMC_MAX_LEDS 128
#endif

// *******************************************
// *** LEDS end
// *******************************************

// *******************************************
// *** GLOBAL_LEDS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_LEDS
  #undef BMC_MAX_GLOBAL_LEDS
#endif

#define BMC_MAX_GLOBAL_LEDS 0

#if defined(BMC_DEVICE_UI_GLOBAL_LED_1) && BMC_MAX_GLOBAL_LEDS == 0 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_2) && defined(BMC_DEVICE_UI_GLOBAL_LED_1) && BMC_MAX_GLOBAL_LEDS == 1 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_3) && defined(BMC_DEVICE_UI_GLOBAL_LED_2) && BMC_MAX_GLOBAL_LEDS == 2 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_4) && defined(BMC_DEVICE_UI_GLOBAL_LED_3) && BMC_MAX_GLOBAL_LEDS == 3 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_5) && defined(BMC_DEVICE_UI_GLOBAL_LED_4) && BMC_MAX_GLOBAL_LEDS == 4 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_6) && defined(BMC_DEVICE_UI_GLOBAL_LED_5) && BMC_MAX_GLOBAL_LEDS == 5 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_7) && defined(BMC_DEVICE_UI_GLOBAL_LED_6) && BMC_MAX_GLOBAL_LEDS == 6 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_8) && defined(BMC_DEVICE_UI_GLOBAL_LED_7) && BMC_MAX_GLOBAL_LEDS == 7 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_9) && defined(BMC_DEVICE_UI_GLOBAL_LED_8) && BMC_MAX_GLOBAL_LEDS == 8 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_10) && defined(BMC_DEVICE_UI_GLOBAL_LED_9) && BMC_MAX_GLOBAL_LEDS == 9 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_11) && defined(BMC_DEVICE_UI_GLOBAL_LED_10) && BMC_MAX_GLOBAL_LEDS == 10 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_12) && defined(BMC_DEVICE_UI_GLOBAL_LED_11) && BMC_MAX_GLOBAL_LEDS == 11 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_13) && defined(BMC_DEVICE_UI_GLOBAL_LED_12) && BMC_MAX_GLOBAL_LEDS == 12 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_14) && defined(BMC_DEVICE_UI_GLOBAL_LED_13) && BMC_MAX_GLOBAL_LEDS == 13 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_15) && defined(BMC_DEVICE_UI_GLOBAL_LED_14) && BMC_MAX_GLOBAL_LEDS == 14 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_16) && defined(BMC_DEVICE_UI_GLOBAL_LED_15) && BMC_MAX_GLOBAL_LEDS == 15 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_17) && defined(BMC_DEVICE_UI_GLOBAL_LED_16) && BMC_MAX_GLOBAL_LEDS == 16 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_18) && defined(BMC_DEVICE_UI_GLOBAL_LED_17) && BMC_MAX_GLOBAL_LEDS == 17 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_19) && defined(BMC_DEVICE_UI_GLOBAL_LED_18) && BMC_MAX_GLOBAL_LEDS == 18 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_20) && defined(BMC_DEVICE_UI_GLOBAL_LED_19) && BMC_MAX_GLOBAL_LEDS == 19 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_21) && defined(BMC_DEVICE_UI_GLOBAL_LED_20) && BMC_MAX_GLOBAL_LEDS == 20 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_22) && defined(BMC_DEVICE_UI_GLOBAL_LED_21) && BMC_MAX_GLOBAL_LEDS == 21 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_23) && defined(BMC_DEVICE_UI_GLOBAL_LED_22) && BMC_MAX_GLOBAL_LEDS == 22 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_24) && defined(BMC_DEVICE_UI_GLOBAL_LED_23) && BMC_MAX_GLOBAL_LEDS == 23 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_25) && defined(BMC_DEVICE_UI_GLOBAL_LED_24) && BMC_MAX_GLOBAL_LEDS == 24 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_26) && defined(BMC_DEVICE_UI_GLOBAL_LED_25) && BMC_MAX_GLOBAL_LEDS == 25 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_27) && defined(BMC_DEVICE_UI_GLOBAL_LED_26) && BMC_MAX_GLOBAL_LEDS == 26 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_28) && defined(BMC_DEVICE_UI_GLOBAL_LED_27) && BMC_MAX_GLOBAL_LEDS == 27 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_29) && defined(BMC_DEVICE_UI_GLOBAL_LED_28) && BMC_MAX_GLOBAL_LEDS == 28 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_30) && defined(BMC_DEVICE_UI_GLOBAL_LED_29) && BMC_MAX_GLOBAL_LEDS == 29 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_31) && defined(BMC_DEVICE_UI_GLOBAL_LED_30) && BMC_MAX_GLOBAL_LEDS == 30 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_32) && defined(BMC_DEVICE_UI_GLOBAL_LED_31) && BMC_MAX_GLOBAL_LEDS == 31 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_33) && defined(BMC_DEVICE_UI_GLOBAL_LED_32) && BMC_MAX_GLOBAL_LEDS == 32 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_34) && defined(BMC_DEVICE_UI_GLOBAL_LED_33) && BMC_MAX_GLOBAL_LEDS == 33 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_35) && defined(BMC_DEVICE_UI_GLOBAL_LED_34) && BMC_MAX_GLOBAL_LEDS == 34 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_36) && defined(BMC_DEVICE_UI_GLOBAL_LED_35) && BMC_MAX_GLOBAL_LEDS == 35 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_37) && defined(BMC_DEVICE_UI_GLOBAL_LED_36) && BMC_MAX_GLOBAL_LEDS == 36 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_38) && defined(BMC_DEVICE_UI_GLOBAL_LED_37) && BMC_MAX_GLOBAL_LEDS == 37 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_39) && defined(BMC_DEVICE_UI_GLOBAL_LED_38) && BMC_MAX_GLOBAL_LEDS == 38 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_40) && defined(BMC_DEVICE_UI_GLOBAL_LED_39) && BMC_MAX_GLOBAL_LEDS == 39 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_41) && defined(BMC_DEVICE_UI_GLOBAL_LED_40) && BMC_MAX_GLOBAL_LEDS == 40 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_42) && defined(BMC_DEVICE_UI_GLOBAL_LED_41) && BMC_MAX_GLOBAL_LEDS == 41 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_43) && defined(BMC_DEVICE_UI_GLOBAL_LED_42) && BMC_MAX_GLOBAL_LEDS == 42 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_44) && defined(BMC_DEVICE_UI_GLOBAL_LED_43) && BMC_MAX_GLOBAL_LEDS == 43 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_45) && defined(BMC_DEVICE_UI_GLOBAL_LED_44) && BMC_MAX_GLOBAL_LEDS == 44 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_46) && defined(BMC_DEVICE_UI_GLOBAL_LED_45) && BMC_MAX_GLOBAL_LEDS == 45 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_47) && defined(BMC_DEVICE_UI_GLOBAL_LED_46) && BMC_MAX_GLOBAL_LEDS == 46 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_48) && defined(BMC_DEVICE_UI_GLOBAL_LED_47) && BMC_MAX_GLOBAL_LEDS == 47 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_49) && defined(BMC_DEVICE_UI_GLOBAL_LED_48) && BMC_MAX_GLOBAL_LEDS == 48 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_50) && defined(BMC_DEVICE_UI_GLOBAL_LED_49) && BMC_MAX_GLOBAL_LEDS == 49 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_51) && defined(BMC_DEVICE_UI_GLOBAL_LED_50) && BMC_MAX_GLOBAL_LEDS == 50 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_52) && defined(BMC_DEVICE_UI_GLOBAL_LED_51) && BMC_MAX_GLOBAL_LEDS == 51 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_53) && defined(BMC_DEVICE_UI_GLOBAL_LED_52) && BMC_MAX_GLOBAL_LEDS == 52 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_54) && defined(BMC_DEVICE_UI_GLOBAL_LED_53) && BMC_MAX_GLOBAL_LEDS == 53 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_55) && defined(BMC_DEVICE_UI_GLOBAL_LED_54) && BMC_MAX_GLOBAL_LEDS == 54 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_56) && defined(BMC_DEVICE_UI_GLOBAL_LED_55) && BMC_MAX_GLOBAL_LEDS == 55 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_57) && defined(BMC_DEVICE_UI_GLOBAL_LED_56) && BMC_MAX_GLOBAL_LEDS == 56 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_58) && defined(BMC_DEVICE_UI_GLOBAL_LED_57) && BMC_MAX_GLOBAL_LEDS == 57 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_59) && defined(BMC_DEVICE_UI_GLOBAL_LED_58) && BMC_MAX_GLOBAL_LEDS == 58 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_60) && defined(BMC_DEVICE_UI_GLOBAL_LED_59) && BMC_MAX_GLOBAL_LEDS == 59 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_61) && defined(BMC_DEVICE_UI_GLOBAL_LED_60) && BMC_MAX_GLOBAL_LEDS == 60 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_62) && defined(BMC_DEVICE_UI_GLOBAL_LED_61) && BMC_MAX_GLOBAL_LEDS == 61 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_63) && defined(BMC_DEVICE_UI_GLOBAL_LED_62) && BMC_MAX_GLOBAL_LEDS == 62 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_64) && defined(BMC_DEVICE_UI_GLOBAL_LED_63) && BMC_MAX_GLOBAL_LEDS == 63 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 64
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_65) && defined(BMC_DEVICE_UI_GLOBAL_LED_64) && BMC_MAX_GLOBAL_LEDS == 64 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 65
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_66) && defined(BMC_DEVICE_UI_GLOBAL_LED_65) && BMC_MAX_GLOBAL_LEDS == 65 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 66
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_67) && defined(BMC_DEVICE_UI_GLOBAL_LED_66) && BMC_MAX_GLOBAL_LEDS == 66 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 67
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_68) && defined(BMC_DEVICE_UI_GLOBAL_LED_67) && BMC_MAX_GLOBAL_LEDS == 67 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 68
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_69) && defined(BMC_DEVICE_UI_GLOBAL_LED_68) && BMC_MAX_GLOBAL_LEDS == 68 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 69
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_70) && defined(BMC_DEVICE_UI_GLOBAL_LED_69) && BMC_MAX_GLOBAL_LEDS == 69 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 70
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_71) && defined(BMC_DEVICE_UI_GLOBAL_LED_70) && BMC_MAX_GLOBAL_LEDS == 70 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 71
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_72) && defined(BMC_DEVICE_UI_GLOBAL_LED_71) && BMC_MAX_GLOBAL_LEDS == 71 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 72
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_73) && defined(BMC_DEVICE_UI_GLOBAL_LED_72) && BMC_MAX_GLOBAL_LEDS == 72 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 73
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_74) && defined(BMC_DEVICE_UI_GLOBAL_LED_73) && BMC_MAX_GLOBAL_LEDS == 73 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 74
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_75) && defined(BMC_DEVICE_UI_GLOBAL_LED_74) && BMC_MAX_GLOBAL_LEDS == 74 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 75
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_76) && defined(BMC_DEVICE_UI_GLOBAL_LED_75) && BMC_MAX_GLOBAL_LEDS == 75 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 76
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_77) && defined(BMC_DEVICE_UI_GLOBAL_LED_76) && BMC_MAX_GLOBAL_LEDS == 76 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 77
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_78) && defined(BMC_DEVICE_UI_GLOBAL_LED_77) && BMC_MAX_GLOBAL_LEDS == 77 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 78
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_79) && defined(BMC_DEVICE_UI_GLOBAL_LED_78) && BMC_MAX_GLOBAL_LEDS == 78 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 79
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_80) && defined(BMC_DEVICE_UI_GLOBAL_LED_79) && BMC_MAX_GLOBAL_LEDS == 79 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 80
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_81) && defined(BMC_DEVICE_UI_GLOBAL_LED_80) && BMC_MAX_GLOBAL_LEDS == 80 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 81
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_82) && defined(BMC_DEVICE_UI_GLOBAL_LED_81) && BMC_MAX_GLOBAL_LEDS == 81 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 82
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_83) && defined(BMC_DEVICE_UI_GLOBAL_LED_82) && BMC_MAX_GLOBAL_LEDS == 82 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 83
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_84) && defined(BMC_DEVICE_UI_GLOBAL_LED_83) && BMC_MAX_GLOBAL_LEDS == 83 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 84
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_85) && defined(BMC_DEVICE_UI_GLOBAL_LED_84) && BMC_MAX_GLOBAL_LEDS == 84 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 85
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_86) && defined(BMC_DEVICE_UI_GLOBAL_LED_85) && BMC_MAX_GLOBAL_LEDS == 85 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 86
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_87) && defined(BMC_DEVICE_UI_GLOBAL_LED_86) && BMC_MAX_GLOBAL_LEDS == 86 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 87
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_88) && defined(BMC_DEVICE_UI_GLOBAL_LED_87) && BMC_MAX_GLOBAL_LEDS == 87 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 88
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_89) && defined(BMC_DEVICE_UI_GLOBAL_LED_88) && BMC_MAX_GLOBAL_LEDS == 88 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 89
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_90) && defined(BMC_DEVICE_UI_GLOBAL_LED_89) && BMC_MAX_GLOBAL_LEDS == 89 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 90
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_91) && defined(BMC_DEVICE_UI_GLOBAL_LED_90) && BMC_MAX_GLOBAL_LEDS == 90 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 91
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_92) && defined(BMC_DEVICE_UI_GLOBAL_LED_91) && BMC_MAX_GLOBAL_LEDS == 91 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 92
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_93) && defined(BMC_DEVICE_UI_GLOBAL_LED_92) && BMC_MAX_GLOBAL_LEDS == 92 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 93
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_94) && defined(BMC_DEVICE_UI_GLOBAL_LED_93) && BMC_MAX_GLOBAL_LEDS == 93 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 94
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_95) && defined(BMC_DEVICE_UI_GLOBAL_LED_94) && BMC_MAX_GLOBAL_LEDS == 94 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 95
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_96) && defined(BMC_DEVICE_UI_GLOBAL_LED_95) && BMC_MAX_GLOBAL_LEDS == 95 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 96
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_97) && defined(BMC_DEVICE_UI_GLOBAL_LED_96) && BMC_MAX_GLOBAL_LEDS == 96 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 97
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_98) && defined(BMC_DEVICE_UI_GLOBAL_LED_97) && BMC_MAX_GLOBAL_LEDS == 97 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 98
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_99) && defined(BMC_DEVICE_UI_GLOBAL_LED_98) && BMC_MAX_GLOBAL_LEDS == 98 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 99
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_100) && defined(BMC_DEVICE_UI_GLOBAL_LED_99) && BMC_MAX_GLOBAL_LEDS == 99 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 100
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_101) && defined(BMC_DEVICE_UI_GLOBAL_LED_100) && BMC_MAX_GLOBAL_LEDS == 100 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 101
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_102) && defined(BMC_DEVICE_UI_GLOBAL_LED_101) && BMC_MAX_GLOBAL_LEDS == 101 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 102
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_103) && defined(BMC_DEVICE_UI_GLOBAL_LED_102) && BMC_MAX_GLOBAL_LEDS == 102 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 103
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_104) && defined(BMC_DEVICE_UI_GLOBAL_LED_103) && BMC_MAX_GLOBAL_LEDS == 103 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 104
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_105) && defined(BMC_DEVICE_UI_GLOBAL_LED_104) && BMC_MAX_GLOBAL_LEDS == 104 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 105
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_106) && defined(BMC_DEVICE_UI_GLOBAL_LED_105) && BMC_MAX_GLOBAL_LEDS == 105 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 106
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_107) && defined(BMC_DEVICE_UI_GLOBAL_LED_106) && BMC_MAX_GLOBAL_LEDS == 106 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 107
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_108) && defined(BMC_DEVICE_UI_GLOBAL_LED_107) && BMC_MAX_GLOBAL_LEDS == 107 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 108
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_109) && defined(BMC_DEVICE_UI_GLOBAL_LED_108) && BMC_MAX_GLOBAL_LEDS == 108 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 109
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_110) && defined(BMC_DEVICE_UI_GLOBAL_LED_109) && BMC_MAX_GLOBAL_LEDS == 109 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 110
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_111) && defined(BMC_DEVICE_UI_GLOBAL_LED_110) && BMC_MAX_GLOBAL_LEDS == 110 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 111
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_112) && defined(BMC_DEVICE_UI_GLOBAL_LED_111) && BMC_MAX_GLOBAL_LEDS == 111 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 112
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_113) && defined(BMC_DEVICE_UI_GLOBAL_LED_112) && BMC_MAX_GLOBAL_LEDS == 112 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 113
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_114) && defined(BMC_DEVICE_UI_GLOBAL_LED_113) && BMC_MAX_GLOBAL_LEDS == 113 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 114
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_115) && defined(BMC_DEVICE_UI_GLOBAL_LED_114) && BMC_MAX_GLOBAL_LEDS == 114 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 115
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_116) && defined(BMC_DEVICE_UI_GLOBAL_LED_115) && BMC_MAX_GLOBAL_LEDS == 115 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 116
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_117) && defined(BMC_DEVICE_UI_GLOBAL_LED_116) && BMC_MAX_GLOBAL_LEDS == 116 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 117
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_118) && defined(BMC_DEVICE_UI_GLOBAL_LED_117) && BMC_MAX_GLOBAL_LEDS == 117 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 118
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_119) && defined(BMC_DEVICE_UI_GLOBAL_LED_118) && BMC_MAX_GLOBAL_LEDS == 118 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 119
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_120) && defined(BMC_DEVICE_UI_GLOBAL_LED_119) && BMC_MAX_GLOBAL_LEDS == 119 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 120
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_121) && defined(BMC_DEVICE_UI_GLOBAL_LED_120) && BMC_MAX_GLOBAL_LEDS == 120 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 121
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_122) && defined(BMC_DEVICE_UI_GLOBAL_LED_121) && BMC_MAX_GLOBAL_LEDS == 121 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 122
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_123) && defined(BMC_DEVICE_UI_GLOBAL_LED_122) && BMC_MAX_GLOBAL_LEDS == 122 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 123
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_124) && defined(BMC_DEVICE_UI_GLOBAL_LED_123) && BMC_MAX_GLOBAL_LEDS == 123 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 124
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_125) && defined(BMC_DEVICE_UI_GLOBAL_LED_124) && BMC_MAX_GLOBAL_LEDS == 124 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 125
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_126) && defined(BMC_DEVICE_UI_GLOBAL_LED_125) && BMC_MAX_GLOBAL_LEDS == 125 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 126
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_127) && defined(BMC_DEVICE_UI_GLOBAL_LED_126) && BMC_MAX_GLOBAL_LEDS == 126 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 127
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_LED_128) && defined(BMC_DEVICE_UI_GLOBAL_LED_127) && BMC_MAX_GLOBAL_LEDS == 127 
  #ifdef BMC_MAX_GLOBAL_LEDS
    #undef BMC_MAX_GLOBAL_LEDS
  #endif

  #define BMC_MAX_GLOBAL_LEDS 128
#endif

// *******************************************
// *** GLOBAL_LEDS end
// *******************************************

// *******************************************
// *** BI_LEDS start
// *******************************************

#ifdef BMC_MAX_BI_LEDS
  #undef BMC_MAX_BI_LEDS
#endif

#define BMC_MAX_BI_LEDS 0

#if defined(BMC_DEVICE_UI_BI_LED_1) && BMC_MAX_BI_LEDS == 0 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 1
#endif

#if defined(BMC_DEVICE_UI_BI_LED_2) && defined(BMC_DEVICE_UI_BI_LED_1) && BMC_MAX_BI_LEDS == 1 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 2
#endif

#if defined(BMC_DEVICE_UI_BI_LED_3) && defined(BMC_DEVICE_UI_BI_LED_2) && BMC_MAX_BI_LEDS == 2 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 3
#endif

#if defined(BMC_DEVICE_UI_BI_LED_4) && defined(BMC_DEVICE_UI_BI_LED_3) && BMC_MAX_BI_LEDS == 3 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 4
#endif

#if defined(BMC_DEVICE_UI_BI_LED_5) && defined(BMC_DEVICE_UI_BI_LED_4) && BMC_MAX_BI_LEDS == 4 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 5
#endif

#if defined(BMC_DEVICE_UI_BI_LED_6) && defined(BMC_DEVICE_UI_BI_LED_5) && BMC_MAX_BI_LEDS == 5 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 6
#endif

#if defined(BMC_DEVICE_UI_BI_LED_7) && defined(BMC_DEVICE_UI_BI_LED_6) && BMC_MAX_BI_LEDS == 6 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 7
#endif

#if defined(BMC_DEVICE_UI_BI_LED_8) && defined(BMC_DEVICE_UI_BI_LED_7) && BMC_MAX_BI_LEDS == 7 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 8
#endif

#if defined(BMC_DEVICE_UI_BI_LED_9) && defined(BMC_DEVICE_UI_BI_LED_8) && BMC_MAX_BI_LEDS == 8 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 9
#endif

#if defined(BMC_DEVICE_UI_BI_LED_10) && defined(BMC_DEVICE_UI_BI_LED_9) && BMC_MAX_BI_LEDS == 9 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 10
#endif

#if defined(BMC_DEVICE_UI_BI_LED_11) && defined(BMC_DEVICE_UI_BI_LED_10) && BMC_MAX_BI_LEDS == 10 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 11
#endif

#if defined(BMC_DEVICE_UI_BI_LED_12) && defined(BMC_DEVICE_UI_BI_LED_11) && BMC_MAX_BI_LEDS == 11 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 12
#endif

#if defined(BMC_DEVICE_UI_BI_LED_13) && defined(BMC_DEVICE_UI_BI_LED_12) && BMC_MAX_BI_LEDS == 12 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 13
#endif

#if defined(BMC_DEVICE_UI_BI_LED_14) && defined(BMC_DEVICE_UI_BI_LED_13) && BMC_MAX_BI_LEDS == 13 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 14
#endif

#if defined(BMC_DEVICE_UI_BI_LED_15) && defined(BMC_DEVICE_UI_BI_LED_14) && BMC_MAX_BI_LEDS == 14 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 15
#endif

#if defined(BMC_DEVICE_UI_BI_LED_16) && defined(BMC_DEVICE_UI_BI_LED_15) && BMC_MAX_BI_LEDS == 15 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 16
#endif

#if defined(BMC_DEVICE_UI_BI_LED_17) && defined(BMC_DEVICE_UI_BI_LED_16) && BMC_MAX_BI_LEDS == 16 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 17
#endif

#if defined(BMC_DEVICE_UI_BI_LED_18) && defined(BMC_DEVICE_UI_BI_LED_17) && BMC_MAX_BI_LEDS == 17 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 18
#endif

#if defined(BMC_DEVICE_UI_BI_LED_19) && defined(BMC_DEVICE_UI_BI_LED_18) && BMC_MAX_BI_LEDS == 18 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 19
#endif

#if defined(BMC_DEVICE_UI_BI_LED_20) && defined(BMC_DEVICE_UI_BI_LED_19) && BMC_MAX_BI_LEDS == 19 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 20
#endif

#if defined(BMC_DEVICE_UI_BI_LED_21) && defined(BMC_DEVICE_UI_BI_LED_20) && BMC_MAX_BI_LEDS == 20 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 21
#endif

#if defined(BMC_DEVICE_UI_BI_LED_22) && defined(BMC_DEVICE_UI_BI_LED_21) && BMC_MAX_BI_LEDS == 21 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 22
#endif

#if defined(BMC_DEVICE_UI_BI_LED_23) && defined(BMC_DEVICE_UI_BI_LED_22) && BMC_MAX_BI_LEDS == 22 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 23
#endif

#if defined(BMC_DEVICE_UI_BI_LED_24) && defined(BMC_DEVICE_UI_BI_LED_23) && BMC_MAX_BI_LEDS == 23 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 24
#endif

#if defined(BMC_DEVICE_UI_BI_LED_25) && defined(BMC_DEVICE_UI_BI_LED_24) && BMC_MAX_BI_LEDS == 24 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 25
#endif

#if defined(BMC_DEVICE_UI_BI_LED_26) && defined(BMC_DEVICE_UI_BI_LED_25) && BMC_MAX_BI_LEDS == 25 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 26
#endif

#if defined(BMC_DEVICE_UI_BI_LED_27) && defined(BMC_DEVICE_UI_BI_LED_26) && BMC_MAX_BI_LEDS == 26 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 27
#endif

#if defined(BMC_DEVICE_UI_BI_LED_28) && defined(BMC_DEVICE_UI_BI_LED_27) && BMC_MAX_BI_LEDS == 27 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 28
#endif

#if defined(BMC_DEVICE_UI_BI_LED_29) && defined(BMC_DEVICE_UI_BI_LED_28) && BMC_MAX_BI_LEDS == 28 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 29
#endif

#if defined(BMC_DEVICE_UI_BI_LED_30) && defined(BMC_DEVICE_UI_BI_LED_29) && BMC_MAX_BI_LEDS == 29 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 30
#endif

#if defined(BMC_DEVICE_UI_BI_LED_31) && defined(BMC_DEVICE_UI_BI_LED_30) && BMC_MAX_BI_LEDS == 30 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 31
#endif

#if defined(BMC_DEVICE_UI_BI_LED_32) && defined(BMC_DEVICE_UI_BI_LED_31) && BMC_MAX_BI_LEDS == 31 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 32
#endif

#if defined(BMC_DEVICE_UI_BI_LED_33) && defined(BMC_DEVICE_UI_BI_LED_32) && BMC_MAX_BI_LEDS == 32 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 33
#endif

#if defined(BMC_DEVICE_UI_BI_LED_34) && defined(BMC_DEVICE_UI_BI_LED_33) && BMC_MAX_BI_LEDS == 33 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 34
#endif

#if defined(BMC_DEVICE_UI_BI_LED_35) && defined(BMC_DEVICE_UI_BI_LED_34) && BMC_MAX_BI_LEDS == 34 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 35
#endif

#if defined(BMC_DEVICE_UI_BI_LED_36) && defined(BMC_DEVICE_UI_BI_LED_35) && BMC_MAX_BI_LEDS == 35 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 36
#endif

#if defined(BMC_DEVICE_UI_BI_LED_37) && defined(BMC_DEVICE_UI_BI_LED_36) && BMC_MAX_BI_LEDS == 36 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 37
#endif

#if defined(BMC_DEVICE_UI_BI_LED_38) && defined(BMC_DEVICE_UI_BI_LED_37) && BMC_MAX_BI_LEDS == 37 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 38
#endif

#if defined(BMC_DEVICE_UI_BI_LED_39) && defined(BMC_DEVICE_UI_BI_LED_38) && BMC_MAX_BI_LEDS == 38 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 39
#endif

#if defined(BMC_DEVICE_UI_BI_LED_40) && defined(BMC_DEVICE_UI_BI_LED_39) && BMC_MAX_BI_LEDS == 39 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 40
#endif

#if defined(BMC_DEVICE_UI_BI_LED_41) && defined(BMC_DEVICE_UI_BI_LED_40) && BMC_MAX_BI_LEDS == 40 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 41
#endif

#if defined(BMC_DEVICE_UI_BI_LED_42) && defined(BMC_DEVICE_UI_BI_LED_41) && BMC_MAX_BI_LEDS == 41 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 42
#endif

#if defined(BMC_DEVICE_UI_BI_LED_43) && defined(BMC_DEVICE_UI_BI_LED_42) && BMC_MAX_BI_LEDS == 42 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 43
#endif

#if defined(BMC_DEVICE_UI_BI_LED_44) && defined(BMC_DEVICE_UI_BI_LED_43) && BMC_MAX_BI_LEDS == 43 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 44
#endif

#if defined(BMC_DEVICE_UI_BI_LED_45) && defined(BMC_DEVICE_UI_BI_LED_44) && BMC_MAX_BI_LEDS == 44 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 45
#endif

#if defined(BMC_DEVICE_UI_BI_LED_46) && defined(BMC_DEVICE_UI_BI_LED_45) && BMC_MAX_BI_LEDS == 45 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 46
#endif

#if defined(BMC_DEVICE_UI_BI_LED_47) && defined(BMC_DEVICE_UI_BI_LED_46) && BMC_MAX_BI_LEDS == 46 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 47
#endif

#if defined(BMC_DEVICE_UI_BI_LED_48) && defined(BMC_DEVICE_UI_BI_LED_47) && BMC_MAX_BI_LEDS == 47 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 48
#endif

#if defined(BMC_DEVICE_UI_BI_LED_49) && defined(BMC_DEVICE_UI_BI_LED_48) && BMC_MAX_BI_LEDS == 48 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 49
#endif

#if defined(BMC_DEVICE_UI_BI_LED_50) && defined(BMC_DEVICE_UI_BI_LED_49) && BMC_MAX_BI_LEDS == 49 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 50
#endif

#if defined(BMC_DEVICE_UI_BI_LED_51) && defined(BMC_DEVICE_UI_BI_LED_50) && BMC_MAX_BI_LEDS == 50 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 51
#endif

#if defined(BMC_DEVICE_UI_BI_LED_52) && defined(BMC_DEVICE_UI_BI_LED_51) && BMC_MAX_BI_LEDS == 51 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 52
#endif

#if defined(BMC_DEVICE_UI_BI_LED_53) && defined(BMC_DEVICE_UI_BI_LED_52) && BMC_MAX_BI_LEDS == 52 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 53
#endif

#if defined(BMC_DEVICE_UI_BI_LED_54) && defined(BMC_DEVICE_UI_BI_LED_53) && BMC_MAX_BI_LEDS == 53 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 54
#endif

#if defined(BMC_DEVICE_UI_BI_LED_55) && defined(BMC_DEVICE_UI_BI_LED_54) && BMC_MAX_BI_LEDS == 54 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 55
#endif

#if defined(BMC_DEVICE_UI_BI_LED_56) && defined(BMC_DEVICE_UI_BI_LED_55) && BMC_MAX_BI_LEDS == 55 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 56
#endif

#if defined(BMC_DEVICE_UI_BI_LED_57) && defined(BMC_DEVICE_UI_BI_LED_56) && BMC_MAX_BI_LEDS == 56 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 57
#endif

#if defined(BMC_DEVICE_UI_BI_LED_58) && defined(BMC_DEVICE_UI_BI_LED_57) && BMC_MAX_BI_LEDS == 57 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 58
#endif

#if defined(BMC_DEVICE_UI_BI_LED_59) && defined(BMC_DEVICE_UI_BI_LED_58) && BMC_MAX_BI_LEDS == 58 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 59
#endif

#if defined(BMC_DEVICE_UI_BI_LED_60) && defined(BMC_DEVICE_UI_BI_LED_59) && BMC_MAX_BI_LEDS == 59 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 60
#endif

#if defined(BMC_DEVICE_UI_BI_LED_61) && defined(BMC_DEVICE_UI_BI_LED_60) && BMC_MAX_BI_LEDS == 60 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 61
#endif

#if defined(BMC_DEVICE_UI_BI_LED_62) && defined(BMC_DEVICE_UI_BI_LED_61) && BMC_MAX_BI_LEDS == 61 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 62
#endif

#if defined(BMC_DEVICE_UI_BI_LED_63) && defined(BMC_DEVICE_UI_BI_LED_62) && BMC_MAX_BI_LEDS == 62 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 63
#endif

#if defined(BMC_DEVICE_UI_BI_LED_64) && defined(BMC_DEVICE_UI_BI_LED_63) && BMC_MAX_BI_LEDS == 63 
  #ifdef BMC_MAX_BI_LEDS
    #undef BMC_MAX_BI_LEDS
  #endif

  #define BMC_MAX_BI_LEDS 64
#endif

// *******************************************
// *** BI_LEDS end
// *******************************************

// *******************************************
// *** GLOBAL_BI_LEDS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_BI_LEDS
  #undef BMC_MAX_GLOBAL_BI_LEDS
#endif

#define BMC_MAX_GLOBAL_BI_LEDS 0

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_1) && BMC_MAX_GLOBAL_BI_LEDS == 0 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_2) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_1) && BMC_MAX_GLOBAL_BI_LEDS == 1 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_3) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_2) && BMC_MAX_GLOBAL_BI_LEDS == 2 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_4) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_3) && BMC_MAX_GLOBAL_BI_LEDS == 3 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_5) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_4) && BMC_MAX_GLOBAL_BI_LEDS == 4 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_6) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_5) && BMC_MAX_GLOBAL_BI_LEDS == 5 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_7) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_6) && BMC_MAX_GLOBAL_BI_LEDS == 6 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_8) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_7) && BMC_MAX_GLOBAL_BI_LEDS == 7 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_9) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_8) && BMC_MAX_GLOBAL_BI_LEDS == 8 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_10) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_9) && BMC_MAX_GLOBAL_BI_LEDS == 9 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_11) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_10) && BMC_MAX_GLOBAL_BI_LEDS == 10 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_12) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_11) && BMC_MAX_GLOBAL_BI_LEDS == 11 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_13) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_12) && BMC_MAX_GLOBAL_BI_LEDS == 12 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_14) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_13) && BMC_MAX_GLOBAL_BI_LEDS == 13 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_15) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_14) && BMC_MAX_GLOBAL_BI_LEDS == 14 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_16) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_15) && BMC_MAX_GLOBAL_BI_LEDS == 15 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_17) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_16) && BMC_MAX_GLOBAL_BI_LEDS == 16 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_18) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_17) && BMC_MAX_GLOBAL_BI_LEDS == 17 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_19) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_18) && BMC_MAX_GLOBAL_BI_LEDS == 18 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_20) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_19) && BMC_MAX_GLOBAL_BI_LEDS == 19 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_21) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_20) && BMC_MAX_GLOBAL_BI_LEDS == 20 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_22) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_21) && BMC_MAX_GLOBAL_BI_LEDS == 21 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_23) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_22) && BMC_MAX_GLOBAL_BI_LEDS == 22 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_24) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_23) && BMC_MAX_GLOBAL_BI_LEDS == 23 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_25) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_24) && BMC_MAX_GLOBAL_BI_LEDS == 24 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_26) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_25) && BMC_MAX_GLOBAL_BI_LEDS == 25 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_27) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_26) && BMC_MAX_GLOBAL_BI_LEDS == 26 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_28) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_27) && BMC_MAX_GLOBAL_BI_LEDS == 27 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_29) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_28) && BMC_MAX_GLOBAL_BI_LEDS == 28 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_30) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_29) && BMC_MAX_GLOBAL_BI_LEDS == 29 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_31) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_30) && BMC_MAX_GLOBAL_BI_LEDS == 30 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_32) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_31) && BMC_MAX_GLOBAL_BI_LEDS == 31 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_33) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_32) && BMC_MAX_GLOBAL_BI_LEDS == 32 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_34) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_33) && BMC_MAX_GLOBAL_BI_LEDS == 33 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_35) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_34) && BMC_MAX_GLOBAL_BI_LEDS == 34 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_36) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_35) && BMC_MAX_GLOBAL_BI_LEDS == 35 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_37) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_36) && BMC_MAX_GLOBAL_BI_LEDS == 36 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_38) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_37) && BMC_MAX_GLOBAL_BI_LEDS == 37 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_39) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_38) && BMC_MAX_GLOBAL_BI_LEDS == 38 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_40) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_39) && BMC_MAX_GLOBAL_BI_LEDS == 39 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_41) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_40) && BMC_MAX_GLOBAL_BI_LEDS == 40 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_42) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_41) && BMC_MAX_GLOBAL_BI_LEDS == 41 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_43) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_42) && BMC_MAX_GLOBAL_BI_LEDS == 42 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_44) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_43) && BMC_MAX_GLOBAL_BI_LEDS == 43 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_45) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_44) && BMC_MAX_GLOBAL_BI_LEDS == 44 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_46) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_45) && BMC_MAX_GLOBAL_BI_LEDS == 45 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_47) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_46) && BMC_MAX_GLOBAL_BI_LEDS == 46 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_48) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_47) && BMC_MAX_GLOBAL_BI_LEDS == 47 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_49) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_48) && BMC_MAX_GLOBAL_BI_LEDS == 48 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_50) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_49) && BMC_MAX_GLOBAL_BI_LEDS == 49 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_51) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_50) && BMC_MAX_GLOBAL_BI_LEDS == 50 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_52) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_51) && BMC_MAX_GLOBAL_BI_LEDS == 51 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_53) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_52) && BMC_MAX_GLOBAL_BI_LEDS == 52 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_54) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_53) && BMC_MAX_GLOBAL_BI_LEDS == 53 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_55) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_54) && BMC_MAX_GLOBAL_BI_LEDS == 54 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_56) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_55) && BMC_MAX_GLOBAL_BI_LEDS == 55 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_57) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_56) && BMC_MAX_GLOBAL_BI_LEDS == 56 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_58) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_57) && BMC_MAX_GLOBAL_BI_LEDS == 57 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_59) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_58) && BMC_MAX_GLOBAL_BI_LEDS == 58 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_60) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_59) && BMC_MAX_GLOBAL_BI_LEDS == 59 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_61) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_60) && BMC_MAX_GLOBAL_BI_LEDS == 60 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_62) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_61) && BMC_MAX_GLOBAL_BI_LEDS == 61 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_63) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_62) && BMC_MAX_GLOBAL_BI_LEDS == 62 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_BI_LED_64) && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_63) && BMC_MAX_GLOBAL_BI_LEDS == 63 
  #ifdef BMC_MAX_GLOBAL_BI_LEDS
    #undef BMC_MAX_GLOBAL_BI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_BI_LEDS 64
#endif

// *******************************************
// *** GLOBAL_BI_LEDS end
// *******************************************

// *******************************************
// *** TRI_LEDS start
// *******************************************

#ifdef BMC_MAX_TRI_LEDS
  #undef BMC_MAX_TRI_LEDS
#endif

#define BMC_MAX_TRI_LEDS 0

#if defined(BMC_DEVICE_UI_TRI_LED_1) && BMC_MAX_TRI_LEDS == 0 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 1
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_2) && defined(BMC_DEVICE_UI_TRI_LED_1) && BMC_MAX_TRI_LEDS == 1 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 2
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_3) && defined(BMC_DEVICE_UI_TRI_LED_2) && BMC_MAX_TRI_LEDS == 2 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 3
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_4) && defined(BMC_DEVICE_UI_TRI_LED_3) && BMC_MAX_TRI_LEDS == 3 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 4
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_5) && defined(BMC_DEVICE_UI_TRI_LED_4) && BMC_MAX_TRI_LEDS == 4 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 5
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_6) && defined(BMC_DEVICE_UI_TRI_LED_5) && BMC_MAX_TRI_LEDS == 5 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 6
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_7) && defined(BMC_DEVICE_UI_TRI_LED_6) && BMC_MAX_TRI_LEDS == 6 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 7
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_8) && defined(BMC_DEVICE_UI_TRI_LED_7) && BMC_MAX_TRI_LEDS == 7 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 8
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_9) && defined(BMC_DEVICE_UI_TRI_LED_8) && BMC_MAX_TRI_LEDS == 8 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 9
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_10) && defined(BMC_DEVICE_UI_TRI_LED_9) && BMC_MAX_TRI_LEDS == 9 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 10
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_11) && defined(BMC_DEVICE_UI_TRI_LED_10) && BMC_MAX_TRI_LEDS == 10 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 11
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_12) && defined(BMC_DEVICE_UI_TRI_LED_11) && BMC_MAX_TRI_LEDS == 11 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 12
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_13) && defined(BMC_DEVICE_UI_TRI_LED_12) && BMC_MAX_TRI_LEDS == 12 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 13
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_14) && defined(BMC_DEVICE_UI_TRI_LED_13) && BMC_MAX_TRI_LEDS == 13 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 14
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_15) && defined(BMC_DEVICE_UI_TRI_LED_14) && BMC_MAX_TRI_LEDS == 14 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 15
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_16) && defined(BMC_DEVICE_UI_TRI_LED_15) && BMC_MAX_TRI_LEDS == 15 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 16
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_17) && defined(BMC_DEVICE_UI_TRI_LED_16) && BMC_MAX_TRI_LEDS == 16 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 17
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_18) && defined(BMC_DEVICE_UI_TRI_LED_17) && BMC_MAX_TRI_LEDS == 17 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 18
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_19) && defined(BMC_DEVICE_UI_TRI_LED_18) && BMC_MAX_TRI_LEDS == 18 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 19
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_20) && defined(BMC_DEVICE_UI_TRI_LED_19) && BMC_MAX_TRI_LEDS == 19 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 20
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_21) && defined(BMC_DEVICE_UI_TRI_LED_20) && BMC_MAX_TRI_LEDS == 20 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 21
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_22) && defined(BMC_DEVICE_UI_TRI_LED_21) && BMC_MAX_TRI_LEDS == 21 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 22
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_23) && defined(BMC_DEVICE_UI_TRI_LED_22) && BMC_MAX_TRI_LEDS == 22 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 23
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_24) && defined(BMC_DEVICE_UI_TRI_LED_23) && BMC_MAX_TRI_LEDS == 23 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 24
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_25) && defined(BMC_DEVICE_UI_TRI_LED_24) && BMC_MAX_TRI_LEDS == 24 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 25
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_26) && defined(BMC_DEVICE_UI_TRI_LED_25) && BMC_MAX_TRI_LEDS == 25 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 26
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_27) && defined(BMC_DEVICE_UI_TRI_LED_26) && BMC_MAX_TRI_LEDS == 26 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 27
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_28) && defined(BMC_DEVICE_UI_TRI_LED_27) && BMC_MAX_TRI_LEDS == 27 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 28
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_29) && defined(BMC_DEVICE_UI_TRI_LED_28) && BMC_MAX_TRI_LEDS == 28 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 29
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_30) && defined(BMC_DEVICE_UI_TRI_LED_29) && BMC_MAX_TRI_LEDS == 29 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 30
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_31) && defined(BMC_DEVICE_UI_TRI_LED_30) && BMC_MAX_TRI_LEDS == 30 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 31
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_32) && defined(BMC_DEVICE_UI_TRI_LED_31) && BMC_MAX_TRI_LEDS == 31 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 32
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_33) && defined(BMC_DEVICE_UI_TRI_LED_32) && BMC_MAX_TRI_LEDS == 32 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 33
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_34) && defined(BMC_DEVICE_UI_TRI_LED_33) && BMC_MAX_TRI_LEDS == 33 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 34
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_35) && defined(BMC_DEVICE_UI_TRI_LED_34) && BMC_MAX_TRI_LEDS == 34 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 35
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_36) && defined(BMC_DEVICE_UI_TRI_LED_35) && BMC_MAX_TRI_LEDS == 35 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 36
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_37) && defined(BMC_DEVICE_UI_TRI_LED_36) && BMC_MAX_TRI_LEDS == 36 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 37
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_38) && defined(BMC_DEVICE_UI_TRI_LED_37) && BMC_MAX_TRI_LEDS == 37 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 38
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_39) && defined(BMC_DEVICE_UI_TRI_LED_38) && BMC_MAX_TRI_LEDS == 38 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 39
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_40) && defined(BMC_DEVICE_UI_TRI_LED_39) && BMC_MAX_TRI_LEDS == 39 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 40
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_41) && defined(BMC_DEVICE_UI_TRI_LED_40) && BMC_MAX_TRI_LEDS == 40 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 41
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_42) && defined(BMC_DEVICE_UI_TRI_LED_41) && BMC_MAX_TRI_LEDS == 41 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 42
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_43) && defined(BMC_DEVICE_UI_TRI_LED_42) && BMC_MAX_TRI_LEDS == 42 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 43
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_44) && defined(BMC_DEVICE_UI_TRI_LED_43) && BMC_MAX_TRI_LEDS == 43 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 44
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_45) && defined(BMC_DEVICE_UI_TRI_LED_44) && BMC_MAX_TRI_LEDS == 44 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 45
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_46) && defined(BMC_DEVICE_UI_TRI_LED_45) && BMC_MAX_TRI_LEDS == 45 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 46
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_47) && defined(BMC_DEVICE_UI_TRI_LED_46) && BMC_MAX_TRI_LEDS == 46 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 47
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_48) && defined(BMC_DEVICE_UI_TRI_LED_47) && BMC_MAX_TRI_LEDS == 47 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 48
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_49) && defined(BMC_DEVICE_UI_TRI_LED_48) && BMC_MAX_TRI_LEDS == 48 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 49
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_50) && defined(BMC_DEVICE_UI_TRI_LED_49) && BMC_MAX_TRI_LEDS == 49 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 50
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_51) && defined(BMC_DEVICE_UI_TRI_LED_50) && BMC_MAX_TRI_LEDS == 50 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 51
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_52) && defined(BMC_DEVICE_UI_TRI_LED_51) && BMC_MAX_TRI_LEDS == 51 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 52
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_53) && defined(BMC_DEVICE_UI_TRI_LED_52) && BMC_MAX_TRI_LEDS == 52 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 53
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_54) && defined(BMC_DEVICE_UI_TRI_LED_53) && BMC_MAX_TRI_LEDS == 53 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 54
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_55) && defined(BMC_DEVICE_UI_TRI_LED_54) && BMC_MAX_TRI_LEDS == 54 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 55
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_56) && defined(BMC_DEVICE_UI_TRI_LED_55) && BMC_MAX_TRI_LEDS == 55 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 56
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_57) && defined(BMC_DEVICE_UI_TRI_LED_56) && BMC_MAX_TRI_LEDS == 56 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 57
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_58) && defined(BMC_DEVICE_UI_TRI_LED_57) && BMC_MAX_TRI_LEDS == 57 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 58
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_59) && defined(BMC_DEVICE_UI_TRI_LED_58) && BMC_MAX_TRI_LEDS == 58 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 59
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_60) && defined(BMC_DEVICE_UI_TRI_LED_59) && BMC_MAX_TRI_LEDS == 59 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 60
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_61) && defined(BMC_DEVICE_UI_TRI_LED_60) && BMC_MAX_TRI_LEDS == 60 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 61
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_62) && defined(BMC_DEVICE_UI_TRI_LED_61) && BMC_MAX_TRI_LEDS == 61 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 62
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_63) && defined(BMC_DEVICE_UI_TRI_LED_62) && BMC_MAX_TRI_LEDS == 62 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 63
#endif

#if defined(BMC_DEVICE_UI_TRI_LED_64) && defined(BMC_DEVICE_UI_TRI_LED_63) && BMC_MAX_TRI_LEDS == 63 
  #ifdef BMC_MAX_TRI_LEDS
    #undef BMC_MAX_TRI_LEDS
  #endif

  #define BMC_MAX_TRI_LEDS 64
#endif

// *******************************************
// *** TRI_LEDS end
// *******************************************

// *******************************************
// *** GLOBAL_TRI_LEDS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_TRI_LEDS
  #undef BMC_MAX_GLOBAL_TRI_LEDS
#endif

#define BMC_MAX_GLOBAL_TRI_LEDS 0

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_1) && BMC_MAX_GLOBAL_TRI_LEDS == 0 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_2) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_1) && BMC_MAX_GLOBAL_TRI_LEDS == 1 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_3) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_2) && BMC_MAX_GLOBAL_TRI_LEDS == 2 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_4) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_3) && BMC_MAX_GLOBAL_TRI_LEDS == 3 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_5) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_4) && BMC_MAX_GLOBAL_TRI_LEDS == 4 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_6) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_5) && BMC_MAX_GLOBAL_TRI_LEDS == 5 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_7) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_6) && BMC_MAX_GLOBAL_TRI_LEDS == 6 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_8) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_7) && BMC_MAX_GLOBAL_TRI_LEDS == 7 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_9) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_8) && BMC_MAX_GLOBAL_TRI_LEDS == 8 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_10) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_9) && BMC_MAX_GLOBAL_TRI_LEDS == 9 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_11) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_10) && BMC_MAX_GLOBAL_TRI_LEDS == 10 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_12) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_11) && BMC_MAX_GLOBAL_TRI_LEDS == 11 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_13) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_12) && BMC_MAX_GLOBAL_TRI_LEDS == 12 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_14) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_13) && BMC_MAX_GLOBAL_TRI_LEDS == 13 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_15) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_14) && BMC_MAX_GLOBAL_TRI_LEDS == 14 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_16) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_15) && BMC_MAX_GLOBAL_TRI_LEDS == 15 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_17) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_16) && BMC_MAX_GLOBAL_TRI_LEDS == 16 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_18) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_17) && BMC_MAX_GLOBAL_TRI_LEDS == 17 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_19) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_18) && BMC_MAX_GLOBAL_TRI_LEDS == 18 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_20) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_19) && BMC_MAX_GLOBAL_TRI_LEDS == 19 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_21) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_20) && BMC_MAX_GLOBAL_TRI_LEDS == 20 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_22) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_21) && BMC_MAX_GLOBAL_TRI_LEDS == 21 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_23) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_22) && BMC_MAX_GLOBAL_TRI_LEDS == 22 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_24) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_23) && BMC_MAX_GLOBAL_TRI_LEDS == 23 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_25) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_24) && BMC_MAX_GLOBAL_TRI_LEDS == 24 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_26) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_25) && BMC_MAX_GLOBAL_TRI_LEDS == 25 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_27) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_26) && BMC_MAX_GLOBAL_TRI_LEDS == 26 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_28) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_27) && BMC_MAX_GLOBAL_TRI_LEDS == 27 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_29) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_28) && BMC_MAX_GLOBAL_TRI_LEDS == 28 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_30) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_29) && BMC_MAX_GLOBAL_TRI_LEDS == 29 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_31) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_30) && BMC_MAX_GLOBAL_TRI_LEDS == 30 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_32) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_31) && BMC_MAX_GLOBAL_TRI_LEDS == 31 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_33) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_32) && BMC_MAX_GLOBAL_TRI_LEDS == 32 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_34) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_33) && BMC_MAX_GLOBAL_TRI_LEDS == 33 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_35) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_34) && BMC_MAX_GLOBAL_TRI_LEDS == 34 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_36) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_35) && BMC_MAX_GLOBAL_TRI_LEDS == 35 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_37) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_36) && BMC_MAX_GLOBAL_TRI_LEDS == 36 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_38) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_37) && BMC_MAX_GLOBAL_TRI_LEDS == 37 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_39) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_38) && BMC_MAX_GLOBAL_TRI_LEDS == 38 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_40) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_39) && BMC_MAX_GLOBAL_TRI_LEDS == 39 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_41) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_40) && BMC_MAX_GLOBAL_TRI_LEDS == 40 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_42) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_41) && BMC_MAX_GLOBAL_TRI_LEDS == 41 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_43) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_42) && BMC_MAX_GLOBAL_TRI_LEDS == 42 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_44) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_43) && BMC_MAX_GLOBAL_TRI_LEDS == 43 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_45) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_44) && BMC_MAX_GLOBAL_TRI_LEDS == 44 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_46) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_45) && BMC_MAX_GLOBAL_TRI_LEDS == 45 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_47) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_46) && BMC_MAX_GLOBAL_TRI_LEDS == 46 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_48) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_47) && BMC_MAX_GLOBAL_TRI_LEDS == 47 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_49) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_48) && BMC_MAX_GLOBAL_TRI_LEDS == 48 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_50) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_49) && BMC_MAX_GLOBAL_TRI_LEDS == 49 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_51) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_50) && BMC_MAX_GLOBAL_TRI_LEDS == 50 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_52) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_51) && BMC_MAX_GLOBAL_TRI_LEDS == 51 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_53) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_52) && BMC_MAX_GLOBAL_TRI_LEDS == 52 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_54) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_53) && BMC_MAX_GLOBAL_TRI_LEDS == 53 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_55) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_54) && BMC_MAX_GLOBAL_TRI_LEDS == 54 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_56) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_55) && BMC_MAX_GLOBAL_TRI_LEDS == 55 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_57) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_56) && BMC_MAX_GLOBAL_TRI_LEDS == 56 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_58) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_57) && BMC_MAX_GLOBAL_TRI_LEDS == 57 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_59) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_58) && BMC_MAX_GLOBAL_TRI_LEDS == 58 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_60) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_59) && BMC_MAX_GLOBAL_TRI_LEDS == 59 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_61) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_60) && BMC_MAX_GLOBAL_TRI_LEDS == 60 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_62) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_61) && BMC_MAX_GLOBAL_TRI_LEDS == 61 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_63) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_62) && BMC_MAX_GLOBAL_TRI_LEDS == 62 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_64) && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_63) && BMC_MAX_GLOBAL_TRI_LEDS == 63 
  #ifdef BMC_MAX_GLOBAL_TRI_LEDS
    #undef BMC_MAX_GLOBAL_TRI_LEDS
  #endif

  #define BMC_MAX_GLOBAL_TRI_LEDS 64
#endif

// *******************************************
// *** GLOBAL_TRI_LEDS end
// *******************************************

// *******************************************
// *** POTS start
// *******************************************

#ifdef BMC_MAX_POTS
  #undef BMC_MAX_POTS
#endif

#define BMC_MAX_POTS 0

#if defined(BMC_DEVICE_UI_POT_1) && BMC_MAX_POTS == 0 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 1
#endif

#if defined(BMC_DEVICE_UI_POT_2) && defined(BMC_DEVICE_UI_POT_1) && BMC_MAX_POTS == 1 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 2
#endif

#if defined(BMC_DEVICE_UI_POT_3) && defined(BMC_DEVICE_UI_POT_2) && BMC_MAX_POTS == 2 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 3
#endif

#if defined(BMC_DEVICE_UI_POT_4) && defined(BMC_DEVICE_UI_POT_3) && BMC_MAX_POTS == 3 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 4
#endif

#if defined(BMC_DEVICE_UI_POT_5) && defined(BMC_DEVICE_UI_POT_4) && BMC_MAX_POTS == 4 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 5
#endif

#if defined(BMC_DEVICE_UI_POT_6) && defined(BMC_DEVICE_UI_POT_5) && BMC_MAX_POTS == 5 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 6
#endif

#if defined(BMC_DEVICE_UI_POT_7) && defined(BMC_DEVICE_UI_POT_6) && BMC_MAX_POTS == 6 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 7
#endif

#if defined(BMC_DEVICE_UI_POT_8) && defined(BMC_DEVICE_UI_POT_7) && BMC_MAX_POTS == 7 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 8
#endif

#if defined(BMC_DEVICE_UI_POT_9) && defined(BMC_DEVICE_UI_POT_8) && BMC_MAX_POTS == 8 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 9
#endif

#if defined(BMC_DEVICE_UI_POT_10) && defined(BMC_DEVICE_UI_POT_9) && BMC_MAX_POTS == 9 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 10
#endif

#if defined(BMC_DEVICE_UI_POT_11) && defined(BMC_DEVICE_UI_POT_10) && BMC_MAX_POTS == 10 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 11
#endif

#if defined(BMC_DEVICE_UI_POT_12) && defined(BMC_DEVICE_UI_POT_11) && BMC_MAX_POTS == 11 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 12
#endif

#if defined(BMC_DEVICE_UI_POT_13) && defined(BMC_DEVICE_UI_POT_12) && BMC_MAX_POTS == 12 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 13
#endif

#if defined(BMC_DEVICE_UI_POT_14) && defined(BMC_DEVICE_UI_POT_13) && BMC_MAX_POTS == 13 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 14
#endif

#if defined(BMC_DEVICE_UI_POT_15) && defined(BMC_DEVICE_UI_POT_14) && BMC_MAX_POTS == 14 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 15
#endif

#if defined(BMC_DEVICE_UI_POT_16) && defined(BMC_DEVICE_UI_POT_15) && BMC_MAX_POTS == 15 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 16
#endif

#if defined(BMC_DEVICE_UI_POT_17) && defined(BMC_DEVICE_UI_POT_16) && BMC_MAX_POTS == 16 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 17
#endif

#if defined(BMC_DEVICE_UI_POT_18) && defined(BMC_DEVICE_UI_POT_17) && BMC_MAX_POTS == 17 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 18
#endif

#if defined(BMC_DEVICE_UI_POT_19) && defined(BMC_DEVICE_UI_POT_18) && BMC_MAX_POTS == 18 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 19
#endif

#if defined(BMC_DEVICE_UI_POT_20) && defined(BMC_DEVICE_UI_POT_19) && BMC_MAX_POTS == 19 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 20
#endif

#if defined(BMC_DEVICE_UI_POT_21) && defined(BMC_DEVICE_UI_POT_20) && BMC_MAX_POTS == 20 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 21
#endif

#if defined(BMC_DEVICE_UI_POT_22) && defined(BMC_DEVICE_UI_POT_21) && BMC_MAX_POTS == 21 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 22
#endif

#if defined(BMC_DEVICE_UI_POT_23) && defined(BMC_DEVICE_UI_POT_22) && BMC_MAX_POTS == 22 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 23
#endif

#if defined(BMC_DEVICE_UI_POT_24) && defined(BMC_DEVICE_UI_POT_23) && BMC_MAX_POTS == 23 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 24
#endif

#if defined(BMC_DEVICE_UI_POT_25) && defined(BMC_DEVICE_UI_POT_24) && BMC_MAX_POTS == 24 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 25
#endif

#if defined(BMC_DEVICE_UI_POT_26) && defined(BMC_DEVICE_UI_POT_25) && BMC_MAX_POTS == 25 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 26
#endif

#if defined(BMC_DEVICE_UI_POT_27) && defined(BMC_DEVICE_UI_POT_26) && BMC_MAX_POTS == 26 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 27
#endif

#if defined(BMC_DEVICE_UI_POT_28) && defined(BMC_DEVICE_UI_POT_27) && BMC_MAX_POTS == 27 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 28
#endif

#if defined(BMC_DEVICE_UI_POT_29) && defined(BMC_DEVICE_UI_POT_28) && BMC_MAX_POTS == 28 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 29
#endif

#if defined(BMC_DEVICE_UI_POT_30) && defined(BMC_DEVICE_UI_POT_29) && BMC_MAX_POTS == 29 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 30
#endif

#if defined(BMC_DEVICE_UI_POT_31) && defined(BMC_DEVICE_UI_POT_30) && BMC_MAX_POTS == 30 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 31
#endif

#if defined(BMC_DEVICE_UI_POT_32) && defined(BMC_DEVICE_UI_POT_31) && BMC_MAX_POTS == 31 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 32
#endif

#if defined(BMC_DEVICE_UI_POT_33) && defined(BMC_DEVICE_UI_POT_32) && BMC_MAX_POTS == 32 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 33
#endif

#if defined(BMC_DEVICE_UI_POT_34) && defined(BMC_DEVICE_UI_POT_33) && BMC_MAX_POTS == 33 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 34
#endif

#if defined(BMC_DEVICE_UI_POT_35) && defined(BMC_DEVICE_UI_POT_34) && BMC_MAX_POTS == 34 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 35
#endif

#if defined(BMC_DEVICE_UI_POT_36) && defined(BMC_DEVICE_UI_POT_35) && BMC_MAX_POTS == 35 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 36
#endif

#if defined(BMC_DEVICE_UI_POT_37) && defined(BMC_DEVICE_UI_POT_36) && BMC_MAX_POTS == 36 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 37
#endif

#if defined(BMC_DEVICE_UI_POT_38) && defined(BMC_DEVICE_UI_POT_37) && BMC_MAX_POTS == 37 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 38
#endif

#if defined(BMC_DEVICE_UI_POT_39) && defined(BMC_DEVICE_UI_POT_38) && BMC_MAX_POTS == 38 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 39
#endif

#if defined(BMC_DEVICE_UI_POT_40) && defined(BMC_DEVICE_UI_POT_39) && BMC_MAX_POTS == 39 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 40
#endif

#if defined(BMC_DEVICE_UI_POT_41) && defined(BMC_DEVICE_UI_POT_40) && BMC_MAX_POTS == 40 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 41
#endif

#if defined(BMC_DEVICE_UI_POT_42) && defined(BMC_DEVICE_UI_POT_41) && BMC_MAX_POTS == 41 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 42
#endif

#if defined(BMC_DEVICE_UI_POT_43) && defined(BMC_DEVICE_UI_POT_42) && BMC_MAX_POTS == 42 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 43
#endif

#if defined(BMC_DEVICE_UI_POT_44) && defined(BMC_DEVICE_UI_POT_43) && BMC_MAX_POTS == 43 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 44
#endif

#if defined(BMC_DEVICE_UI_POT_45) && defined(BMC_DEVICE_UI_POT_44) && BMC_MAX_POTS == 44 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 45
#endif

#if defined(BMC_DEVICE_UI_POT_46) && defined(BMC_DEVICE_UI_POT_45) && BMC_MAX_POTS == 45 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 46
#endif

#if defined(BMC_DEVICE_UI_POT_47) && defined(BMC_DEVICE_UI_POT_46) && BMC_MAX_POTS == 46 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 47
#endif

#if defined(BMC_DEVICE_UI_POT_48) && defined(BMC_DEVICE_UI_POT_47) && BMC_MAX_POTS == 47 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 48
#endif

#if defined(BMC_DEVICE_UI_POT_49) && defined(BMC_DEVICE_UI_POT_48) && BMC_MAX_POTS == 48 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 49
#endif

#if defined(BMC_DEVICE_UI_POT_50) && defined(BMC_DEVICE_UI_POT_49) && BMC_MAX_POTS == 49 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 50
#endif

#if defined(BMC_DEVICE_UI_POT_51) && defined(BMC_DEVICE_UI_POT_50) && BMC_MAX_POTS == 50 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 51
#endif

#if defined(BMC_DEVICE_UI_POT_52) && defined(BMC_DEVICE_UI_POT_51) && BMC_MAX_POTS == 51 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 52
#endif

#if defined(BMC_DEVICE_UI_POT_53) && defined(BMC_DEVICE_UI_POT_52) && BMC_MAX_POTS == 52 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 53
#endif

#if defined(BMC_DEVICE_UI_POT_54) && defined(BMC_DEVICE_UI_POT_53) && BMC_MAX_POTS == 53 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 54
#endif

#if defined(BMC_DEVICE_UI_POT_55) && defined(BMC_DEVICE_UI_POT_54) && BMC_MAX_POTS == 54 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 55
#endif

#if defined(BMC_DEVICE_UI_POT_56) && defined(BMC_DEVICE_UI_POT_55) && BMC_MAX_POTS == 55 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 56
#endif

#if defined(BMC_DEVICE_UI_POT_57) && defined(BMC_DEVICE_UI_POT_56) && BMC_MAX_POTS == 56 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 57
#endif

#if defined(BMC_DEVICE_UI_POT_58) && defined(BMC_DEVICE_UI_POT_57) && BMC_MAX_POTS == 57 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 58
#endif

#if defined(BMC_DEVICE_UI_POT_59) && defined(BMC_DEVICE_UI_POT_58) && BMC_MAX_POTS == 58 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 59
#endif

#if defined(BMC_DEVICE_UI_POT_60) && defined(BMC_DEVICE_UI_POT_59) && BMC_MAX_POTS == 59 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 60
#endif

#if defined(BMC_DEVICE_UI_POT_61) && defined(BMC_DEVICE_UI_POT_60) && BMC_MAX_POTS == 60 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 61
#endif

#if defined(BMC_DEVICE_UI_POT_62) && defined(BMC_DEVICE_UI_POT_61) && BMC_MAX_POTS == 61 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 62
#endif

#if defined(BMC_DEVICE_UI_POT_63) && defined(BMC_DEVICE_UI_POT_62) && BMC_MAX_POTS == 62 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 63
#endif

#if defined(BMC_DEVICE_UI_POT_64) && defined(BMC_DEVICE_UI_POT_63) && BMC_MAX_POTS == 63 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 64
#endif

#if defined(BMC_DEVICE_UI_POT_65) && defined(BMC_DEVICE_UI_POT_64) && BMC_MAX_POTS == 64 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 65
#endif

#if defined(BMC_DEVICE_UI_POT_66) && defined(BMC_DEVICE_UI_POT_65) && BMC_MAX_POTS == 65 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 66
#endif

#if defined(BMC_DEVICE_UI_POT_67) && defined(BMC_DEVICE_UI_POT_66) && BMC_MAX_POTS == 66 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 67
#endif

#if defined(BMC_DEVICE_UI_POT_68) && defined(BMC_DEVICE_UI_POT_67) && BMC_MAX_POTS == 67 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 68
#endif

#if defined(BMC_DEVICE_UI_POT_69) && defined(BMC_DEVICE_UI_POT_68) && BMC_MAX_POTS == 68 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 69
#endif

#if defined(BMC_DEVICE_UI_POT_70) && defined(BMC_DEVICE_UI_POT_69) && BMC_MAX_POTS == 69 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 70
#endif

#if defined(BMC_DEVICE_UI_POT_71) && defined(BMC_DEVICE_UI_POT_70) && BMC_MAX_POTS == 70 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 71
#endif

#if defined(BMC_DEVICE_UI_POT_72) && defined(BMC_DEVICE_UI_POT_71) && BMC_MAX_POTS == 71 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 72
#endif

#if defined(BMC_DEVICE_UI_POT_73) && defined(BMC_DEVICE_UI_POT_72) && BMC_MAX_POTS == 72 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 73
#endif

#if defined(BMC_DEVICE_UI_POT_74) && defined(BMC_DEVICE_UI_POT_73) && BMC_MAX_POTS == 73 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 74
#endif

#if defined(BMC_DEVICE_UI_POT_75) && defined(BMC_DEVICE_UI_POT_74) && BMC_MAX_POTS == 74 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 75
#endif

#if defined(BMC_DEVICE_UI_POT_76) && defined(BMC_DEVICE_UI_POT_75) && BMC_MAX_POTS == 75 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 76
#endif

#if defined(BMC_DEVICE_UI_POT_77) && defined(BMC_DEVICE_UI_POT_76) && BMC_MAX_POTS == 76 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 77
#endif

#if defined(BMC_DEVICE_UI_POT_78) && defined(BMC_DEVICE_UI_POT_77) && BMC_MAX_POTS == 77 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 78
#endif

#if defined(BMC_DEVICE_UI_POT_79) && defined(BMC_DEVICE_UI_POT_78) && BMC_MAX_POTS == 78 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 79
#endif

#if defined(BMC_DEVICE_UI_POT_80) && defined(BMC_DEVICE_UI_POT_79) && BMC_MAX_POTS == 79 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 80
#endif

#if defined(BMC_DEVICE_UI_POT_81) && defined(BMC_DEVICE_UI_POT_80) && BMC_MAX_POTS == 80 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 81
#endif

#if defined(BMC_DEVICE_UI_POT_82) && defined(BMC_DEVICE_UI_POT_81) && BMC_MAX_POTS == 81 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 82
#endif

#if defined(BMC_DEVICE_UI_POT_83) && defined(BMC_DEVICE_UI_POT_82) && BMC_MAX_POTS == 82 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 83
#endif

#if defined(BMC_DEVICE_UI_POT_84) && defined(BMC_DEVICE_UI_POT_83) && BMC_MAX_POTS == 83 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 84
#endif

#if defined(BMC_DEVICE_UI_POT_85) && defined(BMC_DEVICE_UI_POT_84) && BMC_MAX_POTS == 84 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 85
#endif

#if defined(BMC_DEVICE_UI_POT_86) && defined(BMC_DEVICE_UI_POT_85) && BMC_MAX_POTS == 85 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 86
#endif

#if defined(BMC_DEVICE_UI_POT_87) && defined(BMC_DEVICE_UI_POT_86) && BMC_MAX_POTS == 86 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 87
#endif

#if defined(BMC_DEVICE_UI_POT_88) && defined(BMC_DEVICE_UI_POT_87) && BMC_MAX_POTS == 87 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 88
#endif

#if defined(BMC_DEVICE_UI_POT_89) && defined(BMC_DEVICE_UI_POT_88) && BMC_MAX_POTS == 88 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 89
#endif

#if defined(BMC_DEVICE_UI_POT_90) && defined(BMC_DEVICE_UI_POT_89) && BMC_MAX_POTS == 89 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 90
#endif

#if defined(BMC_DEVICE_UI_POT_91) && defined(BMC_DEVICE_UI_POT_90) && BMC_MAX_POTS == 90 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 91
#endif

#if defined(BMC_DEVICE_UI_POT_92) && defined(BMC_DEVICE_UI_POT_91) && BMC_MAX_POTS == 91 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 92
#endif

#if defined(BMC_DEVICE_UI_POT_93) && defined(BMC_DEVICE_UI_POT_92) && BMC_MAX_POTS == 92 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 93
#endif

#if defined(BMC_DEVICE_UI_POT_94) && defined(BMC_DEVICE_UI_POT_93) && BMC_MAX_POTS == 93 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 94
#endif

#if defined(BMC_DEVICE_UI_POT_95) && defined(BMC_DEVICE_UI_POT_94) && BMC_MAX_POTS == 94 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 95
#endif

#if defined(BMC_DEVICE_UI_POT_96) && defined(BMC_DEVICE_UI_POT_95) && BMC_MAX_POTS == 95 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 96
#endif

#if defined(BMC_DEVICE_UI_POT_97) && defined(BMC_DEVICE_UI_POT_96) && BMC_MAX_POTS == 96 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 97
#endif

#if defined(BMC_DEVICE_UI_POT_98) && defined(BMC_DEVICE_UI_POT_97) && BMC_MAX_POTS == 97 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 98
#endif

#if defined(BMC_DEVICE_UI_POT_99) && defined(BMC_DEVICE_UI_POT_98) && BMC_MAX_POTS == 98 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 99
#endif

#if defined(BMC_DEVICE_UI_POT_100) && defined(BMC_DEVICE_UI_POT_99) && BMC_MAX_POTS == 99 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 100
#endif

#if defined(BMC_DEVICE_UI_POT_101) && defined(BMC_DEVICE_UI_POT_100) && BMC_MAX_POTS == 100 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 101
#endif

#if defined(BMC_DEVICE_UI_POT_102) && defined(BMC_DEVICE_UI_POT_101) && BMC_MAX_POTS == 101 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 102
#endif

#if defined(BMC_DEVICE_UI_POT_103) && defined(BMC_DEVICE_UI_POT_102) && BMC_MAX_POTS == 102 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 103
#endif

#if defined(BMC_DEVICE_UI_POT_104) && defined(BMC_DEVICE_UI_POT_103) && BMC_MAX_POTS == 103 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 104
#endif

#if defined(BMC_DEVICE_UI_POT_105) && defined(BMC_DEVICE_UI_POT_104) && BMC_MAX_POTS == 104 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 105
#endif

#if defined(BMC_DEVICE_UI_POT_106) && defined(BMC_DEVICE_UI_POT_105) && BMC_MAX_POTS == 105 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 106
#endif

#if defined(BMC_DEVICE_UI_POT_107) && defined(BMC_DEVICE_UI_POT_106) && BMC_MAX_POTS == 106 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 107
#endif

#if defined(BMC_DEVICE_UI_POT_108) && defined(BMC_DEVICE_UI_POT_107) && BMC_MAX_POTS == 107 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 108
#endif

#if defined(BMC_DEVICE_UI_POT_109) && defined(BMC_DEVICE_UI_POT_108) && BMC_MAX_POTS == 108 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 109
#endif

#if defined(BMC_DEVICE_UI_POT_110) && defined(BMC_DEVICE_UI_POT_109) && BMC_MAX_POTS == 109 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 110
#endif

#if defined(BMC_DEVICE_UI_POT_111) && defined(BMC_DEVICE_UI_POT_110) && BMC_MAX_POTS == 110 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 111
#endif

#if defined(BMC_DEVICE_UI_POT_112) && defined(BMC_DEVICE_UI_POT_111) && BMC_MAX_POTS == 111 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 112
#endif

#if defined(BMC_DEVICE_UI_POT_113) && defined(BMC_DEVICE_UI_POT_112) && BMC_MAX_POTS == 112 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 113
#endif

#if defined(BMC_DEVICE_UI_POT_114) && defined(BMC_DEVICE_UI_POT_113) && BMC_MAX_POTS == 113 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 114
#endif

#if defined(BMC_DEVICE_UI_POT_115) && defined(BMC_DEVICE_UI_POT_114) && BMC_MAX_POTS == 114 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 115
#endif

#if defined(BMC_DEVICE_UI_POT_116) && defined(BMC_DEVICE_UI_POT_115) && BMC_MAX_POTS == 115 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 116
#endif

#if defined(BMC_DEVICE_UI_POT_117) && defined(BMC_DEVICE_UI_POT_116) && BMC_MAX_POTS == 116 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 117
#endif

#if defined(BMC_DEVICE_UI_POT_118) && defined(BMC_DEVICE_UI_POT_117) && BMC_MAX_POTS == 117 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 118
#endif

#if defined(BMC_DEVICE_UI_POT_119) && defined(BMC_DEVICE_UI_POT_118) && BMC_MAX_POTS == 118 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 119
#endif

#if defined(BMC_DEVICE_UI_POT_120) && defined(BMC_DEVICE_UI_POT_119) && BMC_MAX_POTS == 119 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 120
#endif

#if defined(BMC_DEVICE_UI_POT_121) && defined(BMC_DEVICE_UI_POT_120) && BMC_MAX_POTS == 120 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 121
#endif

#if defined(BMC_DEVICE_UI_POT_122) && defined(BMC_DEVICE_UI_POT_121) && BMC_MAX_POTS == 121 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 122
#endif

#if defined(BMC_DEVICE_UI_POT_123) && defined(BMC_DEVICE_UI_POT_122) && BMC_MAX_POTS == 122 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 123
#endif

#if defined(BMC_DEVICE_UI_POT_124) && defined(BMC_DEVICE_UI_POT_123) && BMC_MAX_POTS == 123 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 124
#endif

#if defined(BMC_DEVICE_UI_POT_125) && defined(BMC_DEVICE_UI_POT_124) && BMC_MAX_POTS == 124 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 125
#endif

#if defined(BMC_DEVICE_UI_POT_126) && defined(BMC_DEVICE_UI_POT_125) && BMC_MAX_POTS == 125 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 126
#endif

#if defined(BMC_DEVICE_UI_POT_127) && defined(BMC_DEVICE_UI_POT_126) && BMC_MAX_POTS == 126 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 127
#endif

#if defined(BMC_DEVICE_UI_POT_128) && defined(BMC_DEVICE_UI_POT_127) && BMC_MAX_POTS == 127 
  #ifdef BMC_MAX_POTS
    #undef BMC_MAX_POTS
  #endif

  #define BMC_MAX_POTS 128
#endif

// *******************************************
// *** POTS end
// *******************************************

// *******************************************
// *** GLOBAL_POTS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_POTS
  #undef BMC_MAX_GLOBAL_POTS
#endif

#define BMC_MAX_GLOBAL_POTS 0

#if defined(BMC_DEVICE_UI_GLOBAL_POT_1) && BMC_MAX_GLOBAL_POTS == 0 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_2) && defined(BMC_DEVICE_UI_GLOBAL_POT_1) && BMC_MAX_GLOBAL_POTS == 1 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_3) && defined(BMC_DEVICE_UI_GLOBAL_POT_2) && BMC_MAX_GLOBAL_POTS == 2 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_4) && defined(BMC_DEVICE_UI_GLOBAL_POT_3) && BMC_MAX_GLOBAL_POTS == 3 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_5) && defined(BMC_DEVICE_UI_GLOBAL_POT_4) && BMC_MAX_GLOBAL_POTS == 4 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_6) && defined(BMC_DEVICE_UI_GLOBAL_POT_5) && BMC_MAX_GLOBAL_POTS == 5 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_7) && defined(BMC_DEVICE_UI_GLOBAL_POT_6) && BMC_MAX_GLOBAL_POTS == 6 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_8) && defined(BMC_DEVICE_UI_GLOBAL_POT_7) && BMC_MAX_GLOBAL_POTS == 7 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_9) && defined(BMC_DEVICE_UI_GLOBAL_POT_8) && BMC_MAX_GLOBAL_POTS == 8 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_10) && defined(BMC_DEVICE_UI_GLOBAL_POT_9) && BMC_MAX_GLOBAL_POTS == 9 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_11) && defined(BMC_DEVICE_UI_GLOBAL_POT_10) && BMC_MAX_GLOBAL_POTS == 10 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_12) && defined(BMC_DEVICE_UI_GLOBAL_POT_11) && BMC_MAX_GLOBAL_POTS == 11 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_13) && defined(BMC_DEVICE_UI_GLOBAL_POT_12) && BMC_MAX_GLOBAL_POTS == 12 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_14) && defined(BMC_DEVICE_UI_GLOBAL_POT_13) && BMC_MAX_GLOBAL_POTS == 13 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_15) && defined(BMC_DEVICE_UI_GLOBAL_POT_14) && BMC_MAX_GLOBAL_POTS == 14 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_16) && defined(BMC_DEVICE_UI_GLOBAL_POT_15) && BMC_MAX_GLOBAL_POTS == 15 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_17) && defined(BMC_DEVICE_UI_GLOBAL_POT_16) && BMC_MAX_GLOBAL_POTS == 16 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_18) && defined(BMC_DEVICE_UI_GLOBAL_POT_17) && BMC_MAX_GLOBAL_POTS == 17 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_19) && defined(BMC_DEVICE_UI_GLOBAL_POT_18) && BMC_MAX_GLOBAL_POTS == 18 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_20) && defined(BMC_DEVICE_UI_GLOBAL_POT_19) && BMC_MAX_GLOBAL_POTS == 19 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_21) && defined(BMC_DEVICE_UI_GLOBAL_POT_20) && BMC_MAX_GLOBAL_POTS == 20 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_22) && defined(BMC_DEVICE_UI_GLOBAL_POT_21) && BMC_MAX_GLOBAL_POTS == 21 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_23) && defined(BMC_DEVICE_UI_GLOBAL_POT_22) && BMC_MAX_GLOBAL_POTS == 22 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_24) && defined(BMC_DEVICE_UI_GLOBAL_POT_23) && BMC_MAX_GLOBAL_POTS == 23 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_25) && defined(BMC_DEVICE_UI_GLOBAL_POT_24) && BMC_MAX_GLOBAL_POTS == 24 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_26) && defined(BMC_DEVICE_UI_GLOBAL_POT_25) && BMC_MAX_GLOBAL_POTS == 25 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_27) && defined(BMC_DEVICE_UI_GLOBAL_POT_26) && BMC_MAX_GLOBAL_POTS == 26 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_28) && defined(BMC_DEVICE_UI_GLOBAL_POT_27) && BMC_MAX_GLOBAL_POTS == 27 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_29) && defined(BMC_DEVICE_UI_GLOBAL_POT_28) && BMC_MAX_GLOBAL_POTS == 28 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_30) && defined(BMC_DEVICE_UI_GLOBAL_POT_29) && BMC_MAX_GLOBAL_POTS == 29 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_31) && defined(BMC_DEVICE_UI_GLOBAL_POT_30) && BMC_MAX_GLOBAL_POTS == 30 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_32) && defined(BMC_DEVICE_UI_GLOBAL_POT_31) && BMC_MAX_GLOBAL_POTS == 31 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_33) && defined(BMC_DEVICE_UI_GLOBAL_POT_32) && BMC_MAX_GLOBAL_POTS == 32 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_34) && defined(BMC_DEVICE_UI_GLOBAL_POT_33) && BMC_MAX_GLOBAL_POTS == 33 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_35) && defined(BMC_DEVICE_UI_GLOBAL_POT_34) && BMC_MAX_GLOBAL_POTS == 34 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_36) && defined(BMC_DEVICE_UI_GLOBAL_POT_35) && BMC_MAX_GLOBAL_POTS == 35 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_37) && defined(BMC_DEVICE_UI_GLOBAL_POT_36) && BMC_MAX_GLOBAL_POTS == 36 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_38) && defined(BMC_DEVICE_UI_GLOBAL_POT_37) && BMC_MAX_GLOBAL_POTS == 37 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_39) && defined(BMC_DEVICE_UI_GLOBAL_POT_38) && BMC_MAX_GLOBAL_POTS == 38 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_40) && defined(BMC_DEVICE_UI_GLOBAL_POT_39) && BMC_MAX_GLOBAL_POTS == 39 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_41) && defined(BMC_DEVICE_UI_GLOBAL_POT_40) && BMC_MAX_GLOBAL_POTS == 40 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_42) && defined(BMC_DEVICE_UI_GLOBAL_POT_41) && BMC_MAX_GLOBAL_POTS == 41 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_43) && defined(BMC_DEVICE_UI_GLOBAL_POT_42) && BMC_MAX_GLOBAL_POTS == 42 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_44) && defined(BMC_DEVICE_UI_GLOBAL_POT_43) && BMC_MAX_GLOBAL_POTS == 43 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_45) && defined(BMC_DEVICE_UI_GLOBAL_POT_44) && BMC_MAX_GLOBAL_POTS == 44 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_46) && defined(BMC_DEVICE_UI_GLOBAL_POT_45) && BMC_MAX_GLOBAL_POTS == 45 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_47) && defined(BMC_DEVICE_UI_GLOBAL_POT_46) && BMC_MAX_GLOBAL_POTS == 46 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_48) && defined(BMC_DEVICE_UI_GLOBAL_POT_47) && BMC_MAX_GLOBAL_POTS == 47 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_49) && defined(BMC_DEVICE_UI_GLOBAL_POT_48) && BMC_MAX_GLOBAL_POTS == 48 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_50) && defined(BMC_DEVICE_UI_GLOBAL_POT_49) && BMC_MAX_GLOBAL_POTS == 49 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_51) && defined(BMC_DEVICE_UI_GLOBAL_POT_50) && BMC_MAX_GLOBAL_POTS == 50 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_52) && defined(BMC_DEVICE_UI_GLOBAL_POT_51) && BMC_MAX_GLOBAL_POTS == 51 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_53) && defined(BMC_DEVICE_UI_GLOBAL_POT_52) && BMC_MAX_GLOBAL_POTS == 52 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_54) && defined(BMC_DEVICE_UI_GLOBAL_POT_53) && BMC_MAX_GLOBAL_POTS == 53 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_55) && defined(BMC_DEVICE_UI_GLOBAL_POT_54) && BMC_MAX_GLOBAL_POTS == 54 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_56) && defined(BMC_DEVICE_UI_GLOBAL_POT_55) && BMC_MAX_GLOBAL_POTS == 55 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_57) && defined(BMC_DEVICE_UI_GLOBAL_POT_56) && BMC_MAX_GLOBAL_POTS == 56 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_58) && defined(BMC_DEVICE_UI_GLOBAL_POT_57) && BMC_MAX_GLOBAL_POTS == 57 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_59) && defined(BMC_DEVICE_UI_GLOBAL_POT_58) && BMC_MAX_GLOBAL_POTS == 58 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_60) && defined(BMC_DEVICE_UI_GLOBAL_POT_59) && BMC_MAX_GLOBAL_POTS == 59 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_61) && defined(BMC_DEVICE_UI_GLOBAL_POT_60) && BMC_MAX_GLOBAL_POTS == 60 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_62) && defined(BMC_DEVICE_UI_GLOBAL_POT_61) && BMC_MAX_GLOBAL_POTS == 61 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_63) && defined(BMC_DEVICE_UI_GLOBAL_POT_62) && BMC_MAX_GLOBAL_POTS == 62 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_64) && defined(BMC_DEVICE_UI_GLOBAL_POT_63) && BMC_MAX_GLOBAL_POTS == 63 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 64
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_65) && defined(BMC_DEVICE_UI_GLOBAL_POT_64) && BMC_MAX_GLOBAL_POTS == 64 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 65
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_66) && defined(BMC_DEVICE_UI_GLOBAL_POT_65) && BMC_MAX_GLOBAL_POTS == 65 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 66
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_67) && defined(BMC_DEVICE_UI_GLOBAL_POT_66) && BMC_MAX_GLOBAL_POTS == 66 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 67
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_68) && defined(BMC_DEVICE_UI_GLOBAL_POT_67) && BMC_MAX_GLOBAL_POTS == 67 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 68
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_69) && defined(BMC_DEVICE_UI_GLOBAL_POT_68) && BMC_MAX_GLOBAL_POTS == 68 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 69
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_70) && defined(BMC_DEVICE_UI_GLOBAL_POT_69) && BMC_MAX_GLOBAL_POTS == 69 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 70
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_71) && defined(BMC_DEVICE_UI_GLOBAL_POT_70) && BMC_MAX_GLOBAL_POTS == 70 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 71
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_72) && defined(BMC_DEVICE_UI_GLOBAL_POT_71) && BMC_MAX_GLOBAL_POTS == 71 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 72
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_73) && defined(BMC_DEVICE_UI_GLOBAL_POT_72) && BMC_MAX_GLOBAL_POTS == 72 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 73
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_74) && defined(BMC_DEVICE_UI_GLOBAL_POT_73) && BMC_MAX_GLOBAL_POTS == 73 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 74
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_75) && defined(BMC_DEVICE_UI_GLOBAL_POT_74) && BMC_MAX_GLOBAL_POTS == 74 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 75
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_76) && defined(BMC_DEVICE_UI_GLOBAL_POT_75) && BMC_MAX_GLOBAL_POTS == 75 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 76
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_77) && defined(BMC_DEVICE_UI_GLOBAL_POT_76) && BMC_MAX_GLOBAL_POTS == 76 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 77
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_78) && defined(BMC_DEVICE_UI_GLOBAL_POT_77) && BMC_MAX_GLOBAL_POTS == 77 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 78
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_79) && defined(BMC_DEVICE_UI_GLOBAL_POT_78) && BMC_MAX_GLOBAL_POTS == 78 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 79
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_80) && defined(BMC_DEVICE_UI_GLOBAL_POT_79) && BMC_MAX_GLOBAL_POTS == 79 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 80
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_81) && defined(BMC_DEVICE_UI_GLOBAL_POT_80) && BMC_MAX_GLOBAL_POTS == 80 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 81
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_82) && defined(BMC_DEVICE_UI_GLOBAL_POT_81) && BMC_MAX_GLOBAL_POTS == 81 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 82
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_83) && defined(BMC_DEVICE_UI_GLOBAL_POT_82) && BMC_MAX_GLOBAL_POTS == 82 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 83
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_84) && defined(BMC_DEVICE_UI_GLOBAL_POT_83) && BMC_MAX_GLOBAL_POTS == 83 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 84
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_85) && defined(BMC_DEVICE_UI_GLOBAL_POT_84) && BMC_MAX_GLOBAL_POTS == 84 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 85
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_86) && defined(BMC_DEVICE_UI_GLOBAL_POT_85) && BMC_MAX_GLOBAL_POTS == 85 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 86
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_87) && defined(BMC_DEVICE_UI_GLOBAL_POT_86) && BMC_MAX_GLOBAL_POTS == 86 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 87
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_88) && defined(BMC_DEVICE_UI_GLOBAL_POT_87) && BMC_MAX_GLOBAL_POTS == 87 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 88
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_89) && defined(BMC_DEVICE_UI_GLOBAL_POT_88) && BMC_MAX_GLOBAL_POTS == 88 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 89
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_90) && defined(BMC_DEVICE_UI_GLOBAL_POT_89) && BMC_MAX_GLOBAL_POTS == 89 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 90
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_91) && defined(BMC_DEVICE_UI_GLOBAL_POT_90) && BMC_MAX_GLOBAL_POTS == 90 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 91
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_92) && defined(BMC_DEVICE_UI_GLOBAL_POT_91) && BMC_MAX_GLOBAL_POTS == 91 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 92
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_93) && defined(BMC_DEVICE_UI_GLOBAL_POT_92) && BMC_MAX_GLOBAL_POTS == 92 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 93
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_94) && defined(BMC_DEVICE_UI_GLOBAL_POT_93) && BMC_MAX_GLOBAL_POTS == 93 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 94
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_95) && defined(BMC_DEVICE_UI_GLOBAL_POT_94) && BMC_MAX_GLOBAL_POTS == 94 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 95
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_96) && defined(BMC_DEVICE_UI_GLOBAL_POT_95) && BMC_MAX_GLOBAL_POTS == 95 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 96
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_97) && defined(BMC_DEVICE_UI_GLOBAL_POT_96) && BMC_MAX_GLOBAL_POTS == 96 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 97
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_98) && defined(BMC_DEVICE_UI_GLOBAL_POT_97) && BMC_MAX_GLOBAL_POTS == 97 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 98
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_99) && defined(BMC_DEVICE_UI_GLOBAL_POT_98) && BMC_MAX_GLOBAL_POTS == 98 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 99
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_100) && defined(BMC_DEVICE_UI_GLOBAL_POT_99) && BMC_MAX_GLOBAL_POTS == 99 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 100
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_101) && defined(BMC_DEVICE_UI_GLOBAL_POT_100) && BMC_MAX_GLOBAL_POTS == 100 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 101
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_102) && defined(BMC_DEVICE_UI_GLOBAL_POT_101) && BMC_MAX_GLOBAL_POTS == 101 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 102
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_103) && defined(BMC_DEVICE_UI_GLOBAL_POT_102) && BMC_MAX_GLOBAL_POTS == 102 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 103
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_104) && defined(BMC_DEVICE_UI_GLOBAL_POT_103) && BMC_MAX_GLOBAL_POTS == 103 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 104
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_105) && defined(BMC_DEVICE_UI_GLOBAL_POT_104) && BMC_MAX_GLOBAL_POTS == 104 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 105
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_106) && defined(BMC_DEVICE_UI_GLOBAL_POT_105) && BMC_MAX_GLOBAL_POTS == 105 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 106
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_107) && defined(BMC_DEVICE_UI_GLOBAL_POT_106) && BMC_MAX_GLOBAL_POTS == 106 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 107
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_108) && defined(BMC_DEVICE_UI_GLOBAL_POT_107) && BMC_MAX_GLOBAL_POTS == 107 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 108
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_109) && defined(BMC_DEVICE_UI_GLOBAL_POT_108) && BMC_MAX_GLOBAL_POTS == 108 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 109
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_110) && defined(BMC_DEVICE_UI_GLOBAL_POT_109) && BMC_MAX_GLOBAL_POTS == 109 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 110
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_111) && defined(BMC_DEVICE_UI_GLOBAL_POT_110) && BMC_MAX_GLOBAL_POTS == 110 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 111
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_112) && defined(BMC_DEVICE_UI_GLOBAL_POT_111) && BMC_MAX_GLOBAL_POTS == 111 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 112
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_113) && defined(BMC_DEVICE_UI_GLOBAL_POT_112) && BMC_MAX_GLOBAL_POTS == 112 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 113
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_114) && defined(BMC_DEVICE_UI_GLOBAL_POT_113) && BMC_MAX_GLOBAL_POTS == 113 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 114
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_115) && defined(BMC_DEVICE_UI_GLOBAL_POT_114) && BMC_MAX_GLOBAL_POTS == 114 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 115
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_116) && defined(BMC_DEVICE_UI_GLOBAL_POT_115) && BMC_MAX_GLOBAL_POTS == 115 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 116
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_117) && defined(BMC_DEVICE_UI_GLOBAL_POT_116) && BMC_MAX_GLOBAL_POTS == 116 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 117
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_118) && defined(BMC_DEVICE_UI_GLOBAL_POT_117) && BMC_MAX_GLOBAL_POTS == 117 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 118
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_119) && defined(BMC_DEVICE_UI_GLOBAL_POT_118) && BMC_MAX_GLOBAL_POTS == 118 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 119
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_120) && defined(BMC_DEVICE_UI_GLOBAL_POT_119) && BMC_MAX_GLOBAL_POTS == 119 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 120
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_121) && defined(BMC_DEVICE_UI_GLOBAL_POT_120) && BMC_MAX_GLOBAL_POTS == 120 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 121
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_122) && defined(BMC_DEVICE_UI_GLOBAL_POT_121) && BMC_MAX_GLOBAL_POTS == 121 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 122
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_123) && defined(BMC_DEVICE_UI_GLOBAL_POT_122) && BMC_MAX_GLOBAL_POTS == 122 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 123
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_124) && defined(BMC_DEVICE_UI_GLOBAL_POT_123) && BMC_MAX_GLOBAL_POTS == 123 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 124
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_125) && defined(BMC_DEVICE_UI_GLOBAL_POT_124) && BMC_MAX_GLOBAL_POTS == 124 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 125
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_126) && defined(BMC_DEVICE_UI_GLOBAL_POT_125) && BMC_MAX_GLOBAL_POTS == 125 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 126
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_127) && defined(BMC_DEVICE_UI_GLOBAL_POT_126) && BMC_MAX_GLOBAL_POTS == 126 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 127
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_POT_128) && defined(BMC_DEVICE_UI_GLOBAL_POT_127) && BMC_MAX_GLOBAL_POTS == 127 
  #ifdef BMC_MAX_GLOBAL_POTS
    #undef BMC_MAX_GLOBAL_POTS
  #endif

  #define BMC_MAX_GLOBAL_POTS 128
#endif

// *******************************************
// *** GLOBAL_POTS end
// *******************************************

// *******************************************
// *** ENCODERS start
// *******************************************

#ifdef BMC_MAX_ENCODERS
  #undef BMC_MAX_ENCODERS
#endif

#define BMC_MAX_ENCODERS 0

#if defined(BMC_DEVICE_UI_ENCODER_1) && BMC_MAX_ENCODERS == 0 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 1
#endif

#if defined(BMC_DEVICE_UI_ENCODER_2) && defined(BMC_DEVICE_UI_ENCODER_1) && BMC_MAX_ENCODERS == 1 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 2
#endif

#if defined(BMC_DEVICE_UI_ENCODER_3) && defined(BMC_DEVICE_UI_ENCODER_2) && BMC_MAX_ENCODERS == 2 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 3
#endif

#if defined(BMC_DEVICE_UI_ENCODER_4) && defined(BMC_DEVICE_UI_ENCODER_3) && BMC_MAX_ENCODERS == 3 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 4
#endif

#if defined(BMC_DEVICE_UI_ENCODER_5) && defined(BMC_DEVICE_UI_ENCODER_4) && BMC_MAX_ENCODERS == 4 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 5
#endif

#if defined(BMC_DEVICE_UI_ENCODER_6) && defined(BMC_DEVICE_UI_ENCODER_5) && BMC_MAX_ENCODERS == 5 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 6
#endif

#if defined(BMC_DEVICE_UI_ENCODER_7) && defined(BMC_DEVICE_UI_ENCODER_6) && BMC_MAX_ENCODERS == 6 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 7
#endif

#if defined(BMC_DEVICE_UI_ENCODER_8) && defined(BMC_DEVICE_UI_ENCODER_7) && BMC_MAX_ENCODERS == 7 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 8
#endif

#if defined(BMC_DEVICE_UI_ENCODER_9) && defined(BMC_DEVICE_UI_ENCODER_8) && BMC_MAX_ENCODERS == 8 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 9
#endif

#if defined(BMC_DEVICE_UI_ENCODER_10) && defined(BMC_DEVICE_UI_ENCODER_9) && BMC_MAX_ENCODERS == 9 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 10
#endif

#if defined(BMC_DEVICE_UI_ENCODER_11) && defined(BMC_DEVICE_UI_ENCODER_10) && BMC_MAX_ENCODERS == 10 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 11
#endif

#if defined(BMC_DEVICE_UI_ENCODER_12) && defined(BMC_DEVICE_UI_ENCODER_11) && BMC_MAX_ENCODERS == 11 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 12
#endif

#if defined(BMC_DEVICE_UI_ENCODER_13) && defined(BMC_DEVICE_UI_ENCODER_12) && BMC_MAX_ENCODERS == 12 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 13
#endif

#if defined(BMC_DEVICE_UI_ENCODER_14) && defined(BMC_DEVICE_UI_ENCODER_13) && BMC_MAX_ENCODERS == 13 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 14
#endif

#if defined(BMC_DEVICE_UI_ENCODER_15) && defined(BMC_DEVICE_UI_ENCODER_14) && BMC_MAX_ENCODERS == 14 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 15
#endif

#if defined(BMC_DEVICE_UI_ENCODER_16) && defined(BMC_DEVICE_UI_ENCODER_15) && BMC_MAX_ENCODERS == 15 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 16
#endif

#if defined(BMC_DEVICE_UI_ENCODER_17) && defined(BMC_DEVICE_UI_ENCODER_16) && BMC_MAX_ENCODERS == 16 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 17
#endif

#if defined(BMC_DEVICE_UI_ENCODER_18) && defined(BMC_DEVICE_UI_ENCODER_17) && BMC_MAX_ENCODERS == 17 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 18
#endif

#if defined(BMC_DEVICE_UI_ENCODER_19) && defined(BMC_DEVICE_UI_ENCODER_18) && BMC_MAX_ENCODERS == 18 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 19
#endif

#if defined(BMC_DEVICE_UI_ENCODER_20) && defined(BMC_DEVICE_UI_ENCODER_19) && BMC_MAX_ENCODERS == 19 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 20
#endif

#if defined(BMC_DEVICE_UI_ENCODER_21) && defined(BMC_DEVICE_UI_ENCODER_20) && BMC_MAX_ENCODERS == 20 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 21
#endif

#if defined(BMC_DEVICE_UI_ENCODER_22) && defined(BMC_DEVICE_UI_ENCODER_21) && BMC_MAX_ENCODERS == 21 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 22
#endif

#if defined(BMC_DEVICE_UI_ENCODER_23) && defined(BMC_DEVICE_UI_ENCODER_22) && BMC_MAX_ENCODERS == 22 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 23
#endif

#if defined(BMC_DEVICE_UI_ENCODER_24) && defined(BMC_DEVICE_UI_ENCODER_23) && BMC_MAX_ENCODERS == 23 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 24
#endif

#if defined(BMC_DEVICE_UI_ENCODER_25) && defined(BMC_DEVICE_UI_ENCODER_24) && BMC_MAX_ENCODERS == 24 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 25
#endif

#if defined(BMC_DEVICE_UI_ENCODER_26) && defined(BMC_DEVICE_UI_ENCODER_25) && BMC_MAX_ENCODERS == 25 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 26
#endif

#if defined(BMC_DEVICE_UI_ENCODER_27) && defined(BMC_DEVICE_UI_ENCODER_26) && BMC_MAX_ENCODERS == 26 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 27
#endif

#if defined(BMC_DEVICE_UI_ENCODER_28) && defined(BMC_DEVICE_UI_ENCODER_27) && BMC_MAX_ENCODERS == 27 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 28
#endif

#if defined(BMC_DEVICE_UI_ENCODER_29) && defined(BMC_DEVICE_UI_ENCODER_28) && BMC_MAX_ENCODERS == 28 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 29
#endif

#if defined(BMC_DEVICE_UI_ENCODER_30) && defined(BMC_DEVICE_UI_ENCODER_29) && BMC_MAX_ENCODERS == 29 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 30
#endif

#if defined(BMC_DEVICE_UI_ENCODER_31) && defined(BMC_DEVICE_UI_ENCODER_30) && BMC_MAX_ENCODERS == 30 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 31
#endif

#if defined(BMC_DEVICE_UI_ENCODER_32) && defined(BMC_DEVICE_UI_ENCODER_31) && BMC_MAX_ENCODERS == 31 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 32
#endif

#if defined(BMC_DEVICE_UI_ENCODER_33) && defined(BMC_DEVICE_UI_ENCODER_32) && BMC_MAX_ENCODERS == 32 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 33
#endif

#if defined(BMC_DEVICE_UI_ENCODER_34) && defined(BMC_DEVICE_UI_ENCODER_33) && BMC_MAX_ENCODERS == 33 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 34
#endif

#if defined(BMC_DEVICE_UI_ENCODER_35) && defined(BMC_DEVICE_UI_ENCODER_34) && BMC_MAX_ENCODERS == 34 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 35
#endif

#if defined(BMC_DEVICE_UI_ENCODER_36) && defined(BMC_DEVICE_UI_ENCODER_35) && BMC_MAX_ENCODERS == 35 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 36
#endif

#if defined(BMC_DEVICE_UI_ENCODER_37) && defined(BMC_DEVICE_UI_ENCODER_36) && BMC_MAX_ENCODERS == 36 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 37
#endif

#if defined(BMC_DEVICE_UI_ENCODER_38) && defined(BMC_DEVICE_UI_ENCODER_37) && BMC_MAX_ENCODERS == 37 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 38
#endif

#if defined(BMC_DEVICE_UI_ENCODER_39) && defined(BMC_DEVICE_UI_ENCODER_38) && BMC_MAX_ENCODERS == 38 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 39
#endif

#if defined(BMC_DEVICE_UI_ENCODER_40) && defined(BMC_DEVICE_UI_ENCODER_39) && BMC_MAX_ENCODERS == 39 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 40
#endif

#if defined(BMC_DEVICE_UI_ENCODER_41) && defined(BMC_DEVICE_UI_ENCODER_40) && BMC_MAX_ENCODERS == 40 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 41
#endif

#if defined(BMC_DEVICE_UI_ENCODER_42) && defined(BMC_DEVICE_UI_ENCODER_41) && BMC_MAX_ENCODERS == 41 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 42
#endif

#if defined(BMC_DEVICE_UI_ENCODER_43) && defined(BMC_DEVICE_UI_ENCODER_42) && BMC_MAX_ENCODERS == 42 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 43
#endif

#if defined(BMC_DEVICE_UI_ENCODER_44) && defined(BMC_DEVICE_UI_ENCODER_43) && BMC_MAX_ENCODERS == 43 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 44
#endif

#if defined(BMC_DEVICE_UI_ENCODER_45) && defined(BMC_DEVICE_UI_ENCODER_44) && BMC_MAX_ENCODERS == 44 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 45
#endif

#if defined(BMC_DEVICE_UI_ENCODER_46) && defined(BMC_DEVICE_UI_ENCODER_45) && BMC_MAX_ENCODERS == 45 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 46
#endif

#if defined(BMC_DEVICE_UI_ENCODER_47) && defined(BMC_DEVICE_UI_ENCODER_46) && BMC_MAX_ENCODERS == 46 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 47
#endif

#if defined(BMC_DEVICE_UI_ENCODER_48) && defined(BMC_DEVICE_UI_ENCODER_47) && BMC_MAX_ENCODERS == 47 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 48
#endif

#if defined(BMC_DEVICE_UI_ENCODER_49) && defined(BMC_DEVICE_UI_ENCODER_48) && BMC_MAX_ENCODERS == 48 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 49
#endif

#if defined(BMC_DEVICE_UI_ENCODER_50) && defined(BMC_DEVICE_UI_ENCODER_49) && BMC_MAX_ENCODERS == 49 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 50
#endif

#if defined(BMC_DEVICE_UI_ENCODER_51) && defined(BMC_DEVICE_UI_ENCODER_50) && BMC_MAX_ENCODERS == 50 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 51
#endif

#if defined(BMC_DEVICE_UI_ENCODER_52) && defined(BMC_DEVICE_UI_ENCODER_51) && BMC_MAX_ENCODERS == 51 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 52
#endif

#if defined(BMC_DEVICE_UI_ENCODER_53) && defined(BMC_DEVICE_UI_ENCODER_52) && BMC_MAX_ENCODERS == 52 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 53
#endif

#if defined(BMC_DEVICE_UI_ENCODER_54) && defined(BMC_DEVICE_UI_ENCODER_53) && BMC_MAX_ENCODERS == 53 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 54
#endif

#if defined(BMC_DEVICE_UI_ENCODER_55) && defined(BMC_DEVICE_UI_ENCODER_54) && BMC_MAX_ENCODERS == 54 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 55
#endif

#if defined(BMC_DEVICE_UI_ENCODER_56) && defined(BMC_DEVICE_UI_ENCODER_55) && BMC_MAX_ENCODERS == 55 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 56
#endif

#if defined(BMC_DEVICE_UI_ENCODER_57) && defined(BMC_DEVICE_UI_ENCODER_56) && BMC_MAX_ENCODERS == 56 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 57
#endif

#if defined(BMC_DEVICE_UI_ENCODER_58) && defined(BMC_DEVICE_UI_ENCODER_57) && BMC_MAX_ENCODERS == 57 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 58
#endif

#if defined(BMC_DEVICE_UI_ENCODER_59) && defined(BMC_DEVICE_UI_ENCODER_58) && BMC_MAX_ENCODERS == 58 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 59
#endif

#if defined(BMC_DEVICE_UI_ENCODER_60) && defined(BMC_DEVICE_UI_ENCODER_59) && BMC_MAX_ENCODERS == 59 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 60
#endif

#if defined(BMC_DEVICE_UI_ENCODER_61) && defined(BMC_DEVICE_UI_ENCODER_60) && BMC_MAX_ENCODERS == 60 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 61
#endif

#if defined(BMC_DEVICE_UI_ENCODER_62) && defined(BMC_DEVICE_UI_ENCODER_61) && BMC_MAX_ENCODERS == 61 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 62
#endif

#if defined(BMC_DEVICE_UI_ENCODER_63) && defined(BMC_DEVICE_UI_ENCODER_62) && BMC_MAX_ENCODERS == 62 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 63
#endif

#if defined(BMC_DEVICE_UI_ENCODER_64) && defined(BMC_DEVICE_UI_ENCODER_63) && BMC_MAX_ENCODERS == 63 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 64
#endif

#if defined(BMC_DEVICE_UI_ENCODER_65) && defined(BMC_DEVICE_UI_ENCODER_64) && BMC_MAX_ENCODERS == 64 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 65
#endif

#if defined(BMC_DEVICE_UI_ENCODER_66) && defined(BMC_DEVICE_UI_ENCODER_65) && BMC_MAX_ENCODERS == 65 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 66
#endif

#if defined(BMC_DEVICE_UI_ENCODER_67) && defined(BMC_DEVICE_UI_ENCODER_66) && BMC_MAX_ENCODERS == 66 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 67
#endif

#if defined(BMC_DEVICE_UI_ENCODER_68) && defined(BMC_DEVICE_UI_ENCODER_67) && BMC_MAX_ENCODERS == 67 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 68
#endif

#if defined(BMC_DEVICE_UI_ENCODER_69) && defined(BMC_DEVICE_UI_ENCODER_68) && BMC_MAX_ENCODERS == 68 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 69
#endif

#if defined(BMC_DEVICE_UI_ENCODER_70) && defined(BMC_DEVICE_UI_ENCODER_69) && BMC_MAX_ENCODERS == 69 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 70
#endif

#if defined(BMC_DEVICE_UI_ENCODER_71) && defined(BMC_DEVICE_UI_ENCODER_70) && BMC_MAX_ENCODERS == 70 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 71
#endif

#if defined(BMC_DEVICE_UI_ENCODER_72) && defined(BMC_DEVICE_UI_ENCODER_71) && BMC_MAX_ENCODERS == 71 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 72
#endif

#if defined(BMC_DEVICE_UI_ENCODER_73) && defined(BMC_DEVICE_UI_ENCODER_72) && BMC_MAX_ENCODERS == 72 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 73
#endif

#if defined(BMC_DEVICE_UI_ENCODER_74) && defined(BMC_DEVICE_UI_ENCODER_73) && BMC_MAX_ENCODERS == 73 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 74
#endif

#if defined(BMC_DEVICE_UI_ENCODER_75) && defined(BMC_DEVICE_UI_ENCODER_74) && BMC_MAX_ENCODERS == 74 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 75
#endif

#if defined(BMC_DEVICE_UI_ENCODER_76) && defined(BMC_DEVICE_UI_ENCODER_75) && BMC_MAX_ENCODERS == 75 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 76
#endif

#if defined(BMC_DEVICE_UI_ENCODER_77) && defined(BMC_DEVICE_UI_ENCODER_76) && BMC_MAX_ENCODERS == 76 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 77
#endif

#if defined(BMC_DEVICE_UI_ENCODER_78) && defined(BMC_DEVICE_UI_ENCODER_77) && BMC_MAX_ENCODERS == 77 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 78
#endif

#if defined(BMC_DEVICE_UI_ENCODER_79) && defined(BMC_DEVICE_UI_ENCODER_78) && BMC_MAX_ENCODERS == 78 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 79
#endif

#if defined(BMC_DEVICE_UI_ENCODER_80) && defined(BMC_DEVICE_UI_ENCODER_79) && BMC_MAX_ENCODERS == 79 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 80
#endif

#if defined(BMC_DEVICE_UI_ENCODER_81) && defined(BMC_DEVICE_UI_ENCODER_80) && BMC_MAX_ENCODERS == 80 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 81
#endif

#if defined(BMC_DEVICE_UI_ENCODER_82) && defined(BMC_DEVICE_UI_ENCODER_81) && BMC_MAX_ENCODERS == 81 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 82
#endif

#if defined(BMC_DEVICE_UI_ENCODER_83) && defined(BMC_DEVICE_UI_ENCODER_82) && BMC_MAX_ENCODERS == 82 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 83
#endif

#if defined(BMC_DEVICE_UI_ENCODER_84) && defined(BMC_DEVICE_UI_ENCODER_83) && BMC_MAX_ENCODERS == 83 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 84
#endif

#if defined(BMC_DEVICE_UI_ENCODER_85) && defined(BMC_DEVICE_UI_ENCODER_84) && BMC_MAX_ENCODERS == 84 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 85
#endif

#if defined(BMC_DEVICE_UI_ENCODER_86) && defined(BMC_DEVICE_UI_ENCODER_85) && BMC_MAX_ENCODERS == 85 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 86
#endif

#if defined(BMC_DEVICE_UI_ENCODER_87) && defined(BMC_DEVICE_UI_ENCODER_86) && BMC_MAX_ENCODERS == 86 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 87
#endif

#if defined(BMC_DEVICE_UI_ENCODER_88) && defined(BMC_DEVICE_UI_ENCODER_87) && BMC_MAX_ENCODERS == 87 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 88
#endif

#if defined(BMC_DEVICE_UI_ENCODER_89) && defined(BMC_DEVICE_UI_ENCODER_88) && BMC_MAX_ENCODERS == 88 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 89
#endif

#if defined(BMC_DEVICE_UI_ENCODER_90) && defined(BMC_DEVICE_UI_ENCODER_89) && BMC_MAX_ENCODERS == 89 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 90
#endif

#if defined(BMC_DEVICE_UI_ENCODER_91) && defined(BMC_DEVICE_UI_ENCODER_90) && BMC_MAX_ENCODERS == 90 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 91
#endif

#if defined(BMC_DEVICE_UI_ENCODER_92) && defined(BMC_DEVICE_UI_ENCODER_91) && BMC_MAX_ENCODERS == 91 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 92
#endif

#if defined(BMC_DEVICE_UI_ENCODER_93) && defined(BMC_DEVICE_UI_ENCODER_92) && BMC_MAX_ENCODERS == 92 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 93
#endif

#if defined(BMC_DEVICE_UI_ENCODER_94) && defined(BMC_DEVICE_UI_ENCODER_93) && BMC_MAX_ENCODERS == 93 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 94
#endif

#if defined(BMC_DEVICE_UI_ENCODER_95) && defined(BMC_DEVICE_UI_ENCODER_94) && BMC_MAX_ENCODERS == 94 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 95
#endif

#if defined(BMC_DEVICE_UI_ENCODER_96) && defined(BMC_DEVICE_UI_ENCODER_95) && BMC_MAX_ENCODERS == 95 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 96
#endif

#if defined(BMC_DEVICE_UI_ENCODER_97) && defined(BMC_DEVICE_UI_ENCODER_96) && BMC_MAX_ENCODERS == 96 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 97
#endif

#if defined(BMC_DEVICE_UI_ENCODER_98) && defined(BMC_DEVICE_UI_ENCODER_97) && BMC_MAX_ENCODERS == 97 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 98
#endif

#if defined(BMC_DEVICE_UI_ENCODER_99) && defined(BMC_DEVICE_UI_ENCODER_98) && BMC_MAX_ENCODERS == 98 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 99
#endif

#if defined(BMC_DEVICE_UI_ENCODER_100) && defined(BMC_DEVICE_UI_ENCODER_99) && BMC_MAX_ENCODERS == 99 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 100
#endif

#if defined(BMC_DEVICE_UI_ENCODER_101) && defined(BMC_DEVICE_UI_ENCODER_100) && BMC_MAX_ENCODERS == 100 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 101
#endif

#if defined(BMC_DEVICE_UI_ENCODER_102) && defined(BMC_DEVICE_UI_ENCODER_101) && BMC_MAX_ENCODERS == 101 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 102
#endif

#if defined(BMC_DEVICE_UI_ENCODER_103) && defined(BMC_DEVICE_UI_ENCODER_102) && BMC_MAX_ENCODERS == 102 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 103
#endif

#if defined(BMC_DEVICE_UI_ENCODER_104) && defined(BMC_DEVICE_UI_ENCODER_103) && BMC_MAX_ENCODERS == 103 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 104
#endif

#if defined(BMC_DEVICE_UI_ENCODER_105) && defined(BMC_DEVICE_UI_ENCODER_104) && BMC_MAX_ENCODERS == 104 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 105
#endif

#if defined(BMC_DEVICE_UI_ENCODER_106) && defined(BMC_DEVICE_UI_ENCODER_105) && BMC_MAX_ENCODERS == 105 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 106
#endif

#if defined(BMC_DEVICE_UI_ENCODER_107) && defined(BMC_DEVICE_UI_ENCODER_106) && BMC_MAX_ENCODERS == 106 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 107
#endif

#if defined(BMC_DEVICE_UI_ENCODER_108) && defined(BMC_DEVICE_UI_ENCODER_107) && BMC_MAX_ENCODERS == 107 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 108
#endif

#if defined(BMC_DEVICE_UI_ENCODER_109) && defined(BMC_DEVICE_UI_ENCODER_108) && BMC_MAX_ENCODERS == 108 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 109
#endif

#if defined(BMC_DEVICE_UI_ENCODER_110) && defined(BMC_DEVICE_UI_ENCODER_109) && BMC_MAX_ENCODERS == 109 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 110
#endif

#if defined(BMC_DEVICE_UI_ENCODER_111) && defined(BMC_DEVICE_UI_ENCODER_110) && BMC_MAX_ENCODERS == 110 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 111
#endif

#if defined(BMC_DEVICE_UI_ENCODER_112) && defined(BMC_DEVICE_UI_ENCODER_111) && BMC_MAX_ENCODERS == 111 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 112
#endif

#if defined(BMC_DEVICE_UI_ENCODER_113) && defined(BMC_DEVICE_UI_ENCODER_112) && BMC_MAX_ENCODERS == 112 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 113
#endif

#if defined(BMC_DEVICE_UI_ENCODER_114) && defined(BMC_DEVICE_UI_ENCODER_113) && BMC_MAX_ENCODERS == 113 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 114
#endif

#if defined(BMC_DEVICE_UI_ENCODER_115) && defined(BMC_DEVICE_UI_ENCODER_114) && BMC_MAX_ENCODERS == 114 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 115
#endif

#if defined(BMC_DEVICE_UI_ENCODER_116) && defined(BMC_DEVICE_UI_ENCODER_115) && BMC_MAX_ENCODERS == 115 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 116
#endif

#if defined(BMC_DEVICE_UI_ENCODER_117) && defined(BMC_DEVICE_UI_ENCODER_116) && BMC_MAX_ENCODERS == 116 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 117
#endif

#if defined(BMC_DEVICE_UI_ENCODER_118) && defined(BMC_DEVICE_UI_ENCODER_117) && BMC_MAX_ENCODERS == 117 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 118
#endif

#if defined(BMC_DEVICE_UI_ENCODER_119) && defined(BMC_DEVICE_UI_ENCODER_118) && BMC_MAX_ENCODERS == 118 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 119
#endif

#if defined(BMC_DEVICE_UI_ENCODER_120) && defined(BMC_DEVICE_UI_ENCODER_119) && BMC_MAX_ENCODERS == 119 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 120
#endif

#if defined(BMC_DEVICE_UI_ENCODER_121) && defined(BMC_DEVICE_UI_ENCODER_120) && BMC_MAX_ENCODERS == 120 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 121
#endif

#if defined(BMC_DEVICE_UI_ENCODER_122) && defined(BMC_DEVICE_UI_ENCODER_121) && BMC_MAX_ENCODERS == 121 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 122
#endif

#if defined(BMC_DEVICE_UI_ENCODER_123) && defined(BMC_DEVICE_UI_ENCODER_122) && BMC_MAX_ENCODERS == 122 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 123
#endif

#if defined(BMC_DEVICE_UI_ENCODER_124) && defined(BMC_DEVICE_UI_ENCODER_123) && BMC_MAX_ENCODERS == 123 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 124
#endif

#if defined(BMC_DEVICE_UI_ENCODER_125) && defined(BMC_DEVICE_UI_ENCODER_124) && BMC_MAX_ENCODERS == 124 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 125
#endif

#if defined(BMC_DEVICE_UI_ENCODER_126) && defined(BMC_DEVICE_UI_ENCODER_125) && BMC_MAX_ENCODERS == 125 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 126
#endif

#if defined(BMC_DEVICE_UI_ENCODER_127) && defined(BMC_DEVICE_UI_ENCODER_126) && BMC_MAX_ENCODERS == 126 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 127
#endif

#if defined(BMC_DEVICE_UI_ENCODER_128) && defined(BMC_DEVICE_UI_ENCODER_127) && BMC_MAX_ENCODERS == 127 
  #ifdef BMC_MAX_ENCODERS
    #undef BMC_MAX_ENCODERS
  #endif

  #define BMC_MAX_ENCODERS 128
#endif

// *******************************************
// *** ENCODERS end
// *******************************************

// *******************************************
// *** GLOBAL_ENCODERS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_ENCODERS
  #undef BMC_MAX_GLOBAL_ENCODERS
#endif

#define BMC_MAX_GLOBAL_ENCODERS 0

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_1) && BMC_MAX_GLOBAL_ENCODERS == 0 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_2) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_1) && BMC_MAX_GLOBAL_ENCODERS == 1 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_3) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_2) && BMC_MAX_GLOBAL_ENCODERS == 2 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_4) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_3) && BMC_MAX_GLOBAL_ENCODERS == 3 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_5) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_4) && BMC_MAX_GLOBAL_ENCODERS == 4 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_6) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_5) && BMC_MAX_GLOBAL_ENCODERS == 5 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_7) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_6) && BMC_MAX_GLOBAL_ENCODERS == 6 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_8) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_7) && BMC_MAX_GLOBAL_ENCODERS == 7 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_9) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_8) && BMC_MAX_GLOBAL_ENCODERS == 8 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_10) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_9) && BMC_MAX_GLOBAL_ENCODERS == 9 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_11) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_10) && BMC_MAX_GLOBAL_ENCODERS == 10 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_12) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_11) && BMC_MAX_GLOBAL_ENCODERS == 11 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_13) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_12) && BMC_MAX_GLOBAL_ENCODERS == 12 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_14) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_13) && BMC_MAX_GLOBAL_ENCODERS == 13 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_15) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_14) && BMC_MAX_GLOBAL_ENCODERS == 14 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_16) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_15) && BMC_MAX_GLOBAL_ENCODERS == 15 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_17) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_16) && BMC_MAX_GLOBAL_ENCODERS == 16 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_18) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_17) && BMC_MAX_GLOBAL_ENCODERS == 17 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_19) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_18) && BMC_MAX_GLOBAL_ENCODERS == 18 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_20) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_19) && BMC_MAX_GLOBAL_ENCODERS == 19 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_21) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_20) && BMC_MAX_GLOBAL_ENCODERS == 20 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_22) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_21) && BMC_MAX_GLOBAL_ENCODERS == 21 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_23) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_22) && BMC_MAX_GLOBAL_ENCODERS == 22 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_24) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_23) && BMC_MAX_GLOBAL_ENCODERS == 23 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_25) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_24) && BMC_MAX_GLOBAL_ENCODERS == 24 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_26) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_25) && BMC_MAX_GLOBAL_ENCODERS == 25 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_27) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_26) && BMC_MAX_GLOBAL_ENCODERS == 26 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_28) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_27) && BMC_MAX_GLOBAL_ENCODERS == 27 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_29) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_28) && BMC_MAX_GLOBAL_ENCODERS == 28 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_30) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_29) && BMC_MAX_GLOBAL_ENCODERS == 29 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_31) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_30) && BMC_MAX_GLOBAL_ENCODERS == 30 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_32) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_31) && BMC_MAX_GLOBAL_ENCODERS == 31 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_33) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_32) && BMC_MAX_GLOBAL_ENCODERS == 32 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_34) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_33) && BMC_MAX_GLOBAL_ENCODERS == 33 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_35) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_34) && BMC_MAX_GLOBAL_ENCODERS == 34 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_36) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_35) && BMC_MAX_GLOBAL_ENCODERS == 35 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_37) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_36) && BMC_MAX_GLOBAL_ENCODERS == 36 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_38) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_37) && BMC_MAX_GLOBAL_ENCODERS == 37 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_39) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_38) && BMC_MAX_GLOBAL_ENCODERS == 38 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_40) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_39) && BMC_MAX_GLOBAL_ENCODERS == 39 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_41) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_40) && BMC_MAX_GLOBAL_ENCODERS == 40 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_42) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_41) && BMC_MAX_GLOBAL_ENCODERS == 41 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_43) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_42) && BMC_MAX_GLOBAL_ENCODERS == 42 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_44) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_43) && BMC_MAX_GLOBAL_ENCODERS == 43 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_45) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_44) && BMC_MAX_GLOBAL_ENCODERS == 44 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_46) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_45) && BMC_MAX_GLOBAL_ENCODERS == 45 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_47) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_46) && BMC_MAX_GLOBAL_ENCODERS == 46 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_48) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_47) && BMC_MAX_GLOBAL_ENCODERS == 47 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_49) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_48) && BMC_MAX_GLOBAL_ENCODERS == 48 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_50) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_49) && BMC_MAX_GLOBAL_ENCODERS == 49 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_51) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_50) && BMC_MAX_GLOBAL_ENCODERS == 50 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_52) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_51) && BMC_MAX_GLOBAL_ENCODERS == 51 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_53) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_52) && BMC_MAX_GLOBAL_ENCODERS == 52 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_54) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_53) && BMC_MAX_GLOBAL_ENCODERS == 53 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_55) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_54) && BMC_MAX_GLOBAL_ENCODERS == 54 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_56) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_55) && BMC_MAX_GLOBAL_ENCODERS == 55 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_57) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_56) && BMC_MAX_GLOBAL_ENCODERS == 56 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_58) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_57) && BMC_MAX_GLOBAL_ENCODERS == 57 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_59) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_58) && BMC_MAX_GLOBAL_ENCODERS == 58 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_60) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_59) && BMC_MAX_GLOBAL_ENCODERS == 59 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_61) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_60) && BMC_MAX_GLOBAL_ENCODERS == 60 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_62) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_61) && BMC_MAX_GLOBAL_ENCODERS == 61 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_63) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_62) && BMC_MAX_GLOBAL_ENCODERS == 62 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_64) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_63) && BMC_MAX_GLOBAL_ENCODERS == 63 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 64
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_65) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_64) && BMC_MAX_GLOBAL_ENCODERS == 64 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 65
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_66) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_65) && BMC_MAX_GLOBAL_ENCODERS == 65 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 66
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_67) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_66) && BMC_MAX_GLOBAL_ENCODERS == 66 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 67
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_68) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_67) && BMC_MAX_GLOBAL_ENCODERS == 67 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 68
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_69) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_68) && BMC_MAX_GLOBAL_ENCODERS == 68 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 69
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_70) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_69) && BMC_MAX_GLOBAL_ENCODERS == 69 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 70
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_71) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_70) && BMC_MAX_GLOBAL_ENCODERS == 70 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 71
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_72) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_71) && BMC_MAX_GLOBAL_ENCODERS == 71 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 72
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_73) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_72) && BMC_MAX_GLOBAL_ENCODERS == 72 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 73
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_74) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_73) && BMC_MAX_GLOBAL_ENCODERS == 73 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 74
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_75) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_74) && BMC_MAX_GLOBAL_ENCODERS == 74 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 75
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_76) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_75) && BMC_MAX_GLOBAL_ENCODERS == 75 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 76
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_77) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_76) && BMC_MAX_GLOBAL_ENCODERS == 76 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 77
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_78) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_77) && BMC_MAX_GLOBAL_ENCODERS == 77 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 78
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_79) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_78) && BMC_MAX_GLOBAL_ENCODERS == 78 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 79
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_80) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_79) && BMC_MAX_GLOBAL_ENCODERS == 79 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 80
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_81) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_80) && BMC_MAX_GLOBAL_ENCODERS == 80 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 81
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_82) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_81) && BMC_MAX_GLOBAL_ENCODERS == 81 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 82
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_83) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_82) && BMC_MAX_GLOBAL_ENCODERS == 82 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 83
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_84) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_83) && BMC_MAX_GLOBAL_ENCODERS == 83 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 84
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_85) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_84) && BMC_MAX_GLOBAL_ENCODERS == 84 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 85
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_86) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_85) && BMC_MAX_GLOBAL_ENCODERS == 85 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 86
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_87) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_86) && BMC_MAX_GLOBAL_ENCODERS == 86 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 87
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_88) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_87) && BMC_MAX_GLOBAL_ENCODERS == 87 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 88
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_89) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_88) && BMC_MAX_GLOBAL_ENCODERS == 88 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 89
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_90) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_89) && BMC_MAX_GLOBAL_ENCODERS == 89 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 90
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_91) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_90) && BMC_MAX_GLOBAL_ENCODERS == 90 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 91
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_92) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_91) && BMC_MAX_GLOBAL_ENCODERS == 91 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 92
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_93) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_92) && BMC_MAX_GLOBAL_ENCODERS == 92 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 93
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_94) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_93) && BMC_MAX_GLOBAL_ENCODERS == 93 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 94
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_95) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_94) && BMC_MAX_GLOBAL_ENCODERS == 94 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 95
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_96) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_95) && BMC_MAX_GLOBAL_ENCODERS == 95 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 96
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_97) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_96) && BMC_MAX_GLOBAL_ENCODERS == 96 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 97
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_98) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_97) && BMC_MAX_GLOBAL_ENCODERS == 97 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 98
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_99) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_98) && BMC_MAX_GLOBAL_ENCODERS == 98 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 99
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_100) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_99) && BMC_MAX_GLOBAL_ENCODERS == 99 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 100
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_101) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_100) && BMC_MAX_GLOBAL_ENCODERS == 100 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 101
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_102) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_101) && BMC_MAX_GLOBAL_ENCODERS == 101 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 102
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_103) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_102) && BMC_MAX_GLOBAL_ENCODERS == 102 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 103
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_104) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_103) && BMC_MAX_GLOBAL_ENCODERS == 103 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 104
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_105) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_104) && BMC_MAX_GLOBAL_ENCODERS == 104 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 105
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_106) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_105) && BMC_MAX_GLOBAL_ENCODERS == 105 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 106
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_107) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_106) && BMC_MAX_GLOBAL_ENCODERS == 106 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 107
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_108) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_107) && BMC_MAX_GLOBAL_ENCODERS == 107 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 108
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_109) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_108) && BMC_MAX_GLOBAL_ENCODERS == 108 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 109
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_110) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_109) && BMC_MAX_GLOBAL_ENCODERS == 109 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 110
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_111) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_110) && BMC_MAX_GLOBAL_ENCODERS == 110 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 111
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_112) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_111) && BMC_MAX_GLOBAL_ENCODERS == 111 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 112
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_113) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_112) && BMC_MAX_GLOBAL_ENCODERS == 112 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 113
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_114) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_113) && BMC_MAX_GLOBAL_ENCODERS == 113 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 114
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_115) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_114) && BMC_MAX_GLOBAL_ENCODERS == 114 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 115
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_116) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_115) && BMC_MAX_GLOBAL_ENCODERS == 115 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 116
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_117) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_116) && BMC_MAX_GLOBAL_ENCODERS == 116 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 117
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_118) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_117) && BMC_MAX_GLOBAL_ENCODERS == 117 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 118
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_119) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_118) && BMC_MAX_GLOBAL_ENCODERS == 118 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 119
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_120) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_119) && BMC_MAX_GLOBAL_ENCODERS == 119 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 120
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_121) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_120) && BMC_MAX_GLOBAL_ENCODERS == 120 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 121
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_122) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_121) && BMC_MAX_GLOBAL_ENCODERS == 121 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 122
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_123) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_122) && BMC_MAX_GLOBAL_ENCODERS == 122 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 123
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_124) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_123) && BMC_MAX_GLOBAL_ENCODERS == 123 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 124
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_125) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_124) && BMC_MAX_GLOBAL_ENCODERS == 124 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 125
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_126) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_125) && BMC_MAX_GLOBAL_ENCODERS == 125 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 126
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_127) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_126) && BMC_MAX_GLOBAL_ENCODERS == 126 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 127
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_ENCODER_128) && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_127) && BMC_MAX_GLOBAL_ENCODERS == 127 
  #ifdef BMC_MAX_GLOBAL_ENCODERS
    #undef BMC_MAX_GLOBAL_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_ENCODERS 128
#endif

// *******************************************
// *** GLOBAL_ENCODERS end
// *******************************************

// *******************************************
// *** PIXELS start
// *******************************************

#ifdef BMC_MAX_PIXELS
  #undef BMC_MAX_PIXELS
#endif

#define BMC_MAX_PIXELS 0

#if defined(BMC_DEVICE_UI_PIXEL_1) && BMC_MAX_PIXELS == 0 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 1
#endif

#if defined(BMC_DEVICE_UI_PIXEL_2) && defined(BMC_DEVICE_UI_PIXEL_1) && BMC_MAX_PIXELS == 1 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 2
#endif

#if defined(BMC_DEVICE_UI_PIXEL_3) && defined(BMC_DEVICE_UI_PIXEL_2) && BMC_MAX_PIXELS == 2 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 3
#endif

#if defined(BMC_DEVICE_UI_PIXEL_4) && defined(BMC_DEVICE_UI_PIXEL_3) && BMC_MAX_PIXELS == 3 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 4
#endif

#if defined(BMC_DEVICE_UI_PIXEL_5) && defined(BMC_DEVICE_UI_PIXEL_4) && BMC_MAX_PIXELS == 4 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 5
#endif

#if defined(BMC_DEVICE_UI_PIXEL_6) && defined(BMC_DEVICE_UI_PIXEL_5) && BMC_MAX_PIXELS == 5 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 6
#endif

#if defined(BMC_DEVICE_UI_PIXEL_7) && defined(BMC_DEVICE_UI_PIXEL_6) && BMC_MAX_PIXELS == 6 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 7
#endif

#if defined(BMC_DEVICE_UI_PIXEL_8) && defined(BMC_DEVICE_UI_PIXEL_7) && BMC_MAX_PIXELS == 7 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 8
#endif

#if defined(BMC_DEVICE_UI_PIXEL_9) && defined(BMC_DEVICE_UI_PIXEL_8) && BMC_MAX_PIXELS == 8 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 9
#endif

#if defined(BMC_DEVICE_UI_PIXEL_10) && defined(BMC_DEVICE_UI_PIXEL_9) && BMC_MAX_PIXELS == 9 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 10
#endif

#if defined(BMC_DEVICE_UI_PIXEL_11) && defined(BMC_DEVICE_UI_PIXEL_10) && BMC_MAX_PIXELS == 10 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 11
#endif

#if defined(BMC_DEVICE_UI_PIXEL_12) && defined(BMC_DEVICE_UI_PIXEL_11) && BMC_MAX_PIXELS == 11 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 12
#endif

#if defined(BMC_DEVICE_UI_PIXEL_13) && defined(BMC_DEVICE_UI_PIXEL_12) && BMC_MAX_PIXELS == 12 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 13
#endif

#if defined(BMC_DEVICE_UI_PIXEL_14) && defined(BMC_DEVICE_UI_PIXEL_13) && BMC_MAX_PIXELS == 13 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 14
#endif

#if defined(BMC_DEVICE_UI_PIXEL_15) && defined(BMC_DEVICE_UI_PIXEL_14) && BMC_MAX_PIXELS == 14 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 15
#endif

#if defined(BMC_DEVICE_UI_PIXEL_16) && defined(BMC_DEVICE_UI_PIXEL_15) && BMC_MAX_PIXELS == 15 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 16
#endif

#if defined(BMC_DEVICE_UI_PIXEL_17) && defined(BMC_DEVICE_UI_PIXEL_16) && BMC_MAX_PIXELS == 16 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 17
#endif

#if defined(BMC_DEVICE_UI_PIXEL_18) && defined(BMC_DEVICE_UI_PIXEL_17) && BMC_MAX_PIXELS == 17 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 18
#endif

#if defined(BMC_DEVICE_UI_PIXEL_19) && defined(BMC_DEVICE_UI_PIXEL_18) && BMC_MAX_PIXELS == 18 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 19
#endif

#if defined(BMC_DEVICE_UI_PIXEL_20) && defined(BMC_DEVICE_UI_PIXEL_19) && BMC_MAX_PIXELS == 19 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 20
#endif

#if defined(BMC_DEVICE_UI_PIXEL_21) && defined(BMC_DEVICE_UI_PIXEL_20) && BMC_MAX_PIXELS == 20 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 21
#endif

#if defined(BMC_DEVICE_UI_PIXEL_22) && defined(BMC_DEVICE_UI_PIXEL_21) && BMC_MAX_PIXELS == 21 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 22
#endif

#if defined(BMC_DEVICE_UI_PIXEL_23) && defined(BMC_DEVICE_UI_PIXEL_22) && BMC_MAX_PIXELS == 22 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 23
#endif

#if defined(BMC_DEVICE_UI_PIXEL_24) && defined(BMC_DEVICE_UI_PIXEL_23) && BMC_MAX_PIXELS == 23 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 24
#endif

#if defined(BMC_DEVICE_UI_PIXEL_25) && defined(BMC_DEVICE_UI_PIXEL_24) && BMC_MAX_PIXELS == 24 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 25
#endif

#if defined(BMC_DEVICE_UI_PIXEL_26) && defined(BMC_DEVICE_UI_PIXEL_25) && BMC_MAX_PIXELS == 25 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 26
#endif

#if defined(BMC_DEVICE_UI_PIXEL_27) && defined(BMC_DEVICE_UI_PIXEL_26) && BMC_MAX_PIXELS == 26 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 27
#endif

#if defined(BMC_DEVICE_UI_PIXEL_28) && defined(BMC_DEVICE_UI_PIXEL_27) && BMC_MAX_PIXELS == 27 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 28
#endif

#if defined(BMC_DEVICE_UI_PIXEL_29) && defined(BMC_DEVICE_UI_PIXEL_28) && BMC_MAX_PIXELS == 28 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 29
#endif

#if defined(BMC_DEVICE_UI_PIXEL_30) && defined(BMC_DEVICE_UI_PIXEL_29) && BMC_MAX_PIXELS == 29 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 30
#endif

#if defined(BMC_DEVICE_UI_PIXEL_31) && defined(BMC_DEVICE_UI_PIXEL_30) && BMC_MAX_PIXELS == 30 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 31
#endif

#if defined(BMC_DEVICE_UI_PIXEL_32) && defined(BMC_DEVICE_UI_PIXEL_31) && BMC_MAX_PIXELS == 31 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 32
#endif

#if defined(BMC_DEVICE_UI_PIXEL_33) && defined(BMC_DEVICE_UI_PIXEL_32) && BMC_MAX_PIXELS == 32 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 33
#endif

#if defined(BMC_DEVICE_UI_PIXEL_34) && defined(BMC_DEVICE_UI_PIXEL_33) && BMC_MAX_PIXELS == 33 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 34
#endif

#if defined(BMC_DEVICE_UI_PIXEL_35) && defined(BMC_DEVICE_UI_PIXEL_34) && BMC_MAX_PIXELS == 34 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 35
#endif

#if defined(BMC_DEVICE_UI_PIXEL_36) && defined(BMC_DEVICE_UI_PIXEL_35) && BMC_MAX_PIXELS == 35 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 36
#endif

#if defined(BMC_DEVICE_UI_PIXEL_37) && defined(BMC_DEVICE_UI_PIXEL_36) && BMC_MAX_PIXELS == 36 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 37
#endif

#if defined(BMC_DEVICE_UI_PIXEL_38) && defined(BMC_DEVICE_UI_PIXEL_37) && BMC_MAX_PIXELS == 37 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 38
#endif

#if defined(BMC_DEVICE_UI_PIXEL_39) && defined(BMC_DEVICE_UI_PIXEL_38) && BMC_MAX_PIXELS == 38 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 39
#endif

#if defined(BMC_DEVICE_UI_PIXEL_40) && defined(BMC_DEVICE_UI_PIXEL_39) && BMC_MAX_PIXELS == 39 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 40
#endif

#if defined(BMC_DEVICE_UI_PIXEL_41) && defined(BMC_DEVICE_UI_PIXEL_40) && BMC_MAX_PIXELS == 40 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 41
#endif

#if defined(BMC_DEVICE_UI_PIXEL_42) && defined(BMC_DEVICE_UI_PIXEL_41) && BMC_MAX_PIXELS == 41 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 42
#endif

#if defined(BMC_DEVICE_UI_PIXEL_43) && defined(BMC_DEVICE_UI_PIXEL_42) && BMC_MAX_PIXELS == 42 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 43
#endif

#if defined(BMC_DEVICE_UI_PIXEL_44) && defined(BMC_DEVICE_UI_PIXEL_43) && BMC_MAX_PIXELS == 43 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 44
#endif

#if defined(BMC_DEVICE_UI_PIXEL_45) && defined(BMC_DEVICE_UI_PIXEL_44) && BMC_MAX_PIXELS == 44 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 45
#endif

#if defined(BMC_DEVICE_UI_PIXEL_46) && defined(BMC_DEVICE_UI_PIXEL_45) && BMC_MAX_PIXELS == 45 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 46
#endif

#if defined(BMC_DEVICE_UI_PIXEL_47) && defined(BMC_DEVICE_UI_PIXEL_46) && BMC_MAX_PIXELS == 46 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 47
#endif

#if defined(BMC_DEVICE_UI_PIXEL_48) && defined(BMC_DEVICE_UI_PIXEL_47) && BMC_MAX_PIXELS == 47 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 48
#endif

#if defined(BMC_DEVICE_UI_PIXEL_49) && defined(BMC_DEVICE_UI_PIXEL_48) && BMC_MAX_PIXELS == 48 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 49
#endif

#if defined(BMC_DEVICE_UI_PIXEL_50) && defined(BMC_DEVICE_UI_PIXEL_49) && BMC_MAX_PIXELS == 49 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 50
#endif

#if defined(BMC_DEVICE_UI_PIXEL_51) && defined(BMC_DEVICE_UI_PIXEL_50) && BMC_MAX_PIXELS == 50 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 51
#endif

#if defined(BMC_DEVICE_UI_PIXEL_52) && defined(BMC_DEVICE_UI_PIXEL_51) && BMC_MAX_PIXELS == 51 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 52
#endif

#if defined(BMC_DEVICE_UI_PIXEL_53) && defined(BMC_DEVICE_UI_PIXEL_52) && BMC_MAX_PIXELS == 52 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 53
#endif

#if defined(BMC_DEVICE_UI_PIXEL_54) && defined(BMC_DEVICE_UI_PIXEL_53) && BMC_MAX_PIXELS == 53 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 54
#endif

#if defined(BMC_DEVICE_UI_PIXEL_55) && defined(BMC_DEVICE_UI_PIXEL_54) && BMC_MAX_PIXELS == 54 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 55
#endif

#if defined(BMC_DEVICE_UI_PIXEL_56) && defined(BMC_DEVICE_UI_PIXEL_55) && BMC_MAX_PIXELS == 55 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 56
#endif

#if defined(BMC_DEVICE_UI_PIXEL_57) && defined(BMC_DEVICE_UI_PIXEL_56) && BMC_MAX_PIXELS == 56 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 57
#endif

#if defined(BMC_DEVICE_UI_PIXEL_58) && defined(BMC_DEVICE_UI_PIXEL_57) && BMC_MAX_PIXELS == 57 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 58
#endif

#if defined(BMC_DEVICE_UI_PIXEL_59) && defined(BMC_DEVICE_UI_PIXEL_58) && BMC_MAX_PIXELS == 58 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 59
#endif

#if defined(BMC_DEVICE_UI_PIXEL_60) && defined(BMC_DEVICE_UI_PIXEL_59) && BMC_MAX_PIXELS == 59 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 60
#endif

#if defined(BMC_DEVICE_UI_PIXEL_61) && defined(BMC_DEVICE_UI_PIXEL_60) && BMC_MAX_PIXELS == 60 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 61
#endif

#if defined(BMC_DEVICE_UI_PIXEL_62) && defined(BMC_DEVICE_UI_PIXEL_61) && BMC_MAX_PIXELS == 61 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 62
#endif

#if defined(BMC_DEVICE_UI_PIXEL_63) && defined(BMC_DEVICE_UI_PIXEL_62) && BMC_MAX_PIXELS == 62 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 63
#endif

#if defined(BMC_DEVICE_UI_PIXEL_64) && defined(BMC_DEVICE_UI_PIXEL_63) && BMC_MAX_PIXELS == 63 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 64
#endif

#if defined(BMC_DEVICE_UI_PIXEL_65) && defined(BMC_DEVICE_UI_PIXEL_64) && BMC_MAX_PIXELS == 64 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 65
#endif

#if defined(BMC_DEVICE_UI_PIXEL_66) && defined(BMC_DEVICE_UI_PIXEL_65) && BMC_MAX_PIXELS == 65 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 66
#endif

#if defined(BMC_DEVICE_UI_PIXEL_67) && defined(BMC_DEVICE_UI_PIXEL_66) && BMC_MAX_PIXELS == 66 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 67
#endif

#if defined(BMC_DEVICE_UI_PIXEL_68) && defined(BMC_DEVICE_UI_PIXEL_67) && BMC_MAX_PIXELS == 67 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 68
#endif

#if defined(BMC_DEVICE_UI_PIXEL_69) && defined(BMC_DEVICE_UI_PIXEL_68) && BMC_MAX_PIXELS == 68 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 69
#endif

#if defined(BMC_DEVICE_UI_PIXEL_70) && defined(BMC_DEVICE_UI_PIXEL_69) && BMC_MAX_PIXELS == 69 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 70
#endif

#if defined(BMC_DEVICE_UI_PIXEL_71) && defined(BMC_DEVICE_UI_PIXEL_70) && BMC_MAX_PIXELS == 70 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 71
#endif

#if defined(BMC_DEVICE_UI_PIXEL_72) && defined(BMC_DEVICE_UI_PIXEL_71) && BMC_MAX_PIXELS == 71 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 72
#endif

#if defined(BMC_DEVICE_UI_PIXEL_73) && defined(BMC_DEVICE_UI_PIXEL_72) && BMC_MAX_PIXELS == 72 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 73
#endif

#if defined(BMC_DEVICE_UI_PIXEL_74) && defined(BMC_DEVICE_UI_PIXEL_73) && BMC_MAX_PIXELS == 73 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 74
#endif

#if defined(BMC_DEVICE_UI_PIXEL_75) && defined(BMC_DEVICE_UI_PIXEL_74) && BMC_MAX_PIXELS == 74 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 75
#endif

#if defined(BMC_DEVICE_UI_PIXEL_76) && defined(BMC_DEVICE_UI_PIXEL_75) && BMC_MAX_PIXELS == 75 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 76
#endif

#if defined(BMC_DEVICE_UI_PIXEL_77) && defined(BMC_DEVICE_UI_PIXEL_76) && BMC_MAX_PIXELS == 76 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 77
#endif

#if defined(BMC_DEVICE_UI_PIXEL_78) && defined(BMC_DEVICE_UI_PIXEL_77) && BMC_MAX_PIXELS == 77 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 78
#endif

#if defined(BMC_DEVICE_UI_PIXEL_79) && defined(BMC_DEVICE_UI_PIXEL_78) && BMC_MAX_PIXELS == 78 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 79
#endif

#if defined(BMC_DEVICE_UI_PIXEL_80) && defined(BMC_DEVICE_UI_PIXEL_79) && BMC_MAX_PIXELS == 79 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 80
#endif

#if defined(BMC_DEVICE_UI_PIXEL_81) && defined(BMC_DEVICE_UI_PIXEL_80) && BMC_MAX_PIXELS == 80 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 81
#endif

#if defined(BMC_DEVICE_UI_PIXEL_82) && defined(BMC_DEVICE_UI_PIXEL_81) && BMC_MAX_PIXELS == 81 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 82
#endif

#if defined(BMC_DEVICE_UI_PIXEL_83) && defined(BMC_DEVICE_UI_PIXEL_82) && BMC_MAX_PIXELS == 82 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 83
#endif

#if defined(BMC_DEVICE_UI_PIXEL_84) && defined(BMC_DEVICE_UI_PIXEL_83) && BMC_MAX_PIXELS == 83 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 84
#endif

#if defined(BMC_DEVICE_UI_PIXEL_85) && defined(BMC_DEVICE_UI_PIXEL_84) && BMC_MAX_PIXELS == 84 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 85
#endif

#if defined(BMC_DEVICE_UI_PIXEL_86) && defined(BMC_DEVICE_UI_PIXEL_85) && BMC_MAX_PIXELS == 85 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 86
#endif

#if defined(BMC_DEVICE_UI_PIXEL_87) && defined(BMC_DEVICE_UI_PIXEL_86) && BMC_MAX_PIXELS == 86 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 87
#endif

#if defined(BMC_DEVICE_UI_PIXEL_88) && defined(BMC_DEVICE_UI_PIXEL_87) && BMC_MAX_PIXELS == 87 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 88
#endif

#if defined(BMC_DEVICE_UI_PIXEL_89) && defined(BMC_DEVICE_UI_PIXEL_88) && BMC_MAX_PIXELS == 88 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 89
#endif

#if defined(BMC_DEVICE_UI_PIXEL_90) && defined(BMC_DEVICE_UI_PIXEL_89) && BMC_MAX_PIXELS == 89 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 90
#endif

#if defined(BMC_DEVICE_UI_PIXEL_91) && defined(BMC_DEVICE_UI_PIXEL_90) && BMC_MAX_PIXELS == 90 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 91
#endif

#if defined(BMC_DEVICE_UI_PIXEL_92) && defined(BMC_DEVICE_UI_PIXEL_91) && BMC_MAX_PIXELS == 91 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 92
#endif

#if defined(BMC_DEVICE_UI_PIXEL_93) && defined(BMC_DEVICE_UI_PIXEL_92) && BMC_MAX_PIXELS == 92 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 93
#endif

#if defined(BMC_DEVICE_UI_PIXEL_94) && defined(BMC_DEVICE_UI_PIXEL_93) && BMC_MAX_PIXELS == 93 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 94
#endif

#if defined(BMC_DEVICE_UI_PIXEL_95) && defined(BMC_DEVICE_UI_PIXEL_94) && BMC_MAX_PIXELS == 94 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 95
#endif

#if defined(BMC_DEVICE_UI_PIXEL_96) && defined(BMC_DEVICE_UI_PIXEL_95) && BMC_MAX_PIXELS == 95 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 96
#endif

#if defined(BMC_DEVICE_UI_PIXEL_97) && defined(BMC_DEVICE_UI_PIXEL_96) && BMC_MAX_PIXELS == 96 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 97
#endif

#if defined(BMC_DEVICE_UI_PIXEL_98) && defined(BMC_DEVICE_UI_PIXEL_97) && BMC_MAX_PIXELS == 97 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 98
#endif

#if defined(BMC_DEVICE_UI_PIXEL_99) && defined(BMC_DEVICE_UI_PIXEL_98) && BMC_MAX_PIXELS == 98 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 99
#endif

#if defined(BMC_DEVICE_UI_PIXEL_100) && defined(BMC_DEVICE_UI_PIXEL_99) && BMC_MAX_PIXELS == 99 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 100
#endif

#if defined(BMC_DEVICE_UI_PIXEL_101) && defined(BMC_DEVICE_UI_PIXEL_100) && BMC_MAX_PIXELS == 100 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 101
#endif

#if defined(BMC_DEVICE_UI_PIXEL_102) && defined(BMC_DEVICE_UI_PIXEL_101) && BMC_MAX_PIXELS == 101 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 102
#endif

#if defined(BMC_DEVICE_UI_PIXEL_103) && defined(BMC_DEVICE_UI_PIXEL_102) && BMC_MAX_PIXELS == 102 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 103
#endif

#if defined(BMC_DEVICE_UI_PIXEL_104) && defined(BMC_DEVICE_UI_PIXEL_103) && BMC_MAX_PIXELS == 103 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 104
#endif

#if defined(BMC_DEVICE_UI_PIXEL_105) && defined(BMC_DEVICE_UI_PIXEL_104) && BMC_MAX_PIXELS == 104 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 105
#endif

#if defined(BMC_DEVICE_UI_PIXEL_106) && defined(BMC_DEVICE_UI_PIXEL_105) && BMC_MAX_PIXELS == 105 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 106
#endif

#if defined(BMC_DEVICE_UI_PIXEL_107) && defined(BMC_DEVICE_UI_PIXEL_106) && BMC_MAX_PIXELS == 106 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 107
#endif

#if defined(BMC_DEVICE_UI_PIXEL_108) && defined(BMC_DEVICE_UI_PIXEL_107) && BMC_MAX_PIXELS == 107 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 108
#endif

#if defined(BMC_DEVICE_UI_PIXEL_109) && defined(BMC_DEVICE_UI_PIXEL_108) && BMC_MAX_PIXELS == 108 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 109
#endif

#if defined(BMC_DEVICE_UI_PIXEL_110) && defined(BMC_DEVICE_UI_PIXEL_109) && BMC_MAX_PIXELS == 109 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 110
#endif

#if defined(BMC_DEVICE_UI_PIXEL_111) && defined(BMC_DEVICE_UI_PIXEL_110) && BMC_MAX_PIXELS == 110 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 111
#endif

#if defined(BMC_DEVICE_UI_PIXEL_112) && defined(BMC_DEVICE_UI_PIXEL_111) && BMC_MAX_PIXELS == 111 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 112
#endif

#if defined(BMC_DEVICE_UI_PIXEL_113) && defined(BMC_DEVICE_UI_PIXEL_112) && BMC_MAX_PIXELS == 112 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 113
#endif

#if defined(BMC_DEVICE_UI_PIXEL_114) && defined(BMC_DEVICE_UI_PIXEL_113) && BMC_MAX_PIXELS == 113 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 114
#endif

#if defined(BMC_DEVICE_UI_PIXEL_115) && defined(BMC_DEVICE_UI_PIXEL_114) && BMC_MAX_PIXELS == 114 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 115
#endif

#if defined(BMC_DEVICE_UI_PIXEL_116) && defined(BMC_DEVICE_UI_PIXEL_115) && BMC_MAX_PIXELS == 115 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 116
#endif

#if defined(BMC_DEVICE_UI_PIXEL_117) && defined(BMC_DEVICE_UI_PIXEL_116) && BMC_MAX_PIXELS == 116 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 117
#endif

#if defined(BMC_DEVICE_UI_PIXEL_118) && defined(BMC_DEVICE_UI_PIXEL_117) && BMC_MAX_PIXELS == 117 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 118
#endif

#if defined(BMC_DEVICE_UI_PIXEL_119) && defined(BMC_DEVICE_UI_PIXEL_118) && BMC_MAX_PIXELS == 118 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 119
#endif

#if defined(BMC_DEVICE_UI_PIXEL_120) && defined(BMC_DEVICE_UI_PIXEL_119) && BMC_MAX_PIXELS == 119 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 120
#endif

#if defined(BMC_DEVICE_UI_PIXEL_121) && defined(BMC_DEVICE_UI_PIXEL_120) && BMC_MAX_PIXELS == 120 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 121
#endif

#if defined(BMC_DEVICE_UI_PIXEL_122) && defined(BMC_DEVICE_UI_PIXEL_121) && BMC_MAX_PIXELS == 121 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 122
#endif

#if defined(BMC_DEVICE_UI_PIXEL_123) && defined(BMC_DEVICE_UI_PIXEL_122) && BMC_MAX_PIXELS == 122 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 123
#endif

#if defined(BMC_DEVICE_UI_PIXEL_124) && defined(BMC_DEVICE_UI_PIXEL_123) && BMC_MAX_PIXELS == 123 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 124
#endif

#if defined(BMC_DEVICE_UI_PIXEL_125) && defined(BMC_DEVICE_UI_PIXEL_124) && BMC_MAX_PIXELS == 124 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 125
#endif

#if defined(BMC_DEVICE_UI_PIXEL_126) && defined(BMC_DEVICE_UI_PIXEL_125) && BMC_MAX_PIXELS == 125 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 126
#endif

#if defined(BMC_DEVICE_UI_PIXEL_127) && defined(BMC_DEVICE_UI_PIXEL_126) && BMC_MAX_PIXELS == 126 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 127
#endif

#if defined(BMC_DEVICE_UI_PIXEL_128) && defined(BMC_DEVICE_UI_PIXEL_127) && BMC_MAX_PIXELS == 127 
  #ifdef BMC_MAX_PIXELS
    #undef BMC_MAX_PIXELS
  #endif

  #define BMC_MAX_PIXELS 128
#endif

// *******************************************
// *** PIXELS end
// *******************************************

// *******************************************
// *** GLOBAL_PIXELS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_PIXELS
  #undef BMC_MAX_GLOBAL_PIXELS
#endif

#define BMC_MAX_GLOBAL_PIXELS 0

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_1) && BMC_MAX_GLOBAL_PIXELS == 0 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_2) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_1) && BMC_MAX_GLOBAL_PIXELS == 1 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_3) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_2) && BMC_MAX_GLOBAL_PIXELS == 2 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_4) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_3) && BMC_MAX_GLOBAL_PIXELS == 3 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_5) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_4) && BMC_MAX_GLOBAL_PIXELS == 4 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_6) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_5) && BMC_MAX_GLOBAL_PIXELS == 5 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_7) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_6) && BMC_MAX_GLOBAL_PIXELS == 6 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_8) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_7) && BMC_MAX_GLOBAL_PIXELS == 7 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_9) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_8) && BMC_MAX_GLOBAL_PIXELS == 8 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_10) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_9) && BMC_MAX_GLOBAL_PIXELS == 9 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_11) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_10) && BMC_MAX_GLOBAL_PIXELS == 10 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_12) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_11) && BMC_MAX_GLOBAL_PIXELS == 11 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_13) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_12) && BMC_MAX_GLOBAL_PIXELS == 12 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_14) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_13) && BMC_MAX_GLOBAL_PIXELS == 13 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_15) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_14) && BMC_MAX_GLOBAL_PIXELS == 14 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_16) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_15) && BMC_MAX_GLOBAL_PIXELS == 15 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_17) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_16) && BMC_MAX_GLOBAL_PIXELS == 16 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_18) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_17) && BMC_MAX_GLOBAL_PIXELS == 17 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_19) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_18) && BMC_MAX_GLOBAL_PIXELS == 18 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_20) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_19) && BMC_MAX_GLOBAL_PIXELS == 19 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_21) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_20) && BMC_MAX_GLOBAL_PIXELS == 20 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_22) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_21) && BMC_MAX_GLOBAL_PIXELS == 21 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_23) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_22) && BMC_MAX_GLOBAL_PIXELS == 22 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_24) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_23) && BMC_MAX_GLOBAL_PIXELS == 23 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_25) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_24) && BMC_MAX_GLOBAL_PIXELS == 24 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_26) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_25) && BMC_MAX_GLOBAL_PIXELS == 25 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_27) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_26) && BMC_MAX_GLOBAL_PIXELS == 26 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_28) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_27) && BMC_MAX_GLOBAL_PIXELS == 27 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_29) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_28) && BMC_MAX_GLOBAL_PIXELS == 28 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_30) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_29) && BMC_MAX_GLOBAL_PIXELS == 29 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_31) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_30) && BMC_MAX_GLOBAL_PIXELS == 30 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_32) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_31) && BMC_MAX_GLOBAL_PIXELS == 31 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_33) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_32) && BMC_MAX_GLOBAL_PIXELS == 32 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_34) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_33) && BMC_MAX_GLOBAL_PIXELS == 33 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_35) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_34) && BMC_MAX_GLOBAL_PIXELS == 34 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_36) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_35) && BMC_MAX_GLOBAL_PIXELS == 35 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_37) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_36) && BMC_MAX_GLOBAL_PIXELS == 36 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_38) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_37) && BMC_MAX_GLOBAL_PIXELS == 37 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_39) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_38) && BMC_MAX_GLOBAL_PIXELS == 38 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_40) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_39) && BMC_MAX_GLOBAL_PIXELS == 39 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_41) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_40) && BMC_MAX_GLOBAL_PIXELS == 40 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_42) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_41) && BMC_MAX_GLOBAL_PIXELS == 41 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_43) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_42) && BMC_MAX_GLOBAL_PIXELS == 42 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_44) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_43) && BMC_MAX_GLOBAL_PIXELS == 43 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_45) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_44) && BMC_MAX_GLOBAL_PIXELS == 44 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_46) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_45) && BMC_MAX_GLOBAL_PIXELS == 45 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_47) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_46) && BMC_MAX_GLOBAL_PIXELS == 46 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_48) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_47) && BMC_MAX_GLOBAL_PIXELS == 47 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_49) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_48) && BMC_MAX_GLOBAL_PIXELS == 48 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_50) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_49) && BMC_MAX_GLOBAL_PIXELS == 49 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_51) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_50) && BMC_MAX_GLOBAL_PIXELS == 50 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_52) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_51) && BMC_MAX_GLOBAL_PIXELS == 51 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_53) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_52) && BMC_MAX_GLOBAL_PIXELS == 52 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_54) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_53) && BMC_MAX_GLOBAL_PIXELS == 53 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_55) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_54) && BMC_MAX_GLOBAL_PIXELS == 54 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_56) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_55) && BMC_MAX_GLOBAL_PIXELS == 55 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_57) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_56) && BMC_MAX_GLOBAL_PIXELS == 56 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_58) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_57) && BMC_MAX_GLOBAL_PIXELS == 57 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_59) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_58) && BMC_MAX_GLOBAL_PIXELS == 58 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_60) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_59) && BMC_MAX_GLOBAL_PIXELS == 59 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_61) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_60) && BMC_MAX_GLOBAL_PIXELS == 60 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_62) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_61) && BMC_MAX_GLOBAL_PIXELS == 61 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_63) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_62) && BMC_MAX_GLOBAL_PIXELS == 62 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_64) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_63) && BMC_MAX_GLOBAL_PIXELS == 63 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 64
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_65) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_64) && BMC_MAX_GLOBAL_PIXELS == 64 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 65
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_66) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_65) && BMC_MAX_GLOBAL_PIXELS == 65 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 66
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_67) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_66) && BMC_MAX_GLOBAL_PIXELS == 66 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 67
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_68) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_67) && BMC_MAX_GLOBAL_PIXELS == 67 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 68
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_69) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_68) && BMC_MAX_GLOBAL_PIXELS == 68 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 69
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_70) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_69) && BMC_MAX_GLOBAL_PIXELS == 69 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 70
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_71) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_70) && BMC_MAX_GLOBAL_PIXELS == 70 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 71
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_72) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_71) && BMC_MAX_GLOBAL_PIXELS == 71 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 72
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_73) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_72) && BMC_MAX_GLOBAL_PIXELS == 72 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 73
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_74) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_73) && BMC_MAX_GLOBAL_PIXELS == 73 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 74
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_75) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_74) && BMC_MAX_GLOBAL_PIXELS == 74 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 75
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_76) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_75) && BMC_MAX_GLOBAL_PIXELS == 75 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 76
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_77) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_76) && BMC_MAX_GLOBAL_PIXELS == 76 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 77
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_78) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_77) && BMC_MAX_GLOBAL_PIXELS == 77 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 78
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_79) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_78) && BMC_MAX_GLOBAL_PIXELS == 78 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 79
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_80) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_79) && BMC_MAX_GLOBAL_PIXELS == 79 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 80
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_81) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_80) && BMC_MAX_GLOBAL_PIXELS == 80 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 81
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_82) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_81) && BMC_MAX_GLOBAL_PIXELS == 81 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 82
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_83) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_82) && BMC_MAX_GLOBAL_PIXELS == 82 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 83
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_84) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_83) && BMC_MAX_GLOBAL_PIXELS == 83 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 84
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_85) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_84) && BMC_MAX_GLOBAL_PIXELS == 84 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 85
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_86) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_85) && BMC_MAX_GLOBAL_PIXELS == 85 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 86
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_87) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_86) && BMC_MAX_GLOBAL_PIXELS == 86 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 87
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_88) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_87) && BMC_MAX_GLOBAL_PIXELS == 87 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 88
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_89) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_88) && BMC_MAX_GLOBAL_PIXELS == 88 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 89
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_90) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_89) && BMC_MAX_GLOBAL_PIXELS == 89 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 90
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_91) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_90) && BMC_MAX_GLOBAL_PIXELS == 90 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 91
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_92) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_91) && BMC_MAX_GLOBAL_PIXELS == 91 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 92
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_93) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_92) && BMC_MAX_GLOBAL_PIXELS == 92 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 93
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_94) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_93) && BMC_MAX_GLOBAL_PIXELS == 93 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 94
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_95) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_94) && BMC_MAX_GLOBAL_PIXELS == 94 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 95
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_96) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_95) && BMC_MAX_GLOBAL_PIXELS == 95 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 96
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_97) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_96) && BMC_MAX_GLOBAL_PIXELS == 96 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 97
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_98) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_97) && BMC_MAX_GLOBAL_PIXELS == 97 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 98
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_99) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_98) && BMC_MAX_GLOBAL_PIXELS == 98 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 99
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_100) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_99) && BMC_MAX_GLOBAL_PIXELS == 99 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 100
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_101) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_100) && BMC_MAX_GLOBAL_PIXELS == 100 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 101
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_102) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_101) && BMC_MAX_GLOBAL_PIXELS == 101 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 102
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_103) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_102) && BMC_MAX_GLOBAL_PIXELS == 102 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 103
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_104) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_103) && BMC_MAX_GLOBAL_PIXELS == 103 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 104
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_105) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_104) && BMC_MAX_GLOBAL_PIXELS == 104 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 105
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_106) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_105) && BMC_MAX_GLOBAL_PIXELS == 105 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 106
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_107) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_106) && BMC_MAX_GLOBAL_PIXELS == 106 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 107
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_108) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_107) && BMC_MAX_GLOBAL_PIXELS == 107 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 108
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_109) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_108) && BMC_MAX_GLOBAL_PIXELS == 108 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 109
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_110) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_109) && BMC_MAX_GLOBAL_PIXELS == 109 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 110
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_111) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_110) && BMC_MAX_GLOBAL_PIXELS == 110 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 111
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_112) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_111) && BMC_MAX_GLOBAL_PIXELS == 111 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 112
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_113) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_112) && BMC_MAX_GLOBAL_PIXELS == 112 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 113
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_114) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_113) && BMC_MAX_GLOBAL_PIXELS == 113 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 114
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_115) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_114) && BMC_MAX_GLOBAL_PIXELS == 114 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 115
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_116) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_115) && BMC_MAX_GLOBAL_PIXELS == 115 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 116
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_117) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_116) && BMC_MAX_GLOBAL_PIXELS == 116 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 117
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_118) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_117) && BMC_MAX_GLOBAL_PIXELS == 117 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 118
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_119) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_118) && BMC_MAX_GLOBAL_PIXELS == 118 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 119
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_120) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_119) && BMC_MAX_GLOBAL_PIXELS == 119 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 120
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_121) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_120) && BMC_MAX_GLOBAL_PIXELS == 120 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 121
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_122) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_121) && BMC_MAX_GLOBAL_PIXELS == 121 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 122
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_123) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_122) && BMC_MAX_GLOBAL_PIXELS == 122 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 123
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_124) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_123) && BMC_MAX_GLOBAL_PIXELS == 123 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 124
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_125) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_124) && BMC_MAX_GLOBAL_PIXELS == 124 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 125
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_126) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_125) && BMC_MAX_GLOBAL_PIXELS == 125 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 126
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_127) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_126) && BMC_MAX_GLOBAL_PIXELS == 126 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 127
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_PIXEL_128) && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_127) && BMC_MAX_GLOBAL_PIXELS == 127 
  #ifdef BMC_MAX_GLOBAL_PIXELS
    #undef BMC_MAX_GLOBAL_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_PIXELS 128
#endif

// *******************************************
// *** GLOBAL_PIXELS end
// *******************************************

// *******************************************
// *** RGB_PIXELS start
// *******************************************

#ifdef BMC_MAX_RGB_PIXELS
  #undef BMC_MAX_RGB_PIXELS
#endif

#define BMC_MAX_RGB_PIXELS 0

#if defined(BMC_DEVICE_UI_RGB_PIXEL_1) && BMC_MAX_RGB_PIXELS == 0 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 1
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_2) && defined(BMC_DEVICE_UI_RGB_PIXEL_1) && BMC_MAX_RGB_PIXELS == 1 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 2
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_3) && defined(BMC_DEVICE_UI_RGB_PIXEL_2) && BMC_MAX_RGB_PIXELS == 2 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 3
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_4) && defined(BMC_DEVICE_UI_RGB_PIXEL_3) && BMC_MAX_RGB_PIXELS == 3 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 4
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_5) && defined(BMC_DEVICE_UI_RGB_PIXEL_4) && BMC_MAX_RGB_PIXELS == 4 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 5
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_6) && defined(BMC_DEVICE_UI_RGB_PIXEL_5) && BMC_MAX_RGB_PIXELS == 5 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 6
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_7) && defined(BMC_DEVICE_UI_RGB_PIXEL_6) && BMC_MAX_RGB_PIXELS == 6 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 7
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_8) && defined(BMC_DEVICE_UI_RGB_PIXEL_7) && BMC_MAX_RGB_PIXELS == 7 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 8
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_9) && defined(BMC_DEVICE_UI_RGB_PIXEL_8) && BMC_MAX_RGB_PIXELS == 8 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 9
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_10) && defined(BMC_DEVICE_UI_RGB_PIXEL_9) && BMC_MAX_RGB_PIXELS == 9 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 10
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_11) && defined(BMC_DEVICE_UI_RGB_PIXEL_10) && BMC_MAX_RGB_PIXELS == 10 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 11
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_12) && defined(BMC_DEVICE_UI_RGB_PIXEL_11) && BMC_MAX_RGB_PIXELS == 11 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 12
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_13) && defined(BMC_DEVICE_UI_RGB_PIXEL_12) && BMC_MAX_RGB_PIXELS == 12 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 13
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_14) && defined(BMC_DEVICE_UI_RGB_PIXEL_13) && BMC_MAX_RGB_PIXELS == 13 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 14
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_15) && defined(BMC_DEVICE_UI_RGB_PIXEL_14) && BMC_MAX_RGB_PIXELS == 14 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 15
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_16) && defined(BMC_DEVICE_UI_RGB_PIXEL_15) && BMC_MAX_RGB_PIXELS == 15 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 16
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_17) && defined(BMC_DEVICE_UI_RGB_PIXEL_16) && BMC_MAX_RGB_PIXELS == 16 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 17
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_18) && defined(BMC_DEVICE_UI_RGB_PIXEL_17) && BMC_MAX_RGB_PIXELS == 17 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 18
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_19) && defined(BMC_DEVICE_UI_RGB_PIXEL_18) && BMC_MAX_RGB_PIXELS == 18 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 19
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_20) && defined(BMC_DEVICE_UI_RGB_PIXEL_19) && BMC_MAX_RGB_PIXELS == 19 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 20
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_21) && defined(BMC_DEVICE_UI_RGB_PIXEL_20) && BMC_MAX_RGB_PIXELS == 20 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 21
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_22) && defined(BMC_DEVICE_UI_RGB_PIXEL_21) && BMC_MAX_RGB_PIXELS == 21 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 22
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_23) && defined(BMC_DEVICE_UI_RGB_PIXEL_22) && BMC_MAX_RGB_PIXELS == 22 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 23
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_24) && defined(BMC_DEVICE_UI_RGB_PIXEL_23) && BMC_MAX_RGB_PIXELS == 23 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 24
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_25) && defined(BMC_DEVICE_UI_RGB_PIXEL_24) && BMC_MAX_RGB_PIXELS == 24 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 25
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_26) && defined(BMC_DEVICE_UI_RGB_PIXEL_25) && BMC_MAX_RGB_PIXELS == 25 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 26
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_27) && defined(BMC_DEVICE_UI_RGB_PIXEL_26) && BMC_MAX_RGB_PIXELS == 26 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 27
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_28) && defined(BMC_DEVICE_UI_RGB_PIXEL_27) && BMC_MAX_RGB_PIXELS == 27 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 28
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_29) && defined(BMC_DEVICE_UI_RGB_PIXEL_28) && BMC_MAX_RGB_PIXELS == 28 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 29
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_30) && defined(BMC_DEVICE_UI_RGB_PIXEL_29) && BMC_MAX_RGB_PIXELS == 29 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 30
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_31) && defined(BMC_DEVICE_UI_RGB_PIXEL_30) && BMC_MAX_RGB_PIXELS == 30 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 31
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_32) && defined(BMC_DEVICE_UI_RGB_PIXEL_31) && BMC_MAX_RGB_PIXELS == 31 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 32
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_33) && defined(BMC_DEVICE_UI_RGB_PIXEL_32) && BMC_MAX_RGB_PIXELS == 32 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 33
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_34) && defined(BMC_DEVICE_UI_RGB_PIXEL_33) && BMC_MAX_RGB_PIXELS == 33 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 34
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_35) && defined(BMC_DEVICE_UI_RGB_PIXEL_34) && BMC_MAX_RGB_PIXELS == 34 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 35
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_36) && defined(BMC_DEVICE_UI_RGB_PIXEL_35) && BMC_MAX_RGB_PIXELS == 35 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 36
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_37) && defined(BMC_DEVICE_UI_RGB_PIXEL_36) && BMC_MAX_RGB_PIXELS == 36 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 37
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_38) && defined(BMC_DEVICE_UI_RGB_PIXEL_37) && BMC_MAX_RGB_PIXELS == 37 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 38
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_39) && defined(BMC_DEVICE_UI_RGB_PIXEL_38) && BMC_MAX_RGB_PIXELS == 38 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 39
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_40) && defined(BMC_DEVICE_UI_RGB_PIXEL_39) && BMC_MAX_RGB_PIXELS == 39 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 40
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_41) && defined(BMC_DEVICE_UI_RGB_PIXEL_40) && BMC_MAX_RGB_PIXELS == 40 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 41
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_42) && defined(BMC_DEVICE_UI_RGB_PIXEL_41) && BMC_MAX_RGB_PIXELS == 41 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 42
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_43) && defined(BMC_DEVICE_UI_RGB_PIXEL_42) && BMC_MAX_RGB_PIXELS == 42 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 43
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_44) && defined(BMC_DEVICE_UI_RGB_PIXEL_43) && BMC_MAX_RGB_PIXELS == 43 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 44
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_45) && defined(BMC_DEVICE_UI_RGB_PIXEL_44) && BMC_MAX_RGB_PIXELS == 44 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 45
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_46) && defined(BMC_DEVICE_UI_RGB_PIXEL_45) && BMC_MAX_RGB_PIXELS == 45 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 46
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_47) && defined(BMC_DEVICE_UI_RGB_PIXEL_46) && BMC_MAX_RGB_PIXELS == 46 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 47
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_48) && defined(BMC_DEVICE_UI_RGB_PIXEL_47) && BMC_MAX_RGB_PIXELS == 47 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 48
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_49) && defined(BMC_DEVICE_UI_RGB_PIXEL_48) && BMC_MAX_RGB_PIXELS == 48 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 49
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_50) && defined(BMC_DEVICE_UI_RGB_PIXEL_49) && BMC_MAX_RGB_PIXELS == 49 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 50
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_51) && defined(BMC_DEVICE_UI_RGB_PIXEL_50) && BMC_MAX_RGB_PIXELS == 50 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 51
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_52) && defined(BMC_DEVICE_UI_RGB_PIXEL_51) && BMC_MAX_RGB_PIXELS == 51 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 52
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_53) && defined(BMC_DEVICE_UI_RGB_PIXEL_52) && BMC_MAX_RGB_PIXELS == 52 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 53
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_54) && defined(BMC_DEVICE_UI_RGB_PIXEL_53) && BMC_MAX_RGB_PIXELS == 53 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 54
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_55) && defined(BMC_DEVICE_UI_RGB_PIXEL_54) && BMC_MAX_RGB_PIXELS == 54 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 55
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_56) && defined(BMC_DEVICE_UI_RGB_PIXEL_55) && BMC_MAX_RGB_PIXELS == 55 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 56
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_57) && defined(BMC_DEVICE_UI_RGB_PIXEL_56) && BMC_MAX_RGB_PIXELS == 56 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 57
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_58) && defined(BMC_DEVICE_UI_RGB_PIXEL_57) && BMC_MAX_RGB_PIXELS == 57 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 58
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_59) && defined(BMC_DEVICE_UI_RGB_PIXEL_58) && BMC_MAX_RGB_PIXELS == 58 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 59
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_60) && defined(BMC_DEVICE_UI_RGB_PIXEL_59) && BMC_MAX_RGB_PIXELS == 59 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 60
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_61) && defined(BMC_DEVICE_UI_RGB_PIXEL_60) && BMC_MAX_RGB_PIXELS == 60 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 61
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_62) && defined(BMC_DEVICE_UI_RGB_PIXEL_61) && BMC_MAX_RGB_PIXELS == 61 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 62
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_63) && defined(BMC_DEVICE_UI_RGB_PIXEL_62) && BMC_MAX_RGB_PIXELS == 62 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 63
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_64) && defined(BMC_DEVICE_UI_RGB_PIXEL_63) && BMC_MAX_RGB_PIXELS == 63 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 64
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_65) && defined(BMC_DEVICE_UI_RGB_PIXEL_64) && BMC_MAX_RGB_PIXELS == 64 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 65
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_66) && defined(BMC_DEVICE_UI_RGB_PIXEL_65) && BMC_MAX_RGB_PIXELS == 65 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 66
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_67) && defined(BMC_DEVICE_UI_RGB_PIXEL_66) && BMC_MAX_RGB_PIXELS == 66 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 67
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_68) && defined(BMC_DEVICE_UI_RGB_PIXEL_67) && BMC_MAX_RGB_PIXELS == 67 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 68
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_69) && defined(BMC_DEVICE_UI_RGB_PIXEL_68) && BMC_MAX_RGB_PIXELS == 68 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 69
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_70) && defined(BMC_DEVICE_UI_RGB_PIXEL_69) && BMC_MAX_RGB_PIXELS == 69 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 70
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_71) && defined(BMC_DEVICE_UI_RGB_PIXEL_70) && BMC_MAX_RGB_PIXELS == 70 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 71
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_72) && defined(BMC_DEVICE_UI_RGB_PIXEL_71) && BMC_MAX_RGB_PIXELS == 71 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 72
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_73) && defined(BMC_DEVICE_UI_RGB_PIXEL_72) && BMC_MAX_RGB_PIXELS == 72 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 73
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_74) && defined(BMC_DEVICE_UI_RGB_PIXEL_73) && BMC_MAX_RGB_PIXELS == 73 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 74
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_75) && defined(BMC_DEVICE_UI_RGB_PIXEL_74) && BMC_MAX_RGB_PIXELS == 74 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 75
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_76) && defined(BMC_DEVICE_UI_RGB_PIXEL_75) && BMC_MAX_RGB_PIXELS == 75 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 76
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_77) && defined(BMC_DEVICE_UI_RGB_PIXEL_76) && BMC_MAX_RGB_PIXELS == 76 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 77
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_78) && defined(BMC_DEVICE_UI_RGB_PIXEL_77) && BMC_MAX_RGB_PIXELS == 77 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 78
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_79) && defined(BMC_DEVICE_UI_RGB_PIXEL_78) && BMC_MAX_RGB_PIXELS == 78 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 79
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_80) && defined(BMC_DEVICE_UI_RGB_PIXEL_79) && BMC_MAX_RGB_PIXELS == 79 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 80
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_81) && defined(BMC_DEVICE_UI_RGB_PIXEL_80) && BMC_MAX_RGB_PIXELS == 80 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 81
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_82) && defined(BMC_DEVICE_UI_RGB_PIXEL_81) && BMC_MAX_RGB_PIXELS == 81 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 82
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_83) && defined(BMC_DEVICE_UI_RGB_PIXEL_82) && BMC_MAX_RGB_PIXELS == 82 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 83
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_84) && defined(BMC_DEVICE_UI_RGB_PIXEL_83) && BMC_MAX_RGB_PIXELS == 83 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 84
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_85) && defined(BMC_DEVICE_UI_RGB_PIXEL_84) && BMC_MAX_RGB_PIXELS == 84 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 85
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_86) && defined(BMC_DEVICE_UI_RGB_PIXEL_85) && BMC_MAX_RGB_PIXELS == 85 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 86
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_87) && defined(BMC_DEVICE_UI_RGB_PIXEL_86) && BMC_MAX_RGB_PIXELS == 86 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 87
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_88) && defined(BMC_DEVICE_UI_RGB_PIXEL_87) && BMC_MAX_RGB_PIXELS == 87 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 88
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_89) && defined(BMC_DEVICE_UI_RGB_PIXEL_88) && BMC_MAX_RGB_PIXELS == 88 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 89
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_90) && defined(BMC_DEVICE_UI_RGB_PIXEL_89) && BMC_MAX_RGB_PIXELS == 89 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 90
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_91) && defined(BMC_DEVICE_UI_RGB_PIXEL_90) && BMC_MAX_RGB_PIXELS == 90 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 91
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_92) && defined(BMC_DEVICE_UI_RGB_PIXEL_91) && BMC_MAX_RGB_PIXELS == 91 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 92
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_93) && defined(BMC_DEVICE_UI_RGB_PIXEL_92) && BMC_MAX_RGB_PIXELS == 92 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 93
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_94) && defined(BMC_DEVICE_UI_RGB_PIXEL_93) && BMC_MAX_RGB_PIXELS == 93 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 94
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_95) && defined(BMC_DEVICE_UI_RGB_PIXEL_94) && BMC_MAX_RGB_PIXELS == 94 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 95
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_96) && defined(BMC_DEVICE_UI_RGB_PIXEL_95) && BMC_MAX_RGB_PIXELS == 95 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 96
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_97) && defined(BMC_DEVICE_UI_RGB_PIXEL_96) && BMC_MAX_RGB_PIXELS == 96 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 97
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_98) && defined(BMC_DEVICE_UI_RGB_PIXEL_97) && BMC_MAX_RGB_PIXELS == 97 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 98
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_99) && defined(BMC_DEVICE_UI_RGB_PIXEL_98) && BMC_MAX_RGB_PIXELS == 98 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 99
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_100) && defined(BMC_DEVICE_UI_RGB_PIXEL_99) && BMC_MAX_RGB_PIXELS == 99 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 100
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_101) && defined(BMC_DEVICE_UI_RGB_PIXEL_100) && BMC_MAX_RGB_PIXELS == 100 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 101
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_102) && defined(BMC_DEVICE_UI_RGB_PIXEL_101) && BMC_MAX_RGB_PIXELS == 101 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 102
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_103) && defined(BMC_DEVICE_UI_RGB_PIXEL_102) && BMC_MAX_RGB_PIXELS == 102 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 103
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_104) && defined(BMC_DEVICE_UI_RGB_PIXEL_103) && BMC_MAX_RGB_PIXELS == 103 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 104
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_105) && defined(BMC_DEVICE_UI_RGB_PIXEL_104) && BMC_MAX_RGB_PIXELS == 104 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 105
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_106) && defined(BMC_DEVICE_UI_RGB_PIXEL_105) && BMC_MAX_RGB_PIXELS == 105 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 106
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_107) && defined(BMC_DEVICE_UI_RGB_PIXEL_106) && BMC_MAX_RGB_PIXELS == 106 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 107
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_108) && defined(BMC_DEVICE_UI_RGB_PIXEL_107) && BMC_MAX_RGB_PIXELS == 107 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 108
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_109) && defined(BMC_DEVICE_UI_RGB_PIXEL_108) && BMC_MAX_RGB_PIXELS == 108 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 109
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_110) && defined(BMC_DEVICE_UI_RGB_PIXEL_109) && BMC_MAX_RGB_PIXELS == 109 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 110
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_111) && defined(BMC_DEVICE_UI_RGB_PIXEL_110) && BMC_MAX_RGB_PIXELS == 110 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 111
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_112) && defined(BMC_DEVICE_UI_RGB_PIXEL_111) && BMC_MAX_RGB_PIXELS == 111 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 112
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_113) && defined(BMC_DEVICE_UI_RGB_PIXEL_112) && BMC_MAX_RGB_PIXELS == 112 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 113
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_114) && defined(BMC_DEVICE_UI_RGB_PIXEL_113) && BMC_MAX_RGB_PIXELS == 113 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 114
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_115) && defined(BMC_DEVICE_UI_RGB_PIXEL_114) && BMC_MAX_RGB_PIXELS == 114 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 115
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_116) && defined(BMC_DEVICE_UI_RGB_PIXEL_115) && BMC_MAX_RGB_PIXELS == 115 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 116
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_117) && defined(BMC_DEVICE_UI_RGB_PIXEL_116) && BMC_MAX_RGB_PIXELS == 116 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 117
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_118) && defined(BMC_DEVICE_UI_RGB_PIXEL_117) && BMC_MAX_RGB_PIXELS == 117 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 118
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_119) && defined(BMC_DEVICE_UI_RGB_PIXEL_118) && BMC_MAX_RGB_PIXELS == 118 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 119
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_120) && defined(BMC_DEVICE_UI_RGB_PIXEL_119) && BMC_MAX_RGB_PIXELS == 119 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 120
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_121) && defined(BMC_DEVICE_UI_RGB_PIXEL_120) && BMC_MAX_RGB_PIXELS == 120 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 121
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_122) && defined(BMC_DEVICE_UI_RGB_PIXEL_121) && BMC_MAX_RGB_PIXELS == 121 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 122
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_123) && defined(BMC_DEVICE_UI_RGB_PIXEL_122) && BMC_MAX_RGB_PIXELS == 122 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 123
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_124) && defined(BMC_DEVICE_UI_RGB_PIXEL_123) && BMC_MAX_RGB_PIXELS == 123 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 124
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_125) && defined(BMC_DEVICE_UI_RGB_PIXEL_124) && BMC_MAX_RGB_PIXELS == 124 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 125
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_126) && defined(BMC_DEVICE_UI_RGB_PIXEL_125) && BMC_MAX_RGB_PIXELS == 125 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 126
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_127) && defined(BMC_DEVICE_UI_RGB_PIXEL_126) && BMC_MAX_RGB_PIXELS == 126 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 127
#endif

#if defined(BMC_DEVICE_UI_RGB_PIXEL_128) && defined(BMC_DEVICE_UI_RGB_PIXEL_127) && BMC_MAX_RGB_PIXELS == 127 
  #ifdef BMC_MAX_RGB_PIXELS
    #undef BMC_MAX_RGB_PIXELS
  #endif

  #define BMC_MAX_RGB_PIXELS 128
#endif

// *******************************************
// *** RGB_PIXELS end
// *******************************************

// *******************************************
// *** GLOBAL_RGB_PIXELS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_RGB_PIXELS
  #undef BMC_MAX_GLOBAL_RGB_PIXELS
#endif

#define BMC_MAX_GLOBAL_RGB_PIXELS 0

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_1) && BMC_MAX_GLOBAL_RGB_PIXELS == 0 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_2) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_1) && BMC_MAX_GLOBAL_RGB_PIXELS == 1 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_3) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_2) && BMC_MAX_GLOBAL_RGB_PIXELS == 2 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_4) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_3) && BMC_MAX_GLOBAL_RGB_PIXELS == 3 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_5) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_4) && BMC_MAX_GLOBAL_RGB_PIXELS == 4 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_6) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_5) && BMC_MAX_GLOBAL_RGB_PIXELS == 5 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_7) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_6) && BMC_MAX_GLOBAL_RGB_PIXELS == 6 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_8) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_7) && BMC_MAX_GLOBAL_RGB_PIXELS == 7 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_9) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_8) && BMC_MAX_GLOBAL_RGB_PIXELS == 8 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_10) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_9) && BMC_MAX_GLOBAL_RGB_PIXELS == 9 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_11) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_10) && BMC_MAX_GLOBAL_RGB_PIXELS == 10 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_12) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_11) && BMC_MAX_GLOBAL_RGB_PIXELS == 11 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_13) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_12) && BMC_MAX_GLOBAL_RGB_PIXELS == 12 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_14) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_13) && BMC_MAX_GLOBAL_RGB_PIXELS == 13 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_15) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_14) && BMC_MAX_GLOBAL_RGB_PIXELS == 14 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_16) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_15) && BMC_MAX_GLOBAL_RGB_PIXELS == 15 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 16
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_17) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_16) && BMC_MAX_GLOBAL_RGB_PIXELS == 16 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 17
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_18) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_17) && BMC_MAX_GLOBAL_RGB_PIXELS == 17 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 18
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_19) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_18) && BMC_MAX_GLOBAL_RGB_PIXELS == 18 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 19
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_20) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_19) && BMC_MAX_GLOBAL_RGB_PIXELS == 19 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 20
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_21) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_20) && BMC_MAX_GLOBAL_RGB_PIXELS == 20 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 21
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_22) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_21) && BMC_MAX_GLOBAL_RGB_PIXELS == 21 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 22
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_23) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_22) && BMC_MAX_GLOBAL_RGB_PIXELS == 22 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 23
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_24) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_23) && BMC_MAX_GLOBAL_RGB_PIXELS == 23 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 24
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_25) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_24) && BMC_MAX_GLOBAL_RGB_PIXELS == 24 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 25
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_26) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_25) && BMC_MAX_GLOBAL_RGB_PIXELS == 25 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 26
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_27) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_26) && BMC_MAX_GLOBAL_RGB_PIXELS == 26 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 27
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_28) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_27) && BMC_MAX_GLOBAL_RGB_PIXELS == 27 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 28
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_29) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_28) && BMC_MAX_GLOBAL_RGB_PIXELS == 28 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 29
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_30) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_29) && BMC_MAX_GLOBAL_RGB_PIXELS == 29 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 30
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_31) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_30) && BMC_MAX_GLOBAL_RGB_PIXELS == 30 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 31
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_32) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_31) && BMC_MAX_GLOBAL_RGB_PIXELS == 31 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 32
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_33) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_32) && BMC_MAX_GLOBAL_RGB_PIXELS == 32 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 33
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_34) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_33) && BMC_MAX_GLOBAL_RGB_PIXELS == 33 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 34
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_35) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_34) && BMC_MAX_GLOBAL_RGB_PIXELS == 34 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 35
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_36) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_35) && BMC_MAX_GLOBAL_RGB_PIXELS == 35 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 36
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_37) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_36) && BMC_MAX_GLOBAL_RGB_PIXELS == 36 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 37
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_38) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_37) && BMC_MAX_GLOBAL_RGB_PIXELS == 37 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 38
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_39) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_38) && BMC_MAX_GLOBAL_RGB_PIXELS == 38 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 39
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_40) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_39) && BMC_MAX_GLOBAL_RGB_PIXELS == 39 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 40
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_41) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_40) && BMC_MAX_GLOBAL_RGB_PIXELS == 40 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 41
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_42) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_41) && BMC_MAX_GLOBAL_RGB_PIXELS == 41 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 42
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_43) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_42) && BMC_MAX_GLOBAL_RGB_PIXELS == 42 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 43
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_44) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_43) && BMC_MAX_GLOBAL_RGB_PIXELS == 43 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 44
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_45) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_44) && BMC_MAX_GLOBAL_RGB_PIXELS == 44 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 45
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_46) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_45) && BMC_MAX_GLOBAL_RGB_PIXELS == 45 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 46
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_47) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_46) && BMC_MAX_GLOBAL_RGB_PIXELS == 46 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 47
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_48) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_47) && BMC_MAX_GLOBAL_RGB_PIXELS == 47 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 48
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_49) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_48) && BMC_MAX_GLOBAL_RGB_PIXELS == 48 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 49
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_50) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_49) && BMC_MAX_GLOBAL_RGB_PIXELS == 49 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 50
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_51) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_50) && BMC_MAX_GLOBAL_RGB_PIXELS == 50 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 51
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_52) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_51) && BMC_MAX_GLOBAL_RGB_PIXELS == 51 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 52
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_53) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_52) && BMC_MAX_GLOBAL_RGB_PIXELS == 52 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 53
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_54) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_53) && BMC_MAX_GLOBAL_RGB_PIXELS == 53 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 54
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_55) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_54) && BMC_MAX_GLOBAL_RGB_PIXELS == 54 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 55
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_56) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_55) && BMC_MAX_GLOBAL_RGB_PIXELS == 55 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 56
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_57) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_56) && BMC_MAX_GLOBAL_RGB_PIXELS == 56 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 57
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_58) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_57) && BMC_MAX_GLOBAL_RGB_PIXELS == 57 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 58
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_59) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_58) && BMC_MAX_GLOBAL_RGB_PIXELS == 58 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 59
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_60) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_59) && BMC_MAX_GLOBAL_RGB_PIXELS == 59 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 60
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_61) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_60) && BMC_MAX_GLOBAL_RGB_PIXELS == 60 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 61
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_62) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_61) && BMC_MAX_GLOBAL_RGB_PIXELS == 61 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 62
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_63) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_62) && BMC_MAX_GLOBAL_RGB_PIXELS == 62 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 63
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_64) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_63) && BMC_MAX_GLOBAL_RGB_PIXELS == 63 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 64
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_65) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_64) && BMC_MAX_GLOBAL_RGB_PIXELS == 64 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 65
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_66) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_65) && BMC_MAX_GLOBAL_RGB_PIXELS == 65 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 66
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_67) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_66) && BMC_MAX_GLOBAL_RGB_PIXELS == 66 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 67
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_68) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_67) && BMC_MAX_GLOBAL_RGB_PIXELS == 67 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 68
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_69) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_68) && BMC_MAX_GLOBAL_RGB_PIXELS == 68 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 69
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_70) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_69) && BMC_MAX_GLOBAL_RGB_PIXELS == 69 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 70
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_71) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_70) && BMC_MAX_GLOBAL_RGB_PIXELS == 70 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 71
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_72) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_71) && BMC_MAX_GLOBAL_RGB_PIXELS == 71 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 72
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_73) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_72) && BMC_MAX_GLOBAL_RGB_PIXELS == 72 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 73
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_74) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_73) && BMC_MAX_GLOBAL_RGB_PIXELS == 73 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 74
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_75) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_74) && BMC_MAX_GLOBAL_RGB_PIXELS == 74 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 75
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_76) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_75) && BMC_MAX_GLOBAL_RGB_PIXELS == 75 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 76
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_77) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_76) && BMC_MAX_GLOBAL_RGB_PIXELS == 76 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 77
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_78) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_77) && BMC_MAX_GLOBAL_RGB_PIXELS == 77 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 78
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_79) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_78) && BMC_MAX_GLOBAL_RGB_PIXELS == 78 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 79
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_80) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_79) && BMC_MAX_GLOBAL_RGB_PIXELS == 79 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 80
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_81) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_80) && BMC_MAX_GLOBAL_RGB_PIXELS == 80 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 81
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_82) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_81) && BMC_MAX_GLOBAL_RGB_PIXELS == 81 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 82
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_83) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_82) && BMC_MAX_GLOBAL_RGB_PIXELS == 82 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 83
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_84) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_83) && BMC_MAX_GLOBAL_RGB_PIXELS == 83 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 84
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_85) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_84) && BMC_MAX_GLOBAL_RGB_PIXELS == 84 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 85
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_86) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_85) && BMC_MAX_GLOBAL_RGB_PIXELS == 85 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 86
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_87) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_86) && BMC_MAX_GLOBAL_RGB_PIXELS == 86 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 87
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_88) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_87) && BMC_MAX_GLOBAL_RGB_PIXELS == 87 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 88
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_89) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_88) && BMC_MAX_GLOBAL_RGB_PIXELS == 88 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 89
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_90) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_89) && BMC_MAX_GLOBAL_RGB_PIXELS == 89 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 90
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_91) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_90) && BMC_MAX_GLOBAL_RGB_PIXELS == 90 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 91
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_92) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_91) && BMC_MAX_GLOBAL_RGB_PIXELS == 91 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 92
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_93) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_92) && BMC_MAX_GLOBAL_RGB_PIXELS == 92 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 93
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_94) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_93) && BMC_MAX_GLOBAL_RGB_PIXELS == 93 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 94
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_95) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_94) && BMC_MAX_GLOBAL_RGB_PIXELS == 94 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 95
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_96) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_95) && BMC_MAX_GLOBAL_RGB_PIXELS == 95 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 96
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_97) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_96) && BMC_MAX_GLOBAL_RGB_PIXELS == 96 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 97
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_98) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_97) && BMC_MAX_GLOBAL_RGB_PIXELS == 97 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 98
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_99) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_98) && BMC_MAX_GLOBAL_RGB_PIXELS == 98 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 99
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_100) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_99) && BMC_MAX_GLOBAL_RGB_PIXELS == 99 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 100
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_101) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_100) && BMC_MAX_GLOBAL_RGB_PIXELS == 100 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 101
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_102) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_101) && BMC_MAX_GLOBAL_RGB_PIXELS == 101 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 102
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_103) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_102) && BMC_MAX_GLOBAL_RGB_PIXELS == 102 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 103
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_104) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_103) && BMC_MAX_GLOBAL_RGB_PIXELS == 103 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 104
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_105) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_104) && BMC_MAX_GLOBAL_RGB_PIXELS == 104 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 105
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_106) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_105) && BMC_MAX_GLOBAL_RGB_PIXELS == 105 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 106
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_107) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_106) && BMC_MAX_GLOBAL_RGB_PIXELS == 106 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 107
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_108) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_107) && BMC_MAX_GLOBAL_RGB_PIXELS == 107 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 108
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_109) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_108) && BMC_MAX_GLOBAL_RGB_PIXELS == 108 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 109
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_110) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_109) && BMC_MAX_GLOBAL_RGB_PIXELS == 109 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 110
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_111) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_110) && BMC_MAX_GLOBAL_RGB_PIXELS == 110 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 111
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_112) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_111) && BMC_MAX_GLOBAL_RGB_PIXELS == 111 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 112
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_113) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_112) && BMC_MAX_GLOBAL_RGB_PIXELS == 112 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 113
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_114) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_113) && BMC_MAX_GLOBAL_RGB_PIXELS == 113 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 114
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_115) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_114) && BMC_MAX_GLOBAL_RGB_PIXELS == 114 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 115
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_116) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_115) && BMC_MAX_GLOBAL_RGB_PIXELS == 115 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 116
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_117) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_116) && BMC_MAX_GLOBAL_RGB_PIXELS == 116 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 117
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_118) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_117) && BMC_MAX_GLOBAL_RGB_PIXELS == 117 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 118
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_119) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_118) && BMC_MAX_GLOBAL_RGB_PIXELS == 118 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 119
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_120) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_119) && BMC_MAX_GLOBAL_RGB_PIXELS == 119 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 120
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_121) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_120) && BMC_MAX_GLOBAL_RGB_PIXELS == 120 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 121
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_122) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_121) && BMC_MAX_GLOBAL_RGB_PIXELS == 121 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 122
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_123) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_122) && BMC_MAX_GLOBAL_RGB_PIXELS == 122 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 123
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_124) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_123) && BMC_MAX_GLOBAL_RGB_PIXELS == 123 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 124
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_125) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_124) && BMC_MAX_GLOBAL_RGB_PIXELS == 124 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 125
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_126) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_125) && BMC_MAX_GLOBAL_RGB_PIXELS == 125 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 126
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_127) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_126) && BMC_MAX_GLOBAL_RGB_PIXELS == 126 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 127
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_128) && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_127) && BMC_MAX_GLOBAL_RGB_PIXELS == 127 
  #ifdef BMC_MAX_GLOBAL_RGB_PIXELS
    #undef BMC_MAX_GLOBAL_RGB_PIXELS
  #endif

  #define BMC_MAX_GLOBAL_RGB_PIXELS 128
#endif

// *******************************************
// *** GLOBAL_RGB_PIXELS end
// *******************************************

// *******************************************
// *** MAGIC_ENCODERS start
// *******************************************

#ifdef BMC_MAX_MAGIC_ENCODERS
  #undef BMC_MAX_MAGIC_ENCODERS
#endif

#define BMC_MAX_MAGIC_ENCODERS 0

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_1) && BMC_MAX_MAGIC_ENCODERS == 0 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 1
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_2) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_1) && BMC_MAX_MAGIC_ENCODERS == 1 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 2
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_3) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_2) && BMC_MAX_MAGIC_ENCODERS == 2 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 3
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_4) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_3) && BMC_MAX_MAGIC_ENCODERS == 3 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 4
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_5) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_4) && BMC_MAX_MAGIC_ENCODERS == 4 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 5
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_6) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_5) && BMC_MAX_MAGIC_ENCODERS == 5 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 6
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_7) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_6) && BMC_MAX_MAGIC_ENCODERS == 6 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 7
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_8) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_7) && BMC_MAX_MAGIC_ENCODERS == 7 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 8
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_9) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_8) && BMC_MAX_MAGIC_ENCODERS == 8 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 9
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_10) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_9) && BMC_MAX_MAGIC_ENCODERS == 9 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 10
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_11) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_10) && BMC_MAX_MAGIC_ENCODERS == 10 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 11
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_12) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_11) && BMC_MAX_MAGIC_ENCODERS == 11 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 12
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_13) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_12) && BMC_MAX_MAGIC_ENCODERS == 12 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 13
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_14) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_13) && BMC_MAX_MAGIC_ENCODERS == 13 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 14
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_15) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_14) && BMC_MAX_MAGIC_ENCODERS == 14 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 15
#endif

#if defined(BMC_DEVICE_UI_MAGIC_ENCODER_16) && defined(BMC_DEVICE_UI_MAGIC_ENCODER_15) && BMC_MAX_MAGIC_ENCODERS == 15 
  #ifdef BMC_MAX_MAGIC_ENCODERS
    #undef BMC_MAX_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_MAGIC_ENCODERS 16
#endif

// *******************************************
// *** MAGIC_ENCODERS end
// *******************************************

// *******************************************
// *** GLOBAL_MAGIC_ENCODERS start
// *******************************************

#ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
#endif

#define BMC_MAX_GLOBAL_MAGIC_ENCODERS 0

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_1) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 0 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 1
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_2) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_1) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 1 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 2
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_3) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_2) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 2 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 3
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_4) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_3) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 3 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 4
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_5) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_4) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 4 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 5
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_6) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_5) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 5 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 6
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_7) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_6) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 6 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 7
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_8) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_7) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 7 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 8
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_9) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_8) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 8 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 9
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_10) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_9) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 9 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 10
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_11) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_10) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 10 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 11
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_12) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_11) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 11 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 12
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_13) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_12) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 12 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 13
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_14) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_13) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 13 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 14
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_15) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_14) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 14 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 15
#endif

#if defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_16) && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_15) && BMC_MAX_GLOBAL_MAGIC_ENCODERS == 15 
  #ifdef BMC_MAX_GLOBAL_MAGIC_ENCODERS
    #undef BMC_MAX_GLOBAL_MAGIC_ENCODERS
  #endif

  #define BMC_MAX_GLOBAL_MAGIC_ENCODERS 16
#endif

// *******************************************
// *** GLOBAL_MAGIC_ENCODERS end
// *******************************************

// *******************************************
// *** NL_RELAYS start
// *******************************************

#ifdef BMC_MAX_NL_RELAYS
  #undef BMC_MAX_NL_RELAYS
#endif

#define BMC_MAX_NL_RELAYS 0

#if defined(BMC_DEVICE_UI_NL_RELAY_1) && BMC_MAX_NL_RELAYS == 0 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 1
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_2) && defined(BMC_DEVICE_UI_NL_RELAY_1) && BMC_MAX_NL_RELAYS == 1 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 2
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_3) && defined(BMC_DEVICE_UI_NL_RELAY_2) && BMC_MAX_NL_RELAYS == 2 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 3
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_4) && defined(BMC_DEVICE_UI_NL_RELAY_3) && BMC_MAX_NL_RELAYS == 3 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 4
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_5) && defined(BMC_DEVICE_UI_NL_RELAY_4) && BMC_MAX_NL_RELAYS == 4 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 5
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_6) && defined(BMC_DEVICE_UI_NL_RELAY_5) && BMC_MAX_NL_RELAYS == 5 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 6
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_7) && defined(BMC_DEVICE_UI_NL_RELAY_6) && BMC_MAX_NL_RELAYS == 6 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 7
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_8) && defined(BMC_DEVICE_UI_NL_RELAY_7) && BMC_MAX_NL_RELAYS == 7 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 8
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_9) && defined(BMC_DEVICE_UI_NL_RELAY_8) && BMC_MAX_NL_RELAYS == 8 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 9
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_10) && defined(BMC_DEVICE_UI_NL_RELAY_9) && BMC_MAX_NL_RELAYS == 9 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 10
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_11) && defined(BMC_DEVICE_UI_NL_RELAY_10) && BMC_MAX_NL_RELAYS == 10 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 11
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_12) && defined(BMC_DEVICE_UI_NL_RELAY_11) && BMC_MAX_NL_RELAYS == 11 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 12
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_13) && defined(BMC_DEVICE_UI_NL_RELAY_12) && BMC_MAX_NL_RELAYS == 12 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 13
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_14) && defined(BMC_DEVICE_UI_NL_RELAY_13) && BMC_MAX_NL_RELAYS == 13 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 14
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_15) && defined(BMC_DEVICE_UI_NL_RELAY_14) && BMC_MAX_NL_RELAYS == 14 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 15
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_16) && defined(BMC_DEVICE_UI_NL_RELAY_15) && BMC_MAX_NL_RELAYS == 15 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 16
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_17) && defined(BMC_DEVICE_UI_NL_RELAY_16) && BMC_MAX_NL_RELAYS == 16 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 17
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_18) && defined(BMC_DEVICE_UI_NL_RELAY_17) && BMC_MAX_NL_RELAYS == 17 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 18
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_19) && defined(BMC_DEVICE_UI_NL_RELAY_18) && BMC_MAX_NL_RELAYS == 18 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 19
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_20) && defined(BMC_DEVICE_UI_NL_RELAY_19) && BMC_MAX_NL_RELAYS == 19 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 20
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_21) && defined(BMC_DEVICE_UI_NL_RELAY_20) && BMC_MAX_NL_RELAYS == 20 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 21
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_22) && defined(BMC_DEVICE_UI_NL_RELAY_21) && BMC_MAX_NL_RELAYS == 21 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 22
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_23) && defined(BMC_DEVICE_UI_NL_RELAY_22) && BMC_MAX_NL_RELAYS == 22 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 23
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_24) && defined(BMC_DEVICE_UI_NL_RELAY_23) && BMC_MAX_NL_RELAYS == 23 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 24
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_25) && defined(BMC_DEVICE_UI_NL_RELAY_24) && BMC_MAX_NL_RELAYS == 24 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 25
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_26) && defined(BMC_DEVICE_UI_NL_RELAY_25) && BMC_MAX_NL_RELAYS == 25 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 26
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_27) && defined(BMC_DEVICE_UI_NL_RELAY_26) && BMC_MAX_NL_RELAYS == 26 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 27
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_28) && defined(BMC_DEVICE_UI_NL_RELAY_27) && BMC_MAX_NL_RELAYS == 27 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 28
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_29) && defined(BMC_DEVICE_UI_NL_RELAY_28) && BMC_MAX_NL_RELAYS == 28 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 29
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_30) && defined(BMC_DEVICE_UI_NL_RELAY_29) && BMC_MAX_NL_RELAYS == 29 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 30
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_31) && defined(BMC_DEVICE_UI_NL_RELAY_30) && BMC_MAX_NL_RELAYS == 30 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 31
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_32) && defined(BMC_DEVICE_UI_NL_RELAY_31) && BMC_MAX_NL_RELAYS == 31 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 32
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_33) && defined(BMC_DEVICE_UI_NL_RELAY_32) && BMC_MAX_NL_RELAYS == 32 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 33
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_34) && defined(BMC_DEVICE_UI_NL_RELAY_33) && BMC_MAX_NL_RELAYS == 33 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 34
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_35) && defined(BMC_DEVICE_UI_NL_RELAY_34) && BMC_MAX_NL_RELAYS == 34 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 35
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_36) && defined(BMC_DEVICE_UI_NL_RELAY_35) && BMC_MAX_NL_RELAYS == 35 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 36
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_37) && defined(BMC_DEVICE_UI_NL_RELAY_36) && BMC_MAX_NL_RELAYS == 36 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 37
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_38) && defined(BMC_DEVICE_UI_NL_RELAY_37) && BMC_MAX_NL_RELAYS == 37 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 38
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_39) && defined(BMC_DEVICE_UI_NL_RELAY_38) && BMC_MAX_NL_RELAYS == 38 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 39
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_40) && defined(BMC_DEVICE_UI_NL_RELAY_39) && BMC_MAX_NL_RELAYS == 39 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 40
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_41) && defined(BMC_DEVICE_UI_NL_RELAY_40) && BMC_MAX_NL_RELAYS == 40 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 41
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_42) && defined(BMC_DEVICE_UI_NL_RELAY_41) && BMC_MAX_NL_RELAYS == 41 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 42
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_43) && defined(BMC_DEVICE_UI_NL_RELAY_42) && BMC_MAX_NL_RELAYS == 42 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 43
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_44) && defined(BMC_DEVICE_UI_NL_RELAY_43) && BMC_MAX_NL_RELAYS == 43 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 44
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_45) && defined(BMC_DEVICE_UI_NL_RELAY_44) && BMC_MAX_NL_RELAYS == 44 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 45
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_46) && defined(BMC_DEVICE_UI_NL_RELAY_45) && BMC_MAX_NL_RELAYS == 45 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 46
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_47) && defined(BMC_DEVICE_UI_NL_RELAY_46) && BMC_MAX_NL_RELAYS == 46 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 47
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_48) && defined(BMC_DEVICE_UI_NL_RELAY_47) && BMC_MAX_NL_RELAYS == 47 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 48
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_49) && defined(BMC_DEVICE_UI_NL_RELAY_48) && BMC_MAX_NL_RELAYS == 48 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 49
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_50) && defined(BMC_DEVICE_UI_NL_RELAY_49) && BMC_MAX_NL_RELAYS == 49 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 50
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_51) && defined(BMC_DEVICE_UI_NL_RELAY_50) && BMC_MAX_NL_RELAYS == 50 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 51
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_52) && defined(BMC_DEVICE_UI_NL_RELAY_51) && BMC_MAX_NL_RELAYS == 51 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 52
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_53) && defined(BMC_DEVICE_UI_NL_RELAY_52) && BMC_MAX_NL_RELAYS == 52 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 53
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_54) && defined(BMC_DEVICE_UI_NL_RELAY_53) && BMC_MAX_NL_RELAYS == 53 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 54
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_55) && defined(BMC_DEVICE_UI_NL_RELAY_54) && BMC_MAX_NL_RELAYS == 54 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 55
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_56) && defined(BMC_DEVICE_UI_NL_RELAY_55) && BMC_MAX_NL_RELAYS == 55 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 56
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_57) && defined(BMC_DEVICE_UI_NL_RELAY_56) && BMC_MAX_NL_RELAYS == 56 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 57
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_58) && defined(BMC_DEVICE_UI_NL_RELAY_57) && BMC_MAX_NL_RELAYS == 57 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 58
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_59) && defined(BMC_DEVICE_UI_NL_RELAY_58) && BMC_MAX_NL_RELAYS == 58 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 59
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_60) && defined(BMC_DEVICE_UI_NL_RELAY_59) && BMC_MAX_NL_RELAYS == 59 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 60
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_61) && defined(BMC_DEVICE_UI_NL_RELAY_60) && BMC_MAX_NL_RELAYS == 60 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 61
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_62) && defined(BMC_DEVICE_UI_NL_RELAY_61) && BMC_MAX_NL_RELAYS == 61 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 62
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_63) && defined(BMC_DEVICE_UI_NL_RELAY_62) && BMC_MAX_NL_RELAYS == 62 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 63
#endif

#if defined(BMC_DEVICE_UI_NL_RELAY_64) && defined(BMC_DEVICE_UI_NL_RELAY_63) && BMC_MAX_NL_RELAYS == 63 
  #ifdef BMC_MAX_NL_RELAYS
    #undef BMC_MAX_NL_RELAYS
  #endif

  #define BMC_MAX_NL_RELAYS 64
#endif

// *******************************************
// *** NL_RELAYS end
// *******************************************

// *******************************************
// *** L_RELAYS start
// *******************************************

#ifdef BMC_MAX_L_RELAYS
  #undef BMC_MAX_L_RELAYS
#endif

#define BMC_MAX_L_RELAYS 0

#if defined(BMC_DEVICE_UI_L_RELAY_1) && BMC_MAX_L_RELAYS == 0 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 1
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_2) && defined(BMC_DEVICE_UI_L_RELAY_1) && BMC_MAX_L_RELAYS == 1 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 2
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_3) && defined(BMC_DEVICE_UI_L_RELAY_2) && BMC_MAX_L_RELAYS == 2 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 3
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_4) && defined(BMC_DEVICE_UI_L_RELAY_3) && BMC_MAX_L_RELAYS == 3 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 4
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_5) && defined(BMC_DEVICE_UI_L_RELAY_4) && BMC_MAX_L_RELAYS == 4 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 5
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_6) && defined(BMC_DEVICE_UI_L_RELAY_5) && BMC_MAX_L_RELAYS == 5 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 6
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_7) && defined(BMC_DEVICE_UI_L_RELAY_6) && BMC_MAX_L_RELAYS == 6 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 7
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_8) && defined(BMC_DEVICE_UI_L_RELAY_7) && BMC_MAX_L_RELAYS == 7 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 8
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_9) && defined(BMC_DEVICE_UI_L_RELAY_8) && BMC_MAX_L_RELAYS == 8 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 9
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_10) && defined(BMC_DEVICE_UI_L_RELAY_9) && BMC_MAX_L_RELAYS == 9 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 10
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_11) && defined(BMC_DEVICE_UI_L_RELAY_10) && BMC_MAX_L_RELAYS == 10 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 11
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_12) && defined(BMC_DEVICE_UI_L_RELAY_11) && BMC_MAX_L_RELAYS == 11 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 12
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_13) && defined(BMC_DEVICE_UI_L_RELAY_12) && BMC_MAX_L_RELAYS == 12 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 13
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_14) && defined(BMC_DEVICE_UI_L_RELAY_13) && BMC_MAX_L_RELAYS == 13 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 14
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_15) && defined(BMC_DEVICE_UI_L_RELAY_14) && BMC_MAX_L_RELAYS == 14 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 15
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_16) && defined(BMC_DEVICE_UI_L_RELAY_15) && BMC_MAX_L_RELAYS == 15 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 16
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_17) && defined(BMC_DEVICE_UI_L_RELAY_16) && BMC_MAX_L_RELAYS == 16 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 17
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_18) && defined(BMC_DEVICE_UI_L_RELAY_17) && BMC_MAX_L_RELAYS == 17 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 18
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_19) && defined(BMC_DEVICE_UI_L_RELAY_18) && BMC_MAX_L_RELAYS == 18 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 19
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_20) && defined(BMC_DEVICE_UI_L_RELAY_19) && BMC_MAX_L_RELAYS == 19 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 20
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_21) && defined(BMC_DEVICE_UI_L_RELAY_20) && BMC_MAX_L_RELAYS == 20 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 21
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_22) && defined(BMC_DEVICE_UI_L_RELAY_21) && BMC_MAX_L_RELAYS == 21 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 22
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_23) && defined(BMC_DEVICE_UI_L_RELAY_22) && BMC_MAX_L_RELAYS == 22 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 23
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_24) && defined(BMC_DEVICE_UI_L_RELAY_23) && BMC_MAX_L_RELAYS == 23 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 24
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_25) && defined(BMC_DEVICE_UI_L_RELAY_24) && BMC_MAX_L_RELAYS == 24 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 25
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_26) && defined(BMC_DEVICE_UI_L_RELAY_25) && BMC_MAX_L_RELAYS == 25 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 26
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_27) && defined(BMC_DEVICE_UI_L_RELAY_26) && BMC_MAX_L_RELAYS == 26 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 27
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_28) && defined(BMC_DEVICE_UI_L_RELAY_27) && BMC_MAX_L_RELAYS == 27 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 28
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_29) && defined(BMC_DEVICE_UI_L_RELAY_28) && BMC_MAX_L_RELAYS == 28 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 29
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_30) && defined(BMC_DEVICE_UI_L_RELAY_29) && BMC_MAX_L_RELAYS == 29 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 30
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_31) && defined(BMC_DEVICE_UI_L_RELAY_30) && BMC_MAX_L_RELAYS == 30 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 31
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_32) && defined(BMC_DEVICE_UI_L_RELAY_31) && BMC_MAX_L_RELAYS == 31 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 32
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_33) && defined(BMC_DEVICE_UI_L_RELAY_32) && BMC_MAX_L_RELAYS == 32 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 33
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_34) && defined(BMC_DEVICE_UI_L_RELAY_33) && BMC_MAX_L_RELAYS == 33 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 34
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_35) && defined(BMC_DEVICE_UI_L_RELAY_34) && BMC_MAX_L_RELAYS == 34 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 35
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_36) && defined(BMC_DEVICE_UI_L_RELAY_35) && BMC_MAX_L_RELAYS == 35 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 36
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_37) && defined(BMC_DEVICE_UI_L_RELAY_36) && BMC_MAX_L_RELAYS == 36 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 37
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_38) && defined(BMC_DEVICE_UI_L_RELAY_37) && BMC_MAX_L_RELAYS == 37 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 38
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_39) && defined(BMC_DEVICE_UI_L_RELAY_38) && BMC_MAX_L_RELAYS == 38 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 39
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_40) && defined(BMC_DEVICE_UI_L_RELAY_39) && BMC_MAX_L_RELAYS == 39 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 40
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_41) && defined(BMC_DEVICE_UI_L_RELAY_40) && BMC_MAX_L_RELAYS == 40 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 41
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_42) && defined(BMC_DEVICE_UI_L_RELAY_41) && BMC_MAX_L_RELAYS == 41 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 42
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_43) && defined(BMC_DEVICE_UI_L_RELAY_42) && BMC_MAX_L_RELAYS == 42 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 43
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_44) && defined(BMC_DEVICE_UI_L_RELAY_43) && BMC_MAX_L_RELAYS == 43 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 44
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_45) && defined(BMC_DEVICE_UI_L_RELAY_44) && BMC_MAX_L_RELAYS == 44 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 45
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_46) && defined(BMC_DEVICE_UI_L_RELAY_45) && BMC_MAX_L_RELAYS == 45 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 46
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_47) && defined(BMC_DEVICE_UI_L_RELAY_46) && BMC_MAX_L_RELAYS == 46 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 47
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_48) && defined(BMC_DEVICE_UI_L_RELAY_47) && BMC_MAX_L_RELAYS == 47 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 48
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_49) && defined(BMC_DEVICE_UI_L_RELAY_48) && BMC_MAX_L_RELAYS == 48 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 49
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_50) && defined(BMC_DEVICE_UI_L_RELAY_49) && BMC_MAX_L_RELAYS == 49 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 50
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_51) && defined(BMC_DEVICE_UI_L_RELAY_50) && BMC_MAX_L_RELAYS == 50 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 51
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_52) && defined(BMC_DEVICE_UI_L_RELAY_51) && BMC_MAX_L_RELAYS == 51 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 52
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_53) && defined(BMC_DEVICE_UI_L_RELAY_52) && BMC_MAX_L_RELAYS == 52 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 53
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_54) && defined(BMC_DEVICE_UI_L_RELAY_53) && BMC_MAX_L_RELAYS == 53 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 54
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_55) && defined(BMC_DEVICE_UI_L_RELAY_54) && BMC_MAX_L_RELAYS == 54 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 55
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_56) && defined(BMC_DEVICE_UI_L_RELAY_55) && BMC_MAX_L_RELAYS == 55 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 56
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_57) && defined(BMC_DEVICE_UI_L_RELAY_56) && BMC_MAX_L_RELAYS == 56 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 57
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_58) && defined(BMC_DEVICE_UI_L_RELAY_57) && BMC_MAX_L_RELAYS == 57 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 58
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_59) && defined(BMC_DEVICE_UI_L_RELAY_58) && BMC_MAX_L_RELAYS == 58 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 59
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_60) && defined(BMC_DEVICE_UI_L_RELAY_59) && BMC_MAX_L_RELAYS == 59 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 60
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_61) && defined(BMC_DEVICE_UI_L_RELAY_60) && BMC_MAX_L_RELAYS == 60 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 61
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_62) && defined(BMC_DEVICE_UI_L_RELAY_61) && BMC_MAX_L_RELAYS == 61 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 62
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_63) && defined(BMC_DEVICE_UI_L_RELAY_62) && BMC_MAX_L_RELAYS == 62 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 63
#endif

#if defined(BMC_DEVICE_UI_L_RELAY_64) && defined(BMC_DEVICE_UI_L_RELAY_63) && BMC_MAX_L_RELAYS == 63 
  #ifdef BMC_MAX_L_RELAYS
    #undef BMC_MAX_L_RELAYS
  #endif

  #define BMC_MAX_L_RELAYS 64
#endif

// *******************************************
// *** L_RELAYS end
// *******************************************

// *******************************************
// *** AUX_JACKS start
// *******************************************

#ifdef BMC_MAX_AUX_JACKS
  #undef BMC_MAX_AUX_JACKS
#endif

#define BMC_MAX_AUX_JACKS 0

#if defined(BMC_DEVICE_UI_AUX_JACK_1) && BMC_MAX_AUX_JACKS == 0 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 1
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_2) && defined(BMC_DEVICE_UI_AUX_JACK_1) && BMC_MAX_AUX_JACKS == 1 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 2
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_3) && defined(BMC_DEVICE_UI_AUX_JACK_2) && BMC_MAX_AUX_JACKS == 2 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 3
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_4) && defined(BMC_DEVICE_UI_AUX_JACK_3) && BMC_MAX_AUX_JACKS == 3 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 4
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_5) && defined(BMC_DEVICE_UI_AUX_JACK_4) && BMC_MAX_AUX_JACKS == 4 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 5
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_6) && defined(BMC_DEVICE_UI_AUX_JACK_5) && BMC_MAX_AUX_JACKS == 5 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 6
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_7) && defined(BMC_DEVICE_UI_AUX_JACK_6) && BMC_MAX_AUX_JACKS == 6 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 7
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_8) && defined(BMC_DEVICE_UI_AUX_JACK_7) && BMC_MAX_AUX_JACKS == 7 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 8
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_9) && defined(BMC_DEVICE_UI_AUX_JACK_8) && BMC_MAX_AUX_JACKS == 8 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 9
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_10) && defined(BMC_DEVICE_UI_AUX_JACK_9) && BMC_MAX_AUX_JACKS == 9 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 10
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_11) && defined(BMC_DEVICE_UI_AUX_JACK_10) && BMC_MAX_AUX_JACKS == 10 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 11
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_12) && defined(BMC_DEVICE_UI_AUX_JACK_11) && BMC_MAX_AUX_JACKS == 11 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 12
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_13) && defined(BMC_DEVICE_UI_AUX_JACK_12) && BMC_MAX_AUX_JACKS == 12 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 13
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_14) && defined(BMC_DEVICE_UI_AUX_JACK_13) && BMC_MAX_AUX_JACKS == 13 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 14
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_15) && defined(BMC_DEVICE_UI_AUX_JACK_14) && BMC_MAX_AUX_JACKS == 14 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 15
#endif

#if defined(BMC_DEVICE_UI_AUX_JACK_16) && defined(BMC_DEVICE_UI_AUX_JACK_15) && BMC_MAX_AUX_JACKS == 15 
  #ifdef BMC_MAX_AUX_JACKS
    #undef BMC_MAX_AUX_JACKS
  #endif

  #define BMC_MAX_AUX_JACKS 16
#endif

// *******************************************
// *** AUX_JACKS end
// *******************************************

// *******************************************
// *** PIXEL_STRIP start
// *******************************************
#if !defined(BMC_DEVICE_UI_PIXEL_STRIP_1)
  #undef BMC_MAX_PIXEL_STRIP
  #define BMC_MAX_PIXEL_STRIP 0
#endif
// *******************************************
// *** PIXEL_STRIP end
// *******************************************

#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 0

#if defined(BMC_DEVICE_UI_OLED_1)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 1


#if defined(BMC_DEVICE_UI_OLED_2)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 2


#if defined(BMC_DEVICE_UI_OLED_3)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 3


#if defined(BMC_DEVICE_UI_OLED_4)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 4


#if defined(BMC_DEVICE_UI_OLED_5)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 5


#if defined(BMC_DEVICE_UI_OLED_6)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 6


#if defined(BMC_DEVICE_UI_OLED_7)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 7


#if defined(BMC_DEVICE_UI_OLED_8)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 8


#if defined(BMC_DEVICE_UI_OLED_9)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 9


#if defined(BMC_DEVICE_UI_OLED_10)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 10


#if defined(BMC_DEVICE_UI_OLED_11)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 11


#if defined(BMC_DEVICE_UI_OLED_12)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 12


#if defined(BMC_DEVICE_UI_OLED_13)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 13


#if defined(BMC_DEVICE_UI_OLED_14)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 14


#if defined(BMC_DEVICE_UI_OLED_15)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 15


#if defined(BMC_DEVICE_UI_OLED_16)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 16


#if defined(BMC_DEVICE_UI_OLED_17)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 17


#if defined(BMC_DEVICE_UI_OLED_18)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 18


#if defined(BMC_DEVICE_UI_OLED_19)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 19


#if defined(BMC_DEVICE_UI_OLED_20)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 20


#if defined(BMC_DEVICE_UI_OLED_21)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 21


#if defined(BMC_DEVICE_UI_OLED_22)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 22


#if defined(BMC_DEVICE_UI_OLED_23)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 23


#if defined(BMC_DEVICE_UI_OLED_24)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 24


#if defined(BMC_DEVICE_UI_OLED_25)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 25


#if defined(BMC_DEVICE_UI_OLED_26)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 26


#if defined(BMC_DEVICE_UI_OLED_27)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 27


#if defined(BMC_DEVICE_UI_OLED_28)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 28


#if defined(BMC_DEVICE_UI_OLED_29)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 29


#if defined(BMC_DEVICE_UI_OLED_30)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 30


#if defined(BMC_DEVICE_UI_OLED_31)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 31


#if defined(BMC_DEVICE_UI_OLED_32)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 32


#if defined(BMC_DEVICE_UI_OLED_33)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 33


#if defined(BMC_DEVICE_UI_OLED_34)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 34


#if defined(BMC_DEVICE_UI_OLED_35)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 35


#if defined(BMC_DEVICE_UI_OLED_36)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 36


#if defined(BMC_DEVICE_UI_OLED_37)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 37


#if defined(BMC_DEVICE_UI_OLED_38)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 38


#if defined(BMC_DEVICE_UI_OLED_39)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 39


#if defined(BMC_DEVICE_UI_OLED_40)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 40


#if defined(BMC_DEVICE_UI_OLED_41)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 41


#if defined(BMC_DEVICE_UI_OLED_42)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 42


#if defined(BMC_DEVICE_UI_OLED_43)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 43


#if defined(BMC_DEVICE_UI_OLED_44)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 44


#if defined(BMC_DEVICE_UI_OLED_45)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 45


#if defined(BMC_DEVICE_UI_OLED_46)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 46


#if defined(BMC_DEVICE_UI_OLED_47)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 47


#if defined(BMC_DEVICE_UI_OLED_48)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 48


#if defined(BMC_DEVICE_UI_OLED_49)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 49


#if defined(BMC_DEVICE_UI_OLED_50)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 50


#if defined(BMC_DEVICE_UI_OLED_51)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 51


#if defined(BMC_DEVICE_UI_OLED_52)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 52


#if defined(BMC_DEVICE_UI_OLED_53)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 53


#if defined(BMC_DEVICE_UI_OLED_54)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 54


#if defined(BMC_DEVICE_UI_OLED_55)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 55


#if defined(BMC_DEVICE_UI_OLED_56)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 56


#if defined(BMC_DEVICE_UI_OLED_57)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 57


#if defined(BMC_DEVICE_UI_OLED_58)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 58


#if defined(BMC_DEVICE_UI_OLED_59)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 59


#if defined(BMC_DEVICE_UI_OLED_60)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 60


#if defined(BMC_DEVICE_UI_OLED_61)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 61


#if defined(BMC_DEVICE_UI_OLED_62)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 62


#if defined(BMC_DEVICE_UI_OLED_63)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 63


#if defined(BMC_DEVICE_UI_OLED_64)
#ifdef BMC_MAX_OLED
#undef BMC_MAX_OLED
#endif
#define BMC_MAX_OLED 64


#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#if defined(BMC_MAX_ILI9341_BLOCKS)
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 0

#if defined(BMC_USE_ILI9341)
#undef BMC_USE_ILI9341
#endif

#if defined(BMC_DEVICE_UI_ILI) && BMC_MCU_MODEL != 32
#if defined(BMC_DEVICE_UI_ILI_1)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 1
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_2)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 2
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_3)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 3
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_4)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 4
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_5)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 5
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_6)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 6
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_7)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 7
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_8)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 8
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_9)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 9
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_10)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 10
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_11)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 11
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_12)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 12
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_13)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 13
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_14)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 14
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_15)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 15
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#if defined(BMC_DEVICE_UI_ILI_16)
#ifdef BMC_MAX_ILI9341_BLOCKS
#undef BMC_MAX_ILI9341_BLOCKS
#endif
#define BMC_MAX_ILI9341_BLOCKS 16
#if !defined(BMC_USE_ILI9341)
#define BMC_USE_ILI9341
#endif


#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#if defined(BMC_MAX_MINI_DISPLAY)
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 0

#if defined(BMC_USE_MINI_DISPLAY)
#undef BMC_USE_MINI_DISPLAY
#endif

#if BMC_MCU_MODEL != 32
#if defined(BMC_DEVICE_UI_MINI_DISPLAY_1)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 1
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_2)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 2
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_3)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 3
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_4)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 4
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_5)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 5
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_6)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 6
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_7)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 7
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_8)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 8
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_9)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 9
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_10)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 10
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_11)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 11
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_12)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 12
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_13)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 13
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_14)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 14
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_15)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 15
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_16)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 16
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_17)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 17
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_18)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 18
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_19)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 19
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_20)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 20
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_21)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 21
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_22)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 22
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_23)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 23
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_24)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 24
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_25)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 25
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_26)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 26
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_27)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 27
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_28)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 28
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_29)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 29
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_30)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 30
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_31)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 31
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#if defined(BMC_DEVICE_UI_MINI_DISPLAY_32)
#ifdef BMC_MAX_MINI_DISPLAY
#undef BMC_MAX_MINI_DISPLAY
#endif
#define BMC_MAX_MINI_DISPLAY 32
#if !defined(BMC_USE_MINI_DISPLAY)
#define BMC_USE_MINI_DISPLAY
#endif


#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#if defined(BMC_MAX_LCD)
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 0

#if defined(BMC_USE_LCD)
#undef BMC_USE_LCD
#endif

#if defined(BMC_DEVICE_UI_LCD_1)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 1
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#if defined(BMC_DEVICE_UI_LCD_2)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 2
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#if defined(BMC_DEVICE_UI_LCD_3)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 3
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#if defined(BMC_DEVICE_UI_LCD_4)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 4
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#if defined(BMC_DEVICE_UI_LCD_5)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 5
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#if defined(BMC_DEVICE_UI_LCD_6)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 6
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#if defined(BMC_DEVICE_UI_LCD_7)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 7
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#if defined(BMC_DEVICE_UI_LCD_8)
#ifdef BMC_MAX_LCD
#undef BMC_MAX_LCD
#endif
#define BMC_MAX_LCD 8
#if !defined(BMC_USE_LCD)
#define BMC_USE_LCD
#endif


#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 0
#if defined(BMC_LINK_1)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 1

#if defined(BMC_LINK_2)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 2

#if defined(BMC_LINK_3)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 3

#if defined(BMC_LINK_4)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 4

#if defined(BMC_LINK_5)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 5

#if defined(BMC_LINK_6)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 6

#if defined(BMC_LINK_7)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 7

#if defined(BMC_LINK_8)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 8

#if defined(BMC_LINK_9)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 9

#if defined(BMC_LINK_10)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 10

#if defined(BMC_LINK_11)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 11

#if defined(BMC_LINK_12)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 12

#if defined(BMC_LINK_13)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 13

#if defined(BMC_LINK_14)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 14

#if defined(BMC_LINK_15)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 15

#if defined(BMC_LINK_16)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 16

#if defined(BMC_LINK_17)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 17

#if defined(BMC_LINK_18)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 18

#if defined(BMC_LINK_19)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 19

#if defined(BMC_LINK_20)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 20

#if defined(BMC_LINK_21)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 21

#if defined(BMC_LINK_22)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 22

#if defined(BMC_LINK_23)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 23

#if defined(BMC_LINK_24)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 24

#if defined(BMC_LINK_25)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 25

#if defined(BMC_LINK_26)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 26

#if defined(BMC_LINK_27)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 27

#if defined(BMC_LINK_28)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 28

#if defined(BMC_LINK_29)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 29

#if defined(BMC_LINK_30)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 30

#if defined(BMC_LINK_31)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 31

#if defined(BMC_LINK_32)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 32

#if defined(BMC_LINK_33)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 33

#if defined(BMC_LINK_34)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 34

#if defined(BMC_LINK_35)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 35

#if defined(BMC_LINK_36)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 36

#if defined(BMC_LINK_37)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 37

#if defined(BMC_LINK_38)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 38

#if defined(BMC_LINK_39)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 39

#if defined(BMC_LINK_40)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 40

#if defined(BMC_LINK_41)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 41

#if defined(BMC_LINK_42)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 42

#if defined(BMC_LINK_43)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 43

#if defined(BMC_LINK_44)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 44

#if defined(BMC_LINK_45)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 45

#if defined(BMC_LINK_46)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 46

#if defined(BMC_LINK_47)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 47

#if defined(BMC_LINK_48)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 48

#if defined(BMC_LINK_49)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 49

#if defined(BMC_LINK_50)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 50

#if defined(BMC_LINK_51)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 51

#if defined(BMC_LINK_52)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 52

#if defined(BMC_LINK_53)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 53

#if defined(BMC_LINK_54)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 54

#if defined(BMC_LINK_55)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 55

#if defined(BMC_LINK_56)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 56

#if defined(BMC_LINK_57)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 57

#if defined(BMC_LINK_58)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 58

#if defined(BMC_LINK_59)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 59

#if defined(BMC_LINK_60)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 60

#if defined(BMC_LINK_61)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 61

#if defined(BMC_LINK_62)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 62

#if defined(BMC_LINK_63)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 63

#if defined(BMC_LINK_64)
#ifdef BMC_MAX_LINKS
#undef BMC_MAX_LINKS
#endif
#define BMC_MAX_LINKS 64

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif
