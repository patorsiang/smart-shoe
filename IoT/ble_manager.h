#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include "config.h" // Ensure SENSOR_COUNT is defined before usage
#include <NimBLEDevice.h>

void setupBLE();

extern NimBLECharacteristic *forceChar[SENSOR_COUNT]; // Declare forceChar globally

#endif
