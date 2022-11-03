/*
  This is a wrapper for the Adafruit ILI9341 library
  https://github.com/adafruit/ILI9341_t3

  Prints text or built-in icons
*/
#ifndef BMC_ILI9341_BLOCK_H_
#define BMC_ILI9341_BLOCK_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_ILI9341_BLOCKS > 0

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
      case 0: wBound = 320; hBound = 80; break;
      case 1: wBound = 320; hBound = 40; break;
      case 2: wBound = 256; hBound = 80; break;
      case 3: wBound = 256; hBound = 40; break;
      case 4: wBound = 192; hBound = 80; break;
      case 5: wBound = 192; hBound = 40; break;
      case 6: wBound = 128; hBound = 80; break;
      case 7: wBound = 128; hBound = 40; break;
      case 8: wBound = 96;  hBound = 80; break;
      case 9: wBound = 96;  hBound = 40; break;
      case 10: wBound = 64;  hBound = 80; break;
      case 11: wBound = 64;  hBound = 40; break;
    }
    maxCharsPerLine = (wBound / 12)-1;
  }
  void clear(ILI9341_t3 & tft){
    tft.fillRect(xBound, yBound, wBound, hBound, background);
  }
  void print(ILI9341_t3 & tft, const char * str, uint8_t t_xShift=0, uint8_t t_yShift=0){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(tft, c, t_xShift, t_yShift);
  }
  void print(ILI9341_t3 & tft, char * str, uint8_t t_xShift=0, uint8_t t_yShift=0){
    xShift = t_xShift;
    yShift = t_yShift;
    clear(tft);
    uint8_t len = strlen(str);
    if(len == 0){
      return;
    }
    uint8_t lines = 1;
    //len = len > maxCharsPerLine ? maxCharsPerLine : len;
    if(len > maxCharsPerLine){
      if(hBound==80){
        lines = 2;
      } else {
        len = maxCharsPerLine;
      }
    }
    tft.setTextColor(color);
    tft.setTextWrap(false);
    if(lines == 2){
      renderLine(tft, str, 1, lines, 0, len/2);
      renderLine(tft, str, 2, lines, len/2, len);
    } else {
      renderLine(tft, str, 1, lines, 0, len);
    }
  }
  void printLeftBox(ILI9341_t3 & tft, const char * str){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    printLeftBox(tft, c);
  }
  void printLeftBox(ILI9341_t3 & tft, char * str){
    return;
    uint8_t len       = strlen(str);
    uint8_t textSize  = (hBound == 80) ?  2 :  1;
    uint8_t charH     = 8 * textSize;
    uint8_t x         = hBound==80 ? 5 : 7;
    uint8_t y         = (((hBound - (charH*len))/2)+charH)+textSize;
    if(len>4 || len<2){
      return;
    }
    if(len==0){
      tft.fillRect(xBound, yBound, 20, hBound, background);
      return;
    }
    tft.setTextColor(background);
    tft.fillRect(xBound, yBound, 20, hBound, background);
    tft.setTextSize(textSize);
    for(uint8_t i=0;i<len;i++, y += charH){
      tft.setCursor(xBound+x, yBound+y);
      tft.print(str[i]);
    }
  }
  uint16_t getX(){
    return xBound;
  }
  uint8_t getY(){
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
    uint8_t yBound = 0;
    uint16_t wBound = 0;
    uint8_t hBound = 0;
    uint16_t background = 0;
    uint16_t color = 0;
    uint8_t maxLines = 1;
    uint8_t blockSize = 0;
    uint8_t xShift = 0;
    uint8_t yShift = 0;
    uint8_t maxCharsPerLine = 0;

    void renderLine(ILI9341_t3 & tft, char * str, uint8_t lineNumber, uint8_t totalLines, uint8_t start, uint8_t end){
      uint8_t len = end - start;
      char outStr[len+1];
      memset(outStr, 0, len+1);
      bool trimmed = false;
      uint8_t ee = 0;
      for(uint8_t i = start, e=0, n = len ; e < n ; i++, e++){
        if(!trimmed && str[i]==' '){
          continue;
        }
        trimmed = true;
        outStr[ee++] = str[i];
        if(ee >= n){
          break;
        }
      }
      for(int i = strlen(outStr); i --> 0;){
        if(outStr[i] == ' '){
          outStr[i] = 0;
          continue;
        }
        break;
      }
      len = strlen(outStr);
      uint8_t fontH = 0;
      uint16_t wPixels = 0;
      if(totalLines==1){
        if(len==1){
          if(hBound==40){
            tft.setFont(Arial_20);
            fontH = 25;
          } else {
            tft.setFont(Arial_40);
            fontH = 50; // 40 + (40/4)
          }
        } else if(len==2){
          if(hBound==40){
            tft.setFont(Arial_20);
            fontH = 25;
          } else {
            tft.setFont(Arial_32);
            fontH = 40; // 32 + (32/4)
          }
        } else {
          tft.setFont(Arial_18);
          fontH = 22; // 18 + (18/4)
        }
      } else {
        tft.setFont(Arial_18);
        fontH = 27; // 18 + (18/4)
      }

      wPixels = tft.strPixelLen(outStr);
      uint8_t hPixels = totalLines * fontH;
      uint16_t x = xBound + ((wBound - wPixels) / 2);
      uint8_t  y =  yBound + (((hBound - hPixels)/2) + ((lineNumber-1)*fontH));

      tft.setCursor(x, y);
      tft.print(outStr);
    }

    void renderLine2(ILI9341_t3 & tft, char * str, uint8_t lineNumber, uint8_t totalLines, uint8_t start, uint8_t end){
      uint16_t hBoundLine = hBound / totalLines;
      uint8_t font = 2;
      uint8_t len = end - start;
      char outStr[len+1];
      memset(outStr, 0, len+1);
      bool trimmed = false;
      uint8_t ee = 0;
      for(uint8_t i = start, e=0, n = len ; e < n ; i++, e++){
        if(!trimmed && str[i]==' '){
          continue;
        }
        trimmed = true;
        outStr[ee++] = str[i];
        if(ee >= n){
          break;
        }
      }
      for(int i = strlen(outStr); i --> 0;){
        if(outStr[i] == ' '){
          outStr[i] = 0;
          continue;
        }
        break;
      }
      len = strlen(outStr);
      for(uint8_t i = 2; i < 8 ; i++){
        uint16_t wPixels = len * (6*i);
        if(wPixels >= wBound){
          font = i-1;
          break;
        }
        if((8*i) >= hBoundLine){
          font = i-1;
          break;
        }
        font = i;
      }
      uint16_t wPixels = (len * (6*font)) - font;
      uint16_t x = xBound + ((wBound - wPixels) / 2);
      uint8_t  y = 0;
      uint8_t y0 = (hBound - (((8 * font) * totalLines)-font))/2;
      if(totalLines==2){
        if(lineNumber==1){
          y = yBound+y0;
        } else {
          y = (yBound+(8*font)) + y0;
        }
      } else {
        y = yBound + ((hBound - ((8*font)-font))/2);
      }
      tft.setTextSize(font);
      tft.setCursor(x, y);
      tft.print(outStr);
      /*
      if(totalLines==2 && lineNumber==1){
        tft.setCursor(x, y);
        tft.println(outStr);
      } else if(totalLines==2 && lineNumber==2){
        tft.setCursor(x, tft.getCursorY());
        tft.println(outStr);
      } else {
        tft.setCursor(x, y);
        tft.print(outStr);
      }
      */
    }
};

#endif

#endif
