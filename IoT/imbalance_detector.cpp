#include "imbalance_detector.h"
#include "wifi_manager.h"
#include "sensor_manager.h"
#include "config.h" // Ensure SENSOR_COUNT is defined
#include <Arduino.h>

#define BALANCE_THRESHOLD 2000
#define MIN_IMBALANCE_TIME 30000
#define MQTT_UB_TOPIC "uok/iot/nt375/smart_shoe/unbalance"

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

void uploadData()
{
    WiFiSetUp();
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWi-Fi Connected!");
        reconnectMQTT();

        String payload = "{";
        for (int i = 0; i < SENSOR_COUNT; i++)
        {
            payload += "\"sensor_" + String(i) + "\":" + String(medianFilter(i));
            if (i < SENSOR_COUNT - 1)
                payload += ",";
        }

        payload += imbalanceDetected ? ",\"imbalance\":\"true\"}" : "\"imbalance\":\"false\"}";

        client.publish(MQTT_UB_TOPIC, payload.c_str());
        Serial.println("Data Uploaded: " + payload);

        delay(1000);
        WiFi.mode(WIFI_OFF);
        Serial.println("Wi-Fi OFF. Waiting for next upload...");
    }
    else
    {
        Serial.println("Wi-Fi Connection Failed!");
    }
}
