/*
  See https://www.roxxxtar.com/bmc for more details
  Copyright (uint8_t c) 2025 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#pragma once

#if !defined(BMC_ESP32_BLE_H)

#define BMC_ESP32_BLE_H

#include "utility/BMC-Def.h"

#if defined(BMC_FOR_ESP32) && BMC_MCU_HAS_BLE == true

#include <NimBLEDevice.h>

#define BMC_ESP32_BMC_ESP32_MAX_SYSEX_LENGTH 512  // Max size for SysEx message

// UUIDs for MIDI service and characteristic
#define BMC_MIDI_SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define BMC_MIDI_CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"


class BMCEsp32BleMidi {
private:

  BMCGlobals& globals;
  BLEServer *pServer = nullptr;
  BLEAdvertising *pAdvertising = nullptr;
  BLECharacteristic *pCharacteristic = nullptr;

  friend class ServerCallbacks;
  friend class CharacteristicCallbacks;

public:
  // Constructor
  BMCEsp32BleMidi(BMCGlobals& t_globals):globals(t_globals){

  }

  // Initialization function, to be called in setup()
  bool begin(uint16_t baud=0);

  void flush(){

  }

  bool available(){
    return (fifoStart != fifoEnd);
  }

  uint8_t read(){
    // Check if the FIFO is empty
    if (fifoStart != fifoEnd) {
      uint8_t data = fifo[fifoStart];
      fifoStart = (fifoStart + 1) % BMC_ESP32_BMC_ESP32_MAX_SYSEX_LENGTH;  // Circular buffer
      return data;  // Return the byte
    }
    return 0xFF;  // FIFO is empty, return a special value to indicate no data
  }

  void write(uint8_t value){

  }
  
  void send(uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel, uint8_t cable = 0) {
    switch(type) {
      // 3-byte messages that need a channel (Note On, Note Off, etc.)
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_AFTER_TOUCH_POLY:
      case BMC_MIDI_CONTROL_CHANGE:
      case BMC_MIDI_PITCH_BEND:
        sendMidiData(type | (channel & 0x0F), data1 & 0x7F, data2 & 0x7F); // Add channel info
        break;
  
      // 2-byte messages with a channel (Program Change, After Touch, etc.)
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_AFTER_TOUCH:
        sendMidiData(type | (channel & 0x0F), data1 & 0x7F); // Add channel info
        break;
        
      // 3-byte messages without a channel (e.g., song select)
      case BMC_MIDI_SONG_POSITION:
        sendMidiData(type, data1 & 0x7F, data2 & 0x7F); // No channel needed
        break;
  
      // 1-byte system real-time messages (clock, start, stop, etc.)
      case BMC_MIDI_RT_CLOCK:
      case BMC_MIDI_RT_CLOCK_TICK:
      case BMC_MIDI_RT_START:
      case BMC_MIDI_RT_CONTINUE:
      case BMC_MIDI_RT_STOP:
      case BMC_MIDI_RT_ACTIVE_SENSE:
      case BMC_MIDI_RT_SYSTEM_RESET:
        sendMidiData(type, 0); // No data1 or data2 for these
        break;
  
      // Time Code, Song Select, and Tune Request (2-byte messages)
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
      case BMC_MIDI_SONG_SELECT:
      case BMC_MIDI_TUNE_REQUEST:
        sendMidiData(type, data1 & 0x7F); // No channel, 2-byte messages
        break;
  
      default:
        // Handle unknown message types if necessary
        break;
    }
  }

  void sendSysEx(const uint8_t *data, size_t length, bool bounds=false) {
    if (bounds) {
      // Has F0 and F7 bytes, send right away
      sendRaw(data, length);
      return;
    }
  
    size_t newLength = length + 2;
    uint8_t newData[newLength];
  
    newData[0] = 0xF0;
    memcpy(newData + 1, data, length);
    newData[newLength - 1] = 0xF7;
  
    sendRaw(newData, newLength);
  }

  void sendMidiData(uint8_t status) {
    uint8_t midiMessage[1] = {status};
    sendRaw(midiMessage, 1);
  }

  void sendMidiData(uint8_t status, uint8_t data1) {
    uint8_t midiMessage[2] = {status, data1};
    sendRaw(midiMessage, 2);
  }

  void sendMidiData(uint8_t status, uint8_t data1, uint8_t data2) {
    uint8_t midiMessage[3] = {status, data1, data2};
    sendRaw(midiMessage, 3);
  }

  void sendRaw(const uint8_t * _buffer, size_t length) {
    size_t index = 0;
    uint8_t buffer[length + 5];
    unsigned long currentTimeStamp = millis() & 0x01FFF;
    uint8_t timestampHigh = ((currentTimeStamp >> 7) & 0x3F) | 0x80; // 6 bits plus MSB
    uint8_t timestampLow = (currentTimeStamp & 0x7F) | 0x80; // 7 bits plus MSB

    buffer[index++] = timestampHigh;
    buffer[index++] = timestampLow;

    for(uint8_t i = 0 ; i < length; i++){
      buffer[index++] = _buffer[i];
    }

    if (buffer[index - 1] == 0xF7){
      buffer[index - 1] = timestampLow;
      buffer[index++] = 0xF7;
    }

    sendPacket(buffer, index);
  }
  
  void sendPacket(const uint8_t * buffer, size_t length) {
    // BMC_PRINTLN("BLE Packet:");
    // BMC_DEBUG_PRINT_SYSEX(true, buffer, length);
    // Send the MIDI message using the provided array and its length
    pCharacteristic->setValue(buffer, length);
    pCharacteristic->notify(); 
  }
  
private:
  // Add byte to FIFO buffer
  
  uint8_t fifo[BMC_ESP32_BMC_ESP32_MAX_SYSEX_LENGTH];
  size_t fifoStart = 0;  // Index of the first element in FIFO
  size_t fifoEnd = 0;    // Index of the next available slot in FIFO

  void addToFifo(uint8_t data) {
    if ((fifoEnd + 1) % BMC_ESP32_BMC_ESP32_MAX_SYSEX_LENGTH != fifoStart) {
      fifo[fifoEnd] = data;
      fifoEnd = (fifoEnd + 1) % BMC_ESP32_BMC_ESP32_MAX_SYSEX_LENGTH;  // Circular buffer
    } else {
      BMC_PRINTLN("FIFO is full, cannot add more data!");
    }
  }

  void parseIncomingPacket(uint8_t *buffer, size_t length) {
    uint8_t lPtr = 0;
    uint8_t rPtr = 0;
    uint8_t lastStatus;
    lPtr = 2;

    while (true) {
      lastStatus = buffer[lPtr];

      if (buffer[lPtr] < 0x80) {
        return;
      }

      rPtr = lPtr;

      while ((buffer[rPtr + 1] < 0x80) && (rPtr < (length - 1))) {
        rPtr++;
      }

      if (buffer[rPtr + 1] == 0xF7) {
        rPtr++;
      }

      if (rPtr - lPtr < 1) {
        addToFifo(lastStatus);
      } else if (rPtr - lPtr < 2) {
        addToFifo(lastStatus);
        addToFifo(buffer[lPtr + 1]);
      } else if (rPtr - lPtr < 3) {
        addToFifo(lastStatus);
        addToFifo(buffer[lPtr + 1]);
        addToFifo(buffer[lPtr + 2]);
      } else {
        switch (buffer[lPtr] & 0xF0) {
          case 0x80:
          case 0x90:
          case 0xA0:
          case 0xB0:
          case 0xE0:
            for (auto i = lPtr; i < rPtr; i = i + 2) {
              addToFifo(lastStatus);
              addToFifo(buffer[i + 1]);
              addToFifo(buffer[i + 2]);
            }
            break;
          case 0xC0:
          case 0xD0:
            for (auto i = lPtr; i < rPtr; i = i + 1) {
              addToFifo(lastStatus);
              addToFifo(buffer[i + 1]);
            }
            break;
          case 0xF0:
            addToFifo(buffer[lPtr]);
            for (auto i = lPtr; i < rPtr; i++) {
              addToFifo(buffer[i + 1]);
            }
            break;
          default:
            break;
        }
      }

      lPtr = rPtr + 2;
      if (lPtr >= length) {
        return;
      }
    }
  }

  void onConnect(){
    BMC_PRINTLN("BLE: connected");
    globals.setBleConnected(true);
  }

  void onDisconnect(){
    BMC_PRINTLN("BLE: disconnected");
    globals.setBleConnected(false);
  }
};

// * Server Callbacks

class ServerCallbacks : public BLEServerCallbacks {
  public:
    ServerCallbacks(BMCEsp32BleMidi *parent) : parentInstance(parent) {}

    protected:

    BMCEsp32BleMidi *parentInstance = nullptr;

    void onConnect(BLEServer *) {
      parentInstance->onConnect();
    }

    void onDisconnect(BLEServer *) {
      parentInstance->onDisconnect();
    }

    void onMTUChanged(uint16_t MTU, NimBLEConnInfo *){
      BMC_PRINTLN("BLE: onMTUChanged", MTU);
    }
};

// * Characteristic Callbacks

class CharacteristicCallbacks : public BLECharacteristicCallbacks {
  public:
  CharacteristicCallbacks(BMCEsp32BleMidi *parent) : parentInstance(parent) {}

  protected:
  BMCEsp32BleMidi *parentInstance = nullptr;

  void onWrite(BLECharacteristic* characteristic) {
    
    std::string data = characteristic->getValue();
    // BMC_PRINTLN("BLE: Received Data");
    if(data.length() > 0){
      parentInstance->parseIncomingPacket((uint8_t *)(data.c_str()), data.length());
    }
  }
};

#endif

#endif
