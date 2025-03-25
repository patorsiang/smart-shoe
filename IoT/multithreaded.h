#ifndef MULTITHREADED_H
#define MULTITHREADED_H

#include "sensor_manager.h"

extern TaskHandle_t forceSensorTaskHandle;
extern TaskHandle_t mpuTaskHandle;
extern TaskHandle_t batteryTaskHandle;

void forceSensorTask(void *parameter);
void mpuTask(void *parameter);
void batteryTask(void *parameter);

#endif
