// See https://www.RoxXxtar.com/bmc for more details
// See LICENSE file in the project root for full license information.

// ************************************************************
// ************************************************************
// ************************************************************
// ************************************************************
// ************************************************************
// BMCApi is the object that holds all public Methods for BMC
// if you don't use BMC_DEFAULT() in your sketch you must use
// BMCApi for the bmc instance if you plan on using the public API
// however if your sketch will not use the API and you will
// only use the begin() and update() methods then you can
// create a BMC instance.
// This was done to keep the BMC class code easier to manage
// ************************************************************
// ************************************************************
// ************************************************************
// ************************************************************
// ************************************************************
// ************************************************************
#ifndef BMC_API_H
#define BMC_API_H

class BMC;

class BMCApi : public BMC {
public:
  BMCApi(){}
  // ******************************
  // *****  CALLBACKS  *****
  // ******************************
  // triggers every 1 second, additionally adds the stopwatch state as a parameter
  void onOneSecondPassed(void (*fptr)(uint8_t stopwatchState)){
    callback.oneSecondPassed = fptr;
  }
  // triggered when 2 buttons are pressed at the same time
  // see src/hardware/BMC-ButtonsDualHandler.h for info on how this works.
  void onButtonDualPress(void (*fptr)(uint16_t btn1, uint16_t btn2)){
    callback.buttonDualPress = fptr;
  }
  // triggered when a layer button is pressed, released, etc.
  void onButtonActivity(void (*fptr)(uint16_t n, uint8_t eventIndex, uint8_t pressType)){
    callback.buttonActivity = fptr;
  }


  // triggered when an encoder is rotated
  void onEncoderActivity(void (*fptr)(uint16_t index, bool increased, uint8_t ticks)){
    callback.encoderActivity = fptr;
  }
  // triggered when a pot is rotated
  void onPotActivity(void (*fptr)(uint16_t index, uint8_t value)){
    callback.potActivity = fptr;
  }
  // triggered when an led changes states, @states holds the state of each
  // led in bits, so bit 0 of states, is LED 0, if bit 0 is not set then led is off
  void onLedsActivity(void (*fptr)(uint32_t states)){
    callback.ledsActivity = fptr;
  }
  // triggered when a pixel changes states, @states holds the state of each
  // led in bits, so bit 0 of states, is LED 0, if bit 0 is not set then led is off
  void onPixelsActivity(void (*fptr)(uint32_t states)){
    callback.pixelsActivity = fptr;
  }
  // triggered when an RGB pixel changes states, @states holds the state of each
  // led in bits, so bit 0 of states, is LED 0, if bit 0 is not set then led is off
  void onRgbPixelsActivity(void (*fptr)(uint32_t states)){
    callback.rgbPixelsActivity = fptr;
  }

  // triggered when an global button is pressed, released, etc.
  // see src/hardware/BMC-ButtonsDualHandler.h for info on how this works.
  void onGlobalButtonDualPress(void (*fptr)(uint16_t btn1, uint16_t btn2)){
    callback.globalButtonDualPress = fptr;
  }
  void onGlobalButtonActivity(void (*fptr)(uint16_t n, uint8_t eventIndex, uint8_t pressType)){
    callback.globalButtonActivity = fptr;
  }
  // triggered when a global encoder is rotated
  void onGlobalEncoderActivity(void (*fptr)(uint16_t index, bool increased, uint8_t ticks)){
    callback.globalEncoderActivity = fptr;
  }
  // triggered when a global pot is rotated
  void onGlobalPotActivity(void (*fptr)(uint16_t index, uint8_t value)){
    callback.globalPotActivity = fptr;
  }

  // triggered when a global led changes states
  void onGlobalLedsActivity(void (*fptr)(uint32_t states)){
    callback.globalLedsActivity = fptr;
  }
  // triggered when a custom button event is handled
  void onButtonCustomActivity(void (*fptr)(uint16_t n, uint8_t eventIndex, uint8_t ports)){
    callback.buttonsCustomActivity = fptr;
  }
  // triggered when a custom encoder event is handled
  void onEncoderCustomActivity(void (*fptr)(uint16_t index, bool direction, uint8_t ticks)){
    callback.encoderCustomActivity = fptr;
  }
  // triggered when a custom pot event is handled
  void onPotCustomActivity(void (*fptr)(uint16_t index, uint8_t t_value)){
    callback.potCustomActivity = fptr;
  }
  // triggered when a custom global button event is handled
  void onGlobalButtonCustomActivity(void (*fptr)(uint16_t n, uint8_t eventIndex, uint8_t ports)){
    callback.globalButtonsCustomActivity = fptr;
  }
  // triggered when a custom global encoder event is handled
  void onGlobalEncoderCustomActivity(void (*fptr)(uint16_t index, bool direction, uint8_t ticks)){
    callback.globalEncoderCustomActivity = fptr;
  }
  // triggered when a custom global pot event is handled
  void onGlobalPotCustomActivity(void (*fptr)(uint16_t index, uint8_t t_value)){
    callback.globalPotCustomActivity = fptr;
  }
  // for user defined events, includes layer and global
  void onButtonsUserEvent(void (*fptr)(uint8_t n, uint32_t event, uint8_t ports, uint8_t mode)){
    callback.userEventButtons = fptr;
  }
  // for user defined events, includes layer and global encoders
  void onEncodersUserEvent(void (*fptr)(uint8_t n, uint32_t event, uint8_t ports, uint8_t mode)){
    callback.userEventEncoders = fptr;
  }
  // for user defined events, includes layer and global led, pwm leds, pixels and rgb pixels
  void onPotsUserEvent(void (*fptr)(uint8_t n, uint32_t event, uint8_t ports, uint8_t value)){
    callback.userEventPots = fptr;
  }
  // for user defined events, includes layer and global
  // this callback must return a byte
  // 0 will turn led off
  // 1 will turn led on, for PWM Leds the brightness will be use, Pixels the color.
  // 2 will "pulse" the led
  // 3 will blink layer and global leds, for pixels it will turn on RAINBOW and turns PWM leds to their set brightness
  // a value between 4 and 131 will apply only to PWM Leds, this value will have 4 substracted
  // then the remainder will be used as the Brightness of the Led, you could use this to fade a PWM led!
  // a value of 255 will be ignored, this is to avoid changing the state of the led,
  // for example if going to be pulsed then you want to return 255 if the conditions
  // that are supposed to pulse the led are not met, otherwise the led will remain on.
  // true turns Led on, false turnes it off
  void onLedsUserEvent(uint8_t (*fptr)(uint8_t n, uint32_t event, uint8_t type)){
    callback.userEventLeds = fptr;
  }
  // for user defined events
  // this callback must return valid relay command, these are
  // BMC_RELAY_RESET (put relay in reset or Normally Open position)
  // BMC_RELAY_SET (put relay in set or Normally Closed position)
  // BMC_RELAY_TOGGLE (toggle the current state of the relay)
  void onRelaysUserEvent(uint8_t (*fptr)(uint8_t n, uint32_t event)){
    callback.userEventRelays = fptr;
  }
  // triggered when an aux jack detects a plug connected or disconnected
  // @n the Aux Jack Index that had a state change.
  // @state true if a connection has been made, false if disconnected.
  void onAuxJackConnection(void (*fptr)(uint8_t n, bool state)){
    callback.auxJackConnection = fptr;
  }
  // triggered when you change layers, also triggered when BMC runs it's first loop
  void onLayerChange(void (*fptr)(uint8_t layer)){
    callback.pageChanged = fptr;
  }
  /*
  void onTriggerCustom(void (*fptr)(uint8_t id)){
#if BMC_MAX_TRIGGERS > 0
    callback.triggerCustom = fptr;
#endif
  }
  
  void onTimedEventCustom(void (*fptr)(uint8_t id, uint8_t a, uint8_t b, uint8_t c)){
#if BMC_MAX_TIMED_EVENTS > 0
    callback.timedEventCustom = fptr;
#endif
  }
  */
  //DEPRECATED, USE onStoreUpdate INSTEAD
  void onEditorUpdate(void (*fptr)()){
    onStoreUpdate(fptr);
  }
  // triggered when EEPROM has been updated either by the editor or the API
  void onStoreUpdate(void (*fptr)()){
    callback.storeUpdated = fptr;
  }
  // triggered when the editor connects/disconnects
  // @state true if editor is connected
  void onEditorConnection(void (*fptr)(bool state)){
    callback.editorConnection = fptr;
  }
  // triggered when a value stream is handled
  void onValueStream(void (*fptr)(BMCValueStream item)){
    callback.valueStream = fptr;
  }
  // triggered when a BMC Trigger has been handled
  void onTrigger(void (*fptr)(uint32_t source, uint32_t event)){
    callback.midiTriggerReceived = fptr;
  }
  // triggered when a MIDI message is received
  void onMidiRx(void (*fptr)(BMCMidiMessage data)){
    callback.midiReceived = fptr;
  }
  // triggered when a MIDI Clock message is received
  void onMidiClockTick(void (*fptr)()){
    callback.midiClockTickReceived = fptr;
  }
  // triggered every 24 times a MIDI Clock message is received
  void onMidiClockBeat(void (*fptr)()){
    callback.midiClockBeat = fptr;
  }
  // triggered when the Master/Slave Clock has changed it's tempo
  void onMidiClockBpmChange(void (*fptr)(uint16_t tempo)){
    callback.midiClockBpmChange = fptr;
  }
  // triggered when a midi message was sent or received
  void onMidiActivity(void (*fptr)(bool in, bool out)){
    callback.midiActivity = fptr;
  }
  // triggered when MIDI data is updated within the Local MIDI Data Object
  // BMC holds 129 bytes for each of the 16 MIDI Channels,
  // 1 for Program and 128 for Control Change, when you send or receive
  // a Program Change this value is updated for that channel, the same goes for
  // Control Changes. This data is also updated if the message isn't actually sent
  // to a port, so if a button has a Program Change event but no Ports BMC will
  // still update this value.
  void onMidiLocalUpdate(void (*fptr)()){
    callback.midiLocalUpdate = fptr;
  }
  // triggered when a message is about to be sent to a port via Routing.
  // this callback takes in a MIDI message that is about to be routed (soft-thru)
  // the callback must return a bool, if the callback returns false the message
  // will not be routed.
  // The "data" parameter is a reference so you can manipulate the message before
  // it reaches it's intended ports, however once the data is changed, any other
  // BMC functions will see this new data.
  void onMidiPreRouting(bool (*fptr)(BMCMidiMessage& data, uint8_t destinations)){
    callback.midiPreRoute = fptr;
  }
  // triggered when a USB MIDI Device is connected to the Teensy's USB Host
  void onHostConnectionChange(void (*fptr)(bool t_connected)){
#ifdef BMC_USB_HOST_ENABLED
    callback.hostConnection = fptr;
#endif
  }
  // triggered when BMC connects to a BLE Master Device
  void onBleConnectionChange(void (*fptr)(bool t_connected)){
#ifdef BMC_MIDI_BLE_ENABLED
    callback.bleConnection = fptr;
#endif
  }
  // triggered when a Menu Command is handled by a button, encoder, API, etc.
  void onMenu(void (*fptr)(uint8_t t_command)){
    callback.menuCommand = fptr;
  }
  // triggered when the Typer value has been Updated
  void onTyperUpdate(void (*fptr)(uint16_t t_value, uint16_t t_rawValue)){
    callback.typerCommand = fptr;
  }
  // triggered when the Typer value has been Updated and you set it to custom calback
  void onTyperCustomUpdate(void (*fptr)(uint16_t t_value, uint16_t t_rawValue)){
    callback.typerCustomCommand = fptr;
  }


  // triggered when BMC runs it's update() method the first time.
  void onFirstLoop(void (*fptr)()){
    callback.firstLoop = fptr;
  }
  // triggered half way thru the BMC update() method, this is in case you need
  // to do other tasks like update a display without waiting for the BMC update()
  // method to complete
  void onMidUpdate(void (*fptr)()){
    callback.midUpdate = fptr;
  }
  // triggered when Messenger message is received from the Editor App.
  void onMessenger(void (*fptr)(BMCMessenger t_messenger)){
    callback.messengerReceived = fptr;
  }

// only available if BMC has FAS compiler for Fractal Axe FX II and AX8
#ifdef BMC_USE_FAS
  // triggered when BMC Detects a FAS device has been connected/disconnected
  void onFasConnectionChange(void (*fptr)(bool state)){
    callback.fasConnection = fptr;
  }
  // triggered when the FAS preset has changed
  void onFasPresetChange(void (*fptr)(uint16_t n)){
    callback.fasPresetChange = fptr;
  }
  // triggered when the FAS preset name has been received
  void onFasPresetName(void (*fptr)(char* str)){
    callback.fasPresetName = fptr;
  }
  // triggered when the FAS scene has changed
  void onFasSceneChange(void (*fptr)(uint8_t n)){
    callback.fasSceneChange = fptr;
  }
  // triggered when any FAS Effect Block has changed it's states
  void onFasBlocksChange(void (*fptr)()){
    callback.fasBlocksChange = fptr;
  }
  // triggered when the FAS Tuner has been turned on/off
  void onFasTunerStateChange(void (*fptr)(bool state)){
    callback.fasTunerStateChange = fptr;
  }
  // triggered when the FAS tuner data has been received
  void onFasTunerReceived(void (*fptr)(BMCTunerData& data)){
    callback.fasTunerReceived = fptr;
  }
  // triggered when the FAS Looper has been activated or stopped
  void onFasLooperStateChange(void (*fptr)(bool state)){
    callback.fasLooperStateChange = fptr;
  }
  // triggered when the FAS Looper data has been received
  void onFasLooperReceived(void (*fptr)(uint8_t data, uint8_t position)){
    callback.fasLooperReceived = fptr;
  }
  // triggered when FAS CPU usage has been received
  void onFasCpuReceived(void (*fptr)(uint8_t n)){
    callback.fasCpuReceived = fptr;
  }
  // triggered when a FAS Effect Block Parameter has been received
  void onFasBlockParameterReceived(void (*fptr)(uint8_t block, uint8_t param, uint16_t value, char* str, uint8_t strLen)){
    callback.fasBlockParameterReceived = fptr;
  }
#endif

// only available when BEATBUDDY is compiled
#ifdef BMC_USE_BEATBUDDY
  void onBeatBuddyBeatLocationChange(void (*fptr)(uint8_t t_location, uint8_t numerator)){
    callback.beatBuddyBeatLocation = fptr;
  }
#endif
  // triggered when a BMC Preset has changed
  void onPresetChange(void (*fptr)(uint8_t t_bank, uint8_t t_preset)){
    callback.presetChanged = fptr;
  }
  // triggered when a BMC Preset Bank has changed
  void onPresetsBankChange(void (*fptr)(uint8_t n)){
    callback.presetBankChanged = fptr;
  }
  // triggered when the current BMC SetList has changed
  void onSetListChange(void (*fptr)(uint8_t n)){
    callback.setListChanged = fptr;
  }
  // triggered when the current BMC SetList Song has changed
  void onSetListSongChange(void (*fptr)(uint8_t n)){
    callback.setListSongChanged = fptr;
  }
  // triggered when BMC erases the active EEPROM, this usually only happens when
  // you have multiple stores available and BMC changes the store to one that doesn't
  // match the current CRC
  void onEepromErased(void (*fptr)()){
    callback.eepromErased = fptr;
  }
  // ******************************
  // *****  DAW  *****
  // ******************************
#ifdef BMC_USE_DAW_LC
  // passes the state of the connect, true if a project is loaded
  void onDawOnline(void (*fptr)(bool state)){
    callback.dawOnline = fptr;
  }
  // passes the sysex message containing the updated LCD string
  void onDawRecievedLCD(void (*fptr)(BMCMidiMessage data)){
    callback.dawRecievedLCD = fptr;
  }
  // more info to come
  void onDawRecievedTimeDisplay(void (*fptr)(uint8_t digit, char character)){
    callback.dawRecievedTimeDisplay = fptr;
  }
  // more info to come
  void onDawRecievedAssignmentDisplay(void (*fptr)(uint8_t digit, char character)){
    callback.dawRecievedAssignmentDisplay = fptr;
  }
  // passes the meter value for a channel
  void onDawRecievedChannelMeter(void (*fptr)(uint8_t channel, uint8_t value)){
    callback.dawRecievedChannelMeter = fptr;
  }
  // passes the meter value for a channel, includes the overload led status
  void onDawChannelMeterUpdate(void (*fptr)(uint8_t channel, uint8_t value, uint8_t overload)){
    callback.dawChannelMeterUpdate = fptr;
  }
  // more info to come
  void onDawReceivedTimeCodeDigit(void (*fptr)(uint8_t digit, uint8_t value)){
    callback.dawReceivedTimeCodeDigit = fptr;
  }
  // passes the value of the VPOT ring for the specified channel
  void onDawChannelVPotUpdate(void (*fptr)(uint8_t channel, uint8_t value, uint8_t centered, uint8_t mode)){
    callback.dawChannelVPotUpdate = fptr;
  }
  // passes the specified channel's fader position
  void onDawRecievedChannelFaderPosition(void (*fptr)(uint8_t channel, int value)){
    callback.dawRecievedChannelFaderPosition = fptr;
  }
  // passes the master channel's fader position
  void onDawRecievedMasterFaderPosition(void (*fptr)(int value)){
    callback.dawRecievedMasterFaderPosition = fptr;
  }
  // receive the state of a channel, true if the channel is currently selected
  void onDawRecievedChannelSelect(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelSelect = fptr;
  }
  // receive the solo state of a channel, true if the channel is currently in solo
  void onDawRecievedChannelSolo(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelSolo = fptr;
  }
  // receive the mute state of a channel, true if the channel is currently in mute
  void onDawRecievedChannelMute(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelMute = fptr;
  }
  // receive the rec/ready state of a channel, true if the channel is currently in rec/ready
  void onDawRecievedChannelRecReady(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelRecReady = fptr;
  }
  // receive the state leds, @cmd will carry the function of the LED, see documentation
  void onDawRecievedLedState(void (*fptr)(uint8_t cmd, bool state)){
    callback.dawRecievedLedState = fptr;
  }
  //returns the selected channel number
  uint8_t getDawSelectedTrack(){
    return sync.daw.getSelectedChannel();
  }
  //returns state of a specified LED in the led ring of a VPOT.
  // you can use this for a custom led ring to update weather that led should
  // be on or off
  uint8_t getDawVPotLedState(uint8_t channel, uint8_t ledN){
    return sync.daw.getVPotLedState(channel, ledN);
  }
  void sendDawVPot(uint8_t ch, bool clockwise, uint8_t ticks){
    sync.daw.sendVPot(ch, clockwise, ticks);
  }
  void sendDawButton(uint8_t cmd, uint8_t ch, bool release){
    sync.daw.sendButtonCommand(cmd, ch, release);
  }
#endif
  // ******************************
  // *****  STOPWATCH  *****
  // ******************************

  void stopwatchControl(uint8_t cmd, uint8_t h=0, uint8_t m=0, uint8_t s=0){
    stopwatchCmd(cmd, h, m, s);
  }
#if defined(BMC_HAS_DISPLAY)
  void displayHorizontalMeter(uint8_t n, uint8_t value){
    display.printHorizontalMeter(n, value);
  }
#if BMC_MAX_OLED > 0
  BMC_SSD1306 & displayGetOled(uint8_t n){
    return display.get(n);
  }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
  
#endif
#endif

  // ******************************
  // ***** LOCAL MIDI CONTROL *****
  // ******************************
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  void setLocalProgram(uint8_t t_channel, uint8_t t_program){
    midi.setLocalProgram(t_channel, t_program);
  }
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  void setLocalControl(uint8_t t_channel, uint8_t t_control, uint8_t t_value){
    midi.setLocalControl(t_channel, t_control, t_value);
  }
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  uint8_t getLocalProgram(uint8_t t_channel){
    return midi.getLocalProgram(t_channel);
  }
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  uint8_t getLocalControl(uint8_t t_channel, uint8_t t_control){
    return midi.getLocalControl(t_channel, t_control);
  }

  // ******************************
  // *****        STORE       *****
  // ******************************
  bool changeStore(uint8_t t_address){
    if(editor.changeStore(t_address)){
      // since this changed was triggered by your sketch we'll delay
      // it in case it wasn't programmed properly and you are changing
      // the address way too many times.
      BMC_PRINTLN("Store Address has been changed to", getStoreAddress());
      delay(250);
      // reassign all objects to new data
      assignStoreData();
      if(callback.valueStream){
        uint8_t nStoreAddress = getStoreAddress();
        char buff[30] = "";
        sprintf(buff, "Store Address Changed to %02u", (uint8_t)(nStoreAddress+1));
        streamToSketch(0, nStoreAddress, buff);
      }
      return true;
    }
    return false;
  }
  uint8_t getStoreAddress(){
    return editor.getStoreAddress();
  }

  // ******************************
  // *****        LAYERS       *****
  // ******************************
  // change to a new layer.
  // if n is not a valid layer number, nothing happens
  // if n is the same as the current layer, nothing happens
  void changeLayer(uint8_t n){
    setLayer(n);
  }
  // get the current layer
  uint8_t getCurrentLayer(){
    return getLayer();
  }
  // retrieve the name of the current layer
  bmcStoreName getLayerName(){
    return getLayerName(layer);
  }
  // retrieve the name of the a layer specified by n
  bmcStoreName getLayerName(uint16_t n){
    bmcStoreName e;
    if(n<BMC_MAX_LAYERS){
      //strcpy(t_string, store.layers[n].name);
      return globals.getDeviceName(store.layers[n].events[0].name);
    }
    return e;
  }
#if BMC_MAX_LAYERS > 1
  // move to the next layer
  // if endless is true and you are already on the last layer, you will go to the first layer
  void pageUp(bool endless=true){
    scrollLayer(true, endless, 0, BMC_MAX_LAYERS-1, 1);
  }
  // move to the previous layer
  // if endless is true and you are already on the first layer, you will go to the last layer
  void pageDown(bool endless=true){
    scrollLayer(false, endless, 0, BMC_MAX_LAYERS-1, 1);
  }
#endif

// ******************************
// *****      PRESETS       *****
// ******************************
#if BMC_MAX_PRESETS > 0
  #if BMC_NAME_LEN_PRESETS > 1
    // retrieve the current preset name
    /*
    void getPresetName(char* t_string){
      getPresetName(presets.get(), t_string);
    }
    // retrieve a preset name
    void getPresetName(uint16_t n, char* t_string){
      if(n<BMC_MAX_PRESETS){
        presets.getName(n, t_string);
      }
    }
    */
  #endif
  // get how many library messages this preset has
  /*
  uint8_t getPresetLength(uint16_t n){
    return presets.getLength(n);
  }

  // get the current preset number
  uint16_t getPreset(){
    return presets.get();
  }
  // get the current preset bank
  uint8_t getPresetBank(){
    return presets.getBank();
  }
  // get the index of the current preset on the current bank
  uint8_t getPresetInBank(){
    return presets.getPresetInBank();
  }
  // change to a preset
  void setPreset(uint16_t n){
    presets.set(n);
  }
  // go to the next preset
  void presetUp(bool endless){
    presets.scroll(1, true, endless);
  }
  // go to the previous preset
  void presetDown(bool endless){
    presets.scroll(1, false, endless);
  }
  // preset in bank
  void setPresetBank(uint8_t n){
    presets.setBank(n);
  }
  // switch to a specific preset in a specific bank
  void setPresetInBank(uint8_t n, uint8_t b=255){
    if(n >= BMC_MAX_PRESETS_PER_BANK){
      return;
    }
    if(b < presets.getTotalBanks()){
      presets.setBank(b);
    }
    presets.setInBank(n);
  }
  // go to next bank
  void presetBankUp(bool endless){
    presets.bankScroll(1, true, endless);
  }
  // go to previous bank
  void presetBankDown(bool endless){
    presets.bankScroll(1, false, endless);
  }
  // go to next preset in current bank
  void presetInBankUp(bool endless){
    presets.scrollInBank(1, true, endless);
  }
  // go to previous preset in current bank
  void presetInBankDown(bool endless){
    presets.scrollInBank(1, false, endless);
  }
  */
#endif

#if BMC_MAX_SETLISTS > 0
/*
  #if BMC_NAME_LEN_SETLISTS > 1
    // get the name of the current setlist
    void getSetListName(char* t_string){
      getSetListName(setLists.get(), t_string);
    }
    // get the name of a specific setlist
    void getSetListName(uint8_t n, char* t_string){
      if(n<BMC_MAX_SETLISTS){
        setLists.getName(n, t_string);
      }
    }
  #endif
*/
  #if BMC_NAME_LEN_PRESETS > 1
  /*
    // get the name of the current song in the current setlist
    void getSetListSongName(char* t_string){
      getSetListSongName(setLists.getSong(), t_string);
    }
    // get the name of  a specific song in the current setlist
    void getSetListSongName(uint8_t n, char* t_string){
      if(n<BMC_MAX_PRESETS){
        presets.getName(setLists.getSongPreset(n), t_string);
      }
    }
    */
  #endif
  // get the current SetList number
/*
  uint8_t getSetList(){
    return setLists.get();
  }
  // get the number of songs in the current setlist
  uint8_t getSetListLength(){
    return setLists.getSetListLength();
  }
  // get the number of songs in the specified setlist
  uint8_t getSetListLength(uint8_t n){
    return setLists.getSetListLength(n);
  }
  // go to a specific SetList
  void setSetList(uint8_t n){
    setLists.set(n);
  }
  // go to next song in the list
  // @endless if true, after reaching the last setlist
  // the next setlist will be the first setlist
  // otherwise once the last setlist is reached BMC will
  // ignore this function
  void setListUp(bool endless){
    setLists.scroll(1, true, endless);
  }
  // go to the previous setlist
  // @endless if true, after reaching the first setlist
  // the previous setlist will be the last setlist
  // otherwise once the first setlist is reached BMC will
  // ignore this function
  void setListDown(bool endless){
    setLists.scroll(1, false, endless);
  }
  // get the current song number in the setlist
  uint8_t getSetListSong(){
    return setLists.getSong();
  }
  // go to a specific song number in the setlist
  void setSetListSong(uint8_t n){
    setLists.setSong(n);
  }
  // go to next song in the list
  // @endless if true, after reaching the last song
  // the next song will be the first song
  // otherwise once the last song is reached BMC will
  // ignore this function
  void setListSongUp(bool endless){
    setLists.scrollSong(1, true, endless);
  }
  // go to previous song in the list
  // @endless if true, after reaching the first song
  // the previous song will be the last song
  // otherwise once the first song is reached BMC will
  // ignore this function
  void setListSongDown(bool endless){
    setLists.scrollSong(1, false, endless);
  }
  // swap songs inside setlists, returns true if successful, automatically saves
  // to EEPROM
  // @s = setlist index
  // @a = song to swap
  // @b = song to swap
  bool setListSwapSong(uint8_t s, uint8_t a, uint8_t b){
    if(globals.editorConnected()){
      return false;
    }
    if(s>=BMC_MAX_SETLISTS || a>=BMC_MAX_SETLISTS_SONGS || b>=BMC_MAX_SETLISTS_SONGS){
      return false;
    }
    // @sl = setlist length, how many songs it has assigned
    uint8_t sl = setLists.getSetListLength(s);
    if(sl==0 || a>=sl || b>=sl){
      return false;
    }
    uint8_t x = store.global.setLists[s].songs[a];
    uint8_t y = store.global.setLists[s].songs[b];
    store.global.setLists[s].songs[a] = y;
    store.global.setLists[s].songs[b] = x;
    editor.saveSetList(s);
    return true;
  }
  // move a song to new position and shift all songs after the new position
  // to the next position, useful to rearrange songs in setlists. returns true
  // if successful, automatically saves to EEPROM
  // @s = setlist index
  // @n = song index
  // @newPost = new song position
  bool setListShiftSong(uint8_t s, uint8_t n, uint8_t newPos){
    if(globals.editorConnected()){
      return false;
    }
    if(s>=BMC_MAX_SETLISTS || n>=BMC_MAX_SETLISTS_SONGS || newPos>=BMC_MAX_SETLISTS_SONGS){
      return false;
    }
    if(n == newPos){
      return false;
    }
    // @sl = setlist length, how many songs it has assigned
    uint8_t sl = setLists.getSetListLength(s);
    if(sl==0 || n>=sl || newPos>=sl){
      return false;
    }
    uint8_t len = store.global.setLists[s].length;
    uint8_t tmp[len];
    memset(tmp, 0, len);
    if(newPos > n){
      for(uint8_t i=0;i<len;i++){
        if(i==newPos){
          tmp[newPos] = store.global.setLists[s].songs[n];
        } else if(i>=n && (i+1)<len){
          tmp[i] = store.global.setLists[s].songs[i+1];
        } else {
          tmp[i] = store.global.setLists[s].songs[i];
        }
      }
    } else {
      tmp[newPos] = store.global.setLists[s].songs[n];
      for(uint8_t i=0;i<len;i++){
        if((i<newPos && i<n) || (i>newPos && i>n)){
          tmp[i] = store.global.setLists[s].songs[i];
        } else if(i>newPos && (i-1)>0){
          tmp[i] = store.global.setLists[s].songs[i-1];
        }
      }
    }
    memcpy(store.global.setLists[s].songs, tmp, len);
    editor.saveSetList(s);
    return true;
  }
*/
#endif

#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
  // for those using a custom Digital In Multiplexer you would handle reading
  // it's pins then you pass the value of each of those Pins to BMC with this
  // API call, digital inputs must be Active LOW, that is if a button was pressed
  // the value should be LOW if it's not being pressed it's value should be HIGH
  // BMC will debounce these values so don't bother debouncing them on your own.
  void setMuxDigitalValue(uint8_t pin, bool value){
    mux.setDigitalValue(pin, value);
  }
#endif

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
  // for those using a custom Digital Out Multiplexer BMC will hold the state
  // that that pin should be at, for example if the pins is being used to turn
  // leds on/off then BMC will tell you weather that pin should be on or off
  // you would then handle turning those LEDS on/off with your Mux.
  void getMuxDigitalOutValue(uint8_t pin){
    mux.getDigitalValue(pin);
  }
#endif

#if BMC_MAX_MUX_IN_ANALOG > 0
  // same setMuxDigitalValue as but you must pass it a value from 0 to 1024.
  void setMuxAnalogValue(uint8_t n, uint16_t value){
    mux.setAnalogValue(n, value);
  }
#endif

#if BMC_MAX_BUTTONS > 0
  // Get BUTTON Data
  /*
  void getButton(uint8_t t_index, bmcStoreButton& t_item){
    getButton(layer, t_index, t_item);
  }
  void getButton(uint8_t t_page, uint8_t t_index, bmcStoreButton& t_item){
    if(t_page<BMC_MAX_LAYERS && t_index<BMC_MAX_BUTTONS){
      t_item = store.layers[t_page].buttons[t_index];
    }
  }
  #if BMC_NAME_LEN_BUTTONS > 1
    void getButtonName(uint8_t n, char* t_string){
      getButtonName(layer, n, t_string);
    }
    void getButtonName(uint8_t t_page, uint8_t n, char* t_string){
      if(t_page<BMC_MAX_LAYERS && n<BMC_MAX_BUTTONS){
        strcpy(t_string, store.layers[t_page].buttons[n].name);
      }
    }
  #endif
  */
  void triggerButtonPress(uint8_t n){
    if(n<BMC_MAX_BUTTONS){
      buttons[n].triggerPress();
    }
  }
  void triggerButtonRelease(uint8_t n){
    if(n<BMC_MAX_BUTTONS){
      buttons[n].triggerRelease();
    }
  }
  // returns the raw state of a button, this is a pre-debounce value
  bool getButtonRawValue(uint8_t n){
    if(n<BMC_MAX_BUTTONS){
      return buttons[n].readState();
    }
  }
#endif

#if BMC_MAX_GLOBAL_BUTTONS > 0
/*
  void getGlobalButton(uint8_t t_index, bmcStoreButton& t_item){
    if(t_index<BMC_MAX_GLOBAL_BUTTONS){
      t_item = store.global.buttons[t_index];
    }
  }
  #if BMC_NAME_LEN_BUTTONS > 1
    void getGlobalButtonName(uint8_t n, char* t_string){
      if(n<BMC_MAX_GLOBAL_BUTTONS){
        strcpy(t_string, store.global.buttons[n].name);
      }
    }
  #endif
*/
  void triggerGlobalButtonPress(uint8_t n){
    if(n<BMC_MAX_GLOBAL_BUTTONS){
      globalButtons[n].triggerPress();
    }
  }
  void triggerGlobalButtonRelease(uint8_t n){
    if(n<BMC_MAX_GLOBAL_BUTTONS){
      globalButtons[n].triggerRelease();
    }
  }
  // returns the raw state of a button, this is a pre-debounce value
  bool getGlobalButtonRawValue(uint8_t n){
    if(n<BMC_MAX_GLOBAL_BUTTONS){
      return globalButtons[n].readState();
    }
  }
#endif

#if BMC_MAX_LEDS > 0
  // Get LED Data
  /*
  void getLed(uint8_t t_index, bmcStoreLed& t_item){
    getLed(layer, t_index, t_item);
  }
  void getLed(uint8_t t_page, uint8_t t_index, bmcStoreLed& t_item){
    if(t_page<BMC_MAX_LAYERS && t_index<BMC_MAX_LEDS){
      t_item = store.layers[t_page].leds[t_index];
    }
  }
  */

#if BMC_NAME_LEN_LEDS > 1
  void getLedName(uint8_t t_index, char* t_string){
    getLedName(layer, t_index, t_string);
  }
  void getLedName(uint8_t t_page, uint8_t t_index, char* t_string){
    if(t_page<BMC_MAX_LAYERS && t_index<BMC_MAX_LEDS){
      strcpy(t_string, store.layers[t_page].leds[t_index].name);
    }
  }
#endif
  // used to control leds only by the sketch, no matter what layer
  void setLedCustomState(uint16_t n, bool t_value){
    if(n < BMC_MAX_LEDS){
      globals.ledCustomState.setBit(n, t_value);
    }
  }
  bool getLedCustomState(uint16_t n){
    return (n < BMC_MAX_LEDS) ? globals.ledCustomState.getBit(n) : 0;
  }
  bool getLedState(uint16_t n){
    return (n < BMC_MAX_LEDS) ? globals.ledStates.getBit(n) : 0;
  }
#endif

#if BMC_MAX_GLOBAL_LEDS > 0
  // get GLOBAL_LED Data
  /*
  void getGlobalLed(uint8_t n, bmcStoreLed& t_item){
    if(n < BMC_MAX_GLOBAL_LEDS){
      t_item = store.global.leds[n];
    }
  }
  #if BMC_NAME_LEN_LEDS > 1
    void getGlobalLedName(uint8_t n, char* t_string){
      if(n < BMC_MAX_GLOBAL_LEDS){
        strcpy(t_string, store.global.leds[n].name);
      }
    }
  #endif
  */
  // used to control leds only by the sketch, no matter what layer
  void setGlobalLedCustomState(uint16_t n, bool t_value){
    if(n < BMC_MAX_GLOBAL_LEDS){
      globals.globalLedCustomState.setBit(n, t_value);
    }
  }
  bool getGlobalLedCustomState(uint16_t n){
    return (n < BMC_MAX_GLOBAL_LEDS) ? globals.globalLedCustomState.getBit(n) : 0;
  }
  /*
  uint32_t getGlobalLedStates(){
    return globalLedStates;
  }
  */
#endif

#if BMC_MAX_PIXELS > 0
  // get Pixel Data
  /*
  void getPixel(uint8_t n, bmcStoreLed& t_item){
    getPixel(layer, n, t_item);
  }
  void getPixel(uint8_t t_page, uint8_t n, bmcStoreLed& t_item){
    if(t_page<BMC_MAX_LAYERS && n<BMC_MAX_PIXELS){
      t_item = store.layers[t_page].pixels[n];
    }
  }
  */
  /*
#if BMC_NAME_LEN_LEDS > 1
  void getPixelName(uint8_t n, char* t_string){
    getPixelName(layer, n, t_string);
  }
  void getPixelName(uint8_t t_page, uint8_t n, char* t_string){
    if(t_page<BMC_MAX_LAYERS && n<BMC_MAX_PIXELS){
      strcpy(t_string, store.layers[t_page].pixels[n].name);
    }
  }
#endif
*/
  // used to control pixels only by the sketch, no matter what layer
  void setPixelCustomState(uint8_t n, uint8_t t_color, uint8_t t_brightness){
    if(n < BMC_MAX_PIXELS && t_brightness <= 15){
      pixelCustomState[n] = (t_color & 0x0F) | (t_brightness << 4);
    }
  }
  uint8_t getPixelCustomState(uint8_t n){
    return (n < BMC_MAX_PIXELS) ? pixelCustomState[n] : 0;
  }
  uint8_t getPixelCustomStateColor(uint8_t n){
    return (n < BMC_MAX_PIXELS) ? (pixelCustomState[n]&0x0F) : 0;
  }
  uint8_t getPixelCustomStateBrightness(uint8_t n){
    return (n < BMC_MAX_PIXELS) ? ((pixelCustomState[n]&0xF0)>>4) : 0;
  }
  /*
  uint32_t getPixelStates(){
    return pixelStates;
  }
  */
 /*
  #if BMC_MAX_PIXEL_PROGRAMS > 0
    // change the current pixel program
    void setPixelProgram(uint8_t t_program){
      pixelPrograms.setProgram(t_program);
    }
    // get the current pixel program
    uint8_t getPixelProgram(){
      return pixelPrograms.getProgram();
    }
  #endif
  */
#endif

#if BMC_MAX_RGB_PIXELS > 0
  // get RgbPixel Data
  /*
  void getRgbPixel(uint8_t n, bmcStoreRgbLed& t_item){
    getRgbPixel(layer, n, t_item);
  }
  void getRgbPixel(uint8_t t_page, uint8_t n, bmcStoreRgbLed& t_item){
    if(t_page<BMC_MAX_LAYERS && n<BMC_MAX_RGB_PIXELS){
      t_item = store.layers[t_page].rgbPixels[n];
    }
  }
#if BMC_NAME_LEN_LEDS > 1
  void getRgbPixelName(uint8_t n, char* t_string){
    getRgbPixelName(layer, n, t_string);
  }
  void getRgbPixelName(uint8_t t_page, uint8_t n, char* t_string){
    if(t_page<BMC_MAX_LAYERS && n<BMC_MAX_RGB_PIXELS){
      strcpy(t_string, store.layers[t_page].rgbPixels[n].name);
    }
  }
#endif
*/
  // used to control rgb pixels only by the sketch, no matter what layer
  // if the rgb pixel is set to custom this becomes it's state so your
  // sketch can have full control of it
  // set the specified color to on/off, valued values are
  // 0 for Red, 1 for Green and 2 for Blue
  void setRgbPixelCustomState(uint8_t n, uint8_t color, bool value){
    if(n < BMC_MAX_RGB_PIXELS && color < 3){
      bitWrite(rgbPixelCustomState[n], color, value);
    }
  }
  uint8_t getRgbPixelCustomState(uint8_t n){
    return (n < BMC_MAX_RGB_PIXELS) ? rgbPixelCustomState[n] : 0;
  }
  /*
  uint32_t getRgbPixelStates(uint8_t n){
    if(n==0){
      return rgbPixelStatesR;
    } else if(n==1){
      return rgbPixelStatesG;
    }
    return rgbPixelStatesB;
  }
  */

#endif

#if BMC_MAX_ENCODERS > 0
  // Get ENCODER Data on current layer
  /*
  void getEncoder(uint8_t t_index, bmcStoreEncoder& t_item){
    getEncoder(layer, t_index, t_item);
  }

  // Get ENCODER Data on specified layer
  void getEncoder(uint8_t t_page, uint8_t t_index, bmcStoreEncoder& t_item){
    if(t_page<BMC_MAX_LAYERS && t_index<BMC_MAX_ENCODERS){
      t_item = store.layers[t_page].encoders[t_index];
    }
  }
  #if BMC_NAME_LEN_ENCODERS > 1
    // get encoder name on current layer passing a pointer string
    void getEncoderName(uint8_t t_index, char* t_string){
      getEncoderName(layer, t_index, t_string);
    }
    // get encoder name on specified layer passing a pointer string
    void getEncoderName(uint8_t t_page, uint8_t t_index, char* t_string){
      if(t_page<BMC_MAX_LAYERS && t_index<BMC_MAX_ENCODERS){
        strcpy(t_string, store.layers[t_page].encoders[t_index].name);
      }
    }
  #endif
  */
#endif

#if BMC_MAX_GLOBAL_ENCODERS > 0
  // Get Global encoder Data
  /*
  void getGlobalEncoder(uint8_t t_index, bmcStoreEncoder& t_item){
    if(t_index<BMC_MAX_GLOBAL_ENCODERS){
      t_item = store.global.encoders[t_index];
    }
  }
  #if BMC_NAME_LEN_ENCODERS > 1
    // get global encoder name passing a pointer string
    void getGlobalEncoderName(uint8_t t_index, char* t_string){
      if(t_index<BMC_MAX_GLOBAL_ENCODERS){
        strcpy(t_string, store.global.encoders[t_index].name);
      }
    }
  #endif
  */
#endif

#if BMC_MAX_POTS > 0
  // Get POT Data on current layer
  /*
  void getPot(uint8_t n, bmcStorePot& t_item){
    getPot(layer, n, t_item);
  }
  // Get POT Data on specified layer
  void getPot(uint8_t t_page, uint8_t n, bmcStorePot& t_item){
    if(t_page<BMC_MAX_LAYERS && n<BMC_MAX_POTS){
      t_item = store.layers[t_page].pots[n];
    }
  }
  #if BMC_NAME_LEN_POTS > 1
    // get pot name on current layer passing a pointer string
    void getPotName(uint8_t n, char* t_string){
      getPotName(layer, n, t_string);
    }
    // get pot name on specified layer passing a pointer string
    void getPotName(uint8_t t_page, uint8_t n, char* t_string){
      if(t_page<BMC_MAX_LAYERS && n<BMC_MAX_POTS){
        strcpy(t_string, store.layers[t_page].pots[n].name);
      }
    }
  #endif
  // start/stop pot calibration, pot calibration data is global
  // so the calibration set is for that pot no matter what layer you are in.
  bool calibratePot(uint8_t n){
    potCalibration.toggle(n);
    return potCalibration.active();
  }
  */
#endif

#if BMC_MAX_GLOBAL_POTS > 0
/*
  // get global pot Data on current layer
  void getGlobalPot(uint8_t n, bmcStorePot& t_item){
    if(n<BMC_MAX_GLOBAL_POTS){
      t_item = store.global.pots[n];
    }
  }
  #if BMC_NAME_LEN_POTS > 1
    // get global pot name on current layer passing a pointer string
    void getGlobalPotName(uint8_t n, char* t_string){
      if(n<BMC_MAX_GLOBAL_POTS){
        strcpy(t_string, store.global.pots[n].name);
      }
    }
  #endif

  // start/stop global pot calibration, pot calibration data is global
  bool calibrateGlobalPot(uint8_t n){
    potCalibration.toggle(n);
    return potCalibration.active();
  }
  */
#endif

#if BMC_MAX_NL_RELAYS > 0
  // get NL RELAY Name Data
  /*
  void getRelayNL(uint8_t n, bmcStoreGlobalRelay& t_item){
    if(n<BMC_MAX_NL_RELAYS){
      t_item = store.global.relaysNL[n];
    }
  }
  #if BMC_NAME_LEN_RELAYS > 1
    void getRelayNLName(uint8_t n, char* t_string){
      if(n<BMC_MAX_NL_RELAYS){
        strcpy(t_string, store.global.relaysNL[n].name);
      }
    }
  #endif
  */
#endif

#if BMC_MAX_L_RELAYS > 0
  // get NL RELAY Name Data
  /*
  void getRelayL(uint8_t t_index, bmcStoreGlobalRelay& t_item){
    if(t_index<BMC_MAX_L_RELAYS){
      t_item = store.global.relaysL[t_index];
    }
  }
  #if BMC_NAME_LEN_RELAYS > 1
    void getRelayLName(uint8_t t_index, char* t_string){
      if(t_index<BMC_MAX_L_RELAYS){
        strcpy(t_string, store.global.relaysL[t_index].name);
      }
    }
  #endif
  */
#endif


#if BMC_MAX_CUSTOM_SYSEX > 0
/*
  // send the specified Custom SysEx Message to the specified Ports
  // @n the index of the custom sysex
  // @ports midi ports mask
  void sendCustomSysEx(uint8_t n, uint8_t ports){
    customSysEx.send(BMC_CUSTOM_SYSEX_SEND_A, ports, n);
  }
  // send 2 custom sysex messages merged into 1
  // all used bytes of message a are sent first then the used bytes of message b
  // @a the index of the first custom sysex
  // @b the index of the second custom sysex
  // @ports midi ports mask
  void sendMergedCustomSysEx(uint8_t a, uint8_t b, uint8_t ports){
    customSysEx.send(BMC_CUSTOM_SYSEX_SEND_MERGE, ports, a, b);
  }
*/
#endif

#if BMC_MAX_SKETCH_BYTES > 0
  // scroll thru sketch bytes, you must pass the initial value "n"
  // this function will then return the next value up or down
  // this function is to scroll the index of a sketch byte, useful for editors
  uint8_t scrollSketchByte(uint8_t n, uint8_t t_direction, uint8_t t_amount){
    if(n>=BMC_MAX_SKETCH_BYTES){
      return 0;
    }
    t_amount = (t_amount==0) ? 1 : t_amount;
    BMCScroller <uint8_t> scroller(0, BMC_MAX_SKETCH_BYTES-1);
    return scroller.scroll(t_amount, t_direction, true, n, 0, BMC_MAX_SKETCH_BYTES-1);
  }
  // scroll the value of a sketch byte up or down based on the sketch byte's data
  // n is the index of the sketch byte, that sketch byte value is then loaded and scrolled
  uint8_t scrollSketchByteValue(uint8_t n, uint8_t t_direction, uint8_t t_amount){
    return scrollSketchByteValue(n, getSketchByte(n), t_direction, t_amount);
  }
  // same as above but you can use it to pass it a value that you store on your sketch
  uint8_t scrollSketchByteValue(uint8_t n, uint8_t t_value, uint8_t t_direction, uint8_t t_amount){
    if(n>=BMC_MAX_SKETCH_BYTES){
      return 0;
    }
    t_amount = (t_amount==0) ? 1 : t_amount;
    BMCSketchByteData data = BMCBuildData::getSketchByteData(n);
    BMCScroller <uint8_t> scroller(data.min, data.max);
    return scroller.scroll(t_amount*data.step, t_direction, true, t_value, data.min, data.max);
  }
  // format the value of a sketch byte based on it's config format data
  // if value is not passed then the sketch byte's value is loaded from EEPROM
  void formatSketchByteValue(uint8_t n, char * t_string){
    formatSketchByteValue(n, getSketchByte(n), t_string);
  }
  void formatSketchByteValue(uint8_t n, uint8_t t_value, char * t_string){
    if(n>=BMC_MAX_SKETCH_BYTES){
      return;
    }
    BMCSketchByteData data = BMCBuildData::getSketchByteData(n);
    uint8_t fType = data.formatType;
    uint8_t fValue = data.formatValue;
    uint8_t fAppend = data.formatAppend;
    int value = 0;
    switch(fType){
      case 1:
        value = t_value + fValue;// add
        break;
      case 2:
        value = t_value - fValue;// substract
        break;
      case 3:
        value = t_value * fValue;// multiply
        break;
      case 4:
        value = t_value / fValue;// divide
        break;
      case 5:
        strcpy(t_string,(t_value==0)?"OFF":"ON");
        return;
    }
    char append[16] = "";
    switch(fAppend){
      case 0: strcpy(append,""); break;
      case 1: strcpy(append,"sec"); break;
      case 2: strcpy(append,"ms"); break;
      case 3: strcpy(append,"us"); break;
      case 4: strcpy(append,"mm"); break;
      case 5: strcpy(append,"cm"); break;
      case 6: strcpy(append,"m"); break;
      case 7: strcpy(append,"%"); break;
      case 8: strcpy(append,"degrees"); break;
      case 9: strcpy(append,"bpm"); break;
      case 10: strcpy(append,"hours"); break;
      case 11: strcpy(append,"minutes"); break;
      case 12: strcpy(append,"seconds"); break;
      case 13: strcpy(append,"days"); break;
      case 14: strcpy(append,"weeks"); break;
      case 15: strcpy(append,"hours"); break;
    }
    sprintf(t_string,"%d %s",value,append);
  }
#endif

#if defined(BMC_USE_FAS)
  bool fasConnected(){
    return sync.fas.connected();
  }
  void fasConnect(){
    sync.fas.connect();
  }
  void fasDisconnect(){
    sync.fas.disconnect();
  }
  void fasToggleConnection(){
    if(sync.fas.connected()){
      sync.fas.disconnect();
    } else {
      sync.fas.connect();
    }
  }
  // copy the current Preset Name into a buffer char array
  // the length of the char array must be at least 32 bytes
  bool getFasPresetName(char* str){
    sync.fas.getPresetName(str);
    return sync.fas.connected();
  }
  // get the synced preset number (0 index)
  // this is the actual preset number within your Fractal, these are not
  // broken into bank/preset but the location of the preset in your fractal's memory
  // depending on your Fractal the numbers will be:
  // Axe FX II: 0 to 383
  // Axe FX II XL/XL+: 0 tp 767
  // AX8: 0 to 511
  uint16_t getFasPresetNumber(){
    return sync.fas.getPresetNumber();
  }
  // get the synced scene number
  uint8_t getFasSceneNumber(){
    return sync.fas.getSceneNumber();
  }
  // get the synced preset Bank Number (0 index)
  // the Axe FX II has 384 presets that is 3 banks each with 128 presets
  // on Axe FX II a number from 0 to 2 will be returned
  // the Axe FX II XL and XL+ have 768 for a total of 6 banks of 128 presets each
  // so a number from 0 to 5 will be returned
  // the AX8 has 512 presets, 64 banks of 8 presets per bank
  // so a number from 0 to 63 will be returned
  uint8_t getFasPresetBankNumber(){
    return sync.fas.getPresetBankNumber();
  }
  // get the synced preset number within it's bank (0 index)
  // on Axe FX there are 128 presets per bank so a number from 000 to 127
  // will always be returned
  // on AX8 there are 8 presets per bank so a number from 000 to 007 will
  // always be returned.
  // use this in conjunction with getFasPresetBankNumber() to get the
  // bank # & preset # to display it on an LCD or OLED
  uint8_t getFasPresetInBankNumber(){
    return sync.fas.getPresetInBankNumber();
  }
  // change to a new FAS preset number, value is the actual preset number
  void setFasPresetNumber(uint16_t value){
    sync.fas.setPreset(value);
  }
  // change to a new FAS scene number, value must be 0 to 7
  void setFasSceneNumber(uint8_t value, bool revert=false){
    sync.fas.setSceneNumber(value, revert);
  }
  void setFasSceneScroll(bool t_up=true, bool t_endless=true, bool t_revert=false, uint8_t t_min=0, uint8_t t_max=7){
    sync.fas.sceneScroll(t_up, t_endless, t_revert, t_min, t_max);
  }
  bool getFasBlockBypassed(uint8_t n){
    return sync.fas.isBlockBypassed(n);
  }
  bool getFasBlockEngaged(uint8_t n){
    return sync.fas.isBlockEngaged(n);
  }
  bool getFasIsBlockX(uint8_t n){
    return sync.fas.isBlockX(n);
  }
  bool getFasIsBlockY(uint8_t n){
    return sync.fas.isBlockY(n);
  }
  void getFasTuner(BMCTunerData& buff){
    sync.fas.getTunerData(buff);
  }
  bool fasIsBlockBypassed(uint8_t blockId){
    return sync.fas.isBlockBypassed(blockId);
  }
  bool fasIsBlockEngaged(uint8_t blockId){
    return sync.fas.isBlockEngaged(blockId);
  }
  bool fasIsBlockX(uint8_t blockId){
    return sync.fas.isBlockX(blockId);
  }
  bool fasIsBlockY(uint8_t blockId){
    return sync.fas.isBlockY(blockId);
  }
  void fasToggleTuner(){
    sync.fas.toggleTuner();
  }
  void fasTapTempo(){
    sync.fas.tapTempo();
  }
  void fasSendSetBlockParameter(uint8_t blockId, uint8_t parameterId, uint16_t value){
    sync.fas.sendSetBlockParameter(blockId, parameterId, value);
  }
  void fasSendGetBlockParameter(uint8_t blockId, uint8_t parameterId){
    sync.fas.sendGetBlockParameter(blockId, parameterId);
  }
  void fasSyncParameter(uint8_t slot, uint8_t block, uint8_t parameter){
    sync.fas.setSyncedParameter(slot, block, parameter);
  }
  uint16_t fasGetSyncedParameter(uint8_t block, uint8_t parameter){
    return sync.fas.getSyncedParameterValue(block, parameter);
  }
  uint16_t fasGetSyncedParameter(uint8_t slot){
    return sync.fas.getSyncedParameterValue(slot);
  }
  void fasChangeSyncedParameter(uint8_t slot, uint16_t value){
    sync.fas.sendChangeSyncedParameter(slot, value);
  }
#endif

#if defined(BMC_USE_BEATBUDDY)
  bool beatBuddySynced(){
    return sync.beatBuddy.inSync();
  }
  bool beatBuddyPlaying(){
    return sync.beatBuddy.isPlaying();
  }
  bool getBeatBuddyCurrentPart(){
    return sync.beatBuddy.getSongPart();
  }
  void sendBeatBuddyCommand(uint8_t value, uint8_t data=127){
    sync.beatBuddy.sendCommand(value, data);
  }
#endif


  // for master or slave clock
  // get the current BPM
  uint16_t getMidiClockBpm(){
    return midiClock.getBpm();
  }
  // only works when on master clock
  // set the Clock's BPM
  void setMidiClockBpm(uint16_t t_bpm){
    midiClock.setBpm(t_bpm);
  }
  // only works when on master clock
  // simulates a Tap Tempo
  // the Clock BPM is determined based on how often the function is called
  // for example if there's a gap of 500ms between calling this function
  // the BPM would be set to 120 BPM, (60000/500) = 120
  void midiClockTap(){
    midiClock.tap();
  }
  bool editorConnected(){
    return globals.editorConnected();
  }
  bool bleConnected(){
    return globals.bleConnected();
  }
  bool hostConnected(){
    return globals.hostConnected();
  }
  // STOP WATCH
  uint8_t getStopwatchState(){
    return stopwatch.getState();
  }
  uint8_t getStopwatchHours(){
    return stopwatch.hours;
  }
  uint8_t getStopwatchMinutes(){
    return stopwatch.minutes;
  }
  uint8_t getStopwatchSeconds(){
    return stopwatch.seconds;
  }
  uint32_t getStopwatchTimeout(){
    return stopwatch.timeout;
  }
  // RUN TIME
  uint32_t getRuntime(){
    return runTime.getSeconds();
  }
  //TIME
#if defined(BMC_USE_TIME)
  uint8_t getHour(){
    return editor.getHour();
  }
  uint8_t getMinute(){
    return editor.getMinute();
  }
  uint8_t getSecond(){
    return editor.getSecond();
  }
  uint8_t getDay(){
    return editor.getDay();
  }
  uint8_t getMonth(){
    return editor.getMonth();
  }
  uint16_t getYear(){
    return editor.getYear();
  }
#endif

  // ***************************
  // ******** MESSENGER ********
  // ***************************
  // with the Messenger you can send a signed long value and a char array
  // the string can only be up to 32 characters
  // send a value and a string as a char array
  void messengerSend(uint16_t status, signed long value, char* str, uint8_t len){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, value, str, len);
  }
  // send a value and a string as a const string
  void messengerSend(uint16_t status, signed long value, const char* str){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, value, str);
  }
  // send just a value without string
  void messengerSend(uint16_t status, signed long value){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, value, "");
  }
  // send just a char array string
  void messengerSend(uint16_t status, char* str, uint8_t len){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, 0, str, len);
  }
  // send just a const string
  void messengerSend(uint16_t status, const char* str){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, 0, str);
  }

#if defined(BMC_MIDI_BLE_ENABLED)
  // BLE MIDI CONTROLS, ignored if BLE is not compiled
  void disconnectBLE(){
    midi.disconnectBLE();
  }
#endif

  // ***************************
  // ********* TIMING **********
  // ***************************
  // used only during DEBUG
  // use these to time how long it takes for a piece of code to execute
  // BMC has 1 millis and 1 micros timer this just a simple timer
  // you can specify how many timers you want by defining BMC_DEBUG_MAX_TIMING
  // in your config file, the value of BMC_DEBUG_MAX_TIMING is the number of timers
  // you want. Once a timer is complete it will print out the time it took on the serial monitor

  // start a timer specified by n (inclusive)
  // @n = the index of the timer you want to use
  // @t_micros = true if you want to time the number of microseconds, false for millis
  // for every timer you compile there's a millis timer and a micros timer
  // t_micros specifies which one you want to use
  void startTiming(uint8_t n, bool t_micros=false){
#if defined(BMC_DEBUG)
    debugStartTiming(n, t_micros);
#endif
  }

  // stop the active timer specified by n (inclusive)
  // @n = the index of the timer you want to use
  // @t_micros = true if you want to time the number of microseconds, false for millis
  // for every timer you compile there's a millis timer and a micros timer
  // t_micros specifies which one you want to use
  // when you stop an active timer BMC will print it's output to the Serial monitor
  unsigned long stopTiming(uint8_t n, bool t_micros=false){
#if defined(BMC_DEBUG)
    return debugStopTiming(n, t_micros);
#endif
    return 0;
  }

  // ***************************
  // ******* MIDI SEND *********
  // ***************************
  void sendRealTime(uint8_t port, uint8_t type, uint8_t cable=0){
    midi.sendRealTime(port, type, cable);
  }
  void sendSysEx(uint8_t port, uint8_t *data, uint16_t size, bool hasTerm=false, uint8_t cable=0){
    midi.sendSysEx(port, data, size, hasTerm, cable);
  }
  void sendProgramChange(uint8_t port, uint8_t channel, uint8_t program, uint8_t cable=0){
    midi.sendProgramChange(port, channel, program, cable);
  }
  void sendControlChange(uint8_t port, uint8_t channel, uint8_t control, uint8_t value, uint8_t cable=0){
    midi.sendControlChange(port, channel, control, value, cable);
  }
  void sendNoteOn(uint8_t port, uint8_t channel, uint8_t note, uint8_t velocity, uint8_t cable=0){
    midi.sendNoteOn(port, channel, note, velocity, cable);
  }
  void sendNoteOff(uint8_t port, uint8_t channel, uint8_t note, uint8_t velocity, uint8_t cable=0){
    midi.sendNoteOff(port, channel, note, velocity, cable);
  }
  void sendPitchBend(uint8_t port, uint8_t channel, int16_t value, uint8_t cable=0){
    midi.sendPitchBend(port, channel, value, cable);
  }
  void sendAfterTouch(uint8_t port, uint8_t channel, uint8_t pressure, uint8_t cable=0){
    midi.sendAfterTouch(port, channel, pressure, cable);
  }
  void sendAfterTouchPoly(uint8_t port, uint8_t channel, uint8_t note, uint8_t pressure, uint8_t cable=0){
    midi.sendAfterTouchPoly(port, channel, note, pressure, cable);
  }
  void sendTimeCodeQuarterFrame(uint8_t port, uint8_t type, uint8_t value, uint8_t cable=0){
    midi.sendTimeCodeQuarterFrame(port, type, value, cable);
  }
  void sendSongPosition(uint8_t port, uint16_t beats, uint8_t cable=0){
    midi.sendSongPosition(port, beats, cable);
  }
  void sendSongSelect(uint8_t port, uint8_t song, uint8_t cable=0){
    midi.sendSongSelect(port, song, cable);
  }
  void sendTuneRequest(uint8_t port, uint8_t cable=0){
    midi.sendTuneRequest(port, cable);
  }
  void beginRpn(uint8_t port, uint8_t channel, uint16_t number, uint8_t cable=0){
    midi.beginRpn(port, channel, number, cable);
  }
  void sendRpnValue(uint8_t port, uint8_t channel, uint16_t value, uint8_t cable=0){
    midi.sendRpnValue(port, channel, value, cable);
  }
  void sendRpnIncrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendRpnIncrement(port, channel, amount, cable);
  }
  void sendRpnDecrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendRpnDecrement(port, channel, amount, cable);
  }
  void endRpn(uint8_t port, uint8_t channel, uint8_t cable=0){
    midi.endRpn(port, channel, cable);
  }
  void beginNrpn(uint8_t port, uint8_t channel, uint16_t number, uint8_t cable=0){
    midi.beginNrpn(port, channel, number, cable);
  }
  void sendNrpnValue(uint8_t port, uint8_t channel, uint16_t value, uint8_t cable=0){
    midi.sendNrpnValue(port, channel, value, cable);
  }
  void sendNrpnIncrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendNrpnIncrement(port, channel, amount, cable);
  }
  void sendNrpnDecrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendNrpnDecrement(port, channel, amount, cable);
  }
  void endNrpn(uint8_t port, uint8_t channel, uint8_t cable=0){
    midi.endNrpn(port, channel, cable);
  }

  // ********************************************************************
  // METHODS TO UPDATE THE STORE BUT ONLY IF NOT CONNECTED TO THE EDITOR
  // ********************************************************************

  // ***************************
  // ******* SETTINGS *********
  // ***************************

  // Save any changes to settings and re-assign all data, writes to EEPROM
  // also calls the onStoreUpdate callback
  void settingsSave(){
    if(!globals.editorConnected()){
      editor.saveSettings();
      assignStoreData();
    }
  }
  // Change the PWM when off setting for Leds
  // if @save is true it will call the settingsSave() writing the store to EEPROM
  void settingsSetPwmOff(bool state, bool save=false){
    if(!globals.editorConnected()){
      settings.setPwmDimWhenOff(state);
      if(save){
        settingsSave();
      }
    }
  }
  // Get the PWM when off setting for Leds
  bool settingsGetPwmOff(){
    return settings.getPwmDimWhenOff();
  }
  // Change the Buttons Hold Time Setting for Buttons
  // if @save is true it will call the settingsSave() writing the store to EEPROM
  // @value must be a value from 0 to 15, where 0 is 500ms, 1 is 750ms, 2 is 1000ms, etc.
  // each value after 0 adds 250ms to the hold time.
  // When the value is passed to buttons the actual hold threshold is ((value+2)*250)
  // this is so that with a value of 0 the hold threshold is 500ms, that's the minimum
  // since during testing i've found that a value any lower than that is unusable.
  void settingsSetButtonHold(uint8_t value, bool save=false){
    if(!globals.editorConnected() && value<=15){
      settings.setButtonHoldThreshold(value);
      if(save){
        settingsSave();
      }
    }
  }
  // Get the Buttons Hold Threshold Setting for Buttons
  // this value will range from 0 to 15
  // to get the actual time in milliseconds set inMillis to true
  uint8_t settingsGetButtonHold(bool inMillis=false){
    if(inMillis){
      return (settings.getButtonHoldThreshold()+2)*250;
    }
    return settings.getButtonHoldThreshold();
  }
};

#endif
