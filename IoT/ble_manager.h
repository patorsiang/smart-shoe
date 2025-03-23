#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <NimBLEDevice.h>
#include "config.h"

#define BLE_NAME "smart-shoe-nt375"

void setupBLE();

extern NimBLECharacteristic *forceChar[SENSOR_COUNT]; // Declare forceChar globally
extern NimBLECharacteristic *stepChar;
extern NimBLECharacteristic *fallChar;
extern NimBLECharacteristic *MPUChar;
extern NimBLECharacteristic *batteryChar;

#endif
