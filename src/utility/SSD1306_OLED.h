/*
  This is a wrapper for the Adafruit SSD1306 library
  https://github.com/adafruit/Adafruit_SSD1306

  it handles up to 2 lines of text, it centers the text and keeps it as large
  as possible, you can use this if you want to use an OLED display to show
  the name of a button/pot/encoder etc.
*/
#ifndef BMC_OLED_H_
#define BMC_OLED_H_

#ifdef BMC_USE_OLED
#include "SSD1306.h"

class BMC_OLED {
 public:
  uint8_t w = 0;
  uint8_t h = 0;
  BMC_SSD1306 display;
  BMC_OLED(uint8_t _w, uint8_t _h):display(_w, _h){
    w = _w;
    h = _h;
  }
  bool begin(uint8_t switchvcc=BMC_SSD1306_SWITCHCAPVCC, uint8_t i2caddr=0){
    if(!display.begin(switchvcc, i2caddr)){
      return false;
    }
    display.setTextWrap(false);
    display.setTextSize(2);
    display.setTextColor(BMC_SSD1306_WHITE);
    clear();
    return true;
  }
  void setRotation(uint8_t r){
    display.setRotation(r);
  }
  void clear(){
    display.clearDisplay();
    display.display();
  }
  void print(const char * str){
    char c[strlen(str)];
    strncpy(c, str, strlen(str));
    print(c);
  }
  void print(char * str){
    display.clearDisplay();
    //display.drawRect(0, 0, 128, 64, BMC_SSD1306_WHITE);
    //display.drawLine(0, 32, 128, 32, BMC_SSD1306_WHITE);
    display.setTextColor(BMC_SSD1306_WHITE);
    uint8_t spaceIndex = 0;
    uint8_t lines = 1;
    int len = strlen(str);
    for(uint8_t i = 0 ; i < len ; i++){
      if(str[i]==' '){
        spaceIndex = i;
        break;
      }
    }
    if(spaceIndex > 0 && len > 7){
      lines = 2;
    } else {
      if(len <= 10 && spaceIndex < 0){
        lines = 1;
      } else if(len > 7 && len <= 10 && spaceIndex > 0){
        lines = 2;
      } else if(len > 10 && len <= 12){
        lines = 1;
      } else if(len > 12){
        lines = spaceIndex > 0 ? 2 : 3;
      }
    }
    if(lines==3){
      if(len>20){
        renderLine(str, 0, 2, 0, 10, h/2);
        renderLine(str, 1, 2, 10, len, h/2);
      } else {
        renderLine(str, 0, 2, 0, len/2, h/2);
        renderLine(str, 1, 2, len/2, len, h/2);
      }
    } else if(lines==2){
      renderLine(str, 0, 2, 0, spaceIndex, h/2);
      renderLine(str, 1, 2, (spaceIndex+1), len, h/2);
    } else {
      renderLine(str, 0, 2, 0, len, h);
    }
    display.display();
  }
 private:
   void renderLine(const char * str, uint8_t lineNumber, uint8_t totalLines, uint8_t start, uint8_t end, uint8_t height){
     uint8_t font = 2;
     uint8_t len = end - start;
     len = constrain(len, 0, 10);
     if(len <= 5){
       font = totalLines == 1 ? 4 : 3;
     } else if(len > 5 && len < 8){
       font = 3;
     } else if(len > 7){
       font = 2;
     }

     uint8_t x = (w - (((font * 6) * len) - font)) / 2;
     uint8_t y = ceil((height - (font * 7)) / 2.0) + (height * lineNumber);

     if(totalLines==2){
       if(lineNumber==0){
         y += font;
       } else {
         y -= font;
       }
     }

     display.setTextSize(font);
     display.setCursor(x, y);

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
