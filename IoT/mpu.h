#ifndef MPU_H
#define MPU_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "global_heads.h"

void initMPU();
void getGyroReadings();
void getAccReadings();
void getTemperature();
void updateMPUEvents();
void calibrateMPU(int samples = 500);

#endif
