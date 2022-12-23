/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>
void BMC::reloadPage(){
  setPage(page, true, true);
}
void BMC::setPage(uint8_t t_page, bool reassignSettings, bool forced){
  if(t_page >= BMC_MAX_PAGES && !forced){
    return;
  }
  if(page!=t_page && !forced){
    flags.write(BMC_FLAGS_PAGE_CHANGED, true);
    bmcStoreName e = globals.getDeviceName(store.pages[page].name);
    streamToSketch(BMC_DEVICE_ID_PAGE, t_page, e.name);
  }
  page = t_page;

  BMC_PRINTLN("Switching to Page #",page+1,"(",page,")");

  editor.setPage(page);
  editor.pageSendChangeMessage();

  if(reassignSettings){
    assignSettings();
  }

  #if defined(BMC_HAS_HARDWARE)
    assignHardware();
  #endif

  #if defined(BMC_HAS_DISPLAY)
    display.reassign();
  #endif

  #if defined(BMC_USE_BEATBUDDY)
    sync.beatBuddy.reassign();
  #endif

  if(callback.pageChanged){
    callback.pageChanged(page);
  }
  if(flags.read(BMC_FLAGS_PAGE_CHANGED) && editor.connected()){
    editor.triggerStates();
  }
};
bool BMC::pageChanged(){
  return flags.toggleIfTrue(BMC_FLAGS_PAGE_CHANGED);
}
bool BMC::pageChangedPeek(){
  return flags.read(BMC_FLAGS_PAGE_CHANGED);
}
uint8_t BMC::getPage(){
  return page;
}
void BMC::nextPage(){
  BMCScroller <uint8_t> scroller(0, BMC_MAX_PAGES-1);
  setPage(scroller.scroll(1, true, true, page, 0, BMC_MAX_PAGES-1));
}
void BMC::prevPage(){
  BMCScroller <uint8_t> scroller(0, BMC_MAX_PAGES-1);
  setPage(scroller.scroll(1, false, true, page, 0, BMC_MAX_PAGES-1));
}
void BMC::scrollPage(bool t_dir, bool t_endless, uint8_t t_amount){
  scrollPage(t_dir, t_endless, 0, BMC_MAX_PAGES-1, t_amount);
}

void BMC::scrollPage(uint8_t t_settings, uint8_t t_amount){
  scrollPage((bitRead(t_amount,7)),bitRead(t_settings,2), 0, BMC_MAX_PAGES-1, t_amount & 0x7F);
}
void BMC::scrollPage(uint8_t t_flags, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  // t_flags bit-0 = direction
  // t_flags bit-1 = endless
  scrollPage((bitRead(t_flags,0)),bitRead(t_flags,1),t_min,t_max,t_amount);
}
void BMC::scrollPage(bool t_dir, bool t_endless, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  BMCScroller <uint8_t> scroller(0, BMC_MAX_PAGES-1);
  setPage(scroller.scroll(t_amount, t_dir, t_endless, page, t_min, t_max));
}
