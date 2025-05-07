/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
// SETUP
void BMC::setupEncoders(){
#if BMC_MAX_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ENCODER, i);
    BMC_PRINT(i, "l");
    encoders[i].begin(ui.pins[0], ui.pins[1]);
  }
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_ENCODER, i);
    BMC_PRINT(i, "g");
    globalEncoders[i].begin(ui.pins[0], ui.pins[1]);
  }
#endif
}

void BMC::assignEncoders(){
#if BMC_MAX_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_ENCODERS; i++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].encoders[i];
    encoders[i].reassign(device.settings[0]);
  }
#endif
#if BMC_MAX_GLOBAL_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    bmcStoreDevice <1, 1>& device = store.global.encoders[i];
    globalEncoders[i].reassign(device.settings[0]);
  }
#endif
}

void BMC::readEncoders(){
#if BMC_MAX_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_ENCODERS; i++){
    bmcStoreDevice <1, 1>& device = store.layers[layer].encoders[i];
    // GET THE PIN STATE FROM MUX
    #if defined(BMC_MUX_INPUTS_AVAILABLE)
      if(encoders[i].hasMux()){
        encoders[i].setMuxValue(0, mux.readDigital(encoders[i].getMuxPin(0)));
        encoders[i].setMuxValue(1, mux.readDigital(encoders[i].getMuxPin(1)));
      }
    #endif

    if(encoders[i].update()){
      bool increased = encoders[i].increased();
      uint8_t ticks = encoders[i].getTicks();
      #if defined(BMC_DEBUG)
        printEncoderTrigger(BMC_DEVICE_ID_ENCODER, i, increased, ticks);
      #endif
      #if defined(BMC_USE_ON_BOARD_EDITOR)
      if(obe.checkDeviceAssignment(BMC_DEVICE_ID_ENCODER, i, increased, ticks)){
        break;
      }
      #endif
      processEvent(BMC_DEVICE_GROUP_ENCODER,
                  BMC_DEVICE_ID_ENCODER,
                  i,
                  device.events[0],
                  (increased << 7 | ticks)
                  );

      
      //uint32_t event = pageData.encoders[i].event;
      /*
      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.encoderCustomActivity){
        callback.encoderCustomActivity(i, increased, ticks);
      } else if(callback.encoderActivity){
        callback.encoderActivity(i, increased, ticks);
      }
      */
      editor.utilitySendEncoderActivity(BMC_DEVICE_ID_ENCODER, i, increased);
    }
  }
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    bmcStoreDevice <1, 1>& device = store.global.encoders[i];
    // GET THE PIN STATE FROM MUX
  #if defined(BMC_MUX_INPUTS_AVAILABLE)
    if(globalEncoders[i].hasMux()){
      globalEncoders[i].setMuxValue(0, mux.readDigital(globalEncoders[i].getMuxPin(0)));
      globalEncoders[i].setMuxValue(1, mux.readDigital(globalEncoders[i].getMuxPin(1)));
    }
  #endif

    if(globalEncoders[i].update()){
      bool increased = globalEncoders[i].increased();
      uint8_t ticks = globalEncoders[i].getTicks();
      #if defined(BMC_DEBUG)
        printEncoderTrigger(BMC_DEVICE_ID_GLOBAL_ENCODER, i, increased, ticks);
      #endif
      #if defined(BMC_USE_ON_BOARD_EDITOR)
      if(obe.checkDeviceAssignment(BMC_DEVICE_ID_GLOBAL_ENCODER, i, increased, ticks)){
        break;
      }
      #endif
      processEvent(BMC_DEVICE_GROUP_ENCODER,
                  BMC_DEVICE_ID_GLOBAL_ENCODER,
                  i,
                  device.events[0],
                  increased<<7 | ticks
                  );

      
      /*
      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.globalEncoderCustomActivity){
        callback.globalEncoderCustomActivity(i, increased, ticks);
      } else if(callback.globalEncoderActivity){
        callback.globalEncoderActivity(i, increased, ticks);
      }
      */
      //editor.utilitySendGlobalEncoderActivity(i, increased);
      editor.utilitySendEncoderActivity(BMC_DEVICE_ID_GLOBAL_ENCODER, i, increased);
    }
  }
#endif
}
#endif

