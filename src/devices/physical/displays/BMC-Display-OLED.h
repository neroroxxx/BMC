/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  This is a wrapper for the Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306
*/
#ifndef BMC_OLED_H_
#define BMC_OLED_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_OLED > 0

#if !defined(BMC_OLED_HEIGHT)
  #define BMC_OLED_HEIGHT 64
#endif

#if BMC_OLED_HEIGHT !=64 && BMC_OLED_HEIGHT !=32
  #undef BMC_OLED_HEIGHT
  #define BMC_OLED_HEIGHT 64
#endif

#define BMC_OLED_ICON_LENGTH 14

class BMC_OLED {
 public:
  const uint8_t wBound = 128;
  const uint8_t hBound = BMC_OLED_HEIGHT;
  uint8_t crc = 1;
  uint8_t settings = 0;
  int8_t selChar = -1;
  uint16_t meterPixelValue = 0xFFFF;
  uint16_t meterValue = 0xFFFF;
  BMC_SSD1306 display;
  BMC_OLED(uint8_t _w=128, uint8_t _h=BMC_OLED_HEIGHT):display(_w, _h){
    
  }
  bool begin(uint8_t n, uint8_t i2caddr, uint8_t rotation, uint8_t switchvcc=BMC_SSD1306_SWITCHCAPVCC){
    // switchvcc = 
    if(!display.begin(switchvcc, i2caddr)){
      // return false;
      BMC_PRINTLN("* display init failed");
      while(1);
    }
    display.setRotation(rotation);
    display.setTextWrap(false);
    #if BMC_OLED_HEIGHT == 32
       display.dim(true);
    #endif
    display.setTextSize(1);
    display.setTextColor(BMC_OLED_WHITE);
    display.setFont(BMC_FONT_LG);
    display.fillRect(0, 0, wBound, hBound, BMC_OLED_WHITE);

    display.printCenteredXY(n, 2, 2, wBound-4, hBound-4, 1, BMC_OLED_WHITE, BMC_OLED_BLACK);
    
    display.display();

    display.setFont(BMC_FONT_SM);
    display.fillRect(0, 0, wBound, hBound, BMC_OLED_BLACK);
    
    return true;
  }
  void setRotation(uint8_t r){
    display.setRotation(r);
  }
  int8_t getSelChar(){
    return selChar;
  }
  void setSelChar(uint8_t t_selChar){
    selChar = t_selChar;
  }
  void reassign(uint8_t t_settings){
    display.setTextSize(1);
    selChar = -1;
    meterPixelValue = 0xFFFF;
    meterValue = 0xFFFF;
    // crc = 1;
    settings = t_settings;
    if(bitRead(t_settings, 1)){
      display.drawRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
    }
    // clear(t_settings);
  }
  void blackout(){
    crc = 0;
    display.clearDisplay();
    display.display();
  }
  void clear(uint8_t t_settings){
    // settings
    // bit 0 label
    // bit 1 border
    // bit 2 selected
    // bit 3 use name instead of number
    // crc = 1;
    settings = t_settings;
    display.clearDisplay();
    if(bitRead(t_settings, 1)){
      display.drawRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
    }
    display.display();
  }
  void setCrc(uint8_t t_crc){
    crc = t_crc;
  }
  bool isCrc(uint8_t t_crc){
    return crc == t_crc;
  }
  uint16_t getX(){
    return 0;
  }
  uint16_t getY(){
    return 0;
  }
  uint16_t getWidth(){
    return wBound;
  }
  uint16_t getHeight(){
    return hBound;
  }
  uint16_t getBackground(){
    return BMC_OLED_BLACK;
  }
  uint16_t getColor(){
    return BMC_OLED_WHITE;
  }
  uint16_t getMeterPixelValue(){
    return meterPixelValue;
  }
  uint16_t getMeterValue(){
    return meterValue;
  }
  void setMeterPixelValue(uint16_t t_value){
    meterPixelValue = t_value;
  }
  void setMeterValue(uint16_t t_value){
    meterValue = t_value;
  }

  void printCenteredXY(int n, uint16_t t_x=0, uint16_t t_y=0, uint16_t t_w=0xFFFF, uint16_t t_h=0xFFFF, uint8_t t_padding=0, uint8_t t_color=BMC_OLED_WHITE){
    char str[16] = "";
    sprintf(str, "%d", n);
    printCenteredXY(str, t_x, t_y, t_w, t_h, t_padding, t_color);
  }
  // @str the string to print
  // @t_x the x position where the text will start
  // @t_y the y position where the text will start
  //      these custom fonts set the y position at the bottom of the text
  // @t_w the width of the area to print in
  // @t_h the height of the area to print in
  // @t_padding amount of space that will be removed from @t_h to keep
  //            the text from printing over that area.
  void printCenteredXY(const char * str, uint16_t t_x=0, uint16_t t_y=0, uint16_t t_w=0xFFFF, uint16_t t_h=0xFFFF, uint8_t t_padding=0, uint8_t t_color=BMC_OLED_WHITE){
    t_x = (t_x == 0xFFFF) ? 0 : t_x;
    t_y = (t_y == 0xFFFF) ? 0 : t_y;
    t_w = (t_w == 0xFFFF) ? wBound : t_w;
    t_h = (t_h == 0xFFFF) ? hBound : t_h;

    BMCTextPixelSize t;
    
    for(int i = 0 ; i < 4 ; i++){
      // only 3 font sizes are available
      if(i == 0){
        if(hBound < 64){
          continue;
        }
        display.setFont(BMC_FONT_XL);
      } else if(i == 1){
        display.setFont(BMC_FONT_LG);
      } else if(i == 2){
        display.setFont(BMC_FONT_MD);
      } else if(i == 3){
        display.setFont(BMC_FONT_SM);
      } else if(i == 4){
        display.setFont(BMC_FONT_XS);
      }
      t = display.strPixelSize(str, 0, 0);
      
      if((t.w) <= (t_w-t_padding) && ((t.h+(t_padding*2))+((t.y) + (t.h))) <= (t_h-t_padding)){
        break;
      }
    }
    t.x = t_x + (((t_w-t.x)-(t.w))/2);
    t.y = (t_y + ((t_h) - ((t_h-t.h)/2.0))) - (((t.y) + (t.h)));
    if(t.y >= (t_h+t_y)){
      t.y = t_y + (t_h-1);
    }
    display.fillRect(t_x, t_y, t_w, t_h, !t_color);
    display.setCursor(t.x, t.y);
    display.setTextColor(t_color);
    display.setTextWrap(false);
    display.print(str);
  }
  void getTextCenterXY(BMCTextPixelSize &t, const char * str, uint16_t t_x=0xFFFF, uint16_t t_y=0xFFFF, uint16_t t_w=0xFFFF, uint16_t t_h=0xFFFF){
    t_x = (t_x == 0xFFFF) ? 0 : t_x;
    t_y = (t_y == 0xFFFF) ? 0 : t_y;
    t_w = (t_w == 0xFFFF) ? wBound : t_w;
    t_h = (t_h == 0xFFFF) ? hBound : t_h;

    t = display.strPixelSize(str);

    t.x = (t_w-t.w)/2;
    t.y = t_h - ((t_h-t.h)/2);

    if(t.x < t_x){
      t.x = t_x;
    }
    if(t.y > t_h){
      t.y = t_h;
    }
  }
  void print(BMCDataContainer d, const char * str){
    strcpy(d.str, str);
    print(d, d.str);
  }
  void print(BMCDataContainer d, char * str){
    if(d.crc == crc){
      return;
    }
    crc = d.crc;
    display.clearDisplay();
    
    uint8_t len = strlen(str);
    if(len == 0){
      display.display();
      return;
    }

    uint8_t totalSpaces = 0;
    uint8_t breakPoint = 0;
    int8_t spaceIndex = -1;
    int8_t spaceIndex2 = -1;
    uint8_t lines = 1;

    // first limit the number of characters to print to 20 characters.
    len = (len > 20) ? 20 : len;

    // start by looking for spaces, use the spaces to split a long line in 2

    // figure out how many lines to print
    if(hBound==32){
      // on a 128x32 display we keep the maximum font size at 2
      // with that we can fit up to 10 characters in one line
      // if we have a single line and we are using the 128x32 display
      // then we won't bother to split the text into 2 lines using spaces
      lines = 1;
      if(len>10){
        BMCTools::strRemoveSpaces(str);
      }
    } else {
      // find out how many spaces the text has and record the first 2 spaces
      for(uint8_t i = 0 ; i < len ; i++){
        if(str[i]==' '){
          if(totalSpaces == 1){
            spaceIndex2 = i;
            totalSpaces = 2;
            break;
          } else {
            spaceIndex = i;
            totalSpaces = 1;
          }
        }
      }
      if(hBound == 32){
        if(totalSpaces == 2){
          uint8_t t1 = len - (spaceIndex+1); // 9
          uint8_t t2 = len - (spaceIndex2+1); // 4
          if(abs(spaceIndex - t1) < abs(spaceIndex2 - t2)){
            breakPoint = spaceIndex;
          } else {
            breakPoint = spaceIndex2;
          }
        } else if(totalSpaces == 1){
          // since we have only 1 space, we'll split the word at that space
          breakPoint = spaceIndex;
        } else if(totalSpaces == 0){
          // if this is a single long word then just split it down the middle
          breakPoint = len / 2;
        }
        spaceIndex = breakPoint;
        lines = 2;
      } else {
        if(spaceIndex >= 0 && len > 7){
          lines = 2;
        } else {
          if(len <= 10 && spaceIndex < 0){
            lines = 1;
          } else if(len > 7 && len <= 10 && spaceIndex >= 0){
            lines = 2;
          } else if(len > 10 && len <= 12){
            lines = 1;
          } else if(len > 12){
            lines = spaceIndex > 0 ? 2 : 3;
          }
        }
      }
    }
    if(lines==3){
      if(len>20){
        renderLine(str, 0, 2, 0, 10, d.highlight);
        renderLine(str, 1, 2, 10, len, d.highlight);
      } else {
        renderLine(str, 0, 2, 0, len/2, d.highlight);
        renderLine(str, 1, 2, len/2, len, d.highlight);
      }
    } else if(lines==2){
      renderLine(str, 0, 2, 0, spaceIndex, d.highlight);
      renderLine(str, 1, 2, (spaceIndex+1), len, d.highlight);
    } else {
      renderLine(str, 0, 1, 0, len, d.highlight);
    }
    if(bitRead(d.settings, 1)){
      display.drawRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
    }
    if(d.highlight){
      display.drawFastHLine(0, hBound, wBound, BMC_OLED_WHITE);
      display.drawFastHLine(0, hBound-1, wBound, BMC_OLED_WHITE);
    }
    display.display();
  }
 private:
  void renderLine(const char * str, uint8_t lineNumber, uint8_t totalLines, uint8_t start, uint8_t end, bool highlight=false){
    uint8_t len = end - start;
    // trim line
    for(uint8_t i = start, n=(end - start), e = 0 ; e < n ; i++, e++){
      if(str[i] == ' '){
        start++;
        len--;
      } else {
        break;
      }
    }
    len = constrain(len, 0, 10);
    char buff[strlen(str)+1] = "";
    for(uint8_t i = start, e = 0 ; e < len ; i++, e++){
      buff[e] = str[i];
      if(e >= len){
        break;
      }
    }
    uint16_t yPos = 0;
    uint16_t hPos = hBound;
    if(totalLines == 2){
      hPos = hBound/2;
      if(lineNumber == 1){
        yPos = hBound/2;
      }
    }
    display.printCenteredXY(buff, 0, yPos, wBound, hPos, 0, BMC_OLED_WHITE, BMC_OLED_BLACK);
  }
};

#endif

#endif
