/*
  * See https://www.roxxxtar.com/bmc for more details
  * Copyright (c) 2015 - 2025 Roxxxtar.com
  * Licensed under the MIT license.
  * See LICENSE file in the project root for full license information.
*/
// This class handles both Pixels and RGB Pixels and they are fed fom the same data pin
// If you are using both Pixels and RGB Pixels then BMC will address
// Pixels first then RGB Pixels.
// For example: Pixel#1, Pixel#2, Pixel#3, RgbPixel#1, RgbPixel#2, RgbPixel#3
// If you're only using one type then just chain as usual
// The current state and color of each pixel is stored in currentColor[n]
// It's 8-bits and it holds the BMC color not and RGB value, there are 15 BMC Colors
// so only 4 bits of that byte are used, then the 8th bit represents weather the
// Pixel is ON or OFF, obviously if that bit is 1 then the Pixel is ON otherwise OFF
// BMC also allows you to rearrange the order of Pixels, that is Pixel #1 can
// positioned last in the chain or anywhere in the chain for that matter. The
// same goes for RGB Pixels.

// RGB Pixels behave different, Red, Green & Blue are all addressed independently.
// Each color has it's own event, so their color is based on which event is true.

#if !defined(BMC_PIXELS_H)
#define BMC_PIXELS_H

#include "utility/BMC-Def.h"

#if BMC_TOTAL_PIXELS > 0 && defined(BMC_PIXELS_PIN)

// RGB Pixels do not use the rainbow effect
// only enable rainbow effects if either pixels, global pixels or pixel strip
// are compiled
#if BMC_MAX_PIXELS > 0 || BMC_MAX_GLOBAL_PIXELS > 0 || BMC_MAX_PIXEL_STRIP > 0
  #define BMC_PIXELS_ENABLE_RAINBOW
#endif

// #include <WS2812Serial.h>
#include <FastLED.h>

#define BMC_PIXELS_FLAG_SHOW 0
#define BMC_PIXELS_FLAG_USE_DIM 1
#define BMC_PIXELS_FLAG_RAINBOW_CHANGED 2
#define BMC_PIXELS_FLAG_RAINBOW_FADE_CHANGED 3
// --------------------------------------
#define BMC_PIXELS_RAINBOW_AMOUNT 8

// Default Data Trasmition order is RGB, most WS2812 however are GRB
// I made this the default since the first NeoPixels I tried were the 5mm diffused
// NeoPixels which are RGB
#if !defined(WS2812_RGB)
  #define WS2812_RGB      RGB
  #define WS2812_RBG      RBG 
  #define WS2812_GRB      GRB
  #define WS2812_GBR      GBR
  #define WS2812_BRG      BRG
  #define WS2812_BGR      BGR
#endif

#if !defined(BMC_PIXELS_RGB_MODE)
  #define BMC_PIXELS_RGB_MODE RGB
#endif

// BMC_PIXEL_MAX_BRIGHTNESS must be higher than BMC_PIXEL_DIM_BRIGHTNESS
// #if BMC_PIXEL_DIM_BRIGHTNESS >= BMC_PIXEL_MAX_BRIGHTNESS
//   #error "BMC_PIXEL_DIM_BRIGHTNESS must be a lower value than BMC_PIXEL_MAX_BRIGHTNESS"
// #endif

// The value of the dimmed color (or brightness) is stored by an array "dimColors",
// this is an 8-bit unsigned, each element of the array stores 2 dim values.
// the first element's four least significant bits hold the dim value for the first pixel
// the four most significant bits hold the dim value for the second pixel,
// the second element's four least significant bits hold the dim value for
// the third pixel and so on.
// this define determines how many elements that array should have
#define BMC_TOTAL_DIM_COLORS (BMC_IS_EVEN(BMC_TOTAL_PIXELS)?(BMC_TOTAL_PIXELS/2):((BMC_TOTAL_PIXELS/2)+1))

class BMCPixels {
public:
  BMCPixels(BMCGlobals& t_globals):globals(t_globals){
    

#if defined(BMC_PIXELS_ENABLE_PIN)
  #if !defined(BMC_PIXELS_ENABLE_PIN_MODE)
    #define BMC_PIXELS_ENABLE_PIN_MODE 0
  #endif
    // If your pixels turn on by default when they are first powered up
    // you can setup a pin to go HIGH when BMC starts, this pin can then be
    // connected to a MOSFET or Relay, this circuit can then turn on the power
    // line to the pixels, you should also put a large capacitor between
    // the 5V and GND lines right before feeding the pixles, a 1000uF capacitor
    // is usually recommended tho if you are not using a lot of pixels you could
    // use a smaller capacitor, I usually use 220uF capacitors for BMC
    // builds with a few pixels. The 250ms delay should give the capacitor some time
    // to charge up to help keep the LEDs from turning on.
    delay(250);
    pinMode(BMC_PIXELS_ENABLE_PIN, OUTPUT);
    digitalWrite(BMC_PIXELS_ENABLE_PIN, ((BMC_PIXELS_ENABLE_PIN_MODE==0)?LOW:HIGH));
    delay(1);
    
#endif

    reset(false);
    delay(50);
  }
  void begin(){
    BMC_PRINTLN("BMCPixels::begin() FastLED");
    BMC_PRINTLN(" - BMC_PIXELS_MAX_CURRENT    :", BMC_PIXELS_MAX_CURRENT);
    BMC_PRINTLN(" - BMC_PIXELS_DIM_BRIGHTNESS :", BMC_PIXELS_DIM_BRIGHTNESS);
    BMC_PRINTLN(" - BMC_MAX_PIXELS            :", BMC_MAX_PIXELS);
    BMC_PRINTLN(" - BMC_MAX_GLOBAL_PIXELS     :", BMC_MAX_GLOBAL_PIXELS);
    BMC_PRINTLN(" - BMC_MAX_RGB_PIXELS        :", BMC_MAX_RGB_PIXELS);
    BMC_PRINTLN(" - BMC_MAX_GLOBAL_RGB_PIXELS :", BMC_MAX_GLOBAL_RGB_PIXELS);
    BMC_PRINTLN(" - BMC_MAX_PIXEL_STRIP       :", BMC_MAX_PIXEL_STRIP);
    
    
    FastLED.addLeds<WS2812, BMC_PIXELS_PIN, BMC_PIXELS_RGB_MODE>(pixels, BMC_TOTAL_PIXELS);
    // Set the maximum power limit to 5V and the value set by BMC_PIXELS_MAX_CURRENT
    FastLED.setMaxPowerInVoltsAndMilliamps(5, BMC_PIXELS_MAX_CURRENT);
    FastLED.show();

#if defined(BMC_PIXELS_ENABLE_RAINBOW)
    rainbowCurrentColor = BMC_COLOR_RED;
    rainbowTimeout = 0;
    rainbowFadeTimeout = 0;
#endif

#if BMC_MAX_PIXELS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_PIXELS; i++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_PIXEL, i);
      setDimColor(i, ui.style);
      #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
        test(BMC_DEVICE_ID_PIXEL, i, true);
      #endif
    }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
    for(uint8_t i = 0, n = getGlobalPixelIndex(0) ; i < BMC_MAX_GLOBAL_PIXELS; i++, n++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_PIXEL, i);
      setDimColor(n, ui.style);
      #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
        test(BMC_DEVICE_ID_GLOBAL_PIXEL, i, true);
      #endif
    }
#endif

#if BMC_MAX_RGB_PIXELS > 0
    for(uint8_t i = 0, n = getRgbPixelIndex(0) ; i<BMC_MAX_RGB_PIXELS; i++, n++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_RGB_PIXEL, i);
      setDimColor(n, ui.style);
      #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
        test(BMC_DEVICE_ID_RGB_PIXEL, i, true);
      #endif
    }
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    for(uint8_t i = 0, n = getGlobalRgbPixelIndex(0); i<BMC_MAX_GLOBAL_RGB_PIXELS; i++, n++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_RGB_PIXEL, i);
      setDimColor(n, ui.style);
      #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
        test(BMC_DEVICE_ID_GLOBAL_RGB_PIXEL, i, true);
      #endif
    }
#endif

#if BMC_MAX_PIXEL_STRIP > 0
    for(uint8_t i = 0, n = getPixelStripIndex(0); i < 1; i++, n++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_PIXEL_STRIP, i);
      setDimColor(n, ui.style);
      #if !defined(BMC_NO_LED_TEST_AT_LAUNCH)
        test(BMC_DEVICE_ID_PIXEL_STRIP, i, true);
      #endif
    }
#endif

    BMC_PRINTLN("");
  }
  // * since BMC uses the FastLED.setMaxPowerInVoltsAndMilliamps function
  // * instead of setting the max brightness of the pixels using FastLED.setBrightness
  // * we will scale the max current macro BMC_PIXELS_MAX_CURRENT to from 25% to 100%
  // * in 25% increments.
  void setBrightness(uint8_t value){
    if(value < 4){
      uint16_t max = BMC_PIXELS_MAX_CURRENT;
      switch(value){
        case 0: 
          max = uint16_t (BMC_PIXELS_MAX_CURRENT * 0.25f);
          break;
        case 1: 
          max = uint16_t (BMC_PIXELS_MAX_CURRENT * 0.5f);
          break;
        case 2: 
          max = uint16_t (BMC_PIXELS_MAX_CURRENT * 0.75f);
          break;
      }
      // BMC_PRINTLN("set Pixels brightness", max, "of ", BMC_PIXELS_MAX_CURRENT);
      FastLED.setMaxPowerInVoltsAndMilliamps(5, (uint16_t) max);
      FastLED.show();
    }
  }

  void clockBeat(uint16_t speed){
#if defined(BMC_PIXELS_ENABLE_RAINBOW)
    if(speed == 0){
      speed = 120;
    }
    updateRainbowColor(60000 / speed);
    updateRainbowFadeColor(15000 / speed);
#else
    speed = 0;
#endif
  }

  // *****************************************************************************
  // *            Reassign by resetting all Pixels and Turning them off           
  // *****************************************************************************
  void reassign(){
#if BMC_MAX_PIXELS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_PIXELS ; i++){
      off(getPixelIndex(i));
    }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_GLOBAL_PIXELS ; i++){
      off(getGlobalPixelIndex(i));
    }
#endif

#if BMC_MAX_RGB_PIXELS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_RGB_PIXELS ; i++){
      off(getRgbPixelIndex(i));
    }
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    for(uint8_t i = 0 ; i < BMC_MAX_GLOBAL_RGB_PIXELS ; i++){
      off(getGlobalRgbPixelIndex(i));
    }
#endif

#if BMC_MAX_PIXEL_STRIP > 0
    off(getPixelStripIndex(0));
#endif

    reset();
  }

  // *****************************************************************************
  // *                         Get the Index of the pixels                        
  // *      Each pixel type occupies a different area of the pixels array     
  // *   Pixels > RGB Pixels > Global Pixels > Global RGB Pixels > Pixel Strips  
  // *   In other words Pixels start at index 0 all the way to BMC_MAX_PIXELS-1  
  // *      RGB Pixels start at index BMC_MAX_PIXELS to BMC_MAX_RGB_PIXELS-1     
  // *                                    etc.                                   
  // *****************************************************************************

  uint16_t getPixelIndex(uint16_t n){
    return n;
  }
  uint16_t getGlobalPixelIndex(uint16_t n){
    return BMC_MAX_PIXELS + n;
  }
  uint16_t getRgbPixelIndex(uint16_t n){
    return (BMC_MAX_PIXELS + BMC_MAX_GLOBAL_PIXELS) + n;
  }
  uint16_t getGlobalRgbPixelIndex(uint16_t n){
    return (BMC_MAX_PIXELS + BMC_MAX_GLOBAL_PIXELS+BMC_MAX_RGB_PIXELS) + n;
  }
  uint16_t getPixelStripIndex(uint16_t n){
    return (BMC_MAX_PIXELS + BMC_MAX_GLOBAL_PIXELS + BMC_MAX_RGB_PIXELS + BMC_MAX_GLOBAL_RGB_PIXELS) + n;
  }

  // *****************************************************************************
  // *                       Test Pixels, blinks each pixel.                      
  // *****************************************************************************

  void test(uint8_t deviceType, uint16_t n, bool t_init=false){
    if(deviceType == BMC_DEVICE_ID_PIXEL){
      #if BMC_MAX_PIXELS > 0
        _test(getPixelIndex(n), false, t_init);
      #endif

    } else if(deviceType == BMC_DEVICE_ID_GLOBAL_PIXEL){
      #if BMC_MAX_GLOBAL_PIXELS > 0
        _test(getGlobalPixelIndex(n), false, t_init);
      #endif

    } else if(deviceType == BMC_DEVICE_ID_RGB_PIXEL){
      #if BMC_MAX_RGB_PIXELS > 0
        _test(getRgbPixelIndex(n), false, t_init);
      #endif

    } else if(deviceType == BMC_DEVICE_ID_GLOBAL_RGB_PIXEL){
      #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
        _test(getGlobalRgbPixelIndex(n), false, t_init);
      #endif

    } else if(deviceType == BMC_DEVICE_ID_PIXEL_STRIP){
      #if BMC_MAX_PIXEL_STRIP > 0
        _test(getPixelStripIndex(0), true, t_init);
      #endif

    }
  }

  void _test(uint16_t n, bool strip=false, bool t_init=false){
    if(n >= BMC_TOTAL_PIXELS){
      return;
    }
    
    for(uint8_t i = 0, m = (t_init ? 2 : 4) ; i < m ; i++){
      setPixelValue(n, BMCPixelColors::getHSVColor(i+1));
      FastLED.show();
      delay(BMC_MAX_LED_TEST_DELAY);

      setPixelValue(n, 0);
      FastLED.show();
      delay(BMC_MAX_LED_TEST_DELAY);
    }

    // * return pixel to original state
    uint8_t prev = currentColor[n];
    if(bitRead(prev, 7)){
      setPixelValue(n, BMCPixelColors::getHSVColor(prev));
    } else {
      turnPixelOff(n);
    }
    FastLED.show();
    delay(5);
  }

  // * store dim colors in an array of uint8_t, each pixel uses 4 bits
  // * the 4 least significant bits are the first pixel, the 4 most significant
  // * are the next pixel, then the next element of the array the same and so on
  // * this function is used when the pixel is assigned so that dim color is
  // * always ready to be used.
  void setDimColor(uint16_t n, uint8_t color){
    color &= 0x0F;

    if(color == 0){
      // * if the dimmed color is 0/black use default color
      color = getDefaultColor(n);

#if defined(BMC_PIXELS_ENABLE_RAINBOW)
    } else if(color == BMC_COLOR_RAINBOW){
      // * only Pixels (not RGB) use rainbow
      color = rainbowCurrentColor;
    } else if(color == BMC_COLOR_RAINBOW_FADE){
      // * only Pixels (not RGB) use rainbow
      color = rainbowFadeCurrentColor;
#endif

    }

    uint16_t offset = (uint16_t) ((n>0) ? (n/2) : 0);
    if(offset > BMC_TOTAL_DIM_COLORS){
      return;
    }

    uint8_t tmp = dimColors[offset];
    if(BMC_IS_EVEN(n)){
      tmp &= 0xF0;
      tmp |= (color&0x0F);
    } else {
      tmp &= 0x0F;
      tmp |= (color<<4);
    }
    dimColors[offset] = tmp;
  }

  void update(){
#if BMC_MAX_PIXELS > 0
    for(uint8_t i = 0; i < BMC_MAX_PIXELS; i++){
      if(pulseTimer[i].complete()){
        off(getPixelIndex(i));
      }
    }
#endif
#if BMC_MAX_GLOBAL_PIXELS > 0
    for(uint8_t i = 0, n = getGlobalPixelIndex(0); i < BMC_MAX_GLOBAL_PIXELS; i++, n++){
      if(pulseTimer[n].complete()){
        off(getGlobalPixelIndex(i));
      }
    }
#endif
#if BMC_MAX_RGB_PIXELS > 0
    for(uint8_t i = 0, n = getRgbPixelIndex(0); i < BMC_MAX_RGB_PIXELS; i++, n++){
      if(pulseTimer[n].complete()){
        // * restore the pulsed led
        // * since RGB pixels can have each of the 3 colors controller separately
        // * we have to only turn off the color that was pulsed, the color being
        // * pulse is stored by rgbPulseReset so we XOR it agains the current color
        // * in case any of the other 2 colors have an event and are being turned
        // * on by something else.
        write(n, ( (currentColor[n] & 7) ^ rgbPulseReset[i] ));

        // * reset pulse the color
        rgbPulseReset[i] = 0;
      }
    }
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    for(uint8_t i = 0, n = getGlobalRgbPixelIndex(0); i < BMC_MAX_GLOBAL_RGB_PIXELS; i++, n++){
      if(pulseTimer[n].complete()){
        // * restore the pulsed led
        // * since RGB pixels can have each of the 3 colors controller separately
        // * we have to only turn off the color that was pulsed, the color being
        // * pulse is stored by rgbPulseReset so we XOR it agains the current color
        // * in case any of the other 2 colors have an event and are being turned
        // * on by something else.
        write(n, ( (currentColor[n] & 7) ^ globalRgbPulseReset[i] ));

        // * reset pulse the color
        globalRgbPulseReset[i] = 0;
      }
    }
#endif

#if BMC_MAX_PIXEL_STRIP > 0
    if(pulseTimer[getPixelStripIndex(0)].complete()){
      off(getPixelStripIndex(0));
    }
#endif

    if(flags.toggleIfTrue(BMC_PIXELS_FLAG_SHOW)){
      FastLED.show();
      flags.off(BMC_PIXELS_FLAG_RAINBOW_CHANGED);
      flags.off(BMC_PIXELS_FLAG_RAINBOW_FADE_CHANGED);
    }
  }

  // * instead of calling show everytime an pixel is turned on/off
  // * we call show once per update cycle (loop) this flag
  // * if on calls the show method
  void show(){
    flags.on(BMC_PIXELS_FLAG_SHOW);
  }

  void setPwmOffValue(bool value){
    if(value != flags.read(BMC_PIXELS_FLAG_USE_DIM)){
      flags.write(BMC_PIXELS_FLAG_USE_DIM, value);
      for(uint8_t i=0;i<BMC_TOTAL_PIXELS;i++){
        if(bitRead(currentColor[i], 7)){
          // swap the on state of the led
          bitWrite(currentColor[i], 7, 0);
          on(i, currentColor[i]);
        } else {
          // swap the on state of the led
          bitWrite(currentColor[i], 7, 1);
          off(i);
        }
      }
    }
  }

#if BMC_MAX_PIXELS > 0
  void pulse(uint16_t t_index, uint8_t t_color=255){
    if(t_index < BMC_MAX_PIXELS){
      write(t_index, t_color);
      pulseTimer[t_index].start(BMC_LED_PULSE_TIMEOUT);
      return;
    }
  }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
  void setStateGlobal(uint16_t n, uint8_t t_color=255){
    n = getGlobalPixelIndex(n);
    write(n, t_color);
  }
  void pulseGlobal(uint16_t t_index, uint8_t t_color=255){
    if(t_index < BMC_MAX_GLOBAL_PIXELS){
      write(t_index, t_color);
      pulseTimer[t_index].start(BMC_LED_PULSE_TIMEOUT);
      return;
    }
  }
#endif

#if BMC_MAX_RGB_PIXELS > 0
  void setStateRgb(uint16_t n, uint8_t color, bool t_state){
    n += getRgbPixelIndex(0);
    // * get the current color of the led
    // * but don't account for for the MS bit
    uint8_t cColor = currentColor[n] & 0x07;
    bitWrite(cColor, color, t_state);
    write(n, cColor);
  }
  void pulseRgb(uint8_t t_index, uint8_t t_color){
    if(t_index>=BMC_MAX_RGB_PIXELS){
      return;
    }
    // * since RGB pixels can have each of the 3 colors controller separately
    // * we pulse them independently of the others, rgbPulseReset will hold the
    // * bit of the color being pulsed and we pulse more than 1 of the colors
    // * then we have to update the bits that are being pulsed to add any additional
    // * bits so they can be turned off by update(), we do this by ORing the values
    // * rgbPulseReset is indexed by BMC_MAX_RGB_PIXELS, so from 0 to BMC_MAX_RGB_PIXELS
    bitWrite(rgbPulseReset[t_index], t_color, 1);
    t_index += BMC_MAX_PIXELS;
    t_color = bitWrite(currentColor[t_index],t_color,1);
    write(t_index, t_color);
    pulseTimer[t_index].start(BMC_LED_PULSE_TIMEOUT);
  }
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
  void setStateGlobalRgb(uint16_t n, uint8_t color, bool t_state){
    n = getGlobalRgbPixelIndex(n);
    // get the current color of the led
    // but don't account for for the MS bit
    uint8_t cColor = currentColor[n] & 0x07;
    bitWrite(cColor, color, t_state);
    write(n, cColor);
  }
  void pulseGlobalRgb(uint8_t t_index, uint8_t t_color){
    if(t_index>=BMC_MAX_GLOBAL_RGB_PIXELS){
      return;
    }
    // since RGB pixels can have each of the 3 colors controller separately
    // we pulse them independently of the others, rgbPulseReset will hold the
    // bit of the color being pulsed and we pulse more than 1 of the colors
    // then we have to update the bits that are being pulsed to add any additional
    // bits so they can be turned off by update(), we do this by ORing the values
    // rgbPulseReset is indexed by BMC_MAX_RGB_PIXELS, so from 0 to BMC_MAX_RGB_PIXELS
    bitWrite(globalRgbPulseReset[t_index], t_color, 1);
    t_index += BMC_MAX_PIXELS;
    t_color = bitWrite(currentColor[t_index],t_color,1);
    write(t_index, t_color);
    pulseTimer[t_index].start(BMC_LED_PULSE_TIMEOUT);
  }
  // @t_input   = the value we're comparing to
  // @t_default = the value that will turn the led on either way
  // @compare   = the flags with the operator and operation value
  bool compare(uint16_t t_input, uint16_t t_default, uint8_t compare){
    // if t_input is the same as t_default return true
    if(t_input == t_default){
      return true;
    }
    // compare's bits 6 and 7 are the operator
    // compare's bits 0 to 5 are teh operator value
    switch(((compare >> 6) & 0x03)){
      case 0: // skip
        return false;
      case 1: // ==
        return (t_input == (compare & 0x3F));
      case 2: // ORing
        return (t_input  | (compare & 0x3F));
      case 3: // ANDin
        return (t_input  & (compare & 0x3F));
    }
    return false;
  }
#endif

#if BMC_MAX_PIXEL_STRIP > 0
  void setStateStrip(uint8_t t_color=255){
    write(getPixelStripIndex(0), t_color);
  }
  
  void pulseStrip(uint8_t t_color=255){
    write(getPixelStripIndex(0), t_color);
    pulseTimer[getPixelStripIndex(0)].start(BMC_LED_PULSE_TIMEOUT);
  }
#endif


  void setState(uint16_t n, uint8_t t_color=255){
    write(n, t_color);
  }
  void on(uint16_t n, uint8_t t_color=255){
    write(n, (t_color==0 ? 255 : t_color));
  }
  void off(uint16_t n, uint8_t t_color=255){
    write(n, 0);
  }
  void toggle(uint16_t n, uint8_t t_color=255){
    write(n, (getState(n)>0) ? 0 : t_color);
  }
  uint8_t getState(uint16_t n){
    return (n<BMC_TOTAL_PIXELS ? currentColor[n] : 0);
  }
#if BMC_MAX_RGB_PIXELS > 0
  uint8_t getRgbState(uint8_t n){
    return (((BMC_MAX_PIXELS+n)<BMC_MAX_RGB_PIXELS) ? currentColor[BMC_MAX_PIXELS+n] : 0);
  }
#endif

private:
  BMCGlobals& globals;
  
  CRGB pixels[BMC_TOTAL_PIXELS];

  // * this array will store the color of each pixel
  // * the most significant bit however specifies if the pixel is on (1) or off(0)
  uint8_t currentColor[BMC_TOTAL_PIXELS];

#if defined(BMC_PIXELS_ENABLE_RAINBOW)
  // * brightness, only used for pot controls as of right now
  // uint8_t currentBrightness[BMC_TOTAL_PIXELS];
#endif

  // * store the dim value for each pixel, this value is based on color that the
  // * pixel event has each byte stores 2 pixel's dim values, if your pixel has
  // * an event and it's set to green then green becomes the DIM color if you pixel
  // * doesn't have an event then dim color will be the last color that was used
  // * at startup there's no last color so then the initial color is the Pixels
  // * default colors assigned by the Config File.
  // * This is updated when pixels are reassigned
  uint8_t dimColors[BMC_TOTAL_DIM_COLORS];

  // * pulse timers, one per led
  BMCTimer pulseTimer[BMC_TOTAL_PIXELS];

#if BMC_MAX_RGB_PIXELS > 0
  uint8_t rgbPulseReset[BMC_MAX_RGB_PIXELS];
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
  uint8_t globalRgbPulseReset[BMC_MAX_GLOBAL_RGB_PIXELS];
#endif


#if defined(BMC_PIXELS_REARRANGE)
  const uint8_t pixelsSort[BMC_TOTAL_PIXELS] = BMC_PIXELS_REARRANGE;
#endif

  void setPixelValue(uint16_t n, CHSV color, bool dim = false){
    if(n >= BMC_TOTAL_PIXELS){
      return;
    }
    if(dim){
      color.value = BMC_PIXELS_DIM_BRIGHTNESS;
    }

    if(n >= getPixelStripIndex(0)){
      for(uint16_t i = n ; i < BMC_TOTAL_PIXELS ; i++){
        pixels[i] = color;
      }
    } else {
  #if defined(BMC_PIXELS_REARRANGE)
    pixels[pixelsSort[n]] = color;
  #else
    pixels[n] = color;
  #endif
    }
  }

  void setPixelValue(uint16_t n, CRGB color){
    if(n>=BMC_TOTAL_PIXELS){
      return;
    }

    if(n >= getPixelStripIndex(0)){
      for(uint16_t i = n ; i < BMC_TOTAL_PIXELS ; i++){
        pixels[i] = color;
      }
    } else {
#if defined(BMC_PIXELS_REARRANGE)
    pixels[pixelsSort[n]] = color;
#else
    pixels[n] = color;
#endif
    }
  }
  void setPixelValue(uint16_t n, uint32_t color){
    // * Extract RGB values from the 24-bit color
    uint8_t r = (color >> 16) & 0xFF;  // * Red
    uint8_t g = (color >> 8) & 0xFF;   // * Green
    uint8_t b = color & 0xFF;          // * Blue
    CRGB pixelColor = CRGB(r, g, b);
    setPixelValue(n, pixelColor);
  }

  // * flags
  BMCFlags <uint16_t> flags;
  // * uint8_t rainbowRGB[3] = {250, 0, 0};

#if defined(BMC_PIXELS_ENABLE_RAINBOW)
  // * RAINBOW
  
  // * in Rainbow mode the led uses a different color anytime you set the color
  // * the rainbowCurrentColor variable is changed only when FastLED.show() is called

  uint8_t rainbowCurrentColor = BMC_COLOR_RED;
  uint8_t rainbowFadeCurrentColor = 0;
  // * time the rainbow to be triggered after 10ms
  BMCElapsedMillis rainbowTimeout;
  BMCElapsedMillis rainbowFadeTimeout;

  void updateRainbowColor(uint16_t speed = 500){
    if(rainbowTimeout >= speed){
      if(!flags.read(BMC_PIXELS_FLAG_RAINBOW_CHANGED)){

        rainbowCurrentColor++;
        // * BMC_COLOR_RAINBOW is the highest index number
        // * once we reach it we go back to the start of the colors
        if(rainbowCurrentColor >= BMC_COLOR_RAINBOW){
          rainbowCurrentColor = BMC_COLOR_RED;
        } else if(rainbowCurrentColor == BMC_COLOR_WHITE){
          // * if it's white we skip it, that way we avoid drawing all the
          // * max led current
          rainbowCurrentColor++;
        }
        rainbowTimeout = 0;
      }
      flags.on(BMC_PIXELS_FLAG_RAINBOW_CHANGED);
    }
  }
  void updateRainbowFadeColor(uint16_t speed = 500){
    if(rainbowFadeTimeout >= speed){
      if(!flags.read(BMC_PIXELS_FLAG_RAINBOW_FADE_CHANGED)){

        rainbowFadeCurrentColor += BMC_PIXELS_RAINBOW_AMOUNT;
        rainbowFadeTimeout = 0;
      }
      flags.on(BMC_PIXELS_FLAG_RAINBOW_FADE_CHANGED);
    }
  }
#endif
  uint8_t getDimColor(uint16_t n){
    uint8_t offset = (uint16_t) ((n>0) ? (n/2) : 0);
    if(offset > BMC_TOTAL_DIM_COLORS){
      return BMC_COLOR_RED;
    }
    if(BMC_IS_EVEN(n)){
      return (dimColors[offset] & 0x0F);
    }
    return ((dimColors[offset] >> 4) & 0x0F);
  }

  void turnPixelOff(uint16_t n){
    CHSV offValue = CHSV(0, 0, 0);

    if(flags.read(BMC_PIXELS_FLAG_USE_DIM)){
      BMC_PRINTLN(n, "Pixel Dim??");
      offValue = BMCPixelColors::getHSVColor(getDimColor(n));
    }
    setPixelValue(n, offValue, flags.read(BMC_PIXELS_FLAG_USE_DIM));
  }

  void setValuesChanged(uint16_t n, bool t_state){
    if(n >= BMC_TOTAL_PIXELS){
      return;
    }
#if BMC_MAX_PIXEL_STRIP > 0
    if(n >= getPixelStripIndex(0)){
      globals.pixelStripStates.setBit(0, t_state);
      return;
    }
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    if(n >= getGlobalRgbPixelIndex(0)){
      uint8_t color = currentColor[n]&0x0F;
      n -= getGlobalRgbPixelIndex(0);
      globals.globalRgbPixelStates[0].setBit(n, bitRead(color, 0));
      globals.globalRgbPixelStates[1].setBit(n, bitRead(color, 1));
      globals.globalRgbPixelStates[2].setBit(n, bitRead(color, 2));
      return;
    }
#endif

#if BMC_MAX_RGB_PIXELS > 0
    if(n >= getRgbPixelIndex(0)){
      uint8_t color = currentColor[n]&0x0F;
      n -= getRgbPixelIndex(0);
      globals.rgbPixelStates[0].setBit(n, bitRead(color, 0));
      globals.rgbPixelStates[1].setBit(n, bitRead(color, 1));
      globals.rgbPixelStates[2].setBit(n, bitRead(color, 2));
      return;
    }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
    if(n >= getGlobalPixelIndex(0)){
      n -= getGlobalPixelIndex(0);
      globals.globalPixelStates.setBit(n, t_state);
      return;
    }
#endif

#if BMC_MAX_PIXELS > 0
    if(n >= getPixelIndex(0)){
      globals.pixelStates.setBit(n, t_state);
      return;
    }
#endif
  }

  void write(uint16_t t_index, uint8_t t_color = 255){
    if(t_index >= BMC_TOTAL_PIXELS){
      return;
    }
    // hold the current color assigned to the pixel
    uint8_t cColor = getState(t_index);
    uint8_t _t_color = t_color;

    if(t_color==255){
      // if target color is 255 we use the last assigned color
      t_color = cColor & 0x0F;

    } else if(t_color==127){
      // if target color is 127 we use default color
      t_color = getDefaultColor(t_index);

    } else if(t_color==BMC_COLOR_RAINBOW){
#if defined(BMC_PIXELS_ENABLE_RAINBOW)
       // if the target color BMC_COLOR_RAINBOW then we will go thru all colors
      //  t_color = rainbowCurrentColor;
      //  setDimColor(t_index, t_color);
#endif
    } else if(t_color==BMC_COLOR_RAINBOW_FADE){
#if defined(BMC_PIXELS_ENABLE_RAINBOW)
      // t_color = rainbowFadeCurrentColor;
      // setDimColor(t_index, rainbowCurrentColor);
#endif
    }

    // if t_color is 0, we are turning the pixel off
    if(t_color == 0){
      // if it's not already off we set it to off/black
      // we do all these checks because we have to change the states of all
      // pixels everytime one changes, so if there's no need to do that, we don't
      if(bitRead(cColor, 7)){
        turnPixelOff(t_index);
        // set bit 7 to 0
        // thats the bit that tells you if the led is on(1) or off(0)
        // we don't change the actual color just the on/off state

        #if BMC_MAX_PIXEL_STRIP > 0
          if(t_index >= getPixelStripIndex(0)){
            //currentColor[t_index] = 0;
            bitWrite(currentColor[t_index], 7, 0);
          }
        #endif

        #if BMC_MAX_GLOBAL_RGB_PIXELS > 0
          if(t_index >= getGlobalRgbPixelIndex(0)){
            //bitWrite(currentColor[t_index], 7, 0);
            currentColor[t_index] = 0;
          }
        #endif

        #if BMC_MAX_RGB_PIXELS > 0
          if(t_index >= getRgbPixelIndex(0)){
            currentColor[t_index] = 0;
          }
        #endif

        #if BMC_MAX_GLOBAL_PIXELS > 0
          if(t_index >= getGlobalPixelIndex(0)){
            //currentColor[t_index] = 0;
            bitWrite(currentColor[t_index], 7, 0);
          }
        #endif

        #if BMC_MAX_PIXELS > 0
          if(t_index >= getPixelIndex(0)){
            //currentColor[t_index] = 0;
            bitWrite(currentColor[t_index], 7, 0);
          }
        #endif

        // we specify that a value has changed for BMC to provide feedback
        // to the editor
        setValuesChanged(t_index, false);

        // show just sets a flag so on the next loop() the pixel.show()
        // method is called, this way we don't do it every time a pixel
        // color/state has changed
        show();
      }
    } else {
      // only update and refresh the leds that have rainbow if needed?
      // if(_t_color == BMC_COLOR_RAINBOW || _t_color == BMC_COLOR_RAINBOW_FADE){

      // }

      // we are setting a color aka turning the pixel ON
      // we are going to check if the pixel is OFF or if the color is different
      // than the current color, in either case we want to update the pixel
      bool isRainbow = (_t_color == BMC_COLOR_RAINBOW && flags.read(BMC_PIXELS_FLAG_RAINBOW_CHANGED)) || 
      (_t_color == BMC_COLOR_RAINBOW_FADE && flags.read(BMC_PIXELS_FLAG_RAINBOW_FADE_CHANGED));

      if(!bitRead(cColor, 7) || (cColor & 0x7F) != t_color || isRainbow){
        // if it's a rainbow fade, we want to update
        if(_t_color == BMC_COLOR_RAINBOW_FADE){
          #if defined(BMC_PIXELS_ENABLE_RAINBOW)
            CHSV rainbow = CHSV(rainbowFadeCurrentColor, 255, 255);
            setPixelValue(t_index, rainbow);
          #endif

        } else if(_t_color == BMC_COLOR_RAINBOW){
          #if defined(BMC_PIXELS_ENABLE_RAINBOW)
            setPixelValue(t_index, BMCPixelColors::getHSVColor(rainbowCurrentColor));
          #endif

        } else {
          
          setPixelValue(t_index, BMCPixelColors::getHSVColor(t_color));

        }
        // set bit 7 to 0
        // thats the bit that tells you if the led is on(1) or off(0)

        bitWrite(t_color, 7, 1);
        currentColor[t_index] = t_color;

        // we specify that a value has changed for BMC to provide feedback
        // to the editor
        setValuesChanged(t_index, true);
        // show just sets a flag so on the next loop() the pixel.show()
        // method is called, this way we don't do it every time a pixel
        // color/state has changed
        show();
      }
    }
  }
  void reset(bool showPixels=true){
    flags.reset(1 << BMC_PIXELS_FLAG_USE_DIM);

#if BMC_MAX_PIXELS > 0
    globals.pixelStates.zeroOut();
    // the default color to each LED
    for(uint8_t i=0; i< BMC_MAX_PIXELS; i++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_PIXEL, i);
      currentColor[i] = ui.style;
      pulseTimer[i].stop();
      // currentBrightness[i] = 0;
    }
#endif

#if BMC_MAX_GLOBAL_PIXELS > 0
    globals.globalPixelStates.zeroOut();
    // the default color to each LED
    for(uint8_t i = 0, n = getGlobalPixelIndex(0); i < BMC_MAX_GLOBAL_PIXELS; i++, n++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_PIXEL, i);
      currentColor[n] = ui.style;
      pulseTimer[n].stop();
      // currentBrightness[n] = 0;
    }
#endif

#if BMC_MAX_RGB_PIXELS > 0
    globals.rgbPixelStates[0].zeroOut(); // red
    globals.rgbPixelStates[1].zeroOut(); // green
    globals.rgbPixelStates[2].zeroOut(); // blue
    // the default color to each LED
    for(uint8_t i = 0, n = getRgbPixelIndex(0); i < BMC_MAX_RGB_PIXELS; i++, n++){
      pulseTimer[n].stop();
      currentColor[n] = 0;
    }
    memset(rgbPulseReset, 0, sizeof(rgbPulseReset[0])*BMC_MAX_RGB_PIXELS);
#endif

#if BMC_MAX_GLOBAL_RGB_PIXELS > 0
    globals.globalRgbPixelStates[0].zeroOut(); // red
    globals.globalRgbPixelStates[1].zeroOut(); // green
    globals.globalRgbPixelStates[2].zeroOut(); // blue
    // the default color to each LED
    for(uint8_t i = 0, n = getGlobalRgbPixelIndex(0); i < BMC_MAX_GLOBAL_RGB_PIXELS; i++, n++){
      pulseTimer[n].stop();
      currentColor[n] = 0;
    }
    memset(globalRgbPulseReset, 0, BMC_MAX_RGB_PIXELS);
#endif

#if BMC_MAX_PIXEL_STRIP > 0
    globals.pixelStripStates.zeroOut();
    // the default color to each LED
    for(uint8_t i = 0, n = getPixelStripIndex(0); i < 1; i++, n++){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_PIXEL_STRIP, i);
      currentColor[n] = ui.style;
      pulseTimer[n].stop();
      // currentBrightness[n] = 0;
    }
#endif

    if(showPixels){
      show();
    }
  }
  uint8_t getDefaultColor(uint16_t n){
    if(n >= getGlobalRgbPixelIndex(n)){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_RGB_PIXEL, n-getGlobalRgbPixelIndex(0));
      return ui.style;
    } else if(n >= getRgbPixelIndex(n)){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_RGB_PIXEL, n-getRgbPixelIndex(0));
      return ui.style;
    } else if(n >= getGlobalPixelIndex(n)){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_GLOBAL_PIXEL, n-getGlobalPixelIndex(0));
      return ui.style;
    } else if(n >= getPixelIndex(n)){
      BMCUIData ui = BMCBuildData::getUIData(BMC_DEVICE_ID_PIXEL, n);
      return ui.style;
    }
    return BMC_COLOR_RED;
  }
};

#endif

#endif
