*Under MIT license.*

[Official BMC Website >> RoxXxtar.com/bmc](https://www.roxxxtar.com/bmc)

[< Back to Documentation](README.md)

# Bluetooth LE MIDI
BMC has support for the [Adafruit nRF8001](https://www.adafruit.com/product/1697), with that breakout you can easily wire it over SPI to your teensy and have full BLE MIDI IO for BMC (except for MIDI Clock it's just not accurate enough)

You MUST download theBLEPeripheral library from this fork [https://github.com/neroroxxx/arduino-BLEPeripheral](https://github.com/neroroxxx/arduino-BLEPeripheral)

*UNFORTUNATELY Adafruit has discontinued the nRF8001 likely due to the fact that the chip is old I've been testing many of their other BLE modules but they all need custom firmware to run MIDI and they all really lack MIDI support for anything other than NOTE and maybe Control Change. Currently I'm working on firmware for the ESP32 to convert it into a BLE MIDI device to behave the same way as the nRF8001, I figured the ESP32 would be the best bet for BLE for BMC because it's a very common and affordable board*

### API
There are many API callbacks and functions available for use, these may not reflect the latest version

##### FUNCTIONS
```c++
```

##### CALLBACKS
```c++
```
