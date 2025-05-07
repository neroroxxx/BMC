/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  A wrapper to read/write bits instead of using bools
  If you require using muliple bool variables each bool takes up 1 Byte
  Instead you can use one 8-bit byte for 8 bool values.
  The class is a template so you can use <uint8_t>, <uint16_t>, or <uint32_t>
  Giving you up to 32 booleans using only 4 bytes instead of 32 bytes!
  See the BMCFlags Example in the examples folder
  BMCFlags can be used as a standalone class as it does not require BMC-Def.h
*/
#ifndef __BMC_FLAGS_H__
#define __BMC_FLAGS_H__

#include <Arduino.h>

template <typename T>
class BMCFlags {
private:
  T flags = 0;
public:
  // write the value for all flags
  void write(T t_value){
    flags = t_value;
  }
  // returns the value of all flags
  T read(){
    return flags;
  }
  // if you include the bit value to read() it will return true/false
  // if the bit is on or off
  bool read(uint8_t bit){
    return bitRead(flags, bit);
  }
  bool compare(uint8_t bit, bool t_value){
    return read(bit)==t_value;
  }
  bool compareFlags(uint8_t bitA, uint8_t bitB){
    return read(bitA) == read(bitB);
  }
  // turn the bit on/off
  // bit = the bit that will be toggle 0 to n,
  // where n is the number of bits in the template
  // value = true/false, 0/1
  void write(uint8_t bit, bool value){
    bitWrite(flags, bit, value);
  }
  // turns the bit on (true)
  void on(uint8_t bit){
    bitSet(flags, bit);
  }
  // turns the bit off (false)
  void off(uint8_t bit){
    bitClear(flags, bit);
  }
  // flip all the bits in the flag
  void flip(){
    flags = ~flags;
  }
  // toggle the bit value from 0 to 1 or vice-versa
  bool toggle(uint8_t bit){
    flags ^= 1UL << bit;
    return bitRead(flags, bit);
  }
  // if the bit is on, it will turn it off and return true
  // if the bit is off it will leave the bit alone and return false
  // useful when you want to know the state of the bit only once if it's true
  // this is used on BMC to check if something has changed then reverting
  // the bit to 0
  bool toggleIfTrue(uint8_t bit){
    if(bitRead(flags, bit)){
      bitClear(flags, bit);
      return true;
    }
    return false;
  }
  // same as toggleIfTrue but it toggles the bit to 1 if it's 0
  // useful if you want to check if something has already happened.
  bool toggleIfFalse(uint8_t bit){
    if(!bitRead(flags,bit)){
      bitSet(flags, bit);
      return false;
    }
    return true;
  }
  // set all bits to 0
  void reset(){
    reset(0);
  }
  // set all bits to 0
  // excluded =  any bits that you want to keep on when you reset
  // this can be used for default values
  void reset(T excluded){
    if(excluded){
      flags &= excluded;
    } else {
      flags = 0;
    }
  }
  // reset all flags execpt the bit passed
  void resetNotBit(T n){
    uint8_t tmp = 0;
    bitWrite(tmp, n, bitRead(flags, n));
    flags = tmp;
  }
};
#endif
