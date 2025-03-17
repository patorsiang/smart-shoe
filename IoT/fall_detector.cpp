#include "fall_detector.h"
#include "wifi_manager.h"
#include "sensor_manager.h"
#include "ble_manager.h"

static int16_t lastAcX = 0;
static float baselineAccMagnitude = 1.00;
static unsigned long lastBaselineUpdate = 0;

void detectFall()
{
    float accMagnitude = readMPU(); // Get total acceleration magnitude

    getCalibratedAccelerometer();

    // Compute % Increase in Forward Acceleration
    float tripIncrease = (abs(AcX - lastAcX) * 100.0) / max(abs(lastAcX), 1);

    // Dynamic Acceleration Threshold (Adapts Over Time)
    float dynamicThreshold = baselineAccMagnitude * 1.5;

    // Detect "Tripped"
    if (tripIncrease > TRIP_PERCENT_THRESHOLD && accMagnitude > dynamicThreshold)
    {
        Serial.printf("⚠️ [WARNING] Tripped! Forward Acceleration Increased by %.1f%%\n", tripIncrease);

        // BLE Notify
        stepChar->setValue("Tripped");
        stepChar->notify();

        // MQTT Emergency Alert (Wi-Fi needed)
        if (WiFi.status() == WL_CONNECTED)
        {
            client.publish("uok/iot/nt375/smart_shoe/fall_alert", "Tripped Detected!");
            Serial.println("📡 Emergency Alert Sent!");
        }

        // Update Last Known X-Axis Acceleration Only When Tripping Happens
        lastAcX = AcX;
    }

    // Compute % Drop for Fall Detection (Using Dynamic Baseline)
    float dropPercent = ((baselineAccMagnitude - accMagnitude) * 100.0) / baselineAccMagnitude;

    if (dropPercent > FALL_PERCENT_THRESHOLD)
    {
        Serial.println("🚨 [ALERT] Fall Detected! Significant Drop in Acceleration.");

        stepChar->setValue("Fell!");
        stepChar->notify();

        if (WiFi.status() == WL_CONNECTED)
        {
            client.publish("uok/iot/nt375/smart_shoe/fall_alert", "Emergency Fall Detected!");
            Serial.println("📡 Emergency Alert Sent!");
        }
    }

    // Update Baseline Acceleration Every 5 Sec
    if (millis() - lastBaselineUpdate > 5000)
    {
        baselineAccMagnitude = accMagnitude; // Reset baseline to adapt over time
        lastBaselineUpdate = millis();
        Serial.printf("🔄 Baseline Acceleration Updated: %.2f G\n", baselineAccMagnitude);
    }
}
