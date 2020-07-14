/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  A future editor that would allow you to build an editor within your teensy using
  any display.

  This is a far future addition for BMC
*/
#ifndef __BMC_EDITORONDEVICE__
#define __BMC_EDITORONDEVICE__

#include "BMC.h"


class BMCEditorOnDevice {
public:
  /*
    BMC-Editor.cpp
  */
  BMCEditorOnDevice(BMC& t_bmc);
  void begin();

private:
  // Reference to the store from BMC.h
  BMC& bmc;
};
#endif
