// https://github.com/PaulStoffregen/BMC_ILI9488_t3
// http://forum.pjrc.com/threads/26305-Highly-optimized-ILI9488-(320x240-TFT-color-display)-library

/***************************************************
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

// <SoftEgg>

//Additional graphics routines by Tim Trzepacz, SoftEgg LLC added December 2015
//(And then accidentally deleted and rewritten March 2016. Oops!)
//Gradient support
//----------------
//		fillRectVGradient	- fills area with vertical gradient
//		fillRectHGradient	- fills area with horizontal gradient
//		fillScreenVGradient - fills screen with vertical gradient
// 	fillScreenHGradient - fills screen with horizontal gradient

//Additional Color Support
//------------------------
//		color565toRGB		- converts 565 format 16 bit color to RGB
//		color565toRGB14		- converts 16 bit 565 format color to 14 bit RGB (2 bits clear for math and sign)
//		RGB14tocolor565		- converts 14 bit RGB back to 16 bit 565 format color

//Low Memory Bitmap Support
//-------------------------
// writeRect8BPP - 	write 8 bit per pixel paletted bitmap
// writeRect4BPP - 	write 4 bit per pixel paletted bitmap
// writeRect2BPP - 	write 2 bit per pixel paletted bitmap
// writeRect1BPP - 	write 1 bit per pixel paletted bitmap

//String Pixel Length support
//---------------------------
//		strPixelLen			- gets pixel length of given ASCII string

// <\SoftEgg>

#include "utility/BMC-Def.h"

#if !defined(_BMC_ILI9488_t3H_) && defined(BMC_FOR_TEENSY) && BMC_MAX_ILI9341_BLOCKS > 0
  #define _BMC_ILI9488_t3H_
  #if defined __has_include

    #if __has_include(<ILI9488_sketch_options.h>)
      #  include <ILI9488_sketch_options.h>
      //#pragma message "BMC_ILI9488_t3h - included ILI9488_sketch_options.h"
    #endif
  #endif

  #ifdef __cplusplus
    #include "Arduino.h"
    #include <DMAChannel.h>
  #endif

  #include <stdint.h>

  #if defined(__AVR__)
    #error "Sorry, BMC_ILI9488_t3 does not work with Teensy 2.0 or Teensy++ 2.0.  Use Adafruit_ILI9488."
  #endif

  #define  ILI9488_USE_DMAMEM

  // Allow us to enable or disable capabilities, particully Frame Buffer and Clipping for speed and size
  #ifndef DISABLE_ILI9488_FRAMEBUFFER
  #if defined(__MK64FX512__) || defined(__MK66FX1M0__)
  #define ENABLE_ILI9488_FRAMEBUFFER
  #define ILI9488_USES_PALLET
  typedef uint8_t RAFB;
  #elif defined(__IMXRT1052__) || defined(__IMXRT1062__)
  #define ENABLE_ILI9488_FRAMEBUFFER
  // define ILI9488_USES_PALLET if you wish to force T4 to use 8 bit buffer instead of 16 bit
  //#define ILI9488_USES_PALLET
  //#define ENABLE_EXT_DMA_UPDATES  // This is only valid for those T4.1 which have external memory. 

  #ifndef ARDUINO_TEENSY41
  #undef ENABLE_EXT_DMA_UPDATES
  #endif
  #ifdef ILI9488_USES_PALLET
  typedef uint8_t RAFB;
  #elif defined(ENABLE_EXT_DMA_UPDATES)
  typedef uint32_t RAFB;
  #else
  typedef uint16_t RAFB;
  #endif
  #else 
  // won't be used on processors like T3.2 but allow api exist and not compile error
  typedef uint8_t RAFB;
  #endif
  #endif

  #include "display/drivers/BMC-ILI9341_fonts.h"

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

  #define ILI9488_CASET   0x2A   //Column Address Set 
  #define ILI9488_PASET   0x2B   //Page Address Set 
  #define ILI9488_RAMWR   0x2C   //Memory Write 
  #define ILI9488_RAMRD   0x2E   //Memory Read

  #define ILI9488_PTLAR    0x30
  #define ILI9488_MADCTL   0x36
  #define ILI9488_VSCRSADD 0x37
  #define ILI9488_PIXFMT   0x3A

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

  // define aliases for commonly used commands. 
  #define SET_COLUMN_ADDRESS_WINDOW  0x2A
  #define SET_ROW_ADDRESS_WINDOW     0x2B
  #define BEGIN_PIXEL_DATA           0x2C
  #define BEGIN_READ_DATA            0x2E
  #define READ_MEMORY_CONTINUE       0x3E
  /*
  #define ILI9488_PWCTR6  0xFC

  */

  // Color definitions
  #define ILI9488_BLACK       0x0000      /*   0,   0,   0 */
  #define ILI9488_NAVY        0x000F      /*   0,   0, 128 */
  #define ILI9488_DARKGREEN   0x03E0      /*   0, 128,   0 */
  #define ILI9488_DARKCYAN    0x03EF      /*   0, 128, 128 */
  #define ILI9488_MAROON      0x7800      /* 128,   0,   0 */
  #define ILI9488_PURPLE      0x780F      /* 128,   0, 128 */
  #define ILI9488_OLIVE       0x7BE0      /* 128, 128,   0 */
  #define ILI9488_LIGHTGREY   0xC618      /* 192, 192, 192 */
  #define ILI9488_DARKGREY    0x7BEF      /* 128, 128, 128 */
  #define ILI9488_BLUE        0x001F      /*   0,   0, 255 */
  #define ILI9488_GREEN       0x07E0      /*   0, 255,   0 */
  #define ILI9488_CYAN        0x07FF      /*   0, 255, 255 */
  #define ILI9488_RED         0xF800      /* 255,   0,   0 */
  #define ILI9488_MAGENTA     0xF81F      /* 255,   0, 255 */
  #define ILI9488_YELLOW      0xFFE0      /* 255, 255,   0 */
  #define ILI9488_WHITE       0xFFFF      /* 255, 255, 255 */
  #define ILI9488_ORANGE      0xFD20      /* 255, 165,   0 */
  #define ILI9488_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
  #define ILI9488_PINK        0xF81F

  #ifndef CL
  #define CL(_r,_g,_b) ((((_r)&0xF8)<<8)|(((_g)&0xFC)<<3)|((_b)>>3))
  #endif
  #define sint16_t int16_t

  // Map fonts that were modified back to the ILI9341 font
  #define BMC_ILI9488_t3_font_t BMC_ILI9341_t3_font_t

  // Lets see about supporting Adafruit fonts as well?
  #if __has_include(<gfxfont.h>)
    #include <gfxfont.h>
  #endif

  // Lets see about supporting Adafruit fonts as well?
  #ifndef _GFXFONT_H_
  #define _GFXFONT_H_

  /// Font data stored PER GLYPH
  typedef struct {
    uint16_t bitmapOffset;     ///< Pointer into GFXfont->bitmap
    uint8_t  width;            ///< Bitmap dimensions in pixels
      uint8_t  height;           ///< Bitmap dimensions in pixels
    uint8_t  xAdvance;         ///< Distance to advance cursor (x axis)
    int8_t   xOffset;          ///< X dist from cursor pos to UL corner
      int8_t   yOffset;          ///< Y dist from cursor pos to UL corner
  } GFXglyph;

  /// Data stored for FONT AS A WHOLE
  typedef struct { 
    uint8_t  *bitmap;      ///< Glyph bitmaps, concatenated
    GFXglyph *glyph;       ///< Glyph array
    uint8_t   first;       ///< ASCII extents (first char)
      uint8_t   last;        ///< ASCII extents (last char)
    uint8_t   yAdvance;    ///< Newline distance (y axis)
  } GFXfont;

  #endif // _GFXFONT_H_

  #define ILI9488_DMA_INIT	0x01 	// We have init the Dma settings
  #define ILI9488_DMA_CONT	0x02 	// continuous mode
  #define ILI9488_DMA_ACTIVE  0x80    // Is currently active

  //These enumerate the text plotting alignment (reference datum point)
  #define TL_DATUM 0 // Top left (default)
  #define TC_DATUM 1 // Top centre
  #define TR_DATUM 2 // Top right
  #define ML_DATUM 3 // Middle left
  #define CL_DATUM 3 // Centre left, same as above
  #define MC_DATUM 4 // Middle centre
  #define CC_DATUM 4 // Centre centre, same as above
  #define MR_DATUM 5 // Middle right
  #define CR_DATUM 5 // Centre right, same as above
  #define BL_DATUM 6 // Bottom left
  #define BC_DATUM 7 // Bottom centre
  #define BR_DATUM 8 // Bottom right
  //#define L_BASELINE  9 // Left character baseline (Line the 'A' character would sit on)
  //#define C_BASELINE 10 // Centre character baseline
  //#define R_BASELINE 11 // Right character baseline

  #ifdef __cplusplus
  // At all other speeds, ILI9241_KINETISK__pspi->beginTransaction() will use the fastest available clock
  #include <SPI.h>

  #if defined(__MK64FX512__) || defined(__MK66FX1M0__)
  #if F_BUS >= 64000000
  #define ILI9488_SPICLOCK 64000000
  #define ILI9488_SPICLOCK_READ 4000000
  #else
  #define ILI9488_SPICLOCK 30000000
  #define ILI9488_SPICLOCK_READ 2000000
  #endif
  #elif defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
  #define ILI9488_SPICLOCK 30000000
  //#define ILI9488_SPICLOCK 72000000
  #define ILI9488_SPICLOCK_READ 4000000
  #else
  #define ILI9488_SPICLOCK 30000000
  #define ILI9488_SPICLOCK_READ 2000000
  #endif

  class BMC_ILI9488_t3 : public Print
  {
    public:
    BMC_ILI9488_t3(SPIClass *SPIWire, uint8_t _CS, uint8_t _DC, uint8_t _RST = 255, uint8_t _MOSI=255, uint8_t _SCLK=255, uint8_t _MISO=255); 
    BMC_ILI9488_t3(uint8_t _CS, uint8_t _DC, uint8_t _RST = 255, uint8_t _MOSI=255, uint8_t _SCLK=255, uint8_t _MISO=255);
    void begin(uint32_t clock = ILI9488_SPICLOCK);
      void sleep(bool enable);		
    void pushColor(uint16_t color);
    void fillScreen(uint16_t color);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        
    void fillRectHGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2);
    void fillRectVGradient(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1, uint16_t color2);
    void fillScreenVGradient(uint16_t color1, uint16_t color2);
    void fillScreenHGradient(uint16_t color1, uint16_t color2);

    void setRotation(uint8_t r);
    void setScroll(uint16_t offset);
    void invertDisplay(boolean i);
    void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    // Pass 8-bit (each) R,G,B, get back 16-bit packed color
    static uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
      return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

    //color565toRGB		- converts 565 format 16 bit color to RGB
    static void color565toRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
      r = (color>>8)&0x00F8;
      g = (color>>3)&0x00FC;
      b = (color<<3)&0x00F8;
    }
    
    //color565toRGB14		- converts 16 bit 565 format color to 14 bit RGB (2 bits clear for math and sign)
    //returns 00rrrrr000000000,00gggggg00000000,00bbbbb000000000
    //thus not overloading sign, and allowing up to double for additions for fixed point delta
    static void color565toRGB14(uint16_t color, int16_t &r, int16_t &g, int16_t &b) {
      r = (color>>2)&0x3E00;
      g = (color<<3)&0x3F00;
      b = (color<<9)&0x3E00;
    }
    
    //RGB14tocolor565		- converts 14 bit RGB back to 16 bit 565 format color
    static uint16_t RGB14tocolor565(int16_t r, int16_t g, int16_t b)
    {
      return (((r & 0x3E00) << 2) | ((g & 0x3F00) >>3) | ((b & 0x3E00) >> 9));
    }
    
    //uint8_t readdata(void);
    uint8_t readcommand8(uint8_t reg, uint8_t index = 0);

    // Added functions to read pixel data...
    uint16_t readPixel(int16_t x, int16_t y);
    void readRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors);
    void writeRect(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *pcolors);

    // writeRect8BPP - 	write 8 bit per pixel paletted bitmap
    //					bitmap data in array at pixels, one byte per pixel
    //					color palette data in array at palette
    void writeRect8BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette );

    // writeRect4BPP - 	write 4 bit per pixel paletted bitmap
    //					bitmap data in array at pixels, 4 bits per pixel
    //					color palette data in array at palette
    //					width must be at least 2 pixels
    void writeRect4BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette );
    
    // writeRect2BPP - 	write 2 bit per pixel paletted bitmap
    //					bitmap data in array at pixels, 4 bits per pixel
    //					color palette data in array at palette
    //					width must be at least 4 pixels
    void writeRect2BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette );
    
    // writeRect1BPP - 	write 1 bit per pixel paletted bitmap
    //					bitmap data in array at pixels, 4 bits per pixel
    //					color palette data in array at palette
    //					width must be at least 8 pixels
    void writeRect1BPP(int16_t x, int16_t y, int16_t w, int16_t h, const uint8_t *pixels, const uint16_t * palette );

      // writeRectNBPP - 	write N(1, 2, 4, 8) bit per pixel paletted bitmap
    //					bitmap data in array at pixels
    //  Currently writeRect1BPP, writeRect2BPP, writeRect4BPP use this to do all of the work. 
    // 
    void writeRectNBPP(int16_t x, int16_t y, int16_t w, int16_t h,  uint8_t bits_per_pixel, 
      const uint8_t *pixels, const uint16_t * palette );
    
    // from Adafruit_GFX.h
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);
    void inline drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) 
        { drawChar(x, y, c, color, bg, size, size);}
    #ifndef CENTER
    static const int16_t CENTER = 9998;
    #endif
    void setCursor(int16_t x, int16_t y, bool autoCenter=false);
      void getCursor(int16_t *x, int16_t *y);
    void setTextColor(uint16_t c);
    void setTextColor(uint16_t c, uint16_t bg);
      void setTextSize(uint8_t sx, uint8_t sy);
    void inline setTextSize(uint8_t s) { setTextSize(s,s); }
    uint8_t getTextSizeX();
    uint8_t getTextSizeY();
    uint8_t getTextSize();
    void setTextWrap(boolean w);
    boolean getTextWrap();

    // setOrigin sets an offset in display pixels where drawing to (0,0) will appear
    // for example: setOrigin(10,10); drawPixel(5,5); will cause a pixel to be drawn at hardware pixel (15,15)
    void setOrigin(int16_t x = 0, int16_t y = 0) { 
      _originx = x; _originy = y; 
      //if (Serial) Serial.printf("Set Origin %d %d\n", x, y);
      updateDisplayClip();
    }
    void getOrigin(int16_t* x, int16_t* y) { *x = _originx; *y = _originy; }

    // setClipRect() sets a clipping rectangle (relative to any set origin) for drawing to be limited to.
    // Drawing is also restricted to the bounds of the display

    void setClipRect(int16_t x1, int16_t y1, int16_t w, int16_t h) 
      { _clipx1 = x1; _clipy1 = y1; _clipx2 = x1+w; _clipy2 = y1+h; 
        //if (Serial) Serial.printf("Set clip Rect %d %d %d %d\n", x1, y1, w, h);
        updateDisplayClip();
      }
    void setClipRect() {
        _clipx1 = 0; _clipy1 = 0; _clipx2 = _width; _clipy2 = _height; 
        //if (Serial) Serial.printf("clear clip Rect\n");
        updateDisplayClip(); 
      }

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);	int16_t width(void)  { return _width; }
    int16_t height(void) { return _height; }
    uint8_t getRotation(void);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    int16_t getCursorX(void) const { return cursor_x; }
    int16_t getCursorY(void) const { return cursor_y; }
    void setFont(const BMC_ILI9341_t3_font_t &f);
      void setFont(const GFXfont *f = NULL);
    void setFontAdafruit(void) { setFont(); }
    void drawFontChar(unsigned int c);
    void drawGFXFontChar(unsigned int c);

      void getTextBounds(const uint8_t *buffer, uint16_t len, int16_t x, int16_t y,
        int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
      void getTextBounds(const char *string, int16_t x, int16_t y,
        int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
      void getTextBounds(const String &str, int16_t x, int16_t y,
        int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    int16_t strPixelLen(const char * str, uint16_t cb=0xffff);
    
    uint32_t fetchpixel(const uint8_t *p, uint32_t index, uint32_t x);
    void drawFontPixel( uint8_t alpha, uint32_t x, uint32_t y );

    void write16BitColor(uint16_t color, bool last_pixel=false);
    void write16BitColor(uint16_t color, uint16_t count, bool last_pixel);

    
    // added support for drawing strings/numbers/floats with centering
    // modified from tft_ili9488_ESP github library
    // Handle numbers
    int16_t  drawNumber(long long_num,int poX, int poY);
    int16_t  drawFloat(float floatNumber,int decimal,int poX, int poY);   
    // Handle char arrays
    int16_t drawString(const String& string, int poX, int poY);
    int16_t drawString(const char string[], int16_t len, int poX, int poY);

    void setTextDatum(uint8_t datum);
    
    // added support for scrolling text area
    // https://github.com/vitormhenrique/BMC_ILI9488_t3
    // Discussion regarding this optimized version:
      //http://forum.pjrc.com/threads/26305-Highly-optimized-ILI9488-%28320x240-TFT-color-display%29-library
    //	
    void setScrollTextArea(int16_t x, int16_t y, int16_t w, int16_t h);
    void setScrollBackgroundColor(uint16_t color);
    void enableScroll(void);
    void disableScroll(void);
    void scrollTextArea(uint8_t scrollSize);
    void resetScrollBackgroundColor(uint16_t color);
    
  #ifdef ENABLE_ILI9488_FRAMEBUFFER
    // added support to use optional Frame buffer
    // Wonder if this should be void*
    void	setFrameBuffer(RAFB *frame_buffer);
    RAFB 	*getFrameBuffer() {return _pfbtft;}
  #ifdef ILI9488_USES_PALLET
    uint16_t *getPallet() {return _pallet; }
    void	colorsArePalletIndex(boolean b) {_colors_are_index = b;}
    boolean	colorsArePalletIndex() {return _colors_are_index;}
    inline uint16_t mapColorToPalletIndex(uint16_t color) 
      {
        if (_pallet && _colors_are_index) return (uint8_t)color;
        return doActualConvertColorToIndex(color);		
      }
  #elif defined(ENABLE_EXT_DMA_UPDATES)
    uint16_t *getPallet() {return nullptr; }
    void	colorsArePalletIndex(boolean b) {;}
    boolean	colorsArePalletIndex() {return true;}
    inline uint32_t mapColorToPalletIndex(uint16_t color) { 
        // convert 565 to 666 format. 
        uint8_t r = (color & 0xF800) >> 11;
        uint8_t g = (color & 0x07E0) >> 5;
        uint8_t b = color & 0x001F;

        r = (r * 255) / 31;
        g = (g * 255) / 63;
        b = (b * 255) / 31;
        return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
      }
  #else
    // not using pallet
    uint16_t *getPallet() {return nullptr; }
    void	colorsArePalletIndex(boolean b) {;}
    boolean	colorsArePalletIndex() {return true;}
    inline uint16_t mapColorToPalletIndex(uint16_t color) { return color; }
  #endif 		
  #else
    // added support to use optional Frame buffer
    void	setFrameBuffer(uint8_t *frame_buffer);
    uint8_t *getFrameBuffer() {return nullptr;}
    uint16_t *getPallet() {return nullptr; }
    void	colorsArePalletIndex(boolean b) {;}
    boolean	colorsArePalletIndex() {return true;}
    inline uint16_t mapColorToPalletIndex(uint16_t color) { return color; }
  #endif	
    uint8_t useFrameBuffer(boolean b);		// use the frame buffer?  First call will allocate
    void	freeFrameBuffer(void);			// explicit call to release the buffer
    void	updateScreen(void);				// call to say update the screen now. 

    // Support for user to set Pallet. 
    void	setPallet(uint16_t *pal, uint16_t count);	// <= 256
    
    // probably not called directly... 
    uint8_t doActualConvertColorToIndex(uint16_t color);  

      
    bool	updateScreenAsync(bool update_cont = false);	// call to say update the screen optinoally turn into continuous mode. 
    void	waitUpdateAsyncComplete(void);
    void	endUpdateAsync();			 // Turn of the continueous mode fla
    void	dumpDMASettings();
    #ifdef ENABLE_ILI9488_FRAMEBUFFER
    uint32_t frameCount() {return _dma_frame_count; }
    uint8_t	 subFrameCount() { return _dma_sub_frame_count;}
    boolean	asyncUpdateActive(void)  {return (_dma_state & ILI9488_DMA_ACTIVE);}
    void	initDMASettings(void);
    void	setFrameCompleteCB(void (*pcb)(), bool fCallAlsoHalfDone=false);
    #else
    uint32_t frameCount() {return 0; }
    boolean	asyncUpdateActive(void)  {return false;}
    #endif


  protected:
    uint32_t				_clock;
      SPIClass                *spi_port;
    SPIClass::SPI_Hardware_t *_spi_hardware;
      uint8_t   				_spi_num;         	// Which buss is this spi on? 
      //uint32_t                _spi_port_memorymap = 0;
  #if defined(KINETISK)
    KINETISK_SPI_t *_pkinetisk_spi;
    uint8_t			_fifo_size;
  #elif defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
    //inline IMXRT_LPSPI_t & port() { return (*(IMXRT_LPSPI_t *)0x403A0000); }
    IMXRT_LPSPI_t *_pimxrt_spi;
  #elif defined(KINETISL)
    KINETISL_SPI_t *_pkinetisl_spi;
  #endif
    int16_t _width, _height; // Display w/h as modified by current rotation
    int16_t  cursor_x, cursor_y;
    bool 	_center_x_text = false; 
    bool 	_center_y_text = false; 
    int16_t  _clipx1, _clipy1, _clipx2, _clipy2;
    int16_t  _originx, _originy;
    int16_t  _displayclipx1, _displayclipy1, _displayclipx2, _displayclipy2;
    bool _invisible = false; 
    bool _standard = true; // no bounding rectangle or origin set. 

    inline void updateDisplayClip() {
      _displayclipx1 = max(0,min(_clipx1+_originx,width()));
      _displayclipx2 = max(0,min(_clipx2+_originx,width()));

      _displayclipy1 = max(0,min(_clipy1+_originy,height()));
      _displayclipy2 = max(0,min(_clipy2+_originy,height()));
      _invisible = (_displayclipx1 == _displayclipx2 || _displayclipy1 == _displayclipy2);
      _standard =  (_displayclipx1 == 0) && (_displayclipx2 == _width) && (_displayclipy1 == 0) && (_displayclipy2 == _height);
      if (Serial) {
        //Serial.printf("UDC (%d %d)-(%d %d) %d %d\n", _displayclipx1, _displayclipy1, _displayclipx2, 
        //	_displayclipy2, _invisible, _standard);

      }
    }
    
    uint16_t textcolor, textbgcolor, scrollbgcolor;
    uint8_t textsize, textsize_x, textsize_y, rotation,textdatum;
    uint32_t textcolorPrexpanded, textbgcolorPrexpanded;
    boolean wrap; // If set, 'wrap' text at right edge of display
    const BMC_ILI9341_t3_font_t *font;

    // Anti-aliased font support
    uint8_t fontbpp = 1;
    uint8_t fontbppindex = 0;
    uint8_t fontbppmask = 1;
    uint8_t fontppb = 8;
    uint8_t* fontalphalut;
    float fontalphamx = 1;	
    
    uint32_t padX;
    int16_t scroll_x, scroll_y, scroll_width, scroll_height;
    boolean scrollEnable,isWritingScrollArea; // If set, 'wrap' text at right edge of display

    // GFX Font support
    const GFXfont *gfxFont = nullptr;
    int8_t _gfxFont_min_yOffset = 0;
    
    // Opaque font chracter overlap?
    unsigned int _gfx_c_last;
    int16_t   _gfx_last_cursor_x, _gfx_last_cursor_y;
    int16_t	 _gfx_last_char_x_write = 0;
    uint16_t _gfx_last_char_textcolor;
    uint16_t _gfx_last_char_textbgcolor;
    bool gfxFontLastCharPosFG(int16_t x, int16_t y);
    
      uint8_t  _rst;
      uint8_t _cs, _dc;
    uint8_t pcs_data, pcs_command;
    uint8_t _miso, _mosi, _sclk;
    // add support to allow only one hardware CS (used for dc)
  #if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
    
      uint32_t _cspinmask;
      volatile uint32_t *_csport;
      uint32_t _spi_tcr_current;
      uint32_t _dcpinmask;
      uint8_t _pending_rx_count;
      volatile uint32_t *_dcport;
      uint32_t _tcr_dc_assert;
      uint32_t _tcr_dc_not_assert;

  #elif defined(KINETISK)
      uint8_t _cspinmask;
      volatile uint8_t *_csport;

  #elif defined(KINETISL)
      uint8_t _pending_rx_count;
    uint8_t _dcpinAsserted;
      volatile uint8_t  *_dcport;
      uint8_t _dcpinmask;
      uint8_t _cspinmask;
      volatile uint8_t *_csport;

  #endif

  #ifdef ENABLE_ILI9488_FRAMEBUFFER
    enum {DMA_PIXELS_OUTPUT_PER_DMA=80};  // How many pixels at a time?
      // Add support for optional frame buffer
      RAFB		*_pfbtft;						// Optional Frame buffer 
      uint8_t		_use_fbtft;						// Are we in frame buffer mode?
      uint8_t		*_we_allocated_buffer;			// We allocated the buffer; 

  #ifdef ILI9488_USES_PALLET
      uint16_t	*_pallet;						// Support for user to set Pallet. 
      uint16_t	_pallet_size;					// How big is the pallet
      uint16_t	_pallet_count;					// how many items are in it...
      boolean		_colors_are_index;				// are the values passed in index or color?
  #endif
      // Add DMA support. 
    void		(*_frame_complete_callback)() = nullptr;
    bool 		_frame_callback_on_HalfDone = false;
    #if defined(__IMXRT1062__)  // Teensy 4.x
    static  BMC_ILI9488_t3 		*_dmaActiveDisplay[3];  // Use pointer to this as a way to get back to object...
    #else
    static  BMC_ILI9488_t3 		*_dmaActiveDisplay;  // Use pointer to this as a way to get back to object...
    #endif
    volatile uint8_t  	_dma_state;  			// DMA status
    volatile uint32_t	_dma_frame_count;		// Can return a frame count...
    volatile uint16_t	_dma_sub_frame_count;	// Can return a frame count...

    // T3.6
    #if defined(__MK66FX1M0__) 
    static DMASetting 	_dmasettings[3];
    static DMAChannel  	_dmatx;

    bool fillDMApixelBuffer(RAFB *buffer_ptr);

    RAFB _dma_pixel_buffer0[DMA_PIXELS_OUTPUT_PER_DMA*3] __attribute__ ((aligned(4)));
    RAFB _dma_pixel_buffer1[DMA_PIXELS_OUTPUT_PER_DMA*3] __attribute__ ((aligned(4)));

    #elif defined(__MK64FX512__)
    // T3.5 - had issues scatter/gather so do just use channels/interrupts
    // and update and continue
    static DMAChannel  	_dmatx;
    bool fillDMApixelBuffer(RAFB *buffer_ptr);

    RAFB _dma_pixel_buffer0[DMA_PIXELS_OUTPUT_PER_DMA*3] __attribute__ ((aligned(4)));
    RAFB _dma_pixel_buffer1[DMA_PIXELS_OUTPUT_PER_DMA*3] __attribute__ ((aligned(4)));

    #elif defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
    // Going to try it similar to T4.
    #if defined(ENABLE_EXT_DMA_UPDATES)
    #define SCREEN_DMA_NUM_SETTINGS 5 // see if making it a constant value makes difference...
    DMASetting   		_dmasettings[6];
    DMAChannel  		_dmatx;
    #else
    DMASetting 			_dmasettings[2];
    DMAChannel  		_dmatx;

    bool fillDMApixelBuffer(uint32_t *buffer_ptr);

    uint32_t _dma_pixel_buffer0[DMA_PIXELS_OUTPUT_PER_DMA] __attribute__ ((aligned(4)));
    uint32_t _dma_pixel_buffer1[DMA_PIXELS_OUTPUT_PER_DMA] __attribute__ ((aligned(4)));

    #endif
    uint32_t 			_spi_fcr_save;		// save away previous FCR register value
    #endif	
    static void dmaInterrupt(void);
    static void dmaInterrupt1(void);
    static void dmaInterrupt2(void);
    void process_dma_interrupt(void);
    static volatile uint32_t _dma_pixel_index;
    //static volatile uint16_t	_dma_sub_frame_count;	// Can return a frame count...
  #endif

    void charBounds(char c, int16_t *x, int16_t *y,
              int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);
    uint16_t _previous_addr_x0 = 0xffff; 
    uint16_t _previous_addr_x1 = 0xffff; 
    uint16_t _previous_addr_y0 = 0xffff; 
    uint16_t _previous_addr_y1 = 0xffff; 

    void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
      __attribute__((always_inline)) {
        if ((x0 != _previous_addr_x0) || (x1 != _previous_addr_x1)) {
        writecommand_cont(ILI9488_CASET); // Column addr set
        writedata16_cont(x0);   // XSTART
        writedata16_cont(x1);   // XEND	
        _previous_addr_x0 = x0;
        _previous_addr_x1 = x1;
        }
        if ((y0 != _previous_addr_y0) || (y1 != _previous_addr_y1)) {
        writecommand_cont(ILI9488_PASET); // Row addr set
        writedata16_cont(y0);   // YSTART
        writedata16_cont(y1);   // YEND
        _previous_addr_y0 = y0;
        _previous_addr_y1 = y1;
      }
    }
    
  //----------------------------------------------------------------------
  // Processor Specific stuff
  #if defined(__IMXRT1052__) || defined(__IMXRT1062__)  // Teensy 4.x
  // T4
    void DIRECT_WRITE_LOW(volatile uint32_t * base, uint32_t mask)  __attribute__((always_inline)) {
      *(base+34) = mask;
    }
    void DIRECT_WRITE_HIGH(volatile uint32_t * base, uint32_t mask)  __attribute__((always_inline)) {
      *(base+33) = mask;
    }
    void waitFifoNotFull(void) {
        uint32_t tmp __attribute__((unused));
        do {
            if ((_pimxrt_spi->RSR & LPSPI_RSR_RXEMPTY) == 0)  {
                tmp = _pimxrt_spi->RDR;  // Read any pending RX bytes in
                if (_pending_rx_count) _pending_rx_count--; //decrement count of bytes still levt
            }
        } while ((_pimxrt_spi->SR & LPSPI_SR_TDF) == 0) ;
    }
    void waitTransmitComplete(void)  {
        uint32_t tmp __attribute__((unused));
    //    digitalWriteFast(2, HIGH);

        while (_pending_rx_count) {
            if ((_pimxrt_spi->RSR & LPSPI_RSR_RXEMPTY) == 0)  {
                tmp = _pimxrt_spi->RDR;  // Read any pending RX bytes in
                _pending_rx_count--; //decrement count of bytes still levt
            }
        }
        _pimxrt_spi->CR = LPSPI_CR_MEN | LPSPI_CR_RRF;       // Clear RX FIFO
    //    digitalWriteFast(2, LOW);
    }

  #ifndef TCR_MASK
  #define TCR_MASK  (LPSPI_TCR_PCS(3) | LPSPI_TCR_FRAMESZ(31) | LPSPI_TCR_CONT | LPSPI_TCR_RXMSK )
  #endif
    void maybeUpdateTCR(uint32_t requested_tcr_state) /*__attribute__((always_inline)) */ {
      if ((_spi_tcr_current & TCR_MASK) != requested_tcr_state) {
        bool dc_state_change = (_spi_tcr_current & LPSPI_TCR_PCS(3)) != (requested_tcr_state & LPSPI_TCR_PCS(3));
        _spi_tcr_current = (_spi_tcr_current & ~TCR_MASK) | requested_tcr_state ;
        // only output when Transfer queue is empty.
        if (!dc_state_change || !_dcpinmask) {
          while ((_pimxrt_spi->FSR & 0x1f) )	;
          _pimxrt_spi->TCR = _spi_tcr_current;	// update the TCR

        } else {
          waitTransmitComplete();
          if (requested_tcr_state & LPSPI_TCR_PCS(3)) DIRECT_WRITE_HIGH(_dcport, _dcpinmask);
          else DIRECT_WRITE_LOW(_dcport, _dcpinmask);
          _pimxrt_spi->TCR = _spi_tcr_current & ~(LPSPI_TCR_PCS(3) | LPSPI_TCR_CONT);	// go ahead and update TCR anyway?  

        }
      }
    }

    void beginSPITransaction()  __attribute__((always_inline)) {
      spi_port->beginTransaction(SPISettings(_clock, MSBFIRST, SPI_MODE0));
      if (!_dcport) _spi_tcr_current = _pimxrt_spi->TCR; 	// Only if DC is on hardware CS 
      if (_csport)
        DIRECT_WRITE_LOW(_csport, _cspinmask);
    }
    void beginSPITransaction(uint32_t clock)  __attribute__((always_inline)) {
      spi_port->beginTransaction(SPISettings(clock, MSBFIRST, SPI_MODE0));
      if (_csport)
        DIRECT_WRITE_LOW(_csport, _cspinmask);
    }
    void endSPITransaction()  __attribute__((always_inline)) {
      if (_csport)
        DIRECT_WRITE_HIGH(_csport, _cspinmask);
      spi_port->endTransaction();
    }

    // BUGBUG:: currently assumming we only have CS_0 as valid CS
    void writecommand_cont(uint8_t c) __attribute__((always_inline)) {
      maybeUpdateTCR(_tcr_dc_assert | LPSPI_TCR_FRAMESZ(7) /*| LPSPI_TCR_CONT*/);
      _pimxrt_spi->TDR = c;
      _pending_rx_count++;	//
      waitFifoNotFull();
    }
    void writedata8_cont(uint8_t c) __attribute__((always_inline)) {
      maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(7) | LPSPI_TCR_CONT);
      _pimxrt_spi->TDR = c;
      _pending_rx_count++;	//
      waitFifoNotFull();
    }
    void writedata16_cont(uint16_t d) __attribute__((always_inline)) {
      maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(15) | LPSPI_TCR_CONT);
      _pimxrt_spi->TDR = d;
      _pending_rx_count++;	//
      waitFifoNotFull();
    }
    void writecommand_last(uint8_t c) __attribute__((always_inline)) {
      maybeUpdateTCR(_tcr_dc_assert | LPSPI_TCR_FRAMESZ(7));
      _pimxrt_spi->TDR = c;
  //		_pimxrt_spi->SR = LPSPI_SR_WCF | LPSPI_SR_FCF | LPSPI_SR_TCF;
      _pending_rx_count++;	//
      waitTransmitComplete();
    }
    void writedata8_last(uint8_t c) __attribute__((always_inline)) {
      maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(7));
      _pimxrt_spi->TDR = c;
  //		_pimxrt_spi->SR = LPSPI_SR_WCF | LPSPI_SR_FCF | LPSPI_SR_TCF;
      _pending_rx_count++;	//
      waitTransmitComplete();
    }
    void writedata16_last(uint16_t d) __attribute__((always_inline)) {
      maybeUpdateTCR(_tcr_dc_not_assert | LPSPI_TCR_FRAMESZ(15));
      _pimxrt_spi->TDR = d;
  //		_pimxrt_spi->SR = LPSPI_SR_WCF | LPSPI_SR_FCF | LPSPI_SR_TCF;
      _pending_rx_count++;	//
      waitTransmitComplete();
    }
  #elif defined(KINETISK)
  // T3.x	
    void waitFifoNotFull(void) {
      uint32_t sr;
      uint32_t tmp __attribute__((unused));
      do {
        sr = _pkinetisk_spi->SR;
        if (sr & 0xF0) tmp = _pkinetisk_spi->POPR;  // drain RX FIFO
      } while ((uint16_t)(sr & (15 << 12)) > ((uint16_t)(_fifo_size-1) << 12));
    }
    void waitFifoEmpty(void) {
      uint32_t sr;
      uint32_t tmp __attribute__((unused));
      do {
        sr = _pkinetisk_spi->SR;
        if (sr & 0xF0) tmp = _pkinetisk_spi->POPR;  // drain RX FIFO
      } while ((sr & 0xF0F0) > 0);             // wait both RX & TX empty
    }
    void waitTransmitComplete(void) {
      uint32_t tmp __attribute__((unused));
      while (!(_pkinetisk_spi->SR & SPI_SR_TCF)) ; // wait until final output done
      tmp = _pkinetisk_spi->POPR;                  // drain the final RX FIFO word
    }
    void waitTransmitComplete(uint32_t mcr) {
      uint32_t tmp __attribute__((unused));
      while (1) {
        uint32_t sr = _pkinetisk_spi->SR;
        if (sr & SPI_SR_EOQF) break;  // wait for last transmit
        if (sr &  0xF0) tmp = _pkinetisk_spi->POPR;
      }
      _pkinetisk_spi->SR = SPI_SR_EOQF;
      _pkinetisk_spi->MCR = mcr;
      while (_pkinetisk_spi->SR & 0xF0) {
        tmp = _pkinetisk_spi->POPR;
      }
    }
    void beginSPITransaction()  __attribute__((always_inline)) {
      spi_port->beginTransaction(SPISettings(_clock, MSBFIRST, SPI_MODE0));
      if (_csport)
        *_csport  &= ~_cspinmask;
    }

    void beginSPITransaction(uint32_t clock)  __attribute__((always_inline)) {
      spi_port->beginTransaction(SPISettings(clock, MSBFIRST, SPI_MODE0));
      if (_csport)
        *_csport  &= ~_cspinmask;
    }
    void endSPITransaction()  __attribute__((always_inline)) {
      if (_csport)
        *_csport |= _cspinmask;
      spi_port->endTransaction();
    }

    void writecommand_cont(uint8_t c)  __attribute__((always_inline)) {
      _pkinetisk_spi->PUSHR = c | (pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
      waitFifoNotFull();
    }
    void writedata8_cont(uint8_t c)  __attribute__((always_inline)) {
      _pkinetisk_spi->PUSHR = c | (pcs_data << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
      waitFifoNotFull();
    }
    void writedata16_cont(uint16_t d)  __attribute__((always_inline)) {
      _pkinetisk_spi->PUSHR = d | (pcs_data << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
      waitFifoNotFull();
    }
    void writecommand_last(uint8_t c)  __attribute__((always_inline)) {
      uint32_t mcr = _pkinetisk_spi->MCR;
      _pkinetisk_spi->PUSHR = c | (pcs_command << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
      waitTransmitComplete(mcr);
    }
    void writedata8_last(uint8_t c)  __attribute__((always_inline)) {
      uint32_t mcr = _pkinetisk_spi->MCR;
      _pkinetisk_spi->PUSHR = c | (pcs_data << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
      waitTransmitComplete(mcr);
    }
    void writedata16_last(uint16_t d)  __attribute__((always_inline)) {
      uint32_t mcr = _pkinetisk_spi->MCR;
      _pkinetisk_spi->PUSHR = d | (pcs_data << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_EOQ;
      waitTransmitComplete(mcr);
    }
  #elif defined(KINETISL)
    void waitTransmitComplete(void)  {
        uint32_t tmp __attribute__((unused));

      while (_pending_rx_count) {
        uint16_t timeout_count = 0xff; // hopefully enough 
        while (!(_pkinetisl_spi->S & SPI_S_SPRF) && timeout_count--) ; // wait 
        uint8_t d __attribute__((unused));
        d = _pkinetisl_spi->DL;
        d = _pkinetisl_spi->DH;
        _pending_rx_count--; // We hopefully received our data...
      }
    }
    

    void setCommandMode()  __attribute__((always_inline)) {
      if (!_dcpinAsserted) {
        waitTransmitComplete();
        *_dcport  &= ~_dcpinmask;
        _dcpinAsserted = 1;
      }
    }

    void setDataMode()  __attribute__((always_inline)){
      if (_dcpinAsserted) {
        waitTransmitComplete();
        *_dcport  |= _dcpinmask;
        _dcpinAsserted = 0;
      }
    }
    void outputToSPIAlready8Bits(uint8_t c) __attribute__((always_inline)){
      while (!(_pkinetisl_spi->S & SPI_S_SPTEF)) ; // wait if output buffer busy.
      // Clear out buffer if there is something there...
      if  ((_pkinetisl_spi->S & SPI_S_SPRF)) {
        uint8_t d __attribute__((unused));
        d = _pkinetisl_spi->DL;
        _pending_rx_count--;
      } 
      _pkinetisl_spi->DL = c; // output byte
      _pending_rx_count++; // let system know we sent something	
    }

    void outputToSPI(uint8_t c) __attribute__((always_inline)){
      if (_pkinetisl_spi->C2 & SPI_C2_SPIMODE) {
        // Wait to change modes until any pending output has been done.
        waitTransmitComplete();
        _pkinetisl_spi->C2 = 0; // make sure 8 bit mode.
      }
      outputToSPIAlready8Bits(c);
    }

    void outputToSPI16(uint16_t data)  {
      if (!(_pkinetisl_spi->C2 & SPI_C2_SPIMODE)) {
        // Wait to change modes until any pending output has been done.
        waitTransmitComplete();
        _pkinetisl_spi->C2 = SPI_C2_SPIMODE; // make sure 8 bit mode.
      }
      uint8_t s;
      do {
        s = _pkinetisl_spi->S;
        // wait if output buffer busy.
        // Clear out buffer if there is something there...
        if  ((s & SPI_S_SPRF)) {
          uint8_t d __attribute__((unused));
          d = _pkinetisl_spi->DL;
          d = _pkinetisl_spi->DH;
          _pending_rx_count--; 	// let system know we sent something	
        }

      } while (!(s & SPI_S_SPTEF) || (s & SPI_S_SPRF));

      _pkinetisl_spi->DL = data; 		// output low byte
      _pkinetisl_spi->DH = data >> 8; // output high byte
      _pending_rx_count++; 	// let system know we sent something	
    }

    void beginSPITransaction() __attribute__((always_inline)) {
      spi_port->beginTransaction(SPISettings(_clock, MSBFIRST, SPI_MODE0));
      if (_csport)
        *_csport  &= ~_cspinmask;
    }
    void beginSPITransaction(uint32_t clock) __attribute__((always_inline)) {
      spi_port->beginTransaction(SPISettings(clock, MSBFIRST, SPI_MODE0));
      if (_csport)
        *_csport  &= ~_cspinmask;
    }
    void endSPITransaction() __attribute__((always_inline)) {
      if (_csport)
        *_csport |= _cspinmask;
      spi_port->endTransaction();
    }

    void writecommand_cont(uint8_t c) __attribute__((always_inline))  {
      setCommandMode();
      outputToSPI(c);
    }
    void writedata8_cont(uint8_t c) __attribute__((always_inline)) {
      setDataMode();
      outputToSPI(c);
    }

    void writedata16_cont(uint16_t c) __attribute__((always_inline))  {
      setDataMode();
      outputToSPI16(c);
    }

    void writecommand_last(uint8_t c) __attribute__((always_inline))  {
      setCommandMode();
      outputToSPI(c);
      waitTransmitComplete();
    }
    void writedata8_last(uint8_t c) __attribute__((always_inline))  {
      setDataMode();
      outputToSPI(c);
      waitTransmitComplete();
    }
    void writedata16_last(uint16_t c) __attribute__((always_inline)) {
      setDataMode();
      outputToSPI16(c);
      waitTransmitComplete();
    }

  #endif

    // Other helper functions.
    void HLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void VLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void Pixel(int16_t x, int16_t y, uint16_t color);

    /**
     * Found in a pull request for the Adafruit framebuffer library. Clever!
     * https://github.com/tricorderproject/arducordermini/pull/1/files#diff-d22a481ade4dbb4e41acc4d7c77f683d
     * Converts  0000000000000000rrrrrggggggbbbbb
     *     into  00000gggggg00000rrrrr000000bbbbb
     * with mask 00000111111000001111100000011111
     * This is useful because it makes space for a parallel fixed-point multiply
     * This implements the linear interpolation formula: result = bg * (1.0 - alpha) + fg * alpha
     * This can be factorized into: result = bg + (fg - bg) * alpha
     * alpha is in Q1.5 format, so 0.0 is represented by 0, and 1.0 is represented by 32
     * @param	fg		Color to draw in RGB565 (16bit)
     * @param	bg		Color to draw over in RGB565 (16bit)
     * @param	alpha	Alpha in range 0-255
     **/
    uint16_t alphaBlendRGB565( uint32_t fg, uint32_t bg, uint8_t alpha )
    __attribute__((always_inline)) {
      alpha = ( alpha + 4 ) >> 3; // from 0-255 to 0-31
      bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
      fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;
      uint32_t result = ((((fg - bg) * alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
      return (uint16_t)((result >> 16) | result); // contract result
    }
    
    /**
     * Same as above, but fg and bg are premultiplied, and alpah is already in range 0-31
     */
    uint16_t alphaBlendRGB565Premultiplied( uint32_t fg, uint32_t bg, uint8_t alpha )
    __attribute__((always_inline)) {
      uint32_t result = ((((fg - bg) * alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
      return (uint16_t)((result >> 16) | result); // contract result
    }
    
    void drawFontBits(bool opaque, uint32_t bits, uint32_t numbits, int32_t x, int32_t y, uint32_t repeat);};

  #ifndef ILI9488_swap
  #define ILI9488_swap(a, b) { typeof(a) t = a; a = b; b = t; }
  #endif

  // To avoid conflict when also using Adafruit_GFX or any Adafruit library
  // which depends on Adafruit_GFX, #include the Adafruit library *BEFORE*
  // you #include BMC_ILI9341_t3.h.
  // Warning the implemention of class needs to be here, else the code
  // compiled in the c++ file will cause duplicate defines in the link phase. 
  //#ifndef _ADAFRUIT_GFX_H
  // #ifdef Adafruit_GFX_Button
  // #undef Adafruit_GFX_Button
  // #endif
  // #define Adafruit_GFX_Button ILI9488_Button
  // class ILI9488_Button {
  // public:
  // 	ILI9488_Button(void) { _gfx = NULL; }
  // 	void initButton(BMC_ILI9488_t3 *gfx, int16_t x, int16_t y,
  // 		uint8_t w, uint8_t h,
  // 		uint16_t outline, uint16_t fill, uint16_t textcolor,
  // 		const char *label, uint8_t textsize_x, uint8_t textsize_y) {
  // 		_x = x;
  // 		_y = y;
  // 		_w = w;
  // 		_h = h;
  // 		_outlinecolor = outline;
  // 		_fillcolor = fill;
  // 		_textcolor = textcolor;
  // 		_textsize_x = textsize_x;
  // 		_textsize_y = textsize_y;
  // 		_gfx = gfx;
  // 		strncpy(_label, label, 9);
  // 		_label[9] = 0;

  // 	}
  // 	void drawButton(bool inverted = false) {
  // 		uint16_t fill, outline, text;

  // 		if (! inverted) {
  // 			fill = _fillcolor;
  // 			outline = _outlinecolor;
  // 			text = _textcolor;
  // 		} else {
  // 			fill =  _textcolor;
  // 			outline = _outlinecolor;
  // 			text = _fillcolor;
  // 		}
  // 		_gfx->fillRoundRect(_x - (_w/2), _y - (_h/2), _w, _h, min(_w,_h)/4, fill);
  // 		_gfx->drawRoundRect(_x - (_w/2), _y - (_h/2), _w, _h, min(_w,_h)/4, outline);
  // 		_gfx->setCursor(_x - strlen(_label)*3*_textsize_x, _y-4*_textsize_y);
  // 		_gfx->setTextColor(text);
  // 		_gfx->setTextSize(_textsize_x, _textsize_y);
  // 		_gfx->print(_label);
  // 	}

  // 	bool contains(int16_t x, int16_t y) {
  // 		if ((x < (_x - _w/2)) || (x > (_x + _w/2))) return false;
  // 		if ((y < (_y - _h/2)) || (y > (_y + _h/2))) return false;
  // 		return true;
  // 	}

  // 	void press(boolean p) {
  // 		laststate = currstate;
  // 		currstate = p;
  // 	}
  // 	bool isPressed() { return currstate; }
  // 	bool justPressed() { return (currstate && !laststate); }
  // 	bool justReleased() { return (!currstate && laststate); }
  // private:
  // 	BMC_ILI9488_t3 *_gfx;
  // 	int16_t _x, _y;
  // 	uint16_t _w, _h;
  // 	uint8_t _textsize_x, _textsize_y;
  // 	uint16_t _outlinecolor, _fillcolor, _textcolor;
  // 	char _label[10];
  // 	boolean currstate, laststate;
  // };
  //#endif

  #endif // __cplusplus


#endif
