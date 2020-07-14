*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Editor App
BMC works by using a single Global file that contains things like the number of buttons and what pin each button is connected to. This file contains tons of defines, you can create the file manually but why do that when we have an Editor App!
With the editor app you have a GUI where you select what features you want and what pins will be used then export the file as *config.h* to your Sketch's folder.

Many of the features/settings of BMC can be easily overridden by adding a **#define** for that setting in your config file and these are available within the Config File Maker in the Advanced Section.
The idea of the config file is that you can have a config file for each build, one controller may have only pots, the other one may be a foot controller with foot switches and the other one may be all relays for amp switching.
All these features can be mixed and the config file gives you control without having to make changes to the BMC library's source code.

The Editor app also has tons of features like MIDI Profiles, these allow you to create a profile for a specific MIDI device then when you edit a MIDI CC you are presented those commands available to that device for easier editing.

The Editor App communicates with BMC on your Teensy using MIDI System Exclusive (SysEx) messages, MIDI SysEx uses a Manufacturer ID but they also have a Non-Commercial ID (0x7D) which is reserved for use during R&D this is what BMC uses for communication. A SysEx Message is a Byte Array that starts with 0xF0 and ends with 0xF7 and all data bytes within the message using only 7-bits of the byte, a typical SysEx looks like this

* **0xF0** *start of SysEx byte*
* **0x..** *1 or 3 Byte ID*
* **0xNN** *data bytes*
* **0xF7** *end of SysEx byte*

BMC will use the 1 Byte ID 0x7D reserved for R&D, HOWEVER, it also appends an additional 2 bytes, BMC considers those bytes part of the ID even tho technically only the first byte is needed for that ID. The reason for this is to always have 3 bytes available for an ID, my goal is to eventually buy a SysEx ID from the MMA for use by all BMC Builds.

The Config Maker allows you to give your BMC build any SysEx ID you want in case you actually own one? In that case when you connect with the Editor you MUST specify that SysEx ID in the "Advanced" tab of the Connection Window to match the ID of your BMC build.

The Editor App is available as a stand alone app for Mac and Windows and as Web Browser app compatible only with Google Chrome *(as it requires the Web MIDI API)*, the editor is written in HTML/Javascript/CSS and runs within [Electron](https://www.electronjs.org). The editor can be used with iOS by using [Web Midi Browser](https://apps.apple.com/us/app/web-midi-browser/id953846217) and Apple's [Lightning to USB Camera Adapter](https://www.apple.com/shop/product/MD821AM/A/lightning-to-usb-camera-adapter) or [Lightning to USB 3 Camera Adapter](https://www.apple.com/shop/product/MK0W2AM/A/lightning-to-usb-3-camera-adapter)

Should you want to, you can create your own Editor app by going thru the editor section of the library.


[More info on SysEx Id](http://www.personal.kent.edu/~sbirch/Music_Production/MP-II/MIDI/midi_system_exclusive_messages.htm#note1)

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
// get the connection state
bool editorConnected();

// triggered when EEPROM has been updated either by the editor or the API
void onStoreUpdate(void (*fptr)());
```
##### CALLBACKS
```c++
// triggered when the editor connects/disconnects
// @state true if editor is connected
void onEditorConnection(void (*fptr)(bool state));
```
