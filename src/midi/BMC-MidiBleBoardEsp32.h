/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Use a ESP32 as a BLE MIDI Bridge using SPI

  not finished, doesn't work yet
*/
#ifndef BMC_MIDI_BLE_BOARD_ESP32_H
#define BMC_MIDI_BLE_BOARD_ESP32_H

#include "utility/BMC-Def.h"

#if defined(BMC_MIDI_BLE_ENABLED) && BMC_MIDI_BLE_BOARD == 1

#include <SPI.h>
#include <BLEPeripheral.h>

// how often to poll the ble module in millis
// do not exceed more than 50ms as it may disconnect the central
#define BMC_ESP32_NEXT_CHECK_MILLIS 5
// flags
#define BMC_ESP32_FLAG_CONNECTED 0
#define BMC_ESP32_FLAG_RUNNING 1

// the following can overloaded on your config
// nRF8001 REQ, chip select pin
#ifndef BMC_BLE_SPI_PIN_CS
  #define BMC_BLE_SPI_PIN_CS 10
#endif
// nRF8001 RDY, interrupt pin
#ifndef BMC_BLE_SPI_PIN_INT
  #define BMC_BLE_SPI_PIN_INT 2
#endif
// nRF8001 RST, reset pin
#ifndef BMC_BLE_SPI_PIN_RST
  #define BMC_BLE_SPI_PIN_RST 9
#endif

class BMCEsp32BleMidi {
public:
  BMCEsp32BleMidi(){
    nextCheckMillis = 0;
    flags.reset();
  }
  operator bool(){
    return flags.read(BMC_ESP32_FLAG_CONNECTED);
  }
  void begin(){
    if(flags.read(BMC_ESP32_FLAG_RUNNING)){
      return;
    }
    BMC_PRINTLN("    BMCEsp32BleMidi::begin");

    String tmp = BMC_BLE_MIDI_DEVICE_NAME;
    uint8_t len = tmp.length();
    char tmpArr[len+1];
    tmp.toCharArray(tmp, len);

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
    SPI.usingInterrupt(BMC_BLE_SPI_PIN_INT);
    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    //SPI.transfer(10);// reset
    //SPI.transfer(tmp, length);// send device name


    //SPI.transfer(buffer, size);
    /*
      BMC_BLE_SPI_PIN_CS
      BMC_BLE_SPI_PIN_INT
      BMC_BLE_SPI_PIN_RST
    */

    // local name sometimes used by central
    //ble.setLocalName(BMC_BLE_MIDI_DEVICE_NAME);
    // device name sometimes used by central
    //ble.setDeviceName(BMC_BLE_MIDI_DEVICE_NAME);
    // Advertise MIDI UUID
    //ble.setAdvertisedServiceUuid(midiService.uuid());
    // add attributes
    //ble.addAttribute(midiService);
    //ble.addAttribute(midiCharacteristic);
    //ble.addAttribute(descriptor);
    //ble.setConnectionInterval(7.5, 20);
    //The accessory shall respond to the initial MIDI I/O characteristic read with a packet that has no payload.
    //midiCharacteristic.setValue(0);
    //ble.begin();
    flags.on(BMC_ESP32_FLAG_RUNNING);
  }
  bool sendData(){
    
  }
  int available(){
    update();
    if(flags.read(BMC_ESP32_FLAG_CONNECTED) && midiCharacteristic.written()){
      return midiCharacteristic.valueLength();
    }
    return 0;
  }
  bool update(){
    // check if the device is connected, only check it every 1 millisecond
    // this is because otherwise BMC will check with the the module about
    // 20,000 times per seconds, this allows for other things to happen in between
    if(nextCheckMillis >= BMC_ESP32_NEXT_CHECK_MILLIS){
      nextCheckMillis -= BMC_ESP32_NEXT_CHECK_MILLIS;
      BLECentral central = ble.central();
      if(central){
        flags.write(BMC_ESP32_FLAG_CONNECTED, central.connected());
      } else {
        flags.off(BMC_ESP32_FLAG_CONNECTED);
      }
    }
    return flags.read(BMC_ESP32_FLAG_CONNECTED);
  }
  unsigned const char* getPacket() const {
    return midiCharacteristic.value();
  }
  uint8_t getPacketLength(){
    return midiCharacteristic.valueLength();
  }
  bool setValue(const unsigned char value[], unsigned char length){
    if(flags.read(BMC_ESP32_FLAG_CONNECTED)){
      return midiCharacteristic.setValue(value, length);
    }
    return false;
  }
  void enableBLE(){
    begin();
  }
  void disconnectBLE(){
    if(flags.read(BMC_ESP32_FLAG_CONNECTED)){
      ble.disconnect();
      BMC_PRINTLN("BMCEsp32BleMidi::disconnectBLE");
    }
  }
private:
  BLEPeripheral ble;
  BLEService midiService;
  BLECharacteristic midiCharacteristic;
  BLEDescriptor descriptor;
  uint8_t packetLength = 0;
  uint8_t packetData[20];
  BMCFlags <uint8_t> flags;
  BMCElapsedMillis nextCheckMillis;
};

#endif
#endif
