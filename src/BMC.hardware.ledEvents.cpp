/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

// these are used for all LEDs and Pixels
#if (BMC_TOTAL_LEDS+BMC_TOTAL_PIXELS) > 0
uint8_t BMC::handleLedEvent(uint8_t index, uint32_t event, uint8_t ledType){
  // ledType
  // 0 = page led (BMC_LED_TYPE_PAGE)
  // 1 = global led (BMC_LED_TYPE_GLOBAL)
  // 2 = PWM led (BMC_LED_TYPE_PWM)
  // 3 = pixel (BMC_LED_TYPE_PIXEL)
  // 4 = rgb pixel Red event (BMC_LED_TYPE_RGB_RED)
  // 5 = rgb pixel Green event (BMC_LED_TYPE_RGB_GREEN)
  // 6 = rgb pixel Blue event (BMC_LED_TYPE_RGB_BLUE)
  // page and global leds use the most significant bit of the even as the Blink setting
  // this is bit-31
  // pixels use the 4 most significant bits for color
  // PWM Leds use the 4 most significant bits for brightness
  uint8_t type = BMC_GET_BYTE(0, event);

  if(type == BMC_NONE){
    return 0;
  } else if(type == BMC_LED_EVENT_TYPE_CLOCK_SYNC){
    // leds with a BMC_LED_EVENT_TYPE_CLOCK_SYNC
    // are handled @BMC.midi.cpp
    // when a midi clock tick is recieved, it triggers handleClockLeds()
    // return 255 as a sign that the led state should not be changed
    // BMC_IGNORE_LED_EVENT can also be used as a return value
    return BMC_IGNORE_LED_EVENT;
  }

  uint8_t byteA = BMC_GET_BYTE(1, event);

  switch(parseMidiEventType(type)){
    case BMC_MIDI_PROGRAM_CHANGE:
      {
        uint8_t channel = BMC_TO_MIDI_CHANNEL(type);
        uint8_t pc = midi.getLocalProgram(channel);
        return pc == (byteA & 0x7F);
      }
      break;

    case BMC_MIDI_CONTROL_CHANGE:
      {
        uint8_t channel = BMC_TO_MIDI_CHANNEL(type);
        uint8_t cc = midi.getLocalControl(channel, byteA);
        return cc == (BMC_GET_BYTE(2, event) & 0x7F);
      }
      break;

    case BMC_LED_EVENT_TYPE_MIDI_ACTIVITY:
      return globals.hasMidiActivity(byteA) ? BMC_PULSE_LED_EVENT : BMC_IGNORE_LED_EVENT;

    case BMC_LED_EVENT_TYPE_PAGE:
      return byteA == page;


    case BMC_EVENT_TYPE_CUSTOM:
#if BMC_MAX_GLOBAL_LEDS > 0
      if(ledType==BMC_LED_TYPE_GLOBAL){// page led
        if(byteA<BMC_MAX_GLOBAL_LEDS){
          return globalLedCustomState.read(byteA);
        }
      }
#endif

#if BMC_MAX_LEDS > 0
      // the only reason to leave ledType here even if Global Leds are
      // not compiled is so we don't get compiler errors for the unused variable
      if(ledType==BMC_LED_TYPE_PAGE){// global led
        if(byteA<BMC_MAX_LEDS){
          return ledCustomState.read(byteA);
        }
      }
#endif

#if BMC_MAX_PWM_LEDS > 0
      if(ledType==BMC_LED_TYPE_PWM){
        if(byteA<BMC_MAX_PWM_LEDS){
          return pwmLedCustomState[byteA];
        }
      }
#endif

#if BMC_MAX_PIXELS > 0
      if(ledType==BMC_LED_TYPE_PIXEL){
        if(byteA<BMC_MAX_PIXELS){
          //uint8_t color = pixelCustomState[byteA] & 0x0F;
          //uint8_t brightness = (pixelCustomState[byteA]>>4)&0x0F;
          //return map(brightness, 0, 15, 0, 127);
          return pixelCustomState[byteA];
        }
      }
#endif

#if BMC_MAX_RGB_PIXELS > 0
      if(ledType>=BMC_LED_TYPE_RGB_RED && ledType<=BMC_LED_TYPE_RGB_BLUE){
        if(byteA<BMC_MAX_RGB_PIXELS){
          return bitRead(rgbPixelCustomState[byteA], ledType-BMC_LED_TYPE_RGB_RED);
        }
      }
#endif
      break;


    case BMC_LED_EVENT_TYPE_STATUS:
      if(byteA==BMC_LED_STATUS_STOPWATCH_STATE){
        return (stopwatch.getState()==2)?3:handleStatusLedEvent(byteA);
      } else if(byteA==BMC_LED_STATUS_BMC){
        // return 2 to pulse led, 255 to leave as is
        return handleStatusLedEvent(byteA) ? BMC_PULSE_LED_EVENT : BMC_IGNORE_LED_EVENT;
      } else {
        // return 1 if led should be fully turned on.
        return handleStatusLedEvent(byteA);
      }
      break;


#if defined(BMC_USE_BEATBUDDY)
      case BMC_LED_EVENT_TYPE_BEATBUDDY:
        return handleBeatBuddyLedEvent(byteA, BMC_GET_BYTE(2, event));
#endif


#if defined(BMC_USE_HELIX)
    case BMC_LED_EVENT_TYPE_HELIX_SNAPSHOT:
      return helix.isSnapshot(byteA);
#endif


#if defined(BMC_USE_FAS)
    case BMC_LED_EVENT_TYPE_FAS_STATE:
      if(byteA==0){
        return fas.connected();
      } else if(byteA==1){
        return fas.isTunerActive();
      } else if(byteA==2){
        return fas.tempoReceived() ? BMC_PULSE_LED_EVENT : BMC_IGNORE_LED_EVENT;
      }
      break;
    case BMC_LED_EVENT_TYPE_FAS_PRESET:
      return fas.getPresetNumber()==(byteA | BMC_GET_BYTE(2, event)<<8);
    case BMC_LED_EVENT_TYPE_FAS_SCENE:
      return fas.getSceneNumber()==byteA;
    case BMC_LED_EVENT_TYPE_FAS_BLOCK_STATE:
      {
        bool state = false;
        if(fas.connected()){
          if(byteA==0){ // on if bypassed
            state = fas.isBlockBypassed(BMC_GET_BYTE(2, event));
          } else if(byteA==1){ // on if engage
            state = fas.isBlockEngaged(BMC_GET_BYTE(2, event));
          } else if(byteA==2){ // on if X
            state = fas.isBlockX(BMC_GET_BYTE(2, event));
          } else if(byteA==3){ // on if Y
            state = fas.isBlockY(BMC_GET_BYTE(2, event));
          }
        }
        return state;
      }
      break;
#endif


#if BMC_MAX_PRESETS > 0
    case BMC_LED_EVENT_TYPE_PRESET:
      return byteA == presets.get();
    case BMC_LED_EVENT_TYPE_PRESET_IN_BANK:
      return presets.isPresetInBank(byteA);
    case BMC_LED_EVENT_TYPE_PRESETS_BANK:
      return byteA == presets.getBank();
#endif


#if BMC_MAX_SETLISTS > 0
    case BMC_LED_EVENT_TYPE_SETLIST:
      return byteA == setLists.get();
    case BMC_LED_EVENT_TYPE_SETLIST_SONG:
      return byteA == setLists.getSong();
#endif


#if BMC_MAX_BUTTONS > 0
    case BMC_LED_EVENT_TYPE_BUTTON:
      if(byteA < BMC_MAX_BUTTONS){
        #if BMC_MAX_BUTTONS > 32
          if(byteA>32){
            return bitRead(buttonStates2, byteA-32);
          } else {
            return bitRead(buttonStates, byteA);
          }
        #else
          return bitRead(buttonStates, byteA);
        #endif
      }
      break;
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
    case BMC_LED_EVENT_TYPE_GLOBAL_BUTTON:
      if(byteA < BMC_MAX_GLOBAL_BUTTONS){
        return bitRead(globalButtonStates, byteA);
      }
      break;
#endif

#if BMC_MAX_NL_RELAYS > 0
    case BMC_LED_EVENT_TYPE_NL_RELAY:
      if(byteA < BMC_MAX_NL_RELAYS){
        return bitRead(relayNLStates, byteA);
      }
      break;
#endif

#if BMC_MAX_L_RELAYS > 0
    case BMC_LED_EVENT_TYPE_L_RELAY:
      if(byteA < BMC_MAX_L_RELAYS){
        return bitRead(relayLStates, byteA);
      }
      break;
#endif

#if BMC_MAX_AUX_JACKS > 0
    case BMC_LED_EVENT_TYPE_AUX_JACK_CONNECTED:
      if(byteA < BMC_MAX_AUX_JACKS){
        return auxJacks.isConnected(byteA);
      }
      break;
#endif

#if BMC_MAX_POTS > 0
    case BMC_LED_EVENT_TYPE_POT:
      // no actual brightness, just turn the led to ON if
      // the pot value is equalto or more than 63
      if(byteA < BMC_MAX_POTS){
        if(ledType==BMC_LED_TYPE_PWM){
          return pots[byteA].getValue()+4;
        }
        return pots[byteA].getValue()>=63;
      }
      break;
  #if defined(BMC_USE_POT_TOE_SWITCH)
    case BMC_LED_EVENT_TYPE_TOE_SWITCH:
      if(byteA < BMC_MAX_POTS){
        return pots[byteA].toeSwitchGetState();
      }
      break;
  #endif
#endif

#if BMC_MAX_GLOBAL_POTS > 0
    case BMC_LED_EVENT_TYPE_GLOBAL_POT:
      // no actual brightness, just turn the led to ON if
      // the pot value is equalto or more than 63
      if(byteA < BMC_MAX_GLOBAL_POTS){
        if(ledType==BMC_LED_TYPE_PWM){
          return globalPots[byteA].getValue()+4;
        }
        return globalPots[byteA].getValue()>=63;
      }
      break;
  #if defined(BMC_USE_POT_TOE_SWITCH)
    case BMC_LED_EVENT_TYPE_GLOBAL_TOE_SWITCH:
      if(byteA < BMC_MAX_GLOBAL_POTS){
        return globalPots[byteA].toeSwitchGetState();
      }
      break;
  #endif
#endif
    case BMC_LED_EVENT_TYPE_USER_1:
    case BMC_LED_EVENT_TYPE_USER_2:
    case BMC_LED_EVENT_TYPE_USER_3:
    case BMC_LED_EVENT_TYPE_USER_4:
    case BMC_LED_EVENT_TYPE_USER_5:
    case BMC_LED_EVENT_TYPE_USER_6:
    case BMC_LED_EVENT_TYPE_USER_7:
    case BMC_LED_EVENT_TYPE_USER_8:
      if(callback.userEventLeds){
        return callback.userEventLeds(parseUserEventType(type), event, ledType);
      }
      break;
  }
  return BMC_OFF_LED_EVENT;
}

// return true if the status is matched
bool BMC::handleStatusLedEvent(uint8_t status){
  switch(status){
    case BMC_LED_STATUS_ALWAYS_ON:
      return true;
    case BMC_LED_STATUS_BMC:
      return flags.read(BMC_FLAGS_STATUS_LED);
    case BMC_LED_STATUS_EDITOR_CONNECTED:
      return globals.editorConnected();
    case BMC_LED_STATUS_HOST_CONNECTED:
      return globals.hostConnected();
    case BMC_LED_STATUS_BLE_CONNECTED:
      return globals.bleConnected();
    case BMC_LED_STATUS_ACTIVE_SENSE_SENDING:
      return midiActiveSense.active();
    case BMC_LED_STATUS_ACTIVE_SENSE_READING:
      return midiActiveSense.reading();
    case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_INPUT:
      return !midi.getRealTimeBlockInput();
    case BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_OUTPUT:
      return !midi.getRealTimeBlockOutput();
    case BMC_LED_STATUS_STOPWATCH_ACTIVE:
      return (stopwatch.getState() == 1);
    case BMC_LED_STATUS_STOPWATCH_STATE:
      return (stopwatch.getState() > 0);
    case BMC_LED_STATUS_STOPWATCH_COMPLETE:
      return (stopwatch.getState() == 2);
  }
  return false;
}

#ifdef BMC_USE_BEATBUDDY
  bool BMC::handleBeatBuddyLedEvent(uint8_t status, uint8_t data){
    switch(status){
      case BMC_LED_BEATBUDDY_SYNC:
        return beatBuddy.inSync();
      case BMC_LED_BEATBUDDY_PLAYING:
        return beatBuddy.isPlaying();
      case BMC_LED_BEATBUDDY_PART:
        return beatBuddy.isSongPart(data);
      case BMC_LED_BEATBUDDY_HALF_TIME:
        return beatBuddy.isHalfTime();
      case BMC_LED_BEATBUDDY_DOUBLE_TIME:
        return beatBuddy.isDoubleTime();
    }
    return false;
  }
#endif

void BMC::handleClockLeds(){

#if BMC_MAX_LEDS > 0
  for(uint8_t index = 0; index < BMC_MAX_LEDS; index++){
    bmcStoreLed& item = store.pages[page].leds[index];
    if(BMCTools::isMidiClockLedEvent(item.event)){
      leds[index].pulse();
    }
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  for(uint8_t index = 0; index < BMC_MAX_GLOBAL_LEDS; index++){
    bmcStoreLed& item = globalData.leds[index];
    if(BMCTools::isMidiClockLedEvent(item.event)){
      globalLeds[index].pulse();
    }
  }
#endif

#if BMC_MAX_PWM_LEDS > 0
  for(uint8_t index = 0; index < BMC_MAX_PWM_LEDS; index++){
    bmcStoreLed& item = store.pages[page].pwmLeds[index];
    if(BMCTools::isMidiClockLedEvent(item.event)){
      pwmLeds[index].pulse(((BMC_GET_BYTE(3, item.event)) & 0x7F));
    }
  }
#endif

#if BMC_MAX_PIXELS > 0
  for(uint8_t index = 0; index < BMC_MAX_PIXELS; index++){
    bmcStoreLed& item = store.pages[page].pixels[index];
    // first bit is always the "blink" state
    if(BMCTools::isMidiClockLedEvent(item.event)){
      // last 4 bits are always the color
      pixels.pulse(index, (BMC_GET_BYTE(3, item.event) >> 4));
    }
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0
  for(uint8_t index = 0; index < BMC_MAX_RGB_PIXELS; index++){
    bmcStoreRgbLed& item = store.pages[page].rgbPixels[index];
    if(BMCTools::isMidiClockLedEvent(item.red)){
      pixels.pulseRgb(index, 0);
    }
    if(BMCTools::isMidiClockLedEvent(item.green)){
      pixels.pulseRgb(index, 1);
    }
    if(BMCTools::isMidiClockLedEvent(item.blue)){
      pixels.pulseRgb(index, 2);
    }
  }
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

  #if BMC_MAX_PWM_LEDS > 0
    pwmLeds[0].overrideState(t_value?127:0);
  #endif

  #if BMC_MAX_PIXELS > 0
    pixels.setState(0, t_value?255:0);
  #endif

  #if BMC_MAX_RGB_PIXELS > 0
    pixels.setStateRgb(0, 0, t_value);
  #endif
}
#endif
