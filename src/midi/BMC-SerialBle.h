/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Emulates a Serial object to be used with the MIDI library
  https://github.com/FortySevenEffects/arduino_midi_library

  This class is just a packet parsing class, other classes read/write the
  packets from a BLE module then this class handles adding/removing timestamps,
  queueing and managing connection status.

  Code for this class was based on:
  https://learn.sparkfun.com/tutorials/midi-ble-tutorial/all
  https://github.com/sparkfun/MIDI-BLE-Adapter

*/
#ifndef BMC_MIDI_BLE_TO_SERIAL_H
#define BMC_MIDI_BLE_TO_SERIAL_H

#include "utility/BMC-Def.h"

#if defined(BMC_MIDI_BLE_ENABLED)

#if BMC_MIDI_BLE_BOARD == 0
  // nRF8001
  #include "midi/BMC-MidiBleBoardnRF8001.h"
  #define BMC_BLE_MIDI_TX_BUFFER_SIZE 20
  #define BMC_BLE_PACKET_TX_INTERVAL 20
  #define BMC_BLE_PACKET_RESEND_TX_INTERVAL 10
  #define BMC_BLE_MAX_PACKETS 2

#elif BMC_MIDI_BLE_BOARD == 1
  // ESP32
  #include "midi/BMC-BMC-MidiBleBoardEsp32.h"
  #define BMC_BLE_MIDI_TX_BUFFER_SIZE 20
  #define BMC_BLE_PACKET_TX_INTERVAL 20
  #define BMC_BLE_PACKET_RESEND_TX_INTERVAL 10
  #define BMC_BLE_MAX_PACKETS 2
#elif BMC_MIDI_BLE_BOARD == 2
  // ADAFRUIT BLUEFRUIT LE SPI FRIEND
  #include "midi/BMC-MidiBleBoardSpiFriend.h"
  #define BMC_BLE_MIDI_TX_BUFFER_SIZE 30
  #define BMC_BLE_PACKET_TX_INTERVAL 1
  #define BMC_BLE_PACKET_RESEND_TX_INTERVAL 10
  #define BMC_BLE_MAX_PACKETS 4
#else
  #error "Invalid BLE Board defined"
#endif

#include "utility/QueueArray.h"


#define MAX_MS 0x01FFF //13 bits, 8192 dec

// Fake serial to feed the MIDI library

#define BMC_MIDI_BLE_FLAG_STATE_CHANGED 0
#define BMC_MIDI_BLE_FLAG_QUEUE_AVAILABLE 1
#define BMC_MIDI_BLE_FLAG_SYSEX_OPEN 2

class BMCSerialBle {
public:
  BMCSerialBle(BMCGlobals& t_globals):
    globals(t_globals){
    memset(txBuffer,0,BMC_BLE_MIDI_TX_BUFFER_SIZE);
    txTimestamps = 1;
  }
  operator bool(){
    return globals.bleConnected();
  }
  void begin(int baudRate){
    BMC_PRINTLN("BMCSerialBle::begin");
    ble.begin();
  }

  void disconnectBLE(){
    ble.disconnectBLE();
  }

  uint8_t read(){
    return rxQueue.pop();
  }
  uint8_t peek(){
    return rxQueue.peek();
  }
  size_t write(uint8_t value){
    txQueue.push(value);
    return 1;
  }

  int available(){
    update();
    if(rxQueue.count()>0){
      return rxQueue.count();
    }
    if(ble.available() > 0){
      parsePacket();
      return rxQueue.count();
    }
    return 0;
  }
  void update(){
    bool state = ble.update();
    if(state){
      flushBle();
    }
    connectionState(state);
  }
  void flush(){
    // kept in a separate function to keep the flush method public
    flushBle();
  }

  // UTILITIES
  bool midiConnected(){
    return globals.bleConnected();
  }
  bool stateChanged(){
    return flags.toggleIfTrue(BMC_MIDI_BLE_FLAG_STATE_CHANGED);
  }
private:
  BMCGlobals& globals;
#if BMC_MIDI_BLE_BOARD == 0
  BMCnRF8001 ble = BMCnRF8001();
#elif BMC_MIDI_BLE_BOARD == 1
  // ADAFRUIT BLUEFRUIT LE SPI FRIEND
  BMCSpiFriend ble = BMCSpiFriend();
#else
  #error "Invalid BLE Board defined"
#endif

  BMCFlags <uint8_t> flags;
  QueueArray <uint8_t> rxQueue;
  QueueArray <uint8_t> txQueue;
  unsigned long txTime = 0;
  uint8_t rxRunningStatus = 0;
  uint8_t txRunningStatus = 0;
  uint8_t txBuffer[BMC_BLE_MIDI_TX_BUFFER_SIZE];
  uint8_t txBufferSize = 0;
  uint8_t txTimestamps = 1;
  uint8_t txPacket[BMC_BLE_MIDI_TX_BUFFER_SIZE];
  uint8_t txPacketSize = 0;
  uint8_t txAdditionalMs = 0;
  unsigned long msOffset = 0;
  unsigned long currentMillis = 0;

  void connectionState(bool value){
    if(value != globals.bleConnected()){
      globals.setBleConnected(value);
      if(!value){
        flags.reset();
      }
      flags.on(BMC_MIDI_BLE_FLAG_STATE_CHANGED);
      BMC_PRINTLN("BLE MIDI Connection State",value);
    }
  }

  // read data from BLE and remove timestamps
  // adds them to the rxQueue to then pass them to the MIDI Library
  void parsePacket(){
    uint8_t * packet = (uint8_t*) ble.getPacket();
    uint8_t packetSize = ble.getPacketLength();

    if(bitRead(packet[0],7) && packetSize<2){
      return; // invalid header...
    }

    uint8_t packetIndex = 1;

    // clear the RX Running status since running status can not span across packets
    rxRunningStatus = 0;

    // uncomment code below to see all the bytes in the packet
    #ifdef BMC_DEBUG
      if(globals.getBleDebug()){
        BMC_PRINTLN("Incoming BLE Packet");
        BMC_PRINT_ARRAY(true,packet, packetSize);
      }
    #endif

    if((packetSize >= 2 && !bitRead(packet[1],7))){
      // only the rest of a sysex can start with a header
      // but no timestamp as the next byte after he header
      // so this is a chunk of a sysex which may be the end of it
      packetIndex = parseSystemExclusive(packet, packetSize, packetIndex, false);
    }
    // maxLoops is only used in case a packet has bad data of any form and
    // will prevent the while loop from running forever
    uint8_t maxLoops = 0;

    while(packetIndex < packetSize){
      // the first byte of the current chunk, it could be a timestamp or a data byte of a running status
      uint8_t byte1 = packet[packetIndex];
      // the second byte of the current chunk, it could be the timestamp for the next full midi message
      // or a data byte of a running status, we only get the next byte if we aren't at the end of the buffer
      uint8_t byte2 = packet[packetIndex];

      // if we have enough bytes to get byte2 we get it
      if(packetIndex < packetSize-1){
        byte2 = packet[packetIndex+1];
      }
      // read byte1 to see if it has bit 7 set to 1 (>127), if so it's a timestamp (>127) or a data byte (<127)
      bool hasTimestamp = bitRead(byte1, 7);
      // read byte2 to see if it has bit 7 set to 1 (>127), if so it's a status
      // of if it's a running status then it may be the second byte of the running status
      // or the timestamp of the next full midi message
      bool hasStatus = bitRead(byte2, 7);

      // SysEx messages start with a status then a timestamp and then 0xF0
      if(hasTimestamp && hasStatus && byte2 == BMC_MIDI_SYSTEM_EXCLUSIVE){
        packetIndex = parseSystemExclusive(packet, packetSize, packetIndex, true);// it's a sysex

      } else if(hasTimestamp && hasStatus){
        // it's a full midi message, increase the packetIndex by 1 to skip the timestamp
        packetIndex++;
        packetIndex = parseFullMidiMessage(packet, packetSize, packetIndex);

      } else {
        // either a running status, end of a running status, start of a new status
        // no need to increase the packetIndex here, it's done by parseRunningStatusMidiMessage
        // if there's no timestamp
        packetIndex = parseRunningStatusMidiMessage(packet, packetSize, packetIndex, hasTimestamp);
      }
      // in case for any reason we get stuck in the loop because of a bad message
      // we break it after 20 runs since the packet will have no more than 20 bytes
      maxLoops++;
      if(maxLoops>=20){
        #ifdef BMC_DEBUG
          if(globals.getBleDebug()){
            BMC_PRINTLN("!!!!!!!! BLE Packet was not read properly !!!!!!!!");
          }
        #endif

        break;
      }
    }
  }
  uint8_t parseSystemExclusive(uint8_t *bytes, uint8_t size, uint8_t index, bool startOfSysEx){
    if(startOfSysEx){
      // we already skipped the header now we skip the low timestamp and the 0xF0
      // skip timestamp (0) and 0xF0 (1)
      // then start with the next byte (2)
      index += 2;
      rxQueue.push(0xF0);
    }
    while(index<size){
      if(bytes[index] < 0x80){
        rxQueue.push(bytes[index]);
      } else if(bytes[index]==0xF7){
        rxQueue.push(0xF7);
        index++;
        break;
      }
      index++;
    }
    return index;
  }
  uint8_t parseFullMidiMessage(uint8_t *bytes, uint8_t size, uint8_t index){
    uint8_t status = bytes[index];
    switch(status & 0xF0){
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_AFTER_TOUCH:
        // status + 1 byte message + running status
        rxRunningStatus = bytes[index++];
        rxQueue.push(rxRunningStatus);
        rxQueue.push(bytes[index++]);
        return index;
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_AFTER_TOUCH_POLY:
      case BMC_MIDI_CONTROL_CHANGE:
      case BMC_MIDI_PITCH_BEND:
        // status + 2 bytes message+ running status
        rxRunningStatus = bytes[index++];
        rxQueue.push(rxRunningStatus);
        rxQueue.push(bytes[index++]);
        rxQueue.push(bytes[index++]);
        return index;
    }
    switch(status){
      case 0xF7:
        rxQueue.push(bytes[index++]);
        break;
      case BMC_MIDI_SONG_SELECT:
        // status + 1 byte message
        rxQueue.push(bytes[index++]);
        rxQueue.push(bytes[index++]);
        break;
      case BMC_MIDI_SONG_POSITION:
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
        // status + 2 bytes message
        rxQueue.push(bytes[index++]);
        rxQueue.push(bytes[index++]);
        rxQueue.push(bytes[index++]);
        break;
      case 0xF4:
      case 0xF5:
      case 0xFD:
      case 0xFF:
        index++;
        break;
      default:
        // single status message
        rxQueue.push(bytes[index++]);
        break;
    }
    return index;
  }
  uint8_t parseRunningStatusMidiMessage(uint8_t *bytes, uint8_t size, uint8_t index, bool hasTimestamp){
    uint8_t status = bytes[index];
    if(!hasTimestamp){
      status = rxRunningStatus;
    }
    switch(status & 0xF0){
      case BMC_MIDI_PROGRAM_CHANGE:
      case BMC_MIDI_AFTER_TOUCH:
        // status + 1 byte message + running status
        if(!hasTimestamp && rxRunningStatus>0){
          rxQueue.push(rxRunningStatus);
          rxQueue.push(bytes[index++]);
          return index;
        }
        break;
      case BMC_MIDI_NOTE_OFF:
      case BMC_MIDI_NOTE_ON:
      case BMC_MIDI_AFTER_TOUCH_POLY:
      case BMC_MIDI_CONTROL_CHANGE:
      case BMC_MIDI_PITCH_BEND:
        // status + 2 bytes message+ running status
        if(!hasTimestamp && rxRunningStatus>0){
          rxQueue.push(rxRunningStatus);
          rxQueue.push(bytes[index++]);
          rxQueue.push(bytes[index++]);
          return index;
        }
        break;
    }
    switch(status){
      case 0xF7:
        if(hasTimestamp){
          rxQueue.push(bytes[index++]);
        }
        rxRunningStatus = 0;
        break;
      case BMC_MIDI_SONG_POSITION:
      case BMC_MIDI_TIME_CODE_QUARTER_FRAME:
      case BMC_MIDI_SONG_SELECT:
      case 0xF4:
      case 0xF5:
      case 0xFD:
        rxRunningStatus = 0;
        index++;
        break;
      default:
        // single status message
        rxQueue.push(bytes[index++]);
        break;
    }
    return index;
  }

  // Write data to the BLE buffer to send it 2 packets at a time
  // Even tho iOS says that it can receive more than 2 packets at a time
  // in my tests it only seems to accept 2 packets per connection interval
  // so we need to buffer any bytes written by the MIDI library,
  // then flush them out 2 packets at a time, each packet with up to 20 bytes
  // including header and timestamps, and each pair of packets sent within an interval of BMC_BLE_PACKET_TX_INTERVAL
  // So the idea here is to buffer bytes without timestamps then everytime we update()
  // we check the length of the buffer, we check the status bytes and based on that we
  // split the bytes into 2 packets.
  // this is slower and sortof redundant and convoluted but it's the only way I've been
  // able to send larger System Exclusive arrays to communicate with the Editor over BLE
  // Obviously this makes this BLE MIDI Implementation not suitable for MIDI Clock...
  void flushBle(){
    // if there's an unsent packet try sending it again.
    // until this packet is sent no other packets will be sent
    if(txPacketSize>0){
      // has enough time passed?
      if((millis() - txTime) >= BMC_BLE_PACKET_RESEND_TX_INTERVAL){
        #ifdef BMC_DEBUG
          if(globals.getBleDebug()){
            BMC_PRINTLN("-------- Trying to resend packet --------",millis());
          }
        #endif
        // try sending the packet, if it's sent clear the unsent packet and the txBuffer as usual
        // we always set the txTime to the current millis for the next pass
        if(ble.setValue(txPacket, txPacketSize)){
          // packet was sent, clear the buffer
          clearTxBuffers();
          #ifdef BMC_DEBUG
            if(globals.getBleDebug()){
              BMC_PRINTLN("****** PACKET WAS RE-SENT ******",millis());
            }
          #endif
        } else {
          // if the packet was not sent then we will appempt to send it again
          // in BMC_BLE_PACKET_RESEND_TX_INTERVAL ms
          #ifdef BMC_DEBUG
            if(globals.getBleDebug()){
              BMC_PRINTLN("!!!!!!!!!!!!!!!!!!!!");
              BMC_PRINTLN("PACKET WAS NOT RE-SENT!!!!!!!!!!",millis());
              BMC_PRINTLN("!!!!!!!!!!!!!!!!!!!!");
            }
          #endif
        }
        txTime = millis();
      }
      return;
    }
    //BMC_PRINTLN("BLE ???",txQueue.count());
    if(txQueue.count()>0 && ( (millis() - txTime) >= txAdditionalMs ) ){
      uint8_t totalPacketsSent = 0;
      while(totalPacketsSent<BMC_BLE_MAX_PACKETS && txQueue.count()>0){
        // we only want to peek at the next byte and then
        // in writeByteToBlePacket we'll pop it, this is so we can make sure
        // that we have enough room in the packet to send it out
        // if we don't we leave the value for the next packet
        uint8_t value = txQueue.peek();
        totalPacketsSent += writeByteToBlePacket(value);
        // if we still have more than 18 bytes it's likely that the rest of the bytes will have to
        // fit inside 2 more packets, in which case we increase the time to wait before sending
        // the 3rd packet
        if(totalPacketsSent==1 && txQueue.count()>(BMC_BLE_MIDI_TX_BUFFER_SIZE-2)){
          txAdditionalMs = BMC_BLE_MIDI_TX_BUFFER_SIZE + BMC_BLE_PACKET_TX_INTERVAL;
        }
      }
      // we are done sending the txBuffer so reset the extra time
      if(txQueue.count()==0){
        txAdditionalMs = BMC_BLE_PACKET_TX_INTERVAL;
      }
      txTime = millis();
    }
  }

  uint8_t writeByteToBlePacket(uint8_t value){
    // @ txTimestamps the number of low timestamps that will be appended to the message
    // if it's the end of a system exclusive just send the buffer out
    uint8_t additionalBytes = txTimestamps;
    if(value == 0xF7){
      // check if there's room for the 0xF7 and it's timestamp
      // if not then just send the current buffer and send the 0xF7 after
      additionalBytes += 2;
      if(txBufferSize+additionalBytes > BMC_BLE_MIDI_TX_BUFFER_SIZE){
        return send();
      }
      txTimestamps++;
      txBuffer[txBufferSize++] = txQueue.pop();
      flags.off(BMC_MIDI_BLE_FLAG_SYSEX_OPEN);
      return send();
    }
    // if it's the start then start collecting the bytes
    if(value == 0xF0){
      // if the buffer size is more than 0 then send the buffer
      // and start this sysex in the next packet
      if(txBufferSize>0){
        return send();
      }
      txTimestamps++;
      flags.on(BMC_MIDI_BLE_FLAG_SYSEX_OPEN);
      txBuffer[txBufferSize++] = txQueue.pop();
      return 0;
    }
    // if we are currently reading a sysex then dont sent it out
    // unless we filled the buffer
    if(flags.read(BMC_MIDI_BLE_FLAG_SYSEX_OPEN)){
      additionalBytes++;
      txBuffer[txBufferSize++] = txQueue.pop();
      if((txBufferSize-1)+additionalBytes == BMC_BLE_MIDI_TX_BUFFER_SIZE){
        return send();
      }
      return 0;
    }
    // if it's not a sysex we can try and send multiple messages in one packet
    // but first we check to make sure that we have room for the total bytes of the message
    // we have to make sure we have enough room for the status + it's bytes + 1 timestamp
    if(BMCTools::isOneByteMidiMessage(value)){
      // single status message, we need to make sure we have enough room
      // for the status byte and it's timestamp
      additionalBytes += 2;
      if(txBufferSize+additionalBytes <= BMC_BLE_MIDI_TX_BUFFER_SIZE){
        // we have enough room for it
        txTimestamps++;
        txBuffer[txBufferSize++] = txQueue.pop();
        // send the packet if the buffer is full or it's the end of the data
        if((txBufferSize-1)+txTimestamps == BMC_BLE_MIDI_TX_BUFFER_SIZE || txQueue.count() == 0){
          return send();
        }
      } else {
        // we don't have enough room for it so flush it out and
        // leave this status for the next packet
        return send();
      }
    } else if(BMCTools::isTwoByteMidiMessage(value)){


      // status + 1 data byte message,
      // we need to make sure we have enough room for status + data1 + timestamp
      additionalBytes += 3;
      if(txRunningStatus>0 && txRunningStatus == value){
        // this is a running status, we check if we can fit it
        // we only need to send the next byte not the status nor the timestamp
        additionalBytes -= 2;
      }
      if(txBufferSize+additionalBytes <= BMC_BLE_MIDI_TX_BUFFER_SIZE){
        // if it's a running status pop the status byte
        if(txRunningStatus>0 && txRunningStatus == value){
          txQueue.pop();// pop the status byte
        } else {
          // it's not a running status so we increase the timestamps number
          txTimestamps++;
        }

        // we have enough room for it, add the running status for next pass
        if(BMCTools::isRunningStatusMidiMessage(value)){
          txRunningStatus = value;
        }

        txBuffer[txBufferSize++] = txQueue.pop();

        // send the packet if the buffer is full or it's the end of the data
        if((txBufferSize-1)+txTimestamps == BMC_BLE_MIDI_TX_BUFFER_SIZE || txQueue.count() == 0){
          return send();
        }
      } else {
        // we don't have enough room for it so flush it out and
        // leave this status for the next one
        return send();
      }


    } else if(BMCTools::isThreeByteMidiMessage(value)){
      // status + 2 data bytes message,
      // we need to make sure we have enough room for, status + data1 + data2 + timestamp
      additionalBytes += 4;
      if(txRunningStatus>0 && txRunningStatus == value){
        // this is a running status, we check if we can fit it
        // otherwise we send it in the next packet
        additionalBytes -= 2;
      }

      if(txBufferSize+additionalBytes <= BMC_BLE_MIDI_TX_BUFFER_SIZE){
        // if it's a running status pop the status byte
        if(txRunningStatus>0 && txRunningStatus == value){
          txQueue.pop();// pop the status byte
        } else {
          // it's not a running status so we increase the timestamps number
          txTimestamps++;
        }

        // we have enough room for it
        if(BMCTools::isRunningStatusMidiMessage(value)){
          txRunningStatus = value;
        }

        txBuffer[txBufferSize++] = txQueue.pop();

        // send the packet if the buffer is full or it's the end of the data
        if(txBufferSize+txTimestamps == BMC_BLE_MIDI_TX_BUFFER_SIZE || txQueue.count() == 0){
          return send();
        }
      } else {
        // we don't have enough room for it so flush it out and
        // leave this status for the next one
        return send();
      }
    } else {
      if(bitRead(value,7)){
        txTimestamps++;
      }
      txBuffer[txBufferSize++] = txQueue.pop();
    }
    if((txBufferSize>0 && (txBufferSize-1)+txTimestamps == BMC_BLE_MIDI_TX_BUFFER_SIZE) || txQueue.count() == 0){
      return send();
    }
    return 0;
  }
  uint8_t send(){
    updateCurrentTimestamp();
    txPacket[txPacketSize++] = getHeaderByte();
    for(uint8_t i = 0; i < txBufferSize; i++){
      if(txPacketSize>=BMC_BLE_MIDI_TX_BUFFER_SIZE){
        break;
      }
      if(bitRead(txBuffer[i],7)){
        // always add a timestamp before a status byte
        txPacket[txPacketSize++] = getTimestamp();
      }
      txPacket[txPacketSize++] = txBuffer[i];
    }

    #ifdef BMC_DEBUG
      if(globals.getBleDebug()){
        BMC_PRINTLN("Outgoing Packet ");
        BMC_PRINT_ARRAY(true,txPacket, txPacketSize);
      }
    #endif

    if(ble.setValue(txPacket,txPacketSize)){
      // the packet was sent, we clear all buffers for any new packets to send
      clearTxBuffers();
    } else {
      // the packet was not sent, we don't clear the buffers so we can try
      // resending the packet, we return BMC_BLE_MAX_PACKETS
      #ifdef BMC_DEBUG
        if(globals.getBleDebug()){
          BMC_PRINTLN("!!!!!!!!!!!!!!!!!!!!");
          BMC_PRINTLN("PACKET WAS NOT SENT!!!!!!!!!!",millis());
          BMC_PRINTLN("!!!!!!!!!!!!!!!!!!!!");
        }
      #endif
      return BMC_BLE_MAX_PACKETS;
    }
    return 1;
  }
  void clearTxBuffers(){
    txBuffer[0] = 0;
    txBufferSize = 0;
    txPacket[0] = 0;
    txPacketSize = 0;
    txRunningStatus = 0;
    txTimestamps = 1;
  }
  uint8_t getHeaderByte(){
    return (((currentMillis - msOffset) >> 7) & 0x3F) | 0x80;
  }
  uint8_t getTimestamp(){
    return ((currentMillis - msOffset) & 0x7F) | 0x80;
  }
  void updateCurrentTimestamp(){
    //https://learn.sparkfun.com/tutorials/midi-ble-tutorial
    //Calculate timestamp.
    currentMillis = millis();
    if(currentMillis < 5000){
      if(msOffset > 5000){
        //it's been 49 days! millis rolled.
        while(msOffset > 5000){
          //roll msOffset - this should preserve current ~8 second count.
          msOffset += MAX_MS;
        }
      }
    }
    // if the offset is more than 2^13 ms away, move it up in 2^13 ms intervals
    while(currentMillis >= (unsigned long)(msOffset + MAX_MS)){
      msOffset += MAX_MS;
    }
  }
};


#endif
#endif
