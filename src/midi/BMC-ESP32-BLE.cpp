/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (uint8_t c) 2025 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.
*/

#include "midi/BMC-ESP32-BLE.h"

#if defined(BMC_FOR_ESP32)

bool BMCEsp32BleMidi::begin(uint16_t baud) {
  BLEDevice::init(BMC_BLE_DEVICE_NAME);
  
  // NimBLEDevice::setSecurityAuth(true, false, false);

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks(this));
  pServer->advertiseOnDisconnect(true);
  
  auto pService = pServer->createService(BLEUUID(BMC_MIDI_SERVICE_UUID));

  pCharacteristic = pService->createCharacteristic(
    BLEUUID(BMC_MIDI_CHARACTERISTIC_UUID),
    NIMBLE_PROPERTY::READ |
    NIMBLE_PROPERTY::WRITE |
    NIMBLE_PROPERTY::NOTIFY |
    NIMBLE_PROPERTY::WRITE_NR
  );
  pCharacteristic->setCallbacks(new CharacteristicCallbacks(this));

  pService->start();

  // Set MTU for larger MIDI messages
  BLEDevice::setMTU(BMC_ESP32_BMC_ESP32_MAX_SYSEX_LENGTH);


  auto advertisementData = BLEAdvertisementData();
  advertisementData.setFlags(0x04);
  advertisementData.setCompleteServices(BLEUUID(BMC_MIDI_SERVICE_UUID));
  advertisementData.setName(BMC_BLE_DEVICE_NAME);

  // Configure BLE advertising
  pAdvertising = pServer->getAdvertising();
  pAdvertising->setAdvertisementData(advertisementData);
  // pAdvertising->addServiceUUID(pService->getUUID());
  // pAdvertising->setAppearance(0x00);
  pAdvertising->start();




  BMC_PRINTLN("");
  BMC_PRINTLN("ESP32 MIDI Service Started...");

  return true;
}

#endif