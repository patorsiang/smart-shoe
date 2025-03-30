#include "utils.h"
#include "global_params.h"

void detectStep()
{
  int front = getForce(0);
  int mid = getForce(1);
  int heel = getForce(2);

  double az = (double)readingsJSONAcc["z"];
  double deltaAz = abs(az - previousAz);
  previousAz = az;

  unsigned long now = millis();
  String debug = " Step " + String(stepCount) + "| Accel Z: " + String(deltaAz) + " g | Heel: " + String(heel) + "| Mid: " + String(mid) + "| Front: " + String(front);
  Serial.println(debug);

  if (deltaAz > ACCEL_THRESHOLD && heel > FORCE_THRESHOLD && mid > FORCE_THRESHOLD && front > FORCE_THRESHOLD && !stepDetected && (now - lastStepTime > DEBOUNCE_TIME))
  {
    stepDetected = true;
    lastStepTime = now;
    stepCount++;

    stepChar->setValue(String(stepCount));
    stepChar->notify();
  }

  if (heel < FORCE_THRESHOLD && mid < FORCE_THRESHOLD && front < FORCE_THRESHOLD)
  {
    stepDetected = false;
  }
  lastUploadStep = upload("uok/iot/nt375/smart_shoe/step", String(stepCount), lastUploadStep, uploadIntervalStep);
}
