/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  This is a wrapper for the Adafruit ILI9341 library
  https://github.com/adafruit/BMC_TFT

  Prints text or built-in icons
*/
#ifndef BMC_ILI_BLOCK_H_
#define BMC_ILI_BLOCK_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_ILI9341_BLOCKS > 0


class BMC_ILI_BLOCK {
 public:
  BMC_ILI_BLOCK(){

  }
  void begin(uint8_t n){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ILI, n);
    xBound = ui.x;
    yBound = ui.y;
    blockSize = ui.style;
    // background = ui.other1;
    // color = ui.other2;

    background = BMC_ILI9341_BLACK;
    color = BMC_ILI9341_WHITE;

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
  void setCrc(uint8_t t_crc){
    crc = t_crc;
  }
  bool isCrc(uint8_t t_crc){
    return crc == t_crc;
  }
  void reassign(BMC_TFT& tft, uint16_t t_settings, bool highlight=false){
    tft.setTextSize(1);
    selChar = -1;
    meterPixelValue = 0xFFFF;
    meterValue = 0xFFFF;
    settings = t_settings;
    // clear(tft, t_settings, highlight);
  }
  void blackout(BMC_TFT& tft){
    crc = 0;
    tft.fillRect(xBound, yBound, wBound, hBound, BMC_ILI9341_BLACK);
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
      // add border
      tft.drawRect(xBound, yBound, wBound, hBound, highlight ? background : color);
      // add a bottom line
      // tft.fillRect(xBound, (yBound+hBound)-2, wBound, 2, highlight ? background : color);
    }
  }

  void print(BMC_TFT& tft, uint8_t t_crc, const char* str, const char* label="", bool highlight=false){
    constexpr size_t MAX_LEN = 255;
    char c[MAX_LEN] = "";
    strncpy(c, str, MAX_LEN-1);
    c[MAX_LEN-1] = 0;
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
    tft.printCenteredXY(str, xBound, yBound, wBound, hBound, 2, highlight?background:color, highlight?color:background);



    // return;
    
    // uint16_t labelYOffset = renderLabel(tft, label, highlight);
    // uint16_t fontData = findFontSize(tft, str, labelYOffset);
    // uint8_t fontHeight = fontData & 0xFF;
    // uint8_t fontPadding = (fontData>>8) & 0xFF;
    
    // len = strlen(str);

    // char outStr[len+1] = "";
    
    // for(uint8_t i = 0 ; i < len ; i++){
    //   outStr[i] = str[i];
    //   uint16_t lineWidth = BMC_TFT_STR_LEN(tft, outStr);
    //   if(lineWidth > wBound){
    //     if(outStr[i] == 32 && i > 0){
    //       outStr[i-1] = 0;
    //     }
    //     outStr[i] = 0;
    //     break;
    //   }
    // }

    // fontHeight += (fontPadding*2);
    // fontPadding += labelYOffset;

    // int16_t x = xBound + ((wBound - BMC_TFT_STR_LEN(tft, outStr)) / 2);
    // uint16_t y = yBound + fontPadding + ((hBound - fontHeight) / 2);

    // tft.setCursor(x, y);
    // tft.setTextColor(highlight ? background : color);
    // if(selChar >= 0){
    //   for(uint8_t i = 0 ; i < strlen(outStr) ; i++){
    //     if(selChar == i){
    //       uint16_t c = highlight ? background : color;
    //       if(background != BMC_ILI9341_YELLOW && color != BMC_ILI9341_YELLOW){
    //         c = BMC_ILI9341_YELLOW;
    //       } else if(background != BMC_ILI9341_WHITE && color != BMC_ILI9341_WHITE){
    //         c = BMC_ILI9341_WHITE;
    //       } else if(background != BMC_ILI9341_RED && color != BMC_ILI9341_RED){
    //         c = BMC_ILI9341_RED;
    //       } else if(background != BMC_ILI9341_GREEN && color != BMC_ILI9341_GREEN){
    //         c = BMC_ILI9341_GREEN;
    //       }
    //       tft.setTextColor(c);
    //       tft.print(outStr[i]);
    //       tft.setTextColor(highlight ? background : color);
    //       continue;
    //     }
    //     tft.print(outStr[i]);
    //   }
    // } else {
    //   tft.print(outStr);
    // }
  }
  uint8_t renderLabel(BMC_TFT& tft, const char* t_str, bool highlight=false){
    if(hBound == 40 || !bitRead(settings, 0) || strlen(t_str) == 0){
      return 0;
    }
    char str[strlen(t_str)+1] = "";
    strcpy(str, t_str);
    tft.setFont(BMC_FONT_XS);
    
    int16_t x = xBound + ((wBound - BMC_TFT_STR_LEN(tft, str)) / 2);
    uint16_t y = yBound + 4;
    tft.setTextColor(highlight ? background : color);
    tft.setCursor(x, y);
    tft.print(str);
    return 10;
  }

  uint16_t findFontSize(BMC_TFT& tft, char * str, uint16_t t_labelYOffset, uint16_t _w = 0, uint16_t _h = 0){
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
        case 0: tft.setFont(BMC_FONT_XXL); break;
        case 1: tft.setFont(BMC_FONT_XL); break;
        case 2: tft.setFont(BMC_FONT_LG); break;
        case 3: tft.setFont(BMC_FONT_MD); break;
        case 4: tft.setFont(BMC_FONT_SM); break;
          // if(_h == 40 || blockSize>=8){
          //   tft.setFont(BMC_FONT_SM);
          // }
          // break;
      }
#if defined(BMC_TRIM_DISPLAY_STRINGS)
      strWidth = BMC_TFT_STR_LEN(tft, str);
#endif
      if(fontHeight+4+(fontPadding*2) <= maxHeight && BMC_TFT_STR_LEN(tft, str) < _w){
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

  uint16_t fitStrInWidth(BMC_TFT& tft, char* buff, uint16_t t_width){
    if(strlen(buff) < 2){
      return BMC_TFT_STR_LEN(tft, buff);
    }
    uint16_t pixLen = 0;
    uint8_t len = strlen(buff)-1;
    for(int i = len; i --> 0; ){
      pixLen = BMC_TFT_STR_LEN(tft, buff);
      if(pixLen > t_width){
        buff[i] = 0;
      } else {
        return pixLen;
      }
    }
    return pixLen;
  }







  // drawKnobFace & drawKnobPosition
  // based on code from this sketch:
  // https://github.com/rydepier/Arduino-OLED-Clock/blob/master/Arduino-OLED-Clock%20using%20ADAfruit%20libraries.ino
  // void drawKnobFace(BMC_TFT& tft, uint16_t t_x, uint16_t t_y, uint16_t t_r){
  //   tft.fillRect(t_x, t_y, t_r, t_r, background);
  //   tft.drawCircle(t_x, t_y, t_r-12, color);
  //   uint8_t outterR = 5;
  //   for(int z = 0 ; z < 360 ; z += 30){
  //     if(z == 180){
  //       continue;
  //     }
  //     float angle = z;
  //     angle = (angle / 57.29577951) ;
  //     int x1 = (t_x + (sin(angle) * (t_r-outterR)));
  //     int y1 = (t_y - (cos(angle) * (t_r-outterR)));
  //     tft.fillCircle(x1, y1, 1, color);
  //   }
  // }
  // void drawKnobPositionDot(BMC_TFT& tft, uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color){
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
  //   tft.fillCircle(x1, y1, 2, t_color);
  // }
  // void drawKnobPositionLine(BMC_TFT& tft, uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color){
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

  //   tft.drawLine(x1, y1, x2, y2, t_color);
  // }
  // void printKnob(BMC_TFT& tft, BMCDataContainer d){
  //   bool showLabel      = d.showLabel() && wBound > 120;
  //   uint16_t wPos       = xBound + (showLabel ? (wBound/4) : (wBound/2));
  //   uint16_t hPos       = yBound + (hBound/2);
  //   uint16_t rPos       = ((hBound/2)-2);
  //   uint16_t pixelValue = map(d.value, d.min, d.max, 0, 100);
  //   uint16_t strL       = 0;
  //   uint16_t blockW     = (wBound/2);
  //   uint16_t txtX       = 0;
    

  //   if(showLabel){
  //     tft.setFont(BMC_FONT_DEFAULT);
  //     tft.setTextWrap(false);
  //     uint16_t txtY      = yBound + (BMC_TFT_STR_LEN(tft, d.label)==0 ? hBound : 40);
  //     char outStr[32] = "";
  //     // display the last value but in the background color

  //     BMCTools::formatKnobValue(d, meterValue, outStr);
  //     strL = fitStrInWidth(tft, outStr, blockW);
  //     if(strL > blockW){
  //       txtX = xBound + blockW+5;
  //     } else {
  //       txtX = xBound + blockW + ((blockW - strL)/2);
  //     }

  //     tft.setTextColor(background);
  //     tft.setCursor(txtX, txtY);
  //     tft.print(outStr);
      
  //     BMCTools::formatKnobValue(d, d.value, outStr);
  //     strL = fitStrInWidth(tft, outStr, blockW);
  //     if(strL > blockW){
  //       txtX = xBound + blockW+5;
  //     } else {
  //       txtX = xBound + blockW + ((blockW - strL)/2);
  //     }
      
  //     tft.setTextColor(color);
  //     tft.setCursor(txtX, txtY);
  //     tft.print(outStr);
  //   }
  //   if(meterPixelValue == 0xFFFF){
  //     if(showLabel){
  //       // strL = BMC_TFT_STR_LEN(tft, d.label);
  //       strL = fitStrInWidth(tft, d.label, blockW);
  //       if(strL > blockW){
  //         txtX = xBound + blockW + 5;
  //       } else {
  //         txtX = xBound + blockW + ((blockW - strL)/2);
  //       }
  //       tft.setCursor(txtX, yBound+17);
  //       tft.print(d.label);
  //     }
  //     drawKnobFace(tft, wPos, hPos, rPos);
  //     drawKnobPositionDot(tft, pixelValue, wPos, hPos, rPos, color);
      
  //   } else {
  //     drawKnobPositionDot(tft, meterPixelValue, wPos, hPos, rPos, background);
  //     drawKnobPositionDot(tft, pixelValue, wPos, hPos, rPos, color);
  //   }
  //   meterPixelValue = pixelValue;
  //   meterValue = d.value;
  // }


  // void drawSwitchRect(BMC_TFT& tft, uint16_t pos){
  //   uint16_t pos2 = pos*2;
  //   tft.drawRect(xBound+pos, yBound+pos, wBound-pos2, hBound-pos2, color);
  // }
  
  // void drawSwitch(BMC_TFT& tft, uint16_t pos, bool value){
  //   // hBound = 32;
  //   uint16_t pos2 = pos*2;
  //   uint16_t centerX = wBound/2;

  //   tft.setFont(BMC_FONT_DEFAULT);
  //   tft.setTextWrap(false);
    
  //   if(!value){
  //     tft.fillRect(xBound+centerX, yBound+pos, centerX-pos, hBound-pos2, background);
  //     tft.fillRect(xBound+pos, yBound+pos, centerX-pos, hBound-pos2, color);
  //     uint16_t txtX = xBound+(pos + ((wBound-pos2)*0.75)) - (18);
  //     tft.setTextColor(color);
  //     tft.setCursor(txtX, yBound+(hBound/2)-8);
  //     tft.print("OFF");
  //   } else {
  //     tft.fillRect(xBound+pos, yBound+pos, centerX-pos, hBound-pos2, background);
  //     tft.fillRect(xBound+centerX, yBound+pos, centerX-pos, hBound-pos2, color);

  //     uint16_t txtX = xBound+(pos + ((wBound-pos2)*0.25)) - (12);
  //     tft.setTextColor(color);
  //     tft.setCursor(txtX, yBound+(hBound/2)-8);
  //     tft.print("ON");
  //   }
  // }
  // void printSwitch(BMC_TFT& tft, BMCDataContainer d){
  //   // 2 pixel wide box
  //   // drawSwitchRect(4);
  //   // drawSwitchRect(5);
  //   // switch border with 5px padding

  //   uint16_t pixelValue = d.value == d.max ? 1 : 0;
  //   uint8_t startPoint = 10;
    
  //   if(meterPixelValue == 0xFFFF){
  //     drawSwitchRect(tft, startPoint);
  //     drawSwitchRect(tft, startPoint+1);
  //   }
  //   if(pixelValue != meterPixelValue){
  //     drawSwitch(tft, startPoint+2, pixelValue);
  //   }
  //   meterPixelValue = pixelValue;
  //   meterValue = d.value;
  // }
  

  
  // void printSlider(BMC_TFT& tft, BMCDataContainer d){
  //   if(crc == d.crc){
  //     return;
  //   }
  //   // set crc after clear()
  //   crc = d.crc;


  //   if(hBound == 80 && wBound >= 80){
  //     if(d.useOnOffSwitch()){
  //       printSwitch(tft, d);
  //     } else {
  //       printKnob(tft, d);
  //     }
  //     return;
  //   }

  //   uint8_t padding    = (hBound == 80) ? 4 : 2;
  //   uint16_t h         = hBound;
  //   uint16_t x         = xBound + padding;
  //   uint16_t frameH    = ((hBound == 80) ? (h / 2) : (h / 3)) - padding;
  //   uint16_t frameW    = wBound - (padding * 2);
  //   uint16_t frameYC   = yBound + ((h-frameH)/2);
  //   uint16_t y         = frameYC;
  //   uint16_t fillH     = frameH-(padding*4);
  //   uint16_t fillW     = frameW-(padding*4);
  //   uint16_t txtY      = (h == 80) ? yBound+10 : yBound+5;
  //   uint16_t pixelValue = map(d.value, d.min, d.max, (d.useOffset ? d.offset : 0), fillW);
  //   bool addLabel = d.showLabel() && wBound > 120;

  //   tft.setFont(BMC_FONT_DEFAULT);

  //   uint16_t txtX = 0;
  //   char outStr[32] = "";
  //   // display the last value but in the background color
  //   sprintf(outStr, "%u", meterValue+(d.useOffset ? d.offset : 0));
    
  //   if(addLabel){
  //     txtX = ((xBound + wBound) - BMC_TFT_STR_LEN(tft, outStr))-padding;
  //   } else {
  //     txtX = xBound + ((wBound - BMC_TFT_STR_LEN(tft, outStr))/2);
  //   }
  //   tft.setTextColor(background);
  //   tft.setCursor(txtX, txtY);
  //   tft.print(outStr);

  //   // display the new value but in the foreground color
  //   sprintf(outStr, "%u", d.value+(d.useOffset ? d.offset : 0));
  //   if(addLabel){
  //     txtX = ((xBound + wBound) - BMC_TFT_STR_LEN(tft, outStr))-padding;
  //   } else {
  //     txtX = xBound + ((wBound - BMC_TFT_STR_LEN(tft, outStr))/2);
  //   }
  //   tft.setTextColor(color);
  //   tft.setCursor(txtX, txtY);
  //   tft.print(outStr);
  //   y = ((yBound+hBound)-frameH)-2;

  //   uint16_t fillX     = x+(padding*2);
  //   uint16_t fillY     = y+(padding*2);

  //   if(meterPixelValue == 0xFFFF){
  //     tft.drawRect(x, y, frameW, frameH, color);
  //     tft.fillRect(fillX, fillY, fillW, fillH, background);
  //     tft.fillRect(fillX, fillY, pixelValue, fillH, color);
  //     if(addLabel){
  //       tft.setTextColor(color);
  //       tft.setCursor(xBound+padding, txtY);
  //       tft.print(d.label);
  //     }
  //   } else if(pixelValue != meterPixelValue){
  //     if(pixelValue > meterPixelValue){
  //       tft.fillRect(fillX, fillY, pixelValue, fillH, color);
  //     } else {
  //       tft.fillRect(fillX+pixelValue, fillY, fillW-pixelValue, fillH, background);
  //     }

  //     // if(pixelValue > meterPixelValue){
  //     //   tft.fillRect(fillX+meterPixelValue, fillY, pixelValue-meterPixelValue, fillH, color);
  //     // } else {
  //     //   tft.fillRect(fillX+pixelValue, fillY, meterPixelValue-pixelValue, fillH, background);
  //     // }
  //   }

  //   meterPixelValue = pixelValue;
  //   meterValue = d.value;
  // }
  
  // void printPC(BMC_TFT& tft, BMCDataContainer d){
  //   if(d.useMeter(wBound >= 120)){
  //     // display dial
  //     printSlider(tft, d);
  //     return;
  //   }
  //   d.byteC = 0xFF;
  //   d.type = BMC_MIDI_PROGRAM_CHANGE;
  //   printMIDI(tft, d);
  // }
  // void printCC(BMC_TFT& tft, BMCDataContainer d){
  //   if(d.useMeter(wBound >= 120)){
  //     // display dial
  //     printSlider(tft, d);
  //     return;
  //   }
  //   d.type = BMC_MIDI_CONTROL_CHANGE;
  //   printMIDI(tft, d);
  // }
  // void printNote(BMC_TFT& tft, BMCDataContainer d){
  //   d.type = BMC_MIDI_NOTE_ON;
  //   printMIDI(tft, d);
  // }
  // void printMIDI(BMC_TFT& tft, BMCDataContainer d){
  //   if(crc == d.crc || wBound < 120){
  //     return;
  //   }
  //   clear(tft, d.settings, d.highlight);
  //   tft.setTextColor(d.highlight ? background : color);
  //   // set crc after clear()
  //   crc = d.crc;
  //   char strChTitle[4] = "CH";
  //   char strD1Title[4] = "";
  //   char strD2Title[4] = "";
  //   char strCH[4] = "";
  //   char strD1[4] = "";
  //   char strD2[4] = "";
  //   uint8_t t_ch = d.byteA;
  //   uint8_t t_d1 = d.byteB;
  //   uint8_t t_d2 = d.byteC;

  //   t_ch = constrain(t_ch, 1, 16);
  //   t_d1 = constrain(t_d1, 0, 127);
  //   sprintf(strCH, "%02u", t_ch);
  //   if(t_d2 != 0xFF){
  //     sprintf(strD1, "%03u", t_d1);
  //     t_d2 = constrain(t_d2, 0, 127);
  //     sprintf(strD2, "%03u", t_d2+(d.useOffset ? (uint8_t)d.offset : 0));
  //   } else {
  //     sprintf(strD1, "%03u", t_d1+(d.useOffset ? (uint8_t)d.offset : 0));
  //   }
  //   // wBound kept at 120 pixels instead of block width
  //   uint16_t t_wBound = 120;
  //   uint16_t bW = (t_wBound/3);
  //   uint16_t y1 = (hBound == 40) ? 2 : 16;
  //   uint16_t y2 = (hBound == 40) ? 22 : 48;

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
  //   tft.setFont(BMC_FONT_DEFAULT);
  //   printMidiLabelAndValue(tft, strChTitle, strCH, y1, y2, bW, 0);
  //   if(t_d2 == 0xFF){
  //     printMidiLabelAndValue(tft, strD1Title, strD1, y1, y2, bW, bW);
  //   } else {
  //     printMidiLabelAndValue(tft, strD1Title, strD1, y1, y2, bW, bW);
  //     printMidiLabelAndValue(tft, strD2Title, strD2, y1, y2, bW, bW*2);
  //   }
  // }
  // void printMidiLabelAndValue(BMC_TFT& tft, char * t_label, char * t_value, uint8_t y1, uint8_t y2, uint16_t bW, uint16_t bW2){
  //   uint16_t centered = wBound-120;
  //   if(centered > 0){
  //     centered /= 2; 
  //   }
  //   uint16_t x = xBound+bW2 + ((bW - BMC_TFT_STR_LEN(tft, t_label)) / 2);
  //   tft.setCursor(centered+x, yBound + y1);
  //   tft.println(t_label);
    
  //   x = xBound+bW2 + ((bW - BMC_TFT_STR_LEN(tft, t_value)) / 2);
  //   tft.setCursor(centered+x, yBound + y2);
  //   tft.println(t_value);
  // }
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
    uint16_t meterPixelValue = 0xFFFF;
    uint16_t meterValue = 0xFFFF;
};

#endif

#endif
