/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2022 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef BMC_ILI_SELECTOR_H
#define BMC_ILI_SELECTOR_H

#if defined(BMC_USE_ON_BOARD_EDITOR)

#include "utility/BMC-Def.h"
#include "display/BMC-Display.h"
#include "editor/onBoard/BMC-OBEDef.h"

class BMCIliSelector {
public:
  BMCIliSelector(BMCGlobals& t_globals, BMCSettings& t_settings, BMCEditor& t_editor, BMCDisplay& t_display):
                  globals(t_globals),
                  store(globals.store),
                  settings(t_settings),
                  editor(t_editor),
                  display(t_display),
                  tft(t_display.tft){

  }
  void begin(){
    
  }
  void update(){
    
  }
  void render(){
    
  }
  // @queue is used for encoders to avoid the values being unstable
  void menuCommand(uint8_t cmd, bool queue=false){
    // c
    if(
      cmd==BMC_MENU_TOGGLE_LAYERS ||
      cmd==BMC_MENU_TOGGLE_PRESETS ||
      cmd==BMC_MENU_TOGGLE_SETLISTS ||
      cmd==BMC_MENU_TOGGLE_SONGS
    ){
      isActive = !isActive;
      if(active()){
        selectorType = cmd;
        enterSelector();
      } else {
        selectorType = 0;
        exitSelector();
      }
      return;
    } else if(!active()){
      return;
    }
    switch(cmd){
      case BMC_MENU_SELECT:
        BMC_PRINTLN("");
        break;
      case BMC_MENU_BACK:
        
        break;
      case BMC_MENU_PREV:
        
        break;
      case BMC_MENU_NEXT:
        
        break;
      default:
        break;
    }
  }
  bool active(){
    return isActive;
  }
private:
  // Reference to the store from BMC.h
  BMCGlobals& globals;
  bmcStore& store;
  BMCSettings& settings;
  BMCEditor& editor;
  BMCDisplay& display;
  BMC_ILI9341& tft;
  // all variables live here
  bool isActive = false;
  uint8_t selectorType = false;

  BMCFlags <uint8_t> flags;

  void enterSelector(){
    isActive = true;
    tft.display.setFont(BMC_OBE_ROW_FONT);
    tft.display.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
    render();
  }
  void exitSelector(){
    isActive = false;
    tft.display.setFontAdafruit();
    tft.display.fillRect(0, 0, BMC_OBE_W, BMC_OBE_H, BMC_ILI9341_BLACK);
    display.reassign(globals.layer);
  }

};
#endif
#endif