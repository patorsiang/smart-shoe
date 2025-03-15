#include "wifi_manager.h"

#define SSID "napatchol's Galaxy Note10+"
#define WIFI_PWD "napatchol"

WiFiClient espClient;
PubSubClient client(espClient);

void WiFiSetUp() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("Connecting to " SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WIFI_PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  Serial.println("Connecting to " MQTT_BROKER);
  while (!client.connected()) {
    if (client.connect(("ESP32-" + String(random(0xffff), HEX)).c_str())) {
      Serial.println("MQTT connected.");
    } else {
      Serial.printf("Failed, rc=%d, try again in 5 seconds\n", client.state());
      delay(5000);
    }
  }
}
