/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#ifndef BMC_TOOLS_H
#define BMC_TOOLS_H
#include "utility/BMC-Def.h"

class BMCTools {
private:
  BMCTools(){}
public:
  static bool match(int n, int v){
    return n==v;
  }
  static bool match(int n1, int v1, int n2, int v2){
    return match(n1,v1) && match(n2,v2);
  }
  static bool match(int n1, int v1, int n2, int v2, int n3, int v3){
    return match(n1,v1,n2,v2) && match(n3,v3);
  }
  static bool match(int n1, int v1, int n2, int v2, int n3, int v3, int n4, int v4){
    return match(n1,v1,n2,v2,n3,v3) && match(n4,v4);
  }
  static bool match(int n1, int v1, int n2, int v2, int n3, int v3, int n4, int v4, int n5, int v5){
    return match(n1,v1,n2,v2,n3,v3,n4,v4) && match(n5,v5);
  }
  static bool isMidiUsbPort(uint8_t port){
    return bitRead(port,BMC_MIDI_PORT_USB_BIT);
  }
  static bool isMidiSerialAPort(uint8_t port){
    return bitRead(port,BMC_MIDI_PORT_SERIAL_A_BIT);
  }
  static bool isMidiSerialBPort(uint8_t port){
    return bitRead(port,BMC_MIDI_PORT_SERIAL_B_BIT);
  }
  static bool isMidiSerialCPort(uint8_t port){
    return bitRead(port,BMC_MIDI_PORT_SERIAL_C_BIT);
  }
  static bool isMidiSerialDPort(uint8_t port){
    return bitRead(port,BMC_MIDI_PORT_SERIAL_D_BIT);
  }
  static bool isMidiHostPort(uint8_t port){
    return bitRead(port,BMC_MIDI_PORT_HOST_BIT);
  }
  static bool isMidiBlePort(uint8_t port){
    return bitRead(port,BMC_MIDI_PORT_BLE_BIT);
  }
  static String getPortName(uint8_t port){
    if(isMidiUsbPort(port)){
      return "USB";
    } else if(isMidiSerialAPort(port)){
      return "SerialA";
    } else if(isMidiSerialBPort(port)){
      return "SerialB";
    } else if(isMidiSerialCPort(port)){
      return "SerialC";
    } else if(isMidiSerialDPort(port)){
      return "SerialD";
    } else if(isMidiHostPort(port)){
      return "USB Host";
    } else if(isMidiBlePort(port)){
      return "BLE";
    }
    return "";
  }
  static String getPortsName(uint8_t port){
    return getPortName(port);
  }
  static String printPortsNames(uint8_t port){
    if(isMidiUsbPort(port)){
      BMC_PRINT("USB, ");
    } else if(isMidiSerialAPort(port)){
      BMC_PRINT("SerialA, ");
    } else if(isMidiSerialBPort(port)){
      BMC_PRINT("SerialB, ");
    } else if(isMidiSerialCPort(port)){
      BMC_PRINT("SerialC, ");
    } else if(isMidiSerialDPort(port)){
      BMC_PRINT("SerialD, ");
    } else if(isMidiHostPort(port)){
      BMC_PRINT("USB Host, ");
    } else if(isMidiBlePort(port)){
      BMC_PRINT("BLE, ");
    }
    return "";
  }
  static String getMidiStatusName(uint8_t status){
    switch(status){
      case BMC_MIDI_RT_CLOCK:
        return "Clock";
      case BMC_MIDI_RT_START:
        return "Start";
      case BMC_MIDI_RT_CONTINUE:
        return "Continue";
      case BMC_MIDI_RT_STOP:
        return "Stop";
      case BMC_MIDI_SYSTEM_EXCLUSIVE:
        return "SysEx";
      case BMC_MIDI_CONTROL_CHANGE:
        return "Control Change";
      case BMC_MIDI_PROGRAM_CHANGE:
        return "Program Change";
      case BMC_MIDI_NOTE_ON:
        return "Note On";
      case BMC_MIDI_NOTE_OFF:
        return "Note Off";
      case BMC_MIDI_RT_ACTIVE_SENSE:
        return "Active Sense";
      case BMC_MIDI_PITCH_BEND:
        return "Pitch Bend";
      case BMC_MIDI_AFTER_TOUCH_POLY:
        return "After Touch Poly";
      case BMC_MIDI_AFTER_TOUCH:
        return "After Touch";
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
        return "Time Code Quarter Frame";
      case BMC_MIDI_SONG_POSITION:
        return "Song Position";
      case BMC_MIDI_SONG_SELECT:
        return "Song Select";
      case BMC_MIDI_TUNE_REQUEST:
        return "Tune Request";
      case BMC_MIDI_RT_SYSTEM_RESET:
        return "System Reset";
    }
    return "Unknown";
  }
  /*
  static bool isMidiClockLedEvent(uint32_t t_value){
    return ((t_value&0xFF)==BMC_LED_EVENT_TYPE_CLOCK_SYNC);
  }
  */
  static bool isMidiClockLedEvent(uint8_t t_value){
    return t_value == BMC_EVENT_TYPE_SYSTEM_CLOCK ||
            t_value == BMC_EVENT_TYPE_SYSTEM_CLOCK_TAP;
  }
  static String getButtonTriggerName(uint8_t t_trigger){
    switch(t_trigger){
      case BMC_BUTTON_PRESS_TYPE_PRESS:
        return "Press";
      case BMC_BUTTON_PRESS_TYPE_RELEASE:
        return "Release";
      case BMC_BUTTON_PRESS_TYPE_HOLD:
        return "Hold";
      case BMC_BUTTON_PRESS_TYPE_DOUBLE_PRESS:
        return "Double Press";
      case BMC_BUTTON_PRESS_TYPE_CONTINUOUS:
        return "Continuous";
      case BMC_BUTTON_PRESS_TYPE_ALT_PRESS:
        return "Alt/2nd Press";
    }
    return "Unknown";
  }
  static void getButtonTriggerName(uint8_t value, char* str){
    switch(value){
      case BMC_NONE:
        strcpy(str, "Inactive");
        break;
      case BMC_BUTTON_PRESS_TYPE_PRESS:
        strcpy(str, "Press");
        break;
      case BMC_BUTTON_PRESS_TYPE_HOLD:
        strcpy(str, "Hold");
        break;
      case BMC_BUTTON_PRESS_TYPE_DOUBLE_PRESS:
        strcpy(str, "Double Press");
        break;
      case BMC_BUTTON_PRESS_TYPE_CONTINUOUS:
        strcpy(str, "Continuous");
        break;
      case BMC_BUTTON_PRESS_TYPE_ALT_PRESS:
        strcpy(str, "2nd Press");
        break;
      case BMC_BUTTON_PRESS_TYPE_STATE_CHANGE:
        strcpy(str, "State Change");
        break;
      case BMC_BUTTON_PRESS_TYPE_RELEASE:
        strcpy(str, "Releas/Always");
        break;
      case BMC_BUTTON_PRESS_TYPE_RELEASE_PRESS:
        strcpy(str, "Releas/Press");
        break;
      case BMC_BUTTON_PRESS_TYPE_RELEASE_HOLD:
        strcpy(str, "Releas/Hold");
        break;
      case BMC_BUTTON_PRESS_TYPE_RELEASE_DOUBLE_PRESS:
        strcpy(str, "Releas/DblPress");
        break;
      case BMC_BUTTON_PRESS_TYPE_RELEASE_CONTINUOUS:
        strcpy(str, "Releas/Continuous");
        break;
      case BMC_BUTTON_PRESS_TYPE_RELEASE_ALT:
        strcpy(str, "Releas/2ndPress");
        break;
      default:
        sprintf(str, "%u Inactive", value);
        break;
    }
  }
  static void getPixelColorName(uint8_t value, char* str){
    switch(value){
      case BMC_NONE:
      case BMC_PIXEL_RED:           strcpy(str, "Red"); break;
      case BMC_PIXEL_GREEN:         strcpy(str, "Green"); break;
      case BMC_PIXEL_BLUE:          strcpy(str, "Blue"); break;
      case BMC_PIXEL_YELLOW:        strcpy(str, "Yellow"); break;
      case BMC_PIXEL_MAGENTA:       strcpy(str, "Magenta"); break;
      case BMC_PIXEL_CYAN:          strcpy(str, "Cyan"); break;
      case BMC_PIXEL_ORANGE:        strcpy(str, "Orange"); break;
      case BMC_PIXEL_WHITE:         strcpy(str, "White"); break;
      case BMC_PIXEL_RAINBOW:       strcpy(str, "Rainbow"); break;
      case BMC_PIXEL_RAINBOW_FADE:  strcpy(str, "Rainbow (Fade)"); break;
      default:
        sprintf(str, "%u undefined", value);
        break;
    }
  }
  static void getMagicEncoderColorName(uint8_t value, char* str){
    switch(value){
      case 0:     strcpy(str, "Red"); break;
      case 1:     strcpy(str, "Green"); break;
      case 2:     strcpy(str, "Blue"); break;
      case 3:     strcpy(str, "Magenta"); break;
      case 4:     strcpy(str, "Cyan"); break;
      case 5:     strcpy(str, "Yellow"); break;
      case 6:     strcpy(str, "Rainbow"); break;
      default:
        sprintf(str, "%u undefined", value);
        break;
    }
  }
  static void getMagicEncoderModeName(uint8_t value, char* str){
    switch(value){
      case 0:     strcpy(str, "Dot"); break;
      case 1:     strcpy(str, "Boost/Cut"); break;
      case 2:     strcpy(str, "Wrap"); break;
      case 3:     strcpy(str, "Spread"); break;
      default:
        sprintf(str, "%u undefined", value);
        break;
    }
  }
  static void getMagicEncoderTriggerName(uint8_t value, char* str){
    switch(value){
      case 0:     strcpy(str, "Inactive"); break;
      case 1:     strcpy(str, "Release"); break;
      case 2:     strcpy(str, "Press"); break;
      case 3:     strcpy(str, "Hold"); break;
      case 4:     strcpy(str, "Double Press"); break;
      default:
        sprintf(str, "%u undefined", value);
        break;
    }
  }
  static void getLfoWaveformName(uint8_t value, char* str){
    switch(value){
      case BMC_LFO_SINE:       strcpy(str, "Sine"); break;
      case BMC_LFO_SAW:        strcpy(str, "Saw"); break;
      case BMC_LFO_TRIANGLE:   strcpy(str, "Triangle"); break;
      case BMC_LFO_SQUARE:     strcpy(str, "Square"); break;
      default:
        sprintf(str, "%u undefined", value);
        break;
    }
  }
  static void getLfoNoteDivisionName(uint8_t value, char* str){
    switch(value){
      case BMC_LFO_NOTE_DIV_WHOLE:        strcpy(str, "Whole"); break;
      case BMC_LFO_NOTE_DIV_HALF:         strcpy(str, "Half (1/2)"); break;
      case BMC_LFO_NOTE_DIV_QUARTER:      strcpy(str, "Quarter (1/4)"); break;
      case BMC_LFO_NOTE_DIV_EIGHTH:       strcpy(str, "Eighth (1/8)"); break;
      case BMC_LFO_NOTE_DIV_SIXTEENTH:    strcpy(str, "Sixteenth (1/16)"); break;
      default:
        sprintf(str, "%u undefined", value);
        break;
    }
  }
  static void getSketchByteFormat(char* str, uint8_t n, uint8_t value){
#if BMC_MAX_SKETCH_BYTES > 0
    BMCSketchByteData t = BMCBuildData::getSketchByteData(n);
    // buffer.initialValue = 0;
    // buffer.min = 0;
    // buffer.max = 255;
    // buffer.step = 1;
    // buffer.formatType = BMC_NONE;
    // buffer.formatValue = BMC_NONE;
    // buffer.formatAppend = BMC_NONE;
    uint8_t fType = t.formatType;
    uint8_t fValue = t.formatValue;
    uint8_t fAppend = t.formatAppend;
    char txt[16] = "";

    switch(fAppend){
      case 0: strcpy(txt, ""); break;
      case 1: strcpy(txt, "sec"); break;
      case 2: strcpy(txt, "ms"); break;
      case 3: strcpy(txt, "us"); break;
      case 4: strcpy(txt, "mm"); break;
      case 5: strcpy(txt, "cm"); break;
      case 6: strcpy(txt, "m"); break;
      case 7: strcpy(txt, "%"); break;
      case 8: strcpy(txt, "degrees"); break;
      case 9: strcpy(txt, "bpm"); break;
      case 10: strcpy(txt, "hours"); break;
      case 11: strcpy(txt, "minutes"); break;
      case 12: strcpy(txt, "seconds"); break;
      case 13: strcpy(txt, "days"); break;
      case 14: strcpy(txt, "weeks"); break;
      case 15: strcpy(txt, "hours"); break;
    }
    switch(fType){
      case 0: sprintf(str, "%u %s", value, txt); break;
      case 1: sprintf(str, "%u %s", (value+fValue), txt); break;
      case 2: sprintf(str, "%u %s", (value-fValue), txt); break;
      case 3: sprintf(str, "%u %s", (value*fValue), txt); break;
      case 4: sprintf(str, "%u %s", (value/fValue), txt); break;
      case 5: strcpy(str, (value == 0) ? "Off" : "On"); break;
      default: sprintf(str, "%u", value); break;
    }
#endif
  }
  static bmcStoreEvent getDeviceEventType(bmcStore& store, uint16_t n){
    bmcStoreEvent e;
    if(n > 0 && n <= BMC_MAX_EVENTS_LIBRARY){
      return store.global.events[n-1];
    }
    return e;
  }
  static void strTrim(char * str){
    strTrimHead(str);
    strTrimTail(str);
  }
  static void strTrimHead(char * str){
    // remove spaces at the beginning of a char array
    uint16_t len = strlen(str);
    if(len == 0 || str[0] != 32){
      return;
    }
    char buff[len+1] = "";
    bool skipTrim = false;
    for(uint8_t i = 0, e = 0;i<len;i++){
      if(!skipTrim){
        if(str[i] == 32){
          continue;
        } else if(str[i] == 0){
          break;
        } else {
          skipTrim = true;
        }
      }
      buff[e++] = str[i];
    }
    strcpy(str, buff);
  }
  static void strTrimTail(char * str){
    // remove spaces at end of a char array
    uint16_t len = strlen(str);
    if(len == 0 || str[len-1] != 32){
      return;
    }
    for(int i = len; i --> 0;){
      if(str[i] != 0){
        if(str[i] == 32){
          str[i] = 0;
        } if(str[i] > 32){
          break;
        }
      }
    }
  }
  static void strRemoveSpaces(char * str){
    // trim the end of a char array
    uint16_t len = strlen(str);
    if(len == 0){
      return;
    }
    char buff[len+1] = "";
    for(uint8_t i = 0, e = 0;i<len;i++){
      if(str[i] == 32){
        continue;
      } else if(str[i] == 0){
        break;
      }
      buff[e++] = str[i];
    }
    strcpy(str, buff);
  }
  static void strShorten(char * str, bool removeSpaces=false){
    // removes all vowels as well
    // if the first character of the string is a vowel leave it
    // removes all spaces from string if @removeSpaces is true
    uint16_t len = strlen(str);
    if(len < 5){
      return;
    }
    char buff[len+1] = "";
    for(uint8_t i = 0, e = 0 ; i < len ; i++){
      if((removeSpaces && str[i] == 32) || (i>0 && (str[i] == 65 || str[i] == 69 || str[i] == 73 ||
         str[i] == 79 || str[i] == 85 || str[i] == 97 || str[i] == 101 ||
         str[i] == 105 || str[i] == 111 || str[i] == 117))
      ){
        continue;
      } else if(str[i] == 0){
        break;
      }
      buff[e++] = str[i];
    }
    if(strlen(buff)>0){
      strcpy(str, buff);
    }
  }
  
  static void getBankLetter(uint8_t n, char* buff){
    strcpy(buff, "");
    if(n < 32){
      const char alph[32] = BMC_ALPHABET;
      sprintf(buff, "%c", alph[n]);
    }
  }
  static uint16_t toPresetIndex(uint8_t t_bank, uint8_t t_preset){
    uint16_t p = (t_bank << BMC_PRESET_BANK_MASK) | (t_preset & (BMC_MAX_PRESETS_PER_BANK-1));
    if(p >= BMC_MAX_PRESETS){
      return 0;
    }
    return p;
  }

  static void formatKnobValue(BMCDataContainer d, uint16_t t_value, char * buff){
    if(d.type == BMC_EVENT_TYPE_BANK){
      char letter[3] = "";
      BMCTools::getBankLetter(t_value, letter);
      sprintf(buff, "%s", letter);
    } else if(d.type == BMC_EVENT_TYPE_PRESET && d.byteC == 1){
      char letter[3] = "";
      // all presets
      BMCTools::getPresetLabelNoName(t_value, letter, d.offset);
      sprintf(buff, "%s", letter);
    } else {
      sprintf(buff, "%u", t_value+(d.useOffset ? d.offset : 0));
    }
  }
  static void makePlural(char * buff){
    uint8_t strL = strlen(buff);
    char lastChar = buff[strL-1];
    if(lastChar!='s' && lastChar!='x' && lastChar!='p'){
      buff[strL] = 's';
    }
  }



  
  static void getPresetLabelNoName(uint8_t t_bank, uint8_t t_preset, char * str, bool offset=false){
    uint16_t t_presetAndBank = toPresetIndex(t_bank, t_preset);
    getPresetLabelNoName(t_presetAndBank, str, offset);
  }
  static void getPresetLabelNoName(uint16_t t_presetAndBank, char * str, bool offset=false){
    if(t_presetAndBank < BMC_MAX_PRESETS){
#if BMC_MAX_PRESETS > 0
      char bankStr[2] = "";
      getBankLetter(getBankFromPresetIndex(t_presetAndBank), bankStr);
      sprintf(str, "%s%u", bankStr, getPresetInBankFromPresetIndex(t_presetAndBank)+offset);
#endif
    }
  }
  static uint8_t getBankFromPresetIndex(uint16_t t_presetAndBank){
    return ((t_presetAndBank >> BMC_PRESET_BANK_MASK) & 0x1F);
    
  }
  static uint8_t getPresetInBankFromPresetIndex(uint16_t t_presetAndBank){
    return (t_presetAndBank & (BMC_MAX_PRESETS_PER_BANK-1));
  }



  static void getPresetLabel(uint8_t t_bank, uint8_t t_preset, char * str, bmcStoreGlobal& t_store){
    uint16_t t_presetAndBank = toPresetIndex(t_bank, t_preset);
    if(t_presetAndBank < BMC_MAX_PRESETS){
#if BMC_MAX_PRESETS > 0
      bmcName_t n = t_store.presets[t_presetAndBank].name;
      char name[BMC_MAX_NAMES_LENGTH] = "";
      char bankStr[2] = "";
      getBankLetter(t_bank, bankStr);
      if(n!=0){
        strcpy(name, t_store.names[n].name);
      }
      sprintf(str, "%s%u%s", bankStr, t_preset, name);
#endif
    }
  }
  static void getPresetLabel(uint16_t t_presetAndBank, char * str, bmcStoreGlobal& t_store){
    if(t_presetAndBank < BMC_MAX_PRESETS){
#if BMC_MAX_PRESETS > 0
      uint8_t t_bank = (t_presetAndBank >> BMC_PRESET_BANK_MASK) & 0x1F;
      uint8_t t_preset = t_presetAndBank & (BMC_MAX_PRESETS_PER_BANK-1);
      bmcName_t n = t_store.presets[t_presetAndBank].name;
      char name[BMC_MAX_NAMES_LENGTH] = "";
      char bankStr[2] = "";
      getBankLetter(t_bank, bankStr);
      if(n!=0){
        strcpy(name, t_store.names[n].name);
      }
      sprintf(str, "%s%u%s", bankStr, t_preset, name);
#endif
    }
  }
  static bool isValidRelayEvent(uint8_t t_type){
    switch(t_type){
      case BMC_EVENT_TYPE_MIDI_PROGRAM_CHANGE:
      case BMC_EVENT_TYPE_MIDI_CONTROL_CHANGE:
      case BMC_EVENT_TYPE_LAYER:
      case BMC_EVENT_TYPE_PRESET:
        return true;
    }
    return false;
  }
  static bool isLedBlinkAllowed(uint8_t t_type){
    switch(t_type){
      //case BMC_LED_EVENT_TYPE_MIDI_ACTIVITY:
      //case BMC_LED_EVENT_TYPE_CLOCK_SYNC:
      case BMC_EVENT_TYPE_SYSTEM_STATUS:
      case BMC_EVENT_TYPE_SYSTEM_MIDI_ACTIVITY:
      case BMC_EVENT_TYPE_SYSTEM_CLOCK:
      case BMC_EVENT_TYPE_SYSTEM_CLOCK_TAP:
        return false;
    }
    return true;
  }
  static uint8_t parseEventType(uint8_t t_type){
    // this code will take an event type from buttons, encoders, leds, pots
    // and determine what type of event it is.
    // all hardware events can have standard midi message statuses as their type
    // those event types also will include the channel for the midi message
    // if it's a Channel Status(Program, Control, etc).
    // in that case we will return only the 4 MSB bits so a switch statement
    // so that the channel can be ignored
    // For system common messages like System Reset, Clock Start, Stop, etc.
    // there's no need to remove the 4 LSB bits since they are part of the status
    // so if the type is between 128 and 239 it's a standard MIDI message
    // if it's higher than 239 it's a system common
    // otherwise if it's lessage than 128 it's a custom event by BMC
    // if the value is 127 (0x7F) it's a custom event type for Sketch use
    return (t_type > 0x7F && t_type < 0xF0) ? (t_type & 0xF0) : t_type;
  }
  static bool matchPort(uint8_t source, uint8_t target){
    return BMC_MATCH_PORT(source, target);
  }
  static float getPercentage(uint16_t value, uint8_t percentage=1){
    return ((((float)value) / 100) * (percentage==0?1:percentage));
  }
  static bool isStatusByte(uint8_t s){
    return (s > 0x7F) && !isUndefinedMidi(s);
  }
  static bool isOneByteMidiMessage(uint8_t s){
    switch(BMC_GET_MIDI_STATUS(s)){
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
    //return (s == 0xF1 || s == 0xF7 || (s >= 0xF4 && s <= 0xFF));
  }
  static bool isTwoByteMidiMessage(uint8_t s){
    switch(BMC_GET_MIDI_STATUS(s)){
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
      case BMC_MIDI_SONG_SELECT:
      case BMC_MIDI_PROGRAM_CHANGE:
        return true;
    }
    return false;
    //return (s == 0xF3 || (s >= 0xC0 && s <= 0xDF));
  }
  static bool isThreeByteMidiMessage(uint8_t s){
    switch(BMC_GET_MIDI_STATUS(s)){
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
    //return (s == 0xF2 || (s >= 0x80 && s <= 0xBF) || (s >= 0xE0 && s <= 0xEF));
  }
  static bool isRunningStatusMidiMessage(uint8_t s){
    return (s>=0x80 && s<=0xEF);
  }
  bool isValidMidiStatus(uint8_t s){
    return (s > 127) && !isUndefinedMidi(s);
  }
  bool isMidiStatus(uint8_t s){
    return isValidMidiStatus(s);
  }
  bool isMidiChannelStatus(uint8_t s){
    return (s > 0x7F && s < 0xF0);
  }
  bool isMidiSystemCommonStatus(uint8_t s){
    return (s >= 0xF0 && s <= 0xF7);
  }
  bool isMidiSystemRealTimeStatus(uint8_t s){
    return (s >= 0xF8);
  }
  static bool isUndefinedMidi(uint8_t s){
    switch(s){
      case 0xF4:
      case 0xF5:
      case 0xF7:
      case 0xFD:
        return true;
    }
    return false;
  }
  // NUMBER SCROLL
  static uint16_t numberScroll(uint16_t amount, bool scrollUp,
                                bool endless, uint16_t value,
                                uint16_t min, uint16_t max){
    if(scrollUp){
      return (endless) ? endlessNumberScrollUp(amount,value,min,max) : numberScrollUp(amount,value,min,max);
    }
    return (endless) ? endlessNumberScrollDown(amount,value,min,max) : numberScrollDown(amount,value,min,max);
  }
  static uint16_t endlessNumberScrollUp(uint16_t amount, uint16_t value,
                                        uint16_t min, uint16_t max){
    long newValue = (value+amount);
    return (newValue > max || newValue < min) ? min : newValue;
  }
  static uint16_t endlessNumberScrollDown(uint16_t amount, uint16_t value,
                                          uint16_t min, uint16_t max){
    long newValue = (value-amount);
    return (newValue < min) ? max : newValue;
  }
  static uint16_t numberScrollUp(uint16_t amount, uint16_t value,
                                  uint16_t min, uint16_t max){
    long newValue = (value+amount);
    if(newValue>max){
      return max;
    } else if(newValue<min){
      return min;
    }
    return newValue;
  }
  static uint16_t numberScrollDown(uint16_t amount, uint16_t value,
                                    uint16_t min, uint16_t max){
    long newValue = (value-amount);
    return (newValue < min) ? min : newValue;
  }
  // an Endless SOS of all LEDs, use for stopping BMC
  static void sos(){
    while(1);
    /*
    #if BMC_TOTAL_LEDS == 0
      while(1);
    #else
    uint8_t items[3];
    uint8_t totalLeds = 0;

    #if BMC_MAX_LEDS > 0
    for(uint8_t i = 0; i < BMC_MAX_LEDS; i++){
      items[totalLeds++] = BMCBuildData::getLedPin(i);
      pinMode(BMCBuildData::getLedPin(i),OUTPUT);
      break;
    }
    #endif
    #if BMC_MAX_GLOBAL_LEDS > 0
    for(uint8_t i = 0; i < BMC_MAX_GLOBAL_LEDS; i++){
      items[totalLeds++] = BMCBuildData::getGlobalLedPin(i);
      pinMode(BMCBuildData::getGlobalLedPin(i),OUTPUT);
      break;
    }
    #endif
    delay(500);
    while(1){
      for(uint8_t i = 0; i < totalLeds; i++){
        digitalWrite(items[i], HIGH);
        delay(250);
        digitalWrite(items[i], LOW);
        delay(250);
      }
    }
    #endif
    */
  }
};

#endif
