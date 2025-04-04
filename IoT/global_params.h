#ifndef GLOBAL_PARAMS_H
#define GLOBAL_PARAMS_H

#include <Arduino_JSON.h>

#define BLE_NAME "smart-shoe-nt375"

#define SSID "napatchol's Galaxy Note10+"
#define WIFI_PWD "napatchol"

#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT (1883)

#define BATTERY_TOPIC "uok/iot/nt375/smart_shoe/battery"
#define FORCE_TOPIC "uok/iot/nt375/smart_shoe/forces"
#define GYRO_TOPIC "uok/iot/nt375/smart_shoe/gyro"
#define ACC_TOPIC "uok/iot/nt375/smart_shoe/acc"
#define TEMP_TOPIC "uok/iot/nt375/smart_shoe/temp"
#define FALL_TOPIC "uok/iot/nt375/smart_shoe/fall"
#define INFO_TOPIC "uok/iot/nt375/smart_shoe/info"
#define STEP_TOPIC "uok/iot/nt375/smart_shoe/step"

#define SENSOR_COUNT 3
#define FORCE_THRESHOLD 100
#define ACCEL_THRESHOLD 0.2
#define DEBOUNCE_TIME 300
#define BAD_POSTURE_DETECTION_NUM 150
#define FALLING_ACCEL_DETECTION_THRESHOLD_HIGH 35.0 // try increasing
#define FALLING_ACCEL_DETECTION_THRESHOLD_LOW 3.0   // already low is okay
#define FALLING_ROTATION_DETECTION_THRESHOLD 1.5    // increase this to ignore walking rotation

extern float smoothVoltage;
extern unsigned long lastUploadBattery;
extern unsigned long lastUploadStep;
extern unsigned long lastUploadForce;
extern unsigned long lastUploadGyro;
extern unsigned long lastUploadTemp;
extern unsigned long lastUploadAcc;
extern unsigned long lastUploadFall;
extern unsigned long lastUploadUB;
extern const unsigned long uploadIntervalUB;
extern const unsigned long uploadIntervalBattery;
extern const unsigned long uploadIntervalFall;
extern const unsigned long uploadIntervalStep;
extern const unsigned long uploadIntervalForce;
extern const unsigned long uploadIntervalGyro;
extern const unsigned long uploadIntervalTemp;
extern const unsigned long uploadIntervalAcc;

extern double previousAx;
extern int stepCount;
extern bool stepDetected;
extern unsigned long lastStepTime;

extern JSONVar readingsJSONInfo;
extern JSONVar readingsJSONForce;
extern JSONVar readingsJSONGyro;
extern JSONVar readingsJSONAcc;
#endif
