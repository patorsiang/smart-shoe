#include <WiFi.h>
#include <NimBLEDevice.h>
#include <esp_heap_caps.h>

const char *ssid = "napatchol's Galaxy Note10+";
const char *password = "napatchol";

NimBLEServer *pServer;

class MyServerCallbacks : public NimBLEServerCallbacks {
public:
    void onConnect (NimBLEServer *pServer, NimBLEConnInfo &connInfo) override {
        Serial.println("BLE Device Connected!");
    }

    void onDisconnect (NimBLEServer *pServer, NimBLEConnInfo &connInfo, int reason) override {
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
  NimBLECharacteristic *sensorCharacteristic = pService->createCharacteristic(
    "abcdef01-1234-5678-1234-56789abcdef1",
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

  pService->start();

  // Start BLE Advertising
  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("12345678-1234-5678-1234-56789abcdef2");
  pAdvertising->start();
  Serial.println("BLE Advertising Started");

  // Check available memory
  Serial.print("Free memory: ");
  Serial.println(heap_caps_get_free_size(MALLOC_CAP_8BIT));
}

void loop() {
  // Your application logic here
  delay(1000);
}
