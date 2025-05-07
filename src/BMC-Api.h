// See https://www.roxxxtar.com/bmc for more details 
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
  // *********  CALLBACKS  ********
  // ******************************

  // * GROUP: SYSTEM
  // triggered when BMC runs it's update() method the very first time.
  void onFirstLoop(void (*fptr)()){
    callback.firstLoop = fptr;
  }
  // * GROUP: SYSTEM
  // triggers every 1 second, additionally adds the stopwatch state as a parameter
  void onOneSecondPassed(void (*fptr)(uint8_t stopwatchState)){
    callback.oneSecondPassed = fptr;
  }
  // * GROUP: SYSTEM
  // DEPRECATED, USE onStoreUpdate INSTEAD
  void onEditorUpdate(void (*fptr)()){
    onStoreUpdate(fptr);
  }
  // * GROUP: SYSTEM
  // triggered when EEPROM has been updated either by the editor or the API
  void onStoreUpdate(void (*fptr)()){
    callback.storeUpdated = fptr;
  }
  // * GROUP: SYSTEM
  // triggered when the editor connects/disconnects
  // @state true if editor is connected
  void onEditorConnection(void (*fptr)(bool state)){
    callback.editorConnection = fptr;
  }
  // * GROUP: SYSTEM
  // triggered when BMC erases the active EEPROM, this usually only happens when
  // you have multiple stores available and BMC changes the store to one that doesn't
  // match the current CRC
  void onEepromErased(void (*fptr)()){
    callback.eepromErased = fptr;
  }
  // * GROUP: SYSTEM
  // triggered when a value stream is handled
  void onValueStream(void (*fptr)(BMCValueStream item)){
    callback.valueStream = fptr;
  }
  // * GROUP: SYSTEM
  // triggered when a BMC Trigger has been handled
  void onTrigger(void (*fptr)(uint32_t source, uint32_t event)){
    callback.midiTriggerReceived = fptr;
  }// * GROUP: SYSTEM
  // triggered when a Menu Command is handled by a button, encoder, API, etc.
  void onMenu(void (*fptr)(uint8_t t_command)){
    callback.menuCommand = fptr;
  }
  // * GROUP: SYSTEM
  // triggered when the Typer value has been Updated
  void onTyperUpdate(void (*fptr)(uint16_t t_value, uint16_t t_rawValue)){
    callback.typerCommand = fptr;
  }
  // * GROUP: SYSTEM
  // triggered when the Typer value has been Updated and you set it to custom calback
  void onTyperCustomUpdate(void (*fptr)(uint16_t t_value, uint16_t t_rawValue)){
    callback.typerCustomCommand = fptr;
  }
  // * GROUP: SYSTEM
  // triggered half way thru the BMC update() method, this is in case you need
  // to do other tasks like update a display without waiting for the BMC update()
  // method to complete
  void onMidUpdate(void (*fptr)()){
    callback.midUpdate = fptr;
  }
  // * GROUP: SYSTEM
  // triggered when Messenger message is received from the Editor App.
  void onMessenger(void (*fptr)(BMCMessenger t_messenger)){
    callback.messengerReceived = fptr;
  }
  // * GROUP: LAYERS
  // triggered when you change layers, also triggered when BMC runs it's first loop
  void onLayerChange(void (*fptr)(uint8_t layer)){
    callback.pageChanged = fptr;
  }
  // * GROUP: MIDI
  // triggered when a MIDI message is received
  void onMidiRx(void (*fptr)(BMCMidiMessage data)){
    callback.midiReceived = fptr;
  }
  // * GROUP: MIDI
  // triggered when a MIDI Clock message is received
  void onMidiClockTick(void (*fptr)()){
    callback.midiClockTickReceived = fptr;
  }
  // * GROUP: MIDI
  // triggered every 24 times a MIDI Clock message is received
  void onMidiClockBeat(void (*fptr)()){
    callback.midiClockBeat = fptr;
  }
  // * GROUP: MIDI
  // triggered when the Master/Slave Clock has changed it's tempo
  void onMidiClockBpmChange(void (*fptr)(uint16_t tempo)){
    callback.midiClockBpmChange = fptr;
  }
  // * GROUP: MIDI
  // triggered when a midi message was sent or received
  void onMidiActivity(void (*fptr)(bool in, bool out)){
    callback.midiActivity = fptr;
  }
  // * GROUP: MIDI
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
  // * GROUP: MIDI
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
   // * GROUP: HARDWARE
  // you must assign it to hardware, the event is labeled HARDWARE:Custom in the editor events
  // this will allow you to trigger a function in your sketch when a button is pressed, encoder rotated, etc.
  void onCustomActivity(bool (*fptr)(uint8_t deviceType, uint16_t deviceIndex, uint8_t id, uint8_t dat1, uint8_t dat2)){
    callback.customActivity = fptr;
  }
  
  // * GROUP: HARDWARE
  // triggered when 2 buttons are pressed at the same time
  // see src/devices/physical/buttons/BMC-ButtonsDualHandler.h for info on how this works.
  void onButtonDualPress(void (*fptr)(uint16_t btn1, uint16_t btn2)){
    callback.buttonDualPress = fptr;
  }
  // * GROUP: HARDWARE
  // triggered when an global button is pressed, released, etc.
  // see src/devices/physical/buttons/BMC-ButtonsDualHandler.h for info on how this works.
  void onGlobalButtonDualPress(void (*fptr)(uint16_t btn1, uint16_t btn2)){
    callback.globalButtonDualPress = fptr;
  }
  // * GROUP: HARDWARE
  // Set callback for buttons activity,
  // called when a button changes states
  // @n = index of button
  // @eventIndex = event's index
  // @trigger = trigger type (BMC_TRIG_PRESS, etc.)

  // list of triggers
  // - BMC_TRIG_PRESS
  // - BMC_TRIG_RELEASE
  // - BMC_TRIG_HOLD
  // - BMC_TRIG_DOUBLE_PRESS
  // - BMC_TRIG_CONTINUOUS
  // - BMC_TRIG_ALT_PRESS
  // - BMC_TRIG_RELEASE_PRESS
  // - BMC_TRIG_RELEASE_HOLD
  // - BMC_TRIG_RELEASE_DOUBLE_PRESS
  // - BMC_TRIG_RELEASE_CONTINUOUS
  // - BMC_TRIG_RELEASE_ALT
  // - BMC_TRIG_STATE_CHANGE
  void onButtonActivity(void (*fptr)(uint16_t n, uint8_t eventIndex, uint8_t trigger)){
    #if BMC_MAX_BUTTONS > 0
      callback.globalButtonActivity = fptr;
    #endif
  }

  // * GROUP: HARDWARE
  // Set callback for global buttons activity
  // called when a global button changes states
  // @n = index of global button
  // @eventIndex = event's index
  // @trigger = trigger type (BMC_TRIG_PRESS, etc.)
  // same list of triggers as onGlobalButtonDualPress
  void onGlobalButtonActivity(void (*fptr)(uint16_t n, uint8_t eventIndex, uint8_t trigger)){
    #if BMC_MAX_GLOBAL_BUTTONS > 0
      callback.globalButtonActivity = fptr;
    #endif
  }
  // * GROUP: HARDWARE
  // triggered when an aux jack detects a plug connected or disconnected
  // @n the Aux Jack Index that had a state change.
  // @state true if a connection has been made, false if disconnected.
  void onAuxJackConnection(void (*fptr)(uint8_t n, bool state)){
    callback.auxJackConnection = fptr;
  }


#ifdef BMC_USB_HOST_ENABLED
  // * GROUP: SYSTEM
  // triggered when a USB MIDI Device is connected to the Teensy's USB Host
  void onHostConnectionChange(void (*fptr)(bool t_connected)){
    callback.hostConnection = fptr;
  }
#endif

#ifdef BMC_MIDI_BLE_ENABLED
  // * GROUP: SYSTEM
  // triggered when BMC connects to a BLE Master Device
  void onBleConnectionChange(void (*fptr)(bool t_connected)){
    callback.bleConnection = fptr;
  }
#endif
  
  
#ifdef BMC_USE_FAS
  // * GROUP: SYNC/FAS
  // triggered when BMC Detects a FAS device has been connected/disconnected
  void onFasConnectionChange(void (*fptr)(bool state)){
    callback.fasConnection = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when the FAS preset has changed
  void onFasPresetChange(void (*fptr)(uint16_t n)){
    callback.fasPresetChange = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when the FAS preset name has been received
  void onFasPresetName(void (*fptr)(char* str)){
    callback.fasPresetName = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when the FAS scene has changed
  void onFasSceneChange(void (*fptr)(uint8_t n)){
    callback.fasSceneChange = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when any FAS Effect Block has changed it's states
  void onFasBlocksChange(void (*fptr)()){
    callback.fasBlocksChange = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when the FAS Tuner has been turned on/off
  void onFasTunerStateChange(void (*fptr)(bool state)){
    callback.fasTunerStateChange = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when the FAS tuner data has been received
  // the BMCTunerData struct
  // contains the following attributes
  // uint8_t stringNumber = 0;
  // uint8_t note = 0;
  // uint8_t pitchRaw = 0;
  // int pitch = 0;
  // char noteName[3] = "";
  void onFasTunerReceived(void (*fptr)(BMCTunerData& data)){
    callback.fasTunerReceived = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when the FAS Looper has been activated or stopped
  void onFasLooperStateChange(void (*fptr)(bool state)){
    callback.fasLooperStateChange = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when the FAS Looper data has been received
  void onFasLooperReceived(void (*fptr)(uint8_t data, uint8_t position)){
    callback.fasLooperReceived = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when FAS CPU usage has been received
  void onFasCpuReceived(void (*fptr)(uint8_t n)){
    callback.fasCpuReceived = fptr;
  }
  // * GROUP: SYNC/FAS
  // triggered when a FAS Effect Block Parameter has been received
  void onFasBlockParameterReceived(void (*fptr)(uint8_t block, uint8_t param, uint16_t value, char* str, uint8_t strLen)){
    callback.fasBlockParameterReceived = fptr;
  }
#endif

#ifdef BMC_USE_BEATBUDDY
  // * GROUP: SYNC/BEATBUDDY
  void onBeatBuddyBeatLocationChange(void (*fptr)(uint8_t t_location, uint8_t numerator)){
    callback.beatBuddyBeatLocation = fptr;
  }
#endif
  // * GROUP: PRESETS
  // triggered when a BMC Preset has changed
  void onPresetChange(void (*fptr)(uint8_t t_bank, uint8_t t_preset)){
    callback.presetChanged = fptr;
  }
  // * GROUP: PRESETS
  // triggered when a BMC Preset Bank has changed
  void onPresetsBankChange(void (*fptr)(uint8_t n)){
    callback.presetBankChanged = fptr;
  }
  // * GROUP: SETLIST
  // triggered when the current BMC SetList has changed
  void onSetListChange(void (*fptr)(uint8_t n)){
    callback.setListChanged = fptr;
  }
  // * GROUP: SETLIST
  // triggered when the current BMC SetList Song has changed
  void onSetListSongChange(void (*fptr)(uint8_t n)){
    callback.setListSongChanged = fptr;
  }

  // ******************************
  // *****  DAW  *****
  // ******************************

#ifdef BMC_USE_DAW_LC
  // * GROUP: SYNC/DAW
  // passes the state of the connect, true if a project is loaded
  void onDawOnline(void (*fptr)(bool state)){
    callback.dawOnline = fptr;
  }
  // * GROUP: SYNC/DAW
  // passes the sysex message containing the updated LCD string
  void onDawRecievedLCD(void (*fptr)(BMCMidiMessage data)){
    callback.dawRecievedLCD = fptr;
  }
  // * GROUP: SYNC/DAW
  // more info to come
  void onDawRecievedTimeDisplay(void (*fptr)(uint8_t digit, char character)){
    callback.dawRecievedTimeDisplay = fptr;
  }
  // * GROUP: SYNC/DAW
  // more info to come
  void onDawRecievedAssignmentDisplay(void (*fptr)(uint8_t digit, char character)){
    callback.dawRecievedAssignmentDisplay = fptr;
  }
  // * GROUP: SYNC/DAW
  // passes the meter value for a channel
  void onDawRecievedChannelMeter(void (*fptr)(uint8_t channel, uint8_t value)){
    callback.dawRecievedChannelMeter = fptr;
  }
  // * GROUP: SYNC/DAW
  // passes the meter value for a channel, includes the overload led status
  void onDawChannelMeterUpdate(void (*fptr)(uint8_t channel, uint8_t value, uint8_t overload)){
    callback.dawChannelMeterUpdate = fptr;
  }
  // * GROUP: SYNC/DAW
  // more info to come
  void onDawReceivedTimeCodeDigit(void (*fptr)(uint8_t digit, uint8_t value)){
    callback.dawReceivedTimeCodeDigit = fptr;
  }
  // * GROUP: SYNC/DAW
  // passes the value of the VPOT ring for the specified channel
  void onDawChannelVPotUpdate(void (*fptr)(uint8_t channel, uint8_t value, uint8_t centered, uint8_t mode)){
    callback.dawChannelVPotUpdate = fptr;
  }
  // * GROUP: SYNC/DAW
  // passes the specified channel's fader position
  void onDawRecievedChannelFaderPosition(void (*fptr)(uint8_t channel, int value)){
    callback.dawRecievedChannelFaderPosition = fptr;
  }
  // * GROUP: SYNC/DAW
  // passes the master channel's fader position
  void onDawRecievedMasterFaderPosition(void (*fptr)(int value)){
    callback.dawRecievedMasterFaderPosition = fptr;
  }
  // * GROUP: SYNC/DAW
  // receive the state of a channel, true if the channel is currently selected
  void onDawRecievedChannelSelect(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelSelect = fptr;
  }
  // * GROUP: SYNC/DAW
  // receive the solo state of a channel, true if the channel is currently in solo
  void onDawRecievedChannelSolo(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelSolo = fptr;
  }
  // * GROUP: SYNC/DAW
  // receive the mute state of a channel, true if the channel is currently in mute
  void onDawRecievedChannelMute(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelMute = fptr;
  }
  // * GROUP: SYNC/DAW
  // receive the rec/ready state of a channel, true if the channel is currently in rec/ready
  void onDawRecievedChannelRecReady(void (*fptr)(uint8_t channel, bool state)){
    callback.dawRecievedChannelRecReady = fptr;
  }
  // * GROUP: SYNC/DAW
  // receive the state leds, @cmd will carry the function of the LED, see documentation
  void onDawRecievedLedState(void (*fptr)(uint8_t cmd, bool state)){
    callback.dawRecievedLedState = fptr;
  }
  // * GROUP: SYNC/DAW
  // returns the selected channel number
  uint8_t getDawSelectedTrack(){
    return sync.daw.getSelectedChannel();
  }
  // * GROUP: SYNC/DAW
  // returns state of a specified LED in the led ring of a VPOT.
  // you can use this for a custom led ring to update weather that led should
  // be on or off
  uint8_t getDawVPotLedState(uint8_t channel, uint8_t ledN){
    return sync.daw.getVPotLedState(channel, ledN);
  }
  // * GROUP: SYNC/DAW
  // sends a rotation of a v-pot
  void sendDawVPot(uint8_t ch, bool clockwise, uint8_t ticks){
    sync.daw.sendVPot(ch, clockwise, ticks);
  }
  // * GROUP: SYNC/DAW
  // sends a button press command
  void sendDawButton(uint8_t cmd, uint8_t ch, bool release){
    sync.daw.sendButtonCommand(cmd, ch, release);
  }
#endif
  // ******************************
  // *****  STOPWATCH  *****
  // ******************************
  // * GROUP: SYSTEM
  void stopwatchControl(uint8_t cmd, uint8_t h=0, uint8_t m=0, uint8_t s=0){
    stopwatchCmd(cmd, h, m, s);
  }

#ifdef BMC_HAS_DISPLAY
#if BMC_MAX_OLED > 0
  // * GROUP: HARDWARE
  BMC_SSD1306 & displayGetOled(uint8_t n){
    return display.get(n);
  }
#endif
#if BMC_MAX_ILI9341_BLOCKS > 0
  
#endif
#endif



  // * GROUP: SYSTEM
  // retrieve a name from the names library
  bmcStoreName getName(uint16_t n){
    if(n < BMC_MAX_NAMES_LIBRARY){
      return store.global.names[n];
    }
    bmcStoreName t;
    return t;
  }


  // ******************************
  // ***** LOCAL MIDI CONTROL *****
  // ******************************
  // * GROUP: MIDI
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  void setLocalProgram(uint8_t t_channel, uint8_t t_program){
    midi.setLocalProgram(t_channel, t_program);
  }
  // * GROUP: MIDI
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  void setLocalControl(uint8_t t_channel, uint8_t t_control, uint8_t t_value){
    midi.setLocalControl(t_channel, t_control, t_value);
  }
  // * GROUP: MIDI
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  uint8_t getLocalProgram(uint8_t t_channel){
    return midi.getLocalProgram(t_channel);
  }
  // * GROUP: MIDI
  // @t_channel MUST be 1 thru 16, not 0 thru 15
  // all other parameters are 0 indexed
  uint8_t getLocalControl(uint8_t t_channel, uint8_t t_control){
    return midi.getLocalControl(t_channel, t_control);
  }

  // * GROUP: SYSTEM
  // switch to a different Store, only available with SD Card and 24LC256 EEPROM
  // since this changed was triggered by your sketch we'll delay
  // it in case it wasn't programmed properly and you are changing
  // the address way too many times.
  bool changeStore(uint8_t t_address){
    if(editor.changeStore(t_address)){
      BMC_PRINTLN("Store Address has been changed to", getStoreAddress());
      delay(250);
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
  // * GROUP: SYSTEM
  // get the current store address
  uint8_t getStoreAddress(){
    return editor.getStoreAddress();
  }

  // * GROUP: LAYERS
  // change to a new layer.
  // if n is not a valid layer number, nothing happens
  // if n is the same as the current layer, nothing happens
  void changeLayer(uint8_t n){
    setLayer(n);
  }
  // * GROUP: LAYERS
  // get the current layer
  uint8_t getCurrentLayer(){
    return getLayer();
  }
  // * GROUP: LAYERS
  // retrieve the name of the current layer
  bmcStoreName getLayerName(){
    return getLayerName(layer);
  }
  // * GROUP: LAYERS
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
  // * GROUP: LAYERS
  // move to the next layer
  // if t_wrap is true and you are already on the last layer, you will go to the first layer
  void pageUp(bool t_wrap=true){
    scrollLayer(true, t_wrap, 0, BMC_MAX_LAYERS-1, 1);
  }
  // * GROUP: LAYERS
  // move to the previous layer
  // if t_wrap is true and you are already on the first layer, you will go to the last layer
  void pageDown(bool t_wrap=true){
    scrollLayer(false, t_wrap, 0, BMC_MAX_LAYERS-1, 1);
  }
#endif
// ****************************
// *****      NAMES       *****
// ****************************
// get the name of a device
// @deviceType the device ID, exp: BMC_DEVICE_ID_LAYER
// list of current device IDs can be found in src/utility/BMC-Def.h
// @index index of the device
// @str char array reference, it must be big enough to hold names
// you should always use BMC_MAX_NAMES_LENGTH as the size of the char array
// exp: str[BMC_MAX_NAMES_LENGTH]
// NOTE: not all devices have names.
// -------------------------------------------
// device types at the time of writing this
// - BMC_DEVICE_ID_LAYER
// - BMC_DEVICE_ID_EVENT
// - BMC_DEVICE_ID_NAME

// hardware
// - BMC_DEVICE_ID_BUTTON
// - BMC_DEVICE_ID_GLOBAL_BUTTON
// - BMC_DEVICE_ID_LED
// - BMC_DEVICE_ID_GLOBAL_LED
// - BMC_DEVICE_ID_ENCODER
// - BMC_DEVICE_ID_GLOBAL_ENCODER
// - BMC_DEVICE_ID_POT
// - BMC_DEVICE_ID_GLOBAL_POT
// - BMC_DEVICE_ID_PIXEL
// - BMC_DEVICE_ID_GLOBAL_PIXEL
// - BMC_DEVICE_ID_RGB_PIXEL
// - BMC_DEVICE_ID_GLOBAL_RGB_PIXEL
// - BMC_DEVICE_ID_BI_LED
// - BMC_DEVICE_ID_GLOBAL_BI_LED
// - BMC_DEVICE_ID_TRI_LED
// - BMC_DEVICE_ID_GLOBAL_TRI_LED
// - BMC_DEVICE_ID_MAGIC_ENCODER
// - BMC_DEVICE_ID_GLOBAL_MAGIC_ENCODER

// only layer
// - BMC_DEVICE_ID_OLED
// - BMC_DEVICE_ID_ILI
// - BMC_DEVICE_ID_PIXEL_STRIP

// only global
// - BMC_DEVICE_ID_NL_RELAY
// - BMC_DEVICE_ID_L_RELAY
// - BMC_DEVICE_ID_AUX_JACK

// pot calibration
// - BMC_DEVICE_ID_POT_CALIBRATION

// presets and setlist
// - BMC_DEVICE_ID_PRESET
// - BMC_DEVICE_ID_SETLIST
// - BMC_DEVICE_ID_SETLIST_SONG
// - BMC_DEVICE_ID_SETLIST_SONG_LIBRARY

// special events
// - BMC_DEVICE_ID_CUSTOM_SYSEX
// - BMC_DEVICE_ID_TRIGGER
// - BMC_DEVICE_ID_TEMPO_TO_TAP
// - BMC_DEVICE_ID_PIXEL_PROGRAM
// - BMC_DEVICE_ID_TIMED_EVENT
// - BMC_DEVICE_ID_LFO

// others
// - BMC_DEVICE_ID_SKETCH_BYTE
// - BMC_DEVICE_ID_PORT_PRESET
// - BMC_DEVICE_ID_SHORTCUTS
// - BMC_DEVICE_ID_LAYER_EVENT
  // * GROUP: HARDWARE
void getDeviceName(uint8_t deviceType, uint16_t index, char* str){
  editor.getDeviceNameText(deviceType, index, str);
}

// ******************************
// *****      PRESETS       *****
// ******************************
#if BMC_MAX_PRESETS > 0
  // * GROUP: PRESETS
  // returns number of events the current preset has
  uint8_t getPresetLength(){
    return presets.getLength();
  }
  // * GROUP: PRESETS
  // returns number of events a specified preset has
  uint8_t getPresetLength(uint8_t t_bank, uint8_t t_preset){
    return presets.getLength(t_bank, t_preset);
  }
  // * GROUP: PRESETS
  // returns the current preset number (within the current bank)
  uint8_t getPreset(){
    return presets.get();
  }
  // * GROUP: PRESETS
  // returns the current bank number
  uint8_t getPresetBank(){
    return presets.getBank();
  }
  // * GROUP: PRESETS
  // returns the actual index of a preset, in BMC presets are arranged
  // in banks, for example preset index 0 is bank 0 / preset 0
  // preset index 2 is bank 0 / preset 2 etc.
  // this function returns the actual index of the preset
  uint16_t getPresetIndex(){
    return presets.getIndex();
  }
  // * GROUP: PRESETS
  // set to the specified preset within the current bank
  void setPresetNumber(uint8_t t_preset, bool t_retrigger = false){
    presets.setPreset(t_preset, t_retrigger);
  }
  // * GROUP: PRESETS
  // set to the specified bank
  void setPresetBank(uint8_t t_bank, bool t_retrigger = false){
    presets.setBank(t_bank, t_retrigger);
  }
  // * GROUP: PRESETS
  // set to a preset by specifying the preset index
  void setPresetByIndex(uint16_t t_preset, bool t_retrigger = false){
    presets.setByIndex(t_preset, t_retrigger);
  }
  // * GROUP: PRESETS
  // go to the next preset within the current bank
  // @t_wrap true to go to first preset after reaching the last one
  void presetNext(bool t_wrap){
    presets.scrollPreset(BMC_NEXT, t_wrap, 1);
  }
  // * GROUP: PRESETS
  // go to the previous preset within the current bank
  // @t_wrap true to go to last preset after reaching the first one
  void presetPrevious(bool t_wrap){
    presets.scrollPreset(BMC_PREV, t_wrap, 1);
  }
  // * GROUP: PRESETS
  // go to the next bank
  // @t_wrap true to go to first bank after reaching the last one
  void presetBankNext(bool t_wrap){
    presets.scrollBank(BMC_NEXT, t_wrap, 1);
  }
  // * GROUP: PRESETS
  // go to the previous bank
  // @t_wrap true to go to last bank after reaching the first one
  void presetBankPrevious(bool t_wrap){
    presets.scrollBank(BMC_PREV, t_wrap, 1);
  }
  // * GROUP: PRESETS
  // returns the letter of the current bank
  bmcStoreName getPresetBankLetter(){
    return presets.getBankStr();
  }
  // * GROUP: PRESETS
  // returns the letter of the specified bank
  bmcStoreName getPresetBankLetter(uint8_t t_bank){
    return presets.getBankStr(t_bank);
  }
#endif

// ******************************
// *****      SETLISTS       ****
// ******************************
#if BMC_MAX_SETLISTS > 0

  // * GROUP: SETLISTS
  // get the current SetList number
  uint8_t getSetList(){
    return setLists.get();
  }
  // * GROUP: SETLISTS
  // returns the number of songs in the current setlist
  uint8_t getSetListLength(){
    return setLists.getSetListLength();
  }
  // * GROUP: SETLISTS
  // returns the number of songs in the specified setlist
  uint8_t getSetListLength(uint8_t n){
    return setLists.getSetListLength(n);
  }
  // * GROUP: SETLISTS
  // go to a specific SetList
  void setSetList(uint8_t n){
    setLists.set(n);
  }
  // * GROUP: SETLISTS
  // go to next song in the list
  // @t_wrap if true, after reaching the last setlist
  // the next setlist will be the first setlist
  // otherwise once the last setlist is reached BMC will
  // ignore this function
  void setListNext(bool t_wrap){
    setLists.scrollSet(BMC_NEXT, t_wrap, 1, 0, BMC_MAX_SETLISTS-1);
  }
  // * GROUP: SETLISTS
  // go to the previous setlist
  // @t_wrap if true, after reaching the first setlist
  // the previous setlist will be the last setlist
  // otherwise once the first setlist is reached BMC will
  // ignore this function
  void setListPrevious(bool t_wrap){
    setLists.scrollSet(BMC_PREV, t_wrap, 1, 0, BMC_MAX_SETLISTS-1);
  }
  // * GROUP: SETLISTS
  // returns the current song number in the setlist
  uint8_t getSetListSong(){
    return setLists.getSong();
  }
  // * GROUP: SETLISTS
  // go to a specific song number in the setlist
  void setSetListSong(uint8_t n){
    setLists.setSong(n);
  }
  // * GROUP: SETLISTS
  // go to next song in the list
  // @t_wrap if true, after reaching the last song
  // the next song will be the first song
  // otherwise once the last song is reached BMC will
  // ignore this function
  void setListSongNext(bool t_wrap){
    setLists.scrollSong(BMC_NEXT, t_wrap, 1, 0, BMC_MAX_SETLISTS_SONGS-1);
  }
  // * GROUP: SETLISTS
  // go to previous song in the list
  // @t_wrap if true, after reaching the first song
  // the previous song will be the last song
  // otherwise once the first song is reached BMC will
  // ignore this function
  void setListSongPrevious(bool t_wrap){
    setLists.scrollSong(BMC_PREV, t_wrap, 1, 0, BMC_MAX_SETLISTS_SONGS-1);
  }
  // * GROUP: SETLISTS
  // get the current song number in the setlist
  uint8_t getSetListSongPart(){
    return setLists.getPart();
  }
  // * GROUP: SETLISTS
  // go to a specific song number in the setlist
  void setSetListSongPart(uint8_t n){
    setLists.setPart(n);
  }
  // * GROUP: SETLISTS
  // go to next song in the list
  // @t_wrap if true, after reaching the last song
  // the next song will be the first song
  // otherwise once the last song is reached BMC will
  // ignore this function
  void setListSongPartNext(bool t_wrap){
    setLists.scrollPart(BMC_NEXT, t_wrap, 1, 0, BMC_MAX_SETLISTS_SONG_PARTS-1);
  }
  // * GROUP: SETLISTS
  // go to previous song in the list
  // @t_wrap if true, after reaching the first song
  // the previous song will be the last song
  // otherwise once the first song is reached BMC will
  // ignore this function
  void setListSongPartPrevious(bool t_wrap){
    setLists.scrollPart(BMC_PREV, t_wrap, 1, 0, BMC_MAX_SETLISTS_SONG_PARTS-1);
  }
  // * GROUP: SETLISTS
  // move a song within a setlist, you can move the song up or down
  // @t_song the index of the song in the setlist you want to move
  // @t_direction weather to move it up of down, use BMC_UP/BMC_DOWN
  // @t_save true writes the new setlist order to EEPROM
  // function returns true if the move was successful
  bool moveSetListSong(uint8_t t_song, bool t_direction, bool t_save){
    if(t_song >= BMC_MAX_SETLISTS_SONGS || globals.editorConnected()){
      return false;
    }
    uint8_t n = setLists.get();
    uint8_t len = setLists.getSetListLength();
    if(t_song >= len || len < 2){
      return false;
    }
    uint8_t swapSlot = 0;
    if(t_direction == BMC_NEXT){
      swapSlot = (t_song+1 >= len) ? 0 : t_song+1;
    } else {
      swapSlot = (t_song == 0) ? len-1 : t_song-1;
    }
    uint8_t a = store.global.setLists[n].events[t_song];
    uint8_t b = store.global.setLists[n].events[swapSlot];
    store.global.setLists[n].events[t_song] = b;
    store.global.setLists[n].events[swapSlot] = a;
    if(t_save){
      editor.saveSetList(n);
    }
    return true;
  }

#endif

#if BMC_MAX_MUX_IN > 0 || BMC_MAX_MUX_GPIO > 0
  // * GROUP: MUX
  // for those using a custom Digital In Multiplexer you would handle reading
  // it's pins then you pass the value of each of those Pins to BMC with this
  // API call, digital inputs must be Active LOW, that is if a button was pressed
  // the value should be LOW if it's not being pressed it's value should be HIGH
  // BMC will handle all debouncing, DO NOT DEBOUNCE IN YOUR CODE, pass the raw reading
  void setMuxDigitalValue(uint8_t pin, bool value){
    mux.setDigitalValue(pin, value);
  }
#endif

#if BMC_MAX_MUX_OUT > 0 || BMC_MAX_MUX_GPIO > 0
  // * GROUP: MUX
  // for those using a custom Digital Out Multiplexer BMC will hold the state
  // that that pin should be at, for example if the pins is being used to turn
  // leds on/off then BMC will tell you weather that pin should be on or off
  // you would then handle turning those LEDS on/off with your Mux.
  void getMuxDigitalOutValue(uint8_t pin){
    mux.getDigitalValue(pin);
  }
#endif

#if BMC_MAX_MUX_IN_ANALOG > 0
  // * GROUP: MUX
  // same setMuxDigitalValue as but you must pass it a value from 0 to 1024.
  // BMC will handle all debouncing, pass the raw reading of your analog input
  void setMuxAnalogValue(uint8_t n, uint16_t value){
    mux.setAnalogValue(n, value);
  }
#endif

#if BMC_MAX_BUTTONS > 0 || BMC_MAX_GLOBAL_BUTTONS > 0
  // * GROUP: HARDWARE
  // trigger the press of a button remotely
  // @n = index of button
  // @isGlobal = true if reading a global button, false for a layer button
  void triggerButtonPress(uint8_t n, bool isGlobal){
    #if BMC_MAX_BUTTONS > 0
      if(!isGlobal && n<BMC_MAX_BUTTONS){
        buttons[n].triggerPress();
        return;
      }
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS > 0
      if(isGlobal && n<BMC_MAX_GLOBAL_BUTTONS){
        globalButtons[n].triggerPress();
      }
    #endif
  }
  // * GROUP: HARDWARE
  // trigger the release of a button remotely
  // @n = index of button
  // @isGlobal = true if reading a global button, false for a layer button
  void triggerButtonRelease(uint8_t n, bool isGlobal){
    #if BMC_MAX_BUTTONS > 0
      if(!isGlobal && n<BMC_MAX_BUTTONS){
        buttons[n].triggerRelease();
        return;
      }
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS > 0
      if(isGlobal && n<BMC_MAX_GLOBAL_BUTTONS){
        globalButtons[n].triggerRelease();
      }
    #endif
  }
  // * GROUP: HARDWARE
  // returns the raw state of a button, this is a pre-debounce value
  // @n = index of button
  // @isGlobal = true if reading a global button, false for a layer button
  bool getButtonRawValue(uint8_t n, bool isGlobal){
    #if BMC_MAX_BUTTONS > 0
      if(!isGlobal && n<BMC_MAX_BUTTONS){
        return buttons[n].readState();
      }
    #endif

    #if BMC_MAX_GLOBAL_BUTTONS > 0
      if(isGlobal && n<BMC_MAX_GLOBAL_BUTTONS){
        return globalButtons[n].readState();
      }
    #endif

    return false;
  }
#endif

#if BMC_MAX_LEDS > 0 || BMC_MAX_GLOBAL_LEDS > 0
  // * GROUP: HARDWARE
  // return the state of the specified Led
  bool getLedState(uint16_t n, bool isGlobal){
    #if BMC_MAX_LEDS > 0
      if(!isGlobal && n<BMC_MAX_LEDS){
        return globals.ledStates.getBit(n);
      }
    #endif

    #if BMC_MAX_GLOBAL_LEDS > 0
      if(isGlobal && n<BMC_MAX_GLOBAL_LEDS){
        return globals.globalLedStates.getBit(n);
      }
    #endif

    return 0;
  }
#endif

#if BMC_MAX_PIXELS > 0 || BMC_MAX_GLOBAL_PIXELS > 0
  // * GROUP: HARDWARE
  // return the state of the specified pixel
  uint8_t getPixelState(uint8_t n, bool isGlobal){
    #if BMC_MAX_PIXELS > 0
      if(!isGlobal && n<BMC_MAX_PIXELS){
        return globals.pixelStates.getBit(n);
      }
    #endif

    #if BMC_MAX_GLOBAL_PIXELS > 0
      if(isGlobal && n<BMC_MAX_GLOBAL_PIXELS){
        return globals.globalPixelStates.getBit(n);
      }
    #endif
    
    return 0;
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0 || BMC_MAX_GLOBAL_RGB_PIXELS > 0
  // * GROUP: HARDWARE
  // return the state of the specified rgb pixel
  uint8_t getRgbPixelState(uint8_t n, uint8_t color, bool isGlobal){
    #if BMC_MAX_RGB_PIXELS > 0
      if(!isGlobal && n<BMC_MAX_RGB_PIXELS && color < 3){
        return globals.rgbPixelStates[color].getBit(n);
      }
    #endif

    #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
      if(isGlobal && n<BMC_MAX_GLOBAL_RGB_PIXELS && color < 3){
        return globals.globalRgbPixelStates[color].getBit(n);
      }
    #endif
    
    return 0;
  }
#endif

#if BMC_MAX_POTS > 0 || BMC_MAX_GLOBAL_POTS > 0
  // * GROUP: HARDWARE
  // return the value of the specified pot
  uint8_t getPotValue(uint8_t n, bool isGlobal){
    #if BMC_MAX_POTS > 0
      if(!isGlobal && n<BMC_MAX_POTS){
        return pots[n].getValue();
      }
    #endif

    #if BMC_MAX_GLOBAL_POTS > 0
      if(isGlobal && n<BMC_MAX_GLOBAL_POTS){
        return globalPots[n].getValue();
      }
    #endif
    
    return 0;
  }
#endif

#if BMC_MAX_NL_RELAYS > 0 || BMC_MAX_L_RELAYS > 0
  // * GROUP: HARDWARE
  // return the state of the specified relay
  bool getRelayState(uint8_t n, uint8_t isLatching){
    #if BMC_MAX_NL_RELAYS > 0
      if(!isLatching && n<BMC_MAX_NL_RELAYS){
        return relaysNL[n].getState();
      }
    #endif

    #if BMC_MAX_L_RELAYS > 0
      if(isLatching && n<BMC_MAX_L_RELAYS){
        return relaysL[n].getState();
      }
    #endif
    
    return 0;
  }
#endif

#if BMC_MAX_SKETCH_BYTES > 0
  // * GROUP: SYSTEM
  // get the value of a sketch byte
  uint8_t getSketchByte(uint8_t n){
    if(n < BMC_MAX_SKETCH_BYTES){
      return store.global.sketchBytes[0].events[n];
    }
    return 0;
  }
  // * GROUP: SYSTEM
  // scroll thru sketch bytes, you must pass the initial value "n"
  // this function will then return the next value up or down
  // this function is to scroll the index of a sketch byte, useful for editors
  uint8_t scrollSketchByte(uint8_t n, uint8_t t_direction, uint8_t t_amount){
    if(n>=BMC_MAX_SKETCH_BYTES){
      return 0;
    }
    t_amount = (t_amount==0) ? 1 : t_amount;
    return BMCCycle<uint8_t>(0, BMC_MAX_SKETCH_BYTES - 1)
    .withAmount(t_amount)
    .withDirection(t_direction)
    .withWrap(BMC_WRAP)
    .withValue(n)
    .withRange(0, BMC_MAX_SKETCH_BYTES - 1)
    .process();
  }
  // * GROUP: SYSTEM
  // scroll the value of a sketch byte up or down based on the sketch byte's data
  // n is the index of the sketch byte, that sketch byte value is then loaded and scrolled
  uint8_t scrollSketchByteValue(uint8_t n, uint8_t t_direction, uint8_t t_amount){
    return scrollSketchByteValue(n, getSketchByte(n), t_direction, t_amount);
  }
  // * GROUP: SYSTEM
  // same as above but you can use it to pass it a value that you store on your sketch
  uint8_t scrollSketchByteValue(uint8_t n, uint8_t t_value, uint8_t t_direction, uint8_t t_amount){
    if(n>=BMC_MAX_SKETCH_BYTES){
      return 0;
    }
    t_amount = (t_amount==0) ? 1 : t_amount;
    BMCSketchByteData data = BMCBuildData::getSketchByteData(n);
    
    return BMCCycle<uint8_t>(data.min, data.max)
    .withAmount(t_amount * data.step)
    .withDirection(t_direction)
    .withWrap(BMC_WRAP)
    .withValue(t_value)
    .withRange(data.min, data.max)
    .process();
  }
  // * GROUP: SYSTEM
  // format the value of a sketch byte based on it's config format data
  // if value is not passed then the sketch byte's value is loaded from EEPROM
  void formatSketchByteValue(uint8_t n, char * t_string){
    formatSketchByteValue(n, getSketchByte(n), t_string);
  }
  // * GROUP: SYSTEM
  // get the formatted value of a sketch byte
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

#ifdef BMC_USE_FAS
  // * GROUP: SYNC/FAS
  // return the state of a FAS connection
  bool fasConnected(){
    return sync.fas.connected();
  }
  // * GROUP: SYNC/FAS
  // trigger a FAS Connection
  void fasConnect(){
    sync.fas.connect();
  }
  // * GROUP: SYNC/FAS
  // trigger a FAS Disconnect
  void fasDisconnect(){
    sync.fas.disconnect();
  }
  // * GROUP: SYNC/FAS
  // toggle FAS Connection
  void fasToggleConnection(){
    if(sync.fas.connected()){
      sync.fas.disconnect();
    } else {
      sync.fas.connect();
    }
  }
  // * GROUP: SYNC/FAS
  // copy the current Preset Name into a buffer char array
  // the length of the char array must be at least 32 bytes
  bool getFasPresetName(char* str){
    sync.fas.getPresetName(str);
    return sync.fas.connected();
  }
  // * GROUP: SYNC/FAS
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
  // * GROUP: SYNC/FAS
  // get the synced scene number
  uint8_t getFasSceneNumber(){
    return sync.fas.getSceneNumber();
  }
  // * GROUP: SYNC/FAS
  // copy the current Scene Name into a buffer char array
  // the length of the char array must be at least 32 bytes
  // only available for FAS3
  bool getFasSceneName(char* str){
    sync.fas.getSceneName(str);
    return sync.fas.connected();
  }
  // * GROUP: SYNC/FAS
  // copy the specified Scene Name into a buffer char array
  // the length of the char array must be at least 32 bytes
  // only available for FAS3
  bool getFasSceneName(uint8_t n, char* str){
    sync.fas.getSceneName(n, str);
    return sync.fas.connected();
  }
  // * GROUP: SYNC/FAS
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

  // * GROUP: SYNC/FAS
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
  // * GROUP: SYNC/FAS
  // change to a new FAS preset number, value is the actual preset number
  void setFasPresetNumber(uint16_t value){
    sync.fas.setPreset(value);
  }
  // * GROUP: SYNC/FAS
  // change to a new FAS scene number, value must be 0 to 7
  void setFasSceneNumber(uint8_t value, bool revert=false){
    sync.fas.setSceneNumber(value, revert);
  }
  // * GROUP: SYNC/FAS
  // scroll thru FAS Scenes
  void setFasSceneScroll(bool t_up=true, bool t_wrap=true, bool t_revert=false, uint8_t t_min=0, uint8_t t_max=7){
    sync.fas.sceneScroll(t_up, t_wrap, t_revert, t_min, t_max);
  }
  // * GROUP: SYNC/FAS
  // check if a FAS block is bypassed
  bool getFasBlockBypassed(uint8_t n){
    return sync.fas.isBlockBypassed(n);
  }
  // * GROUP: SYNC/FAS
  // check if a FAS block is engaged
  bool getFasBlockEngaged(uint8_t n){
    return sync.fas.isBlockEngaged(n);
  }
  // * GROUP: SYNC/FAS
  // check if a FAS block is in X State
  // if using FAS 3 sync return true if channel is A
  // this is only here for compatibility,
  // when you use FAS 3 sync use the getFasBlockChannel call instead
  bool getFasIsBlockX(uint8_t n){
    #if !defined(BMC_USE_FAS3)
      return sync.fas.isBlockX(n);
    #else
      return sync.fas.getBlockChannel(n) == 0;
    #endif
  }
  // * GROUP: SYNC/FAS
  // check if a FAS block is in Y State
  // if using FAS 3 sync return true if channel is B
  // this is only here for compatibility,
  // when you use FAS 3 sync use the getFasBlockChannel call instead
  bool getFasIsBlockY(uint8_t n){
    #if !defined(BMC_USE_FAS3)
      return sync.fas.isBlockY(n);
    #else
      return sync.fas.getBlockChannel(n) == 1;
    #endif
  }
  // * GROUP: SYNC/FAS
  // get the channel of a specified block
  // returns 0 for channel A, 1 for channel B, etc.
  uint8_t getFasBlockChannel(uint8_t n){
    #if defined(BMC_USE_FAS3)
      return sync.fas.getBlockChannel(n);
    #else
      return 0;
    #endif
  }
  
  // * GROUP: SYNC/FAS
  // get FAS Tuner Data, the BMCTunerData struct
  // contains the following attributes
  // uint8_t stringNumber = 0;
  // uint8_t note = 0;
  // uint8_t pitchRaw = 0;
  // int pitch = 0;
  // char noteName[3] = "";
  void getFasTuner(BMCTunerData& buff){
    sync.fas.getTunerData(buff);
  }
  // * GROUP: SYNC/FAS
  // get FAS Tuner Data
  bool fasIsBlockBypassed(uint8_t blockId){
    return sync.fas.isBlockBypassed(blockId);
  }
  // * GROUP: SYNC/FAS
  bool fasIsBlockEngaged(uint8_t blockId){
    return sync.fas.isBlockEngaged(blockId);
  }
  // * GROUP: SYNC/FAS
  bool fasIsBlockX(uint8_t blockId){
    return sync.fas.isBlockX(blockId);
  }
  // * GROUP: SYNC/FAS
  bool fasIsBlockY(uint8_t blockId){
    return sync.fas.isBlockY(blockId);
  }
  // * GROUP: SYNC/FAS
  void fasToggleTuner(){
    sync.fas.toggleTuner();
  }
  // * GROUP: SYNC/FAS
  void fasTapTempo(){
    sync.fas.tapTempo();
  }
#if !defined(BMC_USE_FAS3)
  // * GROUP: SYNC/FAS
  void fasSendSetBlockParameter(uint8_t blockId, uint8_t parameterId, uint16_t value){
    sync.fas.sendSetBlockParameter(blockId, parameterId, value);
  }
  // * GROUP: SYNC/FAS
  void fasSendGetBlockParameter(uint8_t blockId, uint8_t parameterId){
    sync.fas.sendGetBlockParameter(blockId, parameterId);
  }
  // * GROUP: SYNC/FAS
  void fasSyncParameter(uint8_t slot, uint8_t block, uint8_t parameter){
    sync.fas.setSyncedParameter(slot, block, parameter);
  }
  // * GROUP: SYNC/FAS
  uint16_t fasGetSyncedParameter(uint8_t block, uint8_t parameter){
    return sync.fas.getSyncedParameterValue(block, parameter);
  }
  // * GROUP: SYNC/FAS
  uint16_t fasGetSyncedParameter(uint8_t slot){
    return sync.fas.getSyncedParameterValue(slot);
  }
  // * GROUP: SYNC/FAS
  void fasChangeSyncedParameter(uint8_t slot, uint16_t value){
    sync.fas.sendChangeSyncedParameter(slot, value);
  }
#endif
#endif

#ifdef BMC_USE_BEATBUDDY
  // * GROUP: SYNC/BEATBUDDY
  bool beatBuddySynced(){
    return sync.beatBuddy.inSync();
  }
  // * GROUP: SYNC/BEATBUDDY
  bool beatBuddyPlaying(){
    return sync.beatBuddy.isPlaying();
  }
  // * GROUP: SYNC/BEATBUDDY
  bool getBeatBuddyCurrentPart(){
    return sync.beatBuddy.getSongPart();
  }
  // * GROUP: SYNC/BEATBUDDY
  void sendBeatBuddyCommand(uint8_t value, uint8_t data=127){
    sync.beatBuddy.sendCommand(value, data);
  }
#endif
  // * GROUP: MIDI
  // for master or slave clock
  // get the current BPM
  uint16_t getMidiClockBpm(){
    return midiClock.getBpm();
  }
  // * GROUP: MIDI
  // only works when on master clock
  // set the Clock's BPM
  void setMidiClockBpm(uint16_t t_bpm){
    midiClock.setBpm(t_bpm);
  }
  // * GROUP: MIDI
  // only works when on master clock
  // simulates a Tap Tempo
  // the Clock BPM is determined based on how often the function is called
  // for example if there's a gap of 500ms between calling this function
  // the BPM would be set to 120 BPM, (60000/500) = 120
  void midiClockTap(){
    midiClock.tap();
  }
  // * GROUP: SYSTEM
  bool editorConnected(){
    return globals.editorConnected();
  }
  // * GROUP: SYSTEM
  bool bleConnected(){
    return globals.bleConnected();
  }
  // * GROUP: SYSTEM
  bool hostConnected(){
    return globals.hostConnected();
  }
  // * GROUP: SYSTEM
  // STOP WATCH
  uint8_t getStopwatchState(){
    return stopwatch.getState();
  }
  // * GROUP: SYSTEM
  uint8_t getStopwatchHours(){
    return stopwatch.hours;
  }
  // * GROUP: SYSTEM
  uint8_t getStopwatchMinutes(){
    return stopwatch.minutes;
  }
  // * GROUP: SYSTEM
  uint8_t getStopwatchSeconds(){
    return stopwatch.seconds;
  }
  // * GROUP: SYSTEM
  uint32_t getStopwatchTimeout(){
    return stopwatch.timeout;
  }
  // * GROUP: SYSTEM
  // RUN TIME
  uint32_t getRuntime(){
    return runTime.getSeconds();
  }
  //TIME
#ifdef BMC_USE_TIME
  // * GROUP: SYSTEM
  uint8_t getHour(){
    return editor.getHour();
  }
  // * GROUP: SYSTEM
  uint8_t getMinute(){
    return editor.getMinute();
  }
  // * GROUP: SYSTEM
  uint8_t getSecond(){
    return editor.getSecond();
  }
  // * GROUP: SYSTEM
  uint8_t getDay(){
    return editor.getDay();
  }
  // * GROUP: SYSTEM
  uint8_t getMonth(){
    return editor.getMonth();
  }
  // * GROUP: SYSTEM
  uint16_t getYear(){
    return editor.getYear();
  }
#endif

  // ***************************
  // ******** MESSENGER ********
  // ***************************
  // * GROUP: SYSTEM
  // with the Messenger you can send a signed long value and a char array
  // the string can only be up to 32 characters
  // send a value and a string as a char array
  void messengerSend(uint16_t status, signed long value, char* str, uint8_t len){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, value, str, len);
  }
  // * GROUP: SYSTEM
  // send a value and a string as a const string
  void messengerSend(uint16_t status, signed long value, const char* str){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, value, str);
  }
  // * GROUP: SYSTEM
  // send just a value without string
  void messengerSend(uint16_t status, signed long value){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, value, "");
  }
  // * GROUP: SYSTEM
  // send just a char array string
  void messengerSend(uint16_t status, char* str, uint8_t len){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, 0, str, len);
  }
  // * GROUP: SYSTEM
  // send just a const string
  void messengerSend(uint16_t status, const char* str){
    if(!globals.editorConnected()){
      return;
    }
    editor.messengerSend(status, 0, str);
  }

#ifdef BMC_MIDI_BLE_ENABLED
  // * GROUP: SYSTEM
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
  // @t_micros specifies which one you want to use
  // * GROUP: DEBUG
  void startTiming(uint8_t n, bool t_micros=false){
#ifdef BMC_DEBUG
    debugStartTiming(n, t_micros);
#endif
  }
  // * GROUP: DEBUG
  // stop the active timer specified by n (inclusive)
  // @n = the index of the timer you want to use
  // @t_micros = true if you want to time the number of microseconds, false for millis
  // for every timer you compile there's a millis timer and a micros timer
  // t_micros specifies which one you want to use
  // when you stop an active timer BMC will print it's output to the Serial monitor
  unsigned long stopTiming(uint8_t n, bool t_micros=false){
#ifdef BMC_DEBUG
    return debugStopTiming(n, t_micros);
#endif
    return 0;
  }

  // ***************************
  // ******* MIDI SEND *********
  // ***************************
  // * GROUP: MIDI
  void sendRealTime(uint8_t port, uint8_t type, uint8_t cable=0){
    midi.sendRealTime(port, type, cable);
  }
  // * GROUP: MIDI
  void sendSysEx(uint8_t port, uint8_t *data, uint16_t size, bool hasTerm=false, uint8_t cable=0){
    midi.sendSysEx(port, data, size, hasTerm, cable);
  }
  // * GROUP: MIDI
  void sendProgramChange(uint8_t port, uint8_t channel, uint8_t program, uint8_t cable=0){
    midi.sendProgramChange(port, channel, program, cable);
  }
  // * GROUP: MIDI
  void sendControlChange(uint8_t port, uint8_t channel, uint8_t control, uint8_t value, uint8_t cable=0){
    midi.sendControlChange(port, channel, control, value, cable);
  }
  // * GROUP: MIDI
  void sendNoteOn(uint8_t port, uint8_t channel, uint8_t note, uint8_t velocity, uint8_t cable=0){
    midi.sendNoteOn(port, channel, note, velocity, cable);
  }
  // * GROUP: MIDI
  void sendNoteOff(uint8_t port, uint8_t channel, uint8_t note, uint8_t velocity, uint8_t cable=0){
    midi.sendNoteOff(port, channel, note, velocity, cable);
  }
  // * GROUP: MIDI
  void sendPitchBend(uint8_t port, uint8_t channel, int16_t value, uint8_t cable=0){
    midi.sendPitchBend(port, channel, value, cable);
  }
  // * GROUP: MIDI
  void sendAfterTouch(uint8_t port, uint8_t channel, uint8_t pressure, uint8_t cable=0){
    midi.sendAfterTouch(port, channel, pressure, cable);
  }
  // * GROUP: MIDI
  void sendAfterTouchPoly(uint8_t port, uint8_t channel, uint8_t note, uint8_t pressure, uint8_t cable=0){
    midi.sendAfterTouchPoly(port, channel, note, pressure, cable);
  }
  // * GROUP: MIDI
  void sendTimeCodeQuarterFrame(uint8_t port, uint8_t type, uint8_t value, uint8_t cable=0){
    midi.sendTimeCodeQuarterFrame(port, type, value, cable);
  }
  // * GROUP: MIDI
  void sendSongPosition(uint8_t port, uint16_t beats, uint8_t cable=0){
    midi.sendSongPosition(port, beats, cable);
  }
  // * GROUP: MIDI
  void sendSongSelect(uint8_t port, uint8_t song, uint8_t cable=0){
    midi.sendSongSelect(port, song, cable);
  }
  // * GROUP: MIDI
  void sendTuneRequest(uint8_t port, uint8_t cable=0){
    midi.sendTuneRequest(port, cable);
  }
  // * GROUP: MIDI
  void beginRpn(uint8_t port, uint8_t channel, uint16_t number, uint8_t cable=0){
    midi.beginRpn(port, channel, number, cable);
  }
  // * GROUP: MIDI
  void sendRpnValue(uint8_t port, uint8_t channel, uint16_t value, uint8_t cable=0){
    midi.sendRpnValue(port, channel, value, cable);
  }
  // * GROUP: MIDI
  void sendRpnIncrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendRpnIncrement(port, channel, amount, cable);
  }
  // * GROUP: MIDI
  void sendRpnDecrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendRpnDecrement(port, channel, amount, cable);
  }
  // * GROUP: MIDI
  void endRpn(uint8_t port, uint8_t channel, uint8_t cable=0){
    midi.endRpn(port, channel, cable);
  }
  // * GROUP: MIDI
  void beginNrpn(uint8_t port, uint8_t channel, uint16_t number, uint8_t cable=0){
    midi.beginNrpn(port, channel, number, cable);
  }
  // * GROUP: MIDI
  void sendNrpnValue(uint8_t port, uint8_t channel, uint16_t value, uint8_t cable=0){
    midi.sendNrpnValue(port, channel, value, cable);
  }
  // * GROUP: MIDI
  void sendNrpnIncrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendNrpnIncrement(port, channel, amount, cable);
  }
  // * GROUP: MIDI
  void sendNrpnDecrement(uint8_t port, uint8_t channel, uint8_t amount, uint8_t cable=0){
    midi.sendNrpnDecrement(port, channel, amount, cable);
  }
  // * GROUP: MIDI
  void endNrpn(uint8_t port, uint8_t channel, uint8_t cable=0){
    midi.endNrpn(port, channel, cable);
  }

  // ********************************************************************
  // METHODS TO UPDATE THE STORE BUT ONLY IF NOT CONNECTED TO THE EDITOR
  // ********************************************************************

  // ***************************
  // ******* SETTINGS *********
  // ***************************
  // * GROUP: SYSTEM
  // Save any changes to settings and re-assign all data, writes to EEPROM
  // also calls the onStoreUpdate callback
  void settingsSave(){
    if(!globals.editorConnected()){
      editor.saveSettings();
      assignStoreData();
    }
  }
  // * GROUP: SYSTEM
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
  // * GROUP: SYSTEM
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
  // * GROUP: SYSTEM
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
