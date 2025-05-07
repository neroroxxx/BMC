/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.

  Reads/Writes raw BLE packets into byte arrays for the the BMCSerialBle to parse.

  Unfortunately Adafruit discontinued their nRF8001 board which was a plug and play board with BMC.

  Requires the Bluefruit LE - nRF8001 Breakout
  https://www.adafruit.com/product/1697

  Requires arduino-BLEPeripheral library, forked with some fixes
  https://github.com/neroroxxx/arduino-BLEPeripheral/tree/master/src
*/
#ifndef BMC_MIDI_BLE_BOARD_NRF8001_H
#define BMC_MIDI_BLE_BOARD_NRF8001_H

#include "utility/BMC-Def.h"

#if defined(BMC_MIDI_BLE_ENABLED) && BMC_MIDI_BLE_BOARD == 0

#include <SPI.h>
#include <BLEPeripheral.h>

// how often to poll the ble module in millis
// do not exceed more than 50ms as it may disconnect the central
#define BMC_NRF8001_NEXT_CHECK_MILLIS 5
// flags
#define BMC_NRF8001_FLAG_CONNECTED 0
#define BMC_NRF8001_FLAG_RUNNING 1
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


class BMCnRF8001 {
public:
  BMCnRF8001():
    ble(BMC_BLE_SPI_PIN_CS, BMC_BLE_SPI_PIN_INT, BMC_BLE_SPI_PIN_RST)
    ,midiService("03B80E5A-EDE8-4B33-A751-6CE34EC4C700")
    ,midiCharacteristic("7772E5DB-3868-4112-A1A9-F2669D106BF3", BLERead | BLEWrite | BLEWriteWithoutResponse | BLENotify, 20)
    ,descriptor("2902", 0)
  {
    nextCheckMillis = 0;
    flags.reset();
  }
  operator bool(){
    return flags.read(BMC_NRF8001_FLAG_CONNECTED);
  }
  void begin(){
    if(flags.read(BMC_NRF8001_FLAG_RUNNING)){
      return;
    }
    BMC_PRINTLN("    BMCnRF8001::begin");
    // local name sometimes used by central
    ble.setLocalName(BMC_BLE_MIDI_DEVICE_NAME);
    // device name sometimes used by central
    ble.setDeviceName(BMC_BLE_MIDI_DEVICE_NAME);
    // Advertise MIDI UUID
    ble.setAdvertisedServiceUuid(midiService.uuid());
    // add attributes
    ble.addAttribute(midiService);
    ble.addAttribute(midiCharacteristic);
    ble.addAttribute(descriptor);
    ble.setConnectionInterval(7.5, 20);
    //The accessory shall respond to the initial MIDI I/O characteristic read with a packet that has no payload.
    midiCharacteristic.setValue(0);
    ble.begin();
    flags.on(BMC_NRF8001_FLAG_RUNNING);
  }
  int available(){
    update();
    if(flags.read(BMC_NRF8001_FLAG_CONNECTED) && midiCharacteristic.written()){
      return midiCharacteristic.valueLength();
    }
    return 0;
  }
  bool update(){
    // check if the device is connected, only check it every 1 millisecond
    // this is because otherwise BMC will check with the the module about
    // 20,000 times per seconds, this allows for other things to happen in between
    if(nextCheckMillis>=BMC_NRF8001_NEXT_CHECK_MILLIS){
      nextCheckMillis -= BMC_NRF8001_NEXT_CHECK_MILLIS;
      BLECentral central = ble.central();
      if(central){
        flags.write(BMC_NRF8001_FLAG_CONNECTED, central.connected());
      } else {
        flags.off(BMC_NRF8001_FLAG_CONNECTED);
      }
    }
    return flags.read(BMC_NRF8001_FLAG_CONNECTED);
  }
  unsigned const char* getPacket() const {
    return midiCharacteristic.value();
  }
  uint8_t getPacketLength(){
    return midiCharacteristic.valueLength();
  }
  bool setValue(const unsigned char value[], unsigned char length){
    if(flags.read(BMC_NRF8001_FLAG_CONNECTED)){
      return midiCharacteristic.setValue(value, length);
    }
    return false;
  }
  void enableBLE(){
    begin();
  }
  void disconnectBLE(){
    if(flags.read(BMC_NRF8001_FLAG_CONNECTED)){
      ble.disconnect();
      BMC_PRINTLN("BMCnRF8001::disconnectBLE");
    }
  }
private:
  BLEPeripheral ble;
  BLEService midiService;
  BLECharacteristic midiCharacteristic;
  BLEDescriptor descriptor;
  BMCFlags <uint8_t> flags;
  BMCElapsedMillis nextCheckMillis;
};

#endif
#endif
