**Licensed under the MIT license.**

*See LICENSE file in the project root for full license information.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

# BMC the Badass MIDI Controller For Teensy 3.x & 4.x!

***Version 1.7.3 Supports Teensyduino 1.58, previous version will not compile without modifications***

***Version 1.5.0 Now includes Logic Control Support, make your own DAW MIDI Controller!***

***Version 1.2.0 Teensy LC is no longer supported as it doesn't have enough Flash to hold BMC + Debugging, this makes it very difficult to ensure compatibility.***

**PLEASE READ THIS DOCUMENT FIRST, SPECIALLY THE [INSTALLATION](#installation) REQUIREMENTS FOR THE LIBRARY, BMC REQUIRES TEENSYDUINO AND THE BMC FOR TEENSY BOARDS TO BE INSTALLED.**

**YOU CAN DOWNLOAD THE BMC LIBRARY FROM THE ARDUINO LIBRARY MANAGER AND KEEP IT UP TO DATE THERE!**

### Get BMC updates on Facebook [https://www.facebook.com/badassmidi](https://www.facebook.com/badassmidi)


BMC is an all-in-one Scalable MIDI Controller library with a companion Desktop/Browser Editor App specifically designed for the Arduino-Compatible **Teensy** development Boards. BMC allows you to build your own MIDI Controllers with a mixed number of Buttons/Leds/Encoders/Pots/Relays etc with only a few lines of code!

BMC is only available for Teensy 3.2, 3.5, 3.6, 4.0, 4.1, support for Teensy LC is no longer available due to RAM usage.

**If you have any experience with HUI control and would like to help me implement it's functionality in BMC please email me at [https://www.RoxXxtar.com/contact](https://www.roxxxtar.com/contact)**

## [BMC DOCUMENTATION](docs/README.md)

***You can access they web-based editor at [https://www.RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)***

![BMC Editor App](images/bmc-editor-preview.jpg)


## Support BMC Development
To support BMC Development you can can buy products from the BMC Shop @ [BadassMIDI.com](http://www.badassmidi.com)

### Meet MIDI CHIP
MIDI CHIP is a tiny board meassuring at 0.7" x 0.85" with a MIDI Input and Output Circuit ready to drop into any BMC project. It includes all the circuitry needed for Serial MIDI Communication including an Optocoupler Isolated  Input and a Buffered Output and 5v or 3.3v Operation!
[![Meet MIDI CHIP](images/midi-chip-all-in-one-midi-io-board.jpg)](https://www.roxxxtar.com/bmc-shop)


**Watch BMC Videos on [YouTube](https://www.youtube.com/channel/UCDl3gSF3X0cuXY3fBwXpQYA)**

The goal of BMC is to let you build a MIDI Controller without having to worry about writing a ton of code by using all the power already available within the Teensy platform, all the code to support hardware, MIDI, Data Storage & Editor Communication is already part of the library.

BMC utilizes a Configuration File which contains all the pre-processors that tell the library what features to compile, the Config file can be created manually or better yet it can be created using the Editor Apps GUI making it really easy to get started.

As this is the initial release of BMC this basic documentation below will grow and get better over time and if it's a little confusing I apologize in advance. Keep in mind tho, I've been using multiple BMC foot controllers over the last year for live shows without any issues so the library has been VERY solid. Also because there are SO MANY combinations of hardware I haven't been able to test every single combination (as in 5 Relays + 52 buttons + 1 PWM led, etc.) however i'm constantly making new devices and also testing on breadboards and so far so good.

My advice to you is to start with a breadboard and your teensy since you likely already have those, then test all the hardware you want to use. As far as the best teensy for your purposes I usually base it on the size of the enclosure I will be using. The Teensy 3.6 has been my go to for any larger project since they have the SD card holder (no need to use the internal EEPROM or a 24LC256) plus you get TONS of pins and tons of FLASH/RAM however it's larger and it's not as easy to fit in a commonly available enclousure, in which case the new king of the block is the Teensy 4.0 so for tighter fits thats you best bet, BMC will run great on a 3.2 as well

* [3rd Party Dependencies](#3rd-party-dependencies)
* [Compatible Boards](#compatible-boards)
* [Hardware Limits](#hardware-limits)
* [Installation Instructions](#installation)
* [Coding](#coding)
* [Library File Structure](#library-file-structure)
* [About BMC](#about-bmc)
* [Documentation](docs/README.md)

## 3rd Party Dependencies
BMC will use many libraries included with Teensyduino, however, here are some of the 3rd party libraries it uses.

* Arduino MIDI Library (Version 5.0 or later)
* QueueArray Library (bundled with BMC)
* i2c EEPROM Library (bundled with BMC)
* BLEPeripheral Library for nRF8001 (download at [https://github.com/neroroxxx/arduino-BLEPeripheral](https://github.com/neroroxxx/arduino-BLEPeripheral), you must instal from this url as it's a modified version of the library.)
* Source code has comments with credits if the code comes from another library, if I missed any please let me know.

## Compatible Boards
I haven't had a chance to test BMC on all Teensy boards out there only the Teensy 3.2/3.6/4.0/4.1 however the Editor and Library are compatible with the boards below even tho they are not tested, If you have those boards please let me know how they work with BMC!

***Teensy LC is no longer supported as it doesn't have enough Flash to hold BMC + Debugging, this makes it very difficult to ensure compatibility.***

|Board             |Compatible  |Tested      |
|------------------|------------|------------|
|Teensy LC         |No         |No          |
|Teensy 3.2        |Yes         |Yes         |
|Teensy 3.5        |Yes         |No          |
|Teensy 3.6        |Yes         |Yes         |
|Teensy 4.0        |Yes         |Yes         |
|Teensy 4.1        |Yes         |Yes         |
|Teensy MicroMod   |Yes         |Yes         |


BMC includes support for:
* **Buttons** *(momentary/non-latching switches)*
* **Leds** *(standard, Bi-Color and/or RGB Leds)*
* **Pixels** *(WS2812/NeoPixels)*
* **Rotary Encoders**
* **Potentiometers/Expression** Pedals
* **Relays** *(latching and non-latching)*
* Up to 7 MIDI IO Ports that can be used simultaneously
* **Port Routing/Soft-thru** across all ports
* **MIDI Clock** *(Master/Slave)*
* **MIDI Active Sense** *(Master/Slave)*
* **MIDI Triggers**/Translation
* **Custom System Exclusive** Messages
* **Library** of MIDI Messages *(that can be assigned across BMC)*
* **Presets** of Library Messages
* Tempo To Tap *(send timed MIDI CC based on BPM)*
* Some built-in Beatbuddy and Helix support
* Some built-in Axe FX II and AX8 support
* **Messenger** *(send strings back and forth between editor and sketch)*
* **String Library** *(editable array of strings to be used in sketch)*
* **SetList**
* up to 64 Mux inputs/outputs using the MCP23017, MCP23018, 74HC165, 74HC595, 74HC4067 and/or 74HC4051
* Lots More!

## Hardware Limits
Hardware like Buttons, Leds, Pots, etc. have a limit which is based on the board you use, for example if your board only has 8 Analog Pins then you can only have 8 Pots, etc. The table below is a general limit to each that can not be exceeded as these are hard-coded. *These may change*

|Hardware             |Max  | 3.2 | 3.5 | 3.6 | 4.0 | 4.1 |
|---------------------|-----|-----|-----|-----|-----|-----|
|Buttons              |64   |Max  |Max  |Max  |Max  |Max  |
|Leds                 |32   |Max  |Max  |Max  |Max  |Max  |
|Pwm Leds             |16   |12   |Max  |Max  |Max  |Max  |
|Global Leds          |16   |Max  |Max  |Max  |Max  |Max  |
|Pots                 |128  |Max  |Max  |Max  |Max  |Max  |
|Encoder              |64   |Max  |Max  |Max  |Max  |Max  |
|Latching Relays      |16   |Max  |Max  |Max  |Max  |Max  |
|Non-Latching Relays  |16   |Max  |Max  |Max  |Max  |Max  |

You can use any combination of Hardware as long as your Teensy supports it!

**NOTE:** using Mux Inputs/Outputs will not increase the maximum number of items that can be used, Muxes just allow you to reach that maximum.

## Installation

Moved to [docs/installation-instructions.md](docs/installation-instructions.md)

### Documentation
As you can imagine this is a very large and ambitious project and requires a lot of documentation, the editor app has a ton of info about the events for buttons, leds, etc built-in and the library also has lots of comments in the code.

For those who would like to collaborate, helping with documentation would be a HUGE help.

Additionally the code base while solid, needs lots of optimizing.

You can access the documentation [Here](docs/README.md)

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


## About BMC
BMC started because at around 2017 I wanted to build my own MIDI Controller that could fully sync with my Fractal AX8 guitar processor, I started with an Arduino Mega but I quickly found that there was no easy library that would allow me to make an editor app to make changes to my footcontroller's buttons.

This prompted me to make an editor app for that device, since I'm mainly a Web Programmer, I chose MIDI for the communication since it's available with Google Chrome and that made it very easy to put an app together, the main downside was that I needed to use a Serial MIDI to USB adaptor or Serial to MIDI Software to communicate with the Arduino.

After this I started looking for boards that had USB MIDI already implemented and that's when I found (and fell in love with) the Teensy Platform and their range of boards, they are smaller and much faster than Arduino boards plus they have tons of features already built-in without hacking them, mainly **USB MIDI**.

Once I got a couple of Teensys I started working on a new editor to be able to edit the data on the EEPROM without having to upload the sketch again which went well, but then I wanted to make a larger foot controller with more buttons and pots which meant that I had to write all new code, this is what gave me the idea of having a master Configuration File that would make the entire library adapt to the number of buttons, encoders, pots, etc. of my new device.

After I had the original version of BMC, as usual for me, I decided to completely re-write it from scratch to fix design flaws, this happened a total of 4 times with the 4th re-write being the current version of BMC, I then realized If I had a library like BMC when I first had the desire to build a MIDI controller I would have spent more time playing my guitar than coding and testing (not that there's anything wrong with that) so I decided to start documenting it so I could Open-Source it for others to use it.

I've done the best I could within my abilities to make BMC as easy to use as possible, however as I'm not a C++ Pro and the code base is not as optimized (or as well coded) as a seasoned C++ programmer would have done. This is where you can come in and help.

If you're a seasoned C++ programmer who wants to collaborate and make BMC as powerful as possible please feel free to contact me @ [https://www.RoxXxtar.com/contact](https://www.roxxxtar.com/contact) to discuss ideas and improvements to the code.

For more info on BMC and to access the editor you can visit the official site at [https://www.RoxXxtar.com/BMC](https://www.roxxxtar.com/bmc)
