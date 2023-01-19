/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Handle all the global incoming MIDI Messages and spit out all others.
*/
#include "editor/BMC-Editor.h"

void BMCEditor::layerProcessMessage(){
  switch(getMessageRequestId()){
    case BMC_LAYERF_LAYER:
      layerMessage(isWriteMessage());
      break;
    case BMC_LAYERF_LAYER_NAME:
      layerNameMessage(isWriteMessage());
      break;
  }
}
void BMCEditor::layerMessage(bool write){
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  //BMC_LAYERF_LAYER
  uint8_t layer = getMessageLayerNumber();
  if(layer>=BMC_MAX_LAYERS){
    sendNotification(BMC_NOTIFY_INVALID_LAYER, layer, true);
    return;
  }
  if(write){
    // switch layers
    if(layer<BMC_MAX_LAYERS){
      this->layer = layer;
      reloadData();
    }
  }
}
void BMCEditor::layerNameMessage(bool write){
  if(!isValidLayerMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 13;
  // handle backup
  if(write && backupActive()){
    backupLayerName(sysExLength);
    return;
  }
  uint8_t layer = getMessageLayerNumber();

  if(layer >= BMC_MAX_LAYERS){
    sendNotification(BMC_NOTIFY_INVALID_LAYER, layer, true);
    return;
  }
  if(write && incoming.size() != sysExLength){
    BMC_PRINTLN("pageNameMessage: incoming.size()", incoming.size(), "sysExLength", sysExLength);
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write){
    store.layers[layer].name     = incoming.get14Bits(9);
    if(!backupActive()){
      saveLayersAndReloadData(layer);
    }
  }
  BMCEditorMidiFlags flag;
  flag.setLayer(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_LAYERF_LAYER_NAME, flag, layer);
  buff.appendToSysEx14Bits(store.layers[layer].name);
  sendToEditor(buff);
}
void BMCEditor::layerSendChangeMessage(bool onlyIfConnected){
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  BMCEditorMidiFlags flag;
  flag.setWrite(false);
  flag.setLayer(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_LAYERF_LAYER, flag, layer);
  buff.appendToSysEx14Bits(BMC_MAX_LAYERS);
  buff.appendToSysEx14Bits(layer);
  sendToEditor(buff);
}