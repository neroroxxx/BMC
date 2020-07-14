*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# MIDI Events Library
BMC has an events library, these are events that are stored globally and can be used across hardware, these events contain MIDI Messages and are meant to make it easier to pre define some of your most used MIDI messages, for example, if you're a guitar player you'll likely want to use your controller to Engage/Bypass an effect on your processor, we'll use a delay as an example. This is commonly done with MIDI Control Change Messages, so let's say CC#100 is used to engage/bypass your Delay and your device is on Channel 1 and connected to Serial Port A, when you send CC#100 with value 127 the Delay is turned on, CC#100 with value 0 will bypass it.

You can then create a Library message assigned to CC#100/CH#1/Value#127 and assign it to Serial Port A, do the same for Value#0 then set 2 button events one for PRESS and one for 2nd PRESS the PRESS trigger will send the engage library event and the 2nd PRESS will send the bypass message. Even better a library message for Control Change can be set to TOGGLE which will toggle the value sent so you only need 1 event to turn the Delay On/Off. **Toggling happens because BMC remembers the last value of any CC on any Channel that was sent or received and this feature is available across BMC**

Library Events also have their own PORT or PORT Preset, that means that you can assign the port that you want that preset to be sent to every time that library event is triggered. These are Global and do not change with page changes.

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// retrieve a Library event name
// must pass a pointer to your string with length >= BMC_NAME_LEN_LIBRARY
void getLibraryEventName(uint8_t n, char* t_string);

// send/execute a library event
void sendLibraryEvent(uint8_t n);

// send a library even but override the port(s)
// example to send library event 0 to USB and Serial A ports at the same time
// sendLibraryEventToPorts(0, BMC_USB | BMC_SERIAL_A);
void sendLibraryEventToPorts(uint8_t n, uint8_t ports);

// retrieve the a library event as a 32-bit unsigned integer
uint32_t getLibraryEvent(uint8_t n);

// retrieve the status of a library event
uint8_t getLibraryEventStatus(uint8_t n);

// retrieve the channel of a library event
uint8_t getLibraryEventChannel(uint8_t n);

// retrieve the first MIDI word of a library event
uint8_t getLibraryEventData1(uint8_t n);

// retrieve the second MIDI word of a library event
uint8_t getLibraryEventData2(uint8_t n);

// retrieve the stored ports of a library event
uint8_t getLibraryEventPort(uint8_t n);
```
##### CALLBACKS
