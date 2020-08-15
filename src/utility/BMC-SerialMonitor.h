/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_SERIAL_MONITOR_H
#define BMC_SERIAL_MONITOR_H
#ifdef BMC_DEBUG

#include <Arduino.h>

#define BMC_SERIAL_MONITOR_MAX_CHARS 25

#define BMC_SERIAL_MONITOR_FLAG_READY 0

class BMCSerialMonitor {
public:
  BMCSerialMonitor(){

  }
  void setup(){
    delay(2000);
    flags = 0;
  }
  bool read(char *buff){
    static uint8_t i = 0;
    char receivedChar;
    while(Serial.available() > 0 && !readFlag(BMC_SERIAL_MONITOR_FLAG_READY)){
      receivedChar = Serial.read();
      //if(receivedChar != '\n') {
      if((uint8_t)receivedChar != 10) {
        buff[i] = receivedChar;
        i++;
        if(i >= BMC_SERIAL_MONITOR_MAX_CHARS){
          i = BMC_SERIAL_MONITOR_MAX_CHARS-1;
        }
      } else {
        //buff[i] = '\0';
        buff[i] = 0;
        i = 0;
        writeFlag(BMC_SERIAL_MONITOR_FLAG_READY, true);
      }
    }
    if(readFlag(BMC_SERIAL_MONITOR_FLAG_READY)){
      writeFlag(BMC_SERIAL_MONITOR_FLAG_READY, false);
      return true;
    }
    return false;
  }
  // static
  static void printArray(bool inHex, uint8_t *t_data, uint16_t t_size){
    if(inHex){
      Serial.print("(HEX) (");
    } else {
      Serial.print("(DEC) (");
    }
    Serial.print(t_size, inHex?HEX:DEC);
    Serial.print(")");
    for(uint16_t i = 0 ; i < t_size ; i++){
      Serial.print(" ");
      Serial.print(t_data[i], inHex?HEX:DEC);
    }
    Serial.println("");
  }
private:
  uint8_t flags;
  char debugChars[BMC_SERIAL_MONITOR_MAX_CHARS];
  bool readFlag(uint8_t t_offset){
    return bitRead(flags, t_offset);
  }
  void writeFlag(uint8_t t_offset, bool t_value){
    bitWrite(flags, t_offset, t_value);
  }
};
#endif
#endif
