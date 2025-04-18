#include "battery.h"
#include "global_params.h"

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

void getBatteryVoltage()
{
  // Adafruit ESP32 Feather uses a 100K + 100K divider inside
  float batteryVoltage = readBatteryVoltage();

  // Exponential Moving Average filter
  smoothVoltage = (0.9 * smoothVoltage) + (0.1 * batteryVoltage); // EMA filter

  // Mapping voltage to percentage:
  // 4.15V = 100% (fully charged), 3.30V = 0% (safe minimum for LiPo)
  int batteryPercent = map(smoothVoltage * 100, 330, 415, 0, 100);
  batteryPercent = constrain(batteryPercent, 0, 100);

  Serial.print("V | Battery Percent: ");
  Serial.print(batteryPercent);
  Serial.println(" %");

  String batteryPercentString = String(batteryPercent);
  batteryChar->setValue(batteryPercentString);
  batteryChar->notify();

  lastUploadBattery = upload(BATTERY_TOPIC, batteryPercentString, lastUploadBattery, uploadIntervalBattery);
}
