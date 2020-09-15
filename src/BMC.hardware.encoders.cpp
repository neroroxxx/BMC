/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
// SETUP
void BMC::setupEncoders(){
#if BMC_MAX_ENCODERS > 0
  for(uint8_t i = 0; i < BMC_MAX_ENCODERS; i++){
    encoders[i].begin(BMCBuildData::getEncoderPinA(i),BMCBuildData::getEncoderPinB(i));
  }
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    globalEncoders[i].begin(BMCBuildData::getGlobalEncoderPinA(i),
                            BMCBuildData::getGlobalEncoderPinB(i));
  }
  assignGlobalEncoders();
#endif
}
void BMC::assignEncoder(BMCEncoder& encoder, bmcStoreEncoder& data){
  encoder.reassign();
}
#endif

#if BMC_MAX_ENCODERS > 0
void BMC::assignEncoders(){
  for(uint8_t i = 0; i < BMC_MAX_ENCODERS; i++){
    assignEncoder(encoders[i], store.pages[page].encoders[i]);
  }
}
// READ
void BMC::readEncoders(){
  bmcStorePage& pageData = store.pages[page];
  for(uint8_t i = 0; i < BMC_MAX_ENCODERS; i++){
    // GET THE PIN STATE FROM MUX
    #if BMC_MAX_MUX_IN > 0
      if(encoders[i].hasMux()){
        encoders[i].setMuxValue(0, mux.readDigital(encoders[i].getMuxPin(0)));
        encoders[i].setMuxValue(1, mux.readDigital(encoders[i].getMuxPin(1)));
      }
    #endif

    if(encoders[i].update()){
      bool increased = encoders[i].increased();
      handleEncoder(pageData.encoders[i], increased);

      uint32_t event = pageData.encoders[i].event;
      if(BMC_GET_BYTE(0, event)==BMC_EVENT_TYPE_CUSTOM && callback.encoderCustomActivity){
        callback.encoderCustomActivity(i,
                              BMC_GET_BYTE(1, event),
                              BMC_GET_BYTE(2, event),
                              BMC_GET_BYTE(3, event),
                              increased);
      } else if(callback.encoderActivity){
        callback.encoderActivity(i,increased,pageData.encoders[i]);
      }
      editor.utilitySendEncoderActivity(i, increased);
    }
  }
}
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
void BMC::assignGlobalEncoders(){
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    assignEncoder(globalEncoders[i], globalData.encoders[i]);
  }
}
// READ
void BMC::readGlobalEncoders(){
  for(uint8_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    // GET THE PIN STATE FROM MUX
#if BMC_MAX_MUX_IN > 0
    if(globalEncoders[i].hasMux()){
      globalEncoders[i].setMuxValue(0, mux.readDigital(globalEncoders[i].getMuxPin(0)));
      globalEncoders[i].setMuxValue(1, mux.readDigital(globalEncoders[i].getMuxPin(1)));
    }
#endif

    if(globalEncoders[i].update()){
      bool increased = globalEncoders[i].increased();
      handleEncoder(globalData.encoders[i], increased);

      uint32_t event = globalData.encoders[i].event;
      if(BMC_GET_BYTE(0, event)==BMC_EVENT_TYPE_CUSTOM && callback.globalEncoderCustomActivity){
        callback.globalEncoderCustomActivity(i,
                              BMC_GET_BYTE(1, event),
                              BMC_GET_BYTE(2, event),
                              BMC_GET_BYTE(3, event),
                              increased);
      } else if(callback.globalEncoderActivity){
        callback.globalEncoderActivity(i, increased, globalData.encoders[i]);
      }
      editor.utilitySendGlobalEncoderActivity(i, increased);
    }
  }
}
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
void BMC::handleEncoder(bmcStoreEncoder& data, bool increased){
  uint32_t event  = data.event;
  uint8_t type    = BMC_GET_BYTE(0,event);
  if(type == BMC_NONE){
    // inactive event
    return;
  }
  uint8_t ports   = data.ports;
  uint8_t mode    = data.mode;
  uint8_t byteA   = BMC_GET_BYTE(1,event);
  uint8_t byteB   = BMC_GET_BYTE(2,event);
  // create a temporary value so we don't always have to scope the case
  uint16_t tmp = 0;

  switch(parseMidiEventType(type)){
    case BMC_MIDI_PROGRAM_CHANGE:
      // type = midi status and channel
      // byteA = limit, BMC_SCROLL_LIMITED, BMC_SCROLL_ENDLESS
      tmp = getNewEncoderValue(
        mode,
        midi.getLocalProgram((type&0x0F)+1),
        0, 127,
        0, 127,
        increased,
        byteA
      );
      tmp = tmp & 0xFF;
      midi.send(ports, (event & 0xFFFF00FF) | (tmp<<8));
      streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), tmp);
      break;
    case BMC_MIDI_CONTROL_CHANGE:
      // type = midi status and channel
      // byteA = control #
      // byteB = limit, BMC_SCROLL_LIMITED, BMC_SCROLL_ENDLESS
      tmp = getNewEncoderValue(
        mode,
        midi.getLocalControl((type&0x0F)+1, byteA),
        0, 127,
        0, 127,
        increased,
        byteB
      );
      tmp = tmp & 0xFF;
      midi.send(ports, (event & 0xFF00FFFF) | (tmp<<16));
      streamMidi(type & 0xF0, BMC_TO_MIDI_CHANNEL(type), byteA, tmp);
      break;

    case BMC_ENCODER_EVENT_TYPE_CLOCK:
      // type = midi clock status "0xF0"
      // event (bits 8-16) = min scroll value, 0 to 300
      // event (bits 17-25) = max scroll value, 0 to 300
      // event (bit 26) = limit, BMC_SCROLL_LIMITED, BMC_SCROLL_ENDLESS
      tmp = getNewEncoderValue(
        mode,
        midiClock.getBpm(),
        0, 300,
        (event>>8) &0x1FF, (event>>17)&0x1FF,
        increased,
        bitRead(event,26)
      );
      midiClock.setBpm(tmp);
      break;

    case BMC_ENCODER_EVENT_TYPE_MENU:
      if(callback.menuCommand){
        if(byteA==BMC_MENU_UP || byteA==BMC_MENU_DOWN){
          callback.menuCommand(increased?BMC_MENU_UP:BMC_MENU_DOWN);
        } else if(byteA==BMC_MENU_LEFT || byteA==BMC_MENU_RIGHT){
          callback.menuCommand(increased?BMC_MENU_RIGHT:BMC_MENU_LEFT);
        } else if(byteA==BMC_MENU_INC || byteA==BMC_MENU_DEC){
          callback.menuCommand(increased?BMC_MENU_INC:BMC_MENU_DEC);
        }
      }
      break;
#if BMC_MAX_PIXEL_PROGRAMS > 0
    case BMC_ENCODER_EVENT_TYPE_PIXEL_PROGRAM_SCROLL:
      tmp = getNewEncoderValue(
        mode,
        pixelPrograms.getProgram(),
        0, BMC_MAX_PIXEL_PROGRAMS-1,
        byteA, byteB,
        increased,
        BMC_GET_BYTE(3,event)
      ) & 0xFF;
      pixelPrograms.setProgram(tmp);
      break;
#endif
    case BMC_ENCODER_EVENT_TYPE_PROGRAM_BANKING_SCROLL:
      // byteA (bits 0 and 1) = flags, bit-0 direction, bit-1 endless
      // byteA (bits 2 to 7) = amount (0 to 63 max then add 1 here)
      // byteB min program
      // byteC max program
      //midiProgramBankScroll(bool up, bool endless, uint8_t amount, uint8_t min, uint8_t max)
      midiProgramBankScroll(increased, bitRead(byteA, 0), (byteA>>1), byteB, BMC_GET_BYTE(3,event));
      break;

#if BMC_MAX_PAGES > 1
    case BMC_ENCODER_EVENT_TYPE_PAGES:
      // byteA = min Page
      // byteB = max Page
      tmp = getNewEncoderValue(
        mode,
        page,
        0, BMC_MAX_PAGES-1,
        byteA, byteB,
        increased,
        BMC_GET_BYTE(3,event)
      ) & 0xFF;
      setPage(tmp);
      break;
#endif

#if BMC_MAX_PRESETS > 0
    case BMC_ENCODER_EVENT_TYPE_PRESETS:
      // byteA = max Presets
      // byteB = max Presets
      // byteC = limit, BMC_SCROLL_LIMITED, BMC_SCROLL_ENDLESS
      tmp = (bmcPreset_t) getNewEncoderValue(
        mode,
        presets.get(),
        0, BMC_MAX_PRESETS-1,
        0, BMC_EVENT_TO_PRESET_NUM(event>>8),
        increased,
        BMC_GET_BYTE(3,event)
      );
      presets.set(tmp);
      break;
#endif

#ifdef BMC_USE_BEATBUDDY
    case BMC_ENCODER_EVENT_TYPE_BEATBUDDY_CMD:
      if(byteA==BMC_BEATBUDDY_CMD_SONG_SCROLL_UP || byteA==BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN){
        // with the beatbuddy a scroll UP brings you UP the song list so the
        // previous song, when you scroll DOWN you go DOWN the left iow to the
        // the next song, for this reason the encoder here is reversed so that
        // when you rotate to the encoder to the RIGHT you go to the NEXT song
        // and when you rotate to the LEFT you go to the PREVIOUS song
        if(increased){
          beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN);
        } else {
          beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_SONG_SCROLL_UP);
        }
      } else if(byteA==BMC_BEATBUDDY_CMD_BPM_DEC || byteA==BMC_BEATBUDDY_CMD_BPM_INC){
        beatBuddy.tempoControl((((mode>>1)&0x7F)+1), increased);
      }
      break;
#endif

#if BMC_MAX_LIBRARY > 1
    case BMC_ENCODER_EVENT_TYPE_LIBRARY:
      library.send(BMC_EVENT_TO_LIBRARY_NUM(event >> (increased ? 18 : 8)));
      break;
#endif

#if BMC_MAX_CUSTOM_SYSEX > 1
    case BMC_ENCODER_EVENT_TYPE_CUSTOM_SYSEX:
      customSysEx.send(ports, (increased) ? byteB : byteA);
      break;
#endif

#ifdef BMC_USE_FAS
    case BMC_ENCODER_EVENT_TYPE_FAS_PRESET:
      {
        uint16_t min = (event >> 10) & 0x3FF;
        uint16_t max = (event >> 20) & 0x3FF;
        fas.presetScroll(increased, bitRead(byteA,0), min, max);
      }
      break;
    case BMC_ENCODER_EVENT_TYPE_FAS_SCENE:
      // byteA (flags) = bit-0 limit, limited (0), endless (1)
      // byteA (flags) = bit-1 scene revert, no revert (0), revert (1)
      // byteB = minimum scene for scrolling
      // byteC = maximum scene for scrolling
      fas.sceneScroll(increased, bitRead(byteA,0), bitRead(byteA,1), byteB, BMC_GET_BYTE(2,event));
      break;
    case BMC_ENCODER_EVENT_TYPE_FAS_PARAM:
      {
        uint16_t value = fas.getSyncedParameterValue(byteB);
        tmp = getNewEncoderValue(
          mode,
          value,
          0, 65534,
          0, 65534,
          increased,
          byteA
        );
        fas.sendChangeSyncedParameter(byteB, tmp);
      }
      break;
#endif



#ifdef BMC_USE_CLICK_TRACK
    case BMC_ENCODER_EVENT_TYPE_CLICK_TRACK_FREQ:
      // byteA = min Frequency, 0 to 7, add 1 then multiple by 500
      // byteB = max Frequency, same as above
      if(increased){
        midiClock.clickTrackFreqInc((byteA+1)*500, (byteB+1)*500);
      } else {
        midiClock.clickTrackFreqDec((byteA+1)*500, (byteB+1)*500);
      }
      break;
    case BMC_ENCODER_EVENT_TYPE_CLICK_TRACK_LEVEL:
      // byteA = min Level, 0 to 10
      // byteB = max Level, 0 to 10
      if(increased){
        midiClock.clickTrackLevelInc(byteA, byteB);
      } else {
        midiClock.clickTrackLevelDec(byteA, byteB);
      }
      break;
#endif
    case BMC_ENCODER_EVENT_TYPE_USER_1:
    case BMC_ENCODER_EVENT_TYPE_USER_2:
    case BMC_ENCODER_EVENT_TYPE_USER_3:
    case BMC_ENCODER_EVENT_TYPE_USER_4:
    case BMC_ENCODER_EVENT_TYPE_USER_5:
    case BMC_ENCODER_EVENT_TYPE_USER_6:
    case BMC_ENCODER_EVENT_TYPE_USER_7:
    case BMC_ENCODER_EVENT_TYPE_USER_8:
      if(callback.userEventEncoders){
        callback.userEventEncoders(parseUserEventType(type), event, ports, mode);
      }
      break;
  }
}

uint16_t BMC::getNewEncoderValue(uint8_t mode, uint16_t value,
                                uint16_t lowest, uint16_t highest,
                                uint16_t min, uint16_t max,
                                bool increased, bool endless){
  BMCScroller <uint16_t> scroller(lowest, highest);
  scroller.increaseByPercentage(bitRead(mode,0));
  scroller.set(value, min, max);
  return scroller.scroll(((mode>>1)&0x7F)+1, increased, endless);
}
#endif
