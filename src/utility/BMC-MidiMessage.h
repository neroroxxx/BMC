/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  This class started as a simple wrapper for midi data
  but overtime I added all the functions needed by the editor
*/

#ifndef BMC_MIDIMESSAGE_H
#define BMC_MIDIMESSAGE_H
#include <Arduino.h>

struct BMCMidiMessage {
  uint8_t ports = 0;
  uint8_t status = 0;
  uint8_t channel = 0;
  uint8_t data1 = 0;
  uint8_t data2 = 0;
  uint8_t sysex[BMC_MIDI_SYSEX_SIZE];

  uint8_t getStatus(bool t_and=false){
    return (t_and) ? (status & 0xF0) : status;
  }
  uint8_t getChannel(){ return channel; }
  uint8_t getData1()  { return data1; }
  uint8_t getData2()  { return data2; }
  uint8_t getPort()   { return ports; }
  uint8_t getSource() { return getPort(); }

  void setStatus(uint8_t t_status)    { status = t_status; }
  void setChannel(uint8_t t_channel)  { channel = t_channel; }
  void setData1(uint8_t t_data1)      { data1 = t_data1; }
  void setData2(uint8_t t_data2)      { data2 = t_data2; }
  void setPort(uint8_t t_port)        { ports = t_port; }
  void setSource(uint8_t t_port)      { setPort(t_port); }
  // reset all data in the struct
  void reset(uint8_t sourcePortBit=0){
    memset(sysex, 0, sizeof(sysex[0])*BMC_MIDI_SYSEX_SIZE);
    setStatus(0);
    setChannel(0);
    setData1(0);
    setData2(0);
    setPort(0);
    bitWrite(ports, sourcePortBit, 1);
  }
  void addRaw(uint8_t t_port, uint8_t t_status,
              uint8_t t_data1=0, uint8_t t_data2=0){
    reset();
    if(t_status>=0xF0){
      setStatus(t_status);
    } else{
      setStatus(t_status & 0xF0);
      setChannel(t_status & 0x0F);
      setData1(t_data1 & 0x7F);
      setData2(t_data2);
    }
    setPort(t_port);
  }
  bool matchSourceAndChannel(uint8_t t_source, uint8_t t_channel){
    return matchSource(t_source) && matchChannel(t_channel);
  }
  bool matchSource(uint8_t t_source){
    return getSource()==t_source;
  }
  bool matchChannel(uint8_t t_channel){
    return getChannel()==t_channel;
  }
  uint32_t getEvent(){
    uint32_t event = 0;
    if(getStatus()>127 && !isSysEx()){
      // channel passed must be 1 to 16
      if(getChannel()==0){
        return event;
      }
      // if the status is less than 0xF0 it has a channel
      if(getStatus()<0xF0){
        // has a channel
        event = getStatus();
        event |= ((getChannel()-1) & 0x0F);
      } else {
        // use the raw status
        event = getStatus();
      }
      event |= (getData1() << 8) | (getData2() << 16);
      event |= (getPort()<<24);
    }
    return event;
  }
  // append a byte to the sysex array
  // @value the byte to append
  // @andByte if true, removes the 8th bit of the byte
  // this is because MIDI data is only 7-bit and 8-bit bytes
  // are reserved for MIDI Status
  bool appendSysExByte(uint8_t value, bool andByte=true){
    if(andByte && (value!=0xF0 && value!=0xF7)){
      value &= 0x7F;
    }
    uint16_t sysLength = size();
    if(sysLength<BMC_MIDI_SYSEX_SIZE){
      sysex[sysLength++] = value;
      setSysExArrayLength(sysLength);
      return true;
    }
    return false;
  }
  void setSysExArrayLength(uint16_t value){
    setData1(value & 0xFF);
    setData2((value >> 8) & 0xFF);
	}
  uint8_t peekSysEx(uint8_t index){
    if(index < BMC_MIDI_SYSEX_SIZE){
      return sysex[index];
    }
    return 0;
  }
  uint8_t * getSysExArray(){
		return sysex;
	}
  uint8_t * getSysEx(){
		return sysex;
	}
  uint16_t size(){
		return getData1() | (getData2() << 8);
	}
  uint16_t getSysExSize(){
		return size();
	}
  uint16_t getSysExArrayLength(){
		return size();
	}
  int getPitchValue(){
    return (getData1() & 0x7F) | ((getData2() & 0x7F) << 7);
  }
  void addSysEx(const uint8_t *data, uint16_t length){
    if(length < BMC_MIDI_SYSEX_SIZE){
      setStatus(BMC_MIDI_SYSTEM_EXCLUSIVE);
      memcpy(sysex, data, length);
      setSysExArrayLength(length);
    }
  }
  bool isEditorMessage(){
    return (isSysEx() && isEditorSysExLength() && isEditorSysExId());
  }
  bool isEditorSysExLength(){
    return size()>=BMC_EDITOR_SYSEX_MIN_LENGTH;
  }
  bool isEditorSysExId(){
    return (BMC_MERGE_BYTES(sysex[1],sysex[2],sysex[3])==BMC_EDITOR_SYSEX_ID);
  }
  uint8_t getCrc(){
    if(isSysEx() && size()>3){
      return sysex[size()-2];
    }
    return 0;
  }
  bool validateChecksum(){
    return validateCrc();
  }
  void createChecksum(bool addCrcByte){
    return createCrc(addCrcByte);
  }
  bool isData1(uint8_t t_value){
    return getData1()==t_value;
  }
  bool isData2(uint8_t t_value){
    return getData2()==t_value;
  }
  bool validateCrc(){
    if(isSysEx() && size()>0){
      uint8_t crc = 0;
      uint8_t crcIndex = size()-2;
      uint8_t crcIncoming = sysex[crcIndex];
      for(uint16_t i=0;i<crcIndex;i++){
        crc ^= (sysex[i] & 0x7F);
      }
      return (crcIncoming == crc);
    }
    return false;
  }
  void createCrc(bool addCrcByte){
    if(isSysEx() && size()>0){
      if(addCrcByte && sysex[size()-1]!=0xF7){
        appendToSysEx7Bits(0);
      }
      uint8_t crc = 0;
      uint16_t n = size() - (addCrcByte ? 1 : 2);
      if(sysex[0]!=0xF0){
        crc ^= 0x70;// 0x70 = (0xF0 & 0x7F);
      }
      for(uint16_t i=0;i<n;i++){
        crc ^= (sysex[i] & 0x7F);
      }
      sysex[n] = crc;
    }
  }
  void prepareEditorMessage(uint8_t t_source, uint8_t deviceId,
                            uint8_t functionId, BMCEditorMidiFlags flags,
                            uint16_t layer=0){
    prepareEditorMessage(t_source, deviceId, functionId, flags.get(), layer);
  }
  uint8_t get7Bits(uint16_t t_offset){
    // get 8-bits from a sysex at a specified index, encoded as 2 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if(t_offset < size()){
      return sysex[t_offset] & 0x7F;
    }
    return 0;
  }
  uint8_t get8Bits(uint16_t t_offset){
    // get 8-bits from a sysex at a specified index, encoded as 2 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+1) < size()){
      return BMC_MIDI_ARRAY_TO_8BITS(t_offset,sysex) & 0xFF;
    }
    return 0;
  }
  uint8_t get8BitsLSBFirst(uint16_t t_offset){
    // get 8-bits from a sysex at a specified index, encoded as 2 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+1) < size()){
      return BMC_MIDI_ARRAY_TO_8BITS_LSB_FIRST(t_offset,sysex) & 0xFF;
    }
    return 0;
  }
  uint16_t get14Bits(uint16_t t_offset){
    // get 14-bits from a sysex at a specified index, encoded as 2 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+1) < size()){
      return BMC_MIDI_ARRAY_TO_8BITS(t_offset, sysex);
    }
    return 0;
  }
  uint16_t get14BitsLSBFirst(uint16_t t_offset){
    // get 14-bits from a sysex at a specified index, encoded as 2 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+1) < size()){
      return BMC_MIDI_ARRAY_TO_8BITS_LSB_FIRST(t_offset, sysex);
    }
    return 0;
  }
  uint16_t get16Bits(uint16_t t_offset){
    // get 16-bits from a sysex at a specified index, encoded as 3 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+2) < size()){
      return BMC_MIDI_ARRAY_TO_16BITS(t_offset, sysex) & BMC_MASK_16;
    }
    return 0;
  }
  uint16_t get16BitsLSBFirst(uint16_t t_offset){
    // get 16-bits from a sysex at a specified index, encoded as 3 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+2) < size()){
      return BMC_MIDI_ARRAY_TO_16BITS_LSB_FIRST(t_offset, sysex) & BMC_MASK_16;
    }
    return 0;
  }
  uint32_t get32Bits(uint16_t t_offset){
    // get 32-bits from a sysex at a specified index, encoded as 5 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+4) < size()){
      return BMC_MIDI_ARRAY_TO_32BITS(t_offset, sysex) & BMC_MASK_32;
    }
    return 0;
  }

  uint32_t get32BitsLSBFirst(uint16_t t_offset){
    // get 32-bits from a sysex at a specified index, encoded as 5 midi words
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    if((t_offset+4) < size()){
      return BMC_MIDI_ARRAY_TO_32BITS_LSB_FIRST(t_offset, sysex) & BMC_MASK_32;
    }
    return 0;
  }




  int get8BitsSigned(uint16_t t_offset){
    // get 8-bits from a sysex at a specified index, encoded as 2 midi words
    // signed
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    return (int) get8Bits(t_offset);
  }
  int get16BitsSigned(uint16_t t_offset){
    // get 16-bits from a sysex at a specified index, encoded as 3 midi words
    // signed
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    return (int) get16Bits(t_offset);
  }
  long get32BitsSigned(uint16_t t_offset){
    // get 32-bits from a sysex at a specified index, encoded as 5 midi words
    // signed
    // a midi word refers to a 7-bit byte which are used by MIDI for data
    return (long) get32Bits(t_offset);
  }
  void prepareEditorMessage(uint8_t t_source, uint8_t deviceId,
                            uint8_t functionId, uint8_t flags=0,
                            uint16_t layer=0){
    // 0 = 0xF0 altho we don't actually include since when
    //     we send the message we specify that it has no 0xF0 nor 0xF7
    //     but we still specify it here for when we read and incoming sysex
    // 1 = 7D sysex id A
    // 2 = 7D sysex id B
    // 3 = 7D sysex id C
    // 4 = XX device id
    // 5 = XX flags:
    //   bit0 -> query type    =>  0=read, 1=write
    //   bit1 -> query target  =>  0=global, 1=layer
    //   bit2 -> Save to all layers  =>  0=save item specified layer, 1=all layers
    // 6 = XX layer/item number (MSB) 14-bits total
    // 7 = XX layer/item number (LSB) 14-bits total
    // 8 = XX function id
    // x ...
    // 9 -> CRC
    // 10 -> 0xF0
    reset(t_source);
    setStatus(BMC_MIDI_SYSTEM_EXCLUSIVE);
    appendToSysEx7Bits(BMC_GET_BYTE(2,BMC_EDITOR_SYSEX_ID));
    appendToSysEx7Bits(BMC_GET_BYTE(1,BMC_EDITOR_SYSEX_ID));
    appendToSysEx7Bits(BMC_GET_BYTE(0,BMC_EDITOR_SYSEX_ID));
    appendToSysEx7Bits(deviceId);
    appendToSysEx7Bits(flags);
    appendToSysEx14Bits(layer); // 2 bytes
    appendToSysEx7Bits(functionId);
  }
  // append a 7-bit midi word to the sysex array
  void appendToSysEx7Bits(uint8_t value){
    appendSysExByte(value & 0x7F);
  }
  // append a byte as two 7-bit midi words to the sysex array
  void appendToSysEx8Bits(uint8_t value){
    // Always MSB first
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0,value));
  }
  // append a byte as two 7-bit midi words to the sysex array
  void appendToSysEx8BitsLSBFirst(uint8_t value){
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1,value));
  }
  // same as appendToSysEx14Bits
  void appendToSysEx14Bits(uint16_t value){
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1, value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0, value));
  }
  // same as appendToSysEx8BitsLSBFirst
  void appendToSysEx14BitsLSBFirst(uint16_t value){
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0, value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1, value));
  }

  // append a 16-bit byte as three 7-bit midi words to the sysex array
  void appendToSysEx16Bits(uint16_t value){
    // Always MSB first
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(2,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0,value));
  }
  // append a 16-bit byte as three 7-bit midi words to the sysex array
  void appendToSysEx16BitsLSBFirst(uint16_t value){
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(2,value));
  }
  // append a 32-bit byte as five 7-bit midi words to the sysex array
  void appendToSysEx32Bits(uint32_t value){
    // Always MSB first
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(4,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(3,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(2,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0,value));
  }
  // append a 32-bit byte as five 7-bit midi words to the sysex array
  void appendToSysEx32BitsLSBFirst(uint32_t value){
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(0,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(1,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(2,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(3,value));
    appendToSysEx7Bits(BMC_MIDI_GET_WORD(4,value));
  }
  // append a string to the sysex array
  // str = char string array
  // length = length of the string (including null)
  // no more than 32 characters should be allowed including the EOL
  void appendCharArrayToSysEx(char *str, uint8_t length){
    for(uint8_t i = 0, n = length-1 ; i < length ; i++){
      // max 32 characters
      if(i==32){
        appendToSysEx7Bits(0);
        break;
      }
      // n = the index of the last char of the char array
      // this one must always be 0
      if(i == n){
        appendToSysEx7Bits(0);
      } else {
        appendToSysEx7Bits((uint8_t) str[i]);
      }
    }
  }
  // same as above but with a String instead
  void appendCharArrayToSysEx(String str){
    // create a buffer
    uint8_t len = str.length()+1;
    char buff[len];
    str.toCharArray(buff, len);
    appendCharArrayToSysEx(buff, len);
  }
  // get a char string array from the sysex message
  // startsAt = where in the sysex array the string starts
  // str = char array buffer that will take in the bytes from sysex
  // length = the length of the char buffer
  void getStringFromSysEx(uint8_t startsAt, char *str, uint8_t length){
    if(length > 1 && (startsAt + length) < size()){
      // set all characters in the array to be 0 (null)
      memset(str, 0, length);

      for(uint8_t i = 0, e = startsAt ; i < length ; i++, e++){
        // only get actual characters, numbers or symbols
        str[i] = (char) sysex[e];
      }
      // always set the last character to 0
      str[length-1] = 0;
    }
  }
  bool isValidCharacterValue(uint8_t c){
    return (c >= 1 && c <= 126);
  }
  bool isValid(){
    return getStatus()>127 && !isUndefined();
    //return !((getStatus() < 128) || isUndefined());
  }
  bool isStatus(){
    return isValid();
  }
  bool isChannelStatus(){
    //return (getStatus() > 0x7F && getStatus() < 0xF0);
    switch(getStatus()){
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_AFTER_TOUCH_POLY:
      case BMC_MIDI_CONTROL_CHANGE:
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_AFTER_TOUCH:
      case BMC_MIDI_PITCH_BEND:
        return true;
    }
    return false;
  }
  bool isVoiceStatus(){
    return isChannelStatus();
  }
  bool isSystemCommonStatus(){
    switch(getStatus()){
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
      case BMC_MIDI_SONG_POSITION:
      case BMC_MIDI_SONG_SELECT:
      case BMC_MIDI_TUNE_REQUEST:
        return true;
    }
    return false;
  }
  bool isSystemExclusiveStatus(){
    return (getStatus() == BMC_MIDI_SYSTEM_EXCLUSIVE);
  }
  bool isSystemRealTimeStatus(){
    //return (getStatus() >= 0xF8);
    switch(getStatus()){
      case BMC_MIDI_RT_CLOCK:
      case BMC_MIDI_RT_START:
      case BMC_MIDI_RT_CONTINUE:
      case BMC_MIDI_RT_STOP:
      case BMC_MIDI_RT_ACTIVE_SENSE:
      case BMC_MIDI_RT_SYSTEM_RESET:
        return true;
    }
    return false;
  }
  bool isUndefined(){
    switch(getStatus()){
      case 0xF4:
      case 0xF5:
      case 0xF7:
      case 0xFD:
        return true;
    }
    return false;
  }
  bool isOneByteMidiMessage(){
    switch(BMC_GET_MIDI_STATUS(getStatus())){
      case BMC_MIDI_TUNE_REQUEST:
      case BMC_MIDI_RT_CLOCK:
      case BMC_MIDI_RT_START:
      case BMC_MIDI_RT_CONTINUE:
      case BMC_MIDI_RT_STOP:
      case BMC_MIDI_RT_ACTIVE_SENSE:
      case BMC_MIDI_RT_SYSTEM_RESET:
        return true;
    }
    return false;
  }
  bool isTwoByteMidiMessage(){
    switch(BMC_GET_MIDI_STATUS(getStatus())){
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
      case BMC_MIDI_SONG_SELECT:
      case BMC_MIDI_PROGRAM_CHANGE:
        return true;
    }
    return false;
  }
  bool isThreeByteMidiMessage(){
    switch(BMC_GET_MIDI_STATUS(getStatus())){
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_AFTER_TOUCH_POLY:
      case BMC_MIDI_CONTROL_CHANGE:
      case BMC_MIDI_AFTER_TOUCH:
      case BMC_MIDI_PITCH_BEND:
      case BMC_MIDI_SONG_POSITION:
        return true;
    }
    return false;
  }
  bool isProgramOrControl(){
    switch(getStatus(true)){
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_CONTROL_CHANGE:
        return true;
    }
    return false;
  }
  bool isNoteOff(){
    return BMC_IS_NOTE_OFF(getStatus()); //0x80
  }
  bool isNoteOn(){
    return BMC_IS_NOTE_ON(getStatus()); //0x90
  }
  bool isAfterTouchPoly(){
    return BMC_IS_AFTER_TOUCH_POLY(getStatus()); //0xA0
  }
  bool isControlChange(){
    return BMC_IS_CONTROL_CHANGE(getStatus()); //0xB0
  }
  bool isProgramChange(){
    return BMC_IS_PROGRAM_CHANGE(getStatus()); //0xC0
  }
  bool isProgramChange(uint8_t t_channel){
    return BMC_IS_PROGRAM_CHANGE(getStatus()) && t_channel==getChannel();
  }
  bool isProgramChange(uint8_t t_channel, uint8_t t_program){
    return isProgramChange() && t_channel==getChannel() && t_program==getData1();
  }
  bool isAfterTouch(){
    return BMC_IS_AFTER_TOUCH(getStatus()); //0xD0
  }
  bool isPitchBend(){
    return BMC_IS_PITCH_BEND(getStatus()); //0xE0
  }
  bool isSystemExclusive(){
    return BMC_IS_SYSTEM_EXCLUSIVE(getStatus()); //0xF0
  }
  bool isSysEx(){
    return isSystemExclusive();
  }
  bool isTimeCodeQuarterFrame(){
    return BMC_IS_TIME_CODE_QUARTER_FRAME(getStatus()); //0xF1
  }
  bool isSongPosition(){
    return BMC_IS_SONG_POSITION(getStatus()); //0xF2
  }
  bool isSongSelect(){
    return BMC_IS_SONG_SELECT(getStatus()); //0xF2
  }
  bool isTuneRequest(){
    return BMC_IS_TUNE_REQUEST(getStatus()); //0xF6
  }
  bool isClock(){
    return BMC_IS_CLOCK(getStatus()); //0xF8
  }
  bool isStart(){
    return BMC_IS_START(getStatus()); //0xFA
  }
  bool isContinue(){
    return BMC_IS_CONTINUE(getStatus()); //0xFB
  }
  bool isStartOrContinue(){
    return isStart() || isContinue();
  }

  bool isStop(){
    return BMC_IS_STOP(getStatus()); //0xFC
  }
  bool isActiveSense(){
    return BMC_IS_ACTIVE_SENSE(getStatus()); //0xFE
  }
  bool isSystemReset(){
    return BMC_IS_SYSTEM_RESET(getStatus()); //0xFF
  }
  // check which port is assigned to message
  bool isUSB(){
    return bitRead(ports, BMC_MIDI_PORT_USB_BIT);
  }
  bool isSerialA(){
    return bitRead(ports, BMC_MIDI_PORT_SERIAL_A_BIT);
  }
  bool isSerialB(){
    return bitRead(ports, BMC_MIDI_PORT_SERIAL_B_BIT);
  }
  bool isSerialC(){
    return bitRead(ports, BMC_MIDI_PORT_SERIAL_C_BIT);
  }
  bool isSerialD(){
    return bitRead(ports, BMC_MIDI_PORT_SERIAL_D_BIT);
  }
  bool isHost(){
    return bitRead(ports, BMC_MIDI_PORT_HOST_BIT);
  }
  bool isBLE(){
    return bitRead(ports, BMC_MIDI_PORT_BLE_BIT);
  }
};
#endif
