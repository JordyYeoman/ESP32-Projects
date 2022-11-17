// Coding Kingth Rider LED animation using a shift register and demo on tinkercad
// Link: https://www.tinkercad.com/things/1d5G7bvJaR7-fantastic-vihelmo-leelo/editel?tenant=circuits
#include <Arduino.h>

int data_pin = 2;
int clock_pin = 3;
int latch_pin = 4;

void setup()
{
    pinMode(data_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);
    pinMode(latch_pin, OUTPUT);
}

void shiftDisplay(byte data)
{
    digitalWrite(latch_pin, LOW);
    shiftOut(data_pin, clock_pin, LSBFIRST, data);
    digitalWrite(latch_pin, HIGH);
}

void loop()
{
    byte x = B00000001; // 1 Byte AKA 8 bits of data
    // 'B' tells arduino that we are writing a number in binary
    for (int i = 0; i < 8; i++)
    {
        if (i == 7)
        {
            for (int k = 0; k < 8; k++)
            {
                shiftDisplay(x);
                x = x >> 1;
                delay(200);
            }
        }
        shiftDisplay(x);
        x = x << 1; // Secret sauce to shift all bits to the right, moving our 1 bit by 1 to the right.
        delay(200);
    }
}