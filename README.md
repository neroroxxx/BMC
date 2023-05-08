**Licensed under the MIT license.**

*See LICENSE file in the project root for full license information.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

# BMC 2.0 is Here!
## BMC the Badass MIDI Controller For Teensy 3.x, 4.x & Teensy Micromod!

***BMC 2.0 is NOT compatible with previous versions of BMC, BMC 2.0 is a major re-write and re-architectured of the core, if you have a device with a previous version of BMC you will need to create a new config file. For more info on what's changed and why see:***

**PLEASE READ THIS DOCUMENT FIRST, SPECIALLY THE [INSTALLATION](#installation) REQUIREMENTS FOR THE LIBRARY, BMC REQUIRES TEENSYDUINO AND THE BMC FOR TEENSY BOARDS TO BE INSTALLED.**

**YOU CAN DOWNLOAD THE BMC LIBRARY FROM THE ARDUINO LIBRARY MANAGER AND KEEP IT UP TO DATE THERE!**

### Get BMC updates on Facebook [https://www.facebook.com/badassmidi](https://www.facebook.com/badassmidi)

***You can access they web-based editor at [https://www.RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)***

***The editor app runs on Google Chrome and requires internet access the first time, after that you can instal the app on your computer as a chrome app***

---


# Introduction

The Badass MIDI Controller (BMC) Library is an all in one MIDI Controller library specifically designed for the Teensy Platform with a Companion dedicated Desktop Editor App!

With BMC you can use Buttons/Footswitches, Rotary Encoders, Potentiometers/Expression Pedals, Leds, WS2812 Addressable Leds, Relays, OLED displays and the ILI9341 Touch Displays along with the ability to edit all their functions using a customizable desktop app.

BMC was designed to allow you to build your Hardware MIDI Controller powered by a Teensy and then easily customize your firmware to fit your hardware, what's more is that you can easily edit your firmware using a Graphic User Interface (GUI) within the Editor App, allowing you to make modifications to your hardware like changing the pin used for a button or adding new hardware like more buttons or more leds, etc without having to write new code.

With BMC you actually don't have to write any code or even be a seasoned programmer, everything is taken care of it by the firmware using a configuration file that you can create on the desktop app. For more experienced programmers BMC does have an API to allow to write your own code into your sketch and feed from BMC.

BMC 2.0 is compatible with the Following Teensy Models:
* Teensy Micromod
* Teensy 4.1
* Teensy 4.0
* Teensy 3.6
* Teensy 3.5
* Teensy 3.2

Some of BMC's key Features Include:

* **USB and USB Host MIDI** BMC leverages Teensy's USB MIDI to communicate with the editor app and also to control MIDI apps on your computer, in addition Teensy boards with USB Host support (Teensy 4.x, Micromod and Teensy 3.6) can use the host usb to send/receive MIDI.

* **4 Serial MIDI Ports** you can have up to 4 independent Standard/Legacy MIDI Ports.

* **Automatic Handling of EEPROM** either using the built-in EEPROM, SD Card (on boards that have it) or with a 24LC256 i2c EEPROM Chip. EEPROM is where all editable data lives.

* **Automatic Handling of Reading and Controlling all basic hardware** in other words, if you want to add footswitches you don't have to write any of the code to read the footswitch, BMC will do all of it just stomp away!

* **Sync** BMC can sync to your Fractal Axe FX II or AX8, Logic Pro and more.

---

## DOCUMENTATION
As you can imagine this is a very large and ambitious project and requires a lot of documentation, the editor app has a ton of info about the events for buttons, leds, etc built-in and the library also has lots of comments in the code.

For better management all BMC Documentation has been moved to [https://www.roxxxtar.com/bmc](https://www.roxxxtar.com/bmc)

---

## The Editor App
![BMC Editor App](images/bmc-editor-preview.jpg)

---

## Support BMC Development
To support BMC Development you can can buy products from the BMC Shop @ [BadassMIDI.com](http://www.badassmidi.com)

---

**Watch BMC Videos on [YouTube](https://www.youtube.com/channel/UCDl3gSF3X0cuXY3fBwXpQYA)**

---

## 3rd Party Dependencies
BMC will use many libraries included with Teensyduino, however, here are some of the 3rd party libraries it uses.

* Arduino MIDI Library (Version 5.0 or later)
* QueueArray Library (bundled with BMC)
* i2c EEPROM Library (bundled with BMC)
* BLEPeripheral Library for nRF8001 (download at [https://github.com/neroroxxx/arduino-BLEPeripheral](https://github.com/neroroxxx/arduino-BLEPeripheral), you must instal from this url as it's a modified version of the library.)
* Source code has comments with credits if the code comes from another library, if I missed any please let me know.

---

## Installation
Moved to [docs/installation-instructions.md](docs/installation-instructions.md)

---

## Coding
All pre-processors/macros are all uppercase with underscores between words and are always prefixed **BMC_** this is to avoid issues with other libraries.

```c++
#define BMC_MIDI_CONTROL_CHANGE 0xB0
```

All classes are prefixed `BMC` in camelCase with the first letter capital, Example:

* `BMCMidi`
* `BMCTimer`
* `BMCFlags`
* `BMCMidiMessage`

The **"store"** struct and all it's member structs are prefixed with **bmcStore** and are camelCase this is to tell them apart from classes and other structs. Example:

* `bmcStore`
* `bmcStoreGlobalCustomSysEx`

Some of the macros, classes and function names may be long but I want them to be as easy to read and understand their purpose as possible.

## Library File Structure
The BMC library is split into multiple folders and multiple files,
I refer to the "**src**" folder in the library as the "**root**" folder.

The main class is the **BMC** class, this class is split into one header **BMC.h** and
multiple implementation files **(.cpp)** in order to keep the code manageable.
For example the file named **BMC.cpp** contains the class initialization, the **begin**
method and the **update** method, while **BMC.midi.cpp** handles reading the MIDI Ports.

Additionally the **API** is it's own class, `BMCApi`, this is the class you want to use if you want to use any API calls.

You can also just use an instance of `BMC` if you won't be using the API.

You can also use this macro to initialize the API.

```c++
// this macro creates an instance of BMCApi named bmc
BMC_DEFAULT();
```

The above is the equivalent of:

```c++
BMCApi bmc = BMCApi();
```
---

## About BMC
BMC started because at around 2017 I wanted to build my own MIDI Controller that could fully sync with my Fractal AX8 guitar processor, I started with an Arduino Mega but I quickly found that there was no easy library that would allow me to make an editor app to make changes to my footcontroller's buttons.

This prompted me to make an editor app for that device, since I'm mainly a Web Programmer, I chose MIDI for the communication since it's available with Google Chrome and that made it very easy to put an app together, the main downside was that I needed to use a Serial MIDI to USB adaptor or Serial to MIDI Software to communicate with the Arduino.

After this I started looking for boards that had USB MIDI already implemented and that's when I found (and fell in love with) the Teensy Platform and their range of boards, they are smaller and much faster than Arduino boards plus they have tons of features already built-in without hacking them, mainly **USB MIDI**.

Once I got a couple of Teensys I started working on a new editor to be able to edit the data on the EEPROM without having to upload the sketch again which went well, but then I wanted to make a larger foot controller with more buttons and pots which meant that I had to write all new code, this is what gave me the idea of having a master Configuration File that would make the entire library adapt to the number of buttons, encoders, pots, etc. of my new device.

After I had the original version of BMC, as usual for me, I decided to completely re-write it from scratch to fix design flaws, this happened a total of 4 times with the 4th re-write being the current version of BMC, I then realized If I had a library like BMC when I first had the desire to build a MIDI controller I would have spent more time playing my guitar than coding and testing (not that there's anything wrong with that) so I decided to start documenting it so I could Open-Source it for others to use it.

I've done the best I could within my abilities to make BMC as easy to use as possible, however as I'm not a C++ Pro and the code base is not as optimized (or as well coded) as a seasoned C++ programmer would have done. This is where you can come in and help.

---

If you're a seasoned C++ programmer who wants to collaborate and make BMC as powerful as possible please feel free to contact me @ [https://www.RoxXxtar.com/contact](https://www.roxxxtar.com/contact) to discuss ideas and improvements to the code.

**If you have any experience with HUI control and would like to help me implement it's functionality in BMC please email me at [https://www.RoxXxtar.com/contact](https://www.roxxxtar.com/contact)**

For more info on BMC and to access the editor you can visit the official site at [https://www.RoxXxtar.com/BMC](https://www.roxxxtar.com/bmc)
