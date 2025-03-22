#include "fall_detector.h"
#include "wifi_manager.h"
#include "ble_manager.h"
#include "sensor_manager.h"

// Kalman filter variables
float kalmanAngleX = 0;
float kalmanAngleY = 0;
float kalmanAngleZ = 0;
float kalmanErrorX = 1, kalmanErrorY = 1, kalmanErrorZ = 1;
const float R_measure = 0.02; // Measurement noise
const float Q_angle = 0.01;   // Process noise

// Low-pass filter variables
#define ALPHA 0.6 // Low-pass filter smoothing factor

// Thresholds
#define FALL_THRESHOLD 1.2 // Fall acceleration threshold in G
#define TRIP_THRESHOLD 0.8 // Trip forward acceleration threshold in G

// Low-pass filter to reduce noise
float lowPassFilter(float newValue, float previousValue)
{
    return ALPHA * newValue + (1 - ALPHA) * previousValue;
}

// Kalman filter for smoother motion estimation
float kalmanFilter(float newAngle, float &kalmanAngle, float &kalmanError)
{
    kalmanAngle += Q_angle; // Predict
    kalmanError += Q_angle; // Update error

    float K = kalmanError / (kalmanError + R_measure); // Kalman gain
    kalmanAngle += K * (newAngle - kalmanAngle);
    kalmanError *= (1 - K); // Update error covariance

    return kalmanAngle;
}

// Fall detection logic
void detectFall()
{
    static float lastAcX = 0, lastAcY = 0, lastAcZ = 0;

    calibratedAccelerometer();

    AcX = lowPassFilter(AcX, lastAcX);
    AcY = lowPassFilter(AcY, lastAcY);
    AcZ = lowPassFilter(AcZ, lastAcZ);

    AcX = kalmanFilter(AcX, kalmanAngleX, kalmanErrorX);
    AcY = kalmanFilter(AcY, kalmanAngleY, kalmanErrorY);
    AcZ = kalmanFilter(AcZ, kalmanAngleZ, kalmanErrorZ);

    lastAcX = AcX;
    lastAcY = AcY;
    lastAcZ = AcZ;

    float acceleration = getAccelerometer();

    if (acceleration > FALL_THRESHOLD)
    {
        Serial.println("🚨 Fall Detected!");
        fallChar->setValue("Fall Detected!");
        fallChar->notify();

        if (WiFi.status() == WL_CONNECTED)
        {
            client.publish("smart_shoe/fall_alert", "Emergency Fall Detected!");
            Serial.println("📡 Emergency Alert Sent!");
        }
    }
}
