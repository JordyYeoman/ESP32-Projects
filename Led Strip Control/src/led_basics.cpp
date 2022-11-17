#include <Arduino.h>

int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 10;
// Stores the PWM brightness values
int brightness1;
int brightness2;
int brightness3;
int brightness4;

void setup()
{
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
}

void updateLEDState(int onPin, int offPin)
{
    digitalWrite(onPin, HIGH);
    digitalWrite(offPin, LOW);
}

int getBrightnessForLEDValue(int brightness)
{
    if (brightness > 255)
    {
        return 255;
    }
    if (brightness < 0)
    {
        return 0;
    }
    return brightness;
}

void loop()
{
    for (int i = 0; i < 355; i++)
    {
        brightness1 = i;
        brightness2 = i - 50;
        brightness3 = i - 75;
        brightness4 = i - 100;

        brightness1 = getBrightnessForLEDValue(brightness1);
        brightness2 = getBrightnessForLEDValue(brightness2);
        brightness3 = getBrightnessForLEDValue(brightness3);
        brightness4 = getBrightnessForLEDValue(brightness4);

        // set LED brightness levels using analog write to create a PWM duty cycle
        analogWrite(led1, brightness1);
        analogWrite(led2, brightness2);
        analogWrite(led3, brightness3);
        analogWrite(led4, brightness4);

        delay(10);
    }
}