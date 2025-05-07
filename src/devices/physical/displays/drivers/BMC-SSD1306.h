/*
  This is a modified version of the Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  It's modified for BMC and to only use I2C
  Class name and definitions were also changed form Adafruit_SSD1306 to BMC_SSD1306
  to prevent issues if you have the Adafruit_SSD1306 installed.
  Also adds some functions to center text which is the main reason
  I modified it and included it with BMC.
  Requires Adafruit GFX and Adafruit BusIO Libraries

  see https://github.com/adafruit/Adafruit_SSD1306/blob/master/license.txt
  for license information

  Software License Agreement (BSD License)

  Copyright (c) 2012, Adafruit Industries
  All rights reserved.
*/
#if !defined(BMC_SSD1306_H_)
#define BMC_SSD1306_H_

#include "utility/BMC-Def.h"

#if BMC_MAX_OLED > 0

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "devices/physical/displays/drivers/BMC-GFXFonts.h"
#include "devices/physical/displays/drivers/BMC-DisplayStruct.h"
// #include "devices/physical/displays/drivers/BMC-GFX.h"

/// fit into the BMC_SSD1306_ naming scheme
#ifndef BMC_SSD1306_BLACK
  #define BMC_SSD1306_BLACK               0    ///< Draw 'off' pixels
  #define BMC_SSD1306_WHITE               1    ///< Draw 'on' pixels
  #define BMC_SSD1306_INVERSE             2    ///< Invert pixels
#endif

#ifndef BMC_OLED_BLACK
  #define BMC_OLED_BLACK               0    ///< Draw 'off' pixels
  #define BMC_OLED_WHITE               1    ///< Draw 'on' pixels
  #define BMC_OLED_INVERSE             2    ///< Invert pixels
#endif

#define BMC_SSD1306_MEMORYMODE          0x20 ///< See datasheet
#define BMC_SSD1306_COLUMNADDR          0x21 ///< See datasheet
#define BMC_SSD1306_PAGEADDR            0x22 ///< See datasheet
#define BMC_SSD1306_SETCONTRAST         0x81 ///< See datasheet
#define BMC_SSD1306_CHARGEPUMP          0x8D ///< See datasheet
#define BMC_SSD1306_SEGREMAP            0xA0 ///< See datasheet
#define BMC_SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define BMC_SSD1306_DISPLAYALLON        0xA5 ///< Not currently used
#define BMC_SSD1306_NORMALDISPLAY       0xA6 ///< See datasheet
#define BMC_SSD1306_INVERTDISPLAY       0xA7 ///< See datasheet
#define BMC_SSD1306_SETMULTIPLEX        0xA8 ///< See datasheet
#define BMC_SSD1306_DISPLAYOFF          0xAE ///< See datasheet
#define BMC_SSD1306_DISPLAYON           0xAF ///< See datasheet
#define BMC_SSD1306_COMSCANINC          0xC0 ///< Not currently used
#define BMC_SSD1306_COMSCANDEC          0xC8 ///< See datasheet
#define BMC_SSD1306_SETDISPLAYOFFSET    0xD3 ///< See datasheet
#define BMC_SSD1306_SETDISPLAYCLOCKDIV  0xD5 ///< See datasheet
#define BMC_SSD1306_SETPRECHARGE        0xD9 ///< See datasheet
#define BMC_SSD1306_SETCOMPINS          0xDA ///< See datasheet
#define BMC_SSD1306_SETVCOMDETECT       0xDB ///< See datasheet

#define BMC_SSD1306_SETLOWCOLUMN        0x00 ///< Not currently used
#define BMC_SSD1306_SETHIGHCOLUMN       0x10 ///< Not currently used
#define BMC_SSD1306_SETSTARTLINE        0x40 ///< See datasheet

#define BMC_SSD1306_EXTERNALVCC         0x01 ///< External display voltage source
#define BMC_SSD1306_SWITCHCAPVCC        0x02 ///< Gen. display voltage from 3.3V

#define BMC_SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26 ///< Init rt scroll
#define BMC_SSD1306_LEFT_HORIZONTAL_SCROLL               0x27 ///< Init left scroll
#define BMC_SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define BMC_SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A ///< Init diag scroll
#define BMC_SSD1306_DEACTIVATE_SCROLL                    0x2E ///< Stop scroll
#define BMC_SSD1306_ACTIVATE_SCROLL                      0x2F ///< Start scroll
#define BMC_SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 ///< Set scroll range

/*!
    @brief  Class that stores state and functions for interacting with
            SSD1306 OLED displays.
*/
class BMC_SSD1306 : public Adafruit_GFX {
 public:
  BMC_SSD1306(uint8_t w, uint8_t h);

  ~BMC_SSD1306(void);

  boolean      begin(uint8_t switchvcc=BMC_SSD1306_SWITCHCAPVCC, uint8_t i2caddr=0);
  void         display(void);
  void         clearDisplay(void);
  void         invertDisplay(boolean i);
  void         dim(boolean dim);
  void         drawPixel(int16_t x, int16_t y, uint16_t color);
  virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void         startscrollright(uint8_t start, uint8_t stop);
  void         startscrollleft(uint8_t start, uint8_t stop);
  void         startscrolldiagright(uint8_t start, uint8_t stop);
  void         startscrolldiagleft(uint8_t start, uint8_t stop);
  void         stopscroll(void);
  void         ssd1306_command(uint8_t c);
  boolean      getPixel(int16_t x, int16_t y);
  uint8_t     *getBuffer(void);

  int16_t strPixelLen(const char * str){
    if(!str){
      return 0;
    }
    int16_t x1, y1;
		uint16_t w1, h1;
		getTextBounds(str, 0, 0, &x1, &y1, &w1, &h1);
    return w1;
  }
  BMCTextPixelSize strPixelSize(const char * str){
    BMCTextPixelSize t;
    if(!str){
      return t;
    }
		getTextBounds(str, 0, 0, &t.x, &t.y, &t.w, &t.h);
    return t;
  }

  BMCTextPixelSize strPixelSize(const char * str, uint16_t t_x, uint16_t t_y){
    BMCTextPixelSize t;
    if(!str){
      return t;
    }
		getTextBounds(str, t_x, t_y, &t.x, &t.y, &t.w, &t.h);
    return t;
  }
  void printCenteredXY(int n, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding, uint16_t t_color, uint16_t t_background){
    char str[16] = "";
    sprintf(str, "%d", n);
    printCenteredXY(str, t_x, t_y, t_w, t_h, t_padding, t_color, t_background);
  }
  // @str the string to print
  // @t_x the x position where the text will start
  // @t_y the y position where the text will start
  //      these custom fonts set the y position at the bottom of the text
  // @t_w the width of the area to print in
  // @t_h the height of the area to print in
  // @t_padding amount of space that will be removed from @t_h to keep
  //            the text from printing over that area.
  void printCenteredXY(const char * str, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding, uint16_t t_color, uint16_t t_background){
    BMCTextPixelSize t = getCenteredXY(str, t_x, t_y, t_w, t_h, t_padding);
    
    fillRect(t_x, t_y, t_w, t_h, t_background);
    setCursor(t.x, t.y);
    setTextColor(t_color);
    setTextWrap(false);
    print(str);
  }

  BMCTextPixelSize getCenteredXY(int n, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding){
    char str[16] = "";
    sprintf(str, "%d", n);
    return getCenteredXY(str, t_x, t_y, t_w, t_h, t_padding);
  }
  // @str the string to print
  // @t_x the x position where the text will start
  // @t_y the y position where the text will start
  //      these custom fonts set the y position at the bottom of the text
  // @t_w the width of the area to print in
  // @t_h the height of the area to print in
  // @t_padding amount of space that will be removed from @t_h to keep
  //            the text from printing over that area.
  BMCTextPixelSize getCenteredXY(const char * str, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding){
    char buff[strlen(str)+1];
    strcpy(buff, str);
    return getCenteredXY(buff,t_x,t_y,t_w,t_h,t_padding);
  }
  BMCTextPixelSize getCenteredXY(char * str, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding){
    setTextSize(1);
    BMCTextPixelSize t;
    for(int i = 0 ; i < 6 ; i++){
      // only 4 font sizes are available
      if(i == 0){
        if(t_h < 64){
          continue;
        }
        setFont(BMC_FONT_XXL);
      } else if(i == 1){
        setFont(BMC_FONT_XL);
      } else if(i == 2){
        setFont(BMC_FONT_LG);
      } else if(i == 3){
        setFont(BMC_FONT_MD);
      } else if(i == 4){
        setFont(BMC_FONT_SM);
      } else if(i == 5){
        setFont(BMC_FONT_XS);
      }
      t = strPixelSize(str, 0, 0);
      if((t.w) <= (t_w-t_padding) && ((t.h+(t_padding*2))+((t.y) + (t.h))) <= (t_h-t_padding)){
        // Serial.print("ILI ");
        // Serial.print(str);
        // Serial.print(" using font ");
        // Serial.println(i);
        break;
      }
    }
    t.x = t_x + (((t_w-t.x)-(t.w))/2);
    t.y = (t_y + ((t_h) - ((t_h-t.h)/2.0))) - (((t.y) + (t.h)));
    if(t.y >= (t_h+t_y)){
      t.y = t_y + (t_h-1);
    }
    return t;
  }

  BMCTextPixelSize getCurrentCenteredXY(int n, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding){
    char str[16] = "";
    sprintf(str, "%d", n);
    return getCurrentCenteredXY(str, t_x, t_y, t_w, t_h, t_padding);
  }
  // @str the string to print
  // @t_x the x position where the text will start
  // @t_y the y position where the text will start
  //      these custom fonts set the y position at the bottom of the text
  // @t_w the width of the area to print in
  // @t_h the height of the area to print in
  // @t_padding amount of space that will be removed from @t_h to keep
  //            the text from printing over that area.
  BMCTextPixelSize getCurrentCenteredXY(const char * str, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding){
    setTextSize(1);
    BMCTextPixelSize t = strPixelSize(str, 0, 0);
    t.x = t_x + (((t_w-t.x)-(t.w))/2);
    t.y = (t_y + ((t_h) - ((t_h-t.h)/2.0))) - (((t.y) + (t.h)));
    if(t.y >= (t_h+t_y)){
      t.y = t_y + (t_h-1);
    }
    return t;
  }


 private:
  void         drawFastHLineInternal(int16_t x, int16_t y, int16_t w,
                 uint16_t color);
  void         drawFastVLineInternal(int16_t x, int16_t y, int16_t h,
                 uint16_t color);
  void         ssd1306_command1(uint8_t c);
  void         ssd1306_commandList(const uint8_t *c, uint8_t n);

  uint8_t     *buffer;
  int8_t       i2caddr, vccstate, page_end;
};

#endif

#endif // BMC_SSD1306_H_
