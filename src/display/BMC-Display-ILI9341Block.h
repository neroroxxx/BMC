/*
  This is a wrapper for the Adafruit ILI9341 library
  https://github.com/adafruit/BMC_TFT

  Prints text or built-in icons
*/
#ifndef BMC_ILI9341_BLOCK_H_
#define BMC_ILI9341_BLOCK_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_ILI9341_BLOCKS > 0

#define BMC_ILI_FONT BMCLiberationSansNarrow_24
#define BMC_ILI_FONT_MD BMCLiberationSansNarrow_32
#define BMC_ILI_FONT_LG BMCLiberationSansNarrow_40
#define BMC_ILI_FONT_XL BMCLiberationSansNarrow_48

// BMCLiberationMono_24;
// BMCLiberationMono_28;
// BMCLiberationMono_32;
// BMCLiberationMono_40;
// BMCLiberationMono_48;
// BMCLiberationMono_60;
// BMCLiberationMono_72;
// BMCLiberationMono_96;

class BMC_ILI9341_BLOCK {
 public:
  BMC_ILI9341_BLOCK(){

  }
  void begin(uint8_t n){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, n);
    xBound = ui.x;
    yBound = ui.y;
    blockSize = ui.style;
    background = ui.other1;
    color = ui.other2;

    switch(blockSize){
      case 0:
      case 1:
        wBound = BMC_TFT_WIDTH;
        break;
      case 2:
      case 3:
        wBound = BMC_TFT_WIDTH * 0.75;
        break;
      case 4:
      case 5:
        wBound = BMC_TFT_WIDTH * 0.5;
        break;
      case 6:
      case 7:
        wBound = BMC_TFT_WIDTH * 0.25;
        break;
    }
    if(BMC_IS_EVEN(blockSize)){
      hBound = 80;
    } else {
      hBound = 40;
    }
  }
  void clear(BMC_TFT& tft, uint16_t t_settings){
    settings = t_settings;
    crc = 0;
    //BMC_PRINTLN("block settings", settings);
    tft.fillRect(xBound, yBound, wBound, hBound, background);
    if(bitRead(settings, 1)){
      tft.drawRect(xBound, yBound, wBound, hBound, color);
    }
    // tft.drawRect(xBound, yBound, wBound, hBound, color);
  }
  void print(BMC_TFT& tft, uint8_t t_crc, const char* str, const char* label=""){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(tft, t_crc, c, label);
  }
  void print(BMC_TFT& tft, uint8_t t_crc, char* str, const char* label=""){
    if(crc == t_crc){
      return;
    }
    clear(tft, settings);
    // set crc after clear()
    crc = t_crc;
    BMCTools::strTrimTail(str);
    uint8_t len = strlen(str);
    if(len == 0){
      return;
    }
    
    uint16_t labelYOffset = renderLabel(tft, label);
    uint16_t fontData = findFontSize(tft, str, labelYOffset);
    uint8_t fontHeight = fontData & 0xFF;
    uint8_t fontPadding = (fontData>>8) & 0xFF;
    
    len = strlen(str);

    char outStr[len+1] = "";
    
    for(uint8_t i = 0 ; i < len ; i++){
      outStr[i] = str[i];
      uint16_t lineWidth = tft.strPixelLen(outStr);
      if(lineWidth > wBound){
        if(outStr[i] == 32 && i > 0){
          outStr[i-1] = 0;
        }
        outStr[i] = 0;
        break;
      }
    }

    fontHeight += (fontPadding*2);
    fontPadding += labelYOffset;

    int16_t x = xBound + ((wBound - tft.strPixelLen(outStr)) / 2);
    uint16_t y = yBound + fontPadding + ((hBound - fontHeight) / 2);

    tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.print(outStr);
  }
  uint8_t renderLabel(BMC_TFT& tft, const char* t_str){
    if(hBound == 40 || !bitRead(settings, 0) || strlen(t_str) == 0){
      return 0;
    }
    char str[strlen(t_str)] = "";
    strcpy(str, t_str);
    tft.setFont(Arial_9_Bold);
    
    int16_t x = xBound + ((wBound - tft.strPixelLen(str)) / 2);
    uint16_t y = yBound + 3;
    tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.print(str);
    return 10;
  }
  uint16_t findFontSize(BMC_TFT& tft, char * str, uint16_t t_labelYOffset){
    uint8_t fontHeightList[7] = {48, 40, 32, 28, 24, 20, 16};
    // offset for font, this value is added to top and bottom to keep string
    // as centered vertically as possible
    uint8_t fontPaddingList[7] = {12, 12, 8, 8, 6, 6, 4};
    uint8_t fontHeight = 0;
    uint8_t fontPadding = 0;
    uint16_t strWidth = 0;
    uint16_t maxHeight = (hBound - t_labelYOffset);
    for(uint8_t i = 0 ; i < 7 ; i++){
      fontHeight = fontHeightList[i];
      fontPadding = fontPaddingList[i];
      if(fontHeight+4+(fontPadding*2) > maxHeight){
        continue;
      }
      if(i == 0){
        tft.setFont(BMCLiberationSansNarrow_48);
      } else if(i == 1){
        tft.setFont(BMCLiberationSansNarrow_40);
      } else if(i == 2){
        tft.setFont(BMCLiberationSansNarrow_32);
      } else if(i == 3){
        tft.setFont(BMCLiberationSansNarrow_28);
      } else if(i == 4){
        tft.setFont(BMCLiberationSansNarrow_24);
      } else if(i == 5){
        tft.setFont(BMCLiberationSansNarrow_20);
      } else if(i == 6 && (hBound == 40 || blockSize>=8)){
        tft.setFont(BMCLiberationSansNarrow_16);
      } else {
        break;
      }      
      strWidth = tft.strPixelLen(str);
      if(fontHeight+4+(fontPadding*2) <= maxHeight && tft.strPixelLen(str) < wBound){
        break;
      }
    }
    if(strWidth > wBound){
      // if it's more than 50% of the string doesn't fit
      // remove all spaces and vowels to shorten string
      if(strWidth > (wBound*2)){
        // BMCTools::strShorten(str, true);
      } else if(strWidth > (wBound*1.5)){
        // BMCTools::strShorten(str);
      }
    }
    return fontHeight | ((fontPadding*2)<<8);
  }
  uint16_t getX(){
    return xBound;
  }
  uint16_t getY(){
    return yBound;
  }
  uint16_t getWidth(){
    return wBound;
  }
  uint8_t getHeight(){
    return hBound;
  }
  uint16_t getBackground(){
    return background;
  }
  uint16_t getColor(){
    return color;
  }

  private:
    uint16_t xBound = 0;
    uint16_t yBound = 0;
    uint16_t wBound = 0;
    uint8_t hBound = 0;
    uint16_t background = 0;
    uint16_t color = 0;
    uint8_t blockSize = 0;
    uint8_t settings = 0;
    uint8_t crc = 0;
};

#endif

#endif
