#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <NimBLEDevice.h>
#include "config.h" // Include global config file

extern int16_t AcX, AcY, AcZ;

void setupForceSensors();
void readForceSensors();
int medianFilter(int index);
float readMPU();
void getCalibratedAccelerometer();
void setupMPU();

#endif
