#include "step_detector.h"
#include "sensor_manager.h"
#include "ble_manager.h"

bool stepActive = false;
int stepCount = 0;
unsigned long lastStepTime = 0;

void detectStep(int foreForce, int heelForce)
{
  static int lastForeForce = 0, lastHeelForce = 0;

  // Compute % change in force from the last step
  float foreChange = (abs(foreForce - lastForeForce) * 100.0) / max(lastForeForce, 1);
  float heelChange = (abs(heelForce - lastHeelForce) * 100.0) / max(lastHeelForce, 1);

  // If either front or heel force increases by STEP_PERCENT_THRESHOLD
  if ((foreChange > STEP_PERCENT_THRESHOLD || heelChange > STEP_PERCENT_THRESHOLD) &&
      getAccelerometer() > MPU_ACC_THRESHOLD)
  {
    stepCount++;
    lastStepTime = millis();

    Serial.printf("👣 Step %d Detected! Pressure Change: Fore %.1f%% | Heel %.1f%%\n",
                  stepCount, foreChange, heelChange);

    stepChar->setValue(stepCount);
    stepChar->notify();
  }

  // Update last known forces
  lastForeForce = foreForce;
  lastHeelForce = heelForce;
}
