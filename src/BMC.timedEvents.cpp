/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_TIMED_EVENTS > 0
  void BMC::readTimedEvent(){
    if(timedEvents.available()==0){
      return;
    }
    for(uint8_t index = 0, n=timedEvents.available(); index < n; index++){
      if(timedEvents.isReady(index)){
        //processTimedEvent(index);
      }
    }
  }
#endif
