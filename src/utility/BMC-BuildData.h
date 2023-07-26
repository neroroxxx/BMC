/*
See https://www.RoxXxtar.com/bmc for more details
Copyright (c) 2023 RoxXxtar.com
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
        case BMC_DEVICE_ID_SHORTCUTS:
          #if defined(BMC_DEVICE_UI_SHORTCUTS_1)
            return BMC_DEVICE_UI_SHORTCUTS_1;
          #endif
          break;
        case BMC_DEVICE_ID_PIXEL_STRIP:
          #if defined(BMC_DEVICE_UI_PIXEL_STRIP_1) && BMC_MAX_PIXEL_STRIP > 0
            return BMC_DEVICE_UI_PIXEL_STRIP_1;
          #endif
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
      case BMC_DEVICE_ID_BI_LED:
          #if BMC_MAX_BI_LEDS > 0 
            switch(n){
              #if BMC_MAX_BI_LEDS > 0 && defined(BMC_DEVICE_UI_BI_LED_1)
              case 0: return BMC_DEVICE_UI_BI_LED_1;
            #endif
            #if BMC_MAX_BI_LEDS > 1 && defined(BMC_DEVICE_UI_BI_LED_2)
              case 1: return BMC_DEVICE_UI_BI_LED_2;
            #endif
            #if BMC_MAX_BI_LEDS > 2 && defined(BMC_DEVICE_UI_BI_LED_3)
              case 2: return BMC_DEVICE_UI_BI_LED_3;
            #endif
            #if BMC_MAX_BI_LEDS > 3 && defined(BMC_DEVICE_UI_BI_LED_4)
              case 3: return BMC_DEVICE_UI_BI_LED_4;
            #endif
            #if BMC_MAX_BI_LEDS > 4 && defined(BMC_DEVICE_UI_BI_LED_5)
              case 4: return BMC_DEVICE_UI_BI_LED_5;
            #endif
            #if BMC_MAX_BI_LEDS > 5 && defined(BMC_DEVICE_UI_BI_LED_6)
              case 5: return BMC_DEVICE_UI_BI_LED_6;
            #endif
            #if BMC_MAX_BI_LEDS > 6 && defined(BMC_DEVICE_UI_BI_LED_7)
              case 6: return BMC_DEVICE_UI_BI_LED_7;
            #endif
            #if BMC_MAX_BI_LEDS > 7 && defined(BMC_DEVICE_UI_BI_LED_8)
              case 7: return BMC_DEVICE_UI_BI_LED_8;
            #endif
            #if BMC_MAX_BI_LEDS > 8 && defined(BMC_DEVICE_UI_BI_LED_9)
              case 8: return BMC_DEVICE_UI_BI_LED_9;
            #endif
            #if BMC_MAX_BI_LEDS > 9 && defined(BMC_DEVICE_UI_BI_LED_10)
              case 9: return BMC_DEVICE_UI_BI_LED_10;
            #endif
            #if BMC_MAX_BI_LEDS > 10 && defined(BMC_DEVICE_UI_BI_LED_11)
              case 10: return BMC_DEVICE_UI_BI_LED_11;
            #endif
            #if BMC_MAX_BI_LEDS > 11 && defined(BMC_DEVICE_UI_BI_LED_12)
              case 11: return BMC_DEVICE_UI_BI_LED_12;
            #endif
            #if BMC_MAX_BI_LEDS > 12 && defined(BMC_DEVICE_UI_BI_LED_13)
              case 12: return BMC_DEVICE_UI_BI_LED_13;
            #endif
            #if BMC_MAX_BI_LEDS > 13 && defined(BMC_DEVICE_UI_BI_LED_14)
              case 13: return BMC_DEVICE_UI_BI_LED_14;
            #endif
            #if BMC_MAX_BI_LEDS > 14 && defined(BMC_DEVICE_UI_BI_LED_15)
              case 14: return BMC_DEVICE_UI_BI_LED_15;
            #endif
            #if BMC_MAX_BI_LEDS > 15 && defined(BMC_DEVICE_UI_BI_LED_16)
              case 15: return BMC_DEVICE_UI_BI_LED_16;
            #endif
            #if BMC_MAX_BI_LEDS > 16 && defined(BMC_DEVICE_UI_BI_LED_17)
              case 16: return BMC_DEVICE_UI_BI_LED_17;
            #endif
            #if BMC_MAX_BI_LEDS > 17 && defined(BMC_DEVICE_UI_BI_LED_18)
              case 17: return BMC_DEVICE_UI_BI_LED_18;
            #endif
            #if BMC_MAX_BI_LEDS > 18 && defined(BMC_DEVICE_UI_BI_LED_19)
              case 18: return BMC_DEVICE_UI_BI_LED_19;
            #endif
            #if BMC_MAX_BI_LEDS > 19 && defined(BMC_DEVICE_UI_BI_LED_20)
              case 19: return BMC_DEVICE_UI_BI_LED_20;
            #endif
            #if BMC_MAX_BI_LEDS > 20 && defined(BMC_DEVICE_UI_BI_LED_21)
              case 20: return BMC_DEVICE_UI_BI_LED_21;
            #endif
            #if BMC_MAX_BI_LEDS > 21 && defined(BMC_DEVICE_UI_BI_LED_22)
              case 21: return BMC_DEVICE_UI_BI_LED_22;
            #endif
            #if BMC_MAX_BI_LEDS > 22 && defined(BMC_DEVICE_UI_BI_LED_23)
              case 22: return BMC_DEVICE_UI_BI_LED_23;
            #endif
            #if BMC_MAX_BI_LEDS > 23 && defined(BMC_DEVICE_UI_BI_LED_24)
              case 23: return BMC_DEVICE_UI_BI_LED_24;
            #endif
            #if BMC_MAX_BI_LEDS > 24 && defined(BMC_DEVICE_UI_BI_LED_25)
              case 24: return BMC_DEVICE_UI_BI_LED_25;
            #endif
            #if BMC_MAX_BI_LEDS > 25 && defined(BMC_DEVICE_UI_BI_LED_26)
              case 25: return BMC_DEVICE_UI_BI_LED_26;
            #endif
            #if BMC_MAX_BI_LEDS > 26 && defined(BMC_DEVICE_UI_BI_LED_27)
              case 26: return BMC_DEVICE_UI_BI_LED_27;
            #endif
            #if BMC_MAX_BI_LEDS > 27 && defined(BMC_DEVICE_UI_BI_LED_28)
              case 27: return BMC_DEVICE_UI_BI_LED_28;
            #endif
            #if BMC_MAX_BI_LEDS > 28 && defined(BMC_DEVICE_UI_BI_LED_29)
              case 28: return BMC_DEVICE_UI_BI_LED_29;
            #endif
            #if BMC_MAX_BI_LEDS > 29 && defined(BMC_DEVICE_UI_BI_LED_30)
              case 29: return BMC_DEVICE_UI_BI_LED_30;
            #endif
            #if BMC_MAX_BI_LEDS > 30 && defined(BMC_DEVICE_UI_BI_LED_31)
              case 30: return BMC_DEVICE_UI_BI_LED_31;
            #endif
            #if BMC_MAX_BI_LEDS > 31 && defined(BMC_DEVICE_UI_BI_LED_32)
              case 31: return BMC_DEVICE_UI_BI_LED_32;
            #endif
            #if BMC_MAX_BI_LEDS > 32 && defined(BMC_DEVICE_UI_BI_LED_33)
              case 32: return BMC_DEVICE_UI_BI_LED_33;
            #endif
            #if BMC_MAX_BI_LEDS > 33 && defined(BMC_DEVICE_UI_BI_LED_34)
              case 33: return BMC_DEVICE_UI_BI_LED_34;
            #endif
            #if BMC_MAX_BI_LEDS > 34 && defined(BMC_DEVICE_UI_BI_LED_35)
              case 34: return BMC_DEVICE_UI_BI_LED_35;
            #endif
            #if BMC_MAX_BI_LEDS > 35 && defined(BMC_DEVICE_UI_BI_LED_36)
              case 35: return BMC_DEVICE_UI_BI_LED_36;
            #endif
            #if BMC_MAX_BI_LEDS > 36 && defined(BMC_DEVICE_UI_BI_LED_37)
              case 36: return BMC_DEVICE_UI_BI_LED_37;
            #endif
            #if BMC_MAX_BI_LEDS > 37 && defined(BMC_DEVICE_UI_BI_LED_38)
              case 37: return BMC_DEVICE_UI_BI_LED_38;
            #endif
            #if BMC_MAX_BI_LEDS > 38 && defined(BMC_DEVICE_UI_BI_LED_39)
              case 38: return BMC_DEVICE_UI_BI_LED_39;
            #endif
            #if BMC_MAX_BI_LEDS > 39 && defined(BMC_DEVICE_UI_BI_LED_40)
              case 39: return BMC_DEVICE_UI_BI_LED_40;
            #endif
            #if BMC_MAX_BI_LEDS > 40 && defined(BMC_DEVICE_UI_BI_LED_41)
              case 40: return BMC_DEVICE_UI_BI_LED_41;
            #endif
            #if BMC_MAX_BI_LEDS > 41 && defined(BMC_DEVICE_UI_BI_LED_42)
              case 41: return BMC_DEVICE_UI_BI_LED_42;
            #endif
            #if BMC_MAX_BI_LEDS > 42 && defined(BMC_DEVICE_UI_BI_LED_43)
              case 42: return BMC_DEVICE_UI_BI_LED_43;
            #endif
            #if BMC_MAX_BI_LEDS > 43 && defined(BMC_DEVICE_UI_BI_LED_44)
              case 43: return BMC_DEVICE_UI_BI_LED_44;
            #endif
            #if BMC_MAX_BI_LEDS > 44 && defined(BMC_DEVICE_UI_BI_LED_45)
              case 44: return BMC_DEVICE_UI_BI_LED_45;
            #endif
            #if BMC_MAX_BI_LEDS > 45 && defined(BMC_DEVICE_UI_BI_LED_46)
              case 45: return BMC_DEVICE_UI_BI_LED_46;
            #endif
            #if BMC_MAX_BI_LEDS > 46 && defined(BMC_DEVICE_UI_BI_LED_47)
              case 46: return BMC_DEVICE_UI_BI_LED_47;
            #endif
            #if BMC_MAX_BI_LEDS > 47 && defined(BMC_DEVICE_UI_BI_LED_48)
              case 47: return BMC_DEVICE_UI_BI_LED_48;
            #endif
            #if BMC_MAX_BI_LEDS > 48 && defined(BMC_DEVICE_UI_BI_LED_49)
              case 48: return BMC_DEVICE_UI_BI_LED_49;
            #endif
            #if BMC_MAX_BI_LEDS > 49 && defined(BMC_DEVICE_UI_BI_LED_50)
              case 49: return BMC_DEVICE_UI_BI_LED_50;
            #endif
            #if BMC_MAX_BI_LEDS > 50 && defined(BMC_DEVICE_UI_BI_LED_51)
              case 50: return BMC_DEVICE_UI_BI_LED_51;
            #endif
            #if BMC_MAX_BI_LEDS > 51 && defined(BMC_DEVICE_UI_BI_LED_52)
              case 51: return BMC_DEVICE_UI_BI_LED_52;
            #endif
            #if BMC_MAX_BI_LEDS > 52 && defined(BMC_DEVICE_UI_BI_LED_53)
              case 52: return BMC_DEVICE_UI_BI_LED_53;
            #endif
            #if BMC_MAX_BI_LEDS > 53 && defined(BMC_DEVICE_UI_BI_LED_54)
              case 53: return BMC_DEVICE_UI_BI_LED_54;
            #endif
            #if BMC_MAX_BI_LEDS > 54 && defined(BMC_DEVICE_UI_BI_LED_55)
              case 54: return BMC_DEVICE_UI_BI_LED_55;
            #endif
            #if BMC_MAX_BI_LEDS > 55 && defined(BMC_DEVICE_UI_BI_LED_56)
              case 55: return BMC_DEVICE_UI_BI_LED_56;
            #endif
            #if BMC_MAX_BI_LEDS > 56 && defined(BMC_DEVICE_UI_BI_LED_57)
              case 56: return BMC_DEVICE_UI_BI_LED_57;
            #endif
            #if BMC_MAX_BI_LEDS > 57 && defined(BMC_DEVICE_UI_BI_LED_58)
              case 57: return BMC_DEVICE_UI_BI_LED_58;
            #endif
            #if BMC_MAX_BI_LEDS > 58 && defined(BMC_DEVICE_UI_BI_LED_59)
              case 58: return BMC_DEVICE_UI_BI_LED_59;
            #endif
            #if BMC_MAX_BI_LEDS > 59 && defined(BMC_DEVICE_UI_BI_LED_60)
              case 59: return BMC_DEVICE_UI_BI_LED_60;
            #endif
            #if BMC_MAX_BI_LEDS > 60 && defined(BMC_DEVICE_UI_BI_LED_61)
              case 60: return BMC_DEVICE_UI_BI_LED_61;
            #endif
            #if BMC_MAX_BI_LEDS > 61 && defined(BMC_DEVICE_UI_BI_LED_62)
              case 61: return BMC_DEVICE_UI_BI_LED_62;
            #endif
            #if BMC_MAX_BI_LEDS > 62 && defined(BMC_DEVICE_UI_BI_LED_63)
              case 62: return BMC_DEVICE_UI_BI_LED_63;
            #endif
            #if BMC_MAX_BI_LEDS > 63 && defined(BMC_DEVICE_UI_BI_LED_64)
              case 63: return BMC_DEVICE_UI_BI_LED_64;
            #endif
    
            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_BI_LED:
          #if BMC_MAX_GLOBAL_BI_LEDS > 0 
            switch(n){
              #if BMC_MAX_GLOBAL_BI_LEDS > 0 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_BI_LED_1;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 1 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_BI_LED_2;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 2 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_BI_LED_3;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 3 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_BI_LED_4;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 4 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_BI_LED_5;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 5 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_BI_LED_6;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 6 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_BI_LED_7;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 7 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_BI_LED_8;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 8 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_BI_LED_9;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 9 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_BI_LED_10;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 10 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_BI_LED_11;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 11 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_BI_LED_12;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 12 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_BI_LED_13;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 13 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_BI_LED_14;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 14 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_BI_LED_15;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 15 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_BI_LED_16;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 16 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_BI_LED_17;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 17 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_BI_LED_18;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 18 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_BI_LED_19;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 19 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_BI_LED_20;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 20 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_BI_LED_21;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 21 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_BI_LED_22;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 22 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_BI_LED_23;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 23 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_BI_LED_24;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 24 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_BI_LED_25;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 25 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_BI_LED_26;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 26 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_BI_LED_27;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 27 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_BI_LED_28;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 28 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_BI_LED_29;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 29 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_BI_LED_30;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 30 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_BI_LED_31;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 31 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_BI_LED_32;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 32 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_BI_LED_33;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 33 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_BI_LED_34;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 34 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_BI_LED_35;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 35 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_BI_LED_36;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 36 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_BI_LED_37;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 37 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_BI_LED_38;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 38 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_BI_LED_39;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 39 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_BI_LED_40;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 40 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_BI_LED_41;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 41 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_BI_LED_42;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 42 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_BI_LED_43;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 43 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_BI_LED_44;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 44 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_BI_LED_45;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 45 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_BI_LED_46;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 46 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_BI_LED_47;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 47 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_BI_LED_48;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 48 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_BI_LED_49;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 49 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_BI_LED_50;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 50 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_BI_LED_51;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 51 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_BI_LED_52;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 52 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_BI_LED_53;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 53 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_BI_LED_54;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 54 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_BI_LED_55;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 55 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_BI_LED_56;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 56 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_BI_LED_57;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 57 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_BI_LED_58;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 58 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_BI_LED_59;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 59 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_BI_LED_60;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 60 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_BI_LED_61;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 61 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_BI_LED_62;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 62 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_BI_LED_63;
            #endif
            #if BMC_MAX_GLOBAL_BI_LEDS > 63 && defined(BMC_DEVICE_UI_GLOBAL_BI_LED_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_BI_LED_64;
            #endif
    
            }
          #endif
          break;
      case BMC_DEVICE_ID_TRI_LED:
          #if BMC_MAX_TRI_LEDS > 0 
            switch(n){
              #if BMC_MAX_TRI_LEDS > 0 && defined(BMC_DEVICE_UI_TRI_LED_1)
              case 0: return BMC_DEVICE_UI_TRI_LED_1;
            #endif
            #if BMC_MAX_TRI_LEDS > 1 && defined(BMC_DEVICE_UI_TRI_LED_2)
              case 1: return BMC_DEVICE_UI_TRI_LED_2;
            #endif
            #if BMC_MAX_TRI_LEDS > 2 && defined(BMC_DEVICE_UI_TRI_LED_3)
              case 2: return BMC_DEVICE_UI_TRI_LED_3;
            #endif
            #if BMC_MAX_TRI_LEDS > 3 && defined(BMC_DEVICE_UI_TRI_LED_4)
              case 3: return BMC_DEVICE_UI_TRI_LED_4;
            #endif
            #if BMC_MAX_TRI_LEDS > 4 && defined(BMC_DEVICE_UI_TRI_LED_5)
              case 4: return BMC_DEVICE_UI_TRI_LED_5;
            #endif
            #if BMC_MAX_TRI_LEDS > 5 && defined(BMC_DEVICE_UI_TRI_LED_6)
              case 5: return BMC_DEVICE_UI_TRI_LED_6;
            #endif
            #if BMC_MAX_TRI_LEDS > 6 && defined(BMC_DEVICE_UI_TRI_LED_7)
              case 6: return BMC_DEVICE_UI_TRI_LED_7;
            #endif
            #if BMC_MAX_TRI_LEDS > 7 && defined(BMC_DEVICE_UI_TRI_LED_8)
              case 7: return BMC_DEVICE_UI_TRI_LED_8;
            #endif
            #if BMC_MAX_TRI_LEDS > 8 && defined(BMC_DEVICE_UI_TRI_LED_9)
              case 8: return BMC_DEVICE_UI_TRI_LED_9;
            #endif
            #if BMC_MAX_TRI_LEDS > 9 && defined(BMC_DEVICE_UI_TRI_LED_10)
              case 9: return BMC_DEVICE_UI_TRI_LED_10;
            #endif
            #if BMC_MAX_TRI_LEDS > 10 && defined(BMC_DEVICE_UI_TRI_LED_11)
              case 10: return BMC_DEVICE_UI_TRI_LED_11;
            #endif
            #if BMC_MAX_TRI_LEDS > 11 && defined(BMC_DEVICE_UI_TRI_LED_12)
              case 11: return BMC_DEVICE_UI_TRI_LED_12;
            #endif
            #if BMC_MAX_TRI_LEDS > 12 && defined(BMC_DEVICE_UI_TRI_LED_13)
              case 12: return BMC_DEVICE_UI_TRI_LED_13;
            #endif
            #if BMC_MAX_TRI_LEDS > 13 && defined(BMC_DEVICE_UI_TRI_LED_14)
              case 13: return BMC_DEVICE_UI_TRI_LED_14;
            #endif
            #if BMC_MAX_TRI_LEDS > 14 && defined(BMC_DEVICE_UI_TRI_LED_15)
              case 14: return BMC_DEVICE_UI_TRI_LED_15;
            #endif
            #if BMC_MAX_TRI_LEDS > 15 && defined(BMC_DEVICE_UI_TRI_LED_16)
              case 15: return BMC_DEVICE_UI_TRI_LED_16;
            #endif
            #if BMC_MAX_TRI_LEDS > 16 && defined(BMC_DEVICE_UI_TRI_LED_17)
              case 16: return BMC_DEVICE_UI_TRI_LED_17;
            #endif
            #if BMC_MAX_TRI_LEDS > 17 && defined(BMC_DEVICE_UI_TRI_LED_18)
              case 17: return BMC_DEVICE_UI_TRI_LED_18;
            #endif
            #if BMC_MAX_TRI_LEDS > 18 && defined(BMC_DEVICE_UI_TRI_LED_19)
              case 18: return BMC_DEVICE_UI_TRI_LED_19;
            #endif
            #if BMC_MAX_TRI_LEDS > 19 && defined(BMC_DEVICE_UI_TRI_LED_20)
              case 19: return BMC_DEVICE_UI_TRI_LED_20;
            #endif
            #if BMC_MAX_TRI_LEDS > 20 && defined(BMC_DEVICE_UI_TRI_LED_21)
              case 20: return BMC_DEVICE_UI_TRI_LED_21;
            #endif
            #if BMC_MAX_TRI_LEDS > 21 && defined(BMC_DEVICE_UI_TRI_LED_22)
              case 21: return BMC_DEVICE_UI_TRI_LED_22;
            #endif
            #if BMC_MAX_TRI_LEDS > 22 && defined(BMC_DEVICE_UI_TRI_LED_23)
              case 22: return BMC_DEVICE_UI_TRI_LED_23;
            #endif
            #if BMC_MAX_TRI_LEDS > 23 && defined(BMC_DEVICE_UI_TRI_LED_24)
              case 23: return BMC_DEVICE_UI_TRI_LED_24;
            #endif
            #if BMC_MAX_TRI_LEDS > 24 && defined(BMC_DEVICE_UI_TRI_LED_25)
              case 24: return BMC_DEVICE_UI_TRI_LED_25;
            #endif
            #if BMC_MAX_TRI_LEDS > 25 && defined(BMC_DEVICE_UI_TRI_LED_26)
              case 25: return BMC_DEVICE_UI_TRI_LED_26;
            #endif
            #if BMC_MAX_TRI_LEDS > 26 && defined(BMC_DEVICE_UI_TRI_LED_27)
              case 26: return BMC_DEVICE_UI_TRI_LED_27;
            #endif
            #if BMC_MAX_TRI_LEDS > 27 && defined(BMC_DEVICE_UI_TRI_LED_28)
              case 27: return BMC_DEVICE_UI_TRI_LED_28;
            #endif
            #if BMC_MAX_TRI_LEDS > 28 && defined(BMC_DEVICE_UI_TRI_LED_29)
              case 28: return BMC_DEVICE_UI_TRI_LED_29;
            #endif
            #if BMC_MAX_TRI_LEDS > 29 && defined(BMC_DEVICE_UI_TRI_LED_30)
              case 29: return BMC_DEVICE_UI_TRI_LED_30;
            #endif
            #if BMC_MAX_TRI_LEDS > 30 && defined(BMC_DEVICE_UI_TRI_LED_31)
              case 30: return BMC_DEVICE_UI_TRI_LED_31;
            #endif
            #if BMC_MAX_TRI_LEDS > 31 && defined(BMC_DEVICE_UI_TRI_LED_32)
              case 31: return BMC_DEVICE_UI_TRI_LED_32;
            #endif
            #if BMC_MAX_TRI_LEDS > 32 && defined(BMC_DEVICE_UI_TRI_LED_33)
              case 32: return BMC_DEVICE_UI_TRI_LED_33;
            #endif
            #if BMC_MAX_TRI_LEDS > 33 && defined(BMC_DEVICE_UI_TRI_LED_34)
              case 33: return BMC_DEVICE_UI_TRI_LED_34;
            #endif
            #if BMC_MAX_TRI_LEDS > 34 && defined(BMC_DEVICE_UI_TRI_LED_35)
              case 34: return BMC_DEVICE_UI_TRI_LED_35;
            #endif
            #if BMC_MAX_TRI_LEDS > 35 && defined(BMC_DEVICE_UI_TRI_LED_36)
              case 35: return BMC_DEVICE_UI_TRI_LED_36;
            #endif
            #if BMC_MAX_TRI_LEDS > 36 && defined(BMC_DEVICE_UI_TRI_LED_37)
              case 36: return BMC_DEVICE_UI_TRI_LED_37;
            #endif
            #if BMC_MAX_TRI_LEDS > 37 && defined(BMC_DEVICE_UI_TRI_LED_38)
              case 37: return BMC_DEVICE_UI_TRI_LED_38;
            #endif
            #if BMC_MAX_TRI_LEDS > 38 && defined(BMC_DEVICE_UI_TRI_LED_39)
              case 38: return BMC_DEVICE_UI_TRI_LED_39;
            #endif
            #if BMC_MAX_TRI_LEDS > 39 && defined(BMC_DEVICE_UI_TRI_LED_40)
              case 39: return BMC_DEVICE_UI_TRI_LED_40;
            #endif
            #if BMC_MAX_TRI_LEDS > 40 && defined(BMC_DEVICE_UI_TRI_LED_41)
              case 40: return BMC_DEVICE_UI_TRI_LED_41;
            #endif
            #if BMC_MAX_TRI_LEDS > 41 && defined(BMC_DEVICE_UI_TRI_LED_42)
              case 41: return BMC_DEVICE_UI_TRI_LED_42;
            #endif
            #if BMC_MAX_TRI_LEDS > 42 && defined(BMC_DEVICE_UI_TRI_LED_43)
              case 42: return BMC_DEVICE_UI_TRI_LED_43;
            #endif
            #if BMC_MAX_TRI_LEDS > 43 && defined(BMC_DEVICE_UI_TRI_LED_44)
              case 43: return BMC_DEVICE_UI_TRI_LED_44;
            #endif
            #if BMC_MAX_TRI_LEDS > 44 && defined(BMC_DEVICE_UI_TRI_LED_45)
              case 44: return BMC_DEVICE_UI_TRI_LED_45;
            #endif
            #if BMC_MAX_TRI_LEDS > 45 && defined(BMC_DEVICE_UI_TRI_LED_46)
              case 45: return BMC_DEVICE_UI_TRI_LED_46;
            #endif
            #if BMC_MAX_TRI_LEDS > 46 && defined(BMC_DEVICE_UI_TRI_LED_47)
              case 46: return BMC_DEVICE_UI_TRI_LED_47;
            #endif
            #if BMC_MAX_TRI_LEDS > 47 && defined(BMC_DEVICE_UI_TRI_LED_48)
              case 47: return BMC_DEVICE_UI_TRI_LED_48;
            #endif
            #if BMC_MAX_TRI_LEDS > 48 && defined(BMC_DEVICE_UI_TRI_LED_49)
              case 48: return BMC_DEVICE_UI_TRI_LED_49;
            #endif
            #if BMC_MAX_TRI_LEDS > 49 && defined(BMC_DEVICE_UI_TRI_LED_50)
              case 49: return BMC_DEVICE_UI_TRI_LED_50;
            #endif
            #if BMC_MAX_TRI_LEDS > 50 && defined(BMC_DEVICE_UI_TRI_LED_51)
              case 50: return BMC_DEVICE_UI_TRI_LED_51;
            #endif
            #if BMC_MAX_TRI_LEDS > 51 && defined(BMC_DEVICE_UI_TRI_LED_52)
              case 51: return BMC_DEVICE_UI_TRI_LED_52;
            #endif
            #if BMC_MAX_TRI_LEDS > 52 && defined(BMC_DEVICE_UI_TRI_LED_53)
              case 52: return BMC_DEVICE_UI_TRI_LED_53;
            #endif
            #if BMC_MAX_TRI_LEDS > 53 && defined(BMC_DEVICE_UI_TRI_LED_54)
              case 53: return BMC_DEVICE_UI_TRI_LED_54;
            #endif
            #if BMC_MAX_TRI_LEDS > 54 && defined(BMC_DEVICE_UI_TRI_LED_55)
              case 54: return BMC_DEVICE_UI_TRI_LED_55;
            #endif
            #if BMC_MAX_TRI_LEDS > 55 && defined(BMC_DEVICE_UI_TRI_LED_56)
              case 55: return BMC_DEVICE_UI_TRI_LED_56;
            #endif
            #if BMC_MAX_TRI_LEDS > 56 && defined(BMC_DEVICE_UI_TRI_LED_57)
              case 56: return BMC_DEVICE_UI_TRI_LED_57;
            #endif
            #if BMC_MAX_TRI_LEDS > 57 && defined(BMC_DEVICE_UI_TRI_LED_58)
              case 57: return BMC_DEVICE_UI_TRI_LED_58;
            #endif
            #if BMC_MAX_TRI_LEDS > 58 && defined(BMC_DEVICE_UI_TRI_LED_59)
              case 58: return BMC_DEVICE_UI_TRI_LED_59;
            #endif
            #if BMC_MAX_TRI_LEDS > 59 && defined(BMC_DEVICE_UI_TRI_LED_60)
              case 59: return BMC_DEVICE_UI_TRI_LED_60;
            #endif
            #if BMC_MAX_TRI_LEDS > 60 && defined(BMC_DEVICE_UI_TRI_LED_61)
              case 60: return BMC_DEVICE_UI_TRI_LED_61;
            #endif
            #if BMC_MAX_TRI_LEDS > 61 && defined(BMC_DEVICE_UI_TRI_LED_62)
              case 61: return BMC_DEVICE_UI_TRI_LED_62;
            #endif
            #if BMC_MAX_TRI_LEDS > 62 && defined(BMC_DEVICE_UI_TRI_LED_63)
              case 62: return BMC_DEVICE_UI_TRI_LED_63;
            #endif
            #if BMC_MAX_TRI_LEDS > 63 && defined(BMC_DEVICE_UI_TRI_LED_64)
              case 63: return BMC_DEVICE_UI_TRI_LED_64;
            #endif
    
            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_TRI_LED:
          #if BMC_MAX_GLOBAL_TRI_LEDS > 0 
            switch(n){
              #if BMC_MAX_GLOBAL_TRI_LEDS > 0 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_TRI_LED_1;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 1 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_TRI_LED_2;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 2 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_TRI_LED_3;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 3 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_TRI_LED_4;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 4 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_TRI_LED_5;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 5 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_TRI_LED_6;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 6 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_TRI_LED_7;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 7 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_TRI_LED_8;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 8 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_TRI_LED_9;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 9 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_TRI_LED_10;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 10 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_TRI_LED_11;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 11 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_TRI_LED_12;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 12 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_TRI_LED_13;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 13 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_TRI_LED_14;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 14 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_TRI_LED_15;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 15 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_TRI_LED_16;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 16 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_17)
              case 16: return BMC_DEVICE_UI_GLOBAL_TRI_LED_17;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 17 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_18)
              case 17: return BMC_DEVICE_UI_GLOBAL_TRI_LED_18;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 18 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_19)
              case 18: return BMC_DEVICE_UI_GLOBAL_TRI_LED_19;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 19 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_20)
              case 19: return BMC_DEVICE_UI_GLOBAL_TRI_LED_20;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 20 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_21)
              case 20: return BMC_DEVICE_UI_GLOBAL_TRI_LED_21;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 21 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_22)
              case 21: return BMC_DEVICE_UI_GLOBAL_TRI_LED_22;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 22 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_23)
              case 22: return BMC_DEVICE_UI_GLOBAL_TRI_LED_23;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 23 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_24)
              case 23: return BMC_DEVICE_UI_GLOBAL_TRI_LED_24;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 24 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_25)
              case 24: return BMC_DEVICE_UI_GLOBAL_TRI_LED_25;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 25 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_26)
              case 25: return BMC_DEVICE_UI_GLOBAL_TRI_LED_26;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 26 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_27)
              case 26: return BMC_DEVICE_UI_GLOBAL_TRI_LED_27;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 27 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_28)
              case 27: return BMC_DEVICE_UI_GLOBAL_TRI_LED_28;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 28 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_29)
              case 28: return BMC_DEVICE_UI_GLOBAL_TRI_LED_29;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 29 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_30)
              case 29: return BMC_DEVICE_UI_GLOBAL_TRI_LED_30;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 30 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_31)
              case 30: return BMC_DEVICE_UI_GLOBAL_TRI_LED_31;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 31 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_32)
              case 31: return BMC_DEVICE_UI_GLOBAL_TRI_LED_32;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 32 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_33)
              case 32: return BMC_DEVICE_UI_GLOBAL_TRI_LED_33;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 33 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_34)
              case 33: return BMC_DEVICE_UI_GLOBAL_TRI_LED_34;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 34 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_35)
              case 34: return BMC_DEVICE_UI_GLOBAL_TRI_LED_35;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 35 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_36)
              case 35: return BMC_DEVICE_UI_GLOBAL_TRI_LED_36;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 36 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_37)
              case 36: return BMC_DEVICE_UI_GLOBAL_TRI_LED_37;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 37 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_38)
              case 37: return BMC_DEVICE_UI_GLOBAL_TRI_LED_38;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 38 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_39)
              case 38: return BMC_DEVICE_UI_GLOBAL_TRI_LED_39;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 39 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_40)
              case 39: return BMC_DEVICE_UI_GLOBAL_TRI_LED_40;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 40 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_41)
              case 40: return BMC_DEVICE_UI_GLOBAL_TRI_LED_41;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 41 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_42)
              case 41: return BMC_DEVICE_UI_GLOBAL_TRI_LED_42;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 42 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_43)
              case 42: return BMC_DEVICE_UI_GLOBAL_TRI_LED_43;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 43 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_44)
              case 43: return BMC_DEVICE_UI_GLOBAL_TRI_LED_44;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 44 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_45)
              case 44: return BMC_DEVICE_UI_GLOBAL_TRI_LED_45;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 45 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_46)
              case 45: return BMC_DEVICE_UI_GLOBAL_TRI_LED_46;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 46 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_47)
              case 46: return BMC_DEVICE_UI_GLOBAL_TRI_LED_47;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 47 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_48)
              case 47: return BMC_DEVICE_UI_GLOBAL_TRI_LED_48;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 48 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_49)
              case 48: return BMC_DEVICE_UI_GLOBAL_TRI_LED_49;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 49 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_50)
              case 49: return BMC_DEVICE_UI_GLOBAL_TRI_LED_50;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 50 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_51)
              case 50: return BMC_DEVICE_UI_GLOBAL_TRI_LED_51;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 51 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_52)
              case 51: return BMC_DEVICE_UI_GLOBAL_TRI_LED_52;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 52 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_53)
              case 52: return BMC_DEVICE_UI_GLOBAL_TRI_LED_53;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 53 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_54)
              case 53: return BMC_DEVICE_UI_GLOBAL_TRI_LED_54;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 54 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_55)
              case 54: return BMC_DEVICE_UI_GLOBAL_TRI_LED_55;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 55 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_56)
              case 55: return BMC_DEVICE_UI_GLOBAL_TRI_LED_56;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 56 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_57)
              case 56: return BMC_DEVICE_UI_GLOBAL_TRI_LED_57;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 57 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_58)
              case 57: return BMC_DEVICE_UI_GLOBAL_TRI_LED_58;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 58 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_59)
              case 58: return BMC_DEVICE_UI_GLOBAL_TRI_LED_59;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 59 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_60)
              case 59: return BMC_DEVICE_UI_GLOBAL_TRI_LED_60;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 60 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_61)
              case 60: return BMC_DEVICE_UI_GLOBAL_TRI_LED_61;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 61 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_62)
              case 61: return BMC_DEVICE_UI_GLOBAL_TRI_LED_62;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 62 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_63)
              case 62: return BMC_DEVICE_UI_GLOBAL_TRI_LED_63;
            #endif
            #if BMC_MAX_GLOBAL_TRI_LEDS > 63 && defined(BMC_DEVICE_UI_GLOBAL_TRI_LED_64)
              case 63: return BMC_DEVICE_UI_GLOBAL_TRI_LED_64;
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
      case BMC_DEVICE_ID_AUX_JACK:
          #if BMC_MAX_AUX_JACKS > 0 
            switch(n){
              #if BMC_MAX_AUX_JACKS > 0 && defined(BMC_DEVICE_UI_AUX_JACK_1)
              case 0: return BMC_DEVICE_UI_AUX_JACK_1;
            #endif
            #if BMC_MAX_AUX_JACKS > 1 && defined(BMC_DEVICE_UI_AUX_JACK_2)
              case 1: return BMC_DEVICE_UI_AUX_JACK_2;
            #endif
            #if BMC_MAX_AUX_JACKS > 2 && defined(BMC_DEVICE_UI_AUX_JACK_3)
              case 2: return BMC_DEVICE_UI_AUX_JACK_3;
            #endif
            #if BMC_MAX_AUX_JACKS > 3 && defined(BMC_DEVICE_UI_AUX_JACK_4)
              case 3: return BMC_DEVICE_UI_AUX_JACK_4;
            #endif
            #if BMC_MAX_AUX_JACKS > 4 && defined(BMC_DEVICE_UI_AUX_JACK_5)
              case 4: return BMC_DEVICE_UI_AUX_JACK_5;
            #endif
            #if BMC_MAX_AUX_JACKS > 5 && defined(BMC_DEVICE_UI_AUX_JACK_6)
              case 5: return BMC_DEVICE_UI_AUX_JACK_6;
            #endif
            #if BMC_MAX_AUX_JACKS > 6 && defined(BMC_DEVICE_UI_AUX_JACK_7)
              case 6: return BMC_DEVICE_UI_AUX_JACK_7;
            #endif
            #if BMC_MAX_AUX_JACKS > 7 && defined(BMC_DEVICE_UI_AUX_JACK_8)
              case 7: return BMC_DEVICE_UI_AUX_JACK_8;
            #endif
            #if BMC_MAX_AUX_JACKS > 8 && defined(BMC_DEVICE_UI_AUX_JACK_9)
              case 8: return BMC_DEVICE_UI_AUX_JACK_9;
            #endif
            #if BMC_MAX_AUX_JACKS > 9 && defined(BMC_DEVICE_UI_AUX_JACK_10)
              case 9: return BMC_DEVICE_UI_AUX_JACK_10;
            #endif
            #if BMC_MAX_AUX_JACKS > 10 && defined(BMC_DEVICE_UI_AUX_JACK_11)
              case 10: return BMC_DEVICE_UI_AUX_JACK_11;
            #endif
            #if BMC_MAX_AUX_JACKS > 11 && defined(BMC_DEVICE_UI_AUX_JACK_12)
              case 11: return BMC_DEVICE_UI_AUX_JACK_12;
            #endif
            #if BMC_MAX_AUX_JACKS > 12 && defined(BMC_DEVICE_UI_AUX_JACK_13)
              case 12: return BMC_DEVICE_UI_AUX_JACK_13;
            #endif
            #if BMC_MAX_AUX_JACKS > 13 && defined(BMC_DEVICE_UI_AUX_JACK_14)
              case 13: return BMC_DEVICE_UI_AUX_JACK_14;
            #endif
            #if BMC_MAX_AUX_JACKS > 14 && defined(BMC_DEVICE_UI_AUX_JACK_15)
              case 14: return BMC_DEVICE_UI_AUX_JACK_15;
            #endif
            #if BMC_MAX_AUX_JACKS > 15 && defined(BMC_DEVICE_UI_AUX_JACK_16)
              case 15: return BMC_DEVICE_UI_AUX_JACK_16;
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
      case BMC_DEVICE_ID_MINI_DISPLAY:
          #if BMC_MAX_MINI_DISPLAY > 0 
            switch(n){
              #if BMC_MAX_MINI_DISPLAY > 0 && defined(BMC_DEVICE_UI_MINI_DISPLAY_1)
              case 0: return BMC_DEVICE_UI_MINI_DISPLAY_1;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 1 && defined(BMC_DEVICE_UI_MINI_DISPLAY_2)
              case 1: return BMC_DEVICE_UI_MINI_DISPLAY_2;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 2 && defined(BMC_DEVICE_UI_MINI_DISPLAY_3)
              case 2: return BMC_DEVICE_UI_MINI_DISPLAY_3;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 3 && defined(BMC_DEVICE_UI_MINI_DISPLAY_4)
              case 3: return BMC_DEVICE_UI_MINI_DISPLAY_4;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 4 && defined(BMC_DEVICE_UI_MINI_DISPLAY_5)
              case 4: return BMC_DEVICE_UI_MINI_DISPLAY_5;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 5 && defined(BMC_DEVICE_UI_MINI_DISPLAY_6)
              case 5: return BMC_DEVICE_UI_MINI_DISPLAY_6;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 6 && defined(BMC_DEVICE_UI_MINI_DISPLAY_7)
              case 6: return BMC_DEVICE_UI_MINI_DISPLAY_7;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 7 && defined(BMC_DEVICE_UI_MINI_DISPLAY_8)
              case 7: return BMC_DEVICE_UI_MINI_DISPLAY_8;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 8 && defined(BMC_DEVICE_UI_MINI_DISPLAY_9)
              case 8: return BMC_DEVICE_UI_MINI_DISPLAY_9;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 9 && defined(BMC_DEVICE_UI_MINI_DISPLAY_10)
              case 9: return BMC_DEVICE_UI_MINI_DISPLAY_10;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 10 && defined(BMC_DEVICE_UI_MINI_DISPLAY_11)
              case 10: return BMC_DEVICE_UI_MINI_DISPLAY_11;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 11 && defined(BMC_DEVICE_UI_MINI_DISPLAY_12)
              case 11: return BMC_DEVICE_UI_MINI_DISPLAY_12;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 12 && defined(BMC_DEVICE_UI_MINI_DISPLAY_13)
              case 12: return BMC_DEVICE_UI_MINI_DISPLAY_13;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 13 && defined(BMC_DEVICE_UI_MINI_DISPLAY_14)
              case 13: return BMC_DEVICE_UI_MINI_DISPLAY_14;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 14 && defined(BMC_DEVICE_UI_MINI_DISPLAY_15)
              case 14: return BMC_DEVICE_UI_MINI_DISPLAY_15;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 15 && defined(BMC_DEVICE_UI_MINI_DISPLAY_16)
              case 15: return BMC_DEVICE_UI_MINI_DISPLAY_16;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 16 && defined(BMC_DEVICE_UI_MINI_DISPLAY_17)
              case 16: return BMC_DEVICE_UI_MINI_DISPLAY_17;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 17 && defined(BMC_DEVICE_UI_MINI_DISPLAY_18)
              case 17: return BMC_DEVICE_UI_MINI_DISPLAY_18;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 18 && defined(BMC_DEVICE_UI_MINI_DISPLAY_19)
              case 18: return BMC_DEVICE_UI_MINI_DISPLAY_19;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 19 && defined(BMC_DEVICE_UI_MINI_DISPLAY_20)
              case 19: return BMC_DEVICE_UI_MINI_DISPLAY_20;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 20 && defined(BMC_DEVICE_UI_MINI_DISPLAY_21)
              case 20: return BMC_DEVICE_UI_MINI_DISPLAY_21;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 21 && defined(BMC_DEVICE_UI_MINI_DISPLAY_22)
              case 21: return BMC_DEVICE_UI_MINI_DISPLAY_22;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 22 && defined(BMC_DEVICE_UI_MINI_DISPLAY_23)
              case 22: return BMC_DEVICE_UI_MINI_DISPLAY_23;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 23 && defined(BMC_DEVICE_UI_MINI_DISPLAY_24)
              case 23: return BMC_DEVICE_UI_MINI_DISPLAY_24;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 24 && defined(BMC_DEVICE_UI_MINI_DISPLAY_25)
              case 24: return BMC_DEVICE_UI_MINI_DISPLAY_25;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 25 && defined(BMC_DEVICE_UI_MINI_DISPLAY_26)
              case 25: return BMC_DEVICE_UI_MINI_DISPLAY_26;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 26 && defined(BMC_DEVICE_UI_MINI_DISPLAY_27)
              case 26: return BMC_DEVICE_UI_MINI_DISPLAY_27;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 27 && defined(BMC_DEVICE_UI_MINI_DISPLAY_28)
              case 27: return BMC_DEVICE_UI_MINI_DISPLAY_28;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 28 && defined(BMC_DEVICE_UI_MINI_DISPLAY_29)
              case 28: return BMC_DEVICE_UI_MINI_DISPLAY_29;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 29 && defined(BMC_DEVICE_UI_MINI_DISPLAY_30)
              case 29: return BMC_DEVICE_UI_MINI_DISPLAY_30;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 30 && defined(BMC_DEVICE_UI_MINI_DISPLAY_31)
              case 30: return BMC_DEVICE_UI_MINI_DISPLAY_31;
            #endif
            #if BMC_MAX_MINI_DISPLAY > 31 && defined(BMC_DEVICE_UI_MINI_DISPLAY_32)
              case 31: return BMC_DEVICE_UI_MINI_DISPLAY_32;
            #endif
    
            }
          #endif
          break;
      case BMC_DEVICE_ID_LCD:
          #if BMC_MAX_LCD > 0 
            switch(n){
              #if BMC_MAX_LCD > 0 && defined(BMC_DEVICE_UI_LCD_1)
              case 0: return BMC_DEVICE_UI_LCD_1;
            #endif
            #if BMC_MAX_LCD > 1 && defined(BMC_DEVICE_UI_LCD_2)
              case 1: return BMC_DEVICE_UI_LCD_2;
            #endif
            #if BMC_MAX_LCD > 2 && defined(BMC_DEVICE_UI_LCD_3)
              case 2: return BMC_DEVICE_UI_LCD_3;
            #endif
            #if BMC_MAX_LCD > 3 && defined(BMC_DEVICE_UI_LCD_4)
              case 3: return BMC_DEVICE_UI_LCD_4;
            #endif
            #if BMC_MAX_LCD > 4 && defined(BMC_DEVICE_UI_LCD_5)
              case 4: return BMC_DEVICE_UI_LCD_5;
            #endif
            #if BMC_MAX_LCD > 5 && defined(BMC_DEVICE_UI_LCD_6)
              case 5: return BMC_DEVICE_UI_LCD_6;
            #endif
            #if BMC_MAX_LCD > 6 && defined(BMC_DEVICE_UI_LCD_7)
              case 6: return BMC_DEVICE_UI_LCD_7;
            #endif
            #if BMC_MAX_LCD > 7 && defined(BMC_DEVICE_UI_LCD_8)
              case 7: return BMC_DEVICE_UI_LCD_8;
            #endif
    
            }
          #endif
          break;
      case BMC_DEVICE_ID_MAGIC_ENCODER:
          #if BMC_MAX_MAGIC_ENCODERS > 0 
            switch(n){
              #if BMC_MAX_MAGIC_ENCODERS > 0 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_1)
              case 0: return BMC_DEVICE_UI_MAGIC_ENCODER_1;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 1 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_2)
              case 1: return BMC_DEVICE_UI_MAGIC_ENCODER_2;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 2 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_3)
              case 2: return BMC_DEVICE_UI_MAGIC_ENCODER_3;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 3 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_4)
              case 3: return BMC_DEVICE_UI_MAGIC_ENCODER_4;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 4 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_5)
              case 4: return BMC_DEVICE_UI_MAGIC_ENCODER_5;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 5 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_6)
              case 5: return BMC_DEVICE_UI_MAGIC_ENCODER_6;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 6 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_7)
              case 6: return BMC_DEVICE_UI_MAGIC_ENCODER_7;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 7 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_8)
              case 7: return BMC_DEVICE_UI_MAGIC_ENCODER_8;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 8 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_9)
              case 8: return BMC_DEVICE_UI_MAGIC_ENCODER_9;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 9 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_10)
              case 9: return BMC_DEVICE_UI_MAGIC_ENCODER_10;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 10 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_11)
              case 10: return BMC_DEVICE_UI_MAGIC_ENCODER_11;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 11 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_12)
              case 11: return BMC_DEVICE_UI_MAGIC_ENCODER_12;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 12 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_13)
              case 12: return BMC_DEVICE_UI_MAGIC_ENCODER_13;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 13 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_14)
              case 13: return BMC_DEVICE_UI_MAGIC_ENCODER_14;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 14 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_15)
              case 14: return BMC_DEVICE_UI_MAGIC_ENCODER_15;
            #endif
            #if BMC_MAX_MAGIC_ENCODERS > 15 && defined(BMC_DEVICE_UI_MAGIC_ENCODER_16)
              case 15: return BMC_DEVICE_UI_MAGIC_ENCODER_16;
            #endif
    
            }
          #endif
          break;
      case BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER:
          #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0 
            switch(n){
              #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_1)
              case 0: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_1;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 1 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_2)
              case 1: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_2;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 2 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_3)
              case 2: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_3;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 3 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_4)
              case 3: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_4;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 4 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_5)
              case 4: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_5;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 5 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_6)
              case 5: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_6;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 6 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_7)
              case 6: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_7;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 7 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_8)
              case 7: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_8;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 8 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_9)
              case 8: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_9;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 9 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_10)
              case 9: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_10;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 10 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_11)
              case 10: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_11;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 11 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_12)
              case 11: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_12;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 12 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_13)
              case 12: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_13;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 13 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_14)
              case 13: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_14;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 14 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_15)
              case 14: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_15;
            #endif
            #if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 15 && defined(BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_16)
              case 15: return BMC_DEVICE_UI_GLOBAL_MAGIC_ENCODER_16;
            #endif
    
            }
          #endif
          break;
}
    BMCUIData e;
    return e;
  }
static BMCLinkData getLinkData(uint16_t n){
#if BMC_MAX_LINKS > 0
  switch(n){
#if BMC_MAX_LINKS > 0 && defined(BMC_LINK_1)
  case 0: return BMC_LINK_1;
#endif
#if BMC_MAX_LINKS > 1 && defined(BMC_LINK_2)
  case 1: return BMC_LINK_2;
#endif
#if BMC_MAX_LINKS > 2 && defined(BMC_LINK_3)
  case 2: return BMC_LINK_3;
#endif
#if BMC_MAX_LINKS > 3 && defined(BMC_LINK_4)
  case 3: return BMC_LINK_4;
#endif
#if BMC_MAX_LINKS > 4 && defined(BMC_LINK_5)
  case 4: return BMC_LINK_5;
#endif
#if BMC_MAX_LINKS > 5 && defined(BMC_LINK_6)
  case 5: return BMC_LINK_6;
#endif
#if BMC_MAX_LINKS > 6 && defined(BMC_LINK_7)
  case 6: return BMC_LINK_7;
#endif
#if BMC_MAX_LINKS > 7 && defined(BMC_LINK_8)
  case 7: return BMC_LINK_8;
#endif
#if BMC_MAX_LINKS > 8 && defined(BMC_LINK_9)
  case 8: return BMC_LINK_9;
#endif
#if BMC_MAX_LINKS > 9 && defined(BMC_LINK_10)
  case 9: return BMC_LINK_10;
#endif
#if BMC_MAX_LINKS > 10 && defined(BMC_LINK_11)
  case 10: return BMC_LINK_11;
#endif
#if BMC_MAX_LINKS > 11 && defined(BMC_LINK_12)
  case 11: return BMC_LINK_12;
#endif
#if BMC_MAX_LINKS > 12 && defined(BMC_LINK_13)
  case 12: return BMC_LINK_13;
#endif
#if BMC_MAX_LINKS > 13 && defined(BMC_LINK_14)
  case 13: return BMC_LINK_14;
#endif
#if BMC_MAX_LINKS > 14 && defined(BMC_LINK_15)
  case 14: return BMC_LINK_15;
#endif
#if BMC_MAX_LINKS > 15 && defined(BMC_LINK_16)
  case 15: return BMC_LINK_16;
#endif
#if BMC_MAX_LINKS > 16 && defined(BMC_LINK_17)
  case 16: return BMC_LINK_17;
#endif
#if BMC_MAX_LINKS > 17 && defined(BMC_LINK_18)
  case 17: return BMC_LINK_18;
#endif
#if BMC_MAX_LINKS > 18 && defined(BMC_LINK_19)
  case 18: return BMC_LINK_19;
#endif
#if BMC_MAX_LINKS > 19 && defined(BMC_LINK_20)
  case 19: return BMC_LINK_20;
#endif
#if BMC_MAX_LINKS > 20 && defined(BMC_LINK_21)
  case 20: return BMC_LINK_21;
#endif
#if BMC_MAX_LINKS > 21 && defined(BMC_LINK_22)
  case 21: return BMC_LINK_22;
#endif
#if BMC_MAX_LINKS > 22 && defined(BMC_LINK_23)
  case 22: return BMC_LINK_23;
#endif
#if BMC_MAX_LINKS > 23 && defined(BMC_LINK_24)
  case 23: return BMC_LINK_24;
#endif
#if BMC_MAX_LINKS > 24 && defined(BMC_LINK_25)
  case 24: return BMC_LINK_25;
#endif
#if BMC_MAX_LINKS > 25 && defined(BMC_LINK_26)
  case 25: return BMC_LINK_26;
#endif
#if BMC_MAX_LINKS > 26 && defined(BMC_LINK_27)
  case 26: return BMC_LINK_27;
#endif
#if BMC_MAX_LINKS > 27 && defined(BMC_LINK_28)
  case 27: return BMC_LINK_28;
#endif
#if BMC_MAX_LINKS > 28 && defined(BMC_LINK_29)
  case 28: return BMC_LINK_29;
#endif
#if BMC_MAX_LINKS > 29 && defined(BMC_LINK_30)
  case 29: return BMC_LINK_30;
#endif
#if BMC_MAX_LINKS > 30 && defined(BMC_LINK_31)
  case 30: return BMC_LINK_31;
#endif
#if BMC_MAX_LINKS > 31 && defined(BMC_LINK_32)
  case 31: return BMC_LINK_32;
#endif
#if BMC_MAX_LINKS > 32 && defined(BMC_LINK_33)
  case 32: return BMC_LINK_33;
#endif
#if BMC_MAX_LINKS > 33 && defined(BMC_LINK_34)
  case 33: return BMC_LINK_34;
#endif
#if BMC_MAX_LINKS > 34 && defined(BMC_LINK_35)
  case 34: return BMC_LINK_35;
#endif
#if BMC_MAX_LINKS > 35 && defined(BMC_LINK_36)
  case 35: return BMC_LINK_36;
#endif
#if BMC_MAX_LINKS > 36 && defined(BMC_LINK_37)
  case 36: return BMC_LINK_37;
#endif
#if BMC_MAX_LINKS > 37 && defined(BMC_LINK_38)
  case 37: return BMC_LINK_38;
#endif
#if BMC_MAX_LINKS > 38 && defined(BMC_LINK_39)
  case 38: return BMC_LINK_39;
#endif
#if BMC_MAX_LINKS > 39 && defined(BMC_LINK_40)
  case 39: return BMC_LINK_40;
#endif
#if BMC_MAX_LINKS > 40 && defined(BMC_LINK_41)
  case 40: return BMC_LINK_41;
#endif
#if BMC_MAX_LINKS > 41 && defined(BMC_LINK_42)
  case 41: return BMC_LINK_42;
#endif
#if BMC_MAX_LINKS > 42 && defined(BMC_LINK_43)
  case 42: return BMC_LINK_43;
#endif
#if BMC_MAX_LINKS > 43 && defined(BMC_LINK_44)
  case 43: return BMC_LINK_44;
#endif
#if BMC_MAX_LINKS > 44 && defined(BMC_LINK_45)
  case 44: return BMC_LINK_45;
#endif
#if BMC_MAX_LINKS > 45 && defined(BMC_LINK_46)
  case 45: return BMC_LINK_46;
#endif
#if BMC_MAX_LINKS > 46 && defined(BMC_LINK_47)
  case 46: return BMC_LINK_47;
#endif
#if BMC_MAX_LINKS > 47 && defined(BMC_LINK_48)
  case 47: return BMC_LINK_48;
#endif
#if BMC_MAX_LINKS > 48 && defined(BMC_LINK_49)
  case 48: return BMC_LINK_49;
#endif
#if BMC_MAX_LINKS > 49 && defined(BMC_LINK_50)
  case 49: return BMC_LINK_50;
#endif
#if BMC_MAX_LINKS > 50 && defined(BMC_LINK_51)
  case 50: return BMC_LINK_51;
#endif
#if BMC_MAX_LINKS > 51 && defined(BMC_LINK_52)
  case 51: return BMC_LINK_52;
#endif
#if BMC_MAX_LINKS > 52 && defined(BMC_LINK_53)
  case 52: return BMC_LINK_53;
#endif
#if BMC_MAX_LINKS > 53 && defined(BMC_LINK_54)
  case 53: return BMC_LINK_54;
#endif
#if BMC_MAX_LINKS > 54 && defined(BMC_LINK_55)
  case 54: return BMC_LINK_55;
#endif
#if BMC_MAX_LINKS > 55 && defined(BMC_LINK_56)
  case 55: return BMC_LINK_56;
#endif
#if BMC_MAX_LINKS > 56 && defined(BMC_LINK_57)
  case 56: return BMC_LINK_57;
#endif
#if BMC_MAX_LINKS > 57 && defined(BMC_LINK_58)
  case 57: return BMC_LINK_58;
#endif
#if BMC_MAX_LINKS > 58 && defined(BMC_LINK_59)
  case 58: return BMC_LINK_59;
#endif
#if BMC_MAX_LINKS > 59 && defined(BMC_LINK_60)
  case 59: return BMC_LINK_60;
#endif
#if BMC_MAX_LINKS > 60 && defined(BMC_LINK_61)
  case 60: return BMC_LINK_61;
#endif
#if BMC_MAX_LINKS > 61 && defined(BMC_LINK_62)
  case 61: return BMC_LINK_62;
#endif
#if BMC_MAX_LINKS > 62 && defined(BMC_LINK_63)
  case 62: return BMC_LINK_63;
#endif
#if BMC_MAX_LINKS > 63 && defined(BMC_LINK_64)
  case 63: return BMC_LINK_64;
#endif

  }
#endif
BMCLinkData buff;
return buff;
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
static bool isMuxInAnalogPinIndex(uint8_t n){
#if BMC_MAX_MUX_IN_ANALOG > 0
  return (n>=(BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT) && n<(BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG));
#endif
  return false;
}

// MUX IN KEYPAD
static bool isMuxInKeypadPin(uint8_t n){
#if BMC_MAX_MUX_IN_KEYPAD > 0
  return (n>=(64+BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG) && n<(64+BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG+BMC_MAX_MUX_IN_KEYPAD));
#endif
  return false;
}
static bool isMuxInKeypadPinIndex(uint8_t n){
#if BMC_MAX_MUX_IN_KEYPAD > 0
  return (n>=(BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG) && n<(BMC_MAX_MUX_GPIO+BMC_MAX_MUX_IN+BMC_MAX_MUX_OUT+BMC_MAX_MUX_IN_ANALOG+BMC_MAX_MUX_IN_KEYPAD));
#endif
  return false;
}
// MUX INPUT
static bool isMuxInputPin(uint8_t n){
  if(isMuxInPin(n)){return true;}
  if(isMuxInAnalogPin(n)){return true;}
  if(isMuxInKeypadPinIndex(n)){return true;}
  return false;
}
};
#endif