/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>
/*
  Setup the hardware items
*/
void BMC::setupHardware(){

  BMC_PRINTLN("");

#if defined(BMC_MUX_AVAILABLE)
  mux.begin();
#endif

#if BMC_TOTAL_PIXELS > 0
  // BMC.hardware.pixels
  setupPixels();
#endif

#if BMC_TOTAL_LEDS > 0
  // BMC.hardware.leds
  setupLeds();
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  // BMC.hardware.buttons
  setupButtons();
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  // BMC.hardware.encoders
  setupEncoders();
#endif

#if BMC_MAX_MAGIC_ENCODERS > 0 || BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  setupMagicEncoders();
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  // BMC.hardware.pots
  setupPots();
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  // BMC.hardware.relays
  setupRelays();
#endif

#if BMC_MAX_AUX_JACKS > 0
  // BMC.hardware.auxJacks
  setupAuxJacks();
#endif

  BMC_PRINTLN("");
}
/*
  Assign how hardware will behave
*/
void BMC::assignHardware() {

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  // BMC.hardware.buttons
  assignButtons();
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  // BMC.hardware.encoders
  assignEncoders();
#endif

#if BMC_MAX_MAGIC_ENCODERS > 0 || BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  assignMagicEncoders();
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  // BMC.hardware.pots
  assignPots();
#endif

#if BMC_TOTAL_PIXELS > 0
  // BMC.hardware.pixels
  assignPixels();
#endif

#if BMC_TOTAL_LEDS > 0
  // BMC.hardware.leds
  assignLeds();
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  assignRelays();
#endif

#if BMC_MAX_AUX_JACKS > 0
  assignAuxJacks();
#endif


  // if EEPROM has been cleared we'll blink all LEDS/PIXELS available
  // even if there's no
  if(editor.eepromErased()){
#if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) > 1
    for(uint8_t i=0;i<5;i++){
      controlFirstLed(true);
      delay(100);
      controlFirstLed(false);
      delay(100);
    }
#endif
    if(callback.eepromErased){
      callback.eepromErased();
    }
  }
// Global Buttons,Leds,Encoders,Pots are assigned at startup and when data is updated
// Relays don't need assignments
}
// Read the hardware items for changes
void BMC::readHardware(){

#if defined(BMC_MUX_AVAILABLE)
  mux.update();
#endif


#if defined(BMC_HAS_DISPLAY)
#if BMC_MAX_ILI9341_BLOCKS > 0 && (BMC_MAX_SETLISTS > 0 || BMC_MAX_LAYERS > 1 || BMC_MAX_PRESETS > 0)
  if(globals.getRenderDisplayList()){
    display.renderDisplayLists();
  } else if(globals.displayListsComplete()){
    globals.exitDisplayListMode();
    display.blackoutIliScreen();
    display.reassign(true);
  }
#endif

if(oneMillisecondPassed()){
  
  #if defined(BMC_DEBUG)
  // time how long it takes to render all displays
  unsigned long t = millis();
  #endif

  #if BMC_MAX_ILI9341_BLOCKS > 0
    if(!globals.pauseIli()){
      for(uint8_t index = 0 ; index < BMC_MAX_ILI9341_BLOCKS ; index++){
        uint16_t eIndex = store.layers[layer].ili[index].events[0];
        if(eIndex == 0 && !settings.getDisplayNames()){
          display.blackoutIli(index);
          continue;
        }
        processEvent(BMC_DEVICE_GROUP_DISPLAY, BMC_DEVICE_ID_ILI, index, eIndex);
      }
    }
  #endif

  #if BMC_MAX_OLED > 0
    for(uint8_t index = 0 ; index < BMC_MAX_OLED ; index++){
      uint16_t eIndex = store.layers[layer].oled[index].events[0];
      if(eIndex == 0 && !settings.getDisplayNames()){
        display.blackoutOled(index);
        continue;
      }
      processEvent(BMC_DEVICE_GROUP_DISPLAY, BMC_DEVICE_ID_OLED, index, eIndex);
    }
  #endif

  #if BMC_MAX_MINI_DISPLAY > 0
    for(uint8_t index = 0 ; index < BMC_MAX_MINI_DISPLAY ; index++){
      for(uint8_t e = 0 ; e < BMC_MAX_MINI_DISPLAY_EVENTS ; e++){
        display.setMiniDisplayLine(index, e);
        uint16_t eIndex = store.layers[layer].miniDisplay[index].events[e];
        if(eIndex == 0 && !settings.getDisplayNames()){
          display.blackoutMiniDisplay(index);
          continue;
        }
        processEvent(BMC_DEVICE_GROUP_DISPLAY, BMC_DEVICE_ID_MINI_DISPLAY, index, eIndex);
      }
    }
  #endif

  #if BMC_MAX_LCD > 0
    for(uint8_t index = 0 ; index < BMC_MAX_LCD ; index++){
      uint16_t eIndex = store.layers[layer].lcd[index].events[0];
      if(eIndex == 0 && !settings.getDisplayNames()){
        display.blackoutLcd(index);
        continue;
      }
      processEvent(BMC_DEVICE_GROUP_DISPLAY, BMC_DEVICE_ID_LCD, index, eIndex);
    }
  #endif

  #if defined(BMC_DEBUG)
  // time how long it takes to render all displays
  unsigned long y = millis()-t;
  if(y>1){
    if(globals.getDisplayRenderTimeDebug()){
      BMC_PRINTLN("display render time",y,"ms");
    }
    
  }
  #endif
  
}
#endif

// read hardware that can "send" data first and LEDs/Pixels last
#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  // BMC.hardware.buttons
  readButtons();
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  // BMC.hardware.encoders
  readEncoders();
#endif


#if BMC_MAX_MAGIC_ENCODERS > 0 || BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  // BMC.hardware.encoders
  readMagicEncoders();
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  // BMC.hardware.pots
  readPots();
#endif

#if BMC_TOTAL_LEDS > 0
  // BMC.hardware.leds
  readLeds();
#endif


#if BMC_TOTAL_PIXELS > 0
  // BMC.hardware.pixels
  readPixels();
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  // BMC.hardware.relays
  readRelays();
#endif

#if BMC_MAX_AUX_JACKS > 0
  // BMC.hardware.auxJacks
  readAuxJacks();
#endif

}
// just used when EEPROM is erased, blinks first of each led type
void BMC::controlFirstLed(bool t_value){
  #if BMC_MAX_LEDS > 0
    leds[0].overrideState(t_value);
  #endif

  #if BMC_MAX_GLOBAL_LEDS > 0
    globalLeds[0].overrideState(t_value);
  #endif

  #if BMC_MAX_PIXELS > 0
    pixels.setState(0, t_value?255:0);
  #endif

  #if BMC_MAX_GLOBAL_PIXELS > 0
    pixels.setStateGlobal(0, t_value?255:0);
  #endif

  #if BMC_MAX_RGB_PIXELS > 0
    pixels.setStateRgb(0, 0, t_value);
  #endif

  #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    pixels.setStateGlobalRgb(0, 0, t_value);
  #endif
}
uint8_t BMC::parseMidiEventType(uint8_t t_type){
  // this code will take an event type from buttons, encoders, leds, pots
  // and determine what type of event it is.
  // all hardware events can have standard midi message status as their type
  // those event types also will include the channel for the midi message
  // if it's a Channel Status(Program, Control, etc).
  // in that case we will return only the 4 MSB bits so a switch statement
  // so that the channel can be ignored
  // For system common messages like System Reset, Clock Start, Stop, etc.
  // there's no need to remove the 4 LSB bits since they are part of the status
  // so if the type is between 128 and 239 it's a standard MIDI message
  // if it's higher than 239 it's a system common
  // otherwise if it's lessage than 128 it's a custom event by BMC
  // if the value is 127 (0x7F) it's a custom event type for Sketch use
  return (t_type > 0x7F && t_type < 0xF0) ? (t_type & 0xF0) : t_type;
}

// uint8_t BMC::parseUserEventType(uint8_t t_type){
//   if(t_type<BMC_BUTTON_EVENT_TYPE_USER_1){
//     return 0;
//   }
//   return parseMidiEventType(t_type)-BMC_BUTTON_EVENT_TYPE_USER_1;
// }
