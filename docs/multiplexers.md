*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Multiplexers
***********************************************
***BMC now allows for up to 127 Analog Mux Pins, Digital Mux In will still be limited to 64 pins***
***********************************************
While BMC uses a Teensy's pins to read inputs it also has support for up 64 Mux inputs.

These include:

IC | Input Type | Inputs | Pins Required
-|-|-|-
**74HC165** | Digital Only | 8 | 3
**MCP23017** | Digital Only | 16 | 2 *(uses i2c pins 18 & 19)*
**MCP23018** | Digital Only | 16 | 2 *(uses i2c pins 18 & 19)*
**74HC4067** | Analog Only | 16 | 5 *(1 must be analog)*
**74HC4051** | Analog Only | 8 | 4 *(1 must be analog)*



BMC has code to read all chips above however there are a few limits. For digital inputs you can only use one type of chip, so if you want to have 32 inputs you can either use four 74HC165 or two MCP23017 or two MCP23018, you can not combine them.

For Analog input you can only use a chain of 74HC4067 or 74HC4051, not a mix of them.

You can however have a digital mux chain and an analog mux chain at the same time as long as the total number of pins doesn't exceed 64.

More chips may be added in the future, however, I picked these chips because they're common and easy to find online.

### How mux inputs are handled
To explain it better we'll use an example build with two 74HC165s for buttons and one 74HC4067 for pots, these will give us a total of 16 digital and 16 analog, 32 pins all together.

BMC will see these as 32 additional pins, even if you don't use all of them, it's just as if your Teensy suddently has 32 new pins, all input only, and in this example case 16 digital only and 16 analog only. Their pin numbers will start at 64, so pin 0 of the first 74HC165 is now pin 64 and so on.

BMC will always place the Digital pins first in the chain, if you have only one 74HC4067 then the first pin of that chip will be seen as pin 64.

Back to the example, we have 16 digital pins starting at pin 64, the last pin of the second 74HC165 is now pin 79, the first pin of the 74HC4067 is now pin 80 and it's last pin is pin 95.

Once you configure the Mux In on the **Config File Maker** when it comes to selecting the Pin for Buttons/Encoders/Pots you will see these additional pins. All you have to do is choose which pin is connected to which hardware.

Again BMC will still read those 32 pins even if you only end up using 20 of them all together. You can basically have four 74HC165s, each one with only 1 pin connected to a button.

So again, BMC will read all the pins of each IC but only the pins assigned to a button/encoder/pot are utilized.

Digital Mux In states are stores in bits, an 8-bit unsigned int (uint8_t) is used to hold up to 8 pins and so on, so for every 8 digital pins an addional byte of RAM is used, this is aside from the space utilized by the classes that read the IC. These bits are LSB first, so the first pin state is store in bit-0 and so on.

For Analog Mux In, the values read are held in an array of 16-bit unsigned int (uint16_t) so for each Analog Mux pin 2 bytes of RAM are allocated, using 64 analog pins will eat up 128 bytes of RAM.

***MUX PINS CAN NOT BE USED FOR AUX JACKS***

### Other Mux In ICs
BMC also lets you use other ICs, however you have to write the code to read them and then provide BMC the state of each via the API.

For Digital Inputs you can use these API functions:

```c++
// for the first 32 pins
void setMuxIn1To32(uint32_t values);

// for the last 32 pins
// (only available if more than 32 Digital Mux In pins compiled)
void setMuxIn33To64(uint32_t values);
```

For Analog Inputs you can use:

```c++
// @n the analog pin index, this is the actual index, that is if it's the very first analog pin, n will be 0
// @value the 10-bit analog value 0 to 1023
void setMuxInAnalogValue(uint8_t n, uint16_t value);
```

Since digital inputs only have 2 states on/off, true/false, 0/1, etc, you have to think of each digital input as a ***bit***,  so bit-0 of `values` in `setMuxIn1To32` is the very first digital pin.

Additionally, BMC reads digital inputs **Active Low** that is when a button is inactive (depressed) that bit must be **1**, when a button is pressed that bit must be **0**

With the API could use a touch sensor to trigger a Pot and send MIDI messages from assigned to that Pot, MIDI Theremin anybody?

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS


```c++
// Only available if Mux In is set to *Other*
// for the first 32 pins
// each bit of the 32-bit int represents the digital input
// they must be active low
void setMuxIn1To32(uint32_t values);

// Only available if Mux In is set to *Other*
// for the last 32 pins
// (only available if more than 32 Digital Mux In pins compiled)
void setMuxIn33To64(uint32_t values);

// Only available for supported Mux ICs, useful when you want to read pins
// to be handled by your sketch
// read a digital mux in pin
bool getMuxInValue(uint8_t n);
```

For Analog Inputs you can use these API functions:

```c++
// Only available if Mux In is set to *Other*
// @n the analog pin index, this is the actual index, that is if it's the very first analog pin, n will be 0
// @value the 10-bit analog value 0 to 1023
void setMuxInAnalogValue(uint8_t n, uint16_t value);

// Only available for supported Analog Mux ICs, useful when you want to read pins
// to be handled by your sketch
// @n the analog pin index, this is the actual index, that is if it's the very first analog pin, n will be 0
// returns a 10-bit value
uint16_t getMuxInAnalogValue(uint8_t n);
```


##### CALLBACKS
```c++
```
