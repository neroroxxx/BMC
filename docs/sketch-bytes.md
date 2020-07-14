*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Sketch Bytes
Sketch Bytes are an Array of `uint8_t`, you can specify the number of bytes in this array in the **Config File Maker**

Sketch Bytes as their name states are meant to be used within your Sketch, you can edit their value with the Editor App and they are great to store settings for your build that aren't used by BMC.

A good example is a Display's Brightness Control.

To your Sketch, each Sketch Byte is just that, a Byte a number ranging from 0 to 255, however BMC can also limit it's min/max range and it's initial value.

With the **Config File Maker** you can also specify their format so when each sketch byte is displayed on the editor they will have an easier to understand gui.

For example in the case of a display's brightness, if your display can take in a value from 0 to 100 then you can limit the min value of that byte to 0 or 1 (in case you don't want it to ever be off) and the max value to 100, additionally you can specify it's default value to be 100 *(the default value is only set when BMC first builds a new store)*

You can also set their *Step* if you want the Editor to only allow for these bytes to change by adding/substracting the *Step* value, for example a 2 *Step* with a range from 0 to 10 will give you values 0, 2, 4, 6, 8 and 10.

You can also do math on the sketch byte so that it displays a different value, for example you can choose the *Raw Value* in which case the Editor will just show you the actual value of the byte, you can also choose *Multiply Value* and specify a value to multiply the current sketch byte value by, so if the byte's value is 10 and the *Multiply By* value is 100 then the editor will display "1,000".

Also you can append a predefined set of strings like "ms" or "sec" or "hours" etc.

With all these settings you can taylor the way that sketch bytes are displayed by the editor.

Only the actual byte array is store in EEPROM, all other data is defined into the build.

To get a better idea on how to format them, try the **Config File Maker**

### Name
Each sketch byte can also have a name, specified **Config File Maker**, this name is non-editable after compile.

Adding a name to your sketch byte doesn't take up EEPROM.


### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// set a value for the specified sketch byte
void setSketchByte(uint8_t n, uint8_t value);
// save sketch bytes to EEPROM
// @triggerStoreUpdateCallback will trigger the onStoreUpdate callback
void saveSketchBytes(bool triggerStoreUpdateCallback=false);
// get the specified sketch byte
uint8_t getSketchByte(uint8_t n);
// get the defined sketch byte data for the specified byte
BMCSketchByteData getSketchByteData(uint8_t n);

// scroll thru sketch bytes, you must pass the initial value "n"
// this function will then return the next value up or down
// this function is to scroll the index of a sketch byte, useful for editors
uint8_t scrollSketchByte(uint8_t n, uint8_t t_direction, uint8_t t_amount);

// scroll the value of a sketch byte up or down based on the sketch byte's data
// n is the index of the sketch byte, that sketch byte value is then loaded and scrolled
uint8_t scrollSketchByteValue(uint8_t n, uint8_t t_direction, uint8_t t_amount);

// same as above but you can use it to pass it a value that you store on your sketch
uint8_t scrollSketchByteValue(uint8_t n, uint8_t t_value, uint8_t t_direction, uint8_t t_amount);

// format the value of a sketch byte based on it's config format data
// if value is not passed then the sketch byte's value is loaded from EEPROM
void formatSketchByteValue(uint8_t n, char * t_string);
void formatSketchByteValue(uint8_t n, uint8_t t_value, char * t_string);
```
##### CALLBACKS

For sketch bytes you can use the `onStoreUpdate` call to keep track of any changes to the **Store**
```c++
// triggered when EEPROM has been updated either by the editor or the API
void onStoreUpdate(void (*fptr)()){
  callback.storeUpdated = fptr;
}
```
