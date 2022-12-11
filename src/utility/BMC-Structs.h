/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#ifndef BMC_STRUCT_H
#define BMC_STRUCT_H
#include <Arduino.h>

struct __attribute__ ((packed)) BMCDeviceData {
  uint8_t id = 0;
  char idtxt[40] = "";
  char label[19] = "";
  int16_t group = 0;
  uint16_t length = 0;
  bool global = 0;
  uint8_t settings = 0;
  uint8_t events = 0;
};

// pin, pinB, x, y, style, rotation, mergeType, mergeIndex, address,
struct BMCUIData {
  int16_t pins[3] = {-1, -1, -1};
  uint16_t x = 0;
  uint16_t y = 0;
  uint8_t style = 0;
  uint8_t rotation = 0;
  uint8_t mergeType = 0;
  uint16_t mergeIndex = 0;
  uint16_t other1 = 0;
  uint16_t other2 = 0;
};

struct BMCEventScrollData {
  bool enabled = false;
  bool direction = false;
  bool endless = true;
  uint8_t amount = 1;
  BMCEventScrollData(uint8_t settings, uint8_t ticks){
    enabled = bitRead(settings, 0);
    direction = bitRead(settings, 1);
    endless = bitRead(settings, 2);
    if(ticks > 0){
      direction = bitRead(ticks, 7);
    }
    if(!enabled){
      endless = true;
    }
    amount = ticks & 0x7F;
    if(amount==0){
      amount = 1;
    }
  }
};
template <uint16_t len>
struct BMCBitStates {
  uint16_t value[((len >> 4) & 0x0F)+1];
  bool updated = false;
  BMCBitStates(){
    memset(value, 0 , ((len >> 4) & 0x0F)+1);
  }
  uint8_t getLength(){
    return ((len >> 4) & 0x0F)+1;
  }
  uint16_t get(uint8_t n){
    return value[n];
  }
  void clear(){
    for(uint8_t i = 0, n = getLength() ; i < n ; i++){
      value[i] = ~value[i];
    }
  }
  void zeroOut(){
    for(uint8_t i = 0, n = getLength() ; i < n ; i++){
      value[i] = 0;
    }
  }
  bool hasChanged(){
    if(updated){
      updated = false;
      return true;
    }
    return false;
  }
  void setBit(uint16_t n, bool newValue){
    uint8_t mask = (n >> 4) & 0x0F;
    uint8_t bit = n & 0x0F;
    if(bitRead(value[mask], bit) != newValue){
      bitWrite(value[mask], bit, newValue);
      updated = true;
    }
  }
  bool getBit(uint16_t n){
    uint8_t mask = (n >> 4) & 0x0F;
    uint8_t bit = n & 0x0F;
    return bitRead(value[mask], bit);
  }
};

struct BMCRunTime {
  uint32_t seconds = 0;
  void tick(){
    seconds++;
  }
  uint32_t getWeeks(){
    return seconds / 604800;
  }
  uint32_t getDays(){
    return seconds / 86400;
  }
  uint32_t getHours(){
    return seconds / 3600;
  }
  uint32_t getMinutes(){
    return seconds / 60;
  }
  uint32_t getSeconds(){
    return seconds;
  }
};
struct BMCTunerData {
  uint8_t stringNumber = 0;
  uint8_t note = 0;
  int pitch = 0;
  char noteName[3] = "";

  void reset(){
    stringNumber = 0;
    pitch = 0;
    note = 0;
    strcpy(noteName, "");
  }
};
struct BMCStopwatch {
  bool running = false;
  uint32_t timeout = 0;
  uint32_t current = 0;
  uint8_t hours = 0;
  uint8_t minutes = 0;
  uint8_t seconds = 0;
  void tick(){
    if(running && !reached()){
      current++;
      seconds++;
      if(seconds>=60){
        seconds = 0;
        minutes++;
        if(minutes>=60){
          minutes = 0;
          hours++;
          if(hours>=24){
            hours = 0;
            current = 0;
          }
        }
      }
    }
  }
  uint8_t getState(){
    if(active()){
      return reached() ? 2 : 1;
    }
    return 0;
  }
  bool isState(uint8_t n){
    return getState()==n;
  }
  bool reached(){
    return (timeout>0 && (current >= timeout));
  }
  bool active(){
    return running;
  }
  void set(uint8_t h, uint8_t m, uint8_t s){
    if(timeout>0){
      //return;
    }
    timeout = (h * 3600) + (m * 60) + s;
    if(timeout>86400){
      timeout = 0;
    }
    BMC_PRINTLN("Stopwatch h,m,s,timeout",h,m,s,timeout);
  }
  void start(){
    running = true;
  }
  void stop(){
    running = false;
  }
  void restart(){
    reset();
    running = true;
  }
  void toggle(){
    running = !running;
  }
  void toggleReset(){
    if(getState() > 0){
      reset();
    } else {
      running = true;
    }

  }
  void reset(){
    running = false;
    current = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
  }
};
struct BMCFracTunerData {
  bool valid = false;
  char noteStr[2];
  uint8_t note = 0;
  uint8_t stringNum = 0;
  int pitch = 0;
};
struct BMCMidiDataChannel {
  uint8_t program = 0;
  int8_t pitch = 0;
  uint8_t control[128];
};
struct BMCMidiData {
  BMCMidiDataChannel channel[BMC_MAX_MIDI_CHANNEL_TRACKING];
  void set(uint32_t t_event){
    if((t_event & 0xF0) == BMC_MIDI_PROGRAM_CHANGE){
      setProgram(t_event);
    } else if((t_event & 0xF0) == BMC_MIDI_CONTROL_CHANGE){
      setControl(t_event);
    }
  }
  // PROGRAM
  void setProgram(uint32_t t_event){
    uint8_t ch = BMC_GET_BYTE(0, t_event) & 0x0F;
    if(ch<BMC_MAX_MIDI_CHANNEL_TRACKING){
      uint8_t pc = BMC_GET_BYTE(1, t_event) & 0x7F;
      channel[ch].program = pc;
    }
  }
  void setProgram(uint8_t t_channel, uint8_t t_program){
    uint8_t ch = ((t_channel-1) & 0x0F);
    if(ch<BMC_MAX_MIDI_CHANNEL_TRACKING){
      channel[ch].program = (t_program & 0x7F);
    }
  }
  uint8_t getProgram(uint8_t t_channel){
    uint8_t ch = ((t_channel-1) & 0x0F);
    return (ch<BMC_MAX_MIDI_CHANNEL_TRACKING)?channel[ch].program:0;
  }
  // CONTROL
  void setControl(uint32_t t_event){
    uint8_t ch = BMC_GET_BYTE(0, t_event) & 0x0F;
    if(ch<BMC_MAX_MIDI_CHANNEL_TRACKING){
      uint8_t cc = BMC_GET_BYTE(1, t_event) & 0x7F;
      uint8_t value = BMC_GET_BYTE(2, t_event) & 0x7F;
      channel[ch].control[cc] = value;
    }
  }
  void setControl(uint8_t t_channel, uint8_t t_control, uint8_t t_value){
    uint8_t ch = ((t_channel-1) & 0x0F);
    if(ch<BMC_MAX_MIDI_CHANNEL_TRACKING){
      uint8_t cc = (t_control & 0x7F);
      channel[ch].control[cc] = (t_value & 0x7F);
    }
  }
  uint8_t getControl(uint8_t t_channel, uint8_t t_control){
    uint8_t ch = ((t_channel-1) & 0x0F);
    uint8_t cc = (t_control & 0x7F);
    return (ch<BMC_MAX_MIDI_CHANNEL_TRACKING) ? channel[ch].control[cc] : 0;
  }
  void setPitch(uint8_t t_channel, uint8_t t_value){
    uint8_t ch = ((t_channel-1) & 0x0F);
    if(ch<BMC_MAX_MIDI_CHANNEL_TRACKING){
      channel[ch].pitch = (t_value & 0x7F);
    }
  }
  uint8_t getPitch(uint8_t t_channel){
    uint8_t ch = ((t_channel-1) & 0x0F);
    return (ch<BMC_MAX_MIDI_CHANNEL_TRACKING) ? channel[ch].pitch : 0;
  }
};
struct BMCMidiEvent {
  uint32_t event = 0;
  void setEvent(uint32_t e){
    event = e;
  }
  void setEvent(uint8_t port=0, uint8_t status=0, uint8_t channel=0, uint8_t data1=0, uint8_t data2=0){
    // don't mask data2 to 7 bits since we can allow for 128 as a value to toggle
    if(status>127 && status<0xF0){
      status = ((status & 0xF0) | (channel & 0x0F));
    }
    event = BMC_MERGE_BYTES(port, data2, data1 & 0x7F, status);
  }
  uint32_t getEvent(){
    return event;
  }
  bool hasEvent(){
    return (BMC_GET_BYTE(0,event) > 0);
  }
  uint8_t getStatus(){
    uint8_t status = BMC_GET_BYTE(0,event);
    return (status > 127 && status < 0xF0) ? (status & 0xF0) : status;
  }
  uint8_t getChannel(){
    return BMC_GET_BYTE(0,event) & 0x0F;
  }
  uint8_t getData1(){
    return BMC_GET_BYTE(1,event) & 0x7F;
  }
  uint8_t getData2(){
    // don't mask it to 7 bits since we can allow for 128 as a value to toggle
    return BMC_GET_BYTE(2,event);
  }
  uint8_t getPort(){
    return BMC_GET_BYTE(3,event);
  }
  void reset(){
    event = 0;
  }
};
struct BMCMidiPort {
  uint8_t ports;

  uint8_t get(){
    return ports;
  }
  void set(uint8_t value){
    ports = value;
  }
  bool portBitActive(uint8_t port){
    return bitRead(ports,port);
  }
  void setUsb(bool value=true){
    bitWrite(ports,BMC_MIDI_PORT_USB_BIT,value);
  }
  void setSerialA(bool value=true){
#ifdef BMC_MIDI_SERIAL_A_ENABLED
      bitWrite(ports,BMC_MIDI_PORT_SERIAL_A_BIT,value);
#endif
  }
  void setSerialB(bool value=true){
#ifdef BMC_MIDI_SERIAL_B_ENABLED
      bitWrite(ports,BMC_MIDI_PORT_SERIAL_B_BIT,value);
#endif
  }
  void setSerialC(bool value=true){
#ifdef BMC_MIDI_SERIAL_C_ENABLED
      bitWrite(ports,BMC_MIDI_PORT_SERIAL_C_BIT,value);
#endif
  }
  void setSerialD(bool value=true){
#ifdef BMC_MIDI_SERIAL_D_ENABLED
      bitWrite(ports,BMC_MIDI_PORT_SERIAL_D_BIT,value);
#endif
  }
  void setHost(bool value=true){
    #ifdef BMC_USB_HOST_ENABLED
      bitWrite(ports,BMC_MIDI_PORT_HOST_BIT,value);
    #endif
  }
  void setBle(bool value=true){
    #ifdef BMC_MIDI_BLE_ENABLED
      bitWrite(ports,BMC_MIDI_PORT_BLE_BIT,value);
    #endif
  }
  void setSerialAll(bool value=true){
    setSerialA(value);
    setSerialB(value);
    setSerialC(value);
    setSerialD(value);
  }
  void reset(){
    ports = 0;
  }
};
struct BMCEditorMidiFlags {
  // Editor SysEx Message flags, just an easier way to manage them
  // bit0 -> query type         =>  0=read, 1=write
  // bit1 -> query target       =>  0=global, 1=page
  // bit2 -> Save to all pages  =>  if on, save the payload to all pages
  // bit3 -> Available          =>
  // bit4 -> Available          =>
  // bit5 -> Backup             =>  if on, message is intended as a backup restore
  // bit6 -> Error              =>  if on, message is an error notification

  uint8_t flags = 0;
  uint8_t get(){
    return flags;
  }
  void set(uint8_t value=0){
    flags = value & 0x7F;
  }
  void setWrite(bool value=true)    {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_WRITE,value);}
  bool isWrite()                    {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_WRITE);}

  void setPage(bool value=true)     {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_PAGE,value);}
  bool isPage()                     {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_PAGE);}

  void setAllPages(bool value=true) {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_ALL_PAGES,value);}
  bool isAllPages()                 {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_ALL_PAGES);}

  void setBackup(bool value=true)   {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_BACKUP,value);}
  bool isBackup()                   {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_BACKUP);}

  void setError(bool value=true)    {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_ERROR,value);}
  bool isError()                    {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_ERROR);}

  void reset(){
    flags = 0;
  }
};

struct BMCSketchByteData {
  char name[BMC_NAME_LEN_SKETCH_BYTES] = "";
  uint8_t initialValue = 0;
  uint8_t min = 0;
  uint8_t max = 255;
  uint8_t step = 1;
  uint8_t formatType = BMC_NONE;
  uint8_t formatValue = BMC_NONE;
  uint8_t formatAppend = BMC_NONE;
  BMCSketchByteData(){}
  BMCSketchByteData(const char* t_name, uint8_t t_initialValue, uint8_t t_min,
                    uint8_t t_max, uint8_t t_step,
                    uint8_t t_formatType, uint8_t t_formatValue,
                    uint8_t t_formatAppend)
  {

    strcpy(name, t_name);
    initialValue = constrain(t_initialValue, t_min, t_max);
    min = t_min;
    max = t_max;
    step = t_step;

    formatType = t_formatType;
    formatValue = t_formatValue;
    formatAppend = t_formatAppend;
  }
  uint8_t getInitialValue(){
    return constrain(initialValue, min, max);
  }
};
struct BMCRelayMidiTrigger {
  uint8_t type = 255;
  uint8_t data1 = 255;
  bool match(uint8_t t_type, uint8_t t_channel, uint8_t t_data1){
    uint8_t t = (t_type & 0xF0) | (t_channel & 0x0F);
    return (type!=255 && data1!=255) && (t==type && t_data1==data1);
  }
  uint8_t match2(uint8_t t_type, uint8_t t_channel, uint8_t t_data1){
    uint8_t t = (t_type & 0xF0) | (t_channel & 0x0F);
    if((type==255 && data1==255) || (t!=type)){
      return 0;
    }
    if(type==BMC_MIDI_PROGRAM_CHANGE){
      return (t_data1==data1)?1:2;
    } else if(type==BMC_MIDI_CONTROL_CHANGE){
      return (t_data1==data1)?1:0;
    }
    return 0;
    //return (type!=255 && data1!=255) && (t==type && t_data1==data1);
  }
};
struct BMCValueStream {
  uint8_t source = 0;
  uint8_t id = 0;
  int value = 0;
  uint32_t data = 0;
  char name[30];
};
struct BMCMessenger {
  uint16_t status = 0;
  signed long value = 0;
  uint8_t strLen = 0;
  char string[33];
  void reset(){
    memset(string, 0, strLen);
    status = 0;
    value = 0;
    strLen = 0;
  }
};

struct BMCRoutingItem {
  uint8_t destinations = 0;
  uint8_t filters = 0;
  uint8_t channel = 0;
  void setData(uint16_t t_data){
    destinations = t_data & 0x7F;
    filters = (t_data>>7) & 0x0F;
    channel = (t_data>>11) & 0x1F;
  }
  bool hasDestination(){
    return destinations!=BMC_NONE;
  }
};
struct BMCRoutingData {
  BMCRoutingItem usb;
  BMCRoutingItem serialA;
  BMCRoutingItem serialB;
  BMCRoutingItem serialC;
  BMCRoutingItem serialD;
  BMCRoutingItem host;
  BMCRoutingItem ble;
};
struct BMCMidiTimeSignature {
  //Numerator of time signature
  uint8_t numerator = 0;
  //Denominator of time signature (negative power of 2)
  uint8_t denominator = 0;
  //Number of MIDI clocks in a metronome click
  uint8_t metClocks = 0;
  //Number of notated 32nd notes in a MIDI quarter note
  uint8_t notated32 = 0;
  // kept track of the current beat
  uint8_t beat = 0;

  void setFromMidi(uint8_t n, uint8_t d, uint8_t c, uint8_t n32){
    numerator = n;
    denominator = (uint8_t) pow((int)(-d),2);
    metClocks = c;
    notated32 = n32;
  }
  void reset(){
    numerator = 0;
    denominator = 0;
    metClocks = 0;
    notated32 = 0;
    beat = 0;
  }
  uint8_t getBeat(){
    return beat;
  }
  void setBeat(uint8_t t_beat){
    beat = t_beat;
  }
  bool available(){
    return numerator>0&&denominator>0;
  }
  uint8_t getBeatLocation(){
    float x = ((float)100/(float)numerator) * (float)beat;
    beat++;
    if(beat>numerator){
      beat = 1;
    }
    return map(x,0,100,1,32);
  }
};

struct BMCLogicControlChannelVU {
  // bits 0=overload, 1=changed
  BMCFlags <uint8_t> flags;
  BMCEndlessTimer meterDecayTimer;
  uint8_t meter = 0;
  uint8_t lastPeak = 0;
  void reset(){
    flags.reset();
    meter = 0;
    lastPeak = 0;
  }

  BMCLogicControlChannelVU(){
    meterDecayTimer.start(300);
  }
  void update(){
    if(meter>0 && meterDecayTimer){
      meter--;
      flags.on(1);
    }
  }
  bool hasChanged(){
    return flags.toggleIfTrue(1);
  }
  bool getOverload(){
    return flags.read(0);
  }
  uint8_t getPeak(){
    return lastPeak;
  }
  uint8_t getMeter(uint8_t max=0){
    if(max > 0 && (meter < max)){
      return 0;
    }
    return meter;
  }
  uint8_t getMeterValue(){
    return meter;
  }
  void setMeter(uint8_t value){
    if(assignMeterValue(value)){
      meterDecayTimer.restart();
    }
  }
  bool assignMeterValue(uint8_t value){
    switch(value){
      case 0x0D:
        break;
      case 0x0E:
        // set the overload
        if(!flags.read(0)){flags.on(1);}
        flags.on(0);
        return true;
      case 0x0F:
        // remove the overload
        if(flags.read(0)){flags.on(1);}
        flags.off(0);
        return true;
      default:
        // get the last peak state
        if(value != lastPeak){
          meter = value;
          flags.on(1);
        }
        lastPeak = value;
        return true;
    }
    return false;
  }
};
struct BMCLogicControlChannel {
  // state bits: 0=rec, 1=solo, 2=mute, 3=select, 4=signal
  uint8_t states = 0;
  int fader = -8192;
  uint8_t vPot = 0;
  BMCLogicControlChannelVU vu;
  void reset(){
    vu.reset();
    states = 0;
    fader = -8192;
    vPot = 0;
  }
  // get the state
  bool getRecState(){     return bitRead(states, 0);}
  bool getSoloState(){    return bitRead(states, 1);}
  bool getMuteState(){    return bitRead(states, 2);}
  bool getSelectState(){  return bitRead(states, 3);}
  bool getSignalState(){  return bitRead(states, 4);}

  void update(){
    vu.update();
  }
  uint8_t getVPot(){
    return vPot;
  }
  uint8_t getVPotCentered(){
    return bitRead(vPot, 6);
  }
  uint8_t getVPotMode(){
    return (vPot>>4)&0x03;
  }
  uint8_t getVPotValue(uint8_t ledN=0){
    if(ledN>0 && ledN<=11){
      switch(getVPotMode()){
        case 0: return getVPotMode0SingleDot(ledN);
        case 1: return getVPotMode1BoostCut(ledN);
        case 2: return getVPotMode2Wrap(ledN);
        case 3: return getVPotMode3Spread(ledN);
      }
    }
    return vPot & 0x0F;
  }
  uint8_t getVPotMode0SingleDot(uint8_t ledN=0){ // ok
    uint8_t value = vPot & 0x0F;
    return (ledN == value) ? value : 0;
  }
  uint8_t getVPotMode1BoostCut(uint8_t ledN=0){ // ok
    uint8_t value = vPot & 0x0F;
    if(ledN==6){
      return value;
    } else if(ledN<6){
      return (ledN >= value)?value:0;
    }
    return (ledN <= value)?value:0;// ledN > 6
  }
  uint8_t getVPotMode2Wrap(uint8_t ledN=0){ // ok
    uint8_t value = vPot & 0x0F;
    return (ledN > value) ? 0 : value;
  }
  uint8_t getVPotMode3Spread(uint8_t ledN=0){ // ok
    uint8_t value = vPot & 0x0F;
    if((ledN==6 && value==1) || value>6){
      return value;
    }
    if(value==1 && ledN!=6){
      return 0;
    }
    for(uint8_t i=2,e=0;i<7;i++,e++){
      if(value==i){
        if(ledN>=(5-e) && ledN<=(7+e)){
          return value;
        }
        return 0;
      }
    }
    return ledN==value ? value : 0;
  }

  // set the state
  void setRecState(bool value){     bitWrite(states, 0, value);}
  void setSoloState(bool value){    bitWrite(states, 1, value);}
  void setMuteState(bool value){    bitWrite(states, 2, value);}
  void setSelectState(bool value){  bitWrite(states, 3, value);}
  void setSignalState(bool value){  bitWrite(states, 4, value);}

  void setVPot(uint8_t value){
    vPot = value;
  }
  void setVolume(int value){
    fader = value;
  }
  int getVolume(){
    return fader;
  }
};
struct BMCLogicControlData {
  // flag bits: 0=online,
  uint8_t flags = 0;
  uint8_t selected = 0;
  uint32_t states = 0;
  uint8_t states2 = 0;
  int masterVolume = 0;
  BMCLogicControlChannel channel[8];

  void reset(){
    flags = 0;
    selected = 0;
    states = 0;
    for(uint8_t i=0;i<9;i++){
      channel[i].reset();
    }
  }

  void update(){
    for(uint8_t i=0;i<9;i++){
      channel[i].update();
    }
  }
  void setOnline(){
    reset();
    bitWrite(flags, 0, 1);
  }
  void setOffline(){
    reset();
    bitWrite(flags, 0, 0);
  }
  bool isOnline(){
    return bitRead(flags, 0);
  }
  uint8_t getSelectedChannel(){
    return selected;
  }
  void setSelectedChannel(uint8_t value){
    selected = value;
  }
  // GET
  bool getAssignTrack(){ return bitRead(states, 0); }
  bool getAssignSend(){ return bitRead(states, 1); }
  bool getAssignPan(){ return bitRead(states, 2); }
  bool getAssignPlugin(){ return bitRead(states, 3); }
  bool getAssignEQ(){ return bitRead(states, 4); }
  bool getAssignInstr(){ return bitRead(states, 5); }
  bool getFaderViewFlip(){ return bitRead(states, 6); }
  bool getFaderViewGlobal(){ return bitRead(states, 7); }
  bool getAutomationRead(){ return bitRead(states, 8); }
  bool getAutomationWrite(){ return bitRead(states, 9); }
  bool getAutomationTrim(){ return bitRead(states, 10); }
  bool getAutomationTouch(){ return bitRead(states, 11); }
  bool getAutomationLatch(){ return bitRead(states, 12); }
  bool getAutomationGroup(){ return bitRead(states, 13); }
  bool getUtilitySave(){ return bitRead(states, 14); }
  bool getUtilityUndo(){ return bitRead(states, 15); }
  bool getTransportMarker(){ return bitRead(states, 16); }
  bool getTransportNudge(){ return bitRead(states, 17); }
  bool getTransportCycle(){ return bitRead(states, 18); }
  bool getTransportDrop(){ return bitRead(states, 19); }
  bool getTransportReplace(){ return bitRead(states, 20); }
  bool getTransportClick(){ return bitRead(states, 21); }
  bool getTransportSolo(){ return bitRead(states, 22); }
  bool getTransportRewind(){ return bitRead(states, 23); }
  bool getTransportForward(){ return bitRead(states, 24); }
  bool getTransportStop(){ return bitRead(states, 25); }
  bool getTransportPlay(){ return bitRead(states, 26); }
  bool getTransportRecord(){ return bitRead(states, 27); }
  bool getTransportCursorZoom(){ return bitRead(states, 28); }
  bool getTransportScrub(){ return bitRead(states, 29); }
  bool getSMPTE(){ return bitRead(states, 30); }
  bool getBeats(){ return bitRead(states, 31); }
  bool getRudeSolo(){ return bitRead(states2, 0); }
  bool getRelay(){ return bitRead(states2, 1); }
  // SET
  void setAssignTrack(bool value){ bitWrite(states, 0, value); }
  void setAssignSend(bool value){ bitWrite(states, 1, value); }
  void setAssignPan(bool value){ bitWrite(states, 2, value); }
  void setAssignPlugin(bool value){ bitWrite(states, 3, value); }
  void setAssignEQ(bool value){ bitWrite(states, 4, value); }
  void setAssignInstr(bool value){ bitWrite(states, 5, value); }
  void setFaderViewFlip(bool value){ bitWrite(states, 6, value); }
  void setFaderViewGlobal(bool value){ bitWrite(states, 7, value); }
  void setAutomationRead(bool value){ bitWrite(states, 8, value); }
  void setAutomationWrite(bool value){ bitWrite(states, 9, value); }
  void setAutomationTrim(bool value){ bitWrite(states, 10, value); }
  void setAutomationTouch(bool value){ bitWrite(states, 11, value); }
  void setAutomationLatch(bool value){ bitWrite(states, 12, value); }
  void setAutomationGroup(bool value){ bitWrite(states, 13, value); }
  void setUtilitySave(bool value){ bitWrite(states, 14, value); }
  void setUtilityUndo(bool value){ bitWrite(states, 15, value); }
  void setTransportMarker(bool value){ bitWrite(states, 16, value); }
  void setTransportNudge(bool value){ bitWrite(states, 17, value); }
  void setTransportCycle(bool value){ bitWrite(states, 18, value); }
  void setTransportDrop(bool value){ bitWrite(states, 19, value); }
  void setTransportReplace(bool value){ bitWrite(states, 20, value); }
  void setTransportClick(bool value){ bitWrite(states, 21, value); }
  void setTransportSolo(bool value){ bitWrite(states, 22, value); }
  void setTransportRewind(bool value){ bitWrite(states, 23, value); }
  void setTransportForward(bool value){ bitWrite(states, 24, value); }
  void setTransportStop(bool value){ bitWrite(states, 25, value); }
  void setTransportPlay(bool value){ bitWrite(states, 26, value); }
  void setTransportRecord(bool value){ bitWrite(states, 27, value); }
  void setTransportCursorZoom(bool value){ bitWrite(states, 28, value); }
  void setTransportScrub(bool value){ bitWrite(states, 29, value); }

  void setSMPTE(bool value){ bitWrite(states, 30, value); }
  void setBeats(bool value){ bitWrite(states, 31, value); }
  void setRudeSolo(bool value){ bitWrite(states2, 0, value); }
  void setRelay(bool value){ bitWrite(states2, 1, value); }

  // CHANNELS
  // set the state
  bool getRecState(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getRecState() : 0;
  }
  bool getSoloState(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getSoloState() : 0;
  }
  bool getMuteState(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getMuteState() : 0;
  }
  bool getSelectState(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getSelectState() : 0;
  }
  bool getSignalState(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getSignalState() : 0;
  }
  uint8_t getVPot(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getVPot() : 0;
  }
  uint8_t getVPotCentered(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getVPotCentered() : 0;
  }
  uint8_t getVPotMode(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getVPotMode() : 0;
  }
  uint8_t getVPotValue(uint8_t n, uint8_t ledN=0){
    return chAllowed(n) ? channel[chCheck(n)].getVPotValue(ledN) : 0;
  }

  bool getMeterOverload(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].vu.getOverload() : false;
  }
  uint8_t getMeter(uint8_t n, uint8_t max=0){
    return chAllowed(n) ? channel[chCheck(n)].vu.getMeter(max) : 0;
  }
  uint8_t getMeterValue(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].vu.getMeterValue() : 0;
  }
  
  uint8_t getMeterPeak(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].vu.getPeak() : 0;
  }
  uint8_t getMeterChanged(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].vu.hasChanged() : 0;
  }

  // set the state
  void setRecState(uint8_t n, bool value){     if(chAllowed(n)){channel[n].setRecState(value);}}
  void setSoloState(uint8_t n, bool value){    if(chAllowed(n)){channel[n].setSoloState(value);}}
  void setMuteState(uint8_t n, bool value){    if(chAllowed(n)){channel[n].setMuteState(value);}}
  void setSelectState(uint8_t n, bool value){  if(chAllowed(n)){channel[n].setSelectState(value);}}
  void setSignalState(uint8_t n, bool value){  if(chAllowed(n)){channel[n].setSignalState(value);}}
  void setVPot(uint8_t n, uint8_t value){      if(chAllowed(n)){channel[n].setVPot(value);}}
  void setMeter(uint8_t n, uint8_t value){     if(chAllowed(n)){channel[n].vu.setMeter(value);}}

  void setVolume(uint8_t n, int value){
    if(chAllowed(n)){
      channel[n].setVolume(value);
    }
  }
  int getVolume(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getVolume() : 0;
  }
  void setMasterVolume(int value){
    masterVolume = value;
  }
  int getMasterVolume(){
    return masterVolume;
  }




  uint8_t chCheck(uint8_t n){
    return (n>=8) ? selected : n;
  }
  bool chAllowed(uint8_t n){
    return (n<=8);
  }
};
#endif
