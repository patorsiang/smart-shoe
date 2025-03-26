#include "force.h"

int sensorPins[SENSOR_COUNT] = {A2, A3, A4};
int readings[SENSOR_COUNT][3];

JSONVar readingsJSON;

unsigned long lastUploadForce = 0;
const unsigned long uploadIntervalForce = 15000 + (esp_random() % 3000); // every 10 secs

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
    readingsJSON[String(i)] = filteredValue;
  }

  String jsonString = JSON.stringify(readingsJSON);
  forceChar->setValue(jsonString);
  lastUploadForce = upload("uok/iot/nt375/smart_shoe/forces", jsonString, lastUploadForce, uploadIntervalForce);
}
