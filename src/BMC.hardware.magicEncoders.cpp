/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_MAGIC_ENCODERS > 0 || BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
// SETUP
void BMC::setupMagicEncoders(){
#if BMC_MAX_MAGIC_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_MAGIC_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_MAGIC_ENCODER, i);
    if(!magicEncoders[i].begin(ui.other1)){
      BMC_ERROR(
        "Magic Encoder:", i,
        "could not be reached"
      );
      BMC_HALT();
    }
  }
#endif

#if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_MAGIC_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER, i);
    if(!globalMagicEncoders[i].begin(ui.other1)){
      BMC_ERROR(
        "Global Magic Encoder:", i,
        "could not be reached"
      );
      BMC_HALT();
    }
  }
  assignGlobalMagicEncoders();
#endif
}

void BMC::assignMagicEncoders(){
#if BMC_MAX_MAGIC_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_MAGIC_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_MAGIC_ENCODER, i);
    bmcStoreDevice <3, 3>& device = store.layers[layer].magicEncoders[i];
    // bmcStoreEvent dataPixel   = globals.getDeviceEventType(device.events[0]);
    //bmcStoreEvent dataEncoder = globals.getDeviceEventType(device.events[1]);
    //bmcStoreEvent dataBtn     = globals.getDeviceEventType(device.events[2]);
    magicEncoders[i].reassign(ui.rotation & 0x0F);
    magicEncoders[i].setColors(device.settings[0]);
//     if(dataPixel.type==BMC_EVENT_TYPE_DAW_MAGIC_ENCODER){
// #if defined(BMC_USE_DAW_LC)
//       if(BMC_GET_BYTE(0, dataPixel.event)==0){
//         magicEncoders[i].setView(sync.daw.getVPotMode(BMC_GET_BYTE(1, dataPixel.event)));
//       } else {
//         magicEncoders[i].setView(BMC_ME_WRAP);
//       }
// #else
//       magicEncoders[i].setView(device.settings[1]);
// #endif
//     } else {
      
//     }
    magicEncoders[i].setView(device.settings[1]);
    magicEncoders[i].setLimit(BMC_ME_LIMIT_100);
    magicEncoders[i].setBrightness(BMC_ME_BRIGHTNESS_LOW);
  }
#endif
#if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_MAGIC_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER, i);
    bmcStoreDevice <3, 3>& device = store.global.magicEncoders[i];
    // bmcStoreEvent dataPixel   = globals.getDeviceEventType(device.events[0]);
    //bmcStoreEvent dataEncoder = globals.getDeviceEventType(device.events[1]);
    //bmcStoreEvent dataBtn     = globals.getDeviceEventType(device.events[2]);
    globalMagicEncoders[i].reassign(ui.rotation & 0x0F);
    globalMagicEncoders[i].setColors(device.settings[0]);

//     if(dataPixel.type==BMC_EVENT_TYPE_DAW_MAGIC_ENCODER && BMC_GET_BYTE(0, dataPixel.event)==0){
// #if defined(BMC_USE_DAW_LC)
//       if(BMC_GET_BYTE(0, dataPixel.event)==0){
//         globalMagicEncoders[i].setView(sync.daw.getVPotMode(BMC_GET_BYTE(1, dataPixel.event)));
//       } else {
//         globalMagicEncoders[i].setView(BMC_ME_WRAP);
//       }
// #else
//       globalMagicEncoders[i].setView(device.settings[1]);
// #endif
//     } else {
//       globalMagicEncoders[i].setView(device.settings[1]);
//     }
    
    globalMagicEncoders[i].setView(device.settings[1]);
    globalMagicEncoders[i].setLimit(BMC_ME_LIMIT_100);
    globalMagicEncoders[i].setBrightness(BMC_ME_BRIGHTNESS_LOW);
  }
#endif
}

void BMC::readMagicEncoders(){
#if BMC_MAX_MAGIC_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_MAGIC_ENCODERS; i++){
    bmcStoreDevice <3, 3>& device = store.layers[layer].magicEncoders[i];
    bool hasUpdate = false;
    uint8_t ledValue = 0;
    uint8_t trigger = 0;
    uint8_t ticks = 0;
    bool increased = false;
    if(device.events[0] != BMC_NONE){
      ledValue = processEvent(BMC_DEVICE_GROUP_MAGIC_ENCODER, 
                                BMC_DEVICE_ID_MAGIC_ENCODER,
                                i,
                                device.events[0]
                              );
      hasUpdate = magicEncoders[i].setValue(ledValue);
      if(hasUpdate){
        BMC_PRINTLN("hasUpdate", ledValue);
      }
    }
    if(magicEncoders[i].update(2)){
      hasUpdate = true;
      trigger = magicEncoders[i].getTrigger();
      ticks = magicEncoders[i].getTicks();
      increased = magicEncoders[i].increased();
      if(trigger != BMC_NONE && trigger==(device.settings[2] & 0x0F)){
        processEvent(BMC_DEVICE_GROUP_BUTTON,
                      BMC_DEVICE_ID_MAGIC_ENCODER,
                      i,
                      device.events[2]
                    );
      }
      if(ticks > 0){
        processEvent(BMC_DEVICE_GROUP_ENCODER,
                      BMC_DEVICE_ID_MAGIC_ENCODER,
                      i,
                      device.events[1],
                      (increased<<7 | ticks)
                    );
      }
    }
    if(hasUpdate || editor.isTriggerStates()){
      editor.utilitySendMagicEncoderActivity(BMC_DEVICE_ID_MAGIC_ENCODER, i, trigger, ticks, increased, ledValue);
    }
    
  }
#endif

#if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_MAGIC_ENCODERS; i++){
    bmcStoreDevice <3, 3>& device = store.global.magicEncoders[i];
    bool hasUpdate = false;
    uint8_t ledValue = 0;
    uint8_t trigger = 0;
    uint8_t ticks = 0;
    bool increased = 0;
    if(device.events[0] != BMC_NONE){
      ledValue = processEvent(BMC_DEVICE_GROUP_MAGIC_ENCODER, 
                                BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER,
                                i,
                                device.events[0]
                              );
      hasUpdate = globalMagicEncoders[i].setValue(ledValue);
    }
    if(globalMagicEncoders[i].update(2)){
      hasUpdate = true;
      trigger = globalMagicEncoders[i].getTrigger();
      ticks = globalMagicEncoders[i].getTicks();
      increased = globalMagicEncoders[i].increased();
      if(trigger != BMC_NONE && trigger==(device.settings[2] & 0x0F)){
        processEvent(BMC_DEVICE_GROUP_BUTTON,
                      BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER,
                      i,
                      device.events[2]
                    );
      }
      if(ticks > 0){
        bmcStoreEvent data = globals.getDeviceEventType(device.events[1]);
        processEvent(BMC_DEVICE_GROUP_ENCODER,
                      BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER,
                      i,
                      device.events[1],
                      (increased<<7 | ticks)
                    );
      }
    }
    if(hasUpdate || editor.isTriggerStates()){
      editor.utilitySendMagicEncoderActivity(BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER, i, trigger, ticks, increased, ledValue);
    }
  }
#endif
}
#endif
