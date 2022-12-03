/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Handle all the global incoming MIDI Messages and spit out all others.
*/
#include "editor/BMC-Editor.h"

void BMCEditor::pageProcessMessage(){
  switch(getMessageRequestId()){
    case BMC_PAGEF_PAGE:
      pageMessage(isWriteMessage());
      break;
    case BMC_PAGEF_PAGE_NAME:
      pageNameMessage(isWriteMessage());
      break;
  }
}
void BMCEditor::pageMessage(bool write){
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  //BMC_PAGEF_PAGE
  uint8_t page = getMessagePageNumber();
  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  }
  if(write){
    // switch pages
    if(page<BMC_MAX_PAGES){
      this->page = page;
      reloadData();
    }
  }
}
void BMCEditor::pageNameMessage(bool write){
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 13;
  // handle backup
  if(write && backupActive()){
    backupPageName(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();

  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  }
  if(write && incoming.size() != sysExLength){
    BMC_PRINTLN("pageNameMessage: incoming.size()", incoming.size(), "sysExLength", sysExLength);
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  if(write){
    store.pages[page].name     = incoming.get14Bits(9);
    if(!backupActive()){
      savePagesAndReloadData(page);
    }
  }
  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_PAGE_NAME, flag, page);
  buff.appendToSysEx14Bits(store.pages[page].name);
  sendToEditor(buff);
}
void BMCEditor::pageSendChangeMessage(bool onlyIfConnected){
  if(flags.read(BMC_EDITOR_FLAG_BACKUP_ACTIVE)){
    return;
  }
  if(onlyIfConnected && !midi.globals.editorConnected()){
    return;
  }
  BMCEditorMidiFlags flag;
  flag.setWrite(false);
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_PAGE, flag, page);
  buff.appendToSysEx14Bits(BMC_MAX_PAGES);
  buff.appendToSysEx14Bits(page);
  sendToEditor(buff);
}