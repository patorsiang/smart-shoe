#include "global_params.h"

float smoothVoltage = 3.7; // starting guess
unsigned long lastUploadBattery = 0;
unsigned long lastUploadStep = 0;
unsigned long lastUploadForce = 0;
unsigned long lastUploadGyro = 0;
unsigned long lastUploadTemp = 0;
unsigned long lastUploadAcc = 0;
unsigned long lastUploadFall = 0;
unsigned long lastUploadUB = 0;
const unsigned long uploadIntervalBattery = 300000; // every 5 mins
const unsigned long uploadIntervalFall = 5000;      // every 5 sec
const unsigned long uploadIntervalUB = 5000;        // every 5 sec
const unsigned long uploadIntervalStep = 15000 + (esp_random() % 3000);
const unsigned long uploadIntervalForce = 15000 + (esp_random() % 3000);
const unsigned long uploadIntervalGyro = 15000 + (esp_random() % 3000);
const unsigned long uploadIntervalTemp = 15000 + (esp_random() % 3000);
const unsigned long uploadIntervalAcc = 15000 + (esp_random() % 3000);

double previousAx = 9.81;
int stepCount = 0;
bool stepDetected = false;
unsigned long lastStepTime = 0;

JSONVar readingsJSONInfo;
JSONVar readingsJSONForce;
JSONVar readingsJSONGyro;
JSONVar readingsJSONAcc;
