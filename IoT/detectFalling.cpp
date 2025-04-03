#include "detectFalling.h"
#include "global_params.h"

static double lastAccMagnitude = 0;

void detectFalling()
{
  double accX = (double)readingsJSONAcc["x"];
  double accY = (double)readingsJSONAcc["y"];
  double accZ = (double)readingsJSONAcc["z"];
  double accMagnitude = sqrt(accX * accX + accY * accY + accZ * accZ);

  double gyroX = (double)readingsJSONGyro["x"];
  double gyroY = (double)readingsJSONGyro["y"];
  double gyroZ = (double)readingsJSONGyro["z"];
  double rotationMagnitude = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ);

  String debug = "accMagnitude: " + String(accMagnitude) + " rotationMagnitude: " + String(rotationMagnitude);
  Serial.println(debug);
  upload(String(FALL_TOPIC) + "_log", debug, 0, 0);
  if ((accMagnitude > FALLING_ACCEL_DETECTION_THRESHOLD_HIGH || accMagnitude < FALLING_ACCEL_DETECTION_THRESHOLD_LOW) && rotationMagnitude > FALLING_ROTATION_DETECTION_THRESHOLD)
  {
    lastAccMagnitude = accMagnitude;
    readingsJSONInfo["title"] = "⚠️ Warning: Possible Fall Detection!";
    // readingsJSONInfo["msg"] = debug;
    readingsJSONInfo["msg"] = "A possible fall has been detected. Please check on the elder under your care.";
    readingsJSONInfo["type"] = "warning";
    lastUploadFall = upload(INFO_TOPIC, JSON.stringify(readingsJSONInfo), lastUploadFall, uploadIntervalFall);
  }
  else
  {
    lastAccMagnitude = 0;
  }
}
