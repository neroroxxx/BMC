/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  This is a wrapper for the Adafruit ILI9341 library
  https://github.com/adafruit/ILI9341_t3

  Prints text or built-in icons
*/
#ifndef BMC_ILI_H_
#define BMC_ILI_H_
#include "utility/BMC-Def.h"
#include "SPI.h"

#if BMC_MAX_ILI9341_BLOCKS > 0

#if !defined(BMC_SPLASH_BORDER_COLOR)
  #define BMC_SPLASH_BORDER_COLOR BMC_ILI9341_YELLOW
#endif

#if !defined(BMC_SPLASH_NAME_COLOR)
  #define BMC_SPLASH_NAME_COLOR BMC_ILI9341_YELLOW
#endif

#if !defined(BMC_SPLASH_VERSION_COLOR)
  #define BMC_SPLASH_VERSION_COLOR BMC_ILI9341_GRAY_18
#endif

#if defined(BMC_FOR_ESP32)
  #define USE_HSPI_PORT
#endif

class BMC_ILI {
 public:
  BMC_TFT display;

  BMC_ILI():display(BMC_SPI_PIN_CS, BMC_SPI_PIN_DC, BMC_TFT_RESET_PIN){}

// #if defined(BMC_FOR_TEENSY)
//   BMC_ILI():display(BMC_SPI_PIN_CS, BMC_SPI_PIN_DC, BMC_TFT_RESET_PIN){}
// #else
//   SPIClass spi1;
//   BMC_ILI():spi1(HSPI), display(&spi1, BMC_SPI_PIN_DC, BMC_SPI_PIN_CS, BMC_TFT_RESET_PIN){}
// #endif

  bool begin(uint8_t rotation=0){
    // #if defined(BMC_FOR_ESP32)
    //   spi1.begin(BMC_SPI_PIN_SCK, BMC_SPI_PIN_MISO, BMC_SPI_PIN_MOSI, BMC_SPI_PIN_CS);
    // #endif

    display.begin();
    display.setRotation(rotation);
    display.fillScreen(BMC_ILI9341_BLACK);
    display.setTextWrap(false);
    display.setTextSize(1);
    return true;
  }
  void renderBMCSplashScreen(){
    BMC_PRINTLN(" - Render Splash Screen");

    char buff[40] = BMC_DEVICE_NAME;
    // this is the thickness of the border in pixels
    uint8_t border  = 5;
    // this is the height of the version text area
    uint16_t h2     = 40;

    uint16_t h1     = (BMC_TFT_HEIGHT-(border*3))-h2;
    uint16_t w      = BMC_TFT_WIDTH-(border*2);
    uint16_t y1     = border;
    uint16_t y2     = h1;
    uint16_t x      = border;
    uint16_t borderColor  = BMC_SPLASH_BORDER_COLOR;
    uint16_t nameColor    = BMC_SPLASH_NAME_COLOR;
    uint16_t versionColor = BMC_SPLASH_VERSION_COLOR;

    for(uint8_t i=0;i<border;i++){
      display.drawRect(i, i, BMC_TFT_WIDTH-(i*2), BMC_TFT_HEIGHT-(i*2), borderColor);
    }

    BMCTextPixelSize tt = display.getCenteredXY(buff, x, y1, w, h1, 2);    
    
    display.setTextColor(nameColor);
    display.setCursor(tt.x, tt.y);
    display.print(buff);

    sprintf(buff, "BMC Version %s", BMC_VERSION_STR);
    tt = display.getCenteredXY(buff, x, y2, w, h2, 2);
    display.setTextColor(versionColor);
    display.setCursor(tt.x, tt.y);
    display.print(buff);
  }
  void clear(){
    display.fillRect(0, 0, BMC_TFT_WIDTH, BMC_TFT_HEIGHT, BMC_ILI9341_BLACK);
  }
};

#endif

#endif
