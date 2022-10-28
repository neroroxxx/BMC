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
  for(uint16_t i = 0; i < BMC_MAX_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_ENCODER, i);
    encoders[i].begin(ui.pin, ui.pinB);
  }
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_ENCODER, i);
    globalEncoders[i].begin(ui.pin, ui.pinB);
  }
  assignGlobalEncoders();
#endif
}
/*
void BMC::assignEncoder(BMCEncoder& encoder, bmcStoreDevice <1, 1>& data){
  encoder.reassign();
}
*/
#endif




#if BMC_MAX_ENCODERS > 0
void BMC::assignEncoders(){
  for(uint16_t i = 0; i < BMC_MAX_ENCODERS; i++){
    encoders[i].reassign();
  }
}
void BMC::readEncoders(){
  //bmcStorePage& pageData = store.pages[page];

  for(uint16_t i = 0; i < BMC_MAX_ENCODERS; i++){
    bmcStoreDevice <1, 1>& device = store.pages[page].encoders[i];
    // GET THE PIN STATE FROM MUX
    #if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0 || BMC_MAX_MUX_IN_ANALOG > 0
      if(encoders[i].hasMux()){
        encoders[i].setMuxValue(0, mux.readDigital(encoders[i].getMuxPin(0)));
        encoders[i].setMuxValue(1, mux.readDigital(encoders[i].getMuxPin(1)));
      }
    #endif

    if(encoders[i].update()){
      bool increased = encoders[i].increased();
      uint8_t ticks = encoders[i].getTicks();
      bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
      //handleEncoder(pageData.encoders[i], increased, ticks);
      processEvent(BMC_DEVICE_GROUP_ENCODER, BMC_DEVICE_ID_ENCODER,
                  i, BMC_EVENT_IO_TYPE_INPUT, device.events[0],  increased<<7 | ticks);
      //uint32_t event = pageData.encoders[i].event;
      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.encoderCustomActivity){
        callback.encoderCustomActivity(i, increased, ticks);
      } else if(callback.encoderActivity){
        callback.encoderActivity(i, increased, ticks);
      }
      editor.utilitySendEncoderActivity(i, increased);
    }
  }
}
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
void BMC::assignGlobalEncoders(){
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    globalEncoders[i].reassign();
    //assignEncoder(globalEncoders[i], globalData.encoders[i]);
  }
}
// READ
void BMC::readGlobalEncoders(){
  for(uint16_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
    bmcStoreDevice <1, 1>& device = store.global.encoders[i];
    // GET THE PIN STATE FROM MUX
#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0 || BMC_MAX_MUX_IN_ANALOG > 0
    if(globalEncoders[i].hasMux()){
      globalEncoders[i].setMuxValue(0, mux.readDigital(globalEncoders[i].getMuxPin(0)));
      globalEncoders[i].setMuxValue(1, mux.readDigital(globalEncoders[i].getMuxPin(1)));
    }
#endif

    if(globalEncoders[i].update()){
      bool increased = globalEncoders[i].increased();
      uint8_t ticks = globalEncoders[i].getTicks();
      bmcStoreEvent data = globals.getDeviceEventType(device.events[0]);
      //handleEncoder(globalData.encoders[i], increased, ticks);
      processEvent(BMC_DEVICE_GROUP_ENCODER, BMC_DEVICE_ID_GLOBAL_ENCODER,
                    i, BMC_EVENT_IO_TYPE_INPUT, device.events[0], increased<<7 | ticks);

      //uint32_t event = globalData.encoders[i].event;
      if(data.type==BMC_EVENT_TYPE_CUSTOM && callback.globalEncoderCustomActivity){
        callback.globalEncoderCustomActivity(i, increased, ticks);
      } else if(callback.globalEncoderActivity){
        callback.globalEncoderActivity(i, increased, ticks);
      }
      editor.utilitySendGlobalEncoderActivity(i, increased);
    }
  }
}
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS > 0
/*
void BMC::handleEncoder(bmcStoreEncoder& data, bool increased, uint8_t ticks){
  uint32_t event  = data.event;
  uint8_t type    = BMC_GET_BYTE(0,event);
  if(type == BMC_NONE){
    // inactive event
    return;
  }
  #if defined(BMC_ENABLE_ENCODER_BUTTON_FILTERING)
    // ignore encoder readings right after a button press
    // this is to avoid issues when you press the button on an encoder and a reading
    // of the encoder is triggered by mechanical noise
    // default time 50ms
    if(encoderFixTimer.active() && !encoderFixTimer.complete()){
      return;
    }
  #endif
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
    case BMC_ENCODER_EVENT_TYPE_CC_RELATIVE:
      tmp = increased ? 1 : 65;
      midi.sendControlChangeNoLocalLog(ports, byteA, byteB,  increased ? 1 : 65);
      break;
    case BMC_ENCODER_EVENT_TYPE_NON_RELATIVE:
      tmp = increased ? 1 : 65;
      midi.sendNoteOn(ports, byteA, byteB,  increased ? 1 : 65);
      break;
    case BMC_ENCODER_EVENT_TYPE_NOFF_RELATIVE:
      tmp = increased ? 1 : 65;
      midi.sendNoteOff(ports, byteA, byteB,  increased ? 1 : 65);
      break;
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
          sync.beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN);
        } else {
          sync.beatBuddy.sendCommand(BMC_BEATBUDDY_CMD_SONG_SCROLL_UP);
        }
      } else if(byteA==BMC_BEATBUDDY_CMD_BPM_DEC || byteA==BMC_BEATBUDDY_CMD_BPM_INC){
        sync.beatBuddy.tempoControl((((mode>>1)&0x7F)+1), increased);
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
        sync.fas.presetScroll(increased, bitRead(byteA,0), min, max);
      }
      break;
    case BMC_ENCODER_EVENT_TYPE_FAS_SCENE:
      // byteA (flags) = bit-0 limit, limited (0), endless (1)
      // byteA (flags) = bit-1 scene revert, no revert (0), revert (1)
      // byteB = minimum scene for scrolling
      // byteC = maximum scene for scrolling
      sync.fas.sceneScroll(increased, bitRead(byteA,0), bitRead(byteA,1), byteB, BMC_GET_BYTE(2,event));
      break;
    case BMC_ENCODER_EVENT_TYPE_FAS_PARAM:
      {
        uint16_t value = sync.fas.getSyncedParameterValue(byteB);
        tmp = getNewEncoderValue(
          mode,
          value,
          0, 65534,
          0, 65534,
          increased,
          byteA
        );
        sync.fas.sendChangeSyncedParameter(byteB, tmp);
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

#ifdef BMC_USE_DAW_LC
    case BMC_ENCODER_EVENT_TYPE_DAW:
      if(byteA==BMC_DAW_ENC_CMD_VPOT){
        sync.daw.sendVPot(byteB, increased, ticks);
      } else if(byteA==BMC_DAW_ENC_CMD_FADER){
        sync.daw.sendEncoderFader(byteB, increased, ticks);
      } else if(byteA==BMC_DAW_ENC_CMD_FADER_MASTER){
        sync.daw.sendEncoderMasterFader(increased, ticks);
      } else if(byteA==BMC_DAW_ENC_CMD_SCRUB){
        sync.daw.sendTransportScrubWheel(increased, ticks);
      }
      break;
#endif
#if BMC_MAX_SETLISTS > 0
    case BMC_ENCODER_EVENT_TYPE_SETLIST:
      setLists.scroll(1+ticks, bitRead(byteA, 0), (byteA>>1), byteB, BMC_GET_BYTE(3,event));
      break;
    case BMC_ENCODER_EVENT_TYPE_SONG:
      setLists.scrollSong(1+ticks, bitRead(byteA, 0), (byteA>>1), byteB, BMC_GET_BYTE(3,event));
      break;
    case BMC_ENCODER_EVENT_TYPE_PART:
      setLists.scrollPart(1+ticks, bitRead(byteA, 0), (byteA>>1), byteB, BMC_GET_BYTE(3,event));
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
*/
#endif
