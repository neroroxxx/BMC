/*
  See https://www.roxxxtar.com/bmc for more details
  Copyright (c) 2015 - 2025 Roxxxtar.com 
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

  BMC_PRINT_CHANGE("Layer: ", (layer + 1), " (", layer, ")");

  editor.setLayer(layer);
  editor.layerSendChangeMessage();

  if(reassignSettings){
    assignSettings();
  }

  #if defined(BMC_HAS_HARDWARE)
    assignHardware();
  #endif
  
  #if defined(BMC_HAS_DISPLAY)
    if(!globals.displayListsActive()){
      // display.midi.globals.exitDisplayListMode();
      display.reassign();
    }
    
  #endif

  #if defined(BMC_USE_SYNC)
    sync.reassign();
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
bmcStoreName BMC::getLayerName(){
  return getLayerName(layer);
}
bmcStoreName BMC::getLayerName(uint8_t n){
  bmcStoreName t = globals.getDeviceName(store.layers[n].events[0].name);
  if(BMC_STR_MATCH(t.name, "")){
    sprintf(t.name, "L %u", n+globals.offset);
  }
  return t;
}

bmcStoreName BMC::getLayerStr(){
  return getLayerStr(layer);
}
bmcStoreName BMC::getLayerStr(uint8_t n){
  bmcStoreName t;
  sprintf(t.name, "%u", n+midi.globals.offset);
  return t;
}




void BMC::getLayerName(char * str){
  getLayerName(layer, str);
}
void BMC::getLayerName(uint8_t n, char * str){
  bmcStoreName t = globals.getDeviceName(store.layers[n].events[0].name);
  if(BMC_STR_MATCH(t.name, "")){
    sprintf(str, "L %u", n+globals.offset);
  } else {
    strcpy(str, t.name);
  }
}
void BMC::getLayerStr(char * str){
  getLayerStr(layer, str);
}
void BMC::getLayerStr(uint8_t n, char * str){
  sprintf(str, "%u", n+midi.globals.offset);
}









void BMC::nextLayer(){
  scrollLayer(BMC_NEXT, BMC_WRAP, 1);
}
void BMC::prevLayer(){
  scrollLayer(BMC_PREV, BMC_WRAP, 1);
}
void BMC::scrollLayer(bool t_dir, bool t_wrap, uint8_t t_amount){
  scrollLayer(t_dir, t_wrap, 0, BMC_MAX_LAYERS-1, t_amount);
}

void BMC::scrollLayer(uint8_t t_settings, uint8_t t_amount){
  scrollLayer((bitRead(t_amount,7)),bitRead(t_settings,2), 0, BMC_MAX_LAYERS-1, t_amount & 0x7F);
}
void BMC::scrollLayer(uint8_t t_flags, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  // t_flags bit-0 = direction
  // t_flags bit-1 = wrap
  scrollLayer((bitRead(t_flags,0)),bitRead(t_flags,1),t_min,t_max,t_amount);
}
void BMC::scrollLayer(bool t_dir, bool t_wrap, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  // if(!globals.onBoardEditorActive()){
  //   if(settings.getDisplayListMode() && !globals.displayListsActive()){
  //     globals.setRenderDisplayList(BMC_DEVICE_ID_LAYER);
  //     return;
  //   }
  // }
  if(globals.setRenderDisplayList(BMC_DEVICE_ID_LAYER)){
    return;
  }
  uint8_t nextLayer = BMCCycle<uint8_t>(0, BMC_MAX_LAYERS - 1)
  .withAmount(t_amount)
  .withDirection(t_dir)
  .withWrap(t_wrap)
  .withValue(layer)
  .withRange(t_min, t_max)
  .process();

  setLayer(nextLayer);
}

