#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT (1883)

void WiFiSetUp();
void reconnectMQTT();

extern PubSubClient client;

#endif
