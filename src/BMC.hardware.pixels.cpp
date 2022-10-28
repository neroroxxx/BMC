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
  //bmcStoreDevice
  for(uint16_t i=0;i<BMC_MAX_PIXELS;i++){
    bmcStoreDevice <1, 1>& device = store.pages[page].pixels[i];
    pixels.setDimColor(i, device.settings[0]);
  }

#if BMC_MAX_RGB_PIXELS > 0
  for(uint16_t i=0;i<BMC_MAX_RGB_PIXELS;i++){
    bmcStoreDevice <1, 3>& device = store.pages[page].rgbPixels[i];
    bmcStoreEvent r = globals.getDeviceEventType(device.events[0]);
    bmcStoreEvent g = globals.getDeviceEventType(device.events[1]);
    bmcStoreEvent b = globals.getDeviceEventType(device.events[2]);
    uint8_t color = 0;
    bitWrite(color, 0, (r.type > 0));
    bitWrite(color, 1, (g.type > 0));
    bitWrite(color, 2, (b.type > 0));
    pixels.setDimColor(BMC_MAX_PIXELS+i, color);
    /*
    bmcStoreRgbLed& item = store.pages[page].rgbPixels[i];
    uint8_t color = 0;
    bitWrite(color, 0, (BMC_GET_BYTE(0, item.red)>0));
    bitWrite(color, 1, (BMC_GET_BYTE(0, item.green)>0));
    bitWrite(color, 2, (BMC_GET_BYTE(0, item.blue)>0));
    pixels.setDimColor(BMC_MAX_PIXELS+i, color);
    */
  }
#endif
  pixels.reassign();
  pixels.setPwmOffValue(settings.getPwmDimWhenOff());
}
void BMC::readPixels(){
  //bmcStorePage& pageData = store.pages[page];
  for(uint16_t i = 0; i < BMC_MAX_PIXELS; i++){
    // handleLedEvent() @ BMC.hardware.ledEvents.cpp
    //uint8_t state = handleLedEvent(i, pageData.pixels[i].event, 3);
    //uint8_t color = BMC_GET_BYTE(3, pageData.pixels[i].event) >> 4;
    //uint8_t type = BMC_GET_BYTE(0, pageData.pixels[i].event);
    bmcStoreDevice <1, 1>& device = store.pages[page].pixels[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);


    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED, BMC_DEVICE_ID_PIXEL, i,
                                BMC_EVENT_IO_TYPE_OUTPUT, device.events[0]);
    uint8_t color = device.settings[0];
    uint8_t type = data.type;
    if(type==BMC_EVENT_TYPE_CUSTOM){
      pixels.setBrightness(i, map(((state>>4)&0x0F), 0, 15, 0, 127), (state&0x0F));
    } else if(type==BMC_LED_EVENT_TYPE_PIXEL_PROGRAM){
#if BMC_MAX_PIXEL_PROGRAMS > 0
      //pixels.setState(i, pixelPrograms.getColor());
#endif
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
  if(globals.pixelStates.hasChanged()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_PIXEL);
  }
/*
  uint32_t _pixelStates = pixels.getPixelsState();
  if(_pixelStates!=pixelStates){
    pixelStates = _pixelStates;
    editor.utilitySendPixelActivity(pixelStates);
  }
  */
}
#endif
