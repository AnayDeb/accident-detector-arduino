// Accident Detector using MPU6050 (Accelerometer) + Buzzer
// Author: Anay Deb
// Date: 2025-07-25

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int buzzerPin = 8;  // Buzzer connected to digital pin 8
const int impactThreshold = 20000; // Adjust this value as needed

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pinMode(buzzerPin, OUTPUT);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  long totalForce = ax * ax + ay * ay + az * az;

  Serial.print("Force: ");
  Serial.println(totalForce);

  if (totalForce > impactThreshold) {
    Serial.println("Impact Detected! Activating buzzer...");
    digitalWrite(buzzerPin, HIGH);
    delay(1000);  // Buzzer on for 1 second
    digitalWrite(buzzerPin, LOW);
    delay(1000);  // Wait before next reading
  }

  delay(200);
}
