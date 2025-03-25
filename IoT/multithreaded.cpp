#include "multithreaded.h"

TaskHandle_t forceSensorTaskHandle;
TaskHandle_t mpuTaskHandle;
TaskHandle_t batteryTaskHandle;

void forceSensorTask(void *parameter)
{
  while (true)
  {
    readForceSensors();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void mpuTask(void *parameter)
{
  while (true)
  {
    getAccelerometer();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void batteryTask(void *parameter)
{
  while (true)
  {
    getBatteryVoltage();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
