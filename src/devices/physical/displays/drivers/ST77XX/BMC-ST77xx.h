/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#ifndef _BMC_ST77XXH_
#define _BMC_ST77XXH_

// #include "utility/BMC-Def.h"

// #if BMC_MAX_MINI_DISPLAY > 0

#include "Arduino.h"
#include "Print.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>


#include "devices/physical/displays/drivers/BMC-ILI9341_fonts.h"
#include "devices/physical/displays/drivers/BMC-GFXFonts.h"
#include "devices/physical/displays/drivers/BMC-DisplayStruct.h"

#define ST7735_TFTWIDTH_128 128  // for 1.44 and mini
#define ST7735_TFTWIDTH_80 80    // for mini
#define ST7735_TFTHEIGHT_128 128 // for 1.44" display
#define ST7735_TFTHEIGHT_160 160 // for 1.8" and mini display

#define ST_CMD_DELAY 0x80 // special signifier for command lists

#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13

#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E

#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00

#define ST77XX_RDID1 0xDA
#define ST77XX_RDID2 0xDB
#define ST77XX_RDID3 0xDC
#define ST77XX_RDID4 0xDD

// Some ready-made 16-bit ('565') color settings:
#define ST77XX_BLACK 0x0000
#define ST77XX_WHITE 0xFFFF
#define ST77XX_RED 0xF800
#define ST77XX_GREEN 0x07E0
#define ST77XX_BLUE 0x001F
#define ST77XX_CYAN 0x07FF
#define ST77XX_MAGENTA 0xF81F
#define ST77XX_YELLOW 0xFFE0
#define ST77XX_ORANGE 0xFC00

/// Subclass of SPITFT for ST77xx displays (lots in common!)
class BMC_ST77xx : public Adafruit_SPITFT {
public:
  BMC_ST77xx(uint16_t w, uint16_t h, int8_t _CS, int8_t _DC, int8_t _MOSI,
                  int8_t _SCLK, int8_t _RST = -1, int8_t _MISO = -1);
  BMC_ST77xx(uint16_t w, uint16_t h, int8_t CS, int8_t RS,
                  int8_t RST = -1);
#if !defined(ESP8266)
  BMC_ST77xx(uint16_t w, uint16_t h, SPIClass *spiClass, int8_t CS,
                  int8_t RS, int8_t RST = -1);
#endif // end !ESP8266
  
  
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
    char buff[strlen(str)+1] = "";
    strcpy(buff, str);
    printCenteredXY(buff, t_x, t_y, t_w, t_h, t_padding, t_color, t_background);
  }
  void printCenteredXY(char * str, uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h, uint8_t t_padding, uint16_t t_color, uint16_t t_background){
    BMCTextPixelSize t = getCenteredXY(str, t_x, t_y, t_w, t_h, t_padding);
    if(t.w > t_w){
      strShorten(str, true);
      uint8_t len = strlen(str)-1;
      while(strPixelLen(str)>t_w){
        str[len--] = 0;
      }
      t.x = t_x;
    }
    
    fillRect(t_x, t_y, t_w, t_h, t_background);
    setCursor(t.x, t.y);
    setTextColor(t_color);
    setTextWrap(false);
    print(str);
  }
  void strShorten(char * str, bool removeSpaces=false){
    // removes all vowels as well
    // if the first character of the string is a vowel leave it
    // removes all spaces from string if @removeSpaces is true
    uint16_t len = strlen(str);
    if(len < 5){
      return;
    }
    char buff[len+1] = "";
    for(uint8_t i = 1, e = 0 ; i < len ; i++){
      if((removeSpaces && str[i] == 32) || (str[i] == 65 || str[i] == 69 || str[i] == 73 ||
         str[i] == 79 || str[i] == 85 || str[i] == 97 || str[i] == 101 ||
         str[i] == 105 || str[i] == 111 || str[i] == 117)
      ){
        continue;
      } else if(str[i] == 0){
        break;
      }
      buff[e++] = str[i];
    }
    if(strlen(buff)>0){
      strcpy(str, buff);
    }
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

  void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void setRotation(uint8_t r);
  void enableDisplay(boolean enable);
  void enableTearing(boolean enable);
  void enableSleep(boolean enable);

protected:
  uint8_t _colstart = 0,   ///< Some displays need this changed to offset
      _rowstart = 0,       ///< Some displays need this changed to offset
      spiMode = SPI_MODE0; ///< Certain display needs MODE3 instead

  void begin(uint32_t freq = 0);
  void commonInit(const uint8_t *cmdList);
  void displayInit(const uint8_t *addr);
  void setColRowStart(int8_t col, int8_t row);
};

#endif // _BMC_ST77XXH_

// #endif
