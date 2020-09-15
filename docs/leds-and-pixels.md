*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# LEDs & Pixels

**IMPORTANT: make sure you check how much current your leds draw, a typical led draws 20mA, their draw is based on the resistor you pair with it, but keep in mind, Teensy pins have a maximum of 20mA and it's 3.3v regulator 250mA overall, so be careful with that, if you are planning on using a lot of Leds and pixels make sure you have separate power supplies or use larger sized resistors with each pin to lower the current draw. Using very bright LEDs can also be very distracting on a stage or while you are working so make sure you find the best resistor value possible to work with your leds.**

There are 5 types of LEDs handled by BMC, Page Leds, Global Leds, Pwm Leds, Pixels & RGB Pixels.

* **Page Leds** within BMC are just referred to as LEDs, Leds are assigned per page.
* **Global Leds** are obviously "global" as in they are not part of a page and their data is not updated when a page changes. This are useful as utility Leds like MIDI In/Out Activity, etc.
* **Pwm Leds** this are similar to Leds, they are part of pages however they have a *brightness* value and they require PWM capable pins. These are good if you want to use the brightness of the led as an indicator, you can assign a Pot's value to the brightness so as the pot increases value the Led increases brightness, etc.
* **Pixels** these work using WS2812/NeoPixels, they only require one pin and they behave exactly the same way as any Led, they are assigned to pages but they also have a color value. They are assigned a default color but you can choose from 14 colors, the maximum brightness of these can be set with the Config File Maker, they default to the lowest brightness possible as these can be very bright and draw A LOT of current.
The main upsides of Pixels are that they require only 1 pin and that you can change the color of the pixel.
* **RGB Pixels** these work the same as Pixels but they each have 3 events, one for Red, one for Green and one for Blue, in other words it's like having 3 Leds in 1, you could assign the Red Led to turn on when you are on program 1, the green Led when you are in program 2, and the blue when you are in program 3. Many RGB Pixel events also have a feature that allows you to OR/AND values to create a combination of colors, this is best explained by trying and using the editor app.

### LEDs
These are standard Leds, each Led can be wired to any digital pin on your Teensy with a resistor between the Teensy Pin and the Led's Anode (+) led, they have 2 states ON and OFF.

Leds have only 1 event, when that event's parameters are met the Led will turn on, if they aren't the Led turns off.

For example an Led can turn on when MIDI Program #0 on channel #1 is sent/received, if any other program is sent/received on that channel the Led will turn off.

### PWM LEDs
These work the same as LEDs with 2 differences:

1. PWM LEDs **MUST** be wired to a PWM Capable pin on your Teensy.
2. PWM LEDs have an extra brightness parameter, with this you can change how bright you want the Led to be when it's on.

### Pixels
Pixels are for use with WS2812 Addressable RGB Leds, these are pretty common and only require 1 data pin from your Teensy, they use the [WS2812Serial library](https://github.com/PaulStoffregen/WS2812Serial) from PJRC *(which comes bundled with Teensyduino)*. The data pin must be a Serial Pin.

The advantages over regular LEDs and PWM LEDs are:

1. Only 1 Teensy Pin needed (aside from power and ground)
2. You can specify the color you want it to, you can choose from 14 solid colors **PLUS** a Rainbow effect which loops thru the 14 colors every 500ms

In other words every pixel on your build can be a different color or you can set all LEDs on one page to be one color and a different color in another page, etc.

Just like LEDs and PWM LEDs, each pixel has only 1 event and 2 states ON and OFF with the adantage of being able to change the color.

### RGB Pixels
RGB Pixels are the same as Pixels but they each have 3 events, Red, Green an Blue which gives you a total of 8 states.

For example, you can set the Red Event to turn on when MIDI data has been received, and the Green Event to turn on when MIDI data has been sent, then when MIDI data has been both sent and received the Red and Green Leds of the Pixel will turn on turning the RGB Pixel Yellow.

Many events of RGB Pixels also have a "Operator" feature which uses "AND" and "OR" logic operators, these are used to turn each color on/off within a different set of parameters. Full details of this feature are provided within the Editor app when those events are selected.

### Which to use?

Choosing between the types of LEDs available is up to you but keep a few things in mind.

1. WS2812 can draw a lot more current than using a regular LED, the common types of WS2812s usually use 20mA max per Led, so the Red being on at full brightness will draw 20mA, if you also turn the Green Led at full brightness (turning the Pixel Yellow) that's another 20mA that's 40mA right there while the standard LED will draw 20mA max depending on the resistor value used.

2. Pixels only require one pin from your Teensy so if you are using other pins for buttons then Pixels might be a better choice.

3. WS2812 usually come in SMD packages unlike LEDs which come in 5mm dome packages which are easier to mount onto an enclosure. There are 5mm dome WS2812 compatible leds out there tho, you can search Adafruit's website for them.

Both Pixel are RGB Pixels are handled by the same Class in BMC and there for they will share the Dim Brightness and Max Brightness (more on this later)

### Colors
Pixels have the following colors available
* RED
* GREEN
* BLUE
* YELLOW
* MAGENTA
* LIME
* CYAN
* PINK
* PURPLE
* LIGHT BLUE
* ORANGE
* CORAL
* TEAL
* WHITE
* RAINBOW

You can change these colors by adding a define to your config.h file with a 24-bit color **RAINBOW is excluded from overloading**

The define for each color are:

* `BMC_COLOR_RGB_RED`
* `BMC_COLOR_RGB_GREEN`
* `BMC_COLOR_RGB_BLUE`
* `BMC_COLOR_RGB_YELLOW`
* `BMC_COLOR_RGB_MAGENTA`
* `BMC_COLOR_RGB_LIME`
* `BMC_COLOR_RGB_CYAN`
* `BMC_COLOR_RGB_PINK`
* `BMC_COLOR_RGB_PURPLE`
* `BMC_COLOR_RGB_LIGHT_BLUE`
* `BMC_COLOR_RGB_ORANGE`
* `BMC_COLOR_RGB_CORAL`
* `BMC_COLOR_RGB_TEAL`
* `BMC_COLOR_RGB_WHITE`
* `BMC_COLOR_RGB_RAINBOW`

These must be 24-bit, for example white would be all Leds of the Pixel on so white would be `0xFFFFFF` if you want White to be Red then you can add this to your config.h

```c++
#define BMC_COLOR_RGB_WHITE 0xFF0000
```

### Dim Brightness (Dim When Off)
You can make leds stay dimmed when they are in their off state, this is only available for Leds that are connected to PWM capable pins and Pixels/RGB Pixels. I always wire my Leds to PWM pins so that i have this option available. You do this in **SETTINGS**. You can also override the value of the PWM pins when they are off with the Config File under advanced, the default value is 1, so when the LED is off it will use analogWrite(pin, 1) a value of 1 is usually more than enough and it's not distracting. This settings applies to all leds that are connected to a PWM capable pin and to pixels.
This feature is great in dark stages to see where your footswitches are.

### Max Brightness
You can also set the maximum brightness for Leds and Pixels in the config file maker, again just like with Dim Brightness, Leds/Global Leds and PWM Leds will have one Max Brightness and Pixels and RGB Pixels will have their own.


### Pixels and RGB Pixels Chain Sorting
The config file maker also gives you the option to re-arrange the order of the Pixels in the chain.

By default BMC will put Pixels first in the chain then RGB Pixels, that is BMC will see WS2812 #0, WS2812 #1 and WS2812 #2 in the chain as Pixels #0, #1 and #2, and WS2812 #3, WS2812 #4 and WS2812 #5 as RGB Pixels #0, #1 and #2, however, you can change this order completely and make WS2812 #5 be your RGB Pixel #0, etc.

This is available so you can wire the Closest Pixel to your Teensy and BMC can treat it as if it's say Pixel #6 and so on.

### Names
LEDs and Pixels can all have names compiled, this is done with the Config File Maker and they all share the same number of characters compiled.


### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// ** PAGE LEDS **
// Get LED Data
void getLed(uint8_t t_index, bmcStoreLed& t_item);

void getLed(uint8_t t_page, uint8_t t_index, bmcStoreLed& t_item);

void getLedName(uint8_t t_index, char* t_string);

void getLedName(uint8_t t_page, uint8_t t_index, char* t_string);

// used to control leds only by the sketch, no matter what page
void setLedCustomState(uint8_t n, bool t_value);

bool getLedCustomState(uint8_t n);

uint32_t getLedStates();

// ** GLOBAL LEDS **
// get GLOBAL_LED Data
void getGlobalLed(uint8_t n, bmcStoreLed& t_item);

void getGlobalLedName(uint8_t n, char* t_string);

// used to control leds only by the sketch, no matter what page
void setGlobalLedCustomState(uint8_t n, bool t_value);

bool getGlobalLedCustomState(uint8_t n);

uint32_t getGlobalLedStates();

// ** PWM LEDS **

// get PWM_LED Data
void getPwmLed(uint8_t n, bmcStoreLed& t_item);

void getPwmLed(uint8_t t_page, uint8_t n, bmcStoreLed& t_item);

void getPwmLedName(uint8_t n, char* t_string);

void getPwmLedName(uint8_t t_page, uint8_t n, char* t_string);

// used to control pwm leds only by the sketch, no matter what page
void setPwmLedCustomState(uint8_t n, uint8_t t_value);

uint8_t getPwmLedCustomState(uint8_t n);

uint32_t getPwmLedStates();

// ** PIXELS **

// get Pixel Data
void getPixel(uint8_t n, bmcStoreLed& t_item);

void getPixel(uint8_t t_page, uint8_t n, bmcStoreLed& t_item);

void getPixelName(uint8_t n, char* t_string);

void getPixelName(uint8_t t_page, uint8_t n, char* t_string);

// used to control pixels only by the sketch, no matter what page
void setPixelCustomState(uint8_t n, uint8_t t_color, uint8_t t_brightness);

uint8_t getPixelCustomState(uint8_t n);

uint8_t getPixelCustomStateColor(uint8_t n);

uint8_t getPixelCustomStateBrightness(uint8_t n);

uint32_t getPixelStates();

// available if pixel programs compiled
// change the current pixel program
void setPixelProgram(uint8_t t_program);

// available if pixel programs compiled
// get the current pixel program
uint8_t getPixelProgram();

// ** RGB PIXELS **

// get RgbPixel Data
void getRgbPixel(uint8_t n, bmcStoreRgbLed& t_item);

void getRgbPixel(uint8_t t_page, uint8_t n, bmcStoreRgbLed& t_item);

void getRgbPixelName(uint8_t n, char* t_string);

void getRgbPixelName(uint8_t t_page, uint8_t n, char* t_string);

// used to control rgb pixels only by the sketch, no matter what page
// if the rgb pixel is set to custom this becomes it's state so your
// sketch can have full control of it
// set the specified color to on/off, valued values are
// 0 for Red, 1 for Green and 2 for Blue
void setRgbPixelCustomState(uint8_t n, uint8_t color, bool value);

uint8_t getRgbPixelCustomState(uint8_t n);

uint32_t getRgbPixelStates(uint8_t n);
```

##### CALLBACKS
```c++
// triggered when an led changes states, @states holds the state of each
// led in bits, so bit 0 of states, is LED 0, if bit 0 is not set then led is off
void onLedsActivity(void (*fptr)(uint32_t states));

// triggered when a global led changes states
void onGlobalLedsActivity(void (*fptr)(uint32_t states));

// triggered when a pixel changes states, @states holds the state of each
// led in bits, so bit 0 of states, is LED 0, if bit 0 is not set then led is off
void onPixelsActivity(void (*fptr)(uint32_t states));

// triggered when an RGB pixel changes states, @states holds the state of each
// led in bits, so bit 0 of states, is LED 0, if bit 0 is not set then led is off
void onRgbPixelsActivity(void (*fptr)(uint32_t states));

// for user defined events, includes page, global, pixels & rgb pixels
// this callback must return true or false
// true turns Led on, false turnes it off
void onLedsUserEvent(bool (*fptr)(uint8_t n, uint32_t event, uint8_t type));
```
