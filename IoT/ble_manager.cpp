#include "ble_manager.h"

NimBLECharacteristic *forceChar[SENSOR_COUNT];
NimBLECharacteristic *MPUChar;
NimBLECharacteristic *stepChar;
NimBLECharacteristic *fallChar;
NimBLECharacteristic *batteryChar;
NimBLECharacteristic *chargingChar;

class MyServerCallbacks : public NimBLEServerCallbacks
{
public:
  void onConnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo) override
  {
    Serial.println("BLE Device Connected!");
  }

  void onDisconnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo, int reason) override
  {
    Serial.println("BLE Device Disconnected!");
    pServer->startAdvertising(); // restart advertising
    Serial.println("Start advertising");
  }
};

void setupBLE()
{
  Serial.println("Starting BLE...");
  NimBLEDevice::init(BLE_NAME);
  NimBLEDevice::setPower(ESP_PWR_LVL_P3);

  NimBLEServer *pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  NimBLEService *pService = pServer->createService("12345678-1234-5678-1234-56789abcdef0");

  // Force Sensor BLE Characteristic
  for (int i = 0; i < SENSOR_COUNT; i++)
  {
    char uuid[40];
    snprintf(uuid, sizeof(uuid), "abcdef0%d-1234-5678-1234-56789abcdef0", i);
    forceChar[i] = pService->createCharacteristic(uuid, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
  }

  // MPU BLE Characteristic
  MPUChar = pService->createCharacteristic(
      "abcdef03-1234-5678-1234-56789abcdef0",
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

  // Step Counter BLE Characteristic
  stepChar = pService->createCharacteristic(
      "abcd1234-5678-90ab-cdef-1234567890ef",
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

  // Fall Counter BLE Characteristic
  fallChar = pService->createCharacteristic(
      "1234abcd-5678-90ab-cdef-1234567890ef",
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

  batteryChar = pService->createCharacteristic(
      "1234abcd-5678-90ab-cdef-12345678ef09",
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

  chargingChar = pService->createCharacteristic(
      "1234abcd-5678-90ab-cdef-12345678ef10",
      NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

  pService->start();

  NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID("12345678-1234-5678-1234-56789abcdef2");
  pAdvertising->start();
  Serial.printf("BLE Advertising Started: %s\n", BLE_NAME);
}
