#ifndef MULTITHREADED_H
#define MULTITHREADED_H

#include "force.h"
#include "mpu.h"
#include "battery.h"

extern TaskHandle_t forceSensorTaskHandle;
extern TaskHandle_t mpuTaskHandle;
extern TaskHandle_t batteryTaskHandle;
extern TaskHandle_t gyroTaskHandle;
extern TaskHandle_t accTaskHandle;
extern TaskHandle_t tempTaskHandle;

void forceSensorTask(void *parameter);
void batteryTask(void *parameter);
void gyroTask(void *parameter);
void accTask(void *parameter);
void tempTask(void *parameter);
void mpuTask(void *parameter);

#endif
