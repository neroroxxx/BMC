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
    case BMC_PAGEF_BUTTON:
      pageButtonMessage(isWriteMessage());
      break;
    case BMC_PAGEF_LED:
      pageLedMessage(isWriteMessage());
      break;
    case BMC_PAGEF_PWM_LED:
      pagePwmLedMessage(isWriteMessage());
      break;
    case BMC_PAGEF_PIXEL:
      pagePixelMessage(isWriteMessage());
      break;
    case BMC_PAGEF_RGB_PIXEL:
      pageRgbPixelMessage(isWriteMessage());
      break;
    case BMC_PAGEF_POT:
      pagePotMessage(isWriteMessage());
      break;
    case BMC_PAGEF_ENCODER:
      pageEncoderMessage(isWriteMessage());
      break;
    case BMC_PAGEF_HARDWARE_COPY:
    case BMC_PAGEF_HARDWARE_SWAP:
      pageHardwareCopySwapMessage(isWriteMessage());
      break;
    case BMC_PAGEF_BUTTON_EVENT_SHIFT_POSITION:
      pageButtonEventShiftPositionMessage(isWriteMessage());
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
  uint8_t sysExLength = 12;
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
  sysExLength += BMC_NAME_LEN_PAGES;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

  #if BMC_NAME_LEN_PAGES > 1
  if(write){
    incoming.getStringFromSysEx(10, store.pages[page].name, BMC_NAME_LEN_PAGES);
    if(!backupActive()){
      savePagesAndReloadData(page);
    }
  }
  #endif
  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_PAGE_NAME, flag, page);
  buff.appendToSysEx7Bits(BMC_NAME_LEN_PAGES);//9
  #if BMC_NAME_LEN_PAGES > 1
    buff.appendCharArrayToSysEx(store.pages[page].name,BMC_NAME_LEN_PAGES);
  #endif
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
  buff.appendToSysEx8Bits(BMC_MAX_PAGES);
  buff.appendToSysEx8Bits(page);
  sendToEditor(buff);
}
void BMCEditor::pageButtonMessage(bool write){
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 22;
  // handle backup
  if(write && backupActive()){
    backupPageButton(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();
  uint8_t buttonIndex = incoming.sysex[9];
  uint8_t eventIndex = incoming.sysex[10];
  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  } else if(buttonIndex>0 && buttonIndex>=BMC_MAX_BUTTONS){
    sendNotification(BMC_NOTIFY_INVALID_BUTTON, buttonIndex, true);
    return;
  } else if(eventIndex>0 && eventIndex>=BMC_MAX_BUTTON_EVENTS){
    sendNotification(BMC_NOTIFY_INVALID_BUTTON_EVENT, eventIndex, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_BUTTONS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
#if BMC_MAX_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 0
  if(write){
    // write new data and save, starts at byte 9
    // we only want to store the mode on the current button event
    // the flags are always stored on the first event of the page button
    if(isWriteToAllPages()){
      for(uint8_t i=0;i<BMC_MAX_PAGES;i++){
        bmcStoreButton& button = store.pages[i].buttons[buttonIndex];
        bmcStoreButtonEvent& event = button.events[eventIndex];
        event.mode  = incoming.get8Bits(11) & 0x0F;//+2
        event.ports = incoming.get8Bits(13);//+2
        event.event = incoming.get32Bits(15);

        // add the button flags to the first button
        uint8_t m = button.events[0].mode & 0x0F;
        m |= (incoming.get8Bits(11) & 0xF0);//+2
        button.events[0].mode = m;

        #if BMC_NAME_LEN_BUTTONS > 1
          // starts at 18
          incoming.getStringFromSysEx(20,button.name,BMC_NAME_LEN_BUTTONS);
        #endif
      }
      if(!backupActive()){
        savePagesAndReloadData();
      }
    } else {
      bmcStoreButton& button = store.pages[page].buttons[buttonIndex];
      bmcStoreButtonEvent& event = button.events[eventIndex];
      event.mode  = incoming.get8Bits(11) & 0x0F;//+2
      event.ports = incoming.get8Bits(13);//+2
      event.event = incoming.get32Bits(15);

      // add the button flags to the first button
      uint8_t m = button.events[0].mode & 0x0F;
      m |= (incoming.get8Bits(11) & 0xF0);//+2
      button.events[0].mode = m;

      #if BMC_NAME_LEN_BUTTONS > 1
        incoming.getStringFromSysEx(20,button.name,BMC_NAME_LEN_BUTTONS);
      #endif
      if(!backupActive()){
        savePagesAndReloadData(page);
      }
    }
  }
#endif

  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_BUTTON, flag, page);
  buff.appendToSysEx7Bits(BMC_MAX_BUTTONS);
  buff.appendToSysEx7Bits(BMC_MAX_BUTTON_EVENTS);
#if BMC_MAX_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 0
  bmcStoreButton& button = store.pages[page].buttons[buttonIndex];
  buff.appendToSysEx7Bits(buttonIndex);
  buff.appendToSysEx7Bits(eventIndex);
  buff.appendToSysEx16Bits(BMCBuildData::getButtonPosition(buttonIndex,true));
  buff.appendToSysEx16Bits(BMCBuildData::getButtonPosition(buttonIndex,false));
  uint8_t mode = button.events[eventIndex].mode & 0x0F;
  mode |= (button.events[0].mode & 0xF0);//+2
  buff.appendToSysEx8Bits(mode);
  buff.appendToSysEx8Bits(button.events[eventIndex].ports);
  buff.appendToSysEx32Bits(button.events[eventIndex].event);
  #if BMC_NAME_LEN_BUTTONS > 1
    buff.appendCharArrayToSysEx(button.name,BMC_NAME_LEN_BUTTONS);
  #endif
#endif
  sendToEditor(buff);
}

void BMCEditor::pageLedMessage(bool write){
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 17;
  // handle backup
  if(write && backupActive()){
    backupPageLed(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();
  uint8_t index = incoming.sysex[9];

  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  } else if(index>0 && index>=BMC_MAX_LEDS){
    sendNotification(BMC_NOTIFY_INVALID_LED, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_LEDS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

#if BMC_MAX_LEDS > 0
  // write new data and save, starts at byte 9
  if(write){
    if(isWriteToAllPages()){
      for(uint8_t i=0;i<BMC_MAX_PAGES;i++){
        bmcStoreLed &item = store.pages[i].leds[index];
        item.event = incoming.get32Bits(10);
        #if BMC_NAME_LEN_LEDS > 1
          incoming.getStringFromSysEx(15,item.name,BMC_NAME_LEN_LEDS);
        #endif
      }
      if(!backupActive()){
        savePagesAndReloadData();
      }
    } else {
      bmcStoreLed &item = store.pages[page].leds[index];
      item.event = incoming.get32Bits(10);
      #if BMC_NAME_LEN_LEDS > 1
        incoming.getStringFromSysEx(15,item.name,BMC_NAME_LEN_LEDS);
      #endif
      if(!backupActive()){
        savePagesAndReloadData(page);
      }
    }
  }
#endif

  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_LED, flag, page);
  buff.appendToSysEx7Bits(BMC_MAX_LEDS); //9
#if BMC_MAX_LEDS > 0
  bmcStoreLed &item = store.pages[page].leds[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx7Bits(BMCBuildData::getLedColor(index));
  buff.appendToSysEx16Bits(BMCBuildData::getLedPosition(index,true));
  buff.appendToSysEx16Bits(BMCBuildData::getLedPosition(index,false));
  buff.appendToSysEx32Bits(item.event);
  #if BMC_NAME_LEN_LEDS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_LEDS);
  #endif
  buff.appendToSysEx7Bits(BMC_MAX_LEDS); //9
#endif
  sendToEditor(buff);
}

void BMCEditor::pagePwmLedMessage(bool write){
  //BMC_PRINTLN("PWM LED REQUEST RECEIVED");
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 17;
  // handle backup
  if(write && backupActive()){
    backupPagePwmLed(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();
  uint8_t index = incoming.sysex[9];

  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  } else if(index>0 && index>=BMC_MAX_PWM_LEDS){
    sendNotification(BMC_NOTIFY_INVALID_LED, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_LEDS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

#if BMC_MAX_PWM_LEDS > 0
  if(write){
    // write new data and save, starts at byte 9
    if(isWriteToAllPages()){
      for(uint8_t i=0;i<BMC_MAX_PAGES;i++){
        bmcStoreLed& item = store.pages[i].pwmLeds[index];
        item.event = incoming.get32Bits(10);
        #if BMC_NAME_LEN_LEDS > 1
          incoming.getStringFromSysEx(15, item.name, BMC_NAME_LEN_LEDS);
        #endif
      }
      if(!backupActive()){
        savePagesAndReloadData();
      }
    } else {
      bmcStoreLed &item = store.pages[page].pwmLeds[index];
      item.event = incoming.get32Bits(10);
      #if BMC_NAME_LEN_LEDS > 1
        incoming.getStringFromSysEx(15, item.name, BMC_NAME_LEN_LEDS);
      #endif
      if(!backupActive()){
        savePagesAndReloadData(page);
      }
    }
  }
#endif
  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_PWM_LED, flag, page);
  buff.appendToSysEx7Bits(BMC_MAX_PWM_LEDS);//9


#if BMC_MAX_PWM_LEDS > 0
  bmcStoreLed &item = store.pages[page].pwmLeds[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx7Bits(BMCBuildData::getPwmLedColor(index));
  buff.appendToSysEx16Bits(BMCBuildData::getPwmLedPosition(index,true));
  buff.appendToSysEx16Bits(BMCBuildData::getPwmLedPosition(index,false));
  buff.appendToSysEx32Bits(item.event);
  #if BMC_NAME_LEN_LEDS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_LEDS);
  #endif
#endif

  sendToEditor(buff);
}

void BMCEditor::pagePixelMessage(bool write){
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 17;
  // handle backup
  if(write && backupActive()){
    backupPagePixel(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();
  uint8_t index = incoming.sysex[9];

  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  } else if(index>0 && index>=BMC_MAX_PIXELS){
    sendNotification(BMC_NOTIFY_INVALID_PIXEL, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_LEDS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

  #if BMC_MAX_PIXELS > 0
  // write new data and save, starts at byte 9
  if(write){
    if(isWriteToAllPages()){
      for(uint8_t i=0;i<BMC_MAX_PAGES;i++){
        bmcStoreLed &item = store.pages[i].pixels[index];
        item.event = incoming.get32Bits(10);
        #if BMC_NAME_LEN_LEDS > 1
          incoming.getStringFromSysEx(15,item.name,BMC_NAME_LEN_LEDS);
        #endif
      }
      if(!backupActive()){
        savePagesAndReloadData();
      }
    } else {
      bmcStoreLed &item = store.pages[page].pixels[index];
      item.event = incoming.get32Bits(10);
      #if BMC_NAME_LEN_LEDS > 1
        incoming.getStringFromSysEx(15,item.name,BMC_NAME_LEN_LEDS);
      #endif
      if(!backupActive()){
        savePagesAndReloadData(page);
      }
    }
  }
  #endif

  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_PIXEL, flag, page);
  buff.appendToSysEx7Bits(BMC_MAX_PIXELS);//9
  #if BMC_MAX_PIXELS > 0
  bmcStoreLed &item = store.pages[page].pixels[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx7Bits(BMCBuildData::getPixelDefaultColor(index));
  buff.appendToSysEx16Bits(BMCBuildData::getPixelPosition(index,true));
  buff.appendToSysEx16Bits(BMCBuildData::getPixelPosition(index,false));
  buff.appendToSysEx32Bits(item.event);
  #if BMC_NAME_LEN_LEDS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_LEDS);
  #endif
  #endif
  sendToEditor(buff);
}
void BMCEditor::pageRgbPixelMessage(bool write){
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 27;
  // handle backup
  if(write && backupActive()){
    backupPageRgbPixel(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();
  uint8_t index = incoming.sysex[9];

  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  } else if(index>0 && index>=BMC_MAX_RGB_PIXELS){
    sendNotification(BMC_NOTIFY_INVALID_RGB_PIXEL, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_LEDS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  #if BMC_MAX_RGB_PIXELS > 0
  // write new data and save, starts at byte 9
  if(write){
    if(isWriteToAllPages()){
      for(uint8_t i=0;i<BMC_MAX_PAGES;i++){
        bmcStoreRgbLed &item = store.pages[i].rgbPixels[index];
        item.red = incoming.get32Bits(10);
        item.green = incoming.get32Bits(15);
        item.blue = incoming.get32Bits(20);
        #if BMC_NAME_LEN_LEDS > 1
          incoming.getStringFromSysEx(25,item.name, BMC_NAME_LEN_LEDS);
        #endif
      }
      if(!backupActive()){
        savePagesAndReloadData();
      }
    } else {
      bmcStoreRgbLed &item = store.pages[page].rgbPixels[index];
      item.red = incoming.get32Bits(10);
      item.green = incoming.get32Bits(15);
      item.blue = incoming.get32Bits(20);
      #if BMC_NAME_LEN_LEDS > 1
        incoming.getStringFromSysEx(25,item.name, BMC_NAME_LEN_LEDS);
      #endif
      if(!backupActive()){
        savePagesAndReloadData(page);
      }
    }
  }
  #endif

  BMCEditorMidiFlags flag;
  flag.setPage(true);
  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_RGB_PIXEL, flag, page);
  buff.appendToSysEx7Bits(BMC_MAX_RGB_PIXELS);//9
  #if BMC_MAX_RGB_PIXELS > 0
  bmcStoreRgbLed &item = store.pages[page].rgbPixels[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx7Bits(BMCBuildData::getRgbPixelDefaultColor(index));
  buff.appendToSysEx16Bits(BMCBuildData::getRgbPixelPosition(index, true));
  buff.appendToSysEx16Bits(BMCBuildData::getRgbPixelPosition(index, false));
  buff.appendToSysEx32Bits(item.red);
  buff.appendToSysEx32Bits(item.green);
  buff.appendToSysEx32Bits(item.blue);
  #if BMC_NAME_LEN_LEDS > 1
    buff.appendCharArrayToSysEx(item.name, BMC_NAME_LEN_LEDS);
  #endif
  #endif
  sendToEditor(buff);
}
void BMCEditor::pagePotMessage(bool write){
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 19;
  // handle backup
  if(write && backupActive()){
    backupPagePot(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();
  uint8_t index = incoming.sysex[9];

  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  } else if(index>0 && index>=BMC_MAX_POTS){
    sendNotification(BMC_NOTIFY_INVALID_POT, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_POTS;
  #if defined(BMC_USE_POT_TOE_SWITCH)
    sysExLength += 8;
  #endif
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

#if BMC_MAX_POTS > 0
  if(write){
    // write new data and save, starts at byte 9
    if(isWriteToAllPages()){
      for(uint8_t i=0;i<BMC_MAX_PAGES;i++){
        bmcStorePot& item = store.pages[i].pots[index];
        item.ports = incoming.get8Bits(10);
        item.event = incoming.get32Bits(12);
        #if defined(BMC_USE_POT_TOE_SWITCH)
          item.toeSwitch = incoming.get32Bits(17);
          item.toeSwitchFlags = incoming.get16Bits(22);
          #if BMC_NAME_LEN_POTS > 1
            incoming.getStringFromSysEx(25, item.name, BMC_NAME_LEN_POTS);
          #endif
        #else
          #if BMC_NAME_LEN_POTS > 1
            incoming.getStringFromSysEx(22, item.name, BMC_NAME_LEN_POTS);
          #endif
        #endif
      }
      if(!backupActive()){
        savePagesAndReloadData();
      }
    } else {
      bmcStorePot& item = store.pages[page].pots[index];
      item.ports = incoming.get8Bits(10);
      item.event = incoming.get32Bits(12);
      #if defined(BMC_USE_POT_TOE_SWITCH)
        item.toeSwitch = incoming.get32Bits(17);
        item.toeSwitchFlags = incoming.get16Bits(22);
        #if BMC_NAME_LEN_POTS > 1
          incoming.getStringFromSysEx(25, item.name, BMC_NAME_LEN_POTS);
        #endif
      #else
        #if BMC_NAME_LEN_POTS > 1
          incoming.getStringFromSysEx(22, item.name, BMC_NAME_LEN_POTS);
        #endif
      #endif
      if(!backupActive()){
        savePagesAndReloadData(page);
      }
    }
  }
#endif
  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_POT, flag, page);
  buff.appendToSysEx7Bits(BMC_MAX_POTS);//9
#if BMC_MAX_POTS > 0
  bmcStorePot& item = store.pages[page].pots[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx7Bits(BMCBuildData::getPotStyle(index));
  buff.appendToSysEx16Bits(BMCBuildData::getPotPosition(index,true));
  buff.appendToSysEx16Bits(BMCBuildData::getPotPosition(index,false));
  buff.appendToSysEx8Bits(item.ports);
  buff.appendToSysEx32Bits(item.event);
  #if defined(BMC_USE_POT_TOE_SWITCH)
    buff.appendToSysEx32Bits(item.toeSwitch);
    buff.appendToSysEx16Bits(item.toeSwitchFlags);
  #endif
  #if BMC_NAME_LEN_POTS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_POTS);
  #endif
#endif
  sendToEditor(buff);
}
void BMCEditor::pageEncoderMessage(bool write){
  if(!isValidPageMessage() && !backupActive()){
    return;
  }
  uint8_t sysExLength = 21;
  // handle backup
  if(write && backupActive()){
    backupPageEncoder(sysExLength);
    return;
  }
  uint8_t page = getMessagePageNumber();
  uint8_t index = incoming.sysex[9];

  if(page>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, page, true);
    return;
  } else if(index>0 && index>=BMC_MAX_ENCODERS){
    sendNotification(BMC_NOTIFY_INVALID_ENCODER, index, true);
    return;
  }
  sysExLength += BMC_NAME_LEN_ENCODERS;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }

#if BMC_MAX_ENCODERS > 0
  if(write){
    if(isWriteToAllPages()){
      for(uint8_t i=0;i<BMC_MAX_PAGES;i++){
        bmcStoreEncoder& item = store.pages[i].encoders[index];
        item.mode = incoming.get8Bits(10);//2
        item.ports = incoming.get8Bits(12);//2
        item.event = incoming.get32Bits(14);
        #if BMC_NAME_LEN_ENCODERS > 1
          incoming.getStringFromSysEx(19,item.name,BMC_NAME_LEN_ENCODERS);
        #endif
      }
      if(!backupActive()){
        savePagesAndReloadData();
      }
    } else {
      bmcStoreEncoder& item = store.pages[page].encoders[index];
      item.mode = incoming.get8Bits(10);//2
      item.ports = incoming.get8Bits(12);//2
      item.event = incoming.get32Bits(14);
      #if BMC_NAME_LEN_ENCODERS > 1
        incoming.getStringFromSysEx(19,item.name,BMC_NAME_LEN_ENCODERS);
      #endif
      if(!backupActive()){
        savePagesAndReloadData(page);
      }
    }
  }
#endif

  BMCEditorMidiFlags flag;
  flag.setPage(true);

  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_ENCODER, flag, page);
  buff.appendToSysEx7Bits(BMC_MAX_ENCODERS);//9
#if BMC_MAX_ENCODERS > 0
  bmcStoreEncoder& item = store.pages[page].encoders[index];
  buff.appendToSysEx7Bits(index);
  buff.appendToSysEx16Bits(BMCBuildData::getEncoderPosition(index,true));
  buff.appendToSysEx16Bits(BMCBuildData::getEncoderPosition(index,false));
  buff.appendToSysEx8Bits(item.mode);
  buff.appendToSysEx8Bits(item.ports);
  buff.appendToSysEx32Bits(item.event);
  #if BMC_NAME_LEN_ENCODERS > 1
    buff.appendCharArrayToSysEx(item.name,BMC_NAME_LEN_ENCODERS);
  #endif
#endif
  sendToEditor(buff);
}

void BMCEditor::pageButtonEventShiftPositionMessage(bool write){
  if(backupActive() || !isValidPageMessage()){
    return;
  }
  // 11 minimumlength + 3 bytes
  uint8_t sysExLength = 14;
  if(write && incoming.size() != sysExLength){
    sendNotification(BMC_NOTIFY_INVALID_SIZE, sysExLength, true);
    return;
  }
  uint8_t resp = 0;
  uint8_t page = getMessagePageNumber();
#if BMC_MAX_BUTTONS > 0 && BMC_MAX_BUTTON_EVENTS > 1
  if(write){
    uint8_t buttonIndex = incoming.sysex[9];
    uint8_t eventSource = incoming.sysex[10];
    uint8_t eventTarget = incoming.sysex[11];
    if(buttonIndex<BMC_MAX_BUTTONS && eventSource<BMC_MAX_BUTTON_EVENTS && eventTarget<BMC_MAX_BUTTON_EVENTS){
      if(eventSource!=eventTarget){
        bmcStoreButtonEvent source = store.pages[page].buttons[buttonIndex].events[eventSource];
        if(eventSource>eventTarget){
          // moved up
          for(int i=(eventSource-1);i>=eventTarget;i--){
            if(i>=0 && (i+1) < BMC_MAX_BUTTON_EVENTS){
              bmcStoreButtonEvent tmp = store.pages[page].buttons[buttonIndex].events[i];
              store.pages[page].buttons[buttonIndex].events[i+1] = tmp;
            }
          }
        } else if(eventSource<eventTarget){
          // moved down
          for(uint8_t i=eventSource;i<eventTarget;i++){
            if((i+1)<BMC_MAX_BUTTON_EVENTS){
              bmcStoreButtonEvent tmp = store.pages[page].buttons[buttonIndex].events[i+1];
              store.pages[page].buttons[buttonIndex].events[i] = tmp;
            }

          }
        }
        BMC_PRINTLN("Moved button event from",eventSource,"to",eventTarget);
        store.pages[page].buttons[buttonIndex].events[eventTarget] = source;
        resp = 1;
      }
      savePagesAndReloadData(page);
    }
  }
#endif
  BMCEditorMidiFlags flag;
  flag.setPage(true);
  BMCMidiMessage buff;
  buff.prepareEditorMessage(port, deviceId, BMC_PAGEF_BUTTON_EVENT_SHIFT_POSITION, flag, page);
  buff.appendToSysEx7Bits(resp);
  sendToEditor(buff);
}

void BMCEditor::pageHardwareCopySwapMessage(bool write){
  if(backupActive() || (!isValidPageMessage() || !write)){
    return;
  }
  uint8_t mode = getMessageRequestId();
  if(mode!=BMC_PAGEF_HARDWARE_COPY && mode!=BMC_PAGEF_HARDWARE_SWAP){
    sendNotification(BMC_NOTIFY_INVALID_REQUEST, 0, true);
    return;
  } else if(incoming.size() != 18){
    // check required SysEx Length
    sendNotification(BMC_NOTIFY_INVALID_PAGE, 18, true);
    return;
  }
  // must be a page message and must be a write message
  uint8_t hardwareType = incoming.get7Bits(9);
  uint8_t hardwareLength = checkIfHardwareAvailable(hardwareType);
  // check if the hardware type is vailable otherwise send an error message
  if(hardwareLength==0 && hardwareType!=BMC_ITEM_ID_PAGE){
    sendNotification(BMC_NOTIFY_INVALID_INDEX, hardwareLength | (__LINE__<<16), true);
    return;
  }

  uint8_t sourcePage = incoming.get8Bits(10);
  uint8_t targetPage = incoming.get8Bits(12);
  uint8_t sourceItem = incoming.get7Bits(14);
  uint8_t targetItem = incoming.get7Bits(15);
  if(sourcePage==targetPage && sourceItem==targetItem){
    // notify: copying the same item in the same page
    sendNotification(BMC_NOTIFY_INVALID_COPY_REQUEST, __LINE__, true);
    return;
  }
  if(sourcePage>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, sourcePage | (__LINE__<<16), true);
    return;
  } else if (targetPage>=BMC_MAX_PAGES){
    sendNotification(BMC_NOTIFY_INVALID_PAGE, targetPage | (__LINE__<<16), true);
    return;
  }
  if(hardwareType!=BMC_ITEM_ID_PAGE){
    if(sourceItem>=hardwareLength){
      sendNotification(BMC_NOTIFY_INVALID_INDEX, sourceItem | (__LINE__<<16), true);
      return;
    } else if(targetItem>=hardwareLength){
      sendNotification(BMC_NOTIFY_INVALID_INDEX, targetItem | (__LINE__<<16), true);
      return;
    }
  }
  // on success we send a notification
  bool success = false;
  // everything looks good, proceed
  switch(hardwareType){
    case BMC_ITEM_ID_PAGE:
#if BMC_MAX_PAGES > 1
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStorePage x = store.pages[sourcePage];
        store.pages[targetPage] = x;
        savePagesAndReloadData(targetPage);
        success = true;
      } else {
        bmcStorePage source = store.pages[sourcePage];
        bmcStorePage target = store.pages[targetPage];
        store.pages[sourcePage] = target;
        store.pages[targetPage] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }

#endif
      break;
    case BMC_ITEM_ID_BUTTON:
#if BMC_MAX_BUTTONS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreButton x = store.pages[sourcePage].buttons[sourceItem];
        store.pages[targetPage].buttons[targetItem] = x;
        savePagesAndReloadData(targetPage);
        success = true;
      } else {
        bmcStoreButton source = store.pages[sourcePage].buttons[sourceItem];
        bmcStoreButton target = store.pages[targetPage].buttons[targetItem];
        store.pages[sourcePage].buttons[sourceItem] = target;
        store.pages[targetPage].buttons[targetItem] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_LED:
#if BMC_MAX_LEDS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreLed x = store.pages[sourcePage].leds[sourceItem];
        store.pages[targetPage].leds[targetItem] = x;
        savePagesAndReloadData(targetPage);
        success = true;
      } else {
        bmcStoreLed source = store.pages[sourcePage].leds[sourceItem];
        bmcStoreLed target = store.pages[targetPage].leds[targetItem];
        store.pages[sourcePage].leds[sourceItem] = target;
        store.pages[targetPage].leds[targetItem] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_PIXEL:
#if BMC_MAX_PIXELS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreLed x = store.pages[sourcePage].pixels[sourceItem];
        store.pages[targetPage].pixels[targetItem] = x;
        savePagesAndReloadData(targetPage);
        success = true;
      } else {
        bmcStoreLed source = store.pages[sourcePage].pixels[sourceItem];
        bmcStoreLed target = store.pages[targetPage].pixels[targetItem];
        store.pages[sourcePage].pixels[sourceItem] = target;
        store.pages[targetPage].pixels[targetItem] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_RGB_PIXEL:
#if BMC_MAX_RGB_PIXELS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreRgbLed x = store.pages[sourcePage].rgbPixels[sourceItem];
        store.pages[targetPage].rgbPixels[targetItem] = x;
        savePagesAndReloadData(targetPage);
        success = true;
      } else {
        bmcStoreRgbLed source = store.pages[sourcePage].rgbPixels[sourceItem];
        bmcStoreRgbLed target = store.pages[targetPage].rgbPixels[targetItem];
        store.pages[sourcePage].rgbPixels[sourceItem] = target;
        store.pages[targetPage].rgbPixels[targetItem] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_PWM_LED:
#if BMC_MAX_PWM_LEDS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreLed x = store.pages[sourcePage].pwmLeds[sourceItem];
        store.pages[targetPage].pwmLeds[targetItem] = x;
        if(!backupActive()){
          savePagesAndReloadData(targetPage);
          success = true;
        }
      } else {
        bmcStoreLed source = store.pages[sourcePage].pwmLeds[sourceItem];
        bmcStoreLed target = store.pages[targetPage].pwmLeds[targetItem];
        store.pages[sourcePage].pwmLeds[sourceItem] = target;
        store.pages[targetPage].pwmLeds[targetItem] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_POT:
#if BMC_MAX_POTS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStorePot x = store.pages[sourcePage].pots[sourceItem];
        store.pages[targetPage].pots[targetItem] = x;
        savePagesAndReloadData(targetPage);
        success = true;
      } else {
        bmcStorePot source = store.pages[sourcePage].pots[sourceItem];
        bmcStorePot target = store.pages[targetPage].pots[targetItem];
        store.pages[sourcePage].pots[sourceItem] = target;
        store.pages[targetPage].pots[targetItem] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_ENCODER:
#if BMC_MAX_ENCODERS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreEncoder x = store.pages[sourcePage].encoders[sourceItem];
        store.pages[targetPage].encoders[targetItem] = x;
        savePagesAndReloadData(targetPage);
        success = true;
      } else {
        bmcStoreEncoder source = store.pages[sourcePage].encoders[sourceItem];
        bmcStoreEncoder target = store.pages[targetPage].encoders[targetItem];
        store.pages[sourcePage].encoders[sourceItem] = target;
        store.pages[targetPage].encoders[targetItem] = source;
        savePagesAndReloadData(sourcePage);
        savePagesAndReloadData(targetPage);
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_GLOBAL_LED:
#if BMC_MAX_GLOBAL_LEDS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreLed x = store.global.leds[sourceItem];
        store.global.leds[targetItem] = x;
        saveGlobalLed(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreLed source = store.global.leds[sourceItem];
        bmcStoreLed target = store.global.leds[targetItem];
        store.global.leds[sourceItem] = target;
        store.global.leds[targetItem] = source;
        saveGlobalLed(sourceItem);
        saveGlobalLed(targetItem);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_GLOBAL_BUTTON:
#if BMC_MAX_GLOBAL_BUTTONS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreButton x = store.global.buttons[sourceItem];
        store.global.buttons[targetItem] = x;
        saveGlobalButton(targetPage);
        reloadData();
        success = true;
      } else {
        bmcStoreButton source = store.global.buttons[sourceItem];
        bmcStoreButton target = store.global.buttons[targetItem];
        store.global.buttons[sourceItem] = target;
        store.global.buttons[targetItem] = source;
        saveGlobalButton(sourcePage);
        saveGlobalButton(targetPage);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_GLOBAL_ENCODER:
#if BMC_MAX_GLOBAL_ENCODERS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreEncoder x = store.global.encoders[sourceItem];
        store.global.encoders[targetItem] = x;
        saveGlobalEncoder(targetPage);
        reloadData();
        success = true;
      } else {
        bmcStoreEncoder source = store.global.encoders[sourceItem];
        bmcStoreEncoder target = store.global.encoders[targetItem];
        store.global.encoders[sourceItem] = target;
        store.global.encoders[targetItem] = source;
        saveGlobalEncoder(sourcePage);
        saveGlobalEncoder(targetPage);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_GLOBAL_POT:
#if BMC_MAX_GLOBAL_POTS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStorePot x = store.global.pots[sourceItem];
        store.global.pots[targetItem] = x;
        saveGlobalPot(targetPage);
        reloadData();
        success = true;
      } else {
        bmcStorePot source = store.global.pots[sourceItem];
        bmcStorePot target = store.global.pots[targetItem];
        store.global.pots[sourceItem] = target;
        store.global.pots[targetItem] = source;
        saveGlobalPot(sourcePage);
        saveGlobalPot(targetPage);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_STRING_LIBRARY:
#if BMC_MAX_STRING_LIBRARY > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreGlobalStringLibrary x = store.global.stringLibrary[sourceItem];
        store.global.stringLibrary[targetItem] = x;
        saveStringLibrary(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreGlobalStringLibrary source = store.global.stringLibrary[sourceItem];
        bmcStoreGlobalStringLibrary target = store.global.stringLibrary[targetItem];
        store.global.stringLibrary[sourceItem] = target;
        store.global.stringLibrary[targetItem] = source;
        saveStringLibrary(sourceItem);
        saveStringLibrary(targetItem);
        reloadData();
        success = true;
      }
#endif
    break;
    case BMC_ITEM_ID_LIBRARY:
#if BMC_MAX_LIBRARY > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreGlobalLibrary x = store.global.library[sourceItem];
        store.global.library[targetItem] = x;
        saveLibrary(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreGlobalLibrary source = store.global.library[sourceItem];
        bmcStoreGlobalLibrary target = store.global.library[targetItem];
        store.global.library[sourceItem] = target;
        store.global.library[targetItem] = source;
        saveLibrary(sourceItem);
        saveLibrary(targetItem);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_PRESET:
#if BMC_MAX_PRESETS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreGlobalPresets x = store.global.presets[sourceItem];
        store.global.presets[targetItem] = x;
        savePreset(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreGlobalPresets source = store.global.presets[sourceItem];
        bmcStoreGlobalPresets target = store.global.presets[targetItem];
        store.global.presets[sourceItem] = target;
        store.global.presets[targetItem] = source;
        savePreset(sourceItem);
        savePreset(targetItem);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_SETLIST:
#if BMC_MAX_SETLISTS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreGlobalSetList x = store.global.setLists[sourceItem];
        store.global.setLists[targetItem] = x;
        saveSetList(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreGlobalSetList source = store.global.setLists[sourceItem];
        bmcStoreGlobalSetList target = store.global.setLists[targetItem];
        store.global.setLists[sourceItem] = target;
        store.global.setLists[targetItem] = source;
        saveSetList(sourceItem);
        saveSetList(targetItem);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_CUSTOM_SYSEX:
#if BMC_MAX_CUSTOM_SYSEX > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreGlobalCustomSysEx x = store.global.customSysEx[sourceItem];
        store.global.customSysEx[targetItem] = x;
        saveCustomSysEx(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreGlobalCustomSysEx source = store.global.customSysEx[sourceItem];
        bmcStoreGlobalCustomSysEx target = store.global.customSysEx[targetItem];
        store.global.customSysEx[sourceItem] = target;
        store.global.customSysEx[targetItem] = source;
        saveCustomSysEx(sourceItem);
        saveCustomSysEx(targetItem);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_TRIGGER:
#if BMC_MAX_TRIGGERS > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreGlobalTriggers x = store.global.triggers[sourceItem];
        store.global.triggers[targetItem] = x;
        saveTrigger(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreGlobalTriggers source = store.global.triggers[sourceItem];
        bmcStoreGlobalTriggers target = store.global.triggers[targetItem];
        store.global.triggers[sourceItem] = target;
        store.global.triggers[targetItem] = source;
        saveTrigger(sourceItem);
        saveTrigger(targetItem);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_TEMPO_TO_TAP:
#if BMC_MAX_TEMPO_TO_TAP > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        bmcStoreGlobalTempoToTap x = store.global.tempoToTap[sourceItem];
        store.global.tempoToTap[targetItem] = x;
        saveTempoToTap(targetItem);
        reloadData();
        success = true;
      } else {
        bmcStoreGlobalTempoToTap source = store.global.tempoToTap[sourceItem];
        bmcStoreGlobalTempoToTap target = store.global.tempoToTap[targetItem];
        store.global.tempoToTap[sourceItem] = target;
        store.global.tempoToTap[targetItem] = source;
        saveTempoToTap(sourceItem);
        saveTempoToTap(targetItem);
        reloadData();
        success = true;
      }
#endif
      break;
    case BMC_ITEM_ID_SKETCH_BYTES:
#if BMC_MAX_SKETCH_BYTES > 0
      if(mode==BMC_PAGEF_HARDWARE_COPY){
        uint8_t x = store.global.sketchBytes[sourceItem];
        store.global.sketchBytes[targetItem] = x;
        saveSketchBytes();
        reloadData();
        success = true;
      } else {
        uint8_t source = store.global.sketchBytes[sourceItem];
        uint8_t target = store.global.sketchBytes[targetItem];
        store.global.sketchBytes[sourceItem] = target;
        store.global.sketchBytes[targetItem] = source;
        saveSketchBytes();
        reloadData();
        success = true;
      }
#endif
      break;
  }
  if(success){
    BMCMidiMessage buff;
    buff.prepareEditorMessage(port, deviceId, mode, 0, 0);
    buff.appendToSysEx7Bits(1);
    sendToEditor(buff);
  } else {
    if(mode==BMC_PAGEF_HARDWARE_COPY){
      sendNotification(BMC_NOTIFY_INVALID_COPY_REQUEST, __LINE__, true);
    } else {
      sendNotification(BMC_NOTIFY_INVALID_SWAP_REQUEST, __LINE__, true);
    }
  }
}
