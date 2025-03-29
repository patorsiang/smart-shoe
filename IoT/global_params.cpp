#include "global_params.h"

float smoothVoltage = 3.7; // starting guess
unsigned long lastUploadBattery = 0;
const unsigned long uploadIntervalBattery = 300000; // every 5 mins
JSONVar readingsJSONInfo;
JSONVar readingsJSONForce;
JSONVar readingsJSONGyro;
JSONVar readingsJSONAcc;
