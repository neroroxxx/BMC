*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# EEPROM
All data for you BMC device that's editable via the editor is stored in EEPROM, this can be either your Teensy's built-in EEPROM or the 24LC256 i2c EEPROM chip or on teensy 3.5/3.6/4.0 the built-in SD card (keep in mind you would have to use some sort of breakout to access the SD card on the Teensy 4.0, BMC does NOT support using SD Card Breakouts only the built-in SD card on those boards.)
BMC handles all the reading/writing of the **store** the struct that holds all the editable data to any of these locations.
The maximum store size is 32KB on Teensy 3.5/3.6/4.0 and 16KB on all others this is because the **store** struct is always loaded in RAM for fast access and I wanted to keep the maximum size of the **store** to be no more than a quarter of RAM, obviously the actual size of the **store** is actually based on what you compile onto BMC which will greatly vary. *The Config File Maker in the Editor keeps track of how much EEPROM will be used as you create your config file!*

**Because BMC is very customizable, EEPROM must follow, that is if your build originally had 2 buttons and you decide to add another one, your EEPROM must be rebuilt, this is done automatically by BMC, HOWEVER because make a change like that one will allocate EEPROM for that new button that was added all other bytes adjacent will now be completely different and may cause erroneous behavior. BMC stores a CRC and the version of EEPROM, the CRC is generated based on the space occupied in the EEPROM struct and it's generated at compile time, if this CRC does NOT match the CRC stored in EEPROM BMC will automatically erase your EEPROM setting all bytes to 0 value. This can be an issue if you decide later-on to add another button or encoder etc to your build, to avoid losing all your data the editor app has an IMPORT/EXPORT tool, more details on this are down on this page.**

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

##### CALLBACKS
```c++
// triggered when BMC erases the active EEPROM, this usually only happens when
// you have multiple stores available and BMC changes the store to one that doesn't
// match the current CRC
void onEepromErased(void (*fptr)());

// triggered when EEPROM has been updated either by the editor or the API
void onStoreUpdate(void (*fptr)());
```
