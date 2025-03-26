#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <NimBLEDevice.h>

#define BLE_NAME "smart-shoe-nt375"

void setupBLE();

extern NimBLECharacteristic *forceChar; // Declare forceChar globally
extern NimBLECharacteristic *stepChar;
extern NimBLECharacteristic *fallChar;
extern NimBLECharacteristic *batteryChar;
extern NimBLECharacteristic *gyroChar;
extern NimBLECharacteristic *tempChar;
extern NimBLECharacteristic *accChar;

#endif
