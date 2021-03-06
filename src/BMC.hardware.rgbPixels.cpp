/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_RGB_PIXELS > 0
void BMC::setupRgbPixels(){
  #if BMC_MAX_PIXELS == 0
    pixels.begin();
  #endif
}
void BMC::assignRgbPixels(){
  // if we also have Pixels then they are already reassigning
  // the pixels, but if we don't then we do it here
#if BMC_MAX_PIXELS == 0
  // assign their off value based on what color led has an event
  for(uint8_t i=0;i<BMC_MAX_RGB_PIXELS;i++){
    bmcStoreRgbLed& item = store.pages[page].rgbPixels[i];
    uint8_t color = 0;
    bitWrite(color, 0, (BMC_GET_BYTE(0, item.red)>0));
    bitWrite(color, 1, (BMC_GET_BYTE(0, item.green)>0));
    bitWrite(color, 2, (BMC_GET_BYTE(0, item.blue)>0));
    pixels.setDimColor(BMC_MAX_PIXELS+i, color);
  }
  pixels.reassign();
  pixels.setPwmOffValue(settings.getPwmDimWhenOff());
#endif
}
void BMC::readRgbPixels(){
  bmcStorePage& pageData = store.pages[page];
  for(uint8_t i = 0; i < BMC_MAX_RGB_PIXELS; i++){
    uint32_t events[3] = {
      pageData.rgbPixels[i].red,
      pageData.rgbPixels[i].green,
      pageData.rgbPixels[i].blue
    };
    for(uint8_t e = 0; e < 3; e++){
      // handleLedEvent() @ BMC.hardware.ledEvents.cpp
      uint8_t state = handleLedEvent(i, events[e], e+4);
      if(state<=1){
        pixels.setStateRgb(i, e, state);
      } else if(state==2){
        pixels.pulseRgb(i, e);
      } else if(state==3){
        pixels.setStateRgb(i, e, true);
      } else if(state!=255){
        pixels.setStateRgb(i, e, bitRead(state, 2));
      }
    }
  }
  // rgb pixels can run in parallel with pixels, if there are rgb pixels
  // compiled then we only update here no in the pixels calls
  pixels.update();
  uint32_t _r = pixels.getRgbPixelsStateR();
  uint32_t _g = pixels.getRgbPixelsStateG();
  uint32_t _b = pixels.getRgbPixelsStateB();
  if(_r != rgbPixelStatesR || _g != rgbPixelStatesG || _b != rgbPixelStatesB){
    rgbPixelStatesR = _r;
    rgbPixelStatesG = _g;
    rgbPixelStatesB = _b;
    editor.utilitySendRgbPixelActivity(_r, _g, _b);
  }
}
#endif
