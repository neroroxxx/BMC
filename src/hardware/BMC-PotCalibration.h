/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_POT_CALIBRATION_H
#define BMC_POT_CALIBRATION_H
#include "utility/BMC-Def.h"

class BMCPotCalibration {
public:
  BMCPotCalibration(){
    reset();
  }
  void toggle(uint8_t n){
    if(!active()){
      //start
      potIndex = n;
      min = 1023;
      max = 0;
    } else {
      // complete
      reset();
    }
  }
  bool active(){
    return (potIndex!=255);
  }
  void cancel(){
    reset();
  }
  void setValue(uint16_t value){
    if(active()){
      if(value < min){
        min = value;
      }
      if(value > max){
        max = value;
      }
    }
  }
  uint8_t getIndex(){
    return potIndex;
  }
  uint16_t getMin(){
    return min;
  }
  uint16_t getMax(){
    return max;
  }
private:
  uint8_t potIndex = 255;
  uint16_t min = 1023;
  uint16_t max = 0;
  void reset(){
    potIndex = 255;
    min = 1023;
    max = 0;
  }
};
#endif
