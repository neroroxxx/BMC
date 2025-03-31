/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_TOTAL_PIXELS > 0
void BMC::setupPixels(){
  // unused, kept here to match other setups
  pixels.begin();
}

void BMC::assignPixels(){
#if BMC_MAX_PIXELS > 0
  globals.pixelStates.clear();
  for(uint16_t i=0;i<BMC_MAX_PIXELS;i++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].pixels[i];
    pixels.setDimColor(pixels.getPixelIndex(i), device.settings[0]);
  }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
  globals.globalPixelStates.clear();
  for(uint16_t i=0;i<BMC_MAX_GLOBAL_PIXELS;i++){
    bmcStoreDevice <1, 1>& device = store.global.pixels[i];
    pixels.setDimColor(pixels.getGlobalPixelIndex(i), device.settings[0]);
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0
  globals.rgbPixelStates[0].clear();
  globals.rgbPixelStates[1].clear();
  globals.rgbPixelStates[2].clear();
  for(uint16_t i=0;i<BMC_MAX_RGB_PIXELS;i++){
    bmcStoreDevice <1, 3>& device = store.layers[layer].rgbPixels[i];
    bmcStoreEvent r = globals.getDeviceEventType(device.events[0]);
    bmcStoreEvent g = globals.getDeviceEventType(device.events[1]);
    bmcStoreEvent b = globals.getDeviceEventType(device.events[2]);
    uint8_t color = 0;
    bitWrite(color, 0, (r.type > 0));
    bitWrite(color, 1, (g.type > 0));
    bitWrite(color, 2, (b.type > 0));
    pixels.setDimColor(pixels.getRgbPixelIndex(i), color);
  }
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
  globals.globalRgbPixelStates[0].clear();
  globals.globalRgbPixelStates[1].clear();
  globals.globalRgbPixelStates[2].clear();
  for(uint16_t i=0;i<BMC_MAX_GLOBAL_RGB_PIXELS;i++){
    bmcStoreDevice <1, 3>& device = store.global.rgbPixels[i];
    bmcStoreEvent r = globals.getDeviceEventType(device.events[0]);
    bmcStoreEvent g = globals.getDeviceEventType(device.events[1]);
    bmcStoreEvent b = globals.getDeviceEventType(device.events[2]);
    uint8_t color = 0;
    bitWrite(color, 0, (r.type > 0));
    bitWrite(color, 1, (g.type > 0));
    bitWrite(color, 2, (b.type > 0));
    pixels.setDimColor(pixels.getGlobalRgbPixelIndex(i), color);
  }
#endif

#if BMC_MAX_PIXEL_STRIP > 0
  {
    globals.pixelStripStates.clear();
    bmcStoreDevice <1, 1>& device = store.layers[layer].pixelStrip[0];
    pixels.setDimColor(pixels.getPixelStripIndex(0), device.settings[0]);
  }
#endif

  pixels.reassign();
  pixels.setPwmOffValue(settings.getPwmDimWhenOff());
}

void BMC::readPixels(){
#if BMC_MAX_PIXELS > 0
  for(uint16_t i = 0; i < BMC_MAX_PIXELS; i++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].pixels[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                  BMC_DEVICE_ID_PIXEL,
                                  i,
                                  device.events[0]
                                );
    
    uint8_t color = device.settings[0];
    uint8_t type = data.type;
    if(type==BMC_EVENT_TYPE_PIXEL_PROGRAM){
#if BMC_MAX_PIXEL_PROGRAMS > 0
      pixels.setState(i, pixelPrograms.getColor());
#endif
    } else {
      if(state<=1){
        pixels.setState(i, (state==1) ? color : 0);
      } else if(state==2){
        pixels.pulse(i, color);
      } else if(state==3){
        pixels.setState(i, BMC_PIXEL_RAINBOW);
      } else if(state!=255){
        pixels.setState(i, bitRead(state, 2) ? BMC_PIXEL_RAINBOW : color);
      }
    }
  }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_PIXELS; i++){
    bmcStoreDevice <1, 1>& device = store.global.pixels[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                  BMC_DEVICE_ID_GLOBAL_PIXEL,
                                  i,
                                  device.events[0]
                                );
    uint8_t color = device.settings[0];
    uint8_t type = data.type;
    if(type==BMC_EVENT_TYPE_PIXEL_PROGRAM){
#if BMC_MAX_PIXEL_PROGRAMS > 0
      pixels.setStateGlobal(i, pixelPrograms.getColor());
#endif
    } else {
      if(state<=1){
        pixels.setStateGlobal(i, (state==1) ? color : 0);
      } else if(state==2){
        pixels.pulseGlobal(i, color);
      } else if(state==3){
        pixels.setStateGlobal(i, BMC_PIXEL_RAINBOW);
      } else if(state!=255){
        pixels.setStateGlobal(i, bitRead(state, 2) ? BMC_PIXEL_RAINBOW : color);
      }
    }
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0
  for(uint16_t i = 0; i < BMC_MAX_RGB_PIXELS; i++){
    bmcStoreDevice <1, 3>& device = store.layers[layer].rgbPixels[i];
    for(uint8_t e = 0; e < 3; e++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                    BMC_DEVICE_ID_RGB_PIXEL,
                                    i,
                                    device.events[e],
                                    0,
                                    e
                                  );
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
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_RGB_PIXELS; i++){
    bmcStoreDevice <1, 3>& device = store.global.rgbPixels[i];
    for(uint8_t e = 0; e < 3; e++){
      uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                    BMC_DEVICE_ID_GLOBAL_RGB_PIXEL,
                                    i,
                                    device.events[e],
                                    0,
                                    e
                                  );
      if(state<=1){
        pixels.setStateGlobalRgb(i, e, state);
      } else if(state==2){
        pixels.pulseGlobalRgb(i, e);
      } else if(state==3){
        pixels.setStateGlobalRgb(i, e, true);
      } else if(state!=255){
        pixels.setStateGlobalRgb(i, e, bitRead(state, 2));
      }
    }
  }
#endif

#if BMC_MAX_PIXEL_STRIP > 0
  for(uint16_t i = 0; i < 1; i++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].pixelStrip[i];
    bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
    uint8_t state = processEvent(BMC_DEVICE_GROUP_LED,
                                  BMC_DEVICE_ID_PIXEL_STRIP,
                                  i,
                                  device.events[0]
                                );
    uint8_t color = device.settings[0];
    uint8_t type = data.type;
    if(type==BMC_EVENT_TYPE_CUSTOM){
      //pixels.setBrightness(i, map(((state>>4)&0x0F), 0, 15, 0, 127), (state&0x0F));
    } else if(type == BMC_EVENT_TYPE_PIXEL_PROGRAM){
#if BMC_MAX_PIXEL_PROGRAMS > 0
      pixels.setStateStrip(pixelPrograms.getColor());
#endif
    } else {
      if(state<=1){
        pixels.setStateStrip((state==1) ? color : 0);
      } else if(state==2){
        pixels.pulseStrip(color);
      } else if(state==3){
        pixels.setStateStrip(BMC_PIXEL_RAINBOW);
      } else if(state!=255){
        pixels.setStateStrip(bitRead(state, 2) ? BMC_PIXEL_RAINBOW : color);
      }
    }
  }
#endif

  pixels.update();

#if BMC_MAX_PIXELS > 0
  if(globals.pixelStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_PIXEL);
  }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
  if(globals.globalPixelStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_PIXEL);
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0
  // rgb pixels can run in parallel with pixels, if there are rgb pixels
  // compiled then we only update here no in the pixels calls
  //pixels.update();
  {
    bool r = globals.rgbPixelStates[0].hasChanged();
    bool g = globals.rgbPixelStates[1].hasChanged();
    bool b = globals.rgbPixelStates[2].hasChanged();
    if(r || g || b || editor.isTriggerStates()){
      editor.utilitySendStateBits(BMC_DEVICE_ID_RGB_PIXEL);
    }
  }

#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
  // rgb pixels can run in parallel with pixels, if there are rgb pixels
  // compiled then we only update here no in the pixels calls
  //pixels.update();
  {
    bool r = globals.globalRgbPixelStates[0].hasChanged();
    bool g = globals.globalRgbPixelStates[1].hasChanged();
    bool b = globals.globalRgbPixelStates[2].hasChanged();
    if(r || g || b || editor.isTriggerStates()){
      editor.utilitySendStateBits(BMC_DEVICE_ID_GLOBAL_RGB_PIXEL);
    }
  }
#endif

#if BMC_MAX_PIXEL_STRIP > 0
  if(globals.pixelStripStates.hasChanged() || editor.isTriggerStates()){
    editor.utilitySendStateBits(BMC_DEVICE_ID_PIXEL_STRIP);
  }
#endif
}
#endif
