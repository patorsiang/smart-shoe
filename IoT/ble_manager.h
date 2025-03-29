#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <NimBLEDevice.h>

extern NimBLEServer *pServer;
extern NimBLECharacteristic *forceChar; // Declare forceChar globally
extern NimBLECharacteristic *stepChar;
extern NimBLECharacteristic *fallChar;
extern NimBLECharacteristic *batteryChar;
extern NimBLECharacteristic *gyroChar;
extern NimBLECharacteristic *tempChar;
extern NimBLECharacteristic *accChar;

void setupBLE();

#endif
