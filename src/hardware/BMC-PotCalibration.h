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
  bool toggle(uint8_t t_deviceType, uint16_t n){
    if(!active()){
      //start
      deviceType = t_deviceType;
      potIndex = n;
      min = 1023;
      max = 0;
      return true;
    } else {
      // complete
      reset();
    }
    return false;
  }
  bool active(){
    return (potIndex!=0xFFFF);
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
  uint8_t getDeviceType(){
    return deviceType;
  }
  uint16_t getIndex(){
    return potIndex;
  }
  uint16_t getMin(){
    return min;
  }
  uint16_t getMax(){
    return max;
  }
private:
  uint8_t deviceType = 0;
  uint16_t potIndex = 0xFFFF;
  uint16_t min = 1023;
  uint16_t max = 0;
  void reset(){
    deviceType = 0;
    potIndex = 0xFFFF;
    min = 1023;
    max = 0;
  }
};
#endif
