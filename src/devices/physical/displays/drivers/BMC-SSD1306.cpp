/*!
  This is a modified version of the Adafruit SSD1306 library
  It's modified for BMC and to only use I2C
  It's tested with common Amazon OLED Display

 * @file SSD1306.cpp
 *
 * @mainpage Arduino library for monochrome OLEDs based on SSD1306 drivers.
 *
 * @section intro_sec Introduction
 *
 * This is documentation for Adafruit's SSD1306 library for monochrome
 * OLED displays: http://www.adafruit.com/category/63_98
 *
 * These displays use I2C or SPI to communicate. I2C requires 2 pins
 * (SCL+SDA) and optionally a RESET pin. SPI requires 4 pins (MOSI, SCK,
 * select, data/command) and optionally a reset pin. Hardware SPI or
 * 'bitbang' software SPI are both supported.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section dependencies Dependencies
 *
 * This library depends on <a href="https://github.com/adafruit/Adafruit-GFX-Library">
 * Adafruit_GFX</a> being present on your system. Please make sure you have
 * installed the latest version before using this library.
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries, with
 * contributions from the open source community.
 *
 * @section license License
 *
 * BSD license, all text above, and the splash screen included below,
 * must be included in any redistribution.
 *
 */


#include "utility/BMC-Def.h"

#if BMC_MAX_OLED > 0


#ifdef __AVR__
 #include <avr/pgmspace.h>
#elif defined(BMC_FOR_TEENSY)
 #include <pgmspace.h>
#else
 #define pgm_read_byte(addr) \
  (*(const unsigned char *)(addr)) ///< PROGMEM workaround for non-AVR
#endif

// #if !defined(__ARM_ARCH) && !defined(ENERGIA) && !defined(ESP8266) && !defined(ESP32) && !defined(__arc__)
//  #include <util/delay.h>
// #endif

#include <Arduino.h>
#include <Adafruit_GFX.h>
// #include "devices/physical/displays/drivers/BMC-GFX.h"
#include "devices/physical/displays/drivers/BMC-SSD1306.h"

#if defined(ESP32)
  #define BUFFER_LENGTH I2C_BUFFER_LENGTH
#else
  #if defined(I2C_T3_H)
    #define BUFFER_LENGTH I2C_TX_BUFFER_LENGTH
  #endif
#endif

// SOME DEFINES AND STATIC VARIABLES USED INTERNALLY -----------------------
#if defined(BUFFER_LENGTH)
 #define WIRE_MAX BUFFER_LENGTH          ///< AVR or similar Wire lib
#elif defined(SERIAL_BUFFER_SIZE)
 #define WIRE_MAX (SERIAL_BUFFER_SIZE-1) ///< Newer Wire uses RingBuffer
#else
 #define WIRE_MAX 32                     ///< Use common Arduino core default
#endif


#define ssd1306_swap(a, b) \
  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))) ///< No-temp-var swap operation


// Check first if Wire, then hardware SPI, then soft SPI:
#define TRANSACTION_START
#define TRANSACTION_END

// CONSTRUCTORS, DESTRUCTOR ------------------------------------------------

/*!
    @brief  Constructor for I2C-interfaced SSD1306 displays.
    @param  w
            Display width in pixels
    @param  h
            Display height in pixels
    @param  twi
            Pointer to an existing TwoWire instance (e.g. &Wire, the
            microcontroller's primary I2C bus).
    @param  rst_pin
            Reset pin (using Arduino pin numbering), or -1 if not used
            (some displays might be wired to share the microcontroller's
            reset pin).
    @param  clkDuring
            Speed (in Hz) for Wire transmissions in SSD1306 library calls.
            Defaults to 400000 (400 KHz), a known 'safe' value for most
            microcontrollers, and meets the SSD1306 datasheet spec.
            Some systems can operate I2C faster (800 KHz for ESP32, 1 MHz
            for many other 32-bit MCUs), and some (perhaps not all)
            SSD1306's can work with this -- so it's optionally be specified
            here and is not a default behavior. (Ignored if using pre-1.5.7
            Arduino software, which operates I2C at a fixed 100 KHz.)
    @param  clkAfter
            Speed (in Hz) for Wire transmissions following SSD1306 library
            calls. Defaults to 100000 (100 KHz), the default Arduino Wire
            speed. This is done rather than leaving it at the 'during' speed
            because other devices on the I2C bus might not be compatible
            with the faster rate. (Ignored if using pre-1.5.7 Arduino
            software, which operates I2C at a fixed 100 KHz.)
    @return SSD1306 object.
    @note   Call the object's begin() function before use -- buffer
            allocation is performed there!
*/
BMC_SSD1306::BMC_SSD1306(uint8_t w, uint8_t h):Adafruit_GFX(w, h), buffer(NULL){}

/*!
    @brief  Destructor for SSD1306 object.
*/
BMC_SSD1306::~BMC_SSD1306(void) {
  if(buffer) {
    free(buffer);
    buffer = NULL;
  }
}

// LOW-LEVEL UTILS ---------------------------------------------------------


// Issue single command to SSD1306, using I2C or hard/soft SPI as needed.
// Because command calls are often grouped, SPI transaction and selection
// must be started/ended in calling function for efficiency.
// This is a private function, not exposed (see ssd1306_command() instead).
void BMC_SSD1306::ssd1306_command1(uint8_t c) {
  Wire.beginTransmission(i2caddr);
  Wire.write((uint8_t)0x00); // Co = 0, D/C = 0
  Wire.write(c);
  Wire.endTransmission();
}

// Issue list of commands to SSD1306, same rules as above re: transactions.
// This is a private function, not exposed.
void BMC_SSD1306::ssd1306_commandList(const uint8_t *c, uint8_t n) {
  Wire.beginTransmission(i2caddr);
  Wire.write((uint8_t)0x00); // Co = 0, D/C = 0
  uint8_t bytesOut = 1;
  while(n--) {
    if(bytesOut >= WIRE_MAX) {
      Wire.endTransmission();
      Wire.beginTransmission(i2caddr);
      Wire.write((uint8_t)0x00); // Co = 0, D/C = 0
      bytesOut = 1;
    }
    Wire.write(pgm_read_byte(c++));
    bytesOut++;
  }
  Wire.endTransmission();
}

// A public version of ssd1306_command1(), for existing user code that
// might rely on that function. This encapsulates the command transfer
// in a transaction start/end, similar to old library's handling of it.
/*!
    @brief  Issue a single low-level command directly to the SSD1306
            display, bypassing the library.
    @param  c
            Command to issue (0x00 to 0xFF, see datasheet).
    @return None (void).
*/
void BMC_SSD1306::ssd1306_command(uint8_t c) {
  ssd1306_command1(c);
}

// ALLOCATE & INIT DISPLAY -------------------------------------------------

/*!
    @brief  Allocate RAM for image buffer, initialize peripherals and pins.
    @param  vcs
            VCC selection. Pass BMC_SSD1306_SWITCHCAPVCC to generate the display
            voltage (step up) from the 3.3V source, or BMC_SSD1306_EXTERNALVCC
            otherwise. Most situations with Adafruit SSD1306 breakouts will
            want BMC_SSD1306_SWITCHCAPVCC.
    @param  addr
            I2C address of corresponding SSD1306 display (or pass 0 to use
            default of 0x3C for 128x32 display, 0x3D for all others).
            SPI displays (hardware or software) do not use addresses, but
            this argument is still required (pass 0 or any value really,
            it will simply be ignored). Default if unspecified is 0.
    @param  reset
            If true, and if the reset pin passed to the constructor is
            valid, a hard reset will be performed before initializing the
            display. If using multiple SSD1306 displays on the same bus, and
            if they all share the same reset pin, you should only pass true
            on the first display being initialized, false on all others,
            else the already-initialized displays would be reset. Default if
            unspecified is true.
    @param  periphBegin
            If true, and if a hardware peripheral is being used (I2C or SPI,
            but not software SPI), call that peripheral's begin() function,
            else (false) it has already been done in one's sketch code.
            Cases where false might be used include multiple displays or
            other devices sharing a common bus, or situations on some
            platforms where a nonstandard begin() function is available
            (e.g. a TwoWire interface on non-default pins, as can be done
            on the ESP8266 and perhaps others).
    @return true on successful allocation/init, false otherwise.
            Well-behaved code should check the return value before
            proceeding.
    @note   MUST call this function before any drawing or updates!
*/
boolean BMC_SSD1306::begin(uint8_t vcs, uint8_t addr) {
  if((!buffer) && !(buffer = (uint8_t *)malloc(WIDTH * ((HEIGHT + 7) / 8))))
    return false;

  clearDisplay();

  vccstate = vcs;

  i2caddr = addr;

  Wire.begin();

  Wire.setClock(400000UL);

  // Init sequence
  static const uint8_t PROGMEM init1[] = {
    BMC_SSD1306_DISPLAYOFF,                   // 0xAE
    BMC_SSD1306_SETDISPLAYCLOCKDIV,           // 0xD5
    0x80,                                 // the suggested ratio 0x80
    BMC_SSD1306_SETMULTIPLEX };               // 0xA8
  ssd1306_commandList(init1, sizeof(init1));
  ssd1306_command1(HEIGHT - 1);

  static const uint8_t PROGMEM init2[] = {
    BMC_SSD1306_SETDISPLAYOFFSET,             // 0xD3
    0x0,                                  // no offset
    BMC_SSD1306_SETSTARTLINE | 0x0,           // line #0
    BMC_SSD1306_CHARGEPUMP };                 // 0x8D
  ssd1306_commandList(init2, sizeof(init2));

  ssd1306_command1((vccstate == BMC_SSD1306_EXTERNALVCC) ? 0x10 : 0x14);

  static const uint8_t PROGMEM init3[] = {
    BMC_SSD1306_MEMORYMODE,                   // 0x20
    0x00,                                 // 0x0 act like ks0108
    BMC_SSD1306_SEGREMAP | 0x1,
    BMC_SSD1306_COMSCANDEC };
  ssd1306_commandList(init3, sizeof(init3));

  if((WIDTH == 128) && (HEIGHT == 32)) {
    static const uint8_t PROGMEM init4a[] = {
      BMC_SSD1306_SETCOMPINS,                 // 0xDA
      0x02,
      BMC_SSD1306_SETCONTRAST,                // 0x81
      0x8F };
    ssd1306_commandList(init4a, sizeof(init4a));
  } else if((WIDTH == 128) && (HEIGHT == 64)) {
    static const uint8_t PROGMEM init4b[] = {
      BMC_SSD1306_SETCOMPINS,                 // 0xDA
      0x12,
      BMC_SSD1306_SETCONTRAST };              // 0x81
    ssd1306_commandList(init4b, sizeof(init4b));
    ssd1306_command1((vccstate == BMC_SSD1306_EXTERNALVCC) ? 0x9F : 0xCF);
  } else if((WIDTH == 96) && (HEIGHT == 16)) {
    static const uint8_t PROGMEM init4c[] = {
      BMC_SSD1306_SETCOMPINS,                 // 0xDA
      0x2,    // ada x12
      BMC_SSD1306_SETCONTRAST };              // 0x81
    ssd1306_commandList(init4c, sizeof(init4c));
    ssd1306_command1((vccstate == BMC_SSD1306_EXTERNALVCC) ? 0x10 : 0xAF);
  } else {
    // Other screen varieties -- TBD
  }

  ssd1306_command1(BMC_SSD1306_SETPRECHARGE); // 0xd9
  ssd1306_command1((vccstate == BMC_SSD1306_EXTERNALVCC) ? 0x22 : 0xF1);
  static const uint8_t PROGMEM init5[] = {
    BMC_SSD1306_SETVCOMDETECT,               // 0xDB
    0x40,
    BMC_SSD1306_DISPLAYALLON_RESUME,         // 0xA4
    BMC_SSD1306_NORMALDISPLAY,               // 0xA6
    BMC_SSD1306_DEACTIVATE_SCROLL,
    BMC_SSD1306_DISPLAYON };                 // Main screen turn on
  ssd1306_commandList(init5, sizeof(init5));




  return true; // Success
}

// DRAWING FUNCTIONS -------------------------------------------------------

/*!
    @brief  Set/clear/invert a single pixel. This is also invoked by the
            Adafruit_GFX library in generating many higher-level graphics
            primitives.
    @param  x
            Column of display -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @param  color
            Pixel color, one of: BMC_SSD1306_BLACK, BMC_SSD1306_WHITE or BMC_SSD1306_INVERT.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void BMC_SSD1306::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if((x >= 0) && (x < width()) && (y >= 0) && (y < height())) {
    // Pixel is in-bounds. Rotate coordinates if needed.
    switch(getRotation()) {
     case 1:
      ssd1306_swap(x, y);
      x = WIDTH - x - 1;
      break;
     case 2:
      x = WIDTH  - x - 1;
      y = HEIGHT - y - 1;
      break;
     case 3:
      ssd1306_swap(x, y);
      y = HEIGHT - y - 1;
      break;
    }
    switch(color) {
     case BMC_SSD1306_WHITE:   buffer[x + (y/8)*WIDTH] |=  (1 << (y&7)); break;
     case BMC_SSD1306_BLACK:   buffer[x + (y/8)*WIDTH] &= ~(1 << (y&7)); break;
     case BMC_SSD1306_INVERSE: buffer[x + (y/8)*WIDTH] ^=  (1 << (y&7)); break;
    }
  }
}

/*!
    @brief  Clear contents of display buffer (set all pixels to off).
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void BMC_SSD1306::clearDisplay(void) {
  memset(buffer, 0, WIDTH * ((HEIGHT + 7) / 8));
}

/*!
    @brief  Draw a horizontal line. This is also invoked by the Adafruit_GFX
            library in generating many higher-level graphics primitives.
    @param  x
            Leftmost column -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @param  w
            Width of line, in pixels.
    @param  color
            Line color, one of: BMC_SSD1306_BLACK, BMC_SSD1306_WHITE or BMC_SSD1306_INVERT.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void BMC_SSD1306::drawFastHLine(
  int16_t x, int16_t y, int16_t w, uint16_t color) {
  boolean bSwap = false;
  switch(rotation) {
   case 1:
    // 90 degree rotation, swap x & y for rotation, then invert x
    bSwap = true;
    ssd1306_swap(x, y);
    x = WIDTH - x - 1;
    break;
   case 2:
    // 180 degree rotation, invert x and y, then shift y around for height.
    x  = WIDTH  - x - 1;
    y  = HEIGHT - y - 1;
    x -= (w-1);
    break;
   case 3:
    // 270 degree rotation, swap x & y for rotation,
    // then invert y and adjust y for w (not to become h)
    bSwap = true;
    ssd1306_swap(x, y);
    y  = HEIGHT - y - 1;
    y -= (w-1);
    break;
  }

  if(bSwap) drawFastVLineInternal(x, y, w, color);
  else      drawFastHLineInternal(x, y, w, color);
}

void BMC_SSD1306::drawFastHLineInternal(
  int16_t x, int16_t y, int16_t w, uint16_t color) {

  if((y >= 0) && (y < HEIGHT)) { // Y coord in bounds?
    if(x < 0) { // Clip left
      w += x;
      x  = 0;
    }
    if((x + w) > WIDTH) { // Clip right
      w = (WIDTH - x);
    }
    if(w > 0) { // Proceed only if width is positive
      uint8_t *pBuf = &buffer[(y / 8) * WIDTH + x],
               mask = 1 << (y & 7);
      switch(color) {
       case BMC_SSD1306_WHITE:               while(w--) { *pBuf++ |= mask; }; break;
       case BMC_SSD1306_BLACK: mask = ~mask; while(w--) { *pBuf++ &= mask; }; break;
       case BMC_SSD1306_INVERSE:             while(w--) { *pBuf++ ^= mask; }; break;
      }
    }
  }
}

/*!
    @brief  Draw a vertical line. This is also invoked by the Adafruit_GFX
            library in generating many higher-level graphics primitives.
    @param  x
            Column of display -- 0 at left to (screen width -1) at right.
    @param  y
            Topmost row -- 0 at top to (screen height - 1) at bottom.
    @param  h
            Height of line, in pixels.
    @param  color
            Line color, one of: BMC_SSD1306_BLACK, BMC_SSD1306_WHITE or BMC_SSD1306_INVERT.
    @return None (void).
    @note   Changes buffer contents only, no immediate effect on display.
            Follow up with a call to display(), or with other graphics
            commands as needed by one's own application.
*/
void BMC_SSD1306::drawFastVLine(
  int16_t x, int16_t y, int16_t h, uint16_t color) {
  boolean bSwap = false;
  switch(rotation) {
   case 1:
    // 90 degree rotation, swap x & y for rotation,
    // then invert x and adjust x for h (now to become w)
    bSwap = true;
    ssd1306_swap(x, y);
    x  = WIDTH - x - 1;
    x -= (h-1);
    break;
   case 2:
    // 180 degree rotation, invert x and y, then shift y around for height.
    x = WIDTH  - x - 1;
    y = HEIGHT - y - 1;
    y -= (h-1);
    break;
   case 3:
    // 270 degree rotation, swap x & y for rotation, then invert y
    bSwap = true;
    ssd1306_swap(x, y);
    y = HEIGHT - y - 1;
    break;
  }

  if(bSwap) drawFastHLineInternal(x, y, h, color);
  else      drawFastVLineInternal(x, y, h, color);
}

void BMC_SSD1306::drawFastVLineInternal(
  int16_t x, int16_t __y, int16_t __h, uint16_t color) {

  if((x >= 0) && (x < WIDTH)) { // X coord in bounds?
    if(__y < 0) { // Clip top
      __h += __y;
      __y = 0;
    }
    if((__y + __h) > HEIGHT) { // Clip bottom
      __h = (HEIGHT - __y);
    }
    if(__h > 0) { // Proceed only if height is now positive
      // this display doesn't need ints for coordinates,
      // use local byte registers for faster juggling
      uint8_t  y = __y, h = __h;
      uint8_t *pBuf = &buffer[(y / 8) * WIDTH + x];

      // do the first partial byte, if necessary - this requires some masking
      uint8_t mod = (y & 7);
      if(mod) {
        // mask off the high n bits we want to set
        mod = 8 - mod;
        // note - lookup table results in a nearly 10% performance
        // improvement in fill* functions
        // uint8_t mask = ~(0xFF >> mod);
        static const uint8_t PROGMEM premask[8] =
          { 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
        uint8_t mask = pgm_read_byte(&premask[mod]);
        // adjust the mask if we're not going to reach the end of this byte
        if(h < mod) mask &= (0XFF >> (mod - h));

        switch(color) {
         case BMC_SSD1306_WHITE:   *pBuf |=  mask; break;
         case BMC_SSD1306_BLACK:   *pBuf &= ~mask; break;
         case BMC_SSD1306_INVERSE: *pBuf ^=  mask; break;
        }
        pBuf += WIDTH;
      }

      if(h >= mod) { // More to go?
        h -= mod;
        // Write solid bytes while we can - effectively 8 rows at a time
        if(h >= 8) {
          if(color == BMC_SSD1306_INVERSE) {
            // separate copy of the code so we don't impact performance of
            // black/white write version with an extra comparison per loop
            do {
              *pBuf ^= 0xFF;  // Invert byte
              pBuf  += WIDTH; // Advance pointer 8 rows
              h     -= 8;     // Subtract 8 rows from height
            } while(h >= 8);
          } else {
            // store a local value to work with
            uint8_t val = (color != BMC_SSD1306_BLACK) ? 255 : 0;
            do {
              *pBuf = val;    // Set byte
              pBuf += WIDTH;  // Advance pointer 8 rows
              h    -= 8;      // Subtract 8 rows from height
            } while(h >= 8);
          }
        }

        if(h) { // Do the final partial byte, if necessary
          mod = h & 7;
          // this time we want to mask the low bits of the byte,
          // vs the high bits we did above
          // uint8_t mask = (1 << mod) - 1;
          // note - lookup table results in a nearly 10% performance
          // improvement in fill* functions
          static const uint8_t PROGMEM postmask[8] =
            { 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
          uint8_t mask = pgm_read_byte(&postmask[mod]);
          switch(color) {
           case BMC_SSD1306_WHITE:   *pBuf |=  mask; break;
           case BMC_SSD1306_BLACK:   *pBuf &= ~mask; break;
           case BMC_SSD1306_INVERSE: *pBuf ^=  mask; break;
          }
        }
      }
    } // endif positive height
  } // endif x in bounds
}

/*!
    @brief  Return color of a single pixel in display buffer.
    @param  x
            Column of display -- 0 at left to (screen width - 1) at right.
    @param  y
            Row of display -- 0 at top to (screen height -1) at bottom.
    @return true if pixel is set (usually BMC_SSD1306_WHITE, unless display invert mode
            is enabled), false if clear (BMC_SSD1306_BLACK).
    @note   Reads from buffer contents; may not reflect current contents of
            screen if display() has not been called.
*/
boolean BMC_SSD1306::getPixel(int16_t x, int16_t y) {
  if((x >= 0) && (x < width()) && (y >= 0) && (y < height())) {
    // Pixel is in-bounds. Rotate coordinates if needed.
    switch(getRotation()) {
     case 1:
      ssd1306_swap(x, y);
      x = WIDTH - x - 1;
      break;
     case 2:
      x = WIDTH  - x - 1;
      y = HEIGHT - y - 1;
      break;
     case 3:
      ssd1306_swap(x, y);
      y = HEIGHT - y - 1;
      break;
    }
    return (buffer[x + (y / 8) * WIDTH] & (1 << (y & 7)));
  }
  return false; // Pixel out of bounds
}

/*!
    @brief  Get base address of display buffer for direct reading or writing.
    @return Pointer to an unsigned 8-bit array, column-major, columns padded
            to full byte boundary if needed.
*/
uint8_t *BMC_SSD1306::getBuffer(void) {
  return buffer;
}

// REFRESH DISPLAY ---------------------------------------------------------

/*!
    @brief  Push data currently in RAM to SSD1306 display.
    @return None (void).
    @note   Drawing operations are not visible until this function is
            called. Call after each graphics command, or after a whole set
            of graphics commands, as best needed by one's own application.
*/
void BMC_SSD1306::display(void) {

#if !defined(BMC_OLED_DRIVER_SH1106)
  // * for SSD1306
  static const uint8_t PROGMEM dlist1[] = {
    BMC_SSD1306_PAGEADDR,
    0,                         // Layer start address
    0xFF,                      // Layer end (not really, but works here)
    BMC_SSD1306_COLUMNADDR,
    0 };                       // Column start address
  ssd1306_commandList(dlist1, sizeof(dlist1));
  ssd1306_command1(WIDTH - 1); // Column end address

  uint16_t count = WIDTH * ((HEIGHT + 7) / 8);
  uint8_t *ptr   = buffer;

  Wire.beginTransmission(i2caddr);
  Wire.write((uint8_t)0x40);
  uint8_t bytesOut = 1;
  while(count--) {
    if(bytesOut >= WIRE_MAX) {
      Wire.endTransmission();
      Wire.beginTransmission(i2caddr);
      Wire.write((uint8_t)0x40);
      bytesOut = 1;
    }
    Wire.write(*ptr++);
    bytesOut++;
  }
  Wire.endTransmission();

#else

  for(uint8_t page = 0; page < 8; page++) {
    ssd1306_command1(0xB0 + page); // Set page start address
    ssd1306_command1(0x02);        // Lower column address (start at 2)
    ssd1306_command1(0x10);        // Higher column address

    Wire.beginTransmission(i2caddr);
    Wire.write((uint8_t)0x40); // Co = 0, D/C = 1

    uint8_t bytesOut = 1;
    for(uint8_t col = 0; col < 128; col++) {
      if(bytesOut >= WIRE_MAX) {
        Wire.endTransmission();
        Wire.beginTransmission(i2caddr);
        Wire.write((uint8_t)0x40);
        bytesOut = 1;
      }
      Wire.write(buffer[page * 128 + col]);
      bytesOut++;
    }
    Wire.endTransmission();
  }

#endif
}












// SCROLLING FUNCTIONS -----------------------------------------------------

/*!
    @brief  Activate a right-handed scroll for all or part of the display.
    @param  start
            First row.
    @param  stop
            Last row.
    @return None (void).
*/
// To scroll the whole display, run: display.startscrollright(0x00, 0x0F)
void BMC_SSD1306::startscrollright(uint8_t start, uint8_t stop) {
  static const uint8_t PROGMEM scrollList1a[] = {
    BMC_SSD1306_RIGHT_HORIZONTAL_SCROLL,
    0X00 };
  ssd1306_commandList(scrollList1a, sizeof(scrollList1a));
  ssd1306_command1(start);
  ssd1306_command1(0X00);
  ssd1306_command1(stop);
  static const uint8_t PROGMEM scrollList1b[] = {
    0X00,
    0XFF,
    BMC_SSD1306_ACTIVATE_SCROLL };
  ssd1306_commandList(scrollList1b, sizeof(scrollList1b));
}

/*!
    @brief  Activate a left-handed scroll for all or part of the display.
    @param  start
            First row.
    @param  stop
            Last row.
    @return None (void).
*/
// To scroll the whole display, run: display.startscrollleft(0x00, 0x0F)
void BMC_SSD1306::startscrollleft(uint8_t start, uint8_t stop) {
  static const uint8_t PROGMEM scrollList2a[] = {
    BMC_SSD1306_LEFT_HORIZONTAL_SCROLL,
    0X00 };
  ssd1306_commandList(scrollList2a, sizeof(scrollList2a));
  ssd1306_command1(start);
  ssd1306_command1(0X00);
  ssd1306_command1(stop);
  static const uint8_t PROGMEM scrollList2b[] = {
    0X00,
    0XFF,
    BMC_SSD1306_ACTIVATE_SCROLL };
  ssd1306_commandList(scrollList2b, sizeof(scrollList2b));
}

/*!
    @brief  Activate a diagonal scroll for all or part of the display.
    @param  start
            First row.
    @param  stop
            Last row.
    @return None (void).
*/
// display.startscrolldiagright(0x00, 0x0F)
void BMC_SSD1306::startscrolldiagright(uint8_t start, uint8_t stop) {
  static const uint8_t PROGMEM scrollList3a[] = {
    BMC_SSD1306_SET_VERTICAL_SCROLL_AREA,
    0X00 };
  ssd1306_commandList(scrollList3a, sizeof(scrollList3a));
  ssd1306_command1(HEIGHT);
  static const uint8_t PROGMEM scrollList3b[] = {
    BMC_SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL,
    0X00 };
  ssd1306_commandList(scrollList3b, sizeof(scrollList3b));
  ssd1306_command1(start);
  ssd1306_command1(0X00);
  ssd1306_command1(stop);
  static const uint8_t PROGMEM scrollList3c[] = {
    0X01,
    BMC_SSD1306_ACTIVATE_SCROLL };
  ssd1306_commandList(scrollList3c, sizeof(scrollList3c));
}

/*!
    @brief  Activate alternate diagonal scroll for all or part of the display.
    @param  start
            First row.
    @param  stop
            Last row.
    @return None (void).
*/
// To scroll the whole display, run: display.startscrolldiagleft(0x00, 0x0F)
void BMC_SSD1306::startscrolldiagleft(uint8_t start, uint8_t stop) {
  static const uint8_t PROGMEM scrollList4a[] = {
    BMC_SSD1306_SET_VERTICAL_SCROLL_AREA,
    0X00 };
  ssd1306_commandList(scrollList4a, sizeof(scrollList4a));
  ssd1306_command1(HEIGHT);
  static const uint8_t PROGMEM scrollList4b[] = {
    BMC_SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL,
    0X00 };
  ssd1306_commandList(scrollList4b, sizeof(scrollList4b));
  ssd1306_command1(start);
  ssd1306_command1(0X00);
  ssd1306_command1(stop);
  static const uint8_t PROGMEM scrollList4c[] = {
    0X01,
    BMC_SSD1306_ACTIVATE_SCROLL };
  ssd1306_commandList(scrollList4c, sizeof(scrollList4c));
}

/*!
    @brief  Cease a previously-begun scrolling action.
    @return None (void).
*/
void BMC_SSD1306::stopscroll(void) {
  ssd1306_command1(BMC_SSD1306_DEACTIVATE_SCROLL);
}

// OTHER HARDWARE SETTINGS -------------------------------------------------

/*!
    @brief  Enable or disable display invert mode (white-on-black vs
            black-on-white).
    @param  i
            If true, switch to invert mode (black-on-white), else normal
            mode (white-on-black).
    @return None (void).
    @note   This has an immediate effect on the display, no need to call the
            display() function -- buffer contents are not changed, rather a
            different pixel mode of the display hardware is used. When
            enabled, drawing BMC_SSD1306_BLACK (value 0) pixels will actually draw white,
            BMC_SSD1306_WHITE (value 1) will draw black.
*/
void BMC_SSD1306::invertDisplay(boolean i) {
  ssd1306_command1(i ? BMC_SSD1306_INVERTDISPLAY : BMC_SSD1306_NORMALDISPLAY);
}

/*!
    @brief  Dim the display.
    @param  dim
            true to enable lower brightness mode, false for full brightness.
    @return None (void).
    @note   This has an immediate effect on the display, no need to call the
            display() function -- buffer contents are not changed.
*/
void BMC_SSD1306::dim(boolean dim) {
  uint8_t contrast;

  if(dim) {
    contrast = 0; // Dimmed display
  } else {
    contrast = (vccstate == BMC_SSD1306_EXTERNALVCC) ? 0x9F : 0xCF;
  }
  // the range of contrast to too small to be really useful
  // it is useful to dim the display
  ssd1306_command1(BMC_SSD1306_SETCONTRAST);
  ssd1306_command1(contrast);
}
#endif
