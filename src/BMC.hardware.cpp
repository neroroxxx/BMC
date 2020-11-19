/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>
/*
  Setup the hardware items
*/
void BMC::setupHardware(){

  BMC_PRINTLN("");

#if BMC_MAX_AUX_JACKS > 0
  BMC_PRINTLN("BMC_MAX_AUX_JACKS", BMC_MAX_AUX_JACKS);
  for(uint8_t i=0;i<BMC_MAX_AUX_JACKS;i++){

    #if BMC_MAX_MUX_GPIO > 0 || BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_IN_ANALOG > 0
      if(
        BMCBuildData::getPotPin(BMCBuildData::getPotMergeItem(i, 0))>=64 ||
        BMCBuildData::getButtonPin(BMCBuildData::getPotMergeItem(i, 1))>=64 ||
        BMCBuildData::getButtonPin(BMCBuildData::getPotMergeItem(i, 2))>=64
      ){
        BMC_ERROR("BMC can not be used with Mux Pins");
        BMC_HALT();
      }
    #endif

    auxJacks.begin(i,
                    BMCBuildData::getPotMergeItem(i, 0),
                    BMCBuildData::getPotMergeItem(i, 1),
                    BMCBuildData::getPotMergeItem(i, 2));
  }
#endif

#if defined(BMC_MUX_AVAILABLE)
  mux.begin();
#endif

#if BMC_MAX_PIXELS > 0
  // BMC.hardware.pixels
  setupPixels();
#endif

#if BMC_MAX_RGB_PIXELS > 0
  // BMC.hardware.rgbPixels
  setupRgbPixels();
#endif

#if BMC_MAX_LEDS > 0 || BMC_MAX_GLOBAL_LEDS > 0
  // BMC.hardware.leds
  setupLeds();
#endif

#if BMC_MAX_PWM_LEDS > 0
  // BMC.hardware.pwmLeds
  setupPwmLeds();
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  // BMC.hardware.buttons
  setupButtons();
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
  // BMC.hardware.encoders
  setupEncoders();
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  // BMC.hardware.pots
  setupPots();
#endif

#if BMC_MAX_NL_RELAYS > 0
  // BMC.hardware.relays
  setupRelaysNL();
#endif

#if BMC_MAX_L_RELAYS > 0
  // BMC.hardware.relays
  setupRelaysL();
#endif

  BMC_PRINTLN("");
}
/*
  Assign how hardware will behave
*/
void BMC::assignHardware() {

#if BMC_MAX_BUTTONS > 0
  // BMC.hardware.buttons
  assignButtons();
#endif

#if BMC_MAX_ENCODERS > 0
  // BMC.hardware.encoders
  assignEncoders();
#endif

#if BMC_MAX_POTS > 0
  // BMC.hardware.pots
  assignPots();
#endif

#if BMC_MAX_PIXELS > 0
  // BMC.hardware.pixels
  assignPixels();
#endif

#if BMC_MAX_RGB_PIXELS > 0
  // BMC.hardware.rgbPixels
  assignRgbPixels();
#endif

#if BMC_MAX_LEDS > 0
  // BMC.hardware.leds
  assignLeds();
#endif

#if BMC_MAX_PWM_LEDS > 0
  // BMC.hardware.pwmLeds
  assignPwmLeds();
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

#if BMC_MAX_AUX_JACKS > 0
  uint8_t _auxJacksStates = auxJacksStates;
  for(uint8_t i=0;i<BMC_MAX_AUX_JACKS;i++){
    bool state = auxJacks.isConnected(i);
    if(auxJacks.update(i)){
      if(callback.auxJackConnection){
        callback.auxJackConnection(i, state);
      }
    }
    bitWrite(_auxJacksStates, i, state);
  }
  if(_auxJacksStates != auxJacksStates){
    auxJacksStates = _auxJacksStates;
    editor.utilitySendAuxJackActivity(auxJacksStates);
  }
#endif

// read hardware that can "send" data first and LEDs/Pixels last
#if BMC_MAX_BUTTONS > 0
  // BMC.hardware.buttons
  readButtons();
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
  // BMC.hardware.buttons
  readGlobalButtons();
#endif

#if BMC_MAX_ENCODERS > 0
  // BMC.hardware.encoders
  readEncoders();
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  // BMC.hardware.encoders
  readGlobalEncoders();
#endif

#if BMC_MAX_POTS > 0
  // BMC.hardware.pots
  readPots();
#endif

#if BMC_MAX_GLOBAL_POTS > 0
  // BMC.hardware.pots
  readGlobalPots();
#endif


#if BMC_MAX_LEDS > 0
  // BMC.hardware.leds
  readLeds();
#endif

#if BMC_MAX_PWM_LEDS > 0
  // BMC.hardware.pwmLeds
  readPwmLeds();
#endif

#if BMC_MAX_PIXELS > 0
  // BMC.hardware.pixels
  readPixels();
#endif

#if BMC_MAX_RGB_PIXELS > 0
  // BMC.hardware.pixels
  readRgbPixels();
#endif

#if BMC_MAX_NL_RELAYS > 0
  // BMC.hardware.relays
  readRelaysNL();
#endif

#if BMC_MAX_L_RELAYS > 0
  // BMC.hardware.relays
  readRelaysL();
#endif


#if BMC_MAX_GLOBAL_LEDS > 0
  // BMC.hardware.leds
  readGlobalLeds();
#endif
  // keep at end of hardware read
  flags.off(BMC_FLAGS_STATUS_LED);
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

uint8_t BMC::parseUserEventType(uint8_t t_type){
  if(t_type<BMC_BUTTON_EVENT_TYPE_USER_1){
    return 0;
  }
  return parseMidiEventType(t_type)-BMC_BUTTON_EVENT_TYPE_USER_1;
}
