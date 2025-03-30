#ifndef GLOBAL_PARAMS_H
#define GLOBAL_PARAMS_H

#include <Arduino_JSON.h>

#define BLE_NAME "smart-shoe-nt375"

#define SSID "napatchol's Galaxy Note10+"
#define WIFI_PWD "napatchol"

#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT (1883)

#define SENSOR_COUNT 3
#define FORCE_THRESHOLD 100
#define ACCEL_THRESHOLD 0.2
#define DEBOUNCE_TIME 300
#define BAD_POSTURE_DETECTION_NUM 150

extern float smoothVoltage;
extern unsigned long lastUploadBattery;
extern unsigned long lastUploadStep;
extern unsigned long lastUploadForce;
extern unsigned long lastUploadGyro;
extern unsigned long lastUploadTemp;
extern unsigned long lastUploadAcc;
extern const unsigned long uploadIntervalBattery;
extern const unsigned long uploadIntervalStep;
extern const unsigned long uploadIntervalForce;
extern unsigned long uploadIntervalGyro;
extern unsigned long uploadIntervalTemp;
extern unsigned long uploadIntervalAcc;

extern double previousAz;
extern int stepCount;
extern bool stepDetected;
extern unsigned long lastStepTime;

extern JSONVar readingsJSONInfo;
extern JSONVar readingsJSONForce;
extern JSONVar readingsJSONGyro;
extern JSONVar readingsJSONAcc;
#endif
