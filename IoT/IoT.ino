#include "ble_manager.h"
#include "sensor_manager.h"

void setup()
{
  Serial.begin(115200);
  setupBLE();
  setupForceSensors();
  setupMPU();

  analogReadResolution(12);
}

void loop()
{
  readForceSensors();
  getAccelerometer();
  getBatteryVoltage();

  delay(1000);
}
