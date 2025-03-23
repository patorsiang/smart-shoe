#include "ble_manager.h"
#include "sensor_manager.h"

void setup() {
  Serial.begin(115200);
  setupBLE();
  setupForceSensors();
  setupMPU();
}

void loop() {
  readForceSensors();
  getAccelerometer();

  delay(1000);
}
