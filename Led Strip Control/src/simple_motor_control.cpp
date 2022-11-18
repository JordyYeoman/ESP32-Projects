#include <Arduino.h>
// Motor 1
int pwm_pin_motor_1 = 3;
int dir_1a_pin = 4;
int dir_2a_pin = 5;

// Motor 2
int pwm_pin_motor_2 = 6;
int dir_3a_pin = 7;
int dir_4a_pin = 8;

void setup()
{
    pinMode(pwm_pin_motor_1, OUTPUT);
    pinMode(dir_1a_pin, OUTPUT);
    pinMode(dir_2a_pin, OUTPUT);
    pinMode(pwm_pin_motor_2, OUTPUT);
    pinMode(dir_3a_pin, OUTPUT);
    pinMode(dir_4a_pin, OUTPUT);
}

void loop()
{
    // One direction at half speed
    digitalWrite(dir_1a_pin, HIGH); // M1
    digitalWrite(dir_3a_pin, HIGH); // M2
    digitalWrite(dir_2a_pin, LOW);  // M1
    digitalWrite(dir_4a_pin, LOW);  // M2
    analogWrite(pwm_pin_motor_1, 127);
    analogWrite(pwm_pin_motor_2, 127);
    delay(1000);

    // Stop pinning
    analogWrite(pwm_pin_motor_1, 0);
    analogWrite(pwm_pin_motor_2, 0);
    delay(1000);

    // Other direction at full speed
    digitalWrite(dir_1a_pin, LOW);
    digitalWrite(dir_3a_pin, LOW);
    digitalWrite(dir_2a_pin, HIGH);
    digitalWrite(dir_4a_pin, HIGH);
    analogWrite(pwm_pin_motor_1, 255);
    analogWrite(pwm_pin_motor_2, 255);
    delay(1000);

    // Brake
    digitalWrite(dir_1a_pin, LOW);
    digitalWrite(dir_3a_pin, LOW);
    digitalWrite(dir_2a_pin, LOW);
    digitalWrite(dir_4a_pin, LOW);
    analogWrite(pwm_pin_motor_1, 0);
    analogWrite(pwm_pin_motor_2, 0);
    delay(1000);
}