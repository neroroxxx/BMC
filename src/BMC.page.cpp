/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

void BMC::setPage(uint8_t page, bool reassignSettings){
  if(page >= BMC_MAX_PAGES){
    return;
  }
  if(this->page!=page){
    flags.write(BMC_FLAGS_PAGE_CHANGED, true);
    #if BMC_NAME_LEN_PAGES > 1
      streamToSketch(BMC_ITEM_ID_PAGE, page, store.pages[page].name);
    #endif
  }
  this->page = page;

  BMC_PRINTLN("Switching to Page #",page+1,"(",page,")");

  editor.setPage(page);
  editor.pageSendChangeMessage();

  #if BMC_MAX_LEDS > 0
    ledStates = ~ledStates;
  #endif

  #if BMC_MAX_PWM_LEDS > 0
    pwmLedStates = ~pwmLedStates;
  #endif

  #if BMC_MAX_POTS > 0

  #endif

  if(reassignSettings){
    assignSettings();
  }

  #if defined(BMC_HAS_HARDWARE)
    assignHardware();
  #endif

  #if defined(BMC_USE_BEATBUDDY)
    beatBuddy.reassign();
  #endif

  if(callback.pageChanged){
    callback.pageChanged(page);
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
void BMC::scrollPage(uint8_t t_flags, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  // t_flags bit-0 = direction
  // t_flags bit-1 = endless
  scrollPage((bitRead(t_flags,0)),bitRead(t_flags,1),t_min,t_max,t_amount);
}
void BMC::scrollPage(bool t_dir, bool t_endless, uint8_t t_min, uint8_t t_max, uint8_t t_amount){
  BMCScroller <uint8_t> scroller(0, BMC_MAX_PAGES-1);
  setPage(scroller.scroll(t_amount, t_dir, t_endless, page, t_min, t_max));
}
