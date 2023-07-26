/*
  This is a wrapper for the LiquidCrystal_PCF8574 Library
  https://github.com/mathertel/LiquidCrystal_PCF8574

  Prints text
*/
#ifndef BMC_LCD_LINE_H_
#define BMC_LCD_LINE_H_
#include "utility/BMC-Def.h"

#if BMC_MAX_LCD > 0



class BMC_LCD_LINE {
  private:
      uint8_t line = 0;
      uint8_t crc = 0;
  public:
    BMC_LCD_LINE(){

    }
    void begin(uint8_t n){
      line = n;
    }
    void setSelChar(uint8_t t_selChar){
      
    }
    void reassign(BMC_LCD& lcd){
      // selChar = -1;
      // meterPixelValue = 0xFFFF;
      // meterValue = 0xFFFF;
      // clear(lcd, t_settings, highlight);
    }
    void clear(BMC_LCD& lcd){
      crc = 0;
      lcd.print(line, "");
    }
    void blackout(BMC_LCD& lcd){
      crc = 0;
      lcd.print(line, "");
    }
    void setCrc(uint8_t t_crc){
      crc = t_crc;
    }
    bool isCrc(uint8_t t_crc){
      return crc == t_crc;
    }
    void setCursor(BMC_LCD& lcd, uint8_t x){
      lcd.display.setCursor(x, line);
    }
    void print(BMC_LCD& lcd, BMCDataContainer d, const char* str, bool centered=true){
      if(d.crc == crc){
        return;
      }
      crc = d.crc;
      lcd.print(line, str, centered);
    }
    void print(BMC_LCD& lcd, BMCDataContainer d, char* str, bool centered=true){
      if(d.crc == crc){
        return;
      }
      crc = d.crc;
      lcd.print(line, str, centered);
    }
    void printSlider(BMC_LCD& lcd, BMCDataContainer d){
      if(d.crc == crc){
        return;
      }
      crc = d.crc;
      uint8_t x = map(d.value, d.min, d.max, 1, BMC_LCD_CHARS);
      char buff[BMC_LCD_CHARS+1] = ">";
      memset(buff, '=', sizeof(buff[0])*x);
      for(int i = 0, n = BMC_LCD_CHARS-x; i < n ;i++){
        buff[x+i] = ' ';
      }
      lcd.display.setCursor(0, line);
      lcd.display.print(buff);
    }
    uint8_t getLine(){
      return line;
    }
};

#endif

#endif
