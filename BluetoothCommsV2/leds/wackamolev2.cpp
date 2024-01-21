int tDelay = 1000;
int latchPin = 10; // (11) ST_CP [RCK] on 74HC595
int clockPin = 11; // (9) SH_CP [SCK] on 74HC595
int dataPin = 9;   // (12) DS [S1] on 74HC595
int analogPinVal = 0;
int button_values[] = {481, 311, 227, 176, 141, 114, 89, 60}; // Pin values read by analogue input - A0
int tolerance = 15;
int numLeds = 8;
int binaryNum = 0b00000000;
byte leds = 0;

// this first function to turn them off, from right to left (least significant)
void updateShiftRegister()
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds); // LSBFIRST starts from the least significant Byte, that corresponds to 8th pinout
    digitalWrite(latchPin, HIGH);
}
// this second function is to turn them off
void updateShiftRegister2()
{
    digitalWrite(latchPin, HIGH);
    shiftOut(dataPin, clockPin, LSBFIRST, leds); // if we start with MSBFIRST in this function, then it would start from the most significant, that is the 1st pinout.
    digitalWrite(latchPin, LOW);
}

void updateShiftRegisterWithValue(const uint8_t value)
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, value);
    digitalWrite(latchPin, HIGH);
}

void setup()
{
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    analogPinVal = analogRead(A0); // read the input pin
    // Find which button was pressed
    for (int i : button_values)
    {
        if (analogPinVal > i - tolerance && analogPinVal < i + tolerance)
        {
            Serial.print("Found button pressed: ");
            Serial.println(i);
            // Set button to OFF & record time
        }
    }

    bitSet(binaryNum, 1); // For our binary number, bitSet turns the value ON - which
    // means setting the bit to HIGH.

    updateShiftRegisterWithValue(binaryNum); // led 0 on, other leds off
    delay(tDelay);
    updateShiftRegisterWithValue(binaryNum); // led 2 on, other leds off
    delay(tDelay);
}
