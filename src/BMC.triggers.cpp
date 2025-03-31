/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#include <BMC.h>

#if BMC_MAX_TRIGGERS > 0
  void BMC::readTrigger(){
    if(!triggers.isAllowed()){
      return;
    }
    for(uint8_t index = 0, n=triggers.available(); index < n; index++){
      if(triggers.isValidTrigger(index)){
        bmcStoreDevice <1, 2>& device = store.global.triggers[index];
        processEvent(BMC_DEVICE_GROUP_BUTTON,
                      BMC_DEVICE_ID_TRIGGER,
                      index,
                      device.events[1]
                    );
      }
    }
  }
#endif
