// C++ code
//
/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

int ledPinNumbers[] = {2, 3, 4};
int delayTimeMS = 500;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    // Set all LED pins to OUTPUT
    for (int i : ledPinNumbers)
    {
        pinMode(i, OUTPUT);
    }
}

void loop()
{
    // For loop over led bundles
    for (int i : ledPinNumbers)
    {
        digitalWrite(i, HIGH);
        delay(delayTimeMS);
        // turn the LED off by making the voltage LOW
        digitalWrite(i, LOW);
        delay(delayTimeMS); // Wait for 1000 millisecond(s)
    }
}