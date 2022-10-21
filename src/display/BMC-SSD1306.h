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
#ifndef BMC_SSD1306_H_
#define BMC_SSD1306_H_

#if BMC_MAX_OLED > 0

#include <Wire.h>
//#include <Adafruit_GFX.h>
#include "display/BMC-GFX.h"

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
class BMC_SSD1306 : public BMCGFX {
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

  // center single line centered
  void printLine(uint8_t fontSize, int y, char * str, uint8_t strLen){
    // total number of pixels used by string with font size
    // remove the padding on the last character
    uint16_t totalWidthP = ((fontSize*6) * strLen)-fontSize;
    uint16_t totalHeightP = (fontSize*8)-fontSize;
    uint8_t x = 0;
    uint8_t yClear = y;

    // if "y" is -1  we center across the entire display horizontally and vertically

    if(y==-1){
      totalHeightP = HEIGHT;
      y = getCenteredY(fontSize);
      yClear = 0;
    }
    setTextSize(fontSize);

    if(totalWidthP <= WIDTH){

      x = (uint8_t) ((WIDTH-totalWidthP)/2);

      fillRect(0, yClear, 128, totalHeightP, BMC_SSD1306_BLACK);

      // draw a black box over the line we're using
      setCursor(x, y);
    } else {
      // line is longer than the screen so just print it
      setCursor(x, y);
    }

    println(str);
    display();
  }
  void printLine(uint8_t fontSize, int y, const char * str, uint8_t strLen){
    // total number of pixels used by string with font size
    char _str[strLen+1];
    strcpy(_str, str);
    printLine(fontSize, y, _str, strLen);
  }
  uint8_t getCenteredY(uint8_t fontSize){
    uint8_t totalHeightP = (fontSize*8)-fontSize;
    return (HEIGHT - totalHeightP)/2;
  }
  uint8_t getCenteredY(uint8_t fontSize, uint8_t startingAtY){
    uint8_t totalHeightP = (fontSize*8)-fontSize;
    return startingAtY+(((HEIGHT-startingAtY) - totalHeightP)/2);
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
