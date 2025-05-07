/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
  
  This is a wrapper for the LiquidCrystal_PCF8574 Library
  https://github.com/mathertel/LiquidCrystal_PCF8574
*/

#ifndef BMC_LCD_H_
#define BMC_LCD_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_LCD > 0

#if !defined(BMC_LCD_ADDRESS)
  #error "LCD Address Missing"
#endif

#if BMC_LCD_CHARS == 16
  #define BMC_LCD_BLANK_LINE "                "
#elif BMC_LCD_CHARS == 20
  #define BMC_LCD_BLANK_LINE "                    "
#elif BMC_LCD_CHARS == 40
  #define BMC_LCD_BLANK_LINE "                                "
#endif


class BMC_LCD {
 public:
  BMC_PCF8574 display;
  BMC_LCD():display(BMC_LCD_ADDRESS){}
  
  bool begin(){
    display.begin(BMC_LCD_CHARS, BMC_MAX_LCD);
    display.home();
    display.setBacklight(255);
    display.clear();
    #if defined(BMC_LCD_BACKLIGHT_PIN)
      pinMode(BMC_LCD_BACKLIGHT_PIN, OUTPUT);
      analogWrite(BMC_LCD_BACKLIGHT_PIN, 128);
    #endif

    print(0, BMC_DEVICE_NAME);
    char version[16] = "";
    sprintf(version, "BMC v%s", BMC_VERSION_STR);
    print(BMC_MAX_LCD-1, version);
    return true;
  }
  void clear(){
    display.clear();
  }
  void setBacklight(uint16_t t_value){
    t_value = (uint8_t) constrain(t_value, 0, 255);
    #if defined(BMC_LCD_BACKLIGHT_PIN)
      analogWrite(BMC_LCD_BACKLIGHT_PIN, t_value);
    #endif
  }
  void print(uint8_t lineNumber, const char* str, bool centered=true){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(lineNumber, c, centered);
  }
  void print(uint8_t lineNumber, char* str, bool centered=true){
    if(centered){
      BMCTools::strTrimTail(str);
    }
    uint8_t len = strlen(str);
    uint8_t x   = 0;
    if(len < BMC_LCD_CHARS){
      x = (BMC_LCD_CHARS - len)/2;
    }
    if(len == 0){
      display.setCursor(0, lineNumber);
      char buff[BMC_LCD_CHARS+1] = BMC_LCD_BLANK_LINE;
      display.print(buff);
      return;
    }
    display.setCursor(0, lineNumber);
    if(!centered){
      display.print(str);
      return;
    }

    char buff[BMC_LCD_CHARS+1] = BMC_LCD_BLANK_LINE;
#if !defined(BMC_LCD_LEFT_JUSTIFY)
    // for(uint8_t i=0, e=0;i<BMC_LCD_CHARS;i++){
    //   if(i < x || i >= (x+len)){
    //     buff[i] = (char) ' ';
    //   } else if(i >= x){
    //     buff[i] = str[e++];
    //   }
    // }
    for(uint8_t i=x, e=0;i<BMC_LCD_CHARS;i++,e++){
      if(e >= len){
        break;
      }
      buff[i] = str[e];
    }
    buff[BMC_LCD_CHARS] = 0;
    display.print(buff);
#else
    strcpy(buff, str);
    buff[BMC_LCD_CHARS] = 0;
    display.print(str);
#endif
  }


  uint8_t getCenteredX(const char * str){
    uint8_t len = strlen(str);
    uint8_t x   = 0;
    if(len < BMC_LCD_CHARS){
      x = (BMC_LCD_CHARS - len)/2;
    }
    return x;
  }
  uint8_t getCenteredX(char * str){
    uint8_t len = strlen(str);
    uint8_t x   = 0;
    if(len < BMC_LCD_CHARS){
      x = (BMC_LCD_CHARS - len)/2;
    }
    return x;
  }
};

#endif

#endif
