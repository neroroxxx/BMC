/*!
 * @file BMC_ILI9341.h
 *
 * This is the documentation for Adafruit's ILI9341 driver for the
 * Arduino platform.
 *
 * This library works with the Adafruit 2.8" Touch Shield V2 (SPI)
 *    http://www.adafruit.com/products/1651
 * Adafruit 2.4" TFT LCD with Touchscreen Breakout w/MicroSD Socket - ILI9341
 *    https://www.adafruit.com/product/2478
 * 2.8" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket - ILI9341
 *    https://www.adafruit.com/product/1770
 * 2.2" 18-bit color TFT LCD display with microSD card breakout - ILI9340
 *    https://www.adafruit.com/product/1770
 * TFT FeatherWing - 2.4" 320x240 Touchscreen For All Feathers
 *    https://www.adafruit.com/product/3315
 *
 * These displays use SPI to communicate, 4 or 5 pins are required
 * to interface (RST is optional).
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 *
 * This library depends on <a href="https://github.com/adafruit/Adafruit_GFX">
 * Adafruit_GFX</a> being present on your system. Please make sure you have
 * installed the latest version before using this library.
 *
 * Written by Limor "ladyada" Fried for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef BMC_ILI9341_H
#define BMC_ILI9341_H

#include "Adafruit_GFX.h"
#include "Arduino.h"
#include "Print.h"
#include <Adafruit_SPITFT.h>
#include <SPI.h>
// #include "utility/BMC-Tools.h"
#include "display/drivers/BMC-GFXFonts.h"
#include "display/drivers/BMC-DisplayStruct.h"

#define ILI9341_TFTWIDTH 240  ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 320 ///< ILI9341 max TFT height

#define ILI9341_NOP 0x00     ///< No-op register
#define ILI9341_SWRESET 0x01 ///< Software reset register
#define ILI9341_RDDID 0x04   ///< Read display identification information
#define ILI9341_RDDST 0x09   ///< Read Display Status

#define ILI9341_SLPIN 0x10  ///< Enter Sleep Mode
#define ILI9341_SLPOUT 0x11 ///< Sleep Out
#define ILI9341_PTLON 0x12  ///< Partial Mode ON
#define ILI9341_NORON 0x13  ///< Normal Display Mode ON

#define ILI9341_RDMODE 0x0A     ///< Read Display Power Mode
#define ILI9341_RDMADCTL 0x0B   ///< Read Display MADCTL
#define ILI9341_RDPIXFMT 0x0C   ///< Read Display Pixel Format
#define ILI9341_RDIMGFMT 0x0D   ///< Read Display Image Format
#define ILI9341_RDSELFDIAG 0x0F ///< Read Display Self-Diagnostic Result

#define ILI9341_INVOFF 0x20   ///< Display Inversion OFF
#define ILI9341_INVON 0x21    ///< Display Inversion ON
#define ILI9341_GAMMASET 0x26 ///< Gamma Set
#define ILI9341_DISPOFF 0x28  ///< Display OFF
#define ILI9341_DISPON 0x29   ///< Display ON

#define ILI9341_CASET 0x2A ///< Column Address Set
#define ILI9341_PASET 0x2B ///< Page Address Set
#define ILI9341_RAMWR 0x2C ///< Memory Write
#define ILI9341_RAMRD 0x2E ///< Memory Read

#define ILI9341_PTLAR 0x30    ///< Partial Area
#define ILI9341_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define ILI9341_MADCTL 0x36   ///< Memory Access Control
#define ILI9341_VSCRSADD 0x37 ///< Vertical Scrolling Start Address
#define ILI9341_PIXFMT 0x3A   ///< COLMOD: Pixel Format Set

#define ILI9341_FRMCTR1                                                        \
  0xB1 ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRMCTR2 0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3                                                        \
  0xB3 ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVCTR 0xB4  ///< Display Inversion Control
#define ILI9341_DFUNCTR 0xB6 ///< Display Function Control

#define ILI9341_PWCTR1 0xC0 ///< Power Control 1
#define ILI9341_PWCTR2 0xC1 ///< Power Control 2
#define ILI9341_PWCTR3 0xC2 ///< Power Control 3
#define ILI9341_PWCTR4 0xC3 ///< Power Control 4
#define ILI9341_PWCTR5 0xC4 ///< Power Control 5
#define ILI9341_VMCTR1 0xC5 ///< VCOM Control 1
#define ILI9341_VMCTR2 0xC7 ///< VCOM Control 2

#define ILI9341_RDID1 0xDA ///< Read ID 1
#define ILI9341_RDID2 0xDB ///< Read ID 2
#define ILI9341_RDID3 0xDC ///< Read ID 3
#define ILI9341_RDID4 0xDD ///< Read ID 4

#define ILI9341_GMCTRP1 0xE0 ///< Positive Gamma Correction
#define ILI9341_GMCTRN1 0xE1 ///< Negative Gamma Correction
//#define ILI9341_PWCTR6     0xFC

// Color definitions
// #define ILI9341_BLACK 0x0000       ///<   0,   0,   0
// #define ILI9341_NAVY 0x000F        ///<   0,   0, 123
// #define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
// #define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
// #define ILI9341_MAROON 0x7800      ///< 123,   0,   0
// #define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
// #define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
// #define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
// #define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
// #define ILI9341_BLUE 0x001F        ///<   0,   0, 255
// #define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
// #define ILI9341_CYAN 0x07FF        ///<   0, 255, 255
// #define ILI9341_RED 0xF800         ///< 255,   0,   0
// #define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
// #define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
// #define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
// #define ILI9341_ORANGE 0xFD20      ///< 255, 165,   0
// #define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
// #define ILI9341_PINK 0xFC18        ///< 255, 130, 198

/**************************************************************************/
/*!
@brief Class to manage hardware interface with ILI9341 chipset (also seems to
work with ILI9340)
*/
/**************************************************************************/

class BMC_ILI9341 : public Adafruit_SPITFT {
public:
  BMC_ILI9341(int8_t _CS, int8_t _DC, int8_t _MOSI, int8_t _SCLK,
                   int8_t _RST = -1, int8_t _MISO = -1);
  BMC_ILI9341(int8_t _CS, int8_t _DC, int8_t _RST = -1);
#if !defined(ESP8266)
  BMC_ILI9341(SPIClass *spiClass, int8_t dc, int8_t cs = -1,
                   int8_t rst = -1);
#endif // end !ESP8266
  BMC_ILI9341(tftBusWidth busWidth, int8_t d0, int8_t wr, int8_t dc,
                   int8_t cs = -1, int8_t rst = -1, int8_t rd = -1);

  void begin(uint32_t freq = 0);
  void setRotation(uint8_t r);
  void invertDisplay(bool i);
  void scrollTo(uint16_t y);
  void setScrollMargins(uint16_t top, uint16_t bottom);

  // Transaction API not used by GFX
  void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

  uint8_t readcommand8(uint8_t reg, uint8_t index = 0);


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
};

#endif // BMC_ILI9341_H
