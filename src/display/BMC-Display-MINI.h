/*
  This is a wrapper for the Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  it handles up to 2 lines of text, it centers the text and keeps it as large
  as possible, you can use this if you want to use an OLED display to show
  the name of a button/pot/encoder etc.
*/
#ifndef BMC_MINI_DISPLAY_H_
#define BMC_MINI_DISPLAY_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_MINI_DISPLAY > 0

#define BMC_MD_DRIVER BMC_ST7735_t3

class BMC_MINI_DISPLAY {
 public:
  // uint8_t w = 0;
  // uint8_t h = 0;
  const uint8_t xBound = 0;
  const uint8_t yBound = 0;
  const uint8_t wBound = 128;
  const uint8_t hBound = 128;
  uint8_t settings = 0;
  uint8_t crc = 0;
  uint16_t background = BMC_ILI9341_BLACK;
  uint16_t color = BMC_ILI9341_WHITE;
  int8_t selChar = -1;
  uint16_t meterPixelValue = 0xFFFF;
  uint16_t meterValue = 0xFFFF;
  
  BMC_MD_DRIVER display;
  BMC_MINI_DISPLAY(){
    // wBound = 128;
    // hBound = 128;
    background = BMC_ILI9341_BLACK;
    color = BMC_ILI9341_WHITE;
  }
  bool begin(uint8_t t_cs, uint8_t t_dc, uint8_t t_rst, uint8_t rotation, uint8_t n){
    display.begin(t_cs, t_dc, t_rst);
    display.initR(INITR_144GREENTAB);
    display.setRotation(rotation);
    display.setTextWrap(false);
    display.setTextColor(BMC_ILI9341_YELLOW);

    crc = 1;
    char str[4] = "";
    sprintf(str, "%u", n);
    print(0, str);

    for(int i=0;i<2;i++){
      display.drawRect(i, i, wBound-(i*2), hBound-(i*2), BMC_ILI9341_YELLOW);
    }
    display.setFont(BMC_FONT_SM);
    return true;
  }
  void setRotation(uint8_t r){
    display.setRotation(r);
  }
  int8_t getSelChar(){
    return selChar;
  }
  void setSelChar(uint8_t t_selChar){
    selChar = t_selChar;
  }
  void reassign(uint8_t t_settings){
    selChar = -1;
    meterPixelValue = 0xFFFF;
    meterValue = 0xFFFF;
    clear(t_settings);
  }
  void clear(uint8_t t_settings, bool highlight=false){
    // settings
    // bit 0 label
    // bit 1 border
    // bit 2 selected
    // bit 3 use name instead of number
    settings = t_settings;
    crc = 0;
    display.fillRect(0, 0, wBound, hBound, highlight ? color : background);
    if(bitRead(t_settings, 1)){
      display.drawRect(0, 0, wBound, hBound, highlight ? background : color);
    }
    // display.display();
  }
  void print(uint8_t t_crc, const char* str, const char* label="", bool highlight=false){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(t_crc, c, label, highlight);
  }
  void print(uint8_t t_crc, char* str, const char* label="", bool highlight=false){
    if(crc == t_crc){
      return;
    }
    clear(settings, highlight);
    // set crc after clear()
    crc = t_crc;
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
    uint16_t y = yBound + fontPadding + ((hBound - fontHeight) / 2);

    display.setCursor(x, y);
    display.setTextColor(highlight ? background : color);
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
          display.setTextColor(c);
          display.print(outStr[i]);
          display.setTextColor(highlight ? background : color);
          continue;
        }
        display.print(outStr[i]);
      }
    } else {
      display.print(outStr);
    }
  }
  uint8_t renderLabel(const char* t_str, bool highlight=false){
    if(hBound == 40 || !bitRead(settings, 0) || strlen(t_str) == 0){
      return 0;
    }
    char str[strlen(t_str)+1] = "";
    strcpy(str, t_str);
    display.setFont(BMC_FONT_XS);
    
    int16_t x = xBound + ((wBound - BMC_TFT_STR_LEN(display, str)) / 2);
    uint16_t y = yBound + 4;
    display.setTextColor(highlight ? background : color);
    display.setCursor(x, y);
    display.print(str);
    return 10;
  }

  uint16_t findFontSize(char * str, uint16_t t_labelYOffset, uint16_t _w = 0, uint16_t _h = 0){
    if(_w == 0){
      _w = wBound;
    }
    if(_h == 0){
      _h = hBound;
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
          // if(_h == 40 || blockSize>=8){
          //   display.setFont(BMC_FONT_SM);
          // }
          // break;
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

  // void printCenteredXY(int n, uint16_t t_x=0, uint16_t t_y=0, uint16_t t_w=0xFFFF, uint16_t t_h=0xFFFF, uint8_t t_padding=0, uint16_t t_color=BMC_ILI9341_WHITE){
  //   char str[16] = "";
  //   sprintf(str, "%d", n);
  //   printCenteredXY(str, t_x, t_y, t_w, t_h, t_padding, t_color);
  // }
  // // @str the string to print
  // // @t_x the x position where the text will start
  // // @t_y the y position where the text will start
  // //      these custom fonts set the y position at the bottom of the text
  // // @t_w the width of the area to print in
  // // @t_h the height of the area to print in
  // // @t_padding amount of space that will be removed from @t_h to keep
  // //            the text from printing over that area.
  // void printCenteredXY(const char * str, uint16_t t_x=0, uint16_t t_y=0, uint16_t t_w=0xFFFF, uint16_t t_h=0xFFFF, uint8_t t_padding=0, uint16_t t_color=BMC_ILI9341_WHITE){
  //   t_x = (t_x == 0xFFFF) ? 0 : t_x;
  //   t_y = (t_y == 0xFFFF) ? 0 : t_y;
  //   t_w = (t_w == 0xFFFF) ? wBound : t_w;
  //   t_h = (t_h == 0xFFFF) ? hBound : t_h;

  //   BMCTextPixelSize t;
    
  //   for(int i = 0 ; i < 4 ; i++){
  //     // only 3 font sizes are available
  //     if(i == 0){
  //       if(hBound < 64){
  //         continue;
  //       }
  //       display.setFont(BMC_FONT_XL);
  //     } else if(i == 1){
  //       display.setFont(BMC_FONT_LG);
  //     } else if(i == 2){
  //       display.setFont(BMC_FONT_MD);
  //     } else if(i == 3){
  //       display.setFont(BMC_FONT_SM);
  //     }
  //     // t = display.strPixelSize(str, 0, 0);
      
  //     if((t.w) <= (t_w-t_padding) && ((t.h+(t_padding*2))+((t.y) + (t.h))) <= (t_h-t_padding)){
  //       // BMC_PRINTLN(">>>>>>>>>>>>>>>>>>>>> font", i, "width", t.w, "t.h", (t.h) + ((t.y) + (t.h)));
  //       break;
  //     }
  //   }
  //   t.x = t_x + (((t_w-t.x)-(t.w))/2);
  //   t.y = (t_y + ((t_h) - ((t_h-t.h)/2.0))) - (((t.y) + (t.h)));

  //   // if(t.x < t_x){
  //   //   t.x = t_x;
  //   // }
  //   if(t.y >= (t_h+t_y)){
  //     t.y = t_y + (t_h-1);
  //   }
  //   display.fillRect(t_x, t_y, t_w, t_h, !t_color);
  //   display.setCursor(t.x, t.y);
  //   display.setTextColor(t_color);
  //   display.setTextWrap(false);
  //   display.print(str);
  // }
  // void getTextCenterXY(BMCTextPixelSize &t, const char * str, uint16_t t_x=0xFFFF, uint16_t t_y=0xFFFF, uint16_t t_w=0xFFFF, uint16_t t_h=0xFFFF){
  //   t_x = (t_x == 0xFFFF) ? 0 : t_x;
  //   t_y = (t_y == 0xFFFF) ? 0 : t_y;
  //   t_w = (t_w == 0xFFFF) ? wBound : t_w;
  //   t_h = (t_h == 0xFFFF) ? hBound : t_h;

  //   // t = display.strPixelSize(str);

  //   t.x = (t_w-t.w)/2;
  //   t.y = t_h - ((t_h-t.h)/2);

  //   if(t.x < t_x){
  //     t.x = t_x;
  //   }
  //   if(t.y > t_h){
  //     t.y = t_h;
  //   }
  // }


  // BMCDataContainer d
  // void printPC(BMCDataContainer d){
  //   d.type = BMC_MIDI_PROGRAM_CHANGE;
  //   d.byteC = 0xFF;
  //   printMIDI(d);
  // }
  // void printCC(BMCDataContainer d){
  //   d.type = BMC_MIDI_CONTROL_CHANGE;
  //   printMIDI(d);
  // }
  // void printNote(BMCDataContainer d){
  //   d.type = BMC_MIDI_NOTE_ON;
  //   printMIDI(d);
  // }
  // void printMIDI(BMCDataContainer d){
  //   if(d.highlight){
  //     display.fillRect(0, 0, wBound, hBound, BMC_ILI9341_WHITE);
  //     display.setTextColor(BMC_ILI9341_BLACK);
  //   } else {
  //     display.fillRect(0, 0, wBound, hBound, 0x0000);
  //     display.setTextColor(BMC_ILI9341_WHITE);
  //   }

  //   char strChTitle[4] = "CH";
  //   char strD1Title[4] = "";
  //   char strD2Title[4] = "";
  //   char strCH[4] = "";
  //   char strD1[4] = "";
  //   char strD2[4] = "";

  //   d.byteA = constrain(d.byteA, 1, 16);
  //   d.byteB = constrain(d.byteB, 0, 127);
  //   sprintf(strCH, "%02u", d.byteA);
  //   if(d.byteC != 0xFF){
  //     sprintf(strD1, "%03u", d.byteB);
  //     d.byteC = constrain(d.byteC, 0, 127);
  //     sprintf(strD2, "%03u", d.byteC+(d.useOffset ? (uint8_t)d.offset : 0));
  //   } else {
  //     sprintf(strD1, "%03u", d.byteB+(d.useOffset ? (uint8_t)d.offset : 0));
  //   }

  //   uint16_t t_wBound = 128;
  //   uint16_t bW = (t_wBound/3);
  //   uint16_t y1 = (hBound == 32) ? 16 : 28;
  //   uint16_t y2 = (hBound == 32) ? 34 : 52;

  //   switch(d.type){
  //     case BMC_MIDI_PROGRAM_CHANGE:
  //       strcpy(strD1Title, "PC");
  //       bW = (t_wBound/2);
  //       break;
  //     case BMC_MIDI_CONTROL_CHANGE:
  //       strcpy(strD1Title, "CC");
  //       strcpy(strD2Title, "VAL");
  //       break;
  //     case BMC_MIDI_NOTE_OFF:
  //     case BMC_MIDI_NOTE_ON:
  //       strcpy(strD1Title, "NO");
  //       strcpy(strD2Title, "VEL");
  //       break;
  //   }

  //   display.setTextSize(2);
  //   printMidiLabelAndValue(strChTitle, strCH, y1, y2, bW, 0);
  //   if(d.byteC == 0xFF){
  //     printMidiLabelAndValue(strD1Title, strD1, y1, y2, bW, bW);
  //   } else {
  //     printMidiLabelAndValue(strD1Title, strD1, y1, y2, bW, bW);
  //     printMidiLabelAndValue(strD2Title, strD2, y1, y2, bW, bW*2);
  //   }
  //   // display.display();
  // }
  
  // void printMidiLabelAndValue(char * t_label, char * t_value, uint8_t y1, uint8_t y2, uint16_t bW, uint16_t bW2){
  //   uint16_t x = bW2 + ((bW - (strlen(t_label)*12)) / 2);
  //   display.setCursor(x, y1);
  //   display.println(t_label);
    
  //   x = bW2 + ((bW - (strlen(t_value)*12)) / 2);
  //   display.setCursor(x, y2);
  //   display.println(t_value);
  // }


  // void print(const char * str, uint8_t t_settings, bool highlight=false){
  //   // add one extra character for the EOL
  //   uint8_t len = strlen(str)+1;
  //   char c[len] = "";
  //   strncpy(c, str, len);
  //   print(c, t_settings, highlight);
  // }
  // void print(char * str, uint8_t t_settings, bool highlight=false){
    
  //   if(highlight){
  //     display.fillRect(0, 0, wBound, hBound, BMC_ILI9341_WHITE);
  //   } else {
  //     display.fillRect(0, 0, wBound, hBound, 0x0000);
  //   }
    
  //   uint8_t len = strlen(str);
  //   if(len == 0){
  //     // display.display();
  //     return;
  //   }
  //   // display.setTextColor(highlight ? BMC_ILI9341_BLACK : BMC_ILI9341_WHITE);
  //   // display.setTextWrap(false);

  //   // printCenteredXY(str);
  //   // if(bitRead(t_settings, 1)){
  //   //   display.drawRect(0, 0, wBound, hBound, BMC_ILI9341_WHITE);
  //   // }
  //   // display.display();
  //   // return;

    
  //   uint8_t totalSpaces = 0;
  //   uint8_t breakPoint = 0;
  //   int8_t spaceIndex = -1;
  //   int8_t spaceIndex2 = -1;
  //   uint8_t lines = 1;

  //   // first limit the number of characters to print to 20 characters.
  //   len = (len > 20) ? 20 : len;

  //   // start by looking for spaces, use the spaces to split a long line in 2

  //   // figure out how many lines to print
  //   if(hBound==32 && len <= 10){
  //     // on a 128x32 display we keep the maximum font size at 2
  //     // with that we can fit up to 10 characters in one line
  //     // if we have a single line and we are using the 128x32 display
  //     // then we won't bother to split the text into 2 lines using spaces
  //     lines = 1;
  //   } else {
  //     // find out how many spaces the text has and record the first 2 spaces
  //     for(uint8_t i = 0 ; i < len ; i++){
  //       if(str[i]==' '){
  //         if(totalSpaces == 1){
  //           spaceIndex2 = i;
  //           totalSpaces = 2;
  //           break;
  //         } else {
  //           spaceIndex = i;
  //           totalSpaces = 1;
  //         }
  //       }
  //     }
  //     if(hBound==32){
  //       if(totalSpaces == 2){
  //         uint8_t t1 = len - (spaceIndex+1); // 9
  //         uint8_t t2 = len - (spaceIndex2+1); // 4
  //         if(abs(spaceIndex - t1) < abs(spaceIndex2 - t2)){
  //           breakPoint = spaceIndex;
  //         } else {
  //           breakPoint = spaceIndex2;
  //         }
  //       } else if(totalSpaces == 1){
  //         // since we have only 1 space, we'll split the word at that space
  //         breakPoint = spaceIndex;
  //       } else if(totalSpaces == 0){
  //         // if this is a single long word then just split it down the middle
  //         breakPoint = len / 2;
  //       }
  //       spaceIndex = breakPoint;
  //       lines = 2;
  //     } else {
  //       if(spaceIndex >= 0 && len > 7){
  //         lines = 2;
  //       } else {
  //         if(len <= 10 && spaceIndex < 0){
  //           lines = 1;
  //         } else if(len > 7 && len <= 10 && spaceIndex >= 0){
  //           lines = 2;
  //         } else if(len > 10 && len <= 12){
  //           lines = 1;
  //         } else if(len > 12){
  //           lines = spaceIndex > 0 ? 2 : 3;
  //         }
  //       }
  //     }
  //   }
  //   // display.setTextColor(highlight ? BMC_ILI9341_BLACK : BMC_ILI9341_WHITE);
  //   // display.setTextWrap(false);
  //   if(lines==3){
  //     if(len>20){
  //       renderLine(str, 0, 2, 0, 10, highlight);
  //       renderLine(str, 1, 2, 10, len, highlight);
  //     } else {
  //       renderLine(str, 0, 2, 0, len/2, highlight);
  //       renderLine(str, 1, 2, len/2, len, highlight);
  //     }
  //   } else if(lines==2){
  //     renderLine(str, 0, 2, 0, spaceIndex, highlight);
  //     renderLine(str, 1, 2, (spaceIndex+1), len, highlight);
  //   } else {
  //     renderLine(str, 0, 1, 0, len, highlight);
  //   }
  //   if(bitRead(t_settings, 1)){
  //     display.drawRect(0, 0, wBound, hBound, BMC_ILI9341_WHITE);
  //   }
  //   // display.display();
  // }


  // // drawKnobFace & drawKnobPosition
  // // based on code from this sketch:
  // // https://github.com/rydepier/Arduino-OLED-Clock/blob/master/Arduino-OLED-Clock%20using%20ADAfruit%20libraries.ino
  // void drawKnobFace(uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color, uint16_t t_background){
  //   display.fillRect(t_x, t_y, t_r, t_r, t_background);
  //   display.drawCircle(t_x, t_y, t_r-12, t_color);
  //   uint8_t outterR = 5;
  //   for(int z = 0 ; z < 360 ; z += 30){
  //     if(z == 180){
  //       continue;
  //     }
  //     float angle = z;
  //     angle = (angle / 57.29577951) ;
  //     int x1 = (t_x + (sin(angle) * (t_r-outterR)));
  //     int y1 = (t_y - (cos(angle) * (t_r-outterR)));
  //     display.fillCircle(x1, y1, 1, t_color);
  //   }
  // }
  // void drawKnobPositionDot(uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color){
  //   uint8_t outterR = 19;
  //   int z = map(t_value, 0, 100, 210, 510);
  //   // Begin at 0° and stop at 360°
  //   float angle = z;
  //   if(z > 360){
  //     angle = z - 360;
  //   }
  //   angle = (angle / 57.29577951) ; //Convert degrees to radians
  //   int x1 = (t_x + (sin(angle) * (t_r-outterR)));
  //   int y1 = (t_y - (cos(angle) * (t_r-outterR)));
  //   display.fillCircle(x1, y1, 2, t_color);
  // }
  // void drawKnobPositionLine(uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color){
  //   uint8_t outterR = 18;
  //   uint8_t innerR = 28;
  //   int z = map(t_value, 0, 100, 210, 510);
  //   //Begin at 0° and stop at 360°
  //   float angle = z;
  //   if(z > 360){
  //     angle = z - 360;
  //   }
  //   angle = (angle / 57.29577951) ; //Convert degrees to radians
  //   int x1 = (t_x + (sin(angle) * (t_r-outterR)));
  //   int y1 = (t_y - (cos(angle) * (t_r-outterR)));
  //   int x2 = (t_x + (sin(angle) * (t_r-innerR)));
  //   int y2 = (t_y - (cos(angle) * (t_r-innerR)));

  //   display.drawLine(x1, y1, x2, y2, t_color);
  // }
  // void printKnob(BMCDataContainer d){
  //   uint16_t wPos = d.showLabel()?(wBound/4):(wBound/2);
  //   uint16_t hPos = hBound/2;
  //   uint16_t rPos = (hBound/2)-2;
  //   uint16_t pixelValue = map(d.value, d.min, d.max, 0, 100);
  //   uint16_t strL      = 0;
  //   uint16_t blockW    = wBound/2;
  //   uint16_t txtX      = 0;

  //   if(d.showLabel()){
  //     display.setTextSize(2);
  //     display.setTextWrap(false);
  //     uint16_t txtY      = strlen(d.label)==0 ? hBound : 40;
  //     char outStr[32] = "";
  //     BMCTools::formatKnobValue(d, meterValue, outStr);
      
  //     strL = (12*strlen(outStr))-2;
  //     if(strL > blockW){
  //       txtX = blockW+5;
  //     } else {
  //       txtX = blockW + ((blockW - strL)/2);
  //     }
  //     display.setTextColor(BMC_ILI9341_BLACK);
  //     display.setCursor(txtX, txtY);
  //     display.print(outStr);

  //     // display the new value but in the foreground color
  //     BMCTools::formatKnobValue(d, d.value, outStr);
  //     strL = (12*strlen(outStr))-2;
  //     if(strL > blockW){
  //       txtX = blockW+5;
  //     } else {
  //       txtX = blockW + ((blockW - strL)/2);
  //     }
      
  //     display.setTextColor(BMC_ILI9341_WHITE);
  //     display.setCursor(txtX, txtY);
  //     display.print(outStr);
  //   }
  //   if(meterPixelValue == 0xFFFF){
  //     if(d.showLabel()){
  //       uint8_t tPos = 17;
  //       strL = (12*strlen(d.label))-2;
  //       if(strL > blockW){
  //         txtX = blockW+5;
  //       } else {
  //         txtX = blockW + ((blockW - strL)/2);
  //       }
  //       display.setCursor(txtX, tPos);
  //       display.print(d.label);
  //     }
  //     drawKnobFace(wPos, hPos, rPos, BMC_ILI9341_WHITE, BMC_ILI9341_BLACK);
  //     drawKnobPositionDot(pixelValue, wPos, hPos, rPos, BMC_ILI9341_WHITE);
      
  //   } else {
  //     drawKnobPositionDot(meterPixelValue, wPos, hPos, rPos, BMC_ILI9341_BLACK);
  //     drawKnobPositionDot(pixelValue, wPos, hPos, rPos, BMC_ILI9341_WHITE);
  //   }
  //   // display.display();
  //   meterPixelValue = pixelValue;
  //   meterValue = d.value;
  // }
  // void drawSwitchRect(uint16_t pos){
  //   uint16_t pos2 = pos*2;
  //   display.drawRect(pos, pos, wBound-pos2, hBound-pos2, BMC_ILI9341_WHITE);
  // }
  
  // void drawSwitch(uint16_t pos, bool value){
  //   // hBound = 32;
  //   uint16_t pos2 = pos*2;
  //   uint16_t centerX = wBound/2;

  //   display.setTextSize(2);
  //   display.setTextWrap(false);
    
  //   if(!value){
  //     display.fillRect(centerX, pos, centerX-pos, hBound-pos2, BMC_ILI9341_BLACK);
  //     display.fillRect(pos, pos, centerX-pos, hBound-pos2, BMC_ILI9341_WHITE);
  //     uint16_t txtX = (pos + ((wBound-pos2)*0.75)) - (18);
  //     display.setTextColor(BMC_ILI9341_WHITE);
  //     display.setCursor(txtX, (hBound/2)+8);
  //     display.print("OFF");
  //   } else {
  //     display.fillRect(pos, pos, centerX-pos, hBound-pos2, BMC_ILI9341_BLACK);
  //     display.fillRect(centerX, pos, centerX-pos, hBound-pos2, BMC_ILI9341_WHITE);

  //     uint16_t txtX = (pos + ((wBound-pos2)*0.25)) - (12);
  //     display.setTextColor(BMC_ILI9341_WHITE);
  //     display.setCursor(txtX, (hBound/2)+8);
  //     display.print("ON");
  //   }
  // }
  // void printSwitch(BMCDataContainer d){
  //   // 2 pixel wide box
  //   // drawSwitchRect(4);
  //   // drawSwitchRect(5);
  //   // switch border with 5px padding

  //   uint16_t pixelValue = d.value == d.max ? 1 : 0;
  //   uint8_t startPoint = hBound == 64 ? 10 : 0;
    
  //   if(meterPixelValue == 0xFFFF){
  //     drawSwitchRect(startPoint);
  //     drawSwitchRect(startPoint+1);
  //   }
  //   if(pixelValue != meterPixelValue){
  //     drawSwitch(startPoint+2, pixelValue);
  //   }
  //   // display.display();
  //   meterPixelValue = pixelValue;
  //   meterValue = d.value;
  // }
  // void printSlider(BMCDataContainer d){
  //   if(d.useOnOffSwitch()){
  //     printSwitch(d);
  //     return;
  //   } else if(hBound == 64){
  //     printKnob(d);
  //     return;
  //   }
    
  //   // set crc after clear()
  //   uint8_t padding    = (hBound == 64) ? 4 : 1;
  //   uint16_t x         = padding;
  //   uint16_t frameH    = (hBound == 64 ? hBound / 2 : (hBound/2)-4) - padding;
  //   uint16_t frameW    = wBound - (padding * 2);
  //   uint16_t frameYC   = (hBound-frameH)/2;
  //   uint16_t y         = frameYC;
  //   uint16_t fillH     = frameH-(padding*4);
  //   uint16_t fillW     = frameW-(padding*4);
  //   uint16_t txtY      = (hBound == 64) ? 27 : 17;
  //   uint16_t pixelValue = map(d.value, d.min, d.max, (d.useOffset ? d.offset : 0), fillW);

  //   display.setTextSize(2);
  //   display.setTextWrap(false);

  //   uint16_t txtX = 0;
  //   char outStr[32] = "";
  //   // display the last value but in the background color
  //   sprintf(outStr, "%u", meterValue+(d.useOffset ? d.offset : 0));
    
  //   txtX = ((wBound - (12*strlen(outStr)))/2);

  //   display.setTextColor(BMC_ILI9341_BLACK);
  //   display.setCursor(txtX, txtY);
  //   display.print(outStr);

  //   // display the new value but in the foreground color
  //   sprintf(outStr, "%u", d.value+(d.useOffset ? d.offset : 0));
    
  //   txtX = ((wBound - (12*strlen(outStr)))/2);

  //   display.setTextColor(BMC_ILI9341_WHITE);
  //   display.setCursor(txtX, txtY);
  //   display.print(outStr);
  //   y = (hBound-frameH)-2;

  //   uint16_t fillX     = x+(padding*2);
  //   uint16_t fillY     = y+(padding*2);

  //   if(meterPixelValue == 0xFFFF){
  //     display.drawRect(x, y, frameW, frameH, BMC_ILI9341_WHITE);
  //     display.fillRect(fillX, fillY, fillW, fillH, BMC_ILI9341_BLACK);
  //     display.fillRect(fillX, fillY, pixelValue, fillH, BMC_ILI9341_WHITE);
  //   } else if(pixelValue != meterPixelValue){
  //     if(pixelValue > meterPixelValue){
  //       display.fillRect(fillX, fillY, pixelValue, fillH, BMC_ILI9341_WHITE);
  //     } else {
  //       display.fillRect(fillX+pixelValue, fillY, fillW-pixelValue, fillH, BMC_ILI9341_BLACK);
  //     }
  //   }
  //   // display.display();

  //   meterPixelValue = pixelValue;
  //   meterValue = d.value;
  // }
  uint16_t getX(){
    return 0;
  }
  uint16_t getY(){
    return 0;
  }
  uint16_t getWidth(){
    return wBound;
  }
  uint16_t getHeight(){
    return hBound;
  }
  uint16_t getBackground(){
    return background;
  }
  uint16_t getColor(){
    return color;
  }
  uint16_t getMeterPixelValue(){
    return meterPixelValue;
  }
  uint16_t getMeterValue(){
    return meterValue;
  }
  void setMeterPixelValue(uint16_t t_value){
    meterPixelValue = t_value;
  }
  void setMeterValue(uint16_t t_value){
    meterValue = t_value;
  }
  void setCrc(uint8_t t_crc){
    crc = t_crc;
  }
  bool isCrc(uint8_t t_crc){
    return crc == t_crc;
  }
  void assignColor(uint8_t t_value){
    color = parseColor(t_value);
  }
  void assignBackground(uint8_t t_value){
    background = parseColor(t_value);
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








  // void drawHorizontalMeter(uint8_t t_value, uint16_t t_w, uint16_t t_min, uint16_t t_max, uint16_t t_x, uint16_t t_y){
  //   uint16_t width = t_w - 4;
  //   uint16_t height = 8;
  //   uint16_t fill = map(t_value, t_min, t_max, 0, width-4);
  //   display.drawRect(t_x, t_y, width, height, BMC_ILI9341_WHITE);
  //   display.drawRect(t_x+1, t_y+1, width-2, height-2, BMC_ILI9341_BLACK);
  //   display.drawRect(t_x+2, t_y+2, fill, height-4, BMC_ILI9341_WHITE);
  // }
  // void printHorizontalMeter(uint8_t value){
  //   uint8_t y         = (hBound == 64) ? 10 :  0;
  //   uint8_t meterH    = (hBound == 64) ? 16 : 12;
  //   uint8_t textSize  = (hBound == 64) ?  3 :  2;
  //   uint8_t charW     = 6 * textSize;
  //   uint8_t charH     = 8 * textSize;
  //   value = constrain(value, 0, 100);
  //   display.fillRect(0, 0, wBound, hBound, 0x0000);
  //   display.drawRect(10, y, 108, meterH, BMC_ILI9341_WHITE);
  //   if(value > 0){
  //     display.fillRect(14, y+(meterH/4), value, meterH/2, BMC_ILI9341_WHITE);
  //   }
  //   display.setTextColor(BMC_ILI9341_WHITE);
  //   display.setTextSize(textSize);
  //   uint8_t x = 0;
  //   if(value < 10){
  //     x = (wBound - (charW * 2)) / 2; // 2 chars + %
  //   } else if(value < 100){
  //     x = (wBound - (charW * 3)) / 2; // 3 chars + %
  //   } else {
  //     x = (wBound - (charW * 4)) / 2; // 4 chars + %
  //   }
  //   char str[5];
  //   sprintf(str, "%u%%", value);
  //   display.setCursor(x, 4 + y + meterH + charH);
  //   display.print(str);
  //   // display.display();
  // }

 private:

  // void renderLine(const char * str, uint8_t lineNumber, uint8_t totalLines, uint8_t start, uint8_t end, bool highlight=false){
  //   // uint8_t height = hBound / totalLines;
  //   // uint8_t font = 2;
  //   uint8_t len = end - start;
  //   // trim line
  //   for(uint8_t i = start, n=(end - start), e = 0 ; e < n ; i++, e++){
  //     if(str[i] == ' '){
  //       start++;
  //       len--;
  //     } else {
  //       break;
  //     }
  //   }
  //   len = constrain(len, 0, 10);
  //   char buff[strlen(str)+1] = "";

  //   for(uint8_t i = start, e = 0 ; e < len ; i++, e++){
  //     buff[e] = str[i];
  //     if(e >= len){
  //       break;
  //     }
  //   }
  //   uint16_t yPos = 0;
  //   uint16_t hPos = hBound;


  //   if(totalLines == 2){
  //     hPos = hBound/2;
  //     if(lineNumber == 1){
  //       yPos = hBound/2;
  //     }
      
  //   }

  //   printCenteredXY(buff, 0, yPos, wBound, hPos, 0, highlight ? BMC_ILI9341_BLACK : BMC_ILI9341_WHITE);

  // }
};

#endif

#endif
