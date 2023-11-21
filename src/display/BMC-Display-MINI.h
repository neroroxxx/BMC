/*
  This is a wrapper for the Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  it handles up to 2 lines of text, it centers the text and keeps it as large
  as possible, you can use this if you want to use an OLED display to show
  the name of a button/pot/encoder etc.
*/
#ifndef BMC_MINI_DISPLAY_W_
#define BMC_MINI_DISPLAY_W_
#include "utility/BMC-Def.h"

#if BMC_MAX_MINI_DISPLAY > 0

#define BMC_MD_DRIVER BMC_ST7735_t3


#if defined(BMC_MINI_DISPLAY_188_BLACK)
  #define BMC_MINI_DISPLAY_W    160
  #define BMC_MINI_DISPLAY_INIT INITR_18BLACKTAB

#elif defined(BMC_MINI_DISPLAY_188_GREEN)
  #define BMC_MINI_DISPLAY_W    160
  #define BMC_MINI_DISPLAY_INIT INITR_18GREENTAB

#elif defined(BMC_MINI_DISPLAY_188_RED)
  #define BMC_MINI_DISPLAY_W    160
  #define BMC_MINI_DISPLAY_INIT INITR_18REDTAB

#elif defined(BMC_MINI_DISPLAY_144_RED)
  #define BMC_MINI_DISPLAY_W    128
  #define BMC_MINI_DISPLAY_INIT INITR_144GREENTAB

#else
  #define BMC_MINI_DISPLAY_W    128
  #define BMC_MINI_DISPLAY_INIT INITR_144GREENTAB_OFFSET

#endif

#define BMC_MINI_DISPLAY_H_FULL 128
#if BMC_MAX_MINI_DISPLAY_EVENTS == 1
  #define BMC_MINI_DISPLAY_H 128
#else
  #define BMC_MINI_DISPLAY_H 64
#endif

struct bmcDisplayData {
  uint8_t settings = 0;
  uint8_t crc = 0;
  uint16_t background = BMC_ILI9341_BLACK;
  uint16_t color = BMC_ILI9341_WHITE;
  int8_t selChar = -1;
  uint16_t meterPixelValue = 0xFFFF;
  uint16_t meterValue = 0xFFFF;
};

class BMC_MINI_DISPLAY {
 public:
  // uint8_t w = 0;
  // uint8_t h = 0;
  const uint8_t xBound = 0;
  const uint8_t yBound = 0;
  const uint8_t wBound = BMC_MINI_DISPLAY_W;
  const uint8_t hBound = BMC_MINI_DISPLAY_H;

  bmcDisplayData data[BMC_MAX_MINI_DISPLAY_EVENTS];
  uint8_t lineIndex = 0;
  
  BMC_MD_DRIVER display;
  BMC_MINI_DISPLAY(){
    for(int i=0;i<BMC_MAX_MINI_DISPLAY_EVENTS;i++){
      data[i].background = BMC_ILI9341_BLACK;
      data[i].color = BMC_ILI9341_WHITE;
      data[i].crc = 1;
    }
  }
  bool begin(uint8_t t_cs, uint8_t t_dc, uint8_t t_rst, uint8_t rotation, uint8_t n){
    display.begin(t_cs, t_dc, 11, 13, t_rst);
    display.initR(BMC_MINI_DISPLAY_INIT);
    if(wBound == 160){
      if(rotation == 0){
        rotation = 1;
      } if(rotation == 2){
        rotation = 3;
      }
    }

    display.setRotation(rotation);
    display.setTextWrap(false);
    display.setTextColor(BMC_ILI9341_YELLOW);
    display.fillScreen(BMC_ILI9341_BLACK);

    char str[4] = "";
    sprintf(str, "%u", n);

    for(uint8_t i=0;i<BMC_MAX_MINI_DISPLAY_EVENTS;i++){
      lineIndex = i;
      print(0, str);
      for(int i=0;i<2;i++){
        display.drawRect(i, getY()+i, wBound-(i*2), getHeight()-(i*2), BMC_ILI9341_YELLOW);
      }
    }
    lineIndex = 0;
    display.setFont(BMC_FONT_SM);
    return true;
  }
  void setRotation(uint8_t r){
    display.setRotation(r);
  }
  void reassign(uint8_t t_settings){
    display.setTextSize(1);
    data[lineIndex].selChar = -1;
    data[lineIndex].meterPixelValue = 0xFFFF;
    data[lineIndex].meterValue = 0xFFFF;
    clear(t_settings);
  }
  void blackout(){
    setCrc(0);
    display.fillRect(getX(), getY(), getWidth(), getHeight(), getBackground());
  }
  void clear(uint8_t t_settings, bool highlight=false){
    // settings
    // bit 0 label
    // bit 1 border
    // bit 2 selected
    // bit 3 use name instead of number
    setSettings(t_settings);
    setCrc(0);
    display.fillRect(xBound, getY(), wBound, getHeight(), highlight ? getColor() : getBackground());
    if(bitRead(t_settings, 1)){
      display.drawRect(xBound, getY(), wBound, getHeight(), highlight ? getBackground() : getColor());
    }
  }
  void print(uint8_t t_crc, const char* str, const char* label="", bool highlight=false){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(t_crc, c, label, highlight);
  }
  void print(uint8_t t_crc, char* str, const char* label="", bool highlight=false){
    if(isCrc(t_crc)){
      return;
    }
    clear(getSettings(), highlight);
    // set crc after clear()
    setCrc(t_crc);
    BMCTools::strTrimTail(str);
    uint8_t len = strlen(str);

    if(len == 0){
      return;
    }
    
    uint16_t labelYOffset = renderLabel(label, highlight);
    uint16_t fontData = findFontSize(str, labelYOffset);
    uint8_t fontHeight = fontData & 0xFF;
    uint8_t fontPadding = (fontData>>8) & 0xFF;
    
    len = strlen(str);

    char outStr[len+1] = "";
    
    for(uint8_t i = 0 ; i < len ; i++){
      outStr[i] = str[i];
      uint16_t lineWidth = BMC_TFT_STR_LEN(display, outStr);
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

    int16_t x = xBound + ((wBound - BMC_TFT_STR_LEN(display, outStr)) / 2);
    uint16_t y = getY() + fontPadding + ((getHeight() - fontHeight) / 2);

    display.setCursor(x, y);
    display.setTextColor(highlight ? getBackground() : getColor());
    if(getSelChar() >= 0){
      for(uint8_t i = 0 ; i < strlen(outStr) ; i++){
        if(getSelChar() == i){
          uint16_t c = highlight ? getBackground() : getColor();
          if(getBackground() != BMC_ILI9341_YELLOW && getColor() != BMC_ILI9341_YELLOW){
            c = BMC_ILI9341_YELLOW;
          } else if(getBackground() != BMC_ILI9341_WHITE && getColor() != BMC_ILI9341_WHITE){
            c = BMC_ILI9341_WHITE;
          } else if(getBackground() != BMC_ILI9341_RED && getColor() != BMC_ILI9341_RED){
            c = BMC_ILI9341_RED;
          } else if(getBackground() != BMC_ILI9341_GREEN && getColor() != BMC_ILI9341_GREEN){
            c = BMC_ILI9341_GREEN;
          }
          display.setTextColor(c);
          display.print(outStr[i]);
          display.setTextColor(highlight ? getBackground() : getColor());
          continue;
        }
        display.print(outStr[i]);
      }
    } else {
      display.print(outStr);
    }
  }
  uint8_t renderLabel(const char* t_str, bool highlight=false){
    if(getHeight() == 40 || !bitRead(getSettings(), 0) || strlen(t_str) == 0){
      return 0;
    }
    char str[strlen(t_str)+1] = "";
    strcpy(str, t_str);
    display.setFont(BMC_FONT_XS);
    
    int16_t x = xBound + ((wBound - BMC_TFT_STR_LEN(display, str)) / 2);
    uint16_t y = getY() + 4;
    display.setTextColor(highlight ? getBackground() : getColor());
    display.setCursor(x, y);
    display.print(str);
    return 10;
  }

  uint16_t findFontSize(char * str, uint16_t t_labelYOffset, uint16_t _w = 0, uint16_t _h = 0){
    if(_w == 0){
      _w = wBound;
    }
    if(_h == 0){
      _h = getHeight();
    }
    // estimated font height
    uint8_t fontHeightList[5] = {48, 40, 32, 24, 16};
    // offset for font, this value is added to top and bottom to keep string
    // as centered vertically as possible
    uint8_t fontPaddingList[5] = {12, 12, 8, 6, 4};


    uint8_t fontHeight = 0;
    uint8_t fontPadding = 0;
#if defined(BMC_TRIM_DISPLAY_STRINGS)
    uint16_t strWidth = 0;
#endif
    uint16_t maxHeight = (_h - t_labelYOffset);
    for(uint8_t i = 0 ; i < 5 ; i++){
      fontHeight = fontHeightList[i];
      fontPadding = fontPaddingList[i];
      if(fontHeight+4+(fontPadding*2) > maxHeight){
        continue;
      }
      if(_h == 40 && i == 0){
        continue;
      }
      switch(i){
        case 0: display.setFont(BMC_FONT_XXL); break;
        case 1: display.setFont(BMC_FONT_XL); break;
        case 2: display.setFont(BMC_FONT_LG); break;
        case 3: display.setFont(BMC_FONT_MD); break;
        case 4: display.setFont(BMC_FONT_SM); break;
      }
#if defined(BMC_TRIM_DISPLAY_STRINGS)
      strWidth = BMC_TFT_STR_LEN(display, str);
#endif
      if(fontHeight+4+(fontPadding*2) <= maxHeight && BMC_TFT_STR_LEN(display, str) < _w){
        // BMC_PRINTLN(str, "using", i);
        break;
      }
    }
#if defined(BMC_TRIM_DISPLAY_STRINGS)
    if(strWidth > _w){
      // if it's more than 50% of the string doesn't fit
      // remove all spaces and vowels to shorten string
      if(strWidth > (_w*2)){
        // BMCTools::strShorten(str, true);
      } else if(strWidth > (_w*1.5)){
        // BMCTools::strShorten(str);
      }
    }
#endif
    return fontHeight | ((fontPadding*2)<<8);
  }

  uint16_t fitStrInWidth(char* buff, uint16_t t_width){
    if(strlen(buff) < 2){
      return BMC_TFT_STR_LEN(display, buff);
    }
    uint16_t pixLen = 0;
    uint8_t len = strlen(buff)-1;
    for(int i = len; i --> 0; ){
      pixLen = BMC_TFT_STR_LEN(display, buff);
      if(pixLen > t_width){
        buff[i] = 0;
      } else {
        return pixLen;
      }
    }
    return pixLen;
  }
  int8_t getSelChar(){
    return data[lineIndex].selChar;
  }
  void setSelChar(uint8_t t_selChar){
    data[lineIndex].selChar = t_selChar;
  }
  void setLineIndex(uint8_t n){
    #if BMC_MAX_MINI_DISPLAY_EVENTS == 2
      lineIndex = n & 0x01;
    #else
      lineIndex = 0;
    #endif
  }
  uint8_t getLineIndex(){
    return lineIndex;
  }
  uint8_t getCrc(){
    return data[lineIndex].crc;
  }
  void setCrc(uint8_t t_crc){
    data[lineIndex].crc = t_crc;
  }
  bool isCrc(uint8_t t_crc){
    return data[lineIndex].crc == t_crc;
  }
  uint8_t getSettings(){
    return data[lineIndex].settings;
  }
  void setSettings(uint8_t v){
    data[lineIndex].settings = v;
  }
  uint16_t getX(){
    return 0;
  }
  uint16_t getY(){
    return lineIndex == 0 ? 0 : 64;
  }
  uint16_t getWidth(){
    return wBound;
  }
  uint16_t getHeight(){
    return BMC_MAX_MINI_DISPLAY_EVENTS == 1 ? 128 : 64;
  }
  uint16_t getBackground(){
    return data[lineIndex].background;
  }
  uint16_t getColor(){
    return data[lineIndex].color;
  }
  uint16_t getMeterPixelValue(){
    return data[lineIndex].meterPixelValue;
  }
  uint16_t getMeterValue(){
    return data[lineIndex].meterValue;
  }
  void setMeterPixelValue(uint16_t t_value){
    data[lineIndex].meterPixelValue = t_value;
  }
  void setMeterValue(uint16_t t_value){
    data[lineIndex].meterValue = t_value;
  }
  void assignColor(uint8_t t_value){
    data[lineIndex].color = parseColor(t_value);
  }
  void assignBackground(uint8_t t_value){
    data[lineIndex].background = parseColor(t_value);
  }
  uint16_t parseColor(uint8_t t_value){
    switch(t_value){
      case 0: return BMC_ILI9341_BLACK;
      case 1: return BMC_ILI9341_WHITE;
      case 2: return BMC_ILI9341_NAVY;
      case 3: return BMC_ILI9341_DARKGREEN;
      case 4: return BMC_ILI9341_DARKCYAN;
      case 5: return BMC_ILI9341_MAROON;
      case 6: return BMC_ILI9341_PURPLE;
      case 7: return BMC_ILI9341_OLIVE;
      case 8: return BMC_ILI9341_GRAY;
      case 9: return BMC_ILI9341_ORANGE;
      case 10: return BMC_ILI9341_BLUE;
      case 11: return BMC_ILI9341_GREEN;
      case 12: return BMC_ILI9341_CYAN;
      case 13: return BMC_ILI9341_RED;
      case 14: return BMC_ILI9341_MAGENTA;
      case 15: return BMC_ILI9341_YELLOW;
    }
    return BMC_ILI9341_WHITE;
  }









 private:

};

#endif

#endif
