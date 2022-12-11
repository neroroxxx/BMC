/*
  This is a wrapper for the Adafruit ILI9341 library
  https://github.com/adafruit/ILI9341_t3

  Prints text or built-in icons
*/
#ifndef BMC_ILI9341_H_
#define BMC_ILI9341_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_ILI9341_BLOCKS > 0

#define BMC_ILI_ICON_LENGTH 14


class BMC_ILI9341 {
 public:
  ILI9341_t3 display;
  BMC_ILI9341():display(10, 9){
    
  }
  bool begin(uint8_t rotation=0){
    display.begin();
    display.setRotation(rotation);
    //display.setFont(&BMCDisplay_Font);
    //display.setFont(Arial_24);
    display.setTextWrap(false);
    //display.setTextSize(2);
    //display.setFont(Arial_16);
    display.setTextColor(BMC_ILI9341_WHITE);

    display.fillScreen(BMC_ILI9341_BLACK);
    display.drawRect(0, 0, 320, 240, BMC_ILI9341_WHITE);
    return true;
  }
  void clear(){
    display.fillScreen(BMC_ILI9341_BLACK);
  }
};

#endif

#endif
