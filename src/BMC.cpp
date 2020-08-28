/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>
// Initialize all compiled objects
BMC::BMC():
  globals(),
  globalData(store.global),
  settings(store.global.settings),
  midi(callback, globals, store.global.portPresets),
  valueTyper(callback),
  editor(store, midi, settings, messenger),
  midiClock(midi),
  midiActiveSense(midi)
  #ifdef BMC_USE_BEATBUDDY
    ,beatBuddy(midi,midiClock)
  #endif
  #ifdef BMC_USE_HELIX
    ,helix(midi)
  #endif
  #ifdef BMC_USE_FAS
    ,fas(midi, globals)
  #endif
  #ifdef BMC_USE_KEMPER
    ,kemper(midi)
  #endif
  #if BMC_MAX_CUSTOM_SYSEX > 0
    ,customSysEx(midi, store.global)
  #endif
  #if BMC_MAX_LIBRARY > 0
    #if BMC_MAX_CUSTOM_SYSEX > 0
      ,library(midi, store.global, customSysEx)
    #else
      ,library(midi, store.global)
    #endif
    #if BMC_MAX_PRESETS > 0
      ,presets(midi, store.global, library)
      #if BMC_MAX_SETLISTS > 0
        ,setLists(store.global, presets)
      #endif
    #endif
  #endif
  #if BMC_MAX_TEMPO_TO_TAP > 0
    ,tempoToTap(midi, store.global)
  #endif
  #if BMC_MAX_TRIGGERS > 0
    ,triggers(midi, store.global)
  #endif
  #if BMC_MAX_BUTTONS > 0
    // second argument is true for global buttons
    // to check which callback to use
    ,dualPress(callback, false)
  #endif
  #if BMC_MAX_GLOBAL_BUTTONS > 0
    // second argument is true for global buttons
    // to check which callback to use
    ,dualPressGlobal(callback, true)
  #endif
  #ifdef BMC_DEBUG
    ,serialMonitor()
  #endif
{
  // nothing here
}

void BMC::begin(){
  // keep this order
  #ifdef BMC_DEBUG
    setupDebug();
    BMC_PRINTLN("BMC::begin");
  #endif

  // setup all MIDI Ports being used
  midi.begin();

  // setup midi clock
  midiClock.begin();

  // setup midi active sense
  midiActiveSense.begin();

  // load intial data from EEPROM, etc.
  editor.begin();

  // here we handle pin assignments during the initial setup
  setupHardware();

  #ifdef BMC_USE_CLICK_TRACK
    // the click track object is tied to the MIDI Clock since they work hand in hand.
    // here we setup all the initial data from settings.
    // the CT frequency is stored in 3 bits, a value of 0 to 7
    // 0 to 7, where 0 = 500Hz, 1 = 1000Hz, 2= 1500Hz, up to 4000Hz
    // we add 1 to the stored value and multiply it by 500 to get the frequency
    midiClock.clickTrackSetFrequency( (settings.getClickTrackFrequency()+1) * 500 );
    // track level is 0 to 10
    midiClock.clickTrackSetLevel(settings.getClickTrackLevel());
    // mute or unmuted at startup
    if(settings.getClickTrackMuteState()){
      midiClock.clickTrackMute();
    } else {
      midiClock.clickTrackUnmute();
    }
  #endif

  midi.setRealTimeBlockInput(settings.getMidiRealTimeBlockInput());
  midi.setRealTimeBlockOutput(settings.getMidiRealTimeBlockOutput());

  BMC_INFO("BMC Initial Setup Complete!");

  delay(100);

  #ifdef BMC_USE_FAS
    fas.begin();
  #endif

  // this flag will allow BMC to execute some code only the first time update() runs
  // yes that code can run here instead HOWEVER by letting that code execute
  // after the first loop we are allowing other classes with a begin() method
  // do their thing
  flags.on(BMC_FLAGS_FIRST_LOOP);
}

void BMC::update(){
  // even tho this could be done in the begin() method BMC will do a few things
  // only when the very first bmc.update() method is called.
  // this is so you can initialize other things in your sketch, like displays
  // once all those are initialized then BMC will call the first page and
  // send the startup preset.
  // This way if any callbacks triggered by the page change can be triggered
  // and seen by your display.
  if(flags.toggleIfTrue(BMC_FLAGS_FIRST_LOOP)){
    BMC_PRINTLN("FIRST loop()");
    BMC_PRINTLN("");
    // set the current page to page 1 (0)
    // also the second parameter specifies that we want to reassign settings
    // in this case since it's the initial setup we are assigning the curent
    // data in settings to all objects that require this data
    // We do this here so that any other objects initialized after BMC
    // can receive callbacks.
    setPage(0, true);

    // Startup Preset
    #if BMC_MAX_LIBRARY > 0 && BMC_MAX_PRESETS > 0
      // send the startup Preset if any
      if(settings.getMidiStartup()){
        delay(1);
        presets.send(globalData.startup);
      }
    #endif

    // start sending active sense if stored in settings
    if(settings.getActiveSenseAtStartup()){
      delay(1);
      midiActiveSense.start();
    }
    if(callback.firstLoop){
      callback.firstLoop();
    }
    oneSecondTimer = 0;
    oneMilliSecondtimer = 0;
  }

  #if BMC_MAX_TEMPO_TO_TAP > 0
    tempoToTap.update();
  #endif

  editor.update();

  // read the midi input ports
  // this method is in BMC.midi.cpp
  readMidi();

  // this callback is called in the middle of BMC's update method
  // use it when you need to run code in your sketch more often.
  // on your sketch's setup just add bmc.onMidUpdate(yourFunction);
  // then in the loop function of your sketch add the same yourFunction
  // before  bmc.update(); then yourFunction will run twice per loop()
  // readMidi() and readHardware() are the slowest functions in BMC
  // hence why this callback is right between them
  if(callback.midUpdate){
    callback.midUpdate();
  }

#ifdef BMC_USE_HELIX
    helix.update();
#endif

#ifdef BMC_USE_FAS
    fas.update();
    if(fas.connectionStateChanged()){
      editor.utilitySendFasState(fas.getConnectedDeviceId());
    }
#endif

#ifdef BMC_USE_KEMPER
    kemper.update();
#endif

  // Read/Update the hardware: buttons, leds, pots, encoders
  readHardware();

  // handle callbacks for presets and setlist
  #if BMC_MAX_PRESETS > 0
    if(presets.presetChanged()){
      editor.utilitySendPreset(presets.get());
      char presetName[30] = "";
      presets.getName(presets.get(), presetName);
      streamToSketch(BMC_ITEM_ID_PRESET, presets.get(), presetName);
      if(callback.presetChanged){
        callback.presetChanged(presets.get());
      }
    }
    if(presets.bankChanged()){
      if(callback.presetBankChanged){
        callback.presetBankChanged(presets.getBank());
      }
    }
    #if BMC_MAX_SETLISTS > 0
      if(setLists.setListChanged()){
        char setListName[30] = "";
        setLists.getName(setLists.get(), setListName);
        streamToSketch(BMC_ITEM_ID_SETLIST, setLists.get(), setListName);
        if(callback.setListChanged){
          callback.setListChanged(setLists.get());
        }
      }
      if(setLists.songChanged()){
        char songName[30] = "";
        presets.getName(setLists.getSongPreset(), songName);
        streamToSketch(BMC_ITEM_ID_SETLIST_SONG, setLists.getSong(), songName);
        if(callback.setListSongChanged){
          callback.setListSongChanged(setLists.getSong());
        }
      }
    #endif
  #endif

  //
  #ifdef BMC_USE_CLICK_TRACK
    // this is only used if the editor is connected, tells the editor app
    // that the frequency, level or mute state on the click track has changed.
    if(
      (midiClock.clickTrackDataChanged() && globals.editorConnected()) ||
      flags.toggleIfTrue(BMC_FLAGS_CLICK_TRACK_RESPOND)
    ){
      // turn off the flag just in case since this if statement may be
      // triggered by the first 2 arguments while the flag may be on as well
      // in which case this statement will be triggered twice
      flags.off(BMC_FLAGS_CLICK_TRACK_RESPOND);
      editor.utilitySendClickTrackData(
        midiClock.clickTrackGetFrequency(),
        midiClock.clickTrackGetLevel(),
        midiClock.clickTrackGetMuteState()
      );
    }
  #endif

  // used specifically when pages have changed
  if(pageChanged()){
    #if BMC_MAX_AUX_JACKS > 0
      auxJacks.reAssignPins();
    #endif
    #if BMC_MAX_BUTTONS > 1
      dualPress.pageChanged();
    #endif
  }

  // read the input of the serial monitor
  #ifdef BMC_DEBUG
    readDebug();
  #endif

  // send out midi activity callbacks
  if(callback.midiActivity && globals.hasMidiActivity()){
    callback.midiActivity(
      globals.midiInActivity(),
      globals.midiOutActivity()
    );
  }
  if(callback.midiLocalUpdate && globals.midiLocalUpdate()){
    callback.midiLocalUpdate();
  }

  // update globals clearing some flags that may need to be used only once
  globals.update();

  // handle timeout for tmpScroller
  tmpScroller.update();

  if(oneMillisecondPassed()){
    oneMilliSecondtimer = 0;
  }

  if(oneSecondPassed()){
    // tick stopwatch and runtime tracker
    stopwatch.tick();
    runTime.tick();

    if(callback.oneSecondPassed){
      callback.oneSecondPassed(stopwatch.getState());
    }

    globals.resetCPU();

    if(BMC_IS_EVEN(runTime.seconds)){
      flags.on(BMC_FLAGS_STATUS_LED);
      // only do this every other second
#ifdef BMC_DEBUG
      if(globals.getMetricsDebug()){
        BMC_PRINTLN(">>>",globals.getCPU(), "loops/s, Free RAM:", globals.getRAM(),"<<<");
      }
#endif
    }
    //globals.resetCPU();
    oneSecondTimer = 0;
  }
}

#if BMC_MAX_PRESETS > 0 || BMC_MAX_PAGES > 1
  // tmp Scroller
  void BMC::triggerTmpScroller(){
    if(tmpScroller.isActive()){
      bool isPreset = tmpScroller.isPreset();
      uint16_t value = tmpScroller.get();

#if BMC_MAX_PRESETS > 0
      if(isPreset){
        char str[30] = "";
        sprintf(str,"Preset %03u",value+1);
        presets.set(value);
        return;
      }
#endif

#if BMC_MAX_PAGES > 1
      if(!isPreset){
        char str[30] = "";
        sprintf(str,"Page %03u",value+1);
        setPage(value);
      }
#endif
    }
  }
#endif


void BMC::stopwatchCmd(uint8_t cmd, uint8_t h, uint8_t m, uint8_t s){
  switch(cmd){
    case BMC_STOPWATCH_CMD_STOP:
      stopwatch.stop();
      break;
    case BMC_STOPWATCH_CMD_START:
      if((h+m+s)>0){
        stopwatch.set(h, m, s);
      }
      stopwatch.start();
      break;
    case BMC_STOPWATCH_CMD_RESET:
      stopwatch.reset();
      break;
    case BMC_STOPWATCH_CMD_TOGGLE:
      if((h+m+s)>0){
        stopwatch.set(h, m, s);
      }
      stopwatch.toggle();
      break;
    case BMC_STOPWATCH_CMD_TOGGLE_RESET:
      if((h+m+s)>0){
        stopwatch.set(h, m, s);
      }
      stopwatch.toggleReset();
      break;
  }
}
