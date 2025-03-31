/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

// Initialize all compiled objects
BMC::BMC():
  settings(store.global.settings),
  globals(store, settings),
  layer(globals.layer),
  midi(callback, globals),
  valueTyper(callback),
  editor(store, midi, settings, messenger),
  midiClock(midi),
  midiActiveSense(midi)

  #if BMC_MAX_PRESETS > 0
    ,presets(midi)
  #endif
  #if BMC_MAX_SETLISTS > 0
    ,setLists(presets)
  #endif
  #if defined(BMC_USE_SYNC)
    ,sync(midi, midiClock, callback)
  #endif
  #if BMC_MAX_CUSTOM_SYSEX > 0
    ,customSysEx(midi)
  #endif
  #if BMC_MAX_TEMPO_TO_TAP > 0
    ,tempoToTap(midi)
  #endif
  #if BMC_MAX_TRIGGERS > 0
    ,triggers(midi)
  #endif
  #if BMC_MAX_PIXEL_PROGRAMS > 0
    ,pixelPrograms(midi)
  #endif
  #if BMC_MAX_TIMED_EVENTS > 0
    ,timedEvents(midi)
  #endif
  #if BMC_MAX_BUTTONS > 1
    // second argument is true for global buttons
    // to check which callback to use
    ,dualPress(callback, globals, false, BMC_MAX_BUTTONS)
  #endif
  #if BMC_MAX_GLOBAL_BUTTONS > 1
    // second argument is true for global buttons
    // to check which callback to use
    ,dualPressGlobal(callback, globals, true, BMC_MAX_GLOBAL_BUTTONS)
  #endif
  #ifdef BMC_DEBUG
    ,serialMonitor()
  #endif
  #if defined(BMC_HAS_DISPLAY)
    ,display(midi
    #if defined(BMC_USE_SYNC)
      ,sync
    #endif
    )
  #endif

  #if defined(BMC_USE_ON_BOARD_EDITOR)
    ,obe(editor, display)
  #endif
{
  // nothing here
}

void BMC::begin(){
  #ifdef BMC_DEBUG
    setupDebug();
  #endif

  BMC_PRINTLN("BMC::begin");

  // keep this order
  #if defined(BMC_HAS_DISPLAY)
    display.begin();
  #endif

  #if defined(BMC_USE_ON_BOARD_EDITOR)
    obe.begin();
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

  #if defined(BMC_USE_SYNC)
    sync.begin();
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
  // once all those are initialized then BMC will call the first layer and
  // send the startup preset.
  // This way if any callbacks triggered by the layer change can be triggered
  // and seen by your display.
  if(flags.toggleIfTrue(BMC_FLAGS_FIRST_LOOP)){
    BMC_PRINTLN("Running First loop()");

    #if defined(BMC_HAS_DISPLAY)
      #if BMC_MAX_ILI9341_BLOCKS > 0
        display.initILI9341Blocks();
        #if defined(BMC_HAS_TOUCH_SCREEN)
          if(!settings.getTouchScreenIsCalibrated()){
            display.touchCalibration();
            editor.saveEEPROM();
            while(1);
          }
        #endif
      #endif
      display.clearAll();
    #endif
    // set the current layer to layer 1 (0)
    // also the second parameter specifies that we want to reassign settings
    // in this case since it's the initial setup we are assigning the curent
    // data in settings to all objects that require this data
    // We do this here so that any other objects initialized after BMC
    // can receive callbacks.
    setLayer(0, true);

    // Startup Preset
    #if BMC_MAX_PRESETS > 0
      // send the startup Preset if any
      if(settings.getStartupPreset() > 0){
        delay(1);
        presets.setByIndex(settings.getStartupPreset()-1);
      }
      #if BMC_MAX_SETLISTS > 0
        // set the first setlist and trigger it's first song and part
        setLists.set(0);
        setLists.setPart(0);
      #endif
    #endif

    // start sending active sense if stored in settings
    if(settings.getActiveSenseAtStartup()){
      delay(1);
      midiActiveSense.start();
    }

    #ifdef BMC_USE_DAW_LC
      sync.daw.sendHostConnectionQuery();
    #endif

    if(callback.firstLoop){
      callback.firstLoop();
    }
    oneSecondTimer = 0;
    oneMilliSecondtimer = 0;
    BMC_PRINTLN("");
    BMC_PRINTLN("First loop() complete");
  }
  if(globals.reloadLayer()){
    reloadLayer();
  }
  if(globals.assignStoreData()){
    assignStoreData();
  }
  #if defined(BMC_USE_ON_BOARD_EDITOR)
    obe.update();
  #endif
  
  #if defined(BMC_HAS_DISPLAY)
    display.update();
    // #if defined(BMC_USE_ON_BOARD_EDITOR) && defined(BMC_HAS_TOUCH_SCREEN)
    //   obe.menuCommand(display.getTouchCommand());
    // #endif
  #endif
  
  #if BMC_MAX_TEMPO_TO_TAP > 0
    runTempoToTap();
  #endif
  
  #if BMC_MAX_TIMED_EVENTS > 0
    readTimedEvent();
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

#if defined(BMC_USE_SYNC)
    sync.update();

  #if defined(BMC_USE_FAS)
    if(sync.fas.connectionStateChanged()){
      editor.utilitySendFasState(sync.fas.getConnectedDeviceId());
    }
  #endif
#endif


  // Read/Update the hardware: buttons, leds, pots, encoders
  readHardware();

#if BMC_MAX_PIXEL_PROGRAMS > 0
    pixelPrograms.update(midiClock.isEigthNote(), midiClock.isActive());
#endif

  // handle callbacks for presets and setlist
  #if BMC_MAX_PRESETS > 0
    if(globals.triggerBankChange()){
      presets.setBank(presets.getBank(), true);
    } else if(globals.triggerPresetChange()){
      BMC_PRINTLN("Trigger Preset Change")
      presets.setPreset(presets.get(), true);
    }
    if(presets.presetChanged()){
      runPresetChanged();
    }
    if(presets.bankChanged()){
      runBankChanged();
    }
    #if BMC_MAX_SETLISTS > 0
      // used to re-trigger current preset
      setLists.update();
      if(globals.triggerSetListChange()){
        setLists.set(setLists.get());
      } else if(globals.triggerSongChange()){
        setLists.setSong(setLists.getSong());
      } else if(globals.triggerPartChange()){
        setLists.setPart(setLists.getPart());
      }
      if(setLists.setListChanged()){
        runSetListChanged();
      }
      if(setLists.songChanged()){
        runSongChanged();
      }
      if(setLists.partChanged()){
        runSongPartChanged();
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

  // used specifically when layers have changed
  if(layerChanged()){
    runLayerChanged();
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

  #if BMC_MAX_LFO > 0
    for(uint8_t i=0;i<BMC_MAX_LFO;i++){
      uint8_t lfoValue = lfo[i].getWave(micros());
      if(lfo[i].isEnabled()){
        if(lfo[i].send()){
          if(lastLfo[i] != lfoValue){
            lastLfo[i] = lfoValue;
            uint8_t channel = store.global.lfo[i].events[0]+0;
            uint8_t cc = store.global.lfo[i].events[1]+0;
            uint8_t ports = store.global.lfo[i].events[2]+0;
            midi.sendControlChange(ports, BMC_TO_MIDI_CHANNEL(channel), cc, lfoValue);
            //BMC_PRINTLN(lfoValue);
          }
          
        }
      }
    }
  #endif

  if(oneMillisecondPassed()){
    oneMilliSecondtimer = 0;
  }

  if(oneSecondPassed()){
    // tick stopwatch and runtime tracker
    stopwatch.tick();
    runTime.tick();
    
    #if defined(BMC_DEBUG)
      globals.setTimerComplete();
    #endif

#if BMC_TOTAL_POTS_AUX_JACKS > 0
    if(potCalibration.active() && globals.editorConnected()){
      editor.utilitySendAnalogInputCalibrationActivity(
        potCalibration.getDeviceType(),
        potCalibration.getIndex(),
        potCalibration.getMin(),
        potCalibration.getMax(),
        potCalibration.getValue()
      );
    }
#endif

    if(callback.oneSecondPassed){
      callback.oneSecondPassed(stopwatch.getState());
    }

    globals.resetCPU();

    if(BMC_IS_EVEN(runTime.seconds)){
      flags.on(BMC_FLAGS_STATUS_LED);
      heartbeat = millis();
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
  if(heartbeat>0 && (unsigned long)millis()-heartbeat >= 150){
    flags.off(BMC_FLAGS_STATUS_LED);
    heartbeat = 0;
  }
}

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
