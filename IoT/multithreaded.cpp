#include "multithreaded.h"

TaskHandle_t forceSensorTaskHandle;
TaskHandle_t batteryTaskHandle;
TaskHandle_t gyroTaskHandle;
TaskHandle_t accTaskHandle;
TaskHandle_t tempTaskHandle;

void batteryTask(void *parameter)
{
  while (true)
  {
    getBatteryVoltage();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void forceSensorTask(void *parameter)
{
  while (true)
  {
    readForceSensors();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void gyroTask(void *parameter)
{
  while (true)
  {
    getGyroReadings();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void accTask(void *parameter)
{
  while (true)
  {
    getAccReadings();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void tempTask(void *parameter)
{
  while (true)
  {
    getTemperature();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void mpuTask(void *parameter)
{
  while (true)
  {
    getGyroReadings();
    getAccReadings();
    getTemperature();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
