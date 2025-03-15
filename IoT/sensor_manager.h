#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <NimBLEDevice.h>
#include "config.h" // Include global config file

void setupForceSensors();
void readForceSensors();
int medianFilter(int index);
float readMPU();

void setupMPU();

#endif
