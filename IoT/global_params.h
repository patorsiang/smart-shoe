#ifndef GLOBAL_PARAMS_H
#define GLOBAL_PARAMS_H

#include <Arduino_JSON.h>

#define BLE_NAME "smart-shoe-nt375"

#define SSID "napatchol's Galaxy Note10+"
#define WIFI_PWD "napatchol"

#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT (1883)

#define SENSOR_COUNT 3 // Make SENSOR_COUNT available globally
#define STANDING_FORCE_THRESHOLD 200
#define FORCE_WAKEUP_THRESHOLD 100
#define BAD_POSTURE_DETECTION_NUM 150

extern float smoothVoltage;
extern unsigned long lastUploadBattery;
extern const unsigned long uploadIntervalBattery;
extern JSONVar readingsJSONInfo;
extern JSONVar readingsJSONForce;
extern JSONVar readingsJSONGyro;
extern JSONVar readingsJSONAcc;

#endif
