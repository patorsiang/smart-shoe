#include "sensor_manager.h"
#include "wifi_manager.h"

int sensorPins[SENSOR_COUNT] = {A2, A3, A4};
int readings[SENSOR_COUNT][3];

// MPU Setup
const int MPU = 0x68;
int16_t AcX, AcY, AcZ;
int16_t calibratedOffsetX, calibratedOffsetY, calibratedOffsetZ;

void setupForceSensors()
{
  for (int i = 0; i < SENSOR_COUNT; i++)
  {
    pinMode(sensorPins[i], INPUT);
  }
  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
  Serial.println("Set up Sensors");
}

int medianFilter(int index)
{
  int values[3] = {readings[index][0], readings[index][1], readings[index][2]};
  // Sort values (simple sorting method)
  for (int i = 0; i < 2; i++)
  {
    for (int j = i + 1; j < 3; j++)
    {
      if (values[i] > values[j])
      {
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }
  return values[1]; // Return median
}

void readForceSensors()
{
  int forePressure = 0, heelPressure = 0;

  for (int i = 0; i < SENSOR_COUNT; i++)
  {
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
    forceChar[i]->setValue((uint8_t *)&filteredValue, sizeof(filteredValue)); // Send as raw bytes
    forceChar[i]->notify();                                                   // Notify connected BLE devices
  }
}

void readAccelerometer()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
}

void setupMPU()
{
  Wire.begin();

  Serial.println("🔄 Resetting MPU6050...");

  // 🛠️ Hard Reset MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x80); // Reset bit
  Wire.endTransmission(true);
  delay(100); // Wait for reset

  // 🛠️ Wake up MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(100);

  // 🚀 Set Accelerometer to ±2g for best accuracy
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x00);
  Wire.endTransmission(true);

  // Compute Automatic Offset Calibration
  Serial.println("🔄 Calibrating MPU6050... Please keep the shoe still.");

  long sumX = 0, sumY = 0, sumZ = 0;
  const int samples = 500; // Increase samples for better accuracy

  for (int i = 0; i < samples; i++)
  {
    readAccelerometer(); // Read sensor values

    sumX += AcX;
    sumY += AcY;
    sumZ += AcZ;
    delay(5);
  }

  // Compute Correct Offsets
  calibratedOffsetX = sumX / samples;
  calibratedOffsetY = sumY / samples;
  calibratedOffsetZ = sumZ / samples - 16384; // Ensure proper gravity correction

  Serial.println("MPU6050 Auto-Calibrated!");
  Serial.printf("Offsets -> X: %d, Y: %d, Z: %d\n", calibratedOffsetX, calibratedOffsetY, calibratedOffsetZ);
}

float getAccelerometer()
{
  readCalibratedAccelerometer();

  Serial.printf("📊 Calibrated AcX: %d, AcY: %d, AcZ: %d\n", AcX, AcY, AcZ);

  // Convert to G-force (assuming ±2g range)
  float acceleration = sqrt(AcX * AcX + AcY * AcY + AcZ * AcZ) / 16384.0;

  Serial.printf("📊 Acceleration Magnitude: %.2f G\n", acceleration);
  return acceleration;
}

void readCalibratedAccelerometer()
{
  readAccelerometer();

  // Ensure Offsets Are Applied Correctly
  AcX -= calibratedOffsetX;
  AcY -= calibratedOffsetY;
  AcZ -= calibratedOffsetZ;

  // Update BLE characteristic
  int16_t values[3] = {AcX, AcY, AcZ};
  MPUChar->setValue((uint8_t *)values, sizeof(values));
  MPUChar->notify(); // Notify connected BLE devices
}

float readBatteryVoltage()
{
  long sum = 0;
  const int samples = 10;
  for (int i = 0; i < samples; i++)
  {
    sum += analogRead(VBAT_PIN); // or VBAT_PIN
    delay(5);                    // slight pause
  }
  float averageRaw = sum / (float)samples;
  float vADC = (averageRaw / 4095.0) * 3.3;

  Serial.print("Raw ADC: ");
  Serial.print(averageRaw);
  Serial.print(" | ADC Voltage: ");
  Serial.print(vADC, 2);

  return vADC * 2.0; // If using built-in divider
}

float smoothVoltage = 3.7; // starting guess
unsigned long lastUploadBattery = 0;
const unsigned long uploadIntervalBattery = 10000; // every 10 seconds

void getBatteryVoltage()
{
  // Adafruit ESP32 Feather uses a 100K + 100K divider inside
  float batteryVoltage = readBatteryVoltage();

  smoothVoltage = (0.9 * smoothVoltage) + (0.1 * batteryVoltage); // EMA filter

  int batteryPercent = map(smoothVoltage * 100, 300, 420, 0, 100);
  batteryPercent = constrain(batteryPercent, 0, 100);
  uint8_t batteryLevel = (uint8_t)batteryPercent;
  batteryChar->setValue(&batteryLevel, 1);
  batteryChar->notify();

  Serial.print("V | Battery Percent: ");
  Serial.print(batteryPercent);
  Serial.println(" %");

  lastUploadBattery = upload("uok/iot/nt375/smart_shoe/battery", String(batteryPercent), lastUploadBattery, uploadIntervalBattery);
}
