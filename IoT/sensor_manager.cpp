#include "sensor_manager.h"
#include "ble_manager.h"
#include "config.h"  // Ensure SENSOR_COUNT is defined
#include "imbalance_detector.h"
#include "step_detector.h"

#include <Arduino.h>
#include <Wire.h>

int sensorPins[SENSOR_COUNT] = { A2, A3, A4 };
int readings[SENSOR_COUNT][3];

// MPU Setup
const int MPU = 0x68;
int16_t AcX, AcY, AcZ;

void setupForceSensors() {
  for (int i = 0; i < SENSOR_COUNT; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  analogSetAttenuation(ADC_11db);
  Serial.println("Set up Sensors");
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
  int forePressure = 0, heelPressure = 0;

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

    // Simulate left and right force readings
    if (i == 0)
      forePressure = filteredValue;
    if (i == 2)
      heelPressure = filteredValue;

    // Update BLE characteristic
    forceChar[i]->setValue((uint8_t *)&filteredValue, sizeof(filteredValue));  // Send as raw bytes
    forceChar[i]->notify();                                                    // Notify connected BLE devices
  }

  detectUnevenWeight(forePressure, heelPressure);
  detectStep(forePressure, heelPressure);
}

void setupMPU() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

float readMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  float acceleration = sqrt(AcX * AcX + AcY * AcY + AcZ * AcZ) / 16384.0;

  Serial.printf("📊 Acceleration Magnitude: %.2f G\n", acceleration);

  return acceleration;
}
