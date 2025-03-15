#include "wifi_manager.h"
#include "sensor_manager.h"
#include "imbalance_detector.h"
#include "step_detector.h"
#include "config.h" // Ensure SENSOR_COUNT is defined
#include <Arduino.h>

#define MQTT_UB_TOPIC "uok/iot/nt375/smart_shoe/unbalance"

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

        payload += "\"steps\":" + String(stepCount) + ",";

        payload += imbalanceDetected ? "\"imbalance\":\"true\"}" : "\"imbalance\":\"false\"}";

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
