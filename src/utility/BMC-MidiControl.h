/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/

#ifndef BMC_MIDICONTROL_H
#define BMC_MIDICONTROL_H
#include <Arduino.h>

struct __attribute__ ((packed)) BMCMidiControl {
  bool write = false;
  uint8_t group = 0;
  uint8_t parameter = 0;
  uint32_t value = 0;

  bool set(bool t_write, BMCMidiMessage message){
    if(message.size()==18){
      write = t_write;
      group = message.get7Bits(9);
      parameter = message.get7Bits(10);
      value = message.get32Bits(11);
      return true;
    }
    return false;
  }
  bool set(uint8_t t_write, uint8_t t_group, uint8_t t_parameter, uint32_t t_value){
    write = t_write;
    group = t_group;
    parameter = t_parameter;
    value = t_value;
    return true;
  }
  bool isWrite(){
    return write;
  }
  uint8_t getGroup(){
    return group;
  }
  uint8_t getParameter(){
    return parameter;
  }
  uint32_t getValue(){
    return value;
  }
  void reset(){
    group = 0;
    parameter = 0;
    value = 0;
  }
};


#endif
