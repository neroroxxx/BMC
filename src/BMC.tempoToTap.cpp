/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2023 RoxXxtar.com 
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_TEMPO_TO_TAP > 0
  void BMC::runTempoToTap(){
    tempoToTap.update();
    if(!tempoToTap.isAllowed()){
      return;
    }
    for(uint8_t index = 0, n=tempoToTap.available(); index < n; index++){
      if(tempoToTap.isReady(index)){
        bmcStoreDevice <1, 1>& device = store.global.tempoToTap[index];
        processEvent(BMC_DEVICE_GROUP_BUTTON,
                      BMC_DEVICE_ID_TEMPO_TO_TAP,
                      index,
                      device.events[0]
                    );
      }
    }
  }
#endif
