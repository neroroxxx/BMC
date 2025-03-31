/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2025 Roxxxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.


  #define EXP_1           14  // Expression Pedal 1
  #define EXP_EN_VCC_1    3   //enable pin for Expression 1
  #define EXP_EN_1        2   //enable pin for Expression 1

  #define EXP_2           15  // Expression Pedal 2
  #define EXP_EN_VCC_2    17  //enable pin for Expression 1
  #define EXP_EN_2        16  //enable pin for Expression 2

  #define PIXELS_PIN      8   // pixels data pin
  #define PIXELS_NUM      2

  #define RELAY_PIN       0   // Bypass Relay
  #define LDR_PIN         1   // WAH Controller

  #define DISPLAY_DC_PIN  9   // Data/Command pin for display
  #define DISPLAY_CS_PIN  10  // Chip Select pin for display

  #define MUX_CLK         4   // 74HC165
  #define MUX_LD          5   // 74HC165
  #define MUX_OUT         6   // 74HC165

  // MUX PINS
  #define BTN_1           1 // Menu button 1 (MUX PIN)
  #define BTN_2           2 // Menu button 2 (MUX PIN)
  #define BTN_3           3 // Menu button 3 (MUX PIN)
  #define BTN_4           4 // Menu button 4 (MUX PIN)
  #define FS_1            0 // Footswitch 1 (MUX PIN)
  #define FS_2            5 // Footswitch 2 (MUX PIN)


  // 4 settings bytes
  struct WahSettings {
    uint8_t channel     = 1;
    uint8_t ccBypass    = 0;
    uint8_t ccSweep     = 1;
    uint8_t ccTap       = 2;

    uint8_t fs[2]       = {0, 1};
    uint8_t led[2]      = {0, 0};
  };

  // 5 bytes per preset
  struct WahPreset {
    char name[13]           = "";
    
    uint8_t source          = 0;
    uint8_t mode            = MODE_EXP;
    uint8_t bypassSpeed     = 5;
    uint8_t bypassThresh    = 5;
    bool autoEngage         = false;
    bool autoExpSwitch      = false;
    uint8_t fixed           = 64;
    
    uint16_t lfoSpeed       = 250;
  };
*/
#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();
}

void loop(){
  bmc.update();
}
