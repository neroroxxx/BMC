/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#ifndef BMC_MAGIC_ENCODER_H
#define BMC_MAGIC_ENCODER_H
#if BMC_MAX_MAGIC_ENCODERS > 0 || BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0

#include <Wire.h>
#include "utility/BMC-Def.h"

#define BMC_ME_DEFAULT_ADDRESS 0x40

#define BMC_ME_LIMIT_10  0
#define BMC_ME_LIMIT_100 1

#define BMC_ME_BRIGHTNESS_LOW   0
#define BMC_ME_BRIGHTNESS_MID   1
#define BMC_ME_BRIGHTNESS_HIGH  2

#define BMC_ME_RED                    0
#define BMC_ME_GREEN                  1
#define BMC_ME_BLUE                   2
#define BMC_ME_MAGENTA                3
#define BMC_ME_CYAN                   4
#define BMC_ME_YELLOW                 5
#define BMC_ME_RAINBOW                6
#define BMC_ME_RAINBOW_ALT            7
#define BMC_ME_GREEN_YELLOW_RED       8
#define BMC_ME_GREEN_YELLOW_RED_ALT   9
#define BMC_ME_USER_COLOR             10

#define BMC_ME_MAX_COLORS             11

#define BMC_ME_DOT          0
#define BMC_ME_BOOST_CUT    1
#define BMC_ME_WRAP         2
#define BMC_ME_SPREAD       3
#define BMC_ME_BPM      4

#define BMC_ME_MAX_VIEWS    5

#define BMC_ME_CMD_COLORS             0
#define BMC_ME_CMD_SETTINGS           1
#define BMC_ME_CMD_COLOR              2
#define BMC_ME_CMD_MIDDLE_COLOR       3
#define BMC_ME_CMD_CENTERED_COLOR     4
#define BMC_ME_CMD_USE_MIDDLE_COLOR   5
#define BMC_ME_CMD_USE_CENTERED_LED   6
#define BMC_ME_CMD_VIEW               7
#define BMC_ME_CMD_LIMIT              8
#define BMC_ME_CMD_BRIGHTNESS         9
#define BMC_ME_CMD_USER_COLOR         10
#define BMC_ME_CMD_STATUS_LED         11
#define BMC_ME_CMD_TEST_MODE          12
/*
#define ROX_NONE      0
#define ROX_RELEASED  1
#define ROX_PRESSED   2
#define ROX_HELD      3
#define ROX_DOUBLE    4
*/
class BMCMagicEncoder {
  private:
    uint8_t address = BMC_ME_DEFAULT_ADDRESS;
    uint8_t i2cData[3];
    uint8_t limit = 100;
    uint8_t ledValue = 0;
    unsigned long timer = 0;
    uint8_t event = 0;
    //void (*onUpdateCallback)(uint8_t btnType, uint8_t ticks, bool clockwise);
    void sendByte(uint8_t t_value){
      Wire.beginTransmission(address);
      Wire.write(t_value);
      Wire.endTransmission();
    }
    void sendSettings(uint8_t cmd, uint8_t a, uint8_t b, uint8_t c){
      // i2cData[0] = (a<<4) | cmd;
      // i2cData[1] = (c<<4) | b;
      i2cData[0] = cmd;
      i2cData[1] = (b<<4) | a;
      i2cData[2] = c;
      Wire.beginTransmission(address);
      Wire.write(i2cData, 2);
      Wire.endTransmission();
    }
    void sendSettings(uint8_t cmd, uint8_t t_value){
      i2cData[0] = cmd;
      i2cData[1] = t_value;
      Wire.beginTransmission(address);
      Wire.write(i2cData, 2);
      Wire.endTransmission();
    }
  public:
    BMCMagicEncoder(){
      memset(i2cData, 0, 2);
    }
    bool begin(uint8_t t_address){
      if(t_address>=BMC_ME_DEFAULT_ADDRESS && t_address<=(BMC_ME_DEFAULT_ADDRESS+16)){
        address = t_address;
      }
      Wire.begin();
      delay(1);
      sendByte(0);
      Wire.requestFrom(address, (uint8_t)1);
      unsigned long t = millis();
      bool timedout = false;
      while(Wire.available()==0){
        Wire.requestFrom(address, (uint8_t)1);
        if(((unsigned long)millis()-t)>=5000){
          timedout = true;
          break;
        }
      }
      if(timedout){
        return false;
      }
      while(Wire.available()>0){
        BMC_PRINTLN(">>>",Wire.read());
      }
      timer = millis();
      return true;
    }
    void reassign(uint8_t t_rotation){
      // add rotation to magic encoder firmware
      t_rotation = constrain(t_rotation, 0, 3);
    }
    bool update(uint8_t t_delay=2){
      event = 0;
      t_delay = t_delay==0 ? 1 : t_delay;
      if((unsigned long)millis()-timer < t_delay){
        return false;
      }
      timer = millis();
      Wire.requestFrom(address, (uint8_t)1);
      while(Wire.available()>0) {
        event = Wire.read();
        if(event > 0){
          return true;
        }
      }
      return false;
    }
    uint8_t getEvent(){
      return event;
    }
    uint8_t getTrigger(){
      return event & 0x07;
    }
    bool increased(){
      return bitRead(event, 7);
    }
    uint8_t getTicks(){
      return (event>>3) & 0x0F;
    }
    bool setValue(uint8_t t_value){
      // bit 7 of the value tells the controller that this is the ring value
      // if bit 7 is not set it's seen as a reset
      t_value = constrain(t_value, 0, limit) + 128;
      if(ledValue != t_value){
        ledValue = t_value;
        sendByte(ledValue);
        return true;
      }
      return false;
    }
    void setColors(uint8_t t_mainColor, uint8_t t_middleColor=255, uint8_t t_centeredColor=255){
      if(t_middleColor==255){
        t_middleColor = t_mainColor;
      }
      if(t_centeredColor==255){
        t_centeredColor = t_mainColor;
      }
      t_mainColor = constrain(t_mainColor, 0, BMC_ME_MAX_COLORS-1);
      t_middleColor = constrain(t_middleColor, 0, BMC_ME_MAX_COLORS-1);
      t_centeredColor = constrain(t_centeredColor, 0, BMC_ME_MAX_COLORS-1);
      sendSettings(BMC_ME_CMD_COLORS, t_mainColor, t_middleColor, t_centeredColor);
    }
    void setSettings(uint8_t t_view, uint8_t t_limit, uint8_t t_brightness){
      t_view = constrain(t_view, 0, (BMC_ME_MAX_VIEWS-1));
      t_limit = constrain(t_limit, 0, 1);
      t_brightness = constrain(t_brightness, 0, 2);
      limit = t_limit==0 ? 10 : 100;
      sendSettings(BMC_ME_CMD_SETTINGS, t_view, t_limit, t_brightness);
    }
    void setColor(uint8_t t_value){
      t_value = constrain(t_value, 0, BMC_ME_MAX_COLORS-1);
      sendSettings(BMC_ME_CMD_COLOR, t_value);
    }
    void setMiddleColor(uint8_t t_value){
      t_value = constrain(t_value, 0, BMC_ME_MAX_COLORS-1);
      sendSettings(BMC_ME_CMD_MIDDLE_COLOR, t_value);
    }
    void setCenteredColor(uint8_t t_value){
      t_value = constrain(t_value, 0, BMC_ME_MAX_COLORS-1);
      sendSettings(BMC_ME_CMD_CENTERED_COLOR, t_value);
    }
    void setUseMiddleColor(uint8_t t_value){
      t_value = constrain(t_value, 0, 1);
      sendSettings(BMC_ME_CMD_USE_MIDDLE_COLOR, t_value);
    }
    void setUseCenteredLed(uint8_t t_value){
      t_value = constrain(t_value, 0, 1);
      sendSettings(BMC_ME_CMD_USE_CENTERED_LED, t_value);
    }
    void setView(uint8_t t_value){
      t_value = constrain(t_value, 0, (BMC_ME_MAX_VIEWS-1));
      sendSettings(BMC_ME_CMD_VIEW, t_value);
    }
    void setLimit(uint8_t t_value){
      t_value = constrain(t_value, 0, 1);
      sendSettings(BMC_ME_CMD_LIMIT, t_value);
    }
    void setBrightness(uint8_t t_value){
      t_value = constrain(t_value, 0, 2);
      sendSettings(BMC_ME_CMD_BRIGHTNESS, t_value);
    }
    void setStatusLed(uint8_t t_value){
      t_value = constrain(t_value, 0, 1);
      sendSettings(BMC_ME_CMD_STATUS_LED, t_value);
    }
    void setUserColor(uint8_t t_red, uint8_t t_green,uint8_t t_blue){
      t_red   = map(t_red, 0, 255, 0, 15);
      t_green = map(t_green, 0, 255, 0, 15);
      t_blue  = map(t_blue, 0, 255, 0, 15);
      sendSettings(BMC_ME_CMD_USER_COLOR, t_red, t_green, t_blue);
    }
    void setDemoMode(uint8_t t_value){
      t_value = constrain(t_value, 0, 1);
      sendSettings(BMC_ME_CMD_TEST_MODE, t_value);
    }
    void setViewDot(){
      setView(BMC_ME_DOT);
    }
    void setVieBoostCut(){
      setView(BMC_ME_BOOST_CUT);
    }
    void setViewWrap(){
      setView(BMC_ME_WRAP);
    }
    void setViewSpread(){
      setView(BMC_ME_SPREAD);
    }
    void setViewTheater(){
      setView(BMC_ME_BPM);
    }

};
#endif
#endif
