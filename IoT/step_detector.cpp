#include "step_detector.h"
#include "sensor_manager.h"
#include "ble_manager.h"
#include <Arduino.h>

#define STEP_THRESHOLD 800
#define STEP_DEBOUNCE_TIME 300
#define MPU_ACC_THRESHOLD 2.0 // Acceleration threshold for detecting steps

bool stepActive = false;
int stepCount = 0;
unsigned long lastStepTime = 0;

void detectStep(int foreForce, int heelForce)
{

  float accMagnitude = readMPU(); // Get motion data

  if (!stepActive && heelForce > STEP_THRESHOLD && accMagnitude > MPU_ACC_THRESHOLD && (millis() - lastStepTime > STEP_DEBOUNCE_TIME))
  {
    stepActive = true;
    Serial.println("👣 Step Detected!");
    stepCount++;
    lastStepTime = millis();

    stepChar->setValue(stepCount);
    stepChar->notify();
  }

  if (stepActive && foreForce < (STEP_THRESHOLD / 2))
  {
    stepActive = false;
    Serial.println("🏁 Step Ended");
  }
}
