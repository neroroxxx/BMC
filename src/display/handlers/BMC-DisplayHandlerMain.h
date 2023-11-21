/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_DISPLAY_HANDLER_MAIN_H
#define BMC_DISPLAY_HANDLER_MAIN_H
#include "utility/BMC-Def.h"

#if defined(BMC_HAS_DISPLAY)

class BMCDisplayHandlerMain {
public:
  BMCMidi& midi;
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  #if defined(BMC_USE_SYNC)
  BMCSync& sync;
  #endif

  BMCDisplayHandlerMain(BMCMidi& t_midi
  #if defined(BMC_USE_SYNC)
  ,BMCSync& t_sync
  #endif
  ):
    midi(t_midi),
    globals(t_midi.globals),
    store(t_midi.globals.store),
    settings(t_midi.globals.settings)
    #if defined(BMC_USE_SYNC)
    ,sync(t_sync)
    #endif
  {
    
  }
  void begin(){
    reassign();
  }
  void update(){
    
  }
  void reassign(){
    
  }
  #if BMC_MAX_ILI9341_BLOCKS > 0
  bool renderMidiIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d){
    BMC_TFT& display = tft.display;
    if(block.isCrc(d.crc)){
      return false;
    }
    bool t_reset = false;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_ILI;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    // t.setColor(BMC_ILI9341_RED, BMC_ILI9341_GREEN, BMC_ILI9341_WHITE);
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());

    renderMidi<BMC_TFT>(display, d, t, t_reset);

    block.setCrc(d.crc);
    return true;
  }
  bool renderSliderIli(BMC_ILI& tft, BMC_ILI_BLOCK& block, BMCDataContainer d){
    BMC_TFT& display = tft.display;
    if(block.isCrc(d.crc)){
      return false;
    }
    block.setCrc(d.crc);
    bool t_reset = false;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_ILI;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());

    uint16_t meterValue = block.getMeterValue();
    uint16_t meterPixelValue = block.getMeterPixelValue();

    if(t.h >= 64 && t.w >= 120){
      if(d.useOnOffSwitch()){
        renderSwitch<BMC_TFT>(display, meterValue, meterPixelValue, d, t, t_reset);
      } else {
        renderKnob<BMC_TFT>(display, meterValue, meterPixelValue, d, t, t_reset);
      }
      return true;
    }
    renderSlider<BMC_TFT>(display, meterValue, meterPixelValue, d, t, t_reset);
    
    block.setMeterValue(meterValue);
    block.setMeterPixelValue(meterPixelValue);

    
    return true;
  }
  
  #endif




  #if BMC_MAX_OLED > 0
  bool renderMidiOled(BMC_OLED& block, BMCDataContainer d){
    BMC_SSD1306& display = block.display;
    if(block.isCrc(d.crc)){
      return false;
    }
    bool t_reset = false;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_OLED;

    renderMidi<BMC_SSD1306>(display, d, t, t_reset);
    display.display();

    block.setCrc(d.crc);
    return true;
  }
  bool renderSliderOled(BMC_OLED& block, BMCDataContainer d){
    BMC_SSD1306& display = block.display;
    if(block.isCrc(d.crc)){
      return false;
    }
    block.setCrc(d.crc);
    bool t_reset = false;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_OLED;

    uint16_t meterValue = block.getMeterValue();
    uint16_t meterPixelValue = block.getMeterPixelValue();

    
    if(t.h >= 64 && t.w >= 120){
      if(d.useOnOffSwitch()){
        renderSwitch<BMC_SSD1306>(display, meterValue, meterPixelValue, d, t, t_reset);
      } else {
        renderKnob<BMC_SSD1306>(display, meterValue, meterPixelValue, d, t, t_reset);
      }
      return true;
    }
    renderSlider<BMC_SSD1306>(display, meterValue, meterPixelValue, d, t, t_reset);

    display.display();
    
    block.setMeterValue(meterValue);
    block.setMeterPixelValue(meterPixelValue);

    
    return true;
  }
  #endif




  #if BMC_MAX_MINI_DISPLAY > 0
  bool renderMidiMiniDisplay(BMC_MINI_DISPLAY& block, BMCDataContainer d){
    BMC_MD_DRIVER& display = block.display;
    if(block.isCrc(d.crc)){
      return false;
    }
    bool t_reset = false;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_MINI_DISPLAY;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());

    renderMidi<BMC_MD_DRIVER>(display, d, t, t_reset);

    block.setCrc(d.crc);
    return true;
  }
  bool renderSliderMiniDisplay(BMC_MINI_DISPLAY& block, BMCDataContainer d){
    BMC_MD_DRIVER& display = block.display;
    if(block.isCrc(d.crc)){
      return false;
    }
    block.setCrc(d.crc);
    bool t_reset = false;
    BMCDiplayHandlerData t = BMC_DEFAULT_DISPLAY_DATA_MINI_DISPLAY;
    t.setBounds(block.getX(),block.getY(),block.getWidth(),block.getHeight());
    t.setColor(block.getColor());
    t.setBackground(block.getBackground());

    uint16_t meterValue = block.getMeterValue();
    uint16_t meterPixelValue = block.getMeterPixelValue();

    if(t.h >= 64 && t.w >= 120){
      if(d.useOnOffSwitch()){
        renderSwitch<BMC_MD_DRIVER>(display, meterValue, meterPixelValue, d, t, t_reset);
      } else {
        renderKnob<BMC_MD_DRIVER>(display, meterValue, meterPixelValue, d, t, t_reset);
      }
      return true;
    }
    renderSlider<BMC_MD_DRIVER>(display, meterValue, meterPixelValue, d, t, t_reset);
    block.setMeterValue(meterValue);
    block.setMeterPixelValue(meterPixelValue);
    
    return true;
  }
  #endif




  #if BMC_MAX_LCD > 0

  #endif



  template <typename T>
  bool renderMidi(T& display, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset=false){
    uint8_t maxLines = ((t.h/3) >= 16) ? 3 : 2;
    uint8_t lineHeight = (t.h / maxLines);
    uint8_t totalLines = 2;
    // uint8_t halfH = t.h/2;
    uint8_t fontSize = maxLines == 2 ? 1 : 2;
    uint8_t fontWidth = (fontSize*6);
    uint8_t fontHeight = (fontSize*8);
    char type[6] = "";
    switch(d.type){
      case BMC_MIDI_PROGRAM_CHANGE:
        totalLines = 2;
        strcpy(type, "PC");
        break;
      case BMC_MIDI_CONTROL_CHANGE:
        totalLines = 3;
        strcpy(type, "CC");
        break;
      case BMC_MIDI_NOTE_ON:
        totalLines = 3;
        strcpy(type, "NN");
        break;
    }
    // invert the colors for the header
    display.fillRect(t.x, t.y, t.w, t.h, t.background);
    display.fillRect(t.x, t.y, t.w, lineHeight, t.color);
    display.drawRect(t.x, t.y, t.w, t.h, t.color);
    display.setFont();
    display.setTextSize(fontSize);
    // invert the colors for the header
    display.setTextColor(t.background);
    char buff[16] = "";
    sprintf(buff, "Ch %02u", d.getChannel());

    int cX = (t.w-(fontWidth*strlen(buff)))/2;
    
    display.setCursor(t.x+((cX < 0) ? 0 : cX), t.y + ((lineHeight-fontHeight)/2));
    display.print(buff);
    
    display.setTextColor(t.color);
    if(totalLines > maxLines){
      fontSize = 1;
      fontWidth = 6;
      fontHeight = 8;
      display.setTextSize(fontSize);

      sprintf(buff, "%s %03u", type, d.byteB);
      cX = ((t.w/2)-(fontWidth*strlen(buff)))/2;
      display.setCursor(t.x+((cX < 0) ? 0 : cX), t.y + lineHeight + ((lineHeight-fontHeight)/2));
      display.print(buff);

      sprintf(buff, "V %03u", d.byteC);
      cX = t.w + (((t.w/2)-(fontWidth*strlen(buff)))/2);
      display.setCursor(t.x+((cX < 0) ? 0 : cX), t.y + lineHeight + ((lineHeight-fontHeight)/2));
      display.print(buff);
    } else {
      sprintf(buff, "%s %03u", type, d.byteB);
      uint8_t newLineHeight = lineHeight;
      if(totalLines < maxLines){
        newLineHeight = (t.h - lineHeight);

        uint8_t newFontSize = BMCTools::getFontSize(t.w, newLineHeight, buff);
        if(newFontSize != fontSize){
          fontSize = newFontSize;
          fontWidth = (fontSize*6);
          fontHeight = (fontSize*8);
          display.setTextSize(fontSize);
        }
      }
      uint8_t lineY = lineHeight + ((newLineHeight-fontHeight)/2);
      
      cX = (t.w-(fontWidth*strlen(buff)))/2;
      display.setCursor(t.x+((cX < 0) ? 0 : cX), t.y + lineY);
      display.print(buff);

      if(totalLines == 3){
        lineY = (lineHeight*2) + ((newLineHeight-fontHeight)/2);
        // sprintf(buff, "VV %03u", d.byteA+1);
        sprintf(buff, "VV %03u", d.byteC);
        cX = (t.w-(fontWidth*strlen(buff)))/2;
        display.setCursor(t.x+((cX < 0) ? 0 : cX), t.y + lineY);
        display.print(buff);
        display.drawFastHLine(t.x, t.y + (newLineHeight*2), t.w, t.color);
      }
    }
    display.setTextSize(1);
    return true;
  }


  // drawKnobFace & drawKnobPosition
  // based on code from this sketch:
  // https://github.com/rydepier/Arduino-OLED-Clock/blob/master/Arduino-OLED-Clock%20using%20ADAfruit%20libraries.ino
  template <typename T>
  bool renderKnob(T& display, uint16_t& meterValue, uint16_t& meterPixelValue, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset = false){
    // bool showLabel        = d.showLabel() && strlen(d.label);
    // uint16_t wPos         = showLabel?(t.w/4):(t.w/2);
    uint16_t wPos         = t.w/2;
    uint16_t hPos         = t.x + (t.h/2);
    // uint16_t rPos         = t.y + (t.h/2)-2;
    uint16_t rPos         = ((t.h/2)-2);
    
    uint16_t pixelValue   = map(d.value, d.min, d.max, 0, 100);
    // uint16_t strL         = 0;
    // uint16_t blockW       = t.w/2;
    // uint16_t txtX         = t.x;
    // uint8_t fontSize      = 1;
    // uint8_t dotRadius     = ((t.h >= 80) && !showLabel) ? 3 : 2;
    uint8_t dotRadius       = (t.h >= 80) ? 3 : 2;
    uint8_t borderDotRadius = (t.h >= 80) ? 2 : 1;
    // display.setFont();

    // if(showLabel){
    //   display.setTextSize(fontSize);
    //   display.setTextWrap(false);
    //   uint16_t txtY      = t.y;
    //   char outStr[32] = "";
    //   BMCTools::formatKnobValue(d, meterValue, outStr);
      
    //   strL = ((fontSize*6)*strlen(outStr))-2;
    //   if(strL > blockW){
    //     txtX = t.x + blockW + 5;
    //   } else {
    //     txtX = t.x + blockW + ((blockW - strL)/2);
    //   }
    //   display.setTextColor(t.background);
    //   display.setCursor(txtX, txtY);
    //   display.print(outStr);

    //   // display the new value but in the foreground color
    //   BMCTools::formatKnobValue(d, d.value, outStr);
    //   strL = ((fontSize*6)*strlen(outStr))-2;
    //   if(strL > blockW){
    //     txtX = t.x + blockW+5;
    //   } else {
    //     txtX = t.x + blockW + ((blockW - strL)/2);
    //   }
      
    //   display.setTextColor(t.color);
    //   display.setCursor(txtX, txtY);
    //   display.print(outStr);
    // }
    if(meterPixelValue == 0xFFFF){
      // if(showLabel){
      //   strL = ((fontSize*6)*strlen(d.label))-2;
      //   if(strL > blockW){
      //     txtX = t.x + blockW+5;
      //   } else {
      //     txtX = t.x + blockW + ((blockW - strL)/2);
      //   }
      //   display.setCursor(txtX, t.y + 17);
      //   display.print(d.label);
      // }
      drawKnobFace<T>(display, wPos, hPos, rPos, t.color, t.background, borderDotRadius);
      drawKnobPositionDot<T>(display, pixelValue, wPos, hPos, rPos, t.background, dotRadius);
      
    } else {
      drawKnobPositionDot<T>(display, meterPixelValue, wPos, hPos, rPos, t.color, dotRadius);
      drawKnobPositionDot<T>(display, pixelValue, wPos, hPos, rPos, t.background, dotRadius);
    }
    
    meterPixelValue = pixelValue;
    meterValue = d.value;
    return true;
  }
  template <typename T>
  void drawKnobFace(T& display, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color, uint16_t t_background, uint16_t dotRadius=1){
    display.fillRect(t_x, t_y, t_r, t_r, t_background);
    display.fillCircle(t_x, t_y, t_r-12, t_color);
    uint8_t outterR = 5;
    for(int z = 0 ; z < 360 ; z += 30){
      if(z == 180){
        continue;
      }
      float angle = z;
      angle = (angle / 57.29577951) ;
      int x1 = (t_x + (sin(angle) * (t_r-outterR)));
      int y1 = (t_y - (cos(angle) * (t_r-outterR)));
      display.fillCircle(x1, y1, dotRadius, t_color);
    }
  }
  template <typename T>
  void drawKnobPositionDot(T& display, uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color, uint8_t dotRadius=2){
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
    display.fillCircle(x1, y1, dotRadius, t_color);
  }
  template <typename T>
  void drawKnobPositionLine(T& display, uint16_t t_value, uint16_t t_x, uint16_t t_y, uint16_t t_r, uint16_t t_color){
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
  
  template <typename T>
  bool renderSlider(T& display, uint16_t& meterValue, uint16_t& meterPixelValue, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset = false){
    // set crc after clear()
    uint8_t padding    = 2;
    uint16_t x         = t.x + padding;
    uint16_t frameH    = t.h / 2;
    uint16_t frameW    = t.w - (padding * 2);
    uint16_t frameYC   = (t.h-frameH)/2;
    uint16_t y         = t.y + frameYC;
    uint16_t fillH     = frameH-(padding*4);
    uint16_t fillW     = frameW-(padding*4);
    uint8_t fontSize   = 2;
    if(frameH >= 32){
      fontSize   = 4;
    } else if(frameH >= 24){
      fontSize   = 3;
    }

    uint16_t txtY      = (frameH-(fontSize*8)) / 2;
    uint16_t pixelValue = map(d.value, d.min, d.max, (d.useOffset ? d.offset : 0), fillW);
    
    display.setFont();
    display.setTextSize(fontSize);
    display.setTextWrap(false);

    uint16_t txtX = 0;
    char outStr[32] = "";
    // display the last value but in the background color
    sprintf(outStr, "%u", meterValue+(d.useOffset ? d.offset : 0));
    
    txtX = ((t.w - (((fontSize*6)*strlen(outStr))-fontSize))/2);

    display.setTextColor(t.background);
    display.setCursor(txtX, txtY);
    display.print(outStr);

    // display the new value but in the foreground color
    sprintf(outStr, "%u", d.value+(d.useOffset ? d.offset : 0));
    
    txtX = ((t.w - (((fontSize*6)*strlen(outStr))-fontSize))/2);

    display.setTextColor(t.color);
    display.setCursor(txtX, txtY);
    display.print(outStr);
    y = (t.h-frameH)-2;

    uint16_t fillX     = x+(padding*2);
    uint16_t fillY     = y+(padding*2);

    if(meterPixelValue == 0xFFFF){
      display.drawRect(x, y, frameW, frameH, t.color);
      display.fillRect(fillX, fillY, fillW, fillH, t.background);
      display.fillRect(fillX, fillY, pixelValue, fillH, t.color);
    } else if(pixelValue != meterPixelValue){
      if(pixelValue > meterPixelValue){
        display.fillRect(fillX, fillY, pixelValue, fillH, t.color);
      } else {
        display.fillRect(fillX+pixelValue, fillY, fillW-pixelValue, fillH, t.background);
      }
    }
    meterPixelValue = pixelValue;
    meterValue = d.value;
    display.setTextSize(1);
    return true;
  }



  template <typename T>
  void renderSwitch(T& display, uint16_t& meterValue, uint16_t& meterPixelValue, BMCDataContainer d, BMCDiplayHandlerData t, bool t_reset = false){
    // 2 pixel wide box
    // drawSwitchRect(4);
    // drawSwitchRect(5);
    // switch border with 5px padding

    uint16_t pixelValue = d.value == d.max ? 1 : 0;
    uint8_t startPoint = 10;
    
    if(meterPixelValue == 0xFFFF){
      drawSwitchRect(display, t, startPoint);
      drawSwitchRect(display, t, startPoint+1);
    }
    if(pixelValue != meterPixelValue){
      drawSwitch(display, t, startPoint+2, pixelValue);
    }
    meterPixelValue = pixelValue;
    meterValue = d.value;
  }
  template <typename T>
  void drawSwitchRect(T& display, BMCDiplayHandlerData t, uint16_t pos){
    uint16_t pos2 = pos*2;
    display.drawRect(t.x+pos, t.y+pos, t.w-pos2, t.h-pos2, t.color);
  }
  template <typename T>
  void drawSwitch(T& display, BMCDiplayHandlerData t, uint16_t pos, bool value){
    // t.h = 32;
    uint16_t pos2 = pos*2;
    uint16_t centerX = t.w/2;

    display.setFont();
    display.setTextSize(2);
    display.setTextWrap(false);
    
    if(!value){
      display.fillRect(t.x+centerX, t.y+pos, centerX-pos, t.h-pos2, t.background);
      display.fillRect(t.x+pos, t.y+pos, centerX-pos, t.h-pos2, t.color);
      uint16_t txtX = t.x+(pos + ((t.w-pos2)*0.75)) - (18);
      display.setTextColor(t.color);
      display.setCursor(txtX, t.y+(t.h/2)-8);
      display.print("OFF");
    } else {
      display.fillRect(t.x+pos, t.y+pos, centerX-pos, t.h-pos2, t.background);
      display.fillRect(t.x+centerX, t.y+pos, centerX-pos, t.h-pos2, t.color);

      uint16_t txtX = t.x+(pos + ((t.w-pos2)*0.25)) - (12);
      display.setTextColor(t.color);
      display.setCursor(txtX, t.y+(t.h/2)-8);
      display.print("ON");
    }
    display.setTextSize(1);
  }
  
};
#endif
#endif
