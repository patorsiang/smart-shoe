#include "wifi_manager.h"
#include "sensor_manager.h"
#include "imbalance_detector.h"
#include "fall_detector.h"
#include "ble_manager.h"

void setup()
{
  Serial.begin(115200);
  WiFiSetUp();

  // Handle MQTT connection
  client.setServer(MQTT_BROKER, MQTT_PORT);

  reconnectMQTT();
  setupBLE();
  setupForceSensors();
  setupMPU();
  getAccelerometer();
}

void loop()
{
  readForceSensors();
  if (millis() - lastUploadTime >= uploadInterval)
  {
    uploadData();
    lastUploadTime = millis();
  }
  detectFall();
  delay(1000);
}
