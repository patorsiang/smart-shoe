#include <WiFi.h>
#include <NimBLEDevice.h>
#include <esp_heap_caps.h>

#define SENSOR_COUNT 3  // Number of force sensors

const char *ssid = "napatchol's Galaxy Note10+";
const char *password = "napatchol";

NimBLEServer *pServer;

int sensorPins[SENSOR_COUNT] = { A2, A3, A4 };
int readings[SENSOR_COUNT][3];  // Store last 3 readings for each sensor
NimBLECharacteristic *forceChar[SENSOR_COUNT];

class MyServerCallbacks : public NimBLEServerCallbacks {
public:
  void onConnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo) override {
    Serial.println("BLE Device Connected!");
  }

  void onDisconnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo, int reason) override {
    Serial.println("BLE Device Disconnected!");
  }
};

void setup() {
  Serial.begin(115200);

  // Release Classic Bluetooth memory to free up RAM
  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);

  // Wi-Fi Setup
  Serial.print("Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wi-Fi Setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi Connected");

  // BLE Setup
  Serial.println("Starting BLE...");
  NimBLEDevice::init("nt375");

  // Set BLE power level (lower to reduce Wi-Fi interference)
  NimBLEDevice::setPower(ESP_PWR_LVL_P3);

  // Create BLE Server
  pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());  // Attach callback

  // Create BLE Service & Characteristic
  NimBLEService *pService = pServer->createService("12345678-1234-5678-1234-56789abcdef0");

  for (int i = 0; i < SENSOR_COUNT; i++) {
    char uuid[40];
    snprintf(uuid, sizeof(uuid), "abcdef0%d-1234-5678-1234-56789abcdef0", i);
    forceChar[i] = pService->createCharacteristic(uuid, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
  }

  pService->start();

  // Start BLE Advertising
  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("12345678-1234-5678-1234-56789abcdef2");
  pAdvertising->start();
  Serial.println("BLE Advertising Started");

  // Set up force sensor
  for (int i = 0; i < SENSOR_COUNT; i++) {
    pinMode(sensorPins[i], INPUT);  // Set sensor pins as input
  }

  // Check available memory
  Serial.print("Free memory: ");
  Serial.println(heap_caps_get_free_size(MALLOC_CAP_8BIT));
}

int medianFilter(int index) {
  int values[3] = { readings[index][0], readings[index][1], readings[index][2] };
  // Sort values (simple sorting method)
  for (int i = 0; i < 2; i++) {
    for (int j = i + 1; j < 3; j++) {
      if (values[i] > values[j]) {
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }
  return values[1];  // Return median
}

void readForceSensors() {
  for (int i = 0; i < SENSOR_COUNT; i++) {
    // Shift old values
    readings[i][2] = readings[i][1];
    readings[i][1] = readings[i][0];

    // Read new sensor value
    readings[i][0] = analogRead(sensorPins[i]);

    // Apply Median Filter
    int filteredValue = medianFilter(i);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(filteredValue);

    // Update BLE characteristic
    forceChar[i]->setValue((uint8_t *)&filteredValue, sizeof(filteredValue));  // Send as raw bytes
    forceChar[i]->notify();                                                    // Notify connected BLE devices
  }
}

void loop() {
  // Your application logic here
  readForceSensors();
  delay(1000);
}
