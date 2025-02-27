#include<Wire.h>

#define FORCE_SENSOR_PIN_A1 A1
#define FORCE_SENSOR_PIN_A2 A2
#define FORCE_SENSOR_PIN_A3 A3

const int MPU=0x68; 

int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  // Set the ADC attenuation to 11 dB (up to ~3.3V input) (ESP32 only)
  analogSetAttenuation(ADC_11db);
}

void forceSensor(int pin) {
  int analogReading = analogRead(pin);

  Serial.print("The force sensor value at pin ");
  Serial.print(pin);
  Serial.print(" = ");
  Serial.println(analogReading);

  if (analogReading < 10)       // from 0 to 9
    Serial.println(" -> no pressure");
  else if (analogReading < 200) // from 10 to 199
    Serial.println(" -> light touch");
  else if (analogReading < 500) // from 200 to 499
    Serial.println(" -> light squeeze");
  else if (analogReading < 800) // from 500 to 799
    Serial.println(" -> medium squeeze");
  else // from 800 to 1023
    Serial.println(" -> big squeeze");
}

void loop() {
  forceSensor(FORCE_SENSOR_PIN_A1);
  forceSensor(FORCE_SENSOR_PIN_A2);
  forceSensor(FORCE_SENSOR_PIN_A3);
  Serial.println("----------------------------"); // Separator for clarity
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = ");  Serial.println(AcZ); 

  Serial.print("Gyroscope: ");
  Serial.print("X  = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(1000);
}
