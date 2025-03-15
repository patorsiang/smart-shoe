#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <NimBLEDevice.h>
#include "config.h" // Include global config file

#define SENSOR_COUNT 3

extern int sensorPins[SENSOR_COUNT];
extern int readings[SENSOR_COUNT][3];

void setupSensors();
void readForceSensors();
int medianFilter(int index);

#endif
