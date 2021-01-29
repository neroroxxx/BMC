*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

[24LC256 wiring](#24LC256 wiring)

# EEPROM / Store

All data for you BMC device that's editable via the editor is stored in EEPROM, all that data is grouped in a Struct known within BMC as the **Store**, you can have up to 32 Stores depending on how much EEPROM you have, for example, on the Teensy 3.6 you have 4K of EEPROM, if your **Store** is 1K or less then you would have 4 **Stores**.

You can change **Stores** with the Editor or the API, if you change the **Store** you would be changing ALL the data of your build, this would include all your pages and all your global data like Settings and Presets, etc.

BMC Supports 3 forms of EEPROM:

- Teensy's built-in EEPROM
- 24LC256 i2c EEPROM chip (32KB)
- Built-in SD Card Reader (only teensy 3.5/3.6/4.0/4.1, external SD Card Readers are not supported)

BMC handles all the reading/writing for the **Store**.
The maximum store size is 32KB on Teensy 3.5/3.6/4.0/4.1 and 16KB on all others this is because the **Store** struct is always loaded in RAM for fast access and I wanted to keep the maximum size of the **Store** to be no more than a quarter of RAM, obviously the actual size of the **Store** is actually based on what you compile onto BMC which will greatly vary. *The Config File Maker in the Editor keeps track of how much EEPROM will be used as you create your config file!*

**Because BMC is very customizable, EEPROM must follow, that is if your build originally had 2 buttons and you decide to add another one, your EEPROM must be rebuilt, this is done automatically by BMC, HOWEVER because make a change like that one will allocate EEPROM for that new button that was added all other bytes adjacent will now be completely different and may cause erroneous behavior. BMC stores a CRC and the version of EEPROM, the CRC is generated based on the space occupied in the EEPROM struct and it's generated at compile time, if this CRC does NOT match the CRC stored in EEPROM BMC will automatically erase your EEPROM setting all bytes to 0 value. This can be an issue if you decide later-on to add another button or encoder etc to your build, to avoid losing all your data the editor app has an IMPORT/EXPORT tool.**

**ALWAYS BACKUP YOUR BUILD BEFORE UPLOADING A NEW OR UPDATED SKETCH.**

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
// use this to refresh displays, etc.
void onStoreUpdate(void (*fptr)());
```


### 24LC256 Wiring
![24LC256 Wiring](../images/24LC256-Wiring)
