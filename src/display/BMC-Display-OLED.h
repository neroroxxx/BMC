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
  // uint8_t w = 0;
  // uint8_t h = 0;
  uint8_t wBound = 0;
  uint8_t hBound = 0;
  int8_t selChar = -1;
  uint16_t meterPixelValue = 0xFFFF;
  uint16_t meterValue = 0xFFFF;
  BMC_SSD1306 display;
  BMC_OLED(uint8_t _w=128, uint8_t _h=BMC_OLED_HEIGHT):display(_w, _h){
    // w = _w;
    // h = _h;
    wBound = _w;
    hBound = _h;
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
    display.setCursor((n < 10) ? 54 : 42, (hBound == 32) ? 34 : 50);
    display.print(n);

    //drawIcon(1);
    display.drawRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
    display.display();

    display.setTextSize(2);
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
  void clear(uint8_t t_settings){
    // settings
    // bit 0 label
    // bit 1 border
    // bit 2 selected
    // bit 3 use name instead of number
    display.clearDisplay();
    if(bitRead(t_settings, 1)){
      display.drawRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
    }
    display.display();
  }
  // BMCDataContainer d
  void printPC(BMCDataContainer d){
    d.type = BMC_MIDI_PROGRAM_CHANGE;
    d.byteC = 0xFF;
    printMIDI(d);
  }
  void printCC(BMCDataContainer d){
    d.type = BMC_MIDI_CONTROL_CHANGE;
    printMIDI(d);
  }
  void printNote(BMCDataContainer d){
    d.type = BMC_MIDI_NOTE_ON;
    printMIDI(d);
  }
  void printMIDI(BMCDataContainer d){
    if(d.highlight){
      display.fillRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
      display.setTextColor(BMC_OLED_BLACK);
    } else {
      display.clearDisplay();
      display.setTextColor(BMC_OLED_WHITE);
    }

    char strChTitle[4] = "CH";
    char strD1Title[4] = "";
    char strD2Title[4] = "";
    char strCH[4] = "";
    char strD1[4] = "";
    char strD2[4] = "";

    d.byteA = constrain(d.byteA, 1, 16);
    d.byteB = constrain(d.byteB, 0, 127);
    sprintf(strCH, "%02u", d.byteA);
    if(d.byteC != 0xFF){
      sprintf(strD1, "%03u", d.byteB);
      d.byteC = constrain(d.byteC, 0, 127);
      sprintf(strD2, "%03u", d.byteC+(d.useOffset ? (uint8_t)d.offset : 0));
    } else {
      sprintf(strD1, "%03u", d.byteB+(d.useOffset ? (uint8_t)d.offset : 0));
    }

    uint16_t t_wBound = 128;
    uint16_t bW = (t_wBound/3);
    uint16_t y1 = (hBound == 32) ? 16 : 28;
    uint16_t y2 = (hBound == 32) ? 34 : 52;

    switch(d.type){
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

    display.setTextSize(2);
    printMidiLabelAndValue(strChTitle, strCH, y1, y2, bW, 0);
    if(d.byteC == 0xFF){
      printMidiLabelAndValue(strD1Title, strD1, y1, y2, bW, bW);
    } else {
      printMidiLabelAndValue(strD1Title, strD1, y1, y2, bW, bW);
      printMidiLabelAndValue(strD2Title, strD2, y1, y2, bW, bW*2);
    }
    display.display();
  }
  
  void printMidiLabelAndValue(char * t_label, char * t_value, uint8_t y1, uint8_t y2, uint16_t bW, uint16_t bW2){
    uint16_t x = bW2 + ((bW - (strlen(t_label)*12)) / 2);
    display.setCursor(x, y1);
    display.println(t_label);
    
    x = bW2 + ((bW - (strlen(t_value)*12)) / 2);
    display.setCursor(x, y2);
    display.println(t_value);
  }
  void print(const char * str, uint8_t t_settings, bool highlight=false){
    // add one extra character for the EOL
    uint8_t len = strlen(str)+1;
    char c[len] = "";
    strncpy(c, str, len);
    print(c, t_settings, highlight);
  }
  void print(char * str, uint8_t t_settings, bool highlight=false){
    
    if(highlight){
      display.fillRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
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
    if(hBound==32 && len <= 10){
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
      if(hBound==32){
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
    if(bitRead(t_settings, 1)){
      display.drawRect(0, 0, wBound, hBound, BMC_OLED_WHITE);
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
    uint8_t textSize  = (hBound == 64) ?  2 :  1;
    uint8_t charH     = 8 * textSize;
    uint8_t x         = hBound==64 ? 5 : 7;
    uint8_t y         = (((hBound - (charH*len))/2)+charH)+textSize;
    if(len>4 || len<2){
      return;
    }
    if(len==0){
      display.fillRect(0, 0, 20, hBound, BMC_OLED_BLACK);
      display.display();
      return;
    }
    display.setTextColor(BMC_OLED_BLACK);
    display.fillRect(0, 0, 20, hBound, BMC_OLED_WHITE);
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
  // drawKnobFace & drawKnobPosition
  // based on code from this sketch:
  // https://github.com/rydepier/Arduino-OLED-Clock/blob/master/Arduino-OLED-Clock%20using%20ADAfruit%20libraries.ino
  void drawKnobFace(uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color, uint16_t t_background){
    display.fillRect(t_x, t_y, t_r, t_r, t_background);
    display.drawCircle(t_x, t_y, t_r-12, t_color);
    uint8_t outterR = 5;
    for(int z = 0 ; z < 360 ; z += 30){
      if(z == 180){
        continue;
      }
      float angle = z;
      angle = (angle / 57.29577951) ;
      int x1 = (t_x + (sin(angle) * (t_r-outterR)));
      int y1 = (t_y - (cos(angle) * (t_r-outterR)));
      display.fillCircle(x1, y1, 1, t_color);
    }
  }
  void drawKnobPositionDot(uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color){
    uint8_t outterR = 19;
    int z = map(t_value, 0, 100, 210, 510);
    // Begin at 0° and stop at 360°
    float angle = z;
    if(z > 360){
      angle = z - 360;
    }
    angle = (angle / 57.29577951) ; //Convert degrees to radians
    int x1 = (t_x + (sin(angle) * (t_r-outterR)));
    int y1 = (t_y - (cos(angle) * (t_r-outterR)));
    display.fillCircle(x1, y1, 2, t_color);
  }
  void drawKnobPositionLine(uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color){
    uint8_t outterR = 18;
    uint8_t innerR = 28;
    int z = map(t_value, 0, 100, 210, 510);
    //Begin at 0° and stop at 360°
    float angle = z;
    if(z > 360){
      angle = z - 360;
    }
    angle = (angle / 57.29577951) ; //Convert degrees to radians
    int x1 = (t_x + (sin(angle) * (t_r-outterR)));
    int y1 = (t_y - (cos(angle) * (t_r-outterR)));
    int x2 = (t_x + (sin(angle) * (t_r-innerR)));
    int y2 = (t_y - (cos(angle) * (t_r-innerR)));

    display.drawLine(x1, y1, x2, y2, t_color);
  }
  void printKnob(BMCDataContainer d){
    uint16_t wPos = d.showLabel()?(wBound/4):(wBound/2);
    uint16_t hPos = hBound/2;
    uint16_t rPos = (hBound/2)-2;
    uint16_t pixelValue = map(d.value, d.min, d.max, 0, 100);
    uint16_t strL      = 0;
    uint16_t blockW    = wBound/2;
    uint16_t txtX      = 0;

    if(d.showLabel()){
      display.setTextSize(2);
      display.setTextWrap(false);
      uint16_t txtY      = strlen(d.label)==0 ? hBound : 40;
      char outStr[32] = "";
      BMCTools::formatKnobValue(d, meterValue, outStr);
      
      strL = (12*strlen(outStr))-2;
      if(strL > blockW){
        txtX = blockW+5;
      } else {
        txtX = blockW + ((blockW - strL)/2);
      }
      display.setTextColor(BMC_OLED_BLACK);
      display.setCursor(txtX, txtY);
      display.print(outStr);

      // display the new value but in the foreground color
      BMCTools::formatKnobValue(d, d.value, outStr);
      strL = (12*strlen(outStr))-2;
      if(strL > blockW){
        txtX = blockW+5;
      } else {
        txtX = blockW + ((blockW - strL)/2);
      }
      
      display.setTextColor(BMC_OLED_WHITE);
      display.setCursor(txtX, txtY);
      display.print(outStr);
    }
    if(meterPixelValue == 0xFFFF){
      if(d.showLabel()){
        uint8_t tPos = 17;
        strL = (12*strlen(d.label))-2;
        if(strL > blockW){
          txtX = blockW+5;
        } else {
          txtX = blockW + ((blockW - strL)/2);
        }
        display.setCursor(txtX, tPos);
        display.print(d.label);
      }
      drawKnobFace(wPos, hPos, rPos, BMC_OLED_WHITE, BMC_OLED_BLACK);
      drawKnobPositionDot(pixelValue, wPos, hPos, rPos, BMC_OLED_WHITE);
      
    } else {
      drawKnobPositionDot(meterPixelValue, wPos, hPos, rPos, BMC_OLED_BLACK);
      drawKnobPositionDot(pixelValue, wPos, hPos, rPos, BMC_OLED_WHITE);
    }
    display.display();
    meterPixelValue = pixelValue;
    meterValue = d.value;
  }
  void drawSwitchRect(uint16_t pos){
    uint16_t pos2 = pos*2;
    display.drawRect(pos, pos, wBound-pos2, hBound-pos2, BMC_OLED_WHITE);
  }
  
  void drawSwitch(uint16_t pos, bool value){
    // hBound = 32;
    uint16_t pos2 = pos*2;
    uint16_t centerX = wBound/2;

    display.setTextSize(2);
    display.setTextWrap(false);
    
    if(!value){
      display.fillRect(centerX, pos, centerX-pos, hBound-pos2, BMC_OLED_BLACK);
      display.fillRect(pos, pos, centerX-pos, hBound-pos2, BMC_OLED_WHITE);
      uint16_t txtX = (pos + ((wBound-pos2)*0.75)) - (18);
      display.setTextColor(BMC_OLED_WHITE);
      display.setCursor(txtX, (hBound/2)+8);
      display.print("OFF");
    } else {
      display.fillRect(pos, pos, centerX-pos, hBound-pos2, BMC_OLED_BLACK);
      display.fillRect(centerX, pos, centerX-pos, hBound-pos2, BMC_OLED_WHITE);

      uint16_t txtX = (pos + ((wBound-pos2)*0.25)) - (12);
      display.setTextColor(BMC_OLED_WHITE);
      display.setCursor(txtX, (hBound/2)+8);
      display.print("ON");
    }
  }
  void printSwitch(BMCDataContainer d){
    // 2 pixel wide box
    // drawSwitchRect(4);
    // drawSwitchRect(5);
    // switch border with 5px padding

    uint16_t pixelValue = d.value == d.max ? 1 : 0;
    uint8_t startPoint = hBound == 64 ? 10 : 0;
    
    if(meterPixelValue == 0xFFFF){
      drawSwitchRect(startPoint);
      drawSwitchRect(startPoint+1);
    }
    if(pixelValue != meterPixelValue){
      drawSwitch(startPoint+2, pixelValue);
    }
    display.display();
    meterPixelValue = pixelValue;
    meterValue = d.value;
  }
  void printSlider(BMCDataContainer d){
    if(d.useOnOffSwitch()){
      printSwitch(d);
      return;
    } else if(hBound == 64){
      printKnob(d);
      return;
    }
    
    // set crc after clear()
    uint8_t padding    = (hBound == 64) ? 4 : 1;
    uint16_t x         = padding;
    uint16_t frameH    = (hBound == 64 ? hBound / 2 : (hBound/2)-4) - padding;
    uint16_t frameW    = wBound - (padding * 2);
    uint16_t frameYC   = (hBound-frameH)/2;
    uint16_t y         = frameYC;
    uint16_t fillH     = frameH-(padding*4);
    uint16_t fillW     = frameW-(padding*4);
    uint16_t txtY      = (hBound == 64) ? 27 : 17;
    uint16_t pixelValue = map(d.value, d.min, d.max, (d.useOffset ? d.offset : 0), fillW);

    display.setTextSize(2);
    display.setTextWrap(false);

    uint16_t txtX = 0;
    char outStr[32] = "";
    // display the last value but in the background color
    sprintf(outStr, "%u", meterValue+(d.useOffset ? d.offset : 0));
    
    txtX = ((wBound - (12*strlen(outStr)))/2);

    display.setTextColor(BMC_OLED_BLACK);
    display.setCursor(txtX, txtY);
    display.print(outStr);

    // display the new value but in the foreground color
    sprintf(outStr, "%u", d.value+(d.useOffset ? d.offset : 0));
    
    txtX = ((wBound - (12*strlen(outStr)))/2);

    display.setTextColor(BMC_OLED_WHITE);
    display.setCursor(txtX, txtY);
    display.print(outStr);
    y = (hBound-frameH)-2;

    uint16_t fillX     = x+(padding*2);
    uint16_t fillY     = y+(padding*2);

    if(meterPixelValue == 0xFFFF){
      display.drawRect(x, y, frameW, frameH, BMC_OLED_WHITE);
      display.fillRect(fillX, fillY, fillW, fillH, BMC_OLED_BLACK);
      display.fillRect(fillX, fillY, pixelValue, fillH, BMC_OLED_WHITE);
    } else if(pixelValue != meterPixelValue){
      if(pixelValue > meterPixelValue){
        display.fillRect(fillX, fillY, pixelValue, fillH, BMC_OLED_WHITE);
      } else {
        display.fillRect(fillX+pixelValue, fillY, fillW-pixelValue, fillH, BMC_OLED_BLACK);
      }
    }
    display.display();

    meterPixelValue = pixelValue;
    meterValue = d.value;
  }








  void drawHorizontalMeter(uint8_t t_value, uint16_t t_w, uint16_t t_min, uint16_t t_max, uint16_t t_x, uint16_t t_y){
    uint16_t width = t_w - 4;
    uint16_t height = 8;
    uint16_t fill = map(t_value, t_min, t_max, 0, width-4);
    display.drawRect(t_x, t_y, width, height, BMC_OLED_WHITE);
    display.drawRect(t_x+1, t_y+1, width-2, height-2, BMC_OLED_BLACK);
    display.drawRect(t_x+2, t_y+2, fill, height-4, BMC_OLED_WHITE);
  }
  void printHorizontalMeter(uint8_t value){
    uint8_t y         = (hBound == 64) ? 10 :  0;
    uint8_t meterH    = (hBound == 64) ? 16 : 12;
    uint8_t textSize  = (hBound == 64) ?  3 :  2;
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
      x = (wBound - (charW * 2)) / 2; // 2 chars + %
    } else if(value < 100){
      x = (wBound - (charW * 3)) / 2; // 3 chars + %
    } else {
      x = (wBound - (charW * 4)) / 2; // 4 chars + %
    }
    char str[5];
    sprintf(str, "%u%%", value);
    display.setCursor(x, 4 + y + meterH + charH);
    display.print(str);
    display.display();
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
    uint8_t textSize = hBound>>3;
    uint8_t charW = 6 * textSize;
    uint8_t xStart = (wBound - charW) / 2;
    display.clearDisplay();
    if(n2 == -1){
      n = constrain(n, 0, (BMC_OLED_ICON_LENGTH-1));
      display.drawChar(xStart, hBound, icon[n], BMC_OLED_WHITE, BMC_OLED_BLACK, textSize);
    } else {
      n = constrain(n, 0, (BMC_OLED_ICON_LENGTH-1));
      n2 = constrain(n2, 0, (BMC_OLED_ICON_LENGTH-1));
      display.drawChar(xStart-(charW/2), hBound, icon[n], BMC_OLED_WHITE, BMC_OLED_BLACK,  textSize);
      display.drawChar(xStart+charW, hBound, icon[n2], BMC_OLED_WHITE, BMC_OLED_BLACK,  textSize);
    }
    if(t_show){
      display.display();
    }
  }
  void renderLine(const char * str, uint8_t lineNumber, uint8_t totalLines, uint8_t start, uint8_t end){
    uint8_t height = hBound / totalLines;
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
    if((hBound==64 && totalLines == 2) || (hBound==32 && totalLines==1)){
      switch(len){
        case 1: case 2: case 3: case 4: case 5: font = 4; break;
        case 6: case 7:                         font = 3; break;
      }
    } else if(hBound==64 && totalLines==1){
      switch(len){
        case 1: case 2:  font = 8; break;
        case 3:          font = 6; break;
        case 4:          font = 5; break;
        case 5:          font = 4; break;
        case 6: case 7:  font = 3; break;
      }
    }

    uint8_t x = (wBound - (((font * 6) * len) - font)) / 2;
    uint8_t y = ceil((height - (font * 7)) / 2.0) + (height * lineNumber) + ((8*font));
    if((hBound==32 && totalLines == 2)){
      y = (lineNumber == 0) ? 16 : 34;
    } else if(totalLines==2){
      if(hBound==32){
        if(lineNumber==0){
          y += font;
        } else {
          y -= font;
        }
      } else {

      }
    }
    display.setTextSize(font);
    display.setCursor(x, y);
    for(uint8_t i = start, e = 0 ; e < len ; i++, e++){
      display.print(str[i]);
      if(selChar>=0 && selChar==i){
        uint16_t fW = 6*font;
        display.fillRect(x+(e*fW), y, fW, 2, BMC_OLED_WHITE);
      }
      if(e >= len){
        break;
      }
    }
  }
};

#endif

#endif
