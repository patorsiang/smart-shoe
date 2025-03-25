#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

#define SSID "napatchol's Galaxy Note10+"
#define WIFI_PWD "napatchol"

#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT (1883)

void WiFiSetUp();
void connectToMQTT();
unsigned long upload(String topic, String payload, unsigned long lastUpload, unsigned long uploadInterval);
String formatData(bool isError, String payload);

extern PubSubClient client;

#endif
