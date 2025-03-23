#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "ble_manager.h"
#include "config.h"

#include <Wire.h>

extern int16_t AcX, AcY, AcZ;

void setupForceSensors();
void readForceSensors();
int medianFilter(int index);
float getAccelerometer();
void readCalibratedAccelerometer();
void setupMPU();

#endif
