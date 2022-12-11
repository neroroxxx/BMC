/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_OBE_DEF_H
#define BMC_OBE_DEF_H

#include "utility/BMC-Def.h"

#define BMC_COLOR_EDITOR_GRAY 0x18C3
#define BMC_COLOR_EDITOR_TXT 0xDEFB

// 7=diamond, 14=music note, 16=carret right, 26=arrow right
#define BMC_OBE_SEL_CHAR_HEART 3
#define BMC_OBE_SEL_CHAR_DIAMOND 7
#define BMC_OBE_SEL_CHAR_MUSIC 14
#define BMC_OBE_SEL_CHAR_CARET 16
#define BMC_OBE_SEL_CHAR_ARROW 26

#define BMC_OBE_SEL_CHAR BMC_OBE_SEL_CHAR_ARROW


#define BMC_OBE_LIST_HEAD_H 32
#define BMC_OBE_LIST_HEAD_TXT_SIZE 2
#define BMC_OBE_LIST_HEAD_CHAR_WIDTH (6*BMC_OBE_LIST_HEAD_TXT_SIZE)
#define BMC_OBE_LIST_HEAD_TXT_Y 8 // 6 for 3 pixel font

#define BMC_OBE_LIST_H 26
#define BMC_OBE_LIST_TXT_Y 7
#define BMC_OBE_LIST_TXT_SIZE 2

#define BMC_OBE_LEVEL_MAIN 0
#define BMC_OBE_LEVEL_SETTINGS 1
#define BMC_OBE_LEVEL_EVENTS 2
#define BMC_OBE_LEVEL_NAMES 3
#define BMC_OBE_LEVEL_DEVICES 4
#define BMC_OBE_LEVEL_PAGES 5
#define BMC_OBE_LEVEL_NAMES_EDITOR 6

#endif