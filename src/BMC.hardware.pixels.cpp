/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_PIXELS > 0
void BMC::setupPixels(){
  // unused, kept here to match other setups
  pixels.begin();
}
void BMC::assignPixels(){
  for(uint8_t i=0;i<BMC_MAX_PIXELS;i++){
    bmcStoreLed& item = store.pages[page].pixels[i];
    pixels.setDimColor(i,(BMC_GET_BYTE(3, item.event) >> 4));
  }

#if BMC_MAX_RGB_PIXELS > 0
  for(uint8_t i=0;i<BMC_MAX_RGB_PIXELS;i++){
    bmcStoreRgbLed& item = store.pages[page].rgbPixels[i];
    uint8_t color = 0;
    bitWrite(color, 0, (BMC_GET_BYTE(0, item.red)>0));
    bitWrite(color, 1, (BMC_GET_BYTE(0, item.green)>0));
    bitWrite(color, 2, (BMC_GET_BYTE(0, item.blue)>0));
    pixels.setDimColor(BMC_MAX_PIXELS+i, color);
  }
#endif
  pixels.reassign();
  pixels.setPwmOffValue(settings.getPwmDimWhenOff());
}
void BMC::readPixels(){
  bmcStorePage& pageData = store.pages[page];
  for(uint8_t i = 0; i < BMC_MAX_PIXELS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    uint8_t state = handleLedEvent(i, pageData.pixels[i].event, 3);
    uint8_t color = BMC_GET_BYTE(3, pageData.pixels[i].event) >> 4;
    if(BMC_GET_BYTE(0, pageData.pixels[i].event)==BMC_EVENT_TYPE_CUSTOM){
      pixels.setBrightness(i, map(((state>>4)&0x0F), 0, 15, 0, 127), (state&0x0F));
    } else {
      if(state<=1){
        pixels.setState(i, (state==1) ? color : 0);
      } else if(state==2){
        pixels.pulse(i, color);
      } else if(state==3){
        pixels.setState(i, 3 ? BMC_PIXEL_RAINBOW : color);
      } else if(state!=255){
        pixels.setState(i, bitRead(state, 2) ? BMC_PIXEL_RAINBOW : color);
      }
    }
  }
  // if there are RGB Pixels compiled
#if BMC_MAX_RGB_PIXELS == 0
  pixels.update();
#endif

  uint32_t _pixelStates = pixels.getPixelsState();
  if(_pixelStates!=pixelStates){
    pixelStates = _pixelStates;
    editor.utilitySendPixelActivity(pixelStates);
  }
}
#endif
