/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>
void BMC::reloadLayer(){
  setLayer(layer, true, true);
}
void BMC::setLayer(uint8_t t_layer, bool reassignSettings, bool forced){
  if(t_layer >= BMC_MAX_LAYERS && !forced){
    return;
  }
  if(layer != t_layer && !forced){
    flags.write(BMC_FLAGS_LAYER_CHANGED, true);
    bmcStoreName e = globals.getDeviceName(store.layers[layer].events[0].name);
    streamToSketch(BMC_DEVICE_ID_LAYER, t_layer, e.name);
  }
  layer = t_layer;

  BMC_PRINTLN("Switching to Layer #",layer+1,"(",layer,")");

  editor.setLayer(layer);
  editor.layerSendChangeMessage();

  if(reassignSettings){
    assignSettings();
  }

  #if defined(BMC_HAS_HARDWARE)
    assignHardware();
  #endif

  #if defined(BMC_HAS_DISPLAY)
    display.reassign();
  #endif

  #if defined(BMC_USE_BEATBUDDY)
    sync.beatBuddy.reassign();
  #endif

  if(callback.pageChanged){
    callback.pageChanged(layer);
  }
  if(flags.read(BMC_FLAGS_LAYER_CHANGED) && editor.connected()){
    editor.triggerStates();
    
  }
};
bool BMC::layerChanged(){
  return flags.toggleIfTrue(BMC_FLAGS_LAYER_CHANGED);
}
bool BMC::layerChangedPeek(){
  return flags.read(BMC_FLAGS_LAYER_CHANGED);
}
uint8_t BMC::getLayer(){
  return layer;
}
void BMC::nextLayer(){
  BMCScroller <uint8_t> scroller(0, BMC_MAX_LAYERS-1);
  setLayer(scroller.scroll(1, true, true, layer, 0, BMC_MAX_LAYERS-1));
}
void BMC::prevLayer(){
  BMCScroller <uint8_t> scroller(0, BMC_MAX_LAYERS-1);
  setLayer(scroller.scroll(1, false, true, layer, 0, BMC_MAX_LAYERS-1));
}
void BMC::scrollLayer(bool t_dir, bool t_endless, uint8_t t_amount){
  scrollLayer(t_dir, t_endless, 0, BMC_MAX_LAYERS-1, t_amount);
}

void BMC::scrollLayer(uint8_t t_settings, uint8_t t_amount){
  scrollLayer((bitRead(t_amount,7)),bitRead(t_settings,2), 0, BMC_MAX_LAYERS-1, t_amount & 0x7F);
}
void BMC::scrollLayer(uint8_t t_flags, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  // t_flags bit-0 = direction
  // t_flags bit-1 = endless
  scrollLayer((bitRead(t_flags,0)),bitRead(t_flags,1),t_min,t_max,t_amount);
}
void BMC::scrollLayer(bool t_dir, bool t_endless, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  BMCScroller <uint8_t> scroller(0, BMC_MAX_LAYERS-1);
  setLayer(scroller.scroll(t_amount, t_dir, t_endless, layer, t_min, t_max));
}
