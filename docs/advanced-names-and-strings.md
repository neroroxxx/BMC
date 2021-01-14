*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)


* [Name Length Constants](#name-length-constants)
* [Name Retrieving Methods](#name-retrieving-methods)
* [Example of usage](#get-a-button-name)


# Names for hardware and data
BMC has constants that hold different data that doesn't change hence why they are **constant**, this data is either directly defined in the config file or defined during the compilation config check.

In the Config File Maker you can specify if you want your buttons/leds/etc to have names this is always available for presets, this feature is intended for those who have a display and what to show the preset name or the name of a button that was pressed, also for those who want to see what an encoder on a page does.

`BMC_NAME_LEN_BUTTONS` is an example of these constants, this constant holds the number of characters compiled for button names, this is the maximum number of characters allocated for each button or global button including the End-of-line character (aka the last character in the string which is used to specify the end of the string).

You can use `BMC_NAME_LEN_BUTTONS` when declaring a char array to retrieve the name of a button. *The length of button names applies to both Page and Global buttons.*

This code will get the name of button 0 of the current page. The first parameter is the button number and the second parameter is the buffer string with at least the same length as the compiled button name length.
```c++
char str[BMC_NAME_LEN_BUTTONS];
bmc.getButtonName(0, str);
```

If you want to read the name of a button in a different page you can do this by adding a 3rd parameter to the `.getButtonName` method, the first parameter is now the page number, second parameter is the button number and the third parameter is the buffer string with at least the same length as the compiled button name length.
```c++
char str[BMC_NAME_LEN_BUTTONS];
bmc.getButtonName(0, 0, str);
```

### Name Length Constants

The length of names for buttons, leds, pots, pages, presets, etc. all start with `BMC_NAME_LEN_`, you can find these all defined in *src/utility/BMC-ConfigCheck.h*

This list represents the current list of names available at the time of this writting.

**Note:** these are always defined so even if you don't use names for say "relays" you can still use `BMC_NAME_LEN_RELAYS` in your sketch tho it will always return 0, also these must always have a value of 2 or more otherwise the config check will reset them to 0

* `BMC_NAME_LEN_BUTTONS` applies to buttons & global buttons
* `BMC_NAME_LEN_LEDS` applies to leds, global leds, pwm leds, Pixels & RGB Pixels
* `BMC_NAME_LEN_POTS` applies to pots and global pots
* `BMC_NAME_LEN_ENCODERS` applies to encoders and global encoders
* `BMC_NAME_LEN_RELAYS` applies to Latching and Non-Latching Relays
* `BMC_NAME_LEN_PAGES` applies to Pages
* `BMC_NAME_LEN_STRING_LIBRARY` applies to String Library names
* `BMC_NAME_LEN_LIBRARY` applies to midi library
* `BMC_NAME_LEN_PRESETS` applies to BMC presets
* `BMC_NAME_LEN_SETLISTS` applies to set lists

### Name retrieving methods

Since BMC is uses the same naming throut the API, all the API calls to retrieve names look the same, also they all require a buffer string with the appropriate length.

```c++
// get the current page name
bmc.getPageName(bufferString);
// get any page name
bmc.getPageName(thePageNumber, bufferString);

// get the name of any button in the current page
bmc.getButtonName(buttonIndex, bufferString);
// get the name of any button in any page
bmc.getButtonName(pageNumber, buttonIndex, bufferString);
// get the name of any global button
bmc.getGlobalButtonName(buttonIndex, bufferString);

// get any led name in the current page
bmc.getLedName(ledIndex, bufferString);
// get any led name in any page
bmc.getLedName(pageNumber, ledIndex, bufferString);
// get the name of any global led
bmc.getLedName(ledIndex, bufferString);
// get any global led name
bmc.getGlobalLedName(ledIndex, bufferString);

// get any pwm led name in the current page
bmc.getPwmLedName(ledIndex, bufferString);
// get any pwm led name in any page
bmc.getPwmLedName(pageNumber, ledIndex, bufferString);

// get any pixel name in the current page
bmc.getPixelName(pixelIndex, bufferString);
// get any pixel name in any page
bmc.getPixelName(pageNumber, pixelIndex, bufferString);

// get any rgb pixel name in the current page
bmc.getRgbPixelName(pixelIndex, bufferString);
// get any rgb pixel name in any page
bmc.getRgbPixelName(pageNumber, pixelIndex, bufferString);

// get the name of any encoder in the current page
bmc.getEncoderName(encoderIndex, bufferString);
// get the name of any encoder in any page
bmc.getEncoderName(pageNumber, encoderIndex, bufferString);
// get the name of any global encoder
bmc.getGlobalEncoderName(encoderIndex, bufferString);

// get the name of any pot in the current page
bmc.getPotName(potIndex, bufferString);
// get the name of any pot in any page
bmc.getPotName(pageNumber, potIndex, bufferString);
// get the name of any global pot
bmc.getGlobalPotName(potIndex, bufferString);

// get the name of any Latching Relay
bmc.getRelayLName(relayIndex, bufferString);
// get the name of any Non-Latching Relay
bmc.getRelayNLName(relayIndex, bufferString);



// get any library event's name
bmc.getLibraryEventName(eventNumber, buffereString);

// get the current preset's name
bmc.getPresetName(bufferString);
// get any preset's name
bmc.getPresetName(presetNumber, bufferString);

// get the current set list's name
bmc.getSetListName(bufferString);
// get any set list's name
bmc.getSetListName(setListNumber, bufferString);

// get the current set list selected song's name
bmc.getSetListSongName(bufferString);
// get the name of any song in the current set list
bmc.getSetListSongName(songNumber, bufferString);
```

### Get a button Name

```c++
#include <BMC.h>

BMC_DEFAULT();

void setup(){
  bmc.begin();
  // loops thru all buttons compiled.
  // BMC_MAX_BUTTONS is a constant that holds the number of buttons compiled.
  // for example if you have 4 buttons, BMC_MAX_BUTTONS will be the number 4
  for(uint8_t i=0;i<BMC_MAX_BUTTONS;i++){
    char str[BMC_NAME_LEN_BUTTONS];
    bmc.getButtonName(i, str);
    Serial.print("Button ");
    Serial.print(i);
    Serial.print(" name is ");
    Serial.println(str);
  }
}

void loop(){
  bmc.update();
}
```
