/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

// sketch bytes
#if BMC_MAX_SKETCH_BYTES > 0
void BMC::setSketchByte(uint8_t n, uint8_t value){
  if(n < BMC_MAX_SKETCH_BYTES){
    BMCSketchByteData data = BMCBuildData::getSketchByteData(n);
    store.global.sketchBytes[n].events[0] = constrain(value, data.min, data.max);
  }
}
void BMC::saveSketchBytes(bool triggerEditorUpdateCallback){
  editor.saveSketchBytesToEEPROM();
  // send the sketch bytes to the editor but only if connected
  editor.utilitySendSketchBytes(true);
  BMC_PRINTLN("BMC::saveSketchBytes()");
  if(triggerEditorUpdateCallback && callback.storeUpdated){
    callback.storeUpdated();
  }
}
// sketch bytes
uint8_t BMC::getSketchByte(uint8_t n){
  if(n<BMC_MAX_SKETCH_BYTES){
    BMCSketchByteData data = BMCBuildData::getSketchByteData(n);
    uint8_t value = store.global.sketchBytes[n].events[0];
    return constrain(value, data.min, data.max);
  }
  return 0;
}
BMCSketchByteData BMC::getSketchByteData(uint8_t n){
  if(n<BMC_MAX_SKETCH_BYTES){
    return BMCBuildData::getSketchByteData(n);
  }
  BMCSketchByteData buff;
  return buff;
}
#endif
