#include "ble_manager.h"
// #include "multithreaded.h"
#include "force.h"
#include "mpu.h"
#include "battery.h"
#include "wifi_manager.h"
#include "mpu.h"

JSONVar readingsJSONWelcome;
void setup() {
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
  readingsJSONWelcome["msg"] = "Hello from Smart Shoe!";
  readingsJSONWelcome["isError"] = false;
  upload("uok/iot/nt375/smart_shoe/info", JSON.stringify(readingsJSONWelcome), 0, 0);

  // xTaskCreatePinnedToCore(forceSensorTask, "Force Sensor Task", 8192, NULL, 1, &forceSensorTaskHandle, 0);
  // xTaskCreatePinnedToCore(batteryTask, "Battery Task", 8192, NULL, 1, &batteryTaskHandle, 0);
  // xTaskCreatePinnedToCore(mpuTask, "MPU Task", 8192, NULL, 1, &gyroTaskHandle, 1);
  // xTaskCreatePinnedToCore(gyroTask, "Gyro Task", 8192, NULL, 1, &gyroTaskHandle, 1);
  // xTaskCreatePinnedToCore(accTask, "Acc Task", 8192, NULL, 1, &accTaskHandle, 1);
  // xTaskCreatePinnedToCore(tempTask, "Temp Task", 8192, NULL, 1, &tempTaskHandle, 1);
}

void loop() {
  getBatteryVoltage();
  readForceSensors();
  getGyroReadings();
  getAccReadings();
  getTemperature();
  delay(10);  // give watchdog a breath

  if (shouldSleep()) {
    Serial.println("No pressure detected — entering deep sleep...");
    readingsJSONWelcome["msg"] = "Enter Light Sleep Mode";
    readingsJSONWelcome["isError"] = false;
    upload("uok/iot/nt375/smart_shoe/info", JSON.stringify(readingsJSONWelcome), 0, 0);
    // esp_deep_sleep_start();
    esp_light_sleep_start();
    delay(100);  // allow print to finish
  }
}
