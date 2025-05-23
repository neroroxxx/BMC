/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/

#ifndef BMC_STRUCT_H
#define BMC_STRUCT_H
#include <Arduino.h>


/*
  eventPacket.group = 0;
  eventPacket.deviceId = 0;
  eventPacket.deviceIndex = 0;
  eventPacket.ioType = 0;
  eventPacket.eventIndex = 0;
  eventPacket.value = 0;
*/
struct __attribute__ ((packed)) bmcEventPacket {
  uint8_t group = 0;
  uint8_t deviceId = 0;
  uint16_t deviceIndex = 0;
  uint8_t ioType = 0;
  uint16_t eventIndex = 0;
  uint8_t value = 0;
};

struct __attribute__ ((packed)) BMCDeviceData {
  uint8_t id = 0;
  char label[19] = "";
  int16_t group = 0;
  uint16_t length = 0;
  bool global = false;
  bool hardware = false;
  uint8_t settings = 0;
  uint8_t events = 0;
};

// struct __attribute__ ((packed)) BMCEventData {
//   uint8_t type = BMC_NONE;
//   char label[35] = "";
//   bool available = false;
//   bool scroll = false;
//   bool ports = false;
//   uint8_t fields = 0;
// };

struct bmcXY {
  int16_t x = 0;
  int16_t y = 0;
};

struct BMCEventScrollData {
  bool enabled = false;
  bool direction = false;
  bool wrap = true;
  uint8_t amount = 1;
  void set(uint8_t settings, uint8_t ticks, bool forceEnable=false){
    enabled = bitRead(settings, 0);
    direction = bitRead(settings, 1);
    wrap = bitRead(settings, 2);
    
    if(forceEnable){
      if(!enabled){
        wrap = true;
      }
      enabled = true; 
    }

    if(ticks > 0 || forceEnable){
      direction = bitRead(ticks, 7);
    }
    
    amount = ticks & 0x7F;
    if(amount == 0){
      amount = 1;
    }
  }
};

struct BMCDataContainer {
  uint16_t index = 0;
  uint8_t crc = 0;
  uint8_t settings = 0;
  uint8_t colors = 0;
  uint8_t type = 0;
  uint8_t byteA = 0;
  uint8_t byteB = 0;
  uint8_t byteC = 0;
  uint8_t byteD = 0;
  uint16_t value = 0;
  uint16_t valueSelected = 0;
  uint16_t min = 0;
  uint16_t max = 0;
  
  uint8_t offset = 0;
  uint8_t displayType = 0;
  bool highlight = false;
  // bool oled = false;
  bool useOffset = true;
  bool noScroll = false;
  bool allowMeter = false;
  bool prependValue = false;

  char str[41] = "";
  char strSelected[41] = "";
  char label[33] = "";
  // sprintf format
  char format[16] = "";
  uint8_t digits = 1;
  BMCEventScrollData scroll;

  uint16_t setMinMax(uint16_t t_currentValue, uint16_t t_min, uint16_t t_max, uint16_t t_min2, uint16_t t_max2){
    min = t_min;
    max = t_max;
    uint16_t outVal = t_min2;
    if(t_max2 > 0){
      // scrolling max or toggle enabled
      min = t_min2;
      max = t_max2-1;
      if(min > max){
        max = t_min2;
        min = t_max2-1;
      } else if(min == max){
        min = t_min;
        max = t_max-1;
      }
      if(!scroll.enabled){
        outVal = t_currentValue != min ? min : max;
      }
    }
    if(noScroll){
      outVal = scroll.direction ? max : min;
      scroll.enabled = false;
    }
    return outVal;
  }
  void setDisplayType(uint8_t t_value){
    displayType = t_value;
  }
  bool isOled(){
    return displayType == BMC_DEVICE_ID_OLED;
  }
  bool isIli(){
    return displayType == BMC_DEVICE_ID_ILI;
  }
  bool isMiniDisplay(){
    return displayType == BMC_DEVICE_ID_MINI_DISPLAY;
  }
  bool isLcd(){
    return displayType == BMC_DEVICE_ID_LCD;
  }
  void setNoScroll(bool t_value){
    noScroll = t_value;
  }
  uint8_t getChannel(){
    return BMC_TO_MIDI_CHANNEL(byteA);
  }
  bool showLabel(){
    return bitRead(settings, 0);
  }
  bool showBorder(){
    return bitRead(settings, 1);
  }
  bool useSelected(){
    return bitRead(settings, 2);
  }
  bool useName(){
    return bitRead(settings, 3);
  }
  bool useMeter(bool additionalCheck=true){
    return bitRead(settings, 4) && additionalCheck;
  }
  bool useOnOffSwitch(){
    return bitRead(settings, 4) && bitRead(settings, 5);
  }
  void setScroll(uint8_t t_settings, uint8_t t_ticks, bool t_forceEnable=false){
    scroll.set(t_settings, t_ticks, t_forceEnable);
  }
  bool scrollEnabled(){
    return scroll.enabled;
  }
  bool scrollDirection(){
    return scroll.direction;
  }
  bool scrollWrap(){
    return scroll.wrap;
  }
  uint8_t scrollAmount(){
    return scroll.amount;
  }
  void forceOnlyString(){
    bitWrite(settings, 2, 0);
    bitWrite(settings, 3, 1);
  }
  bool useStringOnly(){
    return !bitRead(settings, 2) && bitRead(settings, 3);
  }
};



#if defined(BMC_HAS_TOUCH_SCREEN)
struct bmcTouchArea {
  int16_t x = 0;
  int16_t y = 0;
  uint16_t width = 0;
  uint16_t height = 0;
  float xCalM = 0.0, yCalM = 0.0; // gradients
  float xCalC = 0.0, yCalC = 0.0; // y axis crossing points
  bmcXY xy;
  bmcTouchArea(){}
  void begin(int16_t t_x, int16_t t_y, uint16_t w, uint16_t h){
    x = t_x;
    y = t_y;
    width = w;
    height = h;
  }
  void setCalibrationData(float t_xCalM, float t_xCalC, float t_yCalM, float t_yCalC){
    xCalM = t_xCalM;
    xCalC = t_xCalC;
    yCalM = t_yCalM;
    yCalC = t_yCalC;
  }
  bool isTouched(int16_t t_x, int16_t t_y){
    getScreenCoordinates(t_x, t_y);
    if ((xy.x >= x) && (xy.x <= (x+width)) && (xy.y >= y) && (xy.y <= (y+height))){
      return true;
    }
    return false;
  }
  void getScreenCoordinates(int16_t t_x, int16_t t_y){
    int16_t xCoord = round((t_x * xCalM) + xCalC);
    int16_t yCoord = round((t_y * yCalM) + yCalC);
    if(xCoord < 0) xCoord = 0;
    if(xCoord >= BMC_TFT_WIDTH) xCoord = BMC_TFT_WIDTH - 1;
    if(yCoord < 0) yCoord = 0;
    if(yCoord >= BMC_TFT_HEIGHT) yCoord = BMC_TFT_HEIGHT - 1;
    xy.x = xCoord;
    xy.y = yCoord;
  }
};
#endif
struct bmcDawChannelsInfo {
  int8_t index = -1;
  // bool isOled = false;
  char name[10];
  char value[10];
  char twoDigitDisplay[3];
  uint8_t stateBits = 0;
  uint8_t vuValue = 0;
  uint16_t vuBits = 0;
  uint8_t vPotLevel = 0;
  uint16_t vPotBits = 0;
  uint8_t type;
  void reset(){
    index = -1;
    type = 0;
    strcpy(name, "");
    strcpy(value, "");
    stateBits = 0;
    vuValue = 0;
    vuBits = 0;
    vPotLevel = 0;
    vPotBits = 0;
  }
  bool isOled(){
    return type == BMC_DEVICE_ID_OLED;
  }
  bool isIli(){
    return type == BMC_DEVICE_ID_ILI;
  }
  bool isMiniDisplay(){
    return type == BMC_DEVICE_ID_MINI_DISPLAY;
  }
};

struct bmcDisplayIndexSel {
  int8_t index = -1;
  uint8_t type = 0;
  bool active = false;
  void reset(){
    index = -1;
    type = 0;
    active = false;
  }
  bool isOled(){
    return type == BMC_DEVICE_ID_OLED;
  }
  bool isLcd(){
    return type == BMC_DEVICE_ID_LCD;
  }
  bool isIli(){
    return type == BMC_DEVICE_ID_ILI;
  }
  bool isMiniDisplay(){
    return type == BMC_DEVICE_ID_MINI_DISPLAY;
  }
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

// #if !defined(BMC_DEVICE_UI_SHORTCUTS_1)
//   #define BMC_DEVICE_UI_SHORTCUTS_1 {{-1, -1, -1}, 900, 0, 0, 0, 0, 0, 0, 0};
// #endif

struct BMCLinkData {
  uint8_t id1 = 0;
  uint8_t index1 = 0;
  uint8_t id2 = 0;
  uint8_t index2 = 0;
  uint8_t id3 = 0;
  uint8_t index3 = 0;
  uint8_t id4 = 0;
  uint8_t index4 = 0;
};


template <uint16_t len>
struct BMCBitStates {
  uint16_t value[((len >> 4) & 0x0F)+1];
  bool updated = false;
  BMCBitStates(){
    memset(value, 0 , (((len >> 4) & 0x0F)+1)*sizeof(uint16_t));
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
  uint8_t pitchRaw = 0;
  int pitch = 0;
  char noteName[3] = "";
  BMCFlags <uint8_t> flags;
  BMCTimer timeout;
  void setData(uint8_t t_note, uint8_t t_string, uint8_t t_pitch){
    note = t_note & 0x7F;
    stringNumber = t_string & 0x7F;
    pitchRaw = t_pitch & 0x7F;
    pitch = map(t_pitch, 0, 127, -63, 64);
    switch(note){
			case 0: strcpy(noteName, "A "); break;
			case 1: strcpy(noteName, "Bb"); break;
			case 2: strcpy(noteName, "B "); break;
			case 3: strcpy(noteName, "C "); break;
			case 4: strcpy(noteName, "C#"); break;
			case 5: strcpy(noteName, "D "); break;
			case 6: strcpy(noteName, "Eb"); break;
			case 7: strcpy(noteName, "E "); break;
			case 8: strcpy(noteName, "F "); break;
			case 9: strcpy(noteName, "F#"); break;
			case 10: strcpy(noteName, "G "); break;
			case 11: strcpy(noteName, "G#"); break;
      default: strcpy(noteName, "??"); break;
		}
    
    timeout.start(250);
    // flags:
    // 0 > flattest
    // 1 > flatter
    // 2 > flat
    // 3 > sharp
    // 4 > sharper
    // 5 > sharpest
    flags.reset();
    flags.on(0);
    if(pitchRaw<62){
      flags.on(2); // flat
      if(pitchRaw < 42){
        flags.on(1); // flatter
      }
      if(pitchRaw < 21){
        flags.on(0); // flatest
      }
    } else if(pitchRaw > 64){
      flags.on(3); // sharp
      if(pitchRaw > 84){
        flags.on(4); // sharper
      }
      if(pitchRaw > 105){
        flags.on(5); // sharpest
      }
    }
  }
  bool isOn(){
    return flags.read(0);
  }
  bool timedout(){
    bool state = timeout.complete();
    if(state){
      reset();
    }
    return state;
  }

  bool inTune(){
    return isOn() && (!isFlat() && !isSharp());
  }
  bool outOfTune(){
    return isOn() && (isFlat() || isSharp());
  }
  bool isFlat(){
    return isOn() && flags.read(2);
  }
  bool isFlatter(){
    return isOn() && flags.read(1);
  }
  bool isFlattest(){
    return isOn() && flags.read(0);
  }
  bool isSharp(){
    return isOn() && flags.read(3);
  }
  bool isSharper(){
    return isOn() && flags.read(4);
  }
  bool isSharpest(){
    return isOn() && flags.read(5);
  }

  void reset(){
    stringNumber = 0;
    pitch = 0;
    pitchRaw = 0;
    note = 0;
    strcpy(noteName, "");
    timeout.stop();
    flags.reset();
  }
};
struct BMCLooperData {
  bool enabled = false;
  uint8_t data;
  uint8_t position;
  void set(uint8_t t_data, uint8_t t_position){
    data = t_data;
    position = t_position;
  }
  void changeState(bool value){
    enabled = value;
  }
  bool getStates(uint8_t bit=255){
    if(bit<=6){
      return  bitRead(data, bit);
    } else {
      return data;
    }
    return false;
  }
  uint8_t getData(){
    return data;
  }
  bool isEnabled(){   return enabled; }
  bool recording(){   return bitRead(data, BMC_FAS_LOOPER_STATE_RECORDING); }
  bool playing(){     return bitRead(data, BMC_FAS_LOOPER_STATE_PLAYING); }
  bool once(){        return bitRead(data, BMC_FAS_LOOPER_STATE_ONCE); }
  bool overdubbing(){ return bitRead(data, BMC_FAS_LOOPER_STATE_OVERDUBBING); }
  bool reversed(){    return bitRead(data, BMC_FAS_LOOPER_STATE_REVERSED); }
  bool half(){        return bitRead(data, BMC_FAS_LOOPER_STATE_HALF); }
  bool undo(){        return bitRead(data, BMC_FAS_LOOPER_STATE_UNDO); }


  uint8_t getPosition(){ return position; }
  void reset(){
    data = 0;
    position = 0;
    // do not reset the enabled as it's controller by BMC Settings.
    //enabled = false;
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
  // bit1 -> query target       =>  0=global, 1=layer
  // bit2 -> Save to all layers  =>  if on, save the payload to all layers
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

  void setLayer(bool value=true)     {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_LAYER,value);}
  bool isLayer()                     {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_LAYER);}

  void setAllLayers(bool value=true) {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_ALL_LAYERS,value);}
  bool isAllLayers()                 {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_ALL_LAYERS);}

  void setBackup(bool value=true)   {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_BACKUP,value);}
  bool isBackup()                   {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_BACKUP);}

  void setError(bool value=true)    {bitWrite(flags,BMC_EDITOR_SYSEX_FLAG_ERROR,value);}
  bool isError()                    {return bitRead(flags,BMC_EDITOR_SYSEX_FLAG_ERROR);}

  void reset(){
    flags = 0;
  }
};
// keep variable order BMCSketchByteData
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
    memset(string, 0, sizeof(string[0])*strLen);
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

  bool setFromMidi(uint8_t n, uint8_t d, uint8_t c, uint8_t n32){
    uint8_t pNum = numerator;
    uint8_t pDen = denominator;
    numerator = n;
    denominator = (uint8_t) pow((int)(-d),2);
    metClocks = c;
    notated32 = n32;
    // return true if a change has happened
    return (numerator != pNum || denominator != pDen);
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
  // BMCEndlessTimer meterDecayTimer;
  uint8_t meter = 0;
  uint8_t lastPeak = 0;
  void reset(){
    flags.reset();
    meter = 0;
    lastPeak = 0;
  }

  void update(){
    // if(meter>0 && meterDecayTimer){
    //   meter--;
    //   flags.on(1);
    // }
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
      // meterDecayTimer.restart();
    }
  }
  bool assignMeterValue(uint8_t value){
    switch(value){
      case 0x0D:
        break;
      case 0x0E:
        // set the overload
        if(!flags.read(0)){
          flags.on(1);
        }
        flags.on(0);
        return true;
      case 0x0F:
        // remove the overload
        if(flags.read(0)){
          flags.on(1);
        }
        flags.off(0);
        return true;
      default:
        // get the last peak state
        if(value != meter){
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
  int16_t fader = (-8192);
  uint8_t vPot = 0;
  BMCLogicControlChannelVU vu;
  void reset(){
    vu.reset();
    states = 0;
    fader = (-8192);
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
  void setVolume(int16_t value){
    fader = value;
  }
  int16_t getVolume(){
    return fader;
  }
};
struct BMCLogicControlData {
  // flag bits: 0=online,
  uint8_t flags = 0;
  uint8_t selected = 0;
  uint32_t states = 0;
  uint8_t states2 = 0;
  int16_t masterVolume = 0;
  BMCLogicControlChannel channel[9];

  void reset(){
    flags = 0;
    selected = 0;
    states = 0;
    for(uint8_t i = 0 ; i < 9 ; i++){
      channel[i].reset();
    }
  }

  void update(){
    for(uint8_t i = 0 ; i < 9 ; i++){
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

  void setVolume(uint8_t n, int16_t value){
    if(chAllowed(n)){
      channel[n].setVolume(value);
    }
  }
  int16_t getVolume(uint8_t n){
    return chAllowed(n) ? channel[chCheck(n)].getVolume() : 0;
  }
  void setMasterVolume(int16_t value){
    masterVolume = value;
  }
  int16_t getMasterVolume(){
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
