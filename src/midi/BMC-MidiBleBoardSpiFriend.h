/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Reads/Writes raw BLE packets into byte arrays for the the BMCSerialBle to parse.

  This board doesn't work nearly as good as the nRF8001 because it uses
  "AT" commands which take longer to read/write and they have to wait for OKs.
  Unfortunately Adafruit discontinued their nRF8001 board which was a plug and play board with BMC.
  As of 2019-10-01 this class is still in developement.
  Whenever possible use the nRF8001 board.


  Requires ADAFRUIT BLUEFRUIT LE SPI FRIEND
  https://www.adafruit.com/product/2633
*/
#ifndef BMC_MIDI_BLE_BOARD_SPIFRIEND_H
#define BMC_MIDI_BLE_BOARD_SPIFRIEND_H

#include "utility/BMC-Def.h"

#if defined(BMC_MIDI_BLE_ENABLED) && BMC_MIDI_BLE_BOARD == 2

#include <SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BLEGatt.h>

// SPI Friend CS, chip select pin
#ifndef BMC_BLE_SPI_PIN_CS
  #define BMC_BLE_SPI_PIN_CS 10
#endif
// SPI Friend IRQ, interrupt pin
#ifndef BMC_BLE_SPI_PIN_INT
  #define BMC_BLE_SPI_PIN_INT 2
#endif
// SPI Friend RST, reset pin
#ifndef BMC_BLE_SPI_PIN_RST
  #define BMC_BLE_SPI_PIN_RST 9
#endif


class BMCSpiFriend {
public:
  BMCSpiFriend():
    ble(BMC_BLE_SPI_PIN_CS, BMC_BLE_SPI_PIN_INT, BMC_BLE_SPI_PIN_RST)
    ,gatt(ble)
  {

  }
  operator bool(){
    return connected;
  }
  void begin(){
    BMC_PRINTLN("    BMCSpiFriend::begin");
    BMC_PRINTLN("    BMCSpiFriend BMC_BLE_SPI_PIN_CS",BMC_BLE_SPI_PIN_CS,"BMC_BLE_SPI_PIN_INT",BMC_BLE_SPI_PIN_INT,"BMC_BLE_SPI_PIN_RST",BMC_BLE_SPI_PIN_RST);
    delay(100);
    if(!ble.begin(true)){
      BMC_ERROR("    BMCSpiFriend: CAN NOT CONNECT TO ADAFRUIT SPI FRIEND");
      BMC_HALT();
    }
    if(!ble.factoryReset(true)){
      BMC_WARNING("    BMCSpiFriend: CAN NOT DO FACTORY RESET ADAFRUIT SPI FRIEND");
      //BMC_HALT();
    }
    // Disable command echo from Bluefruit
    //ble.echo(false);

    ble.println("AT+BLEPOWERLEVEL=-4");
    ble.waitForOK();

    uint8_t midiServUUID[16] = {0x03,0xB8,0x0E,0x5A,0xED,0xE8,0x4B,0x33,0xA7,0x51,0x6C,0xE3,0x4E,0xC4,0xC7,0x00};
    uint8_t midiCharUUID[16] = {0x77,0x72,0xE5,0xDB,0x38,0x68,0x41,0x12,0xA1,0xA9,0xF2,0x66,0x9D,0x10,0x6B,0xF3};
    uint8_t initialCharValue[1] = {0};
    String command = "AT+GAPDEVNAME=";
    command += BMC_BLE_MIDI_DEVICE_NAME;

    // set device name
    ble.println(command);
    ble.waitForOK();
    // clear custom gatt
    //gatt.clear();

    midiServiceId = gatt.addService(midiServUUID);
    if(midiServiceId == 0){
      BMC_WARNING("BMCSpiFriend: Could not add MIDI Service");
      BMC_HALT();
    }
    midiCharId = gatt.addCharacteristic(midiCharUUID, (0x02 | 0x04 | 0x08 | 0x10), 1, 30, BLE_DATATYPE_BYTEARRAY);
    if(midiCharId == 0){
      BMC_WARNING("BMCSpiFriend: Could not add MIDI characteristic");
      BMC_HALT();
    }

    ble.setAdvData(midiServUUID, 16);
    ble.waitForOK();

    ble.println("AT+GAPCONNECTABLE=1");
    ble.waitForOK();

    ble.println("AT+GAPINTERVALS=12,15,30");
    ble.waitForOK();

    ble.println("AT+GAPSTARTADV");
    ble.waitForOK();

    ble.reset();

    gatt.setChar(midiCharId, initialCharValue, 1);
    ble.waitForOK();

    timer.start(500);
  }
  int available(){
    update();
    if(connected){
      length = ble.available();
      buildBuffer();
    } else {
      length = 0;
    }
    return length;
  }
  bool update(){
    if(timer.complete()){
      connected = ble.isConnected();
    }
    return connected;
  }
  unsigned const char* getPacket() const {
    return buffer;
  }
  uint8_t getPacketLength(){
    return length;
  }
  bool setValue(const unsigned char value[], unsigned char length){
    if(connected){
      return gatt.setChar(midiCharId, value, length);
    }
    return false;
  }
  void enableBLE(){

  }
  void disconnectBLE(){

  }
private:
  Adafruit_BluefruitLE_SPI ble;
  Adafruit_BLEGatt gatt;
  bool connected = false;
  int length = 0;
  BMCEndlessTimer timer;
  uint8_t buffer[30];
  uint8_t midiServiceId = 0;
  uint8_t midiCharId = 0;
  void clearBuffer(){
    length = 0;
    memset(buffer,0,30);
  }
  void buildBuffer(){
    clearBuffer();
    while(ble.available()){
      if(length>=30){
        break;
      }
      char c =  ble.read();
      buffer[length] = c;
    }
  }
};
#endif
#endif
