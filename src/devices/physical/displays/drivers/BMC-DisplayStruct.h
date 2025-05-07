#ifndef BMC_DISPLAY_STRUCT_H
#define BMC_DISPLAY_STRUCT_H

struct BMCTextPixelSize {
  int16_t x = 0;
  int16_t y = 0;
  uint16_t w = 0;
  uint16_t h = 0;
};
struct BMCDiplayHandlerData {
  int16_t x = 0;
  int16_t y = 0;
  uint16_t w = 0;
  uint16_t h = 0;
  uint16_t color = 0;
  uint16_t color2 = 0;
  uint16_t color3 = 0;
  uint16_t background = 0;
  bool mirror = false;
  uint8_t colorMode = 1;
  void setBounds(uint16_t t_x, uint16_t t_y, uint16_t t_w, uint16_t t_h){
    x = t_x;
    y = t_y;
    w = t_w;
    h = t_h;
  }
  void setColor(uint16_t t_c){
    color = t_c;
  }
  void setColor(uint16_t t_c1, uint16_t t_c2){
    color = t_c1;
    color2 = t_c2;
  }
  void setColor(uint16_t t_c1, uint16_t t_c2, uint16_t t_c3){
    color = t_c1;
    color2 = t_c2;
    color3 = t_c3;
  }
  void setBackground(uint16_t t_c){
    background = t_c;
  }
};

#define BMC_DEFAULT_DISPLAY_DATA_OLED {0,0,128,BMC_OLED_HEIGHT,BMC_OLED_WHITE,BMC_OLED_WHITE,BMC_OLED_WHITE,BMC_OLED_BLACK,false,1}
#define BMC_DEFAULT_DISPLAY_DATA_ILI {0,0,0,0,BMC_ILI9341_WHITE,BMC_ILI9341_WHITE,BMC_ILI9341_WHITE,BMC_ILI9341_BLACK,false,16}
#define BMC_DEFAULT_DISPLAY_DATA_LCD {0,0,0,0,0,0,0,0,false,1}
#define BMC_DEFAULT_DISPLAY_DATA_MINI_DISPLAY BMC_DEFAULT_DISPLAY_DATA_ILI


#endif