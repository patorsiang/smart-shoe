#include "mpu.h"

// Create a sensor object
Adafruit_MPU6050 mpu;

// Json Variable to Hold Sensor readingsJSON
JSONVar readingsJSONGyro;
JSONVar readingsJSONAcc;

sensors_event_t a, g, temp;

float gyroX, gyroY, gyroZ;
float accX, accY, accZ;
float temperature;

// Gyroscope sensor deviation
float gyroXerror = 0.07;
float gyroYerror = 0.03;
float gyroZerror = 0.01;

// Timer variables
unsigned long lastUploadGyro = 0;
unsigned long lastUploadTemp = 0;
unsigned long lastUploadAcc = 0;
unsigned long uploadIntervalGyro = 15000 + (esp_random() % 3000);
unsigned long uploadIntervalTemp = 15000 + (esp_random() % 3000);
unsigned long uploadIntervalAcc = 15000 + (esp_random() % 3000);

// Init MPU6050
void initMPU()
{
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
}

void getGyroReadings()
{
  mpu.getEvent(&a, &g, &temp);

  float gyroX_temp = g.gyro.x;
  if (abs(gyroX_temp) > gyroXerror)
  {
    gyroX += gyroX_temp / 50.00;
  }

  float gyroY_temp = g.gyro.y;
  if (abs(gyroY_temp) > gyroYerror)
  {
    gyroY += gyroY_temp / 70.00;
  }

  float gyroZ_temp = g.gyro.z;
  if (abs(gyroZ_temp) > gyroZerror)
  {
    gyroZ += gyroZ_temp / 90.00;
  }

  readingsJSONGyro["x"] = gyroX;
  readingsJSONGyro["y"] = gyroY;
  readingsJSONGyro["z"] = gyroZ;

  String jsonString = JSON.stringify(readingsJSONGyro);
  Serial.println(jsonString);
  gyroChar->setValue(jsonString);
  gyroChar->notify();
  lastUploadGyro = upload("uok/iot/nt375/smart_shoe/gyro", jsonString, lastUploadGyro, uploadIntervalGyro);
}

void getTemperature()
{
  mpu.getEvent(&a, &g, &temp);
  temperature = temp.temperature;
  Serial.print("Temperature: ");
  Serial.println(temperature);
  tempChar->setValue(temperature);
  tempChar->notify();
  lastUploadTemp = upload("uok/iot/nt375/smart_shoe/temp", String(temperature), lastUploadTemp, uploadIntervalTemp);
}

void getAccReadings()
{
  mpu.getEvent(&a, &g, &temp);
  // Get current acceleration values
  accX = a.acceleration.x;
  accY = a.acceleration.y;
  accZ = a.acceleration.z;
  readingsJSONAcc["x"] = accX;
  readingsJSONAcc["y"] = accY;
  readingsJSONAcc["z"] = accZ;
  String jsonString = JSON.stringify(readingsJSONAcc);
  Serial.println(jsonString);
  accChar->setValue(readingsJSONAcc);
  accChar->notify();
  lastUploadAcc = upload("uok/iot/nt375/smart_shoe/acc", jsonString, lastUploadAcc, uploadIntervalAcc);
}
