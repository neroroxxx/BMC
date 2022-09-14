*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Relays
BMC has support for 2 types of Relay, Latching and Non-Latching.

Latching Relays require one data pin, and only go into their Closed/Set state
while they are receiving a voltage, once they stop receiving that volate they
go into their Normally Open State.

Non-Latching Relays on the other hand require 2 data pins and only require a
voltage for a specific amount of time to switch from their Set/Reset States,
also these will stay in whatever state you put them in until you change their state.

In BMC Relays are Global, they don't change their events when changing pages.

You do NOT want to connect your relay directly to the teensy pin as the relay will usually draw a larger amount of current than a teensy can handle on it's pin, instead you want to use a transistor switch setup circuit, below is a common relay circuit.

Relays have 1 event each and have the ability to be reverse polarity.

![Relay Schematic](images/relays.jpg)

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

```c++
// *******************
// NON-LATCHING RELAYS
// *******************

// get NL RELAY Data
void getRelayNL(uint8_t n, bmcStoreGlobalRelay& t_item);

// get NL RELAY Name Data
// see "advanced names and strings" documentation for length of char string
void getRelayNLName(uint8_t n, char* t_string);

// ***************
// LATCHING RELAYS
// ***************

// get L RELAY Data
void getRelayL(uint8_t t_index, bmcStoreGlobalRelay& t_item);

// get L RELAY Name Data
// see "advanced names and strings" documentation for length of char string
void getRelayLName(uint8_t t_index, char* t_string);

```


##### FUNCTIONS

##### CALLBACKS
```c++
// for user defined events
// this callback must return valid relay command, these are
// BMC_RELAY_RESET (put relay in reset or Normally Open position)
// BMC_RELAY_SET (put relay in set or Normally Closed position)
// BMC_RELAY_TOGGLE (toggle the current state of the relay)
// these are uint8_t
void onRelaysUserEvent(uint8_t (*fptr)(uint8_t n, uint32_t event));
```
