#include "ble_manager.h"
// #include "multithreaded.h"
#include "mpu.h"
#include "battery.h"
#include "wifi_manager.h"
#include "detectPostureImbalance.h"
#include "global_params.h"

void setup()
{
  Serial.begin(115200);
  delay(100);
  setupBLE();
  delay(100);
  setupForceSensors();
  delay(100);
  initMPU();
  delay(100);
  Serial.print("ESP Reset Reason: ");
  Serial.println(esp_reset_reason());
  readingsJSONInfo["msg"] = "Hello from Smart Shoe!";
  readingsJSONInfo["type"] = "info";
  upload("uok/iot/nt375/smart_shoe/info", JSON.stringify(readingsJSONInfo), 0, 0);

  // xTaskCreatePinnedToCore(forceSensorTask, "Force Sensor Task", 8192, NULL, 1, &forceSensorTaskHandle, 0);
  // xTaskCreatePinnedToCore(batteryTask, "Battery Task", 8192, NULL, 1, &batteryTaskHandle, 0);
  // xTaskCreatePinnedToCore(mpuTask, "MPU Task", 8192, NULL, 1, &gyroTaskHandle, 1);
  // xTaskCreatePinnedToCore(gyroTask, "Gyro Task", 8192, NULL, 1, &gyroTaskHandle, 1);
  // xTaskCreatePinnedToCore(accTask, "Acc Task", 8192, NULL, 1, &accTaskHandle, 1);
  // xTaskCreatePinnedToCore(tempTask, "Temp Task", 8192, NULL, 1, &tempTaskHandle, 1);
}

void loop()
{
  getBatteryVoltage();
  readForceSensors();
  getGyroReadings();
  getAccReadings();
  getTemperature();
  detectPostureImbalance();
  delay(10); // give watchdog a breath

  if (shouldSleep())
  {
    Serial.println("No pressure detected — entering deep sleep...");
    readingsJSONInfo["msg"] = "Enter Light Sleep Mode";
    readingsJSONInfo["type"] = "info";
    upload("uok/iot/nt375/smart_shoe/info", JSON.stringify(readingsJSONInfo), 0, 0);
    esp_light_sleep_start();
    delay(100); // allow print to finish
  }
}
