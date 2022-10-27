/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/
#ifndef BMC_CALLBACKS_H
#define BMC_CALLBACKS_H

#include "utility/BMC-Def.h"
#include "utility/BMC-Structs.h"

class BMCCallbacks {
public:
  BMCCallbacks(){
    pageChanged = 0;
    editorConnection = 0;
    storeUpdated = 0;
    oneSecondPassed = 0;
    menuCommand = 0;
    typerCommand = 0;
    typerCustomCommand = 0;

#if BMC_MAX_TRIGGERS > 0
    triggerCustom = 0;
#endif

#if BMC_MAX_TIMED_EVENTS > 0
    timedEventCustom = 0;
#endif

#if BMC_MAX_LIBRARY > 0
    libraryCustom = 0;
#endif

    buttonDualPress = 0;
    buttonActivity = 0;
    encoderActivity = 0;
    potActivity = 0;
    ledsActivity = 0;
    globalLedsActivity = 0;
    pixelsActivity = 0;
    rgbPixelsActivity = 0;

#if BMC_MAX_POTS > 0 && defined(BMC_USE_POT_TOE_SWITCH)
    potsToeSwitchState = 0;
#endif

#if BMC_MAX_GLOBAL_POTS > 0 && defined(BMC_USE_POT_TOE_SWITCH)
    globalPotsToeSwitchState = 0;
#endif

    globalButtonDualPress = 0;
    globalButtonActivity = 0;
    globalEncoderActivity = 0;
    globalPotActivity = 0;

    buttonsCustomActivity = 0;
    encoderCustomActivity = 0;
    potCustomActivity = 0;
    globalButtonsCustomActivity = 0;
    globalEncoderCustomActivity = 0;
    globalPotCustomActivity = 0;

    // for user defined events
    userEventButtons = 0;
    userEventEncoders = 0;
    userEventPots = 0;
    userEventLeds = 0;
    userEventRelays = 0;

    auxJackConnection = 0;
    midiTriggerReceived = 0;
    midiReceived = 0;
    midiClockTickReceived = 0;
    midiClockBeat = 0;
    midiClockBpmChange = 0;
    midiActivity = 0;
    midiLocalUpdate = 0;
    midiPreRoute = 0;
    valueStream = 0;
    firstLoop = 0;
    midUpdate = 0;
    messengerReceived = 0;
    presetChanged = 0;
    setListChanged = 0;
    setListSongChanged = 0;
    presetBankChanged = 0;
    eepromErased = 0;
    programBankChanged = 0;
    programBankTrigger = 0;

#ifdef BMC_USB_HOST_ENABLED
    hostConnection = 0;
#endif

#ifdef BMC_MIDI_BLE_ENABLED
    bleConnection = 0;
#endif
    // leave this one on


#ifdef BMC_USE_DAW_LC
    dawOnline = 0;
    dawRecievedLCD = 0;
    dawRecievedTimeDisplay = 0;
    dawRecievedAssignmentDisplay = 0;
    dawRecievedChannelMeter = 0;
    dawChannelMeterUpdate = 0;
    dawChannelVPotUpdate = 0;
    dawRecievedChannelFaderPosition = 0;
    dawRecievedMasterFaderPosition = 0;
    dawRecievedChannelSelect = 0;
    dawRecievedChannelSolo = 0;
    dawRecievedChannelMute = 0;
    dawRecievedChannelRecReady = 0;
    dawRecievedLedState = 0;
    dawReceivedTimeCodeDigit = 0;
#endif

#ifdef BMC_USE_BEATBUDDY
    beatBuddyBeatLocation = 0;
#endif

#ifdef BMC_USE_FAS
    fasConnection = 0;
    fasPresetChange = 0;
    fasPresetName = 0;
    fasSceneChange = 0;
    fasBlocksChange = 0;
    fasTunerStateChange = 0;
    fasTunerReceived = 0;
    fasLooperStateChange = 0;
    fasLooperReceived = 0;
    fasCpuReceived = 0;
    fasBlockParameterReceived = 0;
#endif

#ifdef BMC_USE_FAS
    kemperParamReceived = 0;
    kemperStringReceived = 0;
#endif
  }
  void (*oneSecondPassed)(uint8_t stopwatchState);
  void (*editorConnection)(bool state);
  void (*storeUpdated)();
  void (*pageChanged)(uint8_t page);
  void (*menuCommand)(uint8_t t_command);
  void (*typerCommand)(uint16_t t_value, uint16_t t_rawValue);
  void (*typerCustomCommand)(uint16_t t_value, uint16_t t_rawValue);

#if BMC_MAX_TRIGGERS > 0
  void (*triggerCustom)(uint8_t id);
#endif

#if BMC_MAX_TIMED_EVENTS > 0
  void (*timedEventCustom)(uint8_t id, uint8_t a, uint8_t b, uint8_t c);
#endif

#if BMC_MAX_LIBRARY > 0
  void (*libraryCustom)(uint8_t id);
#endif


  void (*buttonDualPress)(uint16_t btn1, uint16_t btn2);
  void (*buttonActivity)(uint16_t n, uint8_t eventIndex, uint8_t trigger,
                          bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS> button,
                          bmcStoreEvent data);
  void (*encoderActivity)(uint8_t index, bool increased,
                          bmcStoreEncoder data, uint8_t ticks);
  void (*potActivity)(uint8_t index, uint8_t value,
                      bmcStorePot data);
  void (*ledsActivity)(uint32_t states);
  void (*globalLedsActivity)(uint32_t states);
  void (*pixelsActivity)(uint32_t states);
  void (*rgbPixelsActivity)(uint32_t states);

  void (*globalButtonDualPress)(uint16_t btn1, uint16_t btn2);
  void (*globalButtonActivity)(uint16_t n, uint8_t eventIndex, uint8_t trigger,
                          bmcStoreDevice <BMC_MAX_BUTTON_EVENTS, BMC_MAX_BUTTON_EVENTS> button,
                          bmcStoreEvent data);
  void (*globalEncoderActivity)(uint8_t index, bool increased,
                          bmcStoreEncoder data, uint8_t ticks);
  void (*globalPotActivity)(uint8_t index, uint8_t value,
                      bmcStorePot data);

#if BMC_MAX_POTS > 0 && defined(BMC_USE_POT_TOE_SWITCH)
  void (*potsToeSwitchState)(uint8_t n, bool state);
#endif

#if BMC_MAX_GLOBAL_POTS > 0 && defined(BMC_USE_POT_TOE_SWITCH)
  void (*globalPotsToeSwitchState)(uint8_t n, bool state);
#endif

  void (*buttonsCustomActivity)(uint8_t n, uint8_t eventIndex, uint8_t byteA, uint8_t byteB, uint8_t byteC, uint8_t ports);
  void (*encoderCustomActivity)(uint8_t index, uint8_t byteA, uint8_t byteB, uint8_t byteC, bool direction, uint8_t ticks);
  void (*potCustomActivity)(uint8_t index, uint8_t byteA, uint8_t byteB, uint8_t byteC, uint8_t t_value);
  void (*globalButtonsCustomActivity)(uint8_t n, uint8_t eventIndex, uint8_t byteA, uint8_t byteB, uint8_t byteC, uint8_t ports);
  void (*globalEncoderCustomActivity)(uint8_t index, uint8_t byteA, uint8_t byteB, uint8_t byteC, bool direction, uint8_t ticks);
  void (*globalPotCustomActivity)(uint8_t index, uint8_t byteA, uint8_t byteB, uint8_t byteC, uint8_t t_value);

  void (*userEventButtons)(uint8_t n, uint32_t event, uint8_t ports, uint8_t mode);
  void (*userEventEncoders)(uint8_t n, uint32_t event, uint8_t ports, uint8_t mode);
  void (*userEventPots)(uint8_t n, uint32_t event, uint8_t ports, uint8_t value);
  uint8_t (*userEventLeds)(uint8_t n, uint32_t event, uint8_t ledType);
  uint8_t (*userEventRelays)(uint8_t n, uint32_t event);

  void (*auxJackConnection)(uint8_t n, bool state);

  void (*midiTriggerReceived)(uint32_t source, uint32_t event);

  void (*midiReceived)(BMCMidiMessage data);
  void (*midiClockTickReceived)();
  void (*midiClockBeat)();
  void (*midiClockBpmChange)(uint16_t tempo);
  void (*midiActivity)(bool in, bool out);
  void (*midiLocalUpdate)();
  bool (*midiPreRoute)(BMCMidiMessage& data, uint8_t destinations);

  void (*valueStream)(BMCValueStream item);
  void (*presetChanged)(bmcPreset_t n);
  void (*presetBankChanged)(uint8_t n);
  void (*setListChanged)(uint8_t n);
  void (*setListSongChanged)(uint8_t n);

  void (*programBankChanged)(uint8_t n);
  void (*programBankTrigger)(uint8_t n);

  void (*eepromErased)();
  void (*firstLoop)();
  void (*midUpdate)();
  void (*messengerReceived)(BMCMessenger t_messenger);

#ifdef BMC_USB_HOST_ENABLED
    void (*hostConnection)(bool state);
#endif

#ifdef BMC_MIDI_BLE_ENABLED
    void (*bleConnection)(bool state);
#endif

#ifdef BMC_USE_DAW_LC
    void (*dawOnline)(bool state);
    void (*dawRecievedLCD)(BMCMidiMessage data);
    void (*dawRecievedTimeDisplay)(uint8_t digit, char character);
    void (*dawRecievedAssignmentDisplay)(uint8_t digit, char character);
    void (*dawRecievedChannelMeter)(uint8_t channel, uint8_t value);
    void (*dawChannelMeterUpdate)(uint8_t channel, uint8_t value, uint8_t overload);
    void (*dawChannelVPotUpdate)(uint8_t channel, uint8_t value, uint8_t centered, uint8_t mode);
    void (*dawRecievedChannelFaderPosition)(uint8_t channel, int value);
    void (*dawRecievedMasterFaderPosition)(int value);
    void (*dawRecievedChannelSelect)(uint8_t channel, bool state);
    void (*dawRecievedChannelSolo)(uint8_t channel, bool state);
    void (*dawRecievedChannelMute)(uint8_t channel, bool state);
    void (*dawRecievedChannelRecReady)(uint8_t channel, bool state);
    void (*dawRecievedLedState)(uint8_t channel, bool state);
    void (*dawReceivedTimeCodeDigit)(uint8_t digit, uint8_t value);
#endif

#ifdef BMC_USE_BEATBUDDY
  void (*beatBuddyBeatLocation)(uint8_t t_location, uint8_t numerator);
#endif

#ifdef BMC_USE_FAS
  void (*fasConnection)(bool state);
  void (*fasPresetChange)(uint16_t n);
  void (*fasPresetName)(char* str);
  void (*fasSceneChange)(uint8_t n);
  void (*fasBlocksChange)();
  void (*fasTunerStateChange)(bool state);
  void (*fasTunerReceived)(BMCTunerData& data);
  void (*fasLooperStateChange)(bool state);
  void (*fasLooperReceived)(uint8_t state, uint8_t position);
  void (*fasCpuReceived)(uint8_t n);
  void (*fasBlockParameterReceived)(uint8_t block, uint8_t param, uint16_t value, char* str, uint8_t strLen);

#endif

#ifdef BMC_USE_FAS
  void (*kemperParamReceived)(uint16_t param, uint16_t value);
  void (*kemperStringReceived)(uint16_t param, char* str, uint8_t len);
#endif
};

#endif
