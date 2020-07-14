/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This struct is used throut BMC to scroll (increase/decrease) numbers
  I'm using a struct instead of a class make it easier to set the value
  required to scroll the number
  There are many parameters used to scroll these numbers including:

  lowest = lowest value we can ever reach
  highest = highest value we can ever reach
  amount = how much to scroll the unmber
  direction = up (true) or down (false)
  endless = true to endlessly scroll from low to high and vice-versa
  value =  the number to scroll

*/
#ifndef BMC_TMP_SCROLL_H
#define BMC_TMP_SCROLL_H
#include <Arduino.h>
#include "utility/BMC-Timer.h"
#include "utility/BMC-Flags.h"

#define BMC_TMP_SCROLLER_ACTIVE 0
// if this flag is true it's a preset scroll
#define BMC_TMP_SCROLLER_IS_PRESET 1

class BMCTmpScroller {
public:
  BMCTmpScroller(){
    reset();
  }
  void update(){
    if(timer.complete()){
      reset();
    }
  }
  bool isActive(){
    return flags.read(BMC_TMP_SCROLLER_ACTIVE);
  }
  bool isPreset(){
    return flags.read(BMC_TMP_SCROLLER_IS_PRESET);
  }
  bool isPage(){
    return !flags.read(BMC_TMP_SCROLLER_IS_PRESET);
  }
  void set(uint16_t t_value, bool isPreset=false){
    reset();
    value = t_value;
    timer.start(5000);
    flags.on(BMC_TMP_SCROLLER_ACTIVE);
    flags.write(BMC_TMP_SCROLLER_IS_PRESET, isPreset);
  }
  uint16_t get(){
    if(!isActive()){
      return 0;
    }
    uint16_t ret = value;
    reset();
    return ret;
  }
  void reset(){
    value = 0;
    flags.reset();
    timer.stop();
  }

private:
  uint16_t value = 0;
  BMCTimer timer;
  BMCFlags <uint8_t> flags;

};
#endif
