#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

void WiFiSetUp();
void connectToMQTT();
unsigned long upload(String topic, String payload, unsigned long lastUpload, unsigned long uploadInterval);

extern PubSubClient client;

#endif
