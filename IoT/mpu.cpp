#include "mpu.h"
#include "global_params.h"

// Create a sensor object
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

float gyroX, gyroY, gyroZ;
float accX, accY, accZ;
float temperature;

float accXOffset = 0.0, accYOffset = 0.0, accZOffset = 0.0;
float gyroXerror = 0.0, gyroYerror = 0.0, gyroZerror = 0.0;

void calibrateMPU(int samples)
{
  float gx = 0, gy = 0, gz = 0;
  float ax = 0, ay = 0, az = 0;

  Serial.println("Calibrating MPU... Please keep the device still.");
  for (int i = 0; i < samples; i++)
  {
    updateMPUEvents();
    gx += g.gyro.x;
    gy += g.gyro.y;
    gz += g.gyro.z;

    ax += a.acceleration.x;
    ay += a.acceleration.y;
    az += a.acceleration.z;
    delay(5);
  }

  // store average offsets
  gyroXerror = gx / samples;
  gyroYerror = gy / samples;
  gyroZerror = gz / samples;

  accXOffset = ax / samples;
  accYOffset = ay / samples - 9.81;
  accZOffset = az / samples;

  Serial.println("Calibration complete.");
}

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
  calibrateMPU();
}

void getGyroReadings()
{
  float gyroX_temp = g.gyro.x;

  if (abs(gyroX_temp - gyroXerror) > 0.01)
  {
    // simple low-pass filter (smoothing)
    gyroX = (gyroX * 0.9) + ((gyroX_temp - gyroXerror) * 0.1);
  }

  float gyroY_temp = g.gyro.y;
  if (abs(gyroY_temp - gyroYerror) > 0.01)
  {
    gyroY = (gyroY * 0.9) + ((gyroY_temp - gyroYerror) * 0.1);
  }

  float gyroZ_temp = g.gyro.z;
  if (abs(gyroZ_temp - gyroZerror) > 0.01)
  {
    gyroZ = (gyroZ * 0.9) + ((gyroZ_temp - gyroZerror) * 0.1);
  }

  readingsJSONGyro["x"] = gyroX;
  readingsJSONGyro["y"] = gyroY;
  readingsJSONGyro["z"] = gyroZ;

  String jsonString = JSON.stringify(readingsJSONGyro);
  Serial.println(jsonString);
  gyroChar->setValue(jsonString);
  gyroChar->notify();
  lastUploadGyro = upload(GYRO_TOPIC, jsonString, lastUploadGyro, uploadIntervalGyro);
}

void getTemperature()
{
  temperature = temp.temperature;
  Serial.print("Temperature: ");
  Serial.println(temperature);
  tempChar->setValue(temperature);
  tempChar->notify();
  lastUploadTemp = upload(TEMP_TOPIC, String(temperature), lastUploadTemp, uploadIntervalTemp);
}

void getAccReadings()
{
  // Get current acceleration values
  // Apply offsets
  accX = a.acceleration.x - accXOffset;
  accY = a.acceleration.y - accYOffset;
  accZ = a.acceleration.z - accZOffset;

  readingsJSONAcc["x"] = accX;
  readingsJSONAcc["y"] = accY;
  readingsJSONAcc["z"] = accZ;
  String jsonString = JSON.stringify(readingsJSONAcc);
  Serial.println(jsonString);
  accChar->setValue(jsonString);
  accChar->notify();
  lastUploadAcc = upload(ACC_TOPIC, jsonString, lastUploadAcc, uploadIntervalAcc);
}

void updateMPUEvents()
{
  mpu.getEvent(&a, &g, &temp);
}
