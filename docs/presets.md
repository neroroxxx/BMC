*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Presets
BMC Presets are basically collections of Library Events, you can compile presets to have up to 16 library events, you can also enable a startup preset which obviously will be executed upon BMC starting up. These are Global and do not change with page changes.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// retrieve the current preset name
void getPresetName(char* t_string);

// retrieve a preset name
void getPresetName(uint8_t n, char* t_string);

// get how many library messages this preset has
uint8_t getPresetLength(uint8_t n);

// get a library message id
uint8_t getPresetItem(uint8_t n, uint8_t e);

// get the current preset number
uint8_t getPreset();

// get the current preset bank
uint8_t getPresetBank();

// get the index of the current preset on the current bank
uint8_t getPresetInBank();

// change to a preset
void setPreset(uint8_t n);

// go to the next preset
void presetUp(bool endless);

// go to the previous preset
void presetDown(bool endless);

// preset in bank
void setPresetBank(uint8_t n);

// switch to a specific preset in a specific bank
void setPresetInBank(uint8_t n, uint8_t b=255);

// go to next bank
void presetBankUp(bool endless);

// go to previous bank
void presetBankDown(bool endless);

// go to next preset in current bank
void presetInBankUp(bool endless);

// go to previous preset in current bank
void presetInBankDown(bool endless);
```
##### CALLBACKS
```c++
// triggered when a BMC Preset has changed
void onPresetChange(void (*fptr)(uint8_t n));

// triggered when a BMC Preset Bank has changed
void onPresetsBankChange(void (*fptr)(uint8_t n));
```
