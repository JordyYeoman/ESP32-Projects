#include <ESP32Servo.h>
#include <Arduino.h>

int servoPin = 12;
int servoPos = 0;
Servo servo; // create servo object to control a servo
// 16 servo objects can be created on the ESP32

void setup()
{
  Serial.begin(115200);
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo.setPeriodHertz(50);           // standard 50 hz servo
  servo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object
                                      // using default min/max of 1000us and 2000us
                                      // different servos may require different min/max settings
                                      // for an accurate 0 to 180 sweep
}

void loop()
{
  Serial.println("Systems online and ready!");
  for (servoPos = 0; servoPos <= 180; servoPos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.println(servoPos);
    servo.write(servoPos); // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  for (servoPos = 180; servoPos >= 0; servoPos -= 1)
  { // goes from 180 degrees to 0 degrees
    Serial.println(servoPos);
    servo.write(servoPos); // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
}