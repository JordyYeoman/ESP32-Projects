#include <Arduino.h>

int ledPin = 32;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  Serial.println("New Loop started");
  digitalWrite(ledPin, HIGH); // turn on the LED
  delay(500);                 // wait for half a second or 500 milliseconds
  digitalWrite(ledPin, LOW);  // turn off the LED
  delay(500);                 // wait for half a second or 500 milliseconds
  delay(1500);
}