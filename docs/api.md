*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# API
BMC has lots of API calls and callbacks, I will try and keep them up to date here, however check the *BMC.api.h* file in the *src* folder for all the API calls.

##### FUNCTIONS
```c++

// change the current store
bool changeStore(uint8_t t_address);

// get the current store address
uint8_t getStoreAddress();

// check if BLE connected
bool bleConnected();

// check if USB Host connected
bool hostConnected();

// STOP WATCH
uint8_t getStopwatchState();

uint8_t getStopwatchHours();

uint8_t getStopwatchMinutes();

uint8_t getStopwatchSeconds();

uint32_t getStopwatchTimeout();

// RUN TIME
uint32_t getRuntime();

//TIME
uint8_t getHour();

uint8_t getMinute();

uint8_t getSecond();

uint8_t getDay();

uint8_t getMonth();

uint16_t getYear();
```

##### CALLBACKS
```c++
// triggers every 1 second, additionally adds the stopwatch state as a parameter
void onOneSecondPassed(void (*fptr)(uint8_t stopwatchState));

// triggered when a USB MIDI Device is connected to the Teensy's USB Host
void onHostConnectionChange(void (*fptr)(bool t_connected));

// triggered when BMC connects to a BLE Master Device
void onBleConnectionChange(void (*fptr)(bool t_connected));

// triggered when a Menu Command is handled by a button, encoder, API, etc.
void onMenu(void (*fptr)(uint8_t t_command));

// triggered when BMC runs it's update() method the first time.
void onFirstLoop(void (*fptr)());

// triggered half way thru the BMC update() method, this is in case you need
// to do other tasks like update a display without waiting for the BMC update()
// method to complete
void onMidUpdate(void (*fptr)());
```
