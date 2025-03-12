/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Handle all the incoming MIDI Messages and spit out all others.

  editor midi isMaster structure (n=message length)
  0 = 0xF0
  1 = 0x7D sysex id A
  2 = 0x7D sysex id B
  3 = 0x7D sysex id C
  4 = 0xXX device id
  5 = 0xXX flags:
    bit0 -> query type    =>  0=read, 1=write
    bit1 -> query target  =>  0=global, 1=layer
    bit2 -> confirmation  =>  0=send response, 1=send acknowledge
  6 = 0xXX layer/item number (LSB)
  7 = 0xXX layer/item number (MSB)
  8 = 0xXX function id
  9 = start of data
  ...
  n-2 = 0xXX crc
  n-1   = 0xF7


  Requirements to Communicate with the editor:
  #1 BMC must NOT be connected to another editor app
  #2 The System Exclusive Id on the editor MUST match BMC_EDITOR_SYSEX_ID
     Every message to the editor must have this id,
     Byte 0 of the sysex is always 0xF0
     The ID are bytes 1, 2 , 3. BMC_EDITOR_SYSEX_ID has byte 3 as it's LSB
     The default BMC_EDITOR_SYSEX_ID is 0x7D7D7D, this id is split into:
     0x7D, 0x7D, 0x7D, if the id was 0x7D0102,
     byte 1 in the sysex would be 0x7D, byte 2 = 0x01, byte 3 = 0x02
  #3 All editor messages MUST contain a CRC
  #4 CRC MUST be located as the byte before 0xF0 (end of sysex)
     CRC is calculated by XOR'ing all bytes from 0xF0 until the CRC placeholder
     Here's an example of a CRC being created by BMCMidiMessage:
     // sysex = sysex array
     // n = the location of the CRC placeholder
     uint8_t checksum = 0;
     for(uint16_t i = 0; i < n; i++){
       checksum ^= (sysex[i] & 0x7F);
     }
     sysex[n] = checksum;

  To connect to the editor:
  #1 send a message with function id BMC_GLOBALF_CONNECT with "write" flag on
  #2 if BMC is already connected to another editor it will send a notification
  #3 if BMC is able to connect, a notification is sent with BMC_EDITOR_SYSEX_ID
     as the code
  #4 if the editor can not connet a notification will be sent with "error" flag on
  #5 uppon receiving all data you MUST notify BMC that you are done syncing
     with message BMC_GLOBALF_EDITOR_FETCH_COMPLETE, this will re-enable
     some features that are paused while syncing is ongoing

*/
#include "editor/BMC-Editor.h"

bool BMCEditor::read(){
  if(!incoming.isEditorMessage()){
    return false;
  }
  if(getMessageDeviceId() == deviceId){
    if(incoming.validateChecksum()){
      // assign the flags to make it easier to read them
      midiFlags.set(incoming.sysex[5]);

      // handle keeping the connection alive
      keepConnectionAlive();
      
      if(isUtilityMessage()){
        utilityCommand();
        #if BMC_RESET_INCOMING_EDITOR_MESSAGES
        incoming.reset();
        #endif
        return true;
      }
      if(isLayerMessage()){
        // editor/BMC-Editor.midi.layer.h
        layerProcessMessage();
      } else {
        // editor/BMC-Editor.midi.global.h
        globalProcessMessage();
      }
    } else {
      // notify invalid checksum received
      BMC_WARNING("INVALID CHECKSUM RECEIVED");
      sendNotification(0x01, BMC_NOTIFY_INVALID_CHECKSUM);
    }
    #if BMC_RESET_INCOMING_EDITOR_MESSAGES
    incoming.reset();
    #endif
    return true;
  } else if(chaingingPort!=BMC_NONE){
    uint8_t outPort = chaingingPort;
    // if it's not coming from the chaining port then it's coming from the editor
    // so we set the chaingingEditorPort to match the incoming port
    // and we send this message
    if(!BMC_MATCH_PORT(incoming.getSource(), chaingingPort)){
      if(chaingingEditorPort==0){
        chaingingEditorPort = incoming.getPort();
      }
    } else {
      outPort = chaingingEditorPort;
    }
    // send the sysex message to the editor
    midi.sendSysEx(
      outPort, // target port(s)
      incoming.getSysEx(), // the sysex array
      incoming.size(), // the sysex array length
      true, // does it have the 0xF0 & 0xF7 bytes
      0, // cable, used for USB
      false // should it trigger MIDI Out activity
    );
    #if BMC_RESET_INCOMING_EDITOR_MESSAGES
    incoming.reset();
    #endif
  }
  return false;
}
void BMCEditor::sendToEditor(BMCMidiMessage message, bool appendCRC,
                              bool midiOutActivityAllowed){
  if(message.isSysEx() && port!=BMC_NONE){
    // create CRC and also append a 0 for the crc at the end of the array
    message.createChecksum(appendCRC);
    // send the sysex message
    midi.sendSysEx(
      port, // target port(s)
      message.getSysEx(), // the sysex array
      message.size(), // the sysex array length
      false, // does it have the 0xF0 & 0xF7 bytes
      0, // cable, used for USB
      midiOutActivityAllowed // should it trigger MIDI Out activity
    );
  }
}
void BMCEditor::sendNotification(uint16_t code, uint32_t payload, bool hasError, bool forceResponse){
  //BMCF_NOTIFY, byte 9 = 1 for error
  BMCEditorMidiFlags flag;
  flag.setError(hasError);

  BMCMidiMessage buff;
  uint8_t outPort = port;
  if(!forceResponse){
    outPort = incoming.getPort();
  }
  buff.prepareEditorMessage(outPort, deviceId, BMCF_NOTIFY, flag.get(), 0);
  
  // the source of the notification
  buff.appendSysExByte(getMessageRequestId());
  // notification code
  buff.appendToSysEx16Bits(code);
  // the payload
  buff.appendToSysEx32Bits(payload);
  // add the flags of the source message
  buff.appendSysExByte(getMessageFlags());
  // send
  if(!forceResponse){
    sendToEditor(buff);
  } else {
    buff.createChecksum(true);
    // send the sysex message
    midi.sendSysEx(
      buff.getPort(), // target port(s)
      buff.getSysEx(), // the sysex array
      buff.size(), // the sysex array length
      false, // does it have the 0xF0 & 0xF7 bytes
      0, // cable, used for USB
      false // should it trigger MIDI Out activity
    );
  }
  
}
void BMCEditor::sendInvalidIndexReceivedMessage(){
  sendNotification(BMC_NOTIFY_INVALID_INDEX, 0, true);
}
