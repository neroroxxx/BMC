/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license. See LICENSE file in the project root for full license information.
*/
#include <Arduino.h>

#if !defined(BMC_CONFIG_H)
  #error "config.h file is required for BMC."
#endif

#ifndef BMC_DEF_H
#define BMC_DEF_H

/*
  t41 __IMXRT1062__ undergoing testing - NO CLICK TRACK
  t40 __IMXRT1062__ tested & supported - NO CLICK TRACK
  t36 __MK66FX1M0__ tested & supported - NO CLICK TRACK
  t35 __MK64FX512__ not tested - supported?
  t32 __MK20DX256__ tested & supported ***
  t31 __MK20DX256__ not tested - supported?
  t30 __MK20DX128__ not tested - NOT supported
  tLC __MKL26Z64__ not tested - supported? - NO CLICK TRACK

  #define BMC_TEENSY_MODEL 41 (4.1)
  #define BMC_TEENSY_MODEL 40 (4.0)
  #define BMC_TEENSY_MODEL 36 (3.6)
  #define BMC_TEENSY_MODEL 35 (3.5)
  #define BMC_TEENSY_MODEL 32 (3.2)
  #define BMC_TEENSY_MODEL 10 (LC)

*/
#if defined(__arm__) && defined(CORE_TEENSY)
  #if defined(ARDUINO_TEENSY41)
    // Teensy 4.0
    // __IMXRT1062__
    #define BMC_TEENSY_MODEL 41
    #define BMC_TEENSY_MODEL_STR "4.1"
    #define BMC_TEENSY_RAM_SIZE 1024000
    #define BMC_TEENSY_EEPROM_SIZE 4284
    #define BMC_TEENSY_HAS_USB_HOST true
    #define BMC_TEENSY_HAS_SD_CARD true
    #define BMC_TEENSY_TOTAL_SERIAL_PORTS 8
    #define BMC_TEENSY_TOTAL_DIGITAL_PINS 42
    #define BMC_TEENSY_TOTAL_PWM_PINS 27
    #define BMC_TEENSY_TOTAL_ANALOG_PINS 18

  #elif defined(ARDUINO_TEENSY40)
      // Teensy 4.0
      // __IMXRT1062__
      #define BMC_TEENSY_MODEL 40
      #define BMC_TEENSY_MODEL_STR "4.0"
      #define BMC_TEENSY_RAM_SIZE 1024000
      #define BMC_TEENSY_EEPROM_SIZE 1080
      #define BMC_TEENSY_HAS_USB_HOST true
      #define BMC_TEENSY_HAS_SD_CARD true
      #define BMC_TEENSY_TOTAL_SERIAL_PORTS 7
      #define BMC_TEENSY_TOTAL_DIGITAL_PINS 40
      #define BMC_TEENSY_TOTAL_PWM_PINS 31
      #define BMC_TEENSY_TOTAL_ANALOG_PINS 14

  #elif defined(ARDUINO_TEENSY36)
    // Teensy 3.6
    // __MK66FX1M0__
    #define BMC_TEENSY_MODEL 36
    #define BMC_TEENSY_MODEL_STR "3.6"
    #define BMC_TEENSY_RAM_SIZE 262144
    #define BMC_TEENSY_EEPROM_SIZE 4096
    #define BMC_TEENSY_HAS_USB_HOST true
    #define BMC_TEENSY_HAS_SD_CARD true
    #define BMC_TEENSY_TOTAL_SERIAL_PORTS 6
    #define BMC_TEENSY_TOTAL_DIGITAL_PINS 58
    #define BMC_TEENSY_TOTAL_PWM_PINS 22
    #define BMC_TEENSY_TOTAL_ANALOG_PINS 25

  #elif defined(ARDUINO_TEENSY35)
    // Teensy 3.5
    // __MK64FX512__
    #define BMC_TEENSY_MODEL 35
    #define BMC_TEENSY_MODEL_STR "3.5"
    #define BMC_TEENSY_RAM_SIZE 262144
    #define BMC_TEENSY_EEPROM_SIZE 4096
    #define BMC_TEENSY_HAS_USB_HOST false
    #define BMC_TEENSY_HAS_SD_CARD true
    #define BMC_TEENSY_TOTAL_SERIAL_PORTS 6
    #define BMC_TEENSY_TOTAL_DIGITAL_PINS 58
    #define BMC_TEENSY_TOTAL_PWM_PINS 20
    #define BMC_TEENSY_TOTAL_ANALOG_PINS 27

  #elif defined(ARDUINO_TEENSY32)
    // Teensy 3.2 / 3.1
    // __MK20DX256__
    #define BMC_TEENSY_MODEL 32
    #define BMC_TEENSY_MODEL_STR "3.2"
    #define BMC_TEENSY_RAM_SIZE 65536
    #define BMC_TEENSY_EEPROM_SIZE 2048
    #define BMC_TEENSY_HAS_USB_HOST false
    #define BMC_TEENSY_HAS_SD_CARD false
    #define BMC_TEENSY_TOTAL_SERIAL_PORTS 3
    #define BMC_TEENSY_TOTAL_DIGITAL_PINS 33
    #define BMC_TEENSY_TOTAL_PWM_PINS 12
    #define BMC_TEENSY_TOTAL_ANALOG_PINS 21

  #elif defined(ARDUINO_TEENSYLC)
    // Teensy LC
    // __MKL26Z64__
    #define BMC_TEENSY_MODEL 10
    #define BMC_TEENSY_MODEL_STR "LC"
    #define BMC_TEENSY_RAM_SIZE 8192
    #define BMC_TEENSY_EEPROM_SIZE 128
    #define BMC_TEENSY_HAS_USB_HOST false
    #define BMC_TEENSY_HAS_SD_CARD false
    #define BMC_TEENSY_TOTAL_SERIAL_PORTS 3
    #define BMC_TEENSY_TOTAL_DIGITAL_PINS 27
    #define BMC_TEENSY_TOTAL_PWM_PINS 10
    #define BMC_TEENSY_TOTAL_ANALOG_PINS 13

  #else
    #error "BMC is only Compatible with Teensy LC/3.2/3.5/3.6/4.0/4.1"
  #endif

#else
  #error "BMC is only Compatible with Teensy LC/3.2/3.5/3.6/4.0/4.1"
#endif

#if !defined(BMC_TEENSY_MODEL)
  #error "BMC is only Compatible with Teensy LC/3.2/3.5/3.6/4.0/4.1"
#endif

// MIDI STATUS, keep them here as they are used throut BMC
// *************** Voice/Channel ***************
#define BMC_MIDI_NOTE_OFF 0x80 // 3 bytes including status
#define BMC_MIDI_NOTE_ON 0x90 // 3 bytes
#define BMC_MIDI_AFTER_TOUCH_POLY 0xA0 // 3 bytes
#define BMC_MIDI_CONTROL_CHANGE 0xB0 // 3 bytes
#define BMC_MIDI_PROGRAM_CHANGE 0xC0 // 2 bytes
#define BMC_MIDI_AFTER_TOUCH 0xD0 // 3 bytes
#define BMC_MIDI_PITCH_BEND 0xE0 // 3 bytes
// *************** System Exclusive ***************
#define BMC_MIDI_SYSTEM_EXCLUSIVE 0xF0 // variable bytes
// *************** System Common ***************
#define BMC_MIDI_TIME_CODE_QUARTER_FRAME 0xF1 // 2 bytes
#define BMC_MIDI_SONG_POSITION 0xF2 // 3 bytes
#define BMC_MIDI_SONG_SELECT 0xF3 // 2 bytes
//0xF4 undefined
//0xF5 undefined
#define BMC_MIDI_TUNE_REQUEST 0xF6 // 1 byte
//0xF7 undefined

// *************** System Real Time ***************
#define BMC_MIDI_RT_CLOCK 0xF8 // 1 byte
//0xF9 undefined
#define BMC_MIDI_RT_START 0xFA // 1 byte
#define BMC_MIDI_RT_CONTINUE 0xFB // 1 byte
#define BMC_MIDI_RT_STOP 0xFC // 1 byte
//0xFD undefined
#define BMC_MIDI_RT_ACTIVE_SENSE 0xFE // 1 byte
#define BMC_MIDI_RT_SYSTEM_RESET 0xFF // 1 byte

#define BMC_MASK_32 0xFFFFFFFF
#define BMC_MASK_16 0xFFFFFFFF


// Soft Reboot the Teensy 3.x
// https://forum.pjrc.com/threads/24304-_reboot_Teensyduino%28%29-vs-_restart_Teensyduino%28%29?highlight=teensy+reboot
#define CPU_RESTART_ADDR (uint32_t *) 0xE000ED0C
#define CPU_RESTART_VAL 0x5FA0004
#define CPU_RESTART() (*CPU_RESTART_ADDR = CPU_RESTART_VAL)

// Stop running BMC, this happens is something was NOT properly configured
// all LEDs will blink
#define BMC_HALT() BMC_ERROR(\
  "BMC will stop responding",\
  "You MUST update your sketch and/or config file and reupload it."\
);BMCTools::sos();


// Macros
#ifndef digitalToggle
  #define digitalToggle(pin) digitalWriteFast(pin, !digitalReadFast(pin))
#endif

#ifndef digitalHigh
  #define digitalHigh(pin) digitalWriteFast(pin, HIGH)
#endif

#ifndef digitalLow
  #define digitalLow(pin) digitalWriteFast(pin, LOW)
#endif

#ifndef digitalIsHigh
  #define digitalIsHigh(pin) (digitalReadFast(pin)==HIGH)
#endif

#ifndef digitalIsLow
  #define digitalIsLow(pin) (digitalReadFast(pin)==LOW)
#endif

#define BMC_IS_EVEN(n) ((n % 2 == 0))
#define BMC_IS_ODD(n)  ((n % 2 != 0))
#define BMC_GET_MIDI_STATUS(value) ( (uint8_t) ((value&0xFF)<0xF0) ? (value & 0xF0) : value )
#define BMC_GET_MIDI_CHANNEL(value) ((uint8_t)(value & 0x0F))
#define BMC_TO_MIDI_CHANNEL(value) ((uint8_t)(value & 0x0F)+1)
#define BMC_MATCH_PORT(source, target) ((source & target) > 0)

// MIDI
#define BMC_IS_NOTE_OFF(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_NOTE_OFF)
#define BMC_IS_NOTE_ON(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_NOTE_ON)
#define BMC_IS_AFTER_TOUCH_POLY(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_AFTER_TOUCH_POLY)
#define BMC_IS_CONTROL_CHANGE(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_CONTROL_CHANGE)
#define BMC_IS_PROGRAM_CHANGE(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_PROGRAM_CHANGE)
#define BMC_IS_AFTER_TOUCH(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_AFTER_TOUCH)
#define BMC_IS_PITCH_BEND(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_PITCH_BEND)
#define BMC_IS_SYSTEM_EXCLUSIVE(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_SYSTEM_EXCLUSIVE)
#define BMC_IS_SYSEX(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_SYSTEM_EXCLUSIVE)
#define BMC_IS_TIME_CODE_QUARTER_FRAME(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_TIME_CODE_QUARTER_FRAME)
#define BMC_IS_TCQF(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_TIME_CODE_QUARTER_FRAME)
#define BMC_IS_SONG_POSITION(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_SONG_POSITION)
#define BMC_IS_SONG_SELECT(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_SONG_SELECT)
#define BMC_IS_TUNE_REQUEST(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_TUNE_REQUEST)
#define BMC_IS_CLOCK(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_RT_CLOCK)
#define BMC_IS_START(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_RT_START)
#define BMC_IS_CONTINUE(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_RT_CONTINUE)
#define BMC_IS_STOP(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_RT_STOP)
#define BMC_IS_ACTIVE_SENSE(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_RT_ACTIVE_SENSE)
#define BMC_IS_SYSTEM_RESET(s) (BMC_GET_MIDI_STATUS(s)==BMC_MIDI_RT_SYSTEM_RESET)
#define BMC_IS_UNDEFINED_MIDI(s) (s==0xF4&&s==0xF5&&s==0xF7&&s==0xF9&&s==0xFD)


#define BMC_MIDI_GET_WORD(byteIndex,item) ((byteIndex>0) ? ((item >> (byteIndex*7)) & 0x7F) : (item & 0x7F))
#define BMC_CLEAR_BITS(target, mask, shift) (target &= ~((mask) << shift))
#define BMC_WRITE_BITS(target, value, mask, shift) (BMC_CLEAR_BITS(target, mask, shift) |= ((value & mask) << shift))

#define BMC_MIDI_WORDS_TO_INT_MACRO(_1,_2,_3,_4,_5,NAME,...) NAME
#define BMC_MIDI_WORDS_TO_INT(...) BMC_MIDI_WORDS_TO_INT_MACRO(__VA_ARGS__,BMC_MIDI_WORDS_TO_INT5, BMC_MIDI_WORDS_TO_INT4, BMC_MIDI_WORDS_TO_INT3, BMC_MIDI_WORDS_TO_INT2)(__VA_ARGS__)
#define BMC_MIDI_WORDS_TO_INT2(a,b)        ((b & 0x7F) | ((a & 0x7F)<<7))
#define BMC_MIDI_WORDS_TO_INT3(a,b,c)      ((c & 0x7F) | ((b & 0x7F)<<7) | ((a & 0x7F)<<14))
#define BMC_MIDI_WORDS_TO_INT4(a,b,c,d)    ((d & 0x7F) | ((c & 0x7F)<<7) | ((b & 0x7F)<<14) | ((a & 0x7F)<<21))
#define BMC_MIDI_WORDS_TO_INT5(a,b,c,d,e)  ((e & 0x7F) | ((d & 0x7F)<<7) | ((c & 0x7F)<<14) | ((b & 0x7F)<<21) | ((a & 0x7F)<<28))

#define BMC_MIDI_ARRAY_TO_8BITS(i,a)    (BMC_MIDI_WORDS_TO_INT(a[i],a[i+1]))
#define BMC_MIDI_ARRAY_TO_16BITS(i,a)   (BMC_MIDI_WORDS_TO_INT(a[i],a[i+1],a[i+2]))
#define BMC_MIDI_ARRAY_TO_32BITS(i,a)   (BMC_MIDI_WORDS_TO_INT(a[i],a[i+1],a[i+2],a[i+3],a[i+4]))

#define BMC_MIDI_ARRAY_TO_8BITS_LSB_FIRST(i,a)    (BMC_MIDI_WORDS_TO_INT(a[i+1],a[i]))
#define BMC_MIDI_ARRAY_TO_16BITS_LSB_FIRST(i,a)   (BMC_MIDI_WORDS_TO_INT(a[i+2],a[i+1],a[i]))
#define BMC_MIDI_ARRAY_TO_32BITS_LSB_FIRST(i,a)   (BMC_MIDI_WORDS_TO_INT(a[i+4],a[i+3],a[i+2],a[i+1],a[i]))

#define BMC_CALC_TOLERANCE(orignalVal, newVal, tol) ((orignalVal<(newVal-tol)) || (orignalVal>(newVal+tol)))

#define BMC_STR_MATCH(str1,str2)((strcmp(str1,str2)==0))

// get the value of the bits in the range
// for example value 231 (binary 11100111) if you want to get value of bits 4, 5 and 6
// you would do BMC_GET_BITS_VALUE(231, 4, 6) this will return 6, because
// bits 4, 5, 7 = 1"110"0111 = 110 which is the number 6
#define BMC_GET_BITS_VALUE(value, fromBit, toBit) (value >> fromBit) & (pow(2, (toBit-fromBit)+1)-1)

// BMC_GET_BYTE, takes a single byte from a larger int
// where the byteIndex is the LSB index.
// example: BMC_GET_BYTE(0,0x1A2B3C) = 0x3C
// example: BMC_GET_BYTE(1,0x1A2B3C) = 0x2B
// example: BMC_GET_BYTE(2,0x1A2B3C) = 0x1A
#define BMC_GET_BYTE(byteIndex,item) ((byteIndex>0) ? ((item >> (byteIndex*8)) & 0xFF) : (item & 0xFF))

// BMC_MERGE_BYTES, merges mutiple bytes into a single int
// where the first argument becomes the MSB
// example: BMC_MERGE_BYTES(0x1A,0x2B,0x3C) = 0x1A2B3C
#define BMC_MERGE_BYTES_MACRO(_1,_2,_3,_4,_5,NAME,...) NAME
#define BMC_MERGE_BYTES(...) BMC_MERGE_BYTES_MACRO(__VA_ARGS__,BMC_MERGE_BYTES5,BMC_MERGE_BYTES4,BMC_MERGE_BYTES3,BMC_MERGE_BYTES2)(__VA_ARGS__)
#define BMC_MERGE_BYTES2(a,b)        ((b & 0xFF) | ((a & 0xFF)<<8))
#define BMC_MERGE_BYTES3(a,b,c)      ((c & 0xFF) | ((b & 0xFF)<<8) | ((a & 0xFF)<<16))
#define BMC_MERGE_BYTES4(a,b,c,d)    ((d & 0xFF) | ((c & 0xFF)<<8) | ((b & 0xFF)<<16) | ((a & 0xFF)<<24))

// Supported chipsets for Mux In
#define BMC_MUX_IN_CHIPSET_OTHER 1
#define BMC_MUX_IN_CHIPSET_MCP2301X 2
#define BMC_MUX_IN_CHIPSET_74HC165 3

// Supported chipsets for Mux In Analog
#define BMC_MUX_IN_ANALOG_CHIPSET_OTHER 1
#define BMC_MUX_IN_ANALOG_CHIPSET_74HC4067 2
#define BMC_MUX_IN_ANALOG_CHIPSET_74HC4051 3

// Check that all pins in Config are set properly
#include <utility/BMC-ConfigCheck.h>

// Debug Macros
#include <utility/BMC-Debug.h>

/*
  GLOBAL
*/
#define BMC_NONE    0
#define BMC_NULL    0
#define BMC_INVALID 0
#define BMC_IGNORE  0

#define BMC_EQUAL_TO          1
#define BMC_MORE_OR_EQUAL_TO  2
#define BMC_LESS_OR_EQUAL_TO  3
#define BMC_NOT_EQUAL_TO      4

// used for number scrolling
#define BMC_SCROLL_DOWN 0
#define BMC_SCROLL_UP 1
#define BMC_SCROLL_LIMITED 0
#define BMC_SCROLL_ENDLESS 1

// for menu
#define BMC_MENU_ENTER    1
#define BMC_MENU_SELECT   2
#define BMC_MENU_BACK     3
#define BMC_MENU_EXIT     4
#define BMC_MENU_UP       5
#define BMC_MENU_DOWN     6
#define BMC_MENU_RIGHT    7
#define BMC_MENU_LEFT     8
#define BMC_MENU_INC      9
#define BMC_MENU_DEC      10
#define BMC_MENU_SAVE     11

// ID for BMC Elements
#define BMC_ITEM_ID_PAGE 1
#define BMC_ITEM_ID_BUTTON 2
#define BMC_ITEM_ID_GLOBAL_BUTTON 3
#define BMC_ITEM_ID_LED 4
#define BMC_ITEM_ID_GLOBAL_LED 5
#define BMC_ITEM_ID_ENCODER 6
#define BMC_ITEM_ID_GLOBAL_ENCODER 7
#define BMC_ITEM_ID_POT 8
#define BMC_ITEM_ID_GLOBAL_POT 9
#define BMC_ITEM_ID_PWM_LED 10
#define BMC_ITEM_ID_RGB_PIXEL 11
#define BMC_ITEM_ID_PIXEL 12
#define BMC_ITEM_ID_NL_RELAY 13
#define BMC_ITEM_ID_L_RELAY 14
#define BMC_ITEM_ID_LIBRARY 15
#define BMC_ITEM_ID_PRESET 16
#define BMC_ITEM_ID_CUSTOM_SYSEX 17
#define BMC_ITEM_ID_TRIGGER 18
#define BMC_ITEM_ID_TEMPO_TO_TAP 19
#define BMC_ITEM_ID_SKETCH_BYTES 20
#define BMC_ITEM_ID_STRING_LIBRARY 21
#define BMC_ITEM_ID_SETLIST 22
#define BMC_ITEM_ID_SETLIST_SONG 23




#define BMC_ITEM_ID_MIDI_PROGRAM BMC_MIDI_PROGRAM_CHANGE
#define BMC_ITEM_ID_MIDI_CONTROL BMC_MIDI_CONTROL_CHANGE
#define BMC_ITEM_ID_MIDI_NOTE_ON BMC_MIDI_NOTE_ON
#define BMC_ITEM_ID_MIDI_NOTE_OFF BMC_MIDI_NOTE_OFF
#define BMC_ITEM_ID_MIDI_PITCH_BEND BMC_MIDI_PITCH_BEND
#define BMC_ITEM_ID_MIDI_CLOCK BMC_MIDI_RT_CLOCK


// Active Sense Commands
#define BMC_ACTIVE_SENSE_STOP 0
#define BMC_ACTIVE_SENSE_START 1
#define BMC_ACTIVE_SENSE_TOGGLE 2

// Relay Definitions

#define BMC_RELAY_NO 0
#define BMC_RELAY_NC 1
#define BMC_RELAY_TOGGLE 2

#define BMC_RELAY_OPEN BMC_RELAY_NO
#define BMC_RELAY_CLOSE BMC_RELAY_NC
#define BMC_RELAY_CLOSED BMC_RELAY_NC

#define BMC_RELAY_RESET BMC_RELAY_NO
#define BMC_RELAY_SET BMC_RELAY_NC


// Stopwatch commands
#define BMC_STOPWATCH_CMD_STOP 0
#define BMC_STOPWATCH_CMD_START 1
#define BMC_STOPWATCH_CMD_RESET 2
#define BMC_STOPWATCH_CMD_TOGGLE 3
#define BMC_STOPWATCH_CMD_TOGGLE_RESET 4

// Click Track Commands
#define BMC_CLICK_TRACK_MUTE 0
#define BMC_CLICK_TRACK_UNMUTE 1
#define BMC_CLICK_TRACK_MUTE_TOGGLE 2
#define BMC_CLICK_TRACK_FREQ_INCREASE 3
#define BMC_CLICK_TRACK_FREQ_DECREASE 4
#define BMC_CLICK_TRACK_LEVEL_INCREASE 5
#define BMC_CLICK_TRACK_LEVEL_DECREASE 6

// Port Bits, the index of each bit that specifies what port to send to
#define BMC_MIDI_PORT_USB_BIT       0
#define BMC_MIDI_PORT_SERIAL_A_BIT  1
#define BMC_MIDI_PORT_SERIAL_B_BIT  2
#define BMC_MIDI_PORT_SERIAL_C_BIT  3
#define BMC_MIDI_PORT_SERIAL_D_BIT  4
#define BMC_MIDI_PORT_HOST_BIT      5
#define BMC_MIDI_PORT_BLE_BIT       6

// USED TO "OR" PORTS
#define BMC_USB       B00000001 // 0x01 (1)
#define BMC_SERIAL_A  B00000010 // 0x02 (2)
#define BMC_SERIAL_B  B00000100 // 0x04 (4)
#define BMC_SERIAL_C  B00001000 // 0x08 (8)
#define BMC_SERIAL_D  B00010000 // 0x10 (16)
#define BMC_HOST      B00100000 // 0x20 (32)
#define BMC_BLE       B01000000 // 0x40 (64)

// use to send to all ports
#define BMC_ALL_PORTS       127

// use to send to Port Presets
#define BMC_PORTP_0     B1000000 //128
#define BMC_PORTP_1     B1000000 //129
#define BMC_PORTP_2     B1000001 //130
#define BMC_PORTP_3     B1000001 //131
#define BMC_PORTP_4     B1000010 //132
#define BMC_PORTP_5     B1000010 //133
#define BMC_PORTP_6     B1000011 //134
#define BMC_PORTP_7     B1000011 //135
#define BMC_PORTP_8     B1000100 //136
#define BMC_PORTP_9     B1000100 //137
#define BMC_PORTP_10    B1000101 //138
#define BMC_PORTP_11    B1000101 //139
#define BMC_PORTP_12    B1000110 //140
#define BMC_PORTP_13    B1000110 //141
#define BMC_PORTP_14    B1000111 //142
#define BMC_PORTP_15    B1000111 //143



#define BMC_ACTIVE 1
#define BMC_COMPLETE 2

// sketch byte names max length
// DO NOT CHANGE
#define BMC_NAME_LEN_SKETCH_BYTES 21

// the minimun length of sysex messages used by the editor
// DO NOT CHANGE
#define BMC_EDITOR_SYSEX_MIN_LENGTH 11

// part of your config file
#ifndef BMC_EDITOR_SYSEX_ID
  #define BMC_EDITOR_SYSEX_ID 0x7D7D7D
#endif

// can be overloaded by config, must have a value
#ifndef BMC_MIDI_SYSEX_SIZE
  #define BMC_MIDI_SYSEX_SIZE 128
#endif

// can be overloaded by config, must have a value
#ifndef BMC_DELAY_SYSEX_ON_SERIAL
  #define BMC_DELAY_SYSEX_ON_SERIAL 0
#endif

// Custom SysEx Commands
#define BMC_CUSTOM_SYSEX_SEND_A 0
#define BMC_CUSTOM_SYSEX_SEND_B 1
#define BMC_CUSTOM_SYSEX_SEND_MERGE 2

// can be overloaded by config, must have a value
// in ms, how long Latching relays should have the pin set HIGH
#ifndef BMC_L_RELAY_HOLD_TIME
  #define BMC_L_RELAY_HOLD_TIME 15
#endif

// can be overloaded by config, must have a value
// in ms, when relays are in Momentary mode this determines how long they will
// stay in CLOSED (SET) state before going back to OPEN (RESET)
#ifndef BMC_RELAYS_MOMENTARY_HOLD
  #define BMC_RELAYS_MOMENTARY_HOLD 50
#endif

// can be overloaded by config, must have a value
#ifndef BMC_BUTTON_DEBOUNCE_TIME
  #define BMC_BUTTON_DEBOUNCE_TIME 50
#endif

// can be overloaded by config, must have a value
#ifndef BMC_BUTTON_DOUBLE_PRESS_THRESHOLD
  #define BMC_BUTTON_DOUBLE_PRESS_THRESHOLD 250
#endif

// can be overloaded by config, must have a value
#ifndef BMC_BUTTON_DUAL_PRESS_TIMEOUT
  #define BMC_BUTTON_DUAL_PRESS_TIMEOUT 75
#endif


// can be overloaded by config, must have a value
#ifndef BMC_LED_PULSE_TIMEOUT
  #define BMC_LED_PULSE_TIMEOUT 150
#endif

// can be overloaded by config, must have a value
#ifndef BMC_LED_PWM_DIM_VALUE
  #define BMC_LED_PWM_DIM_VALUE 1
#endif

// can be overloaded by config, must have a value
#ifndef BMC_LED_PWM_MAX_VALUE
  #define BMC_LED_PWM_MAX_VALUE 256
#endif

#if BMC_LED_PWM_MAX_VALUE == 0 || BMC_LED_PWM_MAX_VALUE == 255
  #undef BMC_LED_PWM_MAX_VALUE
  #define BMC_LED_PWM_MAX_VALUE 256
#endif

#if BMC_LED_PWM_DIM_VALUE >= BMC_LED_PWM_MAX_VALUE
  #undef BMC_LED_PWM_DIM_VALUE
  #define BMC_LED_PWM_DIM_VALUE 1
#endif

// BMC_MAX_MIDI_CHANNEL_TRACKING must be a value from 1 to 16
#if !defined(BMC_MAX_MIDI_CHANNEL_TRACKING)
  #define BMC_MAX_MIDI_CHANNEL_TRACKING 16
#else
  #if BMC_MAX_MIDI_CHANNEL_TRACKING < 1  || BMC_MAX_MIDI_CHANNEL_TRACKING > 16
    #error "BMC_MAX_MIDI_CHANNEL_TRACKING must range from 1 to 16"
  #endif
#endif

#ifndef BMC_PAGE_LED_DIM
  #define BMC_PAGE_LED_DIM true
#endif

#ifndef BMC_GLOBAL_LED_DIM
  #define BMC_GLOBAL_LED_DIM true
#endif

// can be overloaded by config, must have a value
#ifndef BMC_LED_BLINK_TIMEOUT
  #define BMC_LED_BLINK_TIMEOUT 100
#endif

// can be overloaded by config, must have a value
// how many times to do a quick blink
// must be ((number of times) *2)+1
// default 3 blinks, (3*2)+1 = 7
// applies to all led types
#ifndef BMC_LEDS_MAX_TEMP_BLINKER
  #define BMC_LEDS_MAX_TEMP_BLINKER 7
#endif

// can be overloaded by config, must have a value
#ifndef BMC_RESET_INCOMING_EDITOR_MESSAGES
  #define BMC_RESET_INCOMING_EDITOR_MESSAGES true
#endif

// can be overloaded by config, must have a value
#ifndef BMC_USE_USB_MIDI_BIG_BUFFER
  #define BMC_USE_USB_MIDI_BIG_BUFFER false
#endif

// can be overloaded by config, must have a value
#ifndef BMC_BLE_MIDI_DEVICE_NAME
  #define BMC_BLE_MIDI_DEVICE_NAME "BMC BLE MIDI"
#endif

// the following are templates for value streams
// these strings are the message that will be passed when value streams are triggered
// these can all be overloaded in the config file
// make sure you follow the format of each
// these can not exceed 30 characters including the EOL

// used when changing pages
#ifndef BMC_STREAM_TEMPL_PAGE
  #define BMC_STREAM_TEMPL_PAGE "Page %03u %s"
#endif

// used when changing presets
#ifndef BMC_STREAM_TEMPL_PRESET
  #define BMC_STREAM_TEMPL_PRESET "Preset %03u %s"
#endif

// used when changing setlists
#ifndef BMC_STREAM_TEMPL_SETLIST
  #define BMC_STREAM_TEMPL_SETLIST "SetList %03u %s"
#endif

// used when changing songs
#ifndef BMC_STREAM_TEMPL_SETLIST_SONG
  #define BMC_STREAM_TEMPL_SETLIST_SONG "Song %03u %s"
#endif

// used when sending midi program change
#ifndef BMC_STREAM_TEMPL_MIDI_PC
  #define BMC_STREAM_TEMPL_MIDI_PC "Program Ch:%02u PC:%03u"
#endif

// used when sending midi control change
#ifndef BMC_STREAM_TEMPL_MIDI_CC
  #define BMC_STREAM_TEMPL_MIDI_CC "Control Ch:%02u CC:%03u V:%03u"
#endif

// used when sending midi note on
#ifndef BMC_STREAM_TEMPL_MIDI_NOTE_ON
  #define BMC_STREAM_TEMPL_MIDI_NOTE_ON "Note On Ch:%02u N:%03u V:%03u"
#endif

// used when sending midi note off
#ifndef BMC_STREAM_TEMPL_MIDI_NOTE_OFF
  #define BMC_STREAM_TEMPL_MIDI_NOTE_OFF "Note Off Ch:%02u N:%03u V:%03u"
#endif

// used when midi clock bpm has changed
#ifndef BMC_STREAM_TEMPL_MIDI_CLOCK_BPM
  #define BMC_STREAM_TEMPL_MIDI_CLOCK_BPM "BPM %03u"
#endif

// used temp page scrolling
#ifndef BMC_STREAM_TEMPL_TMP_PAGE_SCROLL
  #define BMC_STREAM_TEMPL_TMP_PAGE_SCROLL "Tmp Page %03u"
#endif

// used temp preset scrolling
#ifndef BMC_STREAM_TEMPL_TMP_PRESET_SCROLL
  #define BMC_STREAM_TEMPL_TMP_PRESET_SCROLL "Tmp Preset %03u"
#endif

#define BMC_FS_MAX_STORES 32

#define BMC_BUTTON_PRESS_TYPE_PRESS 1
#define BMC_BUTTON_PRESS_TYPE_RELEASE 2
#define BMC_BUTTON_PRESS_TYPE_HOLD 3
#define BMC_BUTTON_PRESS_TYPE_DOUBLE_PRESS 4
#define BMC_BUTTON_PRESS_TYPE_CONTINUOUS 5
#define BMC_BUTTON_PRESS_TYPE_ALT_PRESS 6
#define BMC_BUTTON_PRESS_TYPE_RELEASE_PRESS 7
#define BMC_BUTTON_PRESS_TYPE_RELEASE_HOLD 8
#define BMC_BUTTON_PRESS_TYPE_RELEASE_DOUBLE_PRESS 9
#define BMC_BUTTON_PRESS_TYPE_RELEASE_CONTINUOUS 10
#define BMC_BUTTON_PRESS_TYPE_RELEASE_ALT 11
#define BMC_BUTTON_PRESS_TYPE_STATE_CHANGE 12

// 0 = page led
// 1 = global led
// 2 = PWM led
// 3 = pixel
// 4 = rgb pixel
#define BMC_LED_TYPE_PAGE 0
#define BMC_LED_TYPE_GLOBAL 1
#define BMC_LED_TYPE_PWM 2
#define BMC_LED_TYPE_PIXEL 3
#define BMC_LED_TYPE_RGB_RED 4
#define BMC_LED_TYPE_RGB_GREEN 5
#define BMC_LED_TYPE_RGB_BLUE 6

#define BMC_OFF_LED_EVENT 0
#define BMC_ON_LED_EVENT 1
#define BMC_PULSE_LED_EVENT 2
#define BMC_BLINK_LED_EVENT 3
#define BMC_IGNORE_LED_EVENT 255

// beatbuddy control change numbers
#define BMC_BEATBUDDY_CC_TEMPO_INC 80
#define BMC_BEATBUDDY_CC_TEMPO_DEC 81
#define BMC_BEATBUDDY_CC_HALF_TIME 82
#define BMC_BEATBUDDY_CC_DOUBLE_TIME 83
#define BMC_BEATBUDDY_CC_PART_NUMBER 102
#define BMC_BEATBUDDY_CC_TEMPO_MSB 106
#define BMC_BEATBUDDY_CC_TEMPO_LSB 107
#define BMC_BEATBUDDY_CC_MIX_VOL 108
#define BMC_BEATBUDDY_CC_HP_VOL 109
#define BMC_BEATBUDDY_CC_ACCENT_HIT 110
#define BMC_BEATBUDDY_CC_PAUSE 111
#define BMC_BEATBUDDY_CC_DRUM_FILL 112
#define BMC_BEATBUDDY_CC_TRANSITION 113
#define BMC_BEATBUDDY_CC_START_PLAYBACK 114
#define BMC_BEATBUDDY_CC_OUTRO 115
#define BMC_BEATBUDDY_CC_DRUMSET_SELECT 116
#define BMC_BEATBUDDY_CC_TAP 117
#define BMC_BEATBUDDY_CC_FOLDER_ENTER_EXIT 118
#define BMC_BEATBUDDY_CC_SONG_FOLDER_SCROLL 119

// beatbuddy commands
#define BMC_BEATBUDDY_CMD_BPM_INC 0
#define BMC_BEATBUDDY_CMD_BPM_DEC 1
#define BMC_BEATBUDDY_CMD_PAUSE 2
#define BMC_BEATBUDDY_CMD_UNPAUSE 3
#define BMC_BEATBUDDY_CMD_PAUSE_TOGGLE 4
#define BMC_BEATBUDDY_CMD_DRUM_FILL 5
#define BMC_BEATBUDDY_CMD_OUTRO 6
#define BMC_BEATBUDDY_CMD_TAP 7
#define BMC_BEATBUDDY_CMD_MIX_VOL 8
#define BMC_BEATBUDDY_CMD_HP_VOL 9
#define BMC_BEATBUDDY_CMD_ACCENT_HIT 10
#define BMC_BEATBUDDY_CMD_START 11
#define BMC_BEATBUDDY_CMD_STOP 12
#define BMC_BEATBUDDY_CMD_DRUMSET_SELECT 13
#define BMC_BEATBUDDY_CMD_NORMAL_TIME 14
#define BMC_BEATBUDDY_CMD_HALF_TIME 15
#define BMC_BEATBUDDY_CMD_DOUBLE_TIME 16
#define BMC_BEATBUDDY_CMD_FOLDER_ENTER 17
#define BMC_BEATBUDDY_CMD_SONG_SCROLL_DOWN 18
#define BMC_BEATBUDDY_CMD_SONG_SCROLL_UP 19
#define BMC_BEATBUDDY_CMD_HALF_TIME_TOGGLE 20
#define BMC_BEATBUDDY_CMD_DOUBLE_TIME_TOGGLE 21
// part is this value - 100, so it the value is 101 it's part 1
#define BMC_BEATBUDDY_CMD_TRANS_END 100
#define BMC_BEATBUDDY_CMD_TRANS_PART_1 101
#define BMC_BEATBUDDY_CMD_TRANS_PART_2 102
#define BMC_BEATBUDDY_CMD_TRANS_PART_3 103
#define BMC_BEATBUDDY_CMD_TRANS_PART_4 104
#define BMC_BEATBUDDY_CMD_TRANS_PART_5 105
#define BMC_BEATBUDDY_CMD_TRANS_PART_6 106
#define BMC_BEATBUDDY_CMD_TRANS_PART_7 107
#define BMC_BEATBUDDY_CMD_TRANS_PART_8 108
#define BMC_BEATBUDDY_CMD_TRANS_PART_9 109
#define BMC_BEATBUDDY_CMD_TRANS_PART_10 110
#define BMC_BEATBUDDY_CMD_TRANS_PART_11 111
#define BMC_BEATBUDDY_CMD_TRANS_PART_12 112
#define BMC_BEATBUDDY_CMD_TRANS_PART_13 113
#define BMC_BEATBUDDY_CMD_TRANS_PART_14 114
#define BMC_BEATBUDDY_CMD_TRANS_PART_15 115
#define BMC_BEATBUDDY_CMD_TRANS_PART_16 116
#define BMC_BEATBUDDY_CMD_TRANS_PART_17 117
#define BMC_BEATBUDDY_CMD_TRANS_PART_18 118
#define BMC_BEATBUDDY_CMD_TRANS_PART_19 119
#define BMC_BEATBUDDY_CMD_TRANS_PART_20 120
#define BMC_BEATBUDDY_CMD_TRANS_PART_21 121
#define BMC_BEATBUDDY_CMD_TRANS_PART_22 122
#define BMC_BEATBUDDY_CMD_TRANS_PART_23 123
#define BMC_BEATBUDDY_CMD_TRANS_PART_24 124
#define BMC_BEATBUDDY_CMD_TRANS_PART_25 125
#define BMC_BEATBUDDY_CMD_TRANS_PART_26 126
#define BMC_BEATBUDDY_CMD_TRANS_PART_27 127
#define BMC_BEATBUDDY_CMD_TRANS_PART_28 128
#define BMC_BEATBUDDY_CMD_TRANS_PART_29 129
#define BMC_BEATBUDDY_CMD_TRANS_PART_30 130
#define BMC_BEATBUDDY_CMD_TRANS_PART_31 131
#define BMC_BEATBUDDY_CMD_TRANS_PART_32 132
#define BMC_BEATBUDDY_CMD_TRANS_PART_33 133
#define BMC_BEATBUDDY_CMD_TRANS_PART_34 134
#define BMC_BEATBUDDY_CMD_TRANS_PART_35 135
#define BMC_BEATBUDDY_CMD_TRANS_PART_36 136
#define BMC_BEATBUDDY_CMD_TRANS_PART_37 137
#define BMC_BEATBUDDY_CMD_TRANS_PART_38 138
#define BMC_BEATBUDDY_CMD_TRANS_PART_39 139
#define BMC_BEATBUDDY_CMD_TRANS_PART_40 140
#define BMC_BEATBUDDY_CMD_TRANS_PART_41 141
#define BMC_BEATBUDDY_CMD_TRANS_PART_42 142
#define BMC_BEATBUDDY_CMD_TRANS_PART_43 143
#define BMC_BEATBUDDY_CMD_TRANS_PART_44 144
#define BMC_BEATBUDDY_CMD_TRANS_PART_45 145
#define BMC_BEATBUDDY_CMD_TRANS_PART_46 146
#define BMC_BEATBUDDY_CMD_TRANS_PART_47 147
#define BMC_BEATBUDDY_CMD_TRANS_PART_48 148
#define BMC_BEATBUDDY_CMD_TRANS_PART_49 149
#define BMC_BEATBUDDY_CMD_TRANS_PART_50 150
#define BMC_BEATBUDDY_CMD_TRANS_PART_51 151
#define BMC_BEATBUDDY_CMD_TRANS_PART_52 152
#define BMC_BEATBUDDY_CMD_TRANS_PART_53 153
#define BMC_BEATBUDDY_CMD_TRANS_PART_54 154
#define BMC_BEATBUDDY_CMD_TRANS_PART_55 155
#define BMC_BEATBUDDY_CMD_TRANS_PART_56 156
#define BMC_BEATBUDDY_CMD_TRANS_PART_57 157
#define BMC_BEATBUDDY_CMD_TRANS_PART_58 158
#define BMC_BEATBUDDY_CMD_TRANS_PART_59 159
#define BMC_BEATBUDDY_CMD_TRANS_PART_60 160
#define BMC_BEATBUDDY_CMD_TRANS_PART_61 161
#define BMC_BEATBUDDY_CMD_TRANS_PART_62 162
#define BMC_BEATBUDDY_CMD_TRANS_PART_63 163
#define BMC_BEATBUDDY_CMD_TRANS_PART_64 164
#define BMC_BEATBUDDY_CMD_TRANS_PART_65 165
#define BMC_BEATBUDDY_CMD_TRANS_PART_66 166
#define BMC_BEATBUDDY_CMD_TRANS_PART_67 167
#define BMC_BEATBUDDY_CMD_TRANS_PART_68 168
#define BMC_BEATBUDDY_CMD_TRANS_PART_69 169
#define BMC_BEATBUDDY_CMD_TRANS_PART_70 170
#define BMC_BEATBUDDY_CMD_TRANS_PART_71 171
#define BMC_BEATBUDDY_CMD_TRANS_PART_72 172
#define BMC_BEATBUDDY_CMD_TRANS_PART_73 173
#define BMC_BEATBUDDY_CMD_TRANS_PART_74 174
#define BMC_BEATBUDDY_CMD_TRANS_PART_75 175
#define BMC_BEATBUDDY_CMD_TRANS_PART_76 176
#define BMC_BEATBUDDY_CMD_TRANS_PART_77 177
#define BMC_BEATBUDDY_CMD_TRANS_PART_78 178
#define BMC_BEATBUDDY_CMD_TRANS_PART_79 179
#define BMC_BEATBUDDY_CMD_TRANS_PART_80 180
#define BMC_BEATBUDDY_CMD_TRANS_PART_81 181
#define BMC_BEATBUDDY_CMD_TRANS_PART_82 182
#define BMC_BEATBUDDY_CMD_TRANS_PART_83 183
#define BMC_BEATBUDDY_CMD_TRANS_PART_84 184
#define BMC_BEATBUDDY_CMD_TRANS_PART_85 185
#define BMC_BEATBUDDY_CMD_TRANS_PART_86 186
#define BMC_BEATBUDDY_CMD_TRANS_PART_87 187
#define BMC_BEATBUDDY_CMD_TRANS_PART_88 188
#define BMC_BEATBUDDY_CMD_TRANS_PART_89 189
#define BMC_BEATBUDDY_CMD_TRANS_PART_90 190
#define BMC_BEATBUDDY_CMD_TRANS_PART_91 191
#define BMC_BEATBUDDY_CMD_TRANS_PART_92 192
#define BMC_BEATBUDDY_CMD_TRANS_PART_93 193
#define BMC_BEATBUDDY_CMD_TRANS_PART_94 194
#define BMC_BEATBUDDY_CMD_TRANS_PART_95 195
#define BMC_BEATBUDDY_CMD_TRANS_PART_96 196
#define BMC_BEATBUDDY_CMD_TRANS_PART_97 197
#define BMC_BEATBUDDY_CMD_TRANS_PART_98 198
#define BMC_BEATBUDDY_CMD_TRANS_PART_99 199
#define BMC_BEATBUDDY_CMD_TRANS_PART_100 200
#define BMC_BEATBUDDY_CMD_TRANS_PART_101 201
#define BMC_BEATBUDDY_CMD_TRANS_PART_102 202
#define BMC_BEATBUDDY_CMD_TRANS_PART_103 203
#define BMC_BEATBUDDY_CMD_TRANS_PART_104 204
#define BMC_BEATBUDDY_CMD_TRANS_PART_105 205
#define BMC_BEATBUDDY_CMD_TRANS_PART_106 206
#define BMC_BEATBUDDY_CMD_TRANS_PART_107 207
#define BMC_BEATBUDDY_CMD_TRANS_PART_108 208
#define BMC_BEATBUDDY_CMD_TRANS_PART_109 209
#define BMC_BEATBUDDY_CMD_TRANS_PART_110 210
#define BMC_BEATBUDDY_CMD_TRANS_PART_111 211
#define BMC_BEATBUDDY_CMD_TRANS_PART_112 212
#define BMC_BEATBUDDY_CMD_TRANS_PART_113 213
#define BMC_BEATBUDDY_CMD_TRANS_PART_114 214
#define BMC_BEATBUDDY_CMD_TRANS_PART_115 215
#define BMC_BEATBUDDY_CMD_TRANS_PART_116 216
#define BMC_BEATBUDDY_CMD_TRANS_PART_117 217
#define BMC_BEATBUDDY_CMD_TRANS_PART_118 218
#define BMC_BEATBUDDY_CMD_TRANS_PART_119 219
#define BMC_BEATBUDDY_CMD_TRANS_PART_120 220
#define BMC_BEATBUDDY_CMD_TRANS_PART_121 221
#define BMC_BEATBUDDY_CMD_TRANS_PART_122 222
#define BMC_BEATBUDDY_CMD_TRANS_PART_123 223
#define BMC_BEATBUDDY_CMD_TRANS_PART_124 224
#define BMC_BEATBUDDY_CMD_TRANS_PART_125 225
#define BMC_BEATBUDDY_CMD_TRANS_PREV 226
#define BMC_BEATBUDDY_CMD_TRANS_NEXT 227

// Line 6 Helix ID per Device
#define BMC_HELIX_ID 0
#define BMC_HELIX_FX_ID 1
#define BMC_HELIX_STOMP_ID 2
// #define BMC_HELIX_LT_ID 3
// #define BMC_HELIX_HX_ID 4

// Line 6 Helix control change numbers
#define BMC_HELIX_CC_TAP 64
#define BMC_HELIX_CC_TUNER 68
#define BMC_HELIX_CC_SNAPSHOT 69

#define BMC_HELIX_CMD_TAP 0
#define BMC_HELIX_CMD_TUNER 1
#define BMC_HELIX_CMD_SNAPSHOT 2
#define BMC_HELIX_CMD_SNAPSHOT_TOGGLE 3
#define BMC_HELIX_CMD_SNAPSHOT_INC 4
#define BMC_HELIX_CMD_SNAPSHOT_DEC 5

// event type id used for the sketch
#define BMC_EVENT_TYPE_CUSTOM 127

// BUTTON EVENT TYPES
#define BMC_BUTTON_EVENT_TYPE_PAGE 1
#define BMC_BUTTON_EVENT_TYPE_PAGE_SCROLL 2
#define BMC_BUTTON_EVENT_TYPE_PROGRAM_SCROLL 3
#define BMC_BUTTON_EVENT_TYPE_CONTROL_SCROLL 4
#define BMC_BUTTON_EVENT_TYPE_CONTROL_TOGGLE 5
#define BMC_BUTTON_EVENT_TYPE_MASTER_CLOCK_TAP 6
#define BMC_BUTTON_EVENT_TYPE_MASTER_CLOCK_SET 7
#define BMC_BUTTON_EVENT_TYPE_LIBRARY 8
#define BMC_BUTTON_EVENT_TYPE_LIBRARY2 9
#define BMC_BUTTON_EVENT_TYPE_LIBRARY3 10
#define BMC_BUTTON_EVENT_TYPE_PRESET 11
#define BMC_BUTTON_EVENT_TYPE_PRESET_SCROLL 12
#define BMC_BUTTON_EVENT_TYPE_CUSTOM_SYSEX 13
#define BMC_BUTTON_EVENT_TYPE_BEATBUDDY_SET_BPM 14
#define BMC_BUTTON_EVENT_TYPE_BEATBUDDY_CMD 15
#define BMC_BUTTON_EVENT_TYPE_BEATBUDDY_FOLDER_SONG 16
#define BMC_BUTTON_EVENT_TYPE_CLICK_TRACK 17
#define BMC_BUTTON_EVENT_TYPE_BANK_MSB_PROGRAM 18
#define BMC_BUTTON_EVENT_TYPE_BANK_LSB_PROGRAM 19
#define BMC_BUTTON_EVENT_TYPE_BANK_MSB_LSB 20
#define BMC_BUTTON_EVENT_TYPE_HELIX_CMD 21
#define BMC_BUTTON_EVENT_TYPE_ACTIVE_SENSE 22
#define BMC_BUTTON_EVENT_TYPE_NL_RELAY_CONTROL 23
#define BMC_BUTTON_EVENT_TYPE_L_RELAY_CONTROL 24
#define BMC_BUTTON_EVENT_TYPE_SKETCH_BYTE_SET 25
#define BMC_BUTTON_EVENT_TYPE_SKETCH_BYTE_SCROLL 26
#define BMC_BUTTON_EVENT_TYPE_SKETCH_BYTE_TOGGLE 27
#define BMC_BUTTON_EVENT_TYPE_LED_TEMP_BLINK 28
#define BMC_BUTTON_EVENT_TYPE_GLOBAL_LED_TEMP_BLINK 29
#define BMC_BUTTON_EVENT_TYPE_CONTROL_TOGGLE_2 30
#define BMC_BUTTON_EVENT_TYPE_TMP_SCROLLER_TRIGGER 31
#define BMC_BUTTON_EVENT_TYPE_TMP_SCROLLER_PAGES 32
#define BMC_BUTTON_EVENT_TYPE_TMP_SCROLLER_PRESETS 33
#define BMC_BUTTON_EVENT_TYPE_NL_RELAY_CONTROL_TOGGLE 34
#define BMC_BUTTON_EVENT_TYPE_L_RELAY_CONTROL_TOGGLE 35
#define BMC_BUTTON_EVENT_TYPE_MIDI_REAL_TIME_BLOCK 36
// id 37 available
#define BMC_BUTTON_EVENT_TYPE_STOPWATCH 38
#define BMC_BUTTON_EVENT_TYPE_BLE_DISCONNECT 39
#define BMC_BUTTON_EVENT_TYPE_PWM_LED_TEMP_BLINK 40
#define BMC_BUTTON_EVENT_TYPE_PRESET_IN_BANK 41
#define BMC_BUTTON_EVENT_TYPE_PRESET_IN_BANK_SCROLL 42
#define BMC_BUTTON_EVENT_TYPE_PRESETS_SET_BANK 43
#define BMC_BUTTON_EVENT_TYPE_PRESETS_BANK_SCROLL 44
#define BMC_BUTTON_EVENT_TYPE_SETLIST 45
#define BMC_BUTTON_EVENT_TYPE_SETLIST_SCROLL 46
#define BMC_BUTTON_EVENT_TYPE_SETLIST_SONG 47
#define BMC_BUTTON_EVENT_TYPE_SETLIST_SONG_SCROLL 48
#define BMC_BUTTON_EVENT_TYPE_PROGRAM_BANKING_SCROLL 49
#define BMC_BUTTON_EVENT_TYPE_PROGRAM_BANKING_TRIGGER 50
// id 51 to id 79 availabel
#define BMC_BUTTON_EVENT_TYPE_FAS_COMMAND 80
#define BMC_BUTTON_EVENT_TYPE_FAS_PRESET 81
#define BMC_BUTTON_EVENT_TYPE_FAS_PRESET_SCROLL 82
#define BMC_BUTTON_EVENT_TYPE_FAS_SCENE 83
#define BMC_BUTTON_EVENT_TYPE_FAS_SCENE_SCROLL 84
#define BMC_BUTTON_EVENT_TYPE_FAS_BLOCK_STATE 85
#define BMC_BUTTON_EVENT_TYPE_FAS_BLOCK_PARAM 86
#define BMC_BUTTON_EVENT_TYPE_KEMPER_COMMAND 90
#define BMC_BUTTON_EVENT_TYPE_KEMPER_RIG 91
#define BMC_BUTTON_EVENT_TYPE_KEMPER_STOMP 92
#define BMC_BUTTON_EVENT_TYPE_KEMPER_RESERVED1 93
#define BMC_BUTTON_EVENT_TYPE_KEMPER_RESERVED2 94
#define BMC_BUTTON_EVENT_TYPE_SAVE_EEPROM 100
#define BMC_BUTTON_EVENT_TYPE_MENU 110
// 8 user defined events
// this feature will be added to the editor and documented later on
#define BMC_BUTTON_EVENT_TYPE_USER_1 118
#define BMC_BUTTON_EVENT_TYPE_USER_2 119
#define BMC_BUTTON_EVENT_TYPE_USER_3 120
#define BMC_BUTTON_EVENT_TYPE_USER_4 121
#define BMC_BUTTON_EVENT_TYPE_USER_5 122
#define BMC_BUTTON_EVENT_TYPE_USER_6 123
#define BMC_BUTTON_EVENT_TYPE_USER_7 124
#define BMC_BUTTON_EVENT_TYPE_USER_8 125
#define BMC_BUTTON_EVENT_TYPE_DELAY 126
#define BMC_BUTTON_EVENT_TYPE_CUSTOM 127

// **************************************
//           LED EVENT TYPES
// **************************************
// These are used for Page Leds, Global Leds, PWM Leds and Pixels
#define BMC_LED_EVENT_TYPE_MIDI_ACTIVITY 1
#define BMC_LED_EVENT_TYPE_CLOCK_SYNC 2
#define BMC_LED_EVENT_TYPE_STATUS 3
#define BMC_LED_EVENT_TYPE_PAGE 4
#define BMC_LED_EVENT_TYPE_PRESET 5
#define BMC_LED_EVENT_TYPE_BUTTON 6
#define BMC_LED_EVENT_TYPE_GLOBAL_BUTTON 7
#define BMC_LED_EVENT_TYPE_POT 8
#define BMC_LED_EVENT_TYPE_NL_RELAY 9
#define BMC_LED_EVENT_TYPE_L_RELAY 10
#define BMC_LED_EVENT_TYPE_AUX_JACK_CONNECTED 11
#define BMC_LED_EVENT_TYPE_BEATBUDDY 12
#define BMC_LED_EVENT_TYPE_HELIX_SNAPSHOT 13
#define BMC_LED_EVENT_TYPE_PRESET_IN_BANK 14
#define BMC_LED_EVENT_TYPE_PRESETS_BANK 15
#define BMC_LED_EVENT_TYPE_SETLIST 16
#define BMC_LED_EVENT_TYPE_SETLIST_SONG 17
#define BMC_LED_EVENT_TYPE_GLOBAL_POT 18
#define BMC_LED_EVENT_TYPE_FAS_STATE 80
#define BMC_LED_EVENT_TYPE_FAS_PRESET 81
#define BMC_LED_EVENT_TYPE_FAS_SCENE 82
#define BMC_LED_EVENT_TYPE_FAS_BLOCK_STATE 83
#define BMC_LED_EVENT_TYPE_KEMPER_STATE 90
#define BMC_LED_EVENT_TYPE_KEMPER_RIG 91
#define BMC_LED_EVENT_TYPE_KEMPER_STOMP 92
#define BMC_LED_EVENT_TYPE_KEMPER_RESERVED 93
// 8 user defined events
// this feature will be added to the editor and documented later on
#define BMC_LED_EVENT_TYPE_USER_1 118
#define BMC_LED_EVENT_TYPE_USER_2 119
#define BMC_LED_EVENT_TYPE_USER_3 120
#define BMC_LED_EVENT_TYPE_USER_4 121
#define BMC_LED_EVENT_TYPE_USER_5 122
#define BMC_LED_EVENT_TYPE_USER_6 123
#define BMC_LED_EVENT_TYPE_USER_7 124
#define BMC_LED_EVENT_TYPE_USER_8 125

// **********************************
// used for BMC_LED_EVENT_TYPE_STATUS
// **********************************
#define BMC_LED_STATUS_BMC 0
#define BMC_LED_STATUS_ALWAYS_ON 1
#define BMC_LED_STATUS_EDITOR_CONNECTED 2
#define BMC_LED_STATUS_HOST_CONNECTED 3
#define BMC_LED_STATUS_BLE_CONNECTED 4
#define BMC_LED_STATUS_ACTIVE_SENSE_SENDING 5
#define BMC_LED_STATUS_ACTIVE_SENSE_READING 6
#define BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_INPUT 7
#define BMC_LED_STATUS_MIDI_REAL_TIME_BLOCK_OUTPUT 8
#define BMC_LED_STATUS_STOPWATCH_STATE 9
#define BMC_LED_STATUS_STOPWATCH_ACTIVE 10
#define BMC_LED_STATUS_STOPWATCH_COMPLETE 11
// **************************************
// used for BMC_LED_EVENT_TYPE_BEATBUDDY
// **************************************
#define BMC_LED_BEATBUDDY_SYNC 0
#define BMC_LED_BEATBUDDY_PLAYING 1
#define BMC_LED_BEATBUDDY_PART 2
#define BMC_LED_BEATBUDDY_HALF_TIME 3
#define BMC_LED_BEATBUDDY_DOUBLE_TIME 4

// **********************************
//            BMC Colors
// **********************************
// RGB Pixles use the first 3 bits of the color value
// so the max color from this list for RGB Pixels is WHITE
// bit 0 = red
// bit 1 = green
// bit 2 = blue
#define BMC_COLOR_BLACK 0
#define BMC_COLOR_RED B0001 // 1
#define BMC_COLOR_GREEN B0010 // 2
#define BMC_COLOR_YELLOW B0011 // 3
#define BMC_COLOR_BLUE B0100 // 4
#define BMC_COLOR_MAGENTA B0101 // 5
#define BMC_COLOR_CYAN B0110 // 6
#define BMC_COLOR_WHITE B0111 // 7
#define BMC_COLOR_LIME 8
#define BMC_COLOR_PINK 9
#define BMC_COLOR_PURPLE 10
#define BMC_COLOR_ORANGE 11
#define BMC_COLOR_TEAL 12
#define BMC_COLOR_CORAL 13
#define BMC_COLOR_LIGHT_BLUE 14
#define BMC_COLOR_RAINBOW 15


// PIXEL COLORS
// kept here for old configs
#define BMC_PIXEL_BLACK BMC_COLOR_BLACK
#define BMC_PIXEL_RAINBOW BMC_COLOR_RAINBOW
#define BMC_PIXEL_RED BMC_COLOR_RED
#define BMC_PIXEL_GREEN BMC_COLOR_GREEN
#define BMC_PIXEL_BLUE BMC_COLOR_BLUE
#define BMC_PIXEL_YELLOW BMC_COLOR_YELLOW
#define BMC_PIXEL_MAGENTA BMC_COLOR_MAGENTA
#define BMC_PIXEL_LIME BMC_COLOR_LIME
#define BMC_PIXEL_CYAN BMC_COLOR_CYAN
#define BMC_PIXEL_PINK BMC_COLOR_PINK
#define BMC_PIXEL_PURPLE BMC_COLOR_PURPLE
#define BMC_PIXEL_LIGHT_BLUE BMC_COLOR_LIGHT_BLUE
#define BMC_PIXEL_ORANGE BMC_COLOR_ORANGE
#define BMC_PIXEL_CORAL BMC_COLOR_CORAL
#define BMC_PIXEL_TEAL BMC_COLOR_TEAL
#define BMC_PIXEL_WHITE BMC_COLOR_WHITE



// KEMPER DATA
// value = Any
#define BMC_KEMPER_CC_TOGGLE_ALL_STOMPS 16
#define BMC_KEMPER_CC_TOGGLE_STOP_A 17
#define BMC_KEMPER_CC_TOGGLE_STOP_B 18
#define BMC_KEMPER_CC_TOGGLE_STOP_C 19
#define BMC_KEMPER_CC_TOGGLE_STOP_D 20
#define BMC_KEMPER_CC_TOGGLE_STOP_X 22
#define BMC_KEMPER_CC_TOGGLE_STOP_MOD 24
#define BMC_KEMPER_CC_TOGGLE_STOP_DELAY 26
#define BMC_KEMPER_CC_TOGGLE_STOP_DELAY_TAIL 27
#define BMC_KEMPER_CC_TOGGLE_REVERB 28
#define BMC_KEMPER_CC_TOGGLE_REVER_TAIL 29
// BMC will use 0 for the value, see the kemper midi manual
#define BMC_KEMPER_CC_SET_TEMPO 30
// 0 hide, 1 show
#define BMC_KEMPER_CC_TUNER 31
// 0 slow, 1 fast
#define BMC_KEMPER_CC_ROTARY_SPEAKER_SPEED 33
// 0 off, 1 on
#define BMC_KEMPER_CC_DELAY_FEEDBACK_INFINITY 34
// 0 off, 1 on
#define BMC_KEMPER_CC_DELAY_HOLD 35
// Performance Mode only
// Preselected performance index4. Can be set directly or scrolled via CC48/CC49.
// The performance will be loaded when a slot selection is being sent (CC50-54).
// If no slot is selected, the “preselection mode” is being disabled after a
// few seconds. If the “preselection mode” is disabled, the active performance
// number will be sent plus a Slot message (CC50-54)
// value 0 to 124
#define BMC_KEMPER_CC_PM_PRESELECTED_INDEX 47
// ** Performance Mode
// Increases performance index. Value triggers two different modes:
//     - Value 0, increase performance n to n+1
//     - Value 1 initially increases performance by 1, after a timeout the
// Kemper Profiler starts to scroll performances upwards. Value 0
// stops scrolling.
// ** Browse Mode
// Value 0 selects the next Rig (current filter/sort applies), similar to “Rig Right”
#define BMC_KEMPER_CC_NEXT_RIG 48
// ** Performance Mode
// Decrease performance index. Value triggers two different modes:
//     - Value 0, increase performance n to n-1
//     - Value 1 initially decreases performance index by 1, after a
// timeout the Kemper Profiler starts to scroll performances
// downwards. Value 0 stops scrolling.
// ** Browse Mode
// Value 0 selects the previous Rig (current filter/sort applies), similar to “Rig Left”
#define BMC_KEMPER_CC_PREV_RIG 49
// ** Performance Mode
// Select Slot 1 of current performance.
// ** Browse Mode
// Select 1st out of current 5 rigs in list
#define BMC_KEMPER_CC_FIRST_RIG 50
// see above
#define BMC_KEMPER_CC_SECOND_RIG 51
#define BMC_KEMPER_CC_THIRD_RIG 52
#define BMC_KEMPER_CC_FOURTH_RIG 53
#define BMC_KEMPER_CC_FIFTH_RIG 54
// value of the CC is the value that will be set to these parameters
#define BMC_KEMPER_CC_DELAY_MIX 68
#define BMC_KEMPER_CC_DELAY_FEEDBACK 69
#define BMC_KEMPER_CC_REVERB_MIX 70
#define BMC_KEMPER_CC_REVERB_TIME 71
#define BMC_KEMPER_CC_AMP_GAIN 72
#define BMC_KEMPER_CC_GLOBAL_MONITOR_OUT_LEVEL 73


// KEMPER PARAMETERS WITH PAGE AND PARAMETER
// KEMPER PARAM PAGE RIG
#define BMC_KEMPER_PARAM_RIG_TEMPO 0x400
#define BMC_KEMPER_PARAM_RIG_VOLUME 0x401
#define BMC_KEMPER_PARAM_RIG_TEMPO_ENABLE 0x402
// KEMPER PARAM PAGE INPUT
#define BMC_KEMPER_PARAM_INPUT_NOISE_GATE_INTENSITY 0x903
#define BMC_KEMPER_PARAM_INPUT_CLEAN_SENSE 0x904
#define BMC_KEMPER_PARAM_INPUT_DISTORTION_SENSE 0x905
// KEMPER PARAM PAGE AMPLIFIER
#define BMC_KEMPER_PARAM_AMPLIFIER_ON_OFF 0xA02
#define BMC_KEMPER_PARAM_AMPLIFIER_GAIN 0xA04
#define BMC_KEMPER_PARAM_AMPLIFIER_DEFINITION 0xA06
#define BMC_KEMPER_PARAM_AMPLIFIER_CLARITY 0xA07
#define BMC_KEMPER_PARAM_AMPLIFIER_POWER_SAGGING_ 0xA08
#define BMC_KEMPER_PARAM_AMPLIFIER_PICK 0xA09
#define BMC_KEMPER_PARAM_AMPLIFIER_COMPRESSOR_ 0xA0A
#define BMC_KEMPER_PARAM_AMPLIFIER_TUBE_SHAPE_ 0xA0B
#define BMC_KEMPER_PARAM_AMPLIFIER_TUBE_BIAS 0xA0C
#define BMC_KEMPER_PARAM_AMPLIFIER_DIRECT_MIX 0xA0F
// KEMPER PARAM PAGE EQUALIZER
#define BMC_KEMPER_PARAM_EQUALIZER_ON_OFF 0xB02
#define BMC_KEMPER_PARAM_EQUALIZER_BASS 0xB04
#define BMC_KEMPER_PARAM_EQUALIZER_MIDDLE 0xB05
#define BMC_KEMPER_PARAM_EQUALIZER_TREBLE 0xB06
#define BMC_KEMPER_PARAM_EQUALIZER_PRESENCE 0xB07
// KEMPER PARAM PAGE CABINET
#define BMC_KEMPER_PARAM_CABINET_ON_OFF 0xC02
#define BMC_KEMPER_PARAM_CABINET_VOLUME 0xC03
#define BMC_KEMPER_PARAM_CABINET_HIGH_SHIFT 0xC04
#define BMC_KEMPER_PARAM_CABINET_LOW_SHIFT 0xC05
#define BMC_KEMPER_PARAM_CABINET_CHARACTER 0xC06
#define BMC_KEMPER_PARAM_CABINET_PURE_CABINET__RIG_ 0xC07
// KEMPER PARAM PAGE STOMP A
#define BMC_KEMPER_PARAM_STOMP_A_TYPE 0x3200
#define BMC_KEMPER_PARAM_STOMP_A_ON_OFF_4_MIX 0x3203
#define BMC_KEMPER_PARAM_STOMP_A_VOLUME_7_STEREO 0x3206
#define BMC_KEMPER_PARAM_STOMP_A_WAH_MANUAL 0x3208
#define BMC_KEMPER_PARAM_STOMP_A_WAH_PEAK 0x3209
#define BMC_KEMPER_PARAM_STOMP_A_WAH_RANGE 0x320A
#define BMC_KEMPER_PARAM_STOMP_A_WAH_PEDAL_MODE_ 0x320C
#define BMC_KEMPER_PARAM_STOMP_A_WAH_TOUCH_ATTACK_ 0x320D
#define BMC_KEMPER_PARAM_STOMP_A_WAH_TOUCH_RELEASE_ 0x320E
#define BMC_KEMPER_PARAM_STOMP_A_WAH_TOUCH_BOOST 0x320F
#define BMC_KEMPER_PARAM_STOMP_A_DISTORTION_SHAPER_DRIVE_ 0x3210
#define BMC_KEMPER_PARAM_STOMP_A_DISTORTION_BOOSTER_TONE 0x3211
#define BMC_KEMPER_PARAM_STOMP_A_COMPRESSOR_GATE_INTENSITY_ 0x3212
#define BMC_KEMPER_PARAM_STOMP_A_COMPRESSOR_ATTACK 0x3213
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_RATE 0x3214
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_DEPTH 0x3215
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_FEEDBACK 0x3216
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_CROSSOVER 0x3217
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_HYPERCHORUS_AMOUNT_ 0x3218
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_MANUAL 0x3219
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_PHASER_PEAK_SPREAD_ 0x321A
#define BMC_KEMPER_PARAM_STOMP_A_MODULATION_PHASER_STAGES 0x321B
#define BMC_KEMPER_PARAM_STOMP_A_ROTARY_SPEED__SLOW_FAST__ 0x321E
#define BMC_KEMPER_PARAM_STOMP_A_ROTARY_DISTANCE 0x321F
#define BMC_KEMPER_PARAM_STOMP_A_ROTARY_BALANCE 0x3220
#define BMC_KEMPER_PARAM_STOMP_A_COMPRESSOR_SQUASH 0x3221
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_1_ 0x3222
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_2_ 0x3223
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_3_ 0x3224
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_4_ 0x3225
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_5_ 0x3226
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_6_ 0x3227
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_7_ 0x3228
#define BMC_KEMPER_PARAM_STOMP_A_GRAPHIC_EQ_BAND_8 0x3229
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_LOW_GAIN 0x322A
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_LOW_FREQUENCY_ 0x322B
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_HIGH_GAIN 0x322C
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_HIGH_FREQUENCY_ 0x322D
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_PEAK_GAIN 0x322E
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_PEAK_FREQUENCY_ 0x322F
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_PEAK_Q_FACTOR 0x3230
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_PEAK_GAIN_2 0x3231
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_PEAK_FREQUENCY_2_ 0x3232
#define BMC_KEMPER_PARAM_STOMP_A_PARAMETRIC_EQ_PEAK_Q_FACTOR_2 0x3233
#define BMC_KEMPER_PARAM_STOMP_A_WAH_PEAK_RANGE_ 0x3234
#define BMC_KEMPER_PARAM_STOMP_A_DUCKING 0x3235
#define BMC_KEMPER_PARAM_STOMP_A_VOICE_MIX_ 0x3237
#define BMC_KEMPER_PARAM_STOMP_A_VOICE_1_PITCH_ 0x3238
#define BMC_KEMPER_PARAM_STOMP_A_VOICE_2_PITCH_ 0x3239
#define BMC_KEMPER_PARAM_STOMP_A_DETUNE 0x323A
#define BMC_KEMPER_PARAM_STOMP_A_SMOOTH_CHORDS_ 0x323C
#define BMC_KEMPER_PARAM_STOMP_A_PURE_TUNING 0x323D
#define BMC_KEMPER_PARAM_STOMP_A_KEY 0x3240
#define BMC_KEMPER_PARAM_STOMP_A_FREEZE_FORMANTS_ 0x3241
#define BMC_KEMPER_PARAM_STOMP_A_FORMANT_OFFSET_ 0x3242
#define BMC_KEMPER_PARAM_STOMP_A_LOW_CUT 0x3243
#define BMC_KEMPER_PARAM_STOMP_A_HIGH_CUT 0x3244
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_MIX 0x3245
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_MIX_PRE_POST_ 0x3246
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_TIME_1 0x3247
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_TIME_2 0x3248
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_RATIO_2 0x3249
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_RATIO_3 0x324A
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_RATIO_4 0x324B
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_NOTE_VALUE_1_ 0x324C
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_NOTE_VALUE_2_ 0x324D
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_NOTE_VALUE_3_ 0x324E
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_NOTE_VALUE_4_ 0x324F
#define BMC_KEMPER_PARAM_STOMP_A_TO_TEMPO 0x3250
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_VOLUME_1 0x3251
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_VOLUME_2 0x3252
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_VOLUME_3 0x3253
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_VOLUME_4 0x3254
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_PANORAMA_1 0x3255
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_PANORAMA_2 0x3256
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_PANORAMA_3 0x3257
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_PANORAMA_4 0x3258
#define BMC_KEMPER_PARAM_STOMP_A_VOICE3_PITCH 0x3259
#define BMC_KEMPER_PARAM_STOMP_A_VOICE4_PITCH 0x325A
#define BMC_KEMPER_PARAM_STOMP_A_VOICE3_INTERVAL 0x325B
#define BMC_KEMPER_PARAM_STOMP_A_VOICE4_INTERVAL 0x325C
#define BMC_KEMPER_PARAM_STOMP_A_FEEDBACK 0x325D
#define BMC_KEMPER_PARAM_STOMP_A_INFINITY_FEEDBACK 0x325E
#define BMC_KEMPER_PARAM_STOMP_A_INFINITY 0x325F
#define BMC_KEMPER_PARAM_STOMP_A_FEEDBACK2 0x3260
#define BMC_KEMPER_PARAM_STOMP_A_FEEDBACK_SYNC_SWITCH_ 0x3261
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_LOW_CUT 0x3262
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_HIGH_CUT 0x3263
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_FILTER_INTENSITY_ 0x3264
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_MODULATION_ 0x3265
#define BMC_KEMPER_PARAM_STOMP_A_DELAY_CHORUS 0x3266
#define BMC_KEMPER_PARAM_STOMP_A_FLUTTER_INTENSITY 0x3267
#define BMC_KEMPER_PARAM_STOMP_A_FLUTTER_SHAPE 0x3268
#define BMC_KEMPER_PARAM_STOMP_A_GRIT 0x3269
#define BMC_KEMPER_PARAM_STOMP_A_REVERSE_MIX 0x326A
#define BMC_KEMPER_PARAM_STOMP_A_SWELL 0x326B
#define BMC_KEMPER_PARAM_STOMP_A_SMEAR 0x326C
#define BMC_KEMPER_PARAM_STOMP_A_DUCKING_PRE_POST 0x326D
// KEMPER PARAM PAGE STOMP B
#define BMC_KEMPER_PARAM_STOMP_B_TYPE 0x3300
#define BMC_KEMPER_PARAM_STOMP_B_ON_OFF_4_MIX 0x3303
#define BMC_KEMPER_PARAM_STOMP_B_VOLUME_7_STEREO 0x3306
#define BMC_KEMPER_PARAM_STOMP_B_WAH_MANUAL 0x3308
#define BMC_KEMPER_PARAM_STOMP_B_WAH_PEAK 0x3309
#define BMC_KEMPER_PARAM_STOMP_B_WAH_RANGE 0x330A
#define BMC_KEMPER_PARAM_STOMP_B_WAH_PEDAL_MODE_ 0x330C
#define BMC_KEMPER_PARAM_STOMP_B_WAH_TOUCH_ATTACK_ 0x330D
#define BMC_KEMPER_PARAM_STOMP_B_WAH_TOUCH_RELEASE_ 0x330E
#define BMC_KEMPER_PARAM_STOMP_B_WAH_TOUCH_BOOST 0x330F
#define BMC_KEMPER_PARAM_STOMP_B_DISTORTION_SHAPER_DRIVE_ 0x3310
#define BMC_KEMPER_PARAM_STOMP_B_DISTORTION_BOOSTER_TONE 0x3311
#define BMC_KEMPER_PARAM_STOMP_B_COMPRESSOR_GATE_INTENSITY_ 0x3312
#define BMC_KEMPER_PARAM_STOMP_B_COMPRESSOR_ATTACK 0x3313
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_RATE 0x3314
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_DEPTH 0x3315
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_FEEDBACK 0x3316
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_CROSSOVER 0x3317
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_HYPERCHORUS_AMOUNT_ 0x3318
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_MANUAL 0x3319
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_PHASER_PEAK_SPREAD_ 0x331A
#define BMC_KEMPER_PARAM_STOMP_B_MODULATION_PHASER_STAGES 0x331B
#define BMC_KEMPER_PARAM_STOMP_B_ROTARY_SPEED__SLOW_FAST__ 0x331E
#define BMC_KEMPER_PARAM_STOMP_B_ROTARY_DISTANCE 0x331F
#define BMC_KEMPER_PARAM_STOMP_B_ROTARY_BALANCE 0x3320
#define BMC_KEMPER_PARAM_STOMP_B_COMPRESSOR_SQUASH 0x3321
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_1_ 0x3322
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_2_ 0x3323
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_3_ 0x3324
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_4_ 0x3325
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_5_ 0x3326
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_6_ 0x3327
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_7_ 0x3328
#define BMC_KEMPER_PARAM_STOMP_B_GRAPHIC_EQ_BAND_8 0x3329
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_LOW_GAIN 0x332A
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_LOW_FREQUENCY_ 0x332B
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_HIGH_GAIN 0x332C
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_HIGH_FREQUENCY_ 0x332D
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_PEAK_GAIN 0x332E
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_PEAK_FREQUENCY_ 0x332F
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_PEAK_Q_FACTOR 0x3330
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_PEAK_GAIN_2 0x3331
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_PEAK_FREQUENCY_2_ 0x3332
#define BMC_KEMPER_PARAM_STOMP_B_PARAMETRIC_EQ_PEAK_Q_FACTOR_2 0x3333
#define BMC_KEMPER_PARAM_STOMP_B_WAH_PEAK_RANGE_ 0x3334
#define BMC_KEMPER_PARAM_STOMP_B_DUCKING 0x3335
#define BMC_KEMPER_PARAM_STOMP_B_VOICE_MIX_ 0x3337
#define BMC_KEMPER_PARAM_STOMP_B_VOICE_1_PITCH_ 0x3338
#define BMC_KEMPER_PARAM_STOMP_B_VOICE_2_PITCH_ 0x3339
#define BMC_KEMPER_PARAM_STOMP_B_DETUNE 0x333A
#define BMC_KEMPER_PARAM_STOMP_B_SMOOTH_CHORDS_ 0x333C
#define BMC_KEMPER_PARAM_STOMP_B_PURE_TUNING 0x333D
#define BMC_KEMPER_PARAM_STOMP_B_KEY 0x3340
#define BMC_KEMPER_PARAM_STOMP_B_FREEZE_FORMANTS_ 0x3341
#define BMC_KEMPER_PARAM_STOMP_B_FORMANT_OFFSET_ 0x3342
#define BMC_KEMPER_PARAM_STOMP_B_LOW_CUT 0x3343
#define BMC_KEMPER_PARAM_STOMP_B_HIGH_CUT 0x3344
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_MIX 0x3345
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_MIX_PRE_POST_ 0x3346
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_TIME_1 0x3347
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_TIME_2 0x3348
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_RATIO_2 0x3349
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_RATIO_3 0x334A
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_RATIO_4 0x334B
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_NOTE_VALUE_1_ 0x334C
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_NOTE_VALUE_2_ 0x334D
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_NOTE_VALUE_3_ 0x334E
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_NOTE_VALUE_4_ 0x334F
#define BMC_KEMPER_PARAM_STOMP_B_TO_TEMPO 0x3350
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_VOLUME_1 0x3351
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_VOLUME_2 0x3352
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_VOLUME_3 0x3353
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_VOLUME_4 0x3354
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_PANORAMA_1 0x3355
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_PANORAMA_2 0x3356
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_PANORAMA_3 0x3357
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_PANORAMA_4 0x3358
#define BMC_KEMPER_PARAM_STOMP_B_VOICE3_PITCH 0x3359
#define BMC_KEMPER_PARAM_STOMP_B_VOICE4_PITCH 0x335A
#define BMC_KEMPER_PARAM_STOMP_B_VOICE3_INTERVAL 0x335B
#define BMC_KEMPER_PARAM_STOMP_B_VOICE4_INTERVAL 0x335C
#define BMC_KEMPER_PARAM_STOMP_B_FEEDBACK 0x335D
#define BMC_KEMPER_PARAM_STOMP_B_INFINITY_FEEDBACK 0x335E
#define BMC_KEMPER_PARAM_STOMP_B_INFINITY 0x335F
#define BMC_KEMPER_PARAM_STOMP_B_FEEDBACK2 0x3360
#define BMC_KEMPER_PARAM_STOMP_B_FEEDBACK_SYNC_SWITCH_ 0x3361
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_LOW_CUT 0x3362
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_HIGH_CUT 0x3363
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_FILTER_INTENSITY_ 0x3364
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_MODULATION_ 0x3365
#define BMC_KEMPER_PARAM_STOMP_B_DELAY_CHORUS 0x3366
#define BMC_KEMPER_PARAM_STOMP_B_FLUTTER_INTENSITY 0x3367
#define BMC_KEMPER_PARAM_STOMP_B_FLUTTER_SHAPE 0x3368
#define BMC_KEMPER_PARAM_STOMP_B_GRIT 0x3369
#define BMC_KEMPER_PARAM_STOMP_B_REVERSE_MIX 0x336A
#define BMC_KEMPER_PARAM_STOMP_B_SWELL 0x336B
#define BMC_KEMPER_PARAM_STOMP_B_SMEAR 0x336C
#define BMC_KEMPER_PARAM_STOMP_B_DUCKING_PRE_POST 0x336D
// KEMPER PARAM PAGE STOMP C
#define BMC_KEMPER_PARAM_STOMP_C_TYPE 0x3400
#define BMC_KEMPER_PARAM_STOMP_C_ON_OFF_4_MIX 0x3403
#define BMC_KEMPER_PARAM_STOMP_C_VOLUME_7_STEREO 0x3406
#define BMC_KEMPER_PARAM_STOMP_C_WAH_MANUAL 0x3408
#define BMC_KEMPER_PARAM_STOMP_C_WAH_PEAK 0x3409
#define BMC_KEMPER_PARAM_STOMP_C_WAH_RANGE 0x340A
#define BMC_KEMPER_PARAM_STOMP_C_WAH_PEDAL_MODE_ 0x340C
#define BMC_KEMPER_PARAM_STOMP_C_WAH_TOUCH_ATTACK_ 0x340D
#define BMC_KEMPER_PARAM_STOMP_C_WAH_TOUCH_RELEASE_ 0x340E
#define BMC_KEMPER_PARAM_STOMP_C_WAH_TOUCH_BOOST 0x340F
#define BMC_KEMPER_PARAM_STOMP_C_DISTORTION_SHAPER_DRIVE_ 0x3410
#define BMC_KEMPER_PARAM_STOMP_C_DISTORTION_BOOSTER_TONE 0x3411
#define BMC_KEMPER_PARAM_STOMP_C_COMPRESSOR_GATE_INTENSITY_ 0x3412
#define BMC_KEMPER_PARAM_STOMP_C_COMPRESSOR_ATTACK 0x3413
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_RATE 0x3414
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_DEPTH 0x3415
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_FEEDBACK 0x3416
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_CROSSOVER 0x3417
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_HYPERCHORUS_AMOUNT_ 0x3418
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_MANUAL 0x3419
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_PHASER_PEAK_SPREAD_ 0x341A
#define BMC_KEMPER_PARAM_STOMP_C_MODULATION_PHASER_STAGES 0x341B
#define BMC_KEMPER_PARAM_STOMP_C_ROTARY_SPEED__SLOW_FAST__ 0x341E
#define BMC_KEMPER_PARAM_STOMP_C_ROTARY_DISTANCE 0x341F
#define BMC_KEMPER_PARAM_STOMP_C_ROTARY_BALANCE 0x3420
#define BMC_KEMPER_PARAM_STOMP_C_COMPRESSOR_SQUASH 0x3421
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_1_ 0x3422
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_2_ 0x3423
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_3_ 0x3424
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_4_ 0x3425
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_5_ 0x3426
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_6_ 0x3427
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_7_ 0x3428
#define BMC_KEMPER_PARAM_STOMP_C_GRAPHIC_EQ_BAND_8 0x3429
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_LOW_GAIN 0x342A
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_LOW_FREQUENCY_ 0x342B
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_HIGH_GAIN 0x342C
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_HIGH_FREQUENCY_ 0x342D
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_PEAK_GAIN 0x342E
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_PEAK_FREQUENCY_ 0x342F
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_PEAK_Q_FACTOR 0x3430
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_PEAK_GAIN_2 0x3431
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_PEAK_FREQUENCY_2_ 0x3432
#define BMC_KEMPER_PARAM_STOMP_C_PARAMETRIC_EQ_PEAK_Q_FACTOR_2 0x3433
#define BMC_KEMPER_PARAM_STOMP_C_WAH_PEAK_RANGE_ 0x3434
#define BMC_KEMPER_PARAM_STOMP_C_DUCKING 0x3435
#define BMC_KEMPER_PARAM_STOMP_C_VOICE_MIX_ 0x3437
#define BMC_KEMPER_PARAM_STOMP_C_VOICE_1_PITCH_ 0x3438
#define BMC_KEMPER_PARAM_STOMP_C_VOICE_2_PITCH_ 0x3439
#define BMC_KEMPER_PARAM_STOMP_C_DETUNE 0x343A
#define BMC_KEMPER_PARAM_STOMP_C_SMOOTH_CHORDS_ 0x343C
#define BMC_KEMPER_PARAM_STOMP_C_PURE_TUNING 0x343D
#define BMC_KEMPER_PARAM_STOMP_C_KEY 0x3440
#define BMC_KEMPER_PARAM_STOMP_C_FREEZE_FORMANTS_ 0x3441
#define BMC_KEMPER_PARAM_STOMP_C_FORMANT_OFFSET_ 0x3442
#define BMC_KEMPER_PARAM_STOMP_C_LOW_CUT 0x3443
#define BMC_KEMPER_PARAM_STOMP_C_HIGH_CUT 0x3444
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_MIX 0x3445
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_MIX_PRE_POST_ 0x3446
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_TIME_1 0x3447
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_TIME_2 0x3448
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_RATIO_2 0x3449
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_RATIO_3 0x344A
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_RATIO_4 0x344B
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_NOTE_VALUE_1_ 0x344C
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_NOTE_VALUE_2_ 0x344D
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_NOTE_VALUE_3_ 0x344E
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_NOTE_VALUE_4_ 0x344F
#define BMC_KEMPER_PARAM_STOMP_C_TO_TEMPO 0x3450
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_VOLUME_1 0x3451
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_VOLUME_2 0x3452
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_VOLUME_3 0x3453
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_VOLUME_4 0x3454
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_PANORAMA_1 0x3455
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_PANORAMA_2 0x3456
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_PANORAMA_3 0x3457
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_PANORAMA_4 0x3458
#define BMC_KEMPER_PARAM_STOMP_C_VOICE3_PITCH 0x3459
#define BMC_KEMPER_PARAM_STOMP_C_VOICE4_PITCH 0x345A
#define BMC_KEMPER_PARAM_STOMP_C_VOICE3_INTERVAL 0x345B
#define BMC_KEMPER_PARAM_STOMP_C_VOICE4_INTERVAL 0x345C
#define BMC_KEMPER_PARAM_STOMP_C_FEEDBACK 0x345D
#define BMC_KEMPER_PARAM_STOMP_C_INFINITY_FEEDBACK 0x345E
#define BMC_KEMPER_PARAM_STOMP_C_INFINITY 0x345F
#define BMC_KEMPER_PARAM_STOMP_C_FEEDBACK2 0x3460
#define BMC_KEMPER_PARAM_STOMP_C_FEEDBACK_SYNC_SWITCH_ 0x3461
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_LOW_CUT 0x3462
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_HIGH_CUT 0x3463
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_FILTER_INTENSITY_ 0x3464
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_MODULATION_ 0x3465
#define BMC_KEMPER_PARAM_STOMP_C_DELAY_CHORUS 0x3466
#define BMC_KEMPER_PARAM_STOMP_C_FLUTTER_INTENSITY 0x3467
#define BMC_KEMPER_PARAM_STOMP_C_FLUTTER_SHAPE 0x3468
#define BMC_KEMPER_PARAM_STOMP_C_GRIT 0x3469
#define BMC_KEMPER_PARAM_STOMP_C_REVERSE_MIX 0x346A
#define BMC_KEMPER_PARAM_STOMP_C_SWELL 0x346B
#define BMC_KEMPER_PARAM_STOMP_C_SMEAR 0x346C
#define BMC_KEMPER_PARAM_STOMP_C_DUCKING_PRE_POST 0x346D
// KEMPER PARAM PAGE STOMP D
#define BMC_KEMPER_PARAM_STOMP_D_TYPE 0x3500
#define BMC_KEMPER_PARAM_STOMP_D_ON_OFF_4_MIX 0x3503
#define BMC_KEMPER_PARAM_STOMP_D_VOLUME_7_STEREO 0x3506
#define BMC_KEMPER_PARAM_STOMP_D_WAH_MANUAL 0x3508
#define BMC_KEMPER_PARAM_STOMP_D_WAH_PEAK 0x3509
#define BMC_KEMPER_PARAM_STOMP_D_WAH_RANGE 0x350A
#define BMC_KEMPER_PARAM_STOMP_D_WAH_PEDAL_MODE_ 0x350C
#define BMC_KEMPER_PARAM_STOMP_D_WAH_TOUCH_ATTACK_ 0x350D
#define BMC_KEMPER_PARAM_STOMP_D_WAH_TOUCH_RELEASE_ 0x350E
#define BMC_KEMPER_PARAM_STOMP_D_WAH_TOUCH_BOOST 0x350F
#define BMC_KEMPER_PARAM_STOMP_D_DISTORTION_SHAPER_DRIVE_ 0x3510
#define BMC_KEMPER_PARAM_STOMP_D_DISTORTION_BOOSTER_TONE 0x3511
#define BMC_KEMPER_PARAM_STOMP_D_COMPRESSOR_GATE_INTENSITY_ 0x3512
#define BMC_KEMPER_PARAM_STOMP_D_COMPRESSOR_ATTACK 0x3513
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_RATE 0x3514
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_DEPTH 0x3515
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_FEEDBACK 0x3516
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_CROSSOVER 0x3517
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_HYPERCHORUS_AMOUNT_ 0x3518
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_MANUAL 0x3519
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_PHASER_PEAK_SPREAD_ 0x351A
#define BMC_KEMPER_PARAM_STOMP_D_MODULATION_PHASER_STAGES 0x351B
#define BMC_KEMPER_PARAM_STOMP_D_ROTARY_SPEED__SLOW_FAST__ 0x351E
#define BMC_KEMPER_PARAM_STOMP_D_ROTARY_DISTANCE 0x351F
#define BMC_KEMPER_PARAM_STOMP_D_ROTARY_BALANCE 0x3520
#define BMC_KEMPER_PARAM_STOMP_D_COMPRESSOR_SQUASH 0x3521
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_1_ 0x3522
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_2_ 0x3523
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_3_ 0x3524
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_4_ 0x3525
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_5_ 0x3526
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_6_ 0x3527
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_7_ 0x3528
#define BMC_KEMPER_PARAM_STOMP_D_GRAPHIC_EQ_BAND_8 0x3529
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_LOW_GAIN 0x352A
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_LOW_FREQUENCY_ 0x352B
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_HIGH_GAIN 0x352C
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_HIGH_FREQUENCY_ 0x352D
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_PEAK_GAIN 0x352E
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_PEAK_FREQUENCY_ 0x352F
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_PEAK_Q_FACTOR 0x3530
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_PEAK_GAIN_2 0x3531
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_PEAK_FREQUENCY_2_ 0x3532
#define BMC_KEMPER_PARAM_STOMP_D_PARAMETRIC_EQ_PEAK_Q_FACTOR_2 0x3533
#define BMC_KEMPER_PARAM_STOMP_D_WAH_PEAK_RANGE_ 0x3534
#define BMC_KEMPER_PARAM_STOMP_D_DUCKING 0x3535
#define BMC_KEMPER_PARAM_STOMP_D_VOICE_MIX_ 0x3537
#define BMC_KEMPER_PARAM_STOMP_D_VOICE_1_PITCH_ 0x3538
#define BMC_KEMPER_PARAM_STOMP_D_VOICE_2_PITCH_ 0x3539
#define BMC_KEMPER_PARAM_STOMP_D_DETUNE 0x353A
#define BMC_KEMPER_PARAM_STOMP_D_SMOOTH_CHORDS_ 0x353C
#define BMC_KEMPER_PARAM_STOMP_D_PURE_TUNING 0x353D
#define BMC_KEMPER_PARAM_STOMP_D_KEY 0x3540
#define BMC_KEMPER_PARAM_STOMP_D_FREEZE_FORMANTS_ 0x3541
#define BMC_KEMPER_PARAM_STOMP_D_FORMANT_OFFSET_ 0x3542
#define BMC_KEMPER_PARAM_STOMP_D_LOW_CUT 0x3543
#define BMC_KEMPER_PARAM_STOMP_D_HIGH_CUT 0x3544
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_MIX 0x3545
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_MIX_PRE_POST_ 0x3546
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_TIME_1 0x3547
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_TIME_2 0x3548
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_RATIO_2 0x3549
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_RATIO_3 0x354A
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_RATIO_4 0x354B
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_NOTE_VALUE_1_ 0x354C
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_NOTE_VALUE_2_ 0x354D
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_NOTE_VALUE_3_ 0x354E
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_NOTE_VALUE_4_ 0x354F
#define BMC_KEMPER_PARAM_STOMP_D_TO_TEMPO 0x3550
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_VOLUME_1 0x3551
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_VOLUME_2 0x3552
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_VOLUME_3 0x3553
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_VOLUME_4 0x3554
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_PANORAMA_1 0x3555
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_PANORAMA_2 0x3556
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_PANORAMA_3 0x3557
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_PANORAMA_4 0x3558
#define BMC_KEMPER_PARAM_STOMP_D_VOICE3_PITCH 0x3559
#define BMC_KEMPER_PARAM_STOMP_D_VOICE4_PITCH 0x355A
#define BMC_KEMPER_PARAM_STOMP_D_VOICE3_INTERVAL 0x355B
#define BMC_KEMPER_PARAM_STOMP_D_VOICE4_INTERVAL 0x355C
#define BMC_KEMPER_PARAM_STOMP_D_FEEDBACK 0x355D
#define BMC_KEMPER_PARAM_STOMP_D_INFINITY_FEEDBACK 0x355E
#define BMC_KEMPER_PARAM_STOMP_D_INFINITY 0x355F
#define BMC_KEMPER_PARAM_STOMP_D_FEEDBACK2 0x3560
#define BMC_KEMPER_PARAM_STOMP_D_FEEDBACK_SYNC_SWITCH_ 0x3561
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_LOW_CUT 0x3562
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_HIGH_CUT 0x3563
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_FILTER_INTENSITY_ 0x3564
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_MODULATION_ 0x3565
#define BMC_KEMPER_PARAM_STOMP_D_DELAY_CHORUS 0x3566
#define BMC_KEMPER_PARAM_STOMP_D_FLUTTER_INTENSITY 0x3567
#define BMC_KEMPER_PARAM_STOMP_D_FLUTTER_SHAPE 0x3568
#define BMC_KEMPER_PARAM_STOMP_D_GRIT 0x3569
#define BMC_KEMPER_PARAM_STOMP_D_REVERSE_MIX 0x356A
#define BMC_KEMPER_PARAM_STOMP_D_SWELL 0x356B
#define BMC_KEMPER_PARAM_STOMP_D_SMEAR 0x356C
#define BMC_KEMPER_PARAM_STOMP_D_DUCKING_PRE_POST 0x356D
// KEMPER PARAM PAGE STOMP X
#define BMC_KEMPER_PARAM_STOMP_X_TYPE 0x3800
#define BMC_KEMPER_PARAM_STOMP_X_ON_OFF_4_MIX 0x3803
#define BMC_KEMPER_PARAM_STOMP_X_VOLUME_7_STEREO 0x3806
#define BMC_KEMPER_PARAM_STOMP_X_WAH_MANUAL 0x3808
#define BMC_KEMPER_PARAM_STOMP_X_WAH_PEAK 0x3809
#define BMC_KEMPER_PARAM_STOMP_X_WAH_RANGE 0x380A
#define BMC_KEMPER_PARAM_STOMP_X_WAH_PEDAL_MODE_ 0x380C
#define BMC_KEMPER_PARAM_STOMP_X_WAH_TOUCH_ATTACK_ 0x380D
#define BMC_KEMPER_PARAM_STOMP_X_WAH_TOUCH_RELEASE_ 0x380E
#define BMC_KEMPER_PARAM_STOMP_X_WAH_TOUCH_BOOST 0x380F
#define BMC_KEMPER_PARAM_STOMP_X_DISTORTION_SHAPER_DRIVE_ 0x3810
#define BMC_KEMPER_PARAM_STOMP_X_DISTORTION_BOOSTER_TONE 0x3811
#define BMC_KEMPER_PARAM_STOMP_X_COMPRESSOR_GATE_INTENSITY_ 0x3812
#define BMC_KEMPER_PARAM_STOMP_X_COMPRESSOR_ATTACK 0x3813
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_RATE 0x3814
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_DEPTH 0x3815
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_FEEDBACK 0x3816
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_CROSSOVER 0x3817
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_HYPERCHORUS_AMOUNT_ 0x3818
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_MANUAL 0x3819
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_PHASER_PEAK_SPREAD_ 0x381A
#define BMC_KEMPER_PARAM_STOMP_X_MODULATION_PHASER_STAGES 0x381B
#define BMC_KEMPER_PARAM_STOMP_X_ROTARY_SPEED__SLOW_FAST__ 0x381E
#define BMC_KEMPER_PARAM_STOMP_X_ROTARY_DISTANCE 0x381F
#define BMC_KEMPER_PARAM_STOMP_X_ROTARY_BALANCE 0x3820
#define BMC_KEMPER_PARAM_STOMP_X_COMPRESSOR_SQUASH 0x3821
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_1_ 0x3822
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_2_ 0x3823
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_3_ 0x3824
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_4_ 0x3825
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_5_ 0x3826
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_6_ 0x3827
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_7_ 0x3828
#define BMC_KEMPER_PARAM_STOMP_X_GRAPHIC_EQ_BAND_8 0x3829
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_LOW_GAIN 0x382A
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_LOW_FREQUENCY_ 0x382B
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_HIGH_GAIN 0x382C
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_HIGH_FREQUENCY_ 0x382D
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_PEAK_GAIN 0x382E
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_PEAK_FREQUENCY_ 0x382F
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_PEAK_Q_FACTOR 0x3830
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_PEAK_GAIN_2 0x3831
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_PEAK_FREQUENCY_2_ 0x3832
#define BMC_KEMPER_PARAM_STOMP_X_PARAMETRIC_EQ_PEAK_Q_FACTOR_2 0x3833
#define BMC_KEMPER_PARAM_STOMP_X_WAH_PEAK_RANGE_ 0x3834
#define BMC_KEMPER_PARAM_STOMP_X_DUCKING 0x3835
#define BMC_KEMPER_PARAM_STOMP_X_VOICE_MIX_ 0x3837
#define BMC_KEMPER_PARAM_STOMP_X_VOICE_1_PITCH_ 0x3838
#define BMC_KEMPER_PARAM_STOMP_X_VOICE_2_PITCH_ 0x3839
#define BMC_KEMPER_PARAM_STOMP_X_DETUNE 0x383A
#define BMC_KEMPER_PARAM_STOMP_X_SMOOTH_CHORDS_ 0x383C
#define BMC_KEMPER_PARAM_STOMP_X_PURE_TUNING 0x383D
#define BMC_KEMPER_PARAM_STOMP_X_KEY 0x3840
#define BMC_KEMPER_PARAM_STOMP_X_FREEZE_FORMANTS_ 0x3841
#define BMC_KEMPER_PARAM_STOMP_X_FORMANT_OFFSET_ 0x3842
#define BMC_KEMPER_PARAM_STOMP_X_LOW_CUT 0x3843
#define BMC_KEMPER_PARAM_STOMP_X_HIGH_CUT 0x3844
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_MIX 0x3845
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_MIX_PRE_POST_ 0x3846
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_TIME_1 0x3847
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_TIME_2 0x3848
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_RATIO_2 0x3849
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_RATIO_3 0x384A
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_RATIO_4 0x384B
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_NOTE_VALUE_1_ 0x384C
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_NOTE_VALUE_2_ 0x384D
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_NOTE_VALUE_3_ 0x384E
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_NOTE_VALUE_4_ 0x384F
#define BMC_KEMPER_PARAM_STOMP_X_TO_TEMPO 0x3850
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_VOLUME_1 0x3851
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_VOLUME_2 0x3852
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_VOLUME_3 0x3853
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_VOLUME_4 0x3854
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_PANORAMA_1 0x3855
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_PANORAMA_2 0x3856
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_PANORAMA_3 0x3857
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_PANORAMA_4 0x3858
#define BMC_KEMPER_PARAM_STOMP_X_VOICE3_PITCH 0x3859
#define BMC_KEMPER_PARAM_STOMP_X_VOICE4_PITCH 0x385A
#define BMC_KEMPER_PARAM_STOMP_X_VOICE3_INTERVAL 0x385B
#define BMC_KEMPER_PARAM_STOMP_X_VOICE4_INTERVAL 0x385C
#define BMC_KEMPER_PARAM_STOMP_X_FEEDBACK 0x385D
#define BMC_KEMPER_PARAM_STOMP_X_INFINITY_FEEDBACK 0x385E
#define BMC_KEMPER_PARAM_STOMP_X_INFINITY 0x385F
#define BMC_KEMPER_PARAM_STOMP_X_FEEDBACK2 0x3860
#define BMC_KEMPER_PARAM_STOMP_X_FEEDBACK_SYNC_SWITCH_ 0x3861
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_LOW_CUT 0x3862
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_HIGH_CUT 0x3863
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_FILTER_INTENSITY_ 0x3864
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_MODULATION_ 0x3865
#define BMC_KEMPER_PARAM_STOMP_X_DELAY_CHORUS 0x3866
#define BMC_KEMPER_PARAM_STOMP_X_FLUTTER_INTENSITY 0x3867
#define BMC_KEMPER_PARAM_STOMP_X_FLUTTER_SHAPE 0x3868
#define BMC_KEMPER_PARAM_STOMP_X_GRIT 0x3869
#define BMC_KEMPER_PARAM_STOMP_X_REVERSE_MIX 0x386A
#define BMC_KEMPER_PARAM_STOMP_X_SWELL 0x386B
#define BMC_KEMPER_PARAM_STOMP_X_SMEAR 0x386C
#define BMC_KEMPER_PARAM_STOMP_X_DUCKING_PRE_POST 0x386D
// KEMPER PARAM PAGE STOMP MOD
#define BMC_KEMPER_PARAM_STOMP_MOD_TYPE 0x3A00
#define BMC_KEMPER_PARAM_STOMP_MOD_ON_OFF_4_MIX 0x3A03
#define BMC_KEMPER_PARAM_STOMP_MOD_VOLUME_7_STEREO 0x3A06
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_MANUAL 0x3A08
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_PEAK 0x3A09
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_RANGE 0x3A0A
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_PEDAL_MODE_ 0x3A0C
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_TOUCH_ATTACK_ 0x3A0D
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_TOUCH_RELEASE_ 0x3A0E
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_TOUCH_BOOST 0x3A0F
#define BMC_KEMPER_PARAM_STOMP_MOD_DISTORTION_SHAPER_DRIVE_ 0x3A10
#define BMC_KEMPER_PARAM_STOMP_MOD_DISTORTION_BOOSTER_TONE 0x3A11
#define BMC_KEMPER_PARAM_STOMP_MOD_COMPRESSOR_GATE_INTENSITY_ 0x3A12
#define BMC_KEMPER_PARAM_STOMP_MOD_COMPRESSOR_ATTACK 0x3A13
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_RATE 0x3A14
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_DEPTH 0x3A15
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_FEEDBACK 0x3A16
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_CROSSOVER 0x3A17
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_HYPERCHORUS_AMOUNT_ 0x3A18
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_MANUAL 0x3A19
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_PHASER_PEAK_SPREAD_ 0x3A1A
#define BMC_KEMPER_PARAM_STOMP_MOD_MODULATION_PHASER_STAGES 0x3A1B
#define BMC_KEMPER_PARAM_STOMP_MOD_ROTARY_SPEED__SLOW_FAST__ 0x3A1E
#define BMC_KEMPER_PARAM_STOMP_MOD_ROTARY_DISTANCE 0x3A1F
#define BMC_KEMPER_PARAM_STOMP_MOD_ROTARY_BALANCE 0x3A20
#define BMC_KEMPER_PARAM_STOMP_MOD_COMPRESSOR_SQUASH 0x3A21
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_1_ 0x3A22
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_2_ 0x3A23
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_3_ 0x3A24
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_4_ 0x3A25
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_5_ 0x3A26
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_6_ 0x3A27
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_7_ 0x3A28
#define BMC_KEMPER_PARAM_STOMP_MOD_GRAPHIC_EQ_BAND_8 0x3A29
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_LOW_GAIN 0x3A2A
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_LOW_FREQUENCY_ 0x3A2B
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_HIGH_GAIN 0x3A2C
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_HIGH_FREQUENCY_ 0x3A2D
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_PEAK_GAIN 0x3A2E
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_PEAK_FREQUENCY_ 0x3A2F
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_PEAK_Q_FACTOR 0x3A30
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_PEAK_GAIN_2 0x3A31
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_PEAK_FREQUENCY_2_ 0x3A32
#define BMC_KEMPER_PARAM_STOMP_MOD_PARAMETRIC_EQ_PEAK_Q_FACTOR_2 0x3A33
#define BMC_KEMPER_PARAM_STOMP_MOD_WAH_PEAK_RANGE_ 0x3A34
#define BMC_KEMPER_PARAM_STOMP_MOD_DUCKING 0x3A35
#define BMC_KEMPER_PARAM_STOMP_MOD_VOICE_MIX_ 0x3A37
#define BMC_KEMPER_PARAM_STOMP_MOD_VOICE_1_PITCH_ 0x3A38
#define BMC_KEMPER_PARAM_STOMP_MOD_VOICE_2_PITCH_ 0x3A39
#define BMC_KEMPER_PARAM_STOMP_MOD_DETUNE 0x3A3A
#define BMC_KEMPER_PARAM_STOMP_MOD_SMOOTH_CHORDS_ 0x3A3C
#define BMC_KEMPER_PARAM_STOMP_MOD_PURE_TUNING 0x3A3D
#define BMC_KEMPER_PARAM_STOMP_MOD_KEY 0x3A40
#define BMC_KEMPER_PARAM_STOMP_MOD_FREEZE_FORMANTS_ 0x3A41
#define BMC_KEMPER_PARAM_STOMP_MOD_FORMANT_OFFSET_ 0x3A42
#define BMC_KEMPER_PARAM_STOMP_MOD_LOW_CUT 0x3A43
#define BMC_KEMPER_PARAM_STOMP_MOD_HIGH_CUT 0x3A44
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_MIX 0x3A45
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_MIX_PRE_POST_ 0x3A46
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_TIME_1 0x3A47
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_TIME_2 0x3A48
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_RATIO_2 0x3A49
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_RATIO_3 0x3A4A
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_RATIO_4 0x3A4B
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_NOTE_VALUE_1_ 0x3A4C
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_NOTE_VALUE_2_ 0x3A4D
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_NOTE_VALUE_3_ 0x3A4E
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_NOTE_VALUE_4_ 0x3A4F
#define BMC_KEMPER_PARAM_STOMP_MOD_TO_TEMPO 0x3A50
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_VOLUME_1 0x3A51
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_VOLUME_2 0x3A52
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_VOLUME_3 0x3A53
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_VOLUME_4 0x3A54
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_PANORAMA_1 0x3A55
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_PANORAMA_2 0x3A56
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_PANORAMA_3 0x3A57
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_PANORAMA_4 0x3A58
#define BMC_KEMPER_PARAM_STOMP_MOD_VOICE3_PITCH 0x3A59
#define BMC_KEMPER_PARAM_STOMP_MOD_VOICE4_PITCH 0x3A5A
#define BMC_KEMPER_PARAM_STOMP_MOD_VOICE3_INTERVAL 0x3A5B
#define BMC_KEMPER_PARAM_STOMP_MOD_VOICE4_INTERVAL 0x3A5C
#define BMC_KEMPER_PARAM_STOMP_MOD_FEEDBACK 0x3A5D
#define BMC_KEMPER_PARAM_STOMP_MOD_INFINITY_FEEDBACK 0x3A5E
#define BMC_KEMPER_PARAM_STOMP_MOD_INFINITY 0x3A5F
#define BMC_KEMPER_PARAM_STOMP_MOD_FEEDBACK2 0x3A60
#define BMC_KEMPER_PARAM_STOMP_MOD_FEEDBACK_SYNC_SWITCH_ 0x3A61
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_LOW_CUT 0x3A62
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_HIGH_CUT 0x3A63
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_FILTER_INTENSITY_ 0x3A64
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_MODULATION_ 0x3A65
#define BMC_KEMPER_PARAM_STOMP_MOD_DELAY_CHORUS 0x3A66
#define BMC_KEMPER_PARAM_STOMP_MOD_FLUTTER_INTENSITY 0x3A67
#define BMC_KEMPER_PARAM_STOMP_MOD_FLUTTER_SHAPE 0x3A68
#define BMC_KEMPER_PARAM_STOMP_MOD_GRIT 0x3A69
#define BMC_KEMPER_PARAM_STOMP_MOD_REVERSE_MIX 0x3A6A
#define BMC_KEMPER_PARAM_STOMP_MOD_SWELL 0x3A6B
#define BMC_KEMPER_PARAM_STOMP_MOD_SMEAR 0x3A6C
#define BMC_KEMPER_PARAM_STOMP_MOD_DUCKING_PRE_POST 0x3A6D
// KEMPER PARAM PAGE STOMP DELAY
#define BMC_KEMPER_PARAM_STOMP_DELAY_TYPE 0x3C00
#define BMC_KEMPER_PARAM_STOMP_DELAY_ON_OFF_4_MIX 0x3C03
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOLUME_7_STEREO 0x3C06
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_MANUAL 0x3C08
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_PEAK 0x3C09
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_RANGE 0x3C0A
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_PEDAL_MODE_ 0x3C0C
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_TOUCH_ATTACK_ 0x3C0D
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_TOUCH_RELEASE_ 0x3C0E
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_TOUCH_BOOST 0x3C0F
#define BMC_KEMPER_PARAM_STOMP_DELAY_DISTORTION_SHAPER_DRIVE_ 0x3C10
#define BMC_KEMPER_PARAM_STOMP_DELAY_DISTORTION_BOOSTER_TONE 0x3C11
#define BMC_KEMPER_PARAM_STOMP_DELAY_COMPRESSOR_GATE_INTENSITY_ 0x3C12
#define BMC_KEMPER_PARAM_STOMP_DELAY_COMPRESSOR_ATTACK 0x3C13
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_RATE 0x3C14
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_DEPTH 0x3C15
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_FEEDBACK 0x3C16
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_CROSSOVER 0x3C17
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_HYPERCHORUS_AMOUNT_ 0x3C18
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_MANUAL 0x3C19
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_PHASER_PEAK_SPREAD_ 0x3C1A
#define BMC_KEMPER_PARAM_STOMP_DELAY_MODULATION_PHASER_STAGES 0x3C1B
#define BMC_KEMPER_PARAM_STOMP_DELAY_ROTARY_SPEED__SLOW_FAST__ 0x3C1E
#define BMC_KEMPER_PARAM_STOMP_DELAY_ROTARY_DISTANCE 0x3C1F
#define BMC_KEMPER_PARAM_STOMP_DELAY_ROTARY_BALANCE 0x3C20
#define BMC_KEMPER_PARAM_STOMP_DELAY_COMPRESSOR_SQUASH 0x3C21
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_1_ 0x3C22
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_2_ 0x3C23
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_3_ 0x3C24
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_4_ 0x3C25
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_5_ 0x3C26
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_6_ 0x3C27
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_7_ 0x3C28
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRAPHIC_EQ_BAND_8 0x3C29
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_LOW_GAIN 0x3C2A
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_LOW_FREQUENCY_ 0x3C2B
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_HIGH_GAIN 0x3C2C
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_HIGH_FREQUENCY_ 0x3C2D
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_PEAK_GAIN 0x3C2E
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_PEAK_FREQUENCY_ 0x3C2F
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_PEAK_Q_FACTOR 0x3C30
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_PEAK_GAIN_2 0x3C31
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_PEAK_FREQUENCY_2_ 0x3C32
#define BMC_KEMPER_PARAM_STOMP_DELAY_PARAMETRIC_EQ_PEAK_Q_FACTOR_2 0x3C33
#define BMC_KEMPER_PARAM_STOMP_DELAY_WAH_PEAK_RANGE_ 0x3C34
#define BMC_KEMPER_PARAM_STOMP_DELAY_DUCKING 0x3C35
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOICE_MIX_ 0x3C37
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOICE_1_PITCH_ 0x3C38
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOICE_2_PITCH_ 0x3C39
#define BMC_KEMPER_PARAM_STOMP_DELAY_DETUNE 0x3C3A
#define BMC_KEMPER_PARAM_STOMP_DELAY_SMOOTH_CHORDS_ 0x3C3C
#define BMC_KEMPER_PARAM_STOMP_DELAY_PURE_TUNING 0x3C3D
#define BMC_KEMPER_PARAM_STOMP_DELAY_KEY 0x3C40
#define BMC_KEMPER_PARAM_STOMP_DELAY_FREEZE_FORMANTS_ 0x3C41
#define BMC_KEMPER_PARAM_STOMP_DELAY_FORMANT_OFFSET_ 0x3C42
#define BMC_KEMPER_PARAM_STOMP_DELAY_LOW_CUT 0x3C43
#define BMC_KEMPER_PARAM_STOMP_DELAY_HIGH_CUT 0x3C44
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_MIX 0x3C45
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_MIX_PRE_POST_ 0x3C46
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_TIME_1 0x3C47
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_TIME_2 0x3C48
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_RATIO_2 0x3C49
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_RATIO_3 0x3C4A
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_RATIO_4 0x3C4B
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_NOTE_VALUE_1_ 0x3C4C
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_NOTE_VALUE_2_ 0x3C4D
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_NOTE_VALUE_3_ 0x3C4E
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_NOTE_VALUE_4_ 0x3C4F
#define BMC_KEMPER_PARAM_STOMP_DELAY_TO_TEMPO 0x3C50
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_VOLUME_1 0x3C51
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_VOLUME_2 0x3C52
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_VOLUME_3 0x3C53
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_VOLUME_4 0x3C54
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_PANORAMA_1 0x3C55
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_PANORAMA_2 0x3C56
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_PANORAMA_3 0x3C57
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_PANORAMA_4 0x3C58
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOICE3_PITCH 0x3C59
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOICE4_PITCH 0x3C5A
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOICE3_INTERVAL 0x3C5B
#define BMC_KEMPER_PARAM_STOMP_DELAY_VOICE4_INTERVAL 0x3C5C
#define BMC_KEMPER_PARAM_STOMP_DELAY_FEEDBACK 0x3C5D
#define BMC_KEMPER_PARAM_STOMP_DELAY_INFINITY_FEEDBACK 0x3C5E
#define BMC_KEMPER_PARAM_STOMP_DELAY_INFINITY 0x3C5F
#define BMC_KEMPER_PARAM_STOMP_DELAY_FEEDBACK2 0x3C60
#define BMC_KEMPER_PARAM_STOMP_DELAY_FEEDBACK_SYNC_SWITCH_ 0x3C61
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_LOW_CUT 0x3C62
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_HIGH_CUT 0x3C63
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_FILTER_INTENSITY_ 0x3C64
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_MODULATION_ 0x3C65
#define BMC_KEMPER_PARAM_STOMP_DELAY_DELAY_CHORUS 0x3C66
#define BMC_KEMPER_PARAM_STOMP_DELAY_FLUTTER_INTENSITY 0x3C67
#define BMC_KEMPER_PARAM_STOMP_DELAY_FLUTTER_SHAPE 0x3C68
#define BMC_KEMPER_PARAM_STOMP_DELAY_GRIT 0x3C69
#define BMC_KEMPER_PARAM_STOMP_DELAY_REVERSE_MIX 0x3C6A
#define BMC_KEMPER_PARAM_STOMP_DELAY_SWELL 0x3C6B
#define BMC_KEMPER_PARAM_STOMP_DELAY_SMEAR 0x3C6C
#define BMC_KEMPER_PARAM_STOMP_DELAY_DUCKING_PRE_POST 0x3C6D
// KEMPER PARAM PAGE REVERB
#define BMC_KEMPER_PARAM_REVERB_TYPE 0x4B00
#define BMC_KEMPER_PARAM_REVERB_ON_OFF__CUTS_TAIL_ 0x4B02
#define BMC_KEMPER_PARAM_REVERB_MIX 0x4B03
#define BMC_KEMPER_PARAM_REVERB_VOLUME 0x4B04
#define BMC_KEMPER_PARAM_REVERB_DEL_REV_BALANCE 0x4B05
#define BMC_KEMPER_PARAM_REVERB_TIME 0x4B06
#define BMC_KEMPER_PARAM_REVERB_DAMPING 0x4B07
#define BMC_KEMPER_PARAM_REVERB_BANDWIDTH 0x4B08
#define BMC_KEMPER_PARAM_REVERB_CENTER_FREQUENCY_ 0x4B09
#define BMC_KEMPER_PARAM_REVERB_PRE_DELAY 0x4B0A
#define BMC_KEMPER_PARAM_REVERB_ON_OFF__KEEPS_TAIL__ 0x4B0B
#define BMC_KEMPER_PARAM_REVERB_DUCKING 0x4B0C
// KEMPER PARAM PAGE SYSTEM GLOBAL
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_STOMP_A_HOLD_108_STOMP_B_HOLD_ 0x7D6B
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_STOMP_C_HOLD_110_STOMP_D_HOLD_ 0x7D6D
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_STOMP_X_HOLD_113_STOMP_MOD_HOLD_ 0x7D6F
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_STOMP_DLY_HOLD 0x7D72
// KEMPER PARAM PAGE SYSTEM GLOBAL
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MAIN_OUTPUT_VOLUME 0x7F00
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_HEADPHONE_OUTPUT_VOLUME_ 0x7F01
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MONITOR_OUTPUT_VOLUME 0x7F02
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_DIRECT_OUTPUT_VOLUME 0x7F03
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_SPDIF_INPUT_ENABLE 0x7F0B
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MAIN_OUTPUT_EQ_BASS 0x7F0C
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MAIN_OUTPUT_EQ_MIDDLE 0x7F0D
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MAIN_OUTPUT_EQ_TREBLE 0x7F0E
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MAIN_OUTPUT_EQ_PRESENCE 0x7F0F
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MONITOR_OUTPUT_EQ_BASS 0x7F11
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MONITOR_OUTPUT_EQ_MIDDLE 0x7F12
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MONITOR_OUTPUT_EQ_TREBLE 0x7F13
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_MONITOR_OUTPUT_EQ_PRESENCE 0x7F14
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_LOOPER_VOLUME_ 0x7F34
#define BMC_KEMPER_PARAM_SYSTEM_GLOBAL_LOOPER_LOCATION 0x7F35



// EDITOR POT STYLE
#define BMC_EDITOR_POT_STYLE_KNOB 0
#define BMC_EDITOR_POT_STYLE_FADER 1
#define BMC_EDITOR_POT_STYLE_EXPRESSION 2

// RELAY
#define BMC_RELAY_EVENT_TYPE_PRESET 1
#define BMC_RELAY_EVENT_TYPE_PAGE 2
// 8 user defined events
// this feature will be added to the editor and documented later on
#define BMC_RELAY_EVENT_TYPE_USER_1 118
#define BMC_RELAY_EVENT_TYPE_USER_2 119
#define BMC_RELAY_EVENT_TYPE_USER_3 120
#define BMC_RELAY_EVENT_TYPE_USER_4 121
#define BMC_RELAY_EVENT_TYPE_USER_5 122
#define BMC_RELAY_EVENT_TYPE_USER_6 123
#define BMC_RELAY_EVENT_TYPE_USER_7 124
#define BMC_RELAY_EVENT_TYPE_USER_8 125


// POT EVENT TYPES
#define BMC_POT_EVENT_TYPE_CLOCK 1
#define BMC_POT_EVENT_TYPE_BEATBUDDY_CMD 2
#define BMC_POT_EVENT_TYPE_CLICK_TRACK_FREQ 3
#define BMC_POT_EVENT_TYPE_CLICK_TRACK_LEVEL 4
// 8 user defined events
// this feature will be added to the editor and documented later on
#define BMC_POT_EVENT_TYPE_USER_1 118
#define BMC_POT_EVENT_TYPE_USER_2 119
#define BMC_POT_EVENT_TYPE_USER_3 120
#define BMC_POT_EVENT_TYPE_USER_4 121
#define BMC_POT_EVENT_TYPE_USER_5 122
#define BMC_POT_EVENT_TYPE_USER_6 123
#define BMC_POT_EVENT_TYPE_USER_7 124
#define BMC_POT_EVENT_TYPE_USER_8 125



// ENCODER EVENT TYPES
#define BMC_ENCODER_EVENT_TYPE_CLOCK 1
#define BMC_ENCODER_EVENT_TYPE_PAGES 2
#define BMC_ENCODER_EVENT_TYPE_PRESETS 3
#define BMC_ENCODER_EVENT_TYPE_TMP_SCROLLER_PAGES 4
#define BMC_ENCODER_EVENT_TYPE_TMP_SCROLLER_PRESETS 5
#define BMC_ENCODER_EVENT_TYPE_BEATBUDDY_CMD 6
#define BMC_ENCODER_EVENT_TYPE_LIBRARY 7
#define BMC_ENCODER_EVENT_TYPE_CUSTOM_SYSEX 8
#define BMC_ENCODER_EVENT_TYPE_PROGRAM_BANKING_SCROLL 9
#define BMC_ENCODER_EVENT_TYPE_CLICK_TRACK_FREQ 20
#define BMC_ENCODER_EVENT_TYPE_CLICK_TRACK_LEVEL 21
#define BMC_ENCODER_EVENT_TYPE_FAS_PRESET 80
#define BMC_ENCODER_EVENT_TYPE_FAS_SCENE 81
#define BMC_ENCODER_EVENT_TYPE_FAS_PARAM 82
#define BMC_ENCODER_EVENT_TYPE_MENU 110
// 8 user defined events
// this feature will be added to the editor and documented later on
#define BMC_ENCODER_EVENT_TYPE_USER_1 118
#define BMC_ENCODER_EVENT_TYPE_USER_2 119
#define BMC_ENCODER_EVENT_TYPE_USER_3 120
#define BMC_ENCODER_EVENT_TYPE_USER_4 121
#define BMC_ENCODER_EVENT_TYPE_USER_5 122
#define BMC_ENCODER_EVENT_TYPE_USER_6 123
#define BMC_ENCODER_EVENT_TYPE_USER_7 124
#define BMC_ENCODER_EVENT_TYPE_USER_8 125

// TRIGGER TYPES
#define BMC_TRIGGER_EVENT_TYPE_RELAY_MESSAGE 0
#define BMC_TRIGGER_EVENT_TYPE_CLOCK_TAP 1
#define BMC_TRIGGER_EVENT_TYPE_BUTTON 2
#define BMC_TRIGGER_EVENT_TYPE_LIBRARY 3
#define BMC_TRIGGER_EVENT_TYPE_LIBRARY2 4
#define BMC_TRIGGER_EVENT_TYPE_LIBRARY3 5
#define BMC_TRIGGER_EVENT_TYPE_PRESET 6
#define BMC_TRIGGER_EVENT_TYPE_PRESET_SCROLL 7
#define BMC_TRIGGER_EVENT_TYPE_PAGE 8
#define BMC_TRIGGER_EVENT_TYPE_PAGE_SCROLL 9
#define BMC_TRIGGER_EVENT_TYPE_PAGE_ACTIVE_SENSE 10
#define BMC_TRIGGER_EVENT_TYPE_RELAY_NL_CONTROL 12
#define BMC_TRIGGER_EVENT_TYPE_RELAY_L_CONTROL 13
#define BMC_TRIGGER_EVENT_TYPE_SETLIST 14
#define BMC_TRIGGER_EVENT_TYPE_SETLIST_SCROLL 15
#define BMC_TRIGGER_EVENT_TYPE_SETLIST_SONG 16
#define BMC_TRIGGER_EVENT_TYPE_SETLIST_SONG_SCROLL 17
#define BMC_TRIGGER_EVENT_TYPE_GLOBAL_BUTTON 18
#define BMC_TRIGGER_EVENT_TYPE_ENCODER 19
#define BMC_TRIGGER_EVENT_TYPE_GLOBAL_ENCODER 20
#define BMC_TRIGGER_EVENT_TYPE_CUSTOM 127

// flags used by BMCEditorMidiFlags
// only use 7 bits of a uint8_t
#define BMC_EDITOR_SYSEX_FLAG_WRITE 0
#define BMC_EDITOR_SYSEX_FLAG_PAGE 1
#define BMC_EDITOR_SYSEX_FLAG_ALL_PAGES 2
#define BMC_EDITOR_SYSEX_FLAG_BACKUP 3
#define BMC_EDITOR_SYSEX_FLAG_ERROR 4

// BMC Controller functions
#define BMC_CTRL_GROUP_HARDWARE 0
#define BMC_CTRL_GROUP_PRESET 1
#define BMC_CTRL_GROUP_CLICK_TRACK 2
  // BMC_CTRL_GROUP_HARDWARE 0
  #define BMC_CTRL_PAGE_GET 0
  #define BMC_CTRL_PAGE_SET 1
  #define BMC_CTRL_BUTTON_TRIGGER_TOGGLE 2
  #define BMC_CTRL_BUTTON_TRIGGER_PRESS 3
  #define BMC_CTRL_BUTTON_TRIGGER_RELEASE 4
  #define BMC_CTRL_LED_STATES 5
  #define BMC_CTRL_LED_TEST 6
  #define BMC_CTRL_PWM_LED_STATES 7
  #define BMC_CTRL_PWM_LED_TEST 8
  #define BMC_CTRL_PIXEL_STATES 9
  #define BMC_CTRL_PIXEL_TEST 10
  #define BMC_CTRL_GLOBAL_LED_STATES 11
  #define BMC_CTRL_GLOBAL_LED_TEST 12
  #define BMC_CTRL_POT_STATES 13
  #define BMC_CTRL_POT_CALIBRATION 14
  #define BMC_CTRL_POT_CALIBRATION_CANCEL 15
  // RELAYS
  #define BMC_CTRL_NL_RELAYS_GET 16
  #define BMC_CTRL_NL_RELAYS_OPEN 17
  #define BMC_CTRL_NL_RELAYS_CLOSE 18
  #define BMC_CTRL_NL_RELAYS_TOGGLE 19
  #define BMC_CTRL_L_RELAYS_GET 20
  #define BMC_CTRL_L_RELAYS_SET 21
  #define BMC_CTRL_L_RELAYS_RESET 22
  #define BMC_CTRL_L_RELAYS_TOGGLE 23

  #define BMC_CTRL_GLOBAL_POT_STATES 24
  #define BMC_CTRL_GLOBAL_POT_CALIBRATION 25
  #define BMC_CTRL_GLOBAL_POT_CALIBRATION_CANCEL 26
  // AUX JACKS
  #define BMC_CTRL_AUX_JACK_STATES 27
  // keep 28 and 29 available
  // RGB PIXELS
  #define BMC_CTRL_RGB_PIXEL_STATES 30
  #define BMC_CTRL_RGB_PIXEL_TEST 31
  // BMC_CTRL_GROUP_PRESET 1
  #define BMC_CTRL_PRESET_GET 0
  #define BMC_CTRL_PRESET_SET 1
  // BMC_CTRL_GROUP_CLICK_TRACK 2
  #define BMC_CTRL_CLICK_TRACK_ALL 0
  #define BMC_CTRL_CLICK_TRACK_FREQUENCY 1
  #define BMC_CTRL_CLICK_TRACK_LEVEL 2
  #define BMC_CTRL_CLICK_TRACK_MUTE 3


// INCLUDE ALL DEPENDENCIES
#include "BMC-Version.h"
#include "utility/BMC-SerialMonitor.h"
#include "utility/BMC-Debug.h"
#include "storage/BMC-Store.h"
#include "utility/BMC-Scroller.h"
#include "utility/BMC-TmpScroller.h"
#include "utility/BMC-Structs.h"
#include "utility/BMC-PixelColors.h"
#include "utility/BMC-BuildData.h"
#include "utility/BMC-MidiMessage.h"
#include "utility/BMC-MidiControl.h"
#include "utility/BMC-Timer.h"
#include "utility/BMC-Flags.h"
#include "utility/BMC-Tools.h"
#include "utility/BMC-Settings.h"
#include "utility/BMC-BpmCalculator.h"
#include "utility/BMC-Callbacks.h"
#include "utility/BMC-Globals.h"
#include "utility/SSD1306.h"

#endif
