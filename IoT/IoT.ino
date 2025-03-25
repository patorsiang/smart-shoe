#include "ble_manager.h"
#include "multithreaded.h"
#include "wifi_manager.h"


void setup() {
  Serial.begin(115200);
  setupBLE();
  setupForceSensors();
  setupMPU();
  WiFiSetUp();
  connectToMQTT();

  analogReadResolution(12);

  // xTaskCreatePinnedToCore(forceSensorTask, "Force Sensor Task", 4096, NULL, 1, &forceSensorTaskHandle, 1);
  // xTaskCreatePinnedToCore(mpuTask, "MPU Task", 4096, NULL, 1, &mpuTaskHandle, 1);
  // xTaskCreatePinnedToCore(batteryTask, "Battery Task", 4096, NULL, 1, &batteryTaskHandle, 1);
}

void loop() {
}
