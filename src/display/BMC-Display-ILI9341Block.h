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
  void setSelChar(uint8_t t_selChar){
    if(t_selChar != selChar){
      crc = 0;
      selChar = t_selChar;
    }
  }
  void reassign(BMC_TFT& tft, uint16_t t_settings, bool highlight=false){
    selChar = -1;
    clear(tft, t_settings, highlight);
  }
  void clear(BMC_TFT& tft, uint16_t t_settings, bool highlight=false){
    settings = t_settings;
    crc = 0;
    // settings
    // bit 0 label
    // bit 1 border
    // bit 2 selected
    // bit 3 use name instead of number
    tft.fillRect(xBound, yBound, wBound, hBound, highlight ? color : background);
    if(bitRead(settings, 1)){
      tft.drawRect(xBound, yBound, wBound, hBound, highlight ? background : color);
    }
  }
  void drawHorizontalMeter(BMC_TFT& tft, uint8_t t_value, uint16_t t_w, uint16_t t_min, uint16_t t_max, uint16_t t_x, uint16_t t_y){
    uint16_t width = t_w - 4;
    uint16_t height = 8;
    uint16_t fill = map(t_value, t_min, t_max, 0, width-4);
    tft.drawRect(t_x, t_y, width, height, color);
    tft.drawRect(t_x+1, t_y+1, width-2, height-2, background);
    tft.drawRect(t_x+2, t_y+2, fill, height-4, color);
  }
  void print(BMC_TFT& tft, uint8_t t_crc, const char* str, const char* label="", bool highlight=false){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(tft, t_crc, c, label, highlight);
  }
  void print(BMC_TFT& tft, uint8_t t_crc, char* str, const char* label="", bool highlight=false){
    if(crc == t_crc){
      return;
    }
    clear(tft, settings, highlight);
    // set crc after clear()
    crc = t_crc;
    BMCTools::strTrimTail(str);
    uint8_t len = strlen(str);
    if(len == 0){
      return;
    }
    
    uint16_t labelYOffset = renderLabel(tft, label, highlight);
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
    tft.setTextColor(highlight ? background : color);
    if(selChar >= 0){
      for(uint8_t i = 0 ; i < strlen(outStr) ; i++){
        if(selChar == i){
          uint16_t c = highlight ? background : color;
          if(background != BMC_ILI9341_YELLOW && color != BMC_ILI9341_YELLOW){
            c = BMC_ILI9341_YELLOW;
          } else if(background != BMC_ILI9341_WHITE && color != BMC_ILI9341_WHITE){
            c = BMC_ILI9341_WHITE;
          } else if(background != BMC_ILI9341_RED && color != BMC_ILI9341_RED){
            c = BMC_ILI9341_RED;
          } else if(background != BMC_ILI9341_GREEN && color != BMC_ILI9341_GREEN){
            c = BMC_ILI9341_GREEN;
          }
          tft.setTextColor(c);
          tft.print(outStr[i]);
          tft.setTextColor(highlight ? background : color);
          continue;
        }
        tft.print(outStr[i]);
      }
    } else {
      tft.print(outStr);
    }
  }
  uint8_t renderLabel(BMC_TFT& tft, const char* t_str, bool highlight=false){
    if(hBound == 40 || !bitRead(settings, 0) || strlen(t_str) == 0){
      return 0;
    }
    char str[strlen(t_str)+1] = "";
    strcpy(str, t_str);
    tft.setFont(Arial_9_Bold);
    
    int16_t x = xBound + ((wBound - tft.strPixelLen(str)) / 2);
    uint16_t y = yBound + 3;
    tft.setCursor(x, y);
    tft.setTextColor(highlight ? background : color);
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
#if defined(BMC_TRIM_DISPLAY_STRINGS)
    uint16_t strWidth = 0;
#endif
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
#if defined(BMC_TRIM_DISPLAY_STRINGS)
      strWidth = tft.strPixelLen(str);
#endif
      if(fontHeight+4+(fontPadding*2) <= maxHeight && tft.strPixelLen(str) < wBound){
        break;
      }
    }
#if defined(BMC_TRIM_DISPLAY_STRINGS)
    if(strWidth > wBound){
      // if it's more than 50% of the string doesn't fit
      // remove all spaces and vowels to shorten string
      if(strWidth > (wBound*2)){
        // BMCTools::strShorten(str, true);
      } else if(strWidth > (wBound*1.5)){
        // BMCTools::strShorten(str);
      }
    }
#endif
    return fontHeight | ((fontPadding*2)<<8);
  }
  void printPC(BMC_TFT& tft, uint8_t t_crc, uint8_t t_ch, uint8_t t_d1, uint8_t t_settings, bool highlight=false){
    printMIDI(tft, t_crc, BMC_MIDI_PROGRAM_CHANGE, t_ch, t_d1, -1, t_settings, highlight);
  }
  void printCC(BMC_TFT& tft, uint8_t t_crc, uint8_t t_ch, uint8_t t_d1, uint8_t t_d2, uint8_t t_settings, bool highlight=false){
    printMIDI(tft, t_crc, BMC_MIDI_CONTROL_CHANGE, t_ch, t_d1, t_d2, t_settings, highlight);
  }
  void printNote(BMC_TFT& tft, uint8_t t_crc, uint8_t t_ch, uint8_t t_d1, uint8_t t_d2, uint8_t t_settings, bool highlight=false){
    printMIDI(tft, t_crc, BMC_MIDI_NOTE_ON, t_ch, t_d1, t_d2, t_settings, highlight);
  }
  void printMIDI(BMC_TFT& tft, uint8_t t_crc, uint8_t t_type, uint8_t t_ch, uint8_t t_d1, int16_t t_d2, uint8_t t_settings, bool highlight=false){
    if(crc == t_crc || wBound < 120){
      return;
    }
    clear(tft, t_settings, highlight);
    tft.setTextColor(highlight ? background : color);
    // set crc after clear()
    crc = t_crc;
    char strChTitle[4] = "CH";
    char strD1Title[4] = "";
    char strD2Title[4] = "";
    char strCH[4] = "";
    char strD1[4] = "";
    char strD2[4] = "";

    t_ch = constrain(t_ch, 1, 16);
    t_d1 = constrain(t_d1, 0, 127);
    sprintf(strCH, "%02u", t_ch);
    sprintf(strD1, "%03u", t_d1);
    if(t_d2 != -1){
      t_d2 = constrain(t_d2, 0, 127);
      sprintf(strD2, "%03u", t_d2);
    }
    // wBound kept at 120 pixels instead of block width
    uint16_t t_wBound = 120;
    uint16_t bW = (t_wBound/3);
    uint16_t y1 = (hBound == 40) ? 2 : 16;
    uint16_t y2 = (hBound == 40) ? 22 : 48;

    switch(t_type){
      case BMC_MIDI_PROGRAM_CHANGE:
        strcpy(strD1Title, "PC");
        bW = (t_wBound/2);
        break;
      case BMC_MIDI_CONTROL_CHANGE:
        strcpy(strD1Title, "CC");
        strcpy(strD2Title, "VAL");
        break;
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
        strcpy(strD1Title, "NO");
        strcpy(strD2Title, "VEL");
        break;
    }
    tft.setFont(BMCLiberationSansNarrow_16);
    printMidiLabelAndValue(tft, strChTitle, strCH, y1, y2, bW, 0);
    if(t_d2 < 0){
      printMidiLabelAndValue(tft, strD1Title, strD1, y1, y2, bW, bW);
    } else {
      printMidiLabelAndValue(tft, strD1Title, strD1, y1, y2, bW, bW);
      printMidiLabelAndValue(tft, strD2Title, strD2, y1, y2, bW, bW*2);
    }
  }
  void printMidiLabelAndValue(BMC_TFT& tft, char * t_label, char * t_value, uint8_t y1, uint8_t y2, uint16_t bW, uint16_t bW2){
    uint16_t centered = wBound-120;
    if(centered > 0){
      centered /= 2; 
    }
    uint16_t x = xBound+bW2 + ((bW - tft.strPixelLen(t_label)) / 2);
    tft.setCursor(centered+x, yBound + y1);
    tft.println(t_label);
    
    x = xBound+bW2 + ((bW - tft.strPixelLen(t_value)) / 2);
    tft.setCursor(centered+x, yBound + y2);
    tft.println(t_value);
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
    int8_t selChar = -1;
};

#endif

#endif
