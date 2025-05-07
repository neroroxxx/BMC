# 📄 CHANGELOG

All notable changes to this project will be documented in this file.

---

## [2.3.5] - 2025-05-07
- Hotfix for 2.3.4 FS bug
---

## [2.3.4] - 2025-05-07
- Adds **ESP32-S2, ESP32-S3, ESP32-S2 Mini, ESP32-S3 Zero** Beta Support
- Requires updating the BMC for ESP32 boards package.
- USB MIDI built-in on ESP32-S2/S3 - no setup needed.
- Re-organized Files.
- Adds LittleFS File System option for Editable memory.
- Support for Mini Displays (ST7735) on ESP32 boards.
- Mini Display support now requires an updated config.h
- Precision Master MIDI Clock
- Updated code for Buttons, Pots and Encoders.
- Support for SH1106 OLED Displays

---

## [2.3.3] - 2025-03-31
- Adds **ESP32 Beta Support**
- ESP32 uses **BLE MIDI** instead of USB MIDI
- ESP32 currently does **not support Mini Displays**
- ESP32 uses **NimBLE-Arduino** for BLE MIDI (now a library dependency)
- Moved to use **FastLED** for Pixels (now a library dependency)
- Supports Editor App Version 2.3.3
- Added new **BMC for ESP32 boards package**
- Only the **Adafruit GFX Library** needs manual installation — other dependencies are included in the board package
- ESP32 and ESP32 for Arduino board packages can coexist
- [Install instructions](https://www.roxxxtar.com/blog/articles/2023/05/05/installing-teensyduino-and-bmc-on-arduino-2-0)

---

## [2.3.1] - 2025-03-13
- Adds **Keep Connection Alive** routing
  - Especially helpful for iPad — prevents Teensy from staying “connected” when the app closes
  - Ensures Teensy resets its connection state properly if the app disconnects without warning

---

## [2.3.0] - 2025-03-11
- Adds **real-time factory reset** for Pot calibration via the editor
- Supports Editor v2.3.0
- Minor bug fixes

---

## [2.2.5] - 2025-01-31
- Adds ability to **display the name of a MIDI CC event** on a display
- Lets displays show both **text labels and status feedback** based on CC values
- Use case: toggle FX on/off with a button, display the event name, and change display color based on value
- Instructions provided in the release text

---

## [2.2.4] - 2024-04-28
- Fixed **74HC4051 bug**
- Added **Button Callbacks** to the Sketch API

---

## [2.2.3] - 2024-03-06
- Fixed **debug errors when compiling with Pots**

---

## [2.2.2] - 2024-01-03
- Fixed bug with **On-Board Editor**

---

## [2.2.1] - 2023-11-28
- Hotfix: Bug affecting **ILI displays**
- Requires Editor v2.2.0 for new features

---

## [2.2.0] - 2023-11-28
- Adds support for **Mini Displays (ST7735 TFT)**
- Adds support for **MIDIBLE**
- Minor bug fixes
- Requires Editor v2.2.0
- [Full changelog](https://www.roxxxtar.com/blog/articles/2023/11/21/what-s-new-in-bmc-2-2-0)

---

## [2.1.1] - 2023-09-18
- Adds **Outgoing MIDI Control**
- Minor bug fixes
- Requires Editor v2.1.1
- [Full changelog](https://www.roxxxtar.com/blog/articles/2023/09/18/what-s-new-in-bmc-2-1-1)

---

## [2.1.0] - 2023-07-26
### Added
- Support for LCD Displays using I2C with PCD8574 Driver
- ILI9341 and ILI9488 now use Adafruit libraries
- Splash screen for ILI9341 and ILI9488 showing Build Name
- Font update for all display types
- Sync support for Fractal Axe Fx 3, FM3, FM9
- Requires Editor v2.1.0 for full feature support

### Changed
- ILI9341 and ILI9488 now support per-layer color assignments (requires re-exporting Config File)
- Improved button reading
- Removed Arduino MIDI library dependency (now requires Adafruit GFX library)

---

## [2.0.1] - 2023-06-16
### Fixed
- Minor bugs in initial 2.0 release

### Added
- New Toggle feature for Encoders
- Value knob and switch UI for displays
- Hardware mapping to control On-Board Editor while it's running
- Shortcut keys to editor windows

### Changed
- Preset and SetList behavior now allows switching even without assigned events
- Toggling support for Layers, Presets, Setlists, Songs, and Parts

---

## [2.0.0] - 2023-06-14
### 🚀 Major Release
This is the release of **BMC 2.0** — a major rewrite requiring a new config file.  
**Not backward-compatible** with previous versions or backups.

You can run the old and new editor apps side by side to help migrate your config.

### Highlights:
- New **Events Library** for sharing actions across devices
- New **Names Library** for shared naming across devices
- Built-in **On-Board Editor** for real-time device configuration
- Redesigned UI
- LFO support
- Linking devices for easier editing
- "Pages" renamed to **Layers**
- Up to **254 pins** supported (including multiplexers)
- Keypad wiring support for buttons and encoders

---

## [1.7.3] - 2023-04-18
### Updated
- Support for **Teensyduino 1.58**

---

## [1.7.2] - 2023-01-10
### Fixed
- OLED display compile issue

---

## [1.7.1] - 2022-11-27
### Fixed
- Hotfix for Teensy 4.1 compile error

---

## [1.7.0] - 2022-10-20
### Added
- Support for **OLED** and **ILI9341** displays
- Setlists now support **song parts**

### Note
- This was the **final feature release before BMC 2.0**
- BMC 2.0 would introduce a full rewrite based on an Events Library and a smaller flash footprint

---

## [1.6.2] - 2022-09-14
### Added
- New **Pixel Rainbow Fade Mode**

### Changed
- Version bump to match Web Editor version

---

## [1.6.0] - 2022-06-21
### Added
- Support for **74HC40XX** for buttons and encoders
- Support for **Teensy Micromod**

---

## [1.5.0] - 2022-04-19
### Added
- **DAW Logic Control** (see documentation)

### Improved
- Encoder and potentiometer reading accuracy

---

## [1.4.2] - 2021-12-08
### Fixed
- Issue with pot naming

### Added
- Pot debugging: type `pots` in the serial monitor to toggle

---

## [1.4.1] - 2021-11-24
### Added
- Compatibility callback `onEditorUpdate` (replaced by `onStoreUpdate`)

### Changed
- Updated example sketches

---

## [1.4.0] - 2021-07-09
### Added
- **Timed Events**: execute tasks after delays or in loops

### Changed
- Minor code cleanup and fixes

---

## [1.3.0] - 2021-04-30
### Added
- **Pitch Bend Events** for pots

### Fixed
- Pitch Bend callback issues

---

## [1.2.6] - 2021-03-10
### Fixed
- Bug with dual button press handling

---

## [1.2.5] - 2021-02-01
### Fixed
- Bug with `MuxOut`

---

## [1.2.4] - 2021-01-29
### Fixed
- MUX GPIO bug

### Updated
- Documentation

---

## [1.2.3] - 2021-01-14
### Added
- API calls for global buttons, pots, and encoders

---

## [1.2.2] - 2020-12-16
### Improved
- Encoder readings

---

## [1.2.1] - 2020-12-04
### Fixed
- Removed unsupported Teensy LC code
- Corrected version number in editor

---

## [1.2.0] - 2020-11-29
### Removed
- Dropped support for **Teensy LC**

---

## [1.1.0] - 2020-11-20
### Removed
- Removed **MCP23017** from MUX IN
  - Use **MUX GPIO** instead

---

## [1.0.1] - 2020-10-27
### Added
- **FAS Sync Looper Play/Stop** functionality

### Fixed
- Bug affecting **FAS Sync LED states**