/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_DISPLAY_TOUCH_CALIBRATION_H
#define BMC_DISPLAY_TOUCH_CALIBRATION_H
#include "utility/BMC-Def.h"


#if defined(BMC_HAS_TOUCH_SCREEN)

#include <XPT2046_Touchscreen.h>

class BMCDisplayTouchCalibration {
private:
  BMCMidi& midi;
  BMC_TFT& tft;
  XPT2046_Touchscreen& touchScreen;
  TS_Point touchPoint;
  
public:
  bmcStoreTouchSettings cal;
  BMCDisplayTouchCalibration(BMCMidi& t_midi, BMC_TFT& t_tft, XPT2046_Touchscreen& t_touchScreen):
  midi(t_midi),
  tft(t_tft),
  touchScreen(t_touchScreen){
    cal.xM = 0.0;
    cal.xC = 0.0;
    cal.yM = 0.0;
    cal.yC = 0.0;
  }
  void begin(){
    bool firstLoop = true;
    uint16_t xPoint[2] = {0,0};
    uint16_t yPoint[2] = {0,0};
    uint16_t colors[3] = {
      BMC_ILI9341_RED,
      BMC_ILI9341_GREEN,
      BMC_ILI9341_BLUE,
    };
    uint8_t colorSel[3] = {0,0,0};

    printMessage("Touch Calibration", "Touch the center of the", "crosshairs with a stylus");

    drawCrossHair(true, BMC_ILI9341_GREEN);
    
    delay(500);
    while(!touchScreen.touched());
    delay(100);
    touchPoint = touchScreen.getPoint();
    xPoint[0] = touchPoint.x;
    yPoint[0] = touchPoint.y;

    drawCrossHair(true, BMC_ILI9341_BLACK);
    drawCrossHair(false, BMC_ILI9341_GREEN);

    delay(500);
    while(!touchScreen.touched());
    delay(100);

    touchPoint = touchScreen.getPoint();
    xPoint[1] = touchPoint.x;
    yPoint[1] = touchPoint.y;

    // translate in form pos = m x val + c
    // x
    cal.xM = (float)(BMC_TFT_WIDTH - 40) / (float)(xPoint[1] - xPoint[0]);
    cal.xC = 20.0 - ((float)xPoint[0] * cal.xM);
    // y
    cal.yM = (float)(BMC_TFT_HEIGHT - 40) / (float)(yPoint[1] - yPoint[0]);
    cal.yC = 20.0 - ((float)yPoint[0] * cal.yM);

    // BMC_PRINTLN("x1=",xPoint[0], "x2=",xPoint[1], "y1=",yPoint[0], "y2=",yPoint[1]);
    // BMC_PRINTLN("cal.xM=",cal.xM, "cal.xC=",cal.xC, "cal.yM=",cal.yM, "cal.yC=",cal.yC);

    printMessage("Testing Time!", "Tap the blocks to test,", "use a stylus and your fingers");

    bmcTouchArea left;
    bmcTouchArea middle;
    bmcTouchArea right;
    bmcTouchArea btnOk;
    bmcTouchArea btnCancel;

    left.begin(0, 0, 80, 80);
    middle.begin((BMC_TFT_WIDTH-80)/2, 0, 80, 80);
    right.begin(BMC_TFT_WIDTH-80, 0, 80, 80);
    btnOk.begin(BMC_TFT_WIDTH-80, BMC_TFT_HEIGHT-40, 80, 40);
    btnCancel.begin(0, BMC_TFT_HEIGHT-40, 80, 40);

    left.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
    middle.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
    right.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
    btnOk.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
    btnCancel.setCalibrationData(cal.xM, cal.xC, cal.yM, cal.yC);
    renderButton(BMC_TFT_WIDTH-80, BMC_TFT_HEIGHT-40, 80, 40, "Save", BMC_ILI9341_WHITE, BMC_ILI9341_DARKGREEN);
    renderButton(0, BMC_TFT_HEIGHT-40, 80, 40, "Restart", BMC_ILI9341_WHITE, BMC_ILI9341_GRAY_10);

    tft.fillRect(0, 0, 80, 80, BMC_ILI9341_RED);
    tft.fillRect((BMC_TFT_WIDTH-80)/2, 0, 80, 80, BMC_ILI9341_RED);
    tft.fillRect(BMC_TFT_WIDTH-80, 0, 80, 80, BMC_ILI9341_RED);
    
    delay(200);
    
    while(1){
      if(touchScreen.tirqTouched()){
        if(touchScreen.touched()){
          touchPoint = touchScreen.getPoint();
          if(left.isTouched(touchPoint.x, touchPoint.y)){
            colorSel[0]++;
            if(colorSel[0]>2){
              colorSel[0] = 0;
            }
            tft.fillRect(0, 0, 80, 80, colors[colorSel[0]]);
          } else if(middle.isTouched(touchPoint.x, touchPoint.y)){
            colorSel[1]++;
            if(colorSel[1]>2){
              colorSel[1] = 0;
            }
            tft.fillRect((BMC_TFT_WIDTH-80)/2, 0, 80, 80, colors[colorSel[1]]);
          } else if(right.isTouched(touchPoint.x, touchPoint.y)){
            colorSel[2]++;
            if(colorSel[2]>2){
              colorSel[2] = 0;
            }
            tft.fillRect(BMC_TFT_WIDTH-80, 0, 80, 80, colors[colorSel[2]]);
          } else if(btnOk.isTouched(touchPoint.x, touchPoint.y)){
            if(!firstLoop){
              break;
            }
            firstLoop = false;
          } else if(btnCancel.isTouched(touchPoint.x, touchPoint.y)){
            begin();
            break;
          }
        }
        while(touchScreen.touched());
        delay(50);
      }
    }
    midi.globals.settings.setTouchTftCalibration(0, cal.xM);
    midi.globals.settings.setTouchTftCalibration(1, cal.xC);
    midi.globals.settings.setTouchTftCalibration(2, cal.yM);
    midi.globals.settings.setTouchTftCalibration(3, cal.yC);
    midi.globals.settings.setTouchScreenIsCalibrated(1);
    printMessage("Calibration Complete!", "You can now", "reboot your Teensy");
  }
  void drawCrossHair(bool top, uint16_t color){
    if(top){
      tft.drawFastHLine(10, 20, 20, color);
      tft.drawFastVLine(20, 10, 20, color);
    } else {
      tft.drawFastHLine(BMC_TFT_WIDTH-30, BMC_TFT_HEIGHT-20, 20, color);
      tft.drawFastVLine(BMC_TFT_WIDTH-20, BMC_TFT_HEIGHT-30, 20, color);
    }
    
  }
  void printMessage(const char * title, const char * line1, const char * line2=""){
    tft.fillScreen(BMC_ILI9341_BLACK);
    uint8_t y = 95;
    printLine(title, true, y);
    printLine(line1, false, y+38);
    if(strlen(line2)>0){
      printLine(line2, false, y+68);
    }
  }
  void printLine(const char* str, bool header, uint8_t y){
    if(header){
      tft.setFont(BMCLiberationSansNarrow_24_Bold);
      tft.setTextColor(BMC_ILI9341_ORANGE);
    } else {
      tft.setFont(BMCLiberationSansNarrow_20);
      tft.setTextColor(BMC_ILI9341_WHITE);
    }
    char buff[strlen(str)+1] = "";
    strcpy(buff, str);
    int16_t textWidth = tft.strPixelLen(buff);
    int16_t x = (BMC_TFT_WIDTH-textWidth) / 2;
    x = (x < 0) ? 0 : x;
    tft.setCursor(x, y);
    tft.print(buff);
  }
  void renderButton(int x, int y, int width, int height, const char *text, uint16_t color, uint16_t background){
    char buff[strlen(text)+1] = "";
    strcpy(buff, text);
    tft.fillRect(x, y, width, height, background);
    tft.setTextColor(color);
    tft.setFont(BMCLiberationSansNarrow_16);
    int16_t textWidth = tft.strPixelLen(buff);
    uint16_t textX = (width-textWidth) / 2;
    textX = (textX < 0) ? 0 : textX;
    tft.setCursor(x+textX, y+10);
    tft.print(buff);
  }
};
#endif
#endif
