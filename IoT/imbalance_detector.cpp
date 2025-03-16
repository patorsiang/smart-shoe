#include "imbalance_detector.h"
#include "wifi_manager.h"
#include "sensor_manager.h"
#include "config.h" // Ensure SENSOR_COUNT is defined
#include <Arduino.h>

bool imbalanceDetected = false;
unsigned long imbalanceStartTime = 0;

unsigned long lastUploadTime = 0;
const unsigned long uploadInterval = 5 * 60 * 1000;

void detectUnevenWeight(int foreForce, int heelForce)
{
    int forceDifference = abs(foreForce - heelForce);
    if (forceDifference > BALANCE_THRESHOLD)
    {
        if (!imbalanceDetected)
        {
            imbalanceStartTime = millis();
            imbalanceDetected = true;
            Serial.println("⚠️ Possible Imbalance Detected... Checking Duration");
        }

        if (millis() - imbalanceStartTime >= MIN_IMBALANCE_TIME)
        {
            Serial.println("⚠️ [ALERT] Uneven Weight Detected!");
            uploadData();
        }
    }
    else
    {
        if (imbalanceDetected)
        {
            Serial.println("✔️ Balance Restored");
            imbalanceDetected = false;
        }
    }
}
