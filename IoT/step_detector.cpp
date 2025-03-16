#include "step_detector.h"
#include "sensor_manager.h"
#include "ble_manager.h"
#include <Arduino.h>

bool stepActive = false;
int stepCount = 0;
unsigned long lastStepTime = 0;

void detectStep(int foreForce, int heelForce)
{
  float accMagnitude = readMPU(); // Get acceleration magnitude

  // 🔧 Lowered Thresholds for Better Step Detection
  if (!stepActive && heelForce > STEP_THRESHOLD && accMagnitude > MPU_ACC_THRESHOLD &&
      (millis() - lastStepTime > STEP_DEBOUNCE_TIME))
  {
    stepActive = true;
    stepCount++;
    lastStepTime = millis();

    Serial.printf("👣 Step %d Detected! Acceleration: %.2f G\n", stepCount, accMagnitude);

    // Send step count via BLE
    stepChar->setValue(stepCount);
    stepChar->notify();
  }

  // Reset step detection when toe-off occurs
  if (stepActive && foreForce < 500) // Reduce toe-off threshold
  {
    stepActive = false;
    Serial.println("🏁 Step Ended");
  }
}
