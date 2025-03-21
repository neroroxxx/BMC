# **Badass MIDI Controller (BMC)**

[Official BMC Website @ BadassMIDI.com](http://www.badassmidi.com/)

## **BMC 2.0 is Here!** 🚀
### For Teensy 3.x, 4.x & Teensy Micromod

⚠ **BMC 2.0 is NOT compatible with previous versions of BMC!, you will need to create a new config file and backups for older versions are not compatible.**

BMC 2.0 is a major re-write of the BMC core. If you're upgrading from an older version, you'll need to create a new config file. Learn more about the changes [here](#documentation).

📌 **Before proceeding, please review the [Installation](#installation) requirements!**

✅ **Download the BMC library directly from the Arduino Library Manager.**

### 📢 Stay Updated!
🔹 [Follow BMC on Facebook](https://www.facebook.com/badassmidi)
🔹 [Follow BMC on Instagram](https://www.instagram.com/badassmidi)  
🔹 [Watch BMC Videos on YouTube](https://www.youtube.com/channel/UCDl3gSF3X0cuXY3fBwXpQYA)  
🔹 [Access the Web Editor](https://www.RoxXxtar.com/bmc) (Google Chrome required)  

---

## **Table of Contents**
- [What is BMC?](#what-is-bmc)
- [Supported Teensy Boards](#supported-teensy-boards)
- [Key Features](#key-features)
- [Documentation](#documentation)
- [BMC Editor App](#bmc-editor-app)
- [Installation](#installation)
- [Library Structure & Coding Style](#library-structure--coding-style)
- [About BMC](#about-bmc)
- [Contribute to BMC](#contribute-to-bmc)
- [License](#license)

---

## **What is BMC?**
BMC (**Badass MIDI Controller**) is a powerful MIDI controller library designed for **Teensy** boards. It comes with a **companion editor app** that lets users design their MIDI controller’s hardware and UI **without writing code**.

### **How It Works**
1. **Design Your MIDI Controller** 🛠️  
   - Specify buttons, LEDs, potentiometers, encoders, displays, MIDI ports, and more.
   - Configure the **UI layout** to match your physical hardware setup.
   - Customize the UI elements (e.g., different button styles and colors).
2. **Compile & Upload** 🚀  
   - BMC generates a **config.h** file that defines your controller setup.
   - The library compiles with this config file to enable only the required features.
3. **Edit & Manage** 🎛️  
   - Use the editor app to modify settings and  data in EEPROM—no need to re-upload code!

✅ **No coding required!** BMC handles everything behind the scenes.  
💡 Advanced users can extend functionality using the **BMC API**.

---

## **Supported Teensy Boards**
- Teensy **Micromod**
- Teensy **4.1**
- Teensy **4.0**
- Teensy **3.6** *(⚠ Not recommended for new designs)*
- Teensy **3.5** *(⚠ Not recommended for new designs)*
- Teensy **3.2** *(⚠ Not recommended for new designs)*

---

## **Key Features**
✅ **MIDI Communication**  
   - USB & USB Host MIDI support for controlling DAWs and MIDI apps.
   - Up to **4 Serial MIDI Ports** for legacy devices.
✅ **Automatic Hardware Management**  
   - Reads buttons, encoders, pots, LEDs, and displays **without extra coding**.
✅ **EEPROM Handling**  
   - Supports **built-in EEPROM**, **SD Card**, or **external I2C EEPROM (24LC256)**.
✅ **MIDI Sync**  
   - Syncs with **Fractal Axe FX II**, **AX8**, **Logic Pro**, and more!

---

## **Documentation** 📖
For complete documentation, visit:  
📌 [BMC Documentation](https://www.roxxxtar.com/bmc)

---

## **BMC Editor App**

🎉 **Get the BMC Editor App for iPad!** 🎉

<a href="https://www.roxxxtar.com/?urlrefcode=58a6d4b18f998172d83f3171d43b465f" target="_blank">
  <img src="images/app-store.png" alt="Description" width="400" style="margin: 5px auto;">
</a>

Purchasing the app **supports BMC development**! ❤️

![BMC Editor Preview](images/bmc-editor-preview.jpg)

Creating a matchinglayout is this easy

![BMC Editor Preview](images/layout-edit.gif)

---

## **Support BMC Development**
Help improve BMC by purchasing MIDI modules & accessories at [BadassMIDI.com](http://www.badassmidi.com)!

[![BadassMIDI.com](images/badassmidi-shop-link-image.jpg)](https://www.roxxxtar.com/badassmidi)

---

## **Installation** 🛠️
📌 Follow the installation guide here:  
[Installing Teensyduino & BMC on Arduino 2.0](https://www.roxxxtar.com/blog/articles/2023/05/05/installing-teensyduino-and-bmc-on-arduino-2-0)

---

## **Library Structure & Coding Style**
✅ **Macros**: Prefixed with `BMC_`, uppercase with underscores.
```c++
#define BMC_MIDI_CONTROL_CHANGE 0xB0
```
✅ **Class Naming**: Prefixed with `BMC`, using camelCase.
```c++
BMCMidi, BMCTimer, BMCFlags, BMCMidiMessage
```
✅ **Struct Naming**: Prefixed with `bmcStore`.
```c++
bmcStore, bmcStoreGlobalCustomSysEx
```
✅ **Default API Initialization**:
```c++
// Creates an instance of BMCApi named bmc
BMC_DEFAULT();
// Equivalent to:
BMCApi bmc = BMCApi();
```

---

## **About BMC**
BMC started in **2017** as a custom MIDI controller project for a **Fractal AX8** guitar processor. After struggling with Arduino libraries, the need for an easy-to-use editor app became clear. 

💡 **Why Teensy?**  
Teensy boards were the perfect solution due to their **built-in USB MIDI support** and superior **performance** compared to standard Arduinos.

Since then, BMC has evolved into a powerful **no-code MIDI controller framework** that saves time and effort, letting users focus on music instead of programming!

---

## **Contribute to BMC** 🚀
Are you a **C++ programmer**? Want to improve BMC? 
Contact me here: [RoxXxtar Contact Page](https://www.roxxxtar.com/contact)

💡 **HUI Control**: If you have experience with **HUI MIDI Control**, let’s collaborate! Email me at [RoxXxtar Contact Page](https://www.roxxxtar.com/contact).

📌 **More Info & Web Editor:** [RoxXxtar.com/BMC](https://www.roxxxtar.com/bmc)

---

## **License**
**MIT License**  
See the `LICENSE` file for details.
