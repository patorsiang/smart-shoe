#include "wifi_manager.h"
#include "global_params.h"

WiFiClient espClient;
PubSubClient client(espClient);

void WiFiSetUp()
{
  if (WiFi.status() == WL_CONNECTED)
    return;

  Serial.print("Connecting to " SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WIFI_PWD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToMQTT()
{
  const int maxRetries = 5;
  int retryCount = 0;
  client.setServer(MQTT_BROKER, MQTT_PORT); // set broker settings
  Serial.println("Connecting to " MQTT_BROKER);
  while (!client.connected() && retryCount < maxRetries)
  {
    if (client.connect(("ESP32-" + String(random(0xffff), HEX)).c_str()))
    {
      Serial.println("MQTT connected.");
    }
    else
    {
      Serial.printf("Failed, rc=%d, try again in 5 seconds\n", client.state());
      retryCount++;
      delay(5000);
      WiFiSetUp();
    }
  }
}

void disconnect()
{
  WiFi.disconnect(true);
  delay(100); // Give some time to disconnect
  WiFi.mode(WIFI_OFF);
  delay(100); // Let the system shut down WiFi stack gracefully
  Serial.println("Wi-Fi OFF. Waiting for next upload...");
}

unsigned long upload(String topic, String payload, unsigned long lastUpload, unsigned long uploadInterval)
{
  if ((millis() - lastUpload > uploadInterval) || lastUpload == 0)
  {
    WiFiSetUp();
    connectToMQTT();
    bool result = client.publish(topic.c_str(), payload.c_str());
    if (result)
    {
      Serial.println("Data Uploaded: " + payload);
    }
    else
    {
      Serial.println("Failed to upload data.");
    }
    // delay(100); // Let MQTT transmission complete
    // disconnect();
    return millis();
  }
  return lastUpload;
}
