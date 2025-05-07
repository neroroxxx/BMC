/***************************************************
  STM32 Support added by Jaret Burkett at OSHlab.com

  This is our library for the Adafruit  ILI9488 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "utility/BMC-Def.h"

#if !defined(BMC_ILI9488_H) && defined(BMC_FOR_TEENSY)
#define BMC_ILI9488_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif
#include "Adafruit_GFX.h"
#include <Arduino.h>
#include <Print.h>
#include "Adafruit_SPITFT.h"
#include <SPI.h>


#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif

// #include "utility/BMC-Tools.h"
#include "devices/physical/displays/drivers/BMC-GFXFonts.h"
#include "devices/physical/displays/drivers/BMC-DisplayStruct.h"

#ifdef ARDUINO_STM32_FEATHER
typedef volatile uint32 RwReg;
#endif
#if defined (__AVR__) || defined(TEENSYDUINO) || defined (__arm__) || defined (__STM32F1__)
#define USE_FAST_PINIO
#endif

#define ILI9488_TFTWIDTH  320
#define ILI9488_TFTHEIGHT 480

#define ILI9488_NOP     0x00
#define ILI9488_SWRESET 0x01
#define ILI9488_RDDID   0x04
#define ILI9488_RDDST   0x09

#define ILI9488_SLPIN   0x10
#define ILI9488_SLPOUT  0x11
#define ILI9488_PTLON   0x12
#define ILI9488_NORON   0x13

#define ILI9488_RDMODE  0x0A
#define ILI9488_RDMADCTL  0x0B
#define ILI9488_RDPIXFMT  0x0C
#define ILI9488_RDIMGFMT  0x0D
#define ILI9488_RDSELFDIAG  0x0F

#define ILI9488_INVOFF  0x20
#define ILI9488_INVON   0x21
#define ILI9488_GAMMASET 0x26
#define ILI9488_DISPOFF 0x28
#define ILI9488_DISPON  0x29

#define ILI9488_CASET   0x2A
#define ILI9488_PASET   0x2B
#define ILI9488_RAMWR   0x2C
#define ILI9488_RAMRD   0x2E

#define ILI9488_PTLAR   0x30
#define ILI9488_MADCTL  0x36
#define ILI9488_PIXFMT  0x3A

#define ILI9488_FRMCTR1 0xB1
#define ILI9488_FRMCTR2 0xB2
#define ILI9488_FRMCTR3 0xB3
#define ILI9488_INVCTR  0xB4
#define ILI9488_DFUNCTR 0xB6

#define ILI9488_PWCTR1  0xC0
#define ILI9488_PWCTR2  0xC1
#define ILI9488_PWCTR3  0xC2
#define ILI9488_PWCTR4  0xC3
#define ILI9488_PWCTR5  0xC4
#define ILI9488_VMCTR1  0xC5
#define ILI9488_VMCTR2  0xC7

#define ILI9488_RDID1   0xDA
#define ILI9488_RDID2   0xDB
#define ILI9488_RDID3   0xDC
#define ILI9488_RDID4   0xDD

#define ILI9488_GMCTRP1 0xE0
#define ILI9488_GMCTRN1 0xE1
/*
#define ILI9488_PWCTR6  0xFC

*/

// Color definitions
// #define ILI9488_BLACK       0x0000      /*   0,   0,   0 */
// #define ILI9488_NAVY        0x000F      /*   0,   0, 128 */
// #define ILI9488_DARKGREEN   0x03E0      /*   0, 128,   0 */
// #define ILI9488_DARKCYAN    0x03EF      /*   0, 128, 128 */
// #define ILI9488_MAROON      0x7800      /* 128,   0,   0 */
// #define ILI9488_PURPLE      0x780F      /* 128,   0, 128 */
// #define ILI9488_OLIVE       0x7BE0      /* 128, 128,   0 */
// #define ILI9488_LIGHTGREY   0xC618      /* 192, 192, 192 */
// #define ILI9488_DARKGREY    0x7BEF      /* 128, 128, 128 */
// #define ILI9488_BLUE        0x001F      /*   0,   0, 255 */
// #define ILI9488_GREEN       0x07E0      /*   0, 255,   0 */
// #define ILI9488_CYAN        0x07FF      /*   0, 255, 255 */
// #define ILI9488_RED         0xF800      /* 255,   0,   0 */
// #define ILI9488_MAGENTA     0xF81F      /* 255,   0, 255 */
// #define ILI9488_YELLOW      0xFFE0      /* 255, 255,   0 */
// #define ILI9488_WHITE       0xFFFF      /* 255, 255, 255 */
// #define ILI9488_ORANGE      0xFD20      /* 255, 165,   0 */
// #define ILI9488_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
// #define ILI9488_PINK        0xF81F

class BMC_ILI9488 : public Adafruit_GFX {

 public:

  // BMC_ILI9488(int8_t _CS, int8_t _DC, int8_t _MOSI, int8_t _SCLK,
	// 	   int8_t _RST, int8_t _MISO);
  BMC_ILI9488(int8_t _CS, int8_t _DC, int8_t _RST = -1);

  void     begin(void),
           setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1),
           setScrollArea(uint16_t topFixedArea, uint16_t bottomFixedArea),
           scroll(uint16_t pixels),
           pushColor(uint16_t color),
           pushColors(uint16_t *data, uint8_t len, boolean first),
           drawImage(const uint8_t* img, uint16_t x, uint16_t y, uint16_t w, uint16_t h),
           fillScreen(uint16_t color),
           drawPixel(int16_t x, int16_t y, uint16_t color),
           drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
           drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
           fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
             uint16_t color),
           setRotation(uint8_t r),
           invertDisplay(boolean i);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

  /* These are not for current use, 8-bit protocol only! */
  uint8_t  readdata(void),
    readcommand8(uint8_t reg, uint8_t index = 0);
  /*
  uint16_t readcommand16(uint8_t);
  uint32_t readcommand32(uint8_t);
  void     dummyclock(void);
  */

  void     spiwrite(uint8_t),
    writecommand(uint8_t c),
    write16BitColor(uint16_t color),
    writedata(uint8_t d),
    commandList(uint8_t *addr);
  uint8_t  spiread(void);

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

 private:
  uint8_t  tabcolor;
  boolean  hwSPI;


  

#if defined (__IMXRT1062__)
  uint32_t mySPCR;
  volatile uint32_t *mosiport, *clkport, *dcport, *rsport, *csport;
  int32_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
  uint32_t  mosipinmask, clkpinmask, cspinmask, dcpinmask;
#elif defined (__AVR__) || defined(TEENSYDUINO)
  uint8_t mySPCR;
  volatile uint8_t *mosiport, *clkport, *dcport, *rsport, *csport;
  int8_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
  uint8_t  mosipinmask, clkpinmask, cspinmask, dcpinmask;
////This def is for the Arduino.ORG M0!!!
//#elif defined(ARDUINO_SAM_ZERO)
//    volatile PORT_OUT_Type *mosiport, *clkport, *dcport, *rsport, *csport;
//    int32_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
//    PORT_OUT_Type  mosipinmask, clkpinmask, cspinmask, dcpinmask;
#elif defined (__STM32F1__) || defined (_VARIANT_ARDUINO_STM32_) || defined (STM32F100xE) || defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
    uint8_t mySPCR;
    volatile uint32_t *mosiport, *clkport, *dcport, *rsport, *csport;
    int32_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
    uint32_t  mosipinmask, clkpinmask, cspinmask, dcpinmask;
#elif defined (__arm__)
    volatile RwReg *mosiport, *clkport, *dcport, *rsport, *csport;
    int32_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
    uint32_t  mosipinmask, clkpinmask, cspinmask, dcpinmask;
#elif defined (ESP8266)
    int32_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
#else
    int8_t  _cs, _dc, _rst, _mosi, _miso, _sclk;
#endif
};

#endif
