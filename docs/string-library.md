*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# String Library
BMC has a String Library, this is simply an array `char` strings.

These are designed to be used within your sketch.

These strings are editable via the Editor App and

The length of the library and number of characters per string are set via the **Config File Maker**

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS

```c++
// get a String Library item
// must pass a pointer to your string with length >= BMC_NAME_LEN_STRING_LIBRARY
void getStringLibrary(uint8_t n, char* t_string);

// update the value of a String Library item
// must pass a pointer to your string with length <= BMC_NAME_LEN_STRING_LIBRARY
// only works when not connected to editor app
bool setStringLibrary(uint8_t n, char* t_string, bool t_save=false);

// update the value of a String Library item
// must pass a pointer to your string with length <= BMC_NAME_LEN_STRING_LIBRARY
// only works when not connected to editor app
bool setStringLibrary(uint8_t n, const char* t_string, bool t_save=false);
```

##### CALLBACKS
