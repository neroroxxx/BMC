/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#ifndef BMC_STRUCT_H
#define BMC_STRUCT_H
#include <Arduino.h>

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
};
struct BMCMidiEvent {
  uint32_t event = 0;
  void setEvent(uint32_t e){
    event = e;
  }
  void setEvent(uint8_t port=0, uint8_t status=0, uint8_t channel=0, uint8_t data1=0, uint8_t data2=0){
    // don't mask data2 to 7 bits since we can allow for 128 as a value to toggle
    if(status<0xF0){
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
    return (status < 0xF0) ? (status & 0xF0) : status;
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

#endif
