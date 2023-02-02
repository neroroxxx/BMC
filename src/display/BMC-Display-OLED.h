/*
  This is a wrapper for the Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  it handles up to 2 lines of text, it centers the text and keeps it as large
  as possible, you can use this if you want to use an OLED display to show
  the name of a button/pot/encoder etc.
*/
#ifndef BMC_OLED_H_
#define BMC_OLED_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_OLED > 0

#if !defined(BMC_OLED_HEIGHT)
  #define BMC_OLED_HEIGHT 64
#endif

#if BMC_OLED_HEIGHT !=64 && BMC_OLED_HEIGHT !=32
  #undef BMC_OLED_HEIGHT
  #define BMC_OLED_HEIGHT 64
#endif

#define BMC_OLED_ICON_LENGTH 14

//#include <Adafruit_GFX.h>

//#include "SSD1306.h"

class BMC_OLED {
 public:
  uint8_t w = 0;
  uint8_t h = 0;
  uint8_t maxLines = 3;
  uint8_t xShift = 0;
  uint8_t yShift = 0;
  BMC_SSD1306 display;
  BMC_OLED(uint8_t _w=128, uint8_t _h=BMC_OLED_HEIGHT):display(_w, _h){
    w = _w;
    h = _h;
    maxLines = (h == 64) ? 3 : 2;
  }
  bool begin(uint8_t switchvcc=BMC_SSD1306_SWITCHCAPVCC, uint8_t i2caddr=0, uint8_t rotation=0, uint8_t n=0){
    if(!display.begin(switchvcc, i2caddr)){
      return false;
    }
    display.setFont(&BMCDisplay_Font);
    display.setRotation(rotation);
    display.setTextWrap(false);
    
    display.setTextColor(BMC_OLED_WHITE);
    display.setTextSize(4);
    display.setCursor((n < 10) ? 54 : 42, (h == 32) ? 34 : 50);
    display.print(n);

    //drawIcon(1);
    display.drawRect(0, 0, w, h, BMC_OLED_WHITE);
    display.display();

    display.setTextSize(2);
    return true;
  }
  void setRotation(uint8_t r){
    display.setRotation(r);
  }
  void clear(){
    display.clearDisplay();
    display.display();
  }
  void print(const char * str, uint8_t t_xShift=0, uint8_t t_yShift=0, bool highlight=false){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(c, t_xShift, t_yShift, highlight);
  }
  void print(char * str, uint8_t t_xShift=0, uint8_t t_yShift=0, bool highlight=false){
    xShift = t_xShift;
    yShift = t_yShift;
    
    if(highlight){
      display.fillRect(0, 0, w, h, BMC_OLED_WHITE);
    } else {
      display.clearDisplay();
    }
    
    uint8_t len = strlen(str);
    if(len == 0){
      display.display();
      return;
    }
    uint8_t totalSpaces = 0;
    uint8_t breakPoint = 0;
    int8_t spaceIndex = -1;
    int8_t spaceIndex2 = -1;
    uint8_t lines = 1;

    // first limit the number of characters to print to 20 characters.
    len = (len > 20) ? 20 : len;

    // start by looking for spaces, use the spaces to split a long line in 2

    // figure out how many lines to print
    if(h==32 && len <= 10){
      // on a 128x32 display we keep the maximum font size at 2
      // with that we can fit up to 10 characters in one line
      // if we have a single line and we are using the 128x32 display
      // then we won't bother to split the text into 2 lines using spaces
      lines = 1;
    } else {
      // find out how many spaces the text has and record the first 2 spaces
      for(uint8_t i = 0 ; i < len ; i++){
        if(str[i]==' '){
          if(totalSpaces == 1){
            spaceIndex2 = i;
            totalSpaces = 2;
            break;
          } else {
            spaceIndex = i;
            totalSpaces = 1;
          }
        }
      }
      if(h==32){
        if(totalSpaces == 2){
          uint8_t t1 = len - (spaceIndex+1); // 9
          uint8_t t2 = len - (spaceIndex2+1); // 4
          if(abs(spaceIndex - t1) < abs(spaceIndex2 - t2)){
            breakPoint = spaceIndex;
          } else {
            breakPoint = spaceIndex2;
          }
        } else if(totalSpaces == 1){
          // since we have only 1 space, we'll split the word at that space
          breakPoint = spaceIndex;
        } else if(totalSpaces == 0){
          // if this is a single long word then just split it down the middle
          breakPoint = len / 2;
        }
        spaceIndex = breakPoint;
        lines = 2;
      } else {
        if(spaceIndex >= 0 && len > 7){
          lines = 2;
        } else {
          if(len <= 10 && spaceIndex < 0){
            lines = 1;
          } else if(len > 7 && len <= 10 && spaceIndex >= 0){
            lines = 2;
          } else if(len > 10 && len <= 12){
            lines = 1;
          } else if(len > 12){
            lines = spaceIndex > 0 ? 2 : 3;
          }
        }
      }
    }
    display.setTextColor(highlight ? BMC_OLED_BLACK : BMC_OLED_WHITE);
    display.setTextWrap(false);
    if(lines==3){
      if(len>20){
        renderLine(str, 0, 2, 0, 10);
        renderLine(str, 1, 2, 10, len);
      } else {
        renderLine(str, 0, 2, 0, len/2);
        renderLine(str, 1, 2, len/2, len);
      }
    } else if(lines==2){
      renderLine(str, 0, 2, 0, spaceIndex);
      renderLine(str, 1, 2, (spaceIndex+1), len);
    } else {
      renderLine(str, 0, 1, 0, len);
    }
    display.display();
  }
  void printLeftBox(const char * str){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    printLeftBox(c);
  }
  void printLeftBox(char * str){
    uint8_t len       = strlen(str);
    uint8_t textSize  = (h == 64) ?  2 :  1;
    uint8_t charH     = 8 * textSize;
    uint8_t x         = h==64 ? 5 : 7;
    uint8_t y         = (((h - (charH*len))/2)+charH)+textSize;
    if(len>4 || len<2){
      return;
    }
    if(len==0){
      display.fillRect(0, 0, 20, h, BMC_OLED_BLACK);
      display.display();
      return;
    }
    display.setTextColor(BMC_OLED_BLACK);
    display.fillRect(0, 0, 20, h, BMC_OLED_WHITE);
    display.setTextSize(textSize);
    for(uint8_t i=0;i<len;i++, y += charH){
      display.setCursor(x, y);
      display.print(str[i]);
    }
    display.setTextColor(BMC_OLED_WHITE);
    display.display();
  }
  void printIcon(uint8_t n, int8_t n2=-1){
    drawIcon(n, n2, true);
  }
  void printHorizontalMeter(uint8_t value){
    uint8_t y         = (h == 64) ? 10 :  0;
    uint8_t meterH    = (h == 64) ? 16 : 12;
    uint8_t textSize  = (h == 64) ?  3 :  2;
    uint8_t charW     = 6 * textSize;
    uint8_t charH     = 8 * textSize;
    value = constrain(value, 0, 100);
    display.clearDisplay();
    display.drawRect(10, y, 108, meterH, BMC_OLED_WHITE);
    if(value > 0){
      display.fillRect(14, y+(meterH/4), value, meterH/2, BMC_OLED_WHITE);
    }
    display.setTextColor(BMC_OLED_WHITE);
    display.setTextSize(textSize);
    uint8_t x = 0;
    if(value < 10){
      x = (w - (charW * 2)) / 2; // 2 chars + %
    } else if(value < 100){
      x = (w - (charW * 3)) / 2; // 3 chars + %
    } else {
      x = (w - (charW * 4)) / 2; // 4 chars + %
    }
    char str[5];
    sprintf(str, "%u%%", value);
    display.setCursor(x, 4 + y + meterH + charH);
    display.print(str);
    display.display();
  }
  void printMIDI(bool pc, uint8_t ch, uint8_t value){
    display.fillRect(0, 0, 128, 18, BMC_OLED_WHITE);
    display.setTextColor(BMC_OLED_BLACK);
    display.setTextSize(2);
    char str[11];
    if(pc){
      display.setCursor(5, 18);
      sprintf(str, "PC | CH %02u",ch);
    } else {
      display.setCursor(11, 18);
      sprintf(str, "CC %02u/%03u",ch,value);
    }
    display.print(str);
    display.display();
    display.setTextColor(BMC_OLED_WHITE);
  }

 private:
  const char icon[BMC_OLED_ICON_LENGTH] = {
    0x12,// 0x12 'stop'
    0x13,// 0x13 'check'
    0x14,// 0x14 'menu'
    0x15,// 0x15 'up'
    0x16,// 0x16 'down'
    0x17,// 0x17 'left arrow'
    0x18,// 0x18 'right arrow'
    0x19,// 0x19 'back'
    0x1A,// 0x1A 'enter'
    0x1B,// 0x1B 'record'
    0x1C,// 0x1C 'rewind'
    0x1D,// 0x1D 'fast forward'
    0x1E,// 0x1E 'prev'
    0x1F// 0x1F 'next/play'
  };
  void drawSideBox(){
    display.setTextColor(BMC_OLED_WHITE);
    display.fillRect(0, 0, 17, 64, BMC_OLED_BLACK);
    display.setTextSize(2);
  }

  void drawIcon(uint8_t n, int8_t n2=-1, bool t_show=false){
    uint8_t textSize = h>>3;
    uint8_t charW = 6 * textSize;
    uint8_t xStart = (w - charW) / 2;
    display.clearDisplay();
    if(n2 == -1){
      n = constrain(n, 0, (BMC_OLED_ICON_LENGTH-1));
      display.drawChar(xStart, h, icon[n], BMC_OLED_WHITE, BMC_OLED_BLACK, textSize);
    } else {
      n = constrain(n, 0, (BMC_OLED_ICON_LENGTH-1));
      n2 = constrain(n2, 0, (BMC_OLED_ICON_LENGTH-1));
      display.drawChar(xStart-(charW/2), h, icon[n], BMC_OLED_WHITE, BMC_OLED_BLACK,  textSize);
      display.drawChar(xStart+charW, h, icon[n2], BMC_OLED_WHITE, BMC_OLED_BLACK,  textSize);
    }
    if(t_show){
      display.display();
    }
  }
  void renderLine(const char * str, uint8_t lineNumber, uint8_t totalLines, uint8_t start, uint8_t end){
    uint8_t height = h / totalLines;
    uint8_t font = 2;
    uint8_t len = end - start;
    // trim line
    for(uint8_t i = start, n=(end - start), e = 0 ; e < n ; i++, e++){
      if(str[i] == ' '){
        start++;
        len--;
      } else {
        break;
      }
    }
    len = constrain(len, 0, 10);
    if((h==64 && totalLines == 2) || (h==32 && totalLines==1)){
      switch(len){
        case 1: case 2: case 3: case 4: case 5: font = 4; break;
        case 6: case 7:                         font = 3; break;
      }
    } else if(h==64 && totalLines==1){
      switch(len){
        case 1: case 2:  font = 8; break;
        case 3:          font = 6; break;
        case 4:          font = 5; break;
        case 5:          font = 4; break;
        case 6: case 7:  font = 3; break;
      }
    }

    uint8_t x = (w - (((font * 6) * len) - font)) / 2;
    uint8_t y = ceil((height - (font * 7)) / 2.0) + (height * lineNumber) + ((8*font));
    if((h==32 && totalLines == 2)){
      y = (lineNumber == 0) ? 16 : 34;
    } else if(totalLines==2){
      if(h==32){
        if(lineNumber==0){
          y += font;
        } else {
          y -= font;
        }
      } else {

      }
    }
    //display.drawRect(0, 0, w, h,BMC_OLED_WHITE);
    display.setTextSize(font);
    display.setCursor(x+xShift, y+yShift);
    for(uint8_t i = start, e = 0 ; e < len ; i++, e++){
      display.print(str[i]);
      if(e >= len){
        break;
      }
    }
  }
};

#endif

#endif
