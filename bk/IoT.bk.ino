#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Force Sensor Pins
#define FORCE_SENSOR_FRONT A2
#define FORCE_SENSOR_MIDDLE A3
#define FORCE_SENSOR_HEEL A4

// WiFi Credentials (Stored in Flash Memory)
const char SSID[] PROGMEM = "napatchol's Galaxy Note10+";
const char WIFI_PWD[] PROGMEM = "napatchol";

// MQTT Configuration
#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT 1883

const char MQTT_FALL_TOPIC[] PROGMEM = "uok/iot/nt375/smart_shoe/fall";
const char MQTT_STEP_TOPIC[] PROGMEM = "uok/iot/nt375/smart_shoe/step";
const char MQTT_FORCE_TOPIC[] PROGMEM = "uok/iot/nt375/smart_shoe/force";
const char MQTT_UNBALANCE_TOPIC[] PROGMEM = "uok/iot/nt375/smart_shoe/unbalance";
const char MQTT_RESET_TOPIC[] PROGMEM = "uok/iot/nt375/smart_shoe/reset_step";

// MQTT Client
WiFiClient espClient;
PubSubClient client(espClient);

// MPU Setup
const int MPU = 0x68;
int16_t AcX, AcY, AcZ;

// Thresholds
int stepThreshold = 400;
int unevenThreshold = 80;
float fallThresholdLow = 0.4;
float fallThresholdHigh = 2.0;

bool isStep = false;
int stepCount = 0;

int lastValidFront = 0, lastValidMiddle = 0, lastValidHeel = 0;

void resetStepCount() {
  stepCount = 0;
  client.publish(MQTT_STEP_TOPIC, "0");
}

// Callback function to handle MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];  // Convert payload to string
  }

  Serial.print("Received message: ");
  Serial.println(String(topic) == MQTT_RESET_TOPIC);

  if (String(topic) == MQTT_RESET_TOPIC) {
    resetStepCount();
  }
}

int readForceSensor(int pin, int& lastValid) {
  int rawValue = analogRead(pin);

  if (rawValue < stepThreshold && lastValid == 0) {  // Ignore single sudden jumps
    return 0;
  }

  lastValid = (rawValue < stepThreshold) ? 0 : rawValue;  // Store the last valid value
  return lastValid;
}

void stepTracking(int frontForce, int heelForce) {
  if (heelForce > stepThreshold && frontForce > stepThreshold) {
    if (!isStep) {
      stepCount++;
      client.publish(MQTT_STEP_TOPIC, String(stepCount).c_str());
      isStep = true;
    }
  } else {
    isStep = false;
  }
}

void unevenWeightDetection(int frontForce, int middleForce, int heelForce) {
  int totalForce = frontForce + middleForce + heelForce;
  if (totalForce == 0) return;  // Avoid division by zero

  float frontRatio = (float)frontForce / totalForce * 100;
  float heelRatio = (float)heelForce / totalForce * 100;

  if (frontRatio > unevenThreshold) {
    client.publish(MQTT_UNBALANCE_TOPIC, "⚠️ Too much weight on the front!");
  } else if (heelRatio > unevenThreshold) {
    client.publish(MQTT_UNBALANCE_TOPIC, "⚠️ Too much weight on the heel!");
  }
}

void fallDetection() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  float acceleration = sqrt(AcX * AcX + AcY * AcY + AcZ * AcZ) / 16384.0;

  if (acceleration < fallThresholdLow || acceleration > fallThresholdHigh) {
    client.publish(MQTT_FALL_TOPIC, "Fall Detected!");
  }
}


void setupWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(SSID, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
}

void setupMQTT() {
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);  // Assign the callback function

  while (!client.connected()) {
    if (client.connect("SmartShoeClient")) {
      Serial.println("MQTT connected.");
      client.subscribe(MQTT_RESET_TOPIC);  // Subscribe to the reset topic
      Serial.print("Subscribed to ");
      Serial.print(MQTT_RESET_TOPIC);
      Serial.println(" topic.");
    } else {
      Serial.printf("failed , rc=%d try again in 5 seconds", client.state());
      Serial.println();
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  setupWiFi();
  setupMQTT();
}

void sendForceData(int frontForce, int middleForce, int heelForce) {
  char bleData[18];
  snprintf(bleData, sizeof(bleData), "%d,%d,%d", frontForce, middleForce, heelForce);
  client.publish(MQTT_FORCE_TOPIC, bleData);
  // Serial.println(bleData);
}

void loop() {
  client.loop();

  int frontForce = readForceSensor(FORCE_SENSOR_FRONT, lastValidFront);
  int middleForce = readForceSensor(FORCE_SENSOR_MIDDLE, lastValidMiddle);
  int heelForce = readForceSensor(FORCE_SENSOR_HEEL, lastValidHeel);


  sendForceData(frontForce, middleForce, heelForce);
  unevenWeightDetection(frontForce, middleForce, heelForce);
  stepTracking(frontForce, heelForce);
  fallDetection();
  delay(100);
}
