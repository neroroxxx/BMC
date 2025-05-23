/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/


#ifndef BMC_MIDI_H
#define BMC_MIDI_H

#include "utility/BMC-Def.h"



#if defined(BMC_FOR_TEENSY)
  // *****************************************************************************
  // *          For Teensy use USB MIDI, no need to do anything special.         
  // *****************************************************************************
  #define USB_MIDI_PORT usbMIDI
  #define BLE_MIDI_PORT midiBle.Port

#elif defined(BMC_FOR_ESP32)
  // *****************************************************************************
  // *        For ESP32 use BLE if the esp32 model doesn't have native usb       
  // * The only board that BMC will support with Native USB will be the ESP32-S3
  // *   I want to keep things as simple as possible, more MCUs = more headaches 
  // *   BMC does require the USB port to be available so for boards without it  
  // *  emulates it using BLE MIDI, the built-in BLE port takes the place USB as 
  // *    the first and main port, this mainly applies to the ESP32 DEVKIT and   
  // *     ESP32 MicroMod, these boards are mainly supported because at least    
  // *         ESP32 DEVKIT is one of the most available boards out there        
  // *****************************************************************************

  #if BMC_MCU_HAS_USB == false && BMC_MCU_HAS_BLE == true
    // *****************************************************************************
    // *                     ESP32 DEVKIT V1 and ESP32 MicroMod                    
    // *                            No Native USB Support                           
    // *                           Use BLE on them Instead                          
    // *****************************************************************************
    #define BMC_ESP32_USE_BLE_AS_USB
    #define USB_MIDI_PORT usbMIDIESP32

    #include "midi/BMC-ESP32-BLE.h"
    #include "midi/BMC-SerialMIDI.h"

  #elif BMC_MCU_HAS_USB == true
    // *****************************************************************************
    // *                         For ESP32-S2 and ESP32-S23                        
    // *              These have Native USB so they use it for USB MIDI             
    // *            The S3 has BLE built-in so it's automatically enabled           
    // *           The S2 doesn't have BLE, only USB MIDI will be available         
    // *****************************************************************************
    #define BMC_ESP32_USE_NATIVE_USB

    #if BMC_MCU_HAS_BLE == true
      // *****************************************************************************
      // *            The S3 has BLE built-in so it's automatically enabled           
      // *****************************************************************************
      #include "midi/BMC-ESP32-BLE.h"
      #define BLE_MIDI_PORT midiBle
    #endif

    // *****************************************************************************
    // *                  Use AdaFruit's tinyUSB to handle USB MIDI                 
    // *****************************************************************************
    #define TINYUSB_DEVICE_CDC 1
    #define TINYUSB_DEVICE_MIDI 1
    #define USB_MIDI_PORT usbMIDI
    #include <Adafruit_TinyUSB.h>
    #include "midi/BMC-SerialMIDI.h"

  #endif

#endif


#define BMC_FLAG_MIDI_LISTENER_ENABLE 0
#define BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT 1
#define BMC_FLAG_MIDI_REAL_TIME_BLOCK_OUTPUT 2

#ifdef BMC_HAS_SERIAL_MIDI
  #include "midi/BMC-MidiPortSerial.h"
#endif

#ifdef BMC_USB_HOST_ENABLED
  #include "midi/BMC-MidiPortHost.h"
#endif

// *****************************************************************************
// *          The BLE port when using Teensy is designed to use MIDIBLE         
// *          a ESP32 powered BLE module that translates BLE to Serial         
// *              when using ESP32 it instead uses the built-in BLE             
// *****************************************************************************
#if defined(BMC_MIDI_BLE_ENABLED) && defined(BMC_FOR_TEENSY)
  #include "midi/BMC-MidiPortBle.h"
#endif

#include "midi/BMC-MidiRouting.h"

class BMCMidi {
public:
  // message holds the incoming MIDI message read from any of the ports
  // it must remain public to be easily accessible thruout BMC
  // it can be passed to any other objects or accessed thru the BMCMidi object
  BMCMidiMessage message;
  BMCCallbacks& callback;
  BMCGlobals& globals;

#if defined(BMC_ESP32_USE_BLE_AS_USB)
  // * use BLE as the USB MIDI replacement
  BMCEsp32BleMidi midiBleTransport;
  BMCSerialMIDI <BMC_MIDI_PORT_USB_BIT, BMCEsp32BleMidi, 0, true> USB_MIDI_PORT;

#elif defined(BMC_ESP32_USE_NATIVE_USB)
  // *****************************************************************************
  // *       Use Native USB on ESP32, Teensy doesn't need any of this stuff.      
  // * The Adafruit's USB MIDI is designed to be used with the Arduino MIDI library
  // * BMC has it's own MIDI library that is much more lightweight as it doesn't
  // * need all the features of the MIDI Library, BMCSerialMIDI also takes
  // *    a transport layer so it's used here with tinyUSB MIDI implementation   
  // *****************************************************************************
  Adafruit_USBD_MIDI midiUSBTransport;
  BMCSerialMIDI <BMC_MIDI_PORT_USB_BIT, Adafruit_USBD_MIDI, 0, false> USB_MIDI_PORT;

  #if BMC_MCU_HAS_BLE == true
    // *****************************************************************************
    // *         If the ESP32 has BLE (S3) then enable the built-in BLE MIDI        
    // *      Also set the Port Bit to the BLE port bit (BMC_MIDI_PORT_BLE_BIT)     
    // *****************************************************************************
    BMCEsp32BleMidi midiBleTransport;
    BMCSerialMIDI <BMC_MIDI_PORT_BLE_BIT, BMCEsp32BleMidi, 0, true> BLE_MIDI_PORT;
  #endif
#endif

  BMCMidi(BMCCallbacks& cb, BMCGlobals& t_globals):
    callback(cb),
    globals(t_globals)

// * initialize the Native USB and BLE as USB objects
#if defined(BMC_ESP32_USE_BLE_AS_USB)
    ,midiBleTransport(t_globals)
    ,USB_MIDI_PORT(midiBleTransport)
#elif defined(BMC_ESP32_USE_NATIVE_USB)
    ,USB_MIDI_PORT(midiUSBTransport)
#endif

#if defined(BMC_HAS_SERIAL_MIDI)
    ,midiSerial(cb)
#endif

#if defined(BMC_USB_HOST_ENABLED)
    ,midiHost(cb, t_globals)
#endif


// * initialize the BLE Port
#if defined(BMC_MIDI_BLE_ENABLED)
  #if defined(BMC_ESP32_USE_NATIVE_USB)
    // * for a board with Native USB and BLE we use the built-in BLE
    ,midiBleTransport(t_globals)
    ,BLE_MIDI_PORT(midiBleTransport)
  #else
    // * BLE over Serial using MIDIBLE
    ,midiBle(cb, t_globals)
  #endif
#endif

    {
    flags.reset();
    
  }

  void begin(){
    BMC_PRINTLN("BMCMidi::begin");

#if defined(BMC_ESP32_USE_BLE_AS_USB) ||defined(BMC_ESP32_USE_NATIVE_USB)
    #if defined(BMC_ESP32_USE_NATIVE_USB)
      if (!TinyUSBDevice.isInitialized()) {
        TinyUSBDevice.begin(0);
      }
      midiUSBTransport.setStringDescriptor(BMC_DEVICE_NAME);
      TinyUSBDevice.setProductDescriptor(BMC_DEVICE_NAME);
    #endif

    USB_MIDI_PORT.begin();

    #if defined(BMC_ESP32_USE_NATIVE_USB)
      BMC_PRINTLN(" (i) TinyUSBDevice checking for attached device.");
      if (TinyUSBDevice.mounted()) {
        TinyUSBDevice.detach();
        delay(10);
        TinyUSBDevice.attach();
      }
      delay(500);
      BMC_PRINTLN(" (i) TinyUSBDevice Mounted");
    #endif
#endif

#ifdef BMC_HAS_SERIAL_MIDI
      midiSerial.begin();
#endif

#ifdef BMC_USB_HOST_ENABLED
      midiHost.begin();
#endif

#ifdef BMC_MIDI_BLE_ENABLED
      midiBle.begin();
#endif
    
    
  }
  void flush(){
    #ifdef BMC_HAS_SERIAL_MIDI
      midiSerial.flush();
    #endif
  }

  BMCMidiMessage read(){
    message.reset();

    #if defined(BMC_FOR_TEENSY)
      // *****************************************************************************
      // *          When using Teensy we deal with the usbMIDI port directly         
      // *****************************************************************************
      if(USB_MIDI_PORT.read()){
        message.reset(BMC_MIDI_PORT_USB_BIT);
        message.setStatus(USB_MIDI_PORT.getType());
        if(message.isSystemRealTimeStatus()){
          if(!flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT)){
            routing(message);
          } else {
            message.reset();
          }
          return message;
        }
        message.setData1(USB_MIDI_PORT.getData1());
        message.setData2(USB_MIDI_PORT.getData2());
        if(message.isSystemExclusive()){
          message.setData1(0);
          message.setData2(0);
          if(USB_MIDI_PORT.getSysExArrayLength() <= BMC_MIDI_SYSEX_SIZE){
            message.addSysEx(
              USB_MIDI_PORT.getSysExArray(),
              USB_MIDI_PORT.getSysExArrayLength()
            );
          } else {
            message.setStatus(BMC_NONE);
          }
        } else if(message.isChannelStatus()){
          message.setChannel(USB_MIDI_PORT.getChannel());
          addToLocalData(message);
        }
        routing(message);
      }

    #elif defined(BMC_FOR_ESP32)

      // *****************************************************************************
      // *          When dealing with the ESP32 we either use BLE MIDI or the         
      // *                     Native USB which uses BMCSerialMIDI                    
      // *****************************************************************************
      if(USB_MIDI_PORT.read(message, flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT))){
        routing(message);
        addToLocalData(message);
      }

    #endif

    return message;
  }

  // BMCMidiMessage readSerial(uint8_t port=0){
  //   message.reset();
  //   if(midiSerial.read(port, message, flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT))){
  //     routing(message);
  //     addToLocalData(message);
  //   }
  //   return message;
  // }


  bool isSkipped(uint8_t type){
    return (type==BMC_MIDI_RT_CLOCK || type==BMC_MIDI_RT_ACTIVE_SENSE);
  }
  void setRealTimeBlockInput(bool value){
    flags.write(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT, value);
  }
  bool toggleRealTimeBlockInput(){
    return flags.toggle(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT);
  }
  bool getRealTimeBlockInput(){
    return flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT);
  }
  void setRealTimeBlockOutput(bool value){
    flags.write(BMC_FLAG_MIDI_REAL_TIME_BLOCK_OUTPUT, value);
  }
  bool toggleRealTimeBlockOutput(){
    return flags.toggle(BMC_FLAG_MIDI_REAL_TIME_BLOCK_OUTPUT);
  }
  bool getRealTimeBlockOutput(){
    return flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_OUTPUT);
  }

#ifdef BMC_HAS_SERIAL_MIDI
  //To read from each of the 4 serial ports you index them with 0,
  //Serial A is 0 midi
  BMCMidiMessage readSerial(uint8_t port=0){
    message.reset();
    if(midiSerial.read(port, message, flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT))){
      routing(message);
      addToLocalData(message);
    }
    return message;
  }
#endif

#ifdef BMC_USB_HOST_ENABLED
  BMCMidiMessage readHost(){
    message.reset();
    if(midiHost.read(message, flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT))){
      routing(message);
      addToLocalData(message);
    }
    return message;
  }
#endif

#ifdef BMC_MIDI_BLE_ENABLED
  BMCMidiMessage readBle(){
    message.reset();
    if(midiBle.read(message, flags.read(BMC_FLAG_MIDI_REAL_TIME_BLOCK_INPUT))){
      routing(message);
      addToLocalData(message);
    }
    return message;
  }
#endif

  void disconnectBLE(){
#ifdef BMC_MIDI_BLE_ENABLED
    // midiBle.disconnectBLE();
#endif
  }

#if defined(BMC_DEBUG)
  void setDebugOut(bool t_debug){
    debug = t_debug;
  }
  void setDebugClockOut(bool t_debug){
    debugClock = t_debug;
  }
  void toggleDebugOut(){
    debug = !debug;
  }
  void toggleDebugClockOut(){
    debugClock = !debugClock;
  }
  bool getDebugOut(){
    return debug;
  }
  bool getDebugClockOut(){
    return debugClock;
  }
#endif

  // *Routing*
  void setRouting(uint8_t t_port, uint16_t t_data){
    midiRouting.assign(t_port, t_data);
  }

  BMCMidiMessage getMessage(){
    return message;
  }
  // BMC-Midi.cpp
  void send(BMCMidiMessage m, uint8_t cable=0);
  void send(uint8_t port, BMCMidiMessage m, uint8_t cable=0);
  void send(uint8_t ports, uint32_t event);
  void send(uint32_t event);
  void send(BMCMidiEvent event, uint8_t cable=0);
  void send(uint8_t port, uint8_t type,
            uint8_t data1=0, uint8_t data2=0,
            uint8_t channel=0, uint8_t cable=0);
  void sendRealTime(uint8_t port, uint8_t type, uint8_t cable=0);
  void sendSysEx(uint8_t port, uint8_t *data,
                  uint16_t size, bool hasTerm=false,
                  uint8_t cable=0, bool midiOutActivityAllowed=true);
  void sendProgramChange(uint8_t port, uint8_t channel,
                          uint8_t program, uint8_t cable=0);
  void sendControlChange(uint8_t port, uint8_t channel,
                          uint8_t control, uint8_t value, uint8_t cable=0, bool localLog=true);
  void sendControlChangeNoLocalLog(uint8_t port, uint8_t channel,
                          uint8_t control, uint8_t value, uint8_t cable=0);
  void sendNoteOn(uint8_t port, uint8_t channel, uint8_t note,
                  uint8_t velocity, uint8_t cable=0);
  void sendNoteOff(uint8_t port, uint8_t channel,
                    uint8_t note, uint8_t velocity, uint8_t cable=0);
  void sendPitchBend(uint8_t port, uint8_t channel,
                      int16_t value, uint8_t cable=0);
  void sendAfterTouch(uint8_t port, uint8_t channel,
                      uint8_t pressure, uint8_t cable=0);
  void sendAfterTouchPoly(uint8_t port, uint8_t channel,
                          uint8_t note, uint8_t pressure, uint8_t cable=0);
  void sendTimeCodeQuarterFrame(uint8_t port, uint8_t type,
                                uint8_t value, uint8_t cable=0);
  void sendSongPosition(uint8_t port, uint16_t beats, uint8_t cable=0);
  void sendSongSelect(uint8_t port, uint8_t song, uint8_t cable=0);
  void sendTuneRequest(uint8_t port, uint8_t cable=0);
  // RPN
  void beginRpn(uint8_t port, uint8_t channel,
                uint16_t number, uint8_t cable=0);
  void sendRpnValue(uint8_t port, uint8_t channel,
                    uint16_t value, uint8_t cable=0);
  void sendRpnIncrement(uint8_t port, uint8_t channel,
                        uint8_t amount, uint8_t cable=0);
  void sendRpnDecrement(uint8_t port, uint8_t channel,
                        uint8_t amount, uint8_t cable=0);
  void endRpn(uint8_t port, uint8_t channel, uint8_t cable=0);
  // NRPN
  void beginNrpn(uint8_t port, uint8_t channel,
                  uint16_t number, uint8_t cable=0);
  void sendNrpnValue(uint8_t port, uint8_t channel,
                    uint16_t value, uint8_t cable=0);
  void sendNrpnIncrement(uint8_t port, uint8_t channel,
                        uint8_t amount, uint8_t cable=0);
  void sendNrpnDecrement(uint8_t port, uint8_t channel,
                        uint8_t amount, uint8_t cable=0);
  void endNrpn(uint8_t port, uint8_t channel, uint8_t cable=0);

  // TOGGLE
  uint8_t toggleCC(uint8_t ports, uint8_t channel, uint8_t control);

  // SCROLLING
  uint8_t scrollCC(uint8_t ports, uint8_t channel, uint8_t control, uint8_t amount,
                bool direction, bool endless, uint8_t min, uint8_t max);
  
  uint8_t scrollPC(uint8_t ports, uint8_t channel, uint8_t amount, bool direction,
                bool endless, uint8_t min, uint8_t max);

  // Specific to USB & HOST
  void send_now(){
    #if defined(BMC_FOR_TEENSY)
      USB_MIDI_PORT.send_now();
    #endif
    
    #ifdef BMC_USB_HOST_ENABLED
      midiHost.Port.send_now();
    #endif
  }
  // Specific to USB HOST
  uint16_t getHostDeviceVendorId(){
    #ifdef BMC_USB_HOST_ENABLED
      return midiHost.Port.idVendor();
    #else
      return 0;
    #endif
  }
  uint16_t getHostDeviceProductId(){
    #ifdef BMC_USB_HOST_ENABLED
      return midiHost.Port.idProduct();
    #else
      return 0;
    #endif
  }
  // to get local program or control channel must be between 1-16 not 0-15
  uint8_t getLocalProgram(uint8_t t_channel){
    return midiData.getProgram(t_channel);
  }
  uint8_t getLocalControl(uint8_t t_channel, uint8_t t_control){
    return midiData.getControl(t_channel, t_control);
  }
  uint8_t getLocalPitch(uint8_t t_channel){
    return midiData.getPitch(t_channel);
  }

  void setLocalMidiData(uint32_t t_event){
    midiData.set(t_event);
  }
  void setLocalProgram(uint32_t t_event){
    midiData.setProgram(t_event);
    globals.setMidiLocalUpdate(true);
  }
  void setLocalControl(uint32_t t_event){
    midiData.setControl(t_event);
    globals.setMidiLocalUpdate(true);
  }

  void setLocalProgram(uint8_t t_channel, uint8_t t_program){
    midiData.setProgram(t_channel, t_program);
    globals.setMidiLocalUpdate(true);
  }
  void setLocalControl(uint8_t t_channel, uint8_t t_control, uint8_t t_value){
    midiData.setControl(t_channel, t_control, t_value);
    globals.setMidiLocalUpdate(true);
  }
  void setLocalPitch(uint8_t t_channel, uint8_t t_value){
    midiData.setPitch(t_channel, t_value);
    globals.setMidiLocalUpdate(true);
  }

  void setListenerEnable(bool t_value){
    flags.write(BMC_FLAG_MIDI_LISTENER_ENABLE,t_value);
  }
  void setListenerChannel(uint8_t t_value){
    channel = t_value;
  }
  uint8_t getListenerChannel(){
    return channel;
  }
  void setListenerPorts(uint8_t t_value){
    listenerPorts.set(t_value);
  }
  uint8_t getListenerPorts(){
    return listenerPorts.get();
  }
  void setClockPort(uint8_t t_port){
    slaveClockPort = 0;
    bitWrite(slaveClockPort, (t_port & 0x07), 1);
  }
  uint8_t getClockPort(){
    return slaveClockPort;
  }
  bool isIncomingClockPort(){
    // return message.getSource() == slaveClockPort;
    return BMC_MATCH_PORT(message.getSource(), slaveClockPort);
  }
  bool isIncoming(){
    return isListenerEnabled() &&
          isValidListenerStatus() &&
          matchSourceAndChannel() &&
          matchSourceAndListenerPorts();
  }
  bool isListenerEnabled(){
    return flags.read(BMC_FLAG_MIDI_LISTENER_ENABLE);
  }
  bool isValidListenerStatus(){
    return message.isProgramOrControl();
  }
  bool matchSourceAndListenerPorts(){
    return BMC_MATCH_PORT(message.getSource(),listenerPorts.get());
  }
  bool matchSourceAndChannel(){
    return (channel==0 || (channel == message.getChannel()));
  }
  uint8_t getPortPreset(uint8_t port){
    if(port>127){
      return globals.store.global.portPresets[(port & 0x0F)].events[0];
    }
    return port;
  }
private:
  // port presets
  //bmcStorePortPresets& portPresets;
  // bmcStoreGlobal& global;
  // flags
  BMCFlags <uint8_t> flags;
  // midiData = is a large struct that stores incoming and outgoing
  // program/control values for all 16 MIDI channels
  // the object contains 16 channels
  // each channel has a 128 byte array, each represents a MIDI Control #
  // each control number is the last value sent or received
  // each channel also contains a Program #, representing the last Program
  // sent or received
  BMCMidiData midiData;
  // listenerPorts = the MIDI port that will react to things like
  // layer changes, preset changes and bank changes
  BMCMidiPort listenerPorts;
  // the port that wil receive MIDI Clock signal
  uint8_t slaveClockPort = 0;
  // channel = the channel that BMC will react to things like
  // layer changes, preset changes and bank changes
  uint8_t channel = 0;
  // debug variables only compiled if BMC_DEBUG is enabled
  #if defined(BMC_DEBUG)
    bool debug = false;
    bool debugClock = false;
  #endif


  // midiSerial = an object holding each MIDI Serial Port (DIN) that is compiled
  #ifdef BMC_HAS_SERIAL_MIDI
    BMCMidiPortSerial midiSerial;
  #endif
  // midiHost = the USB Host port on Teensy 3.6 for MIDI IO
  #ifdef BMC_USB_HOST_ENABLED
    BMCMidiPortHost midiHost;
  #endif
  // midiBle = the BLE MIDI port, it uses an object that emulates a serial port
  // then feeding/reading the MIDI library
  #if defined(BMC_MIDI_BLE_ENABLED) && defined(BMC_FOR_TEENSY)
    BMCMidiPortBle midiBle;
  #endif

  BMCMidiRouting midiRouting;

  bool isMidiUsbPort(uint8_t port){
    return BMCTools::isMidiUsbPort(getPortPreset(port));
  }
  bool isMidiSerialAPort(uint8_t port){
    return BMCTools::isMidiSerialAPort(getPortPreset(port));
  }
  bool isMidiSerialBPort(uint8_t port){
    return BMCTools::isMidiSerialBPort(getPortPreset(port));
  }
  bool isMidiSerialCPort(uint8_t port){
    return BMCTools::isMidiSerialCPort(getPortPreset(port));
  }
  bool isMidiSerialDPort(uint8_t port){
    return BMCTools::isMidiSerialDPort(getPortPreset(port));
  }
  bool isMidiHostPort(uint8_t port){
    return BMCTools::isMidiHostPort(getPortPreset(port));
  }
  bool isMidiBlePort(uint8_t port){
    return BMCTools::isMidiBlePort(getPortPreset(port));
  }

  // when a message is sent out or received we want to add that data to
  // the midiData Object which holds the last incoming/outgoing program/control
  // values for every channel
  void addToLocalData(BMCMidiMessage message){
    // since MIDI Clock messages are time sensitive we want to check
    // if it is one first and skip this chunk of code
    if(message.isClock() || message.getStatus() == BMC_NONE ||
      message.getStatus() >= BMC_MIDI_SYSTEM_EXCLUSIVE)
    {
      return;
    }
    setLocalMidiData(message.getEvent());
  }

  // *Routing*
  void routing(BMCMidiMessage& message){
    uint8_t destinations = midiRouting.incoming(message);
    if(destinations!=BMC_NONE){
      if(callback.midiPreRoute){
        // if the callback returns false we block the routing
        if(!callback.midiPreRoute(message, destinations)){
          return;
        }
      }
      send(destinations, message);
    }
  }

  bool isAnySerialPort(uint8_t port){
#if defined(BMC_MIDI_SERIAL_A_ENABLED)
    if(isMidiSerialAPort(port)){
      return true;
    }
#endif

#if defined(BMC_MIDI_SERIAL_B_ENABLED)
    if(isMidiSerialBPort(port)){
      return true;
    }
#endif

#if defined(BMC_MIDI_SERIAL_C_ENABLED)
    if(isMidiSerialCPort(port)){
      return true;
    }
#endif

#if defined(BMC_MIDI_SERIAL_D_ENABLED)
    if(isMidiSerialDPort(port)){
      return true;
    }
#endif
    return false;
  }
};
#endif
