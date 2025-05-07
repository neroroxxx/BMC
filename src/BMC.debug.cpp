/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if defined(BMC_DEBUG)
void BMC::setupDebug(){
  
  #if defined(BMC_FOR_ESP32)
    Serial.begin(115200);
    delay(500);
  #endif

  serialMonitor.setup();

  // BMC_PRINTLN(__FILE__ " " __DATE__ " " __TIME__);
  
  BMC_INFO(
    "Badass MIDI Controller (BMC)",
    "For more info and to download/access the Editor",
    "Visit https://www.RoxXxtar.com/BMC",
    "BMC DEBUG is enabled",
    "You can type help in the Serial Monitor",
    "to see a list of commands available.",
    "Once you are done Debugging delete the",
    "line '#define BMC_DEBUG' from your config"
  );
  printBoardInfo();
  BMC_PRINTLN("");
}
void BMC::printDebugHeader(char* str){
  BMC_PRINTLN("");
  BMC_PRINTLN("====================", str, "====================");
  BMC_PRINTLN("");
}
void BMC::readDebug(){
  //debugInput must be 25 chars long
  char debugInput[25];
  if(!serialMonitor.read(debugInput)){
    return;
  }
  uint8_t serX = 255;
  if(BMCTools::isValidAnalogReadCommand(debugInput)){
    return;
  } else if(BMCTools::isValidDigitalReadCommand(debugInput)){
    return;
#if BMC_MAX_CUSTOM_SYSEX > 0
  } else if(BMCTools::isValidCustomSysExCommand(debugInput, serX)){
    customSysEx.send(BMC_CUSTOM_SYSEX_SEND_A, BMC_USB, serX);
    return;
#endif
  }
  if(BMC_STR_MATCH(debugInput,"") || BMC_STR_MATCH(debugInput,"help")){
    //debugInput = "help";
    strcpy(debugInput,"help");
    printDebugHeader(debugInput);

    BMC_PRINTLN("SYSTEM:");
    BMC_PRINTLN(" - version = Displays the BMC Library version and the Version store in EEPROM");
    BMC_PRINTLN(" - storage = Displays details of the Storage");
    BMC_PRINTLN(" - storageDebug = Prints the time it takes to read/write/clear EEPROM everytime the actions happens");
    BMC_PRINTLN(" - build = Displays build details");
    BMC_PRINTLN(" - board = Print Board Info");
    BMC_PRINTLN(" - objects = Displays the sizes of many objects used by BMC");

#if defined(BMC_USE_SYNC)
    BMC_PRINTLN(" - sync = Displays the Sync Features Available");
#endif
    
#ifdef BMC_HAS_HARDWARE
    BMC_PRINTLN(" - pins = Displays the pins for buttons/leds/pots/encoders");
#endif

#ifdef BMC_USE_FAS
    BMC_PRINTLN(" - fasConnection = Toggle the connection state of a FAS device");
    BMC_PRINTLN(" - fasDebug = Toggle Additional debug information of synced FAS device");
#endif

    BMC_PRINTLN(" - metrics = Prints some metrics of the performance of BMC like loops per second, etc. Happens every other second.");
    BMC_PRINTLN(" - nextLayer = Go to next layer");
    BMC_PRINTLN(" - prevLayer = Go to previous layer");
    BMC_PRINTLN(" - runTime = Displays how long BMC has been running.");
    BMC_PRINTLN(" - stopwatch = Displays Stopwatch info.");
    
    BMC_PRINTLN("\nPORTS:");
    BMC_PRINTLN(" - midiIn = Toggles displaying all incoming MIDI Messages (excludes Clock)");
    BMC_PRINTLN(" - midiOut = Toggles displaying all outgoing MIDI Messages (excludes Clock)");
    BMC_PRINTLN(" - midiInClock = Toggles displaying Incoming Clock Messages & Active Sense (midiIn must be on)");
    BMC_PRINTLN(" - midiOutClock = Toggles displaying Outgoing Clock Messages & Active Sense (midiOut must be on)");
    BMC_PRINTLN(" - midiClockInfo = Displays MIDI Clock Mode, BPM and other runtime information.");
    BMC_PRINTLN(" - flush = flush midi buffers.");

#ifdef BMC_MIDI_BLE_ENABLED
    BMC_PRINTLN(" - bleDebug = Toggles BLE MIDI Debugging, displays Incoming/Outgoing BLE Packet arrays.");
    BMC_PRINTLN(" - disconnectBLE = Disconnect the BLE Module if connected.");
#endif

    BMC_PRINTLN("\nDEVICES");
    
#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
    BMC_PRINTLN(" - buttons = Toggles displaying buttons activity");
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERSS > 0
    BMC_PRINTLN(" - encoders = Toggles displaying encoder activity");
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
    BMC_PRINTLN(" - pots = Toggle debugging layer and global pots output.");
#endif

#if defined(BMC_HAS_DISPLAY)
    BMC_PRINTLN(" - displayRenderTime = Display rendering time for displays.");
#endif

#if BMC_MAX_CUSTOM_SYSEX > 0
    BMC_PRINTLN(" - customSysEx = Send the specified Custom SysEx message to the USB ports");
#endif

    
    printDebugHeader(debugInput);

#ifdef BMC_USE_FAS
  } else if(BMC_STR_MATCH(debugInput,"fasConnection")){
    printDebugHeader(debugInput);
    if(sync.fas.connected()){
      sync.fas.disconnect();
    } else {
      sync.fas.connect();
    }
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"fasDebug")){
    printDebugHeader(debugInput);
    BMC_PRINTLN("FAS Debug:",globals.toggleFasDebug());
    printDebugHeader(debugInput);
  } else if(BMC_STR_MATCH(debugInput,"flush")){
    printDebugHeader(debugInput);
    midi.flush();
    printDebugHeader(debugInput);

#endif

  } else if(BMC_STR_MATCH(debugInput, "storage")){
    printDebugHeader(debugInput);
    printStorageInfo();
    printDebugHeader(debugInput);
    
  } else if(BMC_STR_MATCH(debugInput, "storageDebug")){
    printDebugHeader(debugInput);
    BMC_PRINTLN("Storage Debug:",globals.toggleStorageDebug());
    editor.printStorageInfo();
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"runTime")){
    printDebugHeader(debugInput);
    BMC_PRINTLN("millis()", millis());
    BMC_PRINTLN(runTime.getSeconds(), "seconds");
    BMC_PRINTLN(runTime.getMinutes(), "minutes");
    BMC_PRINTLN(runTime.getHours(), "hours");
    BMC_PRINTLN(runTime.getDays(), "days");
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"pots")){
    printDebugHeader(debugInput);
    BMC_PRINTLN("pots debug", globals.togglePotsDebug());
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"displayRenderTime")){
    printDebugHeader(debugInput);
    BMC_PRINTLN("Display Render Time", globals.toggleDisplayRenderTimeDebug());
    printDebugHeader(debugInput);

    

  } else if(BMC_STR_MATCH(debugInput,"stopwatch")){
    printDebugHeader(debugInput);
    if(stopwatch.getState()==0){
      BMC_PRINTLN("Stopwatch Inactive");
    } else if(stopwatch.getState()==1){
      BMC_PRINTLN("Stopwatch Active");
    } else if(stopwatch.getState()==2){
      BMC_PRINTLN("Stopwatch Complete");
    }

    BMC_PRINTLN(stopwatch.hours, "hours");
    BMC_PRINTLN(stopwatch.minutes, "minutes");
    BMC_PRINTLN(stopwatch.seconds, "seconds");
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"board")){
    printDebugHeader(debugInput);
    printBoardInfo();
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"sync")){
    #if defined(BMC_USE_SYNC)
    printDebugHeader(debugInput);
    sync.printDebug();
    printDebugHeader(debugInput);
    #endif

    


#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS> 0
  } else if(BMC_STR_MATCH(debugInput,"buttons")){
    printDebugHeader(debugInput);

    BMC_PRINTLN("Buttons Debug", globals.toggleButtonsDebug() ?"on":"off");

    BMC_PRINT("Debounce Mode:");
    switch(settings.getButtonDebounceMode()){
      case BMC_DEBOUNCE_MODE_DEFAULT:     BMC_PRINTLN("BMC_DEBOUNCE_MODE_DEFAULT"); break;
      case BMC_DEBOUNCE_MODE_RESPONSIVE:  BMC_PRINTLN("BMC_DEBOUNCE_MODE_RESPONSIVE"); break;
      case BMC_DEBOUNCE_MODE_FILTER:      BMC_PRINTLN("BMC_DEBOUNCE_MODE_FILTER"); break;
      case BMC_DEBOUNCE_MODE_SMART:       BMC_PRINTLN("BMC_DEBOUNCE_MODE_SMART"); break;
    }
    
    BMC_PRINTLN("Hold Time:", (500 + (settings.getButtonHoldThreshold() * 250)), "ms");
    BMC_PRINTLN("Double Press Window:", (300 + (settings.getButtonDoublePressWindow() * 50)), "ms");
    BMC_PRINTLN("Continuous Time:", (300 + (settings.getButtonContinuousTime() * 50)), "ms");

    printDebugHeader(debugInput);
#endif

#if BMC_MAX_ENCODERS > 0 || BMC_MAX_GLOBAL_ENCODERS> 0
  } else if(BMC_STR_MATCH(debugInput,"encoders")){
    printDebugHeader(debugInput);
    BMC_PRINTLN("encoders debug", globals.toggleEncodersDebug());
    printDebugHeader(debugInput);
#endif

  } else if(BMC_STR_MATCH(debugInput,"metrics")){

    printDebugHeader(debugInput);
    bool v = globals.toggleMetricsDebug();
    BMC_PRINTLN("metrics", v);
    if(v){
      BMC_PRINTLN("type \"metrics\" to stop seeing this...");
      BMC_PRINTLN("metrics are shown every 2 seconds");
      BMC_PRINTLN("Please keep in mind, loops per second is just to estimate how fast the loop() function is executing");
      BMC_PRINTLN("Some features may increase or decrease this number");
    }
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"nextLayer")){

    nextLayer();

  } else if(BMC_STR_MATCH(debugInput,"prevLayer")){

    prevLayer();

  } else if(BMC_STR_MATCH(debugInput,"midiIn")){

    printDebugHeader(debugInput);
    BMC_PRINTLN("midiIn", globals.toggleMidiInDebug());
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"midiInClock")){

    printDebugHeader(debugInput);
    BMC_PRINTLN("midiInClock", globals.toggleMidiInClockDebug());
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"midiOut")){

    printDebugHeader(debugInput);
    BMC_PRINTLN("midiOut", globals.toggleMidiOutDebug());
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"midiOutClock")){

    printDebugHeader(debugInput);
    BMC_PRINTLN("midiOutClock",globals.toggleMidiOutClockDebug());
    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"midiClockInfo")){

      printDebugHeader(debugInput);

      BMC_PRINTLN("midiClockInfo", globals.toggleMidiClockDebug());

      #if defined(BMC_USE_PRECISION_MIDI_CLOCK)
        BMC_PRINTLN("Timer: Precision");
      #else
        BMC_PRINTLN("Timer: micros()");
      #endif

      if(midiClock.isMaster()){
        BMC_PRINTLN("Mode: Master");
      } else {
        BMC_PRINTLN("Mode: Slave");
      }

      BMC_PRINTLN(
        "Port:", BMCTools::printPortsNames(midi.getClockPort())
      );

      BMC_PRINTLN("Currently @", midiClock.getBpm(), "BPM");

      printDebugHeader(debugInput);

#ifdef BMC_MIDI_BLE_ENABLED
  } else if(BMC_STR_MATCH(debugInput,"bleDebug")){
    printDebugHeader(debugInput);
    BMC_PRINTLN("BLE Debug", globals.toggleBleDebug());
    printDebugHeader(debugInput);
  } else if(BMC_STR_MATCH(debugInput,"disconnectBLE")){
    printDebugHeader(debugInput);
    midi.disconnectBLE();
    printDebugHeader(debugInput);

#endif



  } else if(BMC_STR_MATCH(debugInput,"version")){

    printDebugHeader(debugInput);
    BMC_PRINTLN("BMC Library Version", BMC_VERSION_STR);
    BMC_PRINTLNNS("BMC Library Version stored in EEPROM ",'"',BMC_GET_BYTE(1,store.version),".",BMC_GET_BYTE(0,store.version),'"');

    printDebugHeader(debugInput);

  } else if(BMC_STR_MATCH(debugInput,"build")){

    printDebugHeader(debugInput);
    BMC_PRINTLN("BMC_DEVICE_NAME:",BMC_DEVICE_NAME);
    BMC_PRINT("BMC_EDITOR_SYSEX_ID:",BMC_EDITOR_SYSEX_ID);
    BMC_PRINTNS("0x");
    BMC_PRINT_HEX(BMC_EDITOR_SYSEX_ID);
    BMC_PRINTLN("");
    editor.printDevicesInfo();
    BMC_PRINTLN("");
    printDebugHeader(debugInput);
#ifdef BMC_HAS_HARDWARE
  } else if(BMC_STR_MATCH(debugInput,"pins")){

    printDebugHeader(debugInput);

    #if BMC_MAX_BUTTONS > 0
    BMC_PRINTLN("Buttons:");
    for(uint8_t i = 0; i < BMC_MAX_BUTTONS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pin:",BMCBuildData::getButtonPin(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_ENCODERS > 0
    BMC_PRINTLN("Encoders:");
    for(uint8_t i = 0; i < BMC_MAX_ENCODERS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pinA:",BMCBuildData::getEncoderPinA(i),"| pinB:",BMCBuildData::getEncoderPinB(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_POTS > 0
    BMC_PRINTLN("Pots:");
    for(uint8_t i = 0; i < BMC_MAX_POTS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pin:",BMCBuildData::getPotPin(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_LEDS > 0
    BMC_PRINTLN("Leds:");
    for(uint8_t i = 0; i < BMC_MAX_LEDS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pin:",BMCBuildData::getLedPin(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS > 0
    BMC_PRINTLN("Global Buttons:");
    for(uint8_t i = 0; i < BMC_MAX_GLOBAL_BUTTONS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pin:",BMCBuildData::getGlobalButtonPin(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_GLOBAL_ENCODERS > 0
    BMC_PRINTLN("Global Encoders:");
    for(uint8_t i = 0; i < BMC_MAX_GLOBAL_ENCODERS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pinA:",BMCBuildData::getGlobalEncoderPinA(i),"| pinB:",BMCBuildData::getGlobalEncoderPinB(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_GLOBAL_POTS > 0
    BMC_PRINTLN("Global Pots:");
    for(uint8_t i = 0; i < BMC_MAX_GLOBAL_POTS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pin:",BMCBuildData::getGlobalPotPin(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_GLOBAL_LEDS > 0
    BMC_PRINTLN("Global Leds:");
    for(uint8_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pin:",BMCBuildData::getGlobalLedPin(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_NL_RELAYS > 0
    BMC_PRINTLN("NL Relays:");
    for(uint8_t i = 0; i < BMC_MAX_NL_RELAYS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pin:",BMCBuildData::getRelayNLPin(i));
    }
    BMC_PRINTLN("");
    #endif

    #if BMC_MAX_L_RELAYS > 0
    BMC_PRINTLN("NL Relays:");
    for(uint8_t i = 0; i < BMC_MAX_L_RELAYS; i++){
      //BMC_PRINTLN("#",i+1,"connected to pinA:",BMCBuildData::getRelayLPinA(i),"| pinB:",BMCBuildData::getRelayLPinB(i));
    }
    BMC_PRINTLN("");
    #endif

    printDebugHeader(debugInput);

#endif

  } else if(BMC_STR_MATCH(debugInput,"objects")){

    printDebugHeader(debugInput);
    BMC_PRINTLN("sizeof BMC",sizeof(BMC),"bytes");
    BMC_PRINTLN("");
    BMC_PRINTLN("sizeof BMCMidi",sizeof(BMCMidi),"bytes");
    BMC_PRINTLN("sizeof BMCMidiData",sizeof(BMCMidiData),"bytes");
    BMC_PRINTLN("sizeof BMCEditor",sizeof(BMCEditor),"bytes");
    BMC_PRINTLN("sizeof BMCMidiClock",sizeof(BMCMidiClock),"bytes");
    BMC_PRINTLN("sizeof BMCMidiActiveSense",sizeof(BMCMidiActiveSense),"bytes");

    #ifdef BMC_USE_BEATBUDDY
      BMC_PRINTLN("sizeof BMCBeatBuddy",sizeof(BMCBeatBuddy),"bytes");
    #endif

    #ifdef BMC_USE_HELIX
      BMC_PRINTLN("sizeof BMCHelix",sizeof(BMCHelix),"bytes");
    #endif

    #if defined(BMC_USE_FAS)
      #if defined(BMC_USE_FAS3)
        // BMC_PRINTLN("fas",sizeof(BMCFas),"BMCFasBlocks",sizeof(BMCFasBlocks),"BMCFasData",sizeof(BMCFasData));
      #else
        BMC_PRINTLN("fas",sizeof(BMCFas),"BMCFasBlocks",sizeof(BMCFasBlocks),"BMCFasData",sizeof(BMCFasData));
      #endif
    #endif

    #ifdef BMC_USE_KEMPER
      // BMC_PRINTLN("kemper",sizeof(kemper));
    #endif

    #if BMC_MAX_BUTTONS > 0
      BMC_PRINTLN("sizeof BMCButton",sizeof(BMCButton),"bytes,",sizeof(buttons),"bytes total");
    #endif

    #if BMC_MAX_POTS > 0
      BMC_PRINTLN("sizeof BMCPot",sizeof(BMCPot),"bytes,",sizeof(pots),"bytes total");
    #endif

    #if BMC_MAX_ENCODERS > 0
      BMC_PRINTLN("sizeof BMCEncoder",sizeof(BMCEncoder),"bytes,",sizeof(encoders),"bytes total");
    #endif

    #if BMC_MAX_LEDS > 0
      BMC_PRINTLN("sizeof BMCLed",sizeof(BMCLed),"bytes,",sizeof(leds),"bytes total");
    #endif
    
    #if BMC_MAX_PIXELS > 0 || BMC_MAX_RGB_PIXELS > 0
      BMC_PRINTLN("sizeof BMCPixels",sizeof(BMCPixels),"bytes");
    #endif

    #if BBMC_MAX_GLOBAL_BUTTONS > 0
      BMC_PRINTLN("sizeof BMCButton",sizeof(BMCButton),"bytes,",sizeof(globalButtons),"bytes total");
    #endif

    #if BBMC_MAX_GLOBAL_POTS > 0
      BMC_PRINTLN("sizeof BMCPot",sizeof(BMCPot),"bytes,",sizeof(globalPots),"bytes total");
    #endif

    #if BBMC_MAX_GLOBAL_ENCODERS > 0
      BMC_PRINTLN("sizeof BMCEncoder",sizeof(BMCEncoder),"bytes,",sizeof(globalEncoders),"bytes total");
    #endif

    #if BMC_MAX_GLOBAL_LEDS > 0
      BMC_PRINTLN("sizeof BMCLed (global)",sizeof(BMCLed),"bytes,",sizeof(globalLeds),"bytes total");
    #endif
    #if BMC_MAX_NL_RELAYS > 0
      BMC_PRINTLN("sizeof BMCRelayNL",sizeof(BMCRelayNL),"bytes,",sizeof(relaysNL),"bytes total");
    #endif
    #if BMC_MAX_L_RELAYS > 0
      BMC_PRINTLN("sizeof BMCRelayL",sizeof(BMCRelayNL),"bytes,",sizeof(relaysL),"bytes total");
    #endif

    printDebugHeader(debugInput);

  } else {

    BMC_PRINTLN("");
    BMC_PRINTLN("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    BMC_PRINTLN(debugInput,"is NOT a valid command");
    BMC_PRINTLN("Type \"help\" to view all available commands");
    BMC_PRINTLN("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    BMC_PRINTLN("");

  }
}
void BMC::printBoardInfo(){
  BMC_INFO_HEAD;

  BMC_PRINTLN("Device Name:", BMC_DEVICE_NAME);
  #if defined(TEENSYDUINO)
    BMC_PRINTLN("Compiled with Teensyduino", TEENSYDUINO);  
  #endif

  #if __cplusplus == 201402L
    BMC_PRINTLN("C++14");
  #elif __cplusplus == 201703L
    BMC_PRINTLN("C++17");
  #elif __cplusplus == 202002L
    BMC_PRINTLN("C++20");
  #elif __cplusplus > 202002L
    BMC_PRINTLN("C++23");
  #else
    BMC_PRINTLN("C++ version unknown");
  #endif

  
  BMC_PRINTLNNS(BMC_MCU_MODEL_STR," @ ",F_CPU/1000000.0,"MHz (",F_CPU,")");
  BMC_PRINTLN("RAM:", BMC_MCU_RAM_SIZE,"Bytes");
  BMC_PRINTLN("EEPROM:", BMC_MCU_EEPROM_SIZE,"Bytes");
  BMC_PRINTLN("Store:", sizeof(bmcStore),"Bytes");
  BMC_PRINTLN("USB Host:", BMC_MCU_HAS_USB_HOST?"Yes":"No");
  BMC_PRINTLN("SD Card:", BMC_MCU_HAS_SD_CARD?"Yes":"No");
  BMC_PRINTLN("FS Support:", BMC_MCU_HAS_FS?"Yes":"No");
  BMC_PRINTLN("Hardware Serial Ports:", BMC_MCU_TOTAL_SERIAL_PORTS);

  #if defined(BMC_SD_CARD_ENABLED)
    BMC_PRINTLN("* Using SD Card");
  #elif defined(BMC_FS_ENABLED)
    BMC_PRINTLN("* Using LittleFS");
  #elif defined(BMC_USE_24LC256)
    BMC_PRINTLN("* Using 24LC256 EEPROM");
  #else
    BMC_PRINTLN("* Using Built-in EEPROM");
  #endif


  #if BMC_MAX_ILI9341_BLOCKS > 0
    #if BMC_TFT_SIZE == 1
      BMC_PRINTLN("Using ILI9341 Driver");
    #else
      BMC_PRINTLN("Using ILI9844 Driver");
    #endif
    #if defined(BMC_USE_ON_BOARD_EDITOR)
      BMC_PRINTLN("On-Board Editor (OBE) Active");
    #endif
  #endif

  BMC_INFO_FOOT;
  
}
void BMC::midiInDebug(BMCMidiMessage message){
  if(!globals.getMidiInDebug() || message.getStatus()==BMC_NONE){
    return;
  }
  if(message.isClock()){
    if(globals.getMidiInClockDebug()){
      BMC_PRINTLN(
        millis(),
        BMCTools::getPortName(message.getSource()),
        "Incoming Clock"
      );
    }
  } else if(message.isStart()){
    BMC_PRINTLN(
      millis(),
      BMCTools::getPortName(message.getSource()),
      "*** Start ***"
    );
  } else if(message.isContinue()){
    BMC_PRINTLN(
      millis(),
      BMCTools::getPortName(message.getSource()),
      "*** Continue ***"
    );
  } else if(message.isStop()){
    BMC_PRINTLN(
      millis(),
      BMCTools::getPortName(message.getSource()),
      "*** Stop ***"
    );
  } else if(message.isActiveSense()){
    if(globals.getMidiInClockDebug()){
      BMC_PRINTLN(
        millis(),
        BMCTools::getPortName(message.getSource()),
        "Active Sense"
      );
    }
  } else if(message.isSystemExclusive()){
    BMC_PRINTLN(
      millis(),
      BMCTools::getPortName(message.getSource()),
      "Incoming",BMCTools::getMidiStatusName(message.getStatus())
    );
    BMC_PRINT_ARRAY(true,message.sysex,message.size());
  } else if(message.getStatus() > BMC_MIDI_SYSTEM_EXCLUSIVE){
    // no need to print the channel
    BMC_PRINTLN(
      millis(),
      BMCTools::getPortName(message.getSource()),
      "Incoming",BMCTools::getMidiStatusName(message.getStatus()),
      "data1:",message.getData1(),
      "data2:",message.getData2());
  } else if(message.getStatus()==BMC_MIDI_PITCH_BEND){
    uint8_t d1 = message.getData1();
    uint8_t d2 = message.getData2();
    int p = map(((d1 & 0x7F) | ((d2 & 0x7F) << 7)), 0, 16383, -8192, 8191);
    BMC_PRINTLN(
      millis(),
      BMCTools::getPortName(message.getSource()),
      "Incoming",BMCTools::getMidiStatusName(message.getStatus()),
      message.getChannel(),
      d1,
      d2,
      ">>>",p
    );
  } else {
    BMC_PRINTLN(
      millis(),
      BMCTools::getPortName(message.getSource()),
      "Incoming", BMCTools::getMidiStatusName(message.getStatus()),
      "channel:", message.getChannel(),
      "data1:", message.getData1(),
      "data2:", message.getData2()
    );
  }
}
void BMC::printButtonTrigger(uint8_t deviceId, uint8_t n, uint8_t t_trigger){
  if(!globals.getButtonsDebug()){
    return;
  }
  BMC_PRINT(millis() & 0xFFFF);
  BMC_PRINT((deviceId == BMC_DEVICE_ID_GLOBAL_BUTTON ? "Global Button" : "Button"), n + globals.offset);
  switch(t_trigger){
    case BMC_BUTTON_PRESS_TYPE_PRESS:
      BMC_PRINTLN("PRESS");break;
    case BMC_BUTTON_PRESS_TYPE_RELEASE:
      BMC_PRINTLN("RELEASE (Always)");break;
    case BMC_BUTTON_PRESS_TYPE_HOLD:
      BMC_PRINTLN("HOLD");break;
    case BMC_BUTTON_PRESS_TYPE_DOUBLE_PRESS:
      BMC_PRINTLN("DOUBLE PRESS");break;
    case BMC_BUTTON_PRESS_TYPE_CONTINUOUS:
      BMC_PRINTLN("CONTINUOUS");break;
    case BMC_BUTTON_PRESS_TYPE_ALT_PRESS:
      BMC_PRINTLN("2ND PRESS");break;
    case BMC_BUTTON_PRESS_TYPE_RELEASE_PRESS:
      BMC_PRINTLN("RELEASE (Press)");break;
    case BMC_BUTTON_PRESS_TYPE_RELEASE_HOLD:
      BMC_PRINTLN("RELEASE (Hold)");break;
    case BMC_BUTTON_PRESS_TYPE_RELEASE_DOUBLE_PRESS:
      BMC_PRINTLN("RELEASE (Double Press)");break;
    case BMC_BUTTON_PRESS_TYPE_RELEASE_CONTINUOUS:
      BMC_PRINTLN("RELEASE (Continuous)");break;
    case BMC_BUTTON_PRESS_TYPE_RELEASE_ALT:
      BMC_PRINTLN("RELEASE (2nd Press)");break;
    case BMC_BUTTON_PRESS_TYPE_STATE_CHANGE:
      BMC_PRINTLN("STATE CHANGE");break;
    default:
      BMC_PRINTLN(""); break;
  }
}
void BMC::printEncoderTrigger(uint8_t t_deviceId, uint8_t t_n, uint8_t t_direction, uint8_t t_ticks){
  if(!globals.getEncodersDebug()){
    return;
  }
  if(t_deviceId == BMC_DEVICE_ID_ENCODER){
    BMC_PRINT("Encoder");
  } else if(t_deviceId == BMC_DEVICE_ID_GLOBAL_ENCODER){
    BMC_PRINT("Global Encoder");
  }
  BMC_PRINTLN((t_n + globals.offset), (t_direction ? "INC" : "- DEC -"), "ticks:", t_ticks);
}
void BMC::debugStartTiming(uint8_t n, bool t_micros){
  if(n>=BMC_DEBUG_MAX_TIMING){
    return;
  }
  if(!t_micros){
    millisTiming[n] = millis();
  } else {
    microsTiming[n] = micros();
  }
}
unsigned long BMC::debugStopTiming(uint8_t n, bool t_micros){
  if(n>=BMC_DEBUG_MAX_TIMING){
    return 0;
  }
  if(!t_micros){
    millisTiming[n] = millis()-millisTiming[n];
    return millisTiming[n];
  } else {
    microsTiming[n] = micros()-microsTiming[n];
    return microsTiming[n];
  }
}
unsigned long BMC::getTiming(uint8_t n, bool t_micros){
  if(n>=BMC_DEBUG_MAX_TIMING){
    return 0;
  }
  if(!t_micros){
    return millisTiming[n];
  } else {
    return microsTiming[n];
  }
}
void BMC::printStorageInfo(){
  editor.printStorageInfo();

  BMC_INFO_HEAD;
  BMC_INFO_HEAD;
  BMC_PRINT(  "Version:  ", store.version); BMC_PRINTNS("0x"); BMC_PRINT_HEX(store.version); BMC_PRINTLN(" (2 bytes)");
  BMC_PRINT(  "CRC:      ", store.crc); BMC_PRINTNS("0x"); BMC_PRINT_HEX(store.crc); BMC_PRINTLN(" (2 bytes)");
  BMC_PRINTLN("Total:    ", sizeof(store), "bytes");
  BMC_PRINTLN("");

  BMC_PRINTLN("Global");
  BMC_PRINTLN(" - store.global");
  BMC_PRINTLN(" - Total :", sizeof(store.global), "bytes");
  BMC_INFO_HEAD;

  BMC_PRINTLN("Settings");
  BMC_PRINTLN(" - store.global.settings");
  BMC_PRINTLN(" - Total :", sizeof(store.global.settings), "bytes");
  BMC_INFO_HEAD;

  BMC_PRINTLN("Events",BMC_MAX_EVENTS_LIBRARY);
  BMC_PRINTLN(" - store.global.events");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.events[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.events), "bytes");
  BMC_INFO_HEAD;

  BMC_PRINTLN("Names",BMC_MAX_NAMES_LIBRARY);
  BMC_PRINTLN(" - store.global.names");
  BMC_PRINTLN(" - Each   :", sizeof(store.global.names[0]), "bytes");
  BMC_PRINTLN(" - Total  :", sizeof(store.global.names), "bytes");
  BMC_PRINTLN(" - Length :", BMC_MAX_NAMES_LENGTH, "bytes");
  BMC_INFO_HEAD;

  BMC_PRINTLN("Port Presets", 16);
  BMC_PRINTLN(" - store.global.portPresets");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.portPresets[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.portPresets), "bytes");
  BMC_INFO_HEAD;

  BMC_PRINTLN("Shortcuts", 6);
  BMC_PRINTLN(" - store.global.shortcuts");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.shortcuts[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.shortcuts), "bytes");
  BMC_INFO_HEAD;

#if BMC_MAX_LFO > 0
  BMC_PRINTLN("LFO", BMC_MAX_LFO);
  BMC_PRINTLN(" - store.global.lfo");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.lfo[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.lfo), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_SKETCH_BYTES > 0
  BMC_PRINTLN("Sketch Bytes", BMC_MAX_SKETCH_BYTES);
  BMC_PRINTLN(" - store.global.sketchBytes");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.sketchBytes[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.sketchBytes), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_PRESETS > 0
  BMC_PRINTLN("Presets",BMC_MAX_PRESETS);
  BMC_PRINTLN(" - store.global.presets");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.presets[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.presets), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_SETLISTS > 0
  BMC_PRINTLN("SetLists",BMC_MAX_SETLISTS);
  BMC_PRINTLN(" - store.global.setLists");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.setLists[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.setLists), "bytes");
  BMC_INFO_HEAD;

  BMC_PRINTLN("Song Library", BMC_MAX_SETLISTS_SONGS_LIBRARY);
  BMC_PRINTLN(" - store.global.songLibrary");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.songLibrary[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.songLibrary), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_BUTTONS > 0
  BMC_PRINTLN("Buttons", BMC_MAX_GLOBAL_BUTTONS);
  BMC_PRINTLN(" - store.global.buttons");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.buttons[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.buttons), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_LEDS > 0
  BMC_PRINTLN("LEDs",BMC_MAX_GLOBAL_LEDS);
  BMC_PRINTLN(" - store.global.leds");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.leds[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.leds), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_BI_LEDS > 0
  BMC_PRINTLN("Bi-LEDs",BMC_MAX_GLOBAL_BI_LEDS);
  BMC_PRINTLN(" - store.global.biLeds");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.biLeds[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.biLeds), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_TRI_LEDS > 0
  BMC_PRINTLN("Tri-LEDs",BMC_MAX_GLOBAL_TRI_LEDS);
  BMC_PRINTLN(" - store.global.triLeds");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.triLeds[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.triLeds), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_ENCODERS > 0
  BMC_PRINTLN("Encoders",BMC_MAX_GLOBAL_ENCODERS);
  BMC_PRINTLN(" - store.global.encoders");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.encoders[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.encoders), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_POTS > 0
  BMC_PRINTLN("Pots",BMC_MAX_GLOBAL_POTS);
  BMC_PRINTLN(" - store.global.pots");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.pots[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.pots), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_TOTAL_POTS_AUX_JACKS > 0
  BMC_PRINTLN("Pot Calibration",BMC_TOTAL_POTS_AUX_JACKS);
  BMC_PRINTLN(" - store.global.potCalibration");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.potCalibration[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.potCalibration), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_PIXELS > 0
  BMC_PRINTLN("Pixels",BMC_MAX_GLOBAL_PIXELS);
  BMC_PRINTLN(" - store.global.pixels");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.pixels[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.pixels), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
  BMC_PRINTLN("RGB Pixels",BMC_MAX_GLOBAL_RGB_PIXELS);
  BMC_PRINTLN(" - store.global.rgbPixels");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.rgbPixels[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.rgbPixels), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_GLOBAL_MAGIC_ENCODERS > 0
  BMC_PRINTLN("Magic Encoders",BMC_MAX_GLOBAL_MAGIC_ENCODERS);
  BMC_PRINTLN(" - store.global.magicEncoders");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.magicEncoders[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.magicEncoders), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_NL_RELAYS > 0
  BMC_PRINTLN("Relays NL",BMC_MAX_NL_RELAYS);
  BMC_PRINTLN(" - store.global.relaysNL");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.relaysNL[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.relaysNL), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_L_RELAYS > 0
  BMC_PRINTLN("Relays L",BMC_MAX_L_RELAYS);
  BMC_PRINTLN(" - store.global.relaysL");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.relaysL[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.relaysL), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_AUX_JACKS > 0
  BMC_PRINTLN("Aux Jacks",BMC_MAX_AUX_JACKS);
  BMC_PRINTLN(" - store.global.auxJacks");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.auxJacks[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.auxJacks), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_CUSTOM_SYSEX > 0
  BMC_PRINTLN("Custom SysEx",BMC_MAX_CUSTOM_SYSEX);
  BMC_PRINTLN(" - store.global.customSysEx");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.customSysEx[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.customSysEx), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_TRIGGERS > 0
  BMC_PRINTLN("Triggers",BMC_MAX_TRIGGERS);
  BMC_PRINTLN(" - store.global.triggers");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.triggers[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.triggers), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_TEMPO_TO_TAP > 0
  BMC_PRINTLN("Tempo to Tap",BMC_MAX_TEMPO_TO_TAP);
  BMC_PRINTLN(" - store.global.tempoToTap");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.tempoToTap[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.tempoToTap), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_PIXEL_PROGRAMS > 0
  BMC_PRINTLN("Pixel Programs",BMC_MAX_PIXEL_PROGRAMS);
  BMC_PRINTLN(" - store.global.pixelPrograms");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.pixelPrograms[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.pixelPrograms), "bytes");
  BMC_INFO_HEAD;
#endif
#if BMC_MAX_TIMED_EVENTS > 0
  BMC_PRINTLN("Timed Events",BMC_MAX_TIMED_EVENTS);
  BMC_PRINTLN(" - store.global.timedEvents");
  BMC_PRINTLN(" - Each  :", sizeof(store.global.timedEvents[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.global.timedEvents), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_LAYERS > 0
  BMC_PRINTLN("");
  BMC_PRINTLN("");

  BMC_PRINTLN("Layers",BMC_MAX_LAYERS);
  BMC_PRINTLN(" - store.layers");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers), "bytes");
  BMC_INFO_HEAD;

  BMC_PRINTLN("Layer Events",BMC_MAX_LAYER_EVENTS);
  BMC_PRINTLN(" - store.layers[n].events");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].events), "bytes");
  BMC_INFO_HEAD;

#if BMC_MAX_BUTTONS > 0
  BMC_PRINTLN("Buttons",BMC_MAX_BUTTONS);
  BMC_PRINTLN(" - store.layers[n].buttons[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].buttons[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].buttons), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_LEDS > 0
  BMC_PRINTLN("LEDs",BMC_MAX_LEDS);
  BMC_PRINTLN(" - store.layers[n].leds[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].leds[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].leds), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_BI_LEDS > 0
  BMC_PRINTLN("Bi-LEDs",BMC_MAX_BI_LEDS);
  BMC_PRINTLN(" - store.layers[n].biLeds[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].biLeds[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].biLeds), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_TRI_LEDS > 0
  BMC_PRINTLN("Tri-LEDs",BMC_MAX_TRI_LEDS);
  BMC_PRINTLN(" - store.layers[n].triLeds[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].triLeds[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].triLeds), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_PIXELS > 0
  BMC_PRINTLN("Pixels",BMC_MAX_PIXELS);
  BMC_PRINTLN(" - store.layers[n].pixels[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].pixels[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].pixels), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_RGB_PIXELS > 0
  BMC_PRINTLN("RGB Pixels",BMC_MAX_RGB_PIXELS);
  BMC_PRINTLN(" - store.layers[n].rgbPixels[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].rgbPixels[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].rgbPixels), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_MAGIC_ENCODERS > 0
  BMC_PRINTLN("Magic Encoders",BMC_MAX_MAGIC_ENCODERS);
  BMC_PRINTLN(" - store.layers[n].magicEncoders[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].magicEncoders[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].magicEncoders), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_PIXEL_STRIP > 0
  BMC_PRINTLN("Pixel Strip",BMC_MAX_PIXEL_STRIP);
  BMC_PRINTLN(" - store.layers[n].pixelStrip[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].pixelStrip[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].pixelStrip), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_ENCODERS > 0
  BMC_PRINTLN("Encoders",BMC_MAX_ENCODERS);
  BMC_PRINTLN(" - store.layers[n].encoders[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].encoders[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].encoders), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_POTS > 0
  BMC_PRINTLN("Pots",BMC_MAX_POTS);
  BMC_PRINTLN(" - store.layers[n].pots[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].pots[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].pots), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_OLED > 0
  BMC_PRINTLN("OLED",BMC_MAX_OLED);
  BMC_PRINTLN(" - store.layers[n].oled[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].oled[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].oled), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_ILI9341_BLOCKS > 0
  BMC_PRINTLN("ILI9341 Blocks",BMC_MAX_ILI9341_BLOCKS);
  BMC_PRINTLN(" - store.layers[n].ili[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].ili[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].ili), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_MINI_DISPLAY > 0
  BMC_PRINTLN("Mini Display",BMC_MAX_MINI_DISPLAY);
  BMC_PRINTLN(" - store.layers[n].miniDisplay[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].miniDisplay[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].miniDisplay), "bytes");
  BMC_INFO_HEAD;
#endif

#if BMC_MAX_LCD > 0
  BMC_PRINTLN("LCD",BMC_MAX_LCD);
  BMC_PRINTLN(" - store.layers[n].lcd[n]");
  BMC_PRINTLN(" - Each  :", sizeof(store.layers[0].lcd[0]), "bytes");
  BMC_PRINTLN(" - Total :", sizeof(store.layers[0].lcd), "bytes");
  BMC_INFO_HEAD;
#endif
#endif

  BMC_INFO_FOOT;
  BMC_INFO_FOOT;
  
}
#endif
