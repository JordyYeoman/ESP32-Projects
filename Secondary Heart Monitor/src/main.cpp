#include <Arduino.h>

int sensorValue = 0;

void setup() {
  pinMode (2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Serial.println("LED ON");
  digitalWrite(2, HIGH);
  // delay(100);

  // read the analog in value
  sensorValue = analogRead(A0);
  // Serial.print("sensor = ");
  Serial.println(sensorValue);
  // delay(100);

  // Serial.println("LED OFF");
  digitalWrite(2, LOW);
  delay(25);
}