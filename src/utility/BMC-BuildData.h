/*
See https://www.RoxXxtar.com/bmc for more details
Copyright (c) 2022 RoxXxtar.com
See BMC Documentation for License
See LICENSE file in the project root for full license information.
*/

#ifndef BMC_BUILD_DATA_H
#define BMC_BUILD_DATA_H

#include "utility/BMC-Def.h"

class BMCBuildData {
  public:
    BMCBuildData(){}
    void begin(){}

    //pin, pinB, x, y, style, rotation, mergeType, mergeIndex, other1, other2
    static BMCUIData getUIData(uint8_t device, int16_t n){
      switch(device){
          case BMC_DEVICE_ID_PRESET:
          #if BMC_MAX_PRESETS > 0
          {BMCUIData e; return e;}
          #endif
          break;
      case BMC_DEVICE_ID_SETLIST:
          #if BMC_MAX_SETLISTS > 0
          {BMCUIData e; return e;}
          #endif
          break;
      case BMC_DEVICE_ID_SETLIST_SONG_LIBRARY:
          #if BMC_MAX_SETLISTS_SONGS_LIBRARY > 0
          {BMCUIData e; return e;}
          #endif
          break;
      case BMC_DEVICE_ID_BUTTON:
          #if BMC_MAX_BUTTONS > 0
            switch(n){
              #if BMC_MAX_BUTTONS > 0 && defined(BMC_DEVICE_UI_BUTTON_1)
              case 0: return BMC_DEVICE_UI_BUTTON_1;
            #endif
            #if BMC_MAX_BUTTONS > 1 && defined(BMC_DEVICE_UI_BUTTON_2)
              case 1: return BMC_DEVICE_UI_BUTTON_2;
            #endif
            #if BMC_MAX_BUTTONS > 2 && defined(BMC_DEVICE_UI_BUTTON_3)
              case 2: return BMC_DEVICE_UI_BUTTON_3;
            #endif
            #if BMC_MAX_BUTTONS > 3 && defined(BMC_DEVICE_UI_BUTTON_4)
              case 3: return BMC_DEVICE_UI_BUTTON_4;
            #endif
            #if BMC_MAX_BUTTONS > 4 && defined(BMC_DEVICE_UI_BUTTON_5)
              case 4: return BMC_DEVICE_UI_BUTTON_5;
            #endif
            #if BMC_MAX_BUTTONS > 5 && defined(BMC_DEVICE_UI_BUTTON_6)
              case 5: return BMC_DEVICE_UI_BUTTON_6;
            #endif
            #if BMC_MAX_BUTTONS > 6 && defined(BMC_DEVICE_UI_BUTTON_7)
              case 6: return BMC_DEVICE_UI_BUTTON_7;
            #endif
            #if BMC_MAX_BUTTONS > 7 && defined(BMC_DEVICE_UI_BUTTON_8)
              case 7: return BMC_DEVICE_UI_BUTTON_8;
            #endif
            #if BMC_MAX_BUTTONS > 8 && defined(BMC_DEVICE_UI_BUTTON_9)
              case 8: return BMC_DEVICE_UI_BUTTON_9;
            #endif
            #if BMC_MAX_BUTTONS > 9 && defined(BMC_DEVICE_UI_BUTTON_10)
              case 9: return BMC_DEVICE_UI_BUTTON_10;
            #endif
            #if BMC_MAX_BUTTONS > 10 && defined(BMC_DEVICE_UI_BUTTON_11)
              case 10: return BMC_DEVICE_UI_BUTTON_11;
            #endif
            #if BMC_MAX_BUTTONS > 11 && defined(BMC_DEVICE_UI_BUTTON_12)
              case 11: return BMC_DEVICE_UI_BUTTON_12;
            #endif
            #if BMC_MAX_BUTTONS > 12 && defined(BMC_DEVICE_UI_BUTTON_13)
              case 12: return BMC_DEVICE_UI_BUTTON_13;
            #endif
            #if BMC_MAX_BUTTONS > 13 && defined(BMC_DEVICE_UI_BUTTON_14)
              case 13: return BMC_DEVICE_UI_BUTTON_14;
            #endif
            #if BMC_MAX_BUTTONS > 14 && defined(BMC_DEVICE_UI_BUTTON_15)
              case 14: return BMC_DEVICE_UI_BUTTON_15;
            #endif
            #if BMC_MAX_BUTTONS > 15 && defined(BMC_DEVICE_UI_BUTTON_16)
              case 15: return BMC_DEVICE_UI_BUTTON_16;
            #endif
            #if BMC_MAX_BUTTONS > 16 && defined(BMC_DEVICE_UI_BUTTON_17)
              case 16: return BMC_DEVICE_UI_BUTTON_17;
            #endif
            #if BMC_MAX_BUTTONS > 17 && defined(BMC_DEVICE_UI_BUTTON_18)
              case 17: return BMC_DEVICE_UI_BUTTON_18;
            #endif
            #if BMC_MAX_BUTTONS > 18 && defined(BMC_DEVICE_UI_BUTTON_19)
              case 18: return BMC_DEVICE_UI_BUTTON_19;
            #endif
            #if BMC_MAX_BUTTONS > 19 && defined(BMC_DEVICE_UI_BUTTON_20)
              case 19: return BMC_DEVICE_UI_BUTTON_20;
            #endif
            #if BMC_MAX_BUTTONS > 20 && defined(BMC_DEVICE_UI_BUTTON_21)
              case 20: return BMC_DEVICE_UI_BUTTON_21;
            #endif
            #if BMC_MAX_BUTTONS > 21 && defined(BMC_DEVICE_UI_BUTTON_22)
              case 21: return BMC_DEVICE_UI_BUTTON_22;
            #endif
            #if BMC_MAX_BUTTONS > 22 && defined(BMC_DEVICE_UI_BUTTON_23)
              case 22: return BMC_DEVICE_UI_BUTTON_23;
            #endif
            #if BMC_MAX_BUTTONS > 23 && defined(BMC_DEVICE_UI_BUTTON_24)
              case 23: return BMC_DEVICE_UI_BUTTON_24;
            #endif
            #if BMC_MAX_BUTTONS > 24 && defined(BMC_DEVICE_UI_BUTTON_25)
              case 24: return BMC_DEVICE_UI_BUTTON_25;
            #endif
            #if BMC_MAX_BUTTONS > 25 && defined(BMC_DEVICE_UI_BUTTON_26)
              case 25: return BMC_DEVICE_UI_BUTTON_26;
            #endif
            #if BMC_MAX_BUTTONS > 26 && defined(BMC_DEVICE_UI_BUTTON_27)
              case 26: return BMC_DEVICE_UI_BUTTON_27;
            #endif
            #if BMC_MAX_BUTTONS > 27 && defined(BMC_DEVICE_UI_BUTTON_28)
              case 27: return BMC_DEVICE_UI_BUTTON_28;
            #endif
            #if BMC_MAX_BUTTONS > 28 && defined(BMC_DEVICE_UI_BUTTON_29)
              case 28: return BMC_DEVICE_UI_BUTTON_29;
            #endif
            #if BMC_MAX_BUTTONS > 29 && defined(BMC_DEVICE_UI_BUTTON_30)
              case 29: return BMC_DEVICE_UI_BUTTON_30;
            #endif
            #if BMC_MAX_BUTTONS > 30 && defined(BMC_DEVICE_UI_BUTTON_31)
              case 30: return BMC_DEVICE_UI_BUTTON_31;
            #endif
            #if BMC_MAX_BUTTONS > 31 && defined(BMC_DEVICE_UI_BUTTON_32)
              case 31: return BMC_DEVICE_UI_BUTTON_32;
            #endif
            #if BMC_MAX_BUTTONS > 32 && defined(BMC_DEVICE_UI_BUTTON_33)
              case 32: return BMC_DEVICE_UI_BUTTON_33;
            #endif
            #if BMC_MAX_BUTTONS > 33 && defined(BMC_DEVICE_UI_BUTTON_34)
              case 33: return BMC_DEVICE_UI_BUTTON_34;
            #endif
            #if BMC_MAX_BUTTONS > 34 && defined(BMC_DEVICE_UI_BUTTON_35)
              case 34: return BMC_DEVICE_UI_BUTTON_35;
            #endif
            #if BMC_MAX_BUTTONS > 35 && defined(BMC_DEVICE_UI_BUTTON_36)
              case 35: return BMC_DEVICE_UI_BUTTON_36;
            #endif
            #if BMC_MAX_BUTTONS > 36 && defined(BMC_DEVICE_UI_BUTTON_37)
              case 36: return BMC_DEVICE_UI_BUTTON_37;
            #endif
            #if BMC_MAX_BUTTONS > 37 && defined(BMC_DEVICE_UI_BUTTON_38)
              case 37: return BMC_DEVICE_UI_BUTTON_38;
            #endif
            #if BMC_MAX_BUTTONS > 38 && defined(BMC_DEVICE_UI_BUTTON_39)
              case 38: return BMC_DEVICE_UI_BUTTON_39;
            #endif
            #if BMC_MAX_BUTTONS > 39 && defined(BMC_DEVICE_UI_BUTTON_40)
              case 39: return BMC_DEVICE_UI_BUTTON_40;
            #endif
            #if BMC_MAX_BUTTONS > 40 && defined(BMC_DEVICE_UI_BUTTON_41)
              case 40: return BMC_DEVICE_UI_BUTTON_41;
            #endif
            #if BMC_MAX_BUTTONS > 41 && defined(BMC_DEVICE_UI_BUTTON_42)
              case 41: return BMC_DEVICE_UI_BUTTON_42;
            #endif
            #if BMC_MAX_BUTTONS > 42 && defined(BMC_DEVICE_UI_BUTTON_43)
              case 42: return BMC_DEVICE_UI_BUTTON_43;
            #endif
            #if BMC_MAX_BUTTONS > 43 && defined(BMC_DEVICE_UI_BUTTON_44)
              case 43: return BMC_DEVICE_UI_BUTTON_44;
            #endif
            #if BMC_MAX_BUTTONS > 44 && defined(BMC_DEVICE_UI_BUTTON_45)
              case 44: return BMC_DEVICE_UI_BUTTON_45;
            #endif
            #if BMC_MAX_BUTTONS > 45 && defined(BMC_DEVICE_UI_BUTTON_46)
              case 45: return BMC_DEVICE_UI_BUTTON_46;
            #endif
            #if BMC_MAX_BUTTONS > 46 && defined(BMC_DEVICE_UI_BUTTON_47)
              case 46: return BMC_DEVICE_UI_BUTTON_47;
            #endif
            #if BMC_MAX_BUTTONS > 47 && defined(BMC_DEVICE_UI_BUTTON_48)
              case 47: return BMC_DEVICE_UI_BUTTON_48;
            #endif
            #if BMC_MAX_BUTTONS > 48 && defined(BMC_DEVICE_UI_BUTTON_49)
              case 48: return BMC_DEVICE_UI_BUTTON_49;
            #endif
            #if BMC_MAX_BUTTONS > 49 && defined(BMC_DEVICE_UI_BUTTON_50)
              case 49: return BMC_DEVICE_UI_BUTTON_50;
            #endif
            #if BMC_MAX_BUTTONS > 50 && defined(BMC_DEVICE_UI_BUTTON_51)
              case 50: return BMC_DEVICE_UI_BUTTON_51;
            #endif
            #if BMC_MAX_BUTTONS > 51 && defined(BMC_DEVICE_UI_BUTTON_52)
              case 51: return BMC_DEVICE_UI_BUTTON_52;
            #endif
            #if BMC_MAX_BUTTONS > 52 && defined(BMC_DEVICE_UI_BUTTON_53)
              case 52: return BMC_DEVICE_UI_BUTTON_53;
            #endif
            #if BMC_MAX_BUTTONS > 53 && defined(BMC_DEVICE_UI_BUTTON_54)
              case 53: return BMC_DEVICE_UI_BUTTON_54;
            #endif
            #if BMC_MAX_BUTTONS > 54 && defined(BMC_DEVICE_UI_BUTTON_55)
              case 54: return BMC_DEVICE_UI_BUTTON_55;
            #endif
            #if BMC_MAX_BUTTONS > 55 && defined(BMC_DEVICE_UI_BUTTON_56)
              case 55: return BMC_DEVICE_UI_BUTTON_56;
            #endif
            #if BMC_MAX_BUTTONS > 56 && defined(BMC_DEVICE_UI_BUTTON_57)
              case 56: return BMC_DEVICE_UI_BUTTON_57;
            #endif
            #if BMC_MAX_BUTTONS > 57 && defined(BMC_DEVICE_UI_BUTTON_58)
              case 57: return BMC_DEVICE_UI_BUTTON_58;
            #endif
            #if BMC_MAX_BUTTONS > 58 && defined(BMC_DEVICE_UI_BUTTON_59)
              case 58: return BMC_DEVICE_UI_BUTTON_59;
            #endif
            #if BMC_MAX_BUTTONS > 59 && defined(BMC_DEVICE_UI_BUTTON_60)
              case 59: return BMC_DEVICE_UI_BUTTON_60;
            #endif
            #if BMC_MAX_BUTTONS > 60 && defined(BMC_DEVICE_UI_BUTTON_61)
              case 60: return BMC_DEVICE_UI_BUTTON_61;
            #endif
            #if BMC_MAX_BUTTONS > 61 && defined(BMC_DEVICE_UI_BUTTON_62)
              case 61: return BMC_DEVICE_UI_BUTTON_62;
            #endif
            #if BMC_MAX_BUTTONS > 62 && defined(BMC_DEVICE_UI_BUTTON_63)
              case 62: return BMC_DEVICE_UI_BUTTON_63;
            #endif
            #if BMC_MAX_BUTTONS > 63 && defined(BMC_DEVICE_UI_BUTTON_64)
              case 63: return BMC_DEVICE_UI_BUTTON_64;
            #endif
            #if BMC_MAX_BUTTONS > 64 && defined(BMC_DEVICE_UI_BUTTON_65)
              case 64: return BMC_DEVICE_UI_BUTTON_65;
            #endif
            #if BMC_MAX_BUTTONS > 65 && defined(BMC_DEVICE_UI_BUTTON_66)
              case 65: return BMC_DEVICE_UI_BUTTON_66;
            #endif
            #if BMC_MAX_BUTTONS > 66 && defined(BMC_DEVICE_UI_BUTTON_67)
              case 66: return BMC_DEVICE_UI_BUTTON_67;
            #endif
            #if BMC_MAX_BUTTONS > 67 && defined(BMC_DEVICE_UI_BUTTON_68)
              case 67: return BMC_DEVICE_UI_BUTTON_68;
            #endif
            #if BMC_MAX_BUTTONS > 68 && defined(BMC_DEVICE_UI_BUTTON_69)
              case 68: return BMC_DEVICE_UI_BUTTON_69;
            #endif
            #if BMC_MAX_BUTTONS > 69 && defined(BMC_DEVICE_UI_BUTTON_70)
              case 69: return BMC_DEVICE_UI_BUTTON_70;
            #endif
            #if BMC_MAX_BUTTONS > 70 && defined(BMC_DEVICE_UI_BUTTON_71)
              case 70: return BMC_DEVICE_UI_BUTTON_71;
            #endif
            #if BMC_MAX_BUTTONS > 71 && defined(BMC_DEVICE_UI_BUTTON_72)
              case 71: return BMC_DEVICE_UI_BUTTON_72;
            #endif
            #if BMC_MAX_BUTTONS > 72 && defined(BMC_DEVICE_UI_BUTTON_73)
              case 72: return BMC_DEVICE_UI_BUTTON_73;
            #endif
            #if BMC_MAX_BUTTONS > 73 && defined(BMC_DEVICE_UI_BUTTON_74)
              case 73: return BMC_DEVICE_UI_BUTTON_74;
            #endif
            #if BMC_MAX_BUTTONS > 74 && defined(BMC_DEVICE_UI_BUTTON_75)
              case 74: return BMC_DEVICE_UI_BUTTON_75;
            #endif
            #if BMC_MAX_BUTTONS > 75 && defined(BMC_DEVICE_UI_BUTTON_76)
              case 75: return BMC_DEVICE_UI_BUTTON_76;
            #endif
            #if BMC_MAX_BUTTONS > 76 && defined(BMC_DEVICE_UI_BUTTON_77)
              case 76: return BMC_DEVICE_UI_BUTTON_77;
            #endif
            #if BMC_MAX_BUTTONS > 77 && defined(BMC_DEVICE_UI_BUTTON_78)
              case 77: return BMC_DEVICE_UI_BUTTON_78;
            #endif
            #if BMC_MAX_BUTTONS > 78 && defined(BMC_DEVICE_UI_BUTTON_79)
              case 78: return BMC_DEVICE_UI_BUTTON_79;
            #endif
            #if BMC_MAX_BUTTONS > 79 && defined(BMC_DEVICE_UI_BUTTON_80)
              case 79: return BMC_DEVICE_UI_BUTTON_80;
            #endif
            #if BMC_MAX_BUTTONS > 80 && defined(BMC_DEVICE_UI_BUTTON_81)
              case 80: return BMC_DEVICE_UI_BUTTON_81;
            #endif
            #if BMC_MAX_BUTTONS > 81 && defined(BMC_DEVICE_UI_BUTTON_82)
              case 81: return BMC_DEVICE_UI_BUTTON_82;
            #endif
            #if BMC_MAX_BUTTONS > 82 && defined(BMC_DEVICE_UI_BUTTON_83)
              case 82: return BMC_DEVICE_UI_BUTTON_83;
            #endif
            #if BMC_MAX_BUTTONS > 83 && defined(BMC_DEVICE_UI_BUTTON_84)
              case 83: return BMC_DEVICE_UI_BUTTON_84;
            #endif
            #if BMC_MAX_BUTTONS > 84 && defined(BMC_DEVICE_UI_BUTTON_85)
              case 84: return BMC_DEVICE_UI_BUTTON_85;
            #endif
            #if BMC_MAX_BUTTONS > 85 && defined(BMC_DEVICE_UI_BUTTON_86)
              case 85: return BMC_DEVICE_UI_BUTTON_86;
            #endif
            #if BMC_MAX_BUTTONS > 86 && defined(BMC_DEVICE_UI_BUTTON_87)
              case 86: return BMC_DEVICE_UI_BUTTON_87;
            #endif
            #if BMC_MAX_BUTTONS > 87 && defined(BMC_DEVICE_UI_BUTTON_88)
              case 87: return BMC_DEVICE_UI_BUTTON_88;
            #endif
            #if BMC_MAX_BUTTONS > 88 && defined(BMC_DEVICE_UI_BUTTON_89)
              case 88: return BMC_DEVICE_UI_BUTTON_89;
            #endif
            #if BMC_MAX_BUTTONS > 89 && defined(BMC_DEVICE_UI_BUTTON_90)
              case 89: return BMC_DEVICE_UI_BUTTON_90;
            #endif
            #if BMC_MAX_BUTTONS > 90 && defined(BMC_DEVICE_UI_BUTTON_91)
              case 90: return BMC_DEVICE_UI_BUTTON_91;
            #endif
            #if BMC_MAX_BUTTONS > 91 && defined(BMC_DEVICE_UI_BUTTON_92)
              case 91: return BMC_DEVICE_UI_BUTTON_92;
            #endif
            #if BMC_MAX_BUTTONS > 92 && defined(BMC_DEVICE_UI_BUTTON_93)
              case 92: return BMC_DEVICE_UI_BUTTON_93;
            #endif
            #if BMC_MAX_BUTTONS > 93 && defined(BMC_DEVICE_UI_BUTTON_94)
              case 93: return BMC_DEVICE_UI_BUTTON_94;
            #endif
            #if BMC_MAX_BUTTONS > 94 && defined(BMC_DEVICE_UI_BUTTON_95)
              case 94: return BMC_DEVICE_UI_BUTTON_95;
            #endif
            #if BMC_MAX_BUTTONS > 95 && defined(BMC_DEVICE_UI_BUTTON_96)
              case 95: return BMC_DEVICE_UI_BUTTON_96;
            #endif
            #if BMC_MAX_BUTTONS > 96 && defined(BMC_DEVICE_UI_BUTTON_97)
              case 96: return BMC_DEVICE_UI_BUTTON_97;
            #endif
            #if BMC_MAX_BUTTONS > 97 && defined(BMC_DEVICE_UI_BUTTON_98)
              case 97: return BMC_DEVICE_UI_BUTTON_98;
            #endif
            #if BMC_MAX_BUTTONS > 98 && defined(BMC_DEVICE_UI_BUTTON_99)
              case 98: return BMC_DEVICE_UI_BUTTON_99;
            #endif
            #if BMC_MAX_BUTTONS > 99 && defined(BMC_DEVICE_UI_BUTTON_100)
              case 99: return BMC_DEVICE_UI_BUTTON_100;
            #endif
            #if BMC_MAX_BUTTONS > 100 && defined(BMC_DEVICE_UI_BUTTON_101)
              case 100: return BMC_DEVICE_UI_BUTTON_101;
            #endif
            #if BMC_MAX_BUTTONS > 101 && defined(BMC_DEVICE_UI_BUTTON_102)
              case 101: return BMC_DEVICE_UI_BUTTON_102;
            #endif
            #if BMC_MAX_BUTTONS > 102 && defined(BMC_DEVICE_UI_BUTTON_103)
              case 102: return BMC_DEVICE_UI_BUTTON_103;
            #endif
            #if BMC_MAX_BUTTONS > 103 && defined(BMC_DEVICE_UI_BUTTON_104)
              case 103: return BMC_DEVICE_UI_BUTTON_104;
            #endif
            #if BMC_MAX_BUTTONS > 104 && defined(BMC_DEVICE_UI_BUTTON_105)
              case 104: return BMC_DEVICE_UI_BUTTON_105;
            #endif
            #if BMC_MAX_BUTTONS > 105 && defined(BMC_DEVICE_UI_BUTTON_106)
              case 105: return BMC_DEVICE_UI_BUTTON_106;
            #endif
            #if BMC_MAX_BUTTONS > 106 && defined(BMC_DEVICE_UI_BUTTON_107)
              case 106: return BMC_DEVICE_UI_BUTTON_107;
            #endif
            #if BMC_MAX_BUTTONS > 107 && defined(BMC_DEVICE_UI_BUTTON_108)
              case 107: return BMC_DEVICE_UI_BUTTON_108;
            #endif
            #if BMC_MAX_BUTTONS > 108 && defined(BMC_DEVICE_UI_BUTTON_109)
              case 108: return BMC_DEVICE_UI_BUTTON_109;
            #endif
            #if BMC_MAX_BUTTONS > 109 && defined(BMC_DEVICE_UI_BUTTON_110)
              case 109: return BMC_DEVICE_UI_BUTTON_110;
            #endif
            #if BMC_MAX_BUTTONS > 110 && defined(BMC_DEVICE_UI_BUTTON_111)
              case 110: return BMC_DEVICE_UI_BUTTON_111;
            #endif
            #if BMC_MAX_BUTTONS > 111 && defined(BMC_DEVICE_UI_BUTTON_112)
              case 111: return BMC_DEVICE_UI_BUTTON_112;
            #endif
            #if BMC_MAX_BUTTONS > 112 && defined(BMC_DEVICE_UI_BUTTON_113)
              case 112: return BMC_DEVICE_UI_BUTTON_113;
            #endif
            #if BMC_MAX_BUTTONS > 113 && defined(BMC_DEVICE_UI_BUTTON_114)
              case 113: return BMC_DEVICE_UI_BUTTON_114;
            #endif
            #if BMC_MAX_BUTTONS > 114 && defined(BMC_DEVICE_UI_BUTTON_115)
              case 114: return BMC_DEVICE_UI_BUTTON_115;
            #endif
            #if BMC_MAX_BUTTONS > 115 && defined(BMC_DEVICE_UI_BUTTON_116)
              case 115: return BMC_DEVICE_UI_BUTTON_116;
            #endif
            #if BMC_MAX_BUTTONS > 116 && defined(BMC_DEVICE_UI_BUTTON_117)
              case 116: return BMC_DEVICE_UI_BUTTON_117;
            #endif
            #if BMC_MAX_BUTTONS > 117 && defined(BMC_DEVICE_UI_BUTTON_118)
              case 117: return BMC_DEVICE_UI_BUTTON_118;
            #endif
            #if BMC_MAX_BUTTONS > 118 && defined(BMC_DEVICE_UI_BUTTON_119)
              case 118: return BMC_DEVICE_UI_BUTTON_119;
            #endif
            #if BMC_MAX_BUTTONS > 119 && defined(BMC_DEVICE_UI_BUTTON_120)
              case 119: return BMC_DEVICE_UI_BUTTON_120;
            #endif
            #if BMC_MAX_BUTTONS > 120 && defined(BMC_DEVICE_UI_BUTTON_121)
              case 120: return BMC_DEVICE_UI_BUTTON_121;
            #endif
            #if BMC_MAX_BUTTONS > 121 && defined(BMC_DEVICE_UI_BUTTON_122)
              case 121: return BMC_DEVICE_UI_BUTTON_122;
            #endif
            #if BMC_MAX_BUTTONS > 122 && defined(BMC_DEVICE_UI_BUTTON_123)
              case 122: return BMC_DEVICE_UI_BUTTON_123;
            #endif
            #if BMC_MAX_BUTTONS > 123 && defined(BMC_DEVICE_UI_BUTTON_124)
              case 123: return BMC_DEVICE_UI_BUTTON_124;
            #endif
            #if BMC_MAX_BUTTONS > 124 && defined(BMC_DEVICE_UI_BUTTON_125)
              case 124: return BMC_DEVICE_UI_BUTTON_125;
            #endif
            #if BMC_MAX_BUTTONS > 125 && defined(BMC_DEVICE_UI_BUTTON_126)
              case 125: return BMC_DEVICE_UI_BUTTON_126;
            #endif
            #if BMC_MAX_BUTTONS > 126 && defined(BMC_DEVICE_UI_BUTTON_127)
              case 126: return BMC_DEVICE_UI_BUTTON_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_BUTTON:
          #if BMC_MAX_GLOBAL_BUTTONS > 0
            switch(n){
              #if BMC_MAX_GLOBAL_BUTTONS > 0 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_BUTTON_1;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 1 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_BUTTON_2;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 2 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_BUTTON_3;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 3 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_BUTTON_4;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 4 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_BUTTON_5;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 5 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_BUTTON_6;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 6 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_BUTTON_7;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 7 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_BUTTON_8;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 8 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_BUTTON_9;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 9 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_BUTTON_10;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 10 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_BUTTON_11;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 11 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_BUTTON_12;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 12 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_BUTTON_13;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 13 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_BUTTON_14;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 14 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_BUTTON_15;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 15 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_BUTTON_16;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 16 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_BUTTON_17;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 17 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_BUTTON_18;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 18 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_BUTTON_19;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 19 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_BUTTON_20;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 20 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_BUTTON_21;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 21 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_BUTTON_22;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 22 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_BUTTON_23;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 23 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_BUTTON_24;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 24 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_BUTTON_25;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 25 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_BUTTON_26;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 26 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_BUTTON_27;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 27 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_BUTTON_28;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 28 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_BUTTON_29;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 29 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_BUTTON_30;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 30 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_BUTTON_31;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 31 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_BUTTON_32;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 32 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_BUTTON_33;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 33 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_BUTTON_34;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 34 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_BUTTON_35;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 35 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_BUTTON_36;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 36 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_BUTTON_37;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 37 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_BUTTON_38;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 38 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_BUTTON_39;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 39 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_BUTTON_40;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 40 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_BUTTON_41;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 41 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_BUTTON_42;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 42 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_BUTTON_43;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 43 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_BUTTON_44;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 44 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_BUTTON_45;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 45 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_BUTTON_46;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 46 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_BUTTON_47;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 47 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_BUTTON_48;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 48 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_BUTTON_49;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 49 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_BUTTON_50;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 50 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_BUTTON_51;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 51 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_BUTTON_52;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 52 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_BUTTON_53;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 53 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_BUTTON_54;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 54 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_BUTTON_55;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 55 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_BUTTON_56;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 56 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_BUTTON_57;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 57 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_BUTTON_58;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 58 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_BUTTON_59;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 59 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_BUTTON_60;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 60 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_BUTTON_61;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 61 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_BUTTON_62;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 62 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_BUTTON_63;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 63 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_BUTTON_64;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 64 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_65)
              case 64: return BMC_DEVICE_UI_GLOBAL_BUTTON_65;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 65 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_66)
              case 65: return BMC_DEVICE_UI_GLOBAL_BUTTON_66;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 66 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_67)
              case 66: return BMC_DEVICE_UI_GLOBAL_BUTTON_67;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 67 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_68)
              case 67: return BMC_DEVICE_UI_GLOBAL_BUTTON_68;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 68 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_69)
              case 68: return BMC_DEVICE_UI_GLOBAL_BUTTON_69;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 69 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_70)
              case 69: return BMC_DEVICE_UI_GLOBAL_BUTTON_70;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 70 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_71)
              case 70: return BMC_DEVICE_UI_GLOBAL_BUTTON_71;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 71 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_72)
              case 71: return BMC_DEVICE_UI_GLOBAL_BUTTON_72;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 72 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_73)
              case 72: return BMC_DEVICE_UI_GLOBAL_BUTTON_73;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 73 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_74)
              case 73: return BMC_DEVICE_UI_GLOBAL_BUTTON_74;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 74 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_75)
              case 74: return BMC_DEVICE_UI_GLOBAL_BUTTON_75;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 75 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_76)
              case 75: return BMC_DEVICE_UI_GLOBAL_BUTTON_76;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 76 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_77)
              case 76: return BMC_DEVICE_UI_GLOBAL_BUTTON_77;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 77 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_78)
              case 77: return BMC_DEVICE_UI_GLOBAL_BUTTON_78;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 78 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_79)
              case 78: return BMC_DEVICE_UI_GLOBAL_BUTTON_79;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 79 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_80)
              case 79: return BMC_DEVICE_UI_GLOBAL_BUTTON_80;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 80 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_81)
              case 80: return BMC_DEVICE_UI_GLOBAL_BUTTON_81;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 81 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_82)
              case 81: return BMC_DEVICE_UI_GLOBAL_BUTTON_82;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 82 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_83)
              case 82: return BMC_DEVICE_UI_GLOBAL_BUTTON_83;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 83 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_84)
              case 83: return BMC_DEVICE_UI_GLOBAL_BUTTON_84;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 84 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_85)
              case 84: return BMC_DEVICE_UI_GLOBAL_BUTTON_85;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 85 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_86)
              case 85: return BMC_DEVICE_UI_GLOBAL_BUTTON_86;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 86 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_87)
              case 86: return BMC_DEVICE_UI_GLOBAL_BUTTON_87;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 87 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_88)
              case 87: return BMC_DEVICE_UI_GLOBAL_BUTTON_88;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 88 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_89)
              case 88: return BMC_DEVICE_UI_GLOBAL_BUTTON_89;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 89 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_90)
              case 89: return BMC_DEVICE_UI_GLOBAL_BUTTON_90;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 90 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_91)
              case 90: return BMC_DEVICE_UI_GLOBAL_BUTTON_91;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 91 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_92)
              case 91: return BMC_DEVICE_UI_GLOBAL_BUTTON_92;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 92 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_93)
              case 92: return BMC_DEVICE_UI_GLOBAL_BUTTON_93;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 93 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_94)
              case 93: return BMC_DEVICE_UI_GLOBAL_BUTTON_94;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 94 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_95)
              case 94: return BMC_DEVICE_UI_GLOBAL_BUTTON_95;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 95 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_96)
              case 95: return BMC_DEVICE_UI_GLOBAL_BUTTON_96;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 96 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_97)
              case 96: return BMC_DEVICE_UI_GLOBAL_BUTTON_97;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 97 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_98)
              case 97: return BMC_DEVICE_UI_GLOBAL_BUTTON_98;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 98 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_99)
              case 98: return BMC_DEVICE_UI_GLOBAL_BUTTON_99;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 99 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_100)
              case 99: return BMC_DEVICE_UI_GLOBAL_BUTTON_100;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 100 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_101)
              case 100: return BMC_DEVICE_UI_GLOBAL_BUTTON_101;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 101 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_102)
              case 101: return BMC_DEVICE_UI_GLOBAL_BUTTON_102;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 102 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_103)
              case 102: return BMC_DEVICE_UI_GLOBAL_BUTTON_103;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 103 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_104)
              case 103: return BMC_DEVICE_UI_GLOBAL_BUTTON_104;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 104 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_105)
              case 104: return BMC_DEVICE_UI_GLOBAL_BUTTON_105;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 105 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_106)
              case 105: return BMC_DEVICE_UI_GLOBAL_BUTTON_106;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 106 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_107)
              case 106: return BMC_DEVICE_UI_GLOBAL_BUTTON_107;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 107 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_108)
              case 107: return BMC_DEVICE_UI_GLOBAL_BUTTON_108;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 108 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_109)
              case 108: return BMC_DEVICE_UI_GLOBAL_BUTTON_109;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 109 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_110)
              case 109: return BMC_DEVICE_UI_GLOBAL_BUTTON_110;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 110 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_111)
              case 110: return BMC_DEVICE_UI_GLOBAL_BUTTON_111;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 111 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_112)
              case 111: return BMC_DEVICE_UI_GLOBAL_BUTTON_112;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 112 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_113)
              case 112: return BMC_DEVICE_UI_GLOBAL_BUTTON_113;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 113 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_114)
              case 113: return BMC_DEVICE_UI_GLOBAL_BUTTON_114;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 114 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_115)
              case 114: return BMC_DEVICE_UI_GLOBAL_BUTTON_115;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 115 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_116)
              case 115: return BMC_DEVICE_UI_GLOBAL_BUTTON_116;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 116 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_117)
              case 116: return BMC_DEVICE_UI_GLOBAL_BUTTON_117;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 117 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_118)
              case 117: return BMC_DEVICE_UI_GLOBAL_BUTTON_118;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 118 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_119)
              case 118: return BMC_DEVICE_UI_GLOBAL_BUTTON_119;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 119 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_120)
              case 119: return BMC_DEVICE_UI_GLOBAL_BUTTON_120;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 120 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_121)
              case 120: return BMC_DEVICE_UI_GLOBAL_BUTTON_121;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 121 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_122)
              case 121: return BMC_DEVICE_UI_GLOBAL_BUTTON_122;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 122 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_123)
              case 122: return BMC_DEVICE_UI_GLOBAL_BUTTON_123;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 123 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_124)
              case 123: return BMC_DEVICE_UI_GLOBAL_BUTTON_124;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 124 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_125)
              case 124: return BMC_DEVICE_UI_GLOBAL_BUTTON_125;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 125 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_126)
              case 125: return BMC_DEVICE_UI_GLOBAL_BUTTON_126;
            #endif
            #if BMC_MAX_GLOBAL_BUTTONS > 126 && defined(BMC_DEVICE_UI_GLOBAL_BUTTON_127)
              case 126: return BMC_DEVICE_UI_GLOBAL_BUTTON_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_LED:
          #if BMC_MAX_LEDS > 0
            switch(n){
              #if BMC_MAX_LEDS > 0 && defined(BMC_DEVICE_UI_LED_1)
              case 0: return BMC_DEVICE_UI_LED_1;
            #endif
            #if BMC_MAX_LEDS > 1 && defined(BMC_DEVICE_UI_LED_2)
              case 1: return BMC_DEVICE_UI_LED_2;
            #endif
            #if BMC_MAX_LEDS > 2 && defined(BMC_DEVICE_UI_LED_3)
              case 2: return BMC_DEVICE_UI_LED_3;
            #endif
            #if BMC_MAX_LEDS > 3 && defined(BMC_DEVICE_UI_LED_4)
              case 3: return BMC_DEVICE_UI_LED_4;
            #endif
            #if BMC_MAX_LEDS > 4 && defined(BMC_DEVICE_UI_LED_5)
              case 4: return BMC_DEVICE_UI_LED_5;
            #endif
            #if BMC_MAX_LEDS > 5 && defined(BMC_DEVICE_UI_LED_6)
              case 5: return BMC_DEVICE_UI_LED_6;
            #endif
            #if BMC_MAX_LEDS > 6 && defined(BMC_DEVICE_UI_LED_7)
              case 6: return BMC_DEVICE_UI_LED_7;
            #endif
            #if BMC_MAX_LEDS > 7 && defined(BMC_DEVICE_UI_LED_8)
              case 7: return BMC_DEVICE_UI_LED_8;
            #endif
            #if BMC_MAX_LEDS > 8 && defined(BMC_DEVICE_UI_LED_9)
              case 8: return BMC_DEVICE_UI_LED_9;
            #endif
            #if BMC_MAX_LEDS > 9 && defined(BMC_DEVICE_UI_LED_10)
              case 9: return BMC_DEVICE_UI_LED_10;
            #endif
            #if BMC_MAX_LEDS > 10 && defined(BMC_DEVICE_UI_LED_11)
              case 10: return BMC_DEVICE_UI_LED_11;
            #endif
            #if BMC_MAX_LEDS > 11 && defined(BMC_DEVICE_UI_LED_12)
              case 11: return BMC_DEVICE_UI_LED_12;
            #endif
            #if BMC_MAX_LEDS > 12 && defined(BMC_DEVICE_UI_LED_13)
              case 12: return BMC_DEVICE_UI_LED_13;
            #endif
            #if BMC_MAX_LEDS > 13 && defined(BMC_DEVICE_UI_LED_14)
              case 13: return BMC_DEVICE_UI_LED_14;
            #endif
            #if BMC_MAX_LEDS > 14 && defined(BMC_DEVICE_UI_LED_15)
              case 14: return BMC_DEVICE_UI_LED_15;
            #endif
            #if BMC_MAX_LEDS > 15 && defined(BMC_DEVICE_UI_LED_16)
              case 15: return BMC_DEVICE_UI_LED_16;
            #endif
            #if BMC_MAX_LEDS > 16 && defined(BMC_DEVICE_UI_LED_17)
              case 16: return BMC_DEVICE_UI_LED_17;
            #endif
            #if BMC_MAX_LEDS > 17 && defined(BMC_DEVICE_UI_LED_18)
              case 17: return BMC_DEVICE_UI_LED_18;
            #endif
            #if BMC_MAX_LEDS > 18 && defined(BMC_DEVICE_UI_LED_19)
              case 18: return BMC_DEVICE_UI_LED_19;
            #endif
            #if BMC_MAX_LEDS > 19 && defined(BMC_DEVICE_UI_LED_20)
              case 19: return BMC_DEVICE_UI_LED_20;
            #endif
            #if BMC_MAX_LEDS > 20 && defined(BMC_DEVICE_UI_LED_21)
              case 20: return BMC_DEVICE_UI_LED_21;
            #endif
            #if BMC_MAX_LEDS > 21 && defined(BMC_DEVICE_UI_LED_22)
              case 21: return BMC_DEVICE_UI_LED_22;
            #endif
            #if BMC_MAX_LEDS > 22 && defined(BMC_DEVICE_UI_LED_23)
              case 22: return BMC_DEVICE_UI_LED_23;
            #endif
            #if BMC_MAX_LEDS > 23 && defined(BMC_DEVICE_UI_LED_24)
              case 23: return BMC_DEVICE_UI_LED_24;
            #endif
            #if BMC_MAX_LEDS > 24 && defined(BMC_DEVICE_UI_LED_25)
              case 24: return BMC_DEVICE_UI_LED_25;
            #endif
            #if BMC_MAX_LEDS > 25 && defined(BMC_DEVICE_UI_LED_26)
              case 25: return BMC_DEVICE_UI_LED_26;
            #endif
            #if BMC_MAX_LEDS > 26 && defined(BMC_DEVICE_UI_LED_27)
              case 26: return BMC_DEVICE_UI_LED_27;
            #endif
            #if BMC_MAX_LEDS > 27 && defined(BMC_DEVICE_UI_LED_28)
              case 27: return BMC_DEVICE_UI_LED_28;
            #endif
            #if BMC_MAX_LEDS > 28 && defined(BMC_DEVICE_UI_LED_29)
              case 28: return BMC_DEVICE_UI_LED_29;
            #endif
            #if BMC_MAX_LEDS > 29 && defined(BMC_DEVICE_UI_LED_30)
              case 29: return BMC_DEVICE_UI_LED_30;
            #endif
            #if BMC_MAX_LEDS > 30 && defined(BMC_DEVICE_UI_LED_31)
              case 30: return BMC_DEVICE_UI_LED_31;
            #endif
            #if BMC_MAX_LEDS > 31 && defined(BMC_DEVICE_UI_LED_32)
              case 31: return BMC_DEVICE_UI_LED_32;
            #endif
            #if BMC_MAX_LEDS > 32 && defined(BMC_DEVICE_UI_LED_33)
              case 32: return BMC_DEVICE_UI_LED_33;
            #endif
            #if BMC_MAX_LEDS > 33 && defined(BMC_DEVICE_UI_LED_34)
              case 33: return BMC_DEVICE_UI_LED_34;
            #endif
            #if BMC_MAX_LEDS > 34 && defined(BMC_DEVICE_UI_LED_35)
              case 34: return BMC_DEVICE_UI_LED_35;
            #endif
            #if BMC_MAX_LEDS > 35 && defined(BMC_DEVICE_UI_LED_36)
              case 35: return BMC_DEVICE_UI_LED_36;
            #endif
            #if BMC_MAX_LEDS > 36 && defined(BMC_DEVICE_UI_LED_37)
              case 36: return BMC_DEVICE_UI_LED_37;
            #endif
            #if BMC_MAX_LEDS > 37 && defined(BMC_DEVICE_UI_LED_38)
              case 37: return BMC_DEVICE_UI_LED_38;
            #endif
            #if BMC_MAX_LEDS > 38 && defined(BMC_DEVICE_UI_LED_39)
              case 38: return BMC_DEVICE_UI_LED_39;
            #endif
            #if BMC_MAX_LEDS > 39 && defined(BMC_DEVICE_UI_LED_40)
              case 39: return BMC_DEVICE_UI_LED_40;
            #endif
            #if BMC_MAX_LEDS > 40 && defined(BMC_DEVICE_UI_LED_41)
              case 40: return BMC_DEVICE_UI_LED_41;
            #endif
            #if BMC_MAX_LEDS > 41 && defined(BMC_DEVICE_UI_LED_42)
              case 41: return BMC_DEVICE_UI_LED_42;
            #endif
            #if BMC_MAX_LEDS > 42 && defined(BMC_DEVICE_UI_LED_43)
              case 42: return BMC_DEVICE_UI_LED_43;
            #endif
            #if BMC_MAX_LEDS > 43 && defined(BMC_DEVICE_UI_LED_44)
              case 43: return BMC_DEVICE_UI_LED_44;
            #endif
            #if BMC_MAX_LEDS > 44 && defined(BMC_DEVICE_UI_LED_45)
              case 44: return BMC_DEVICE_UI_LED_45;
            #endif
            #if BMC_MAX_LEDS > 45 && defined(BMC_DEVICE_UI_LED_46)
              case 45: return BMC_DEVICE_UI_LED_46;
            #endif
            #if BMC_MAX_LEDS > 46 && defined(BMC_DEVICE_UI_LED_47)
              case 46: return BMC_DEVICE_UI_LED_47;
            #endif
            #if BMC_MAX_LEDS > 47 && defined(BMC_DEVICE_UI_LED_48)
              case 47: return BMC_DEVICE_UI_LED_48;
            #endif
            #if BMC_MAX_LEDS > 48 && defined(BMC_DEVICE_UI_LED_49)
              case 48: return BMC_DEVICE_UI_LED_49;
            #endif
            #if BMC_MAX_LEDS > 49 && defined(BMC_DEVICE_UI_LED_50)
              case 49: return BMC_DEVICE_UI_LED_50;
            #endif
            #if BMC_MAX_LEDS > 50 && defined(BMC_DEVICE_UI_LED_51)
              case 50: return BMC_DEVICE_UI_LED_51;
            #endif
            #if BMC_MAX_LEDS > 51 && defined(BMC_DEVICE_UI_LED_52)
              case 51: return BMC_DEVICE_UI_LED_52;
            #endif
            #if BMC_MAX_LEDS > 52 && defined(BMC_DEVICE_UI_LED_53)
              case 52: return BMC_DEVICE_UI_LED_53;
            #endif
            #if BMC_MAX_LEDS > 53 && defined(BMC_DEVICE_UI_LED_54)
              case 53: return BMC_DEVICE_UI_LED_54;
            #endif
            #if BMC_MAX_LEDS > 54 && defined(BMC_DEVICE_UI_LED_55)
              case 54: return BMC_DEVICE_UI_LED_55;
            #endif
            #if BMC_MAX_LEDS > 55 && defined(BMC_DEVICE_UI_LED_56)
              case 55: return BMC_DEVICE_UI_LED_56;
            #endif
            #if BMC_MAX_LEDS > 56 && defined(BMC_DEVICE_UI_LED_57)
              case 56: return BMC_DEVICE_UI_LED_57;
            #endif
            #if BMC_MAX_LEDS > 57 && defined(BMC_DEVICE_UI_LED_58)
              case 57: return BMC_DEVICE_UI_LED_58;
            #endif
            #if BMC_MAX_LEDS > 58 && defined(BMC_DEVICE_UI_LED_59)
              case 58: return BMC_DEVICE_UI_LED_59;
            #endif
            #if BMC_MAX_LEDS > 59 && defined(BMC_DEVICE_UI_LED_60)
              case 59: return BMC_DEVICE_UI_LED_60;
            #endif
            #if BMC_MAX_LEDS > 60 && defined(BMC_DEVICE_UI_LED_61)
              case 60: return BMC_DEVICE_UI_LED_61;
            #endif
            #if BMC_MAX_LEDS > 61 && defined(BMC_DEVICE_UI_LED_62)
              case 61: return BMC_DEVICE_UI_LED_62;
            #endif
            #if BMC_MAX_LEDS > 62 && defined(BMC_DEVICE_UI_LED_63)
              case 62: return BMC_DEVICE_UI_LED_63;
            #endif
            #if BMC_MAX_LEDS > 63 && defined(BMC_DEVICE_UI_LED_64)
              case 63: return BMC_DEVICE_UI_LED_64;
            #endif
            #if BMC_MAX_LEDS > 64 && defined(BMC_DEVICE_UI_LED_65)
              case 64: return BMC_DEVICE_UI_LED_65;
            #endif
            #if BMC_MAX_LEDS > 65 && defined(BMC_DEVICE_UI_LED_66)
              case 65: return BMC_DEVICE_UI_LED_66;
            #endif
            #if BMC_MAX_LEDS > 66 && defined(BMC_DEVICE_UI_LED_67)
              case 66: return BMC_DEVICE_UI_LED_67;
            #endif
            #if BMC_MAX_LEDS > 67 && defined(BMC_DEVICE_UI_LED_68)
              case 67: return BMC_DEVICE_UI_LED_68;
            #endif
            #if BMC_MAX_LEDS > 68 && defined(BMC_DEVICE_UI_LED_69)
              case 68: return BMC_DEVICE_UI_LED_69;
            #endif
            #if BMC_MAX_LEDS > 69 && defined(BMC_DEVICE_UI_LED_70)
              case 69: return BMC_DEVICE_UI_LED_70;
            #endif
            #if BMC_MAX_LEDS > 70 && defined(BMC_DEVICE_UI_LED_71)
              case 70: return BMC_DEVICE_UI_LED_71;
            #endif
            #if BMC_MAX_LEDS > 71 && defined(BMC_DEVICE_UI_LED_72)
              case 71: return BMC_DEVICE_UI_LED_72;
            #endif
            #if BMC_MAX_LEDS > 72 && defined(BMC_DEVICE_UI_LED_73)
              case 72: return BMC_DEVICE_UI_LED_73;
            #endif
            #if BMC_MAX_LEDS > 73 && defined(BMC_DEVICE_UI_LED_74)
              case 73: return BMC_DEVICE_UI_LED_74;
            #endif
            #if BMC_MAX_LEDS > 74 && defined(BMC_DEVICE_UI_LED_75)
              case 74: return BMC_DEVICE_UI_LED_75;
            #endif
            #if BMC_MAX_LEDS > 75 && defined(BMC_DEVICE_UI_LED_76)
              case 75: return BMC_DEVICE_UI_LED_76;
            #endif
            #if BMC_MAX_LEDS > 76 && defined(BMC_DEVICE_UI_LED_77)
              case 76: return BMC_DEVICE_UI_LED_77;
            #endif
            #if BMC_MAX_LEDS > 77 && defined(BMC_DEVICE_UI_LED_78)
              case 77: return BMC_DEVICE_UI_LED_78;
            #endif
            #if BMC_MAX_LEDS > 78 && defined(BMC_DEVICE_UI_LED_79)
              case 78: return BMC_DEVICE_UI_LED_79;
            #endif
            #if BMC_MAX_LEDS > 79 && defined(BMC_DEVICE_UI_LED_80)
              case 79: return BMC_DEVICE_UI_LED_80;
            #endif
            #if BMC_MAX_LEDS > 80 && defined(BMC_DEVICE_UI_LED_81)
              case 80: return BMC_DEVICE_UI_LED_81;
            #endif
            #if BMC_MAX_LEDS > 81 && defined(BMC_DEVICE_UI_LED_82)
              case 81: return BMC_DEVICE_UI_LED_82;
            #endif
            #if BMC_MAX_LEDS > 82 && defined(BMC_DEVICE_UI_LED_83)
              case 82: return BMC_DEVICE_UI_LED_83;
            #endif
            #if BMC_MAX_LEDS > 83 && defined(BMC_DEVICE_UI_LED_84)
              case 83: return BMC_DEVICE_UI_LED_84;
            #endif
            #if BMC_MAX_LEDS > 84 && defined(BMC_DEVICE_UI_LED_85)
              case 84: return BMC_DEVICE_UI_LED_85;
            #endif
            #if BMC_MAX_LEDS > 85 && defined(BMC_DEVICE_UI_LED_86)
              case 85: return BMC_DEVICE_UI_LED_86;
            #endif
            #if BMC_MAX_LEDS > 86 && defined(BMC_DEVICE_UI_LED_87)
              case 86: return BMC_DEVICE_UI_LED_87;
            #endif
            #if BMC_MAX_LEDS > 87 && defined(BMC_DEVICE_UI_LED_88)
              case 87: return BMC_DEVICE_UI_LED_88;
            #endif
            #if BMC_MAX_LEDS > 88 && defined(BMC_DEVICE_UI_LED_89)
              case 88: return BMC_DEVICE_UI_LED_89;
            #endif
            #if BMC_MAX_LEDS > 89 && defined(BMC_DEVICE_UI_LED_90)
              case 89: return BMC_DEVICE_UI_LED_90;
            #endif
            #if BMC_MAX_LEDS > 90 && defined(BMC_DEVICE_UI_LED_91)
              case 90: return BMC_DEVICE_UI_LED_91;
            #endif
            #if BMC_MAX_LEDS > 91 && defined(BMC_DEVICE_UI_LED_92)
              case 91: return BMC_DEVICE_UI_LED_92;
            #endif
            #if BMC_MAX_LEDS > 92 && defined(BMC_DEVICE_UI_LED_93)
              case 92: return BMC_DEVICE_UI_LED_93;
            #endif
            #if BMC_MAX_LEDS > 93 && defined(BMC_DEVICE_UI_LED_94)
              case 93: return BMC_DEVICE_UI_LED_94;
            #endif
            #if BMC_MAX_LEDS > 94 && defined(BMC_DEVICE_UI_LED_95)
              case 94: return BMC_DEVICE_UI_LED_95;
            #endif
            #if BMC_MAX_LEDS > 95 && defined(BMC_DEVICE_UI_LED_96)
              case 95: return BMC_DEVICE_UI_LED_96;
            #endif
            #if BMC_MAX_LEDS > 96 && defined(BMC_DEVICE_UI_LED_97)
              case 96: return BMC_DEVICE_UI_LED_97;
            #endif
            #if BMC_MAX_LEDS > 97 && defined(BMC_DEVICE_UI_LED_98)
              case 97: return BMC_DEVICE_UI_LED_98;
            #endif
            #if BMC_MAX_LEDS > 98 && defined(BMC_DEVICE_UI_LED_99)
              case 98: return BMC_DEVICE_UI_LED_99;
            #endif
            #if BMC_MAX_LEDS > 99 && defined(BMC_DEVICE_UI_LED_100)
              case 99: return BMC_DEVICE_UI_LED_100;
            #endif
            #if BMC_MAX_LEDS > 100 && defined(BMC_DEVICE_UI_LED_101)
              case 100: return BMC_DEVICE_UI_LED_101;
            #endif
            #if BMC_MAX_LEDS > 101 && defined(BMC_DEVICE_UI_LED_102)
              case 101: return BMC_DEVICE_UI_LED_102;
            #endif
            #if BMC_MAX_LEDS > 102 && defined(BMC_DEVICE_UI_LED_103)
              case 102: return BMC_DEVICE_UI_LED_103;
            #endif
            #if BMC_MAX_LEDS > 103 && defined(BMC_DEVICE_UI_LED_104)
              case 103: return BMC_DEVICE_UI_LED_104;
            #endif
            #if BMC_MAX_LEDS > 104 && defined(BMC_DEVICE_UI_LED_105)
              case 104: return BMC_DEVICE_UI_LED_105;
            #endif
            #if BMC_MAX_LEDS > 105 && defined(BMC_DEVICE_UI_LED_106)
              case 105: return BMC_DEVICE_UI_LED_106;
            #endif
            #if BMC_MAX_LEDS > 106 && defined(BMC_DEVICE_UI_LED_107)
              case 106: return BMC_DEVICE_UI_LED_107;
            #endif
            #if BMC_MAX_LEDS > 107 && defined(BMC_DEVICE_UI_LED_108)
              case 107: return BMC_DEVICE_UI_LED_108;
            #endif
            #if BMC_MAX_LEDS > 108 && defined(BMC_DEVICE_UI_LED_109)
              case 108: return BMC_DEVICE_UI_LED_109;
            #endif
            #if BMC_MAX_LEDS > 109 && defined(BMC_DEVICE_UI_LED_110)
              case 109: return BMC_DEVICE_UI_LED_110;
            #endif
            #if BMC_MAX_LEDS > 110 && defined(BMC_DEVICE_UI_LED_111)
              case 110: return BMC_DEVICE_UI_LED_111;
            #endif
            #if BMC_MAX_LEDS > 111 && defined(BMC_DEVICE_UI_LED_112)
              case 111: return BMC_DEVICE_UI_LED_112;
            #endif
            #if BMC_MAX_LEDS > 112 && defined(BMC_DEVICE_UI_LED_113)
              case 112: return BMC_DEVICE_UI_LED_113;
            #endif
            #if BMC_MAX_LEDS > 113 && defined(BMC_DEVICE_UI_LED_114)
              case 113: return BMC_DEVICE_UI_LED_114;
            #endif
            #if BMC_MAX_LEDS > 114 && defined(BMC_DEVICE_UI_LED_115)
              case 114: return BMC_DEVICE_UI_LED_115;
            #endif
            #if BMC_MAX_LEDS > 115 && defined(BMC_DEVICE_UI_LED_116)
              case 115: return BMC_DEVICE_UI_LED_116;
            #endif
            #if BMC_MAX_LEDS > 116 && defined(BMC_DEVICE_UI_LED_117)
              case 116: return BMC_DEVICE_UI_LED_117;
            #endif
            #if BMC_MAX_LEDS > 117 && defined(BMC_DEVICE_UI_LED_118)
              case 117: return BMC_DEVICE_UI_LED_118;
            #endif
            #if BMC_MAX_LEDS > 118 && defined(BMC_DEVICE_UI_LED_119)
              case 118: return BMC_DEVICE_UI_LED_119;
            #endif
            #if BMC_MAX_LEDS > 119 && defined(BMC_DEVICE_UI_LED_120)
              case 119: return BMC_DEVICE_UI_LED_120;
            #endif
            #if BMC_MAX_LEDS > 120 && defined(BMC_DEVICE_UI_LED_121)
              case 120: return BMC_DEVICE_UI_LED_121;
            #endif
            #if BMC_MAX_LEDS > 121 && defined(BMC_DEVICE_UI_LED_122)
              case 121: return BMC_DEVICE_UI_LED_122;
            #endif
            #if BMC_MAX_LEDS > 122 && defined(BMC_DEVICE_UI_LED_123)
              case 122: return BMC_DEVICE_UI_LED_123;
            #endif
            #if BMC_MAX_LEDS > 123 && defined(BMC_DEVICE_UI_LED_124)
              case 123: return BMC_DEVICE_UI_LED_124;
            #endif
            #if BMC_MAX_LEDS > 124 && defined(BMC_DEVICE_UI_LED_125)
              case 124: return BMC_DEVICE_UI_LED_125;
            #endif
            #if BMC_MAX_LEDS > 125 && defined(BMC_DEVICE_UI_LED_126)
              case 125: return BMC_DEVICE_UI_LED_126;
            #endif
            #if BMC_MAX_LEDS > 126 && defined(BMC_DEVICE_UI_LED_127)
              case 126: return BMC_DEVICE_UI_LED_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_LED:
          #if BMC_MAX_GLOBAL_LEDS > 0
            switch(n){
              #if BMC_MAX_GLOBAL_LEDS > 0 && defined(BMC_DEVICE_UI_GLOBAL_LED_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_LED_1;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 1 && defined(BMC_DEVICE_UI_GLOBAL_LED_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_LED_2;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 2 && defined(BMC_DEVICE_UI_GLOBAL_LED_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_LED_3;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 3 && defined(BMC_DEVICE_UI_GLOBAL_LED_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_LED_4;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 4 && defined(BMC_DEVICE_UI_GLOBAL_LED_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_LED_5;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 5 && defined(BMC_DEVICE_UI_GLOBAL_LED_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_LED_6;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 6 && defined(BMC_DEVICE_UI_GLOBAL_LED_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_LED_7;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 7 && defined(BMC_DEVICE_UI_GLOBAL_LED_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_LED_8;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 8 && defined(BMC_DEVICE_UI_GLOBAL_LED_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_LED_9;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 9 && defined(BMC_DEVICE_UI_GLOBAL_LED_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_LED_10;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 10 && defined(BMC_DEVICE_UI_GLOBAL_LED_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_LED_11;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 11 && defined(BMC_DEVICE_UI_GLOBAL_LED_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_LED_12;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 12 && defined(BMC_DEVICE_UI_GLOBAL_LED_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_LED_13;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 13 && defined(BMC_DEVICE_UI_GLOBAL_LED_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_LED_14;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 14 && defined(BMC_DEVICE_UI_GLOBAL_LED_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_LED_15;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 15 && defined(BMC_DEVICE_UI_GLOBAL_LED_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_LED_16;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 16 && defined(BMC_DEVICE_UI_GLOBAL_LED_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_LED_17;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 17 && defined(BMC_DEVICE_UI_GLOBAL_LED_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_LED_18;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 18 && defined(BMC_DEVICE_UI_GLOBAL_LED_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_LED_19;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 19 && defined(BMC_DEVICE_UI_GLOBAL_LED_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_LED_20;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 20 && defined(BMC_DEVICE_UI_GLOBAL_LED_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_LED_21;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 21 && defined(BMC_DEVICE_UI_GLOBAL_LED_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_LED_22;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 22 && defined(BMC_DEVICE_UI_GLOBAL_LED_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_LED_23;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 23 && defined(BMC_DEVICE_UI_GLOBAL_LED_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_LED_24;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 24 && defined(BMC_DEVICE_UI_GLOBAL_LED_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_LED_25;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 25 && defined(BMC_DEVICE_UI_GLOBAL_LED_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_LED_26;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 26 && defined(BMC_DEVICE_UI_GLOBAL_LED_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_LED_27;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 27 && defined(BMC_DEVICE_UI_GLOBAL_LED_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_LED_28;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 28 && defined(BMC_DEVICE_UI_GLOBAL_LED_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_LED_29;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 29 && defined(BMC_DEVICE_UI_GLOBAL_LED_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_LED_30;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 30 && defined(BMC_DEVICE_UI_GLOBAL_LED_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_LED_31;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 31 && defined(BMC_DEVICE_UI_GLOBAL_LED_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_LED_32;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 32 && defined(BMC_DEVICE_UI_GLOBAL_LED_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_LED_33;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 33 && defined(BMC_DEVICE_UI_GLOBAL_LED_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_LED_34;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 34 && defined(BMC_DEVICE_UI_GLOBAL_LED_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_LED_35;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 35 && defined(BMC_DEVICE_UI_GLOBAL_LED_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_LED_36;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 36 && defined(BMC_DEVICE_UI_GLOBAL_LED_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_LED_37;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 37 && defined(BMC_DEVICE_UI_GLOBAL_LED_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_LED_38;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 38 && defined(BMC_DEVICE_UI_GLOBAL_LED_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_LED_39;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 39 && defined(BMC_DEVICE_UI_GLOBAL_LED_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_LED_40;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 40 && defined(BMC_DEVICE_UI_GLOBAL_LED_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_LED_41;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 41 && defined(BMC_DEVICE_UI_GLOBAL_LED_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_LED_42;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 42 && defined(BMC_DEVICE_UI_GLOBAL_LED_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_LED_43;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 43 && defined(BMC_DEVICE_UI_GLOBAL_LED_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_LED_44;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 44 && defined(BMC_DEVICE_UI_GLOBAL_LED_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_LED_45;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 45 && defined(BMC_DEVICE_UI_GLOBAL_LED_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_LED_46;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 46 && defined(BMC_DEVICE_UI_GLOBAL_LED_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_LED_47;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 47 && defined(BMC_DEVICE_UI_GLOBAL_LED_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_LED_48;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 48 && defined(BMC_DEVICE_UI_GLOBAL_LED_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_LED_49;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 49 && defined(BMC_DEVICE_UI_GLOBAL_LED_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_LED_50;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 50 && defined(BMC_DEVICE_UI_GLOBAL_LED_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_LED_51;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 51 && defined(BMC_DEVICE_UI_GLOBAL_LED_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_LED_52;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 52 && defined(BMC_DEVICE_UI_GLOBAL_LED_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_LED_53;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 53 && defined(BMC_DEVICE_UI_GLOBAL_LED_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_LED_54;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 54 && defined(BMC_DEVICE_UI_GLOBAL_LED_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_LED_55;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 55 && defined(BMC_DEVICE_UI_GLOBAL_LED_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_LED_56;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 56 && defined(BMC_DEVICE_UI_GLOBAL_LED_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_LED_57;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 57 && defined(BMC_DEVICE_UI_GLOBAL_LED_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_LED_58;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 58 && defined(BMC_DEVICE_UI_GLOBAL_LED_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_LED_59;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 59 && defined(BMC_DEVICE_UI_GLOBAL_LED_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_LED_60;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 60 && defined(BMC_DEVICE_UI_GLOBAL_LED_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_LED_61;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 61 && defined(BMC_DEVICE_UI_GLOBAL_LED_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_LED_62;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 62 && defined(BMC_DEVICE_UI_GLOBAL_LED_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_LED_63;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 63 && defined(BMC_DEVICE_UI_GLOBAL_LED_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_LED_64;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 64 && defined(BMC_DEVICE_UI_GLOBAL_LED_65)
              case 64: return BMC_DEVICE_UI_GLOBAL_LED_65;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 65 && defined(BMC_DEVICE_UI_GLOBAL_LED_66)
              case 65: return BMC_DEVICE_UI_GLOBAL_LED_66;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 66 && defined(BMC_DEVICE_UI_GLOBAL_LED_67)
              case 66: return BMC_DEVICE_UI_GLOBAL_LED_67;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 67 && defined(BMC_DEVICE_UI_GLOBAL_LED_68)
              case 67: return BMC_DEVICE_UI_GLOBAL_LED_68;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 68 && defined(BMC_DEVICE_UI_GLOBAL_LED_69)
              case 68: return BMC_DEVICE_UI_GLOBAL_LED_69;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 69 && defined(BMC_DEVICE_UI_GLOBAL_LED_70)
              case 69: return BMC_DEVICE_UI_GLOBAL_LED_70;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 70 && defined(BMC_DEVICE_UI_GLOBAL_LED_71)
              case 70: return BMC_DEVICE_UI_GLOBAL_LED_71;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 71 && defined(BMC_DEVICE_UI_GLOBAL_LED_72)
              case 71: return BMC_DEVICE_UI_GLOBAL_LED_72;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 72 && defined(BMC_DEVICE_UI_GLOBAL_LED_73)
              case 72: return BMC_DEVICE_UI_GLOBAL_LED_73;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 73 && defined(BMC_DEVICE_UI_GLOBAL_LED_74)
              case 73: return BMC_DEVICE_UI_GLOBAL_LED_74;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 74 && defined(BMC_DEVICE_UI_GLOBAL_LED_75)
              case 74: return BMC_DEVICE_UI_GLOBAL_LED_75;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 75 && defined(BMC_DEVICE_UI_GLOBAL_LED_76)
              case 75: return BMC_DEVICE_UI_GLOBAL_LED_76;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 76 && defined(BMC_DEVICE_UI_GLOBAL_LED_77)
              case 76: return BMC_DEVICE_UI_GLOBAL_LED_77;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 77 && defined(BMC_DEVICE_UI_GLOBAL_LED_78)
              case 77: return BMC_DEVICE_UI_GLOBAL_LED_78;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 78 && defined(BMC_DEVICE_UI_GLOBAL_LED_79)
              case 78: return BMC_DEVICE_UI_GLOBAL_LED_79;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 79 && defined(BMC_DEVICE_UI_GLOBAL_LED_80)
              case 79: return BMC_DEVICE_UI_GLOBAL_LED_80;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 80 && defined(BMC_DEVICE_UI_GLOBAL_LED_81)
              case 80: return BMC_DEVICE_UI_GLOBAL_LED_81;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 81 && defined(BMC_DEVICE_UI_GLOBAL_LED_82)
              case 81: return BMC_DEVICE_UI_GLOBAL_LED_82;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 82 && defined(BMC_DEVICE_UI_GLOBAL_LED_83)
              case 82: return BMC_DEVICE_UI_GLOBAL_LED_83;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 83 && defined(BMC_DEVICE_UI_GLOBAL_LED_84)
              case 83: return BMC_DEVICE_UI_GLOBAL_LED_84;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 84 && defined(BMC_DEVICE_UI_GLOBAL_LED_85)
              case 84: return BMC_DEVICE_UI_GLOBAL_LED_85;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 85 && defined(BMC_DEVICE_UI_GLOBAL_LED_86)
              case 85: return BMC_DEVICE_UI_GLOBAL_LED_86;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 86 && defined(BMC_DEVICE_UI_GLOBAL_LED_87)
              case 86: return BMC_DEVICE_UI_GLOBAL_LED_87;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 87 && defined(BMC_DEVICE_UI_GLOBAL_LED_88)
              case 87: return BMC_DEVICE_UI_GLOBAL_LED_88;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 88 && defined(BMC_DEVICE_UI_GLOBAL_LED_89)
              case 88: return BMC_DEVICE_UI_GLOBAL_LED_89;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 89 && defined(BMC_DEVICE_UI_GLOBAL_LED_90)
              case 89: return BMC_DEVICE_UI_GLOBAL_LED_90;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 90 && defined(BMC_DEVICE_UI_GLOBAL_LED_91)
              case 90: return BMC_DEVICE_UI_GLOBAL_LED_91;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 91 && defined(BMC_DEVICE_UI_GLOBAL_LED_92)
              case 91: return BMC_DEVICE_UI_GLOBAL_LED_92;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 92 && defined(BMC_DEVICE_UI_GLOBAL_LED_93)
              case 92: return BMC_DEVICE_UI_GLOBAL_LED_93;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 93 && defined(BMC_DEVICE_UI_GLOBAL_LED_94)
              case 93: return BMC_DEVICE_UI_GLOBAL_LED_94;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 94 && defined(BMC_DEVICE_UI_GLOBAL_LED_95)
              case 94: return BMC_DEVICE_UI_GLOBAL_LED_95;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 95 && defined(BMC_DEVICE_UI_GLOBAL_LED_96)
              case 95: return BMC_DEVICE_UI_GLOBAL_LED_96;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 96 && defined(BMC_DEVICE_UI_GLOBAL_LED_97)
              case 96: return BMC_DEVICE_UI_GLOBAL_LED_97;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 97 && defined(BMC_DEVICE_UI_GLOBAL_LED_98)
              case 97: return BMC_DEVICE_UI_GLOBAL_LED_98;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 98 && defined(BMC_DEVICE_UI_GLOBAL_LED_99)
              case 98: return BMC_DEVICE_UI_GLOBAL_LED_99;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 99 && defined(BMC_DEVICE_UI_GLOBAL_LED_100)
              case 99: return BMC_DEVICE_UI_GLOBAL_LED_100;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 100 && defined(BMC_DEVICE_UI_GLOBAL_LED_101)
              case 100: return BMC_DEVICE_UI_GLOBAL_LED_101;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 101 && defined(BMC_DEVICE_UI_GLOBAL_LED_102)
              case 101: return BMC_DEVICE_UI_GLOBAL_LED_102;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 102 && defined(BMC_DEVICE_UI_GLOBAL_LED_103)
              case 102: return BMC_DEVICE_UI_GLOBAL_LED_103;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 103 && defined(BMC_DEVICE_UI_GLOBAL_LED_104)
              case 103: return BMC_DEVICE_UI_GLOBAL_LED_104;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 104 && defined(BMC_DEVICE_UI_GLOBAL_LED_105)
              case 104: return BMC_DEVICE_UI_GLOBAL_LED_105;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 105 && defined(BMC_DEVICE_UI_GLOBAL_LED_106)
              case 105: return BMC_DEVICE_UI_GLOBAL_LED_106;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 106 && defined(BMC_DEVICE_UI_GLOBAL_LED_107)
              case 106: return BMC_DEVICE_UI_GLOBAL_LED_107;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 107 && defined(BMC_DEVICE_UI_GLOBAL_LED_108)
              case 107: return BMC_DEVICE_UI_GLOBAL_LED_108;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 108 && defined(BMC_DEVICE_UI_GLOBAL_LED_109)
              case 108: return BMC_DEVICE_UI_GLOBAL_LED_109;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 109 && defined(BMC_DEVICE_UI_GLOBAL_LED_110)
              case 109: return BMC_DEVICE_UI_GLOBAL_LED_110;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 110 && defined(BMC_DEVICE_UI_GLOBAL_LED_111)
              case 110: return BMC_DEVICE_UI_GLOBAL_LED_111;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 111 && defined(BMC_DEVICE_UI_GLOBAL_LED_112)
              case 111: return BMC_DEVICE_UI_GLOBAL_LED_112;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 112 && defined(BMC_DEVICE_UI_GLOBAL_LED_113)
              case 112: return BMC_DEVICE_UI_GLOBAL_LED_113;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 113 && defined(BMC_DEVICE_UI_GLOBAL_LED_114)
              case 113: return BMC_DEVICE_UI_GLOBAL_LED_114;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 114 && defined(BMC_DEVICE_UI_GLOBAL_LED_115)
              case 114: return BMC_DEVICE_UI_GLOBAL_LED_115;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 115 && defined(BMC_DEVICE_UI_GLOBAL_LED_116)
              case 115: return BMC_DEVICE_UI_GLOBAL_LED_116;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 116 && defined(BMC_DEVICE_UI_GLOBAL_LED_117)
              case 116: return BMC_DEVICE_UI_GLOBAL_LED_117;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 117 && defined(BMC_DEVICE_UI_GLOBAL_LED_118)
              case 117: return BMC_DEVICE_UI_GLOBAL_LED_118;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 118 && defined(BMC_DEVICE_UI_GLOBAL_LED_119)
              case 118: return BMC_DEVICE_UI_GLOBAL_LED_119;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 119 && defined(BMC_DEVICE_UI_GLOBAL_LED_120)
              case 119: return BMC_DEVICE_UI_GLOBAL_LED_120;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 120 && defined(BMC_DEVICE_UI_GLOBAL_LED_121)
              case 120: return BMC_DEVICE_UI_GLOBAL_LED_121;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 121 && defined(BMC_DEVICE_UI_GLOBAL_LED_122)
              case 121: return BMC_DEVICE_UI_GLOBAL_LED_122;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 122 && defined(BMC_DEVICE_UI_GLOBAL_LED_123)
              case 122: return BMC_DEVICE_UI_GLOBAL_LED_123;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 123 && defined(BMC_DEVICE_UI_GLOBAL_LED_124)
              case 123: return BMC_DEVICE_UI_GLOBAL_LED_124;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 124 && defined(BMC_DEVICE_UI_GLOBAL_LED_125)
              case 124: return BMC_DEVICE_UI_GLOBAL_LED_125;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 125 && defined(BMC_DEVICE_UI_GLOBAL_LED_126)
              case 125: return BMC_DEVICE_UI_GLOBAL_LED_126;
            #endif
            #if BMC_MAX_GLOBAL_LEDS > 126 && defined(BMC_DEVICE_UI_GLOBAL_LED_127)
              case 126: return BMC_DEVICE_UI_GLOBAL_LED_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_PIXEL:
          #if BMC_MAX_PIXELS > 0
            switch(n){
              #if BMC_MAX_PIXELS > 0 && defined(BMC_DEVICE_UI_PIXEL_1)
              case 0: return BMC_DEVICE_UI_PIXEL_1;
            #endif
            #if BMC_MAX_PIXELS > 1 && defined(BMC_DEVICE_UI_PIXEL_2)
              case 1: return BMC_DEVICE_UI_PIXEL_2;
            #endif
            #if BMC_MAX_PIXELS > 2 && defined(BMC_DEVICE_UI_PIXEL_3)
              case 2: return BMC_DEVICE_UI_PIXEL_3;
            #endif
            #if BMC_MAX_PIXELS > 3 && defined(BMC_DEVICE_UI_PIXEL_4)
              case 3: return BMC_DEVICE_UI_PIXEL_4;
            #endif
            #if BMC_MAX_PIXELS > 4 && defined(BMC_DEVICE_UI_PIXEL_5)
              case 4: return BMC_DEVICE_UI_PIXEL_5;
            #endif
            #if BMC_MAX_PIXELS > 5 && defined(BMC_DEVICE_UI_PIXEL_6)
              case 5: return BMC_DEVICE_UI_PIXEL_6;
            #endif
            #if BMC_MAX_PIXELS > 6 && defined(BMC_DEVICE_UI_PIXEL_7)
              case 6: return BMC_DEVICE_UI_PIXEL_7;
            #endif
            #if BMC_MAX_PIXELS > 7 && defined(BMC_DEVICE_UI_PIXEL_8)
              case 7: return BMC_DEVICE_UI_PIXEL_8;
            #endif
            #if BMC_MAX_PIXELS > 8 && defined(BMC_DEVICE_UI_PIXEL_9)
              case 8: return BMC_DEVICE_UI_PIXEL_9;
            #endif
            #if BMC_MAX_PIXELS > 9 && defined(BMC_DEVICE_UI_PIXEL_10)
              case 9: return BMC_DEVICE_UI_PIXEL_10;
            #endif
            #if BMC_MAX_PIXELS > 10 && defined(BMC_DEVICE_UI_PIXEL_11)
              case 10: return BMC_DEVICE_UI_PIXEL_11;
            #endif
            #if BMC_MAX_PIXELS > 11 && defined(BMC_DEVICE_UI_PIXEL_12)
              case 11: return BMC_DEVICE_UI_PIXEL_12;
            #endif
            #if BMC_MAX_PIXELS > 12 && defined(BMC_DEVICE_UI_PIXEL_13)
              case 12: return BMC_DEVICE_UI_PIXEL_13;
            #endif
            #if BMC_MAX_PIXELS > 13 && defined(BMC_DEVICE_UI_PIXEL_14)
              case 13: return BMC_DEVICE_UI_PIXEL_14;
            #endif
            #if BMC_MAX_PIXELS > 14 && defined(BMC_DEVICE_UI_PIXEL_15)
              case 14: return BMC_DEVICE_UI_PIXEL_15;
            #endif
            #if BMC_MAX_PIXELS > 15 && defined(BMC_DEVICE_UI_PIXEL_16)
              case 15: return BMC_DEVICE_UI_PIXEL_16;
            #endif
            #if BMC_MAX_PIXELS > 16 && defined(BMC_DEVICE_UI_PIXEL_17)
              case 16: return BMC_DEVICE_UI_PIXEL_17;
            #endif
            #if BMC_MAX_PIXELS > 17 && defined(BMC_DEVICE_UI_PIXEL_18)
              case 17: return BMC_DEVICE_UI_PIXEL_18;
            #endif
            #if BMC_MAX_PIXELS > 18 && defined(BMC_DEVICE_UI_PIXEL_19)
              case 18: return BMC_DEVICE_UI_PIXEL_19;
            #endif
            #if BMC_MAX_PIXELS > 19 && defined(BMC_DEVICE_UI_PIXEL_20)
              case 19: return BMC_DEVICE_UI_PIXEL_20;
            #endif
            #if BMC_MAX_PIXELS > 20 && defined(BMC_DEVICE_UI_PIXEL_21)
              case 20: return BMC_DEVICE_UI_PIXEL_21;
            #endif
            #if BMC_MAX_PIXELS > 21 && defined(BMC_DEVICE_UI_PIXEL_22)
              case 21: return BMC_DEVICE_UI_PIXEL_22;
            #endif
            #if BMC_MAX_PIXELS > 22 && defined(BMC_DEVICE_UI_PIXEL_23)
              case 22: return BMC_DEVICE_UI_PIXEL_23;
            #endif
            #if BMC_MAX_PIXELS > 23 && defined(BMC_DEVICE_UI_PIXEL_24)
              case 23: return BMC_DEVICE_UI_PIXEL_24;
            #endif
            #if BMC_MAX_PIXELS > 24 && defined(BMC_DEVICE_UI_PIXEL_25)
              case 24: return BMC_DEVICE_UI_PIXEL_25;
            #endif
            #if BMC_MAX_PIXELS > 25 && defined(BMC_DEVICE_UI_PIXEL_26)
              case 25: return BMC_DEVICE_UI_PIXEL_26;
            #endif
            #if BMC_MAX_PIXELS > 26 && defined(BMC_DEVICE_UI_PIXEL_27)
              case 26: return BMC_DEVICE_UI_PIXEL_27;
            #endif
            #if BMC_MAX_PIXELS > 27 && defined(BMC_DEVICE_UI_PIXEL_28)
              case 27: return BMC_DEVICE_UI_PIXEL_28;
            #endif
            #if BMC_MAX_PIXELS > 28 && defined(BMC_DEVICE_UI_PIXEL_29)
              case 28: return BMC_DEVICE_UI_PIXEL_29;
            #endif
            #if BMC_MAX_PIXELS > 29 && defined(BMC_DEVICE_UI_PIXEL_30)
              case 29: return BMC_DEVICE_UI_PIXEL_30;
            #endif
            #if BMC_MAX_PIXELS > 30 && defined(BMC_DEVICE_UI_PIXEL_31)
              case 30: return BMC_DEVICE_UI_PIXEL_31;
            #endif
            #if BMC_MAX_PIXELS > 31 && defined(BMC_DEVICE_UI_PIXEL_32)
              case 31: return BMC_DEVICE_UI_PIXEL_32;
            #endif
            #if BMC_MAX_PIXELS > 32 && defined(BMC_DEVICE_UI_PIXEL_33)
              case 32: return BMC_DEVICE_UI_PIXEL_33;
            #endif
            #if BMC_MAX_PIXELS > 33 && defined(BMC_DEVICE_UI_PIXEL_34)
              case 33: return BMC_DEVICE_UI_PIXEL_34;
            #endif
            #if BMC_MAX_PIXELS > 34 && defined(BMC_DEVICE_UI_PIXEL_35)
              case 34: return BMC_DEVICE_UI_PIXEL_35;
            #endif
            #if BMC_MAX_PIXELS > 35 && defined(BMC_DEVICE_UI_PIXEL_36)
              case 35: return BMC_DEVICE_UI_PIXEL_36;
            #endif
            #if BMC_MAX_PIXELS > 36 && defined(BMC_DEVICE_UI_PIXEL_37)
              case 36: return BMC_DEVICE_UI_PIXEL_37;
            #endif
            #if BMC_MAX_PIXELS > 37 && defined(BMC_DEVICE_UI_PIXEL_38)
              case 37: return BMC_DEVICE_UI_PIXEL_38;
            #endif
            #if BMC_MAX_PIXELS > 38 && defined(BMC_DEVICE_UI_PIXEL_39)
              case 38: return BMC_DEVICE_UI_PIXEL_39;
            #endif
            #if BMC_MAX_PIXELS > 39 && defined(BMC_DEVICE_UI_PIXEL_40)
              case 39: return BMC_DEVICE_UI_PIXEL_40;
            #endif
            #if BMC_MAX_PIXELS > 40 && defined(BMC_DEVICE_UI_PIXEL_41)
              case 40: return BMC_DEVICE_UI_PIXEL_41;
            #endif
            #if BMC_MAX_PIXELS > 41 && defined(BMC_DEVICE_UI_PIXEL_42)
              case 41: return BMC_DEVICE_UI_PIXEL_42;
            #endif
            #if BMC_MAX_PIXELS > 42 && defined(BMC_DEVICE_UI_PIXEL_43)
              case 42: return BMC_DEVICE_UI_PIXEL_43;
            #endif
            #if BMC_MAX_PIXELS > 43 && defined(BMC_DEVICE_UI_PIXEL_44)
              case 43: return BMC_DEVICE_UI_PIXEL_44;
            #endif
            #if BMC_MAX_PIXELS > 44 && defined(BMC_DEVICE_UI_PIXEL_45)
              case 44: return BMC_DEVICE_UI_PIXEL_45;
            #endif
            #if BMC_MAX_PIXELS > 45 && defined(BMC_DEVICE_UI_PIXEL_46)
              case 45: return BMC_DEVICE_UI_PIXEL_46;
            #endif
            #if BMC_MAX_PIXELS > 46 && defined(BMC_DEVICE_UI_PIXEL_47)
              case 46: return BMC_DEVICE_UI_PIXEL_47;
            #endif
            #if BMC_MAX_PIXELS > 47 && defined(BMC_DEVICE_UI_PIXEL_48)
              case 47: return BMC_DEVICE_UI_PIXEL_48;
            #endif
            #if BMC_MAX_PIXELS > 48 && defined(BMC_DEVICE_UI_PIXEL_49)
              case 48: return BMC_DEVICE_UI_PIXEL_49;
            #endif
            #if BMC_MAX_PIXELS > 49 && defined(BMC_DEVICE_UI_PIXEL_50)
              case 49: return BMC_DEVICE_UI_PIXEL_50;
            #endif
            #if BMC_MAX_PIXELS > 50 && defined(BMC_DEVICE_UI_PIXEL_51)
              case 50: return BMC_DEVICE_UI_PIXEL_51;
            #endif
            #if BMC_MAX_PIXELS > 51 && defined(BMC_DEVICE_UI_PIXEL_52)
              case 51: return BMC_DEVICE_UI_PIXEL_52;
            #endif
            #if BMC_MAX_PIXELS > 52 && defined(BMC_DEVICE_UI_PIXEL_53)
              case 52: return BMC_DEVICE_UI_PIXEL_53;
            #endif
            #if BMC_MAX_PIXELS > 53 && defined(BMC_DEVICE_UI_PIXEL_54)
              case 53: return BMC_DEVICE_UI_PIXEL_54;
            #endif
            #if BMC_MAX_PIXELS > 54 && defined(BMC_DEVICE_UI_PIXEL_55)
              case 54: return BMC_DEVICE_UI_PIXEL_55;
            #endif
            #if BMC_MAX_PIXELS > 55 && defined(BMC_DEVICE_UI_PIXEL_56)
              case 55: return BMC_DEVICE_UI_PIXEL_56;
            #endif
            #if BMC_MAX_PIXELS > 56 && defined(BMC_DEVICE_UI_PIXEL_57)
              case 56: return BMC_DEVICE_UI_PIXEL_57;
            #endif
            #if BMC_MAX_PIXELS > 57 && defined(BMC_DEVICE_UI_PIXEL_58)
              case 57: return BMC_DEVICE_UI_PIXEL_58;
            #endif
            #if BMC_MAX_PIXELS > 58 && defined(BMC_DEVICE_UI_PIXEL_59)
              case 58: return BMC_DEVICE_UI_PIXEL_59;
            #endif
            #if BMC_MAX_PIXELS > 59 && defined(BMC_DEVICE_UI_PIXEL_60)
              case 59: return BMC_DEVICE_UI_PIXEL_60;
            #endif
            #if BMC_MAX_PIXELS > 60 && defined(BMC_DEVICE_UI_PIXEL_61)
              case 60: return BMC_DEVICE_UI_PIXEL_61;
            #endif
            #if BMC_MAX_PIXELS > 61 && defined(BMC_DEVICE_UI_PIXEL_62)
              case 61: return BMC_DEVICE_UI_PIXEL_62;
            #endif
            #if BMC_MAX_PIXELS > 62 && defined(BMC_DEVICE_UI_PIXEL_63)
              case 62: return BMC_DEVICE_UI_PIXEL_63;
            #endif
            #if BMC_MAX_PIXELS > 63 && defined(BMC_DEVICE_UI_PIXEL_64)
              case 63: return BMC_DEVICE_UI_PIXEL_64;
            #endif
            #if BMC_MAX_PIXELS > 64 && defined(BMC_DEVICE_UI_PIXEL_65)
              case 64: return BMC_DEVICE_UI_PIXEL_65;
            #endif
            #if BMC_MAX_PIXELS > 65 && defined(BMC_DEVICE_UI_PIXEL_66)
              case 65: return BMC_DEVICE_UI_PIXEL_66;
            #endif
            #if BMC_MAX_PIXELS > 66 && defined(BMC_DEVICE_UI_PIXEL_67)
              case 66: return BMC_DEVICE_UI_PIXEL_67;
            #endif
            #if BMC_MAX_PIXELS > 67 && defined(BMC_DEVICE_UI_PIXEL_68)
              case 67: return BMC_DEVICE_UI_PIXEL_68;
            #endif
            #if BMC_MAX_PIXELS > 68 && defined(BMC_DEVICE_UI_PIXEL_69)
              case 68: return BMC_DEVICE_UI_PIXEL_69;
            #endif
            #if BMC_MAX_PIXELS > 69 && defined(BMC_DEVICE_UI_PIXEL_70)
              case 69: return BMC_DEVICE_UI_PIXEL_70;
            #endif
            #if BMC_MAX_PIXELS > 70 && defined(BMC_DEVICE_UI_PIXEL_71)
              case 70: return BMC_DEVICE_UI_PIXEL_71;
            #endif
            #if BMC_MAX_PIXELS > 71 && defined(BMC_DEVICE_UI_PIXEL_72)
              case 71: return BMC_DEVICE_UI_PIXEL_72;
            #endif
            #if BMC_MAX_PIXELS > 72 && defined(BMC_DEVICE_UI_PIXEL_73)
              case 72: return BMC_DEVICE_UI_PIXEL_73;
            #endif
            #if BMC_MAX_PIXELS > 73 && defined(BMC_DEVICE_UI_PIXEL_74)
              case 73: return BMC_DEVICE_UI_PIXEL_74;
            #endif
            #if BMC_MAX_PIXELS > 74 && defined(BMC_DEVICE_UI_PIXEL_75)
              case 74: return BMC_DEVICE_UI_PIXEL_75;
            #endif
            #if BMC_MAX_PIXELS > 75 && defined(BMC_DEVICE_UI_PIXEL_76)
              case 75: return BMC_DEVICE_UI_PIXEL_76;
            #endif
            #if BMC_MAX_PIXELS > 76 && defined(BMC_DEVICE_UI_PIXEL_77)
              case 76: return BMC_DEVICE_UI_PIXEL_77;
            #endif
            #if BMC_MAX_PIXELS > 77 && defined(BMC_DEVICE_UI_PIXEL_78)
              case 77: return BMC_DEVICE_UI_PIXEL_78;
            #endif
            #if BMC_MAX_PIXELS > 78 && defined(BMC_DEVICE_UI_PIXEL_79)
              case 78: return BMC_DEVICE_UI_PIXEL_79;
            #endif
            #if BMC_MAX_PIXELS > 79 && defined(BMC_DEVICE_UI_PIXEL_80)
              case 79: return BMC_DEVICE_UI_PIXEL_80;
            #endif
            #if BMC_MAX_PIXELS > 80 && defined(BMC_DEVICE_UI_PIXEL_81)
              case 80: return BMC_DEVICE_UI_PIXEL_81;
            #endif
            #if BMC_MAX_PIXELS > 81 && defined(BMC_DEVICE_UI_PIXEL_82)
              case 81: return BMC_DEVICE_UI_PIXEL_82;
            #endif
            #if BMC_MAX_PIXELS > 82 && defined(BMC_DEVICE_UI_PIXEL_83)
              case 82: return BMC_DEVICE_UI_PIXEL_83;
            #endif
            #if BMC_MAX_PIXELS > 83 && defined(BMC_DEVICE_UI_PIXEL_84)
              case 83: return BMC_DEVICE_UI_PIXEL_84;
            #endif
            #if BMC_MAX_PIXELS > 84 && defined(BMC_DEVICE_UI_PIXEL_85)
              case 84: return BMC_DEVICE_UI_PIXEL_85;
            #endif
            #if BMC_MAX_PIXELS > 85 && defined(BMC_DEVICE_UI_PIXEL_86)
              case 85: return BMC_DEVICE_UI_PIXEL_86;
            #endif
            #if BMC_MAX_PIXELS > 86 && defined(BMC_DEVICE_UI_PIXEL_87)
              case 86: return BMC_DEVICE_UI_PIXEL_87;
            #endif
            #if BMC_MAX_PIXELS > 87 && defined(BMC_DEVICE_UI_PIXEL_88)
              case 87: return BMC_DEVICE_UI_PIXEL_88;
            #endif
            #if BMC_MAX_PIXELS > 88 && defined(BMC_DEVICE_UI_PIXEL_89)
              case 88: return BMC_DEVICE_UI_PIXEL_89;
            #endif
            #if BMC_MAX_PIXELS > 89 && defined(BMC_DEVICE_UI_PIXEL_90)
              case 89: return BMC_DEVICE_UI_PIXEL_90;
            #endif
            #if BMC_MAX_PIXELS > 90 && defined(BMC_DEVICE_UI_PIXEL_91)
              case 90: return BMC_DEVICE_UI_PIXEL_91;
            #endif
            #if BMC_MAX_PIXELS > 91 && defined(BMC_DEVICE_UI_PIXEL_92)
              case 91: return BMC_DEVICE_UI_PIXEL_92;
            #endif
            #if BMC_MAX_PIXELS > 92 && defined(BMC_DEVICE_UI_PIXEL_93)
              case 92: return BMC_DEVICE_UI_PIXEL_93;
            #endif
            #if BMC_MAX_PIXELS > 93 && defined(BMC_DEVICE_UI_PIXEL_94)
              case 93: return BMC_DEVICE_UI_PIXEL_94;
            #endif
            #if BMC_MAX_PIXELS > 94 && defined(BMC_DEVICE_UI_PIXEL_95)
              case 94: return BMC_DEVICE_UI_PIXEL_95;
            #endif
            #if BMC_MAX_PIXELS > 95 && defined(BMC_DEVICE_UI_PIXEL_96)
              case 95: return BMC_DEVICE_UI_PIXEL_96;
            #endif
            #if BMC_MAX_PIXELS > 96 && defined(BMC_DEVICE_UI_PIXEL_97)
              case 96: return BMC_DEVICE_UI_PIXEL_97;
            #endif
            #if BMC_MAX_PIXELS > 97 && defined(BMC_DEVICE_UI_PIXEL_98)
              case 97: return BMC_DEVICE_UI_PIXEL_98;
            #endif
            #if BMC_MAX_PIXELS > 98 && defined(BMC_DEVICE_UI_PIXEL_99)
              case 98: return BMC_DEVICE_UI_PIXEL_99;
            #endif
            #if BMC_MAX_PIXELS > 99 && defined(BMC_DEVICE_UI_PIXEL_100)
              case 99: return BMC_DEVICE_UI_PIXEL_100;
            #endif
            #if BMC_MAX_PIXELS > 100 && defined(BMC_DEVICE_UI_PIXEL_101)
              case 100: return BMC_DEVICE_UI_PIXEL_101;
            #endif
            #if BMC_MAX_PIXELS > 101 && defined(BMC_DEVICE_UI_PIXEL_102)
              case 101: return BMC_DEVICE_UI_PIXEL_102;
            #endif
            #if BMC_MAX_PIXELS > 102 && defined(BMC_DEVICE_UI_PIXEL_103)
              case 102: return BMC_DEVICE_UI_PIXEL_103;
            #endif
            #if BMC_MAX_PIXELS > 103 && defined(BMC_DEVICE_UI_PIXEL_104)
              case 103: return BMC_DEVICE_UI_PIXEL_104;
            #endif
            #if BMC_MAX_PIXELS > 104 && defined(BMC_DEVICE_UI_PIXEL_105)
              case 104: return BMC_DEVICE_UI_PIXEL_105;
            #endif
            #if BMC_MAX_PIXELS > 105 && defined(BMC_DEVICE_UI_PIXEL_106)
              case 105: return BMC_DEVICE_UI_PIXEL_106;
            #endif
            #if BMC_MAX_PIXELS > 106 && defined(BMC_DEVICE_UI_PIXEL_107)
              case 106: return BMC_DEVICE_UI_PIXEL_107;
            #endif
            #if BMC_MAX_PIXELS > 107 && defined(BMC_DEVICE_UI_PIXEL_108)
              case 107: return BMC_DEVICE_UI_PIXEL_108;
            #endif
            #if BMC_MAX_PIXELS > 108 && defined(BMC_DEVICE_UI_PIXEL_109)
              case 108: return BMC_DEVICE_UI_PIXEL_109;
            #endif
            #if BMC_MAX_PIXELS > 109 && defined(BMC_DEVICE_UI_PIXEL_110)
              case 109: return BMC_DEVICE_UI_PIXEL_110;
            #endif
            #if BMC_MAX_PIXELS > 110 && defined(BMC_DEVICE_UI_PIXEL_111)
              case 110: return BMC_DEVICE_UI_PIXEL_111;
            #endif
            #if BMC_MAX_PIXELS > 111 && defined(BMC_DEVICE_UI_PIXEL_112)
              case 111: return BMC_DEVICE_UI_PIXEL_112;
            #endif
            #if BMC_MAX_PIXELS > 112 && defined(BMC_DEVICE_UI_PIXEL_113)
              case 112: return BMC_DEVICE_UI_PIXEL_113;
            #endif
            #if BMC_MAX_PIXELS > 113 && defined(BMC_DEVICE_UI_PIXEL_114)
              case 113: return BMC_DEVICE_UI_PIXEL_114;
            #endif
            #if BMC_MAX_PIXELS > 114 && defined(BMC_DEVICE_UI_PIXEL_115)
              case 114: return BMC_DEVICE_UI_PIXEL_115;
            #endif
            #if BMC_MAX_PIXELS > 115 && defined(BMC_DEVICE_UI_PIXEL_116)
              case 115: return BMC_DEVICE_UI_PIXEL_116;
            #endif
            #if BMC_MAX_PIXELS > 116 && defined(BMC_DEVICE_UI_PIXEL_117)
              case 116: return BMC_DEVICE_UI_PIXEL_117;
            #endif
            #if BMC_MAX_PIXELS > 117 && defined(BMC_DEVICE_UI_PIXEL_118)
              case 117: return BMC_DEVICE_UI_PIXEL_118;
            #endif
            #if BMC_MAX_PIXELS > 118 && defined(BMC_DEVICE_UI_PIXEL_119)
              case 118: return BMC_DEVICE_UI_PIXEL_119;
            #endif
            #if BMC_MAX_PIXELS > 119 && defined(BMC_DEVICE_UI_PIXEL_120)
              case 119: return BMC_DEVICE_UI_PIXEL_120;
            #endif
            #if BMC_MAX_PIXELS > 120 && defined(BMC_DEVICE_UI_PIXEL_121)
              case 120: return BMC_DEVICE_UI_PIXEL_121;
            #endif
            #if BMC_MAX_PIXELS > 121 && defined(BMC_DEVICE_UI_PIXEL_122)
              case 121: return BMC_DEVICE_UI_PIXEL_122;
            #endif
            #if BMC_MAX_PIXELS > 122 && defined(BMC_DEVICE_UI_PIXEL_123)
              case 122: return BMC_DEVICE_UI_PIXEL_123;
            #endif
            #if BMC_MAX_PIXELS > 123 && defined(BMC_DEVICE_UI_PIXEL_124)
              case 123: return BMC_DEVICE_UI_PIXEL_124;
            #endif
            #if BMC_MAX_PIXELS > 124 && defined(BMC_DEVICE_UI_PIXEL_125)
              case 124: return BMC_DEVICE_UI_PIXEL_125;
            #endif
            #if BMC_MAX_PIXELS > 125 && defined(BMC_DEVICE_UI_PIXEL_126)
              case 125: return BMC_DEVICE_UI_PIXEL_126;
            #endif
            #if BMC_MAX_PIXELS > 126 && defined(BMC_DEVICE_UI_PIXEL_127)
              case 126: return BMC_DEVICE_UI_PIXEL_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_PIXEL:
          #if BMC_MAX_GLOBAL_PIXELS > 0
            switch(n){
              #if BMC_MAX_GLOBAL_PIXELS > 0 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_PIXEL_1;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 1 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_PIXEL_2;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 2 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_PIXEL_3;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 3 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_PIXEL_4;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 4 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_PIXEL_5;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 5 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_PIXEL_6;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 6 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_PIXEL_7;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 7 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_PIXEL_8;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 8 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_PIXEL_9;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 9 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_PIXEL_10;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 10 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_PIXEL_11;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 11 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_PIXEL_12;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 12 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_PIXEL_13;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 13 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_PIXEL_14;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 14 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_PIXEL_15;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 15 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_PIXEL_16;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 16 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_PIXEL_17;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 17 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_PIXEL_18;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 18 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_PIXEL_19;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 19 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_PIXEL_20;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 20 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_PIXEL_21;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 21 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_PIXEL_22;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 22 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_PIXEL_23;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 23 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_PIXEL_24;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 24 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_PIXEL_25;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 25 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_PIXEL_26;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 26 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_PIXEL_27;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 27 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_PIXEL_28;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 28 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_PIXEL_29;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 29 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_PIXEL_30;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 30 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_PIXEL_31;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 31 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_PIXEL_32;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 32 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_PIXEL_33;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 33 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_PIXEL_34;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 34 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_PIXEL_35;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 35 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_PIXEL_36;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 36 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_PIXEL_37;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 37 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_PIXEL_38;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 38 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_PIXEL_39;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 39 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_PIXEL_40;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 40 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_PIXEL_41;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 41 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_PIXEL_42;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 42 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_PIXEL_43;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 43 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_PIXEL_44;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 44 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_PIXEL_45;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 45 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_PIXEL_46;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 46 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_PIXEL_47;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 47 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_PIXEL_48;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 48 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_PIXEL_49;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 49 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_PIXEL_50;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 50 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_PIXEL_51;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 51 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_PIXEL_52;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 52 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_PIXEL_53;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 53 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_PIXEL_54;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 54 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_PIXEL_55;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 55 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_PIXEL_56;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 56 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_PIXEL_57;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 57 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_PIXEL_58;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 58 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_PIXEL_59;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 59 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_PIXEL_60;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 60 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_PIXEL_61;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 61 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_PIXEL_62;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 62 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_PIXEL_63;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 63 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_PIXEL_64;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 64 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_65)
              case 64: return BMC_DEVICE_UI_GLOBAL_PIXEL_65;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 65 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_66)
              case 65: return BMC_DEVICE_UI_GLOBAL_PIXEL_66;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 66 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_67)
              case 66: return BMC_DEVICE_UI_GLOBAL_PIXEL_67;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 67 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_68)
              case 67: return BMC_DEVICE_UI_GLOBAL_PIXEL_68;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 68 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_69)
              case 68: return BMC_DEVICE_UI_GLOBAL_PIXEL_69;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 69 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_70)
              case 69: return BMC_DEVICE_UI_GLOBAL_PIXEL_70;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 70 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_71)
              case 70: return BMC_DEVICE_UI_GLOBAL_PIXEL_71;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 71 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_72)
              case 71: return BMC_DEVICE_UI_GLOBAL_PIXEL_72;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 72 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_73)
              case 72: return BMC_DEVICE_UI_GLOBAL_PIXEL_73;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 73 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_74)
              case 73: return BMC_DEVICE_UI_GLOBAL_PIXEL_74;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 74 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_75)
              case 74: return BMC_DEVICE_UI_GLOBAL_PIXEL_75;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 75 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_76)
              case 75: return BMC_DEVICE_UI_GLOBAL_PIXEL_76;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 76 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_77)
              case 76: return BMC_DEVICE_UI_GLOBAL_PIXEL_77;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 77 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_78)
              case 77: return BMC_DEVICE_UI_GLOBAL_PIXEL_78;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 78 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_79)
              case 78: return BMC_DEVICE_UI_GLOBAL_PIXEL_79;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 79 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_80)
              case 79: return BMC_DEVICE_UI_GLOBAL_PIXEL_80;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 80 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_81)
              case 80: return BMC_DEVICE_UI_GLOBAL_PIXEL_81;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 81 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_82)
              case 81: return BMC_DEVICE_UI_GLOBAL_PIXEL_82;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 82 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_83)
              case 82: return BMC_DEVICE_UI_GLOBAL_PIXEL_83;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 83 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_84)
              case 83: return BMC_DEVICE_UI_GLOBAL_PIXEL_84;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 84 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_85)
              case 84: return BMC_DEVICE_UI_GLOBAL_PIXEL_85;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 85 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_86)
              case 85: return BMC_DEVICE_UI_GLOBAL_PIXEL_86;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 86 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_87)
              case 86: return BMC_DEVICE_UI_GLOBAL_PIXEL_87;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 87 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_88)
              case 87: return BMC_DEVICE_UI_GLOBAL_PIXEL_88;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 88 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_89)
              case 88: return BMC_DEVICE_UI_GLOBAL_PIXEL_89;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 89 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_90)
              case 89: return BMC_DEVICE_UI_GLOBAL_PIXEL_90;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 90 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_91)
              case 90: return BMC_DEVICE_UI_GLOBAL_PIXEL_91;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 91 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_92)
              case 91: return BMC_DEVICE_UI_GLOBAL_PIXEL_92;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 92 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_93)
              case 92: return BMC_DEVICE_UI_GLOBAL_PIXEL_93;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 93 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_94)
              case 93: return BMC_DEVICE_UI_GLOBAL_PIXEL_94;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 94 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_95)
              case 94: return BMC_DEVICE_UI_GLOBAL_PIXEL_95;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 95 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_96)
              case 95: return BMC_DEVICE_UI_GLOBAL_PIXEL_96;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 96 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_97)
              case 96: return BMC_DEVICE_UI_GLOBAL_PIXEL_97;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 97 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_98)
              case 97: return BMC_DEVICE_UI_GLOBAL_PIXEL_98;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 98 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_99)
              case 98: return BMC_DEVICE_UI_GLOBAL_PIXEL_99;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 99 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_100)
              case 99: return BMC_DEVICE_UI_GLOBAL_PIXEL_100;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 100 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_101)
              case 100: return BMC_DEVICE_UI_GLOBAL_PIXEL_101;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 101 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_102)
              case 101: return BMC_DEVICE_UI_GLOBAL_PIXEL_102;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 102 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_103)
              case 102: return BMC_DEVICE_UI_GLOBAL_PIXEL_103;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 103 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_104)
              case 103: return BMC_DEVICE_UI_GLOBAL_PIXEL_104;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 104 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_105)
              case 104: return BMC_DEVICE_UI_GLOBAL_PIXEL_105;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 105 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_106)
              case 105: return BMC_DEVICE_UI_GLOBAL_PIXEL_106;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 106 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_107)
              case 106: return BMC_DEVICE_UI_GLOBAL_PIXEL_107;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 107 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_108)
              case 107: return BMC_DEVICE_UI_GLOBAL_PIXEL_108;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 108 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_109)
              case 108: return BMC_DEVICE_UI_GLOBAL_PIXEL_109;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 109 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_110)
              case 109: return BMC_DEVICE_UI_GLOBAL_PIXEL_110;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 110 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_111)
              case 110: return BMC_DEVICE_UI_GLOBAL_PIXEL_111;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 111 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_112)
              case 111: return BMC_DEVICE_UI_GLOBAL_PIXEL_112;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 112 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_113)
              case 112: return BMC_DEVICE_UI_GLOBAL_PIXEL_113;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 113 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_114)
              case 113: return BMC_DEVICE_UI_GLOBAL_PIXEL_114;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 114 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_115)
              case 114: return BMC_DEVICE_UI_GLOBAL_PIXEL_115;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 115 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_116)
              case 115: return BMC_DEVICE_UI_GLOBAL_PIXEL_116;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 116 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_117)
              case 116: return BMC_DEVICE_UI_GLOBAL_PIXEL_117;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 117 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_118)
              case 117: return BMC_DEVICE_UI_GLOBAL_PIXEL_118;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 118 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_119)
              case 118: return BMC_DEVICE_UI_GLOBAL_PIXEL_119;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 119 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_120)
              case 119: return BMC_DEVICE_UI_GLOBAL_PIXEL_120;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 120 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_121)
              case 120: return BMC_DEVICE_UI_GLOBAL_PIXEL_121;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 121 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_122)
              case 121: return BMC_DEVICE_UI_GLOBAL_PIXEL_122;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 122 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_123)
              case 122: return BMC_DEVICE_UI_GLOBAL_PIXEL_123;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 123 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_124)
              case 123: return BMC_DEVICE_UI_GLOBAL_PIXEL_124;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 124 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_125)
              case 124: return BMC_DEVICE_UI_GLOBAL_PIXEL_125;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 125 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_126)
              case 125: return BMC_DEVICE_UI_GLOBAL_PIXEL_126;
            #endif
            #if BMC_MAX_GLOBAL_PIXELS > 126 && defined(BMC_DEVICE_UI_GLOBAL_PIXEL_127)
              case 126: return BMC_DEVICE_UI_GLOBAL_PIXEL_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_RGB_PIXEL:
          #if BMC_MAX_RGB_PIXELS > 0
            switch(n){
              #if BMC_MAX_RGB_PIXELS > 0 && defined(BMC_DEVICE_UI_RGB_PIXEL_1)
              case 0: return BMC_DEVICE_UI_RGB_PIXEL_1;
            #endif
            #if BMC_MAX_RGB_PIXELS > 1 && defined(BMC_DEVICE_UI_RGB_PIXEL_2)
              case 1: return BMC_DEVICE_UI_RGB_PIXEL_2;
            #endif
            #if BMC_MAX_RGB_PIXELS > 2 && defined(BMC_DEVICE_UI_RGB_PIXEL_3)
              case 2: return BMC_DEVICE_UI_RGB_PIXEL_3;
            #endif
            #if BMC_MAX_RGB_PIXELS > 3 && defined(BMC_DEVICE_UI_RGB_PIXEL_4)
              case 3: return BMC_DEVICE_UI_RGB_PIXEL_4;
            #endif
            #if BMC_MAX_RGB_PIXELS > 4 && defined(BMC_DEVICE_UI_RGB_PIXEL_5)
              case 4: return BMC_DEVICE_UI_RGB_PIXEL_5;
            #endif
            #if BMC_MAX_RGB_PIXELS > 5 && defined(BMC_DEVICE_UI_RGB_PIXEL_6)
              case 5: return BMC_DEVICE_UI_RGB_PIXEL_6;
            #endif
            #if BMC_MAX_RGB_PIXELS > 6 && defined(BMC_DEVICE_UI_RGB_PIXEL_7)
              case 6: return BMC_DEVICE_UI_RGB_PIXEL_7;
            #endif
            #if BMC_MAX_RGB_PIXELS > 7 && defined(BMC_DEVICE_UI_RGB_PIXEL_8)
              case 7: return BMC_DEVICE_UI_RGB_PIXEL_8;
            #endif
            #if BMC_MAX_RGB_PIXELS > 8 && defined(BMC_DEVICE_UI_RGB_PIXEL_9)
              case 8: return BMC_DEVICE_UI_RGB_PIXEL_9;
            #endif
            #if BMC_MAX_RGB_PIXELS > 9 && defined(BMC_DEVICE_UI_RGB_PIXEL_10)
              case 9: return BMC_DEVICE_UI_RGB_PIXEL_10;
            #endif
            #if BMC_MAX_RGB_PIXELS > 10 && defined(BMC_DEVICE_UI_RGB_PIXEL_11)
              case 10: return BMC_DEVICE_UI_RGB_PIXEL_11;
            #endif
            #if BMC_MAX_RGB_PIXELS > 11 && defined(BMC_DEVICE_UI_RGB_PIXEL_12)
              case 11: return BMC_DEVICE_UI_RGB_PIXEL_12;
            #endif
            #if BMC_MAX_RGB_PIXELS > 12 && defined(BMC_DEVICE_UI_RGB_PIXEL_13)
              case 12: return BMC_DEVICE_UI_RGB_PIXEL_13;
            #endif
            #if BMC_MAX_RGB_PIXELS > 13 && defined(BMC_DEVICE_UI_RGB_PIXEL_14)
              case 13: return BMC_DEVICE_UI_RGB_PIXEL_14;
            #endif
            #if BMC_MAX_RGB_PIXELS > 14 && defined(BMC_DEVICE_UI_RGB_PIXEL_15)
              case 14: return BMC_DEVICE_UI_RGB_PIXEL_15;
            #endif
            #if BMC_MAX_RGB_PIXELS > 15 && defined(BMC_DEVICE_UI_RGB_PIXEL_16)
              case 15: return BMC_DEVICE_UI_RGB_PIXEL_16;
            #endif
            #if BMC_MAX_RGB_PIXELS > 16 && defined(BMC_DEVICE_UI_RGB_PIXEL_17)
              case 16: return BMC_DEVICE_UI_RGB_PIXEL_17;
            #endif
            #if BMC_MAX_RGB_PIXELS > 17 && defined(BMC_DEVICE_UI_RGB_PIXEL_18)
              case 17: return BMC_DEVICE_UI_RGB_PIXEL_18;
            #endif
            #if BMC_MAX_RGB_PIXELS > 18 && defined(BMC_DEVICE_UI_RGB_PIXEL_19)
              case 18: return BMC_DEVICE_UI_RGB_PIXEL_19;
            #endif
            #if BMC_MAX_RGB_PIXELS > 19 && defined(BMC_DEVICE_UI_RGB_PIXEL_20)
              case 19: return BMC_DEVICE_UI_RGB_PIXEL_20;
            #endif
            #if BMC_MAX_RGB_PIXELS > 20 && defined(BMC_DEVICE_UI_RGB_PIXEL_21)
              case 20: return BMC_DEVICE_UI_RGB_PIXEL_21;
            #endif
            #if BMC_MAX_RGB_PIXELS > 21 && defined(BMC_DEVICE_UI_RGB_PIXEL_22)
              case 21: return BMC_DEVICE_UI_RGB_PIXEL_22;
            #endif
            #if BMC_MAX_RGB_PIXELS > 22 && defined(BMC_DEVICE_UI_RGB_PIXEL_23)
              case 22: return BMC_DEVICE_UI_RGB_PIXEL_23;
            #endif
            #if BMC_MAX_RGB_PIXELS > 23 && defined(BMC_DEVICE_UI_RGB_PIXEL_24)
              case 23: return BMC_DEVICE_UI_RGB_PIXEL_24;
            #endif
            #if BMC_MAX_RGB_PIXELS > 24 && defined(BMC_DEVICE_UI_RGB_PIXEL_25)
              case 24: return BMC_DEVICE_UI_RGB_PIXEL_25;
            #endif
            #if BMC_MAX_RGB_PIXELS > 25 && defined(BMC_DEVICE_UI_RGB_PIXEL_26)
              case 25: return BMC_DEVICE_UI_RGB_PIXEL_26;
            #endif
            #if BMC_MAX_RGB_PIXELS > 26 && defined(BMC_DEVICE_UI_RGB_PIXEL_27)
              case 26: return BMC_DEVICE_UI_RGB_PIXEL_27;
            #endif
            #if BMC_MAX_RGB_PIXELS > 27 && defined(BMC_DEVICE_UI_RGB_PIXEL_28)
              case 27: return BMC_DEVICE_UI_RGB_PIXEL_28;
            #endif
            #if BMC_MAX_RGB_PIXELS > 28 && defined(BMC_DEVICE_UI_RGB_PIXEL_29)
              case 28: return BMC_DEVICE_UI_RGB_PIXEL_29;
            #endif
            #if BMC_MAX_RGB_PIXELS > 29 && defined(BMC_DEVICE_UI_RGB_PIXEL_30)
              case 29: return BMC_DEVICE_UI_RGB_PIXEL_30;
            #endif
            #if BMC_MAX_RGB_PIXELS > 30 && defined(BMC_DEVICE_UI_RGB_PIXEL_31)
              case 30: return BMC_DEVICE_UI_RGB_PIXEL_31;
            #endif
            #if BMC_MAX_RGB_PIXELS > 31 && defined(BMC_DEVICE_UI_RGB_PIXEL_32)
              case 31: return BMC_DEVICE_UI_RGB_PIXEL_32;
            #endif
            #if BMC_MAX_RGB_PIXELS > 32 && defined(BMC_DEVICE_UI_RGB_PIXEL_33)
              case 32: return BMC_DEVICE_UI_RGB_PIXEL_33;
            #endif
            #if BMC_MAX_RGB_PIXELS > 33 && defined(BMC_DEVICE_UI_RGB_PIXEL_34)
              case 33: return BMC_DEVICE_UI_RGB_PIXEL_34;
            #endif
            #if BMC_MAX_RGB_PIXELS > 34 && defined(BMC_DEVICE_UI_RGB_PIXEL_35)
              case 34: return BMC_DEVICE_UI_RGB_PIXEL_35;
            #endif
            #if BMC_MAX_RGB_PIXELS > 35 && defined(BMC_DEVICE_UI_RGB_PIXEL_36)
              case 35: return BMC_DEVICE_UI_RGB_PIXEL_36;
            #endif
            #if BMC_MAX_RGB_PIXELS > 36 && defined(BMC_DEVICE_UI_RGB_PIXEL_37)
              case 36: return BMC_DEVICE_UI_RGB_PIXEL_37;
            #endif
            #if BMC_MAX_RGB_PIXELS > 37 && defined(BMC_DEVICE_UI_RGB_PIXEL_38)
              case 37: return BMC_DEVICE_UI_RGB_PIXEL_38;
            #endif
            #if BMC_MAX_RGB_PIXELS > 38 && defined(BMC_DEVICE_UI_RGB_PIXEL_39)
              case 38: return BMC_DEVICE_UI_RGB_PIXEL_39;
            #endif
            #if BMC_MAX_RGB_PIXELS > 39 && defined(BMC_DEVICE_UI_RGB_PIXEL_40)
              case 39: return BMC_DEVICE_UI_RGB_PIXEL_40;
            #endif
            #if BMC_MAX_RGB_PIXELS > 40 && defined(BMC_DEVICE_UI_RGB_PIXEL_41)
              case 40: return BMC_DEVICE_UI_RGB_PIXEL_41;
            #endif
            #if BMC_MAX_RGB_PIXELS > 41 && defined(BMC_DEVICE_UI_RGB_PIXEL_42)
              case 41: return BMC_DEVICE_UI_RGB_PIXEL_42;
            #endif
            #if BMC_MAX_RGB_PIXELS > 42 && defined(BMC_DEVICE_UI_RGB_PIXEL_43)
              case 42: return BMC_DEVICE_UI_RGB_PIXEL_43;
            #endif
            #if BMC_MAX_RGB_PIXELS > 43 && defined(BMC_DEVICE_UI_RGB_PIXEL_44)
              case 43: return BMC_DEVICE_UI_RGB_PIXEL_44;
            #endif
            #if BMC_MAX_RGB_PIXELS > 44 && defined(BMC_DEVICE_UI_RGB_PIXEL_45)
              case 44: return BMC_DEVICE_UI_RGB_PIXEL_45;
            #endif
            #if BMC_MAX_RGB_PIXELS > 45 && defined(BMC_DEVICE_UI_RGB_PIXEL_46)
              case 45: return BMC_DEVICE_UI_RGB_PIXEL_46;
            #endif
            #if BMC_MAX_RGB_PIXELS > 46 && defined(BMC_DEVICE_UI_RGB_PIXEL_47)
              case 46: return BMC_DEVICE_UI_RGB_PIXEL_47;
            #endif
            #if BMC_MAX_RGB_PIXELS > 47 && defined(BMC_DEVICE_UI_RGB_PIXEL_48)
              case 47: return BMC_DEVICE_UI_RGB_PIXEL_48;
            #endif
            #if BMC_MAX_RGB_PIXELS > 48 && defined(BMC_DEVICE_UI_RGB_PIXEL_49)
              case 48: return BMC_DEVICE_UI_RGB_PIXEL_49;
            #endif
            #if BMC_MAX_RGB_PIXELS > 49 && defined(BMC_DEVICE_UI_RGB_PIXEL_50)
              case 49: return BMC_DEVICE_UI_RGB_PIXEL_50;
            #endif
            #if BMC_MAX_RGB_PIXELS > 50 && defined(BMC_DEVICE_UI_RGB_PIXEL_51)
              case 50: return BMC_DEVICE_UI_RGB_PIXEL_51;
            #endif
            #if BMC_MAX_RGB_PIXELS > 51 && defined(BMC_DEVICE_UI_RGB_PIXEL_52)
              case 51: return BMC_DEVICE_UI_RGB_PIXEL_52;
            #endif
            #if BMC_MAX_RGB_PIXELS > 52 && defined(BMC_DEVICE_UI_RGB_PIXEL_53)
              case 52: return BMC_DEVICE_UI_RGB_PIXEL_53;
            #endif
            #if BMC_MAX_RGB_PIXELS > 53 && defined(BMC_DEVICE_UI_RGB_PIXEL_54)
              case 53: return BMC_DEVICE_UI_RGB_PIXEL_54;
            #endif
            #if BMC_MAX_RGB_PIXELS > 54 && defined(BMC_DEVICE_UI_RGB_PIXEL_55)
              case 54: return BMC_DEVICE_UI_RGB_PIXEL_55;
            #endif
            #if BMC_MAX_RGB_PIXELS > 55 && defined(BMC_DEVICE_UI_RGB_PIXEL_56)
              case 55: return BMC_DEVICE_UI_RGB_PIXEL_56;
            #endif
            #if BMC_MAX_RGB_PIXELS > 56 && defined(BMC_DEVICE_UI_RGB_PIXEL_57)
              case 56: return BMC_DEVICE_UI_RGB_PIXEL_57;
            #endif
            #if BMC_MAX_RGB_PIXELS > 57 && defined(BMC_DEVICE_UI_RGB_PIXEL_58)
              case 57: return BMC_DEVICE_UI_RGB_PIXEL_58;
            #endif
            #if BMC_MAX_RGB_PIXELS > 58 && defined(BMC_DEVICE_UI_RGB_PIXEL_59)
              case 58: return BMC_DEVICE_UI_RGB_PIXEL_59;
            #endif
            #if BMC_MAX_RGB_PIXELS > 59 && defined(BMC_DEVICE_UI_RGB_PIXEL_60)
              case 59: return BMC_DEVICE_UI_RGB_PIXEL_60;
            #endif
            #if BMC_MAX_RGB_PIXELS > 60 && defined(BMC_DEVICE_UI_RGB_PIXEL_61)
              case 60: return BMC_DEVICE_UI_RGB_PIXEL_61;
            #endif
            #if BMC_MAX_RGB_PIXELS > 61 && defined(BMC_DEVICE_UI_RGB_PIXEL_62)
              case 61: return BMC_DEVICE_UI_RGB_PIXEL_62;
            #endif
            #if BMC_MAX_RGB_PIXELS > 62 && defined(BMC_DEVICE_UI_RGB_PIXEL_63)
              case 62: return BMC_DEVICE_UI_RGB_PIXEL_63;
            #endif
            #if BMC_MAX_RGB_PIXELS > 63 && defined(BMC_DEVICE_UI_RGB_PIXEL_64)
              case 63: return BMC_DEVICE_UI_RGB_PIXEL_64;
            #endif
            #if BMC_MAX_RGB_PIXELS > 64 && defined(BMC_DEVICE_UI_RGB_PIXEL_65)
              case 64: return BMC_DEVICE_UI_RGB_PIXEL_65;
            #endif
            #if BMC_MAX_RGB_PIXELS > 65 && defined(BMC_DEVICE_UI_RGB_PIXEL_66)
              case 65: return BMC_DEVICE_UI_RGB_PIXEL_66;
            #endif
            #if BMC_MAX_RGB_PIXELS > 66 && defined(BMC_DEVICE_UI_RGB_PIXEL_67)
              case 66: return BMC_DEVICE_UI_RGB_PIXEL_67;
            #endif
            #if BMC_MAX_RGB_PIXELS > 67 && defined(BMC_DEVICE_UI_RGB_PIXEL_68)
              case 67: return BMC_DEVICE_UI_RGB_PIXEL_68;
            #endif
            #if BMC_MAX_RGB_PIXELS > 68 && defined(BMC_DEVICE_UI_RGB_PIXEL_69)
              case 68: return BMC_DEVICE_UI_RGB_PIXEL_69;
            #endif
            #if BMC_MAX_RGB_PIXELS > 69 && defined(BMC_DEVICE_UI_RGB_PIXEL_70)
              case 69: return BMC_DEVICE_UI_RGB_PIXEL_70;
            #endif
            #if BMC_MAX_RGB_PIXELS > 70 && defined(BMC_DEVICE_UI_RGB_PIXEL_71)
              case 70: return BMC_DEVICE_UI_RGB_PIXEL_71;
            #endif
            #if BMC_MAX_RGB_PIXELS > 71 && defined(BMC_DEVICE_UI_RGB_PIXEL_72)
              case 71: return BMC_DEVICE_UI_RGB_PIXEL_72;
            #endif
            #if BMC_MAX_RGB_PIXELS > 72 && defined(BMC_DEVICE_UI_RGB_PIXEL_73)
              case 72: return BMC_DEVICE_UI_RGB_PIXEL_73;
            #endif
            #if BMC_MAX_RGB_PIXELS > 73 && defined(BMC_DEVICE_UI_RGB_PIXEL_74)
              case 73: return BMC_DEVICE_UI_RGB_PIXEL_74;
            #endif
            #if BMC_MAX_RGB_PIXELS > 74 && defined(BMC_DEVICE_UI_RGB_PIXEL_75)
              case 74: return BMC_DEVICE_UI_RGB_PIXEL_75;
            #endif
            #if BMC_MAX_RGB_PIXELS > 75 && defined(BMC_DEVICE_UI_RGB_PIXEL_76)
              case 75: return BMC_DEVICE_UI_RGB_PIXEL_76;
            #endif
            #if BMC_MAX_RGB_PIXELS > 76 && defined(BMC_DEVICE_UI_RGB_PIXEL_77)
              case 76: return BMC_DEVICE_UI_RGB_PIXEL_77;
            #endif
            #if BMC_MAX_RGB_PIXELS > 77 && defined(BMC_DEVICE_UI_RGB_PIXEL_78)
              case 77: return BMC_DEVICE_UI_RGB_PIXEL_78;
            #endif
            #if BMC_MAX_RGB_PIXELS > 78 && defined(BMC_DEVICE_UI_RGB_PIXEL_79)
              case 78: return BMC_DEVICE_UI_RGB_PIXEL_79;
            #endif
            #if BMC_MAX_RGB_PIXELS > 79 && defined(BMC_DEVICE_UI_RGB_PIXEL_80)
              case 79: return BMC_DEVICE_UI_RGB_PIXEL_80;
            #endif
            #if BMC_MAX_RGB_PIXELS > 80 && defined(BMC_DEVICE_UI_RGB_PIXEL_81)
              case 80: return BMC_DEVICE_UI_RGB_PIXEL_81;
            #endif
            #if BMC_MAX_RGB_PIXELS > 81 && defined(BMC_DEVICE_UI_RGB_PIXEL_82)
              case 81: return BMC_DEVICE_UI_RGB_PIXEL_82;
            #endif
            #if BMC_MAX_RGB_PIXELS > 82 && defined(BMC_DEVICE_UI_RGB_PIXEL_83)
              case 82: return BMC_DEVICE_UI_RGB_PIXEL_83;
            #endif
            #if BMC_MAX_RGB_PIXELS > 83 && defined(BMC_DEVICE_UI_RGB_PIXEL_84)
              case 83: return BMC_DEVICE_UI_RGB_PIXEL_84;
            #endif
            #if BMC_MAX_RGB_PIXELS > 84 && defined(BMC_DEVICE_UI_RGB_PIXEL_85)
              case 84: return BMC_DEVICE_UI_RGB_PIXEL_85;
            #endif
            #if BMC_MAX_RGB_PIXELS > 85 && defined(BMC_DEVICE_UI_RGB_PIXEL_86)
              case 85: return BMC_DEVICE_UI_RGB_PIXEL_86;
            #endif
            #if BMC_MAX_RGB_PIXELS > 86 && defined(BMC_DEVICE_UI_RGB_PIXEL_87)
              case 86: return BMC_DEVICE_UI_RGB_PIXEL_87;
            #endif
            #if BMC_MAX_RGB_PIXELS > 87 && defined(BMC_DEVICE_UI_RGB_PIXEL_88)
              case 87: return BMC_DEVICE_UI_RGB_PIXEL_88;
            #endif
            #if BMC_MAX_RGB_PIXELS > 88 && defined(BMC_DEVICE_UI_RGB_PIXEL_89)
              case 88: return BMC_DEVICE_UI_RGB_PIXEL_89;
            #endif
            #if BMC_MAX_RGB_PIXELS > 89 && defined(BMC_DEVICE_UI_RGB_PIXEL_90)
              case 89: return BMC_DEVICE_UI_RGB_PIXEL_90;
            #endif
            #if BMC_MAX_RGB_PIXELS > 90 && defined(BMC_DEVICE_UI_RGB_PIXEL_91)
              case 90: return BMC_DEVICE_UI_RGB_PIXEL_91;
            #endif
            #if BMC_MAX_RGB_PIXELS > 91 && defined(BMC_DEVICE_UI_RGB_PIXEL_92)
              case 91: return BMC_DEVICE_UI_RGB_PIXEL_92;
            #endif
            #if BMC_MAX_RGB_PIXELS > 92 && defined(BMC_DEVICE_UI_RGB_PIXEL_93)
              case 92: return BMC_DEVICE_UI_RGB_PIXEL_93;
            #endif
            #if BMC_MAX_RGB_PIXELS > 93 && defined(BMC_DEVICE_UI_RGB_PIXEL_94)
              case 93: return BMC_DEVICE_UI_RGB_PIXEL_94;
            #endif
            #if BMC_MAX_RGB_PIXELS > 94 && defined(BMC_DEVICE_UI_RGB_PIXEL_95)
              case 94: return BMC_DEVICE_UI_RGB_PIXEL_95;
            #endif
            #if BMC_MAX_RGB_PIXELS > 95 && defined(BMC_DEVICE_UI_RGB_PIXEL_96)
              case 95: return BMC_DEVICE_UI_RGB_PIXEL_96;
            #endif
            #if BMC_MAX_RGB_PIXELS > 96 && defined(BMC_DEVICE_UI_RGB_PIXEL_97)
              case 96: return BMC_DEVICE_UI_RGB_PIXEL_97;
            #endif
            #if BMC_MAX_RGB_PIXELS > 97 && defined(BMC_DEVICE_UI_RGB_PIXEL_98)
              case 97: return BMC_DEVICE_UI_RGB_PIXEL_98;
            #endif
            #if BMC_MAX_RGB_PIXELS > 98 && defined(BMC_DEVICE_UI_RGB_PIXEL_99)
              case 98: return BMC_DEVICE_UI_RGB_PIXEL_99;
            #endif
            #if BMC_MAX_RGB_PIXELS > 99 && defined(BMC_DEVICE_UI_RGB_PIXEL_100)
              case 99: return BMC_DEVICE_UI_RGB_PIXEL_100;
            #endif
            #if BMC_MAX_RGB_PIXELS > 100 && defined(BMC_DEVICE_UI_RGB_PIXEL_101)
              case 100: return BMC_DEVICE_UI_RGB_PIXEL_101;
            #endif
            #if BMC_MAX_RGB_PIXELS > 101 && defined(BMC_DEVICE_UI_RGB_PIXEL_102)
              case 101: return BMC_DEVICE_UI_RGB_PIXEL_102;
            #endif
            #if BMC_MAX_RGB_PIXELS > 102 && defined(BMC_DEVICE_UI_RGB_PIXEL_103)
              case 102: return BMC_DEVICE_UI_RGB_PIXEL_103;
            #endif
            #if BMC_MAX_RGB_PIXELS > 103 && defined(BMC_DEVICE_UI_RGB_PIXEL_104)
              case 103: return BMC_DEVICE_UI_RGB_PIXEL_104;
            #endif
            #if BMC_MAX_RGB_PIXELS > 104 && defined(BMC_DEVICE_UI_RGB_PIXEL_105)
              case 104: return BMC_DEVICE_UI_RGB_PIXEL_105;
            #endif
            #if BMC_MAX_RGB_PIXELS > 105 && defined(BMC_DEVICE_UI_RGB_PIXEL_106)
              case 105: return BMC_DEVICE_UI_RGB_PIXEL_106;
            #endif
            #if BMC_MAX_RGB_PIXELS > 106 && defined(BMC_DEVICE_UI_RGB_PIXEL_107)
              case 106: return BMC_DEVICE_UI_RGB_PIXEL_107;
            #endif
            #if BMC_MAX_RGB_PIXELS > 107 && defined(BMC_DEVICE_UI_RGB_PIXEL_108)
              case 107: return BMC_DEVICE_UI_RGB_PIXEL_108;
            #endif
            #if BMC_MAX_RGB_PIXELS > 108 && defined(BMC_DEVICE_UI_RGB_PIXEL_109)
              case 108: return BMC_DEVICE_UI_RGB_PIXEL_109;
            #endif
            #if BMC_MAX_RGB_PIXELS > 109 && defined(BMC_DEVICE_UI_RGB_PIXEL_110)
              case 109: return BMC_DEVICE_UI_RGB_PIXEL_110;
            #endif
            #if BMC_MAX_RGB_PIXELS > 110 && defined(BMC_DEVICE_UI_RGB_PIXEL_111)
              case 110: return BMC_DEVICE_UI_RGB_PIXEL_111;
            #endif
            #if BMC_MAX_RGB_PIXELS > 111 && defined(BMC_DEVICE_UI_RGB_PIXEL_112)
              case 111: return BMC_DEVICE_UI_RGB_PIXEL_112;
            #endif
            #if BMC_MAX_RGB_PIXELS > 112 && defined(BMC_DEVICE_UI_RGB_PIXEL_113)
              case 112: return BMC_DEVICE_UI_RGB_PIXEL_113;
            #endif
            #if BMC_MAX_RGB_PIXELS > 113 && defined(BMC_DEVICE_UI_RGB_PIXEL_114)
              case 113: return BMC_DEVICE_UI_RGB_PIXEL_114;
            #endif
            #if BMC_MAX_RGB_PIXELS > 114 && defined(BMC_DEVICE_UI_RGB_PIXEL_115)
              case 114: return BMC_DEVICE_UI_RGB_PIXEL_115;
            #endif
            #if BMC_MAX_RGB_PIXELS > 115 && defined(BMC_DEVICE_UI_RGB_PIXEL_116)
              case 115: return BMC_DEVICE_UI_RGB_PIXEL_116;
            #endif
            #if BMC_MAX_RGB_PIXELS > 116 && defined(BMC_DEVICE_UI_RGB_PIXEL_117)
              case 116: return BMC_DEVICE_UI_RGB_PIXEL_117;
            #endif
            #if BMC_MAX_RGB_PIXELS > 117 && defined(BMC_DEVICE_UI_RGB_PIXEL_118)
              case 117: return BMC_DEVICE_UI_RGB_PIXEL_118;
            #endif
            #if BMC_MAX_RGB_PIXELS > 118 && defined(BMC_DEVICE_UI_RGB_PIXEL_119)
              case 118: return BMC_DEVICE_UI_RGB_PIXEL_119;
            #endif
            #if BMC_MAX_RGB_PIXELS > 119 && defined(BMC_DEVICE_UI_RGB_PIXEL_120)
              case 119: return BMC_DEVICE_UI_RGB_PIXEL_120;
            #endif
            #if BMC_MAX_RGB_PIXELS > 120 && defined(BMC_DEVICE_UI_RGB_PIXEL_121)
              case 120: return BMC_DEVICE_UI_RGB_PIXEL_121;
            #endif
            #if BMC_MAX_RGB_PIXELS > 121 && defined(BMC_DEVICE_UI_RGB_PIXEL_122)
              case 121: return BMC_DEVICE_UI_RGB_PIXEL_122;
            #endif
            #if BMC_MAX_RGB_PIXELS > 122 && defined(BMC_DEVICE_UI_RGB_PIXEL_123)
              case 122: return BMC_DEVICE_UI_RGB_PIXEL_123;
            #endif
            #if BMC_MAX_RGB_PIXELS > 123 && defined(BMC_DEVICE_UI_RGB_PIXEL_124)
              case 123: return BMC_DEVICE_UI_RGB_PIXEL_124;
            #endif
            #if BMC_MAX_RGB_PIXELS > 124 && defined(BMC_DEVICE_UI_RGB_PIXEL_125)
              case 124: return BMC_DEVICE_UI_RGB_PIXEL_125;
            #endif
            #if BMC_MAX_RGB_PIXELS > 125 && defined(BMC_DEVICE_UI_RGB_PIXEL_126)
              case 125: return BMC_DEVICE_UI_RGB_PIXEL_126;
            #endif
            #if BMC_MAX_RGB_PIXELS > 126 && defined(BMC_DEVICE_UI_RGB_PIXEL_127)
              case 126: return BMC_DEVICE_UI_RGB_PIXEL_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_RGB_PIXEL:
          #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
            switch(n){
              #if BMC_MAX_GLOBAL_RGB_PIXELS > 0 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_1;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 1 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_2;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 2 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_3;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 3 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_4;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 4 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_5;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 5 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_6;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 6 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_7;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 7 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_8;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 8 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_9;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 9 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_10;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 10 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_11;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 11 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_12;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 12 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_13;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 13 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_14;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 14 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_15;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 15 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_16;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 16 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_17;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 17 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_18;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 18 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_19;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 19 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_20;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 20 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_21;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 21 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_22;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 22 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_23;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 23 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_24;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 24 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_25;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 25 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_26;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 26 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_27;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 27 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_28;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 28 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_29;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 29 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_30;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 30 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_31;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 31 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_32;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 32 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_33;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 33 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_34;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 34 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_35;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 35 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_36;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 36 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_37;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 37 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_38;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 38 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_39;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 39 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_40;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 40 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_41;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 41 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_42;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 42 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_43;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 43 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_44;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 44 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_45;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 45 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_46;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 46 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_47;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 47 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_48;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 48 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_49;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 49 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_50;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 50 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_51;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 51 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_52;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 52 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_53;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 53 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_54;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 54 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_55;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 55 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_56;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 56 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_57;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 57 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_58;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 58 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_59;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 59 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_60;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 60 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_61;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 61 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_62;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 62 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_63;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 63 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_64;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 64 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_65)
              case 64: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_65;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 65 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_66)
              case 65: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_66;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 66 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_67)
              case 66: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_67;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 67 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_68)
              case 67: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_68;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 68 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_69)
              case 68: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_69;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 69 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_70)
              case 69: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_70;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 70 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_71)
              case 70: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_71;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 71 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_72)
              case 71: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_72;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 72 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_73)
              case 72: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_73;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 73 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_74)
              case 73: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_74;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 74 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_75)
              case 74: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_75;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 75 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_76)
              case 75: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_76;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 76 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_77)
              case 76: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_77;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 77 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_78)
              case 77: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_78;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 78 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_79)
              case 78: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_79;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 79 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_80)
              case 79: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_80;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 80 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_81)
              case 80: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_81;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 81 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_82)
              case 81: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_82;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 82 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_83)
              case 82: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_83;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 83 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_84)
              case 83: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_84;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 84 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_85)
              case 84: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_85;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 85 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_86)
              case 85: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_86;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 86 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_87)
              case 86: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_87;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 87 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_88)
              case 87: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_88;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 88 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_89)
              case 88: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_89;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 89 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_90)
              case 89: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_90;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 90 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_91)
              case 90: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_91;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 91 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_92)
              case 91: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_92;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 92 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_93)
              case 92: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_93;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 93 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_94)
              case 93: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_94;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 94 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_95)
              case 94: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_95;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 95 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_96)
              case 95: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_96;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 96 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_97)
              case 96: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_97;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 97 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_98)
              case 97: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_98;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 98 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_99)
              case 98: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_99;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 99 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_100)
              case 99: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_100;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 100 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_101)
              case 100: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_101;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 101 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_102)
              case 101: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_102;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 102 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_103)
              case 102: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_103;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 103 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_104)
              case 103: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_104;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 104 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_105)
              case 104: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_105;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 105 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_106)
              case 105: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_106;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 106 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_107)
              case 106: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_107;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 107 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_108)
              case 107: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_108;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 108 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_109)
              case 108: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_109;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 109 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_110)
              case 109: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_110;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 110 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_111)
              case 110: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_111;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 111 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_112)
              case 111: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_112;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 112 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_113)
              case 112: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_113;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 113 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_114)
              case 113: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_114;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 114 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_115)
              case 114: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_115;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 115 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_116)
              case 115: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_116;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 116 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_117)
              case 116: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_117;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 117 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_118)
              case 117: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_118;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 118 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_119)
              case 118: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_119;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 119 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_120)
              case 119: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_120;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 120 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_121)
              case 120: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_121;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 121 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_122)
              case 121: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_122;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 122 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_123)
              case 122: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_123;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 123 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_124)
              case 123: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_124;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 124 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_125)
              case 124: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_125;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 125 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_126)
              case 125: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_126;
            #endif
            #if BMC_MAX_GLOBAL_RGB_PIXELS > 126 && defined(BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_127)
              case 126: return BMC_DEVICE_UI_GLOBAL_RGB_PIXEL_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_POT:
          #if BMC_MAX_POTS > 0
            switch(n){
              #if BMC_MAX_POTS > 0 && defined(BMC_DEVICE_UI_POT_1)
              case 0: return BMC_DEVICE_UI_POT_1;
            #endif
            #if BMC_MAX_POTS > 1 && defined(BMC_DEVICE_UI_POT_2)
              case 1: return BMC_DEVICE_UI_POT_2;
            #endif
            #if BMC_MAX_POTS > 2 && defined(BMC_DEVICE_UI_POT_3)
              case 2: return BMC_DEVICE_UI_POT_3;
            #endif
            #if BMC_MAX_POTS > 3 && defined(BMC_DEVICE_UI_POT_4)
              case 3: return BMC_DEVICE_UI_POT_4;
            #endif
            #if BMC_MAX_POTS > 4 && defined(BMC_DEVICE_UI_POT_5)
              case 4: return BMC_DEVICE_UI_POT_5;
            #endif
            #if BMC_MAX_POTS > 5 && defined(BMC_DEVICE_UI_POT_6)
              case 5: return BMC_DEVICE_UI_POT_6;
            #endif
            #if BMC_MAX_POTS > 6 && defined(BMC_DEVICE_UI_POT_7)
              case 6: return BMC_DEVICE_UI_POT_7;
            #endif
            #if BMC_MAX_POTS > 7 && defined(BMC_DEVICE_UI_POT_8)
              case 7: return BMC_DEVICE_UI_POT_8;
            #endif
            #if BMC_MAX_POTS > 8 && defined(BMC_DEVICE_UI_POT_9)
              case 8: return BMC_DEVICE_UI_POT_9;
            #endif
            #if BMC_MAX_POTS > 9 && defined(BMC_DEVICE_UI_POT_10)
              case 9: return BMC_DEVICE_UI_POT_10;
            #endif
            #if BMC_MAX_POTS > 10 && defined(BMC_DEVICE_UI_POT_11)
              case 10: return BMC_DEVICE_UI_POT_11;
            #endif
            #if BMC_MAX_POTS > 11 && defined(BMC_DEVICE_UI_POT_12)
              case 11: return BMC_DEVICE_UI_POT_12;
            #endif
            #if BMC_MAX_POTS > 12 && defined(BMC_DEVICE_UI_POT_13)
              case 12: return BMC_DEVICE_UI_POT_13;
            #endif
            #if BMC_MAX_POTS > 13 && defined(BMC_DEVICE_UI_POT_14)
              case 13: return BMC_DEVICE_UI_POT_14;
            #endif
            #if BMC_MAX_POTS > 14 && defined(BMC_DEVICE_UI_POT_15)
              case 14: return BMC_DEVICE_UI_POT_15;
            #endif
            #if BMC_MAX_POTS > 15 && defined(BMC_DEVICE_UI_POT_16)
              case 15: return BMC_DEVICE_UI_POT_16;
            #endif
            #if BMC_MAX_POTS > 16 && defined(BMC_DEVICE_UI_POT_17)
              case 16: return BMC_DEVICE_UI_POT_17;
            #endif
            #if BMC_MAX_POTS > 17 && defined(BMC_DEVICE_UI_POT_18)
              case 17: return BMC_DEVICE_UI_POT_18;
            #endif
            #if BMC_MAX_POTS > 18 && defined(BMC_DEVICE_UI_POT_19)
              case 18: return BMC_DEVICE_UI_POT_19;
            #endif
            #if BMC_MAX_POTS > 19 && defined(BMC_DEVICE_UI_POT_20)
              case 19: return BMC_DEVICE_UI_POT_20;
            #endif
            #if BMC_MAX_POTS > 20 && defined(BMC_DEVICE_UI_POT_21)
              case 20: return BMC_DEVICE_UI_POT_21;
            #endif
            #if BMC_MAX_POTS > 21 && defined(BMC_DEVICE_UI_POT_22)
              case 21: return BMC_DEVICE_UI_POT_22;
            #endif
            #if BMC_MAX_POTS > 22 && defined(BMC_DEVICE_UI_POT_23)
              case 22: return BMC_DEVICE_UI_POT_23;
            #endif
            #if BMC_MAX_POTS > 23 && defined(BMC_DEVICE_UI_POT_24)
              case 23: return BMC_DEVICE_UI_POT_24;
            #endif
            #if BMC_MAX_POTS > 24 && defined(BMC_DEVICE_UI_POT_25)
              case 24: return BMC_DEVICE_UI_POT_25;
            #endif
            #if BMC_MAX_POTS > 25 && defined(BMC_DEVICE_UI_POT_26)
              case 25: return BMC_DEVICE_UI_POT_26;
            #endif
            #if BMC_MAX_POTS > 26 && defined(BMC_DEVICE_UI_POT_27)
              case 26: return BMC_DEVICE_UI_POT_27;
            #endif
            #if BMC_MAX_POTS > 27 && defined(BMC_DEVICE_UI_POT_28)
              case 27: return BMC_DEVICE_UI_POT_28;
            #endif
            #if BMC_MAX_POTS > 28 && defined(BMC_DEVICE_UI_POT_29)
              case 28: return BMC_DEVICE_UI_POT_29;
            #endif
            #if BMC_MAX_POTS > 29 && defined(BMC_DEVICE_UI_POT_30)
              case 29: return BMC_DEVICE_UI_POT_30;
            #endif
            #if BMC_MAX_POTS > 30 && defined(BMC_DEVICE_UI_POT_31)
              case 30: return BMC_DEVICE_UI_POT_31;
            #endif
            #if BMC_MAX_POTS > 31 && defined(BMC_DEVICE_UI_POT_32)
              case 31: return BMC_DEVICE_UI_POT_32;
            #endif
            #if BMC_MAX_POTS > 32 && defined(BMC_DEVICE_UI_POT_33)
              case 32: return BMC_DEVICE_UI_POT_33;
            #endif
            #if BMC_MAX_POTS > 33 && defined(BMC_DEVICE_UI_POT_34)
              case 33: return BMC_DEVICE_UI_POT_34;
            #endif
            #if BMC_MAX_POTS > 34 && defined(BMC_DEVICE_UI_POT_35)
              case 34: return BMC_DEVICE_UI_POT_35;
            #endif
            #if BMC_MAX_POTS > 35 && defined(BMC_DEVICE_UI_POT_36)
              case 35: return BMC_DEVICE_UI_POT_36;
            #endif
            #if BMC_MAX_POTS > 36 && defined(BMC_DEVICE_UI_POT_37)
              case 36: return BMC_DEVICE_UI_POT_37;
            #endif
            #if BMC_MAX_POTS > 37 && defined(BMC_DEVICE_UI_POT_38)
              case 37: return BMC_DEVICE_UI_POT_38;
            #endif
            #if BMC_MAX_POTS > 38 && defined(BMC_DEVICE_UI_POT_39)
              case 38: return BMC_DEVICE_UI_POT_39;
            #endif
            #if BMC_MAX_POTS > 39 && defined(BMC_DEVICE_UI_POT_40)
              case 39: return BMC_DEVICE_UI_POT_40;
            #endif
            #if BMC_MAX_POTS > 40 && defined(BMC_DEVICE_UI_POT_41)
              case 40: return BMC_DEVICE_UI_POT_41;
            #endif
            #if BMC_MAX_POTS > 41 && defined(BMC_DEVICE_UI_POT_42)
              case 41: return BMC_DEVICE_UI_POT_42;
            #endif
            #if BMC_MAX_POTS > 42 && defined(BMC_DEVICE_UI_POT_43)
              case 42: return BMC_DEVICE_UI_POT_43;
            #endif
            #if BMC_MAX_POTS > 43 && defined(BMC_DEVICE_UI_POT_44)
              case 43: return BMC_DEVICE_UI_POT_44;
            #endif
            #if BMC_MAX_POTS > 44 && defined(BMC_DEVICE_UI_POT_45)
              case 44: return BMC_DEVICE_UI_POT_45;
            #endif
            #if BMC_MAX_POTS > 45 && defined(BMC_DEVICE_UI_POT_46)
              case 45: return BMC_DEVICE_UI_POT_46;
            #endif
            #if BMC_MAX_POTS > 46 && defined(BMC_DEVICE_UI_POT_47)
              case 46: return BMC_DEVICE_UI_POT_47;
            #endif
            #if BMC_MAX_POTS > 47 && defined(BMC_DEVICE_UI_POT_48)
              case 47: return BMC_DEVICE_UI_POT_48;
            #endif
            #if BMC_MAX_POTS > 48 && defined(BMC_DEVICE_UI_POT_49)
              case 48: return BMC_DEVICE_UI_POT_49;
            #endif
            #if BMC_MAX_POTS > 49 && defined(BMC_DEVICE_UI_POT_50)
              case 49: return BMC_DEVICE_UI_POT_50;
            #endif
            #if BMC_MAX_POTS > 50 && defined(BMC_DEVICE_UI_POT_51)
              case 50: return BMC_DEVICE_UI_POT_51;
            #endif
            #if BMC_MAX_POTS > 51 && defined(BMC_DEVICE_UI_POT_52)
              case 51: return BMC_DEVICE_UI_POT_52;
            #endif
            #if BMC_MAX_POTS > 52 && defined(BMC_DEVICE_UI_POT_53)
              case 52: return BMC_DEVICE_UI_POT_53;
            #endif
            #if BMC_MAX_POTS > 53 && defined(BMC_DEVICE_UI_POT_54)
              case 53: return BMC_DEVICE_UI_POT_54;
            #endif
            #if BMC_MAX_POTS > 54 && defined(BMC_DEVICE_UI_POT_55)
              case 54: return BMC_DEVICE_UI_POT_55;
            #endif
            #if BMC_MAX_POTS > 55 && defined(BMC_DEVICE_UI_POT_56)
              case 55: return BMC_DEVICE_UI_POT_56;
            #endif
            #if BMC_MAX_POTS > 56 && defined(BMC_DEVICE_UI_POT_57)
              case 56: return BMC_DEVICE_UI_POT_57;
            #endif
            #if BMC_MAX_POTS > 57 && defined(BMC_DEVICE_UI_POT_58)
              case 57: return BMC_DEVICE_UI_POT_58;
            #endif
            #if BMC_MAX_POTS > 58 && defined(BMC_DEVICE_UI_POT_59)
              case 58: return BMC_DEVICE_UI_POT_59;
            #endif
            #if BMC_MAX_POTS > 59 && defined(BMC_DEVICE_UI_POT_60)
              case 59: return BMC_DEVICE_UI_POT_60;
            #endif
            #if BMC_MAX_POTS > 60 && defined(BMC_DEVICE_UI_POT_61)
              case 60: return BMC_DEVICE_UI_POT_61;
            #endif
            #if BMC_MAX_POTS > 61 && defined(BMC_DEVICE_UI_POT_62)
              case 61: return BMC_DEVICE_UI_POT_62;
            #endif
            #if BMC_MAX_POTS > 62 && defined(BMC_DEVICE_UI_POT_63)
              case 62: return BMC_DEVICE_UI_POT_63;
            #endif
            #if BMC_MAX_POTS > 63 && defined(BMC_DEVICE_UI_POT_64)
              case 63: return BMC_DEVICE_UI_POT_64;
            #endif
            #if BMC_MAX_POTS > 64 && defined(BMC_DEVICE_UI_POT_65)
              case 64: return BMC_DEVICE_UI_POT_65;
            #endif
            #if BMC_MAX_POTS > 65 && defined(BMC_DEVICE_UI_POT_66)
              case 65: return BMC_DEVICE_UI_POT_66;
            #endif
            #if BMC_MAX_POTS > 66 && defined(BMC_DEVICE_UI_POT_67)
              case 66: return BMC_DEVICE_UI_POT_67;
            #endif
            #if BMC_MAX_POTS > 67 && defined(BMC_DEVICE_UI_POT_68)
              case 67: return BMC_DEVICE_UI_POT_68;
            #endif
            #if BMC_MAX_POTS > 68 && defined(BMC_DEVICE_UI_POT_69)
              case 68: return BMC_DEVICE_UI_POT_69;
            #endif
            #if BMC_MAX_POTS > 69 && defined(BMC_DEVICE_UI_POT_70)
              case 69: return BMC_DEVICE_UI_POT_70;
            #endif
            #if BMC_MAX_POTS > 70 && defined(BMC_DEVICE_UI_POT_71)
              case 70: return BMC_DEVICE_UI_POT_71;
            #endif
            #if BMC_MAX_POTS > 71 && defined(BMC_DEVICE_UI_POT_72)
              case 71: return BMC_DEVICE_UI_POT_72;
            #endif
            #if BMC_MAX_POTS > 72 && defined(BMC_DEVICE_UI_POT_73)
              case 72: return BMC_DEVICE_UI_POT_73;
            #endif
            #if BMC_MAX_POTS > 73 && defined(BMC_DEVICE_UI_POT_74)
              case 73: return BMC_DEVICE_UI_POT_74;
            #endif
            #if BMC_MAX_POTS > 74 && defined(BMC_DEVICE_UI_POT_75)
              case 74: return BMC_DEVICE_UI_POT_75;
            #endif
            #if BMC_MAX_POTS > 75 && defined(BMC_DEVICE_UI_POT_76)
              case 75: return BMC_DEVICE_UI_POT_76;
            #endif
            #if BMC_MAX_POTS > 76 && defined(BMC_DEVICE_UI_POT_77)
              case 76: return BMC_DEVICE_UI_POT_77;
            #endif
            #if BMC_MAX_POTS > 77 && defined(BMC_DEVICE_UI_POT_78)
              case 77: return BMC_DEVICE_UI_POT_78;
            #endif
            #if BMC_MAX_POTS > 78 && defined(BMC_DEVICE_UI_POT_79)
              case 78: return BMC_DEVICE_UI_POT_79;
            #endif
            #if BMC_MAX_POTS > 79 && defined(BMC_DEVICE_UI_POT_80)
              case 79: return BMC_DEVICE_UI_POT_80;
            #endif
            #if BMC_MAX_POTS > 80 && defined(BMC_DEVICE_UI_POT_81)
              case 80: return BMC_DEVICE_UI_POT_81;
            #endif
            #if BMC_MAX_POTS > 81 && defined(BMC_DEVICE_UI_POT_82)
              case 81: return BMC_DEVICE_UI_POT_82;
            #endif
            #if BMC_MAX_POTS > 82 && defined(BMC_DEVICE_UI_POT_83)
              case 82: return BMC_DEVICE_UI_POT_83;
            #endif
            #if BMC_MAX_POTS > 83 && defined(BMC_DEVICE_UI_POT_84)
              case 83: return BMC_DEVICE_UI_POT_84;
            #endif
            #if BMC_MAX_POTS > 84 && defined(BMC_DEVICE_UI_POT_85)
              case 84: return BMC_DEVICE_UI_POT_85;
            #endif
            #if BMC_MAX_POTS > 85 && defined(BMC_DEVICE_UI_POT_86)
              case 85: return BMC_DEVICE_UI_POT_86;
            #endif
            #if BMC_MAX_POTS > 86 && defined(BMC_DEVICE_UI_POT_87)
              case 86: return BMC_DEVICE_UI_POT_87;
            #endif
            #if BMC_MAX_POTS > 87 && defined(BMC_DEVICE_UI_POT_88)
              case 87: return BMC_DEVICE_UI_POT_88;
            #endif
            #if BMC_MAX_POTS > 88 && defined(BMC_DEVICE_UI_POT_89)
              case 88: return BMC_DEVICE_UI_POT_89;
            #endif
            #if BMC_MAX_POTS > 89 && defined(BMC_DEVICE_UI_POT_90)
              case 89: return BMC_DEVICE_UI_POT_90;
            #endif
            #if BMC_MAX_POTS > 90 && defined(BMC_DEVICE_UI_POT_91)
              case 90: return BMC_DEVICE_UI_POT_91;
            #endif
            #if BMC_MAX_POTS > 91 && defined(BMC_DEVICE_UI_POT_92)
              case 91: return BMC_DEVICE_UI_POT_92;
            #endif
            #if BMC_MAX_POTS > 92 && defined(BMC_DEVICE_UI_POT_93)
              case 92: return BMC_DEVICE_UI_POT_93;
            #endif
            #if BMC_MAX_POTS > 93 && defined(BMC_DEVICE_UI_POT_94)
              case 93: return BMC_DEVICE_UI_POT_94;
            #endif
            #if BMC_MAX_POTS > 94 && defined(BMC_DEVICE_UI_POT_95)
              case 94: return BMC_DEVICE_UI_POT_95;
            #endif
            #if BMC_MAX_POTS > 95 && defined(BMC_DEVICE_UI_POT_96)
              case 95: return BMC_DEVICE_UI_POT_96;
            #endif
            #if BMC_MAX_POTS > 96 && defined(BMC_DEVICE_UI_POT_97)
              case 96: return BMC_DEVICE_UI_POT_97;
            #endif
            #if BMC_MAX_POTS > 97 && defined(BMC_DEVICE_UI_POT_98)
              case 97: return BMC_DEVICE_UI_POT_98;
            #endif
            #if BMC_MAX_POTS > 98 && defined(BMC_DEVICE_UI_POT_99)
              case 98: return BMC_DEVICE_UI_POT_99;
            #endif
            #if BMC_MAX_POTS > 99 && defined(BMC_DEVICE_UI_POT_100)
              case 99: return BMC_DEVICE_UI_POT_100;
            #endif
            #if BMC_MAX_POTS > 100 && defined(BMC_DEVICE_UI_POT_101)
              case 100: return BMC_DEVICE_UI_POT_101;
            #endif
            #if BMC_MAX_POTS > 101 && defined(BMC_DEVICE_UI_POT_102)
              case 101: return BMC_DEVICE_UI_POT_102;
            #endif
            #if BMC_MAX_POTS > 102 && defined(BMC_DEVICE_UI_POT_103)
              case 102: return BMC_DEVICE_UI_POT_103;
            #endif
            #if BMC_MAX_POTS > 103 && defined(BMC_DEVICE_UI_POT_104)
              case 103: return BMC_DEVICE_UI_POT_104;
            #endif
            #if BMC_MAX_POTS > 104 && defined(BMC_DEVICE_UI_POT_105)
              case 104: return BMC_DEVICE_UI_POT_105;
            #endif
            #if BMC_MAX_POTS > 105 && defined(BMC_DEVICE_UI_POT_106)
              case 105: return BMC_DEVICE_UI_POT_106;
            #endif
            #if BMC_MAX_POTS > 106 && defined(BMC_DEVICE_UI_POT_107)
              case 106: return BMC_DEVICE_UI_POT_107;
            #endif
            #if BMC_MAX_POTS > 107 && defined(BMC_DEVICE_UI_POT_108)
              case 107: return BMC_DEVICE_UI_POT_108;
            #endif
            #if BMC_MAX_POTS > 108 && defined(BMC_DEVICE_UI_POT_109)
              case 108: return BMC_DEVICE_UI_POT_109;
            #endif
            #if BMC_MAX_POTS > 109 && defined(BMC_DEVICE_UI_POT_110)
              case 109: return BMC_DEVICE_UI_POT_110;
            #endif
            #if BMC_MAX_POTS > 110 && defined(BMC_DEVICE_UI_POT_111)
              case 110: return BMC_DEVICE_UI_POT_111;
            #endif
            #if BMC_MAX_POTS > 111 && defined(BMC_DEVICE_UI_POT_112)
              case 111: return BMC_DEVICE_UI_POT_112;
            #endif
            #if BMC_MAX_POTS > 112 && defined(BMC_DEVICE_UI_POT_113)
              case 112: return BMC_DEVICE_UI_POT_113;
            #endif
            #if BMC_MAX_POTS > 113 && defined(BMC_DEVICE_UI_POT_114)
              case 113: return BMC_DEVICE_UI_POT_114;
            #endif
            #if BMC_MAX_POTS > 114 && defined(BMC_DEVICE_UI_POT_115)
              case 114: return BMC_DEVICE_UI_POT_115;
            #endif
            #if BMC_MAX_POTS > 115 && defined(BMC_DEVICE_UI_POT_116)
              case 115: return BMC_DEVICE_UI_POT_116;
            #endif
            #if BMC_MAX_POTS > 116 && defined(BMC_DEVICE_UI_POT_117)
              case 116: return BMC_DEVICE_UI_POT_117;
            #endif
            #if BMC_MAX_POTS > 117 && defined(BMC_DEVICE_UI_POT_118)
              case 117: return BMC_DEVICE_UI_POT_118;
            #endif
            #if BMC_MAX_POTS > 118 && defined(BMC_DEVICE_UI_POT_119)
              case 118: return BMC_DEVICE_UI_POT_119;
            #endif
            #if BMC_MAX_POTS > 119 && defined(BMC_DEVICE_UI_POT_120)
              case 119: return BMC_DEVICE_UI_POT_120;
            #endif
            #if BMC_MAX_POTS > 120 && defined(BMC_DEVICE_UI_POT_121)
              case 120: return BMC_DEVICE_UI_POT_121;
            #endif
            #if BMC_MAX_POTS > 121 && defined(BMC_DEVICE_UI_POT_122)
              case 121: return BMC_DEVICE_UI_POT_122;
            #endif
            #if BMC_MAX_POTS > 122 && defined(BMC_DEVICE_UI_POT_123)
              case 122: return BMC_DEVICE_UI_POT_123;
            #endif
            #if BMC_MAX_POTS > 123 && defined(BMC_DEVICE_UI_POT_124)
              case 123: return BMC_DEVICE_UI_POT_124;
            #endif
            #if BMC_MAX_POTS > 124 && defined(BMC_DEVICE_UI_POT_125)
              case 124: return BMC_DEVICE_UI_POT_125;
            #endif
            #if BMC_MAX_POTS > 125 && defined(BMC_DEVICE_UI_POT_126)
              case 125: return BMC_DEVICE_UI_POT_126;
            #endif
            #if BMC_MAX_POTS > 126 && defined(BMC_DEVICE_UI_POT_127)
              case 126: return BMC_DEVICE_UI_POT_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_POT:
          #if BMC_MAX_GLOBAL_POTS > 0
            switch(n){
              #if BMC_MAX_GLOBAL_POTS > 0 && defined(BMC_DEVICE_UI_GLOBAL_POT_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_POT_1;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 1 && defined(BMC_DEVICE_UI_GLOBAL_POT_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_POT_2;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 2 && defined(BMC_DEVICE_UI_GLOBAL_POT_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_POT_3;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 3 && defined(BMC_DEVICE_UI_GLOBAL_POT_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_POT_4;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 4 && defined(BMC_DEVICE_UI_GLOBAL_POT_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_POT_5;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 5 && defined(BMC_DEVICE_UI_GLOBAL_POT_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_POT_6;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 6 && defined(BMC_DEVICE_UI_GLOBAL_POT_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_POT_7;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 7 && defined(BMC_DEVICE_UI_GLOBAL_POT_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_POT_8;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 8 && defined(BMC_DEVICE_UI_GLOBAL_POT_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_POT_9;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 9 && defined(BMC_DEVICE_UI_GLOBAL_POT_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_POT_10;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 10 && defined(BMC_DEVICE_UI_GLOBAL_POT_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_POT_11;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 11 && defined(BMC_DEVICE_UI_GLOBAL_POT_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_POT_12;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 12 && defined(BMC_DEVICE_UI_GLOBAL_POT_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_POT_13;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 13 && defined(BMC_DEVICE_UI_GLOBAL_POT_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_POT_14;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 14 && defined(BMC_DEVICE_UI_GLOBAL_POT_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_POT_15;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 15 && defined(BMC_DEVICE_UI_GLOBAL_POT_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_POT_16;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 16 && defined(BMC_DEVICE_UI_GLOBAL_POT_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_POT_17;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 17 && defined(BMC_DEVICE_UI_GLOBAL_POT_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_POT_18;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 18 && defined(BMC_DEVICE_UI_GLOBAL_POT_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_POT_19;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 19 && defined(BMC_DEVICE_UI_GLOBAL_POT_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_POT_20;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 20 && defined(BMC_DEVICE_UI_GLOBAL_POT_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_POT_21;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 21 && defined(BMC_DEVICE_UI_GLOBAL_POT_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_POT_22;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 22 && defined(BMC_DEVICE_UI_GLOBAL_POT_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_POT_23;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 23 && defined(BMC_DEVICE_UI_GLOBAL_POT_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_POT_24;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 24 && defined(BMC_DEVICE_UI_GLOBAL_POT_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_POT_25;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 25 && defined(BMC_DEVICE_UI_GLOBAL_POT_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_POT_26;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 26 && defined(BMC_DEVICE_UI_GLOBAL_POT_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_POT_27;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 27 && defined(BMC_DEVICE_UI_GLOBAL_POT_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_POT_28;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 28 && defined(BMC_DEVICE_UI_GLOBAL_POT_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_POT_29;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 29 && defined(BMC_DEVICE_UI_GLOBAL_POT_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_POT_30;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 30 && defined(BMC_DEVICE_UI_GLOBAL_POT_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_POT_31;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 31 && defined(BMC_DEVICE_UI_GLOBAL_POT_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_POT_32;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 32 && defined(BMC_DEVICE_UI_GLOBAL_POT_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_POT_33;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 33 && defined(BMC_DEVICE_UI_GLOBAL_POT_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_POT_34;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 34 && defined(BMC_DEVICE_UI_GLOBAL_POT_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_POT_35;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 35 && defined(BMC_DEVICE_UI_GLOBAL_POT_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_POT_36;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 36 && defined(BMC_DEVICE_UI_GLOBAL_POT_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_POT_37;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 37 && defined(BMC_DEVICE_UI_GLOBAL_POT_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_POT_38;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 38 && defined(BMC_DEVICE_UI_GLOBAL_POT_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_POT_39;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 39 && defined(BMC_DEVICE_UI_GLOBAL_POT_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_POT_40;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 40 && defined(BMC_DEVICE_UI_GLOBAL_POT_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_POT_41;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 41 && defined(BMC_DEVICE_UI_GLOBAL_POT_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_POT_42;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 42 && defined(BMC_DEVICE_UI_GLOBAL_POT_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_POT_43;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 43 && defined(BMC_DEVICE_UI_GLOBAL_POT_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_POT_44;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 44 && defined(BMC_DEVICE_UI_GLOBAL_POT_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_POT_45;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 45 && defined(BMC_DEVICE_UI_GLOBAL_POT_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_POT_46;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 46 && defined(BMC_DEVICE_UI_GLOBAL_POT_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_POT_47;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 47 && defined(BMC_DEVICE_UI_GLOBAL_POT_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_POT_48;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 48 && defined(BMC_DEVICE_UI_GLOBAL_POT_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_POT_49;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 49 && defined(BMC_DEVICE_UI_GLOBAL_POT_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_POT_50;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 50 && defined(BMC_DEVICE_UI_GLOBAL_POT_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_POT_51;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 51 && defined(BMC_DEVICE_UI_GLOBAL_POT_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_POT_52;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 52 && defined(BMC_DEVICE_UI_GLOBAL_POT_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_POT_53;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 53 && defined(BMC_DEVICE_UI_GLOBAL_POT_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_POT_54;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 54 && defined(BMC_DEVICE_UI_GLOBAL_POT_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_POT_55;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 55 && defined(BMC_DEVICE_UI_GLOBAL_POT_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_POT_56;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 56 && defined(BMC_DEVICE_UI_GLOBAL_POT_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_POT_57;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 57 && defined(BMC_DEVICE_UI_GLOBAL_POT_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_POT_58;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 58 && defined(BMC_DEVICE_UI_GLOBAL_POT_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_POT_59;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 59 && defined(BMC_DEVICE_UI_GLOBAL_POT_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_POT_60;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 60 && defined(BMC_DEVICE_UI_GLOBAL_POT_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_POT_61;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 61 && defined(BMC_DEVICE_UI_GLOBAL_POT_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_POT_62;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 62 && defined(BMC_DEVICE_UI_GLOBAL_POT_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_POT_63;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 63 && defined(BMC_DEVICE_UI_GLOBAL_POT_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_POT_64;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 64 && defined(BMC_DEVICE_UI_GLOBAL_POT_65)
              case 64: return BMC_DEVICE_UI_GLOBAL_POT_65;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 65 && defined(BMC_DEVICE_UI_GLOBAL_POT_66)
              case 65: return BMC_DEVICE_UI_GLOBAL_POT_66;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 66 && defined(BMC_DEVICE_UI_GLOBAL_POT_67)
              case 66: return BMC_DEVICE_UI_GLOBAL_POT_67;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 67 && defined(BMC_DEVICE_UI_GLOBAL_POT_68)
              case 67: return BMC_DEVICE_UI_GLOBAL_POT_68;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 68 && defined(BMC_DEVICE_UI_GLOBAL_POT_69)
              case 68: return BMC_DEVICE_UI_GLOBAL_POT_69;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 69 && defined(BMC_DEVICE_UI_GLOBAL_POT_70)
              case 69: return BMC_DEVICE_UI_GLOBAL_POT_70;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 70 && defined(BMC_DEVICE_UI_GLOBAL_POT_71)
              case 70: return BMC_DEVICE_UI_GLOBAL_POT_71;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 71 && defined(BMC_DEVICE_UI_GLOBAL_POT_72)
              case 71: return BMC_DEVICE_UI_GLOBAL_POT_72;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 72 && defined(BMC_DEVICE_UI_GLOBAL_POT_73)
              case 72: return BMC_DEVICE_UI_GLOBAL_POT_73;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 73 && defined(BMC_DEVICE_UI_GLOBAL_POT_74)
              case 73: return BMC_DEVICE_UI_GLOBAL_POT_74;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 74 && defined(BMC_DEVICE_UI_GLOBAL_POT_75)
              case 74: return BMC_DEVICE_UI_GLOBAL_POT_75;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 75 && defined(BMC_DEVICE_UI_GLOBAL_POT_76)
              case 75: return BMC_DEVICE_UI_GLOBAL_POT_76;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 76 && defined(BMC_DEVICE_UI_GLOBAL_POT_77)
              case 76: return BMC_DEVICE_UI_GLOBAL_POT_77;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 77 && defined(BMC_DEVICE_UI_GLOBAL_POT_78)
              case 77: return BMC_DEVICE_UI_GLOBAL_POT_78;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 78 && defined(BMC_DEVICE_UI_GLOBAL_POT_79)
              case 78: return BMC_DEVICE_UI_GLOBAL_POT_79;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 79 && defined(BMC_DEVICE_UI_GLOBAL_POT_80)
              case 79: return BMC_DEVICE_UI_GLOBAL_POT_80;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 80 && defined(BMC_DEVICE_UI_GLOBAL_POT_81)
              case 80: return BMC_DEVICE_UI_GLOBAL_POT_81;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 81 && defined(BMC_DEVICE_UI_GLOBAL_POT_82)
              case 81: return BMC_DEVICE_UI_GLOBAL_POT_82;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 82 && defined(BMC_DEVICE_UI_GLOBAL_POT_83)
              case 82: return BMC_DEVICE_UI_GLOBAL_POT_83;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 83 && defined(BMC_DEVICE_UI_GLOBAL_POT_84)
              case 83: return BMC_DEVICE_UI_GLOBAL_POT_84;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 84 && defined(BMC_DEVICE_UI_GLOBAL_POT_85)
              case 84: return BMC_DEVICE_UI_GLOBAL_POT_85;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 85 && defined(BMC_DEVICE_UI_GLOBAL_POT_86)
              case 85: return BMC_DEVICE_UI_GLOBAL_POT_86;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 86 && defined(BMC_DEVICE_UI_GLOBAL_POT_87)
              case 86: return BMC_DEVICE_UI_GLOBAL_POT_87;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 87 && defined(BMC_DEVICE_UI_GLOBAL_POT_88)
              case 87: return BMC_DEVICE_UI_GLOBAL_POT_88;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 88 && defined(BMC_DEVICE_UI_GLOBAL_POT_89)
              case 88: return BMC_DEVICE_UI_GLOBAL_POT_89;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 89 && defined(BMC_DEVICE_UI_GLOBAL_POT_90)
              case 89: return BMC_DEVICE_UI_GLOBAL_POT_90;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 90 && defined(BMC_DEVICE_UI_GLOBAL_POT_91)
              case 90: return BMC_DEVICE_UI_GLOBAL_POT_91;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 91 && defined(BMC_DEVICE_UI_GLOBAL_POT_92)
              case 91: return BMC_DEVICE_UI_GLOBAL_POT_92;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 92 && defined(BMC_DEVICE_UI_GLOBAL_POT_93)
              case 92: return BMC_DEVICE_UI_GLOBAL_POT_93;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 93 && defined(BMC_DEVICE_UI_GLOBAL_POT_94)
              case 93: return BMC_DEVICE_UI_GLOBAL_POT_94;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 94 && defined(BMC_DEVICE_UI_GLOBAL_POT_95)
              case 94: return BMC_DEVICE_UI_GLOBAL_POT_95;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 95 && defined(BMC_DEVICE_UI_GLOBAL_POT_96)
              case 95: return BMC_DEVICE_UI_GLOBAL_POT_96;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 96 && defined(BMC_DEVICE_UI_GLOBAL_POT_97)
              case 96: return BMC_DEVICE_UI_GLOBAL_POT_97;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 97 && defined(BMC_DEVICE_UI_GLOBAL_POT_98)
              case 97: return BMC_DEVICE_UI_GLOBAL_POT_98;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 98 && defined(BMC_DEVICE_UI_GLOBAL_POT_99)
              case 98: return BMC_DEVICE_UI_GLOBAL_POT_99;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 99 && defined(BMC_DEVICE_UI_GLOBAL_POT_100)
              case 99: return BMC_DEVICE_UI_GLOBAL_POT_100;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 100 && defined(BMC_DEVICE_UI_GLOBAL_POT_101)
              case 100: return BMC_DEVICE_UI_GLOBAL_POT_101;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 101 && defined(BMC_DEVICE_UI_GLOBAL_POT_102)
              case 101: return BMC_DEVICE_UI_GLOBAL_POT_102;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 102 && defined(BMC_DEVICE_UI_GLOBAL_POT_103)
              case 102: return BMC_DEVICE_UI_GLOBAL_POT_103;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 103 && defined(BMC_DEVICE_UI_GLOBAL_POT_104)
              case 103: return BMC_DEVICE_UI_GLOBAL_POT_104;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 104 && defined(BMC_DEVICE_UI_GLOBAL_POT_105)
              case 104: return BMC_DEVICE_UI_GLOBAL_POT_105;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 105 && defined(BMC_DEVICE_UI_GLOBAL_POT_106)
              case 105: return BMC_DEVICE_UI_GLOBAL_POT_106;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 106 && defined(BMC_DEVICE_UI_GLOBAL_POT_107)
              case 106: return BMC_DEVICE_UI_GLOBAL_POT_107;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 107 && defined(BMC_DEVICE_UI_GLOBAL_POT_108)
              case 107: return BMC_DEVICE_UI_GLOBAL_POT_108;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 108 && defined(BMC_DEVICE_UI_GLOBAL_POT_109)
              case 108: return BMC_DEVICE_UI_GLOBAL_POT_109;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 109 && defined(BMC_DEVICE_UI_GLOBAL_POT_110)
              case 109: return BMC_DEVICE_UI_GLOBAL_POT_110;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 110 && defined(BMC_DEVICE_UI_GLOBAL_POT_111)
              case 110: return BMC_DEVICE_UI_GLOBAL_POT_111;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 111 && defined(BMC_DEVICE_UI_GLOBAL_POT_112)
              case 111: return BMC_DEVICE_UI_GLOBAL_POT_112;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 112 && defined(BMC_DEVICE_UI_GLOBAL_POT_113)
              case 112: return BMC_DEVICE_UI_GLOBAL_POT_113;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 113 && defined(BMC_DEVICE_UI_GLOBAL_POT_114)
              case 113: return BMC_DEVICE_UI_GLOBAL_POT_114;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 114 && defined(BMC_DEVICE_UI_GLOBAL_POT_115)
              case 114: return BMC_DEVICE_UI_GLOBAL_POT_115;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 115 && defined(BMC_DEVICE_UI_GLOBAL_POT_116)
              case 115: return BMC_DEVICE_UI_GLOBAL_POT_116;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 116 && defined(BMC_DEVICE_UI_GLOBAL_POT_117)
              case 116: return BMC_DEVICE_UI_GLOBAL_POT_117;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 117 && defined(BMC_DEVICE_UI_GLOBAL_POT_118)
              case 117: return BMC_DEVICE_UI_GLOBAL_POT_118;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 118 && defined(BMC_DEVICE_UI_GLOBAL_POT_119)
              case 118: return BMC_DEVICE_UI_GLOBAL_POT_119;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 119 && defined(BMC_DEVICE_UI_GLOBAL_POT_120)
              case 119: return BMC_DEVICE_UI_GLOBAL_POT_120;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 120 && defined(BMC_DEVICE_UI_GLOBAL_POT_121)
              case 120: return BMC_DEVICE_UI_GLOBAL_POT_121;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 121 && defined(BMC_DEVICE_UI_GLOBAL_POT_122)
              case 121: return BMC_DEVICE_UI_GLOBAL_POT_122;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 122 && defined(BMC_DEVICE_UI_GLOBAL_POT_123)
              case 122: return BMC_DEVICE_UI_GLOBAL_POT_123;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 123 && defined(BMC_DEVICE_UI_GLOBAL_POT_124)
              case 123: return BMC_DEVICE_UI_GLOBAL_POT_124;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 124 && defined(BMC_DEVICE_UI_GLOBAL_POT_125)
              case 124: return BMC_DEVICE_UI_GLOBAL_POT_125;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 125 && defined(BMC_DEVICE_UI_GLOBAL_POT_126)
              case 125: return BMC_DEVICE_UI_GLOBAL_POT_126;
            #endif
            #if BMC_MAX_GLOBAL_POTS > 126 && defined(BMC_DEVICE_UI_GLOBAL_POT_127)
              case 126: return BMC_DEVICE_UI_GLOBAL_POT_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_ENCODER:
          #if BMC_MAX_ENCODERS > 0
            switch(n){
              #if BMC_MAX_ENCODERS > 0 && defined(BMC_DEVICE_UI_ENCODER_1)
              case 0: return BMC_DEVICE_UI_ENCODER_1;
            #endif
            #if BMC_MAX_ENCODERS > 1 && defined(BMC_DEVICE_UI_ENCODER_2)
              case 1: return BMC_DEVICE_UI_ENCODER_2;
            #endif
            #if BMC_MAX_ENCODERS > 2 && defined(BMC_DEVICE_UI_ENCODER_3)
              case 2: return BMC_DEVICE_UI_ENCODER_3;
            #endif
            #if BMC_MAX_ENCODERS > 3 && defined(BMC_DEVICE_UI_ENCODER_4)
              case 3: return BMC_DEVICE_UI_ENCODER_4;
            #endif
            #if BMC_MAX_ENCODERS > 4 && defined(BMC_DEVICE_UI_ENCODER_5)
              case 4: return BMC_DEVICE_UI_ENCODER_5;
            #endif
            #if BMC_MAX_ENCODERS > 5 && defined(BMC_DEVICE_UI_ENCODER_6)
              case 5: return BMC_DEVICE_UI_ENCODER_6;
            #endif
            #if BMC_MAX_ENCODERS > 6 && defined(BMC_DEVICE_UI_ENCODER_7)
              case 6: return BMC_DEVICE_UI_ENCODER_7;
            #endif
            #if BMC_MAX_ENCODERS > 7 && defined(BMC_DEVICE_UI_ENCODER_8)
              case 7: return BMC_DEVICE_UI_ENCODER_8;
            #endif
            #if BMC_MAX_ENCODERS > 8 && defined(BMC_DEVICE_UI_ENCODER_9)
              case 8: return BMC_DEVICE_UI_ENCODER_9;
            #endif
            #if BMC_MAX_ENCODERS > 9 && defined(BMC_DEVICE_UI_ENCODER_10)
              case 9: return BMC_DEVICE_UI_ENCODER_10;
            #endif
            #if BMC_MAX_ENCODERS > 10 && defined(BMC_DEVICE_UI_ENCODER_11)
              case 10: return BMC_DEVICE_UI_ENCODER_11;
            #endif
            #if BMC_MAX_ENCODERS > 11 && defined(BMC_DEVICE_UI_ENCODER_12)
              case 11: return BMC_DEVICE_UI_ENCODER_12;
            #endif
            #if BMC_MAX_ENCODERS > 12 && defined(BMC_DEVICE_UI_ENCODER_13)
              case 12: return BMC_DEVICE_UI_ENCODER_13;
            #endif
            #if BMC_MAX_ENCODERS > 13 && defined(BMC_DEVICE_UI_ENCODER_14)
              case 13: return BMC_DEVICE_UI_ENCODER_14;
            #endif
            #if BMC_MAX_ENCODERS > 14 && defined(BMC_DEVICE_UI_ENCODER_15)
              case 14: return BMC_DEVICE_UI_ENCODER_15;
            #endif
            #if BMC_MAX_ENCODERS > 15 && defined(BMC_DEVICE_UI_ENCODER_16)
              case 15: return BMC_DEVICE_UI_ENCODER_16;
            #endif
            #if BMC_MAX_ENCODERS > 16 && defined(BMC_DEVICE_UI_ENCODER_17)
              case 16: return BMC_DEVICE_UI_ENCODER_17;
            #endif
            #if BMC_MAX_ENCODERS > 17 && defined(BMC_DEVICE_UI_ENCODER_18)
              case 17: return BMC_DEVICE_UI_ENCODER_18;
            #endif
            #if BMC_MAX_ENCODERS > 18 && defined(BMC_DEVICE_UI_ENCODER_19)
              case 18: return BMC_DEVICE_UI_ENCODER_19;
            #endif
            #if BMC_MAX_ENCODERS > 19 && defined(BMC_DEVICE_UI_ENCODER_20)
              case 19: return BMC_DEVICE_UI_ENCODER_20;
            #endif
            #if BMC_MAX_ENCODERS > 20 && defined(BMC_DEVICE_UI_ENCODER_21)
              case 20: return BMC_DEVICE_UI_ENCODER_21;
            #endif
            #if BMC_MAX_ENCODERS > 21 && defined(BMC_DEVICE_UI_ENCODER_22)
              case 21: return BMC_DEVICE_UI_ENCODER_22;
            #endif
            #if BMC_MAX_ENCODERS > 22 && defined(BMC_DEVICE_UI_ENCODER_23)
              case 22: return BMC_DEVICE_UI_ENCODER_23;
            #endif
            #if BMC_MAX_ENCODERS > 23 && defined(BMC_DEVICE_UI_ENCODER_24)
              case 23: return BMC_DEVICE_UI_ENCODER_24;
            #endif
            #if BMC_MAX_ENCODERS > 24 && defined(BMC_DEVICE_UI_ENCODER_25)
              case 24: return BMC_DEVICE_UI_ENCODER_25;
            #endif
            #if BMC_MAX_ENCODERS > 25 && defined(BMC_DEVICE_UI_ENCODER_26)
              case 25: return BMC_DEVICE_UI_ENCODER_26;
            #endif
            #if BMC_MAX_ENCODERS > 26 && defined(BMC_DEVICE_UI_ENCODER_27)
              case 26: return BMC_DEVICE_UI_ENCODER_27;
            #endif
            #if BMC_MAX_ENCODERS > 27 && defined(BMC_DEVICE_UI_ENCODER_28)
              case 27: return BMC_DEVICE_UI_ENCODER_28;
            #endif
            #if BMC_MAX_ENCODERS > 28 && defined(BMC_DEVICE_UI_ENCODER_29)
              case 28: return BMC_DEVICE_UI_ENCODER_29;
            #endif
            #if BMC_MAX_ENCODERS > 29 && defined(BMC_DEVICE_UI_ENCODER_30)
              case 29: return BMC_DEVICE_UI_ENCODER_30;
            #endif
            #if BMC_MAX_ENCODERS > 30 && defined(BMC_DEVICE_UI_ENCODER_31)
              case 30: return BMC_DEVICE_UI_ENCODER_31;
            #endif
            #if BMC_MAX_ENCODERS > 31 && defined(BMC_DEVICE_UI_ENCODER_32)
              case 31: return BMC_DEVICE_UI_ENCODER_32;
            #endif
            #if BMC_MAX_ENCODERS > 32 && defined(BMC_DEVICE_UI_ENCODER_33)
              case 32: return BMC_DEVICE_UI_ENCODER_33;
            #endif
            #if BMC_MAX_ENCODERS > 33 && defined(BMC_DEVICE_UI_ENCODER_34)
              case 33: return BMC_DEVICE_UI_ENCODER_34;
            #endif
            #if BMC_MAX_ENCODERS > 34 && defined(BMC_DEVICE_UI_ENCODER_35)
              case 34: return BMC_DEVICE_UI_ENCODER_35;
            #endif
            #if BMC_MAX_ENCODERS > 35 && defined(BMC_DEVICE_UI_ENCODER_36)
              case 35: return BMC_DEVICE_UI_ENCODER_36;
            #endif
            #if BMC_MAX_ENCODERS > 36 && defined(BMC_DEVICE_UI_ENCODER_37)
              case 36: return BMC_DEVICE_UI_ENCODER_37;
            #endif
            #if BMC_MAX_ENCODERS > 37 && defined(BMC_DEVICE_UI_ENCODER_38)
              case 37: return BMC_DEVICE_UI_ENCODER_38;
            #endif
            #if BMC_MAX_ENCODERS > 38 && defined(BMC_DEVICE_UI_ENCODER_39)
              case 38: return BMC_DEVICE_UI_ENCODER_39;
            #endif
            #if BMC_MAX_ENCODERS > 39 && defined(BMC_DEVICE_UI_ENCODER_40)
              case 39: return BMC_DEVICE_UI_ENCODER_40;
            #endif
            #if BMC_MAX_ENCODERS > 40 && defined(BMC_DEVICE_UI_ENCODER_41)
              case 40: return BMC_DEVICE_UI_ENCODER_41;
            #endif
            #if BMC_MAX_ENCODERS > 41 && defined(BMC_DEVICE_UI_ENCODER_42)
              case 41: return BMC_DEVICE_UI_ENCODER_42;
            #endif
            #if BMC_MAX_ENCODERS > 42 && defined(BMC_DEVICE_UI_ENCODER_43)
              case 42: return BMC_DEVICE_UI_ENCODER_43;
            #endif
            #if BMC_MAX_ENCODERS > 43 && defined(BMC_DEVICE_UI_ENCODER_44)
              case 43: return BMC_DEVICE_UI_ENCODER_44;
            #endif
            #if BMC_MAX_ENCODERS > 44 && defined(BMC_DEVICE_UI_ENCODER_45)
              case 44: return BMC_DEVICE_UI_ENCODER_45;
            #endif
            #if BMC_MAX_ENCODERS > 45 && defined(BMC_DEVICE_UI_ENCODER_46)
              case 45: return BMC_DEVICE_UI_ENCODER_46;
            #endif
            #if BMC_MAX_ENCODERS > 46 && defined(BMC_DEVICE_UI_ENCODER_47)
              case 46: return BMC_DEVICE_UI_ENCODER_47;
            #endif
            #if BMC_MAX_ENCODERS > 47 && defined(BMC_DEVICE_UI_ENCODER_48)
              case 47: return BMC_DEVICE_UI_ENCODER_48;
            #endif
            #if BMC_MAX_ENCODERS > 48 && defined(BMC_DEVICE_UI_ENCODER_49)
              case 48: return BMC_DEVICE_UI_ENCODER_49;
            #endif
            #if BMC_MAX_ENCODERS > 49 && defined(BMC_DEVICE_UI_ENCODER_50)
              case 49: return BMC_DEVICE_UI_ENCODER_50;
            #endif
            #if BMC_MAX_ENCODERS > 50 && defined(BMC_DEVICE_UI_ENCODER_51)
              case 50: return BMC_DEVICE_UI_ENCODER_51;
            #endif
            #if BMC_MAX_ENCODERS > 51 && defined(BMC_DEVICE_UI_ENCODER_52)
              case 51: return BMC_DEVICE_UI_ENCODER_52;
            #endif
            #if BMC_MAX_ENCODERS > 52 && defined(BMC_DEVICE_UI_ENCODER_53)
              case 52: return BMC_DEVICE_UI_ENCODER_53;
            #endif
            #if BMC_MAX_ENCODERS > 53 && defined(BMC_DEVICE_UI_ENCODER_54)
              case 53: return BMC_DEVICE_UI_ENCODER_54;
            #endif
            #if BMC_MAX_ENCODERS > 54 && defined(BMC_DEVICE_UI_ENCODER_55)
              case 54: return BMC_DEVICE_UI_ENCODER_55;
            #endif
            #if BMC_MAX_ENCODERS > 55 && defined(BMC_DEVICE_UI_ENCODER_56)
              case 55: return BMC_DEVICE_UI_ENCODER_56;
            #endif
            #if BMC_MAX_ENCODERS > 56 && defined(BMC_DEVICE_UI_ENCODER_57)
              case 56: return BMC_DEVICE_UI_ENCODER_57;
            #endif
            #if BMC_MAX_ENCODERS > 57 && defined(BMC_DEVICE_UI_ENCODER_58)
              case 57: return BMC_DEVICE_UI_ENCODER_58;
            #endif
            #if BMC_MAX_ENCODERS > 58 && defined(BMC_DEVICE_UI_ENCODER_59)
              case 58: return BMC_DEVICE_UI_ENCODER_59;
            #endif
            #if BMC_MAX_ENCODERS > 59 && defined(BMC_DEVICE_UI_ENCODER_60)
              case 59: return BMC_DEVICE_UI_ENCODER_60;
            #endif
            #if BMC_MAX_ENCODERS > 60 && defined(BMC_DEVICE_UI_ENCODER_61)
              case 60: return BMC_DEVICE_UI_ENCODER_61;
            #endif
            #if BMC_MAX_ENCODERS > 61 && defined(BMC_DEVICE_UI_ENCODER_62)
              case 61: return BMC_DEVICE_UI_ENCODER_62;
            #endif
            #if BMC_MAX_ENCODERS > 62 && defined(BMC_DEVICE_UI_ENCODER_63)
              case 62: return BMC_DEVICE_UI_ENCODER_63;
            #endif
            #if BMC_MAX_ENCODERS > 63 && defined(BMC_DEVICE_UI_ENCODER_64)
              case 63: return BMC_DEVICE_UI_ENCODER_64;
            #endif
            #if BMC_MAX_ENCODERS > 64 && defined(BMC_DEVICE_UI_ENCODER_65)
              case 64: return BMC_DEVICE_UI_ENCODER_65;
            #endif
            #if BMC_MAX_ENCODERS > 65 && defined(BMC_DEVICE_UI_ENCODER_66)
              case 65: return BMC_DEVICE_UI_ENCODER_66;
            #endif
            #if BMC_MAX_ENCODERS > 66 && defined(BMC_DEVICE_UI_ENCODER_67)
              case 66: return BMC_DEVICE_UI_ENCODER_67;
            #endif
            #if BMC_MAX_ENCODERS > 67 && defined(BMC_DEVICE_UI_ENCODER_68)
              case 67: return BMC_DEVICE_UI_ENCODER_68;
            #endif
            #if BMC_MAX_ENCODERS > 68 && defined(BMC_DEVICE_UI_ENCODER_69)
              case 68: return BMC_DEVICE_UI_ENCODER_69;
            #endif
            #if BMC_MAX_ENCODERS > 69 && defined(BMC_DEVICE_UI_ENCODER_70)
              case 69: return BMC_DEVICE_UI_ENCODER_70;
            #endif
            #if BMC_MAX_ENCODERS > 70 && defined(BMC_DEVICE_UI_ENCODER_71)
              case 70: return BMC_DEVICE_UI_ENCODER_71;
            #endif
            #if BMC_MAX_ENCODERS > 71 && defined(BMC_DEVICE_UI_ENCODER_72)
              case 71: return BMC_DEVICE_UI_ENCODER_72;
            #endif
            #if BMC_MAX_ENCODERS > 72 && defined(BMC_DEVICE_UI_ENCODER_73)
              case 72: return BMC_DEVICE_UI_ENCODER_73;
            #endif
            #if BMC_MAX_ENCODERS > 73 && defined(BMC_DEVICE_UI_ENCODER_74)
              case 73: return BMC_DEVICE_UI_ENCODER_74;
            #endif
            #if BMC_MAX_ENCODERS > 74 && defined(BMC_DEVICE_UI_ENCODER_75)
              case 74: return BMC_DEVICE_UI_ENCODER_75;
            #endif
            #if BMC_MAX_ENCODERS > 75 && defined(BMC_DEVICE_UI_ENCODER_76)
              case 75: return BMC_DEVICE_UI_ENCODER_76;
            #endif
            #if BMC_MAX_ENCODERS > 76 && defined(BMC_DEVICE_UI_ENCODER_77)
              case 76: return BMC_DEVICE_UI_ENCODER_77;
            #endif
            #if BMC_MAX_ENCODERS > 77 && defined(BMC_DEVICE_UI_ENCODER_78)
              case 77: return BMC_DEVICE_UI_ENCODER_78;
            #endif
            #if BMC_MAX_ENCODERS > 78 && defined(BMC_DEVICE_UI_ENCODER_79)
              case 78: return BMC_DEVICE_UI_ENCODER_79;
            #endif
            #if BMC_MAX_ENCODERS > 79 && defined(BMC_DEVICE_UI_ENCODER_80)
              case 79: return BMC_DEVICE_UI_ENCODER_80;
            #endif
            #if BMC_MAX_ENCODERS > 80 && defined(BMC_DEVICE_UI_ENCODER_81)
              case 80: return BMC_DEVICE_UI_ENCODER_81;
            #endif
            #if BMC_MAX_ENCODERS > 81 && defined(BMC_DEVICE_UI_ENCODER_82)
              case 81: return BMC_DEVICE_UI_ENCODER_82;
            #endif
            #if BMC_MAX_ENCODERS > 82 && defined(BMC_DEVICE_UI_ENCODER_83)
              case 82: return BMC_DEVICE_UI_ENCODER_83;
            #endif
            #if BMC_MAX_ENCODERS > 83 && defined(BMC_DEVICE_UI_ENCODER_84)
              case 83: return BMC_DEVICE_UI_ENCODER_84;
            #endif
            #if BMC_MAX_ENCODERS > 84 && defined(BMC_DEVICE_UI_ENCODER_85)
              case 84: return BMC_DEVICE_UI_ENCODER_85;
            #endif
            #if BMC_MAX_ENCODERS > 85 && defined(BMC_DEVICE_UI_ENCODER_86)
              case 85: return BMC_DEVICE_UI_ENCODER_86;
            #endif
            #if BMC_MAX_ENCODERS > 86 && defined(BMC_DEVICE_UI_ENCODER_87)
              case 86: return BMC_DEVICE_UI_ENCODER_87;
            #endif
            #if BMC_MAX_ENCODERS > 87 && defined(BMC_DEVICE_UI_ENCODER_88)
              case 87: return BMC_DEVICE_UI_ENCODER_88;
            #endif
            #if BMC_MAX_ENCODERS > 88 && defined(BMC_DEVICE_UI_ENCODER_89)
              case 88: return BMC_DEVICE_UI_ENCODER_89;
            #endif
            #if BMC_MAX_ENCODERS > 89 && defined(BMC_DEVICE_UI_ENCODER_90)
              case 89: return BMC_DEVICE_UI_ENCODER_90;
            #endif
            #if BMC_MAX_ENCODERS > 90 && defined(BMC_DEVICE_UI_ENCODER_91)
              case 90: return BMC_DEVICE_UI_ENCODER_91;
            #endif
            #if BMC_MAX_ENCODERS > 91 && defined(BMC_DEVICE_UI_ENCODER_92)
              case 91: return BMC_DEVICE_UI_ENCODER_92;
            #endif
            #if BMC_MAX_ENCODERS > 92 && defined(BMC_DEVICE_UI_ENCODER_93)
              case 92: return BMC_DEVICE_UI_ENCODER_93;
            #endif
            #if BMC_MAX_ENCODERS > 93 && defined(BMC_DEVICE_UI_ENCODER_94)
              case 93: return BMC_DEVICE_UI_ENCODER_94;
            #endif
            #if BMC_MAX_ENCODERS > 94 && defined(BMC_DEVICE_UI_ENCODER_95)
              case 94: return BMC_DEVICE_UI_ENCODER_95;
            #endif
            #if BMC_MAX_ENCODERS > 95 && defined(BMC_DEVICE_UI_ENCODER_96)
              case 95: return BMC_DEVICE_UI_ENCODER_96;
            #endif
            #if BMC_MAX_ENCODERS > 96 && defined(BMC_DEVICE_UI_ENCODER_97)
              case 96: return BMC_DEVICE_UI_ENCODER_97;
            #endif
            #if BMC_MAX_ENCODERS > 97 && defined(BMC_DEVICE_UI_ENCODER_98)
              case 97: return BMC_DEVICE_UI_ENCODER_98;
            #endif
            #if BMC_MAX_ENCODERS > 98 && defined(BMC_DEVICE_UI_ENCODER_99)
              case 98: return BMC_DEVICE_UI_ENCODER_99;
            #endif
            #if BMC_MAX_ENCODERS > 99 && defined(BMC_DEVICE_UI_ENCODER_100)
              case 99: return BMC_DEVICE_UI_ENCODER_100;
            #endif
            #if BMC_MAX_ENCODERS > 100 && defined(BMC_DEVICE_UI_ENCODER_101)
              case 100: return BMC_DEVICE_UI_ENCODER_101;
            #endif
            #if BMC_MAX_ENCODERS > 101 && defined(BMC_DEVICE_UI_ENCODER_102)
              case 101: return BMC_DEVICE_UI_ENCODER_102;
            #endif
            #if BMC_MAX_ENCODERS > 102 && defined(BMC_DEVICE_UI_ENCODER_103)
              case 102: return BMC_DEVICE_UI_ENCODER_103;
            #endif
            #if BMC_MAX_ENCODERS > 103 && defined(BMC_DEVICE_UI_ENCODER_104)
              case 103: return BMC_DEVICE_UI_ENCODER_104;
            #endif
            #if BMC_MAX_ENCODERS > 104 && defined(BMC_DEVICE_UI_ENCODER_105)
              case 104: return BMC_DEVICE_UI_ENCODER_105;
            #endif
            #if BMC_MAX_ENCODERS > 105 && defined(BMC_DEVICE_UI_ENCODER_106)
              case 105: return BMC_DEVICE_UI_ENCODER_106;
            #endif
            #if BMC_MAX_ENCODERS > 106 && defined(BMC_DEVICE_UI_ENCODER_107)
              case 106: return BMC_DEVICE_UI_ENCODER_107;
            #endif
            #if BMC_MAX_ENCODERS > 107 && defined(BMC_DEVICE_UI_ENCODER_108)
              case 107: return BMC_DEVICE_UI_ENCODER_108;
            #endif
            #if BMC_MAX_ENCODERS > 108 && defined(BMC_DEVICE_UI_ENCODER_109)
              case 108: return BMC_DEVICE_UI_ENCODER_109;
            #endif
            #if BMC_MAX_ENCODERS > 109 && defined(BMC_DEVICE_UI_ENCODER_110)
              case 109: return BMC_DEVICE_UI_ENCODER_110;
            #endif
            #if BMC_MAX_ENCODERS > 110 && defined(BMC_DEVICE_UI_ENCODER_111)
              case 110: return BMC_DEVICE_UI_ENCODER_111;
            #endif
            #if BMC_MAX_ENCODERS > 111 && defined(BMC_DEVICE_UI_ENCODER_112)
              case 111: return BMC_DEVICE_UI_ENCODER_112;
            #endif
            #if BMC_MAX_ENCODERS > 112 && defined(BMC_DEVICE_UI_ENCODER_113)
              case 112: return BMC_DEVICE_UI_ENCODER_113;
            #endif
            #if BMC_MAX_ENCODERS > 113 && defined(BMC_DEVICE_UI_ENCODER_114)
              case 113: return BMC_DEVICE_UI_ENCODER_114;
            #endif
            #if BMC_MAX_ENCODERS > 114 && defined(BMC_DEVICE_UI_ENCODER_115)
              case 114: return BMC_DEVICE_UI_ENCODER_115;
            #endif
            #if BMC_MAX_ENCODERS > 115 && defined(BMC_DEVICE_UI_ENCODER_116)
              case 115: return BMC_DEVICE_UI_ENCODER_116;
            #endif
            #if BMC_MAX_ENCODERS > 116 && defined(BMC_DEVICE_UI_ENCODER_117)
              case 116: return BMC_DEVICE_UI_ENCODER_117;
            #endif
            #if BMC_MAX_ENCODERS > 117 && defined(BMC_DEVICE_UI_ENCODER_118)
              case 117: return BMC_DEVICE_UI_ENCODER_118;
            #endif
            #if BMC_MAX_ENCODERS > 118 && defined(BMC_DEVICE_UI_ENCODER_119)
              case 118: return BMC_DEVICE_UI_ENCODER_119;
            #endif
            #if BMC_MAX_ENCODERS > 119 && defined(BMC_DEVICE_UI_ENCODER_120)
              case 119: return BMC_DEVICE_UI_ENCODER_120;
            #endif
            #if BMC_MAX_ENCODERS > 120 && defined(BMC_DEVICE_UI_ENCODER_121)
              case 120: return BMC_DEVICE_UI_ENCODER_121;
            #endif
            #if BMC_MAX_ENCODERS > 121 && defined(BMC_DEVICE_UI_ENCODER_122)
              case 121: return BMC_DEVICE_UI_ENCODER_122;
            #endif
            #if BMC_MAX_ENCODERS > 122 && defined(BMC_DEVICE_UI_ENCODER_123)
              case 122: return BMC_DEVICE_UI_ENCODER_123;
            #endif
            #if BMC_MAX_ENCODERS > 123 && defined(BMC_DEVICE_UI_ENCODER_124)
              case 123: return BMC_DEVICE_UI_ENCODER_124;
            #endif
            #if BMC_MAX_ENCODERS > 124 && defined(BMC_DEVICE_UI_ENCODER_125)
              case 124: return BMC_DEVICE_UI_ENCODER_125;
            #endif
            #if BMC_MAX_ENCODERS > 125 && defined(BMC_DEVICE_UI_ENCODER_126)
              case 125: return BMC_DEVICE_UI_ENCODER_126;
            #endif
            #if BMC_MAX_ENCODERS > 126 && defined(BMC_DEVICE_UI_ENCODER_127)
              case 126: return BMC_DEVICE_UI_ENCODER_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_ENCODER:
          #if BMC_MAX_GLOBAL_ENCODERS > 0
            switch(n){
              #if BMC_MAX_GLOBAL_ENCODERS > 0 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_ENCODER_1;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 1 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_ENCODER_2;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 2 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_ENCODER_3;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 3 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_ENCODER_4;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 4 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_ENCODER_5;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 5 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_ENCODER_6;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 6 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_ENCODER_7;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 7 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_ENCODER_8;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 8 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_ENCODER_9;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 9 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_ENCODER_10;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 10 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_ENCODER_11;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 11 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_ENCODER_12;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 12 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_ENCODER_13;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 13 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_ENCODER_14;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 14 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_ENCODER_15;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 15 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_ENCODER_16;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 16 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_ENCODER_17;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 17 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_ENCODER_18;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 18 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_ENCODER_19;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 19 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_ENCODER_20;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 20 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_ENCODER_21;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 21 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_ENCODER_22;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 22 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_ENCODER_23;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 23 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_ENCODER_24;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 24 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_ENCODER_25;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 25 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_ENCODER_26;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 26 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_ENCODER_27;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 27 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_ENCODER_28;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 28 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_ENCODER_29;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 29 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_ENCODER_30;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 30 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_ENCODER_31;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 31 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_ENCODER_32;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 32 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_ENCODER_33;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 33 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_ENCODER_34;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 34 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_ENCODER_35;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 35 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_ENCODER_36;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 36 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_ENCODER_37;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 37 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_ENCODER_38;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 38 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_ENCODER_39;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 39 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_ENCODER_40;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 40 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_ENCODER_41;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 41 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_ENCODER_42;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 42 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_ENCODER_43;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 43 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_ENCODER_44;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 44 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_ENCODER_45;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 45 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_ENCODER_46;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 46 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_ENCODER_47;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 47 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_ENCODER_48;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 48 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_ENCODER_49;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 49 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_ENCODER_50;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 50 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_ENCODER_51;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 51 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_ENCODER_52;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 52 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_ENCODER_53;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 53 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_ENCODER_54;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 54 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_ENCODER_55;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 55 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_ENCODER_56;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 56 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_ENCODER_57;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 57 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_ENCODER_58;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 58 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_ENCODER_59;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 59 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_ENCODER_60;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 60 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_ENCODER_61;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 61 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_ENCODER_62;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 62 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_ENCODER_63;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 63 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_ENCODER_64;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 64 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_65)
              case 64: return BMC_DEVICE_UI_GLOBAL_ENCODER_65;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 65 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_66)
              case 65: return BMC_DEVICE_UI_GLOBAL_ENCODER_66;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 66 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_67)
              case 66: return BMC_DEVICE_UI_GLOBAL_ENCODER_67;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 67 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_68)
              case 67: return BMC_DEVICE_UI_GLOBAL_ENCODER_68;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 68 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_69)
              case 68: return BMC_DEVICE_UI_GLOBAL_ENCODER_69;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 69 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_70)
              case 69: return BMC_DEVICE_UI_GLOBAL_ENCODER_70;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 70 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_71)
              case 70: return BMC_DEVICE_UI_GLOBAL_ENCODER_71;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 71 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_72)
              case 71: return BMC_DEVICE_UI_GLOBAL_ENCODER_72;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 72 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_73)
              case 72: return BMC_DEVICE_UI_GLOBAL_ENCODER_73;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 73 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_74)
              case 73: return BMC_DEVICE_UI_GLOBAL_ENCODER_74;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 74 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_75)
              case 74: return BMC_DEVICE_UI_GLOBAL_ENCODER_75;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 75 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_76)
              case 75: return BMC_DEVICE_UI_GLOBAL_ENCODER_76;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 76 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_77)
              case 76: return BMC_DEVICE_UI_GLOBAL_ENCODER_77;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 77 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_78)
              case 77: return BMC_DEVICE_UI_GLOBAL_ENCODER_78;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 78 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_79)
              case 78: return BMC_DEVICE_UI_GLOBAL_ENCODER_79;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 79 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_80)
              case 79: return BMC_DEVICE_UI_GLOBAL_ENCODER_80;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 80 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_81)
              case 80: return BMC_DEVICE_UI_GLOBAL_ENCODER_81;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 81 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_82)
              case 81: return BMC_DEVICE_UI_GLOBAL_ENCODER_82;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 82 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_83)
              case 82: return BMC_DEVICE_UI_GLOBAL_ENCODER_83;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 83 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_84)
              case 83: return BMC_DEVICE_UI_GLOBAL_ENCODER_84;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 84 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_85)
              case 84: return BMC_DEVICE_UI_GLOBAL_ENCODER_85;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 85 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_86)
              case 85: return BMC_DEVICE_UI_GLOBAL_ENCODER_86;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 86 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_87)
              case 86: return BMC_DEVICE_UI_GLOBAL_ENCODER_87;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 87 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_88)
              case 87: return BMC_DEVICE_UI_GLOBAL_ENCODER_88;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 88 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_89)
              case 88: return BMC_DEVICE_UI_GLOBAL_ENCODER_89;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 89 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_90)
              case 89: return BMC_DEVICE_UI_GLOBAL_ENCODER_90;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 90 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_91)
              case 90: return BMC_DEVICE_UI_GLOBAL_ENCODER_91;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 91 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_92)
              case 91: return BMC_DEVICE_UI_GLOBAL_ENCODER_92;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 92 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_93)
              case 92: return BMC_DEVICE_UI_GLOBAL_ENCODER_93;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 93 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_94)
              case 93: return BMC_DEVICE_UI_GLOBAL_ENCODER_94;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 94 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_95)
              case 94: return BMC_DEVICE_UI_GLOBAL_ENCODER_95;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 95 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_96)
              case 95: return BMC_DEVICE_UI_GLOBAL_ENCODER_96;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 96 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_97)
              case 96: return BMC_DEVICE_UI_GLOBAL_ENCODER_97;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 97 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_98)
              case 97: return BMC_DEVICE_UI_GLOBAL_ENCODER_98;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 98 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_99)
              case 98: return BMC_DEVICE_UI_GLOBAL_ENCODER_99;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 99 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_100)
              case 99: return BMC_DEVICE_UI_GLOBAL_ENCODER_100;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 100 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_101)
              case 100: return BMC_DEVICE_UI_GLOBAL_ENCODER_101;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 101 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_102)
              case 101: return BMC_DEVICE_UI_GLOBAL_ENCODER_102;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 102 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_103)
              case 102: return BMC_DEVICE_UI_GLOBAL_ENCODER_103;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 103 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_104)
              case 103: return BMC_DEVICE_UI_GLOBAL_ENCODER_104;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 104 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_105)
              case 104: return BMC_DEVICE_UI_GLOBAL_ENCODER_105;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 105 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_106)
              case 105: return BMC_DEVICE_UI_GLOBAL_ENCODER_106;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 106 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_107)
              case 106: return BMC_DEVICE_UI_GLOBAL_ENCODER_107;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 107 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_108)
              case 107: return BMC_DEVICE_UI_GLOBAL_ENCODER_108;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 108 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_109)
              case 108: return BMC_DEVICE_UI_GLOBAL_ENCODER_109;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 109 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_110)
              case 109: return BMC_DEVICE_UI_GLOBAL_ENCODER_110;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 110 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_111)
              case 110: return BMC_DEVICE_UI_GLOBAL_ENCODER_111;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 111 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_112)
              case 111: return BMC_DEVICE_UI_GLOBAL_ENCODER_112;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 112 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_113)
              case 112: return BMC_DEVICE_UI_GLOBAL_ENCODER_113;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 113 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_114)
              case 113: return BMC_DEVICE_UI_GLOBAL_ENCODER_114;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 114 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_115)
              case 114: return BMC_DEVICE_UI_GLOBAL_ENCODER_115;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 115 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_116)
              case 115: return BMC_DEVICE_UI_GLOBAL_ENCODER_116;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 116 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_117)
              case 116: return BMC_DEVICE_UI_GLOBAL_ENCODER_117;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 117 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_118)
              case 117: return BMC_DEVICE_UI_GLOBAL_ENCODER_118;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 118 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_119)
              case 118: return BMC_DEVICE_UI_GLOBAL_ENCODER_119;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 119 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_120)
              case 119: return BMC_DEVICE_UI_GLOBAL_ENCODER_120;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 120 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_121)
              case 120: return BMC_DEVICE_UI_GLOBAL_ENCODER_121;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 121 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_122)
              case 121: return BMC_DEVICE_UI_GLOBAL_ENCODER_122;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 122 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_123)
              case 122: return BMC_DEVICE_UI_GLOBAL_ENCODER_123;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 123 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_124)
              case 123: return BMC_DEVICE_UI_GLOBAL_ENCODER_124;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 124 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_125)
              case 124: return BMC_DEVICE_UI_GLOBAL_ENCODER_125;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 125 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_126)
              case 125: return BMC_DEVICE_UI_GLOBAL_ENCODER_126;
            #endif
            #if BMC_MAX_GLOBAL_ENCODERS > 126 && defined(BMC_DEVICE_UI_GLOBAL_ENCODER_127)
              case 126: return BMC_DEVICE_UI_GLOBAL_ENCODER_127;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_NL_RELAY:
          #if BMC_MAX_NL_RELAYS > 0
            switch(n){
              #if BMC_MAX_NL_RELAYS > 0 && defined(BMC_DEVICE_UI_NL_RELAY_1)
              case 0: return BMC_DEVICE_UI_NL_RELAY_1;
            #endif
            #if BMC_MAX_NL_RELAYS > 1 && defined(BMC_DEVICE_UI_NL_RELAY_2)
              case 1: return BMC_DEVICE_UI_NL_RELAY_2;
            #endif
            #if BMC_MAX_NL_RELAYS > 2 && defined(BMC_DEVICE_UI_NL_RELAY_3)
              case 2: return BMC_DEVICE_UI_NL_RELAY_3;
            #endif
            #if BMC_MAX_NL_RELAYS > 3 && defined(BMC_DEVICE_UI_NL_RELAY_4)
              case 3: return BMC_DEVICE_UI_NL_RELAY_4;
            #endif
            #if BMC_MAX_NL_RELAYS > 4 && defined(BMC_DEVICE_UI_NL_RELAY_5)
              case 4: return BMC_DEVICE_UI_NL_RELAY_5;
            #endif
            #if BMC_MAX_NL_RELAYS > 5 && defined(BMC_DEVICE_UI_NL_RELAY_6)
              case 5: return BMC_DEVICE_UI_NL_RELAY_6;
            #endif
            #if BMC_MAX_NL_RELAYS > 6 && defined(BMC_DEVICE_UI_NL_RELAY_7)
              case 6: return BMC_DEVICE_UI_NL_RELAY_7;
            #endif
            #if BMC_MAX_NL_RELAYS > 7 && defined(BMC_DEVICE_UI_NL_RELAY_8)
              case 7: return BMC_DEVICE_UI_NL_RELAY_8;
            #endif
            #if BMC_MAX_NL_RELAYS > 8 && defined(BMC_DEVICE_UI_NL_RELAY_9)
              case 8: return BMC_DEVICE_UI_NL_RELAY_9;
            #endif
            #if BMC_MAX_NL_RELAYS > 9 && defined(BMC_DEVICE_UI_NL_RELAY_10)
              case 9: return BMC_DEVICE_UI_NL_RELAY_10;
            #endif
            #if BMC_MAX_NL_RELAYS > 10 && defined(BMC_DEVICE_UI_NL_RELAY_11)
              case 10: return BMC_DEVICE_UI_NL_RELAY_11;
            #endif
            #if BMC_MAX_NL_RELAYS > 11 && defined(BMC_DEVICE_UI_NL_RELAY_12)
              case 11: return BMC_DEVICE_UI_NL_RELAY_12;
            #endif
            #if BMC_MAX_NL_RELAYS > 12 && defined(BMC_DEVICE_UI_NL_RELAY_13)
              case 12: return BMC_DEVICE_UI_NL_RELAY_13;
            #endif
            #if BMC_MAX_NL_RELAYS > 13 && defined(BMC_DEVICE_UI_NL_RELAY_14)
              case 13: return BMC_DEVICE_UI_NL_RELAY_14;
            #endif
            #if BMC_MAX_NL_RELAYS > 14 && defined(BMC_DEVICE_UI_NL_RELAY_15)
              case 14: return BMC_DEVICE_UI_NL_RELAY_15;
            #endif
            #if BMC_MAX_NL_RELAYS > 15 && defined(BMC_DEVICE_UI_NL_RELAY_16)
              case 15: return BMC_DEVICE_UI_NL_RELAY_16;
            #endif
            #if BMC_MAX_NL_RELAYS > 16 && defined(BMC_DEVICE_UI_NL_RELAY_17)
              case 16: return BMC_DEVICE_UI_NL_RELAY_17;
            #endif
            #if BMC_MAX_NL_RELAYS > 17 && defined(BMC_DEVICE_UI_NL_RELAY_18)
              case 17: return BMC_DEVICE_UI_NL_RELAY_18;
            #endif
            #if BMC_MAX_NL_RELAYS > 18 && defined(BMC_DEVICE_UI_NL_RELAY_19)
              case 18: return BMC_DEVICE_UI_NL_RELAY_19;
            #endif
            #if BMC_MAX_NL_RELAYS > 19 && defined(BMC_DEVICE_UI_NL_RELAY_20)
              case 19: return BMC_DEVICE_UI_NL_RELAY_20;
            #endif
            #if BMC_MAX_NL_RELAYS > 20 && defined(BMC_DEVICE_UI_NL_RELAY_21)
              case 20: return BMC_DEVICE_UI_NL_RELAY_21;
            #endif
            #if BMC_MAX_NL_RELAYS > 21 && defined(BMC_DEVICE_UI_NL_RELAY_22)
              case 21: return BMC_DEVICE_UI_NL_RELAY_22;
            #endif
            #if BMC_MAX_NL_RELAYS > 22 && defined(BMC_DEVICE_UI_NL_RELAY_23)
              case 22: return BMC_DEVICE_UI_NL_RELAY_23;
            #endif
            #if BMC_MAX_NL_RELAYS > 23 && defined(BMC_DEVICE_UI_NL_RELAY_24)
              case 23: return BMC_DEVICE_UI_NL_RELAY_24;
            #endif
            #if BMC_MAX_NL_RELAYS > 24 && defined(BMC_DEVICE_UI_NL_RELAY_25)
              case 24: return BMC_DEVICE_UI_NL_RELAY_25;
            #endif
            #if BMC_MAX_NL_RELAYS > 25 && defined(BMC_DEVICE_UI_NL_RELAY_26)
              case 25: return BMC_DEVICE_UI_NL_RELAY_26;
            #endif
            #if BMC_MAX_NL_RELAYS > 26 && defined(BMC_DEVICE_UI_NL_RELAY_27)
              case 26: return BMC_DEVICE_UI_NL_RELAY_27;
            #endif
            #if BMC_MAX_NL_RELAYS > 27 && defined(BMC_DEVICE_UI_NL_RELAY_28)
              case 27: return BMC_DEVICE_UI_NL_RELAY_28;
            #endif
            #if BMC_MAX_NL_RELAYS > 28 && defined(BMC_DEVICE_UI_NL_RELAY_29)
              case 28: return BMC_DEVICE_UI_NL_RELAY_29;
            #endif
            #if BMC_MAX_NL_RELAYS > 29 && defined(BMC_DEVICE_UI_NL_RELAY_30)
              case 29: return BMC_DEVICE_UI_NL_RELAY_30;
            #endif
            #if BMC_MAX_NL_RELAYS > 30 && defined(BMC_DEVICE_UI_NL_RELAY_31)
              case 30: return BMC_DEVICE_UI_NL_RELAY_31;
            #endif
            #if BMC_MAX_NL_RELAYS > 31 && defined(BMC_DEVICE_UI_NL_RELAY_32)
              case 31: return BMC_DEVICE_UI_NL_RELAY_32;
            #endif
            #if BMC_MAX_NL_RELAYS > 32 && defined(BMC_DEVICE_UI_NL_RELAY_33)
              case 32: return BMC_DEVICE_UI_NL_RELAY_33;
            #endif
            #if BMC_MAX_NL_RELAYS > 33 && defined(BMC_DEVICE_UI_NL_RELAY_34)
              case 33: return BMC_DEVICE_UI_NL_RELAY_34;
            #endif
            #if BMC_MAX_NL_RELAYS > 34 && defined(BMC_DEVICE_UI_NL_RELAY_35)
              case 34: return BMC_DEVICE_UI_NL_RELAY_35;
            #endif
            #if BMC_MAX_NL_RELAYS > 35 && defined(BMC_DEVICE_UI_NL_RELAY_36)
              case 35: return BMC_DEVICE_UI_NL_RELAY_36;
            #endif
            #if BMC_MAX_NL_RELAYS > 36 && defined(BMC_DEVICE_UI_NL_RELAY_37)
              case 36: return BMC_DEVICE_UI_NL_RELAY_37;
            #endif
            #if BMC_MAX_NL_RELAYS > 37 && defined(BMC_DEVICE_UI_NL_RELAY_38)
              case 37: return BMC_DEVICE_UI_NL_RELAY_38;
            #endif
            #if BMC_MAX_NL_RELAYS > 38 && defined(BMC_DEVICE_UI_NL_RELAY_39)
              case 38: return BMC_DEVICE_UI_NL_RELAY_39;
            #endif
            #if BMC_MAX_NL_RELAYS > 39 && defined(BMC_DEVICE_UI_NL_RELAY_40)
              case 39: return BMC_DEVICE_UI_NL_RELAY_40;
            #endif
            #if BMC_MAX_NL_RELAYS > 40 && defined(BMC_DEVICE_UI_NL_RELAY_41)
              case 40: return BMC_DEVICE_UI_NL_RELAY_41;
            #endif
            #if BMC_MAX_NL_RELAYS > 41 && defined(BMC_DEVICE_UI_NL_RELAY_42)
              case 41: return BMC_DEVICE_UI_NL_RELAY_42;
            #endif
            #if BMC_MAX_NL_RELAYS > 42 && defined(BMC_DEVICE_UI_NL_RELAY_43)
              case 42: return BMC_DEVICE_UI_NL_RELAY_43;
            #endif
            #if BMC_MAX_NL_RELAYS > 43 && defined(BMC_DEVICE_UI_NL_RELAY_44)
              case 43: return BMC_DEVICE_UI_NL_RELAY_44;
            #endif
            #if BMC_MAX_NL_RELAYS > 44 && defined(BMC_DEVICE_UI_NL_RELAY_45)
              case 44: return BMC_DEVICE_UI_NL_RELAY_45;
            #endif
            #if BMC_MAX_NL_RELAYS > 45 && defined(BMC_DEVICE_UI_NL_RELAY_46)
              case 45: return BMC_DEVICE_UI_NL_RELAY_46;
            #endif
            #if BMC_MAX_NL_RELAYS > 46 && defined(BMC_DEVICE_UI_NL_RELAY_47)
              case 46: return BMC_DEVICE_UI_NL_RELAY_47;
            #endif
            #if BMC_MAX_NL_RELAYS > 47 && defined(BMC_DEVICE_UI_NL_RELAY_48)
              case 47: return BMC_DEVICE_UI_NL_RELAY_48;
            #endif
            #if BMC_MAX_NL_RELAYS > 48 && defined(BMC_DEVICE_UI_NL_RELAY_49)
              case 48: return BMC_DEVICE_UI_NL_RELAY_49;
            #endif
            #if BMC_MAX_NL_RELAYS > 49 && defined(BMC_DEVICE_UI_NL_RELAY_50)
              case 49: return BMC_DEVICE_UI_NL_RELAY_50;
            #endif
            #if BMC_MAX_NL_RELAYS > 50 && defined(BMC_DEVICE_UI_NL_RELAY_51)
              case 50: return BMC_DEVICE_UI_NL_RELAY_51;
            #endif
            #if BMC_MAX_NL_RELAYS > 51 && defined(BMC_DEVICE_UI_NL_RELAY_52)
              case 51: return BMC_DEVICE_UI_NL_RELAY_52;
            #endif
            #if BMC_MAX_NL_RELAYS > 52 && defined(BMC_DEVICE_UI_NL_RELAY_53)
              case 52: return BMC_DEVICE_UI_NL_RELAY_53;
            #endif
            #if BMC_MAX_NL_RELAYS > 53 && defined(BMC_DEVICE_UI_NL_RELAY_54)
              case 53: return BMC_DEVICE_UI_NL_RELAY_54;
            #endif
            #if BMC_MAX_NL_RELAYS > 54 && defined(BMC_DEVICE_UI_NL_RELAY_55)
              case 54: return BMC_DEVICE_UI_NL_RELAY_55;
            #endif
            #if BMC_MAX_NL_RELAYS > 55 && defined(BMC_DEVICE_UI_NL_RELAY_56)
              case 55: return BMC_DEVICE_UI_NL_RELAY_56;
            #endif
            #if BMC_MAX_NL_RELAYS > 56 && defined(BMC_DEVICE_UI_NL_RELAY_57)
              case 56: return BMC_DEVICE_UI_NL_RELAY_57;
            #endif
            #if BMC_MAX_NL_RELAYS > 57 && defined(BMC_DEVICE_UI_NL_RELAY_58)
              case 57: return BMC_DEVICE_UI_NL_RELAY_58;
            #endif
            #if BMC_MAX_NL_RELAYS > 58 && defined(BMC_DEVICE_UI_NL_RELAY_59)
              case 58: return BMC_DEVICE_UI_NL_RELAY_59;
            #endif
            #if BMC_MAX_NL_RELAYS > 59 && defined(BMC_DEVICE_UI_NL_RELAY_60)
              case 59: return BMC_DEVICE_UI_NL_RELAY_60;
            #endif
            #if BMC_MAX_NL_RELAYS > 60 && defined(BMC_DEVICE_UI_NL_RELAY_61)
              case 60: return BMC_DEVICE_UI_NL_RELAY_61;
            #endif
            #if BMC_MAX_NL_RELAYS > 61 && defined(BMC_DEVICE_UI_NL_RELAY_62)
              case 61: return BMC_DEVICE_UI_NL_RELAY_62;
            #endif
            #if BMC_MAX_NL_RELAYS > 62 && defined(BMC_DEVICE_UI_NL_RELAY_63)
              case 62: return BMC_DEVICE_UI_NL_RELAY_63;
            #endif
            #if BMC_MAX_NL_RELAYS > 63 && defined(BMC_DEVICE_UI_NL_RELAY_64)
              case 63: return BMC_DEVICE_UI_NL_RELAY_64;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_L_RELAY:
          #if BMC_MAX_L_RELAYS > 0
            switch(n){
              #if BMC_MAX_L_RELAYS > 0 && defined(BMC_DEVICE_UI_L_RELAY_1)
              case 0: return BMC_DEVICE_UI_L_RELAY_1;
            #endif
            #if BMC_MAX_L_RELAYS > 1 && defined(BMC_DEVICE_UI_L_RELAY_2)
              case 1: return BMC_DEVICE_UI_L_RELAY_2;
            #endif
            #if BMC_MAX_L_RELAYS > 2 && defined(BMC_DEVICE_UI_L_RELAY_3)
              case 2: return BMC_DEVICE_UI_L_RELAY_3;
            #endif
            #if BMC_MAX_L_RELAYS > 3 && defined(BMC_DEVICE_UI_L_RELAY_4)
              case 3: return BMC_DEVICE_UI_L_RELAY_4;
            #endif
            #if BMC_MAX_L_RELAYS > 4 && defined(BMC_DEVICE_UI_L_RELAY_5)
              case 4: return BMC_DEVICE_UI_L_RELAY_5;
            #endif
            #if BMC_MAX_L_RELAYS > 5 && defined(BMC_DEVICE_UI_L_RELAY_6)
              case 5: return BMC_DEVICE_UI_L_RELAY_6;
            #endif
            #if BMC_MAX_L_RELAYS > 6 && defined(BMC_DEVICE_UI_L_RELAY_7)
              case 6: return BMC_DEVICE_UI_L_RELAY_7;
            #endif
            #if BMC_MAX_L_RELAYS > 7 && defined(BMC_DEVICE_UI_L_RELAY_8)
              case 7: return BMC_DEVICE_UI_L_RELAY_8;
            #endif
            #if BMC_MAX_L_RELAYS > 8 && defined(BMC_DEVICE_UI_L_RELAY_9)
              case 8: return BMC_DEVICE_UI_L_RELAY_9;
            #endif
            #if BMC_MAX_L_RELAYS > 9 && defined(BMC_DEVICE_UI_L_RELAY_10)
              case 9: return BMC_DEVICE_UI_L_RELAY_10;
            #endif
            #if BMC_MAX_L_RELAYS > 10 && defined(BMC_DEVICE_UI_L_RELAY_11)
              case 10: return BMC_DEVICE_UI_L_RELAY_11;
            #endif
            #if BMC_MAX_L_RELAYS > 11 && defined(BMC_DEVICE_UI_L_RELAY_12)
              case 11: return BMC_DEVICE_UI_L_RELAY_12;
            #endif
            #if BMC_MAX_L_RELAYS > 12 && defined(BMC_DEVICE_UI_L_RELAY_13)
              case 12: return BMC_DEVICE_UI_L_RELAY_13;
            #endif
            #if BMC_MAX_L_RELAYS > 13 && defined(BMC_DEVICE_UI_L_RELAY_14)
              case 13: return BMC_DEVICE_UI_L_RELAY_14;
            #endif
            #if BMC_MAX_L_RELAYS > 14 && defined(BMC_DEVICE_UI_L_RELAY_15)
              case 14: return BMC_DEVICE_UI_L_RELAY_15;
            #endif
            #if BMC_MAX_L_RELAYS > 15 && defined(BMC_DEVICE_UI_L_RELAY_16)
              case 15: return BMC_DEVICE_UI_L_RELAY_16;
            #endif
            #if BMC_MAX_L_RELAYS > 16 && defined(BMC_DEVICE_UI_L_RELAY_17)
              case 16: return BMC_DEVICE_UI_L_RELAY_17;
            #endif
            #if BMC_MAX_L_RELAYS > 17 && defined(BMC_DEVICE_UI_L_RELAY_18)
              case 17: return BMC_DEVICE_UI_L_RELAY_18;
            #endif
            #if BMC_MAX_L_RELAYS > 18 && defined(BMC_DEVICE_UI_L_RELAY_19)
              case 18: return BMC_DEVICE_UI_L_RELAY_19;
            #endif
            #if BMC_MAX_L_RELAYS > 19 && defined(BMC_DEVICE_UI_L_RELAY_20)
              case 19: return BMC_DEVICE_UI_L_RELAY_20;
            #endif
            #if BMC_MAX_L_RELAYS > 20 && defined(BMC_DEVICE_UI_L_RELAY_21)
              case 20: return BMC_DEVICE_UI_L_RELAY_21;
            #endif
            #if BMC_MAX_L_RELAYS > 21 && defined(BMC_DEVICE_UI_L_RELAY_22)
              case 21: return BMC_DEVICE_UI_L_RELAY_22;
            #endif
            #if BMC_MAX_L_RELAYS > 22 && defined(BMC_DEVICE_UI_L_RELAY_23)
              case 22: return BMC_DEVICE_UI_L_RELAY_23;
            #endif
            #if BMC_MAX_L_RELAYS > 23 && defined(BMC_DEVICE_UI_L_RELAY_24)
              case 23: return BMC_DEVICE_UI_L_RELAY_24;
            #endif
            #if BMC_MAX_L_RELAYS > 24 && defined(BMC_DEVICE_UI_L_RELAY_25)
              case 24: return BMC_DEVICE_UI_L_RELAY_25;
            #endif
            #if BMC_MAX_L_RELAYS > 25 && defined(BMC_DEVICE_UI_L_RELAY_26)
              case 25: return BMC_DEVICE_UI_L_RELAY_26;
            #endif
            #if BMC_MAX_L_RELAYS > 26 && defined(BMC_DEVICE_UI_L_RELAY_27)
              case 26: return BMC_DEVICE_UI_L_RELAY_27;
            #endif
            #if BMC_MAX_L_RELAYS > 27 && defined(BMC_DEVICE_UI_L_RELAY_28)
              case 27: return BMC_DEVICE_UI_L_RELAY_28;
            #endif
            #if BMC_MAX_L_RELAYS > 28 && defined(BMC_DEVICE_UI_L_RELAY_29)
              case 28: return BMC_DEVICE_UI_L_RELAY_29;
            #endif
            #if BMC_MAX_L_RELAYS > 29 && defined(BMC_DEVICE_UI_L_RELAY_30)
              case 29: return BMC_DEVICE_UI_L_RELAY_30;
            #endif
            #if BMC_MAX_L_RELAYS > 30 && defined(BMC_DEVICE_UI_L_RELAY_31)
              case 30: return BMC_DEVICE_UI_L_RELAY_31;
            #endif
            #if BMC_MAX_L_RELAYS > 31 && defined(BMC_DEVICE_UI_L_RELAY_32)
              case 31: return BMC_DEVICE_UI_L_RELAY_32;
            #endif
            #if BMC_MAX_L_RELAYS > 32 && defined(BMC_DEVICE_UI_L_RELAY_33)
              case 32: return BMC_DEVICE_UI_L_RELAY_33;
            #endif
            #if BMC_MAX_L_RELAYS > 33 && defined(BMC_DEVICE_UI_L_RELAY_34)
              case 33: return BMC_DEVICE_UI_L_RELAY_34;
            #endif
            #if BMC_MAX_L_RELAYS > 34 && defined(BMC_DEVICE_UI_L_RELAY_35)
              case 34: return BMC_DEVICE_UI_L_RELAY_35;
            #endif
            #if BMC_MAX_L_RELAYS > 35 && defined(BMC_DEVICE_UI_L_RELAY_36)
              case 35: return BMC_DEVICE_UI_L_RELAY_36;
            #endif
            #if BMC_MAX_L_RELAYS > 36 && defined(BMC_DEVICE_UI_L_RELAY_37)
              case 36: return BMC_DEVICE_UI_L_RELAY_37;
            #endif
            #if BMC_MAX_L_RELAYS > 37 && defined(BMC_DEVICE_UI_L_RELAY_38)
              case 37: return BMC_DEVICE_UI_L_RELAY_38;
            #endif
            #if BMC_MAX_L_RELAYS > 38 && defined(BMC_DEVICE_UI_L_RELAY_39)
              case 38: return BMC_DEVICE_UI_L_RELAY_39;
            #endif
            #if BMC_MAX_L_RELAYS > 39 && defined(BMC_DEVICE_UI_L_RELAY_40)
              case 39: return BMC_DEVICE_UI_L_RELAY_40;
            #endif
            #if BMC_MAX_L_RELAYS > 40 && defined(BMC_DEVICE_UI_L_RELAY_41)
              case 40: return BMC_DEVICE_UI_L_RELAY_41;
            #endif
            #if BMC_MAX_L_RELAYS > 41 && defined(BMC_DEVICE_UI_L_RELAY_42)
              case 41: return BMC_DEVICE_UI_L_RELAY_42;
            #endif
            #if BMC_MAX_L_RELAYS > 42 && defined(BMC_DEVICE_UI_L_RELAY_43)
              case 42: return BMC_DEVICE_UI_L_RELAY_43;
            #endif
            #if BMC_MAX_L_RELAYS > 43 && defined(BMC_DEVICE_UI_L_RELAY_44)
              case 43: return BMC_DEVICE_UI_L_RELAY_44;
            #endif
            #if BMC_MAX_L_RELAYS > 44 && defined(BMC_DEVICE_UI_L_RELAY_45)
              case 44: return BMC_DEVICE_UI_L_RELAY_45;
            #endif
            #if BMC_MAX_L_RELAYS > 45 && defined(BMC_DEVICE_UI_L_RELAY_46)
              case 45: return BMC_DEVICE_UI_L_RELAY_46;
            #endif
            #if BMC_MAX_L_RELAYS > 46 && defined(BMC_DEVICE_UI_L_RELAY_47)
              case 46: return BMC_DEVICE_UI_L_RELAY_47;
            #endif
            #if BMC_MAX_L_RELAYS > 47 && defined(BMC_DEVICE_UI_L_RELAY_48)
              case 47: return BMC_DEVICE_UI_L_RELAY_48;
            #endif
            #if BMC_MAX_L_RELAYS > 48 && defined(BMC_DEVICE_UI_L_RELAY_49)
              case 48: return BMC_DEVICE_UI_L_RELAY_49;
            #endif
            #if BMC_MAX_L_RELAYS > 49 && defined(BMC_DEVICE_UI_L_RELAY_50)
              case 49: return BMC_DEVICE_UI_L_RELAY_50;
            #endif
            #if BMC_MAX_L_RELAYS > 50 && defined(BMC_DEVICE_UI_L_RELAY_51)
              case 50: return BMC_DEVICE_UI_L_RELAY_51;
            #endif
            #if BMC_MAX_L_RELAYS > 51 && defined(BMC_DEVICE_UI_L_RELAY_52)
              case 51: return BMC_DEVICE_UI_L_RELAY_52;
            #endif
            #if BMC_MAX_L_RELAYS > 52 && defined(BMC_DEVICE_UI_L_RELAY_53)
              case 52: return BMC_DEVICE_UI_L_RELAY_53;
            #endif
            #if BMC_MAX_L_RELAYS > 53 && defined(BMC_DEVICE_UI_L_RELAY_54)
              case 53: return BMC_DEVICE_UI_L_RELAY_54;
            #endif
            #if BMC_MAX_L_RELAYS > 54 && defined(BMC_DEVICE_UI_L_RELAY_55)
              case 54: return BMC_DEVICE_UI_L_RELAY_55;
            #endif
            #if BMC_MAX_L_RELAYS > 55 && defined(BMC_DEVICE_UI_L_RELAY_56)
              case 55: return BMC_DEVICE_UI_L_RELAY_56;
            #endif
            #if BMC_MAX_L_RELAYS > 56 && defined(BMC_DEVICE_UI_L_RELAY_57)
              case 56: return BMC_DEVICE_UI_L_RELAY_57;
            #endif
            #if BMC_MAX_L_RELAYS > 57 && defined(BMC_DEVICE_UI_L_RELAY_58)
              case 57: return BMC_DEVICE_UI_L_RELAY_58;
            #endif
            #if BMC_MAX_L_RELAYS > 58 && defined(BMC_DEVICE_UI_L_RELAY_59)
              case 58: return BMC_DEVICE_UI_L_RELAY_59;
            #endif
            #if BMC_MAX_L_RELAYS > 59 && defined(BMC_DEVICE_UI_L_RELAY_60)
              case 59: return BMC_DEVICE_UI_L_RELAY_60;
            #endif
            #if BMC_MAX_L_RELAYS > 60 && defined(BMC_DEVICE_UI_L_RELAY_61)
              case 60: return BMC_DEVICE_UI_L_RELAY_61;
            #endif
            #if BMC_MAX_L_RELAYS > 61 && defined(BMC_DEVICE_UI_L_RELAY_62)
              case 61: return BMC_DEVICE_UI_L_RELAY_62;
            #endif
            #if BMC_MAX_L_RELAYS > 62 && defined(BMC_DEVICE_UI_L_RELAY_63)
              case 62: return BMC_DEVICE_UI_L_RELAY_63;
            #endif
            #if BMC_MAX_L_RELAYS > 63 && defined(BMC_DEVICE_UI_L_RELAY_64)
              case 63: return BMC_DEVICE_UI_L_RELAY_64;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_OLED:
          #if BMC_MAX_OLED > 0
            switch(n){
              #if BMC_MAX_OLED > 0 && defined(BMC_DEVICE_UI_OLED_1)
              case 0: return BMC_DEVICE_UI_OLED_1;
            #endif
            #if BMC_MAX_OLED > 1 && defined(BMC_DEVICE_UI_OLED_2)
              case 1: return BMC_DEVICE_UI_OLED_2;
            #endif
            #if BMC_MAX_OLED > 2 && defined(BMC_DEVICE_UI_OLED_3)
              case 2: return BMC_DEVICE_UI_OLED_3;
            #endif
            #if BMC_MAX_OLED > 3 && defined(BMC_DEVICE_UI_OLED_4)
              case 3: return BMC_DEVICE_UI_OLED_4;
            #endif
            #if BMC_MAX_OLED > 4 && defined(BMC_DEVICE_UI_OLED_5)
              case 4: return BMC_DEVICE_UI_OLED_5;
            #endif
            #if BMC_MAX_OLED > 5 && defined(BMC_DEVICE_UI_OLED_6)
              case 5: return BMC_DEVICE_UI_OLED_6;
            #endif
            #if BMC_MAX_OLED > 6 && defined(BMC_DEVICE_UI_OLED_7)
              case 6: return BMC_DEVICE_UI_OLED_7;
            #endif
            #if BMC_MAX_OLED > 7 && defined(BMC_DEVICE_UI_OLED_8)
              case 7: return BMC_DEVICE_UI_OLED_8;
            #endif
            #if BMC_MAX_OLED > 8 && defined(BMC_DEVICE_UI_OLED_9)
              case 8: return BMC_DEVICE_UI_OLED_9;
            #endif
            #if BMC_MAX_OLED > 9 && defined(BMC_DEVICE_UI_OLED_10)
              case 9: return BMC_DEVICE_UI_OLED_10;
            #endif
            #if BMC_MAX_OLED > 10 && defined(BMC_DEVICE_UI_OLED_11)
              case 10: return BMC_DEVICE_UI_OLED_11;
            #endif
            #if BMC_MAX_OLED > 11 && defined(BMC_DEVICE_UI_OLED_12)
              case 11: return BMC_DEVICE_UI_OLED_12;
            #endif
            #if BMC_MAX_OLED > 12 && defined(BMC_DEVICE_UI_OLED_13)
              case 12: return BMC_DEVICE_UI_OLED_13;
            #endif
            #if BMC_MAX_OLED > 13 && defined(BMC_DEVICE_UI_OLED_14)
              case 13: return BMC_DEVICE_UI_OLED_14;
            #endif
            #if BMC_MAX_OLED > 14 && defined(BMC_DEVICE_UI_OLED_15)
              case 14: return BMC_DEVICE_UI_OLED_15;
            #endif
            #if BMC_MAX_OLED > 15 && defined(BMC_DEVICE_UI_OLED_16)
              case 15: return BMC_DEVICE_UI_OLED_16;
            #endif
            #if BMC_MAX_OLED > 16 && defined(BMC_DEVICE_UI_OLED_17)
              case 16: return BMC_DEVICE_UI_OLED_17;
            #endif
            #if BMC_MAX_OLED > 17 && defined(BMC_DEVICE_UI_OLED_18)
              case 17: return BMC_DEVICE_UI_OLED_18;
            #endif
            #if BMC_MAX_OLED > 18 && defined(BMC_DEVICE_UI_OLED_19)
              case 18: return BMC_DEVICE_UI_OLED_19;
            #endif
            #if BMC_MAX_OLED > 19 && defined(BMC_DEVICE_UI_OLED_20)
              case 19: return BMC_DEVICE_UI_OLED_20;
            #endif
            #if BMC_MAX_OLED > 20 && defined(BMC_DEVICE_UI_OLED_21)
              case 20: return BMC_DEVICE_UI_OLED_21;
            #endif
            #if BMC_MAX_OLED > 21 && defined(BMC_DEVICE_UI_OLED_22)
              case 21: return BMC_DEVICE_UI_OLED_22;
            #endif
            #if BMC_MAX_OLED > 22 && defined(BMC_DEVICE_UI_OLED_23)
              case 22: return BMC_DEVICE_UI_OLED_23;
            #endif
            #if BMC_MAX_OLED > 23 && defined(BMC_DEVICE_UI_OLED_24)
              case 23: return BMC_DEVICE_UI_OLED_24;
            #endif
            #if BMC_MAX_OLED > 24 && defined(BMC_DEVICE_UI_OLED_25)
              case 24: return BMC_DEVICE_UI_OLED_25;
            #endif
            #if BMC_MAX_OLED > 25 && defined(BMC_DEVICE_UI_OLED_26)
              case 25: return BMC_DEVICE_UI_OLED_26;
            #endif
            #if BMC_MAX_OLED > 26 && defined(BMC_DEVICE_UI_OLED_27)
              case 26: return BMC_DEVICE_UI_OLED_27;
            #endif
            #if BMC_MAX_OLED > 27 && defined(BMC_DEVICE_UI_OLED_28)
              case 27: return BMC_DEVICE_UI_OLED_28;
            #endif
            #if BMC_MAX_OLED > 28 && defined(BMC_DEVICE_UI_OLED_29)
              case 28: return BMC_DEVICE_UI_OLED_29;
            #endif
            #if BMC_MAX_OLED > 29 && defined(BMC_DEVICE_UI_OLED_30)
              case 29: return BMC_DEVICE_UI_OLED_30;
            #endif
            #if BMC_MAX_OLED > 30 && defined(BMC_DEVICE_UI_OLED_31)
              case 30: return BMC_DEVICE_UI_OLED_31;
            #endif
            #if BMC_MAX_OLED > 31 && defined(BMC_DEVICE_UI_OLED_32)
              case 31: return BMC_DEVICE_UI_OLED_32;
            #endif
            #if BMC_MAX_OLED > 32 && defined(BMC_DEVICE_UI_OLED_33)
              case 32: return BMC_DEVICE_UI_OLED_33;
            #endif
            #if BMC_MAX_OLED > 33 && defined(BMC_DEVICE_UI_OLED_34)
              case 33: return BMC_DEVICE_UI_OLED_34;
            #endif
            #if BMC_MAX_OLED > 34 && defined(BMC_DEVICE_UI_OLED_35)
              case 34: return BMC_DEVICE_UI_OLED_35;
            #endif
            #if BMC_MAX_OLED > 35 && defined(BMC_DEVICE_UI_OLED_36)
              case 35: return BMC_DEVICE_UI_OLED_36;
            #endif
            #if BMC_MAX_OLED > 36 && defined(BMC_DEVICE_UI_OLED_37)
              case 36: return BMC_DEVICE_UI_OLED_37;
            #endif
            #if BMC_MAX_OLED > 37 && defined(BMC_DEVICE_UI_OLED_38)
              case 37: return BMC_DEVICE_UI_OLED_38;
            #endif
            #if BMC_MAX_OLED > 38 && defined(BMC_DEVICE_UI_OLED_39)
              case 38: return BMC_DEVICE_UI_OLED_39;
            #endif
            #if BMC_MAX_OLED > 39 && defined(BMC_DEVICE_UI_OLED_40)
              case 39: return BMC_DEVICE_UI_OLED_40;
            #endif
            #if BMC_MAX_OLED > 40 && defined(BMC_DEVICE_UI_OLED_41)
              case 40: return BMC_DEVICE_UI_OLED_41;
            #endif
            #if BMC_MAX_OLED > 41 && defined(BMC_DEVICE_UI_OLED_42)
              case 41: return BMC_DEVICE_UI_OLED_42;
            #endif
            #if BMC_MAX_OLED > 42 && defined(BMC_DEVICE_UI_OLED_43)
              case 42: return BMC_DEVICE_UI_OLED_43;
            #endif
            #if BMC_MAX_OLED > 43 && defined(BMC_DEVICE_UI_OLED_44)
              case 43: return BMC_DEVICE_UI_OLED_44;
            #endif
            #if BMC_MAX_OLED > 44 && defined(BMC_DEVICE_UI_OLED_45)
              case 44: return BMC_DEVICE_UI_OLED_45;
            #endif
            #if BMC_MAX_OLED > 45 && defined(BMC_DEVICE_UI_OLED_46)
              case 45: return BMC_DEVICE_UI_OLED_46;
            #endif
            #if BMC_MAX_OLED > 46 && defined(BMC_DEVICE_UI_OLED_47)
              case 46: return BMC_DEVICE_UI_OLED_47;
            #endif
            #if BMC_MAX_OLED > 47 && defined(BMC_DEVICE_UI_OLED_48)
              case 47: return BMC_DEVICE_UI_OLED_48;
            #endif
            #if BMC_MAX_OLED > 48 && defined(BMC_DEVICE_UI_OLED_49)
              case 48: return BMC_DEVICE_UI_OLED_49;
            #endif
            #if BMC_MAX_OLED > 49 && defined(BMC_DEVICE_UI_OLED_50)
              case 49: return BMC_DEVICE_UI_OLED_50;
            #endif
            #if BMC_MAX_OLED > 50 && defined(BMC_DEVICE_UI_OLED_51)
              case 50: return BMC_DEVICE_UI_OLED_51;
            #endif
            #if BMC_MAX_OLED > 51 && defined(BMC_DEVICE_UI_OLED_52)
              case 51: return BMC_DEVICE_UI_OLED_52;
            #endif
            #if BMC_MAX_OLED > 52 && defined(BMC_DEVICE_UI_OLED_53)
              case 52: return BMC_DEVICE_UI_OLED_53;
            #endif
            #if BMC_MAX_OLED > 53 && defined(BMC_DEVICE_UI_OLED_54)
              case 53: return BMC_DEVICE_UI_OLED_54;
            #endif
            #if BMC_MAX_OLED > 54 && defined(BMC_DEVICE_UI_OLED_55)
              case 54: return BMC_DEVICE_UI_OLED_55;
            #endif
            #if BMC_MAX_OLED > 55 && defined(BMC_DEVICE_UI_OLED_56)
              case 55: return BMC_DEVICE_UI_OLED_56;
            #endif
            #if BMC_MAX_OLED > 56 && defined(BMC_DEVICE_UI_OLED_57)
              case 56: return BMC_DEVICE_UI_OLED_57;
            #endif
            #if BMC_MAX_OLED > 57 && defined(BMC_DEVICE_UI_OLED_58)
              case 57: return BMC_DEVICE_UI_OLED_58;
            #endif
            #if BMC_MAX_OLED > 58 && defined(BMC_DEVICE_UI_OLED_59)
              case 58: return BMC_DEVICE_UI_OLED_59;
            #endif
            #if BMC_MAX_OLED > 59 && defined(BMC_DEVICE_UI_OLED_60)
              case 59: return BMC_DEVICE_UI_OLED_60;
            #endif
            #if BMC_MAX_OLED > 60 && defined(BMC_DEVICE_UI_OLED_61)
              case 60: return BMC_DEVICE_UI_OLED_61;
            #endif
            #if BMC_MAX_OLED > 61 && defined(BMC_DEVICE_UI_OLED_62)
              case 61: return BMC_DEVICE_UI_OLED_62;
            #endif
            #if BMC_MAX_OLED > 62 && defined(BMC_DEVICE_UI_OLED_63)
              case 62: return BMC_DEVICE_UI_OLED_63;
            #endif
            #if BMC_MAX_OLED > 63 && defined(BMC_DEVICE_UI_OLED_64)
              case 63: return BMC_DEVICE_UI_OLED_64;
            #endif

            }
          #endif
          break;
      case BMC_DEVICE_ID_ILI:
          #if BMC_MAX_ILI9341_BLOCKS > 0
          #if defined(BMC_DEVICE_UI_ILI)
            if(n==-1){
              return BMC_DEVICE_UI_ILI;
            }
          #endif
            switch(n){
              #if BMC_MAX_ILI9341_BLOCKS > 0 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_1)
              case 0: return BMC_DEVICE_UI_ILI_1;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 1 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_2)
              case 1: return BMC_DEVICE_UI_ILI_2;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 2 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_3)
              case 2: return BMC_DEVICE_UI_ILI_3;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 3 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_4)
              case 3: return BMC_DEVICE_UI_ILI_4;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 4 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_5)
              case 4: return BMC_DEVICE_UI_ILI_5;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 5 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_6)
              case 5: return BMC_DEVICE_UI_ILI_6;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 6 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_7)
              case 6: return BMC_DEVICE_UI_ILI_7;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 7 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_8)
              case 7: return BMC_DEVICE_UI_ILI_8;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 8 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_9)
              case 8: return BMC_DEVICE_UI_ILI_9;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 9 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_10)
              case 9: return BMC_DEVICE_UI_ILI_10;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 10 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_11)
              case 10: return BMC_DEVICE_UI_ILI_11;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 11 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_12)
              case 11: return BMC_DEVICE_UI_ILI_12;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 12 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_13)
              case 12: return BMC_DEVICE_UI_ILI_13;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 13 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_14)
              case 13: return BMC_DEVICE_UI_ILI_14;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 14 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_15)
              case 14: return BMC_DEVICE_UI_ILI_15;
            #endif
            #if BMC_MAX_ILI9341_BLOCKS > 15 && defined(BMC_DEVICE_UI_ILI) && defined(BMC_DEVICE_UI_ILI_16)
              case 15: return BMC_DEVICE_UI_ILI_16;
            #endif

            }
          #endif
          break;
}
    BMCUIData e;
    return e;
  }
static uint8_t getButtonPin(uint8_t index=0){
#if BMC_MAX_BUTTONS > 0
switch(index){
#if defined(BMC_BUTTON_1_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=1 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_1_X) && defined(BMC_BUTTON_1_Y)
  case 0: return BMC_BUTTON_1_PIN;
#if defined(BMC_BUTTON_2_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_2_X) && defined(BMC_BUTTON_2_Y)
  case 1: return BMC_BUTTON_2_PIN;
#if defined(BMC_BUTTON_3_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=3 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_3_X) && defined(BMC_BUTTON_3_Y)
  case 2: return BMC_BUTTON_3_PIN;
#if defined(BMC_BUTTON_4_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_4_X) && defined(BMC_BUTTON_4_Y)
  case 3: return BMC_BUTTON_4_PIN;
#if defined(BMC_BUTTON_5_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=5 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_5_X) && defined(BMC_BUTTON_5_Y)
  case 4: return BMC_BUTTON_5_PIN;
#if defined(BMC_BUTTON_6_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_6_X) && defined(BMC_BUTTON_6_Y)
  case 5: return BMC_BUTTON_6_PIN;
#if defined(BMC_BUTTON_7_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=7 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_7_X) && defined(BMC_BUTTON_7_Y)
  case 6: return BMC_BUTTON_7_PIN;
#if defined(BMC_BUTTON_8_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_8_X) && defined(BMC_BUTTON_8_Y)
  case 7: return BMC_BUTTON_8_PIN;
#if defined(BMC_BUTTON_9_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=9 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_9_X) && defined(BMC_BUTTON_9_Y)
  case 8: return BMC_BUTTON_9_PIN;
#if defined(BMC_BUTTON_10_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_10_X) && defined(BMC_BUTTON_10_Y)
  case 9: return BMC_BUTTON_10_PIN;
#if defined(BMC_BUTTON_11_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=11 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_11_X) && defined(BMC_BUTTON_11_Y)
  case 10: return BMC_BUTTON_11_PIN;
#if defined(BMC_BUTTON_12_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_12_X) && defined(BMC_BUTTON_12_Y)
  case 11: return BMC_BUTTON_12_PIN;
#if defined(BMC_BUTTON_13_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=13 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_13_X) && defined(BMC_BUTTON_13_Y)
  case 12: return BMC_BUTTON_13_PIN;
#if defined(BMC_BUTTON_14_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_14_X) && defined(BMC_BUTTON_14_Y)
  case 13: return BMC_BUTTON_14_PIN;
#if defined(BMC_BUTTON_15_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=15 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_15_X) && defined(BMC_BUTTON_15_Y)
  case 14: return BMC_BUTTON_15_PIN;
#if defined(BMC_BUTTON_16_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_16_X) && defined(BMC_BUTTON_16_Y)
  case 15: return BMC_BUTTON_16_PIN;
#if defined(BMC_BUTTON_17_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=17 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_17_X) && defined(BMC_BUTTON_17_Y)
  case 16: return BMC_BUTTON_17_PIN;
#if defined(BMC_BUTTON_18_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_18_X) && defined(BMC_BUTTON_18_Y)
  case 17: return BMC_BUTTON_18_PIN;
#if defined(BMC_BUTTON_19_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=19 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_19_X) && defined(BMC_BUTTON_19_Y)
  case 18: return BMC_BUTTON_19_PIN;
#if defined(BMC_BUTTON_20_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_20_X) && defined(BMC_BUTTON_20_Y)
  case 19: return BMC_BUTTON_20_PIN;
#if defined(BMC_BUTTON_21_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=21 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_21_X) && defined(BMC_BUTTON_21_Y)
  case 20: return BMC_BUTTON_21_PIN;
#if defined(BMC_BUTTON_22_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_22_X) && defined(BMC_BUTTON_22_Y)
  case 21: return BMC_BUTTON_22_PIN;
#if defined(BMC_BUTTON_23_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=23 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_23_X) && defined(BMC_BUTTON_23_Y)
  case 22: return BMC_BUTTON_23_PIN;
#if defined(BMC_BUTTON_24_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_24_X) && defined(BMC_BUTTON_24_Y)
  case 23: return BMC_BUTTON_24_PIN;
#if defined(BMC_BUTTON_25_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=25 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_25_X) && defined(BMC_BUTTON_25_Y)
  case 24: return BMC_BUTTON_25_PIN;
#if defined(BMC_BUTTON_26_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_26_X) && defined(BMC_BUTTON_26_Y)
  case 25: return BMC_BUTTON_26_PIN;
#if defined(BMC_BUTTON_27_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=27 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_27_X) && defined(BMC_BUTTON_27_Y)
  case 26: return BMC_BUTTON_27_PIN;
#if defined(BMC_BUTTON_28_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_28_X) && defined(BMC_BUTTON_28_Y)
  case 27: return BMC_BUTTON_28_PIN;
#if defined(BMC_BUTTON_29_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=29 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_29_X) && defined(BMC_BUTTON_29_Y)
  case 28: return BMC_BUTTON_29_PIN;
#if defined(BMC_BUTTON_30_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_30_X) && defined(BMC_BUTTON_30_Y)
  case 29: return BMC_BUTTON_30_PIN;
#if defined(BMC_BUTTON_31_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=31 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_31_X) && defined(BMC_BUTTON_31_Y)
  case 30: return BMC_BUTTON_31_PIN;
#if defined(BMC_BUTTON_32_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_32_X) && defined(BMC_BUTTON_32_Y)
  case 31: return BMC_BUTTON_32_PIN;
#if defined(BMC_BUTTON_33_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=33 && BMC_MAX_BUTTONS > 32 && defined(BMC_BUTTON_33_X) && defined(BMC_BUTTON_33_Y)
  case 32: return BMC_BUTTON_33_PIN;
#if defined(BMC_BUTTON_34_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && BMC_MAX_BUTTONS > 33 && defined(BMC_BUTTON_34_X) && defined(BMC_BUTTON_34_Y)
  case 33: return BMC_BUTTON_34_PIN;
#if defined(BMC_BUTTON_35_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=35 && BMC_MAX_BUTTONS > 34 && defined(BMC_BUTTON_35_X) && defined(BMC_BUTTON_35_Y)
  case 34: return BMC_BUTTON_35_PIN;
#if defined(BMC_BUTTON_36_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && BMC_MAX_BUTTONS > 35 && defined(BMC_BUTTON_36_X) && defined(BMC_BUTTON_36_Y)
  case 35: return BMC_BUTTON_36_PIN;
#if defined(BMC_BUTTON_37_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=37 && BMC_MAX_BUTTONS > 36 && defined(BMC_BUTTON_37_X) && defined(BMC_BUTTON_37_Y)
  case 36: return BMC_BUTTON_37_PIN;
#if defined(BMC_BUTTON_38_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && BMC_MAX_BUTTONS > 37 && defined(BMC_BUTTON_38_X) && defined(BMC_BUTTON_38_Y)
  case 37: return BMC_BUTTON_38_PIN;
#if defined(BMC_BUTTON_39_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=39 && BMC_MAX_BUTTONS > 38 && defined(BMC_BUTTON_39_X) && defined(BMC_BUTTON_39_Y)
  case 38: return BMC_BUTTON_39_PIN;
#if defined(BMC_BUTTON_40_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && BMC_MAX_BUTTONS > 39 && defined(BMC_BUTTON_40_X) && defined(BMC_BUTTON_40_Y)
  case 39: return BMC_BUTTON_40_PIN;
#if defined(BMC_BUTTON_41_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=41 && BMC_MAX_BUTTONS > 40 && defined(BMC_BUTTON_41_X) && defined(BMC_BUTTON_41_Y)
  case 40: return BMC_BUTTON_41_PIN;
#if defined(BMC_BUTTON_42_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && BMC_MAX_BUTTONS > 41 && defined(BMC_BUTTON_42_X) && defined(BMC_BUTTON_42_Y)
  case 41: return BMC_BUTTON_42_PIN;
#if defined(BMC_BUTTON_43_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=43 && BMC_MAX_BUTTONS > 42 && defined(BMC_BUTTON_43_X) && defined(BMC_BUTTON_43_Y)
  case 42: return BMC_BUTTON_43_PIN;
#if defined(BMC_BUTTON_44_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && BMC_MAX_BUTTONS > 43 && defined(BMC_BUTTON_44_X) && defined(BMC_BUTTON_44_Y)
  case 43: return BMC_BUTTON_44_PIN;
#if defined(BMC_BUTTON_45_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=45 && BMC_MAX_BUTTONS > 44 && defined(BMC_BUTTON_45_X) && defined(BMC_BUTTON_45_Y)
  case 44: return BMC_BUTTON_45_PIN;
#if defined(BMC_BUTTON_46_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && BMC_MAX_BUTTONS > 45 && defined(BMC_BUTTON_46_X) && defined(BMC_BUTTON_46_Y)
  case 45: return BMC_BUTTON_46_PIN;
#if defined(BMC_BUTTON_47_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=47 && BMC_MAX_BUTTONS > 46 && defined(BMC_BUTTON_47_X) && defined(BMC_BUTTON_47_Y)
  case 46: return BMC_BUTTON_47_PIN;
#if defined(BMC_BUTTON_48_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && BMC_MAX_BUTTONS > 47 && defined(BMC_BUTTON_48_X) && defined(BMC_BUTTON_48_Y)
  case 47: return BMC_BUTTON_48_PIN;
#if defined(BMC_BUTTON_49_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=49 && BMC_MAX_BUTTONS > 48 && defined(BMC_BUTTON_49_X) && defined(BMC_BUTTON_49_Y)
  case 48: return BMC_BUTTON_49_PIN;
#if defined(BMC_BUTTON_50_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && BMC_MAX_BUTTONS > 49 && defined(BMC_BUTTON_50_X) && defined(BMC_BUTTON_50_Y)
  case 49: return BMC_BUTTON_50_PIN;
#if defined(BMC_BUTTON_51_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=51 && BMC_MAX_BUTTONS > 50 && defined(BMC_BUTTON_51_X) && defined(BMC_BUTTON_51_Y)
  case 50: return BMC_BUTTON_51_PIN;
#if defined(BMC_BUTTON_52_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && BMC_MAX_BUTTONS > 51 && defined(BMC_BUTTON_52_X) && defined(BMC_BUTTON_52_Y)
  case 51: return BMC_BUTTON_52_PIN;
#if defined(BMC_BUTTON_53_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=53 && BMC_MAX_BUTTONS > 52 && defined(BMC_BUTTON_53_X) && defined(BMC_BUTTON_53_Y)
  case 52: return BMC_BUTTON_53_PIN;
#if defined(BMC_BUTTON_54_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && BMC_MAX_BUTTONS > 53 && defined(BMC_BUTTON_54_X) && defined(BMC_BUTTON_54_Y)
  case 53: return BMC_BUTTON_54_PIN;
#if defined(BMC_BUTTON_55_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=55 && BMC_MAX_BUTTONS > 54 && defined(BMC_BUTTON_55_X) && defined(BMC_BUTTON_55_Y)
  case 54: return BMC_BUTTON_55_PIN;
#if defined(BMC_BUTTON_56_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && BMC_MAX_BUTTONS > 55 && defined(BMC_BUTTON_56_X) && defined(BMC_BUTTON_56_Y)
  case 55: return BMC_BUTTON_56_PIN;
#if defined(BMC_BUTTON_57_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=57 && BMC_MAX_BUTTONS > 56 && defined(BMC_BUTTON_57_X) && defined(BMC_BUTTON_57_Y)
  case 56: return BMC_BUTTON_57_PIN;
#if defined(BMC_BUTTON_58_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && BMC_MAX_BUTTONS > 57 && defined(BMC_BUTTON_58_X) && defined(BMC_BUTTON_58_Y)
  case 57: return BMC_BUTTON_58_PIN;
#if defined(BMC_BUTTON_59_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=59 && BMC_MAX_BUTTONS > 58 && defined(BMC_BUTTON_59_X) && defined(BMC_BUTTON_59_Y)
  case 58: return BMC_BUTTON_59_PIN;
#if defined(BMC_BUTTON_60_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && BMC_MAX_BUTTONS > 59 && defined(BMC_BUTTON_60_X) && defined(BMC_BUTTON_60_Y)
  case 59: return BMC_BUTTON_60_PIN;
#if defined(BMC_BUTTON_61_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=61 && BMC_MAX_BUTTONS > 60 && defined(BMC_BUTTON_61_X) && defined(BMC_BUTTON_61_Y)
  case 60: return BMC_BUTTON_61_PIN;
#if defined(BMC_BUTTON_62_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && BMC_MAX_BUTTONS > 61 && defined(BMC_BUTTON_62_X) && defined(BMC_BUTTON_62_Y)
  case 61: return BMC_BUTTON_62_PIN;
#if defined(BMC_BUTTON_63_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=63 && BMC_MAX_BUTTONS > 62 && defined(BMC_BUTTON_63_X) && defined(BMC_BUTTON_63_Y)
  case 62: return BMC_BUTTON_63_PIN;
#if defined(BMC_BUTTON_64_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && BMC_MAX_BUTTONS > 63 && defined(BMC_BUTTON_64_X) && defined(BMC_BUTTON_64_Y)
  case 63: return BMC_BUTTON_64_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getLedPin(uint8_t index=0){
#if BMC_MAX_LEDS > 0
switch(index){
#if defined(BMC_LED_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_LEDS > 0 && defined(BMC_LED_1_X) && defined(BMC_LED_1_Y)
  case 0: return BMC_LED_1_PIN;
#if defined(BMC_LED_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_LEDS > 1 && defined(BMC_LED_2_X) && defined(BMC_LED_2_Y)
  case 1: return BMC_LED_2_PIN;
#if defined(BMC_LED_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_LEDS > 2 && defined(BMC_LED_3_X) && defined(BMC_LED_3_Y)
  case 2: return BMC_LED_3_PIN;
#if defined(BMC_LED_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_LEDS > 3 && defined(BMC_LED_4_X) && defined(BMC_LED_4_Y)
  case 3: return BMC_LED_4_PIN;
#if defined(BMC_LED_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_LEDS > 4 && defined(BMC_LED_5_X) && defined(BMC_LED_5_Y)
  case 4: return BMC_LED_5_PIN;
#if defined(BMC_LED_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_LEDS > 5 && defined(BMC_LED_6_X) && defined(BMC_LED_6_Y)
  case 5: return BMC_LED_6_PIN;
#if defined(BMC_LED_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_LEDS > 6 && defined(BMC_LED_7_X) && defined(BMC_LED_7_Y)
  case 6: return BMC_LED_7_PIN;
#if defined(BMC_LED_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_LEDS > 7 && defined(BMC_LED_8_X) && defined(BMC_LED_8_Y)
  case 7: return BMC_LED_8_PIN;
#if defined(BMC_LED_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_LEDS > 8 && defined(BMC_LED_9_X) && defined(BMC_LED_9_Y)
  case 8: return BMC_LED_9_PIN;
#if defined(BMC_LED_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_LEDS > 9 && defined(BMC_LED_10_X) && defined(BMC_LED_10_Y)
  case 9: return BMC_LED_10_PIN;
#if defined(BMC_LED_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_LEDS > 10 && defined(BMC_LED_11_X) && defined(BMC_LED_11_Y)
  case 10: return BMC_LED_11_PIN;
#if defined(BMC_LED_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_LEDS > 11 && defined(BMC_LED_12_X) && defined(BMC_LED_12_Y)
  case 11: return BMC_LED_12_PIN;
#if defined(BMC_LED_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_LEDS > 12 && defined(BMC_LED_13_X) && defined(BMC_LED_13_Y)
  case 12: return BMC_LED_13_PIN;
#if defined(BMC_LED_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_LEDS > 13 && defined(BMC_LED_14_X) && defined(BMC_LED_14_Y)
  case 13: return BMC_LED_14_PIN;
#if defined(BMC_LED_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_LEDS > 14 && defined(BMC_LED_15_X) && defined(BMC_LED_15_Y)
  case 14: return BMC_LED_15_PIN;
#if defined(BMC_LED_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_LEDS > 15 && defined(BMC_LED_16_X) && defined(BMC_LED_16_Y)
  case 15: return BMC_LED_16_PIN;
#if defined(BMC_LED_17_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && BMC_MAX_LEDS > 16 && defined(BMC_LED_17_X) && defined(BMC_LED_17_Y)
  case 16: return BMC_LED_17_PIN;
#if defined(BMC_LED_18_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && BMC_MAX_LEDS > 17 && defined(BMC_LED_18_X) && defined(BMC_LED_18_Y)
  case 17: return BMC_LED_18_PIN;
#if defined(BMC_LED_19_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && BMC_MAX_LEDS > 18 && defined(BMC_LED_19_X) && defined(BMC_LED_19_Y)
  case 18: return BMC_LED_19_PIN;
#if defined(BMC_LED_20_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && BMC_MAX_LEDS > 19 && defined(BMC_LED_20_X) && defined(BMC_LED_20_Y)
  case 19: return BMC_LED_20_PIN;
#if defined(BMC_LED_21_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && BMC_MAX_LEDS > 20 && defined(BMC_LED_21_X) && defined(BMC_LED_21_Y)
  case 20: return BMC_LED_21_PIN;
#if defined(BMC_LED_22_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && BMC_MAX_LEDS > 21 && defined(BMC_LED_22_X) && defined(BMC_LED_22_Y)
  case 21: return BMC_LED_22_PIN;
#if defined(BMC_LED_23_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && BMC_MAX_LEDS > 22 && defined(BMC_LED_23_X) && defined(BMC_LED_23_Y)
  case 22: return BMC_LED_23_PIN;
#if defined(BMC_LED_24_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && BMC_MAX_LEDS > 23 && defined(BMC_LED_24_X) && defined(BMC_LED_24_Y)
  case 23: return BMC_LED_24_PIN;
#if defined(BMC_LED_25_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && BMC_MAX_LEDS > 24 && defined(BMC_LED_25_X) && defined(BMC_LED_25_Y)
  case 24: return BMC_LED_25_PIN;
#if defined(BMC_LED_26_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && BMC_MAX_LEDS > 25 && defined(BMC_LED_26_X) && defined(BMC_LED_26_Y)
  case 25: return BMC_LED_26_PIN;
#if defined(BMC_LED_27_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && BMC_MAX_LEDS > 26 && defined(BMC_LED_27_X) && defined(BMC_LED_27_Y)
  case 26: return BMC_LED_27_PIN;
#if defined(BMC_LED_28_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && BMC_MAX_LEDS > 27 && defined(BMC_LED_28_X) && defined(BMC_LED_28_Y)
  case 27: return BMC_LED_28_PIN;
#if defined(BMC_LED_29_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && BMC_MAX_LEDS > 28 && defined(BMC_LED_29_X) && defined(BMC_LED_29_Y)
  case 28: return BMC_LED_29_PIN;
#if defined(BMC_LED_30_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && BMC_MAX_LEDS > 29 && defined(BMC_LED_30_X) && defined(BMC_LED_30_Y)
  case 29: return BMC_LED_30_PIN;
#if defined(BMC_LED_31_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && BMC_MAX_LEDS > 30 && defined(BMC_LED_31_X) && defined(BMC_LED_31_Y)
  case 30: return BMC_LED_31_PIN;
#if defined(BMC_LED_32_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && BMC_MAX_LEDS > 31 && defined(BMC_LED_32_X) && defined(BMC_LED_32_Y)
  case 31: return BMC_LED_32_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getPotPin(uint8_t index=0){
#if BMC_MAX_POTS > 0
switch(index){
#if defined(BMC_POT_1_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=1 && BMC_MAX_POTS > 0 && defined(BMC_POT_1_X) && defined(BMC_POT_1_Y)
  case 0: return BMC_POT_1_PIN;
#if defined(BMC_POT_2_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=2 && BMC_MAX_POTS > 1 && defined(BMC_POT_2_X) && defined(BMC_POT_2_Y)
  case 1: return BMC_POT_2_PIN;
#if defined(BMC_POT_3_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=3 && BMC_MAX_POTS > 2 && defined(BMC_POT_3_X) && defined(BMC_POT_3_Y)
  case 2: return BMC_POT_3_PIN;
#if defined(BMC_POT_4_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=4 && BMC_MAX_POTS > 3 && defined(BMC_POT_4_X) && defined(BMC_POT_4_Y)
  case 3: return BMC_POT_4_PIN;
#if defined(BMC_POT_5_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=5 && BMC_MAX_POTS > 4 && defined(BMC_POT_5_X) && defined(BMC_POT_5_Y)
  case 4: return BMC_POT_5_PIN;
#if defined(BMC_POT_6_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=6 && BMC_MAX_POTS > 5 && defined(BMC_POT_6_X) && defined(BMC_POT_6_Y)
  case 5: return BMC_POT_6_PIN;
#if defined(BMC_POT_7_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=7 && BMC_MAX_POTS > 6 && defined(BMC_POT_7_X) && defined(BMC_POT_7_Y)
  case 6: return BMC_POT_7_PIN;
#if defined(BMC_POT_8_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=8 && BMC_MAX_POTS > 7 && defined(BMC_POT_8_X) && defined(BMC_POT_8_Y)
  case 7: return BMC_POT_8_PIN;
#if defined(BMC_POT_9_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=9 && BMC_MAX_POTS > 8 && defined(BMC_POT_9_X) && defined(BMC_POT_9_Y)
  case 8: return BMC_POT_9_PIN;
#if defined(BMC_POT_10_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=10 && BMC_MAX_POTS > 9 && defined(BMC_POT_10_X) && defined(BMC_POT_10_Y)
  case 9: return BMC_POT_10_PIN;
#if defined(BMC_POT_11_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=11 && BMC_MAX_POTS > 10 && defined(BMC_POT_11_X) && defined(BMC_POT_11_Y)
  case 10: return BMC_POT_11_PIN;
#if defined(BMC_POT_12_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=12 && BMC_MAX_POTS > 11 && defined(BMC_POT_12_X) && defined(BMC_POT_12_Y)
  case 11: return BMC_POT_12_PIN;
#if defined(BMC_POT_13_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=13 && BMC_MAX_POTS > 12 && defined(BMC_POT_13_X) && defined(BMC_POT_13_Y)
  case 12: return BMC_POT_13_PIN;
#if defined(BMC_POT_14_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=14 && BMC_MAX_POTS > 13 && defined(BMC_POT_14_X) && defined(BMC_POT_14_Y)
  case 13: return BMC_POT_14_PIN;
#if defined(BMC_POT_15_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=15 && BMC_MAX_POTS > 14 && defined(BMC_POT_15_X) && defined(BMC_POT_15_Y)
  case 14: return BMC_POT_15_PIN;
#if defined(BMC_POT_16_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=16 && BMC_MAX_POTS > 15 && defined(BMC_POT_16_X) && defined(BMC_POT_16_Y)
  case 15: return BMC_POT_16_PIN;
#if defined(BMC_POT_17_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=17 && BMC_MAX_POTS > 16 && defined(BMC_POT_17_X) && defined(BMC_POT_17_Y)
  case 16: return BMC_POT_17_PIN;
#if defined(BMC_POT_18_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=18 && BMC_MAX_POTS > 17 && defined(BMC_POT_18_X) && defined(BMC_POT_18_Y)
  case 17: return BMC_POT_18_PIN;
#if defined(BMC_POT_19_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=19 && BMC_MAX_POTS > 18 && defined(BMC_POT_19_X) && defined(BMC_POT_19_Y)
  case 18: return BMC_POT_19_PIN;
#if defined(BMC_POT_20_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=20 && BMC_MAX_POTS > 19 && defined(BMC_POT_20_X) && defined(BMC_POT_20_Y)
  case 19: return BMC_POT_20_PIN;
#if defined(BMC_POT_21_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=21 && BMC_MAX_POTS > 20 && defined(BMC_POT_21_X) && defined(BMC_POT_21_Y)
  case 20: return BMC_POT_21_PIN;
#if defined(BMC_POT_22_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=22 && BMC_MAX_POTS > 21 && defined(BMC_POT_22_X) && defined(BMC_POT_22_Y)
  case 21: return BMC_POT_22_PIN;
#if defined(BMC_POT_23_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=23 && BMC_MAX_POTS > 22 && defined(BMC_POT_23_X) && defined(BMC_POT_23_Y)
  case 22: return BMC_POT_23_PIN;
#if defined(BMC_POT_24_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=24 && BMC_MAX_POTS > 23 && defined(BMC_POT_24_X) && defined(BMC_POT_24_Y)
  case 23: return BMC_POT_24_PIN;
#if defined(BMC_POT_25_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=25 && BMC_MAX_POTS > 24 && defined(BMC_POT_25_X) && defined(BMC_POT_25_Y)
  case 24: return BMC_POT_25_PIN;
#if defined(BMC_POT_26_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=26 && BMC_MAX_POTS > 25 && defined(BMC_POT_26_X) && defined(BMC_POT_26_Y)
  case 25: return BMC_POT_26_PIN;
#if defined(BMC_POT_27_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=27 && BMC_MAX_POTS > 26 && defined(BMC_POT_27_X) && defined(BMC_POT_27_Y)
  case 26: return BMC_POT_27_PIN;
#if defined(BMC_POT_28_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=28 && BMC_MAX_POTS > 27 && defined(BMC_POT_28_X) && defined(BMC_POT_28_Y)
  case 27: return BMC_POT_28_PIN;
#if defined(BMC_POT_29_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=29 && BMC_MAX_POTS > 28 && defined(BMC_POT_29_X) && defined(BMC_POT_29_Y)
  case 28: return BMC_POT_29_PIN;
#if defined(BMC_POT_30_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=30 && BMC_MAX_POTS > 29 && defined(BMC_POT_30_X) && defined(BMC_POT_30_Y)
  case 29: return BMC_POT_30_PIN;
#if defined(BMC_POT_31_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=31 && BMC_MAX_POTS > 30 && defined(BMC_POT_31_X) && defined(BMC_POT_31_Y)
  case 30: return BMC_POT_31_PIN;
#if defined(BMC_POT_32_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=32 && BMC_MAX_POTS > 31 && defined(BMC_POT_32_X) && defined(BMC_POT_32_Y)
  case 31: return BMC_POT_32_PIN;
#if defined(BMC_POT_33_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=33 && BMC_MAX_POTS > 32 && defined(BMC_POT_33_X) && defined(BMC_POT_33_Y)
  case 32: return BMC_POT_33_PIN;
#if defined(BMC_POT_34_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=34 && BMC_MAX_POTS > 33 && defined(BMC_POT_34_X) && defined(BMC_POT_34_Y)
  case 33: return BMC_POT_34_PIN;
#if defined(BMC_POT_35_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=35 && BMC_MAX_POTS > 34 && defined(BMC_POT_35_X) && defined(BMC_POT_35_Y)
  case 34: return BMC_POT_35_PIN;
#if defined(BMC_POT_36_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=36 && BMC_MAX_POTS > 35 && defined(BMC_POT_36_X) && defined(BMC_POT_36_Y)
  case 35: return BMC_POT_36_PIN;
#if defined(BMC_POT_37_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=37 && BMC_MAX_POTS > 36 && defined(BMC_POT_37_X) && defined(BMC_POT_37_Y)
  case 36: return BMC_POT_37_PIN;
#if defined(BMC_POT_38_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=38 && BMC_MAX_POTS > 37 && defined(BMC_POT_38_X) && defined(BMC_POT_38_Y)
  case 37: return BMC_POT_38_PIN;
#if defined(BMC_POT_39_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=39 && BMC_MAX_POTS > 38 && defined(BMC_POT_39_X) && defined(BMC_POT_39_Y)
  case 38: return BMC_POT_39_PIN;
#if defined(BMC_POT_40_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=40 && BMC_MAX_POTS > 39 && defined(BMC_POT_40_X) && defined(BMC_POT_40_Y)
  case 39: return BMC_POT_40_PIN;
#if defined(BMC_POT_41_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=41 && BMC_MAX_POTS > 40 && defined(BMC_POT_41_X) && defined(BMC_POT_41_Y)
  case 40: return BMC_POT_41_PIN;
#if defined(BMC_POT_42_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=42 && BMC_MAX_POTS > 41 && defined(BMC_POT_42_X) && defined(BMC_POT_42_Y)
  case 41: return BMC_POT_42_PIN;
#if defined(BMC_POT_43_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=43 && BMC_MAX_POTS > 42 && defined(BMC_POT_43_X) && defined(BMC_POT_43_Y)
  case 42: return BMC_POT_43_PIN;
#if defined(BMC_POT_44_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=44 && BMC_MAX_POTS > 43 && defined(BMC_POT_44_X) && defined(BMC_POT_44_Y)
  case 43: return BMC_POT_44_PIN;
#if defined(BMC_POT_45_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=45 && BMC_MAX_POTS > 44 && defined(BMC_POT_45_X) && defined(BMC_POT_45_Y)
  case 44: return BMC_POT_45_PIN;
#if defined(BMC_POT_46_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=46 && BMC_MAX_POTS > 45 && defined(BMC_POT_46_X) && defined(BMC_POT_46_Y)
  case 45: return BMC_POT_46_PIN;
#if defined(BMC_POT_47_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=47 && BMC_MAX_POTS > 46 && defined(BMC_POT_47_X) && defined(BMC_POT_47_Y)
  case 46: return BMC_POT_47_PIN;
#if defined(BMC_POT_48_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=48 && BMC_MAX_POTS > 47 && defined(BMC_POT_48_X) && defined(BMC_POT_48_Y)
  case 47: return BMC_POT_48_PIN;
#if defined(BMC_POT_49_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=49 && BMC_MAX_POTS > 48 && defined(BMC_POT_49_X) && defined(BMC_POT_49_Y)
  case 48: return BMC_POT_49_PIN;
#if defined(BMC_POT_50_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=50 && BMC_MAX_POTS > 49 && defined(BMC_POT_50_X) && defined(BMC_POT_50_Y)
  case 49: return BMC_POT_50_PIN;
#if defined(BMC_POT_51_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=51 && BMC_MAX_POTS > 50 && defined(BMC_POT_51_X) && defined(BMC_POT_51_Y)
  case 50: return BMC_POT_51_PIN;
#if defined(BMC_POT_52_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=52 && BMC_MAX_POTS > 51 && defined(BMC_POT_52_X) && defined(BMC_POT_52_Y)
  case 51: return BMC_POT_52_PIN;
#if defined(BMC_POT_53_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=53 && BMC_MAX_POTS > 52 && defined(BMC_POT_53_X) && defined(BMC_POT_53_Y)
  case 52: return BMC_POT_53_PIN;
#if defined(BMC_POT_54_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=54 && BMC_MAX_POTS > 53 && defined(BMC_POT_54_X) && defined(BMC_POT_54_Y)
  case 53: return BMC_POT_54_PIN;
#if defined(BMC_POT_55_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=55 && BMC_MAX_POTS > 54 && defined(BMC_POT_55_X) && defined(BMC_POT_55_Y)
  case 54: return BMC_POT_55_PIN;
#if defined(BMC_POT_56_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=56 && BMC_MAX_POTS > 55 && defined(BMC_POT_56_X) && defined(BMC_POT_56_Y)
  case 55: return BMC_POT_56_PIN;
#if defined(BMC_POT_57_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=57 && BMC_MAX_POTS > 56 && defined(BMC_POT_57_X) && defined(BMC_POT_57_Y)
  case 56: return BMC_POT_57_PIN;
#if defined(BMC_POT_58_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=58 && BMC_MAX_POTS > 57 && defined(BMC_POT_58_X) && defined(BMC_POT_58_Y)
  case 57: return BMC_POT_58_PIN;
#if defined(BMC_POT_59_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=59 && BMC_MAX_POTS > 58 && defined(BMC_POT_59_X) && defined(BMC_POT_59_Y)
  case 58: return BMC_POT_59_PIN;
#if defined(BMC_POT_60_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=60 && BMC_MAX_POTS > 59 && defined(BMC_POT_60_X) && defined(BMC_POT_60_Y)
  case 59: return BMC_POT_60_PIN;
#if defined(BMC_POT_61_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=61 && BMC_MAX_POTS > 60 && defined(BMC_POT_61_X) && defined(BMC_POT_61_Y)
  case 60: return BMC_POT_61_PIN;
#if defined(BMC_POT_62_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=62 && BMC_MAX_POTS > 61 && defined(BMC_POT_62_X) && defined(BMC_POT_62_Y)
  case 61: return BMC_POT_62_PIN;
#if defined(BMC_POT_63_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=63 && BMC_MAX_POTS > 62 && defined(BMC_POT_63_X) && defined(BMC_POT_63_Y)
  case 62: return BMC_POT_63_PIN;
#if defined(BMC_POT_64_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=64 && BMC_MAX_POTS > 63 && defined(BMC_POT_64_X) && defined(BMC_POT_64_Y)
  case 63: return BMC_POT_64_PIN;
#if defined(BMC_POT_65_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=65 && BMC_MAX_POTS > 64 && defined(BMC_POT_65_X) && defined(BMC_POT_65_Y)
  case 64: return BMC_POT_65_PIN;
#if defined(BMC_POT_66_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=66 && BMC_MAX_POTS > 65 && defined(BMC_POT_66_X) && defined(BMC_POT_66_Y)
  case 65: return BMC_POT_66_PIN;
#if defined(BMC_POT_67_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=67 && BMC_MAX_POTS > 66 && defined(BMC_POT_67_X) && defined(BMC_POT_67_Y)
  case 66: return BMC_POT_67_PIN;
#if defined(BMC_POT_68_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=68 && BMC_MAX_POTS > 67 && defined(BMC_POT_68_X) && defined(BMC_POT_68_Y)
  case 67: return BMC_POT_68_PIN;
#if defined(BMC_POT_69_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=69 && BMC_MAX_POTS > 68 && defined(BMC_POT_69_X) && defined(BMC_POT_69_Y)
  case 68: return BMC_POT_69_PIN;
#if defined(BMC_POT_70_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=70 && BMC_MAX_POTS > 69 && defined(BMC_POT_70_X) && defined(BMC_POT_70_Y)
  case 69: return BMC_POT_70_PIN;
#if defined(BMC_POT_71_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=71 && BMC_MAX_POTS > 70 && defined(BMC_POT_71_X) && defined(BMC_POT_71_Y)
  case 70: return BMC_POT_71_PIN;
#if defined(BMC_POT_72_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=72 && BMC_MAX_POTS > 71 && defined(BMC_POT_72_X) && defined(BMC_POT_72_Y)
  case 71: return BMC_POT_72_PIN;
#if defined(BMC_POT_73_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=73 && BMC_MAX_POTS > 72 && defined(BMC_POT_73_X) && defined(BMC_POT_73_Y)
  case 72: return BMC_POT_73_PIN;
#if defined(BMC_POT_74_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=74 && BMC_MAX_POTS > 73 && defined(BMC_POT_74_X) && defined(BMC_POT_74_Y)
  case 73: return BMC_POT_74_PIN;
#if defined(BMC_POT_75_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=75 && BMC_MAX_POTS > 74 && defined(BMC_POT_75_X) && defined(BMC_POT_75_Y)
  case 74: return BMC_POT_75_PIN;
#if defined(BMC_POT_76_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=76 && BMC_MAX_POTS > 75 && defined(BMC_POT_76_X) && defined(BMC_POT_76_Y)
  case 75: return BMC_POT_76_PIN;
#if defined(BMC_POT_77_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=77 && BMC_MAX_POTS > 76 && defined(BMC_POT_77_X) && defined(BMC_POT_77_Y)
  case 76: return BMC_POT_77_PIN;
#if defined(BMC_POT_78_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=78 && BMC_MAX_POTS > 77 && defined(BMC_POT_78_X) && defined(BMC_POT_78_Y)
  case 77: return BMC_POT_78_PIN;
#if defined(BMC_POT_79_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=79 && BMC_MAX_POTS > 78 && defined(BMC_POT_79_X) && defined(BMC_POT_79_Y)
  case 78: return BMC_POT_79_PIN;
#if defined(BMC_POT_80_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=80 && BMC_MAX_POTS > 79 && defined(BMC_POT_80_X) && defined(BMC_POT_80_Y)
  case 79: return BMC_POT_80_PIN;
#if defined(BMC_POT_81_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=81 && BMC_MAX_POTS > 80 && defined(BMC_POT_81_X) && defined(BMC_POT_81_Y)
  case 80: return BMC_POT_81_PIN;
#if defined(BMC_POT_82_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=82 && BMC_MAX_POTS > 81 && defined(BMC_POT_82_X) && defined(BMC_POT_82_Y)
  case 81: return BMC_POT_82_PIN;
#if defined(BMC_POT_83_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=83 && BMC_MAX_POTS > 82 && defined(BMC_POT_83_X) && defined(BMC_POT_83_Y)
  case 82: return BMC_POT_83_PIN;
#if defined(BMC_POT_84_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=84 && BMC_MAX_POTS > 83 && defined(BMC_POT_84_X) && defined(BMC_POT_84_Y)
  case 83: return BMC_POT_84_PIN;
#if defined(BMC_POT_85_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=85 && BMC_MAX_POTS > 84 && defined(BMC_POT_85_X) && defined(BMC_POT_85_Y)
  case 84: return BMC_POT_85_PIN;
#if defined(BMC_POT_86_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=86 && BMC_MAX_POTS > 85 && defined(BMC_POT_86_X) && defined(BMC_POT_86_Y)
  case 85: return BMC_POT_86_PIN;
#if defined(BMC_POT_87_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=87 && BMC_MAX_POTS > 86 && defined(BMC_POT_87_X) && defined(BMC_POT_87_Y)
  case 86: return BMC_POT_87_PIN;
#if defined(BMC_POT_88_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=88 && BMC_MAX_POTS > 87 && defined(BMC_POT_88_X) && defined(BMC_POT_88_Y)
  case 87: return BMC_POT_88_PIN;
#if defined(BMC_POT_89_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=89 && BMC_MAX_POTS > 88 && defined(BMC_POT_89_X) && defined(BMC_POT_89_Y)
  case 88: return BMC_POT_89_PIN;
#if defined(BMC_POT_90_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=90 && BMC_MAX_POTS > 89 && defined(BMC_POT_90_X) && defined(BMC_POT_90_Y)
  case 89: return BMC_POT_90_PIN;
#if defined(BMC_POT_91_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=91 && BMC_MAX_POTS > 90 && defined(BMC_POT_91_X) && defined(BMC_POT_91_Y)
  case 90: return BMC_POT_91_PIN;
#if defined(BMC_POT_92_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=92 && BMC_MAX_POTS > 91 && defined(BMC_POT_92_X) && defined(BMC_POT_92_Y)
  case 91: return BMC_POT_92_PIN;
#if defined(BMC_POT_93_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=93 && BMC_MAX_POTS > 92 && defined(BMC_POT_93_X) && defined(BMC_POT_93_Y)
  case 92: return BMC_POT_93_PIN;
#if defined(BMC_POT_94_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=94 && BMC_MAX_POTS > 93 && defined(BMC_POT_94_X) && defined(BMC_POT_94_Y)
  case 93: return BMC_POT_94_PIN;
#if defined(BMC_POT_95_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=95 && BMC_MAX_POTS > 94 && defined(BMC_POT_95_X) && defined(BMC_POT_95_Y)
  case 94: return BMC_POT_95_PIN;
#if defined(BMC_POT_96_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=96 && BMC_MAX_POTS > 95 && defined(BMC_POT_96_X) && defined(BMC_POT_96_Y)
  case 95: return BMC_POT_96_PIN;
#if defined(BMC_POT_97_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=97 && BMC_MAX_POTS > 96 && defined(BMC_POT_97_X) && defined(BMC_POT_97_Y)
  case 96: return BMC_POT_97_PIN;
#if defined(BMC_POT_98_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=98 && BMC_MAX_POTS > 97 && defined(BMC_POT_98_X) && defined(BMC_POT_98_Y)
  case 97: return BMC_POT_98_PIN;
#if defined(BMC_POT_99_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=99 && BMC_MAX_POTS > 98 && defined(BMC_POT_99_X) && defined(BMC_POT_99_Y)
  case 98: return BMC_POT_99_PIN;
#if defined(BMC_POT_100_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=100 && BMC_MAX_POTS > 99 && defined(BMC_POT_100_X) && defined(BMC_POT_100_Y)
  case 99: return BMC_POT_100_PIN;
#if defined(BMC_POT_101_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=101 && BMC_MAX_POTS > 100 && defined(BMC_POT_101_X) && defined(BMC_POT_101_Y)
  case 100: return BMC_POT_101_PIN;
#if defined(BMC_POT_102_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=102 && BMC_MAX_POTS > 101 && defined(BMC_POT_102_X) && defined(BMC_POT_102_Y)
  case 101: return BMC_POT_102_PIN;
#if defined(BMC_POT_103_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=103 && BMC_MAX_POTS > 102 && defined(BMC_POT_103_X) && defined(BMC_POT_103_Y)
  case 102: return BMC_POT_103_PIN;
#if defined(BMC_POT_104_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=104 && BMC_MAX_POTS > 103 && defined(BMC_POT_104_X) && defined(BMC_POT_104_Y)
  case 103: return BMC_POT_104_PIN;
#if defined(BMC_POT_105_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=105 && BMC_MAX_POTS > 104 && defined(BMC_POT_105_X) && defined(BMC_POT_105_Y)
  case 104: return BMC_POT_105_PIN;
#if defined(BMC_POT_106_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=106 && BMC_MAX_POTS > 105 && defined(BMC_POT_106_X) && defined(BMC_POT_106_Y)
  case 105: return BMC_POT_106_PIN;
#if defined(BMC_POT_107_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=107 && BMC_MAX_POTS > 106 && defined(BMC_POT_107_X) && defined(BMC_POT_107_Y)
  case 106: return BMC_POT_107_PIN;
#if defined(BMC_POT_108_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=108 && BMC_MAX_POTS > 107 && defined(BMC_POT_108_X) && defined(BMC_POT_108_Y)
  case 107: return BMC_POT_108_PIN;
#if defined(BMC_POT_109_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=109 && BMC_MAX_POTS > 108 && defined(BMC_POT_109_X) && defined(BMC_POT_109_Y)
  case 108: return BMC_POT_109_PIN;
#if defined(BMC_POT_110_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=110 && BMC_MAX_POTS > 109 && defined(BMC_POT_110_X) && defined(BMC_POT_110_Y)
  case 109: return BMC_POT_110_PIN;
#if defined(BMC_POT_111_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=111 && BMC_MAX_POTS > 110 && defined(BMC_POT_111_X) && defined(BMC_POT_111_Y)
  case 110: return BMC_POT_111_PIN;
#if defined(BMC_POT_112_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=112 && BMC_MAX_POTS > 111 && defined(BMC_POT_112_X) && defined(BMC_POT_112_Y)
  case 111: return BMC_POT_112_PIN;
#if defined(BMC_POT_113_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=113 && BMC_MAX_POTS > 112 && defined(BMC_POT_113_X) && defined(BMC_POT_113_Y)
  case 112: return BMC_POT_113_PIN;
#if defined(BMC_POT_114_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=114 && BMC_MAX_POTS > 113 && defined(BMC_POT_114_X) && defined(BMC_POT_114_Y)
  case 113: return BMC_POT_114_PIN;
#if defined(BMC_POT_115_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=115 && BMC_MAX_POTS > 114 && defined(BMC_POT_115_X) && defined(BMC_POT_115_Y)
  case 114: return BMC_POT_115_PIN;
#if defined(BMC_POT_116_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=116 && BMC_MAX_POTS > 115 && defined(BMC_POT_116_X) && defined(BMC_POT_116_Y)
  case 115: return BMC_POT_116_PIN;
#if defined(BMC_POT_117_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=117 && BMC_MAX_POTS > 116 && defined(BMC_POT_117_X) && defined(BMC_POT_117_Y)
  case 116: return BMC_POT_117_PIN;
#if defined(BMC_POT_118_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=118 && BMC_MAX_POTS > 117 && defined(BMC_POT_118_X) && defined(BMC_POT_118_Y)
  case 117: return BMC_POT_118_PIN;
#if defined(BMC_POT_119_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=119 && BMC_MAX_POTS > 118 && defined(BMC_POT_119_X) && defined(BMC_POT_119_Y)
  case 118: return BMC_POT_119_PIN;
#if defined(BMC_POT_120_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=120 && BMC_MAX_POTS > 119 && defined(BMC_POT_120_X) && defined(BMC_POT_120_Y)
  case 119: return BMC_POT_120_PIN;
#if defined(BMC_POT_121_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=121 && BMC_MAX_POTS > 120 && defined(BMC_POT_121_X) && defined(BMC_POT_121_Y)
  case 120: return BMC_POT_121_PIN;
#if defined(BMC_POT_122_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=122 && BMC_MAX_POTS > 121 && defined(BMC_POT_122_X) && defined(BMC_POT_122_Y)
  case 121: return BMC_POT_122_PIN;
#if defined(BMC_POT_123_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=123 && BMC_MAX_POTS > 122 && defined(BMC_POT_123_X) && defined(BMC_POT_123_Y)
  case 122: return BMC_POT_123_PIN;
#if defined(BMC_POT_124_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=124 && BMC_MAX_POTS > 123 && defined(BMC_POT_124_X) && defined(BMC_POT_124_Y)
  case 123: return BMC_POT_124_PIN;
#if defined(BMC_POT_125_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=125 && BMC_MAX_POTS > 124 && defined(BMC_POT_125_X) && defined(BMC_POT_125_Y)
  case 124: return BMC_POT_125_PIN;
#if defined(BMC_POT_126_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=126 && BMC_MAX_POTS > 125 && defined(BMC_POT_126_X) && defined(BMC_POT_126_Y)
  case 125: return BMC_POT_126_PIN;
#if defined(BMC_POT_127_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=127 && BMC_MAX_POTS > 126 && defined(BMC_POT_127_X) && defined(BMC_POT_127_Y)
  case 126: return BMC_POT_127_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getEncoderPinA(uint8_t index=0){
#if BMC_MAX_ENCODERS > 0
switch(index){
#if defined(BMC_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_ENCODER_1B_PIN) && BMC_MAX_ENCODERS > 0 && defined(BMC_ENCODER_1_X) && defined(BMC_ENCODER_1_Y)
  case 0: return BMC_ENCODER_1A_PIN;
#if defined(BMC_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_ENCODER_2B_PIN) && BMC_MAX_ENCODERS > 1 && defined(BMC_ENCODER_2_X) && defined(BMC_ENCODER_2_Y)
  case 1: return BMC_ENCODER_2A_PIN;
#if defined(BMC_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_ENCODER_3B_PIN) && BMC_MAX_ENCODERS > 2 && defined(BMC_ENCODER_3_X) && defined(BMC_ENCODER_3_Y)
  case 2: return BMC_ENCODER_3A_PIN;
#if defined(BMC_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_ENCODER_4B_PIN) && BMC_MAX_ENCODERS > 3 && defined(BMC_ENCODER_4_X) && defined(BMC_ENCODER_4_Y)
  case 3: return BMC_ENCODER_4A_PIN;
#if defined(BMC_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_ENCODER_5B_PIN) && BMC_MAX_ENCODERS > 4 && defined(BMC_ENCODER_5_X) && defined(BMC_ENCODER_5_Y)
  case 4: return BMC_ENCODER_5A_PIN;
#if defined(BMC_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_ENCODER_6B_PIN) && BMC_MAX_ENCODERS > 5 && defined(BMC_ENCODER_6_X) && defined(BMC_ENCODER_6_Y)
  case 5: return BMC_ENCODER_6A_PIN;
#if defined(BMC_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_ENCODER_7B_PIN) && BMC_MAX_ENCODERS > 6 && defined(BMC_ENCODER_7_X) && defined(BMC_ENCODER_7_Y)
  case 6: return BMC_ENCODER_7A_PIN;
#if defined(BMC_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_ENCODER_8B_PIN) && BMC_MAX_ENCODERS > 7 && defined(BMC_ENCODER_8_X) && defined(BMC_ENCODER_8_Y)
  case 7: return BMC_ENCODER_8A_PIN;
#if defined(BMC_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_ENCODER_9B_PIN) && BMC_MAX_ENCODERS > 8 && defined(BMC_ENCODER_9_X) && defined(BMC_ENCODER_9_Y)
  case 8: return BMC_ENCODER_9A_PIN;
#if defined(BMC_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_ENCODER_10B_PIN) && BMC_MAX_ENCODERS > 9 && defined(BMC_ENCODER_10_X) && defined(BMC_ENCODER_10_Y)
  case 9: return BMC_ENCODER_10A_PIN;
#if defined(BMC_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_ENCODER_11B_PIN) && BMC_MAX_ENCODERS > 10 && defined(BMC_ENCODER_11_X) && defined(BMC_ENCODER_11_Y)
  case 10: return BMC_ENCODER_11A_PIN;
#if defined(BMC_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_ENCODER_12B_PIN) && BMC_MAX_ENCODERS > 11 && defined(BMC_ENCODER_12_X) && defined(BMC_ENCODER_12_Y)
  case 11: return BMC_ENCODER_12A_PIN;
#if defined(BMC_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_ENCODER_13B_PIN) && BMC_MAX_ENCODERS > 12 && defined(BMC_ENCODER_13_X) && defined(BMC_ENCODER_13_Y)
  case 12: return BMC_ENCODER_13A_PIN;
#if defined(BMC_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_ENCODER_14B_PIN) && BMC_MAX_ENCODERS > 13 && defined(BMC_ENCODER_14_X) && defined(BMC_ENCODER_14_Y)
  case 13: return BMC_ENCODER_14A_PIN;
#if defined(BMC_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_ENCODER_15B_PIN) && BMC_MAX_ENCODERS > 14 && defined(BMC_ENCODER_15_X) && defined(BMC_ENCODER_15_Y)
  case 14: return BMC_ENCODER_15A_PIN;
#if defined(BMC_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_ENCODER_16B_PIN) && BMC_MAX_ENCODERS > 15 && defined(BMC_ENCODER_16_X) && defined(BMC_ENCODER_16_Y)
  case 15: return BMC_ENCODER_16A_PIN;
#if defined(BMC_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_ENCODER_17B_PIN) && BMC_MAX_ENCODERS > 16 && defined(BMC_ENCODER_17_X) && defined(BMC_ENCODER_17_Y)
  case 16: return BMC_ENCODER_17A_PIN;
#if defined(BMC_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_ENCODER_18B_PIN) && BMC_MAX_ENCODERS > 17 && defined(BMC_ENCODER_18_X) && defined(BMC_ENCODER_18_Y)
  case 17: return BMC_ENCODER_18A_PIN;
#if defined(BMC_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_ENCODER_19B_PIN) && BMC_MAX_ENCODERS > 18 && defined(BMC_ENCODER_19_X) && defined(BMC_ENCODER_19_Y)
  case 18: return BMC_ENCODER_19A_PIN;
#if defined(BMC_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_ENCODER_20B_PIN) && BMC_MAX_ENCODERS > 19 && defined(BMC_ENCODER_20_X) && defined(BMC_ENCODER_20_Y)
  case 19: return BMC_ENCODER_20A_PIN;
#if defined(BMC_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_ENCODER_21B_PIN) && BMC_MAX_ENCODERS > 20 && defined(BMC_ENCODER_21_X) && defined(BMC_ENCODER_21_Y)
  case 20: return BMC_ENCODER_21A_PIN;
#if defined(BMC_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_ENCODER_22B_PIN) && BMC_MAX_ENCODERS > 21 && defined(BMC_ENCODER_22_X) && defined(BMC_ENCODER_22_Y)
  case 21: return BMC_ENCODER_22A_PIN;
#if defined(BMC_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_ENCODER_23B_PIN) && BMC_MAX_ENCODERS > 22 && defined(BMC_ENCODER_23_X) && defined(BMC_ENCODER_23_Y)
  case 22: return BMC_ENCODER_23A_PIN;
#if defined(BMC_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_ENCODER_24B_PIN) && BMC_MAX_ENCODERS > 23 && defined(BMC_ENCODER_24_X) && defined(BMC_ENCODER_24_Y)
  case 23: return BMC_ENCODER_24A_PIN;
#if defined(BMC_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_ENCODER_25B_PIN) && BMC_MAX_ENCODERS > 24 && defined(BMC_ENCODER_25_X) && defined(BMC_ENCODER_25_Y)
  case 24: return BMC_ENCODER_25A_PIN;
#if defined(BMC_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_ENCODER_26B_PIN) && BMC_MAX_ENCODERS > 25 && defined(BMC_ENCODER_26_X) && defined(BMC_ENCODER_26_Y)
  case 25: return BMC_ENCODER_26A_PIN;
#if defined(BMC_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_ENCODER_27B_PIN) && BMC_MAX_ENCODERS > 26 && defined(BMC_ENCODER_27_X) && defined(BMC_ENCODER_27_Y)
  case 26: return BMC_ENCODER_27A_PIN;
#if defined(BMC_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_ENCODER_28B_PIN) && BMC_MAX_ENCODERS > 27 && defined(BMC_ENCODER_28_X) && defined(BMC_ENCODER_28_Y)
  case 27: return BMC_ENCODER_28A_PIN;
#if defined(BMC_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_ENCODER_29B_PIN) && BMC_MAX_ENCODERS > 28 && defined(BMC_ENCODER_29_X) && defined(BMC_ENCODER_29_Y)
  case 28: return BMC_ENCODER_29A_PIN;
#if defined(BMC_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_ENCODER_30B_PIN) && BMC_MAX_ENCODERS > 29 && defined(BMC_ENCODER_30_X) && defined(BMC_ENCODER_30_Y)
  case 29: return BMC_ENCODER_30A_PIN;
#if defined(BMC_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_ENCODER_31B_PIN) && BMC_MAX_ENCODERS > 30 && defined(BMC_ENCODER_31_X) && defined(BMC_ENCODER_31_Y)
  case 30: return BMC_ENCODER_31A_PIN;
#if defined(BMC_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_ENCODER_32B_PIN) && BMC_MAX_ENCODERS > 31 && defined(BMC_ENCODER_32_X) && defined(BMC_ENCODER_32_Y)
  case 31: return BMC_ENCODER_32A_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getEncoderPinB(uint8_t index=0){
#if BMC_MAX_ENCODERS > 0
switch(index){
#if defined(BMC_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_ENCODER_1B_PIN) && BMC_MAX_ENCODERS > 0 && defined(BMC_ENCODER_1_X) && defined(BMC_ENCODER_1_Y)
  case 0: return BMC_ENCODER_1B_PIN;
#if defined(BMC_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_ENCODER_2B_PIN) && BMC_MAX_ENCODERS > 1 && defined(BMC_ENCODER_2_X) && defined(BMC_ENCODER_2_Y)
  case 1: return BMC_ENCODER_2B_PIN;
#if defined(BMC_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_ENCODER_3B_PIN) && BMC_MAX_ENCODERS > 2 && defined(BMC_ENCODER_3_X) && defined(BMC_ENCODER_3_Y)
  case 2: return BMC_ENCODER_3B_PIN;
#if defined(BMC_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_ENCODER_4B_PIN) && BMC_MAX_ENCODERS > 3 && defined(BMC_ENCODER_4_X) && defined(BMC_ENCODER_4_Y)
  case 3: return BMC_ENCODER_4B_PIN;
#if defined(BMC_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_ENCODER_5B_PIN) && BMC_MAX_ENCODERS > 4 && defined(BMC_ENCODER_5_X) && defined(BMC_ENCODER_5_Y)
  case 4: return BMC_ENCODER_5B_PIN;
#if defined(BMC_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_ENCODER_6B_PIN) && BMC_MAX_ENCODERS > 5 && defined(BMC_ENCODER_6_X) && defined(BMC_ENCODER_6_Y)
  case 5: return BMC_ENCODER_6B_PIN;
#if defined(BMC_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_ENCODER_7B_PIN) && BMC_MAX_ENCODERS > 6 && defined(BMC_ENCODER_7_X) && defined(BMC_ENCODER_7_Y)
  case 6: return BMC_ENCODER_7B_PIN;
#if defined(BMC_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_ENCODER_8B_PIN) && BMC_MAX_ENCODERS > 7 && defined(BMC_ENCODER_8_X) && defined(BMC_ENCODER_8_Y)
  case 7: return BMC_ENCODER_8B_PIN;
#if defined(BMC_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_ENCODER_9B_PIN) && BMC_MAX_ENCODERS > 8 && defined(BMC_ENCODER_9_X) && defined(BMC_ENCODER_9_Y)
  case 8: return BMC_ENCODER_9B_PIN;
#if defined(BMC_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_ENCODER_10B_PIN) && BMC_MAX_ENCODERS > 9 && defined(BMC_ENCODER_10_X) && defined(BMC_ENCODER_10_Y)
  case 9: return BMC_ENCODER_10B_PIN;
#if defined(BMC_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_ENCODER_11B_PIN) && BMC_MAX_ENCODERS > 10 && defined(BMC_ENCODER_11_X) && defined(BMC_ENCODER_11_Y)
  case 10: return BMC_ENCODER_11B_PIN;
#if defined(BMC_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_ENCODER_12B_PIN) && BMC_MAX_ENCODERS > 11 && defined(BMC_ENCODER_12_X) && defined(BMC_ENCODER_12_Y)
  case 11: return BMC_ENCODER_12B_PIN;
#if defined(BMC_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_ENCODER_13B_PIN) && BMC_MAX_ENCODERS > 12 && defined(BMC_ENCODER_13_X) && defined(BMC_ENCODER_13_Y)
  case 12: return BMC_ENCODER_13B_PIN;
#if defined(BMC_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_ENCODER_14B_PIN) && BMC_MAX_ENCODERS > 13 && defined(BMC_ENCODER_14_X) && defined(BMC_ENCODER_14_Y)
  case 13: return BMC_ENCODER_14B_PIN;
#if defined(BMC_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_ENCODER_15B_PIN) && BMC_MAX_ENCODERS > 14 && defined(BMC_ENCODER_15_X) && defined(BMC_ENCODER_15_Y)
  case 14: return BMC_ENCODER_15B_PIN;
#if defined(BMC_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_ENCODER_16B_PIN) && BMC_MAX_ENCODERS > 15 && defined(BMC_ENCODER_16_X) && defined(BMC_ENCODER_16_Y)
  case 15: return BMC_ENCODER_16B_PIN;
#if defined(BMC_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_ENCODER_17B_PIN) && BMC_MAX_ENCODERS > 16 && defined(BMC_ENCODER_17_X) && defined(BMC_ENCODER_17_Y)
  case 16: return BMC_ENCODER_17B_PIN;
#if defined(BMC_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_ENCODER_18B_PIN) && BMC_MAX_ENCODERS > 17 && defined(BMC_ENCODER_18_X) && defined(BMC_ENCODER_18_Y)
  case 17: return BMC_ENCODER_18B_PIN;
#if defined(BMC_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_ENCODER_19B_PIN) && BMC_MAX_ENCODERS > 18 && defined(BMC_ENCODER_19_X) && defined(BMC_ENCODER_19_Y)
  case 18: return BMC_ENCODER_19B_PIN;
#if defined(BMC_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_ENCODER_20B_PIN) && BMC_MAX_ENCODERS > 19 && defined(BMC_ENCODER_20_X) && defined(BMC_ENCODER_20_Y)
  case 19: return BMC_ENCODER_20B_PIN;
#if defined(BMC_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_ENCODER_21B_PIN) && BMC_MAX_ENCODERS > 20 && defined(BMC_ENCODER_21_X) && defined(BMC_ENCODER_21_Y)
  case 20: return BMC_ENCODER_21B_PIN;
#if defined(BMC_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_ENCODER_22B_PIN) && BMC_MAX_ENCODERS > 21 && defined(BMC_ENCODER_22_X) && defined(BMC_ENCODER_22_Y)
  case 21: return BMC_ENCODER_22B_PIN;
#if defined(BMC_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_ENCODER_23B_PIN) && BMC_MAX_ENCODERS > 22 && defined(BMC_ENCODER_23_X) && defined(BMC_ENCODER_23_Y)
  case 22: return BMC_ENCODER_23B_PIN;
#if defined(BMC_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_ENCODER_24B_PIN) && BMC_MAX_ENCODERS > 23 && defined(BMC_ENCODER_24_X) && defined(BMC_ENCODER_24_Y)
  case 23: return BMC_ENCODER_24B_PIN;
#if defined(BMC_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_ENCODER_25B_PIN) && BMC_MAX_ENCODERS > 24 && defined(BMC_ENCODER_25_X) && defined(BMC_ENCODER_25_Y)
  case 24: return BMC_ENCODER_25B_PIN;
#if defined(BMC_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_ENCODER_26B_PIN) && BMC_MAX_ENCODERS > 25 && defined(BMC_ENCODER_26_X) && defined(BMC_ENCODER_26_Y)
  case 25: return BMC_ENCODER_26B_PIN;
#if defined(BMC_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_ENCODER_27B_PIN) && BMC_MAX_ENCODERS > 26 && defined(BMC_ENCODER_27_X) && defined(BMC_ENCODER_27_Y)
  case 26: return BMC_ENCODER_27B_PIN;
#if defined(BMC_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_ENCODER_28B_PIN) && BMC_MAX_ENCODERS > 27 && defined(BMC_ENCODER_28_X) && defined(BMC_ENCODER_28_Y)
  case 27: return BMC_ENCODER_28B_PIN;
#if defined(BMC_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_ENCODER_29B_PIN) && BMC_MAX_ENCODERS > 28 && defined(BMC_ENCODER_29_X) && defined(BMC_ENCODER_29_Y)
  case 28: return BMC_ENCODER_29B_PIN;
#if defined(BMC_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_ENCODER_30B_PIN) && BMC_MAX_ENCODERS > 29 && defined(BMC_ENCODER_30_X) && defined(BMC_ENCODER_30_Y)
  case 29: return BMC_ENCODER_30B_PIN;
#if defined(BMC_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_ENCODER_31B_PIN) && BMC_MAX_ENCODERS > 30 && defined(BMC_ENCODER_31_X) && defined(BMC_ENCODER_31_Y)
  case 30: return BMC_ENCODER_31B_PIN;
#if defined(BMC_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_ENCODER_32B_PIN) && BMC_MAX_ENCODERS > 31 && defined(BMC_ENCODER_32_X) && defined(BMC_ENCODER_32_Y)
  case 31: return BMC_ENCODER_32B_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getPwmLedPin(uint8_t index=0){
#if BMC_MAX_PWM_LEDS > 0
switch(index){
#if defined(BMC_PWM_LED_1_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=1 && BMC_MAX_PWM_LEDS > 0 && defined(BMC_PWM_LED_1_X) && defined(BMC_PWM_LED_1_Y)
  case 0: return BMC_PWM_LED_1_PIN;
#if defined(BMC_PWM_LED_2_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=2 && BMC_MAX_PWM_LEDS > 1 && defined(BMC_PWM_LED_2_X) && defined(BMC_PWM_LED_2_Y)
  case 1: return BMC_PWM_LED_2_PIN;
#if defined(BMC_PWM_LED_3_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=3 && BMC_MAX_PWM_LEDS > 2 && defined(BMC_PWM_LED_3_X) && defined(BMC_PWM_LED_3_Y)
  case 2: return BMC_PWM_LED_3_PIN;
#if defined(BMC_PWM_LED_4_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=4 && BMC_MAX_PWM_LEDS > 3 && defined(BMC_PWM_LED_4_X) && defined(BMC_PWM_LED_4_Y)
  case 3: return BMC_PWM_LED_4_PIN;
#if defined(BMC_PWM_LED_5_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=5 && BMC_MAX_PWM_LEDS > 4 && defined(BMC_PWM_LED_5_X) && defined(BMC_PWM_LED_5_Y)
  case 4: return BMC_PWM_LED_5_PIN;
#if defined(BMC_PWM_LED_6_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=6 && BMC_MAX_PWM_LEDS > 5 && defined(BMC_PWM_LED_6_X) && defined(BMC_PWM_LED_6_Y)
  case 5: return BMC_PWM_LED_6_PIN;
#if defined(BMC_PWM_LED_7_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=7 && BMC_MAX_PWM_LEDS > 6 && defined(BMC_PWM_LED_7_X) && defined(BMC_PWM_LED_7_Y)
  case 6: return BMC_PWM_LED_7_PIN;
#if defined(BMC_PWM_LED_8_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=8 && BMC_MAX_PWM_LEDS > 7 && defined(BMC_PWM_LED_8_X) && defined(BMC_PWM_LED_8_Y)
  case 7: return BMC_PWM_LED_8_PIN;
#if defined(BMC_PWM_LED_9_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=9 && BMC_MAX_PWM_LEDS > 8 && defined(BMC_PWM_LED_9_X) && defined(BMC_PWM_LED_9_Y)
  case 8: return BMC_PWM_LED_9_PIN;
#if defined(BMC_PWM_LED_10_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=10 && BMC_MAX_PWM_LEDS > 9 && defined(BMC_PWM_LED_10_X) && defined(BMC_PWM_LED_10_Y)
  case 9: return BMC_PWM_LED_10_PIN;
#if defined(BMC_PWM_LED_11_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=11 && BMC_MAX_PWM_LEDS > 10 && defined(BMC_PWM_LED_11_X) && defined(BMC_PWM_LED_11_Y)
  case 10: return BMC_PWM_LED_11_PIN;
#if defined(BMC_PWM_LED_12_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=12 && BMC_MAX_PWM_LEDS > 11 && defined(BMC_PWM_LED_12_X) && defined(BMC_PWM_LED_12_Y)
  case 11: return BMC_PWM_LED_12_PIN;
#if defined(BMC_PWM_LED_13_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=13 && BMC_MAX_PWM_LEDS > 12 && defined(BMC_PWM_LED_13_X) && defined(BMC_PWM_LED_13_Y)
  case 12: return BMC_PWM_LED_13_PIN;
#if defined(BMC_PWM_LED_14_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=14 && BMC_MAX_PWM_LEDS > 13 && defined(BMC_PWM_LED_14_X) && defined(BMC_PWM_LED_14_Y)
  case 13: return BMC_PWM_LED_14_PIN;
#if defined(BMC_PWM_LED_15_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=15 && BMC_MAX_PWM_LEDS > 14 && defined(BMC_PWM_LED_15_X) && defined(BMC_PWM_LED_15_Y)
  case 14: return BMC_PWM_LED_15_PIN;
#if defined(BMC_PWM_LED_16_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=16 && BMC_MAX_PWM_LEDS > 15 && defined(BMC_PWM_LED_16_X) && defined(BMC_PWM_LED_16_Y)
  case 15: return BMC_PWM_LED_16_PIN;
#if defined(BMC_PWM_LED_17_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=17 && BMC_MAX_PWM_LEDS > 16 && defined(BMC_PWM_LED_17_X) && defined(BMC_PWM_LED_17_Y)
  case 16: return BMC_PWM_LED_17_PIN;
#if defined(BMC_PWM_LED_18_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=18 && BMC_MAX_PWM_LEDS > 17 && defined(BMC_PWM_LED_18_X) && defined(BMC_PWM_LED_18_Y)
  case 17: return BMC_PWM_LED_18_PIN;
#if defined(BMC_PWM_LED_19_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=19 && BMC_MAX_PWM_LEDS > 18 && defined(BMC_PWM_LED_19_X) && defined(BMC_PWM_LED_19_Y)
  case 18: return BMC_PWM_LED_19_PIN;
#if defined(BMC_PWM_LED_20_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=20 && BMC_MAX_PWM_LEDS > 19 && defined(BMC_PWM_LED_20_X) && defined(BMC_PWM_LED_20_Y)
  case 19: return BMC_PWM_LED_20_PIN;
#if defined(BMC_PWM_LED_21_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=21 && BMC_MAX_PWM_LEDS > 20 && defined(BMC_PWM_LED_21_X) && defined(BMC_PWM_LED_21_Y)
  case 20: return BMC_PWM_LED_21_PIN;
#if defined(BMC_PWM_LED_22_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=22 && BMC_MAX_PWM_LEDS > 21 && defined(BMC_PWM_LED_22_X) && defined(BMC_PWM_LED_22_Y)
  case 21: return BMC_PWM_LED_22_PIN;
#if defined(BMC_PWM_LED_23_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=23 && BMC_MAX_PWM_LEDS > 22 && defined(BMC_PWM_LED_23_X) && defined(BMC_PWM_LED_23_Y)
  case 22: return BMC_PWM_LED_23_PIN;
#if defined(BMC_PWM_LED_24_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=24 && BMC_MAX_PWM_LEDS > 23 && defined(BMC_PWM_LED_24_X) && defined(BMC_PWM_LED_24_Y)
  case 23: return BMC_PWM_LED_24_PIN;
#if defined(BMC_PWM_LED_25_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=25 && BMC_MAX_PWM_LEDS > 24 && defined(BMC_PWM_LED_25_X) && defined(BMC_PWM_LED_25_Y)
  case 24: return BMC_PWM_LED_25_PIN;
#if defined(BMC_PWM_LED_26_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=26 && BMC_MAX_PWM_LEDS > 25 && defined(BMC_PWM_LED_26_X) && defined(BMC_PWM_LED_26_Y)
  case 25: return BMC_PWM_LED_26_PIN;
#if defined(BMC_PWM_LED_27_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=27 && BMC_MAX_PWM_LEDS > 26 && defined(BMC_PWM_LED_27_X) && defined(BMC_PWM_LED_27_Y)
  case 26: return BMC_PWM_LED_27_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getPixelDefaultColor(uint8_t index=0){
#if BMC_MAX_PIXELS > 0
switch(index){
#if BMC_MAX_PIXELS > 0 && defined(BMC_PIXEL_1_X) && defined(BMC_PIXEL_1_Y)
  case 0:return BMC_DEFAULT_PIXEL_COLOR_1;
#if BMC_MAX_PIXELS > 1 && defined(BMC_PIXEL_2_X) && defined(BMC_PIXEL_2_Y)
  case 1:return BMC_DEFAULT_PIXEL_COLOR_2;
#if BMC_MAX_PIXELS > 2 && defined(BMC_PIXEL_3_X) && defined(BMC_PIXEL_3_Y)
  case 2:return BMC_DEFAULT_PIXEL_COLOR_3;
#if BMC_MAX_PIXELS > 3 && defined(BMC_PIXEL_4_X) && defined(BMC_PIXEL_4_Y)
  case 3:return BMC_DEFAULT_PIXEL_COLOR_4;
#if BMC_MAX_PIXELS > 4 && defined(BMC_PIXEL_5_X) && defined(BMC_PIXEL_5_Y)
  case 4:return BMC_DEFAULT_PIXEL_COLOR_5;
#if BMC_MAX_PIXELS > 5 && defined(BMC_PIXEL_6_X) && defined(BMC_PIXEL_6_Y)
  case 5:return BMC_DEFAULT_PIXEL_COLOR_6;
#if BMC_MAX_PIXELS > 6 && defined(BMC_PIXEL_7_X) && defined(BMC_PIXEL_7_Y)
  case 6:return BMC_DEFAULT_PIXEL_COLOR_7;
#if BMC_MAX_PIXELS > 7 && defined(BMC_PIXEL_8_X) && defined(BMC_PIXEL_8_Y)
  case 7:return BMC_DEFAULT_PIXEL_COLOR_8;
#if BMC_MAX_PIXELS > 8 && defined(BMC_PIXEL_9_X) && defined(BMC_PIXEL_9_Y)
  case 8:return BMC_DEFAULT_PIXEL_COLOR_9;
#if BMC_MAX_PIXELS > 9 && defined(BMC_PIXEL_10_X) && defined(BMC_PIXEL_10_Y)
  case 9:return BMC_DEFAULT_PIXEL_COLOR_10;
#if BMC_MAX_PIXELS > 10 && defined(BMC_PIXEL_11_X) && defined(BMC_PIXEL_11_Y)
  case 10:return BMC_DEFAULT_PIXEL_COLOR_11;
#if BMC_MAX_PIXELS > 11 && defined(BMC_PIXEL_12_X) && defined(BMC_PIXEL_12_Y)
  case 11:return BMC_DEFAULT_PIXEL_COLOR_12;
#if BMC_MAX_PIXELS > 12 && defined(BMC_PIXEL_13_X) && defined(BMC_PIXEL_13_Y)
  case 12:return BMC_DEFAULT_PIXEL_COLOR_13;
#if BMC_MAX_PIXELS > 13 && defined(BMC_PIXEL_14_X) && defined(BMC_PIXEL_14_Y)
  case 13:return BMC_DEFAULT_PIXEL_COLOR_14;
#if BMC_MAX_PIXELS > 14 && defined(BMC_PIXEL_15_X) && defined(BMC_PIXEL_15_Y)
  case 14:return BMC_DEFAULT_PIXEL_COLOR_15;
#if BMC_MAX_PIXELS > 15 && defined(BMC_PIXEL_16_X) && defined(BMC_PIXEL_16_Y)
  case 15:return BMC_DEFAULT_PIXEL_COLOR_16;
#if BMC_MAX_PIXELS > 16 && defined(BMC_PIXEL_17_X) && defined(BMC_PIXEL_17_Y)
  case 16:return BMC_DEFAULT_PIXEL_COLOR_17;
#if BMC_MAX_PIXELS > 17 && defined(BMC_PIXEL_18_X) && defined(BMC_PIXEL_18_Y)
  case 17:return BMC_DEFAULT_PIXEL_COLOR_18;
#if BMC_MAX_PIXELS > 18 && defined(BMC_PIXEL_19_X) && defined(BMC_PIXEL_19_Y)
  case 18:return BMC_DEFAULT_PIXEL_COLOR_19;
#if BMC_MAX_PIXELS > 19 && defined(BMC_PIXEL_20_X) && defined(BMC_PIXEL_20_Y)
  case 19:return BMC_DEFAULT_PIXEL_COLOR_20;
#if BMC_MAX_PIXELS > 20 && defined(BMC_PIXEL_21_X) && defined(BMC_PIXEL_21_Y)
  case 20:return BMC_DEFAULT_PIXEL_COLOR_21;
#if BMC_MAX_PIXELS > 21 && defined(BMC_PIXEL_22_X) && defined(BMC_PIXEL_22_Y)
  case 21:return BMC_DEFAULT_PIXEL_COLOR_22;
#if BMC_MAX_PIXELS > 22 && defined(BMC_PIXEL_23_X) && defined(BMC_PIXEL_23_Y)
  case 22:return BMC_DEFAULT_PIXEL_COLOR_23;
#if BMC_MAX_PIXELS > 23 && defined(BMC_PIXEL_24_X) && defined(BMC_PIXEL_24_Y)
  case 23:return BMC_DEFAULT_PIXEL_COLOR_24;
#if BMC_MAX_PIXELS > 24 && defined(BMC_PIXEL_25_X) && defined(BMC_PIXEL_25_Y)
  case 24:return BMC_DEFAULT_PIXEL_COLOR_25;
#if BMC_MAX_PIXELS > 25 && defined(BMC_PIXEL_26_X) && defined(BMC_PIXEL_26_Y)
  case 25:return BMC_DEFAULT_PIXEL_COLOR_26;
#if BMC_MAX_PIXELS > 26 && defined(BMC_PIXEL_27_X) && defined(BMC_PIXEL_27_Y)
  case 26:return BMC_DEFAULT_PIXEL_COLOR_27;
#if BMC_MAX_PIXELS > 27 && defined(BMC_PIXEL_28_X) && defined(BMC_PIXEL_28_Y)
  case 27:return BMC_DEFAULT_PIXEL_COLOR_28;
#if BMC_MAX_PIXELS > 28 && defined(BMC_PIXEL_29_X) && defined(BMC_PIXEL_29_Y)
  case 28:return BMC_DEFAULT_PIXEL_COLOR_29;
#if BMC_MAX_PIXELS > 29 && defined(BMC_PIXEL_30_X) && defined(BMC_PIXEL_30_Y)
  case 29:return BMC_DEFAULT_PIXEL_COLOR_30;
#if BMC_MAX_PIXELS > 30 && defined(BMC_PIXEL_31_X) && defined(BMC_PIXEL_31_Y)
  case 30:return BMC_DEFAULT_PIXEL_COLOR_31;
#if BMC_MAX_PIXELS > 31 && defined(BMC_PIXEL_32_X) && defined(BMC_PIXEL_32_Y)
  case 31:return BMC_DEFAULT_PIXEL_COLOR_32;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return BMC_COLOR_RED;
}
// this class makes sure that the return value is never more than 7
// since RGB pixel should only use 3 bits
static uint8_t getRgbPixelDefaultColor(uint8_t index=0){
#if BMC_MAX_RGB_PIXELS > 0
switch(index){
#if BMC_MAX_RGB_PIXELS > 0 && defined(BMC_RGB_PIXEL_1_X) && defined(BMC_RGB_PIXEL_1_Y)
case 0:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_1)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_1));
#if BMC_MAX_RGB_PIXELS > 1 && defined(BMC_RGB_PIXEL_2_X) && defined(BMC_RGB_PIXEL_2_Y)
case 1:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_2)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_2));
#if BMC_MAX_RGB_PIXELS > 2 && defined(BMC_RGB_PIXEL_3_X) && defined(BMC_RGB_PIXEL_3_Y)
case 2:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_3)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_3));
#if BMC_MAX_RGB_PIXELS > 3 && defined(BMC_RGB_PIXEL_4_X) && defined(BMC_RGB_PIXEL_4_Y)
case 3:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_4)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_4));
#if BMC_MAX_RGB_PIXELS > 4 && defined(BMC_RGB_PIXEL_5_X) && defined(BMC_RGB_PIXEL_5_Y)
case 4:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_5)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_5));
#if BMC_MAX_RGB_PIXELS > 5 && defined(BMC_RGB_PIXEL_6_X) && defined(BMC_RGB_PIXEL_6_Y)
case 5:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_6)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_6));
#if BMC_MAX_RGB_PIXELS > 6 && defined(BMC_RGB_PIXEL_7_X) && defined(BMC_RGB_PIXEL_7_Y)
case 6:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_7)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_7));
#if BMC_MAX_RGB_PIXELS > 7 && defined(BMC_RGB_PIXEL_8_X) && defined(BMC_RGB_PIXEL_8_Y)
case 7:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_8)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_8));
#if BMC_MAX_RGB_PIXELS > 8 && defined(BMC_RGB_PIXEL_9_X) && defined(BMC_RGB_PIXEL_9_Y)
case 8:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_9)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_9));
#if BMC_MAX_RGB_PIXELS > 9 && defined(BMC_RGB_PIXEL_10_X) && defined(BMC_RGB_PIXEL_10_Y)
case 9:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_10)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_10));
#if BMC_MAX_RGB_PIXELS > 10 && defined(BMC_RGB_PIXEL_11_X) && defined(BMC_RGB_PIXEL_11_Y)
case 10:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_11)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_11));
#if BMC_MAX_RGB_PIXELS > 11 && defined(BMC_RGB_PIXEL_12_X) && defined(BMC_RGB_PIXEL_12_Y)
case 11:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_12)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_12));
#if BMC_MAX_RGB_PIXELS > 12 && defined(BMC_RGB_PIXEL_13_X) && defined(BMC_RGB_PIXEL_13_Y)
case 12:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_13)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_13));
#if BMC_MAX_RGB_PIXELS > 13 && defined(BMC_RGB_PIXEL_14_X) && defined(BMC_RGB_PIXEL_14_Y)
case 13:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_14)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_14));
#if BMC_MAX_RGB_PIXELS > 14 && defined(BMC_RGB_PIXEL_15_X) && defined(BMC_RGB_PIXEL_15_Y)
case 14:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_15)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_15));
#if BMC_MAX_RGB_PIXELS > 15 && defined(BMC_RGB_PIXEL_16_X) && defined(BMC_RGB_PIXEL_16_Y)
case 15:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_16)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_16));
#if BMC_MAX_RGB_PIXELS > 16 && defined(BMC_RGB_PIXEL_17_X) && defined(BMC_RGB_PIXEL_17_Y)
case 16:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_17)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_17));
#if BMC_MAX_RGB_PIXELS > 17 && defined(BMC_RGB_PIXEL_18_X) && defined(BMC_RGB_PIXEL_18_Y)
case 17:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_18)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_18));
#if BMC_MAX_RGB_PIXELS > 18 && defined(BMC_RGB_PIXEL_19_X) && defined(BMC_RGB_PIXEL_19_Y)
case 18:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_19)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_19));
#if BMC_MAX_RGB_PIXELS > 19 && defined(BMC_RGB_PIXEL_20_X) && defined(BMC_RGB_PIXEL_20_Y)
case 19:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_20)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_20));
#if BMC_MAX_RGB_PIXELS > 20 && defined(BMC_RGB_PIXEL_21_X) && defined(BMC_RGB_PIXEL_21_Y)
case 20:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_21)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_21));
#if BMC_MAX_RGB_PIXELS > 21 && defined(BMC_RGB_PIXEL_22_X) && defined(BMC_RGB_PIXEL_22_Y)
case 21:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_22)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_22));
#if BMC_MAX_RGB_PIXELS > 22 && defined(BMC_RGB_PIXEL_23_X) && defined(BMC_RGB_PIXEL_23_Y)
case 22:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_23)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_23));
#if BMC_MAX_RGB_PIXELS > 23 && defined(BMC_RGB_PIXEL_24_X) && defined(BMC_RGB_PIXEL_24_Y)
case 23:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_24)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_24));
#if BMC_MAX_RGB_PIXELS > 24 && defined(BMC_RGB_PIXEL_25_X) && defined(BMC_RGB_PIXEL_25_Y)
case 24:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_25)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_25));
#if BMC_MAX_RGB_PIXELS > 25 && defined(BMC_RGB_PIXEL_26_X) && defined(BMC_RGB_PIXEL_26_Y)
case 25:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_26)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_26));
#if BMC_MAX_RGB_PIXELS > 26 && defined(BMC_RGB_PIXEL_27_X) && defined(BMC_RGB_PIXEL_27_Y)
case 26:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_27)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_27));
#if BMC_MAX_RGB_PIXELS > 27 && defined(BMC_RGB_PIXEL_28_X) && defined(BMC_RGB_PIXEL_28_Y)
case 27:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_28)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_28));
#if BMC_MAX_RGB_PIXELS > 28 && defined(BMC_RGB_PIXEL_29_X) && defined(BMC_RGB_PIXEL_29_Y)
case 28:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_29)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_29));
#if BMC_MAX_RGB_PIXELS > 29 && defined(BMC_RGB_PIXEL_30_X) && defined(BMC_RGB_PIXEL_30_Y)
case 29:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_30)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_30));
#if BMC_MAX_RGB_PIXELS > 30 && defined(BMC_RGB_PIXEL_31_X) && defined(BMC_RGB_PIXEL_31_Y)
case 30:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_31)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_31));
#if BMC_MAX_RGB_PIXELS > 31 && defined(BMC_RGB_PIXEL_32_X) && defined(BMC_RGB_PIXEL_32_Y)
case 31:
return ((BMC_DEFAULT_RGB_PIXEL_COLOR_32)>7?BMC_COLOR_RED:(BMC_DEFAULT_RGB_PIXEL_COLOR_32));
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return BMC_COLOR_RED;
}
static uint8_t getGlobalButtonPin(uint8_t index=0){
#if BMC_MAX_GLOBAL_BUTTONS > 0
switch(index){
#if defined(BMC_GLOBAL_BUTTON_1_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=1 && BMC_MAX_GLOBAL_BUTTONS > 0 && defined(BMC_GLOBAL_BUTTON_1_X) && defined(BMC_GLOBAL_BUTTON_1_Y)
  case 0: return BMC_GLOBAL_BUTTON_1_PIN;
#if defined(BMC_GLOBAL_BUTTON_2_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && BMC_MAX_GLOBAL_BUTTONS > 1 && defined(BMC_GLOBAL_BUTTON_2_X) && defined(BMC_GLOBAL_BUTTON_2_Y)
  case 1: return BMC_GLOBAL_BUTTON_2_PIN;
#if defined(BMC_GLOBAL_BUTTON_3_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=3 && BMC_MAX_GLOBAL_BUTTONS > 2 && defined(BMC_GLOBAL_BUTTON_3_X) && defined(BMC_GLOBAL_BUTTON_3_Y)
  case 2: return BMC_GLOBAL_BUTTON_3_PIN;
#if defined(BMC_GLOBAL_BUTTON_4_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && BMC_MAX_GLOBAL_BUTTONS > 3 && defined(BMC_GLOBAL_BUTTON_4_X) && defined(BMC_GLOBAL_BUTTON_4_Y)
  case 3: return BMC_GLOBAL_BUTTON_4_PIN;
#if defined(BMC_GLOBAL_BUTTON_5_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=5 && BMC_MAX_GLOBAL_BUTTONS > 4 && defined(BMC_GLOBAL_BUTTON_5_X) && defined(BMC_GLOBAL_BUTTON_5_Y)
  case 4: return BMC_GLOBAL_BUTTON_5_PIN;
#if defined(BMC_GLOBAL_BUTTON_6_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && BMC_MAX_GLOBAL_BUTTONS > 5 && defined(BMC_GLOBAL_BUTTON_6_X) && defined(BMC_GLOBAL_BUTTON_6_Y)
  case 5: return BMC_GLOBAL_BUTTON_6_PIN;
#if defined(BMC_GLOBAL_BUTTON_7_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=7 && BMC_MAX_GLOBAL_BUTTONS > 6 && defined(BMC_GLOBAL_BUTTON_7_X) && defined(BMC_GLOBAL_BUTTON_7_Y)
  case 6: return BMC_GLOBAL_BUTTON_7_PIN;
#if defined(BMC_GLOBAL_BUTTON_8_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && BMC_MAX_GLOBAL_BUTTONS > 7 && defined(BMC_GLOBAL_BUTTON_8_X) && defined(BMC_GLOBAL_BUTTON_8_Y)
  case 7: return BMC_GLOBAL_BUTTON_8_PIN;
#if defined(BMC_GLOBAL_BUTTON_9_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=9 && BMC_MAX_GLOBAL_BUTTONS > 8 && defined(BMC_GLOBAL_BUTTON_9_X) && defined(BMC_GLOBAL_BUTTON_9_Y)
  case 8: return BMC_GLOBAL_BUTTON_9_PIN;
#if defined(BMC_GLOBAL_BUTTON_10_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && BMC_MAX_GLOBAL_BUTTONS > 9 && defined(BMC_GLOBAL_BUTTON_10_X) && defined(BMC_GLOBAL_BUTTON_10_Y)
  case 9: return BMC_GLOBAL_BUTTON_10_PIN;
#if defined(BMC_GLOBAL_BUTTON_11_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=11 && BMC_MAX_GLOBAL_BUTTONS > 10 && defined(BMC_GLOBAL_BUTTON_11_X) && defined(BMC_GLOBAL_BUTTON_11_Y)
  case 10: return BMC_GLOBAL_BUTTON_11_PIN;
#if defined(BMC_GLOBAL_BUTTON_12_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && BMC_MAX_GLOBAL_BUTTONS > 11 && defined(BMC_GLOBAL_BUTTON_12_X) && defined(BMC_GLOBAL_BUTTON_12_Y)
  case 11: return BMC_GLOBAL_BUTTON_12_PIN;
#if defined(BMC_GLOBAL_BUTTON_13_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=13 && BMC_MAX_GLOBAL_BUTTONS > 12 && defined(BMC_GLOBAL_BUTTON_13_X) && defined(BMC_GLOBAL_BUTTON_13_Y)
  case 12: return BMC_GLOBAL_BUTTON_13_PIN;
#if defined(BMC_GLOBAL_BUTTON_14_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && BMC_MAX_GLOBAL_BUTTONS > 13 && defined(BMC_GLOBAL_BUTTON_14_X) && defined(BMC_GLOBAL_BUTTON_14_Y)
  case 13: return BMC_GLOBAL_BUTTON_14_PIN;
#if defined(BMC_GLOBAL_BUTTON_15_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=15 && BMC_MAX_GLOBAL_BUTTONS > 14 && defined(BMC_GLOBAL_BUTTON_15_X) && defined(BMC_GLOBAL_BUTTON_15_Y)
  case 14: return BMC_GLOBAL_BUTTON_15_PIN;
#if defined(BMC_GLOBAL_BUTTON_16_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && BMC_MAX_GLOBAL_BUTTONS > 15 && defined(BMC_GLOBAL_BUTTON_16_X) && defined(BMC_GLOBAL_BUTTON_16_Y)
  case 15: return BMC_GLOBAL_BUTTON_16_PIN;
#if defined(BMC_GLOBAL_BUTTON_17_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=17 && BMC_MAX_GLOBAL_BUTTONS > 16 && defined(BMC_GLOBAL_BUTTON_17_X) && defined(BMC_GLOBAL_BUTTON_17_Y)
  case 16: return BMC_GLOBAL_BUTTON_17_PIN;
#if defined(BMC_GLOBAL_BUTTON_18_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && BMC_MAX_GLOBAL_BUTTONS > 17 && defined(BMC_GLOBAL_BUTTON_18_X) && defined(BMC_GLOBAL_BUTTON_18_Y)
  case 17: return BMC_GLOBAL_BUTTON_18_PIN;
#if defined(BMC_GLOBAL_BUTTON_19_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=19 && BMC_MAX_GLOBAL_BUTTONS > 18 && defined(BMC_GLOBAL_BUTTON_19_X) && defined(BMC_GLOBAL_BUTTON_19_Y)
  case 18: return BMC_GLOBAL_BUTTON_19_PIN;
#if defined(BMC_GLOBAL_BUTTON_20_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && BMC_MAX_GLOBAL_BUTTONS > 19 && defined(BMC_GLOBAL_BUTTON_20_X) && defined(BMC_GLOBAL_BUTTON_20_Y)
  case 19: return BMC_GLOBAL_BUTTON_20_PIN;
#if defined(BMC_GLOBAL_BUTTON_21_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=21 && BMC_MAX_GLOBAL_BUTTONS > 20 && defined(BMC_GLOBAL_BUTTON_21_X) && defined(BMC_GLOBAL_BUTTON_21_Y)
  case 20: return BMC_GLOBAL_BUTTON_21_PIN;
#if defined(BMC_GLOBAL_BUTTON_22_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && BMC_MAX_GLOBAL_BUTTONS > 21 && defined(BMC_GLOBAL_BUTTON_22_X) && defined(BMC_GLOBAL_BUTTON_22_Y)
  case 21: return BMC_GLOBAL_BUTTON_22_PIN;
#if defined(BMC_GLOBAL_BUTTON_23_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=23 && BMC_MAX_GLOBAL_BUTTONS > 22 && defined(BMC_GLOBAL_BUTTON_23_X) && defined(BMC_GLOBAL_BUTTON_23_Y)
  case 22: return BMC_GLOBAL_BUTTON_23_PIN;
#if defined(BMC_GLOBAL_BUTTON_24_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && BMC_MAX_GLOBAL_BUTTONS > 23 && defined(BMC_GLOBAL_BUTTON_24_X) && defined(BMC_GLOBAL_BUTTON_24_Y)
  case 23: return BMC_GLOBAL_BUTTON_24_PIN;
#if defined(BMC_GLOBAL_BUTTON_25_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=25 && BMC_MAX_GLOBAL_BUTTONS > 24 && defined(BMC_GLOBAL_BUTTON_25_X) && defined(BMC_GLOBAL_BUTTON_25_Y)
  case 24: return BMC_GLOBAL_BUTTON_25_PIN;
#if defined(BMC_GLOBAL_BUTTON_26_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && BMC_MAX_GLOBAL_BUTTONS > 25 && defined(BMC_GLOBAL_BUTTON_26_X) && defined(BMC_GLOBAL_BUTTON_26_Y)
  case 25: return BMC_GLOBAL_BUTTON_26_PIN;
#if defined(BMC_GLOBAL_BUTTON_27_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=27 && BMC_MAX_GLOBAL_BUTTONS > 26 && defined(BMC_GLOBAL_BUTTON_27_X) && defined(BMC_GLOBAL_BUTTON_27_Y)
  case 26: return BMC_GLOBAL_BUTTON_27_PIN;
#if defined(BMC_GLOBAL_BUTTON_28_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && BMC_MAX_GLOBAL_BUTTONS > 27 && defined(BMC_GLOBAL_BUTTON_28_X) && defined(BMC_GLOBAL_BUTTON_28_Y)
  case 27: return BMC_GLOBAL_BUTTON_28_PIN;
#if defined(BMC_GLOBAL_BUTTON_29_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=29 && BMC_MAX_GLOBAL_BUTTONS > 28 && defined(BMC_GLOBAL_BUTTON_29_X) && defined(BMC_GLOBAL_BUTTON_29_Y)
  case 28: return BMC_GLOBAL_BUTTON_29_PIN;
#if defined(BMC_GLOBAL_BUTTON_30_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && BMC_MAX_GLOBAL_BUTTONS > 29 && defined(BMC_GLOBAL_BUTTON_30_X) && defined(BMC_GLOBAL_BUTTON_30_Y)
  case 29: return BMC_GLOBAL_BUTTON_30_PIN;
#if defined(BMC_GLOBAL_BUTTON_31_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=31 && BMC_MAX_GLOBAL_BUTTONS > 30 && defined(BMC_GLOBAL_BUTTON_31_X) && defined(BMC_GLOBAL_BUTTON_31_Y)
  case 30: return BMC_GLOBAL_BUTTON_31_PIN;
#if defined(BMC_GLOBAL_BUTTON_32_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && BMC_MAX_GLOBAL_BUTTONS > 31 && defined(BMC_GLOBAL_BUTTON_32_X) && defined(BMC_GLOBAL_BUTTON_32_Y)
  case 31: return BMC_GLOBAL_BUTTON_32_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getGlobalEncoderPinA(uint8_t index=0){
#if BMC_MAX_GLOBAL_ENCODERS > 0
switch(index){
#if defined(BMC_GLOBAL_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_GLOBAL_ENCODER_1B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 0 && defined(BMC_GLOBAL_ENCODER_1_X) && defined(BMC_GLOBAL_ENCODER_1_Y)
  case 0: return BMC_GLOBAL_ENCODER_1A_PIN;
#if defined(BMC_GLOBAL_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_GLOBAL_ENCODER_2B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 1 && defined(BMC_GLOBAL_ENCODER_2_X) && defined(BMC_GLOBAL_ENCODER_2_Y)
  case 1: return BMC_GLOBAL_ENCODER_2A_PIN;
#if defined(BMC_GLOBAL_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_GLOBAL_ENCODER_3B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 2 && defined(BMC_GLOBAL_ENCODER_3_X) && defined(BMC_GLOBAL_ENCODER_3_Y)
  case 2: return BMC_GLOBAL_ENCODER_3A_PIN;
#if defined(BMC_GLOBAL_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_GLOBAL_ENCODER_4B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 3 && defined(BMC_GLOBAL_ENCODER_4_X) && defined(BMC_GLOBAL_ENCODER_4_Y)
  case 3: return BMC_GLOBAL_ENCODER_4A_PIN;
#if defined(BMC_GLOBAL_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_GLOBAL_ENCODER_5B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 4 && defined(BMC_GLOBAL_ENCODER_5_X) && defined(BMC_GLOBAL_ENCODER_5_Y)
  case 4: return BMC_GLOBAL_ENCODER_5A_PIN;
#if defined(BMC_GLOBAL_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_GLOBAL_ENCODER_6B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 5 && defined(BMC_GLOBAL_ENCODER_6_X) && defined(BMC_GLOBAL_ENCODER_6_Y)
  case 5: return BMC_GLOBAL_ENCODER_6A_PIN;
#if defined(BMC_GLOBAL_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_GLOBAL_ENCODER_7B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 6 && defined(BMC_GLOBAL_ENCODER_7_X) && defined(BMC_GLOBAL_ENCODER_7_Y)
  case 6: return BMC_GLOBAL_ENCODER_7A_PIN;
#if defined(BMC_GLOBAL_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_GLOBAL_ENCODER_8B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 7 && defined(BMC_GLOBAL_ENCODER_8_X) && defined(BMC_GLOBAL_ENCODER_8_Y)
  case 7: return BMC_GLOBAL_ENCODER_8A_PIN;
#if defined(BMC_GLOBAL_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_GLOBAL_ENCODER_9B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 8 && defined(BMC_GLOBAL_ENCODER_9_X) && defined(BMC_GLOBAL_ENCODER_9_Y)
  case 8: return BMC_GLOBAL_ENCODER_9A_PIN;
#if defined(BMC_GLOBAL_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_GLOBAL_ENCODER_10B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 9 && defined(BMC_GLOBAL_ENCODER_10_X) && defined(BMC_GLOBAL_ENCODER_10_Y)
  case 9: return BMC_GLOBAL_ENCODER_10A_PIN;
#if defined(BMC_GLOBAL_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_GLOBAL_ENCODER_11B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 10 && defined(BMC_GLOBAL_ENCODER_11_X) && defined(BMC_GLOBAL_ENCODER_11_Y)
  case 10: return BMC_GLOBAL_ENCODER_11A_PIN;
#if defined(BMC_GLOBAL_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_GLOBAL_ENCODER_12B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 11 && defined(BMC_GLOBAL_ENCODER_12_X) && defined(BMC_GLOBAL_ENCODER_12_Y)
  case 11: return BMC_GLOBAL_ENCODER_12A_PIN;
#if defined(BMC_GLOBAL_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_GLOBAL_ENCODER_13B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 12 && defined(BMC_GLOBAL_ENCODER_13_X) && defined(BMC_GLOBAL_ENCODER_13_Y)
  case 12: return BMC_GLOBAL_ENCODER_13A_PIN;
#if defined(BMC_GLOBAL_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_GLOBAL_ENCODER_14B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 13 && defined(BMC_GLOBAL_ENCODER_14_X) && defined(BMC_GLOBAL_ENCODER_14_Y)
  case 13: return BMC_GLOBAL_ENCODER_14A_PIN;
#if defined(BMC_GLOBAL_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_GLOBAL_ENCODER_15B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 14 && defined(BMC_GLOBAL_ENCODER_15_X) && defined(BMC_GLOBAL_ENCODER_15_Y)
  case 14: return BMC_GLOBAL_ENCODER_15A_PIN;
#if defined(BMC_GLOBAL_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_GLOBAL_ENCODER_16B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 15 && defined(BMC_GLOBAL_ENCODER_16_X) && defined(BMC_GLOBAL_ENCODER_16_Y)
  case 15: return BMC_GLOBAL_ENCODER_16A_PIN;
#if defined(BMC_GLOBAL_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_GLOBAL_ENCODER_17B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 16 && defined(BMC_GLOBAL_ENCODER_17_X) && defined(BMC_GLOBAL_ENCODER_17_Y)
  case 16: return BMC_GLOBAL_ENCODER_17A_PIN;
#if defined(BMC_GLOBAL_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_GLOBAL_ENCODER_18B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 17 && defined(BMC_GLOBAL_ENCODER_18_X) && defined(BMC_GLOBAL_ENCODER_18_Y)
  case 17: return BMC_GLOBAL_ENCODER_18A_PIN;
#if defined(BMC_GLOBAL_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_GLOBAL_ENCODER_19B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 18 && defined(BMC_GLOBAL_ENCODER_19_X) && defined(BMC_GLOBAL_ENCODER_19_Y)
  case 18: return BMC_GLOBAL_ENCODER_19A_PIN;
#if defined(BMC_GLOBAL_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_GLOBAL_ENCODER_20B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 19 && defined(BMC_GLOBAL_ENCODER_20_X) && defined(BMC_GLOBAL_ENCODER_20_Y)
  case 19: return BMC_GLOBAL_ENCODER_20A_PIN;
#if defined(BMC_GLOBAL_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_GLOBAL_ENCODER_21B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 20 && defined(BMC_GLOBAL_ENCODER_21_X) && defined(BMC_GLOBAL_ENCODER_21_Y)
  case 20: return BMC_GLOBAL_ENCODER_21A_PIN;
#if defined(BMC_GLOBAL_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_GLOBAL_ENCODER_22B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 21 && defined(BMC_GLOBAL_ENCODER_22_X) && defined(BMC_GLOBAL_ENCODER_22_Y)
  case 21: return BMC_GLOBAL_ENCODER_22A_PIN;
#if defined(BMC_GLOBAL_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_GLOBAL_ENCODER_23B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 22 && defined(BMC_GLOBAL_ENCODER_23_X) && defined(BMC_GLOBAL_ENCODER_23_Y)
  case 22: return BMC_GLOBAL_ENCODER_23A_PIN;
#if defined(BMC_GLOBAL_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_GLOBAL_ENCODER_24B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 23 && defined(BMC_GLOBAL_ENCODER_24_X) && defined(BMC_GLOBAL_ENCODER_24_Y)
  case 23: return BMC_GLOBAL_ENCODER_24A_PIN;
#if defined(BMC_GLOBAL_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_GLOBAL_ENCODER_25B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 24 && defined(BMC_GLOBAL_ENCODER_25_X) && defined(BMC_GLOBAL_ENCODER_25_Y)
  case 24: return BMC_GLOBAL_ENCODER_25A_PIN;
#if defined(BMC_GLOBAL_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_GLOBAL_ENCODER_26B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 25 && defined(BMC_GLOBAL_ENCODER_26_X) && defined(BMC_GLOBAL_ENCODER_26_Y)
  case 25: return BMC_GLOBAL_ENCODER_26A_PIN;
#if defined(BMC_GLOBAL_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_GLOBAL_ENCODER_27B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 26 && defined(BMC_GLOBAL_ENCODER_27_X) && defined(BMC_GLOBAL_ENCODER_27_Y)
  case 26: return BMC_GLOBAL_ENCODER_27A_PIN;
#if defined(BMC_GLOBAL_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_GLOBAL_ENCODER_28B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 27 && defined(BMC_GLOBAL_ENCODER_28_X) && defined(BMC_GLOBAL_ENCODER_28_Y)
  case 27: return BMC_GLOBAL_ENCODER_28A_PIN;
#if defined(BMC_GLOBAL_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_GLOBAL_ENCODER_29B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 28 && defined(BMC_GLOBAL_ENCODER_29_X) && defined(BMC_GLOBAL_ENCODER_29_Y)
  case 28: return BMC_GLOBAL_ENCODER_29A_PIN;
#if defined(BMC_GLOBAL_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_GLOBAL_ENCODER_30B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 29 && defined(BMC_GLOBAL_ENCODER_30_X) && defined(BMC_GLOBAL_ENCODER_30_Y)
  case 29: return BMC_GLOBAL_ENCODER_30A_PIN;
#if defined(BMC_GLOBAL_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_GLOBAL_ENCODER_31B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 30 && defined(BMC_GLOBAL_ENCODER_31_X) && defined(BMC_GLOBAL_ENCODER_31_Y)
  case 30: return BMC_GLOBAL_ENCODER_31A_PIN;
#if defined(BMC_GLOBAL_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_GLOBAL_ENCODER_32B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 31 && defined(BMC_GLOBAL_ENCODER_32_X) && defined(BMC_GLOBAL_ENCODER_32_Y)
  case 31: return BMC_GLOBAL_ENCODER_32A_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getGlobalEncoderPinB(uint8_t index=0){
#if BMC_MAX_GLOBAL_ENCODERS > 0
switch(index){
#if defined(BMC_GLOBAL_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_GLOBAL_ENCODER_1B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 0 && defined(BMC_GLOBAL_ENCODER_1_X) && defined(BMC_GLOBAL_ENCODER_1_Y)
  case 0: return BMC_GLOBAL_ENCODER_1B_PIN;
#if defined(BMC_GLOBAL_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_GLOBAL_ENCODER_2B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 1 && defined(BMC_GLOBAL_ENCODER_2_X) && defined(BMC_GLOBAL_ENCODER_2_Y)
  case 1: return BMC_GLOBAL_ENCODER_2B_PIN;
#if defined(BMC_GLOBAL_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_GLOBAL_ENCODER_3B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 2 && defined(BMC_GLOBAL_ENCODER_3_X) && defined(BMC_GLOBAL_ENCODER_3_Y)
  case 2: return BMC_GLOBAL_ENCODER_3B_PIN;
#if defined(BMC_GLOBAL_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_GLOBAL_ENCODER_4B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 3 && defined(BMC_GLOBAL_ENCODER_4_X) && defined(BMC_GLOBAL_ENCODER_4_Y)
  case 3: return BMC_GLOBAL_ENCODER_4B_PIN;
#if defined(BMC_GLOBAL_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_GLOBAL_ENCODER_5B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 4 && defined(BMC_GLOBAL_ENCODER_5_X) && defined(BMC_GLOBAL_ENCODER_5_Y)
  case 4: return BMC_GLOBAL_ENCODER_5B_PIN;
#if defined(BMC_GLOBAL_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_GLOBAL_ENCODER_6B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 5 && defined(BMC_GLOBAL_ENCODER_6_X) && defined(BMC_GLOBAL_ENCODER_6_Y)
  case 5: return BMC_GLOBAL_ENCODER_6B_PIN;
#if defined(BMC_GLOBAL_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_GLOBAL_ENCODER_7B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 6 && defined(BMC_GLOBAL_ENCODER_7_X) && defined(BMC_GLOBAL_ENCODER_7_Y)
  case 6: return BMC_GLOBAL_ENCODER_7B_PIN;
#if defined(BMC_GLOBAL_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_GLOBAL_ENCODER_8B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 7 && defined(BMC_GLOBAL_ENCODER_8_X) && defined(BMC_GLOBAL_ENCODER_8_Y)
  case 7: return BMC_GLOBAL_ENCODER_8B_PIN;
#if defined(BMC_GLOBAL_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_GLOBAL_ENCODER_9B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 8 && defined(BMC_GLOBAL_ENCODER_9_X) && defined(BMC_GLOBAL_ENCODER_9_Y)
  case 8: return BMC_GLOBAL_ENCODER_9B_PIN;
#if defined(BMC_GLOBAL_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_GLOBAL_ENCODER_10B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 9 && defined(BMC_GLOBAL_ENCODER_10_X) && defined(BMC_GLOBAL_ENCODER_10_Y)
  case 9: return BMC_GLOBAL_ENCODER_10B_PIN;
#if defined(BMC_GLOBAL_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_GLOBAL_ENCODER_11B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 10 && defined(BMC_GLOBAL_ENCODER_11_X) && defined(BMC_GLOBAL_ENCODER_11_Y)
  case 10: return BMC_GLOBAL_ENCODER_11B_PIN;
#if defined(BMC_GLOBAL_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_GLOBAL_ENCODER_12B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 11 && defined(BMC_GLOBAL_ENCODER_12_X) && defined(BMC_GLOBAL_ENCODER_12_Y)
  case 11: return BMC_GLOBAL_ENCODER_12B_PIN;
#if defined(BMC_GLOBAL_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_GLOBAL_ENCODER_13B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 12 && defined(BMC_GLOBAL_ENCODER_13_X) && defined(BMC_GLOBAL_ENCODER_13_Y)
  case 12: return BMC_GLOBAL_ENCODER_13B_PIN;
#if defined(BMC_GLOBAL_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_GLOBAL_ENCODER_14B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 13 && defined(BMC_GLOBAL_ENCODER_14_X) && defined(BMC_GLOBAL_ENCODER_14_Y)
  case 13: return BMC_GLOBAL_ENCODER_14B_PIN;
#if defined(BMC_GLOBAL_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_GLOBAL_ENCODER_15B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 14 && defined(BMC_GLOBAL_ENCODER_15_X) && defined(BMC_GLOBAL_ENCODER_15_Y)
  case 14: return BMC_GLOBAL_ENCODER_15B_PIN;
#if defined(BMC_GLOBAL_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_GLOBAL_ENCODER_16B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 15 && defined(BMC_GLOBAL_ENCODER_16_X) && defined(BMC_GLOBAL_ENCODER_16_Y)
  case 15: return BMC_GLOBAL_ENCODER_16B_PIN;
#if defined(BMC_GLOBAL_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_GLOBAL_ENCODER_17B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 16 && defined(BMC_GLOBAL_ENCODER_17_X) && defined(BMC_GLOBAL_ENCODER_17_Y)
  case 16: return BMC_GLOBAL_ENCODER_17B_PIN;
#if defined(BMC_GLOBAL_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_GLOBAL_ENCODER_18B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 17 && defined(BMC_GLOBAL_ENCODER_18_X) && defined(BMC_GLOBAL_ENCODER_18_Y)
  case 17: return BMC_GLOBAL_ENCODER_18B_PIN;
#if defined(BMC_GLOBAL_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_GLOBAL_ENCODER_19B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 18 && defined(BMC_GLOBAL_ENCODER_19_X) && defined(BMC_GLOBAL_ENCODER_19_Y)
  case 18: return BMC_GLOBAL_ENCODER_19B_PIN;
#if defined(BMC_GLOBAL_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_GLOBAL_ENCODER_20B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 19 && defined(BMC_GLOBAL_ENCODER_20_X) && defined(BMC_GLOBAL_ENCODER_20_Y)
  case 19: return BMC_GLOBAL_ENCODER_20B_PIN;
#if defined(BMC_GLOBAL_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_GLOBAL_ENCODER_21B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 20 && defined(BMC_GLOBAL_ENCODER_21_X) && defined(BMC_GLOBAL_ENCODER_21_Y)
  case 20: return BMC_GLOBAL_ENCODER_21B_PIN;
#if defined(BMC_GLOBAL_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_GLOBAL_ENCODER_22B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 21 && defined(BMC_GLOBAL_ENCODER_22_X) && defined(BMC_GLOBAL_ENCODER_22_Y)
  case 21: return BMC_GLOBAL_ENCODER_22B_PIN;
#if defined(BMC_GLOBAL_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_GLOBAL_ENCODER_23B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 22 && defined(BMC_GLOBAL_ENCODER_23_X) && defined(BMC_GLOBAL_ENCODER_23_Y)
  case 22: return BMC_GLOBAL_ENCODER_23B_PIN;
#if defined(BMC_GLOBAL_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_GLOBAL_ENCODER_24B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 23 && defined(BMC_GLOBAL_ENCODER_24_X) && defined(BMC_GLOBAL_ENCODER_24_Y)
  case 23: return BMC_GLOBAL_ENCODER_24B_PIN;
#if defined(BMC_GLOBAL_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_GLOBAL_ENCODER_25B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 24 && defined(BMC_GLOBAL_ENCODER_25_X) && defined(BMC_GLOBAL_ENCODER_25_Y)
  case 24: return BMC_GLOBAL_ENCODER_25B_PIN;
#if defined(BMC_GLOBAL_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_GLOBAL_ENCODER_26B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 25 && defined(BMC_GLOBAL_ENCODER_26_X) && defined(BMC_GLOBAL_ENCODER_26_Y)
  case 25: return BMC_GLOBAL_ENCODER_26B_PIN;
#if defined(BMC_GLOBAL_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_GLOBAL_ENCODER_27B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 26 && defined(BMC_GLOBAL_ENCODER_27_X) && defined(BMC_GLOBAL_ENCODER_27_Y)
  case 26: return BMC_GLOBAL_ENCODER_27B_PIN;
#if defined(BMC_GLOBAL_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_GLOBAL_ENCODER_28B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 27 && defined(BMC_GLOBAL_ENCODER_28_X) && defined(BMC_GLOBAL_ENCODER_28_Y)
  case 27: return BMC_GLOBAL_ENCODER_28B_PIN;
#if defined(BMC_GLOBAL_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_GLOBAL_ENCODER_29B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 28 && defined(BMC_GLOBAL_ENCODER_29_X) && defined(BMC_GLOBAL_ENCODER_29_Y)
  case 28: return BMC_GLOBAL_ENCODER_29B_PIN;
#if defined(BMC_GLOBAL_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_GLOBAL_ENCODER_30B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 29 && defined(BMC_GLOBAL_ENCODER_30_X) && defined(BMC_GLOBAL_ENCODER_30_Y)
  case 29: return BMC_GLOBAL_ENCODER_30B_PIN;
#if defined(BMC_GLOBAL_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_GLOBAL_ENCODER_31B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 30 && defined(BMC_GLOBAL_ENCODER_31_X) && defined(BMC_GLOBAL_ENCODER_31_Y)
  case 30: return BMC_GLOBAL_ENCODER_31B_PIN;
#if defined(BMC_GLOBAL_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_GLOBAL_ENCODER_32B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 31 && defined(BMC_GLOBAL_ENCODER_32_X) && defined(BMC_GLOBAL_ENCODER_32_Y)
  case 31: return BMC_GLOBAL_ENCODER_32B_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getGlobalPotPin(uint8_t index=0){
#if BMC_MAX_GLOBAL_POTS > 0
switch(index){
#if defined(BMC_GLOBAL_POT_1_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=1 && BMC_MAX_GLOBAL_POTS > 0 && defined(BMC_GLOBAL_POT_1_X) && defined(BMC_GLOBAL_POT_1_Y)
  case 0: return BMC_GLOBAL_POT_1_PIN;
#if defined(BMC_GLOBAL_POT_2_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=2 && BMC_MAX_GLOBAL_POTS > 1 && defined(BMC_GLOBAL_POT_2_X) && defined(BMC_GLOBAL_POT_2_Y)
  case 1: return BMC_GLOBAL_POT_2_PIN;
#if defined(BMC_GLOBAL_POT_3_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=3 && BMC_MAX_GLOBAL_POTS > 2 && defined(BMC_GLOBAL_POT_3_X) && defined(BMC_GLOBAL_POT_3_Y)
  case 2: return BMC_GLOBAL_POT_3_PIN;
#if defined(BMC_GLOBAL_POT_4_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=4 && BMC_MAX_GLOBAL_POTS > 3 && defined(BMC_GLOBAL_POT_4_X) && defined(BMC_GLOBAL_POT_4_Y)
  case 3: return BMC_GLOBAL_POT_4_PIN;
#if defined(BMC_GLOBAL_POT_5_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=5 && BMC_MAX_GLOBAL_POTS > 4 && defined(BMC_GLOBAL_POT_5_X) && defined(BMC_GLOBAL_POT_5_Y)
  case 4: return BMC_GLOBAL_POT_5_PIN;
#if defined(BMC_GLOBAL_POT_6_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=6 && BMC_MAX_GLOBAL_POTS > 5 && defined(BMC_GLOBAL_POT_6_X) && defined(BMC_GLOBAL_POT_6_Y)
  case 5: return BMC_GLOBAL_POT_6_PIN;
#if defined(BMC_GLOBAL_POT_7_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=7 && BMC_MAX_GLOBAL_POTS > 6 && defined(BMC_GLOBAL_POT_7_X) && defined(BMC_GLOBAL_POT_7_Y)
  case 6: return BMC_GLOBAL_POT_7_PIN;
#if defined(BMC_GLOBAL_POT_8_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=8 && BMC_MAX_GLOBAL_POTS > 7 && defined(BMC_GLOBAL_POT_8_X) && defined(BMC_GLOBAL_POT_8_Y)
  case 7: return BMC_GLOBAL_POT_8_PIN;
#if defined(BMC_GLOBAL_POT_9_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=9 && BMC_MAX_GLOBAL_POTS > 8 && defined(BMC_GLOBAL_POT_9_X) && defined(BMC_GLOBAL_POT_9_Y)
  case 8: return BMC_GLOBAL_POT_9_PIN;
#if defined(BMC_GLOBAL_POT_10_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=10 && BMC_MAX_GLOBAL_POTS > 9 && defined(BMC_GLOBAL_POT_10_X) && defined(BMC_GLOBAL_POT_10_Y)
  case 9: return BMC_GLOBAL_POT_10_PIN;
#if defined(BMC_GLOBAL_POT_11_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=11 && BMC_MAX_GLOBAL_POTS > 10 && defined(BMC_GLOBAL_POT_11_X) && defined(BMC_GLOBAL_POT_11_Y)
  case 10: return BMC_GLOBAL_POT_11_PIN;
#if defined(BMC_GLOBAL_POT_12_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=12 && BMC_MAX_GLOBAL_POTS > 11 && defined(BMC_GLOBAL_POT_12_X) && defined(BMC_GLOBAL_POT_12_Y)
  case 11: return BMC_GLOBAL_POT_12_PIN;
#if defined(BMC_GLOBAL_POT_13_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=13 && BMC_MAX_GLOBAL_POTS > 12 && defined(BMC_GLOBAL_POT_13_X) && defined(BMC_GLOBAL_POT_13_Y)
  case 12: return BMC_GLOBAL_POT_13_PIN;
#if defined(BMC_GLOBAL_POT_14_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=14 && BMC_MAX_GLOBAL_POTS > 13 && defined(BMC_GLOBAL_POT_14_X) && defined(BMC_GLOBAL_POT_14_Y)
  case 13: return BMC_GLOBAL_POT_14_PIN;
#if defined(BMC_GLOBAL_POT_15_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=15 && BMC_MAX_GLOBAL_POTS > 14 && defined(BMC_GLOBAL_POT_15_X) && defined(BMC_GLOBAL_POT_15_Y)
  case 14: return BMC_GLOBAL_POT_15_PIN;
#if defined(BMC_GLOBAL_POT_16_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=16 && BMC_MAX_GLOBAL_POTS > 15 && defined(BMC_GLOBAL_POT_16_X) && defined(BMC_GLOBAL_POT_16_Y)
  case 15: return BMC_GLOBAL_POT_16_PIN;
#if defined(BMC_GLOBAL_POT_17_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=17 && BMC_MAX_GLOBAL_POTS > 16 && defined(BMC_GLOBAL_POT_17_X) && defined(BMC_GLOBAL_POT_17_Y)
  case 16: return BMC_GLOBAL_POT_17_PIN;
#if defined(BMC_GLOBAL_POT_18_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=18 && BMC_MAX_GLOBAL_POTS > 17 && defined(BMC_GLOBAL_POT_18_X) && defined(BMC_GLOBAL_POT_18_Y)
  case 17: return BMC_GLOBAL_POT_18_PIN;
#if defined(BMC_GLOBAL_POT_19_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=19 && BMC_MAX_GLOBAL_POTS > 18 && defined(BMC_GLOBAL_POT_19_X) && defined(BMC_GLOBAL_POT_19_Y)
  case 18: return BMC_GLOBAL_POT_19_PIN;
#if defined(BMC_GLOBAL_POT_20_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=20 && BMC_MAX_GLOBAL_POTS > 19 && defined(BMC_GLOBAL_POT_20_X) && defined(BMC_GLOBAL_POT_20_Y)
  case 19: return BMC_GLOBAL_POT_20_PIN;
#if defined(BMC_GLOBAL_POT_21_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=21 && BMC_MAX_GLOBAL_POTS > 20 && defined(BMC_GLOBAL_POT_21_X) && defined(BMC_GLOBAL_POT_21_Y)
  case 20: return BMC_GLOBAL_POT_21_PIN;
#if defined(BMC_GLOBAL_POT_22_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=22 && BMC_MAX_GLOBAL_POTS > 21 && defined(BMC_GLOBAL_POT_22_X) && defined(BMC_GLOBAL_POT_22_Y)
  case 21: return BMC_GLOBAL_POT_22_PIN;
#if defined(BMC_GLOBAL_POT_23_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=23 && BMC_MAX_GLOBAL_POTS > 22 && defined(BMC_GLOBAL_POT_23_X) && defined(BMC_GLOBAL_POT_23_Y)
  case 22: return BMC_GLOBAL_POT_23_PIN;
#if defined(BMC_GLOBAL_POT_24_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=24 && BMC_MAX_GLOBAL_POTS > 23 && defined(BMC_GLOBAL_POT_24_X) && defined(BMC_GLOBAL_POT_24_Y)
  case 23: return BMC_GLOBAL_POT_24_PIN;
#if defined(BMC_GLOBAL_POT_25_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=25 && BMC_MAX_GLOBAL_POTS > 24 && defined(BMC_GLOBAL_POT_25_X) && defined(BMC_GLOBAL_POT_25_Y)
  case 24: return BMC_GLOBAL_POT_25_PIN;
#if defined(BMC_GLOBAL_POT_26_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=26 && BMC_MAX_GLOBAL_POTS > 25 && defined(BMC_GLOBAL_POT_26_X) && defined(BMC_GLOBAL_POT_26_Y)
  case 25: return BMC_GLOBAL_POT_26_PIN;
#if defined(BMC_GLOBAL_POT_27_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=27 && BMC_MAX_GLOBAL_POTS > 26 && defined(BMC_GLOBAL_POT_27_X) && defined(BMC_GLOBAL_POT_27_Y)
  case 26: return BMC_GLOBAL_POT_27_PIN;
#if defined(BMC_GLOBAL_POT_28_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=28 && BMC_MAX_GLOBAL_POTS > 27 && defined(BMC_GLOBAL_POT_28_X) && defined(BMC_GLOBAL_POT_28_Y)
  case 27: return BMC_GLOBAL_POT_28_PIN;
#if defined(BMC_GLOBAL_POT_29_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=29 && BMC_MAX_GLOBAL_POTS > 28 && defined(BMC_GLOBAL_POT_29_X) && defined(BMC_GLOBAL_POT_29_Y)
  case 28: return BMC_GLOBAL_POT_29_PIN;
#if defined(BMC_GLOBAL_POT_30_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=30 && BMC_MAX_GLOBAL_POTS > 29 && defined(BMC_GLOBAL_POT_30_X) && defined(BMC_GLOBAL_POT_30_Y)
  case 29: return BMC_GLOBAL_POT_30_PIN;
#if defined(BMC_GLOBAL_POT_31_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=31 && BMC_MAX_GLOBAL_POTS > 30 && defined(BMC_GLOBAL_POT_31_X) && defined(BMC_GLOBAL_POT_31_Y)
  case 30: return BMC_GLOBAL_POT_31_PIN;
#if defined(BMC_GLOBAL_POT_32_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=32 && BMC_MAX_GLOBAL_POTS > 31 && defined(BMC_GLOBAL_POT_32_X) && defined(BMC_GLOBAL_POT_32_Y)
  case 31: return BMC_GLOBAL_POT_32_PIN;
#if defined(BMC_GLOBAL_POT_33_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=33 && BMC_MAX_GLOBAL_POTS > 32 && defined(BMC_GLOBAL_POT_33_X) && defined(BMC_GLOBAL_POT_33_Y)
  case 32: return BMC_GLOBAL_POT_33_PIN;
#if defined(BMC_GLOBAL_POT_34_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=34 && BMC_MAX_GLOBAL_POTS > 33 && defined(BMC_GLOBAL_POT_34_X) && defined(BMC_GLOBAL_POT_34_Y)
  case 33: return BMC_GLOBAL_POT_34_PIN;
#if defined(BMC_GLOBAL_POT_35_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=35 && BMC_MAX_GLOBAL_POTS > 34 && defined(BMC_GLOBAL_POT_35_X) && defined(BMC_GLOBAL_POT_35_Y)
  case 34: return BMC_GLOBAL_POT_35_PIN;
#if defined(BMC_GLOBAL_POT_36_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=36 && BMC_MAX_GLOBAL_POTS > 35 && defined(BMC_GLOBAL_POT_36_X) && defined(BMC_GLOBAL_POT_36_Y)
  case 35: return BMC_GLOBAL_POT_36_PIN;
#if defined(BMC_GLOBAL_POT_37_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=37 && BMC_MAX_GLOBAL_POTS > 36 && defined(BMC_GLOBAL_POT_37_X) && defined(BMC_GLOBAL_POT_37_Y)
  case 36: return BMC_GLOBAL_POT_37_PIN;
#if defined(BMC_GLOBAL_POT_38_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=38 && BMC_MAX_GLOBAL_POTS > 37 && defined(BMC_GLOBAL_POT_38_X) && defined(BMC_GLOBAL_POT_38_Y)
  case 37: return BMC_GLOBAL_POT_38_PIN;
#if defined(BMC_GLOBAL_POT_39_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=39 && BMC_MAX_GLOBAL_POTS > 38 && defined(BMC_GLOBAL_POT_39_X) && defined(BMC_GLOBAL_POT_39_Y)
  case 38: return BMC_GLOBAL_POT_39_PIN;
#if defined(BMC_GLOBAL_POT_40_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=40 && BMC_MAX_GLOBAL_POTS > 39 && defined(BMC_GLOBAL_POT_40_X) && defined(BMC_GLOBAL_POT_40_Y)
  case 39: return BMC_GLOBAL_POT_40_PIN;
#if defined(BMC_GLOBAL_POT_41_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=41 && BMC_MAX_GLOBAL_POTS > 40 && defined(BMC_GLOBAL_POT_41_X) && defined(BMC_GLOBAL_POT_41_Y)
  case 40: return BMC_GLOBAL_POT_41_PIN;
#if defined(BMC_GLOBAL_POT_42_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=42 && BMC_MAX_GLOBAL_POTS > 41 && defined(BMC_GLOBAL_POT_42_X) && defined(BMC_GLOBAL_POT_42_Y)
  case 41: return BMC_GLOBAL_POT_42_PIN;
#if defined(BMC_GLOBAL_POT_43_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=43 && BMC_MAX_GLOBAL_POTS > 42 && defined(BMC_GLOBAL_POT_43_X) && defined(BMC_GLOBAL_POT_43_Y)
  case 42: return BMC_GLOBAL_POT_43_PIN;
#if defined(BMC_GLOBAL_POT_44_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=44 && BMC_MAX_GLOBAL_POTS > 43 && defined(BMC_GLOBAL_POT_44_X) && defined(BMC_GLOBAL_POT_44_Y)
  case 43: return BMC_GLOBAL_POT_44_PIN;
#if defined(BMC_GLOBAL_POT_45_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=45 && BMC_MAX_GLOBAL_POTS > 44 && defined(BMC_GLOBAL_POT_45_X) && defined(BMC_GLOBAL_POT_45_Y)
  case 44: return BMC_GLOBAL_POT_45_PIN;
#if defined(BMC_GLOBAL_POT_46_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=46 && BMC_MAX_GLOBAL_POTS > 45 && defined(BMC_GLOBAL_POT_46_X) && defined(BMC_GLOBAL_POT_46_Y)
  case 45: return BMC_GLOBAL_POT_46_PIN;
#if defined(BMC_GLOBAL_POT_47_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=47 && BMC_MAX_GLOBAL_POTS > 46 && defined(BMC_GLOBAL_POT_47_X) && defined(BMC_GLOBAL_POT_47_Y)
  case 46: return BMC_GLOBAL_POT_47_PIN;
#if defined(BMC_GLOBAL_POT_48_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=48 && BMC_MAX_GLOBAL_POTS > 47 && defined(BMC_GLOBAL_POT_48_X) && defined(BMC_GLOBAL_POT_48_Y)
  case 47: return BMC_GLOBAL_POT_48_PIN;
#if defined(BMC_GLOBAL_POT_49_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=49 && BMC_MAX_GLOBAL_POTS > 48 && defined(BMC_GLOBAL_POT_49_X) && defined(BMC_GLOBAL_POT_49_Y)
  case 48: return BMC_GLOBAL_POT_49_PIN;
#if defined(BMC_GLOBAL_POT_50_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=50 && BMC_MAX_GLOBAL_POTS > 49 && defined(BMC_GLOBAL_POT_50_X) && defined(BMC_GLOBAL_POT_50_Y)
  case 49: return BMC_GLOBAL_POT_50_PIN;
#if defined(BMC_GLOBAL_POT_51_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=51 && BMC_MAX_GLOBAL_POTS > 50 && defined(BMC_GLOBAL_POT_51_X) && defined(BMC_GLOBAL_POT_51_Y)
  case 50: return BMC_GLOBAL_POT_51_PIN;
#if defined(BMC_GLOBAL_POT_52_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=52 && BMC_MAX_GLOBAL_POTS > 51 && defined(BMC_GLOBAL_POT_52_X) && defined(BMC_GLOBAL_POT_52_Y)
  case 51: return BMC_GLOBAL_POT_52_PIN;
#if defined(BMC_GLOBAL_POT_53_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=53 && BMC_MAX_GLOBAL_POTS > 52 && defined(BMC_GLOBAL_POT_53_X) && defined(BMC_GLOBAL_POT_53_Y)
  case 52: return BMC_GLOBAL_POT_53_PIN;
#if defined(BMC_GLOBAL_POT_54_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=54 && BMC_MAX_GLOBAL_POTS > 53 && defined(BMC_GLOBAL_POT_54_X) && defined(BMC_GLOBAL_POT_54_Y)
  case 53: return BMC_GLOBAL_POT_54_PIN;
#if defined(BMC_GLOBAL_POT_55_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=55 && BMC_MAX_GLOBAL_POTS > 54 && defined(BMC_GLOBAL_POT_55_X) && defined(BMC_GLOBAL_POT_55_Y)
  case 54: return BMC_GLOBAL_POT_55_PIN;
#if defined(BMC_GLOBAL_POT_56_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=56 && BMC_MAX_GLOBAL_POTS > 55 && defined(BMC_GLOBAL_POT_56_X) && defined(BMC_GLOBAL_POT_56_Y)
  case 55: return BMC_GLOBAL_POT_56_PIN;
#if defined(BMC_GLOBAL_POT_57_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=57 && BMC_MAX_GLOBAL_POTS > 56 && defined(BMC_GLOBAL_POT_57_X) && defined(BMC_GLOBAL_POT_57_Y)
  case 56: return BMC_GLOBAL_POT_57_PIN;
#if defined(BMC_GLOBAL_POT_58_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=58 && BMC_MAX_GLOBAL_POTS > 57 && defined(BMC_GLOBAL_POT_58_X) && defined(BMC_GLOBAL_POT_58_Y)
  case 57: return BMC_GLOBAL_POT_58_PIN;
#if defined(BMC_GLOBAL_POT_59_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=59 && BMC_MAX_GLOBAL_POTS > 58 && defined(BMC_GLOBAL_POT_59_X) && defined(BMC_GLOBAL_POT_59_Y)
  case 58: return BMC_GLOBAL_POT_59_PIN;
#if defined(BMC_GLOBAL_POT_60_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=60 && BMC_MAX_GLOBAL_POTS > 59 && defined(BMC_GLOBAL_POT_60_X) && defined(BMC_GLOBAL_POT_60_Y)
  case 59: return BMC_GLOBAL_POT_60_PIN;
#if defined(BMC_GLOBAL_POT_61_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=61 && BMC_MAX_GLOBAL_POTS > 60 && defined(BMC_GLOBAL_POT_61_X) && defined(BMC_GLOBAL_POT_61_Y)
  case 60: return BMC_GLOBAL_POT_61_PIN;
#if defined(BMC_GLOBAL_POT_62_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=62 && BMC_MAX_GLOBAL_POTS > 61 && defined(BMC_GLOBAL_POT_62_X) && defined(BMC_GLOBAL_POT_62_Y)
  case 61: return BMC_GLOBAL_POT_62_PIN;
#if defined(BMC_GLOBAL_POT_63_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=63 && BMC_MAX_GLOBAL_POTS > 62 && defined(BMC_GLOBAL_POT_63_X) && defined(BMC_GLOBAL_POT_63_Y)
  case 62: return BMC_GLOBAL_POT_63_PIN;
#if defined(BMC_GLOBAL_POT_64_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=64 && BMC_MAX_GLOBAL_POTS > 63 && defined(BMC_GLOBAL_POT_64_X) && defined(BMC_GLOBAL_POT_64_Y)
  case 63: return BMC_GLOBAL_POT_64_PIN;
#if defined(BMC_GLOBAL_POT_65_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=65 && BMC_MAX_GLOBAL_POTS > 64 && defined(BMC_GLOBAL_POT_65_X) && defined(BMC_GLOBAL_POT_65_Y)
  case 64: return BMC_GLOBAL_POT_65_PIN;
#if defined(BMC_GLOBAL_POT_66_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=66 && BMC_MAX_GLOBAL_POTS > 65 && defined(BMC_GLOBAL_POT_66_X) && defined(BMC_GLOBAL_POT_66_Y)
  case 65: return BMC_GLOBAL_POT_66_PIN;
#if defined(BMC_GLOBAL_POT_67_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=67 && BMC_MAX_GLOBAL_POTS > 66 && defined(BMC_GLOBAL_POT_67_X) && defined(BMC_GLOBAL_POT_67_Y)
  case 66: return BMC_GLOBAL_POT_67_PIN;
#if defined(BMC_GLOBAL_POT_68_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=68 && BMC_MAX_GLOBAL_POTS > 67 && defined(BMC_GLOBAL_POT_68_X) && defined(BMC_GLOBAL_POT_68_Y)
  case 67: return BMC_GLOBAL_POT_68_PIN;
#if defined(BMC_GLOBAL_POT_69_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=69 && BMC_MAX_GLOBAL_POTS > 68 && defined(BMC_GLOBAL_POT_69_X) && defined(BMC_GLOBAL_POT_69_Y)
  case 68: return BMC_GLOBAL_POT_69_PIN;
#if defined(BMC_GLOBAL_POT_70_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=70 && BMC_MAX_GLOBAL_POTS > 69 && defined(BMC_GLOBAL_POT_70_X) && defined(BMC_GLOBAL_POT_70_Y)
  case 69: return BMC_GLOBAL_POT_70_PIN;
#if defined(BMC_GLOBAL_POT_71_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=71 && BMC_MAX_GLOBAL_POTS > 70 && defined(BMC_GLOBAL_POT_71_X) && defined(BMC_GLOBAL_POT_71_Y)
  case 70: return BMC_GLOBAL_POT_71_PIN;
#if defined(BMC_GLOBAL_POT_72_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=72 && BMC_MAX_GLOBAL_POTS > 71 && defined(BMC_GLOBAL_POT_72_X) && defined(BMC_GLOBAL_POT_72_Y)
  case 71: return BMC_GLOBAL_POT_72_PIN;
#if defined(BMC_GLOBAL_POT_73_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=73 && BMC_MAX_GLOBAL_POTS > 72 && defined(BMC_GLOBAL_POT_73_X) && defined(BMC_GLOBAL_POT_73_Y)
  case 72: return BMC_GLOBAL_POT_73_PIN;
#if defined(BMC_GLOBAL_POT_74_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=74 && BMC_MAX_GLOBAL_POTS > 73 && defined(BMC_GLOBAL_POT_74_X) && defined(BMC_GLOBAL_POT_74_Y)
  case 73: return BMC_GLOBAL_POT_74_PIN;
#if defined(BMC_GLOBAL_POT_75_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=75 && BMC_MAX_GLOBAL_POTS > 74 && defined(BMC_GLOBAL_POT_75_X) && defined(BMC_GLOBAL_POT_75_Y)
  case 74: return BMC_GLOBAL_POT_75_PIN;
#if defined(BMC_GLOBAL_POT_76_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=76 && BMC_MAX_GLOBAL_POTS > 75 && defined(BMC_GLOBAL_POT_76_X) && defined(BMC_GLOBAL_POT_76_Y)
  case 75: return BMC_GLOBAL_POT_76_PIN;
#if defined(BMC_GLOBAL_POT_77_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=77 && BMC_MAX_GLOBAL_POTS > 76 && defined(BMC_GLOBAL_POT_77_X) && defined(BMC_GLOBAL_POT_77_Y)
  case 76: return BMC_GLOBAL_POT_77_PIN;
#if defined(BMC_GLOBAL_POT_78_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=78 && BMC_MAX_GLOBAL_POTS > 77 && defined(BMC_GLOBAL_POT_78_X) && defined(BMC_GLOBAL_POT_78_Y)
  case 77: return BMC_GLOBAL_POT_78_PIN;
#if defined(BMC_GLOBAL_POT_79_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=79 && BMC_MAX_GLOBAL_POTS > 78 && defined(BMC_GLOBAL_POT_79_X) && defined(BMC_GLOBAL_POT_79_Y)
  case 78: return BMC_GLOBAL_POT_79_PIN;
#if defined(BMC_GLOBAL_POT_80_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=80 && BMC_MAX_GLOBAL_POTS > 79 && defined(BMC_GLOBAL_POT_80_X) && defined(BMC_GLOBAL_POT_80_Y)
  case 79: return BMC_GLOBAL_POT_80_PIN;
#if defined(BMC_GLOBAL_POT_81_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=81 && BMC_MAX_GLOBAL_POTS > 80 && defined(BMC_GLOBAL_POT_81_X) && defined(BMC_GLOBAL_POT_81_Y)
  case 80: return BMC_GLOBAL_POT_81_PIN;
#if defined(BMC_GLOBAL_POT_82_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=82 && BMC_MAX_GLOBAL_POTS > 81 && defined(BMC_GLOBAL_POT_82_X) && defined(BMC_GLOBAL_POT_82_Y)
  case 81: return BMC_GLOBAL_POT_82_PIN;
#if defined(BMC_GLOBAL_POT_83_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=83 && BMC_MAX_GLOBAL_POTS > 82 && defined(BMC_GLOBAL_POT_83_X) && defined(BMC_GLOBAL_POT_83_Y)
  case 82: return BMC_GLOBAL_POT_83_PIN;
#if defined(BMC_GLOBAL_POT_84_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=84 && BMC_MAX_GLOBAL_POTS > 83 && defined(BMC_GLOBAL_POT_84_X) && defined(BMC_GLOBAL_POT_84_Y)
  case 83: return BMC_GLOBAL_POT_84_PIN;
#if defined(BMC_GLOBAL_POT_85_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=85 && BMC_MAX_GLOBAL_POTS > 84 && defined(BMC_GLOBAL_POT_85_X) && defined(BMC_GLOBAL_POT_85_Y)
  case 84: return BMC_GLOBAL_POT_85_PIN;
#if defined(BMC_GLOBAL_POT_86_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=86 && BMC_MAX_GLOBAL_POTS > 85 && defined(BMC_GLOBAL_POT_86_X) && defined(BMC_GLOBAL_POT_86_Y)
  case 85: return BMC_GLOBAL_POT_86_PIN;
#if defined(BMC_GLOBAL_POT_87_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=87 && BMC_MAX_GLOBAL_POTS > 86 && defined(BMC_GLOBAL_POT_87_X) && defined(BMC_GLOBAL_POT_87_Y)
  case 86: return BMC_GLOBAL_POT_87_PIN;
#if defined(BMC_GLOBAL_POT_88_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=88 && BMC_MAX_GLOBAL_POTS > 87 && defined(BMC_GLOBAL_POT_88_X) && defined(BMC_GLOBAL_POT_88_Y)
  case 87: return BMC_GLOBAL_POT_88_PIN;
#if defined(BMC_GLOBAL_POT_89_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=89 && BMC_MAX_GLOBAL_POTS > 88 && defined(BMC_GLOBAL_POT_89_X) && defined(BMC_GLOBAL_POT_89_Y)
  case 88: return BMC_GLOBAL_POT_89_PIN;
#if defined(BMC_GLOBAL_POT_90_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=90 && BMC_MAX_GLOBAL_POTS > 89 && defined(BMC_GLOBAL_POT_90_X) && defined(BMC_GLOBAL_POT_90_Y)
  case 89: return BMC_GLOBAL_POT_90_PIN;
#if defined(BMC_GLOBAL_POT_91_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=91 && BMC_MAX_GLOBAL_POTS > 90 && defined(BMC_GLOBAL_POT_91_X) && defined(BMC_GLOBAL_POT_91_Y)
  case 90: return BMC_GLOBAL_POT_91_PIN;
#if defined(BMC_GLOBAL_POT_92_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=92 && BMC_MAX_GLOBAL_POTS > 91 && defined(BMC_GLOBAL_POT_92_X) && defined(BMC_GLOBAL_POT_92_Y)
  case 91: return BMC_GLOBAL_POT_92_PIN;
#if defined(BMC_GLOBAL_POT_93_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=93 && BMC_MAX_GLOBAL_POTS > 92 && defined(BMC_GLOBAL_POT_93_X) && defined(BMC_GLOBAL_POT_93_Y)
  case 92: return BMC_GLOBAL_POT_93_PIN;
#if defined(BMC_GLOBAL_POT_94_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=94 && BMC_MAX_GLOBAL_POTS > 93 && defined(BMC_GLOBAL_POT_94_X) && defined(BMC_GLOBAL_POT_94_Y)
  case 93: return BMC_GLOBAL_POT_94_PIN;
#if defined(BMC_GLOBAL_POT_95_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=95 && BMC_MAX_GLOBAL_POTS > 94 && defined(BMC_GLOBAL_POT_95_X) && defined(BMC_GLOBAL_POT_95_Y)
  case 94: return BMC_GLOBAL_POT_95_PIN;
#if defined(BMC_GLOBAL_POT_96_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=96 && BMC_MAX_GLOBAL_POTS > 95 && defined(BMC_GLOBAL_POT_96_X) && defined(BMC_GLOBAL_POT_96_Y)
  case 95: return BMC_GLOBAL_POT_96_PIN;
#if defined(BMC_GLOBAL_POT_97_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=97 && BMC_MAX_GLOBAL_POTS > 96 && defined(BMC_GLOBAL_POT_97_X) && defined(BMC_GLOBAL_POT_97_Y)
  case 96: return BMC_GLOBAL_POT_97_PIN;
#if defined(BMC_GLOBAL_POT_98_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=98 && BMC_MAX_GLOBAL_POTS > 97 && defined(BMC_GLOBAL_POT_98_X) && defined(BMC_GLOBAL_POT_98_Y)
  case 97: return BMC_GLOBAL_POT_98_PIN;
#if defined(BMC_GLOBAL_POT_99_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=99 && BMC_MAX_GLOBAL_POTS > 98 && defined(BMC_GLOBAL_POT_99_X) && defined(BMC_GLOBAL_POT_99_Y)
  case 98: return BMC_GLOBAL_POT_99_PIN;
#if defined(BMC_GLOBAL_POT_100_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=100 && BMC_MAX_GLOBAL_POTS > 99 && defined(BMC_GLOBAL_POT_100_X) && defined(BMC_GLOBAL_POT_100_Y)
  case 99: return BMC_GLOBAL_POT_100_PIN;
#if defined(BMC_GLOBAL_POT_101_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=101 && BMC_MAX_GLOBAL_POTS > 100 && defined(BMC_GLOBAL_POT_101_X) && defined(BMC_GLOBAL_POT_101_Y)
  case 100: return BMC_GLOBAL_POT_101_PIN;
#if defined(BMC_GLOBAL_POT_102_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=102 && BMC_MAX_GLOBAL_POTS > 101 && defined(BMC_GLOBAL_POT_102_X) && defined(BMC_GLOBAL_POT_102_Y)
  case 101: return BMC_GLOBAL_POT_102_PIN;
#if defined(BMC_GLOBAL_POT_103_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=103 && BMC_MAX_GLOBAL_POTS > 102 && defined(BMC_GLOBAL_POT_103_X) && defined(BMC_GLOBAL_POT_103_Y)
  case 102: return BMC_GLOBAL_POT_103_PIN;
#if defined(BMC_GLOBAL_POT_104_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=104 && BMC_MAX_GLOBAL_POTS > 103 && defined(BMC_GLOBAL_POT_104_X) && defined(BMC_GLOBAL_POT_104_Y)
  case 103: return BMC_GLOBAL_POT_104_PIN;
#if defined(BMC_GLOBAL_POT_105_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=105 && BMC_MAX_GLOBAL_POTS > 104 && defined(BMC_GLOBAL_POT_105_X) && defined(BMC_GLOBAL_POT_105_Y)
  case 104: return BMC_GLOBAL_POT_105_PIN;
#if defined(BMC_GLOBAL_POT_106_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=106 && BMC_MAX_GLOBAL_POTS > 105 && defined(BMC_GLOBAL_POT_106_X) && defined(BMC_GLOBAL_POT_106_Y)
  case 105: return BMC_GLOBAL_POT_106_PIN;
#if defined(BMC_GLOBAL_POT_107_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=107 && BMC_MAX_GLOBAL_POTS > 106 && defined(BMC_GLOBAL_POT_107_X) && defined(BMC_GLOBAL_POT_107_Y)
  case 106: return BMC_GLOBAL_POT_107_PIN;
#if defined(BMC_GLOBAL_POT_108_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=108 && BMC_MAX_GLOBAL_POTS > 107 && defined(BMC_GLOBAL_POT_108_X) && defined(BMC_GLOBAL_POT_108_Y)
  case 107: return BMC_GLOBAL_POT_108_PIN;
#if defined(BMC_GLOBAL_POT_109_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=109 && BMC_MAX_GLOBAL_POTS > 108 && defined(BMC_GLOBAL_POT_109_X) && defined(BMC_GLOBAL_POT_109_Y)
  case 108: return BMC_GLOBAL_POT_109_PIN;
#if defined(BMC_GLOBAL_POT_110_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=110 && BMC_MAX_GLOBAL_POTS > 109 && defined(BMC_GLOBAL_POT_110_X) && defined(BMC_GLOBAL_POT_110_Y)
  case 109: return BMC_GLOBAL_POT_110_PIN;
#if defined(BMC_GLOBAL_POT_111_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=111 && BMC_MAX_GLOBAL_POTS > 110 && defined(BMC_GLOBAL_POT_111_X) && defined(BMC_GLOBAL_POT_111_Y)
  case 110: return BMC_GLOBAL_POT_111_PIN;
#if defined(BMC_GLOBAL_POT_112_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=112 && BMC_MAX_GLOBAL_POTS > 111 && defined(BMC_GLOBAL_POT_112_X) && defined(BMC_GLOBAL_POT_112_Y)
  case 111: return BMC_GLOBAL_POT_112_PIN;
#if defined(BMC_GLOBAL_POT_113_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=113 && BMC_MAX_GLOBAL_POTS > 112 && defined(BMC_GLOBAL_POT_113_X) && defined(BMC_GLOBAL_POT_113_Y)
  case 112: return BMC_GLOBAL_POT_113_PIN;
#if defined(BMC_GLOBAL_POT_114_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=114 && BMC_MAX_GLOBAL_POTS > 113 && defined(BMC_GLOBAL_POT_114_X) && defined(BMC_GLOBAL_POT_114_Y)
  case 113: return BMC_GLOBAL_POT_114_PIN;
#if defined(BMC_GLOBAL_POT_115_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=115 && BMC_MAX_GLOBAL_POTS > 114 && defined(BMC_GLOBAL_POT_115_X) && defined(BMC_GLOBAL_POT_115_Y)
  case 114: return BMC_GLOBAL_POT_115_PIN;
#if defined(BMC_GLOBAL_POT_116_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=116 && BMC_MAX_GLOBAL_POTS > 115 && defined(BMC_GLOBAL_POT_116_X) && defined(BMC_GLOBAL_POT_116_Y)
  case 115: return BMC_GLOBAL_POT_116_PIN;
#if defined(BMC_GLOBAL_POT_117_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=117 && BMC_MAX_GLOBAL_POTS > 116 && defined(BMC_GLOBAL_POT_117_X) && defined(BMC_GLOBAL_POT_117_Y)
  case 116: return BMC_GLOBAL_POT_117_PIN;
#if defined(BMC_GLOBAL_POT_118_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=118 && BMC_MAX_GLOBAL_POTS > 117 && defined(BMC_GLOBAL_POT_118_X) && defined(BMC_GLOBAL_POT_118_Y)
  case 117: return BMC_GLOBAL_POT_118_PIN;
#if defined(BMC_GLOBAL_POT_119_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=119 && BMC_MAX_GLOBAL_POTS > 118 && defined(BMC_GLOBAL_POT_119_X) && defined(BMC_GLOBAL_POT_119_Y)
  case 118: return BMC_GLOBAL_POT_119_PIN;
#if defined(BMC_GLOBAL_POT_120_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=120 && BMC_MAX_GLOBAL_POTS > 119 && defined(BMC_GLOBAL_POT_120_X) && defined(BMC_GLOBAL_POT_120_Y)
  case 119: return BMC_GLOBAL_POT_120_PIN;
#if defined(BMC_GLOBAL_POT_121_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=121 && BMC_MAX_GLOBAL_POTS > 120 && defined(BMC_GLOBAL_POT_121_X) && defined(BMC_GLOBAL_POT_121_Y)
  case 120: return BMC_GLOBAL_POT_121_PIN;
#if defined(BMC_GLOBAL_POT_122_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=122 && BMC_MAX_GLOBAL_POTS > 121 && defined(BMC_GLOBAL_POT_122_X) && defined(BMC_GLOBAL_POT_122_Y)
  case 121: return BMC_GLOBAL_POT_122_PIN;
#if defined(BMC_GLOBAL_POT_123_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=123 && BMC_MAX_GLOBAL_POTS > 122 && defined(BMC_GLOBAL_POT_123_X) && defined(BMC_GLOBAL_POT_123_Y)
  case 122: return BMC_GLOBAL_POT_123_PIN;
#if defined(BMC_GLOBAL_POT_124_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=124 && BMC_MAX_GLOBAL_POTS > 123 && defined(BMC_GLOBAL_POT_124_X) && defined(BMC_GLOBAL_POT_124_Y)
  case 123: return BMC_GLOBAL_POT_124_PIN;
#if defined(BMC_GLOBAL_POT_125_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=125 && BMC_MAX_GLOBAL_POTS > 124 && defined(BMC_GLOBAL_POT_125_X) && defined(BMC_GLOBAL_POT_125_Y)
  case 124: return BMC_GLOBAL_POT_125_PIN;
#if defined(BMC_GLOBAL_POT_126_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=126 && BMC_MAX_GLOBAL_POTS > 125 && defined(BMC_GLOBAL_POT_126_X) && defined(BMC_GLOBAL_POT_126_Y)
  case 125: return BMC_GLOBAL_POT_126_PIN;
#if defined(BMC_GLOBAL_POT_127_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=127 && BMC_MAX_GLOBAL_POTS > 126 && defined(BMC_GLOBAL_POT_127_X) && defined(BMC_GLOBAL_POT_127_Y)
  case 126: return BMC_GLOBAL_POT_127_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getGlobalLedPin(uint8_t index=0){
#if BMC_MAX_GLOBAL_LEDS > 0
switch(index){
#if defined(BMC_GLOBAL_LED_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_GLOBAL_LEDS > 0 && defined(BMC_GLOBAL_LED_1_X) && defined(BMC_GLOBAL_LED_1_Y)
  case 0: return BMC_GLOBAL_LED_1_PIN;
#if defined(BMC_GLOBAL_LED_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_GLOBAL_LEDS > 1 && defined(BMC_GLOBAL_LED_2_X) && defined(BMC_GLOBAL_LED_2_Y)
  case 1: return BMC_GLOBAL_LED_2_PIN;
#if defined(BMC_GLOBAL_LED_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_GLOBAL_LEDS > 2 && defined(BMC_GLOBAL_LED_3_X) && defined(BMC_GLOBAL_LED_3_Y)
  case 2: return BMC_GLOBAL_LED_3_PIN;
#if defined(BMC_GLOBAL_LED_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_GLOBAL_LEDS > 3 && defined(BMC_GLOBAL_LED_4_X) && defined(BMC_GLOBAL_LED_4_Y)
  case 3: return BMC_GLOBAL_LED_4_PIN;
#if defined(BMC_GLOBAL_LED_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_GLOBAL_LEDS > 4 && defined(BMC_GLOBAL_LED_5_X) && defined(BMC_GLOBAL_LED_5_Y)
  case 4: return BMC_GLOBAL_LED_5_PIN;
#if defined(BMC_GLOBAL_LED_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_GLOBAL_LEDS > 5 && defined(BMC_GLOBAL_LED_6_X) && defined(BMC_GLOBAL_LED_6_Y)
  case 5: return BMC_GLOBAL_LED_6_PIN;
#if defined(BMC_GLOBAL_LED_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_GLOBAL_LEDS > 6 && defined(BMC_GLOBAL_LED_7_X) && defined(BMC_GLOBAL_LED_7_Y)
  case 6: return BMC_GLOBAL_LED_7_PIN;
#if defined(BMC_GLOBAL_LED_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_GLOBAL_LEDS > 7 && defined(BMC_GLOBAL_LED_8_X) && defined(BMC_GLOBAL_LED_8_Y)
  case 7: return BMC_GLOBAL_LED_8_PIN;
#if defined(BMC_GLOBAL_LED_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_GLOBAL_LEDS > 8 && defined(BMC_GLOBAL_LED_9_X) && defined(BMC_GLOBAL_LED_9_Y)
  case 8: return BMC_GLOBAL_LED_9_PIN;
#if defined(BMC_GLOBAL_LED_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_GLOBAL_LEDS > 9 && defined(BMC_GLOBAL_LED_10_X) && defined(BMC_GLOBAL_LED_10_Y)
  case 9: return BMC_GLOBAL_LED_10_PIN;
#if defined(BMC_GLOBAL_LED_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_GLOBAL_LEDS > 10 && defined(BMC_GLOBAL_LED_11_X) && defined(BMC_GLOBAL_LED_11_Y)
  case 10: return BMC_GLOBAL_LED_11_PIN;
#if defined(BMC_GLOBAL_LED_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_GLOBAL_LEDS > 11 && defined(BMC_GLOBAL_LED_12_X) && defined(BMC_GLOBAL_LED_12_Y)
  case 11: return BMC_GLOBAL_LED_12_PIN;
#if defined(BMC_GLOBAL_LED_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_GLOBAL_LEDS > 12 && defined(BMC_GLOBAL_LED_13_X) && defined(BMC_GLOBAL_LED_13_Y)
  case 12: return BMC_GLOBAL_LED_13_PIN;
#if defined(BMC_GLOBAL_LED_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_GLOBAL_LEDS > 13 && defined(BMC_GLOBAL_LED_14_X) && defined(BMC_GLOBAL_LED_14_Y)
  case 13: return BMC_GLOBAL_LED_14_PIN;
#if defined(BMC_GLOBAL_LED_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_GLOBAL_LEDS > 14 && defined(BMC_GLOBAL_LED_15_X) && defined(BMC_GLOBAL_LED_15_Y)
  case 14: return BMC_GLOBAL_LED_15_PIN;
#if defined(BMC_GLOBAL_LED_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_GLOBAL_LEDS > 15 && defined(BMC_GLOBAL_LED_16_X) && defined(BMC_GLOBAL_LED_16_Y)
  case 15: return BMC_GLOBAL_LED_16_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getButtonStyle(uint8_t index=0){
#if BMC_MAX_BUTTONS > 0
switch(index){
#if defined(BMC_BUTTON_1_PIN) && defined(BMC_BUTTON_1_STYLE) && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_1_X) && defined(BMC_BUTTON_1_Y)
  case 0: return BMC_BUTTON_1_STYLE;
#if defined(BMC_BUTTON_2_PIN) && defined(BMC_BUTTON_2_STYLE) && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_2_X) && defined(BMC_BUTTON_2_Y)
  case 1: return BMC_BUTTON_2_STYLE;
#if defined(BMC_BUTTON_3_PIN) && defined(BMC_BUTTON_3_STYLE) && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_3_X) && defined(BMC_BUTTON_3_Y)
  case 2: return BMC_BUTTON_3_STYLE;
#if defined(BMC_BUTTON_4_PIN) && defined(BMC_BUTTON_4_STYLE) && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_4_X) && defined(BMC_BUTTON_4_Y)
  case 3: return BMC_BUTTON_4_STYLE;
#if defined(BMC_BUTTON_5_PIN) && defined(BMC_BUTTON_5_STYLE) && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_5_X) && defined(BMC_BUTTON_5_Y)
  case 4: return BMC_BUTTON_5_STYLE;
#if defined(BMC_BUTTON_6_PIN) && defined(BMC_BUTTON_6_STYLE) && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_6_X) && defined(BMC_BUTTON_6_Y)
  case 5: return BMC_BUTTON_6_STYLE;
#if defined(BMC_BUTTON_7_PIN) && defined(BMC_BUTTON_7_STYLE) && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_7_X) && defined(BMC_BUTTON_7_Y)
  case 6: return BMC_BUTTON_7_STYLE;
#if defined(BMC_BUTTON_8_PIN) && defined(BMC_BUTTON_8_STYLE) && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_8_X) && defined(BMC_BUTTON_8_Y)
  case 7: return BMC_BUTTON_8_STYLE;
#if defined(BMC_BUTTON_9_PIN) && defined(BMC_BUTTON_9_STYLE) && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_9_X) && defined(BMC_BUTTON_9_Y)
  case 8: return BMC_BUTTON_9_STYLE;
#if defined(BMC_BUTTON_10_PIN) && defined(BMC_BUTTON_10_STYLE) && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_10_X) && defined(BMC_BUTTON_10_Y)
  case 9: return BMC_BUTTON_10_STYLE;
#if defined(BMC_BUTTON_11_PIN) && defined(BMC_BUTTON_11_STYLE) && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_11_X) && defined(BMC_BUTTON_11_Y)
  case 10: return BMC_BUTTON_11_STYLE;
#if defined(BMC_BUTTON_12_PIN) && defined(BMC_BUTTON_12_STYLE) && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_12_X) && defined(BMC_BUTTON_12_Y)
  case 11: return BMC_BUTTON_12_STYLE;
#if defined(BMC_BUTTON_13_PIN) && defined(BMC_BUTTON_13_STYLE) && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_13_X) && defined(BMC_BUTTON_13_Y)
  case 12: return BMC_BUTTON_13_STYLE;
#if defined(BMC_BUTTON_14_PIN) && defined(BMC_BUTTON_14_STYLE) && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_14_X) && defined(BMC_BUTTON_14_Y)
  case 13: return BMC_BUTTON_14_STYLE;
#if defined(BMC_BUTTON_15_PIN) && defined(BMC_BUTTON_15_STYLE) && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_15_X) && defined(BMC_BUTTON_15_Y)
  case 14: return BMC_BUTTON_15_STYLE;
#if defined(BMC_BUTTON_16_PIN) && defined(BMC_BUTTON_16_STYLE) && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_16_X) && defined(BMC_BUTTON_16_Y)
  case 15: return BMC_BUTTON_16_STYLE;
#if defined(BMC_BUTTON_17_PIN) && defined(BMC_BUTTON_17_STYLE) && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_17_X) && defined(BMC_BUTTON_17_Y)
  case 16: return BMC_BUTTON_17_STYLE;
#if defined(BMC_BUTTON_18_PIN) && defined(BMC_BUTTON_18_STYLE) && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_18_X) && defined(BMC_BUTTON_18_Y)
  case 17: return BMC_BUTTON_18_STYLE;
#if defined(BMC_BUTTON_19_PIN) && defined(BMC_BUTTON_19_STYLE) && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_19_X) && defined(BMC_BUTTON_19_Y)
  case 18: return BMC_BUTTON_19_STYLE;
#if defined(BMC_BUTTON_20_PIN) && defined(BMC_BUTTON_20_STYLE) && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_20_X) && defined(BMC_BUTTON_20_Y)
  case 19: return BMC_BUTTON_20_STYLE;
#if defined(BMC_BUTTON_21_PIN) && defined(BMC_BUTTON_21_STYLE) && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_21_X) && defined(BMC_BUTTON_21_Y)
  case 20: return BMC_BUTTON_21_STYLE;
#if defined(BMC_BUTTON_22_PIN) && defined(BMC_BUTTON_22_STYLE) && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_22_X) && defined(BMC_BUTTON_22_Y)
  case 21: return BMC_BUTTON_22_STYLE;
#if defined(BMC_BUTTON_23_PIN) && defined(BMC_BUTTON_23_STYLE) && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_23_X) && defined(BMC_BUTTON_23_Y)
  case 22: return BMC_BUTTON_23_STYLE;
#if defined(BMC_BUTTON_24_PIN) && defined(BMC_BUTTON_24_STYLE) && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_24_X) && defined(BMC_BUTTON_24_Y)
  case 23: return BMC_BUTTON_24_STYLE;
#if defined(BMC_BUTTON_25_PIN) && defined(BMC_BUTTON_25_STYLE) && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_25_X) && defined(BMC_BUTTON_25_Y)
  case 24: return BMC_BUTTON_25_STYLE;
#if defined(BMC_BUTTON_26_PIN) && defined(BMC_BUTTON_26_STYLE) && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_26_X) && defined(BMC_BUTTON_26_Y)
  case 25: return BMC_BUTTON_26_STYLE;
#if defined(BMC_BUTTON_27_PIN) && defined(BMC_BUTTON_27_STYLE) && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_27_X) && defined(BMC_BUTTON_27_Y)
  case 26: return BMC_BUTTON_27_STYLE;
#if defined(BMC_BUTTON_28_PIN) && defined(BMC_BUTTON_28_STYLE) && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_28_X) && defined(BMC_BUTTON_28_Y)
  case 27: return BMC_BUTTON_28_STYLE;
#if defined(BMC_BUTTON_29_PIN) && defined(BMC_BUTTON_29_STYLE) && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_29_X) && defined(BMC_BUTTON_29_Y)
  case 28: return BMC_BUTTON_29_STYLE;
#if defined(BMC_BUTTON_30_PIN) && defined(BMC_BUTTON_30_STYLE) && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_30_X) && defined(BMC_BUTTON_30_Y)
  case 29: return BMC_BUTTON_30_STYLE;
#if defined(BMC_BUTTON_31_PIN) && defined(BMC_BUTTON_31_STYLE) && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_31_X) && defined(BMC_BUTTON_31_Y)
  case 30: return BMC_BUTTON_31_STYLE;
#if defined(BMC_BUTTON_32_PIN) && defined(BMC_BUTTON_32_STYLE) && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_32_X) && defined(BMC_BUTTON_32_Y)
  case 31: return BMC_BUTTON_32_STYLE;
#if defined(BMC_BUTTON_33_PIN) && defined(BMC_BUTTON_33_STYLE) && BMC_MAX_BUTTONS > 32 && defined(BMC_BUTTON_33_X) && defined(BMC_BUTTON_33_Y)
  case 32: return BMC_BUTTON_33_STYLE;
#if defined(BMC_BUTTON_34_PIN) && defined(BMC_BUTTON_34_STYLE) && BMC_MAX_BUTTONS > 33 && defined(BMC_BUTTON_34_X) && defined(BMC_BUTTON_34_Y)
  case 33: return BMC_BUTTON_34_STYLE;
#if defined(BMC_BUTTON_35_PIN) && defined(BMC_BUTTON_35_STYLE) && BMC_MAX_BUTTONS > 34 && defined(BMC_BUTTON_35_X) && defined(BMC_BUTTON_35_Y)
  case 34: return BMC_BUTTON_35_STYLE;
#if defined(BMC_BUTTON_36_PIN) && defined(BMC_BUTTON_36_STYLE) && BMC_MAX_BUTTONS > 35 && defined(BMC_BUTTON_36_X) && defined(BMC_BUTTON_36_Y)
  case 35: return BMC_BUTTON_36_STYLE;
#if defined(BMC_BUTTON_37_PIN) && defined(BMC_BUTTON_37_STYLE) && BMC_MAX_BUTTONS > 36 && defined(BMC_BUTTON_37_X) && defined(BMC_BUTTON_37_Y)
  case 36: return BMC_BUTTON_37_STYLE;
#if defined(BMC_BUTTON_38_PIN) && defined(BMC_BUTTON_38_STYLE) && BMC_MAX_BUTTONS > 37 && defined(BMC_BUTTON_38_X) && defined(BMC_BUTTON_38_Y)
  case 37: return BMC_BUTTON_38_STYLE;
#if defined(BMC_BUTTON_39_PIN) && defined(BMC_BUTTON_39_STYLE) && BMC_MAX_BUTTONS > 38 && defined(BMC_BUTTON_39_X) && defined(BMC_BUTTON_39_Y)
  case 38: return BMC_BUTTON_39_STYLE;
#if defined(BMC_BUTTON_40_PIN) && defined(BMC_BUTTON_40_STYLE) && BMC_MAX_BUTTONS > 39 && defined(BMC_BUTTON_40_X) && defined(BMC_BUTTON_40_Y)
  case 39: return BMC_BUTTON_40_STYLE;
#if defined(BMC_BUTTON_41_PIN) && defined(BMC_BUTTON_41_STYLE) && BMC_MAX_BUTTONS > 40 && defined(BMC_BUTTON_41_X) && defined(BMC_BUTTON_41_Y)
  case 40: return BMC_BUTTON_41_STYLE;
#if defined(BMC_BUTTON_42_PIN) && defined(BMC_BUTTON_42_STYLE) && BMC_MAX_BUTTONS > 41 && defined(BMC_BUTTON_42_X) && defined(BMC_BUTTON_42_Y)
  case 41: return BMC_BUTTON_42_STYLE;
#if defined(BMC_BUTTON_43_PIN) && defined(BMC_BUTTON_43_STYLE) && BMC_MAX_BUTTONS > 42 && defined(BMC_BUTTON_43_X) && defined(BMC_BUTTON_43_Y)
  case 42: return BMC_BUTTON_43_STYLE;
#if defined(BMC_BUTTON_44_PIN) && defined(BMC_BUTTON_44_STYLE) && BMC_MAX_BUTTONS > 43 && defined(BMC_BUTTON_44_X) && defined(BMC_BUTTON_44_Y)
  case 43: return BMC_BUTTON_44_STYLE;
#if defined(BMC_BUTTON_45_PIN) && defined(BMC_BUTTON_45_STYLE) && BMC_MAX_BUTTONS > 44 && defined(BMC_BUTTON_45_X) && defined(BMC_BUTTON_45_Y)
  case 44: return BMC_BUTTON_45_STYLE;
#if defined(BMC_BUTTON_46_PIN) && defined(BMC_BUTTON_46_STYLE) && BMC_MAX_BUTTONS > 45 && defined(BMC_BUTTON_46_X) && defined(BMC_BUTTON_46_Y)
  case 45: return BMC_BUTTON_46_STYLE;
#if defined(BMC_BUTTON_47_PIN) && defined(BMC_BUTTON_47_STYLE) && BMC_MAX_BUTTONS > 46 && defined(BMC_BUTTON_47_X) && defined(BMC_BUTTON_47_Y)
  case 46: return BMC_BUTTON_47_STYLE;
#if defined(BMC_BUTTON_48_PIN) && defined(BMC_BUTTON_48_STYLE) && BMC_MAX_BUTTONS > 47 && defined(BMC_BUTTON_48_X) && defined(BMC_BUTTON_48_Y)
  case 47: return BMC_BUTTON_48_STYLE;
#if defined(BMC_BUTTON_49_PIN) && defined(BMC_BUTTON_49_STYLE) && BMC_MAX_BUTTONS > 48 && defined(BMC_BUTTON_49_X) && defined(BMC_BUTTON_49_Y)
  case 48: return BMC_BUTTON_49_STYLE;
#if defined(BMC_BUTTON_50_PIN) && defined(BMC_BUTTON_50_STYLE) && BMC_MAX_BUTTONS > 49 && defined(BMC_BUTTON_50_X) && defined(BMC_BUTTON_50_Y)
  case 49: return BMC_BUTTON_50_STYLE;
#if defined(BMC_BUTTON_51_PIN) && defined(BMC_BUTTON_51_STYLE) && BMC_MAX_BUTTONS > 50 && defined(BMC_BUTTON_51_X) && defined(BMC_BUTTON_51_Y)
  case 50: return BMC_BUTTON_51_STYLE;
#if defined(BMC_BUTTON_52_PIN) && defined(BMC_BUTTON_52_STYLE) && BMC_MAX_BUTTONS > 51 && defined(BMC_BUTTON_52_X) && defined(BMC_BUTTON_52_Y)
  case 51: return BMC_BUTTON_52_STYLE;
#if defined(BMC_BUTTON_53_PIN) && defined(BMC_BUTTON_53_STYLE) && BMC_MAX_BUTTONS > 52 && defined(BMC_BUTTON_53_X) && defined(BMC_BUTTON_53_Y)
  case 52: return BMC_BUTTON_53_STYLE;
#if defined(BMC_BUTTON_54_PIN) && defined(BMC_BUTTON_54_STYLE) && BMC_MAX_BUTTONS > 53 && defined(BMC_BUTTON_54_X) && defined(BMC_BUTTON_54_Y)
  case 53: return BMC_BUTTON_54_STYLE;
#if defined(BMC_BUTTON_55_PIN) && defined(BMC_BUTTON_55_STYLE) && BMC_MAX_BUTTONS > 54 && defined(BMC_BUTTON_55_X) && defined(BMC_BUTTON_55_Y)
  case 54: return BMC_BUTTON_55_STYLE;
#if defined(BMC_BUTTON_56_PIN) && defined(BMC_BUTTON_56_STYLE) && BMC_MAX_BUTTONS > 55 && defined(BMC_BUTTON_56_X) && defined(BMC_BUTTON_56_Y)
  case 55: return BMC_BUTTON_56_STYLE;
#if defined(BMC_BUTTON_57_PIN) && defined(BMC_BUTTON_57_STYLE) && BMC_MAX_BUTTONS > 56 && defined(BMC_BUTTON_57_X) && defined(BMC_BUTTON_57_Y)
  case 56: return BMC_BUTTON_57_STYLE;
#if defined(BMC_BUTTON_58_PIN) && defined(BMC_BUTTON_58_STYLE) && BMC_MAX_BUTTONS > 57 && defined(BMC_BUTTON_58_X) && defined(BMC_BUTTON_58_Y)
  case 57: return BMC_BUTTON_58_STYLE;
#if defined(BMC_BUTTON_59_PIN) && defined(BMC_BUTTON_59_STYLE) && BMC_MAX_BUTTONS > 58 && defined(BMC_BUTTON_59_X) && defined(BMC_BUTTON_59_Y)
  case 58: return BMC_BUTTON_59_STYLE;
#if defined(BMC_BUTTON_60_PIN) && defined(BMC_BUTTON_60_STYLE) && BMC_MAX_BUTTONS > 59 && defined(BMC_BUTTON_60_X) && defined(BMC_BUTTON_60_Y)
  case 59: return BMC_BUTTON_60_STYLE;
#if defined(BMC_BUTTON_61_PIN) && defined(BMC_BUTTON_61_STYLE) && BMC_MAX_BUTTONS > 60 && defined(BMC_BUTTON_61_X) && defined(BMC_BUTTON_61_Y)
  case 60: return BMC_BUTTON_61_STYLE;
#if defined(BMC_BUTTON_62_PIN) && defined(BMC_BUTTON_62_STYLE) && BMC_MAX_BUTTONS > 61 && defined(BMC_BUTTON_62_X) && defined(BMC_BUTTON_62_Y)
  case 61: return BMC_BUTTON_62_STYLE;
#if defined(BMC_BUTTON_63_PIN) && defined(BMC_BUTTON_63_STYLE) && BMC_MAX_BUTTONS > 62 && defined(BMC_BUTTON_63_X) && defined(BMC_BUTTON_63_Y)
  case 62: return BMC_BUTTON_63_STYLE;
#if defined(BMC_BUTTON_64_PIN) && defined(BMC_BUTTON_64_STYLE) && BMC_MAX_BUTTONS > 63 && defined(BMC_BUTTON_64_X) && defined(BMC_BUTTON_64_Y)
  case 63: return BMC_BUTTON_64_STYLE;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint8_t getGlobalButtonStyle(uint8_t index=0){
#if BMC_MAX_GLOBAL_BUTTONS > 0
switch(index){
#if defined(BMC_GLOBAL_BUTTON_1_PIN) && defined(BMC_GLOBAL_BUTTON_1_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 0 && defined(BMC_GLOBAL_BUTTON_1_X) && defined(BMC_GLOBAL_BUTTON_1_Y)
  case 0: return BMC_GLOBAL_BUTTON_1_STYLE;
#if defined(BMC_GLOBAL_BUTTON_2_PIN) && defined(BMC_GLOBAL_BUTTON_2_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 1 && defined(BMC_GLOBAL_BUTTON_2_X) && defined(BMC_GLOBAL_BUTTON_2_Y)
  case 1: return BMC_GLOBAL_BUTTON_2_STYLE;
#if defined(BMC_GLOBAL_BUTTON_3_PIN) && defined(BMC_GLOBAL_BUTTON_3_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 2 && defined(BMC_GLOBAL_BUTTON_3_X) && defined(BMC_GLOBAL_BUTTON_3_Y)
  case 2: return BMC_GLOBAL_BUTTON_3_STYLE;
#if defined(BMC_GLOBAL_BUTTON_4_PIN) && defined(BMC_GLOBAL_BUTTON_4_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 3 && defined(BMC_GLOBAL_BUTTON_4_X) && defined(BMC_GLOBAL_BUTTON_4_Y)
  case 3: return BMC_GLOBAL_BUTTON_4_STYLE;
#if defined(BMC_GLOBAL_BUTTON_5_PIN) && defined(BMC_GLOBAL_BUTTON_5_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 4 && defined(BMC_GLOBAL_BUTTON_5_X) && defined(BMC_GLOBAL_BUTTON_5_Y)
  case 4: return BMC_GLOBAL_BUTTON_5_STYLE;
#if defined(BMC_GLOBAL_BUTTON_6_PIN) && defined(BMC_GLOBAL_BUTTON_6_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 5 && defined(BMC_GLOBAL_BUTTON_6_X) && defined(BMC_GLOBAL_BUTTON_6_Y)
  case 5: return BMC_GLOBAL_BUTTON_6_STYLE;
#if defined(BMC_GLOBAL_BUTTON_7_PIN) && defined(BMC_GLOBAL_BUTTON_7_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 6 && defined(BMC_GLOBAL_BUTTON_7_X) && defined(BMC_GLOBAL_BUTTON_7_Y)
  case 6: return BMC_GLOBAL_BUTTON_7_STYLE;
#if defined(BMC_GLOBAL_BUTTON_8_PIN) && defined(BMC_GLOBAL_BUTTON_8_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 7 && defined(BMC_GLOBAL_BUTTON_8_X) && defined(BMC_GLOBAL_BUTTON_8_Y)
  case 7: return BMC_GLOBAL_BUTTON_8_STYLE;
#if defined(BMC_GLOBAL_BUTTON_9_PIN) && defined(BMC_GLOBAL_BUTTON_9_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 8 && defined(BMC_GLOBAL_BUTTON_9_X) && defined(BMC_GLOBAL_BUTTON_9_Y)
  case 8: return BMC_GLOBAL_BUTTON_9_STYLE;
#if defined(BMC_GLOBAL_BUTTON_10_PIN) && defined(BMC_GLOBAL_BUTTON_10_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 9 && defined(BMC_GLOBAL_BUTTON_10_X) && defined(BMC_GLOBAL_BUTTON_10_Y)
  case 9: return BMC_GLOBAL_BUTTON_10_STYLE;
#if defined(BMC_GLOBAL_BUTTON_11_PIN) && defined(BMC_GLOBAL_BUTTON_11_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 10 && defined(BMC_GLOBAL_BUTTON_11_X) && defined(BMC_GLOBAL_BUTTON_11_Y)
  case 10: return BMC_GLOBAL_BUTTON_11_STYLE;
#if defined(BMC_GLOBAL_BUTTON_12_PIN) && defined(BMC_GLOBAL_BUTTON_12_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 11 && defined(BMC_GLOBAL_BUTTON_12_X) && defined(BMC_GLOBAL_BUTTON_12_Y)
  case 11: return BMC_GLOBAL_BUTTON_12_STYLE;
#if defined(BMC_GLOBAL_BUTTON_13_PIN) && defined(BMC_GLOBAL_BUTTON_13_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 12 && defined(BMC_GLOBAL_BUTTON_13_X) && defined(BMC_GLOBAL_BUTTON_13_Y)
  case 12: return BMC_GLOBAL_BUTTON_13_STYLE;
#if defined(BMC_GLOBAL_BUTTON_14_PIN) && defined(BMC_GLOBAL_BUTTON_14_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 13 && defined(BMC_GLOBAL_BUTTON_14_X) && defined(BMC_GLOBAL_BUTTON_14_Y)
  case 13: return BMC_GLOBAL_BUTTON_14_STYLE;
#if defined(BMC_GLOBAL_BUTTON_15_PIN) && defined(BMC_GLOBAL_BUTTON_15_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 14 && defined(BMC_GLOBAL_BUTTON_15_X) && defined(BMC_GLOBAL_BUTTON_15_Y)
  case 14: return BMC_GLOBAL_BUTTON_15_STYLE;
#if defined(BMC_GLOBAL_BUTTON_16_PIN) && defined(BMC_GLOBAL_BUTTON_16_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 15 && defined(BMC_GLOBAL_BUTTON_16_X) && defined(BMC_GLOBAL_BUTTON_16_Y)
  case 15: return BMC_GLOBAL_BUTTON_16_STYLE;
#if defined(BMC_GLOBAL_BUTTON_17_PIN) && defined(BMC_GLOBAL_BUTTON_17_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 16 && defined(BMC_GLOBAL_BUTTON_17_X) && defined(BMC_GLOBAL_BUTTON_17_Y)
  case 16: return BMC_GLOBAL_BUTTON_17_STYLE;
#if defined(BMC_GLOBAL_BUTTON_18_PIN) && defined(BMC_GLOBAL_BUTTON_18_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 17 && defined(BMC_GLOBAL_BUTTON_18_X) && defined(BMC_GLOBAL_BUTTON_18_Y)
  case 17: return BMC_GLOBAL_BUTTON_18_STYLE;
#if defined(BMC_GLOBAL_BUTTON_19_PIN) && defined(BMC_GLOBAL_BUTTON_19_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 18 && defined(BMC_GLOBAL_BUTTON_19_X) && defined(BMC_GLOBAL_BUTTON_19_Y)
  case 18: return BMC_GLOBAL_BUTTON_19_STYLE;
#if defined(BMC_GLOBAL_BUTTON_20_PIN) && defined(BMC_GLOBAL_BUTTON_20_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 19 && defined(BMC_GLOBAL_BUTTON_20_X) && defined(BMC_GLOBAL_BUTTON_20_Y)
  case 19: return BMC_GLOBAL_BUTTON_20_STYLE;
#if defined(BMC_GLOBAL_BUTTON_21_PIN) && defined(BMC_GLOBAL_BUTTON_21_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 20 && defined(BMC_GLOBAL_BUTTON_21_X) && defined(BMC_GLOBAL_BUTTON_21_Y)
  case 20: return BMC_GLOBAL_BUTTON_21_STYLE;
#if defined(BMC_GLOBAL_BUTTON_22_PIN) && defined(BMC_GLOBAL_BUTTON_22_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 21 && defined(BMC_GLOBAL_BUTTON_22_X) && defined(BMC_GLOBAL_BUTTON_22_Y)
  case 21: return BMC_GLOBAL_BUTTON_22_STYLE;
#if defined(BMC_GLOBAL_BUTTON_23_PIN) && defined(BMC_GLOBAL_BUTTON_23_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 22 && defined(BMC_GLOBAL_BUTTON_23_X) && defined(BMC_GLOBAL_BUTTON_23_Y)
  case 22: return BMC_GLOBAL_BUTTON_23_STYLE;
#if defined(BMC_GLOBAL_BUTTON_24_PIN) && defined(BMC_GLOBAL_BUTTON_24_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 23 && defined(BMC_GLOBAL_BUTTON_24_X) && defined(BMC_GLOBAL_BUTTON_24_Y)
  case 23: return BMC_GLOBAL_BUTTON_24_STYLE;
#if defined(BMC_GLOBAL_BUTTON_25_PIN) && defined(BMC_GLOBAL_BUTTON_25_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 24 && defined(BMC_GLOBAL_BUTTON_25_X) && defined(BMC_GLOBAL_BUTTON_25_Y)
  case 24: return BMC_GLOBAL_BUTTON_25_STYLE;
#if defined(BMC_GLOBAL_BUTTON_26_PIN) && defined(BMC_GLOBAL_BUTTON_26_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 25 && defined(BMC_GLOBAL_BUTTON_26_X) && defined(BMC_GLOBAL_BUTTON_26_Y)
  case 25: return BMC_GLOBAL_BUTTON_26_STYLE;
#if defined(BMC_GLOBAL_BUTTON_27_PIN) && defined(BMC_GLOBAL_BUTTON_27_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 26 && defined(BMC_GLOBAL_BUTTON_27_X) && defined(BMC_GLOBAL_BUTTON_27_Y)
  case 26: return BMC_GLOBAL_BUTTON_27_STYLE;
#if defined(BMC_GLOBAL_BUTTON_28_PIN) && defined(BMC_GLOBAL_BUTTON_28_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 27 && defined(BMC_GLOBAL_BUTTON_28_X) && defined(BMC_GLOBAL_BUTTON_28_Y)
  case 27: return BMC_GLOBAL_BUTTON_28_STYLE;
#if defined(BMC_GLOBAL_BUTTON_29_PIN) && defined(BMC_GLOBAL_BUTTON_29_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 28 && defined(BMC_GLOBAL_BUTTON_29_X) && defined(BMC_GLOBAL_BUTTON_29_Y)
  case 28: return BMC_GLOBAL_BUTTON_29_STYLE;
#if defined(BMC_GLOBAL_BUTTON_30_PIN) && defined(BMC_GLOBAL_BUTTON_30_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 29 && defined(BMC_GLOBAL_BUTTON_30_X) && defined(BMC_GLOBAL_BUTTON_30_Y)
  case 29: return BMC_GLOBAL_BUTTON_30_STYLE;
#if defined(BMC_GLOBAL_BUTTON_31_PIN) && defined(BMC_GLOBAL_BUTTON_31_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 30 && defined(BMC_GLOBAL_BUTTON_31_X) && defined(BMC_GLOBAL_BUTTON_31_Y)
  case 30: return BMC_GLOBAL_BUTTON_31_STYLE;
#if defined(BMC_GLOBAL_BUTTON_32_PIN) && defined(BMC_GLOBAL_BUTTON_32_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 31 && defined(BMC_GLOBAL_BUTTON_32_X) && defined(BMC_GLOBAL_BUTTON_32_Y)
  case 31: return BMC_GLOBAL_BUTTON_32_STYLE;
#if defined(BMC_GLOBAL_BUTTON_33_PIN) && defined(BMC_GLOBAL_BUTTON_33_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 32 && defined(BMC_GLOBAL_BUTTON_33_X) && defined(BMC_GLOBAL_BUTTON_33_Y)
  case 32: return BMC_GLOBAL_BUTTON_33_STYLE;
#if defined(BMC_GLOBAL_BUTTON_34_PIN) && defined(BMC_GLOBAL_BUTTON_34_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 33 && defined(BMC_GLOBAL_BUTTON_34_X) && defined(BMC_GLOBAL_BUTTON_34_Y)
  case 33: return BMC_GLOBAL_BUTTON_34_STYLE;
#if defined(BMC_GLOBAL_BUTTON_35_PIN) && defined(BMC_GLOBAL_BUTTON_35_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 34 && defined(BMC_GLOBAL_BUTTON_35_X) && defined(BMC_GLOBAL_BUTTON_35_Y)
  case 34: return BMC_GLOBAL_BUTTON_35_STYLE;
#if defined(BMC_GLOBAL_BUTTON_36_PIN) && defined(BMC_GLOBAL_BUTTON_36_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 35 && defined(BMC_GLOBAL_BUTTON_36_X) && defined(BMC_GLOBAL_BUTTON_36_Y)
  case 35: return BMC_GLOBAL_BUTTON_36_STYLE;
#if defined(BMC_GLOBAL_BUTTON_37_PIN) && defined(BMC_GLOBAL_BUTTON_37_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 36 && defined(BMC_GLOBAL_BUTTON_37_X) && defined(BMC_GLOBAL_BUTTON_37_Y)
  case 36: return BMC_GLOBAL_BUTTON_37_STYLE;
#if defined(BMC_GLOBAL_BUTTON_38_PIN) && defined(BMC_GLOBAL_BUTTON_38_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 37 && defined(BMC_GLOBAL_BUTTON_38_X) && defined(BMC_GLOBAL_BUTTON_38_Y)
  case 37: return BMC_GLOBAL_BUTTON_38_STYLE;
#if defined(BMC_GLOBAL_BUTTON_39_PIN) && defined(BMC_GLOBAL_BUTTON_39_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 38 && defined(BMC_GLOBAL_BUTTON_39_X) && defined(BMC_GLOBAL_BUTTON_39_Y)
  case 38: return BMC_GLOBAL_BUTTON_39_STYLE;
#if defined(BMC_GLOBAL_BUTTON_40_PIN) && defined(BMC_GLOBAL_BUTTON_40_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 39 && defined(BMC_GLOBAL_BUTTON_40_X) && defined(BMC_GLOBAL_BUTTON_40_Y)
  case 39: return BMC_GLOBAL_BUTTON_40_STYLE;
#if defined(BMC_GLOBAL_BUTTON_41_PIN) && defined(BMC_GLOBAL_BUTTON_41_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 40 && defined(BMC_GLOBAL_BUTTON_41_X) && defined(BMC_GLOBAL_BUTTON_41_Y)
  case 40: return BMC_GLOBAL_BUTTON_41_STYLE;
#if defined(BMC_GLOBAL_BUTTON_42_PIN) && defined(BMC_GLOBAL_BUTTON_42_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 41 && defined(BMC_GLOBAL_BUTTON_42_X) && defined(BMC_GLOBAL_BUTTON_42_Y)
  case 41: return BMC_GLOBAL_BUTTON_42_STYLE;
#if defined(BMC_GLOBAL_BUTTON_43_PIN) && defined(BMC_GLOBAL_BUTTON_43_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 42 && defined(BMC_GLOBAL_BUTTON_43_X) && defined(BMC_GLOBAL_BUTTON_43_Y)
  case 42: return BMC_GLOBAL_BUTTON_43_STYLE;
#if defined(BMC_GLOBAL_BUTTON_44_PIN) && defined(BMC_GLOBAL_BUTTON_44_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 43 && defined(BMC_GLOBAL_BUTTON_44_X) && defined(BMC_GLOBAL_BUTTON_44_Y)
  case 43: return BMC_GLOBAL_BUTTON_44_STYLE;
#if defined(BMC_GLOBAL_BUTTON_45_PIN) && defined(BMC_GLOBAL_BUTTON_45_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 44 && defined(BMC_GLOBAL_BUTTON_45_X) && defined(BMC_GLOBAL_BUTTON_45_Y)
  case 44: return BMC_GLOBAL_BUTTON_45_STYLE;
#if defined(BMC_GLOBAL_BUTTON_46_PIN) && defined(BMC_GLOBAL_BUTTON_46_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 45 && defined(BMC_GLOBAL_BUTTON_46_X) && defined(BMC_GLOBAL_BUTTON_46_Y)
  case 45: return BMC_GLOBAL_BUTTON_46_STYLE;
#if defined(BMC_GLOBAL_BUTTON_47_PIN) && defined(BMC_GLOBAL_BUTTON_47_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 46 && defined(BMC_GLOBAL_BUTTON_47_X) && defined(BMC_GLOBAL_BUTTON_47_Y)
  case 46: return BMC_GLOBAL_BUTTON_47_STYLE;
#if defined(BMC_GLOBAL_BUTTON_48_PIN) && defined(BMC_GLOBAL_BUTTON_48_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 47 && defined(BMC_GLOBAL_BUTTON_48_X) && defined(BMC_GLOBAL_BUTTON_48_Y)
  case 47: return BMC_GLOBAL_BUTTON_48_STYLE;
#if defined(BMC_GLOBAL_BUTTON_49_PIN) && defined(BMC_GLOBAL_BUTTON_49_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 48 && defined(BMC_GLOBAL_BUTTON_49_X) && defined(BMC_GLOBAL_BUTTON_49_Y)
  case 48: return BMC_GLOBAL_BUTTON_49_STYLE;
#if defined(BMC_GLOBAL_BUTTON_50_PIN) && defined(BMC_GLOBAL_BUTTON_50_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 49 && defined(BMC_GLOBAL_BUTTON_50_X) && defined(BMC_GLOBAL_BUTTON_50_Y)
  case 49: return BMC_GLOBAL_BUTTON_50_STYLE;
#if defined(BMC_GLOBAL_BUTTON_51_PIN) && defined(BMC_GLOBAL_BUTTON_51_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 50 && defined(BMC_GLOBAL_BUTTON_51_X) && defined(BMC_GLOBAL_BUTTON_51_Y)
  case 50: return BMC_GLOBAL_BUTTON_51_STYLE;
#if defined(BMC_GLOBAL_BUTTON_52_PIN) && defined(BMC_GLOBAL_BUTTON_52_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 51 && defined(BMC_GLOBAL_BUTTON_52_X) && defined(BMC_GLOBAL_BUTTON_52_Y)
  case 51: return BMC_GLOBAL_BUTTON_52_STYLE;
#if defined(BMC_GLOBAL_BUTTON_53_PIN) && defined(BMC_GLOBAL_BUTTON_53_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 52 && defined(BMC_GLOBAL_BUTTON_53_X) && defined(BMC_GLOBAL_BUTTON_53_Y)
  case 52: return BMC_GLOBAL_BUTTON_53_STYLE;
#if defined(BMC_GLOBAL_BUTTON_54_PIN) && defined(BMC_GLOBAL_BUTTON_54_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 53 && defined(BMC_GLOBAL_BUTTON_54_X) && defined(BMC_GLOBAL_BUTTON_54_Y)
  case 53: return BMC_GLOBAL_BUTTON_54_STYLE;
#if defined(BMC_GLOBAL_BUTTON_55_PIN) && defined(BMC_GLOBAL_BUTTON_55_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 54 && defined(BMC_GLOBAL_BUTTON_55_X) && defined(BMC_GLOBAL_BUTTON_55_Y)
  case 54: return BMC_GLOBAL_BUTTON_55_STYLE;
#if defined(BMC_GLOBAL_BUTTON_56_PIN) && defined(BMC_GLOBAL_BUTTON_56_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 55 && defined(BMC_GLOBAL_BUTTON_56_X) && defined(BMC_GLOBAL_BUTTON_56_Y)
  case 55: return BMC_GLOBAL_BUTTON_56_STYLE;
#if defined(BMC_GLOBAL_BUTTON_57_PIN) && defined(BMC_GLOBAL_BUTTON_57_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 56 && defined(BMC_GLOBAL_BUTTON_57_X) && defined(BMC_GLOBAL_BUTTON_57_Y)
  case 56: return BMC_GLOBAL_BUTTON_57_STYLE;
#if defined(BMC_GLOBAL_BUTTON_58_PIN) && defined(BMC_GLOBAL_BUTTON_58_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 57 && defined(BMC_GLOBAL_BUTTON_58_X) && defined(BMC_GLOBAL_BUTTON_58_Y)
  case 57: return BMC_GLOBAL_BUTTON_58_STYLE;
#if defined(BMC_GLOBAL_BUTTON_59_PIN) && defined(BMC_GLOBAL_BUTTON_59_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 58 && defined(BMC_GLOBAL_BUTTON_59_X) && defined(BMC_GLOBAL_BUTTON_59_Y)
  case 58: return BMC_GLOBAL_BUTTON_59_STYLE;
#if defined(BMC_GLOBAL_BUTTON_60_PIN) && defined(BMC_GLOBAL_BUTTON_60_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 59 && defined(BMC_GLOBAL_BUTTON_60_X) && defined(BMC_GLOBAL_BUTTON_60_Y)
  case 59: return BMC_GLOBAL_BUTTON_60_STYLE;
#if defined(BMC_GLOBAL_BUTTON_61_PIN) && defined(BMC_GLOBAL_BUTTON_61_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 60 && defined(BMC_GLOBAL_BUTTON_61_X) && defined(BMC_GLOBAL_BUTTON_61_Y)
  case 60: return BMC_GLOBAL_BUTTON_61_STYLE;
#if defined(BMC_GLOBAL_BUTTON_62_PIN) && defined(BMC_GLOBAL_BUTTON_62_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 61 && defined(BMC_GLOBAL_BUTTON_62_X) && defined(BMC_GLOBAL_BUTTON_62_Y)
  case 61: return BMC_GLOBAL_BUTTON_62_STYLE;
#if defined(BMC_GLOBAL_BUTTON_63_PIN) && defined(BMC_GLOBAL_BUTTON_63_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 62 && defined(BMC_GLOBAL_BUTTON_63_X) && defined(BMC_GLOBAL_BUTTON_63_Y)
  case 62: return BMC_GLOBAL_BUTTON_63_STYLE;
#if defined(BMC_GLOBAL_BUTTON_64_PIN) && defined(BMC_GLOBAL_BUTTON_64_STYLE) && BMC_MAX_GLOBAL_BUTTONS > 63 && defined(BMC_GLOBAL_BUTTON_64_X) && defined(BMC_GLOBAL_BUTTON_64_Y)
  case 63: return BMC_GLOBAL_BUTTON_64_STYLE;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint8_t getGlobalPotStyle(uint8_t index=0){
#if BMC_MAX_GLOBAL_POTS > 0
switch(index){
#if defined(BMC_GLOBAL_POT_1_PIN) && defined(BMC_GLOBAL_POT_1_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=1 && BMC_MAX_GLOBAL_POTS > 0 && defined(BMC_GLOBAL_POT_1_X) && defined(BMC_GLOBAL_POT_1_Y)
  case 0: return BMC_GLOBAL_POT_1_STYLE;
#if defined(BMC_GLOBAL_POT_2_PIN) && defined(BMC_GLOBAL_POT_2_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=2 && BMC_MAX_GLOBAL_POTS > 1 && defined(BMC_GLOBAL_POT_2_X) && defined(BMC_GLOBAL_POT_2_Y)
  case 1: return BMC_GLOBAL_POT_2_STYLE;
#if defined(BMC_GLOBAL_POT_3_PIN) && defined(BMC_GLOBAL_POT_3_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=3 && BMC_MAX_GLOBAL_POTS > 2 && defined(BMC_GLOBAL_POT_3_X) && defined(BMC_GLOBAL_POT_3_Y)
  case 2: return BMC_GLOBAL_POT_3_STYLE;
#if defined(BMC_GLOBAL_POT_4_PIN) && defined(BMC_GLOBAL_POT_4_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=4 && BMC_MAX_GLOBAL_POTS > 3 && defined(BMC_GLOBAL_POT_4_X) && defined(BMC_GLOBAL_POT_4_Y)
  case 3: return BMC_GLOBAL_POT_4_STYLE;
#if defined(BMC_GLOBAL_POT_5_PIN) && defined(BMC_GLOBAL_POT_5_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=5 && BMC_MAX_GLOBAL_POTS > 4 && defined(BMC_GLOBAL_POT_5_X) && defined(BMC_GLOBAL_POT_5_Y)
  case 4: return BMC_GLOBAL_POT_5_STYLE;
#if defined(BMC_GLOBAL_POT_6_PIN) && defined(BMC_GLOBAL_POT_6_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=6 && BMC_MAX_GLOBAL_POTS > 5 && defined(BMC_GLOBAL_POT_6_X) && defined(BMC_GLOBAL_POT_6_Y)
  case 5: return BMC_GLOBAL_POT_6_STYLE;
#if defined(BMC_GLOBAL_POT_7_PIN) && defined(BMC_GLOBAL_POT_7_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=7 && BMC_MAX_GLOBAL_POTS > 6 && defined(BMC_GLOBAL_POT_7_X) && defined(BMC_GLOBAL_POT_7_Y)
  case 6: return BMC_GLOBAL_POT_7_STYLE;
#if defined(BMC_GLOBAL_POT_8_PIN) && defined(BMC_GLOBAL_POT_8_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=8 && BMC_MAX_GLOBAL_POTS > 7 && defined(BMC_GLOBAL_POT_8_X) && defined(BMC_GLOBAL_POT_8_Y)
  case 7: return BMC_GLOBAL_POT_8_STYLE;
#if defined(BMC_GLOBAL_POT_9_PIN) && defined(BMC_GLOBAL_POT_9_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=9 && BMC_MAX_GLOBAL_POTS > 8 && defined(BMC_GLOBAL_POT_9_X) && defined(BMC_GLOBAL_POT_9_Y)
  case 8: return BMC_GLOBAL_POT_9_STYLE;
#if defined(BMC_GLOBAL_POT_10_PIN) && defined(BMC_GLOBAL_POT_10_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=10 && BMC_MAX_GLOBAL_POTS > 9 && defined(BMC_GLOBAL_POT_10_X) && defined(BMC_GLOBAL_POT_10_Y)
  case 9: return BMC_GLOBAL_POT_10_STYLE;
#if defined(BMC_GLOBAL_POT_11_PIN) && defined(BMC_GLOBAL_POT_11_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=11 && BMC_MAX_GLOBAL_POTS > 10 && defined(BMC_GLOBAL_POT_11_X) && defined(BMC_GLOBAL_POT_11_Y)
  case 10: return BMC_GLOBAL_POT_11_STYLE;
#if defined(BMC_GLOBAL_POT_12_PIN) && defined(BMC_GLOBAL_POT_12_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=12 && BMC_MAX_GLOBAL_POTS > 11 && defined(BMC_GLOBAL_POT_12_X) && defined(BMC_GLOBAL_POT_12_Y)
  case 11: return BMC_GLOBAL_POT_12_STYLE;
#if defined(BMC_GLOBAL_POT_13_PIN) && defined(BMC_GLOBAL_POT_13_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=13 && BMC_MAX_GLOBAL_POTS > 12 && defined(BMC_GLOBAL_POT_13_X) && defined(BMC_GLOBAL_POT_13_Y)
  case 12: return BMC_GLOBAL_POT_13_STYLE;
#if defined(BMC_GLOBAL_POT_14_PIN) && defined(BMC_GLOBAL_POT_14_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=14 && BMC_MAX_GLOBAL_POTS > 13 && defined(BMC_GLOBAL_POT_14_X) && defined(BMC_GLOBAL_POT_14_Y)
  case 13: return BMC_GLOBAL_POT_14_STYLE;
#if defined(BMC_GLOBAL_POT_15_PIN) && defined(BMC_GLOBAL_POT_15_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=15 && BMC_MAX_GLOBAL_POTS > 14 && defined(BMC_GLOBAL_POT_15_X) && defined(BMC_GLOBAL_POT_15_Y)
  case 14: return BMC_GLOBAL_POT_15_STYLE;
#if defined(BMC_GLOBAL_POT_16_PIN) && defined(BMC_GLOBAL_POT_16_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=16 && BMC_MAX_GLOBAL_POTS > 15 && defined(BMC_GLOBAL_POT_16_X) && defined(BMC_GLOBAL_POT_16_Y)
  case 15: return BMC_GLOBAL_POT_16_STYLE;
#if defined(BMC_GLOBAL_POT_17_PIN) && defined(BMC_GLOBAL_POT_17_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=17 && BMC_MAX_GLOBAL_POTS > 16 && defined(BMC_GLOBAL_POT_17_X) && defined(BMC_GLOBAL_POT_17_Y)
  case 16: return BMC_GLOBAL_POT_17_STYLE;
#if defined(BMC_GLOBAL_POT_18_PIN) && defined(BMC_GLOBAL_POT_18_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=18 && BMC_MAX_GLOBAL_POTS > 17 && defined(BMC_GLOBAL_POT_18_X) && defined(BMC_GLOBAL_POT_18_Y)
  case 17: return BMC_GLOBAL_POT_18_STYLE;
#if defined(BMC_GLOBAL_POT_19_PIN) && defined(BMC_GLOBAL_POT_19_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=19 && BMC_MAX_GLOBAL_POTS > 18 && defined(BMC_GLOBAL_POT_19_X) && defined(BMC_GLOBAL_POT_19_Y)
  case 18: return BMC_GLOBAL_POT_19_STYLE;
#if defined(BMC_GLOBAL_POT_20_PIN) && defined(BMC_GLOBAL_POT_20_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=20 && BMC_MAX_GLOBAL_POTS > 19 && defined(BMC_GLOBAL_POT_20_X) && defined(BMC_GLOBAL_POT_20_Y)
  case 19: return BMC_GLOBAL_POT_20_STYLE;
#if defined(BMC_GLOBAL_POT_21_PIN) && defined(BMC_GLOBAL_POT_21_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=21 && BMC_MAX_GLOBAL_POTS > 20 && defined(BMC_GLOBAL_POT_21_X) && defined(BMC_GLOBAL_POT_21_Y)
  case 20: return BMC_GLOBAL_POT_21_STYLE;
#if defined(BMC_GLOBAL_POT_22_PIN) && defined(BMC_GLOBAL_POT_22_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=22 && BMC_MAX_GLOBAL_POTS > 21 && defined(BMC_GLOBAL_POT_22_X) && defined(BMC_GLOBAL_POT_22_Y)
  case 21: return BMC_GLOBAL_POT_22_STYLE;
#if defined(BMC_GLOBAL_POT_23_PIN) && defined(BMC_GLOBAL_POT_23_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=23 && BMC_MAX_GLOBAL_POTS > 22 && defined(BMC_GLOBAL_POT_23_X) && defined(BMC_GLOBAL_POT_23_Y)
  case 22: return BMC_GLOBAL_POT_23_STYLE;
#if defined(BMC_GLOBAL_POT_24_PIN) && defined(BMC_GLOBAL_POT_24_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=24 && BMC_MAX_GLOBAL_POTS > 23 && defined(BMC_GLOBAL_POT_24_X) && defined(BMC_GLOBAL_POT_24_Y)
  case 23: return BMC_GLOBAL_POT_24_STYLE;
#if defined(BMC_GLOBAL_POT_25_PIN) && defined(BMC_GLOBAL_POT_25_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=25 && BMC_MAX_GLOBAL_POTS > 24 && defined(BMC_GLOBAL_POT_25_X) && defined(BMC_GLOBAL_POT_25_Y)
  case 24: return BMC_GLOBAL_POT_25_STYLE;
#if defined(BMC_GLOBAL_POT_26_PIN) && defined(BMC_GLOBAL_POT_26_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=26 && BMC_MAX_GLOBAL_POTS > 25 && defined(BMC_GLOBAL_POT_26_X) && defined(BMC_GLOBAL_POT_26_Y)
  case 25: return BMC_GLOBAL_POT_26_STYLE;
#if defined(BMC_GLOBAL_POT_27_PIN) && defined(BMC_GLOBAL_POT_27_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=27 && BMC_MAX_GLOBAL_POTS > 26 && defined(BMC_GLOBAL_POT_27_X) && defined(BMC_GLOBAL_POT_27_Y)
  case 26: return BMC_GLOBAL_POT_27_STYLE;
#if defined(BMC_GLOBAL_POT_28_PIN) && defined(BMC_GLOBAL_POT_28_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=28 && BMC_MAX_GLOBAL_POTS > 27 && defined(BMC_GLOBAL_POT_28_X) && defined(BMC_GLOBAL_POT_28_Y)
  case 27: return BMC_GLOBAL_POT_28_STYLE;
#if defined(BMC_GLOBAL_POT_29_PIN) && defined(BMC_GLOBAL_POT_29_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=29 && BMC_MAX_GLOBAL_POTS > 28 && defined(BMC_GLOBAL_POT_29_X) && defined(BMC_GLOBAL_POT_29_Y)
  case 28: return BMC_GLOBAL_POT_29_STYLE;
#if defined(BMC_GLOBAL_POT_30_PIN) && defined(BMC_GLOBAL_POT_30_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=30 && BMC_MAX_GLOBAL_POTS > 29 && defined(BMC_GLOBAL_POT_30_X) && defined(BMC_GLOBAL_POT_30_Y)
  case 29: return BMC_GLOBAL_POT_30_STYLE;
#if defined(BMC_GLOBAL_POT_31_PIN) && defined(BMC_GLOBAL_POT_31_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=31 && BMC_MAX_GLOBAL_POTS > 30 && defined(BMC_GLOBAL_POT_31_X) && defined(BMC_GLOBAL_POT_31_Y)
  case 30: return BMC_GLOBAL_POT_31_STYLE;
#if defined(BMC_GLOBAL_POT_32_PIN) && defined(BMC_GLOBAL_POT_32_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=32 && BMC_MAX_GLOBAL_POTS > 31 && defined(BMC_GLOBAL_POT_32_X) && defined(BMC_GLOBAL_POT_32_Y)
  case 31: return BMC_GLOBAL_POT_32_STYLE;
#if defined(BMC_GLOBAL_POT_33_PIN) && defined(BMC_GLOBAL_POT_33_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=33 && BMC_MAX_GLOBAL_POTS > 32 && defined(BMC_GLOBAL_POT_33_X) && defined(BMC_GLOBAL_POT_33_Y)
  case 32: return BMC_GLOBAL_POT_33_STYLE;
#if defined(BMC_GLOBAL_POT_34_PIN) && defined(BMC_GLOBAL_POT_34_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=34 && BMC_MAX_GLOBAL_POTS > 33 && defined(BMC_GLOBAL_POT_34_X) && defined(BMC_GLOBAL_POT_34_Y)
  case 33: return BMC_GLOBAL_POT_34_STYLE;
#if defined(BMC_GLOBAL_POT_35_PIN) && defined(BMC_GLOBAL_POT_35_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=35 && BMC_MAX_GLOBAL_POTS > 34 && defined(BMC_GLOBAL_POT_35_X) && defined(BMC_GLOBAL_POT_35_Y)
  case 34: return BMC_GLOBAL_POT_35_STYLE;
#if defined(BMC_GLOBAL_POT_36_PIN) && defined(BMC_GLOBAL_POT_36_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=36 && BMC_MAX_GLOBAL_POTS > 35 && defined(BMC_GLOBAL_POT_36_X) && defined(BMC_GLOBAL_POT_36_Y)
  case 35: return BMC_GLOBAL_POT_36_STYLE;
#if defined(BMC_GLOBAL_POT_37_PIN) && defined(BMC_GLOBAL_POT_37_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=37 && BMC_MAX_GLOBAL_POTS > 36 && defined(BMC_GLOBAL_POT_37_X) && defined(BMC_GLOBAL_POT_37_Y)
  case 36: return BMC_GLOBAL_POT_37_STYLE;
#if defined(BMC_GLOBAL_POT_38_PIN) && defined(BMC_GLOBAL_POT_38_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=38 && BMC_MAX_GLOBAL_POTS > 37 && defined(BMC_GLOBAL_POT_38_X) && defined(BMC_GLOBAL_POT_38_Y)
  case 37: return BMC_GLOBAL_POT_38_STYLE;
#if defined(BMC_GLOBAL_POT_39_PIN) && defined(BMC_GLOBAL_POT_39_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=39 && BMC_MAX_GLOBAL_POTS > 38 && defined(BMC_GLOBAL_POT_39_X) && defined(BMC_GLOBAL_POT_39_Y)
  case 38: return BMC_GLOBAL_POT_39_STYLE;
#if defined(BMC_GLOBAL_POT_40_PIN) && defined(BMC_GLOBAL_POT_40_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=40 && BMC_MAX_GLOBAL_POTS > 39 && defined(BMC_GLOBAL_POT_40_X) && defined(BMC_GLOBAL_POT_40_Y)
  case 39: return BMC_GLOBAL_POT_40_STYLE;
#if defined(BMC_GLOBAL_POT_41_PIN) && defined(BMC_GLOBAL_POT_41_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=41 && BMC_MAX_GLOBAL_POTS > 40 && defined(BMC_GLOBAL_POT_41_X) && defined(BMC_GLOBAL_POT_41_Y)
  case 40: return BMC_GLOBAL_POT_41_STYLE;
#if defined(BMC_GLOBAL_POT_42_PIN) && defined(BMC_GLOBAL_POT_42_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=42 && BMC_MAX_GLOBAL_POTS > 41 && defined(BMC_GLOBAL_POT_42_X) && defined(BMC_GLOBAL_POT_42_Y)
  case 41: return BMC_GLOBAL_POT_42_STYLE;
#if defined(BMC_GLOBAL_POT_43_PIN) && defined(BMC_GLOBAL_POT_43_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=43 && BMC_MAX_GLOBAL_POTS > 42 && defined(BMC_GLOBAL_POT_43_X) && defined(BMC_GLOBAL_POT_43_Y)
  case 42: return BMC_GLOBAL_POT_43_STYLE;
#if defined(BMC_GLOBAL_POT_44_PIN) && defined(BMC_GLOBAL_POT_44_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=44 && BMC_MAX_GLOBAL_POTS > 43 && defined(BMC_GLOBAL_POT_44_X) && defined(BMC_GLOBAL_POT_44_Y)
  case 43: return BMC_GLOBAL_POT_44_STYLE;
#if defined(BMC_GLOBAL_POT_45_PIN) && defined(BMC_GLOBAL_POT_45_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=45 && BMC_MAX_GLOBAL_POTS > 44 && defined(BMC_GLOBAL_POT_45_X) && defined(BMC_GLOBAL_POT_45_Y)
  case 44: return BMC_GLOBAL_POT_45_STYLE;
#if defined(BMC_GLOBAL_POT_46_PIN) && defined(BMC_GLOBAL_POT_46_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=46 && BMC_MAX_GLOBAL_POTS > 45 && defined(BMC_GLOBAL_POT_46_X) && defined(BMC_GLOBAL_POT_46_Y)
  case 45: return BMC_GLOBAL_POT_46_STYLE;
#if defined(BMC_GLOBAL_POT_47_PIN) && defined(BMC_GLOBAL_POT_47_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=47 && BMC_MAX_GLOBAL_POTS > 46 && defined(BMC_GLOBAL_POT_47_X) && defined(BMC_GLOBAL_POT_47_Y)
  case 46: return BMC_GLOBAL_POT_47_STYLE;
#if defined(BMC_GLOBAL_POT_48_PIN) && defined(BMC_GLOBAL_POT_48_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=48 && BMC_MAX_GLOBAL_POTS > 47 && defined(BMC_GLOBAL_POT_48_X) && defined(BMC_GLOBAL_POT_48_Y)
  case 47: return BMC_GLOBAL_POT_48_STYLE;
#if defined(BMC_GLOBAL_POT_49_PIN) && defined(BMC_GLOBAL_POT_49_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=49 && BMC_MAX_GLOBAL_POTS > 48 && defined(BMC_GLOBAL_POT_49_X) && defined(BMC_GLOBAL_POT_49_Y)
  case 48: return BMC_GLOBAL_POT_49_STYLE;
#if defined(BMC_GLOBAL_POT_50_PIN) && defined(BMC_GLOBAL_POT_50_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=50 && BMC_MAX_GLOBAL_POTS > 49 && defined(BMC_GLOBAL_POT_50_X) && defined(BMC_GLOBAL_POT_50_Y)
  case 49: return BMC_GLOBAL_POT_50_STYLE;
#if defined(BMC_GLOBAL_POT_51_PIN) && defined(BMC_GLOBAL_POT_51_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=51 && BMC_MAX_GLOBAL_POTS > 50 && defined(BMC_GLOBAL_POT_51_X) && defined(BMC_GLOBAL_POT_51_Y)
  case 50: return BMC_GLOBAL_POT_51_STYLE;
#if defined(BMC_GLOBAL_POT_52_PIN) && defined(BMC_GLOBAL_POT_52_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=52 && BMC_MAX_GLOBAL_POTS > 51 && defined(BMC_GLOBAL_POT_52_X) && defined(BMC_GLOBAL_POT_52_Y)
  case 51: return BMC_GLOBAL_POT_52_STYLE;
#if defined(BMC_GLOBAL_POT_53_PIN) && defined(BMC_GLOBAL_POT_53_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=53 && BMC_MAX_GLOBAL_POTS > 52 && defined(BMC_GLOBAL_POT_53_X) && defined(BMC_GLOBAL_POT_53_Y)
  case 52: return BMC_GLOBAL_POT_53_STYLE;
#if defined(BMC_GLOBAL_POT_54_PIN) && defined(BMC_GLOBAL_POT_54_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=54 && BMC_MAX_GLOBAL_POTS > 53 && defined(BMC_GLOBAL_POT_54_X) && defined(BMC_GLOBAL_POT_54_Y)
  case 53: return BMC_GLOBAL_POT_54_STYLE;
#if defined(BMC_GLOBAL_POT_55_PIN) && defined(BMC_GLOBAL_POT_55_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=55 && BMC_MAX_GLOBAL_POTS > 54 && defined(BMC_GLOBAL_POT_55_X) && defined(BMC_GLOBAL_POT_55_Y)
  case 54: return BMC_GLOBAL_POT_55_STYLE;
#if defined(BMC_GLOBAL_POT_56_PIN) && defined(BMC_GLOBAL_POT_56_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=56 && BMC_MAX_GLOBAL_POTS > 55 && defined(BMC_GLOBAL_POT_56_X) && defined(BMC_GLOBAL_POT_56_Y)
  case 55: return BMC_GLOBAL_POT_56_STYLE;
#if defined(BMC_GLOBAL_POT_57_PIN) && defined(BMC_GLOBAL_POT_57_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=57 && BMC_MAX_GLOBAL_POTS > 56 && defined(BMC_GLOBAL_POT_57_X) && defined(BMC_GLOBAL_POT_57_Y)
  case 56: return BMC_GLOBAL_POT_57_STYLE;
#if defined(BMC_GLOBAL_POT_58_PIN) && defined(BMC_GLOBAL_POT_58_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=58 && BMC_MAX_GLOBAL_POTS > 57 && defined(BMC_GLOBAL_POT_58_X) && defined(BMC_GLOBAL_POT_58_Y)
  case 57: return BMC_GLOBAL_POT_58_STYLE;
#if defined(BMC_GLOBAL_POT_59_PIN) && defined(BMC_GLOBAL_POT_59_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=59 && BMC_MAX_GLOBAL_POTS > 58 && defined(BMC_GLOBAL_POT_59_X) && defined(BMC_GLOBAL_POT_59_Y)
  case 58: return BMC_GLOBAL_POT_59_STYLE;
#if defined(BMC_GLOBAL_POT_60_PIN) && defined(BMC_GLOBAL_POT_60_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=60 && BMC_MAX_GLOBAL_POTS > 59 && defined(BMC_GLOBAL_POT_60_X) && defined(BMC_GLOBAL_POT_60_Y)
  case 59: return BMC_GLOBAL_POT_60_STYLE;
#if defined(BMC_GLOBAL_POT_61_PIN) && defined(BMC_GLOBAL_POT_61_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=61 && BMC_MAX_GLOBAL_POTS > 60 && defined(BMC_GLOBAL_POT_61_X) && defined(BMC_GLOBAL_POT_61_Y)
  case 60: return BMC_GLOBAL_POT_61_STYLE;
#if defined(BMC_GLOBAL_POT_62_PIN) && defined(BMC_GLOBAL_POT_62_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=62 && BMC_MAX_GLOBAL_POTS > 61 && defined(BMC_GLOBAL_POT_62_X) && defined(BMC_GLOBAL_POT_62_Y)
  case 61: return BMC_GLOBAL_POT_62_STYLE;
#if defined(BMC_GLOBAL_POT_63_PIN) && defined(BMC_GLOBAL_POT_63_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=63 && BMC_MAX_GLOBAL_POTS > 62 && defined(BMC_GLOBAL_POT_63_X) && defined(BMC_GLOBAL_POT_63_Y)
  case 62: return BMC_GLOBAL_POT_63_STYLE;
#if defined(BMC_GLOBAL_POT_64_PIN) && defined(BMC_GLOBAL_POT_64_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=64 && BMC_MAX_GLOBAL_POTS > 63 && defined(BMC_GLOBAL_POT_64_X) && defined(BMC_GLOBAL_POT_64_Y)
  case 63: return BMC_GLOBAL_POT_64_STYLE;
#if defined(BMC_GLOBAL_POT_65_PIN) && defined(BMC_GLOBAL_POT_65_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=65 && BMC_MAX_GLOBAL_POTS > 64 && defined(BMC_GLOBAL_POT_65_X) && defined(BMC_GLOBAL_POT_65_Y)
  case 64: return BMC_GLOBAL_POT_65_STYLE;
#if defined(BMC_GLOBAL_POT_66_PIN) && defined(BMC_GLOBAL_POT_66_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=66 && BMC_MAX_GLOBAL_POTS > 65 && defined(BMC_GLOBAL_POT_66_X) && defined(BMC_GLOBAL_POT_66_Y)
  case 65: return BMC_GLOBAL_POT_66_STYLE;
#if defined(BMC_GLOBAL_POT_67_PIN) && defined(BMC_GLOBAL_POT_67_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=67 && BMC_MAX_GLOBAL_POTS > 66 && defined(BMC_GLOBAL_POT_67_X) && defined(BMC_GLOBAL_POT_67_Y)
  case 66: return BMC_GLOBAL_POT_67_STYLE;
#if defined(BMC_GLOBAL_POT_68_PIN) && defined(BMC_GLOBAL_POT_68_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=68 && BMC_MAX_GLOBAL_POTS > 67 && defined(BMC_GLOBAL_POT_68_X) && defined(BMC_GLOBAL_POT_68_Y)
  case 67: return BMC_GLOBAL_POT_68_STYLE;
#if defined(BMC_GLOBAL_POT_69_PIN) && defined(BMC_GLOBAL_POT_69_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=69 && BMC_MAX_GLOBAL_POTS > 68 && defined(BMC_GLOBAL_POT_69_X) && defined(BMC_GLOBAL_POT_69_Y)
  case 68: return BMC_GLOBAL_POT_69_STYLE;
#if defined(BMC_GLOBAL_POT_70_PIN) && defined(BMC_GLOBAL_POT_70_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=70 && BMC_MAX_GLOBAL_POTS > 69 && defined(BMC_GLOBAL_POT_70_X) && defined(BMC_GLOBAL_POT_70_Y)
  case 69: return BMC_GLOBAL_POT_70_STYLE;
#if defined(BMC_GLOBAL_POT_71_PIN) && defined(BMC_GLOBAL_POT_71_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=71 && BMC_MAX_GLOBAL_POTS > 70 && defined(BMC_GLOBAL_POT_71_X) && defined(BMC_GLOBAL_POT_71_Y)
  case 70: return BMC_GLOBAL_POT_71_STYLE;
#if defined(BMC_GLOBAL_POT_72_PIN) && defined(BMC_GLOBAL_POT_72_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=72 && BMC_MAX_GLOBAL_POTS > 71 && defined(BMC_GLOBAL_POT_72_X) && defined(BMC_GLOBAL_POT_72_Y)
  case 71: return BMC_GLOBAL_POT_72_STYLE;
#if defined(BMC_GLOBAL_POT_73_PIN) && defined(BMC_GLOBAL_POT_73_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=73 && BMC_MAX_GLOBAL_POTS > 72 && defined(BMC_GLOBAL_POT_73_X) && defined(BMC_GLOBAL_POT_73_Y)
  case 72: return BMC_GLOBAL_POT_73_STYLE;
#if defined(BMC_GLOBAL_POT_74_PIN) && defined(BMC_GLOBAL_POT_74_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=74 && BMC_MAX_GLOBAL_POTS > 73 && defined(BMC_GLOBAL_POT_74_X) && defined(BMC_GLOBAL_POT_74_Y)
  case 73: return BMC_GLOBAL_POT_74_STYLE;
#if defined(BMC_GLOBAL_POT_75_PIN) && defined(BMC_GLOBAL_POT_75_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=75 && BMC_MAX_GLOBAL_POTS > 74 && defined(BMC_GLOBAL_POT_75_X) && defined(BMC_GLOBAL_POT_75_Y)
  case 74: return BMC_GLOBAL_POT_75_STYLE;
#if defined(BMC_GLOBAL_POT_76_PIN) && defined(BMC_GLOBAL_POT_76_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=76 && BMC_MAX_GLOBAL_POTS > 75 && defined(BMC_GLOBAL_POT_76_X) && defined(BMC_GLOBAL_POT_76_Y)
  case 75: return BMC_GLOBAL_POT_76_STYLE;
#if defined(BMC_GLOBAL_POT_77_PIN) && defined(BMC_GLOBAL_POT_77_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=77 && BMC_MAX_GLOBAL_POTS > 76 && defined(BMC_GLOBAL_POT_77_X) && defined(BMC_GLOBAL_POT_77_Y)
  case 76: return BMC_GLOBAL_POT_77_STYLE;
#if defined(BMC_GLOBAL_POT_78_PIN) && defined(BMC_GLOBAL_POT_78_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=78 && BMC_MAX_GLOBAL_POTS > 77 && defined(BMC_GLOBAL_POT_78_X) && defined(BMC_GLOBAL_POT_78_Y)
  case 77: return BMC_GLOBAL_POT_78_STYLE;
#if defined(BMC_GLOBAL_POT_79_PIN) && defined(BMC_GLOBAL_POT_79_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=79 && BMC_MAX_GLOBAL_POTS > 78 && defined(BMC_GLOBAL_POT_79_X) && defined(BMC_GLOBAL_POT_79_Y)
  case 78: return BMC_GLOBAL_POT_79_STYLE;
#if defined(BMC_GLOBAL_POT_80_PIN) && defined(BMC_GLOBAL_POT_80_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=80 && BMC_MAX_GLOBAL_POTS > 79 && defined(BMC_GLOBAL_POT_80_X) && defined(BMC_GLOBAL_POT_80_Y)
  case 79: return BMC_GLOBAL_POT_80_STYLE;
#if defined(BMC_GLOBAL_POT_81_PIN) && defined(BMC_GLOBAL_POT_81_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=81 && BMC_MAX_GLOBAL_POTS > 80 && defined(BMC_GLOBAL_POT_81_X) && defined(BMC_GLOBAL_POT_81_Y)
  case 80: return BMC_GLOBAL_POT_81_STYLE;
#if defined(BMC_GLOBAL_POT_82_PIN) && defined(BMC_GLOBAL_POT_82_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=82 && BMC_MAX_GLOBAL_POTS > 81 && defined(BMC_GLOBAL_POT_82_X) && defined(BMC_GLOBAL_POT_82_Y)
  case 81: return BMC_GLOBAL_POT_82_STYLE;
#if defined(BMC_GLOBAL_POT_83_PIN) && defined(BMC_GLOBAL_POT_83_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=83 && BMC_MAX_GLOBAL_POTS > 82 && defined(BMC_GLOBAL_POT_83_X) && defined(BMC_GLOBAL_POT_83_Y)
  case 82: return BMC_GLOBAL_POT_83_STYLE;
#if defined(BMC_GLOBAL_POT_84_PIN) && defined(BMC_GLOBAL_POT_84_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=84 && BMC_MAX_GLOBAL_POTS > 83 && defined(BMC_GLOBAL_POT_84_X) && defined(BMC_GLOBAL_POT_84_Y)
  case 83: return BMC_GLOBAL_POT_84_STYLE;
#if defined(BMC_GLOBAL_POT_85_PIN) && defined(BMC_GLOBAL_POT_85_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=85 && BMC_MAX_GLOBAL_POTS > 84 && defined(BMC_GLOBAL_POT_85_X) && defined(BMC_GLOBAL_POT_85_Y)
  case 84: return BMC_GLOBAL_POT_85_STYLE;
#if defined(BMC_GLOBAL_POT_86_PIN) && defined(BMC_GLOBAL_POT_86_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=86 && BMC_MAX_GLOBAL_POTS > 85 && defined(BMC_GLOBAL_POT_86_X) && defined(BMC_GLOBAL_POT_86_Y)
  case 85: return BMC_GLOBAL_POT_86_STYLE;
#if defined(BMC_GLOBAL_POT_87_PIN) && defined(BMC_GLOBAL_POT_87_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=87 && BMC_MAX_GLOBAL_POTS > 86 && defined(BMC_GLOBAL_POT_87_X) && defined(BMC_GLOBAL_POT_87_Y)
  case 86: return BMC_GLOBAL_POT_87_STYLE;
#if defined(BMC_GLOBAL_POT_88_PIN) && defined(BMC_GLOBAL_POT_88_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=88 && BMC_MAX_GLOBAL_POTS > 87 && defined(BMC_GLOBAL_POT_88_X) && defined(BMC_GLOBAL_POT_88_Y)
  case 87: return BMC_GLOBAL_POT_88_STYLE;
#if defined(BMC_GLOBAL_POT_89_PIN) && defined(BMC_GLOBAL_POT_89_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=89 && BMC_MAX_GLOBAL_POTS > 88 && defined(BMC_GLOBAL_POT_89_X) && defined(BMC_GLOBAL_POT_89_Y)
  case 88: return BMC_GLOBAL_POT_89_STYLE;
#if defined(BMC_GLOBAL_POT_90_PIN) && defined(BMC_GLOBAL_POT_90_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=90 && BMC_MAX_GLOBAL_POTS > 89 && defined(BMC_GLOBAL_POT_90_X) && defined(BMC_GLOBAL_POT_90_Y)
  case 89: return BMC_GLOBAL_POT_90_STYLE;
#if defined(BMC_GLOBAL_POT_91_PIN) && defined(BMC_GLOBAL_POT_91_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=91 && BMC_MAX_GLOBAL_POTS > 90 && defined(BMC_GLOBAL_POT_91_X) && defined(BMC_GLOBAL_POT_91_Y)
  case 90: return BMC_GLOBAL_POT_91_STYLE;
#if defined(BMC_GLOBAL_POT_92_PIN) && defined(BMC_GLOBAL_POT_92_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=92 && BMC_MAX_GLOBAL_POTS > 91 && defined(BMC_GLOBAL_POT_92_X) && defined(BMC_GLOBAL_POT_92_Y)
  case 91: return BMC_GLOBAL_POT_92_STYLE;
#if defined(BMC_GLOBAL_POT_93_PIN) && defined(BMC_GLOBAL_POT_93_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=93 && BMC_MAX_GLOBAL_POTS > 92 && defined(BMC_GLOBAL_POT_93_X) && defined(BMC_GLOBAL_POT_93_Y)
  case 92: return BMC_GLOBAL_POT_93_STYLE;
#if defined(BMC_GLOBAL_POT_94_PIN) && defined(BMC_GLOBAL_POT_94_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=94 && BMC_MAX_GLOBAL_POTS > 93 && defined(BMC_GLOBAL_POT_94_X) && defined(BMC_GLOBAL_POT_94_Y)
  case 93: return BMC_GLOBAL_POT_94_STYLE;
#if defined(BMC_GLOBAL_POT_95_PIN) && defined(BMC_GLOBAL_POT_95_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=95 && BMC_MAX_GLOBAL_POTS > 94 && defined(BMC_GLOBAL_POT_95_X) && defined(BMC_GLOBAL_POT_95_Y)
  case 94: return BMC_GLOBAL_POT_95_STYLE;
#if defined(BMC_GLOBAL_POT_96_PIN) && defined(BMC_GLOBAL_POT_96_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=96 && BMC_MAX_GLOBAL_POTS > 95 && defined(BMC_GLOBAL_POT_96_X) && defined(BMC_GLOBAL_POT_96_Y)
  case 95: return BMC_GLOBAL_POT_96_STYLE;
#if defined(BMC_GLOBAL_POT_97_PIN) && defined(BMC_GLOBAL_POT_97_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=97 && BMC_MAX_GLOBAL_POTS > 96 && defined(BMC_GLOBAL_POT_97_X) && defined(BMC_GLOBAL_POT_97_Y)
  case 96: return BMC_GLOBAL_POT_97_STYLE;
#if defined(BMC_GLOBAL_POT_98_PIN) && defined(BMC_GLOBAL_POT_98_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=98 && BMC_MAX_GLOBAL_POTS > 97 && defined(BMC_GLOBAL_POT_98_X) && defined(BMC_GLOBAL_POT_98_Y)
  case 97: return BMC_GLOBAL_POT_98_STYLE;
#if defined(BMC_GLOBAL_POT_99_PIN) && defined(BMC_GLOBAL_POT_99_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=99 && BMC_MAX_GLOBAL_POTS > 98 && defined(BMC_GLOBAL_POT_99_X) && defined(BMC_GLOBAL_POT_99_Y)
  case 98: return BMC_GLOBAL_POT_99_STYLE;
#if defined(BMC_GLOBAL_POT_100_PIN) && defined(BMC_GLOBAL_POT_100_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=100 && BMC_MAX_GLOBAL_POTS > 99 && defined(BMC_GLOBAL_POT_100_X) && defined(BMC_GLOBAL_POT_100_Y)
  case 99: return BMC_GLOBAL_POT_100_STYLE;
#if defined(BMC_GLOBAL_POT_101_PIN) && defined(BMC_GLOBAL_POT_101_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=101 && BMC_MAX_GLOBAL_POTS > 100 && defined(BMC_GLOBAL_POT_101_X) && defined(BMC_GLOBAL_POT_101_Y)
  case 100: return BMC_GLOBAL_POT_101_STYLE;
#if defined(BMC_GLOBAL_POT_102_PIN) && defined(BMC_GLOBAL_POT_102_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=102 && BMC_MAX_GLOBAL_POTS > 101 && defined(BMC_GLOBAL_POT_102_X) && defined(BMC_GLOBAL_POT_102_Y)
  case 101: return BMC_GLOBAL_POT_102_STYLE;
#if defined(BMC_GLOBAL_POT_103_PIN) && defined(BMC_GLOBAL_POT_103_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=103 && BMC_MAX_GLOBAL_POTS > 102 && defined(BMC_GLOBAL_POT_103_X) && defined(BMC_GLOBAL_POT_103_Y)
  case 102: return BMC_GLOBAL_POT_103_STYLE;
#if defined(BMC_GLOBAL_POT_104_PIN) && defined(BMC_GLOBAL_POT_104_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=104 && BMC_MAX_GLOBAL_POTS > 103 && defined(BMC_GLOBAL_POT_104_X) && defined(BMC_GLOBAL_POT_104_Y)
  case 103: return BMC_GLOBAL_POT_104_STYLE;
#if defined(BMC_GLOBAL_POT_105_PIN) && defined(BMC_GLOBAL_POT_105_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=105 && BMC_MAX_GLOBAL_POTS > 104 && defined(BMC_GLOBAL_POT_105_X) && defined(BMC_GLOBAL_POT_105_Y)
  case 104: return BMC_GLOBAL_POT_105_STYLE;
#if defined(BMC_GLOBAL_POT_106_PIN) && defined(BMC_GLOBAL_POT_106_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=106 && BMC_MAX_GLOBAL_POTS > 105 && defined(BMC_GLOBAL_POT_106_X) && defined(BMC_GLOBAL_POT_106_Y)
  case 105: return BMC_GLOBAL_POT_106_STYLE;
#if defined(BMC_GLOBAL_POT_107_PIN) && defined(BMC_GLOBAL_POT_107_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=107 && BMC_MAX_GLOBAL_POTS > 106 && defined(BMC_GLOBAL_POT_107_X) && defined(BMC_GLOBAL_POT_107_Y)
  case 106: return BMC_GLOBAL_POT_107_STYLE;
#if defined(BMC_GLOBAL_POT_108_PIN) && defined(BMC_GLOBAL_POT_108_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=108 && BMC_MAX_GLOBAL_POTS > 107 && defined(BMC_GLOBAL_POT_108_X) && defined(BMC_GLOBAL_POT_108_Y)
  case 107: return BMC_GLOBAL_POT_108_STYLE;
#if defined(BMC_GLOBAL_POT_109_PIN) && defined(BMC_GLOBAL_POT_109_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=109 && BMC_MAX_GLOBAL_POTS > 108 && defined(BMC_GLOBAL_POT_109_X) && defined(BMC_GLOBAL_POT_109_Y)
  case 108: return BMC_GLOBAL_POT_109_STYLE;
#if defined(BMC_GLOBAL_POT_110_PIN) && defined(BMC_GLOBAL_POT_110_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=110 && BMC_MAX_GLOBAL_POTS > 109 && defined(BMC_GLOBAL_POT_110_X) && defined(BMC_GLOBAL_POT_110_Y)
  case 109: return BMC_GLOBAL_POT_110_STYLE;
#if defined(BMC_GLOBAL_POT_111_PIN) && defined(BMC_GLOBAL_POT_111_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=111 && BMC_MAX_GLOBAL_POTS > 110 && defined(BMC_GLOBAL_POT_111_X) && defined(BMC_GLOBAL_POT_111_Y)
  case 110: return BMC_GLOBAL_POT_111_STYLE;
#if defined(BMC_GLOBAL_POT_112_PIN) && defined(BMC_GLOBAL_POT_112_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=112 && BMC_MAX_GLOBAL_POTS > 111 && defined(BMC_GLOBAL_POT_112_X) && defined(BMC_GLOBAL_POT_112_Y)
  case 111: return BMC_GLOBAL_POT_112_STYLE;
#if defined(BMC_GLOBAL_POT_113_PIN) && defined(BMC_GLOBAL_POT_113_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=113 && BMC_MAX_GLOBAL_POTS > 112 && defined(BMC_GLOBAL_POT_113_X) && defined(BMC_GLOBAL_POT_113_Y)
  case 112: return BMC_GLOBAL_POT_113_STYLE;
#if defined(BMC_GLOBAL_POT_114_PIN) && defined(BMC_GLOBAL_POT_114_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=114 && BMC_MAX_GLOBAL_POTS > 113 && defined(BMC_GLOBAL_POT_114_X) && defined(BMC_GLOBAL_POT_114_Y)
  case 113: return BMC_GLOBAL_POT_114_STYLE;
#if defined(BMC_GLOBAL_POT_115_PIN) && defined(BMC_GLOBAL_POT_115_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=115 && BMC_MAX_GLOBAL_POTS > 114 && defined(BMC_GLOBAL_POT_115_X) && defined(BMC_GLOBAL_POT_115_Y)
  case 114: return BMC_GLOBAL_POT_115_STYLE;
#if defined(BMC_GLOBAL_POT_116_PIN) && defined(BMC_GLOBAL_POT_116_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=116 && BMC_MAX_GLOBAL_POTS > 115 && defined(BMC_GLOBAL_POT_116_X) && defined(BMC_GLOBAL_POT_116_Y)
  case 115: return BMC_GLOBAL_POT_116_STYLE;
#if defined(BMC_GLOBAL_POT_117_PIN) && defined(BMC_GLOBAL_POT_117_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=117 && BMC_MAX_GLOBAL_POTS > 116 && defined(BMC_GLOBAL_POT_117_X) && defined(BMC_GLOBAL_POT_117_Y)
  case 116: return BMC_GLOBAL_POT_117_STYLE;
#if defined(BMC_GLOBAL_POT_118_PIN) && defined(BMC_GLOBAL_POT_118_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=118 && BMC_MAX_GLOBAL_POTS > 117 && defined(BMC_GLOBAL_POT_118_X) && defined(BMC_GLOBAL_POT_118_Y)
  case 117: return BMC_GLOBAL_POT_118_STYLE;
#if defined(BMC_GLOBAL_POT_119_PIN) && defined(BMC_GLOBAL_POT_119_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=119 && BMC_MAX_GLOBAL_POTS > 118 && defined(BMC_GLOBAL_POT_119_X) && defined(BMC_GLOBAL_POT_119_Y)
  case 118: return BMC_GLOBAL_POT_119_STYLE;
#if defined(BMC_GLOBAL_POT_120_PIN) && defined(BMC_GLOBAL_POT_120_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=120 && BMC_MAX_GLOBAL_POTS > 119 && defined(BMC_GLOBAL_POT_120_X) && defined(BMC_GLOBAL_POT_120_Y)
  case 119: return BMC_GLOBAL_POT_120_STYLE;
#if defined(BMC_GLOBAL_POT_121_PIN) && defined(BMC_GLOBAL_POT_121_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=121 && BMC_MAX_GLOBAL_POTS > 120 && defined(BMC_GLOBAL_POT_121_X) && defined(BMC_GLOBAL_POT_121_Y)
  case 120: return BMC_GLOBAL_POT_121_STYLE;
#if defined(BMC_GLOBAL_POT_122_PIN) && defined(BMC_GLOBAL_POT_122_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=122 && BMC_MAX_GLOBAL_POTS > 121 && defined(BMC_GLOBAL_POT_122_X) && defined(BMC_GLOBAL_POT_122_Y)
  case 121: return BMC_GLOBAL_POT_122_STYLE;
#if defined(BMC_GLOBAL_POT_123_PIN) && defined(BMC_GLOBAL_POT_123_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=123 && BMC_MAX_GLOBAL_POTS > 122 && defined(BMC_GLOBAL_POT_123_X) && defined(BMC_GLOBAL_POT_123_Y)
  case 122: return BMC_GLOBAL_POT_123_STYLE;
#if defined(BMC_GLOBAL_POT_124_PIN) && defined(BMC_GLOBAL_POT_124_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=124 && BMC_MAX_GLOBAL_POTS > 123 && defined(BMC_GLOBAL_POT_124_X) && defined(BMC_GLOBAL_POT_124_Y)
  case 123: return BMC_GLOBAL_POT_124_STYLE;
#if defined(BMC_GLOBAL_POT_125_PIN) && defined(BMC_GLOBAL_POT_125_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=125 && BMC_MAX_GLOBAL_POTS > 124 && defined(BMC_GLOBAL_POT_125_X) && defined(BMC_GLOBAL_POT_125_Y)
  case 124: return BMC_GLOBAL_POT_125_STYLE;
#if defined(BMC_GLOBAL_POT_126_PIN) && defined(BMC_GLOBAL_POT_126_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=126 && BMC_MAX_GLOBAL_POTS > 125 && defined(BMC_GLOBAL_POT_126_X) && defined(BMC_GLOBAL_POT_126_Y)
  case 125: return BMC_GLOBAL_POT_126_STYLE;
#if defined(BMC_GLOBAL_POT_127_PIN) && defined(BMC_GLOBAL_POT_127_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=127 && BMC_MAX_GLOBAL_POTS > 126 && defined(BMC_GLOBAL_POT_127_X) && defined(BMC_GLOBAL_POT_127_Y)
  case 126: return BMC_GLOBAL_POT_127_STYLE;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint8_t getRelayNLPin(uint8_t index=0){
#if BMC_MAX_NL_RELAYS > 0
switch(index){
#if defined(BMC_NL_RELAY_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_NL_RELAYS > 0 && defined(BMC_NL_RELAY_1_X) && defined(BMC_NL_RELAY_1_Y)
  case 0: return BMC_NL_RELAY_1_PIN;
#if defined(BMC_NL_RELAY_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_NL_RELAYS > 1 && defined(BMC_NL_RELAY_2_X) && defined(BMC_NL_RELAY_2_Y)
  case 1: return BMC_NL_RELAY_2_PIN;
#if defined(BMC_NL_RELAY_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_NL_RELAYS > 2 && defined(BMC_NL_RELAY_3_X) && defined(BMC_NL_RELAY_3_Y)
  case 2: return BMC_NL_RELAY_3_PIN;
#if defined(BMC_NL_RELAY_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_NL_RELAYS > 3 && defined(BMC_NL_RELAY_4_X) && defined(BMC_NL_RELAY_4_Y)
  case 3: return BMC_NL_RELAY_4_PIN;
#if defined(BMC_NL_RELAY_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_NL_RELAYS > 4 && defined(BMC_NL_RELAY_5_X) && defined(BMC_NL_RELAY_5_Y)
  case 4: return BMC_NL_RELAY_5_PIN;
#if defined(BMC_NL_RELAY_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_NL_RELAYS > 5 && defined(BMC_NL_RELAY_6_X) && defined(BMC_NL_RELAY_6_Y)
  case 5: return BMC_NL_RELAY_6_PIN;
#if defined(BMC_NL_RELAY_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_NL_RELAYS > 6 && defined(BMC_NL_RELAY_7_X) && defined(BMC_NL_RELAY_7_Y)
  case 6: return BMC_NL_RELAY_7_PIN;
#if defined(BMC_NL_RELAY_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_NL_RELAYS > 7 && defined(BMC_NL_RELAY_8_X) && defined(BMC_NL_RELAY_8_Y)
  case 7: return BMC_NL_RELAY_8_PIN;
#if defined(BMC_NL_RELAY_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_NL_RELAYS > 8 && defined(BMC_NL_RELAY_9_X) && defined(BMC_NL_RELAY_9_Y)
  case 8: return BMC_NL_RELAY_9_PIN;
#if defined(BMC_NL_RELAY_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_NL_RELAYS > 9 && defined(BMC_NL_RELAY_10_X) && defined(BMC_NL_RELAY_10_Y)
  case 9: return BMC_NL_RELAY_10_PIN;
#if defined(BMC_NL_RELAY_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_NL_RELAYS > 10 && defined(BMC_NL_RELAY_11_X) && defined(BMC_NL_RELAY_11_Y)
  case 10: return BMC_NL_RELAY_11_PIN;
#if defined(BMC_NL_RELAY_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_NL_RELAYS > 11 && defined(BMC_NL_RELAY_12_X) && defined(BMC_NL_RELAY_12_Y)
  case 11: return BMC_NL_RELAY_12_PIN;
#if defined(BMC_NL_RELAY_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_NL_RELAYS > 12 && defined(BMC_NL_RELAY_13_X) && defined(BMC_NL_RELAY_13_Y)
  case 12: return BMC_NL_RELAY_13_PIN;
#if defined(BMC_NL_RELAY_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_NL_RELAYS > 13 && defined(BMC_NL_RELAY_14_X) && defined(BMC_NL_RELAY_14_Y)
  case 13: return BMC_NL_RELAY_14_PIN;
#if defined(BMC_NL_RELAY_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_NL_RELAYS > 14 && defined(BMC_NL_RELAY_15_X) && defined(BMC_NL_RELAY_15_Y)
  case 14: return BMC_NL_RELAY_15_PIN;
#if defined(BMC_NL_RELAY_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_NL_RELAYS > 15 && defined(BMC_NL_RELAY_16_X) && defined(BMC_NL_RELAY_16_Y)
  case 15: return BMC_NL_RELAY_16_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getRelayLPinA(uint8_t index=0){
#if BMC_MAX_L_RELAYS > 0
switch(index){
#if defined(BMC_L_RELAY_1A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_L_RELAY_1B_PIN) && BMC_MAX_L_RELAYS > 0 && defined(BMC_L_RELAY_1_X) && defined(BMC_L_RELAY_1_Y)
  case 0: return BMC_L_RELAY_1A_PIN;
#if defined(BMC_L_RELAY_2A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_L_RELAY_2B_PIN) && BMC_MAX_L_RELAYS > 1 && defined(BMC_L_RELAY_2_X) && defined(BMC_L_RELAY_2_Y)
  case 1: return BMC_L_RELAY_2A_PIN;
#if defined(BMC_L_RELAY_3A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_L_RELAY_3B_PIN) && BMC_MAX_L_RELAYS > 2 && defined(BMC_L_RELAY_3_X) && defined(BMC_L_RELAY_3_Y)
  case 2: return BMC_L_RELAY_3A_PIN;
#if defined(BMC_L_RELAY_4A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_L_RELAY_4B_PIN) && BMC_MAX_L_RELAYS > 3 && defined(BMC_L_RELAY_4_X) && defined(BMC_L_RELAY_4_Y)
  case 3: return BMC_L_RELAY_4A_PIN;
#if defined(BMC_L_RELAY_5A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_L_RELAY_5B_PIN) && BMC_MAX_L_RELAYS > 4 && defined(BMC_L_RELAY_5_X) && defined(BMC_L_RELAY_5_Y)
  case 4: return BMC_L_RELAY_5A_PIN;
#if defined(BMC_L_RELAY_6A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_L_RELAY_6B_PIN) && BMC_MAX_L_RELAYS > 5 && defined(BMC_L_RELAY_6_X) && defined(BMC_L_RELAY_6_Y)
  case 5: return BMC_L_RELAY_6A_PIN;
#if defined(BMC_L_RELAY_7A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_L_RELAY_7B_PIN) && BMC_MAX_L_RELAYS > 6 && defined(BMC_L_RELAY_7_X) && defined(BMC_L_RELAY_7_Y)
  case 6: return BMC_L_RELAY_7A_PIN;
#if defined(BMC_L_RELAY_8A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_L_RELAY_8B_PIN) && BMC_MAX_L_RELAYS > 7 && defined(BMC_L_RELAY_8_X) && defined(BMC_L_RELAY_8_Y)
  case 7: return BMC_L_RELAY_8A_PIN;
#if defined(BMC_L_RELAY_9A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && defined(BMC_L_RELAY_9B_PIN) && BMC_MAX_L_RELAYS > 8 && defined(BMC_L_RELAY_9_X) && defined(BMC_L_RELAY_9_Y)
  case 8: return BMC_L_RELAY_9A_PIN;
#if defined(BMC_L_RELAY_10A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && defined(BMC_L_RELAY_10B_PIN) && BMC_MAX_L_RELAYS > 9 && defined(BMC_L_RELAY_10_X) && defined(BMC_L_RELAY_10_Y)
  case 9: return BMC_L_RELAY_10A_PIN;
#if defined(BMC_L_RELAY_11A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && defined(BMC_L_RELAY_11B_PIN) && BMC_MAX_L_RELAYS > 10 && defined(BMC_L_RELAY_11_X) && defined(BMC_L_RELAY_11_Y)
  case 10: return BMC_L_RELAY_11A_PIN;
#if defined(BMC_L_RELAY_12A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && defined(BMC_L_RELAY_12B_PIN) && BMC_MAX_L_RELAYS > 11 && defined(BMC_L_RELAY_12_X) && defined(BMC_L_RELAY_12_Y)
  case 11: return BMC_L_RELAY_12A_PIN;
#if defined(BMC_L_RELAY_13A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && defined(BMC_L_RELAY_13B_PIN) && BMC_MAX_L_RELAYS > 12 && defined(BMC_L_RELAY_13_X) && defined(BMC_L_RELAY_13_Y)
  case 12: return BMC_L_RELAY_13A_PIN;
#if defined(BMC_L_RELAY_14A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && defined(BMC_L_RELAY_14B_PIN) && BMC_MAX_L_RELAYS > 13 && defined(BMC_L_RELAY_14_X) && defined(BMC_L_RELAY_14_Y)
  case 13: return BMC_L_RELAY_14A_PIN;
#if defined(BMC_L_RELAY_15A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && defined(BMC_L_RELAY_15B_PIN) && BMC_MAX_L_RELAYS > 14 && defined(BMC_L_RELAY_15_X) && defined(BMC_L_RELAY_15_Y)
  case 14: return BMC_L_RELAY_15A_PIN;
#if defined(BMC_L_RELAY_16A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && defined(BMC_L_RELAY_16B_PIN) && BMC_MAX_L_RELAYS > 15 && defined(BMC_L_RELAY_16_X) && defined(BMC_L_RELAY_16_Y)
  case 15: return BMC_L_RELAY_16A_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getRelayLPinB(uint8_t index=0){
#if BMC_MAX_L_RELAYS > 0
switch(index){
#if defined(BMC_L_RELAY_1A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_L_RELAY_1B_PIN) && BMC_MAX_L_RELAYS > 0 && defined(BMC_L_RELAY_1_X) && defined(BMC_L_RELAY_1_Y)
  case 0: return BMC_L_RELAY_1B_PIN;
#if defined(BMC_L_RELAY_2A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_L_RELAY_2B_PIN) && BMC_MAX_L_RELAYS > 1 && defined(BMC_L_RELAY_2_X) && defined(BMC_L_RELAY_2_Y)
  case 1: return BMC_L_RELAY_2B_PIN;
#if defined(BMC_L_RELAY_3A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_L_RELAY_3B_PIN) && BMC_MAX_L_RELAYS > 2 && defined(BMC_L_RELAY_3_X) && defined(BMC_L_RELAY_3_Y)
  case 2: return BMC_L_RELAY_3B_PIN;
#if defined(BMC_L_RELAY_4A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_L_RELAY_4B_PIN) && BMC_MAX_L_RELAYS > 3 && defined(BMC_L_RELAY_4_X) && defined(BMC_L_RELAY_4_Y)
  case 3: return BMC_L_RELAY_4B_PIN;
#if defined(BMC_L_RELAY_5A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_L_RELAY_5B_PIN) && BMC_MAX_L_RELAYS > 4 && defined(BMC_L_RELAY_5_X) && defined(BMC_L_RELAY_5_Y)
  case 4: return BMC_L_RELAY_5B_PIN;
#if defined(BMC_L_RELAY_6A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_L_RELAY_6B_PIN) && BMC_MAX_L_RELAYS > 5 && defined(BMC_L_RELAY_6_X) && defined(BMC_L_RELAY_6_Y)
  case 5: return BMC_L_RELAY_6B_PIN;
#if defined(BMC_L_RELAY_7A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_L_RELAY_7B_PIN) && BMC_MAX_L_RELAYS > 6 && defined(BMC_L_RELAY_7_X) && defined(BMC_L_RELAY_7_Y)
  case 6: return BMC_L_RELAY_7B_PIN;
#if defined(BMC_L_RELAY_8A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_L_RELAY_8B_PIN) && BMC_MAX_L_RELAYS > 7 && defined(BMC_L_RELAY_8_X) && defined(BMC_L_RELAY_8_Y)
  case 7: return BMC_L_RELAY_8B_PIN;
#if defined(BMC_L_RELAY_9A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && defined(BMC_L_RELAY_9B_PIN) && BMC_MAX_L_RELAYS > 8 && defined(BMC_L_RELAY_9_X) && defined(BMC_L_RELAY_9_Y)
  case 8: return BMC_L_RELAY_9B_PIN;
#if defined(BMC_L_RELAY_10A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && defined(BMC_L_RELAY_10B_PIN) && BMC_MAX_L_RELAYS > 9 && defined(BMC_L_RELAY_10_X) && defined(BMC_L_RELAY_10_Y)
  case 9: return BMC_L_RELAY_10B_PIN;
#if defined(BMC_L_RELAY_11A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && defined(BMC_L_RELAY_11B_PIN) && BMC_MAX_L_RELAYS > 10 && defined(BMC_L_RELAY_11_X) && defined(BMC_L_RELAY_11_Y)
  case 10: return BMC_L_RELAY_11B_PIN;
#if defined(BMC_L_RELAY_12A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && defined(BMC_L_RELAY_12B_PIN) && BMC_MAX_L_RELAYS > 11 && defined(BMC_L_RELAY_12_X) && defined(BMC_L_RELAY_12_Y)
  case 11: return BMC_L_RELAY_12B_PIN;
#if defined(BMC_L_RELAY_13A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && defined(BMC_L_RELAY_13B_PIN) && BMC_MAX_L_RELAYS > 12 && defined(BMC_L_RELAY_13_X) && defined(BMC_L_RELAY_13_Y)
  case 12: return BMC_L_RELAY_13B_PIN;
#if defined(BMC_L_RELAY_14A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && defined(BMC_L_RELAY_14B_PIN) && BMC_MAX_L_RELAYS > 13 && defined(BMC_L_RELAY_14_X) && defined(BMC_L_RELAY_14_Y)
  case 13: return BMC_L_RELAY_14B_PIN;
#if defined(BMC_L_RELAY_15A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && defined(BMC_L_RELAY_15B_PIN) && BMC_MAX_L_RELAYS > 14 && defined(BMC_L_RELAY_15_X) && defined(BMC_L_RELAY_15_Y)
  case 14: return BMC_L_RELAY_15B_PIN;
#if defined(BMC_L_RELAY_16A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && defined(BMC_L_RELAY_16B_PIN) && BMC_MAX_L_RELAYS > 15 && defined(BMC_L_RELAY_16_X) && defined(BMC_L_RELAY_16_Y)
  case 15: return BMC_L_RELAY_16B_PIN;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 255;
}
static uint8_t getLedColor(uint8_t index=0){
#if BMC_MAX_LEDS > 0
switch(index){
#if defined(BMC_LED_1_PIN) && defined(BMC_LED_1_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_LEDS > 0 && defined(BMC_LED_1_X) && defined(BMC_LED_1_Y)
  case 0: return BMC_LED_1_COLOR;
#if defined(BMC_LED_2_PIN) && defined(BMC_LED_2_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_LEDS > 1 && defined(BMC_LED_2_X) && defined(BMC_LED_2_Y)
  case 1: return BMC_LED_2_COLOR;
#if defined(BMC_LED_3_PIN) && defined(BMC_LED_3_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_LEDS > 2 && defined(BMC_LED_3_X) && defined(BMC_LED_3_Y)
  case 2: return BMC_LED_3_COLOR;
#if defined(BMC_LED_4_PIN) && defined(BMC_LED_4_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_LEDS > 3 && defined(BMC_LED_4_X) && defined(BMC_LED_4_Y)
  case 3: return BMC_LED_4_COLOR;
#if defined(BMC_LED_5_PIN) && defined(BMC_LED_5_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_LEDS > 4 && defined(BMC_LED_5_X) && defined(BMC_LED_5_Y)
  case 4: return BMC_LED_5_COLOR;
#if defined(BMC_LED_6_PIN) && defined(BMC_LED_6_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_LEDS > 5 && defined(BMC_LED_6_X) && defined(BMC_LED_6_Y)
  case 5: return BMC_LED_6_COLOR;
#if defined(BMC_LED_7_PIN) && defined(BMC_LED_7_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_LEDS > 6 && defined(BMC_LED_7_X) && defined(BMC_LED_7_Y)
  case 6: return BMC_LED_7_COLOR;
#if defined(BMC_LED_8_PIN) && defined(BMC_LED_8_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_LEDS > 7 && defined(BMC_LED_8_X) && defined(BMC_LED_8_Y)
  case 7: return BMC_LED_8_COLOR;
#if defined(BMC_LED_9_PIN) && defined(BMC_LED_9_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_LEDS > 8 && defined(BMC_LED_9_X) && defined(BMC_LED_9_Y)
  case 8: return BMC_LED_9_COLOR;
#if defined(BMC_LED_10_PIN) && defined(BMC_LED_10_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_LEDS > 9 && defined(BMC_LED_10_X) && defined(BMC_LED_10_Y)
  case 9: return BMC_LED_10_COLOR;
#if defined(BMC_LED_11_PIN) && defined(BMC_LED_11_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_LEDS > 10 && defined(BMC_LED_11_X) && defined(BMC_LED_11_Y)
  case 10: return BMC_LED_11_COLOR;
#if defined(BMC_LED_12_PIN) && defined(BMC_LED_12_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_LEDS > 11 && defined(BMC_LED_12_X) && defined(BMC_LED_12_Y)
  case 11: return BMC_LED_12_COLOR;
#if defined(BMC_LED_13_PIN) && defined(BMC_LED_13_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_LEDS > 12 && defined(BMC_LED_13_X) && defined(BMC_LED_13_Y)
  case 12: return BMC_LED_13_COLOR;
#if defined(BMC_LED_14_PIN) && defined(BMC_LED_14_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_LEDS > 13 && defined(BMC_LED_14_X) && defined(BMC_LED_14_Y)
  case 13: return BMC_LED_14_COLOR;
#if defined(BMC_LED_15_PIN) && defined(BMC_LED_15_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_LEDS > 14 && defined(BMC_LED_15_X) && defined(BMC_LED_15_Y)
  case 14: return BMC_LED_15_COLOR;
#if defined(BMC_LED_16_PIN) && defined(BMC_LED_16_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_LEDS > 15 && defined(BMC_LED_16_X) && defined(BMC_LED_16_Y)
  case 15: return BMC_LED_16_COLOR;
#if defined(BMC_LED_17_PIN) && defined(BMC_LED_17_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && BMC_MAX_LEDS > 16 && defined(BMC_LED_17_X) && defined(BMC_LED_17_Y)
  case 16: return BMC_LED_17_COLOR;
#if defined(BMC_LED_18_PIN) && defined(BMC_LED_18_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && BMC_MAX_LEDS > 17 && defined(BMC_LED_18_X) && defined(BMC_LED_18_Y)
  case 17: return BMC_LED_18_COLOR;
#if defined(BMC_LED_19_PIN) && defined(BMC_LED_19_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && BMC_MAX_LEDS > 18 && defined(BMC_LED_19_X) && defined(BMC_LED_19_Y)
  case 18: return BMC_LED_19_COLOR;
#if defined(BMC_LED_20_PIN) && defined(BMC_LED_20_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && BMC_MAX_LEDS > 19 && defined(BMC_LED_20_X) && defined(BMC_LED_20_Y)
  case 19: return BMC_LED_20_COLOR;
#if defined(BMC_LED_21_PIN) && defined(BMC_LED_21_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && BMC_MAX_LEDS > 20 && defined(BMC_LED_21_X) && defined(BMC_LED_21_Y)
  case 20: return BMC_LED_21_COLOR;
#if defined(BMC_LED_22_PIN) && defined(BMC_LED_22_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && BMC_MAX_LEDS > 21 && defined(BMC_LED_22_X) && defined(BMC_LED_22_Y)
  case 21: return BMC_LED_22_COLOR;
#if defined(BMC_LED_23_PIN) && defined(BMC_LED_23_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && BMC_MAX_LEDS > 22 && defined(BMC_LED_23_X) && defined(BMC_LED_23_Y)
  case 22: return BMC_LED_23_COLOR;
#if defined(BMC_LED_24_PIN) && defined(BMC_LED_24_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && BMC_MAX_LEDS > 23 && defined(BMC_LED_24_X) && defined(BMC_LED_24_Y)
  case 23: return BMC_LED_24_COLOR;
#if defined(BMC_LED_25_PIN) && defined(BMC_LED_25_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && BMC_MAX_LEDS > 24 && defined(BMC_LED_25_X) && defined(BMC_LED_25_Y)
  case 24: return BMC_LED_25_COLOR;
#if defined(BMC_LED_26_PIN) && defined(BMC_LED_26_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && BMC_MAX_LEDS > 25 && defined(BMC_LED_26_X) && defined(BMC_LED_26_Y)
  case 25: return BMC_LED_26_COLOR;
#if defined(BMC_LED_27_PIN) && defined(BMC_LED_27_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && BMC_MAX_LEDS > 26 && defined(BMC_LED_27_X) && defined(BMC_LED_27_Y)
  case 26: return BMC_LED_27_COLOR;
#if defined(BMC_LED_28_PIN) && defined(BMC_LED_28_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && BMC_MAX_LEDS > 27 && defined(BMC_LED_28_X) && defined(BMC_LED_28_Y)
  case 27: return BMC_LED_28_COLOR;
#if defined(BMC_LED_29_PIN) && defined(BMC_LED_29_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && BMC_MAX_LEDS > 28 && defined(BMC_LED_29_X) && defined(BMC_LED_29_Y)
  case 28: return BMC_LED_29_COLOR;
#if defined(BMC_LED_30_PIN) && defined(BMC_LED_30_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && BMC_MAX_LEDS > 29 && defined(BMC_LED_30_X) && defined(BMC_LED_30_Y)
  case 29: return BMC_LED_30_COLOR;
#if defined(BMC_LED_31_PIN) && defined(BMC_LED_31_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && BMC_MAX_LEDS > 30 && defined(BMC_LED_31_X) && defined(BMC_LED_31_Y)
  case 30: return BMC_LED_31_COLOR;
#if defined(BMC_LED_32_PIN) && defined(BMC_LED_32_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && BMC_MAX_LEDS > 31 && defined(BMC_LED_32_X) && defined(BMC_LED_32_Y)
  case 31: return BMC_LED_32_COLOR;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return BMC_COLOR_RED;
}
static uint8_t getGlobalLedColor(uint8_t index=0){
#if BMC_MAX_GLOBAL_LEDS > 0
switch(index){
#if defined(BMC_GLOBAL_LED_1_PIN) && defined(BMC_GLOBAL_LED_1_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_GLOBAL_LEDS > 0 && defined(BMC_GLOBAL_LED_1_X) && defined(BMC_GLOBAL_LED_1_Y)
  case 0: return BMC_GLOBAL_LED_1_COLOR;
#if defined(BMC_GLOBAL_LED_2_PIN) && defined(BMC_GLOBAL_LED_2_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_GLOBAL_LEDS > 1 && defined(BMC_GLOBAL_LED_2_X) && defined(BMC_GLOBAL_LED_2_Y)
  case 1: return BMC_GLOBAL_LED_2_COLOR;
#if defined(BMC_GLOBAL_LED_3_PIN) && defined(BMC_GLOBAL_LED_3_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_GLOBAL_LEDS > 2 && defined(BMC_GLOBAL_LED_3_X) && defined(BMC_GLOBAL_LED_3_Y)
  case 2: return BMC_GLOBAL_LED_3_COLOR;
#if defined(BMC_GLOBAL_LED_4_PIN) && defined(BMC_GLOBAL_LED_4_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_GLOBAL_LEDS > 3 && defined(BMC_GLOBAL_LED_4_X) && defined(BMC_GLOBAL_LED_4_Y)
  case 3: return BMC_GLOBAL_LED_4_COLOR;
#if defined(BMC_GLOBAL_LED_5_PIN) && defined(BMC_GLOBAL_LED_5_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_GLOBAL_LEDS > 4 && defined(BMC_GLOBAL_LED_5_X) && defined(BMC_GLOBAL_LED_5_Y)
  case 4: return BMC_GLOBAL_LED_5_COLOR;
#if defined(BMC_GLOBAL_LED_6_PIN) && defined(BMC_GLOBAL_LED_6_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_GLOBAL_LEDS > 5 && defined(BMC_GLOBAL_LED_6_X) && defined(BMC_GLOBAL_LED_6_Y)
  case 5: return BMC_GLOBAL_LED_6_COLOR;
#if defined(BMC_GLOBAL_LED_7_PIN) && defined(BMC_GLOBAL_LED_7_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_GLOBAL_LEDS > 6 && defined(BMC_GLOBAL_LED_7_X) && defined(BMC_GLOBAL_LED_7_Y)
  case 6: return BMC_GLOBAL_LED_7_COLOR;
#if defined(BMC_GLOBAL_LED_8_PIN) && defined(BMC_GLOBAL_LED_8_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_GLOBAL_LEDS > 7 && defined(BMC_GLOBAL_LED_8_X) && defined(BMC_GLOBAL_LED_8_Y)
  case 7: return BMC_GLOBAL_LED_8_COLOR;
#if defined(BMC_GLOBAL_LED_9_PIN) && defined(BMC_GLOBAL_LED_9_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_GLOBAL_LEDS > 8 && defined(BMC_GLOBAL_LED_9_X) && defined(BMC_GLOBAL_LED_9_Y)
  case 8: return BMC_GLOBAL_LED_9_COLOR;
#if defined(BMC_GLOBAL_LED_10_PIN) && defined(BMC_GLOBAL_LED_10_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_GLOBAL_LEDS > 9 && defined(BMC_GLOBAL_LED_10_X) && defined(BMC_GLOBAL_LED_10_Y)
  case 9: return BMC_GLOBAL_LED_10_COLOR;
#if defined(BMC_GLOBAL_LED_11_PIN) && defined(BMC_GLOBAL_LED_11_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_GLOBAL_LEDS > 10 && defined(BMC_GLOBAL_LED_11_X) && defined(BMC_GLOBAL_LED_11_Y)
  case 10: return BMC_GLOBAL_LED_11_COLOR;
#if defined(BMC_GLOBAL_LED_12_PIN) && defined(BMC_GLOBAL_LED_12_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_GLOBAL_LEDS > 11 && defined(BMC_GLOBAL_LED_12_X) && defined(BMC_GLOBAL_LED_12_Y)
  case 11: return BMC_GLOBAL_LED_12_COLOR;
#if defined(BMC_GLOBAL_LED_13_PIN) && defined(BMC_GLOBAL_LED_13_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_GLOBAL_LEDS > 12 && defined(BMC_GLOBAL_LED_13_X) && defined(BMC_GLOBAL_LED_13_Y)
  case 12: return BMC_GLOBAL_LED_13_COLOR;
#if defined(BMC_GLOBAL_LED_14_PIN) && defined(BMC_GLOBAL_LED_14_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_GLOBAL_LEDS > 13 && defined(BMC_GLOBAL_LED_14_X) && defined(BMC_GLOBAL_LED_14_Y)
  case 13: return BMC_GLOBAL_LED_14_COLOR;
#if defined(BMC_GLOBAL_LED_15_PIN) && defined(BMC_GLOBAL_LED_15_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_GLOBAL_LEDS > 14 && defined(BMC_GLOBAL_LED_15_X) && defined(BMC_GLOBAL_LED_15_Y)
  case 14: return BMC_GLOBAL_LED_15_COLOR;
#if defined(BMC_GLOBAL_LED_16_PIN) && defined(BMC_GLOBAL_LED_16_COLOR) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_GLOBAL_LEDS > 15 && defined(BMC_GLOBAL_LED_16_X) && defined(BMC_GLOBAL_LED_16_Y)
  case 15: return BMC_GLOBAL_LED_16_COLOR;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return BMC_COLOR_RED;
}
static uint8_t getPwmLedColor(uint8_t index=0){
#if BMC_MAX_PWM_LEDS > 0
switch(index){
#if defined(BMC_PWM_LED_1_PIN) && defined(BMC_PWM_LED_1_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=1 && BMC_MAX_PWM_LEDS > 0 && defined(BMC_PWM_LED_1_X) && defined(BMC_PWM_LED_1_Y)
  case 0: return BMC_PWM_LED_1_COLOR;
#if defined(BMC_PWM_LED_2_PIN) && defined(BMC_PWM_LED_2_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=2 && BMC_MAX_PWM_LEDS > 1 && defined(BMC_PWM_LED_2_X) && defined(BMC_PWM_LED_2_Y)
  case 1: return BMC_PWM_LED_2_COLOR;
#if defined(BMC_PWM_LED_3_PIN) && defined(BMC_PWM_LED_3_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=3 && BMC_MAX_PWM_LEDS > 2 && defined(BMC_PWM_LED_3_X) && defined(BMC_PWM_LED_3_Y)
  case 2: return BMC_PWM_LED_3_COLOR;
#if defined(BMC_PWM_LED_4_PIN) && defined(BMC_PWM_LED_4_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=4 && BMC_MAX_PWM_LEDS > 3 && defined(BMC_PWM_LED_4_X) && defined(BMC_PWM_LED_4_Y)
  case 3: return BMC_PWM_LED_4_COLOR;
#if defined(BMC_PWM_LED_5_PIN) && defined(BMC_PWM_LED_5_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=5 && BMC_MAX_PWM_LEDS > 4 && defined(BMC_PWM_LED_5_X) && defined(BMC_PWM_LED_5_Y)
  case 4: return BMC_PWM_LED_5_COLOR;
#if defined(BMC_PWM_LED_6_PIN) && defined(BMC_PWM_LED_6_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=6 && BMC_MAX_PWM_LEDS > 5 && defined(BMC_PWM_LED_6_X) && defined(BMC_PWM_LED_6_Y)
  case 5: return BMC_PWM_LED_6_COLOR;
#if defined(BMC_PWM_LED_7_PIN) && defined(BMC_PWM_LED_7_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=7 && BMC_MAX_PWM_LEDS > 6 && defined(BMC_PWM_LED_7_X) && defined(BMC_PWM_LED_7_Y)
  case 6: return BMC_PWM_LED_7_COLOR;
#if defined(BMC_PWM_LED_8_PIN) && defined(BMC_PWM_LED_8_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=8 && BMC_MAX_PWM_LEDS > 7 && defined(BMC_PWM_LED_8_X) && defined(BMC_PWM_LED_8_Y)
  case 7: return BMC_PWM_LED_8_COLOR;
#if defined(BMC_PWM_LED_9_PIN) && defined(BMC_PWM_LED_9_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=9 && BMC_MAX_PWM_LEDS > 8 && defined(BMC_PWM_LED_9_X) && defined(BMC_PWM_LED_9_Y)
  case 8: return BMC_PWM_LED_9_COLOR;
#if defined(BMC_PWM_LED_10_PIN) && defined(BMC_PWM_LED_10_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=10 && BMC_MAX_PWM_LEDS > 9 && defined(BMC_PWM_LED_10_X) && defined(BMC_PWM_LED_10_Y)
  case 9: return BMC_PWM_LED_10_COLOR;
#if defined(BMC_PWM_LED_11_PIN) && defined(BMC_PWM_LED_11_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=11 && BMC_MAX_PWM_LEDS > 10 && defined(BMC_PWM_LED_11_X) && defined(BMC_PWM_LED_11_Y)
  case 10: return BMC_PWM_LED_11_COLOR;
#if defined(BMC_PWM_LED_12_PIN) && defined(BMC_PWM_LED_12_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=12 && BMC_MAX_PWM_LEDS > 11 && defined(BMC_PWM_LED_12_X) && defined(BMC_PWM_LED_12_Y)
  case 11: return BMC_PWM_LED_12_COLOR;
#if defined(BMC_PWM_LED_13_PIN) && defined(BMC_PWM_LED_13_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=13 && BMC_MAX_PWM_LEDS > 12 && defined(BMC_PWM_LED_13_X) && defined(BMC_PWM_LED_13_Y)
  case 12: return BMC_PWM_LED_13_COLOR;
#if defined(BMC_PWM_LED_14_PIN) && defined(BMC_PWM_LED_14_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=14 && BMC_MAX_PWM_LEDS > 13 && defined(BMC_PWM_LED_14_X) && defined(BMC_PWM_LED_14_Y)
  case 13: return BMC_PWM_LED_14_COLOR;
#if defined(BMC_PWM_LED_15_PIN) && defined(BMC_PWM_LED_15_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=15 && BMC_MAX_PWM_LEDS > 14 && defined(BMC_PWM_LED_15_X) && defined(BMC_PWM_LED_15_Y)
  case 14: return BMC_PWM_LED_15_COLOR;
#if defined(BMC_PWM_LED_16_PIN) && defined(BMC_PWM_LED_16_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=16 && BMC_MAX_PWM_LEDS > 15 && defined(BMC_PWM_LED_16_X) && defined(BMC_PWM_LED_16_Y)
  case 15: return BMC_PWM_LED_16_COLOR;
#if defined(BMC_PWM_LED_17_PIN) && defined(BMC_PWM_LED_17_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=17 && BMC_MAX_PWM_LEDS > 16 && defined(BMC_PWM_LED_17_X) && defined(BMC_PWM_LED_17_Y)
  case 16: return BMC_PWM_LED_17_COLOR;
#if defined(BMC_PWM_LED_18_PIN) && defined(BMC_PWM_LED_18_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=18 && BMC_MAX_PWM_LEDS > 17 && defined(BMC_PWM_LED_18_X) && defined(BMC_PWM_LED_18_Y)
  case 17: return BMC_PWM_LED_18_COLOR;
#if defined(BMC_PWM_LED_19_PIN) && defined(BMC_PWM_LED_19_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=19 && BMC_MAX_PWM_LEDS > 18 && defined(BMC_PWM_LED_19_X) && defined(BMC_PWM_LED_19_Y)
  case 18: return BMC_PWM_LED_19_COLOR;
#if defined(BMC_PWM_LED_20_PIN) && defined(BMC_PWM_LED_20_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=20 && BMC_MAX_PWM_LEDS > 19 && defined(BMC_PWM_LED_20_X) && defined(BMC_PWM_LED_20_Y)
  case 19: return BMC_PWM_LED_20_COLOR;
#if defined(BMC_PWM_LED_21_PIN) && defined(BMC_PWM_LED_21_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=21 && BMC_MAX_PWM_LEDS > 20 && defined(BMC_PWM_LED_21_X) && defined(BMC_PWM_LED_21_Y)
  case 20: return BMC_PWM_LED_21_COLOR;
#if defined(BMC_PWM_LED_22_PIN) && defined(BMC_PWM_LED_22_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=22 && BMC_MAX_PWM_LEDS > 21 && defined(BMC_PWM_LED_22_X) && defined(BMC_PWM_LED_22_Y)
  case 21: return BMC_PWM_LED_22_COLOR;
#if defined(BMC_PWM_LED_23_PIN) && defined(BMC_PWM_LED_23_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=23 && BMC_MAX_PWM_LEDS > 22 && defined(BMC_PWM_LED_23_X) && defined(BMC_PWM_LED_23_Y)
  case 22: return BMC_PWM_LED_23_COLOR;
#if defined(BMC_PWM_LED_24_PIN) && defined(BMC_PWM_LED_24_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=24 && BMC_MAX_PWM_LEDS > 23 && defined(BMC_PWM_LED_24_X) && defined(BMC_PWM_LED_24_Y)
  case 23: return BMC_PWM_LED_24_COLOR;
#if defined(BMC_PWM_LED_25_PIN) && defined(BMC_PWM_LED_25_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=25 && BMC_MAX_PWM_LEDS > 24 && defined(BMC_PWM_LED_25_X) && defined(BMC_PWM_LED_25_Y)
  case 24: return BMC_PWM_LED_25_COLOR;
#if defined(BMC_PWM_LED_26_PIN) && defined(BMC_PWM_LED_26_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=26 && BMC_MAX_PWM_LEDS > 25 && defined(BMC_PWM_LED_26_X) && defined(BMC_PWM_LED_26_Y)
  case 25: return BMC_PWM_LED_26_COLOR;
#if defined(BMC_PWM_LED_27_PIN) && defined(BMC_PWM_LED_27_COLOR) && BMC_TEENSY_TOTAL_PWM_PINS>=27 && BMC_MAX_PWM_LEDS > 26 && defined(BMC_PWM_LED_27_X) && defined(BMC_PWM_LED_27_Y)
  case 26: return BMC_PWM_LED_27_COLOR;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return BMC_COLOR_RED;
}
static uint8_t getPotStyle(uint8_t index=0){
#if BMC_MAX_POTS > 0
switch(index){
#if defined(BMC_POT_1_PIN) && defined(BMC_POT_1_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=1 && BMC_MAX_POTS > 0 && defined(BMC_POT_1_X) && defined(BMC_POT_1_Y)
  case 0: return BMC_POT_1_STYLE;
#if defined(BMC_POT_2_PIN) && defined(BMC_POT_2_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=2 && BMC_MAX_POTS > 1 && defined(BMC_POT_2_X) && defined(BMC_POT_2_Y)
  case 1: return BMC_POT_2_STYLE;
#if defined(BMC_POT_3_PIN) && defined(BMC_POT_3_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=3 && BMC_MAX_POTS > 2 && defined(BMC_POT_3_X) && defined(BMC_POT_3_Y)
  case 2: return BMC_POT_3_STYLE;
#if defined(BMC_POT_4_PIN) && defined(BMC_POT_4_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=4 && BMC_MAX_POTS > 3 && defined(BMC_POT_4_X) && defined(BMC_POT_4_Y)
  case 3: return BMC_POT_4_STYLE;
#if defined(BMC_POT_5_PIN) && defined(BMC_POT_5_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=5 && BMC_MAX_POTS > 4 && defined(BMC_POT_5_X) && defined(BMC_POT_5_Y)
  case 4: return BMC_POT_5_STYLE;
#if defined(BMC_POT_6_PIN) && defined(BMC_POT_6_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=6 && BMC_MAX_POTS > 5 && defined(BMC_POT_6_X) && defined(BMC_POT_6_Y)
  case 5: return BMC_POT_6_STYLE;
#if defined(BMC_POT_7_PIN) && defined(BMC_POT_7_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=7 && BMC_MAX_POTS > 6 && defined(BMC_POT_7_X) && defined(BMC_POT_7_Y)
  case 6: return BMC_POT_7_STYLE;
#if defined(BMC_POT_8_PIN) && defined(BMC_POT_8_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=8 && BMC_MAX_POTS > 7 && defined(BMC_POT_8_X) && defined(BMC_POT_8_Y)
  case 7: return BMC_POT_8_STYLE;
#if defined(BMC_POT_9_PIN) && defined(BMC_POT_9_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=9 && BMC_MAX_POTS > 8 && defined(BMC_POT_9_X) && defined(BMC_POT_9_Y)
  case 8: return BMC_POT_9_STYLE;
#if defined(BMC_POT_10_PIN) && defined(BMC_POT_10_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=10 && BMC_MAX_POTS > 9 && defined(BMC_POT_10_X) && defined(BMC_POT_10_Y)
  case 9: return BMC_POT_10_STYLE;
#if defined(BMC_POT_11_PIN) && defined(BMC_POT_11_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=11 && BMC_MAX_POTS > 10 && defined(BMC_POT_11_X) && defined(BMC_POT_11_Y)
  case 10: return BMC_POT_11_STYLE;
#if defined(BMC_POT_12_PIN) && defined(BMC_POT_12_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=12 && BMC_MAX_POTS > 11 && defined(BMC_POT_12_X) && defined(BMC_POT_12_Y)
  case 11: return BMC_POT_12_STYLE;
#if defined(BMC_POT_13_PIN) && defined(BMC_POT_13_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=13 && BMC_MAX_POTS > 12 && defined(BMC_POT_13_X) && defined(BMC_POT_13_Y)
  case 12: return BMC_POT_13_STYLE;
#if defined(BMC_POT_14_PIN) && defined(BMC_POT_14_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=14 && BMC_MAX_POTS > 13 && defined(BMC_POT_14_X) && defined(BMC_POT_14_Y)
  case 13: return BMC_POT_14_STYLE;
#if defined(BMC_POT_15_PIN) && defined(BMC_POT_15_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=15 && BMC_MAX_POTS > 14 && defined(BMC_POT_15_X) && defined(BMC_POT_15_Y)
  case 14: return BMC_POT_15_STYLE;
#if defined(BMC_POT_16_PIN) && defined(BMC_POT_16_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=16 && BMC_MAX_POTS > 15 && defined(BMC_POT_16_X) && defined(BMC_POT_16_Y)
  case 15: return BMC_POT_16_STYLE;
#if defined(BMC_POT_17_PIN) && defined(BMC_POT_17_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=17 && BMC_MAX_POTS > 16 && defined(BMC_POT_17_X) && defined(BMC_POT_17_Y)
  case 16: return BMC_POT_17_STYLE;
#if defined(BMC_POT_18_PIN) && defined(BMC_POT_18_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=18 && BMC_MAX_POTS > 17 && defined(BMC_POT_18_X) && defined(BMC_POT_18_Y)
  case 17: return BMC_POT_18_STYLE;
#if defined(BMC_POT_19_PIN) && defined(BMC_POT_19_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=19 && BMC_MAX_POTS > 18 && defined(BMC_POT_19_X) && defined(BMC_POT_19_Y)
  case 18: return BMC_POT_19_STYLE;
#if defined(BMC_POT_20_PIN) && defined(BMC_POT_20_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=20 && BMC_MAX_POTS > 19 && defined(BMC_POT_20_X) && defined(BMC_POT_20_Y)
  case 19: return BMC_POT_20_STYLE;
#if defined(BMC_POT_21_PIN) && defined(BMC_POT_21_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=21 && BMC_MAX_POTS > 20 && defined(BMC_POT_21_X) && defined(BMC_POT_21_Y)
  case 20: return BMC_POT_21_STYLE;
#if defined(BMC_POT_22_PIN) && defined(BMC_POT_22_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=22 && BMC_MAX_POTS > 21 && defined(BMC_POT_22_X) && defined(BMC_POT_22_Y)
  case 21: return BMC_POT_22_STYLE;
#if defined(BMC_POT_23_PIN) && defined(BMC_POT_23_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=23 && BMC_MAX_POTS > 22 && defined(BMC_POT_23_X) && defined(BMC_POT_23_Y)
  case 22: return BMC_POT_23_STYLE;
#if defined(BMC_POT_24_PIN) && defined(BMC_POT_24_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=24 && BMC_MAX_POTS > 23 && defined(BMC_POT_24_X) && defined(BMC_POT_24_Y)
  case 23: return BMC_POT_24_STYLE;
#if defined(BMC_POT_25_PIN) && defined(BMC_POT_25_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=25 && BMC_MAX_POTS > 24 && defined(BMC_POT_25_X) && defined(BMC_POT_25_Y)
  case 24: return BMC_POT_25_STYLE;
#if defined(BMC_POT_26_PIN) && defined(BMC_POT_26_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=26 && BMC_MAX_POTS > 25 && defined(BMC_POT_26_X) && defined(BMC_POT_26_Y)
  case 25: return BMC_POT_26_STYLE;
#if defined(BMC_POT_27_PIN) && defined(BMC_POT_27_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=27 && BMC_MAX_POTS > 26 && defined(BMC_POT_27_X) && defined(BMC_POT_27_Y)
  case 26: return BMC_POT_27_STYLE;
#if defined(BMC_POT_28_PIN) && defined(BMC_POT_28_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=28 && BMC_MAX_POTS > 27 && defined(BMC_POT_28_X) && defined(BMC_POT_28_Y)
  case 27: return BMC_POT_28_STYLE;
#if defined(BMC_POT_29_PIN) && defined(BMC_POT_29_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=29 && BMC_MAX_POTS > 28 && defined(BMC_POT_29_X) && defined(BMC_POT_29_Y)
  case 28: return BMC_POT_29_STYLE;
#if defined(BMC_POT_30_PIN) && defined(BMC_POT_30_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=30 && BMC_MAX_POTS > 29 && defined(BMC_POT_30_X) && defined(BMC_POT_30_Y)
  case 29: return BMC_POT_30_STYLE;
#if defined(BMC_POT_31_PIN) && defined(BMC_POT_31_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=31 && BMC_MAX_POTS > 30 && defined(BMC_POT_31_X) && defined(BMC_POT_31_Y)
  case 30: return BMC_POT_31_STYLE;
#if defined(BMC_POT_32_PIN) && defined(BMC_POT_32_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=32 && BMC_MAX_POTS > 31 && defined(BMC_POT_32_X) && defined(BMC_POT_32_Y)
  case 31: return BMC_POT_32_STYLE;
#if defined(BMC_POT_33_PIN) && defined(BMC_POT_33_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=33 && BMC_MAX_POTS > 32 && defined(BMC_POT_33_X) && defined(BMC_POT_33_Y)
  case 32: return BMC_POT_33_STYLE;
#if defined(BMC_POT_34_PIN) && defined(BMC_POT_34_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=34 && BMC_MAX_POTS > 33 && defined(BMC_POT_34_X) && defined(BMC_POT_34_Y)
  case 33: return BMC_POT_34_STYLE;
#if defined(BMC_POT_35_PIN) && defined(BMC_POT_35_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=35 && BMC_MAX_POTS > 34 && defined(BMC_POT_35_X) && defined(BMC_POT_35_Y)
  case 34: return BMC_POT_35_STYLE;
#if defined(BMC_POT_36_PIN) && defined(BMC_POT_36_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=36 && BMC_MAX_POTS > 35 && defined(BMC_POT_36_X) && defined(BMC_POT_36_Y)
  case 35: return BMC_POT_36_STYLE;
#if defined(BMC_POT_37_PIN) && defined(BMC_POT_37_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=37 && BMC_MAX_POTS > 36 && defined(BMC_POT_37_X) && defined(BMC_POT_37_Y)
  case 36: return BMC_POT_37_STYLE;
#if defined(BMC_POT_38_PIN) && defined(BMC_POT_38_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=38 && BMC_MAX_POTS > 37 && defined(BMC_POT_38_X) && defined(BMC_POT_38_Y)
  case 37: return BMC_POT_38_STYLE;
#if defined(BMC_POT_39_PIN) && defined(BMC_POT_39_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=39 && BMC_MAX_POTS > 38 && defined(BMC_POT_39_X) && defined(BMC_POT_39_Y)
  case 38: return BMC_POT_39_STYLE;
#if defined(BMC_POT_40_PIN) && defined(BMC_POT_40_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=40 && BMC_MAX_POTS > 39 && defined(BMC_POT_40_X) && defined(BMC_POT_40_Y)
  case 39: return BMC_POT_40_STYLE;
#if defined(BMC_POT_41_PIN) && defined(BMC_POT_41_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=41 && BMC_MAX_POTS > 40 && defined(BMC_POT_41_X) && defined(BMC_POT_41_Y)
  case 40: return BMC_POT_41_STYLE;
#if defined(BMC_POT_42_PIN) && defined(BMC_POT_42_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=42 && BMC_MAX_POTS > 41 && defined(BMC_POT_42_X) && defined(BMC_POT_42_Y)
  case 41: return BMC_POT_42_STYLE;
#if defined(BMC_POT_43_PIN) && defined(BMC_POT_43_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=43 && BMC_MAX_POTS > 42 && defined(BMC_POT_43_X) && defined(BMC_POT_43_Y)
  case 42: return BMC_POT_43_STYLE;
#if defined(BMC_POT_44_PIN) && defined(BMC_POT_44_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=44 && BMC_MAX_POTS > 43 && defined(BMC_POT_44_X) && defined(BMC_POT_44_Y)
  case 43: return BMC_POT_44_STYLE;
#if defined(BMC_POT_45_PIN) && defined(BMC_POT_45_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=45 && BMC_MAX_POTS > 44 && defined(BMC_POT_45_X) && defined(BMC_POT_45_Y)
  case 44: return BMC_POT_45_STYLE;
#if defined(BMC_POT_46_PIN) && defined(BMC_POT_46_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=46 && BMC_MAX_POTS > 45 && defined(BMC_POT_46_X) && defined(BMC_POT_46_Y)
  case 45: return BMC_POT_46_STYLE;
#if defined(BMC_POT_47_PIN) && defined(BMC_POT_47_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=47 && BMC_MAX_POTS > 46 && defined(BMC_POT_47_X) && defined(BMC_POT_47_Y)
  case 46: return BMC_POT_47_STYLE;
#if defined(BMC_POT_48_PIN) && defined(BMC_POT_48_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=48 && BMC_MAX_POTS > 47 && defined(BMC_POT_48_X) && defined(BMC_POT_48_Y)
  case 47: return BMC_POT_48_STYLE;
#if defined(BMC_POT_49_PIN) && defined(BMC_POT_49_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=49 && BMC_MAX_POTS > 48 && defined(BMC_POT_49_X) && defined(BMC_POT_49_Y)
  case 48: return BMC_POT_49_STYLE;
#if defined(BMC_POT_50_PIN) && defined(BMC_POT_50_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=50 && BMC_MAX_POTS > 49 && defined(BMC_POT_50_X) && defined(BMC_POT_50_Y)
  case 49: return BMC_POT_50_STYLE;
#if defined(BMC_POT_51_PIN) && defined(BMC_POT_51_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=51 && BMC_MAX_POTS > 50 && defined(BMC_POT_51_X) && defined(BMC_POT_51_Y)
  case 50: return BMC_POT_51_STYLE;
#if defined(BMC_POT_52_PIN) && defined(BMC_POT_52_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=52 && BMC_MAX_POTS > 51 && defined(BMC_POT_52_X) && defined(BMC_POT_52_Y)
  case 51: return BMC_POT_52_STYLE;
#if defined(BMC_POT_53_PIN) && defined(BMC_POT_53_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=53 && BMC_MAX_POTS > 52 && defined(BMC_POT_53_X) && defined(BMC_POT_53_Y)
  case 52: return BMC_POT_53_STYLE;
#if defined(BMC_POT_54_PIN) && defined(BMC_POT_54_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=54 && BMC_MAX_POTS > 53 && defined(BMC_POT_54_X) && defined(BMC_POT_54_Y)
  case 53: return BMC_POT_54_STYLE;
#if defined(BMC_POT_55_PIN) && defined(BMC_POT_55_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=55 && BMC_MAX_POTS > 54 && defined(BMC_POT_55_X) && defined(BMC_POT_55_Y)
  case 54: return BMC_POT_55_STYLE;
#if defined(BMC_POT_56_PIN) && defined(BMC_POT_56_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=56 && BMC_MAX_POTS > 55 && defined(BMC_POT_56_X) && defined(BMC_POT_56_Y)
  case 55: return BMC_POT_56_STYLE;
#if defined(BMC_POT_57_PIN) && defined(BMC_POT_57_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=57 && BMC_MAX_POTS > 56 && defined(BMC_POT_57_X) && defined(BMC_POT_57_Y)
  case 56: return BMC_POT_57_STYLE;
#if defined(BMC_POT_58_PIN) && defined(BMC_POT_58_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=58 && BMC_MAX_POTS > 57 && defined(BMC_POT_58_X) && defined(BMC_POT_58_Y)
  case 57: return BMC_POT_58_STYLE;
#if defined(BMC_POT_59_PIN) && defined(BMC_POT_59_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=59 && BMC_MAX_POTS > 58 && defined(BMC_POT_59_X) && defined(BMC_POT_59_Y)
  case 58: return BMC_POT_59_STYLE;
#if defined(BMC_POT_60_PIN) && defined(BMC_POT_60_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=60 && BMC_MAX_POTS > 59 && defined(BMC_POT_60_X) && defined(BMC_POT_60_Y)
  case 59: return BMC_POT_60_STYLE;
#if defined(BMC_POT_61_PIN) && defined(BMC_POT_61_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=61 && BMC_MAX_POTS > 60 && defined(BMC_POT_61_X) && defined(BMC_POT_61_Y)
  case 60: return BMC_POT_61_STYLE;
#if defined(BMC_POT_62_PIN) && defined(BMC_POT_62_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=62 && BMC_MAX_POTS > 61 && defined(BMC_POT_62_X) && defined(BMC_POT_62_Y)
  case 61: return BMC_POT_62_STYLE;
#if defined(BMC_POT_63_PIN) && defined(BMC_POT_63_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=63 && BMC_MAX_POTS > 62 && defined(BMC_POT_63_X) && defined(BMC_POT_63_Y)
  case 62: return BMC_POT_63_STYLE;
#if defined(BMC_POT_64_PIN) && defined(BMC_POT_64_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=64 && BMC_MAX_POTS > 63 && defined(BMC_POT_64_X) && defined(BMC_POT_64_Y)
  case 63: return BMC_POT_64_STYLE;
#if defined(BMC_POT_65_PIN) && defined(BMC_POT_65_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=65 && BMC_MAX_POTS > 64 && defined(BMC_POT_65_X) && defined(BMC_POT_65_Y)
  case 64: return BMC_POT_65_STYLE;
#if defined(BMC_POT_66_PIN) && defined(BMC_POT_66_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=66 && BMC_MAX_POTS > 65 && defined(BMC_POT_66_X) && defined(BMC_POT_66_Y)
  case 65: return BMC_POT_66_STYLE;
#if defined(BMC_POT_67_PIN) && defined(BMC_POT_67_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=67 && BMC_MAX_POTS > 66 && defined(BMC_POT_67_X) && defined(BMC_POT_67_Y)
  case 66: return BMC_POT_67_STYLE;
#if defined(BMC_POT_68_PIN) && defined(BMC_POT_68_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=68 && BMC_MAX_POTS > 67 && defined(BMC_POT_68_X) && defined(BMC_POT_68_Y)
  case 67: return BMC_POT_68_STYLE;
#if defined(BMC_POT_69_PIN) && defined(BMC_POT_69_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=69 && BMC_MAX_POTS > 68 && defined(BMC_POT_69_X) && defined(BMC_POT_69_Y)
  case 68: return BMC_POT_69_STYLE;
#if defined(BMC_POT_70_PIN) && defined(BMC_POT_70_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=70 && BMC_MAX_POTS > 69 && defined(BMC_POT_70_X) && defined(BMC_POT_70_Y)
  case 69: return BMC_POT_70_STYLE;
#if defined(BMC_POT_71_PIN) && defined(BMC_POT_71_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=71 && BMC_MAX_POTS > 70 && defined(BMC_POT_71_X) && defined(BMC_POT_71_Y)
  case 70: return BMC_POT_71_STYLE;
#if defined(BMC_POT_72_PIN) && defined(BMC_POT_72_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=72 && BMC_MAX_POTS > 71 && defined(BMC_POT_72_X) && defined(BMC_POT_72_Y)
  case 71: return BMC_POT_72_STYLE;
#if defined(BMC_POT_73_PIN) && defined(BMC_POT_73_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=73 && BMC_MAX_POTS > 72 && defined(BMC_POT_73_X) && defined(BMC_POT_73_Y)
  case 72: return BMC_POT_73_STYLE;
#if defined(BMC_POT_74_PIN) && defined(BMC_POT_74_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=74 && BMC_MAX_POTS > 73 && defined(BMC_POT_74_X) && defined(BMC_POT_74_Y)
  case 73: return BMC_POT_74_STYLE;
#if defined(BMC_POT_75_PIN) && defined(BMC_POT_75_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=75 && BMC_MAX_POTS > 74 && defined(BMC_POT_75_X) && defined(BMC_POT_75_Y)
  case 74: return BMC_POT_75_STYLE;
#if defined(BMC_POT_76_PIN) && defined(BMC_POT_76_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=76 && BMC_MAX_POTS > 75 && defined(BMC_POT_76_X) && defined(BMC_POT_76_Y)
  case 75: return BMC_POT_76_STYLE;
#if defined(BMC_POT_77_PIN) && defined(BMC_POT_77_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=77 && BMC_MAX_POTS > 76 && defined(BMC_POT_77_X) && defined(BMC_POT_77_Y)
  case 76: return BMC_POT_77_STYLE;
#if defined(BMC_POT_78_PIN) && defined(BMC_POT_78_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=78 && BMC_MAX_POTS > 77 && defined(BMC_POT_78_X) && defined(BMC_POT_78_Y)
  case 77: return BMC_POT_78_STYLE;
#if defined(BMC_POT_79_PIN) && defined(BMC_POT_79_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=79 && BMC_MAX_POTS > 78 && defined(BMC_POT_79_X) && defined(BMC_POT_79_Y)
  case 78: return BMC_POT_79_STYLE;
#if defined(BMC_POT_80_PIN) && defined(BMC_POT_80_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=80 && BMC_MAX_POTS > 79 && defined(BMC_POT_80_X) && defined(BMC_POT_80_Y)
  case 79: return BMC_POT_80_STYLE;
#if defined(BMC_POT_81_PIN) && defined(BMC_POT_81_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=81 && BMC_MAX_POTS > 80 && defined(BMC_POT_81_X) && defined(BMC_POT_81_Y)
  case 80: return BMC_POT_81_STYLE;
#if defined(BMC_POT_82_PIN) && defined(BMC_POT_82_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=82 && BMC_MAX_POTS > 81 && defined(BMC_POT_82_X) && defined(BMC_POT_82_Y)
  case 81: return BMC_POT_82_STYLE;
#if defined(BMC_POT_83_PIN) && defined(BMC_POT_83_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=83 && BMC_MAX_POTS > 82 && defined(BMC_POT_83_X) && defined(BMC_POT_83_Y)
  case 82: return BMC_POT_83_STYLE;
#if defined(BMC_POT_84_PIN) && defined(BMC_POT_84_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=84 && BMC_MAX_POTS > 83 && defined(BMC_POT_84_X) && defined(BMC_POT_84_Y)
  case 83: return BMC_POT_84_STYLE;
#if defined(BMC_POT_85_PIN) && defined(BMC_POT_85_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=85 && BMC_MAX_POTS > 84 && defined(BMC_POT_85_X) && defined(BMC_POT_85_Y)
  case 84: return BMC_POT_85_STYLE;
#if defined(BMC_POT_86_PIN) && defined(BMC_POT_86_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=86 && BMC_MAX_POTS > 85 && defined(BMC_POT_86_X) && defined(BMC_POT_86_Y)
  case 85: return BMC_POT_86_STYLE;
#if defined(BMC_POT_87_PIN) && defined(BMC_POT_87_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=87 && BMC_MAX_POTS > 86 && defined(BMC_POT_87_X) && defined(BMC_POT_87_Y)
  case 86: return BMC_POT_87_STYLE;
#if defined(BMC_POT_88_PIN) && defined(BMC_POT_88_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=88 && BMC_MAX_POTS > 87 && defined(BMC_POT_88_X) && defined(BMC_POT_88_Y)
  case 87: return BMC_POT_88_STYLE;
#if defined(BMC_POT_89_PIN) && defined(BMC_POT_89_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=89 && BMC_MAX_POTS > 88 && defined(BMC_POT_89_X) && defined(BMC_POT_89_Y)
  case 88: return BMC_POT_89_STYLE;
#if defined(BMC_POT_90_PIN) && defined(BMC_POT_90_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=90 && BMC_MAX_POTS > 89 && defined(BMC_POT_90_X) && defined(BMC_POT_90_Y)
  case 89: return BMC_POT_90_STYLE;
#if defined(BMC_POT_91_PIN) && defined(BMC_POT_91_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=91 && BMC_MAX_POTS > 90 && defined(BMC_POT_91_X) && defined(BMC_POT_91_Y)
  case 90: return BMC_POT_91_STYLE;
#if defined(BMC_POT_92_PIN) && defined(BMC_POT_92_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=92 && BMC_MAX_POTS > 91 && defined(BMC_POT_92_X) && defined(BMC_POT_92_Y)
  case 91: return BMC_POT_92_STYLE;
#if defined(BMC_POT_93_PIN) && defined(BMC_POT_93_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=93 && BMC_MAX_POTS > 92 && defined(BMC_POT_93_X) && defined(BMC_POT_93_Y)
  case 92: return BMC_POT_93_STYLE;
#if defined(BMC_POT_94_PIN) && defined(BMC_POT_94_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=94 && BMC_MAX_POTS > 93 && defined(BMC_POT_94_X) && defined(BMC_POT_94_Y)
  case 93: return BMC_POT_94_STYLE;
#if defined(BMC_POT_95_PIN) && defined(BMC_POT_95_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=95 && BMC_MAX_POTS > 94 && defined(BMC_POT_95_X) && defined(BMC_POT_95_Y)
  case 94: return BMC_POT_95_STYLE;
#if defined(BMC_POT_96_PIN) && defined(BMC_POT_96_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=96 && BMC_MAX_POTS > 95 && defined(BMC_POT_96_X) && defined(BMC_POT_96_Y)
  case 95: return BMC_POT_96_STYLE;
#if defined(BMC_POT_97_PIN) && defined(BMC_POT_97_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=97 && BMC_MAX_POTS > 96 && defined(BMC_POT_97_X) && defined(BMC_POT_97_Y)
  case 96: return BMC_POT_97_STYLE;
#if defined(BMC_POT_98_PIN) && defined(BMC_POT_98_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=98 && BMC_MAX_POTS > 97 && defined(BMC_POT_98_X) && defined(BMC_POT_98_Y)
  case 97: return BMC_POT_98_STYLE;
#if defined(BMC_POT_99_PIN) && defined(BMC_POT_99_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=99 && BMC_MAX_POTS > 98 && defined(BMC_POT_99_X) && defined(BMC_POT_99_Y)
  case 98: return BMC_POT_99_STYLE;
#if defined(BMC_POT_100_PIN) && defined(BMC_POT_100_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=100 && BMC_MAX_POTS > 99 && defined(BMC_POT_100_X) && defined(BMC_POT_100_Y)
  case 99: return BMC_POT_100_STYLE;
#if defined(BMC_POT_101_PIN) && defined(BMC_POT_101_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=101 && BMC_MAX_POTS > 100 && defined(BMC_POT_101_X) && defined(BMC_POT_101_Y)
  case 100: return BMC_POT_101_STYLE;
#if defined(BMC_POT_102_PIN) && defined(BMC_POT_102_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=102 && BMC_MAX_POTS > 101 && defined(BMC_POT_102_X) && defined(BMC_POT_102_Y)
  case 101: return BMC_POT_102_STYLE;
#if defined(BMC_POT_103_PIN) && defined(BMC_POT_103_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=103 && BMC_MAX_POTS > 102 && defined(BMC_POT_103_X) && defined(BMC_POT_103_Y)
  case 102: return BMC_POT_103_STYLE;
#if defined(BMC_POT_104_PIN) && defined(BMC_POT_104_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=104 && BMC_MAX_POTS > 103 && defined(BMC_POT_104_X) && defined(BMC_POT_104_Y)
  case 103: return BMC_POT_104_STYLE;
#if defined(BMC_POT_105_PIN) && defined(BMC_POT_105_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=105 && BMC_MAX_POTS > 104 && defined(BMC_POT_105_X) && defined(BMC_POT_105_Y)
  case 104: return BMC_POT_105_STYLE;
#if defined(BMC_POT_106_PIN) && defined(BMC_POT_106_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=106 && BMC_MAX_POTS > 105 && defined(BMC_POT_106_X) && defined(BMC_POT_106_Y)
  case 105: return BMC_POT_106_STYLE;
#if defined(BMC_POT_107_PIN) && defined(BMC_POT_107_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=107 && BMC_MAX_POTS > 106 && defined(BMC_POT_107_X) && defined(BMC_POT_107_Y)
  case 106: return BMC_POT_107_STYLE;
#if defined(BMC_POT_108_PIN) && defined(BMC_POT_108_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=108 && BMC_MAX_POTS > 107 && defined(BMC_POT_108_X) && defined(BMC_POT_108_Y)
  case 107: return BMC_POT_108_STYLE;
#if defined(BMC_POT_109_PIN) && defined(BMC_POT_109_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=109 && BMC_MAX_POTS > 108 && defined(BMC_POT_109_X) && defined(BMC_POT_109_Y)
  case 108: return BMC_POT_109_STYLE;
#if defined(BMC_POT_110_PIN) && defined(BMC_POT_110_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=110 && BMC_MAX_POTS > 109 && defined(BMC_POT_110_X) && defined(BMC_POT_110_Y)
  case 109: return BMC_POT_110_STYLE;
#if defined(BMC_POT_111_PIN) && defined(BMC_POT_111_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=111 && BMC_MAX_POTS > 110 && defined(BMC_POT_111_X) && defined(BMC_POT_111_Y)
  case 110: return BMC_POT_111_STYLE;
#if defined(BMC_POT_112_PIN) && defined(BMC_POT_112_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=112 && BMC_MAX_POTS > 111 && defined(BMC_POT_112_X) && defined(BMC_POT_112_Y)
  case 111: return BMC_POT_112_STYLE;
#if defined(BMC_POT_113_PIN) && defined(BMC_POT_113_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=113 && BMC_MAX_POTS > 112 && defined(BMC_POT_113_X) && defined(BMC_POT_113_Y)
  case 112: return BMC_POT_113_STYLE;
#if defined(BMC_POT_114_PIN) && defined(BMC_POT_114_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=114 && BMC_MAX_POTS > 113 && defined(BMC_POT_114_X) && defined(BMC_POT_114_Y)
  case 113: return BMC_POT_114_STYLE;
#if defined(BMC_POT_115_PIN) && defined(BMC_POT_115_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=115 && BMC_MAX_POTS > 114 && defined(BMC_POT_115_X) && defined(BMC_POT_115_Y)
  case 114: return BMC_POT_115_STYLE;
#if defined(BMC_POT_116_PIN) && defined(BMC_POT_116_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=116 && BMC_MAX_POTS > 115 && defined(BMC_POT_116_X) && defined(BMC_POT_116_Y)
  case 115: return BMC_POT_116_STYLE;
#if defined(BMC_POT_117_PIN) && defined(BMC_POT_117_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=117 && BMC_MAX_POTS > 116 && defined(BMC_POT_117_X) && defined(BMC_POT_117_Y)
  case 116: return BMC_POT_117_STYLE;
#if defined(BMC_POT_118_PIN) && defined(BMC_POT_118_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=118 && BMC_MAX_POTS > 117 && defined(BMC_POT_118_X) && defined(BMC_POT_118_Y)
  case 117: return BMC_POT_118_STYLE;
#if defined(BMC_POT_119_PIN) && defined(BMC_POT_119_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=119 && BMC_MAX_POTS > 118 && defined(BMC_POT_119_X) && defined(BMC_POT_119_Y)
  case 118: return BMC_POT_119_STYLE;
#if defined(BMC_POT_120_PIN) && defined(BMC_POT_120_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=120 && BMC_MAX_POTS > 119 && defined(BMC_POT_120_X) && defined(BMC_POT_120_Y)
  case 119: return BMC_POT_120_STYLE;
#if defined(BMC_POT_121_PIN) && defined(BMC_POT_121_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=121 && BMC_MAX_POTS > 120 && defined(BMC_POT_121_X) && defined(BMC_POT_121_Y)
  case 120: return BMC_POT_121_STYLE;
#if defined(BMC_POT_122_PIN) && defined(BMC_POT_122_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=122 && BMC_MAX_POTS > 121 && defined(BMC_POT_122_X) && defined(BMC_POT_122_Y)
  case 121: return BMC_POT_122_STYLE;
#if defined(BMC_POT_123_PIN) && defined(BMC_POT_123_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=123 && BMC_MAX_POTS > 122 && defined(BMC_POT_123_X) && defined(BMC_POT_123_Y)
  case 122: return BMC_POT_123_STYLE;
#if defined(BMC_POT_124_PIN) && defined(BMC_POT_124_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=124 && BMC_MAX_POTS > 123 && defined(BMC_POT_124_X) && defined(BMC_POT_124_Y)
  case 123: return BMC_POT_124_STYLE;
#if defined(BMC_POT_125_PIN) && defined(BMC_POT_125_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=125 && BMC_MAX_POTS > 124 && defined(BMC_POT_125_X) && defined(BMC_POT_125_Y)
  case 124: return BMC_POT_125_STYLE;
#if defined(BMC_POT_126_PIN) && defined(BMC_POT_126_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=126 && BMC_MAX_POTS > 125 && defined(BMC_POT_126_X) && defined(BMC_POT_126_Y)
  case 125: return BMC_POT_126_STYLE;
#if defined(BMC_POT_127_PIN) && defined(BMC_POT_127_STYLE) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=127 && BMC_MAX_POTS > 126 && defined(BMC_POT_127_X) && defined(BMC_POT_127_Y)
  case 126: return BMC_POT_127_STYLE;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getButtonPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_BUTTONS > 0
switch(index){
#if defined(BMC_BUTTON_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_1_X) && defined(BMC_BUTTON_1_Y)
  case 0: return (x) ? BMC_BUTTON_1_X : BMC_BUTTON_1_Y;
#if defined(BMC_BUTTON_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_2_X) && defined(BMC_BUTTON_2_Y)
  case 1: return (x) ? BMC_BUTTON_2_X : BMC_BUTTON_2_Y;
#if defined(BMC_BUTTON_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_3_X) && defined(BMC_BUTTON_3_Y)
  case 2: return (x) ? BMC_BUTTON_3_X : BMC_BUTTON_3_Y;
#if defined(BMC_BUTTON_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_4_X) && defined(BMC_BUTTON_4_Y)
  case 3: return (x) ? BMC_BUTTON_4_X : BMC_BUTTON_4_Y;
#if defined(BMC_BUTTON_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_5_X) && defined(BMC_BUTTON_5_Y)
  case 4: return (x) ? BMC_BUTTON_5_X : BMC_BUTTON_5_Y;
#if defined(BMC_BUTTON_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_6_X) && defined(BMC_BUTTON_6_Y)
  case 5: return (x) ? BMC_BUTTON_6_X : BMC_BUTTON_6_Y;
#if defined(BMC_BUTTON_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_7_X) && defined(BMC_BUTTON_7_Y)
  case 6: return (x) ? BMC_BUTTON_7_X : BMC_BUTTON_7_Y;
#if defined(BMC_BUTTON_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_8_X) && defined(BMC_BUTTON_8_Y)
  case 7: return (x) ? BMC_BUTTON_8_X : BMC_BUTTON_8_Y;
#if defined(BMC_BUTTON_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_9_X) && defined(BMC_BUTTON_9_Y)
  case 8: return (x) ? BMC_BUTTON_9_X : BMC_BUTTON_9_Y;
#if defined(BMC_BUTTON_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_10_X) && defined(BMC_BUTTON_10_Y)
  case 9: return (x) ? BMC_BUTTON_10_X : BMC_BUTTON_10_Y;
#if defined(BMC_BUTTON_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_11_X) && defined(BMC_BUTTON_11_Y)
  case 10: return (x) ? BMC_BUTTON_11_X : BMC_BUTTON_11_Y;
#if defined(BMC_BUTTON_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_12_X) && defined(BMC_BUTTON_12_Y)
  case 11: return (x) ? BMC_BUTTON_12_X : BMC_BUTTON_12_Y;
#if defined(BMC_BUTTON_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_13_X) && defined(BMC_BUTTON_13_Y)
  case 12: return (x) ? BMC_BUTTON_13_X : BMC_BUTTON_13_Y;
#if defined(BMC_BUTTON_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_14_X) && defined(BMC_BUTTON_14_Y)
  case 13: return (x) ? BMC_BUTTON_14_X : BMC_BUTTON_14_Y;
#if defined(BMC_BUTTON_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_15_X) && defined(BMC_BUTTON_15_Y)
  case 14: return (x) ? BMC_BUTTON_15_X : BMC_BUTTON_15_Y;
#if defined(BMC_BUTTON_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_16_X) && defined(BMC_BUTTON_16_Y)
  case 15: return (x) ? BMC_BUTTON_16_X : BMC_BUTTON_16_Y;
#if defined(BMC_BUTTON_17_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_17_X) && defined(BMC_BUTTON_17_Y)
  case 16: return (x) ? BMC_BUTTON_17_X : BMC_BUTTON_17_Y;
#if defined(BMC_BUTTON_18_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_18_X) && defined(BMC_BUTTON_18_Y)
  case 17: return (x) ? BMC_BUTTON_18_X : BMC_BUTTON_18_Y;
#if defined(BMC_BUTTON_19_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_19_X) && defined(BMC_BUTTON_19_Y)
  case 18: return (x) ? BMC_BUTTON_19_X : BMC_BUTTON_19_Y;
#if defined(BMC_BUTTON_20_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_20_X) && defined(BMC_BUTTON_20_Y)
  case 19: return (x) ? BMC_BUTTON_20_X : BMC_BUTTON_20_Y;
#if defined(BMC_BUTTON_21_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_21_X) && defined(BMC_BUTTON_21_Y)
  case 20: return (x) ? BMC_BUTTON_21_X : BMC_BUTTON_21_Y;
#if defined(BMC_BUTTON_22_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_22_X) && defined(BMC_BUTTON_22_Y)
  case 21: return (x) ? BMC_BUTTON_22_X : BMC_BUTTON_22_Y;
#if defined(BMC_BUTTON_23_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_23_X) && defined(BMC_BUTTON_23_Y)
  case 22: return (x) ? BMC_BUTTON_23_X : BMC_BUTTON_23_Y;
#if defined(BMC_BUTTON_24_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_24_X) && defined(BMC_BUTTON_24_Y)
  case 23: return (x) ? BMC_BUTTON_24_X : BMC_BUTTON_24_Y;
#if defined(BMC_BUTTON_25_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_25_X) && defined(BMC_BUTTON_25_Y)
  case 24: return (x) ? BMC_BUTTON_25_X : BMC_BUTTON_25_Y;
#if defined(BMC_BUTTON_26_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_26_X) && defined(BMC_BUTTON_26_Y)
  case 25: return (x) ? BMC_BUTTON_26_X : BMC_BUTTON_26_Y;
#if defined(BMC_BUTTON_27_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_27_X) && defined(BMC_BUTTON_27_Y)
  case 26: return (x) ? BMC_BUTTON_27_X : BMC_BUTTON_27_Y;
#if defined(BMC_BUTTON_28_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_28_X) && defined(BMC_BUTTON_28_Y)
  case 27: return (x) ? BMC_BUTTON_28_X : BMC_BUTTON_28_Y;
#if defined(BMC_BUTTON_29_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_29_X) && defined(BMC_BUTTON_29_Y)
  case 28: return (x) ? BMC_BUTTON_29_X : BMC_BUTTON_29_Y;
#if defined(BMC_BUTTON_30_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_30_X) && defined(BMC_BUTTON_30_Y)
  case 29: return (x) ? BMC_BUTTON_30_X : BMC_BUTTON_30_Y;
#if defined(BMC_BUTTON_31_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_31_X) && defined(BMC_BUTTON_31_Y)
  case 30: return (x) ? BMC_BUTTON_31_X : BMC_BUTTON_31_Y;
#if defined(BMC_BUTTON_32_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_32_X) && defined(BMC_BUTTON_32_Y)
  case 31: return (x) ? BMC_BUTTON_32_X : BMC_BUTTON_32_Y;
#if defined(BMC_BUTTON_33_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=33 && BMC_MAX_BUTTONS > 32 && defined(BMC_BUTTON_33_X) && defined(BMC_BUTTON_33_Y)
  case 32: return (x) ? BMC_BUTTON_33_X : BMC_BUTTON_33_Y;
#if defined(BMC_BUTTON_34_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=34 && BMC_MAX_BUTTONS > 33 && defined(BMC_BUTTON_34_X) && defined(BMC_BUTTON_34_Y)
  case 33: return (x) ? BMC_BUTTON_34_X : BMC_BUTTON_34_Y;
#if defined(BMC_BUTTON_35_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=35 && BMC_MAX_BUTTONS > 34 && defined(BMC_BUTTON_35_X) && defined(BMC_BUTTON_35_Y)
  case 34: return (x) ? BMC_BUTTON_35_X : BMC_BUTTON_35_Y;
#if defined(BMC_BUTTON_36_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=36 && BMC_MAX_BUTTONS > 35 && defined(BMC_BUTTON_36_X) && defined(BMC_BUTTON_36_Y)
  case 35: return (x) ? BMC_BUTTON_36_X : BMC_BUTTON_36_Y;
#if defined(BMC_BUTTON_37_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=37 && BMC_MAX_BUTTONS > 36 && defined(BMC_BUTTON_37_X) && defined(BMC_BUTTON_37_Y)
  case 36: return (x) ? BMC_BUTTON_37_X : BMC_BUTTON_37_Y;
#if defined(BMC_BUTTON_38_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=38 && BMC_MAX_BUTTONS > 37 && defined(BMC_BUTTON_38_X) && defined(BMC_BUTTON_38_Y)
  case 37: return (x) ? BMC_BUTTON_38_X : BMC_BUTTON_38_Y;
#if defined(BMC_BUTTON_39_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=39 && BMC_MAX_BUTTONS > 38 && defined(BMC_BUTTON_39_X) && defined(BMC_BUTTON_39_Y)
  case 38: return (x) ? BMC_BUTTON_39_X : BMC_BUTTON_39_Y;
#if defined(BMC_BUTTON_40_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=40 && BMC_MAX_BUTTONS > 39 && defined(BMC_BUTTON_40_X) && defined(BMC_BUTTON_40_Y)
  case 39: return (x) ? BMC_BUTTON_40_X : BMC_BUTTON_40_Y;
#if defined(BMC_BUTTON_41_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=41 && BMC_MAX_BUTTONS > 40 && defined(BMC_BUTTON_41_X) && defined(BMC_BUTTON_41_Y)
  case 40: return (x) ? BMC_BUTTON_41_X : BMC_BUTTON_41_Y;
#if defined(BMC_BUTTON_42_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=42 && BMC_MAX_BUTTONS > 41 && defined(BMC_BUTTON_42_X) && defined(BMC_BUTTON_42_Y)
  case 41: return (x) ? BMC_BUTTON_42_X : BMC_BUTTON_42_Y;
#if defined(BMC_BUTTON_43_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=43 && BMC_MAX_BUTTONS > 42 && defined(BMC_BUTTON_43_X) && defined(BMC_BUTTON_43_Y)
  case 42: return (x) ? BMC_BUTTON_43_X : BMC_BUTTON_43_Y;
#if defined(BMC_BUTTON_44_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=44 && BMC_MAX_BUTTONS > 43 && defined(BMC_BUTTON_44_X) && defined(BMC_BUTTON_44_Y)
  case 43: return (x) ? BMC_BUTTON_44_X : BMC_BUTTON_44_Y;
#if defined(BMC_BUTTON_45_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=45 && BMC_MAX_BUTTONS > 44 && defined(BMC_BUTTON_45_X) && defined(BMC_BUTTON_45_Y)
  case 44: return (x) ? BMC_BUTTON_45_X : BMC_BUTTON_45_Y;
#if defined(BMC_BUTTON_46_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=46 && BMC_MAX_BUTTONS > 45 && defined(BMC_BUTTON_46_X) && defined(BMC_BUTTON_46_Y)
  case 45: return (x) ? BMC_BUTTON_46_X : BMC_BUTTON_46_Y;
#if defined(BMC_BUTTON_47_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=47 && BMC_MAX_BUTTONS > 46 && defined(BMC_BUTTON_47_X) && defined(BMC_BUTTON_47_Y)
  case 46: return (x) ? BMC_BUTTON_47_X : BMC_BUTTON_47_Y;
#if defined(BMC_BUTTON_48_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=48 && BMC_MAX_BUTTONS > 47 && defined(BMC_BUTTON_48_X) && defined(BMC_BUTTON_48_Y)
  case 47: return (x) ? BMC_BUTTON_48_X : BMC_BUTTON_48_Y;
#if defined(BMC_BUTTON_49_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=49 && BMC_MAX_BUTTONS > 48 && defined(BMC_BUTTON_49_X) && defined(BMC_BUTTON_49_Y)
  case 48: return (x) ? BMC_BUTTON_49_X : BMC_BUTTON_49_Y;
#if defined(BMC_BUTTON_50_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=50 && BMC_MAX_BUTTONS > 49 && defined(BMC_BUTTON_50_X) && defined(BMC_BUTTON_50_Y)
  case 49: return (x) ? BMC_BUTTON_50_X : BMC_BUTTON_50_Y;
#if defined(BMC_BUTTON_51_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=51 && BMC_MAX_BUTTONS > 50 && defined(BMC_BUTTON_51_X) && defined(BMC_BUTTON_51_Y)
  case 50: return (x) ? BMC_BUTTON_51_X : BMC_BUTTON_51_Y;
#if defined(BMC_BUTTON_52_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=52 && BMC_MAX_BUTTONS > 51 && defined(BMC_BUTTON_52_X) && defined(BMC_BUTTON_52_Y)
  case 51: return (x) ? BMC_BUTTON_52_X : BMC_BUTTON_52_Y;
#if defined(BMC_BUTTON_53_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=53 && BMC_MAX_BUTTONS > 52 && defined(BMC_BUTTON_53_X) && defined(BMC_BUTTON_53_Y)
  case 52: return (x) ? BMC_BUTTON_53_X : BMC_BUTTON_53_Y;
#if defined(BMC_BUTTON_54_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=54 && BMC_MAX_BUTTONS > 53 && defined(BMC_BUTTON_54_X) && defined(BMC_BUTTON_54_Y)
  case 53: return (x) ? BMC_BUTTON_54_X : BMC_BUTTON_54_Y;
#if defined(BMC_BUTTON_55_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=55 && BMC_MAX_BUTTONS > 54 && defined(BMC_BUTTON_55_X) && defined(BMC_BUTTON_55_Y)
  case 54: return (x) ? BMC_BUTTON_55_X : BMC_BUTTON_55_Y;
#if defined(BMC_BUTTON_56_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=56 && BMC_MAX_BUTTONS > 55 && defined(BMC_BUTTON_56_X) && defined(BMC_BUTTON_56_Y)
  case 55: return (x) ? BMC_BUTTON_56_X : BMC_BUTTON_56_Y;
#if defined(BMC_BUTTON_57_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=57 && BMC_MAX_BUTTONS > 56 && defined(BMC_BUTTON_57_X) && defined(BMC_BUTTON_57_Y)
  case 56: return (x) ? BMC_BUTTON_57_X : BMC_BUTTON_57_Y;
#if defined(BMC_BUTTON_58_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=58 && BMC_MAX_BUTTONS > 57 && defined(BMC_BUTTON_58_X) && defined(BMC_BUTTON_58_Y)
  case 57: return (x) ? BMC_BUTTON_58_X : BMC_BUTTON_58_Y;
#if defined(BMC_BUTTON_59_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=59 && BMC_MAX_BUTTONS > 58 && defined(BMC_BUTTON_59_X) && defined(BMC_BUTTON_59_Y)
  case 58: return (x) ? BMC_BUTTON_59_X : BMC_BUTTON_59_Y;
#if defined(BMC_BUTTON_60_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=60 && BMC_MAX_BUTTONS > 59 && defined(BMC_BUTTON_60_X) && defined(BMC_BUTTON_60_Y)
  case 59: return (x) ? BMC_BUTTON_60_X : BMC_BUTTON_60_Y;
#if defined(BMC_BUTTON_61_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=61 && BMC_MAX_BUTTONS > 60 && defined(BMC_BUTTON_61_X) && defined(BMC_BUTTON_61_Y)
  case 60: return (x) ? BMC_BUTTON_61_X : BMC_BUTTON_61_Y;
#if defined(BMC_BUTTON_62_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=62 && BMC_MAX_BUTTONS > 61 && defined(BMC_BUTTON_62_X) && defined(BMC_BUTTON_62_Y)
  case 61: return (x) ? BMC_BUTTON_62_X : BMC_BUTTON_62_Y;
#if defined(BMC_BUTTON_63_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=63 && BMC_MAX_BUTTONS > 62 && defined(BMC_BUTTON_63_X) && defined(BMC_BUTTON_63_Y)
  case 62: return (x) ? BMC_BUTTON_63_X : BMC_BUTTON_63_Y;
#if defined(BMC_BUTTON_64_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=64 && BMC_MAX_BUTTONS > 63 && defined(BMC_BUTTON_64_X) && defined(BMC_BUTTON_64_Y)
  case 63: return (x) ? BMC_BUTTON_64_X : BMC_BUTTON_64_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getLedPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_LEDS > 0
switch(index){
#if defined(BMC_LED_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_LEDS > 0 && defined(BMC_LED_1_X) && defined(BMC_LED_1_Y)
  case 0: return (x) ? BMC_LED_1_X : BMC_LED_1_Y;
#if defined(BMC_LED_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_LEDS > 1 && defined(BMC_LED_2_X) && defined(BMC_LED_2_Y)
  case 1: return (x) ? BMC_LED_2_X : BMC_LED_2_Y;
#if defined(BMC_LED_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_LEDS > 2 && defined(BMC_LED_3_X) && defined(BMC_LED_3_Y)
  case 2: return (x) ? BMC_LED_3_X : BMC_LED_3_Y;
#if defined(BMC_LED_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_LEDS > 3 && defined(BMC_LED_4_X) && defined(BMC_LED_4_Y)
  case 3: return (x) ? BMC_LED_4_X : BMC_LED_4_Y;
#if defined(BMC_LED_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_LEDS > 4 && defined(BMC_LED_5_X) && defined(BMC_LED_5_Y)
  case 4: return (x) ? BMC_LED_5_X : BMC_LED_5_Y;
#if defined(BMC_LED_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_LEDS > 5 && defined(BMC_LED_6_X) && defined(BMC_LED_6_Y)
  case 5: return (x) ? BMC_LED_6_X : BMC_LED_6_Y;
#if defined(BMC_LED_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_LEDS > 6 && defined(BMC_LED_7_X) && defined(BMC_LED_7_Y)
  case 6: return (x) ? BMC_LED_7_X : BMC_LED_7_Y;
#if defined(BMC_LED_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_LEDS > 7 && defined(BMC_LED_8_X) && defined(BMC_LED_8_Y)
  case 7: return (x) ? BMC_LED_8_X : BMC_LED_8_Y;
#if defined(BMC_LED_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_LEDS > 8 && defined(BMC_LED_9_X) && defined(BMC_LED_9_Y)
  case 8: return (x) ? BMC_LED_9_X : BMC_LED_9_Y;
#if defined(BMC_LED_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_LEDS > 9 && defined(BMC_LED_10_X) && defined(BMC_LED_10_Y)
  case 9: return (x) ? BMC_LED_10_X : BMC_LED_10_Y;
#if defined(BMC_LED_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_LEDS > 10 && defined(BMC_LED_11_X) && defined(BMC_LED_11_Y)
  case 10: return (x) ? BMC_LED_11_X : BMC_LED_11_Y;
#if defined(BMC_LED_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_LEDS > 11 && defined(BMC_LED_12_X) && defined(BMC_LED_12_Y)
  case 11: return (x) ? BMC_LED_12_X : BMC_LED_12_Y;
#if defined(BMC_LED_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_LEDS > 12 && defined(BMC_LED_13_X) && defined(BMC_LED_13_Y)
  case 12: return (x) ? BMC_LED_13_X : BMC_LED_13_Y;
#if defined(BMC_LED_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_LEDS > 13 && defined(BMC_LED_14_X) && defined(BMC_LED_14_Y)
  case 13: return (x) ? BMC_LED_14_X : BMC_LED_14_Y;
#if defined(BMC_LED_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_LEDS > 14 && defined(BMC_LED_15_X) && defined(BMC_LED_15_Y)
  case 14: return (x) ? BMC_LED_15_X : BMC_LED_15_Y;
#if defined(BMC_LED_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_LEDS > 15 && defined(BMC_LED_16_X) && defined(BMC_LED_16_Y)
  case 15: return (x) ? BMC_LED_16_X : BMC_LED_16_Y;
#if defined(BMC_LED_17_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && BMC_MAX_LEDS > 16 && defined(BMC_LED_17_X) && defined(BMC_LED_17_Y)
  case 16: return (x) ? BMC_LED_17_X : BMC_LED_17_Y;
#if defined(BMC_LED_18_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && BMC_MAX_LEDS > 17 && defined(BMC_LED_18_X) && defined(BMC_LED_18_Y)
  case 17: return (x) ? BMC_LED_18_X : BMC_LED_18_Y;
#if defined(BMC_LED_19_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && BMC_MAX_LEDS > 18 && defined(BMC_LED_19_X) && defined(BMC_LED_19_Y)
  case 18: return (x) ? BMC_LED_19_X : BMC_LED_19_Y;
#if defined(BMC_LED_20_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && BMC_MAX_LEDS > 19 && defined(BMC_LED_20_X) && defined(BMC_LED_20_Y)
  case 19: return (x) ? BMC_LED_20_X : BMC_LED_20_Y;
#if defined(BMC_LED_21_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && BMC_MAX_LEDS > 20 && defined(BMC_LED_21_X) && defined(BMC_LED_21_Y)
  case 20: return (x) ? BMC_LED_21_X : BMC_LED_21_Y;
#if defined(BMC_LED_22_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && BMC_MAX_LEDS > 21 && defined(BMC_LED_22_X) && defined(BMC_LED_22_Y)
  case 21: return (x) ? BMC_LED_22_X : BMC_LED_22_Y;
#if defined(BMC_LED_23_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && BMC_MAX_LEDS > 22 && defined(BMC_LED_23_X) && defined(BMC_LED_23_Y)
  case 22: return (x) ? BMC_LED_23_X : BMC_LED_23_Y;
#if defined(BMC_LED_24_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && BMC_MAX_LEDS > 23 && defined(BMC_LED_24_X) && defined(BMC_LED_24_Y)
  case 23: return (x) ? BMC_LED_24_X : BMC_LED_24_Y;
#if defined(BMC_LED_25_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && BMC_MAX_LEDS > 24 && defined(BMC_LED_25_X) && defined(BMC_LED_25_Y)
  case 24: return (x) ? BMC_LED_25_X : BMC_LED_25_Y;
#if defined(BMC_LED_26_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && BMC_MAX_LEDS > 25 && defined(BMC_LED_26_X) && defined(BMC_LED_26_Y)
  case 25: return (x) ? BMC_LED_26_X : BMC_LED_26_Y;
#if defined(BMC_LED_27_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && BMC_MAX_LEDS > 26 && defined(BMC_LED_27_X) && defined(BMC_LED_27_Y)
  case 26: return (x) ? BMC_LED_27_X : BMC_LED_27_Y;
#if defined(BMC_LED_28_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && BMC_MAX_LEDS > 27 && defined(BMC_LED_28_X) && defined(BMC_LED_28_Y)
  case 27: return (x) ? BMC_LED_28_X : BMC_LED_28_Y;
#if defined(BMC_LED_29_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && BMC_MAX_LEDS > 28 && defined(BMC_LED_29_X) && defined(BMC_LED_29_Y)
  case 28: return (x) ? BMC_LED_29_X : BMC_LED_29_Y;
#if defined(BMC_LED_30_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && BMC_MAX_LEDS > 29 && defined(BMC_LED_30_X) && defined(BMC_LED_30_Y)
  case 29: return (x) ? BMC_LED_30_X : BMC_LED_30_Y;
#if defined(BMC_LED_31_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && BMC_MAX_LEDS > 30 && defined(BMC_LED_31_X) && defined(BMC_LED_31_Y)
  case 30: return (x) ? BMC_LED_31_X : BMC_LED_31_Y;
#if defined(BMC_LED_32_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && BMC_MAX_LEDS > 31 && defined(BMC_LED_32_X) && defined(BMC_LED_32_Y)
  case 31: return (x) ? BMC_LED_32_X : BMC_LED_32_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getPotPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_POTS > 0
switch(index){
#if defined(BMC_POT_1_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=1 && BMC_MAX_POTS > 0 && defined(BMC_POT_1_X) && defined(BMC_POT_1_Y)
  case 0: return (x) ? BMC_POT_1_X : BMC_POT_1_Y;
#if defined(BMC_POT_2_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=2 && BMC_MAX_POTS > 1 && defined(BMC_POT_2_X) && defined(BMC_POT_2_Y)
  case 1: return (x) ? BMC_POT_2_X : BMC_POT_2_Y;
#if defined(BMC_POT_3_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=3 && BMC_MAX_POTS > 2 && defined(BMC_POT_3_X) && defined(BMC_POT_3_Y)
  case 2: return (x) ? BMC_POT_3_X : BMC_POT_3_Y;
#if defined(BMC_POT_4_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=4 && BMC_MAX_POTS > 3 && defined(BMC_POT_4_X) && defined(BMC_POT_4_Y)
  case 3: return (x) ? BMC_POT_4_X : BMC_POT_4_Y;
#if defined(BMC_POT_5_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=5 && BMC_MAX_POTS > 4 && defined(BMC_POT_5_X) && defined(BMC_POT_5_Y)
  case 4: return (x) ? BMC_POT_5_X : BMC_POT_5_Y;
#if defined(BMC_POT_6_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=6 && BMC_MAX_POTS > 5 && defined(BMC_POT_6_X) && defined(BMC_POT_6_Y)
  case 5: return (x) ? BMC_POT_6_X : BMC_POT_6_Y;
#if defined(BMC_POT_7_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=7 && BMC_MAX_POTS > 6 && defined(BMC_POT_7_X) && defined(BMC_POT_7_Y)
  case 6: return (x) ? BMC_POT_7_X : BMC_POT_7_Y;
#if defined(BMC_POT_8_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=8 && BMC_MAX_POTS > 7 && defined(BMC_POT_8_X) && defined(BMC_POT_8_Y)
  case 7: return (x) ? BMC_POT_8_X : BMC_POT_8_Y;
#if defined(BMC_POT_9_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=9 && BMC_MAX_POTS > 8 && defined(BMC_POT_9_X) && defined(BMC_POT_9_Y)
  case 8: return (x) ? BMC_POT_9_X : BMC_POT_9_Y;
#if defined(BMC_POT_10_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=10 && BMC_MAX_POTS > 9 && defined(BMC_POT_10_X) && defined(BMC_POT_10_Y)
  case 9: return (x) ? BMC_POT_10_X : BMC_POT_10_Y;
#if defined(BMC_POT_11_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=11 && BMC_MAX_POTS > 10 && defined(BMC_POT_11_X) && defined(BMC_POT_11_Y)
  case 10: return (x) ? BMC_POT_11_X : BMC_POT_11_Y;
#if defined(BMC_POT_12_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=12 && BMC_MAX_POTS > 11 && defined(BMC_POT_12_X) && defined(BMC_POT_12_Y)
  case 11: return (x) ? BMC_POT_12_X : BMC_POT_12_Y;
#if defined(BMC_POT_13_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=13 && BMC_MAX_POTS > 12 && defined(BMC_POT_13_X) && defined(BMC_POT_13_Y)
  case 12: return (x) ? BMC_POT_13_X : BMC_POT_13_Y;
#if defined(BMC_POT_14_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=14 && BMC_MAX_POTS > 13 && defined(BMC_POT_14_X) && defined(BMC_POT_14_Y)
  case 13: return (x) ? BMC_POT_14_X : BMC_POT_14_Y;
#if defined(BMC_POT_15_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=15 && BMC_MAX_POTS > 14 && defined(BMC_POT_15_X) && defined(BMC_POT_15_Y)
  case 14: return (x) ? BMC_POT_15_X : BMC_POT_15_Y;
#if defined(BMC_POT_16_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=16 && BMC_MAX_POTS > 15 && defined(BMC_POT_16_X) && defined(BMC_POT_16_Y)
  case 15: return (x) ? BMC_POT_16_X : BMC_POT_16_Y;
#if defined(BMC_POT_17_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=17 && BMC_MAX_POTS > 16 && defined(BMC_POT_17_X) && defined(BMC_POT_17_Y)
  case 16: return (x) ? BMC_POT_17_X : BMC_POT_17_Y;
#if defined(BMC_POT_18_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=18 && BMC_MAX_POTS > 17 && defined(BMC_POT_18_X) && defined(BMC_POT_18_Y)
  case 17: return (x) ? BMC_POT_18_X : BMC_POT_18_Y;
#if defined(BMC_POT_19_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=19 && BMC_MAX_POTS > 18 && defined(BMC_POT_19_X) && defined(BMC_POT_19_Y)
  case 18: return (x) ? BMC_POT_19_X : BMC_POT_19_Y;
#if defined(BMC_POT_20_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=20 && BMC_MAX_POTS > 19 && defined(BMC_POT_20_X) && defined(BMC_POT_20_Y)
  case 19: return (x) ? BMC_POT_20_X : BMC_POT_20_Y;
#if defined(BMC_POT_21_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=21 && BMC_MAX_POTS > 20 && defined(BMC_POT_21_X) && defined(BMC_POT_21_Y)
  case 20: return (x) ? BMC_POT_21_X : BMC_POT_21_Y;
#if defined(BMC_POT_22_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=22 && BMC_MAX_POTS > 21 && defined(BMC_POT_22_X) && defined(BMC_POT_22_Y)
  case 21: return (x) ? BMC_POT_22_X : BMC_POT_22_Y;
#if defined(BMC_POT_23_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=23 && BMC_MAX_POTS > 22 && defined(BMC_POT_23_X) && defined(BMC_POT_23_Y)
  case 22: return (x) ? BMC_POT_23_X : BMC_POT_23_Y;
#if defined(BMC_POT_24_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=24 && BMC_MAX_POTS > 23 && defined(BMC_POT_24_X) && defined(BMC_POT_24_Y)
  case 23: return (x) ? BMC_POT_24_X : BMC_POT_24_Y;
#if defined(BMC_POT_25_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=25 && BMC_MAX_POTS > 24 && defined(BMC_POT_25_X) && defined(BMC_POT_25_Y)
  case 24: return (x) ? BMC_POT_25_X : BMC_POT_25_Y;
#if defined(BMC_POT_26_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=26 && BMC_MAX_POTS > 25 && defined(BMC_POT_26_X) && defined(BMC_POT_26_Y)
  case 25: return (x) ? BMC_POT_26_X : BMC_POT_26_Y;
#if defined(BMC_POT_27_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=27 && BMC_MAX_POTS > 26 && defined(BMC_POT_27_X) && defined(BMC_POT_27_Y)
  case 26: return (x) ? BMC_POT_27_X : BMC_POT_27_Y;
#if defined(BMC_POT_28_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=28 && BMC_MAX_POTS > 27 && defined(BMC_POT_28_X) && defined(BMC_POT_28_Y)
  case 27: return (x) ? BMC_POT_28_X : BMC_POT_28_Y;
#if defined(BMC_POT_29_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=29 && BMC_MAX_POTS > 28 && defined(BMC_POT_29_X) && defined(BMC_POT_29_Y)
  case 28: return (x) ? BMC_POT_29_X : BMC_POT_29_Y;
#if defined(BMC_POT_30_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=30 && BMC_MAX_POTS > 29 && defined(BMC_POT_30_X) && defined(BMC_POT_30_Y)
  case 29: return (x) ? BMC_POT_30_X : BMC_POT_30_Y;
#if defined(BMC_POT_31_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=31 && BMC_MAX_POTS > 30 && defined(BMC_POT_31_X) && defined(BMC_POT_31_Y)
  case 30: return (x) ? BMC_POT_31_X : BMC_POT_31_Y;
#if defined(BMC_POT_32_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=32 && BMC_MAX_POTS > 31 && defined(BMC_POT_32_X) && defined(BMC_POT_32_Y)
  case 31: return (x) ? BMC_POT_32_X : BMC_POT_32_Y;
#if defined(BMC_POT_33_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=33 && BMC_MAX_POTS > 32 && defined(BMC_POT_33_X) && defined(BMC_POT_33_Y)
  case 32: return (x) ? BMC_POT_33_X : BMC_POT_33_Y;
#if defined(BMC_POT_34_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=34 && BMC_MAX_POTS > 33 && defined(BMC_POT_34_X) && defined(BMC_POT_34_Y)
  case 33: return (x) ? BMC_POT_34_X : BMC_POT_34_Y;
#if defined(BMC_POT_35_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=35 && BMC_MAX_POTS > 34 && defined(BMC_POT_35_X) && defined(BMC_POT_35_Y)
  case 34: return (x) ? BMC_POT_35_X : BMC_POT_35_Y;
#if defined(BMC_POT_36_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=36 && BMC_MAX_POTS > 35 && defined(BMC_POT_36_X) && defined(BMC_POT_36_Y)
  case 35: return (x) ? BMC_POT_36_X : BMC_POT_36_Y;
#if defined(BMC_POT_37_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=37 && BMC_MAX_POTS > 36 && defined(BMC_POT_37_X) && defined(BMC_POT_37_Y)
  case 36: return (x) ? BMC_POT_37_X : BMC_POT_37_Y;
#if defined(BMC_POT_38_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=38 && BMC_MAX_POTS > 37 && defined(BMC_POT_38_X) && defined(BMC_POT_38_Y)
  case 37: return (x) ? BMC_POT_38_X : BMC_POT_38_Y;
#if defined(BMC_POT_39_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=39 && BMC_MAX_POTS > 38 && defined(BMC_POT_39_X) && defined(BMC_POT_39_Y)
  case 38: return (x) ? BMC_POT_39_X : BMC_POT_39_Y;
#if defined(BMC_POT_40_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=40 && BMC_MAX_POTS > 39 && defined(BMC_POT_40_X) && defined(BMC_POT_40_Y)
  case 39: return (x) ? BMC_POT_40_X : BMC_POT_40_Y;
#if defined(BMC_POT_41_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=41 && BMC_MAX_POTS > 40 && defined(BMC_POT_41_X) && defined(BMC_POT_41_Y)
  case 40: return (x) ? BMC_POT_41_X : BMC_POT_41_Y;
#if defined(BMC_POT_42_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=42 && BMC_MAX_POTS > 41 && defined(BMC_POT_42_X) && defined(BMC_POT_42_Y)
  case 41: return (x) ? BMC_POT_42_X : BMC_POT_42_Y;
#if defined(BMC_POT_43_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=43 && BMC_MAX_POTS > 42 && defined(BMC_POT_43_X) && defined(BMC_POT_43_Y)
  case 42: return (x) ? BMC_POT_43_X : BMC_POT_43_Y;
#if defined(BMC_POT_44_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=44 && BMC_MAX_POTS > 43 && defined(BMC_POT_44_X) && defined(BMC_POT_44_Y)
  case 43: return (x) ? BMC_POT_44_X : BMC_POT_44_Y;
#if defined(BMC_POT_45_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=45 && BMC_MAX_POTS > 44 && defined(BMC_POT_45_X) && defined(BMC_POT_45_Y)
  case 44: return (x) ? BMC_POT_45_X : BMC_POT_45_Y;
#if defined(BMC_POT_46_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=46 && BMC_MAX_POTS > 45 && defined(BMC_POT_46_X) && defined(BMC_POT_46_Y)
  case 45: return (x) ? BMC_POT_46_X : BMC_POT_46_Y;
#if defined(BMC_POT_47_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=47 && BMC_MAX_POTS > 46 && defined(BMC_POT_47_X) && defined(BMC_POT_47_Y)
  case 46: return (x) ? BMC_POT_47_X : BMC_POT_47_Y;
#if defined(BMC_POT_48_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=48 && BMC_MAX_POTS > 47 && defined(BMC_POT_48_X) && defined(BMC_POT_48_Y)
  case 47: return (x) ? BMC_POT_48_X : BMC_POT_48_Y;
#if defined(BMC_POT_49_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=49 && BMC_MAX_POTS > 48 && defined(BMC_POT_49_X) && defined(BMC_POT_49_Y)
  case 48: return (x) ? BMC_POT_49_X : BMC_POT_49_Y;
#if defined(BMC_POT_50_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=50 && BMC_MAX_POTS > 49 && defined(BMC_POT_50_X) && defined(BMC_POT_50_Y)
  case 49: return (x) ? BMC_POT_50_X : BMC_POT_50_Y;
#if defined(BMC_POT_51_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=51 && BMC_MAX_POTS > 50 && defined(BMC_POT_51_X) && defined(BMC_POT_51_Y)
  case 50: return (x) ? BMC_POT_51_X : BMC_POT_51_Y;
#if defined(BMC_POT_52_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=52 && BMC_MAX_POTS > 51 && defined(BMC_POT_52_X) && defined(BMC_POT_52_Y)
  case 51: return (x) ? BMC_POT_52_X : BMC_POT_52_Y;
#if defined(BMC_POT_53_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=53 && BMC_MAX_POTS > 52 && defined(BMC_POT_53_X) && defined(BMC_POT_53_Y)
  case 52: return (x) ? BMC_POT_53_X : BMC_POT_53_Y;
#if defined(BMC_POT_54_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=54 && BMC_MAX_POTS > 53 && defined(BMC_POT_54_X) && defined(BMC_POT_54_Y)
  case 53: return (x) ? BMC_POT_54_X : BMC_POT_54_Y;
#if defined(BMC_POT_55_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=55 && BMC_MAX_POTS > 54 && defined(BMC_POT_55_X) && defined(BMC_POT_55_Y)
  case 54: return (x) ? BMC_POT_55_X : BMC_POT_55_Y;
#if defined(BMC_POT_56_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=56 && BMC_MAX_POTS > 55 && defined(BMC_POT_56_X) && defined(BMC_POT_56_Y)
  case 55: return (x) ? BMC_POT_56_X : BMC_POT_56_Y;
#if defined(BMC_POT_57_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=57 && BMC_MAX_POTS > 56 && defined(BMC_POT_57_X) && defined(BMC_POT_57_Y)
  case 56: return (x) ? BMC_POT_57_X : BMC_POT_57_Y;
#if defined(BMC_POT_58_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=58 && BMC_MAX_POTS > 57 && defined(BMC_POT_58_X) && defined(BMC_POT_58_Y)
  case 57: return (x) ? BMC_POT_58_X : BMC_POT_58_Y;
#if defined(BMC_POT_59_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=59 && BMC_MAX_POTS > 58 && defined(BMC_POT_59_X) && defined(BMC_POT_59_Y)
  case 58: return (x) ? BMC_POT_59_X : BMC_POT_59_Y;
#if defined(BMC_POT_60_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=60 && BMC_MAX_POTS > 59 && defined(BMC_POT_60_X) && defined(BMC_POT_60_Y)
  case 59: return (x) ? BMC_POT_60_X : BMC_POT_60_Y;
#if defined(BMC_POT_61_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=61 && BMC_MAX_POTS > 60 && defined(BMC_POT_61_X) && defined(BMC_POT_61_Y)
  case 60: return (x) ? BMC_POT_61_X : BMC_POT_61_Y;
#if defined(BMC_POT_62_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=62 && BMC_MAX_POTS > 61 && defined(BMC_POT_62_X) && defined(BMC_POT_62_Y)
  case 61: return (x) ? BMC_POT_62_X : BMC_POT_62_Y;
#if defined(BMC_POT_63_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=63 && BMC_MAX_POTS > 62 && defined(BMC_POT_63_X) && defined(BMC_POT_63_Y)
  case 62: return (x) ? BMC_POT_63_X : BMC_POT_63_Y;
#if defined(BMC_POT_64_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=64 && BMC_MAX_POTS > 63 && defined(BMC_POT_64_X) && defined(BMC_POT_64_Y)
  case 63: return (x) ? BMC_POT_64_X : BMC_POT_64_Y;
#if defined(BMC_POT_65_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=65 && BMC_MAX_POTS > 64 && defined(BMC_POT_65_X) && defined(BMC_POT_65_Y)
  case 64: return (x) ? BMC_POT_65_X : BMC_POT_65_Y;
#if defined(BMC_POT_66_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=66 && BMC_MAX_POTS > 65 && defined(BMC_POT_66_X) && defined(BMC_POT_66_Y)
  case 65: return (x) ? BMC_POT_66_X : BMC_POT_66_Y;
#if defined(BMC_POT_67_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=67 && BMC_MAX_POTS > 66 && defined(BMC_POT_67_X) && defined(BMC_POT_67_Y)
  case 66: return (x) ? BMC_POT_67_X : BMC_POT_67_Y;
#if defined(BMC_POT_68_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=68 && BMC_MAX_POTS > 67 && defined(BMC_POT_68_X) && defined(BMC_POT_68_Y)
  case 67: return (x) ? BMC_POT_68_X : BMC_POT_68_Y;
#if defined(BMC_POT_69_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=69 && BMC_MAX_POTS > 68 && defined(BMC_POT_69_X) && defined(BMC_POT_69_Y)
  case 68: return (x) ? BMC_POT_69_X : BMC_POT_69_Y;
#if defined(BMC_POT_70_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=70 && BMC_MAX_POTS > 69 && defined(BMC_POT_70_X) && defined(BMC_POT_70_Y)
  case 69: return (x) ? BMC_POT_70_X : BMC_POT_70_Y;
#if defined(BMC_POT_71_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=71 && BMC_MAX_POTS > 70 && defined(BMC_POT_71_X) && defined(BMC_POT_71_Y)
  case 70: return (x) ? BMC_POT_71_X : BMC_POT_71_Y;
#if defined(BMC_POT_72_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=72 && BMC_MAX_POTS > 71 && defined(BMC_POT_72_X) && defined(BMC_POT_72_Y)
  case 71: return (x) ? BMC_POT_72_X : BMC_POT_72_Y;
#if defined(BMC_POT_73_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=73 && BMC_MAX_POTS > 72 && defined(BMC_POT_73_X) && defined(BMC_POT_73_Y)
  case 72: return (x) ? BMC_POT_73_X : BMC_POT_73_Y;
#if defined(BMC_POT_74_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=74 && BMC_MAX_POTS > 73 && defined(BMC_POT_74_X) && defined(BMC_POT_74_Y)
  case 73: return (x) ? BMC_POT_74_X : BMC_POT_74_Y;
#if defined(BMC_POT_75_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=75 && BMC_MAX_POTS > 74 && defined(BMC_POT_75_X) && defined(BMC_POT_75_Y)
  case 74: return (x) ? BMC_POT_75_X : BMC_POT_75_Y;
#if defined(BMC_POT_76_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=76 && BMC_MAX_POTS > 75 && defined(BMC_POT_76_X) && defined(BMC_POT_76_Y)
  case 75: return (x) ? BMC_POT_76_X : BMC_POT_76_Y;
#if defined(BMC_POT_77_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=77 && BMC_MAX_POTS > 76 && defined(BMC_POT_77_X) && defined(BMC_POT_77_Y)
  case 76: return (x) ? BMC_POT_77_X : BMC_POT_77_Y;
#if defined(BMC_POT_78_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=78 && BMC_MAX_POTS > 77 && defined(BMC_POT_78_X) && defined(BMC_POT_78_Y)
  case 77: return (x) ? BMC_POT_78_X : BMC_POT_78_Y;
#if defined(BMC_POT_79_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=79 && BMC_MAX_POTS > 78 && defined(BMC_POT_79_X) && defined(BMC_POT_79_Y)
  case 78: return (x) ? BMC_POT_79_X : BMC_POT_79_Y;
#if defined(BMC_POT_80_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=80 && BMC_MAX_POTS > 79 && defined(BMC_POT_80_X) && defined(BMC_POT_80_Y)
  case 79: return (x) ? BMC_POT_80_X : BMC_POT_80_Y;
#if defined(BMC_POT_81_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=81 && BMC_MAX_POTS > 80 && defined(BMC_POT_81_X) && defined(BMC_POT_81_Y)
  case 80: return (x) ? BMC_POT_81_X : BMC_POT_81_Y;
#if defined(BMC_POT_82_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=82 && BMC_MAX_POTS > 81 && defined(BMC_POT_82_X) && defined(BMC_POT_82_Y)
  case 81: return (x) ? BMC_POT_82_X : BMC_POT_82_Y;
#if defined(BMC_POT_83_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=83 && BMC_MAX_POTS > 82 && defined(BMC_POT_83_X) && defined(BMC_POT_83_Y)
  case 82: return (x) ? BMC_POT_83_X : BMC_POT_83_Y;
#if defined(BMC_POT_84_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=84 && BMC_MAX_POTS > 83 && defined(BMC_POT_84_X) && defined(BMC_POT_84_Y)
  case 83: return (x) ? BMC_POT_84_X : BMC_POT_84_Y;
#if defined(BMC_POT_85_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=85 && BMC_MAX_POTS > 84 && defined(BMC_POT_85_X) && defined(BMC_POT_85_Y)
  case 84: return (x) ? BMC_POT_85_X : BMC_POT_85_Y;
#if defined(BMC_POT_86_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=86 && BMC_MAX_POTS > 85 && defined(BMC_POT_86_X) && defined(BMC_POT_86_Y)
  case 85: return (x) ? BMC_POT_86_X : BMC_POT_86_Y;
#if defined(BMC_POT_87_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=87 && BMC_MAX_POTS > 86 && defined(BMC_POT_87_X) && defined(BMC_POT_87_Y)
  case 86: return (x) ? BMC_POT_87_X : BMC_POT_87_Y;
#if defined(BMC_POT_88_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=88 && BMC_MAX_POTS > 87 && defined(BMC_POT_88_X) && defined(BMC_POT_88_Y)
  case 87: return (x) ? BMC_POT_88_X : BMC_POT_88_Y;
#if defined(BMC_POT_89_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=89 && BMC_MAX_POTS > 88 && defined(BMC_POT_89_X) && defined(BMC_POT_89_Y)
  case 88: return (x) ? BMC_POT_89_X : BMC_POT_89_Y;
#if defined(BMC_POT_90_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=90 && BMC_MAX_POTS > 89 && defined(BMC_POT_90_X) && defined(BMC_POT_90_Y)
  case 89: return (x) ? BMC_POT_90_X : BMC_POT_90_Y;
#if defined(BMC_POT_91_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=91 && BMC_MAX_POTS > 90 && defined(BMC_POT_91_X) && defined(BMC_POT_91_Y)
  case 90: return (x) ? BMC_POT_91_X : BMC_POT_91_Y;
#if defined(BMC_POT_92_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=92 && BMC_MAX_POTS > 91 && defined(BMC_POT_92_X) && defined(BMC_POT_92_Y)
  case 91: return (x) ? BMC_POT_92_X : BMC_POT_92_Y;
#if defined(BMC_POT_93_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=93 && BMC_MAX_POTS > 92 && defined(BMC_POT_93_X) && defined(BMC_POT_93_Y)
  case 92: return (x) ? BMC_POT_93_X : BMC_POT_93_Y;
#if defined(BMC_POT_94_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=94 && BMC_MAX_POTS > 93 && defined(BMC_POT_94_X) && defined(BMC_POT_94_Y)
  case 93: return (x) ? BMC_POT_94_X : BMC_POT_94_Y;
#if defined(BMC_POT_95_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=95 && BMC_MAX_POTS > 94 && defined(BMC_POT_95_X) && defined(BMC_POT_95_Y)
  case 94: return (x) ? BMC_POT_95_X : BMC_POT_95_Y;
#if defined(BMC_POT_96_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=96 && BMC_MAX_POTS > 95 && defined(BMC_POT_96_X) && defined(BMC_POT_96_Y)
  case 95: return (x) ? BMC_POT_96_X : BMC_POT_96_Y;
#if defined(BMC_POT_97_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=97 && BMC_MAX_POTS > 96 && defined(BMC_POT_97_X) && defined(BMC_POT_97_Y)
  case 96: return (x) ? BMC_POT_97_X : BMC_POT_97_Y;
#if defined(BMC_POT_98_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=98 && BMC_MAX_POTS > 97 && defined(BMC_POT_98_X) && defined(BMC_POT_98_Y)
  case 97: return (x) ? BMC_POT_98_X : BMC_POT_98_Y;
#if defined(BMC_POT_99_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=99 && BMC_MAX_POTS > 98 && defined(BMC_POT_99_X) && defined(BMC_POT_99_Y)
  case 98: return (x) ? BMC_POT_99_X : BMC_POT_99_Y;
#if defined(BMC_POT_100_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=100 && BMC_MAX_POTS > 99 && defined(BMC_POT_100_X) && defined(BMC_POT_100_Y)
  case 99: return (x) ? BMC_POT_100_X : BMC_POT_100_Y;
#if defined(BMC_POT_101_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=101 && BMC_MAX_POTS > 100 && defined(BMC_POT_101_X) && defined(BMC_POT_101_Y)
  case 100: return (x) ? BMC_POT_101_X : BMC_POT_101_Y;
#if defined(BMC_POT_102_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=102 && BMC_MAX_POTS > 101 && defined(BMC_POT_102_X) && defined(BMC_POT_102_Y)
  case 101: return (x) ? BMC_POT_102_X : BMC_POT_102_Y;
#if defined(BMC_POT_103_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=103 && BMC_MAX_POTS > 102 && defined(BMC_POT_103_X) && defined(BMC_POT_103_Y)
  case 102: return (x) ? BMC_POT_103_X : BMC_POT_103_Y;
#if defined(BMC_POT_104_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=104 && BMC_MAX_POTS > 103 && defined(BMC_POT_104_X) && defined(BMC_POT_104_Y)
  case 103: return (x) ? BMC_POT_104_X : BMC_POT_104_Y;
#if defined(BMC_POT_105_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=105 && BMC_MAX_POTS > 104 && defined(BMC_POT_105_X) && defined(BMC_POT_105_Y)
  case 104: return (x) ? BMC_POT_105_X : BMC_POT_105_Y;
#if defined(BMC_POT_106_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=106 && BMC_MAX_POTS > 105 && defined(BMC_POT_106_X) && defined(BMC_POT_106_Y)
  case 105: return (x) ? BMC_POT_106_X : BMC_POT_106_Y;
#if defined(BMC_POT_107_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=107 && BMC_MAX_POTS > 106 && defined(BMC_POT_107_X) && defined(BMC_POT_107_Y)
  case 106: return (x) ? BMC_POT_107_X : BMC_POT_107_Y;
#if defined(BMC_POT_108_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=108 && BMC_MAX_POTS > 107 && defined(BMC_POT_108_X) && defined(BMC_POT_108_Y)
  case 107: return (x) ? BMC_POT_108_X : BMC_POT_108_Y;
#if defined(BMC_POT_109_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=109 && BMC_MAX_POTS > 108 && defined(BMC_POT_109_X) && defined(BMC_POT_109_Y)
  case 108: return (x) ? BMC_POT_109_X : BMC_POT_109_Y;
#if defined(BMC_POT_110_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=110 && BMC_MAX_POTS > 109 && defined(BMC_POT_110_X) && defined(BMC_POT_110_Y)
  case 109: return (x) ? BMC_POT_110_X : BMC_POT_110_Y;
#if defined(BMC_POT_111_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=111 && BMC_MAX_POTS > 110 && defined(BMC_POT_111_X) && defined(BMC_POT_111_Y)
  case 110: return (x) ? BMC_POT_111_X : BMC_POT_111_Y;
#if defined(BMC_POT_112_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=112 && BMC_MAX_POTS > 111 && defined(BMC_POT_112_X) && defined(BMC_POT_112_Y)
  case 111: return (x) ? BMC_POT_112_X : BMC_POT_112_Y;
#if defined(BMC_POT_113_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=113 && BMC_MAX_POTS > 112 && defined(BMC_POT_113_X) && defined(BMC_POT_113_Y)
  case 112: return (x) ? BMC_POT_113_X : BMC_POT_113_Y;
#if defined(BMC_POT_114_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=114 && BMC_MAX_POTS > 113 && defined(BMC_POT_114_X) && defined(BMC_POT_114_Y)
  case 113: return (x) ? BMC_POT_114_X : BMC_POT_114_Y;
#if defined(BMC_POT_115_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=115 && BMC_MAX_POTS > 114 && defined(BMC_POT_115_X) && defined(BMC_POT_115_Y)
  case 114: return (x) ? BMC_POT_115_X : BMC_POT_115_Y;
#if defined(BMC_POT_116_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=116 && BMC_MAX_POTS > 115 && defined(BMC_POT_116_X) && defined(BMC_POT_116_Y)
  case 115: return (x) ? BMC_POT_116_X : BMC_POT_116_Y;
#if defined(BMC_POT_117_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=117 && BMC_MAX_POTS > 116 && defined(BMC_POT_117_X) && defined(BMC_POT_117_Y)
  case 116: return (x) ? BMC_POT_117_X : BMC_POT_117_Y;
#if defined(BMC_POT_118_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=118 && BMC_MAX_POTS > 117 && defined(BMC_POT_118_X) && defined(BMC_POT_118_Y)
  case 117: return (x) ? BMC_POT_118_X : BMC_POT_118_Y;
#if defined(BMC_POT_119_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=119 && BMC_MAX_POTS > 118 && defined(BMC_POT_119_X) && defined(BMC_POT_119_Y)
  case 118: return (x) ? BMC_POT_119_X : BMC_POT_119_Y;
#if defined(BMC_POT_120_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=120 && BMC_MAX_POTS > 119 && defined(BMC_POT_120_X) && defined(BMC_POT_120_Y)
  case 119: return (x) ? BMC_POT_120_X : BMC_POT_120_Y;
#if defined(BMC_POT_121_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=121 && BMC_MAX_POTS > 120 && defined(BMC_POT_121_X) && defined(BMC_POT_121_Y)
  case 120: return (x) ? BMC_POT_121_X : BMC_POT_121_Y;
#if defined(BMC_POT_122_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=122 && BMC_MAX_POTS > 121 && defined(BMC_POT_122_X) && defined(BMC_POT_122_Y)
  case 121: return (x) ? BMC_POT_122_X : BMC_POT_122_Y;
#if defined(BMC_POT_123_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=123 && BMC_MAX_POTS > 122 && defined(BMC_POT_123_X) && defined(BMC_POT_123_Y)
  case 122: return (x) ? BMC_POT_123_X : BMC_POT_123_Y;
#if defined(BMC_POT_124_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=124 && BMC_MAX_POTS > 123 && defined(BMC_POT_124_X) && defined(BMC_POT_124_Y)
  case 123: return (x) ? BMC_POT_124_X : BMC_POT_124_Y;
#if defined(BMC_POT_125_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=125 && BMC_MAX_POTS > 124 && defined(BMC_POT_125_X) && defined(BMC_POT_125_Y)
  case 124: return (x) ? BMC_POT_125_X : BMC_POT_125_Y;
#if defined(BMC_POT_126_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=126 && BMC_MAX_POTS > 125 && defined(BMC_POT_126_X) && defined(BMC_POT_126_Y)
  case 125: return (x) ? BMC_POT_126_X : BMC_POT_126_Y;
#if defined(BMC_POT_127_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=127 && BMC_MAX_POTS > 126 && defined(BMC_POT_127_X) && defined(BMC_POT_127_Y)
  case 126: return (x) ? BMC_POT_127_X : BMC_POT_127_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getEncoderPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_ENCODERS > 0
switch(index){
#if defined(BMC_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_ENCODER_1B_PIN) && BMC_MAX_ENCODERS > 0 && defined(BMC_ENCODER_1_X) && defined(BMC_ENCODER_1_Y)
  case 0: return (x) ? BMC_ENCODER_1_X : BMC_ENCODER_1_Y;
#if defined(BMC_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_ENCODER_2B_PIN) && BMC_MAX_ENCODERS > 1 && defined(BMC_ENCODER_2_X) && defined(BMC_ENCODER_2_Y)
  case 1: return (x) ? BMC_ENCODER_2_X : BMC_ENCODER_2_Y;
#if defined(BMC_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_ENCODER_3B_PIN) && BMC_MAX_ENCODERS > 2 && defined(BMC_ENCODER_3_X) && defined(BMC_ENCODER_3_Y)
  case 2: return (x) ? BMC_ENCODER_3_X : BMC_ENCODER_3_Y;
#if defined(BMC_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_ENCODER_4B_PIN) && BMC_MAX_ENCODERS > 3 && defined(BMC_ENCODER_4_X) && defined(BMC_ENCODER_4_Y)
  case 3: return (x) ? BMC_ENCODER_4_X : BMC_ENCODER_4_Y;
#if defined(BMC_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_ENCODER_5B_PIN) && BMC_MAX_ENCODERS > 4 && defined(BMC_ENCODER_5_X) && defined(BMC_ENCODER_5_Y)
  case 4: return (x) ? BMC_ENCODER_5_X : BMC_ENCODER_5_Y;
#if defined(BMC_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_ENCODER_6B_PIN) && BMC_MAX_ENCODERS > 5 && defined(BMC_ENCODER_6_X) && defined(BMC_ENCODER_6_Y)
  case 5: return (x) ? BMC_ENCODER_6_X : BMC_ENCODER_6_Y;
#if defined(BMC_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_ENCODER_7B_PIN) && BMC_MAX_ENCODERS > 6 && defined(BMC_ENCODER_7_X) && defined(BMC_ENCODER_7_Y)
  case 6: return (x) ? BMC_ENCODER_7_X : BMC_ENCODER_7_Y;
#if defined(BMC_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_ENCODER_8B_PIN) && BMC_MAX_ENCODERS > 7 && defined(BMC_ENCODER_8_X) && defined(BMC_ENCODER_8_Y)
  case 7: return (x) ? BMC_ENCODER_8_X : BMC_ENCODER_8_Y;
#if defined(BMC_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_ENCODER_9B_PIN) && BMC_MAX_ENCODERS > 8 && defined(BMC_ENCODER_9_X) && defined(BMC_ENCODER_9_Y)
  case 8: return (x) ? BMC_ENCODER_9_X : BMC_ENCODER_9_Y;
#if defined(BMC_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_ENCODER_10B_PIN) && BMC_MAX_ENCODERS > 9 && defined(BMC_ENCODER_10_X) && defined(BMC_ENCODER_10_Y)
  case 9: return (x) ? BMC_ENCODER_10_X : BMC_ENCODER_10_Y;
#if defined(BMC_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_ENCODER_11B_PIN) && BMC_MAX_ENCODERS > 10 && defined(BMC_ENCODER_11_X) && defined(BMC_ENCODER_11_Y)
  case 10: return (x) ? BMC_ENCODER_11_X : BMC_ENCODER_11_Y;
#if defined(BMC_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_ENCODER_12B_PIN) && BMC_MAX_ENCODERS > 11 && defined(BMC_ENCODER_12_X) && defined(BMC_ENCODER_12_Y)
  case 11: return (x) ? BMC_ENCODER_12_X : BMC_ENCODER_12_Y;
#if defined(BMC_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_ENCODER_13B_PIN) && BMC_MAX_ENCODERS > 12 && defined(BMC_ENCODER_13_X) && defined(BMC_ENCODER_13_Y)
  case 12: return (x) ? BMC_ENCODER_13_X : BMC_ENCODER_13_Y;
#if defined(BMC_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_ENCODER_14B_PIN) && BMC_MAX_ENCODERS > 13 && defined(BMC_ENCODER_14_X) && defined(BMC_ENCODER_14_Y)
  case 13: return (x) ? BMC_ENCODER_14_X : BMC_ENCODER_14_Y;
#if defined(BMC_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_ENCODER_15B_PIN) && BMC_MAX_ENCODERS > 14 && defined(BMC_ENCODER_15_X) && defined(BMC_ENCODER_15_Y)
  case 14: return (x) ? BMC_ENCODER_15_X : BMC_ENCODER_15_Y;
#if defined(BMC_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_ENCODER_16B_PIN) && BMC_MAX_ENCODERS > 15 && defined(BMC_ENCODER_16_X) && defined(BMC_ENCODER_16_Y)
  case 15: return (x) ? BMC_ENCODER_16_X : BMC_ENCODER_16_Y;
#if defined(BMC_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_ENCODER_17B_PIN) && BMC_MAX_ENCODERS > 16 && defined(BMC_ENCODER_17_X) && defined(BMC_ENCODER_17_Y)
  case 16: return (x) ? BMC_ENCODER_17_X : BMC_ENCODER_17_Y;
#if defined(BMC_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_ENCODER_18B_PIN) && BMC_MAX_ENCODERS > 17 && defined(BMC_ENCODER_18_X) && defined(BMC_ENCODER_18_Y)
  case 17: return (x) ? BMC_ENCODER_18_X : BMC_ENCODER_18_Y;
#if defined(BMC_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_ENCODER_19B_PIN) && BMC_MAX_ENCODERS > 18 && defined(BMC_ENCODER_19_X) && defined(BMC_ENCODER_19_Y)
  case 18: return (x) ? BMC_ENCODER_19_X : BMC_ENCODER_19_Y;
#if defined(BMC_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_ENCODER_20B_PIN) && BMC_MAX_ENCODERS > 19 && defined(BMC_ENCODER_20_X) && defined(BMC_ENCODER_20_Y)
  case 19: return (x) ? BMC_ENCODER_20_X : BMC_ENCODER_20_Y;
#if defined(BMC_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_ENCODER_21B_PIN) && BMC_MAX_ENCODERS > 20 && defined(BMC_ENCODER_21_X) && defined(BMC_ENCODER_21_Y)
  case 20: return (x) ? BMC_ENCODER_21_X : BMC_ENCODER_21_Y;
#if defined(BMC_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_ENCODER_22B_PIN) && BMC_MAX_ENCODERS > 21 && defined(BMC_ENCODER_22_X) && defined(BMC_ENCODER_22_Y)
  case 21: return (x) ? BMC_ENCODER_22_X : BMC_ENCODER_22_Y;
#if defined(BMC_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_ENCODER_23B_PIN) && BMC_MAX_ENCODERS > 22 && defined(BMC_ENCODER_23_X) && defined(BMC_ENCODER_23_Y)
  case 22: return (x) ? BMC_ENCODER_23_X : BMC_ENCODER_23_Y;
#if defined(BMC_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_ENCODER_24B_PIN) && BMC_MAX_ENCODERS > 23 && defined(BMC_ENCODER_24_X) && defined(BMC_ENCODER_24_Y)
  case 23: return (x) ? BMC_ENCODER_24_X : BMC_ENCODER_24_Y;
#if defined(BMC_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_ENCODER_25B_PIN) && BMC_MAX_ENCODERS > 24 && defined(BMC_ENCODER_25_X) && defined(BMC_ENCODER_25_Y)
  case 24: return (x) ? BMC_ENCODER_25_X : BMC_ENCODER_25_Y;
#if defined(BMC_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_ENCODER_26B_PIN) && BMC_MAX_ENCODERS > 25 && defined(BMC_ENCODER_26_X) && defined(BMC_ENCODER_26_Y)
  case 25: return (x) ? BMC_ENCODER_26_X : BMC_ENCODER_26_Y;
#if defined(BMC_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_ENCODER_27B_PIN) && BMC_MAX_ENCODERS > 26 && defined(BMC_ENCODER_27_X) && defined(BMC_ENCODER_27_Y)
  case 26: return (x) ? BMC_ENCODER_27_X : BMC_ENCODER_27_Y;
#if defined(BMC_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_ENCODER_28B_PIN) && BMC_MAX_ENCODERS > 27 && defined(BMC_ENCODER_28_X) && defined(BMC_ENCODER_28_Y)
  case 27: return (x) ? BMC_ENCODER_28_X : BMC_ENCODER_28_Y;
#if defined(BMC_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_ENCODER_29B_PIN) && BMC_MAX_ENCODERS > 28 && defined(BMC_ENCODER_29_X) && defined(BMC_ENCODER_29_Y)
  case 28: return (x) ? BMC_ENCODER_29_X : BMC_ENCODER_29_Y;
#if defined(BMC_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_ENCODER_30B_PIN) && BMC_MAX_ENCODERS > 29 && defined(BMC_ENCODER_30_X) && defined(BMC_ENCODER_30_Y)
  case 29: return (x) ? BMC_ENCODER_30_X : BMC_ENCODER_30_Y;
#if defined(BMC_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_ENCODER_31B_PIN) && BMC_MAX_ENCODERS > 30 && defined(BMC_ENCODER_31_X) && defined(BMC_ENCODER_31_Y)
  case 30: return (x) ? BMC_ENCODER_31_X : BMC_ENCODER_31_Y;
#if defined(BMC_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_ENCODER_32B_PIN) && BMC_MAX_ENCODERS > 31 && defined(BMC_ENCODER_32_X) && defined(BMC_ENCODER_32_Y)
  case 31: return (x) ? BMC_ENCODER_32_X : BMC_ENCODER_32_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getPwmLedPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_PWM_LEDS > 0
switch(index){
#if defined(BMC_PWM_LED_1_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=1 && BMC_MAX_PWM_LEDS > 0 && defined(BMC_PWM_LED_1_X) && defined(BMC_PWM_LED_1_Y)
  case 0: return (x) ? BMC_PWM_LED_1_X : BMC_PWM_LED_1_Y;
#if defined(BMC_PWM_LED_2_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=2 && BMC_MAX_PWM_LEDS > 1 && defined(BMC_PWM_LED_2_X) && defined(BMC_PWM_LED_2_Y)
  case 1: return (x) ? BMC_PWM_LED_2_X : BMC_PWM_LED_2_Y;
#if defined(BMC_PWM_LED_3_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=3 && BMC_MAX_PWM_LEDS > 2 && defined(BMC_PWM_LED_3_X) && defined(BMC_PWM_LED_3_Y)
  case 2: return (x) ? BMC_PWM_LED_3_X : BMC_PWM_LED_3_Y;
#if defined(BMC_PWM_LED_4_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=4 && BMC_MAX_PWM_LEDS > 3 && defined(BMC_PWM_LED_4_X) && defined(BMC_PWM_LED_4_Y)
  case 3: return (x) ? BMC_PWM_LED_4_X : BMC_PWM_LED_4_Y;
#if defined(BMC_PWM_LED_5_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=5 && BMC_MAX_PWM_LEDS > 4 && defined(BMC_PWM_LED_5_X) && defined(BMC_PWM_LED_5_Y)
  case 4: return (x) ? BMC_PWM_LED_5_X : BMC_PWM_LED_5_Y;
#if defined(BMC_PWM_LED_6_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=6 && BMC_MAX_PWM_LEDS > 5 && defined(BMC_PWM_LED_6_X) && defined(BMC_PWM_LED_6_Y)
  case 5: return (x) ? BMC_PWM_LED_6_X : BMC_PWM_LED_6_Y;
#if defined(BMC_PWM_LED_7_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=7 && BMC_MAX_PWM_LEDS > 6 && defined(BMC_PWM_LED_7_X) && defined(BMC_PWM_LED_7_Y)
  case 6: return (x) ? BMC_PWM_LED_7_X : BMC_PWM_LED_7_Y;
#if defined(BMC_PWM_LED_8_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=8 && BMC_MAX_PWM_LEDS > 7 && defined(BMC_PWM_LED_8_X) && defined(BMC_PWM_LED_8_Y)
  case 7: return (x) ? BMC_PWM_LED_8_X : BMC_PWM_LED_8_Y;
#if defined(BMC_PWM_LED_9_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=9 && BMC_MAX_PWM_LEDS > 8 && defined(BMC_PWM_LED_9_X) && defined(BMC_PWM_LED_9_Y)
  case 8: return (x) ? BMC_PWM_LED_9_X : BMC_PWM_LED_9_Y;
#if defined(BMC_PWM_LED_10_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=10 && BMC_MAX_PWM_LEDS > 9 && defined(BMC_PWM_LED_10_X) && defined(BMC_PWM_LED_10_Y)
  case 9: return (x) ? BMC_PWM_LED_10_X : BMC_PWM_LED_10_Y;
#if defined(BMC_PWM_LED_11_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=11 && BMC_MAX_PWM_LEDS > 10 && defined(BMC_PWM_LED_11_X) && defined(BMC_PWM_LED_11_Y)
  case 10: return (x) ? BMC_PWM_LED_11_X : BMC_PWM_LED_11_Y;
#if defined(BMC_PWM_LED_12_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=12 && BMC_MAX_PWM_LEDS > 11 && defined(BMC_PWM_LED_12_X) && defined(BMC_PWM_LED_12_Y)
  case 11: return (x) ? BMC_PWM_LED_12_X : BMC_PWM_LED_12_Y;
#if defined(BMC_PWM_LED_13_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=13 && BMC_MAX_PWM_LEDS > 12 && defined(BMC_PWM_LED_13_X) && defined(BMC_PWM_LED_13_Y)
  case 12: return (x) ? BMC_PWM_LED_13_X : BMC_PWM_LED_13_Y;
#if defined(BMC_PWM_LED_14_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=14 && BMC_MAX_PWM_LEDS > 13 && defined(BMC_PWM_LED_14_X) && defined(BMC_PWM_LED_14_Y)
  case 13: return (x) ? BMC_PWM_LED_14_X : BMC_PWM_LED_14_Y;
#if defined(BMC_PWM_LED_15_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=15 && BMC_MAX_PWM_LEDS > 14 && defined(BMC_PWM_LED_15_X) && defined(BMC_PWM_LED_15_Y)
  case 14: return (x) ? BMC_PWM_LED_15_X : BMC_PWM_LED_15_Y;
#if defined(BMC_PWM_LED_16_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=16 && BMC_MAX_PWM_LEDS > 15 && defined(BMC_PWM_LED_16_X) && defined(BMC_PWM_LED_16_Y)
  case 15: return (x) ? BMC_PWM_LED_16_X : BMC_PWM_LED_16_Y;
#if defined(BMC_PWM_LED_17_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=17 && BMC_MAX_PWM_LEDS > 16 && defined(BMC_PWM_LED_17_X) && defined(BMC_PWM_LED_17_Y)
  case 16: return (x) ? BMC_PWM_LED_17_X : BMC_PWM_LED_17_Y;
#if defined(BMC_PWM_LED_18_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=18 && BMC_MAX_PWM_LEDS > 17 && defined(BMC_PWM_LED_18_X) && defined(BMC_PWM_LED_18_Y)
  case 17: return (x) ? BMC_PWM_LED_18_X : BMC_PWM_LED_18_Y;
#if defined(BMC_PWM_LED_19_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=19 && BMC_MAX_PWM_LEDS > 18 && defined(BMC_PWM_LED_19_X) && defined(BMC_PWM_LED_19_Y)
  case 18: return (x) ? BMC_PWM_LED_19_X : BMC_PWM_LED_19_Y;
#if defined(BMC_PWM_LED_20_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=20 && BMC_MAX_PWM_LEDS > 19 && defined(BMC_PWM_LED_20_X) && defined(BMC_PWM_LED_20_Y)
  case 19: return (x) ? BMC_PWM_LED_20_X : BMC_PWM_LED_20_Y;
#if defined(BMC_PWM_LED_21_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=21 && BMC_MAX_PWM_LEDS > 20 && defined(BMC_PWM_LED_21_X) && defined(BMC_PWM_LED_21_Y)
  case 20: return (x) ? BMC_PWM_LED_21_X : BMC_PWM_LED_21_Y;
#if defined(BMC_PWM_LED_22_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=22 && BMC_MAX_PWM_LEDS > 21 && defined(BMC_PWM_LED_22_X) && defined(BMC_PWM_LED_22_Y)
  case 21: return (x) ? BMC_PWM_LED_22_X : BMC_PWM_LED_22_Y;
#if defined(BMC_PWM_LED_23_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=23 && BMC_MAX_PWM_LEDS > 22 && defined(BMC_PWM_LED_23_X) && defined(BMC_PWM_LED_23_Y)
  case 22: return (x) ? BMC_PWM_LED_23_X : BMC_PWM_LED_23_Y;
#if defined(BMC_PWM_LED_24_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=24 && BMC_MAX_PWM_LEDS > 23 && defined(BMC_PWM_LED_24_X) && defined(BMC_PWM_LED_24_Y)
  case 23: return (x) ? BMC_PWM_LED_24_X : BMC_PWM_LED_24_Y;
#if defined(BMC_PWM_LED_25_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=25 && BMC_MAX_PWM_LEDS > 24 && defined(BMC_PWM_LED_25_X) && defined(BMC_PWM_LED_25_Y)
  case 24: return (x) ? BMC_PWM_LED_25_X : BMC_PWM_LED_25_Y;
#if defined(BMC_PWM_LED_26_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=26 && BMC_MAX_PWM_LEDS > 25 && defined(BMC_PWM_LED_26_X) && defined(BMC_PWM_LED_26_Y)
  case 25: return (x) ? BMC_PWM_LED_26_X : BMC_PWM_LED_26_Y;
#if defined(BMC_PWM_LED_27_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=27 && BMC_MAX_PWM_LEDS > 26 && defined(BMC_PWM_LED_27_X) && defined(BMC_PWM_LED_27_Y)
  case 26: return (x) ? BMC_PWM_LED_27_X : BMC_PWM_LED_27_Y;
#if defined(BMC_PWM_LED_28_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=28 && BMC_MAX_PWM_LEDS > 27 && defined(BMC_PWM_LED_28_X) && defined(BMC_PWM_LED_28_Y)
  case 27: return (x) ? BMC_PWM_LED_28_X : BMC_PWM_LED_28_Y;
#if defined(BMC_PWM_LED_29_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=29 && BMC_MAX_PWM_LEDS > 28 && defined(BMC_PWM_LED_29_X) && defined(BMC_PWM_LED_29_Y)
  case 28: return (x) ? BMC_PWM_LED_29_X : BMC_PWM_LED_29_Y;
#if defined(BMC_PWM_LED_30_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=30 && BMC_MAX_PWM_LEDS > 29 && defined(BMC_PWM_LED_30_X) && defined(BMC_PWM_LED_30_Y)
  case 29: return (x) ? BMC_PWM_LED_30_X : BMC_PWM_LED_30_Y;
#if defined(BMC_PWM_LED_31_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=31 && BMC_MAX_PWM_LEDS > 30 && defined(BMC_PWM_LED_31_X) && defined(BMC_PWM_LED_31_Y)
  case 30: return (x) ? BMC_PWM_LED_31_X : BMC_PWM_LED_31_Y;
#if defined(BMC_PWM_LED_32_PIN) && BMC_TEENSY_TOTAL_PWM_PINS>=32 && BMC_MAX_PWM_LEDS > 31 && defined(BMC_PWM_LED_32_X) && defined(BMC_PWM_LED_32_Y)
  case 31: return (x) ? BMC_PWM_LED_32_X : BMC_PWM_LED_32_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getPixelPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_PIXELS > 0
switch(index){
#if BMC_MAX_PIXELS > 0 && defined(BMC_PIXEL_1_X) && defined(BMC_PIXEL_1_Y)
  case 0: return (x) ? BMC_PIXEL_1_X : BMC_PIXEL_1_Y;
#if BMC_MAX_PIXELS > 1 && defined(BMC_PIXEL_2_X) && defined(BMC_PIXEL_2_Y)
  case 1: return (x) ? BMC_PIXEL_2_X : BMC_PIXEL_2_Y;
#if BMC_MAX_PIXELS > 2 && defined(BMC_PIXEL_3_X) && defined(BMC_PIXEL_3_Y)
  case 2: return (x) ? BMC_PIXEL_3_X : BMC_PIXEL_3_Y;
#if BMC_MAX_PIXELS > 3 && defined(BMC_PIXEL_4_X) && defined(BMC_PIXEL_4_Y)
  case 3: return (x) ? BMC_PIXEL_4_X : BMC_PIXEL_4_Y;
#if BMC_MAX_PIXELS > 4 && defined(BMC_PIXEL_5_X) && defined(BMC_PIXEL_5_Y)
  case 4: return (x) ? BMC_PIXEL_5_X : BMC_PIXEL_5_Y;
#if BMC_MAX_PIXELS > 5 && defined(BMC_PIXEL_6_X) && defined(BMC_PIXEL_6_Y)
  case 5: return (x) ? BMC_PIXEL_6_X : BMC_PIXEL_6_Y;
#if BMC_MAX_PIXELS > 6 && defined(BMC_PIXEL_7_X) && defined(BMC_PIXEL_7_Y)
  case 6: return (x) ? BMC_PIXEL_7_X : BMC_PIXEL_7_Y;
#if BMC_MAX_PIXELS > 7 && defined(BMC_PIXEL_8_X) && defined(BMC_PIXEL_8_Y)
  case 7: return (x) ? BMC_PIXEL_8_X : BMC_PIXEL_8_Y;
#if BMC_MAX_PIXELS > 8 && defined(BMC_PIXEL_9_X) && defined(BMC_PIXEL_9_Y)
  case 8: return (x) ? BMC_PIXEL_9_X : BMC_PIXEL_9_Y;
#if BMC_MAX_PIXELS > 9 && defined(BMC_PIXEL_10_X) && defined(BMC_PIXEL_10_Y)
  case 9: return (x) ? BMC_PIXEL_10_X : BMC_PIXEL_10_Y;
#if BMC_MAX_PIXELS > 10 && defined(BMC_PIXEL_11_X) && defined(BMC_PIXEL_11_Y)
  case 10: return (x) ? BMC_PIXEL_11_X : BMC_PIXEL_11_Y;
#if BMC_MAX_PIXELS > 11 && defined(BMC_PIXEL_12_X) && defined(BMC_PIXEL_12_Y)
  case 11: return (x) ? BMC_PIXEL_12_X : BMC_PIXEL_12_Y;
#if BMC_MAX_PIXELS > 12 && defined(BMC_PIXEL_13_X) && defined(BMC_PIXEL_13_Y)
  case 12: return (x) ? BMC_PIXEL_13_X : BMC_PIXEL_13_Y;
#if BMC_MAX_PIXELS > 13 && defined(BMC_PIXEL_14_X) && defined(BMC_PIXEL_14_Y)
  case 13: return (x) ? BMC_PIXEL_14_X : BMC_PIXEL_14_Y;
#if BMC_MAX_PIXELS > 14 && defined(BMC_PIXEL_15_X) && defined(BMC_PIXEL_15_Y)
  case 14: return (x) ? BMC_PIXEL_15_X : BMC_PIXEL_15_Y;
#if BMC_MAX_PIXELS > 15 && defined(BMC_PIXEL_16_X) && defined(BMC_PIXEL_16_Y)
  case 15: return (x) ? BMC_PIXEL_16_X : BMC_PIXEL_16_Y;
#if BMC_MAX_PIXELS > 16 && defined(BMC_PIXEL_17_X) && defined(BMC_PIXEL_17_Y)
  case 16: return (x) ? BMC_PIXEL_17_X : BMC_PIXEL_17_Y;
#if BMC_MAX_PIXELS > 17 && defined(BMC_PIXEL_18_X) && defined(BMC_PIXEL_18_Y)
  case 17: return (x) ? BMC_PIXEL_18_X : BMC_PIXEL_18_Y;
#if BMC_MAX_PIXELS > 18 && defined(BMC_PIXEL_19_X) && defined(BMC_PIXEL_19_Y)
  case 18: return (x) ? BMC_PIXEL_19_X : BMC_PIXEL_19_Y;
#if BMC_MAX_PIXELS > 19 && defined(BMC_PIXEL_20_X) && defined(BMC_PIXEL_20_Y)
  case 19: return (x) ? BMC_PIXEL_20_X : BMC_PIXEL_20_Y;
#if BMC_MAX_PIXELS > 20 && defined(BMC_PIXEL_21_X) && defined(BMC_PIXEL_21_Y)
  case 20: return (x) ? BMC_PIXEL_21_X : BMC_PIXEL_21_Y;
#if BMC_MAX_PIXELS > 21 && defined(BMC_PIXEL_22_X) && defined(BMC_PIXEL_22_Y)
  case 21: return (x) ? BMC_PIXEL_22_X : BMC_PIXEL_22_Y;
#if BMC_MAX_PIXELS > 22 && defined(BMC_PIXEL_23_X) && defined(BMC_PIXEL_23_Y)
  case 22: return (x) ? BMC_PIXEL_23_X : BMC_PIXEL_23_Y;
#if BMC_MAX_PIXELS > 23 && defined(BMC_PIXEL_24_X) && defined(BMC_PIXEL_24_Y)
  case 23: return (x) ? BMC_PIXEL_24_X : BMC_PIXEL_24_Y;
#if BMC_MAX_PIXELS > 24 && defined(BMC_PIXEL_25_X) && defined(BMC_PIXEL_25_Y)
  case 24: return (x) ? BMC_PIXEL_25_X : BMC_PIXEL_25_Y;
#if BMC_MAX_PIXELS > 25 && defined(BMC_PIXEL_26_X) && defined(BMC_PIXEL_26_Y)
  case 25: return (x) ? BMC_PIXEL_26_X : BMC_PIXEL_26_Y;
#if BMC_MAX_PIXELS > 26 && defined(BMC_PIXEL_27_X) && defined(BMC_PIXEL_27_Y)
  case 26: return (x) ? BMC_PIXEL_27_X : BMC_PIXEL_27_Y;
#if BMC_MAX_PIXELS > 27 && defined(BMC_PIXEL_28_X) && defined(BMC_PIXEL_28_Y)
  case 27: return (x) ? BMC_PIXEL_28_X : BMC_PIXEL_28_Y;
#if BMC_MAX_PIXELS > 28 && defined(BMC_PIXEL_29_X) && defined(BMC_PIXEL_29_Y)
  case 28: return (x) ? BMC_PIXEL_29_X : BMC_PIXEL_29_Y;
#if BMC_MAX_PIXELS > 29 && defined(BMC_PIXEL_30_X) && defined(BMC_PIXEL_30_Y)
  case 29: return (x) ? BMC_PIXEL_30_X : BMC_PIXEL_30_Y;
#if BMC_MAX_PIXELS > 30 && defined(BMC_PIXEL_31_X) && defined(BMC_PIXEL_31_Y)
  case 30: return (x) ? BMC_PIXEL_31_X : BMC_PIXEL_31_Y;
#if BMC_MAX_PIXELS > 31 && defined(BMC_PIXEL_32_X) && defined(BMC_PIXEL_32_Y)
  case 31: return (x) ? BMC_PIXEL_32_X : BMC_PIXEL_32_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getRgbPixelPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_RGB_PIXELS > 0
switch(index){
#if BMC_MAX_RGB_PIXELS > 0 && defined(BMC_RGB_PIXEL_1_X) && defined(BMC_RGB_PIXEL_1_Y)
  case 0: return (x) ? BMC_RGB_PIXEL_1_X : BMC_RGB_PIXEL_1_Y;
#if BMC_MAX_RGB_PIXELS > 1 && defined(BMC_RGB_PIXEL_2_X) && defined(BMC_RGB_PIXEL_2_Y)
  case 1: return (x) ? BMC_RGB_PIXEL_2_X : BMC_RGB_PIXEL_2_Y;
#if BMC_MAX_RGB_PIXELS > 2 && defined(BMC_RGB_PIXEL_3_X) && defined(BMC_RGB_PIXEL_3_Y)
  case 2: return (x) ? BMC_RGB_PIXEL_3_X : BMC_RGB_PIXEL_3_Y;
#if BMC_MAX_RGB_PIXELS > 3 && defined(BMC_RGB_PIXEL_4_X) && defined(BMC_RGB_PIXEL_4_Y)
  case 3: return (x) ? BMC_RGB_PIXEL_4_X : BMC_RGB_PIXEL_4_Y;
#if BMC_MAX_RGB_PIXELS > 4 && defined(BMC_RGB_PIXEL_5_X) && defined(BMC_RGB_PIXEL_5_Y)
  case 4: return (x) ? BMC_RGB_PIXEL_5_X : BMC_RGB_PIXEL_5_Y;
#if BMC_MAX_RGB_PIXELS > 5 && defined(BMC_RGB_PIXEL_6_X) && defined(BMC_RGB_PIXEL_6_Y)
  case 5: return (x) ? BMC_RGB_PIXEL_6_X : BMC_RGB_PIXEL_6_Y;
#if BMC_MAX_RGB_PIXELS > 6 && defined(BMC_RGB_PIXEL_7_X) && defined(BMC_RGB_PIXEL_7_Y)
  case 6: return (x) ? BMC_RGB_PIXEL_7_X : BMC_RGB_PIXEL_7_Y;
#if BMC_MAX_RGB_PIXELS > 7 && defined(BMC_RGB_PIXEL_8_X) && defined(BMC_RGB_PIXEL_8_Y)
  case 7: return (x) ? BMC_RGB_PIXEL_8_X : BMC_RGB_PIXEL_8_Y;
#if BMC_MAX_RGB_PIXELS > 8 && defined(BMC_RGB_PIXEL_9_X) && defined(BMC_RGB_PIXEL_9_Y)
  case 8: return (x) ? BMC_RGB_PIXEL_9_X : BMC_RGB_PIXEL_9_Y;
#if BMC_MAX_RGB_PIXELS > 9 && defined(BMC_RGB_PIXEL_10_X) && defined(BMC_RGB_PIXEL_10_Y)
  case 9: return (x) ? BMC_RGB_PIXEL_10_X : BMC_RGB_PIXEL_10_Y;
#if BMC_MAX_RGB_PIXELS > 10 && defined(BMC_RGB_PIXEL_11_X) && defined(BMC_RGB_PIXEL_11_Y)
  case 10: return (x) ? BMC_RGB_PIXEL_11_X : BMC_RGB_PIXEL_11_Y;
#if BMC_MAX_RGB_PIXELS > 11 && defined(BMC_RGB_PIXEL_12_X) && defined(BMC_RGB_PIXEL_12_Y)
  case 11: return (x) ? BMC_RGB_PIXEL_12_X : BMC_RGB_PIXEL_12_Y;
#if BMC_MAX_RGB_PIXELS > 12 && defined(BMC_RGB_PIXEL_13_X) && defined(BMC_RGB_PIXEL_13_Y)
  case 12: return (x) ? BMC_RGB_PIXEL_13_X : BMC_RGB_PIXEL_13_Y;
#if BMC_MAX_RGB_PIXELS > 13 && defined(BMC_RGB_PIXEL_14_X) && defined(BMC_RGB_PIXEL_14_Y)
  case 13: return (x) ? BMC_RGB_PIXEL_14_X : BMC_RGB_PIXEL_14_Y;
#if BMC_MAX_RGB_PIXELS > 14 && defined(BMC_RGB_PIXEL_15_X) && defined(BMC_RGB_PIXEL_15_Y)
  case 14: return (x) ? BMC_RGB_PIXEL_15_X : BMC_RGB_PIXEL_15_Y;
#if BMC_MAX_RGB_PIXELS > 15 && defined(BMC_RGB_PIXEL_16_X) && defined(BMC_RGB_PIXEL_16_Y)
  case 15: return (x) ? BMC_RGB_PIXEL_16_X : BMC_RGB_PIXEL_16_Y;
#if BMC_MAX_RGB_PIXELS > 16 && defined(BMC_RGB_PIXEL_17_X) && defined(BMC_RGB_PIXEL_17_Y)
  case 16: return (x) ? BMC_RGB_PIXEL_17_X : BMC_RGB_PIXEL_17_Y;
#if BMC_MAX_RGB_PIXELS > 17 && defined(BMC_RGB_PIXEL_18_X) && defined(BMC_RGB_PIXEL_18_Y)
  case 17: return (x) ? BMC_RGB_PIXEL_18_X : BMC_RGB_PIXEL_18_Y;
#if BMC_MAX_RGB_PIXELS > 18 && defined(BMC_RGB_PIXEL_19_X) && defined(BMC_RGB_PIXEL_19_Y)
  case 18: return (x) ? BMC_RGB_PIXEL_19_X : BMC_RGB_PIXEL_19_Y;
#if BMC_MAX_RGB_PIXELS > 19 && defined(BMC_RGB_PIXEL_20_X) && defined(BMC_RGB_PIXEL_20_Y)
  case 19: return (x) ? BMC_RGB_PIXEL_20_X : BMC_RGB_PIXEL_20_Y;
#if BMC_MAX_RGB_PIXELS > 20 && defined(BMC_RGB_PIXEL_21_X) && defined(BMC_RGB_PIXEL_21_Y)
  case 20: return (x) ? BMC_RGB_PIXEL_21_X : BMC_RGB_PIXEL_21_Y;
#if BMC_MAX_RGB_PIXELS > 21 && defined(BMC_RGB_PIXEL_22_X) && defined(BMC_RGB_PIXEL_22_Y)
  case 21: return (x) ? BMC_RGB_PIXEL_22_X : BMC_RGB_PIXEL_22_Y;
#if BMC_MAX_RGB_PIXELS > 22 && defined(BMC_RGB_PIXEL_23_X) && defined(BMC_RGB_PIXEL_23_Y)
  case 22: return (x) ? BMC_RGB_PIXEL_23_X : BMC_RGB_PIXEL_23_Y;
#if BMC_MAX_RGB_PIXELS > 23 && defined(BMC_RGB_PIXEL_24_X) && defined(BMC_RGB_PIXEL_24_Y)
  case 23: return (x) ? BMC_RGB_PIXEL_24_X : BMC_RGB_PIXEL_24_Y;
#if BMC_MAX_RGB_PIXELS > 24 && defined(BMC_RGB_PIXEL_25_X) && defined(BMC_RGB_PIXEL_25_Y)
  case 24: return (x) ? BMC_RGB_PIXEL_25_X : BMC_RGB_PIXEL_25_Y;
#if BMC_MAX_RGB_PIXELS > 25 && defined(BMC_RGB_PIXEL_26_X) && defined(BMC_RGB_PIXEL_26_Y)
  case 25: return (x) ? BMC_RGB_PIXEL_26_X : BMC_RGB_PIXEL_26_Y;
#if BMC_MAX_RGB_PIXELS > 26 && defined(BMC_RGB_PIXEL_27_X) && defined(BMC_RGB_PIXEL_27_Y)
  case 26: return (x) ? BMC_RGB_PIXEL_27_X : BMC_RGB_PIXEL_27_Y;
#if BMC_MAX_RGB_PIXELS > 27 && defined(BMC_RGB_PIXEL_28_X) && defined(BMC_RGB_PIXEL_28_Y)
  case 27: return (x) ? BMC_RGB_PIXEL_28_X : BMC_RGB_PIXEL_28_Y;
#if BMC_MAX_RGB_PIXELS > 28 && defined(BMC_RGB_PIXEL_29_X) && defined(BMC_RGB_PIXEL_29_Y)
  case 28: return (x) ? BMC_RGB_PIXEL_29_X : BMC_RGB_PIXEL_29_Y;
#if BMC_MAX_RGB_PIXELS > 29 && defined(BMC_RGB_PIXEL_30_X) && defined(BMC_RGB_PIXEL_30_Y)
  case 29: return (x) ? BMC_RGB_PIXEL_30_X : BMC_RGB_PIXEL_30_Y;
#if BMC_MAX_RGB_PIXELS > 30 && defined(BMC_RGB_PIXEL_31_X) && defined(BMC_RGB_PIXEL_31_Y)
  case 30: return (x) ? BMC_RGB_PIXEL_31_X : BMC_RGB_PIXEL_31_Y;
#if BMC_MAX_RGB_PIXELS > 31 && defined(BMC_RGB_PIXEL_32_X) && defined(BMC_RGB_PIXEL_32_Y)
  case 31: return (x) ? BMC_RGB_PIXEL_32_X : BMC_RGB_PIXEL_32_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getGlobalButtonPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_GLOBAL_BUTTONS > 0
switch(index){
#if defined(BMC_GLOBAL_BUTTON_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_GLOBAL_BUTTONS > 0 && defined(BMC_GLOBAL_BUTTON_1_X) && defined(BMC_GLOBAL_BUTTON_1_Y)
  case 0: return (x) ? BMC_GLOBAL_BUTTON_1_X : BMC_GLOBAL_BUTTON_1_Y;
#if defined(BMC_GLOBAL_BUTTON_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_GLOBAL_BUTTONS > 1 && defined(BMC_GLOBAL_BUTTON_2_X) && defined(BMC_GLOBAL_BUTTON_2_Y)
  case 1: return (x) ? BMC_GLOBAL_BUTTON_2_X : BMC_GLOBAL_BUTTON_2_Y;
#if defined(BMC_GLOBAL_BUTTON_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_GLOBAL_BUTTONS > 2 && defined(BMC_GLOBAL_BUTTON_3_X) && defined(BMC_GLOBAL_BUTTON_3_Y)
  case 2: return (x) ? BMC_GLOBAL_BUTTON_3_X : BMC_GLOBAL_BUTTON_3_Y;
#if defined(BMC_GLOBAL_BUTTON_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_GLOBAL_BUTTONS > 3 && defined(BMC_GLOBAL_BUTTON_4_X) && defined(BMC_GLOBAL_BUTTON_4_Y)
  case 3: return (x) ? BMC_GLOBAL_BUTTON_4_X : BMC_GLOBAL_BUTTON_4_Y;
#if defined(BMC_GLOBAL_BUTTON_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_GLOBAL_BUTTONS > 4 && defined(BMC_GLOBAL_BUTTON_5_X) && defined(BMC_GLOBAL_BUTTON_5_Y)
  case 4: return (x) ? BMC_GLOBAL_BUTTON_5_X : BMC_GLOBAL_BUTTON_5_Y;
#if defined(BMC_GLOBAL_BUTTON_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_GLOBAL_BUTTONS > 5 && defined(BMC_GLOBAL_BUTTON_6_X) && defined(BMC_GLOBAL_BUTTON_6_Y)
  case 5: return (x) ? BMC_GLOBAL_BUTTON_6_X : BMC_GLOBAL_BUTTON_6_Y;
#if defined(BMC_GLOBAL_BUTTON_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_GLOBAL_BUTTONS > 6 && defined(BMC_GLOBAL_BUTTON_7_X) && defined(BMC_GLOBAL_BUTTON_7_Y)
  case 6: return (x) ? BMC_GLOBAL_BUTTON_7_X : BMC_GLOBAL_BUTTON_7_Y;
#if defined(BMC_GLOBAL_BUTTON_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_GLOBAL_BUTTONS > 7 && defined(BMC_GLOBAL_BUTTON_8_X) && defined(BMC_GLOBAL_BUTTON_8_Y)
  case 7: return (x) ? BMC_GLOBAL_BUTTON_8_X : BMC_GLOBAL_BUTTON_8_Y;
#if defined(BMC_GLOBAL_BUTTON_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_GLOBAL_BUTTONS > 8 && defined(BMC_GLOBAL_BUTTON_9_X) && defined(BMC_GLOBAL_BUTTON_9_Y)
  case 8: return (x) ? BMC_GLOBAL_BUTTON_9_X : BMC_GLOBAL_BUTTON_9_Y;
#if defined(BMC_GLOBAL_BUTTON_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_GLOBAL_BUTTONS > 9 && defined(BMC_GLOBAL_BUTTON_10_X) && defined(BMC_GLOBAL_BUTTON_10_Y)
  case 9: return (x) ? BMC_GLOBAL_BUTTON_10_X : BMC_GLOBAL_BUTTON_10_Y;
#if defined(BMC_GLOBAL_BUTTON_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_GLOBAL_BUTTONS > 10 && defined(BMC_GLOBAL_BUTTON_11_X) && defined(BMC_GLOBAL_BUTTON_11_Y)
  case 10: return (x) ? BMC_GLOBAL_BUTTON_11_X : BMC_GLOBAL_BUTTON_11_Y;
#if defined(BMC_GLOBAL_BUTTON_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_GLOBAL_BUTTONS > 11 && defined(BMC_GLOBAL_BUTTON_12_X) && defined(BMC_GLOBAL_BUTTON_12_Y)
  case 11: return (x) ? BMC_GLOBAL_BUTTON_12_X : BMC_GLOBAL_BUTTON_12_Y;
#if defined(BMC_GLOBAL_BUTTON_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_GLOBAL_BUTTONS > 12 && defined(BMC_GLOBAL_BUTTON_13_X) && defined(BMC_GLOBAL_BUTTON_13_Y)
  case 12: return (x) ? BMC_GLOBAL_BUTTON_13_X : BMC_GLOBAL_BUTTON_13_Y;
#if defined(BMC_GLOBAL_BUTTON_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_GLOBAL_BUTTONS > 13 && defined(BMC_GLOBAL_BUTTON_14_X) && defined(BMC_GLOBAL_BUTTON_14_Y)
  case 13: return (x) ? BMC_GLOBAL_BUTTON_14_X : BMC_GLOBAL_BUTTON_14_Y;
#if defined(BMC_GLOBAL_BUTTON_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_GLOBAL_BUTTONS > 14 && defined(BMC_GLOBAL_BUTTON_15_X) && defined(BMC_GLOBAL_BUTTON_15_Y)
  case 14: return (x) ? BMC_GLOBAL_BUTTON_15_X : BMC_GLOBAL_BUTTON_15_Y;
#if defined(BMC_GLOBAL_BUTTON_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_GLOBAL_BUTTONS > 15 && defined(BMC_GLOBAL_BUTTON_16_X) && defined(BMC_GLOBAL_BUTTON_16_Y)
  case 15: return (x) ? BMC_GLOBAL_BUTTON_16_X : BMC_GLOBAL_BUTTON_16_Y;
#if defined(BMC_GLOBAL_BUTTON_17_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=17 && BMC_MAX_GLOBAL_BUTTONS > 16 && defined(BMC_GLOBAL_BUTTON_17_X) && defined(BMC_GLOBAL_BUTTON_17_Y)
  case 16: return (x) ? BMC_GLOBAL_BUTTON_17_X : BMC_GLOBAL_BUTTON_17_Y;
#if defined(BMC_GLOBAL_BUTTON_18_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && BMC_MAX_GLOBAL_BUTTONS > 17 && defined(BMC_GLOBAL_BUTTON_18_X) && defined(BMC_GLOBAL_BUTTON_18_Y)
  case 17: return (x) ? BMC_GLOBAL_BUTTON_18_X : BMC_GLOBAL_BUTTON_18_Y;
#if defined(BMC_GLOBAL_BUTTON_19_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=19 && BMC_MAX_GLOBAL_BUTTONS > 18 && defined(BMC_GLOBAL_BUTTON_19_X) && defined(BMC_GLOBAL_BUTTON_19_Y)
  case 18: return (x) ? BMC_GLOBAL_BUTTON_19_X : BMC_GLOBAL_BUTTON_19_Y;
#if defined(BMC_GLOBAL_BUTTON_20_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && BMC_MAX_GLOBAL_BUTTONS > 19 && defined(BMC_GLOBAL_BUTTON_20_X) && defined(BMC_GLOBAL_BUTTON_20_Y)
  case 19: return (x) ? BMC_GLOBAL_BUTTON_20_X : BMC_GLOBAL_BUTTON_20_Y;
#if defined(BMC_GLOBAL_BUTTON_21_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=21 && BMC_MAX_GLOBAL_BUTTONS > 20 && defined(BMC_GLOBAL_BUTTON_21_X) && defined(BMC_GLOBAL_BUTTON_21_Y)
  case 20: return (x) ? BMC_GLOBAL_BUTTON_21_X : BMC_GLOBAL_BUTTON_21_Y;
#if defined(BMC_GLOBAL_BUTTON_22_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && BMC_MAX_GLOBAL_BUTTONS > 21 && defined(BMC_GLOBAL_BUTTON_22_X) && defined(BMC_GLOBAL_BUTTON_22_Y)
  case 21: return (x) ? BMC_GLOBAL_BUTTON_22_X : BMC_GLOBAL_BUTTON_22_Y;
#if defined(BMC_GLOBAL_BUTTON_23_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=23 && BMC_MAX_GLOBAL_BUTTONS > 22 && defined(BMC_GLOBAL_BUTTON_23_X) && defined(BMC_GLOBAL_BUTTON_23_Y)
  case 22: return (x) ? BMC_GLOBAL_BUTTON_23_X : BMC_GLOBAL_BUTTON_23_Y;
#if defined(BMC_GLOBAL_BUTTON_24_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && BMC_MAX_GLOBAL_BUTTONS > 23 && defined(BMC_GLOBAL_BUTTON_24_X) && defined(BMC_GLOBAL_BUTTON_24_Y)
  case 23: return (x) ? BMC_GLOBAL_BUTTON_24_X : BMC_GLOBAL_BUTTON_24_Y;
#if defined(BMC_GLOBAL_BUTTON_25_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=25 && BMC_MAX_GLOBAL_BUTTONS > 24 && defined(BMC_GLOBAL_BUTTON_25_X) && defined(BMC_GLOBAL_BUTTON_25_Y)
  case 24: return (x) ? BMC_GLOBAL_BUTTON_25_X : BMC_GLOBAL_BUTTON_25_Y;
#if defined(BMC_GLOBAL_BUTTON_26_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && BMC_MAX_GLOBAL_BUTTONS > 25 && defined(BMC_GLOBAL_BUTTON_26_X) && defined(BMC_GLOBAL_BUTTON_26_Y)
  case 25: return (x) ? BMC_GLOBAL_BUTTON_26_X : BMC_GLOBAL_BUTTON_26_Y;
#if defined(BMC_GLOBAL_BUTTON_27_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=27 && BMC_MAX_GLOBAL_BUTTONS > 26 && defined(BMC_GLOBAL_BUTTON_27_X) && defined(BMC_GLOBAL_BUTTON_27_Y)
  case 26: return (x) ? BMC_GLOBAL_BUTTON_27_X : BMC_GLOBAL_BUTTON_27_Y;
#if defined(BMC_GLOBAL_BUTTON_28_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && BMC_MAX_GLOBAL_BUTTONS > 27 && defined(BMC_GLOBAL_BUTTON_28_X) && defined(BMC_GLOBAL_BUTTON_28_Y)
  case 27: return (x) ? BMC_GLOBAL_BUTTON_28_X : BMC_GLOBAL_BUTTON_28_Y;
#if defined(BMC_GLOBAL_BUTTON_29_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=29 && BMC_MAX_GLOBAL_BUTTONS > 28 && defined(BMC_GLOBAL_BUTTON_29_X) && defined(BMC_GLOBAL_BUTTON_29_Y)
  case 28: return (x) ? BMC_GLOBAL_BUTTON_29_X : BMC_GLOBAL_BUTTON_29_Y;
#if defined(BMC_GLOBAL_BUTTON_30_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && BMC_MAX_GLOBAL_BUTTONS > 29 && defined(BMC_GLOBAL_BUTTON_30_X) && defined(BMC_GLOBAL_BUTTON_30_Y)
  case 29: return (x) ? BMC_GLOBAL_BUTTON_30_X : BMC_GLOBAL_BUTTON_30_Y;
#if defined(BMC_GLOBAL_BUTTON_31_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=31 && BMC_MAX_GLOBAL_BUTTONS > 30 && defined(BMC_GLOBAL_BUTTON_31_X) && defined(BMC_GLOBAL_BUTTON_31_Y)
  case 30: return (x) ? BMC_GLOBAL_BUTTON_31_X : BMC_GLOBAL_BUTTON_31_Y;
#if defined(BMC_GLOBAL_BUTTON_32_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && BMC_MAX_GLOBAL_BUTTONS > 31 && defined(BMC_GLOBAL_BUTTON_32_X) && defined(BMC_GLOBAL_BUTTON_32_Y)
  case 31: return (x) ? BMC_GLOBAL_BUTTON_32_X : BMC_GLOBAL_BUTTON_32_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getGlobalEncoderPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_GLOBAL_ENCODERS > 0
switch(index){
#if defined(BMC_GLOBAL_ENCODER_1A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=2 && defined(BMC_GLOBAL_ENCODER_1B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 0 && defined(BMC_GLOBAL_ENCODER_1_X) && defined(BMC_GLOBAL_ENCODER_1_Y)
  case 0: return (x) ? BMC_GLOBAL_ENCODER_1_X : BMC_GLOBAL_ENCODER_1_Y;
#if defined(BMC_GLOBAL_ENCODER_2A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=4 && defined(BMC_GLOBAL_ENCODER_2B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 1 && defined(BMC_GLOBAL_ENCODER_2_X) && defined(BMC_GLOBAL_ENCODER_2_Y)
  case 1: return (x) ? BMC_GLOBAL_ENCODER_2_X : BMC_GLOBAL_ENCODER_2_Y;
#if defined(BMC_GLOBAL_ENCODER_3A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=6 && defined(BMC_GLOBAL_ENCODER_3B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 2 && defined(BMC_GLOBAL_ENCODER_3_X) && defined(BMC_GLOBAL_ENCODER_3_Y)
  case 2: return (x) ? BMC_GLOBAL_ENCODER_3_X : BMC_GLOBAL_ENCODER_3_Y;
#if defined(BMC_GLOBAL_ENCODER_4A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=8 && defined(BMC_GLOBAL_ENCODER_4B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 3 && defined(BMC_GLOBAL_ENCODER_4_X) && defined(BMC_GLOBAL_ENCODER_4_Y)
  case 3: return (x) ? BMC_GLOBAL_ENCODER_4_X : BMC_GLOBAL_ENCODER_4_Y;
#if defined(BMC_GLOBAL_ENCODER_5A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=10 && defined(BMC_GLOBAL_ENCODER_5B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 4 && defined(BMC_GLOBAL_ENCODER_5_X) && defined(BMC_GLOBAL_ENCODER_5_Y)
  case 4: return (x) ? BMC_GLOBAL_ENCODER_5_X : BMC_GLOBAL_ENCODER_5_Y;
#if defined(BMC_GLOBAL_ENCODER_6A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=12 && defined(BMC_GLOBAL_ENCODER_6B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 5 && defined(BMC_GLOBAL_ENCODER_6_X) && defined(BMC_GLOBAL_ENCODER_6_Y)
  case 5: return (x) ? BMC_GLOBAL_ENCODER_6_X : BMC_GLOBAL_ENCODER_6_Y;
#if defined(BMC_GLOBAL_ENCODER_7A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=14 && defined(BMC_GLOBAL_ENCODER_7B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 6 && defined(BMC_GLOBAL_ENCODER_7_X) && defined(BMC_GLOBAL_ENCODER_7_Y)
  case 6: return (x) ? BMC_GLOBAL_ENCODER_7_X : BMC_GLOBAL_ENCODER_7_Y;
#if defined(BMC_GLOBAL_ENCODER_8A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=16 && defined(BMC_GLOBAL_ENCODER_8B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 7 && defined(BMC_GLOBAL_ENCODER_8_X) && defined(BMC_GLOBAL_ENCODER_8_Y)
  case 7: return (x) ? BMC_GLOBAL_ENCODER_8_X : BMC_GLOBAL_ENCODER_8_Y;
#if defined(BMC_GLOBAL_ENCODER_9A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=18 && defined(BMC_GLOBAL_ENCODER_9B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 8 && defined(BMC_GLOBAL_ENCODER_9_X) && defined(BMC_GLOBAL_ENCODER_9_Y)
  case 8: return (x) ? BMC_GLOBAL_ENCODER_9_X : BMC_GLOBAL_ENCODER_9_Y;
#if defined(BMC_GLOBAL_ENCODER_10A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=20 && defined(BMC_GLOBAL_ENCODER_10B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 9 && defined(BMC_GLOBAL_ENCODER_10_X) && defined(BMC_GLOBAL_ENCODER_10_Y)
  case 9: return (x) ? BMC_GLOBAL_ENCODER_10_X : BMC_GLOBAL_ENCODER_10_Y;
#if defined(BMC_GLOBAL_ENCODER_11A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=22 && defined(BMC_GLOBAL_ENCODER_11B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 10 && defined(BMC_GLOBAL_ENCODER_11_X) && defined(BMC_GLOBAL_ENCODER_11_Y)
  case 10: return (x) ? BMC_GLOBAL_ENCODER_11_X : BMC_GLOBAL_ENCODER_11_Y;
#if defined(BMC_GLOBAL_ENCODER_12A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=24 && defined(BMC_GLOBAL_ENCODER_12B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 11 && defined(BMC_GLOBAL_ENCODER_12_X) && defined(BMC_GLOBAL_ENCODER_12_Y)
  case 11: return (x) ? BMC_GLOBAL_ENCODER_12_X : BMC_GLOBAL_ENCODER_12_Y;
#if defined(BMC_GLOBAL_ENCODER_13A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=26 && defined(BMC_GLOBAL_ENCODER_13B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 12 && defined(BMC_GLOBAL_ENCODER_13_X) && defined(BMC_GLOBAL_ENCODER_13_Y)
  case 12: return (x) ? BMC_GLOBAL_ENCODER_13_X : BMC_GLOBAL_ENCODER_13_Y;
#if defined(BMC_GLOBAL_ENCODER_14A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=28 && defined(BMC_GLOBAL_ENCODER_14B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 13 && defined(BMC_GLOBAL_ENCODER_14_X) && defined(BMC_GLOBAL_ENCODER_14_Y)
  case 13: return (x) ? BMC_GLOBAL_ENCODER_14_X : BMC_GLOBAL_ENCODER_14_Y;
#if defined(BMC_GLOBAL_ENCODER_15A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=30 && defined(BMC_GLOBAL_ENCODER_15B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 14 && defined(BMC_GLOBAL_ENCODER_15_X) && defined(BMC_GLOBAL_ENCODER_15_Y)
  case 14: return (x) ? BMC_GLOBAL_ENCODER_15_X : BMC_GLOBAL_ENCODER_15_Y;
#if defined(BMC_GLOBAL_ENCODER_16A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=32 && defined(BMC_GLOBAL_ENCODER_16B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 15 && defined(BMC_GLOBAL_ENCODER_16_X) && defined(BMC_GLOBAL_ENCODER_16_Y)
  case 15: return (x) ? BMC_GLOBAL_ENCODER_16_X : BMC_GLOBAL_ENCODER_16_Y;
#if defined(BMC_GLOBAL_ENCODER_17A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=34 && defined(BMC_GLOBAL_ENCODER_17B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 16 && defined(BMC_GLOBAL_ENCODER_17_X) && defined(BMC_GLOBAL_ENCODER_17_Y)
  case 16: return (x) ? BMC_GLOBAL_ENCODER_17_X : BMC_GLOBAL_ENCODER_17_Y;
#if defined(BMC_GLOBAL_ENCODER_18A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=36 && defined(BMC_GLOBAL_ENCODER_18B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 17 && defined(BMC_GLOBAL_ENCODER_18_X) && defined(BMC_GLOBAL_ENCODER_18_Y)
  case 17: return (x) ? BMC_GLOBAL_ENCODER_18_X : BMC_GLOBAL_ENCODER_18_Y;
#if defined(BMC_GLOBAL_ENCODER_19A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=38 && defined(BMC_GLOBAL_ENCODER_19B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 18 && defined(BMC_GLOBAL_ENCODER_19_X) && defined(BMC_GLOBAL_ENCODER_19_Y)
  case 18: return (x) ? BMC_GLOBAL_ENCODER_19_X : BMC_GLOBAL_ENCODER_19_Y;
#if defined(BMC_GLOBAL_ENCODER_20A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=40 && defined(BMC_GLOBAL_ENCODER_20B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 19 && defined(BMC_GLOBAL_ENCODER_20_X) && defined(BMC_GLOBAL_ENCODER_20_Y)
  case 19: return (x) ? BMC_GLOBAL_ENCODER_20_X : BMC_GLOBAL_ENCODER_20_Y;
#if defined(BMC_GLOBAL_ENCODER_21A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=42 && defined(BMC_GLOBAL_ENCODER_21B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 20 && defined(BMC_GLOBAL_ENCODER_21_X) && defined(BMC_GLOBAL_ENCODER_21_Y)
  case 20: return (x) ? BMC_GLOBAL_ENCODER_21_X : BMC_GLOBAL_ENCODER_21_Y;
#if defined(BMC_GLOBAL_ENCODER_22A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=44 && defined(BMC_GLOBAL_ENCODER_22B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 21 && defined(BMC_GLOBAL_ENCODER_22_X) && defined(BMC_GLOBAL_ENCODER_22_Y)
  case 21: return (x) ? BMC_GLOBAL_ENCODER_22_X : BMC_GLOBAL_ENCODER_22_Y;
#if defined(BMC_GLOBAL_ENCODER_23A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=46 && defined(BMC_GLOBAL_ENCODER_23B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 22 && defined(BMC_GLOBAL_ENCODER_23_X) && defined(BMC_GLOBAL_ENCODER_23_Y)
  case 22: return (x) ? BMC_GLOBAL_ENCODER_23_X : BMC_GLOBAL_ENCODER_23_Y;
#if defined(BMC_GLOBAL_ENCODER_24A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=48 && defined(BMC_GLOBAL_ENCODER_24B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 23 && defined(BMC_GLOBAL_ENCODER_24_X) && defined(BMC_GLOBAL_ENCODER_24_Y)
  case 23: return (x) ? BMC_GLOBAL_ENCODER_24_X : BMC_GLOBAL_ENCODER_24_Y;
#if defined(BMC_GLOBAL_ENCODER_25A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=50 && defined(BMC_GLOBAL_ENCODER_25B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 24 && defined(BMC_GLOBAL_ENCODER_25_X) && defined(BMC_GLOBAL_ENCODER_25_Y)
  case 24: return (x) ? BMC_GLOBAL_ENCODER_25_X : BMC_GLOBAL_ENCODER_25_Y;
#if defined(BMC_GLOBAL_ENCODER_26A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=52 && defined(BMC_GLOBAL_ENCODER_26B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 25 && defined(BMC_GLOBAL_ENCODER_26_X) && defined(BMC_GLOBAL_ENCODER_26_Y)
  case 25: return (x) ? BMC_GLOBAL_ENCODER_26_X : BMC_GLOBAL_ENCODER_26_Y;
#if defined(BMC_GLOBAL_ENCODER_27A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=54 && defined(BMC_GLOBAL_ENCODER_27B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 26 && defined(BMC_GLOBAL_ENCODER_27_X) && defined(BMC_GLOBAL_ENCODER_27_Y)
  case 26: return (x) ? BMC_GLOBAL_ENCODER_27_X : BMC_GLOBAL_ENCODER_27_Y;
#if defined(BMC_GLOBAL_ENCODER_28A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=56 && defined(BMC_GLOBAL_ENCODER_28B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 27 && defined(BMC_GLOBAL_ENCODER_28_X) && defined(BMC_GLOBAL_ENCODER_28_Y)
  case 27: return (x) ? BMC_GLOBAL_ENCODER_28_X : BMC_GLOBAL_ENCODER_28_Y;
#if defined(BMC_GLOBAL_ENCODER_29A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=58 && defined(BMC_GLOBAL_ENCODER_29B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 28 && defined(BMC_GLOBAL_ENCODER_29_X) && defined(BMC_GLOBAL_ENCODER_29_Y)
  case 28: return (x) ? BMC_GLOBAL_ENCODER_29_X : BMC_GLOBAL_ENCODER_29_Y;
#if defined(BMC_GLOBAL_ENCODER_30A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=60 && defined(BMC_GLOBAL_ENCODER_30B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 29 && defined(BMC_GLOBAL_ENCODER_30_X) && defined(BMC_GLOBAL_ENCODER_30_Y)
  case 29: return (x) ? BMC_GLOBAL_ENCODER_30_X : BMC_GLOBAL_ENCODER_30_Y;
#if defined(BMC_GLOBAL_ENCODER_31A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=62 && defined(BMC_GLOBAL_ENCODER_31B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 30 && defined(BMC_GLOBAL_ENCODER_31_X) && defined(BMC_GLOBAL_ENCODER_31_Y)
  case 30: return (x) ? BMC_GLOBAL_ENCODER_31_X : BMC_GLOBAL_ENCODER_31_Y;
#if defined(BMC_GLOBAL_ENCODER_32A_PIN) && (BMC_TEENSY_TOTAL_DIGITAL_PINS+BMC_MAX_MUX_IN)>=64 && defined(BMC_GLOBAL_ENCODER_32B_PIN) && BMC_MAX_GLOBAL_ENCODERS > 31 && defined(BMC_GLOBAL_ENCODER_32_X) && defined(BMC_GLOBAL_ENCODER_32_Y)
  case 31: return (x) ? BMC_GLOBAL_ENCODER_32_X : BMC_GLOBAL_ENCODER_32_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getGlobalPotPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_GLOBAL_POTS > 0
switch(index){
#if defined(BMC_GLOBAL_POT_1_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=1 && BMC_MAX_GLOBAL_POTS > 0 && defined(BMC_GLOBAL_POT_1_X) && defined(BMC_GLOBAL_POT_1_Y)
  case 0: return (x) ? BMC_GLOBAL_POT_1_X : BMC_GLOBAL_POT_1_Y;
#if defined(BMC_GLOBAL_POT_2_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=2 && BMC_MAX_GLOBAL_POTS > 1 && defined(BMC_GLOBAL_POT_2_X) && defined(BMC_GLOBAL_POT_2_Y)
  case 1: return (x) ? BMC_GLOBAL_POT_2_X : BMC_GLOBAL_POT_2_Y;
#if defined(BMC_GLOBAL_POT_3_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=3 && BMC_MAX_GLOBAL_POTS > 2 && defined(BMC_GLOBAL_POT_3_X) && defined(BMC_GLOBAL_POT_3_Y)
  case 2: return (x) ? BMC_GLOBAL_POT_3_X : BMC_GLOBAL_POT_3_Y;
#if defined(BMC_GLOBAL_POT_4_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=4 && BMC_MAX_GLOBAL_POTS > 3 && defined(BMC_GLOBAL_POT_4_X) && defined(BMC_GLOBAL_POT_4_Y)
  case 3: return (x) ? BMC_GLOBAL_POT_4_X : BMC_GLOBAL_POT_4_Y;
#if defined(BMC_GLOBAL_POT_5_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=5 && BMC_MAX_GLOBAL_POTS > 4 && defined(BMC_GLOBAL_POT_5_X) && defined(BMC_GLOBAL_POT_5_Y)
  case 4: return (x) ? BMC_GLOBAL_POT_5_X : BMC_GLOBAL_POT_5_Y;
#if defined(BMC_GLOBAL_POT_6_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=6 && BMC_MAX_GLOBAL_POTS > 5 && defined(BMC_GLOBAL_POT_6_X) && defined(BMC_GLOBAL_POT_6_Y)
  case 5: return (x) ? BMC_GLOBAL_POT_6_X : BMC_GLOBAL_POT_6_Y;
#if defined(BMC_GLOBAL_POT_7_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=7 && BMC_MAX_GLOBAL_POTS > 6 && defined(BMC_GLOBAL_POT_7_X) && defined(BMC_GLOBAL_POT_7_Y)
  case 6: return (x) ? BMC_GLOBAL_POT_7_X : BMC_GLOBAL_POT_7_Y;
#if defined(BMC_GLOBAL_POT_8_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=8 && BMC_MAX_GLOBAL_POTS > 7 && defined(BMC_GLOBAL_POT_8_X) && defined(BMC_GLOBAL_POT_8_Y)
  case 7: return (x) ? BMC_GLOBAL_POT_8_X : BMC_GLOBAL_POT_8_Y;
#if defined(BMC_GLOBAL_POT_9_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=9 && BMC_MAX_GLOBAL_POTS > 8 && defined(BMC_GLOBAL_POT_9_X) && defined(BMC_GLOBAL_POT_9_Y)
  case 8: return (x) ? BMC_GLOBAL_POT_9_X : BMC_GLOBAL_POT_9_Y;
#if defined(BMC_GLOBAL_POT_10_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=10 && BMC_MAX_GLOBAL_POTS > 9 && defined(BMC_GLOBAL_POT_10_X) && defined(BMC_GLOBAL_POT_10_Y)
  case 9: return (x) ? BMC_GLOBAL_POT_10_X : BMC_GLOBAL_POT_10_Y;
#if defined(BMC_GLOBAL_POT_11_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=11 && BMC_MAX_GLOBAL_POTS > 10 && defined(BMC_GLOBAL_POT_11_X) && defined(BMC_GLOBAL_POT_11_Y)
  case 10: return (x) ? BMC_GLOBAL_POT_11_X : BMC_GLOBAL_POT_11_Y;
#if defined(BMC_GLOBAL_POT_12_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=12 && BMC_MAX_GLOBAL_POTS > 11 && defined(BMC_GLOBAL_POT_12_X) && defined(BMC_GLOBAL_POT_12_Y)
  case 11: return (x) ? BMC_GLOBAL_POT_12_X : BMC_GLOBAL_POT_12_Y;
#if defined(BMC_GLOBAL_POT_13_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=13 && BMC_MAX_GLOBAL_POTS > 12 && defined(BMC_GLOBAL_POT_13_X) && defined(BMC_GLOBAL_POT_13_Y)
  case 12: return (x) ? BMC_GLOBAL_POT_13_X : BMC_GLOBAL_POT_13_Y;
#if defined(BMC_GLOBAL_POT_14_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=14 && BMC_MAX_GLOBAL_POTS > 13 && defined(BMC_GLOBAL_POT_14_X) && defined(BMC_GLOBAL_POT_14_Y)
  case 13: return (x) ? BMC_GLOBAL_POT_14_X : BMC_GLOBAL_POT_14_Y;
#if defined(BMC_GLOBAL_POT_15_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=15 && BMC_MAX_GLOBAL_POTS > 14 && defined(BMC_GLOBAL_POT_15_X) && defined(BMC_GLOBAL_POT_15_Y)
  case 14: return (x) ? BMC_GLOBAL_POT_15_X : BMC_GLOBAL_POT_15_Y;
#if defined(BMC_GLOBAL_POT_16_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=16 && BMC_MAX_GLOBAL_POTS > 15 && defined(BMC_GLOBAL_POT_16_X) && defined(BMC_GLOBAL_POT_16_Y)
  case 15: return (x) ? BMC_GLOBAL_POT_16_X : BMC_GLOBAL_POT_16_Y;
#if defined(BMC_GLOBAL_POT_17_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=17 && BMC_MAX_GLOBAL_POTS > 16 && defined(BMC_GLOBAL_POT_17_X) && defined(BMC_GLOBAL_POT_17_Y)
  case 16: return (x) ? BMC_GLOBAL_POT_17_X : BMC_GLOBAL_POT_17_Y;
#if defined(BMC_GLOBAL_POT_18_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=18 && BMC_MAX_GLOBAL_POTS > 17 && defined(BMC_GLOBAL_POT_18_X) && defined(BMC_GLOBAL_POT_18_Y)
  case 17: return (x) ? BMC_GLOBAL_POT_18_X : BMC_GLOBAL_POT_18_Y;
#if defined(BMC_GLOBAL_POT_19_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=19 && BMC_MAX_GLOBAL_POTS > 18 && defined(BMC_GLOBAL_POT_19_X) && defined(BMC_GLOBAL_POT_19_Y)
  case 18: return (x) ? BMC_GLOBAL_POT_19_X : BMC_GLOBAL_POT_19_Y;
#if defined(BMC_GLOBAL_POT_20_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=20 && BMC_MAX_GLOBAL_POTS > 19 && defined(BMC_GLOBAL_POT_20_X) && defined(BMC_GLOBAL_POT_20_Y)
  case 19: return (x) ? BMC_GLOBAL_POT_20_X : BMC_GLOBAL_POT_20_Y;
#if defined(BMC_GLOBAL_POT_21_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=21 && BMC_MAX_GLOBAL_POTS > 20 && defined(BMC_GLOBAL_POT_21_X) && defined(BMC_GLOBAL_POT_21_Y)
  case 20: return (x) ? BMC_GLOBAL_POT_21_X : BMC_GLOBAL_POT_21_Y;
#if defined(BMC_GLOBAL_POT_22_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=22 && BMC_MAX_GLOBAL_POTS > 21 && defined(BMC_GLOBAL_POT_22_X) && defined(BMC_GLOBAL_POT_22_Y)
  case 21: return (x) ? BMC_GLOBAL_POT_22_X : BMC_GLOBAL_POT_22_Y;
#if defined(BMC_GLOBAL_POT_23_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=23 && BMC_MAX_GLOBAL_POTS > 22 && defined(BMC_GLOBAL_POT_23_X) && defined(BMC_GLOBAL_POT_23_Y)
  case 22: return (x) ? BMC_GLOBAL_POT_23_X : BMC_GLOBAL_POT_23_Y;
#if defined(BMC_GLOBAL_POT_24_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=24 && BMC_MAX_GLOBAL_POTS > 23 && defined(BMC_GLOBAL_POT_24_X) && defined(BMC_GLOBAL_POT_24_Y)
  case 23: return (x) ? BMC_GLOBAL_POT_24_X : BMC_GLOBAL_POT_24_Y;
#if defined(BMC_GLOBAL_POT_25_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=25 && BMC_MAX_GLOBAL_POTS > 24 && defined(BMC_GLOBAL_POT_25_X) && defined(BMC_GLOBAL_POT_25_Y)
  case 24: return (x) ? BMC_GLOBAL_POT_25_X : BMC_GLOBAL_POT_25_Y;
#if defined(BMC_GLOBAL_POT_26_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=26 && BMC_MAX_GLOBAL_POTS > 25 && defined(BMC_GLOBAL_POT_26_X) && defined(BMC_GLOBAL_POT_26_Y)
  case 25: return (x) ? BMC_GLOBAL_POT_26_X : BMC_GLOBAL_POT_26_Y;
#if defined(BMC_GLOBAL_POT_27_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=27 && BMC_MAX_GLOBAL_POTS > 26 && defined(BMC_GLOBAL_POT_27_X) && defined(BMC_GLOBAL_POT_27_Y)
  case 26: return (x) ? BMC_GLOBAL_POT_27_X : BMC_GLOBAL_POT_27_Y;
#if defined(BMC_GLOBAL_POT_28_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=28 && BMC_MAX_GLOBAL_POTS > 27 && defined(BMC_GLOBAL_POT_28_X) && defined(BMC_GLOBAL_POT_28_Y)
  case 27: return (x) ? BMC_GLOBAL_POT_28_X : BMC_GLOBAL_POT_28_Y;
#if defined(BMC_GLOBAL_POT_29_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=29 && BMC_MAX_GLOBAL_POTS > 28 && defined(BMC_GLOBAL_POT_29_X) && defined(BMC_GLOBAL_POT_29_Y)
  case 28: return (x) ? BMC_GLOBAL_POT_29_X : BMC_GLOBAL_POT_29_Y;
#if defined(BMC_GLOBAL_POT_30_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=30 && BMC_MAX_GLOBAL_POTS > 29 && defined(BMC_GLOBAL_POT_30_X) && defined(BMC_GLOBAL_POT_30_Y)
  case 29: return (x) ? BMC_GLOBAL_POT_30_X : BMC_GLOBAL_POT_30_Y;
#if defined(BMC_GLOBAL_POT_31_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=31 && BMC_MAX_GLOBAL_POTS > 30 && defined(BMC_GLOBAL_POT_31_X) && defined(BMC_GLOBAL_POT_31_Y)
  case 30: return (x) ? BMC_GLOBAL_POT_31_X : BMC_GLOBAL_POT_31_Y;
#if defined(BMC_GLOBAL_POT_32_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=32 && BMC_MAX_GLOBAL_POTS > 31 && defined(BMC_GLOBAL_POT_32_X) && defined(BMC_GLOBAL_POT_32_Y)
  case 31: return (x) ? BMC_GLOBAL_POT_32_X : BMC_GLOBAL_POT_32_Y;
#if defined(BMC_GLOBAL_POT_33_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=33 && BMC_MAX_GLOBAL_POTS > 32 && defined(BMC_GLOBAL_POT_33_X) && defined(BMC_GLOBAL_POT_33_Y)
  case 32: return (x) ? BMC_GLOBAL_POT_33_X : BMC_GLOBAL_POT_33_Y;
#if defined(BMC_GLOBAL_POT_34_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=34 && BMC_MAX_GLOBAL_POTS > 33 && defined(BMC_GLOBAL_POT_34_X) && defined(BMC_GLOBAL_POT_34_Y)
  case 33: return (x) ? BMC_GLOBAL_POT_34_X : BMC_GLOBAL_POT_34_Y;
#if defined(BMC_GLOBAL_POT_35_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=35 && BMC_MAX_GLOBAL_POTS > 34 && defined(BMC_GLOBAL_POT_35_X) && defined(BMC_GLOBAL_POT_35_Y)
  case 34: return (x) ? BMC_GLOBAL_POT_35_X : BMC_GLOBAL_POT_35_Y;
#if defined(BMC_GLOBAL_POT_36_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=36 && BMC_MAX_GLOBAL_POTS > 35 && defined(BMC_GLOBAL_POT_36_X) && defined(BMC_GLOBAL_POT_36_Y)
  case 35: return (x) ? BMC_GLOBAL_POT_36_X : BMC_GLOBAL_POT_36_Y;
#if defined(BMC_GLOBAL_POT_37_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=37 && BMC_MAX_GLOBAL_POTS > 36 && defined(BMC_GLOBAL_POT_37_X) && defined(BMC_GLOBAL_POT_37_Y)
  case 36: return (x) ? BMC_GLOBAL_POT_37_X : BMC_GLOBAL_POT_37_Y;
#if defined(BMC_GLOBAL_POT_38_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=38 && BMC_MAX_GLOBAL_POTS > 37 && defined(BMC_GLOBAL_POT_38_X) && defined(BMC_GLOBAL_POT_38_Y)
  case 37: return (x) ? BMC_GLOBAL_POT_38_X : BMC_GLOBAL_POT_38_Y;
#if defined(BMC_GLOBAL_POT_39_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=39 && BMC_MAX_GLOBAL_POTS > 38 && defined(BMC_GLOBAL_POT_39_X) && defined(BMC_GLOBAL_POT_39_Y)
  case 38: return (x) ? BMC_GLOBAL_POT_39_X : BMC_GLOBAL_POT_39_Y;
#if defined(BMC_GLOBAL_POT_40_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=40 && BMC_MAX_GLOBAL_POTS > 39 && defined(BMC_GLOBAL_POT_40_X) && defined(BMC_GLOBAL_POT_40_Y)
  case 39: return (x) ? BMC_GLOBAL_POT_40_X : BMC_GLOBAL_POT_40_Y;
#if defined(BMC_GLOBAL_POT_41_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=41 && BMC_MAX_GLOBAL_POTS > 40 && defined(BMC_GLOBAL_POT_41_X) && defined(BMC_GLOBAL_POT_41_Y)
  case 40: return (x) ? BMC_GLOBAL_POT_41_X : BMC_GLOBAL_POT_41_Y;
#if defined(BMC_GLOBAL_POT_42_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=42 && BMC_MAX_GLOBAL_POTS > 41 && defined(BMC_GLOBAL_POT_42_X) && defined(BMC_GLOBAL_POT_42_Y)
  case 41: return (x) ? BMC_GLOBAL_POT_42_X : BMC_GLOBAL_POT_42_Y;
#if defined(BMC_GLOBAL_POT_43_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=43 && BMC_MAX_GLOBAL_POTS > 42 && defined(BMC_GLOBAL_POT_43_X) && defined(BMC_GLOBAL_POT_43_Y)
  case 42: return (x) ? BMC_GLOBAL_POT_43_X : BMC_GLOBAL_POT_43_Y;
#if defined(BMC_GLOBAL_POT_44_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=44 && BMC_MAX_GLOBAL_POTS > 43 && defined(BMC_GLOBAL_POT_44_X) && defined(BMC_GLOBAL_POT_44_Y)
  case 43: return (x) ? BMC_GLOBAL_POT_44_X : BMC_GLOBAL_POT_44_Y;
#if defined(BMC_GLOBAL_POT_45_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=45 && BMC_MAX_GLOBAL_POTS > 44 && defined(BMC_GLOBAL_POT_45_X) && defined(BMC_GLOBAL_POT_45_Y)
  case 44: return (x) ? BMC_GLOBAL_POT_45_X : BMC_GLOBAL_POT_45_Y;
#if defined(BMC_GLOBAL_POT_46_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=46 && BMC_MAX_GLOBAL_POTS > 45 && defined(BMC_GLOBAL_POT_46_X) && defined(BMC_GLOBAL_POT_46_Y)
  case 45: return (x) ? BMC_GLOBAL_POT_46_X : BMC_GLOBAL_POT_46_Y;
#if defined(BMC_GLOBAL_POT_47_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=47 && BMC_MAX_GLOBAL_POTS > 46 && defined(BMC_GLOBAL_POT_47_X) && defined(BMC_GLOBAL_POT_47_Y)
  case 46: return (x) ? BMC_GLOBAL_POT_47_X : BMC_GLOBAL_POT_47_Y;
#if defined(BMC_GLOBAL_POT_48_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=48 && BMC_MAX_GLOBAL_POTS > 47 && defined(BMC_GLOBAL_POT_48_X) && defined(BMC_GLOBAL_POT_48_Y)
  case 47: return (x) ? BMC_GLOBAL_POT_48_X : BMC_GLOBAL_POT_48_Y;
#if defined(BMC_GLOBAL_POT_49_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=49 && BMC_MAX_GLOBAL_POTS > 48 && defined(BMC_GLOBAL_POT_49_X) && defined(BMC_GLOBAL_POT_49_Y)
  case 48: return (x) ? BMC_GLOBAL_POT_49_X : BMC_GLOBAL_POT_49_Y;
#if defined(BMC_GLOBAL_POT_50_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=50 && BMC_MAX_GLOBAL_POTS > 49 && defined(BMC_GLOBAL_POT_50_X) && defined(BMC_GLOBAL_POT_50_Y)
  case 49: return (x) ? BMC_GLOBAL_POT_50_X : BMC_GLOBAL_POT_50_Y;
#if defined(BMC_GLOBAL_POT_51_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=51 && BMC_MAX_GLOBAL_POTS > 50 && defined(BMC_GLOBAL_POT_51_X) && defined(BMC_GLOBAL_POT_51_Y)
  case 50: return (x) ? BMC_GLOBAL_POT_51_X : BMC_GLOBAL_POT_51_Y;
#if defined(BMC_GLOBAL_POT_52_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=52 && BMC_MAX_GLOBAL_POTS > 51 && defined(BMC_GLOBAL_POT_52_X) && defined(BMC_GLOBAL_POT_52_Y)
  case 51: return (x) ? BMC_GLOBAL_POT_52_X : BMC_GLOBAL_POT_52_Y;
#if defined(BMC_GLOBAL_POT_53_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=53 && BMC_MAX_GLOBAL_POTS > 52 && defined(BMC_GLOBAL_POT_53_X) && defined(BMC_GLOBAL_POT_53_Y)
  case 52: return (x) ? BMC_GLOBAL_POT_53_X : BMC_GLOBAL_POT_53_Y;
#if defined(BMC_GLOBAL_POT_54_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=54 && BMC_MAX_GLOBAL_POTS > 53 && defined(BMC_GLOBAL_POT_54_X) && defined(BMC_GLOBAL_POT_54_Y)
  case 53: return (x) ? BMC_GLOBAL_POT_54_X : BMC_GLOBAL_POT_54_Y;
#if defined(BMC_GLOBAL_POT_55_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=55 && BMC_MAX_GLOBAL_POTS > 54 && defined(BMC_GLOBAL_POT_55_X) && defined(BMC_GLOBAL_POT_55_Y)
  case 54: return (x) ? BMC_GLOBAL_POT_55_X : BMC_GLOBAL_POT_55_Y;
#if defined(BMC_GLOBAL_POT_56_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=56 && BMC_MAX_GLOBAL_POTS > 55 && defined(BMC_GLOBAL_POT_56_X) && defined(BMC_GLOBAL_POT_56_Y)
  case 55: return (x) ? BMC_GLOBAL_POT_56_X : BMC_GLOBAL_POT_56_Y;
#if defined(BMC_GLOBAL_POT_57_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=57 && BMC_MAX_GLOBAL_POTS > 56 && defined(BMC_GLOBAL_POT_57_X) && defined(BMC_GLOBAL_POT_57_Y)
  case 56: return (x) ? BMC_GLOBAL_POT_57_X : BMC_GLOBAL_POT_57_Y;
#if defined(BMC_GLOBAL_POT_58_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=58 && BMC_MAX_GLOBAL_POTS > 57 && defined(BMC_GLOBAL_POT_58_X) && defined(BMC_GLOBAL_POT_58_Y)
  case 57: return (x) ? BMC_GLOBAL_POT_58_X : BMC_GLOBAL_POT_58_Y;
#if defined(BMC_GLOBAL_POT_59_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=59 && BMC_MAX_GLOBAL_POTS > 58 && defined(BMC_GLOBAL_POT_59_X) && defined(BMC_GLOBAL_POT_59_Y)
  case 58: return (x) ? BMC_GLOBAL_POT_59_X : BMC_GLOBAL_POT_59_Y;
#if defined(BMC_GLOBAL_POT_60_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=60 && BMC_MAX_GLOBAL_POTS > 59 && defined(BMC_GLOBAL_POT_60_X) && defined(BMC_GLOBAL_POT_60_Y)
  case 59: return (x) ? BMC_GLOBAL_POT_60_X : BMC_GLOBAL_POT_60_Y;
#if defined(BMC_GLOBAL_POT_61_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=61 && BMC_MAX_GLOBAL_POTS > 60 && defined(BMC_GLOBAL_POT_61_X) && defined(BMC_GLOBAL_POT_61_Y)
  case 60: return (x) ? BMC_GLOBAL_POT_61_X : BMC_GLOBAL_POT_61_Y;
#if defined(BMC_GLOBAL_POT_62_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=62 && BMC_MAX_GLOBAL_POTS > 61 && defined(BMC_GLOBAL_POT_62_X) && defined(BMC_GLOBAL_POT_62_Y)
  case 61: return (x) ? BMC_GLOBAL_POT_62_X : BMC_GLOBAL_POT_62_Y;
#if defined(BMC_GLOBAL_POT_63_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=63 && BMC_MAX_GLOBAL_POTS > 62 && defined(BMC_GLOBAL_POT_63_X) && defined(BMC_GLOBAL_POT_63_Y)
  case 62: return (x) ? BMC_GLOBAL_POT_63_X : BMC_GLOBAL_POT_63_Y;
#if defined(BMC_GLOBAL_POT_64_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=64 && BMC_MAX_GLOBAL_POTS > 63 && defined(BMC_GLOBAL_POT_64_X) && defined(BMC_GLOBAL_POT_64_Y)
  case 63: return (x) ? BMC_GLOBAL_POT_64_X : BMC_GLOBAL_POT_64_Y;
#if defined(BMC_GLOBAL_POT_65_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=65 && BMC_MAX_GLOBAL_POTS > 64 && defined(BMC_GLOBAL_POT_65_X) && defined(BMC_GLOBAL_POT_65_Y)
  case 64: return (x) ? BMC_GLOBAL_POT_65_X : BMC_GLOBAL_POT_65_Y;
#if defined(BMC_GLOBAL_POT_66_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=66 && BMC_MAX_GLOBAL_POTS > 65 && defined(BMC_GLOBAL_POT_66_X) && defined(BMC_GLOBAL_POT_66_Y)
  case 65: return (x) ? BMC_GLOBAL_POT_66_X : BMC_GLOBAL_POT_66_Y;
#if defined(BMC_GLOBAL_POT_67_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=67 && BMC_MAX_GLOBAL_POTS > 66 && defined(BMC_GLOBAL_POT_67_X) && defined(BMC_GLOBAL_POT_67_Y)
  case 66: return (x) ? BMC_GLOBAL_POT_67_X : BMC_GLOBAL_POT_67_Y;
#if defined(BMC_GLOBAL_POT_68_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=68 && BMC_MAX_GLOBAL_POTS > 67 && defined(BMC_GLOBAL_POT_68_X) && defined(BMC_GLOBAL_POT_68_Y)
  case 67: return (x) ? BMC_GLOBAL_POT_68_X : BMC_GLOBAL_POT_68_Y;
#if defined(BMC_GLOBAL_POT_69_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=69 && BMC_MAX_GLOBAL_POTS > 68 && defined(BMC_GLOBAL_POT_69_X) && defined(BMC_GLOBAL_POT_69_Y)
  case 68: return (x) ? BMC_GLOBAL_POT_69_X : BMC_GLOBAL_POT_69_Y;
#if defined(BMC_GLOBAL_POT_70_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=70 && BMC_MAX_GLOBAL_POTS > 69 && defined(BMC_GLOBAL_POT_70_X) && defined(BMC_GLOBAL_POT_70_Y)
  case 69: return (x) ? BMC_GLOBAL_POT_70_X : BMC_GLOBAL_POT_70_Y;
#if defined(BMC_GLOBAL_POT_71_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=71 && BMC_MAX_GLOBAL_POTS > 70 && defined(BMC_GLOBAL_POT_71_X) && defined(BMC_GLOBAL_POT_71_Y)
  case 70: return (x) ? BMC_GLOBAL_POT_71_X : BMC_GLOBAL_POT_71_Y;
#if defined(BMC_GLOBAL_POT_72_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=72 && BMC_MAX_GLOBAL_POTS > 71 && defined(BMC_GLOBAL_POT_72_X) && defined(BMC_GLOBAL_POT_72_Y)
  case 71: return (x) ? BMC_GLOBAL_POT_72_X : BMC_GLOBAL_POT_72_Y;
#if defined(BMC_GLOBAL_POT_73_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=73 && BMC_MAX_GLOBAL_POTS > 72 && defined(BMC_GLOBAL_POT_73_X) && defined(BMC_GLOBAL_POT_73_Y)
  case 72: return (x) ? BMC_GLOBAL_POT_73_X : BMC_GLOBAL_POT_73_Y;
#if defined(BMC_GLOBAL_POT_74_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=74 && BMC_MAX_GLOBAL_POTS > 73 && defined(BMC_GLOBAL_POT_74_X) && defined(BMC_GLOBAL_POT_74_Y)
  case 73: return (x) ? BMC_GLOBAL_POT_74_X : BMC_GLOBAL_POT_74_Y;
#if defined(BMC_GLOBAL_POT_75_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=75 && BMC_MAX_GLOBAL_POTS > 74 && defined(BMC_GLOBAL_POT_75_X) && defined(BMC_GLOBAL_POT_75_Y)
  case 74: return (x) ? BMC_GLOBAL_POT_75_X : BMC_GLOBAL_POT_75_Y;
#if defined(BMC_GLOBAL_POT_76_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=76 && BMC_MAX_GLOBAL_POTS > 75 && defined(BMC_GLOBAL_POT_76_X) && defined(BMC_GLOBAL_POT_76_Y)
  case 75: return (x) ? BMC_GLOBAL_POT_76_X : BMC_GLOBAL_POT_76_Y;
#if defined(BMC_GLOBAL_POT_77_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=77 && BMC_MAX_GLOBAL_POTS > 76 && defined(BMC_GLOBAL_POT_77_X) && defined(BMC_GLOBAL_POT_77_Y)
  case 76: return (x) ? BMC_GLOBAL_POT_77_X : BMC_GLOBAL_POT_77_Y;
#if defined(BMC_GLOBAL_POT_78_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=78 && BMC_MAX_GLOBAL_POTS > 77 && defined(BMC_GLOBAL_POT_78_X) && defined(BMC_GLOBAL_POT_78_Y)
  case 77: return (x) ? BMC_GLOBAL_POT_78_X : BMC_GLOBAL_POT_78_Y;
#if defined(BMC_GLOBAL_POT_79_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=79 && BMC_MAX_GLOBAL_POTS > 78 && defined(BMC_GLOBAL_POT_79_X) && defined(BMC_GLOBAL_POT_79_Y)
  case 78: return (x) ? BMC_GLOBAL_POT_79_X : BMC_GLOBAL_POT_79_Y;
#if defined(BMC_GLOBAL_POT_80_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=80 && BMC_MAX_GLOBAL_POTS > 79 && defined(BMC_GLOBAL_POT_80_X) && defined(BMC_GLOBAL_POT_80_Y)
  case 79: return (x) ? BMC_GLOBAL_POT_80_X : BMC_GLOBAL_POT_80_Y;
#if defined(BMC_GLOBAL_POT_81_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=81 && BMC_MAX_GLOBAL_POTS > 80 && defined(BMC_GLOBAL_POT_81_X) && defined(BMC_GLOBAL_POT_81_Y)
  case 80: return (x) ? BMC_GLOBAL_POT_81_X : BMC_GLOBAL_POT_81_Y;
#if defined(BMC_GLOBAL_POT_82_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=82 && BMC_MAX_GLOBAL_POTS > 81 && defined(BMC_GLOBAL_POT_82_X) && defined(BMC_GLOBAL_POT_82_Y)
  case 81: return (x) ? BMC_GLOBAL_POT_82_X : BMC_GLOBAL_POT_82_Y;
#if defined(BMC_GLOBAL_POT_83_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=83 && BMC_MAX_GLOBAL_POTS > 82 && defined(BMC_GLOBAL_POT_83_X) && defined(BMC_GLOBAL_POT_83_Y)
  case 82: return (x) ? BMC_GLOBAL_POT_83_X : BMC_GLOBAL_POT_83_Y;
#if defined(BMC_GLOBAL_POT_84_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=84 && BMC_MAX_GLOBAL_POTS > 83 && defined(BMC_GLOBAL_POT_84_X) && defined(BMC_GLOBAL_POT_84_Y)
  case 83: return (x) ? BMC_GLOBAL_POT_84_X : BMC_GLOBAL_POT_84_Y;
#if defined(BMC_GLOBAL_POT_85_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=85 && BMC_MAX_GLOBAL_POTS > 84 && defined(BMC_GLOBAL_POT_85_X) && defined(BMC_GLOBAL_POT_85_Y)
  case 84: return (x) ? BMC_GLOBAL_POT_85_X : BMC_GLOBAL_POT_85_Y;
#if defined(BMC_GLOBAL_POT_86_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=86 && BMC_MAX_GLOBAL_POTS > 85 && defined(BMC_GLOBAL_POT_86_X) && defined(BMC_GLOBAL_POT_86_Y)
  case 85: return (x) ? BMC_GLOBAL_POT_86_X : BMC_GLOBAL_POT_86_Y;
#if defined(BMC_GLOBAL_POT_87_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=87 && BMC_MAX_GLOBAL_POTS > 86 && defined(BMC_GLOBAL_POT_87_X) && defined(BMC_GLOBAL_POT_87_Y)
  case 86: return (x) ? BMC_GLOBAL_POT_87_X : BMC_GLOBAL_POT_87_Y;
#if defined(BMC_GLOBAL_POT_88_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=88 && BMC_MAX_GLOBAL_POTS > 87 && defined(BMC_GLOBAL_POT_88_X) && defined(BMC_GLOBAL_POT_88_Y)
  case 87: return (x) ? BMC_GLOBAL_POT_88_X : BMC_GLOBAL_POT_88_Y;
#if defined(BMC_GLOBAL_POT_89_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=89 && BMC_MAX_GLOBAL_POTS > 88 && defined(BMC_GLOBAL_POT_89_X) && defined(BMC_GLOBAL_POT_89_Y)
  case 88: return (x) ? BMC_GLOBAL_POT_89_X : BMC_GLOBAL_POT_89_Y;
#if defined(BMC_GLOBAL_POT_90_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=90 && BMC_MAX_GLOBAL_POTS > 89 && defined(BMC_GLOBAL_POT_90_X) && defined(BMC_GLOBAL_POT_90_Y)
  case 89: return (x) ? BMC_GLOBAL_POT_90_X : BMC_GLOBAL_POT_90_Y;
#if defined(BMC_GLOBAL_POT_91_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=91 && BMC_MAX_GLOBAL_POTS > 90 && defined(BMC_GLOBAL_POT_91_X) && defined(BMC_GLOBAL_POT_91_Y)
  case 90: return (x) ? BMC_GLOBAL_POT_91_X : BMC_GLOBAL_POT_91_Y;
#if defined(BMC_GLOBAL_POT_92_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=92 && BMC_MAX_GLOBAL_POTS > 91 && defined(BMC_GLOBAL_POT_92_X) && defined(BMC_GLOBAL_POT_92_Y)
  case 91: return (x) ? BMC_GLOBAL_POT_92_X : BMC_GLOBAL_POT_92_Y;
#if defined(BMC_GLOBAL_POT_93_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=93 && BMC_MAX_GLOBAL_POTS > 92 && defined(BMC_GLOBAL_POT_93_X) && defined(BMC_GLOBAL_POT_93_Y)
  case 92: return (x) ? BMC_GLOBAL_POT_93_X : BMC_GLOBAL_POT_93_Y;
#if defined(BMC_GLOBAL_POT_94_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=94 && BMC_MAX_GLOBAL_POTS > 93 && defined(BMC_GLOBAL_POT_94_X) && defined(BMC_GLOBAL_POT_94_Y)
  case 93: return (x) ? BMC_GLOBAL_POT_94_X : BMC_GLOBAL_POT_94_Y;
#if defined(BMC_GLOBAL_POT_95_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=95 && BMC_MAX_GLOBAL_POTS > 94 && defined(BMC_GLOBAL_POT_95_X) && defined(BMC_GLOBAL_POT_95_Y)
  case 94: return (x) ? BMC_GLOBAL_POT_95_X : BMC_GLOBAL_POT_95_Y;
#if defined(BMC_GLOBAL_POT_96_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=96 && BMC_MAX_GLOBAL_POTS > 95 && defined(BMC_GLOBAL_POT_96_X) && defined(BMC_GLOBAL_POT_96_Y)
  case 95: return (x) ? BMC_GLOBAL_POT_96_X : BMC_GLOBAL_POT_96_Y;
#if defined(BMC_GLOBAL_POT_97_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=97 && BMC_MAX_GLOBAL_POTS > 96 && defined(BMC_GLOBAL_POT_97_X) && defined(BMC_GLOBAL_POT_97_Y)
  case 96: return (x) ? BMC_GLOBAL_POT_97_X : BMC_GLOBAL_POT_97_Y;
#if defined(BMC_GLOBAL_POT_98_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=98 && BMC_MAX_GLOBAL_POTS > 97 && defined(BMC_GLOBAL_POT_98_X) && defined(BMC_GLOBAL_POT_98_Y)
  case 97: return (x) ? BMC_GLOBAL_POT_98_X : BMC_GLOBAL_POT_98_Y;
#if defined(BMC_GLOBAL_POT_99_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=99 && BMC_MAX_GLOBAL_POTS > 98 && defined(BMC_GLOBAL_POT_99_X) && defined(BMC_GLOBAL_POT_99_Y)
  case 98: return (x) ? BMC_GLOBAL_POT_99_X : BMC_GLOBAL_POT_99_Y;
#if defined(BMC_GLOBAL_POT_100_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=100 && BMC_MAX_GLOBAL_POTS > 99 && defined(BMC_GLOBAL_POT_100_X) && defined(BMC_GLOBAL_POT_100_Y)
  case 99: return (x) ? BMC_GLOBAL_POT_100_X : BMC_GLOBAL_POT_100_Y;
#if defined(BMC_GLOBAL_POT_101_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=101 && BMC_MAX_GLOBAL_POTS > 100 && defined(BMC_GLOBAL_POT_101_X) && defined(BMC_GLOBAL_POT_101_Y)
  case 100: return (x) ? BMC_GLOBAL_POT_101_X : BMC_GLOBAL_POT_101_Y;
#if defined(BMC_GLOBAL_POT_102_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=102 && BMC_MAX_GLOBAL_POTS > 101 && defined(BMC_GLOBAL_POT_102_X) && defined(BMC_GLOBAL_POT_102_Y)
  case 101: return (x) ? BMC_GLOBAL_POT_102_X : BMC_GLOBAL_POT_102_Y;
#if defined(BMC_GLOBAL_POT_103_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=103 && BMC_MAX_GLOBAL_POTS > 102 && defined(BMC_GLOBAL_POT_103_X) && defined(BMC_GLOBAL_POT_103_Y)
  case 102: return (x) ? BMC_GLOBAL_POT_103_X : BMC_GLOBAL_POT_103_Y;
#if defined(BMC_GLOBAL_POT_104_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=104 && BMC_MAX_GLOBAL_POTS > 103 && defined(BMC_GLOBAL_POT_104_X) && defined(BMC_GLOBAL_POT_104_Y)
  case 103: return (x) ? BMC_GLOBAL_POT_104_X : BMC_GLOBAL_POT_104_Y;
#if defined(BMC_GLOBAL_POT_105_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=105 && BMC_MAX_GLOBAL_POTS > 104 && defined(BMC_GLOBAL_POT_105_X) && defined(BMC_GLOBAL_POT_105_Y)
  case 104: return (x) ? BMC_GLOBAL_POT_105_X : BMC_GLOBAL_POT_105_Y;
#if defined(BMC_GLOBAL_POT_106_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=106 && BMC_MAX_GLOBAL_POTS > 105 && defined(BMC_GLOBAL_POT_106_X) && defined(BMC_GLOBAL_POT_106_Y)
  case 105: return (x) ? BMC_GLOBAL_POT_106_X : BMC_GLOBAL_POT_106_Y;
#if defined(BMC_GLOBAL_POT_107_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=107 && BMC_MAX_GLOBAL_POTS > 106 && defined(BMC_GLOBAL_POT_107_X) && defined(BMC_GLOBAL_POT_107_Y)
  case 106: return (x) ? BMC_GLOBAL_POT_107_X : BMC_GLOBAL_POT_107_Y;
#if defined(BMC_GLOBAL_POT_108_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=108 && BMC_MAX_GLOBAL_POTS > 107 && defined(BMC_GLOBAL_POT_108_X) && defined(BMC_GLOBAL_POT_108_Y)
  case 107: return (x) ? BMC_GLOBAL_POT_108_X : BMC_GLOBAL_POT_108_Y;
#if defined(BMC_GLOBAL_POT_109_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=109 && BMC_MAX_GLOBAL_POTS > 108 && defined(BMC_GLOBAL_POT_109_X) && defined(BMC_GLOBAL_POT_109_Y)
  case 108: return (x) ? BMC_GLOBAL_POT_109_X : BMC_GLOBAL_POT_109_Y;
#if defined(BMC_GLOBAL_POT_110_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=110 && BMC_MAX_GLOBAL_POTS > 109 && defined(BMC_GLOBAL_POT_110_X) && defined(BMC_GLOBAL_POT_110_Y)
  case 109: return (x) ? BMC_GLOBAL_POT_110_X : BMC_GLOBAL_POT_110_Y;
#if defined(BMC_GLOBAL_POT_111_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=111 && BMC_MAX_GLOBAL_POTS > 110 && defined(BMC_GLOBAL_POT_111_X) && defined(BMC_GLOBAL_POT_111_Y)
  case 110: return (x) ? BMC_GLOBAL_POT_111_X : BMC_GLOBAL_POT_111_Y;
#if defined(BMC_GLOBAL_POT_112_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=112 && BMC_MAX_GLOBAL_POTS > 111 && defined(BMC_GLOBAL_POT_112_X) && defined(BMC_GLOBAL_POT_112_Y)
  case 111: return (x) ? BMC_GLOBAL_POT_112_X : BMC_GLOBAL_POT_112_Y;
#if defined(BMC_GLOBAL_POT_113_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=113 && BMC_MAX_GLOBAL_POTS > 112 && defined(BMC_GLOBAL_POT_113_X) && defined(BMC_GLOBAL_POT_113_Y)
  case 112: return (x) ? BMC_GLOBAL_POT_113_X : BMC_GLOBAL_POT_113_Y;
#if defined(BMC_GLOBAL_POT_114_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=114 && BMC_MAX_GLOBAL_POTS > 113 && defined(BMC_GLOBAL_POT_114_X) && defined(BMC_GLOBAL_POT_114_Y)
  case 113: return (x) ? BMC_GLOBAL_POT_114_X : BMC_GLOBAL_POT_114_Y;
#if defined(BMC_GLOBAL_POT_115_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=115 && BMC_MAX_GLOBAL_POTS > 114 && defined(BMC_GLOBAL_POT_115_X) && defined(BMC_GLOBAL_POT_115_Y)
  case 114: return (x) ? BMC_GLOBAL_POT_115_X : BMC_GLOBAL_POT_115_Y;
#if defined(BMC_GLOBAL_POT_116_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=116 && BMC_MAX_GLOBAL_POTS > 115 && defined(BMC_GLOBAL_POT_116_X) && defined(BMC_GLOBAL_POT_116_Y)
  case 115: return (x) ? BMC_GLOBAL_POT_116_X : BMC_GLOBAL_POT_116_Y;
#if defined(BMC_GLOBAL_POT_117_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=117 && BMC_MAX_GLOBAL_POTS > 116 && defined(BMC_GLOBAL_POT_117_X) && defined(BMC_GLOBAL_POT_117_Y)
  case 116: return (x) ? BMC_GLOBAL_POT_117_X : BMC_GLOBAL_POT_117_Y;
#if defined(BMC_GLOBAL_POT_118_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=118 && BMC_MAX_GLOBAL_POTS > 117 && defined(BMC_GLOBAL_POT_118_X) && defined(BMC_GLOBAL_POT_118_Y)
  case 117: return (x) ? BMC_GLOBAL_POT_118_X : BMC_GLOBAL_POT_118_Y;
#if defined(BMC_GLOBAL_POT_119_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=119 && BMC_MAX_GLOBAL_POTS > 118 && defined(BMC_GLOBAL_POT_119_X) && defined(BMC_GLOBAL_POT_119_Y)
  case 118: return (x) ? BMC_GLOBAL_POT_119_X : BMC_GLOBAL_POT_119_Y;
#if defined(BMC_GLOBAL_POT_120_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=120 && BMC_MAX_GLOBAL_POTS > 119 && defined(BMC_GLOBAL_POT_120_X) && defined(BMC_GLOBAL_POT_120_Y)
  case 119: return (x) ? BMC_GLOBAL_POT_120_X : BMC_GLOBAL_POT_120_Y;
#if defined(BMC_GLOBAL_POT_121_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=121 && BMC_MAX_GLOBAL_POTS > 120 && defined(BMC_GLOBAL_POT_121_X) && defined(BMC_GLOBAL_POT_121_Y)
  case 120: return (x) ? BMC_GLOBAL_POT_121_X : BMC_GLOBAL_POT_121_Y;
#if defined(BMC_GLOBAL_POT_122_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=122 && BMC_MAX_GLOBAL_POTS > 121 && defined(BMC_GLOBAL_POT_122_X) && defined(BMC_GLOBAL_POT_122_Y)
  case 121: return (x) ? BMC_GLOBAL_POT_122_X : BMC_GLOBAL_POT_122_Y;
#if defined(BMC_GLOBAL_POT_123_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=123 && BMC_MAX_GLOBAL_POTS > 122 && defined(BMC_GLOBAL_POT_123_X) && defined(BMC_GLOBAL_POT_123_Y)
  case 122: return (x) ? BMC_GLOBAL_POT_123_X : BMC_GLOBAL_POT_123_Y;
#if defined(BMC_GLOBAL_POT_124_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=124 && BMC_MAX_GLOBAL_POTS > 123 && defined(BMC_GLOBAL_POT_124_X) && defined(BMC_GLOBAL_POT_124_Y)
  case 123: return (x) ? BMC_GLOBAL_POT_124_X : BMC_GLOBAL_POT_124_Y;
#if defined(BMC_GLOBAL_POT_125_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=125 && BMC_MAX_GLOBAL_POTS > 124 && defined(BMC_GLOBAL_POT_125_X) && defined(BMC_GLOBAL_POT_125_Y)
  case 124: return (x) ? BMC_GLOBAL_POT_125_X : BMC_GLOBAL_POT_125_Y;
#if defined(BMC_GLOBAL_POT_126_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=126 && BMC_MAX_GLOBAL_POTS > 125 && defined(BMC_GLOBAL_POT_126_X) && defined(BMC_GLOBAL_POT_126_Y)
  case 125: return (x) ? BMC_GLOBAL_POT_126_X : BMC_GLOBAL_POT_126_Y;
#if defined(BMC_GLOBAL_POT_127_PIN) && (BMC_TEENSY_TOTAL_ANALOG_PINS+BMC_MAX_MUX_IN_ANALOG)>=127 && BMC_MAX_GLOBAL_POTS > 126 && defined(BMC_GLOBAL_POT_127_X) && defined(BMC_GLOBAL_POT_127_Y)
  case 126: return (x) ? BMC_GLOBAL_POT_127_X : BMC_GLOBAL_POT_127_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getGlobalLedPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_GLOBAL_LEDS > 0
switch(index){
#if defined(BMC_GLOBAL_LED_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_GLOBAL_LEDS > 0 && defined(BMC_GLOBAL_LED_1_X) && defined(BMC_GLOBAL_LED_1_Y)
  case 0: return (x) ? BMC_GLOBAL_LED_1_X : BMC_GLOBAL_LED_1_Y;
#if defined(BMC_GLOBAL_LED_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_GLOBAL_LEDS > 1 && defined(BMC_GLOBAL_LED_2_X) && defined(BMC_GLOBAL_LED_2_Y)
  case 1: return (x) ? BMC_GLOBAL_LED_2_X : BMC_GLOBAL_LED_2_Y;
#if defined(BMC_GLOBAL_LED_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_GLOBAL_LEDS > 2 && defined(BMC_GLOBAL_LED_3_X) && defined(BMC_GLOBAL_LED_3_Y)
  case 2: return (x) ? BMC_GLOBAL_LED_3_X : BMC_GLOBAL_LED_3_Y;
#if defined(BMC_GLOBAL_LED_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_GLOBAL_LEDS > 3 && defined(BMC_GLOBAL_LED_4_X) && defined(BMC_GLOBAL_LED_4_Y)
  case 3: return (x) ? BMC_GLOBAL_LED_4_X : BMC_GLOBAL_LED_4_Y;
#if defined(BMC_GLOBAL_LED_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_GLOBAL_LEDS > 4 && defined(BMC_GLOBAL_LED_5_X) && defined(BMC_GLOBAL_LED_5_Y)
  case 4: return (x) ? BMC_GLOBAL_LED_5_X : BMC_GLOBAL_LED_5_Y;
#if defined(BMC_GLOBAL_LED_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_GLOBAL_LEDS > 5 && defined(BMC_GLOBAL_LED_6_X) && defined(BMC_GLOBAL_LED_6_Y)
  case 5: return (x) ? BMC_GLOBAL_LED_6_X : BMC_GLOBAL_LED_6_Y;
#if defined(BMC_GLOBAL_LED_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_GLOBAL_LEDS > 6 && defined(BMC_GLOBAL_LED_7_X) && defined(BMC_GLOBAL_LED_7_Y)
  case 6: return (x) ? BMC_GLOBAL_LED_7_X : BMC_GLOBAL_LED_7_Y;
#if defined(BMC_GLOBAL_LED_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_GLOBAL_LEDS > 7 && defined(BMC_GLOBAL_LED_8_X) && defined(BMC_GLOBAL_LED_8_Y)
  case 7: return (x) ? BMC_GLOBAL_LED_8_X : BMC_GLOBAL_LED_8_Y;
#if defined(BMC_GLOBAL_LED_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_GLOBAL_LEDS > 8 && defined(BMC_GLOBAL_LED_9_X) && defined(BMC_GLOBAL_LED_9_Y)
  case 8: return (x) ? BMC_GLOBAL_LED_9_X : BMC_GLOBAL_LED_9_Y;
#if defined(BMC_GLOBAL_LED_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_GLOBAL_LEDS > 9 && defined(BMC_GLOBAL_LED_10_X) && defined(BMC_GLOBAL_LED_10_Y)
  case 9: return (x) ? BMC_GLOBAL_LED_10_X : BMC_GLOBAL_LED_10_Y;
#if defined(BMC_GLOBAL_LED_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_GLOBAL_LEDS > 10 && defined(BMC_GLOBAL_LED_11_X) && defined(BMC_GLOBAL_LED_11_Y)
  case 10: return (x) ? BMC_GLOBAL_LED_11_X : BMC_GLOBAL_LED_11_Y;
#if defined(BMC_GLOBAL_LED_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_GLOBAL_LEDS > 11 && defined(BMC_GLOBAL_LED_12_X) && defined(BMC_GLOBAL_LED_12_Y)
  case 11: return (x) ? BMC_GLOBAL_LED_12_X : BMC_GLOBAL_LED_12_Y;
#if defined(BMC_GLOBAL_LED_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_GLOBAL_LEDS > 12 && defined(BMC_GLOBAL_LED_13_X) && defined(BMC_GLOBAL_LED_13_Y)
  case 12: return (x) ? BMC_GLOBAL_LED_13_X : BMC_GLOBAL_LED_13_Y;
#if defined(BMC_GLOBAL_LED_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_GLOBAL_LEDS > 13 && defined(BMC_GLOBAL_LED_14_X) && defined(BMC_GLOBAL_LED_14_Y)
  case 13: return (x) ? BMC_GLOBAL_LED_14_X : BMC_GLOBAL_LED_14_Y;
#if defined(BMC_GLOBAL_LED_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_GLOBAL_LEDS > 14 && defined(BMC_GLOBAL_LED_15_X) && defined(BMC_GLOBAL_LED_15_Y)
  case 14: return (x) ? BMC_GLOBAL_LED_15_X : BMC_GLOBAL_LED_15_Y;
#if defined(BMC_GLOBAL_LED_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_GLOBAL_LEDS > 15 && defined(BMC_GLOBAL_LED_16_X) && defined(BMC_GLOBAL_LED_16_Y)
  case 15: return (x) ? BMC_GLOBAL_LED_16_X : BMC_GLOBAL_LED_16_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getRelayNLPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_NL_RELAYS > 0
switch(index){
#if defined(BMC_NL_RELAY_1_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=1 && BMC_MAX_NL_RELAYS > 0 && defined(BMC_NL_RELAY_1_X) && defined(BMC_NL_RELAY_1_Y)
  case 0: return (x) ? BMC_NL_RELAY_1_X : BMC_NL_RELAY_1_Y;
#if defined(BMC_NL_RELAY_2_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && BMC_MAX_NL_RELAYS > 1 && defined(BMC_NL_RELAY_2_X) && defined(BMC_NL_RELAY_2_Y)
  case 1: return (x) ? BMC_NL_RELAY_2_X : BMC_NL_RELAY_2_Y;
#if defined(BMC_NL_RELAY_3_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=3 && BMC_MAX_NL_RELAYS > 2 && defined(BMC_NL_RELAY_3_X) && defined(BMC_NL_RELAY_3_Y)
  case 2: return (x) ? BMC_NL_RELAY_3_X : BMC_NL_RELAY_3_Y;
#if defined(BMC_NL_RELAY_4_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && BMC_MAX_NL_RELAYS > 3 && defined(BMC_NL_RELAY_4_X) && defined(BMC_NL_RELAY_4_Y)
  case 3: return (x) ? BMC_NL_RELAY_4_X : BMC_NL_RELAY_4_Y;
#if defined(BMC_NL_RELAY_5_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=5 && BMC_MAX_NL_RELAYS > 4 && defined(BMC_NL_RELAY_5_X) && defined(BMC_NL_RELAY_5_Y)
  case 4: return (x) ? BMC_NL_RELAY_5_X : BMC_NL_RELAY_5_Y;
#if defined(BMC_NL_RELAY_6_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && BMC_MAX_NL_RELAYS > 5 && defined(BMC_NL_RELAY_6_X) && defined(BMC_NL_RELAY_6_Y)
  case 5: return (x) ? BMC_NL_RELAY_6_X : BMC_NL_RELAY_6_Y;
#if defined(BMC_NL_RELAY_7_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=7 && BMC_MAX_NL_RELAYS > 6 && defined(BMC_NL_RELAY_7_X) && defined(BMC_NL_RELAY_7_Y)
  case 6: return (x) ? BMC_NL_RELAY_7_X : BMC_NL_RELAY_7_Y;
#if defined(BMC_NL_RELAY_8_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && BMC_MAX_NL_RELAYS > 7 && defined(BMC_NL_RELAY_8_X) && defined(BMC_NL_RELAY_8_Y)
  case 7: return (x) ? BMC_NL_RELAY_8_X : BMC_NL_RELAY_8_Y;
#if defined(BMC_NL_RELAY_9_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=9 && BMC_MAX_NL_RELAYS > 8 && defined(BMC_NL_RELAY_9_X) && defined(BMC_NL_RELAY_9_Y)
  case 8: return (x) ? BMC_NL_RELAY_9_X : BMC_NL_RELAY_9_Y;
#if defined(BMC_NL_RELAY_10_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && BMC_MAX_NL_RELAYS > 9 && defined(BMC_NL_RELAY_10_X) && defined(BMC_NL_RELAY_10_Y)
  case 9: return (x) ? BMC_NL_RELAY_10_X : BMC_NL_RELAY_10_Y;
#if defined(BMC_NL_RELAY_11_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=11 && BMC_MAX_NL_RELAYS > 10 && defined(BMC_NL_RELAY_11_X) && defined(BMC_NL_RELAY_11_Y)
  case 10: return (x) ? BMC_NL_RELAY_11_X : BMC_NL_RELAY_11_Y;
#if defined(BMC_NL_RELAY_12_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && BMC_MAX_NL_RELAYS > 11 && defined(BMC_NL_RELAY_12_X) && defined(BMC_NL_RELAY_12_Y)
  case 11: return (x) ? BMC_NL_RELAY_12_X : BMC_NL_RELAY_12_Y;
#if defined(BMC_NL_RELAY_13_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=13 && BMC_MAX_NL_RELAYS > 12 && defined(BMC_NL_RELAY_13_X) && defined(BMC_NL_RELAY_13_Y)
  case 12: return (x) ? BMC_NL_RELAY_13_X : BMC_NL_RELAY_13_Y;
#if defined(BMC_NL_RELAY_14_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && BMC_MAX_NL_RELAYS > 13 && defined(BMC_NL_RELAY_14_X) && defined(BMC_NL_RELAY_14_Y)
  case 13: return (x) ? BMC_NL_RELAY_14_X : BMC_NL_RELAY_14_Y;
#if defined(BMC_NL_RELAY_15_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=15 && BMC_MAX_NL_RELAYS > 14 && defined(BMC_NL_RELAY_15_X) && defined(BMC_NL_RELAY_15_Y)
  case 14: return (x) ? BMC_NL_RELAY_15_X : BMC_NL_RELAY_15_Y;
#if defined(BMC_NL_RELAY_16_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && BMC_MAX_NL_RELAYS > 15 && defined(BMC_NL_RELAY_16_X) && defined(BMC_NL_RELAY_16_Y)
  case 15: return (x) ? BMC_NL_RELAY_16_X : BMC_NL_RELAY_16_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint16_t getRelayLPosition(uint8_t index=0, bool x=true){
#if BMC_MAX_L_RELAYS > 0
switch(index){
#if defined(BMC_L_RELAY_1A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=2 && defined(BMC_L_RELAY_1B_PIN) && BMC_MAX_L_RELAYS > 0 && defined(BMC_L_RELAY_1_X) && defined(BMC_L_RELAY_1_Y)
  case 0: return (x) ? BMC_L_RELAY_1_X : BMC_L_RELAY_1_Y;
#if defined(BMC_L_RELAY_2A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=4 && defined(BMC_L_RELAY_2B_PIN) && BMC_MAX_L_RELAYS > 1 && defined(BMC_L_RELAY_2_X) && defined(BMC_L_RELAY_2_Y)
  case 1: return (x) ? BMC_L_RELAY_2_X : BMC_L_RELAY_2_Y;
#if defined(BMC_L_RELAY_3A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=6 && defined(BMC_L_RELAY_3B_PIN) && BMC_MAX_L_RELAYS > 2 && defined(BMC_L_RELAY_3_X) && defined(BMC_L_RELAY_3_Y)
  case 2: return (x) ? BMC_L_RELAY_3_X : BMC_L_RELAY_3_Y;
#if defined(BMC_L_RELAY_4A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=8 && defined(BMC_L_RELAY_4B_PIN) && BMC_MAX_L_RELAYS > 3 && defined(BMC_L_RELAY_4_X) && defined(BMC_L_RELAY_4_Y)
  case 3: return (x) ? BMC_L_RELAY_4_X : BMC_L_RELAY_4_Y;
#if defined(BMC_L_RELAY_5A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=10 && defined(BMC_L_RELAY_5B_PIN) && BMC_MAX_L_RELAYS > 4 && defined(BMC_L_RELAY_5_X) && defined(BMC_L_RELAY_5_Y)
  case 4: return (x) ? BMC_L_RELAY_5_X : BMC_L_RELAY_5_Y;
#if defined(BMC_L_RELAY_6A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=12 && defined(BMC_L_RELAY_6B_PIN) && BMC_MAX_L_RELAYS > 5 && defined(BMC_L_RELAY_6_X) && defined(BMC_L_RELAY_6_Y)
  case 5: return (x) ? BMC_L_RELAY_6_X : BMC_L_RELAY_6_Y;
#if defined(BMC_L_RELAY_7A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=14 && defined(BMC_L_RELAY_7B_PIN) && BMC_MAX_L_RELAYS > 6 && defined(BMC_L_RELAY_7_X) && defined(BMC_L_RELAY_7_Y)
  case 6: return (x) ? BMC_L_RELAY_7_X : BMC_L_RELAY_7_Y;
#if defined(BMC_L_RELAY_8A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=16 && defined(BMC_L_RELAY_8B_PIN) && BMC_MAX_L_RELAYS > 7 && defined(BMC_L_RELAY_8_X) && defined(BMC_L_RELAY_8_Y)
  case 7: return (x) ? BMC_L_RELAY_8_X : BMC_L_RELAY_8_Y;
#if defined(BMC_L_RELAY_9A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=18 && defined(BMC_L_RELAY_9B_PIN) && BMC_MAX_L_RELAYS > 8 && defined(BMC_L_RELAY_9_X) && defined(BMC_L_RELAY_9_Y)
  case 8: return (x) ? BMC_L_RELAY_9_X : BMC_L_RELAY_9_Y;
#if defined(BMC_L_RELAY_10A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=20 && defined(BMC_L_RELAY_10B_PIN) && BMC_MAX_L_RELAYS > 9 && defined(BMC_L_RELAY_10_X) && defined(BMC_L_RELAY_10_Y)
  case 9: return (x) ? BMC_L_RELAY_10_X : BMC_L_RELAY_10_Y;
#if defined(BMC_L_RELAY_11A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=22 && defined(BMC_L_RELAY_11B_PIN) && BMC_MAX_L_RELAYS > 10 && defined(BMC_L_RELAY_11_X) && defined(BMC_L_RELAY_11_Y)
  case 10: return (x) ? BMC_L_RELAY_11_X : BMC_L_RELAY_11_Y;
#if defined(BMC_L_RELAY_12A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=24 && defined(BMC_L_RELAY_12B_PIN) && BMC_MAX_L_RELAYS > 11 && defined(BMC_L_RELAY_12_X) && defined(BMC_L_RELAY_12_Y)
  case 11: return (x) ? BMC_L_RELAY_12_X : BMC_L_RELAY_12_Y;
#if defined(BMC_L_RELAY_13A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=26 && defined(BMC_L_RELAY_13B_PIN) && BMC_MAX_L_RELAYS > 12 && defined(BMC_L_RELAY_13_X) && defined(BMC_L_RELAY_13_Y)
  case 12: return (x) ? BMC_L_RELAY_13_X : BMC_L_RELAY_13_Y;
#if defined(BMC_L_RELAY_14A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=28 && defined(BMC_L_RELAY_14B_PIN) && BMC_MAX_L_RELAYS > 13 && defined(BMC_L_RELAY_14_X) && defined(BMC_L_RELAY_14_Y)
  case 13: return (x) ? BMC_L_RELAY_14_X : BMC_L_RELAY_14_Y;
#if defined(BMC_L_RELAY_15A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=30 && defined(BMC_L_RELAY_15B_PIN) && BMC_MAX_L_RELAYS > 14 && defined(BMC_L_RELAY_15_X) && defined(BMC_L_RELAY_15_Y)
  case 14: return (x) ? BMC_L_RELAY_15_X : BMC_L_RELAY_15_Y;
#if defined(BMC_L_RELAY_16A_PIN) && BMC_TEENSY_TOTAL_DIGITAL_PINS>=32 && defined(BMC_L_RELAY_16B_PIN) && BMC_MAX_L_RELAYS > 15 && defined(BMC_L_RELAY_16_X) && defined(BMC_L_RELAY_16_Y)
  case 15: return (x) ? BMC_L_RELAY_16_X : BMC_L_RELAY_16_Y;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
}
#endif
return 0;
}
static uint8_t getButtonLedMergeItem(uint8_t n, uint8_t type){
//type 0=led, 1=button
#if BMC_MAX_LEDS > 0 && BMC_MAX_BUTTONS > 0
switch(n){
#if BMC_MAX_LEDS > 0 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_LED_MERGE_1_LED) && defined(BMC_BUTTON_LED_MERGE_1_BTN)
case 0:
if(type==0){
return BMC_BUTTON_LED_MERGE_1_LED;
} else {
return BMC_BUTTON_LED_MERGE_1_BTN;
}
#endif
#if BMC_MAX_LEDS > 1 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_LED_MERGE_2_LED) && defined(BMC_BUTTON_LED_MERGE_2_BTN)
case 1:
if(type==0){
return BMC_BUTTON_LED_MERGE_2_LED;
} else {
return BMC_BUTTON_LED_MERGE_2_BTN;
}
#endif
#if BMC_MAX_LEDS > 2 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_LED_MERGE_3_LED) && defined(BMC_BUTTON_LED_MERGE_3_BTN)
case 2:
if(type==0){
return BMC_BUTTON_LED_MERGE_3_LED;
} else {
return BMC_BUTTON_LED_MERGE_3_BTN;
}
#endif
#if BMC_MAX_LEDS > 3 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_LED_MERGE_4_LED) && defined(BMC_BUTTON_LED_MERGE_4_BTN)
case 3:
if(type==0){
return BMC_BUTTON_LED_MERGE_4_LED;
} else {
return BMC_BUTTON_LED_MERGE_4_BTN;
}
#endif
#if BMC_MAX_LEDS > 4 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_LED_MERGE_5_LED) && defined(BMC_BUTTON_LED_MERGE_5_BTN)
case 4:
if(type==0){
return BMC_BUTTON_LED_MERGE_5_LED;
} else {
return BMC_BUTTON_LED_MERGE_5_BTN;
}
#endif
#if BMC_MAX_LEDS > 5 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_LED_MERGE_6_LED) && defined(BMC_BUTTON_LED_MERGE_6_BTN)
case 5:
if(type==0){
return BMC_BUTTON_LED_MERGE_6_LED;
} else {
return BMC_BUTTON_LED_MERGE_6_BTN;
}
#endif
#if BMC_MAX_LEDS > 6 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_LED_MERGE_7_LED) && defined(BMC_BUTTON_LED_MERGE_7_BTN)
case 6:
if(type==0){
return BMC_BUTTON_LED_MERGE_7_LED;
} else {
return BMC_BUTTON_LED_MERGE_7_BTN;
}
#endif
#if BMC_MAX_LEDS > 7 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_LED_MERGE_8_LED) && defined(BMC_BUTTON_LED_MERGE_8_BTN)
case 7:
if(type==0){
return BMC_BUTTON_LED_MERGE_8_LED;
} else {
return BMC_BUTTON_LED_MERGE_8_BTN;
}
#endif
#if BMC_MAX_LEDS > 8 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_LED_MERGE_9_LED) && defined(BMC_BUTTON_LED_MERGE_9_BTN)
case 8:
if(type==0){
return BMC_BUTTON_LED_MERGE_9_LED;
} else {
return BMC_BUTTON_LED_MERGE_9_BTN;
}
#endif
#if BMC_MAX_LEDS > 9 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_LED_MERGE_10_LED) && defined(BMC_BUTTON_LED_MERGE_10_BTN)
case 9:
if(type==0){
return BMC_BUTTON_LED_MERGE_10_LED;
} else {
return BMC_BUTTON_LED_MERGE_10_BTN;
}
#endif
#if BMC_MAX_LEDS > 10 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_LED_MERGE_11_LED) && defined(BMC_BUTTON_LED_MERGE_11_BTN)
case 10:
if(type==0){
return BMC_BUTTON_LED_MERGE_11_LED;
} else {
return BMC_BUTTON_LED_MERGE_11_BTN;
}
#endif
#if BMC_MAX_LEDS > 11 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_LED_MERGE_12_LED) && defined(BMC_BUTTON_LED_MERGE_12_BTN)
case 11:
if(type==0){
return BMC_BUTTON_LED_MERGE_12_LED;
} else {
return BMC_BUTTON_LED_MERGE_12_BTN;
}
#endif
#if BMC_MAX_LEDS > 12 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_LED_MERGE_13_LED) && defined(BMC_BUTTON_LED_MERGE_13_BTN)
case 12:
if(type==0){
return BMC_BUTTON_LED_MERGE_13_LED;
} else {
return BMC_BUTTON_LED_MERGE_13_BTN;
}
#endif
#if BMC_MAX_LEDS > 13 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_LED_MERGE_14_LED) && defined(BMC_BUTTON_LED_MERGE_14_BTN)
case 13:
if(type==0){
return BMC_BUTTON_LED_MERGE_14_LED;
} else {
return BMC_BUTTON_LED_MERGE_14_BTN;
}
#endif
#if BMC_MAX_LEDS > 14 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_LED_MERGE_15_LED) && defined(BMC_BUTTON_LED_MERGE_15_BTN)
case 14:
if(type==0){
return BMC_BUTTON_LED_MERGE_15_LED;
} else {
return BMC_BUTTON_LED_MERGE_15_BTN;
}
#endif
#if BMC_MAX_LEDS > 15 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_LED_MERGE_16_LED) && defined(BMC_BUTTON_LED_MERGE_16_BTN)
case 15:
if(type==0){
return BMC_BUTTON_LED_MERGE_16_LED;
} else {
return BMC_BUTTON_LED_MERGE_16_BTN;
}
#endif
#if BMC_MAX_LEDS > 16 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_LED_MERGE_17_LED) && defined(BMC_BUTTON_LED_MERGE_17_BTN)
case 16:
if(type==0){
return BMC_BUTTON_LED_MERGE_17_LED;
} else {
return BMC_BUTTON_LED_MERGE_17_BTN;
}
#endif
#if BMC_MAX_LEDS > 17 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_LED_MERGE_18_LED) && defined(BMC_BUTTON_LED_MERGE_18_BTN)
case 17:
if(type==0){
return BMC_BUTTON_LED_MERGE_18_LED;
} else {
return BMC_BUTTON_LED_MERGE_18_BTN;
}
#endif
#if BMC_MAX_LEDS > 18 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_LED_MERGE_19_LED) && defined(BMC_BUTTON_LED_MERGE_19_BTN)
case 18:
if(type==0){
return BMC_BUTTON_LED_MERGE_19_LED;
} else {
return BMC_BUTTON_LED_MERGE_19_BTN;
}
#endif
#if BMC_MAX_LEDS > 19 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_LED_MERGE_20_LED) && defined(BMC_BUTTON_LED_MERGE_20_BTN)
case 19:
if(type==0){
return BMC_BUTTON_LED_MERGE_20_LED;
} else {
return BMC_BUTTON_LED_MERGE_20_BTN;
}
#endif
#if BMC_MAX_LEDS > 20 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_LED_MERGE_21_LED) && defined(BMC_BUTTON_LED_MERGE_21_BTN)
case 20:
if(type==0){
return BMC_BUTTON_LED_MERGE_21_LED;
} else {
return BMC_BUTTON_LED_MERGE_21_BTN;
}
#endif
#if BMC_MAX_LEDS > 21 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_LED_MERGE_22_LED) && defined(BMC_BUTTON_LED_MERGE_22_BTN)
case 21:
if(type==0){
return BMC_BUTTON_LED_MERGE_22_LED;
} else {
return BMC_BUTTON_LED_MERGE_22_BTN;
}
#endif
#if BMC_MAX_LEDS > 22 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_LED_MERGE_23_LED) && defined(BMC_BUTTON_LED_MERGE_23_BTN)
case 22:
if(type==0){
return BMC_BUTTON_LED_MERGE_23_LED;
} else {
return BMC_BUTTON_LED_MERGE_23_BTN;
}
#endif
#if BMC_MAX_LEDS > 23 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_LED_MERGE_24_LED) && defined(BMC_BUTTON_LED_MERGE_24_BTN)
case 23:
if(type==0){
return BMC_BUTTON_LED_MERGE_24_LED;
} else {
return BMC_BUTTON_LED_MERGE_24_BTN;
}
#endif
#if BMC_MAX_LEDS > 24 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_LED_MERGE_25_LED) && defined(BMC_BUTTON_LED_MERGE_25_BTN)
case 24:
if(type==0){
return BMC_BUTTON_LED_MERGE_25_LED;
} else {
return BMC_BUTTON_LED_MERGE_25_BTN;
}
#endif
#if BMC_MAX_LEDS > 25 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_LED_MERGE_26_LED) && defined(BMC_BUTTON_LED_MERGE_26_BTN)
case 25:
if(type==0){
return BMC_BUTTON_LED_MERGE_26_LED;
} else {
return BMC_BUTTON_LED_MERGE_26_BTN;
}
#endif
#if BMC_MAX_LEDS > 26 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_LED_MERGE_27_LED) && defined(BMC_BUTTON_LED_MERGE_27_BTN)
case 26:
if(type==0){
return BMC_BUTTON_LED_MERGE_27_LED;
} else {
return BMC_BUTTON_LED_MERGE_27_BTN;
}
#endif
#if BMC_MAX_LEDS > 27 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_LED_MERGE_28_LED) && defined(BMC_BUTTON_LED_MERGE_28_BTN)
case 27:
if(type==0){
return BMC_BUTTON_LED_MERGE_28_LED;
} else {
return BMC_BUTTON_LED_MERGE_28_BTN;
}
#endif
#if BMC_MAX_LEDS > 28 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_LED_MERGE_29_LED) && defined(BMC_BUTTON_LED_MERGE_29_BTN)
case 28:
if(type==0){
return BMC_BUTTON_LED_MERGE_29_LED;
} else {
return BMC_BUTTON_LED_MERGE_29_BTN;
}
#endif
#if BMC_MAX_LEDS > 29 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_LED_MERGE_30_LED) && defined(BMC_BUTTON_LED_MERGE_30_BTN)
case 29:
if(type==0){
return BMC_BUTTON_LED_MERGE_30_LED;
} else {
return BMC_BUTTON_LED_MERGE_30_BTN;
}
#endif
#if BMC_MAX_LEDS > 30 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_LED_MERGE_31_LED) && defined(BMC_BUTTON_LED_MERGE_31_BTN)
case 30:
if(type==0){
return BMC_BUTTON_LED_MERGE_31_LED;
} else {
return BMC_BUTTON_LED_MERGE_31_BTN;
}
#endif
#if BMC_MAX_LEDS > 31 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_LED_MERGE_32_LED) && defined(BMC_BUTTON_LED_MERGE_32_BTN)
case 31:
if(type==0){
return BMC_BUTTON_LED_MERGE_32_LED;
} else {
return BMC_BUTTON_LED_MERGE_32_BTN;
}
#endif
}
#endif
return 0;
}
static uint8_t getEncoderMergeItem(uint8_t n, uint8_t type){
//type 0=encoder, 1=button
#if BMC_MAX_ENCODERS > 0 && BMC_MAX_BUTTONS > 0
switch(n){
#if BMC_MAX_ENCODERS > 0 && defined(BMC_ENCODER_MERGE_1_ENC) && defined(BMC_ENCODER_MERGE_1_BTN)
case 0:
if(type==0){
return BMC_ENCODER_MERGE_1_ENC;
} else {
return BMC_ENCODER_MERGE_1_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 1 && defined(BMC_ENCODER_MERGE_2_ENC) && defined(BMC_ENCODER_MERGE_2_BTN)
case 1:
if(type==0){
return BMC_ENCODER_MERGE_2_ENC;
} else {
return BMC_ENCODER_MERGE_2_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 2 && defined(BMC_ENCODER_MERGE_3_ENC) && defined(BMC_ENCODER_MERGE_3_BTN)
case 2:
if(type==0){
return BMC_ENCODER_MERGE_3_ENC;
} else {
return BMC_ENCODER_MERGE_3_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 3 && defined(BMC_ENCODER_MERGE_4_ENC) && defined(BMC_ENCODER_MERGE_4_BTN)
case 3:
if(type==0){
return BMC_ENCODER_MERGE_4_ENC;
} else {
return BMC_ENCODER_MERGE_4_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 4 && defined(BMC_ENCODER_MERGE_5_ENC) && defined(BMC_ENCODER_MERGE_5_BTN)
case 4:
if(type==0){
return BMC_ENCODER_MERGE_5_ENC;
} else {
return BMC_ENCODER_MERGE_5_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 5 && defined(BMC_ENCODER_MERGE_6_ENC) && defined(BMC_ENCODER_MERGE_6_BTN)
case 5:
if(type==0){
return BMC_ENCODER_MERGE_6_ENC;
} else {
return BMC_ENCODER_MERGE_6_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 6 && defined(BMC_ENCODER_MERGE_7_ENC) && defined(BMC_ENCODER_MERGE_7_BTN)
case 6:
if(type==0){
return BMC_ENCODER_MERGE_7_ENC;
} else {
return BMC_ENCODER_MERGE_7_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 7 && defined(BMC_ENCODER_MERGE_8_ENC) && defined(BMC_ENCODER_MERGE_8_BTN)
case 7:
if(type==0){
return BMC_ENCODER_MERGE_8_ENC;
} else {
return BMC_ENCODER_MERGE_8_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 8 && defined(BMC_ENCODER_MERGE_9_ENC) && defined(BMC_ENCODER_MERGE_9_BTN)
case 8:
if(type==0){
return BMC_ENCODER_MERGE_9_ENC;
} else {
return BMC_ENCODER_MERGE_9_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 9 && defined(BMC_ENCODER_MERGE_10_ENC) && defined(BMC_ENCODER_MERGE_10_BTN)
case 9:
if(type==0){
return BMC_ENCODER_MERGE_10_ENC;
} else {
return BMC_ENCODER_MERGE_10_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 10 && defined(BMC_ENCODER_MERGE_11_ENC) && defined(BMC_ENCODER_MERGE_11_BTN)
case 10:
if(type==0){
return BMC_ENCODER_MERGE_11_ENC;
} else {
return BMC_ENCODER_MERGE_11_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 11 && defined(BMC_ENCODER_MERGE_12_ENC) && defined(BMC_ENCODER_MERGE_12_BTN)
case 11:
if(type==0){
return BMC_ENCODER_MERGE_12_ENC;
} else {
return BMC_ENCODER_MERGE_12_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 12 && defined(BMC_ENCODER_MERGE_13_ENC) && defined(BMC_ENCODER_MERGE_13_BTN)
case 12:
if(type==0){
return BMC_ENCODER_MERGE_13_ENC;
} else {
return BMC_ENCODER_MERGE_13_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 13 && defined(BMC_ENCODER_MERGE_14_ENC) && defined(BMC_ENCODER_MERGE_14_BTN)
case 13:
if(type==0){
return BMC_ENCODER_MERGE_14_ENC;
} else {
return BMC_ENCODER_MERGE_14_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 14 && defined(BMC_ENCODER_MERGE_15_ENC) && defined(BMC_ENCODER_MERGE_15_BTN)
case 14:
if(type==0){
return BMC_ENCODER_MERGE_15_ENC;
} else {
return BMC_ENCODER_MERGE_15_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 15 && defined(BMC_ENCODER_MERGE_16_ENC) && defined(BMC_ENCODER_MERGE_16_BTN)
case 15:
if(type==0){
return BMC_ENCODER_MERGE_16_ENC;
} else {
return BMC_ENCODER_MERGE_16_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 16 && defined(BMC_ENCODER_MERGE_17_ENC) && defined(BMC_ENCODER_MERGE_17_BTN)
case 16:
if(type==0){
return BMC_ENCODER_MERGE_17_ENC;
} else {
return BMC_ENCODER_MERGE_17_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 17 && defined(BMC_ENCODER_MERGE_18_ENC) && defined(BMC_ENCODER_MERGE_18_BTN)
case 17:
if(type==0){
return BMC_ENCODER_MERGE_18_ENC;
} else {
return BMC_ENCODER_MERGE_18_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 18 && defined(BMC_ENCODER_MERGE_19_ENC) && defined(BMC_ENCODER_MERGE_19_BTN)
case 18:
if(type==0){
return BMC_ENCODER_MERGE_19_ENC;
} else {
return BMC_ENCODER_MERGE_19_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 19 && defined(BMC_ENCODER_MERGE_20_ENC) && defined(BMC_ENCODER_MERGE_20_BTN)
case 19:
if(type==0){
return BMC_ENCODER_MERGE_20_ENC;
} else {
return BMC_ENCODER_MERGE_20_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 20 && defined(BMC_ENCODER_MERGE_21_ENC) && defined(BMC_ENCODER_MERGE_21_BTN)
case 20:
if(type==0){
return BMC_ENCODER_MERGE_21_ENC;
} else {
return BMC_ENCODER_MERGE_21_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 21 && defined(BMC_ENCODER_MERGE_22_ENC) && defined(BMC_ENCODER_MERGE_22_BTN)
case 21:
if(type==0){
return BMC_ENCODER_MERGE_22_ENC;
} else {
return BMC_ENCODER_MERGE_22_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 22 && defined(BMC_ENCODER_MERGE_23_ENC) && defined(BMC_ENCODER_MERGE_23_BTN)
case 22:
if(type==0){
return BMC_ENCODER_MERGE_23_ENC;
} else {
return BMC_ENCODER_MERGE_23_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 23 && defined(BMC_ENCODER_MERGE_24_ENC) && defined(BMC_ENCODER_MERGE_24_BTN)
case 23:
if(type==0){
return BMC_ENCODER_MERGE_24_ENC;
} else {
return BMC_ENCODER_MERGE_24_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 24 && defined(BMC_ENCODER_MERGE_25_ENC) && defined(BMC_ENCODER_MERGE_25_BTN)
case 24:
if(type==0){
return BMC_ENCODER_MERGE_25_ENC;
} else {
return BMC_ENCODER_MERGE_25_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 25 && defined(BMC_ENCODER_MERGE_26_ENC) && defined(BMC_ENCODER_MERGE_26_BTN)
case 25:
if(type==0){
return BMC_ENCODER_MERGE_26_ENC;
} else {
return BMC_ENCODER_MERGE_26_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 26 && defined(BMC_ENCODER_MERGE_27_ENC) && defined(BMC_ENCODER_MERGE_27_BTN)
case 26:
if(type==0){
return BMC_ENCODER_MERGE_27_ENC;
} else {
return BMC_ENCODER_MERGE_27_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 27 && defined(BMC_ENCODER_MERGE_28_ENC) && defined(BMC_ENCODER_MERGE_28_BTN)
case 27:
if(type==0){
return BMC_ENCODER_MERGE_28_ENC;
} else {
return BMC_ENCODER_MERGE_28_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 28 && defined(BMC_ENCODER_MERGE_29_ENC) && defined(BMC_ENCODER_MERGE_29_BTN)
case 28:
if(type==0){
return BMC_ENCODER_MERGE_29_ENC;
} else {
return BMC_ENCODER_MERGE_29_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 29 && defined(BMC_ENCODER_MERGE_30_ENC) && defined(BMC_ENCODER_MERGE_30_BTN)
case 29:
if(type==0){
return BMC_ENCODER_MERGE_30_ENC;
} else {
return BMC_ENCODER_MERGE_30_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 30 && defined(BMC_ENCODER_MERGE_31_ENC) && defined(BMC_ENCODER_MERGE_31_BTN)
case 30:
if(type==0){
return BMC_ENCODER_MERGE_31_ENC;
} else {
return BMC_ENCODER_MERGE_31_BTN;
}
#endif
#if BMC_MAX_ENCODERS > 31 && defined(BMC_ENCODER_MERGE_32_ENC) && defined(BMC_ENCODER_MERGE_32_BTN)
case 31:
if(type==0){
return BMC_ENCODER_MERGE_32_ENC;
} else {
return BMC_ENCODER_MERGE_32_BTN;
}
#endif
}
#endif
return 0;
}
static uint8_t getPotMergeItem(uint8_t n, uint8_t type){
//type 0=pot, 1=button, 2=enable button
#if BMC_MAX_POTS > 0 && BMC_MAX_BUTTONS > 1
switch(n){
#if BMC_MAX_POTS > 0 && defined(BMC_AUX_JACK_1_POT) && defined(BMC_AUX_JACK_1_BTN) && defined(BMC_AUX_JACK_1_BTN_EN)
case 0:
if(type==0){
return BMC_AUX_JACK_1_POT;
} else if(type==1){
return BMC_AUX_JACK_1_BTN;
} else {
return BMC_AUX_JACK_1_BTN_EN;
}
#endif
#if BMC_MAX_POTS > 1 && defined(BMC_AUX_JACK_2_POT) && defined(BMC_AUX_JACK_2_BTN) && defined(BMC_AUX_JACK_2_BTN_EN)
case 1:
if(type==0){
return BMC_AUX_JACK_2_POT;
} else if(type==1){
return BMC_AUX_JACK_2_BTN;
} else {
return BMC_AUX_JACK_2_BTN_EN;
}
#endif
#if BMC_MAX_POTS > 2 && defined(BMC_AUX_JACK_3_POT) && defined(BMC_AUX_JACK_3_BTN) && defined(BMC_AUX_JACK_3_BTN_EN)
case 2:
if(type==0){
return BMC_AUX_JACK_3_POT;
} else if(type==1){
return BMC_AUX_JACK_3_BTN;
} else {
return BMC_AUX_JACK_3_BTN_EN;
}
#endif
#if BMC_MAX_POTS > 3 && defined(BMC_AUX_JACK_4_POT) && defined(BMC_AUX_JACK_4_BTN) && defined(BMC_AUX_JACK_4_BTN_EN)
case 3:
if(type==0){
return BMC_AUX_JACK_4_POT;
} else if(type==1){
return BMC_AUX_JACK_4_BTN;
} else {
return BMC_AUX_JACK_4_BTN_EN;
}
#endif
}
#endif
return 255;
}
static uint8_t getBiLedMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_LEDS >= 2
switch(n){
#if BMC_MAX_LEDS >= 2  && defined(BMC_BI_LED_MERGE_1_LED) && defined(BMC_BI_LED_MERGE_1_LED2)
case 0:
if(type==0){
return BMC_BI_LED_MERGE_1_LED;
} else {
return BMC_BI_LED_MERGE_1_LED2;
}
#endif
#if BMC_MAX_LEDS >= 4  && defined(BMC_BI_LED_MERGE_2_LED) && defined(BMC_BI_LED_MERGE_2_LED2)
case 1:
if(type==0){
return BMC_BI_LED_MERGE_2_LED;
} else {
return BMC_BI_LED_MERGE_2_LED2;
}
#endif
#if BMC_MAX_LEDS >= 6  && defined(BMC_BI_LED_MERGE_3_LED) && defined(BMC_BI_LED_MERGE_3_LED2)
case 2:
if(type==0){
return BMC_BI_LED_MERGE_3_LED;
} else {
return BMC_BI_LED_MERGE_3_LED2;
}
#endif
#if BMC_MAX_LEDS >= 8  && defined(BMC_BI_LED_MERGE_4_LED) && defined(BMC_BI_LED_MERGE_4_LED2)
case 3:
if(type==0){
return BMC_BI_LED_MERGE_4_LED;
} else {
return BMC_BI_LED_MERGE_4_LED2;
}
#endif
#if BMC_MAX_LEDS >= 10  && defined(BMC_BI_LED_MERGE_5_LED) && defined(BMC_BI_LED_MERGE_5_LED2)
case 4:
if(type==0){
return BMC_BI_LED_MERGE_5_LED;
} else {
return BMC_BI_LED_MERGE_5_LED2;
}
#endif
#if BMC_MAX_LEDS >= 12  && defined(BMC_BI_LED_MERGE_6_LED) && defined(BMC_BI_LED_MERGE_6_LED2)
case 5:
if(type==0){
return BMC_BI_LED_MERGE_6_LED;
} else {
return BMC_BI_LED_MERGE_6_LED2;
}
#endif
#if BMC_MAX_LEDS >= 14  && defined(BMC_BI_LED_MERGE_7_LED) && defined(BMC_BI_LED_MERGE_7_LED2)
case 6:
if(type==0){
return BMC_BI_LED_MERGE_7_LED;
} else {
return BMC_BI_LED_MERGE_7_LED2;
}
#endif
#if BMC_MAX_LEDS >= 16  && defined(BMC_BI_LED_MERGE_8_LED) && defined(BMC_BI_LED_MERGE_8_LED2)
case 7:
if(type==0){
return BMC_BI_LED_MERGE_8_LED;
} else {
return BMC_BI_LED_MERGE_8_LED2;
}
#endif
#if BMC_MAX_LEDS >= 18  && defined(BMC_BI_LED_MERGE_9_LED) && defined(BMC_BI_LED_MERGE_9_LED2)
case 8:
if(type==0){
return BMC_BI_LED_MERGE_9_LED;
} else {
return BMC_BI_LED_MERGE_9_LED2;
}
#endif
#if BMC_MAX_LEDS >= 20  && defined(BMC_BI_LED_MERGE_10_LED) && defined(BMC_BI_LED_MERGE_10_LED2)
case 9:
if(type==0){
return BMC_BI_LED_MERGE_10_LED;
} else {
return BMC_BI_LED_MERGE_10_LED2;
}
#endif
#if BMC_MAX_LEDS >= 22  && defined(BMC_BI_LED_MERGE_11_LED) && defined(BMC_BI_LED_MERGE_11_LED2)
case 10:
if(type==0){
return BMC_BI_LED_MERGE_11_LED;
} else {
return BMC_BI_LED_MERGE_11_LED2;
}
#endif
#if BMC_MAX_LEDS >= 24  && defined(BMC_BI_LED_MERGE_12_LED) && defined(BMC_BI_LED_MERGE_12_LED2)
case 11:
if(type==0){
return BMC_BI_LED_MERGE_12_LED;
} else {
return BMC_BI_LED_MERGE_12_LED2;
}
#endif
#if BMC_MAX_LEDS >= 26  && defined(BMC_BI_LED_MERGE_13_LED) && defined(BMC_BI_LED_MERGE_13_LED2)
case 12:
if(type==0){
return BMC_BI_LED_MERGE_13_LED;
} else {
return BMC_BI_LED_MERGE_13_LED2;
}
#endif
#if BMC_MAX_LEDS >= 28  && defined(BMC_BI_LED_MERGE_14_LED) && defined(BMC_BI_LED_MERGE_14_LED2)
case 13:
if(type==0){
return BMC_BI_LED_MERGE_14_LED;
} else {
return BMC_BI_LED_MERGE_14_LED2;
}
#endif
#if BMC_MAX_LEDS >= 30  && defined(BMC_BI_LED_MERGE_15_LED) && defined(BMC_BI_LED_MERGE_15_LED2)
case 14:
if(type==0){
return BMC_BI_LED_MERGE_15_LED;
} else {
return BMC_BI_LED_MERGE_15_LED2;
}
#endif
#if BMC_MAX_LEDS >= 32  && defined(BMC_BI_LED_MERGE_16_LED) && defined(BMC_BI_LED_MERGE_16_LED2)
case 15:
if(type==0){
return BMC_BI_LED_MERGE_16_LED;
} else {
return BMC_BI_LED_MERGE_16_LED2;
}
#endif
}
#endif
return 255;
}
static uint8_t getRgbLedMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_LEDS >= 3
switch(n){
#if BMC_MAX_LEDS >= 3  && defined(BMC_RGB_LED_MERGE_1_LED) && defined(BMC_RGB_LED_MERGE_1_LED2) && defined(BMC_RGB_LED_MERGE_1_LED3)
case 0:
if(type==0){
return BMC_RGB_LED_MERGE_1_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_1_LED2;
} else {
return BMC_RGB_LED_MERGE_1_LED3;
}
#endif
#if BMC_MAX_LEDS >= 6  && defined(BMC_RGB_LED_MERGE_2_LED) && defined(BMC_RGB_LED_MERGE_2_LED2) && defined(BMC_RGB_LED_MERGE_2_LED3)
case 1:
if(type==0){
return BMC_RGB_LED_MERGE_2_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_2_LED2;
} else {
return BMC_RGB_LED_MERGE_2_LED3;
}
#endif
#if BMC_MAX_LEDS >= 9  && defined(BMC_RGB_LED_MERGE_3_LED) && defined(BMC_RGB_LED_MERGE_3_LED2) && defined(BMC_RGB_LED_MERGE_3_LED3)
case 2:
if(type==0){
return BMC_RGB_LED_MERGE_3_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_3_LED2;
} else {
return BMC_RGB_LED_MERGE_3_LED3;
}
#endif
#if BMC_MAX_LEDS >= 12  && defined(BMC_RGB_LED_MERGE_4_LED) && defined(BMC_RGB_LED_MERGE_4_LED2) && defined(BMC_RGB_LED_MERGE_4_LED3)
case 3:
if(type==0){
return BMC_RGB_LED_MERGE_4_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_4_LED2;
} else {
return BMC_RGB_LED_MERGE_4_LED3;
}
#endif
#if BMC_MAX_LEDS >= 15  && defined(BMC_RGB_LED_MERGE_5_LED) && defined(BMC_RGB_LED_MERGE_5_LED2) && defined(BMC_RGB_LED_MERGE_5_LED3)
case 4:
if(type==0){
return BMC_RGB_LED_MERGE_5_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_5_LED2;
} else {
return BMC_RGB_LED_MERGE_5_LED3;
}
#endif
#if BMC_MAX_LEDS >= 18  && defined(BMC_RGB_LED_MERGE_6_LED) && defined(BMC_RGB_LED_MERGE_6_LED2) && defined(BMC_RGB_LED_MERGE_6_LED3)
case 5:
if(type==0){
return BMC_RGB_LED_MERGE_6_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_6_LED2;
} else {
return BMC_RGB_LED_MERGE_6_LED3;
}
#endif
#if BMC_MAX_LEDS >= 21  && defined(BMC_RGB_LED_MERGE_7_LED) && defined(BMC_RGB_LED_MERGE_7_LED2) && defined(BMC_RGB_LED_MERGE_7_LED3)
case 6:
if(type==0){
return BMC_RGB_LED_MERGE_7_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_7_LED2;
} else {
return BMC_RGB_LED_MERGE_7_LED3;
}
#endif
#if BMC_MAX_LEDS >= 24  && defined(BMC_RGB_LED_MERGE_8_LED) && defined(BMC_RGB_LED_MERGE_8_LED2) && defined(BMC_RGB_LED_MERGE_8_LED3)
case 7:
if(type==0){
return BMC_RGB_LED_MERGE_8_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_8_LED2;
} else {
return BMC_RGB_LED_MERGE_8_LED3;
}
#endif
#if BMC_MAX_LEDS >= 27  && defined(BMC_RGB_LED_MERGE_9_LED) && defined(BMC_RGB_LED_MERGE_9_LED2) && defined(BMC_RGB_LED_MERGE_9_LED3)
case 8:
if(type==0){
return BMC_RGB_LED_MERGE_9_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_9_LED2;
} else {
return BMC_RGB_LED_MERGE_9_LED3;
}
#endif
#if BMC_MAX_LEDS >= 30  && defined(BMC_RGB_LED_MERGE_10_LED) && defined(BMC_RGB_LED_MERGE_10_LED2) && defined(BMC_RGB_LED_MERGE_10_LED3)
case 9:
if(type==0){
return BMC_RGB_LED_MERGE_10_LED;
} else if(type==1){
return BMC_RGB_LED_MERGE_10_LED2;
} else {
return BMC_RGB_LED_MERGE_10_LED3;
}
#endif
}
#endif
return 255;
}
static uint8_t getBiGlobalLedMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_GLOBAL_LEDS >= 2
switch(n){
#if BMC_MAX_GLOBAL_LEDS >= 2  && defined(BMC_BI_GLOBAL_LED_MERGE_1_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_1_LED2)
case 0:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_1_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_1_LED2;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 4  && defined(BMC_BI_GLOBAL_LED_MERGE_2_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_2_LED2)
case 1:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_2_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_2_LED2;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 6  && defined(BMC_BI_GLOBAL_LED_MERGE_3_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_3_LED2)
case 2:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_3_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_3_LED2;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 8  && defined(BMC_BI_GLOBAL_LED_MERGE_4_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_4_LED2)
case 3:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_4_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_4_LED2;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 10  && defined(BMC_BI_GLOBAL_LED_MERGE_5_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_5_LED2)
case 4:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_5_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_5_LED2;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 12  && defined(BMC_BI_GLOBAL_LED_MERGE_6_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_6_LED2)
case 5:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_6_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_6_LED2;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 14  && defined(BMC_BI_GLOBAL_LED_MERGE_7_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_7_LED2)
case 6:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_7_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_7_LED2;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 16  && defined(BMC_BI_GLOBAL_LED_MERGE_8_LED) && defined(BMC_BI_GLOBAL_LED_MERGE_8_LED2)
case 7:
if(type==0){
return BMC_BI_GLOBAL_LED_MERGE_8_LED;
} else {
return BMC_BI_GLOBAL_LED_MERGE_8_LED2;
}
#endif
}
#endif
return 255;
}
static uint8_t getRgbGlobalLedMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_GLOBAL_LEDS >= 3
switch(n){
#if BMC_MAX_GLOBAL_LEDS >= 3  && defined(BMC_RGB_GLOBAL_LED_MERGE_1_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_1_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_1_LED3)
case 0:
if(type==0){
return BMC_RGB_GLOBAL_LED_MERGE_1_LED;
} else if(type==1){
return BMC_RGB_GLOBAL_LED_MERGE_1_LED2;
} else {
return BMC_RGB_GLOBAL_LED_MERGE_1_LED3;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 6  && defined(BMC_RGB_GLOBAL_LED_MERGE_2_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_2_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_2_LED3)
case 1:
if(type==0){
return BMC_RGB_GLOBAL_LED_MERGE_2_LED;
} else if(type==1){
return BMC_RGB_GLOBAL_LED_MERGE_2_LED2;
} else {
return BMC_RGB_GLOBAL_LED_MERGE_2_LED3;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 9  && defined(BMC_RGB_GLOBAL_LED_MERGE_3_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_3_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_3_LED3)
case 2:
if(type==0){
return BMC_RGB_GLOBAL_LED_MERGE_3_LED;
} else if(type==1){
return BMC_RGB_GLOBAL_LED_MERGE_3_LED2;
} else {
return BMC_RGB_GLOBAL_LED_MERGE_3_LED3;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 12  && defined(BMC_RGB_GLOBAL_LED_MERGE_4_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_4_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_4_LED3)
case 3:
if(type==0){
return BMC_RGB_GLOBAL_LED_MERGE_4_LED;
} else if(type==1){
return BMC_RGB_GLOBAL_LED_MERGE_4_LED2;
} else {
return BMC_RGB_GLOBAL_LED_MERGE_4_LED3;
}
#endif
#if BMC_MAX_GLOBAL_LEDS >= 15  && defined(BMC_RGB_GLOBAL_LED_MERGE_5_LED) && defined(BMC_RGB_GLOBAL_LED_MERGE_5_LED2) && defined(BMC_RGB_GLOBAL_LED_MERGE_5_LED3)
case 4:
if(type==0){
return BMC_RGB_GLOBAL_LED_MERGE_5_LED;
} else if(type==1){
return BMC_RGB_GLOBAL_LED_MERGE_5_LED2;
} else {
return BMC_RGB_GLOBAL_LED_MERGE_5_LED3;
}
#endif
}
#endif
return 255;
}
static uint8_t getBiPwmLedMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_PWM_LEDS >= 2
switch(n){
#if BMC_MAX_PWM_LEDS >= 2  && defined(BMC_BI_PWM_LED_MERGE_1_LED) && defined(BMC_BI_PWM_LED_MERGE_1_LED2)
case 0:
if(type==0){
return BMC_BI_PWM_LED_MERGE_1_LED;
} else {
return BMC_BI_PWM_LED_MERGE_1_LED2;
}
#endif
#if BMC_MAX_PWM_LEDS >= 4  && defined(BMC_BI_PWM_LED_MERGE_2_LED) && defined(BMC_BI_PWM_LED_MERGE_2_LED2)
case 1:
if(type==0){
return BMC_BI_PWM_LED_MERGE_2_LED;
} else {
return BMC_BI_PWM_LED_MERGE_2_LED2;
}
#endif
#if BMC_MAX_PWM_LEDS >= 6  && defined(BMC_BI_PWM_LED_MERGE_3_LED) && defined(BMC_BI_PWM_LED_MERGE_3_LED2)
case 2:
if(type==0){
return BMC_BI_PWM_LED_MERGE_3_LED;
} else {
return BMC_BI_PWM_LED_MERGE_3_LED2;
}
#endif
#if BMC_MAX_PWM_LEDS >= 8  && defined(BMC_BI_PWM_LED_MERGE_4_LED) && defined(BMC_BI_PWM_LED_MERGE_4_LED2)
case 3:
if(type==0){
return BMC_BI_PWM_LED_MERGE_4_LED;
} else {
return BMC_BI_PWM_LED_MERGE_4_LED2;
}
#endif
#if BMC_MAX_PWM_LEDS >= 10  && defined(BMC_BI_PWM_LED_MERGE_5_LED) && defined(BMC_BI_PWM_LED_MERGE_5_LED2)
case 4:
if(type==0){
return BMC_BI_PWM_LED_MERGE_5_LED;
} else {
return BMC_BI_PWM_LED_MERGE_5_LED2;
}
#endif
#if BMC_MAX_PWM_LEDS >= 12  && defined(BMC_BI_PWM_LED_MERGE_6_LED) && defined(BMC_BI_PWM_LED_MERGE_6_LED2)
case 5:
if(type==0){
return BMC_BI_PWM_LED_MERGE_6_LED;
} else {
return BMC_BI_PWM_LED_MERGE_6_LED2;
}
#endif
#if BMC_MAX_PWM_LEDS >= 14  && defined(BMC_BI_PWM_LED_MERGE_7_LED) && defined(BMC_BI_PWM_LED_MERGE_7_LED2)
case 6:
if(type==0){
return BMC_BI_PWM_LED_MERGE_7_LED;
} else {
return BMC_BI_PWM_LED_MERGE_7_LED2;
}
#endif
#if BMC_MAX_PWM_LEDS >= 16  && defined(BMC_BI_PWM_LED_MERGE_8_LED) && defined(BMC_BI_PWM_LED_MERGE_8_LED2)
case 7:
if(type==0){
return BMC_BI_PWM_LED_MERGE_8_LED;
} else {
return BMC_BI_PWM_LED_MERGE_8_LED2;
}
#endif
}
#endif
return 255;
}
static uint8_t getRgbPwmLedMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_PWM_LEDS >= 3
switch(n){
#if BMC_MAX_PWM_LEDS >= 3  && defined(BMC_RGB_PWM_LED_MERGE_1_LED) && defined(BMC_RGB_PWM_LED_MERGE_1_LED2) && defined(BMC_RGB_PWM_LED_MERGE_1_LED3)
case 0:
if(type==0){
return BMC_RGB_PWM_LED_MERGE_1_LED;
} else if(type==1){
return BMC_RGB_PWM_LED_MERGE_1_LED2;
} else {
return BMC_RGB_PWM_LED_MERGE_1_LED3;
}
#endif
#if BMC_MAX_PWM_LEDS >= 6  && defined(BMC_RGB_PWM_LED_MERGE_2_LED) && defined(BMC_RGB_PWM_LED_MERGE_2_LED2) && defined(BMC_RGB_PWM_LED_MERGE_2_LED3)
case 1:
if(type==0){
return BMC_RGB_PWM_LED_MERGE_2_LED;
} else if(type==1){
return BMC_RGB_PWM_LED_MERGE_2_LED2;
} else {
return BMC_RGB_PWM_LED_MERGE_2_LED3;
}
#endif
#if BMC_MAX_PWM_LEDS >= 9  && defined(BMC_RGB_PWM_LED_MERGE_3_LED) && defined(BMC_RGB_PWM_LED_MERGE_3_LED2) && defined(BMC_RGB_PWM_LED_MERGE_3_LED3)
case 2:
if(type==0){
return BMC_RGB_PWM_LED_MERGE_3_LED;
} else if(type==1){
return BMC_RGB_PWM_LED_MERGE_3_LED2;
} else {
return BMC_RGB_PWM_LED_MERGE_3_LED3;
}
#endif
#if BMC_MAX_PWM_LEDS >= 12  && defined(BMC_RGB_PWM_LED_MERGE_4_LED) && defined(BMC_RGB_PWM_LED_MERGE_4_LED2) && defined(BMC_RGB_PWM_LED_MERGE_4_LED3)
case 3:
if(type==0){
return BMC_RGB_PWM_LED_MERGE_4_LED;
} else if(type==1){
return BMC_RGB_PWM_LED_MERGE_4_LED2;
} else {
return BMC_RGB_PWM_LED_MERGE_4_LED3;
}
#endif
#if BMC_MAX_PWM_LEDS >= 15  && defined(BMC_RGB_PWM_LED_MERGE_5_LED) && defined(BMC_RGB_PWM_LED_MERGE_5_LED2) && defined(BMC_RGB_PWM_LED_MERGE_5_LED3)
case 4:
if(type==0){
return BMC_RGB_PWM_LED_MERGE_5_LED;
} else if(type==1){
return BMC_RGB_PWM_LED_MERGE_5_LED2;
} else {
return BMC_RGB_PWM_LED_MERGE_5_LED3;
}
#endif
}
#endif
return 255;
}
static uint8_t getRelayLMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_L_RELAYS >= 2
switch(n){
#if BMC_MAX_L_RELAYS >= 2  && defined(BMC_RELAY_L_MERGE_1_RELAY) && defined(BMC_RELAY_L_MERGE_1_RELAY2)
case 0:
if(type==0){
return BMC_RELAY_L_MERGE_1_RELAY;
} else {
return BMC_RELAY_L_MERGE_1_RELAY2;
}
#endif
#if BMC_MAX_L_RELAYS >= 4  && defined(BMC_RELAY_L_MERGE_2_RELAY) && defined(BMC_RELAY_L_MERGE_2_RELAY2)
case 1:
if(type==0){
return BMC_RELAY_L_MERGE_2_RELAY;
} else {
return BMC_RELAY_L_MERGE_2_RELAY2;
}
#endif
#if BMC_MAX_L_RELAYS >= 6  && defined(BMC_RELAY_L_MERGE_3_RELAY) && defined(BMC_RELAY_L_MERGE_3_RELAY2)
case 2:
if(type==0){
return BMC_RELAY_L_MERGE_3_RELAY;
} else {
return BMC_RELAY_L_MERGE_3_RELAY2;
}
#endif
#if BMC_MAX_L_RELAYS >= 8  && defined(BMC_RELAY_L_MERGE_4_RELAY) && defined(BMC_RELAY_L_MERGE_4_RELAY2)
case 3:
if(type==0){
return BMC_RELAY_L_MERGE_4_RELAY;
} else {
return BMC_RELAY_L_MERGE_4_RELAY2;
}
#endif
#if BMC_MAX_L_RELAYS >= 10  && defined(BMC_RELAY_L_MERGE_5_RELAY) && defined(BMC_RELAY_L_MERGE_5_RELAY2)
case 4:
if(type==0){
return BMC_RELAY_L_MERGE_5_RELAY;
} else {
return BMC_RELAY_L_MERGE_5_RELAY2;
}
#endif
#if BMC_MAX_L_RELAYS >= 12  && defined(BMC_RELAY_L_MERGE_6_RELAY) && defined(BMC_RELAY_L_MERGE_6_RELAY2)
case 5:
if(type==0){
return BMC_RELAY_L_MERGE_6_RELAY;
} else {
return BMC_RELAY_L_MERGE_6_RELAY2;
}
#endif
#if BMC_MAX_L_RELAYS >= 14  && defined(BMC_RELAY_L_MERGE_7_RELAY) && defined(BMC_RELAY_L_MERGE_7_RELAY2)
case 6:
if(type==0){
return BMC_RELAY_L_MERGE_7_RELAY;
} else {
return BMC_RELAY_L_MERGE_7_RELAY2;
}
#endif
#if BMC_MAX_L_RELAYS >= 16  && defined(BMC_RELAY_L_MERGE_8_RELAY) && defined(BMC_RELAY_L_MERGE_8_RELAY2)
case 7:
if(type==0){
return BMC_RELAY_L_MERGE_8_RELAY;
} else {
return BMC_RELAY_L_MERGE_8_RELAY2;
}
#endif
}
#endif
return 255;
}
static uint8_t getRelayNLMergeItem(uint8_t n, uint8_t type){
#if BMC_MAX_NL_RELAYS >= 2
switch(n){
#if BMC_MAX_NL_RELAYS >= 2  && defined(BMC_RELAY_NL_MERGE_1_RELAY) && defined(BMC_RELAY_NL_MERGE_1_RELAY2)
case 0:
if(type==0){
return BMC_RELAY_NL_MERGE_1_RELAY;
} else {
return BMC_RELAY_NL_MERGE_1_RELAY2;
}
#endif
#if BMC_MAX_NL_RELAYS >= 4  && defined(BMC_RELAY_NL_MERGE_2_RELAY) && defined(BMC_RELAY_NL_MERGE_2_RELAY2)
case 1:
if(type==0){
return BMC_RELAY_NL_MERGE_2_RELAY;
} else {
return BMC_RELAY_NL_MERGE_2_RELAY2;
}
#endif
#if BMC_MAX_NL_RELAYS >= 6  && defined(BMC_RELAY_NL_MERGE_3_RELAY) && defined(BMC_RELAY_NL_MERGE_3_RELAY2)
case 2:
if(type==0){
return BMC_RELAY_NL_MERGE_3_RELAY;
} else {
return BMC_RELAY_NL_MERGE_3_RELAY2;
}
#endif
#if BMC_MAX_NL_RELAYS >= 8  && defined(BMC_RELAY_NL_MERGE_4_RELAY) && defined(BMC_RELAY_NL_MERGE_4_RELAY2)
case 3:
if(type==0){
return BMC_RELAY_NL_MERGE_4_RELAY;
} else {
return BMC_RELAY_NL_MERGE_4_RELAY2;
}
#endif
#if BMC_MAX_NL_RELAYS >= 10  && defined(BMC_RELAY_NL_MERGE_5_RELAY) && defined(BMC_RELAY_NL_MERGE_5_RELAY2)
case 4:
if(type==0){
return BMC_RELAY_NL_MERGE_5_RELAY;
} else {
return BMC_RELAY_NL_MERGE_5_RELAY2;
}
#endif
#if BMC_MAX_NL_RELAYS >= 12  && defined(BMC_RELAY_NL_MERGE_6_RELAY) && defined(BMC_RELAY_NL_MERGE_6_RELAY2)
case 5:
if(type==0){
return BMC_RELAY_NL_MERGE_6_RELAY;
} else {
return BMC_RELAY_NL_MERGE_6_RELAY2;
}
#endif
#if BMC_MAX_NL_RELAYS >= 14  && defined(BMC_RELAY_NL_MERGE_7_RELAY) && defined(BMC_RELAY_NL_MERGE_7_RELAY2)
case 6:
if(type==0){
return BMC_RELAY_NL_MERGE_7_RELAY;
} else {
return BMC_RELAY_NL_MERGE_7_RELAY2;
}
#endif
#if BMC_MAX_NL_RELAYS >= 16  && defined(BMC_RELAY_NL_MERGE_8_RELAY) && defined(BMC_RELAY_NL_MERGE_8_RELAY2)
case 7:
if(type==0){
return BMC_RELAY_NL_MERGE_8_RELAY;
} else {
return BMC_RELAY_NL_MERGE_8_RELAY2;
}
#endif
}
#endif
return 255;
}
static uint8_t getButtonPixelMergeItem(uint8_t n, uint8_t type){
//type 0=pixel, 1=button
#if BMC_MAX_PIXELS > 0 && BMC_MAX_BUTTONS > 0
switch(n){
#if BMC_MAX_PIXELS > 0 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_PIXEL_MERGE_1_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_1_BTN)
case 0:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_1_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_1_BTN;
}
#endif
#if BMC_MAX_PIXELS > 1 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_PIXEL_MERGE_2_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_2_BTN)
case 1:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_2_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_2_BTN;
}
#endif
#if BMC_MAX_PIXELS > 2 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_PIXEL_MERGE_3_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_3_BTN)
case 2:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_3_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_3_BTN;
}
#endif
#if BMC_MAX_PIXELS > 3 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_PIXEL_MERGE_4_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_4_BTN)
case 3:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_4_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_4_BTN;
}
#endif
#if BMC_MAX_PIXELS > 4 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_PIXEL_MERGE_5_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_5_BTN)
case 4:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_5_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_5_BTN;
}
#endif
#if BMC_MAX_PIXELS > 5 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_PIXEL_MERGE_6_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_6_BTN)
case 5:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_6_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_6_BTN;
}
#endif
#if BMC_MAX_PIXELS > 6 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_PIXEL_MERGE_7_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_7_BTN)
case 6:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_7_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_7_BTN;
}
#endif
#if BMC_MAX_PIXELS > 7 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_PIXEL_MERGE_8_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_8_BTN)
case 7:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_8_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_8_BTN;
}
#endif
#if BMC_MAX_PIXELS > 8 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_PIXEL_MERGE_9_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_9_BTN)
case 8:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_9_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_9_BTN;
}
#endif
#if BMC_MAX_PIXELS > 9 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_PIXEL_MERGE_10_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_10_BTN)
case 9:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_10_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_10_BTN;
}
#endif
#if BMC_MAX_PIXELS > 10 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_PIXEL_MERGE_11_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_11_BTN)
case 10:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_11_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_11_BTN;
}
#endif
#if BMC_MAX_PIXELS > 11 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_PIXEL_MERGE_12_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_12_BTN)
case 11:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_12_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_12_BTN;
}
#endif
#if BMC_MAX_PIXELS > 12 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_PIXEL_MERGE_13_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_13_BTN)
case 12:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_13_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_13_BTN;
}
#endif
#if BMC_MAX_PIXELS > 13 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_PIXEL_MERGE_14_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_14_BTN)
case 13:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_14_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_14_BTN;
}
#endif
#if BMC_MAX_PIXELS > 14 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_PIXEL_MERGE_15_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_15_BTN)
case 14:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_15_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_15_BTN;
}
#endif
#if BMC_MAX_PIXELS > 15 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_PIXEL_MERGE_16_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_16_BTN)
case 15:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_16_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_16_BTN;
}
#endif
#if BMC_MAX_PIXELS > 16 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_PIXEL_MERGE_17_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_17_BTN)
case 16:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_17_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_17_BTN;
}
#endif
#if BMC_MAX_PIXELS > 17 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_PIXEL_MERGE_18_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_18_BTN)
case 17:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_18_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_18_BTN;
}
#endif
#if BMC_MAX_PIXELS > 18 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_PIXEL_MERGE_19_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_19_BTN)
case 18:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_19_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_19_BTN;
}
#endif
#if BMC_MAX_PIXELS > 19 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_PIXEL_MERGE_20_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_20_BTN)
case 19:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_20_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_20_BTN;
}
#endif
#if BMC_MAX_PIXELS > 20 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_PIXEL_MERGE_21_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_21_BTN)
case 20:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_21_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_21_BTN;
}
#endif
#if BMC_MAX_PIXELS > 21 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_PIXEL_MERGE_22_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_22_BTN)
case 21:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_22_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_22_BTN;
}
#endif
#if BMC_MAX_PIXELS > 22 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_PIXEL_MERGE_23_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_23_BTN)
case 22:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_23_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_23_BTN;
}
#endif
#if BMC_MAX_PIXELS > 23 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_PIXEL_MERGE_24_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_24_BTN)
case 23:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_24_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_24_BTN;
}
#endif
#if BMC_MAX_PIXELS > 24 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_PIXEL_MERGE_25_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_25_BTN)
case 24:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_25_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_25_BTN;
}
#endif
#if BMC_MAX_PIXELS > 25 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_PIXEL_MERGE_26_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_26_BTN)
case 25:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_26_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_26_BTN;
}
#endif
#if BMC_MAX_PIXELS > 26 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_PIXEL_MERGE_27_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_27_BTN)
case 26:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_27_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_27_BTN;
}
#endif
#if BMC_MAX_PIXELS > 27 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_PIXEL_MERGE_28_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_28_BTN)
case 27:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_28_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_28_BTN;
}
#endif
#if BMC_MAX_PIXELS > 28 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_PIXEL_MERGE_29_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_29_BTN)
case 28:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_29_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_29_BTN;
}
#endif
#if BMC_MAX_PIXELS > 29 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_PIXEL_MERGE_30_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_30_BTN)
case 29:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_30_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_30_BTN;
}
#endif
#if BMC_MAX_PIXELS > 30 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_PIXEL_MERGE_31_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_31_BTN)
case 30:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_31_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_31_BTN;
}
#endif
#if BMC_MAX_PIXELS > 31 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_PIXEL_MERGE_32_PIXEL) && defined(BMC_BUTTON_PIXEL_MERGE_32_BTN)
case 31:
if(type==0){
return BMC_BUTTON_PIXEL_MERGE_32_PIXEL;
} else {
return BMC_BUTTON_PIXEL_MERGE_32_BTN;
}
#endif
}
#endif
return 0;
}
static uint8_t getButtonRgbPixelMergeItem(uint8_t n, uint8_t type){
//type 0=pixel, 1=button
#if BMC_MAX_RGB_PIXELS > 0 && BMC_MAX_BUTTONS > 0
switch(n){
#if BMC_MAX_RGB_PIXELS > 0 && BMC_MAX_BUTTONS > 0 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_1_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_1_BTN)
case 0:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_1_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_1_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 1 && BMC_MAX_BUTTONS > 1 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_2_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_2_BTN)
case 1:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_2_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_2_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 2 && BMC_MAX_BUTTONS > 2 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_3_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_3_BTN)
case 2:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_3_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_3_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 3 && BMC_MAX_BUTTONS > 3 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_4_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_4_BTN)
case 3:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_4_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_4_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 4 && BMC_MAX_BUTTONS > 4 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_5_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_5_BTN)
case 4:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_5_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_5_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 5 && BMC_MAX_BUTTONS > 5 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_6_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_6_BTN)
case 5:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_6_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_6_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 6 && BMC_MAX_BUTTONS > 6 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_7_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_7_BTN)
case 6:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_7_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_7_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 7 && BMC_MAX_BUTTONS > 7 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_8_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_8_BTN)
case 7:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_8_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_8_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 8 && BMC_MAX_BUTTONS > 8 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_9_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_9_BTN)
case 8:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_9_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_9_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 9 && BMC_MAX_BUTTONS > 9 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_10_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_10_BTN)
case 9:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_10_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_10_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 10 && BMC_MAX_BUTTONS > 10 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_11_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_11_BTN)
case 10:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_11_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_11_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 11 && BMC_MAX_BUTTONS > 11 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_12_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_12_BTN)
case 11:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_12_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_12_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 12 && BMC_MAX_BUTTONS > 12 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_13_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_13_BTN)
case 12:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_13_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_13_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 13 && BMC_MAX_BUTTONS > 13 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_14_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_14_BTN)
case 13:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_14_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_14_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 14 && BMC_MAX_BUTTONS > 14 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_15_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_15_BTN)
case 14:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_15_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_15_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 15 && BMC_MAX_BUTTONS > 15 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_16_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_16_BTN)
case 15:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_16_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_16_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 16 && BMC_MAX_BUTTONS > 16 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_17_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_17_BTN)
case 16:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_17_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_17_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 17 && BMC_MAX_BUTTONS > 17 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_18_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_18_BTN)
case 17:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_18_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_18_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 18 && BMC_MAX_BUTTONS > 18 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_19_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_19_BTN)
case 18:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_19_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_19_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 19 && BMC_MAX_BUTTONS > 19 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_20_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_20_BTN)
case 19:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_20_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_20_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 20 && BMC_MAX_BUTTONS > 20 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_21_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_21_BTN)
case 20:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_21_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_21_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 21 && BMC_MAX_BUTTONS > 21 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_22_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_22_BTN)
case 21:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_22_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_22_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 22 && BMC_MAX_BUTTONS > 22 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_23_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_23_BTN)
case 22:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_23_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_23_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 23 && BMC_MAX_BUTTONS > 23 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_24_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_24_BTN)
case 23:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_24_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_24_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 24 && BMC_MAX_BUTTONS > 24 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_25_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_25_BTN)
case 24:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_25_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_25_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 25 && BMC_MAX_BUTTONS > 25 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_26_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_26_BTN)
case 25:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_26_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_26_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 26 && BMC_MAX_BUTTONS > 26 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_27_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_27_BTN)
case 26:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_27_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_27_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 27 && BMC_MAX_BUTTONS > 27 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_28_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_28_BTN)
case 27:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_28_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_28_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 28 && BMC_MAX_BUTTONS > 28 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_29_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_29_BTN)
case 28:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_29_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_29_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 29 && BMC_MAX_BUTTONS > 29 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_30_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_30_BTN)
case 29:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_30_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_30_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 30 && BMC_MAX_BUTTONS > 30 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_31_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_31_BTN)
case 30:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_31_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_31_BTN;
}
#endif
#if BMC_MAX_RGB_PIXELS > 31 && BMC_MAX_BUTTONS > 31 && defined(BMC_BUTTON_RGB_PIXEL_MERGE_32_PIXEL) && defined(BMC_BUTTON_RGB_PIXEL_MERGE_32_BTN)
case 31:
if(type==0){
return BMC_BUTTON_RGB_PIXEL_MERGE_32_PIXEL;
} else {
return BMC_BUTTON_RGB_PIXEL_MERGE_32_BTN;
}
#endif
}
#endif
return 0;
}
static BMCSketchByteData getSketchByteData(uint8_t index){
  char defaultName[BMC_NAME_LEN_SKETCH_BYTES] = "";
  if(index>9){
    sprintf(defaultName,"Byte %02u",(uint8_t)index);
  } else {
    sprintf(defaultName,"Byte %01u",(uint8_t)index);
  }
  BMCSketchByteData buffer;
  strcpy(buffer.name,defaultName);
  buffer.initialValue = 0;
  buffer.min = 0;
  buffer.max = 255;
  buffer.step = 1;
  buffer.formatType = BMC_NONE;
  buffer.formatValue = BMC_NONE;
  buffer.formatAppend = BMC_NONE;
  #if BMC_MAX_SKETCH_BYTES > 0
  switch(index){
  #if defined(BMC_SKETCH_BYTE_0_DATA)
    case 0: buffer = BMC_SKETCH_BYTE_0_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_1_DATA)
    case 1: buffer = BMC_SKETCH_BYTE_1_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_2_DATA)
    case 2: buffer = BMC_SKETCH_BYTE_2_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_3_DATA)
    case 3: buffer = BMC_SKETCH_BYTE_3_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_4_DATA)
    case 4: buffer = BMC_SKETCH_BYTE_4_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_5_DATA)
    case 5: buffer = BMC_SKETCH_BYTE_5_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_6_DATA)
    case 6: buffer = BMC_SKETCH_BYTE_6_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_7_DATA)
    case 7: buffer = BMC_SKETCH_BYTE_7_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_8_DATA)
    case 8: buffer = BMC_SKETCH_BYTE_8_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_9_DATA)
    case 9: buffer = BMC_SKETCH_BYTE_9_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_10_DATA)
    case 10: buffer = BMC_SKETCH_BYTE_10_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_11_DATA)
    case 11: buffer = BMC_SKETCH_BYTE_11_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_12_DATA)
    case 12: buffer = BMC_SKETCH_BYTE_12_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_13_DATA)
    case 13: buffer = BMC_SKETCH_BYTE_13_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_14_DATA)
    case 14: buffer = BMC_SKETCH_BYTE_14_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_15_DATA)
    case 15: buffer = BMC_SKETCH_BYTE_15_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_16_DATA)
    case 16: buffer = BMC_SKETCH_BYTE_16_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_17_DATA)
    case 17: buffer = BMC_SKETCH_BYTE_17_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_18_DATA)
    case 18: buffer = BMC_SKETCH_BYTE_18_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_19_DATA)
    case 19: buffer = BMC_SKETCH_BYTE_19_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_20_DATA)
    case 20: buffer = BMC_SKETCH_BYTE_20_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_21_DATA)
    case 21: buffer = BMC_SKETCH_BYTE_21_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_22_DATA)
    case 22: buffer = BMC_SKETCH_BYTE_22_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_23_DATA)
    case 23: buffer = BMC_SKETCH_BYTE_23_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_24_DATA)
    case 24: buffer = BMC_SKETCH_BYTE_24_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_25_DATA)
    case 25: buffer = BMC_SKETCH_BYTE_25_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_26_DATA)
    case 26: buffer = BMC_SKETCH_BYTE_26_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_27_DATA)
    case 27: buffer = BMC_SKETCH_BYTE_27_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_28_DATA)
    case 28: buffer = BMC_SKETCH_BYTE_28_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_29_DATA)
    case 29: buffer = BMC_SKETCH_BYTE_29_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_30_DATA)
    case 30: buffer = BMC_SKETCH_BYTE_30_DATA; break;
  #endif
  #if defined(BMC_SKETCH_BYTE_31_DATA)
    case 31: buffer = BMC_SKETCH_BYTE_31_DATA; break;
  #endif

}
#endif
return buffer;
}

static bool isDigitalPin(uint8_t index){
#if BMC_TEENSY_MODEL == 32
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 28:
case 29:
case 30:
case 31:
case 32:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 35
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 28:
case 29:
case 30:
case 31:
case 32:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
case 40:
case 41:
case 42:
case 43:
case 44:
case 45:
case 46:
case 47:
case 48:
case 49:
case 50:
case 51:
case 52:
case 53:
case 54:
case 55:
case 56:
case 57:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 36
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 28:
case 29:
case 30:
case 31:
case 32:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
case 40:
case 41:
case 42:
case 43:
case 44:
case 45:
case 46:
case 47:
case 48:
case 49:
case 50:
case 51:
case 52:
case 53:
case 54:
case 55:
case 56:
case 57:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 40
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 28:
case 29:
case 30:
case 31:
case 32:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 41
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 28:
case 29:
case 30:
case 31:
case 32:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
case 40:
case 41:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 42
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 28:
case 29:
case 30:
case 31:
case 32:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
case 40:
case 41:
case 42:
case 43:
case 44:
case 45:
return true;
}
#endif
return false;
}
static bool isAnalogPin(uint8_t index){
#if BMC_TEENSY_MODEL == 32
switch(index){
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 26:
case 27:
case 28:
case 29:
case 30:
case 31:
case 33:
case 34:
case 35:
case 36:
case 37:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 35
switch(index){
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 31:
case 32:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
case 49:
case 50:
case 64:
case 65:
case 66:
case 67:
case 68:
case 69:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 36
switch(index){
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 31:
case 32:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
case 49:
case 50:
case 64:
case 65:
case 66:
case 67:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 40
switch(index){
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 41
switch(index){
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 38:
case 39:
case 40:
case 41:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 42
switch(index){
case 14:
case 15:
case 16:
case 17:
case 18:
case 19:
case 20:
case 21:
case 22:
case 23:
case 24:
case 25:
case 26:
case 27:
case 40:
case 41:
return true;
}
#endif
return false;
}
static bool isPwmPin(uint8_t index){
#if BMC_TEENSY_MODEL == 32
switch(index){
case 3:
case 4:
case 5:
case 6:
case 9:
case 10:
case 20:
case 21:
case 22:
case 23:
case 25:
case 32:
case 37:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 35
switch(index){
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 14:
case 20:
case 21:
case 22:
case 23:
case 29:
case 30:
case 35:
case 36:
case 37:
case 38:
case 66:
case 67:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 36
switch(index){
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 14:
case 16:
case 17:
case 20:
case 21:
case 22:
case 23:
case 29:
case 30:
case 35:
case 36:
case 37:
case 38:
case 66:
case 67:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 40
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 18:
case 19:
case 22:
case 23:
case 24:
case 25:
case 28:
case 29:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 41
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 18:
case 19:
case 22:
case 23:
case 24:
case 25:
case 28:
case 29:
case 33:
case 36:
case 37:
return true;
}
#endif
#if BMC_TEENSY_MODEL == 42
switch(index){
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10:
case 11:
case 12:
case 13:
case 14:
case 15:
case 18:
case 19:
case 22:
case 23:
case 24:
case 25:
case 28:
case 29:
case 33:
case 34:
case 35:
case 36:
case 37:
case 38:
case 39:
return true;
}
#endif
return false;
}


    // MUX GPIO
static bool isMuxGpioPin(uint8_t n){
#if BMC_MAX_MUX_GPIO > 0
  return (n >= 64 && n < (64+BMC_MAX_MUX_GPIO));
#else
  return false;
#endif
}

// MUX IN
static bool isMuxInPin(uint8_t n){
#if BMC_MAX_MUX_GPIO > 0
  if(isMuxGpioPin(n)){
    return true;
  }
#endif
#if BMC_MAX_MUX_IN > 0
  return (n>=64+BMC_MAX_MUX_GPIO && n<(64+BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN));
#endif
  return false;
}

// MUX OUT
static bool isMuxOutPin(uint8_t n){
#if BMC_MAX_MUX_GPIO > 0
  if(isMuxGpioPin(n)){
    return true;
  }
#endif
#if BMC_MAX_MUX_OUT > 0
  return (n>=(64+BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN) && n<(64+BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT));
#endif
  return false;
}

// MUX IN ANALOG
static bool isMuxInAnalogPin(uint8_t n){
#if BMC_MAX_MUX_IN_ANALOG > 0
  return (n>=(64+BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT) && n<(64+BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG));
#endif
  return false;
}
// MUX IN ANALOG
static bool isMuxInAnalogPinIndex(uint8_t n){
#if BMC_MAX_MUX_IN_ANALOG > 0
  return (n>=(BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT) && n<(BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG));
#endif
  return false;
}
};
#endif
