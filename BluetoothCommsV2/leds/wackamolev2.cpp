int tDelay = 1000;
int latchPin = 10; // (11) ST_CP [RCK] on 74HC595
int clockPin = 11; // (9) SH_CP [SCK] on 74HC595
int dataPin = 9;   // (12) DS [S1] on 74HC595
int analogPinVal = 0;
int button_values[] = {481, 311, 227, 176, 141, 114, 89, 60}; // Pin values read by analogue input - A0
int tolerance = 15;
int numLeds = 8;
int binaryNum = 0b00000000;
long randNumber;
byte leds = 0;

// Game State
bool hasPreviouslyPressedButton = false;
bool newGame = true;

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
    randomSeed(analogRead(A1)); // Take random analog input as seed.
    Serial.begin(9600);
}

void loop()
{
    // update random number, if game started || previously
    if (newGame || hasPreviouslyPressedButton)
    {
        randNumber = random(numLeds);
        newGame = false;
        hasPreviouslyPressedButton = false;
    }

    //
    // Update Hardware Display to user
    //
    //
    // For our binary number, bitSet turns the value ON - which means setting the bit to HIGH.
    // Eg - bitSet(num, 3); will set the bit at index 3 to HIGH (On).
    bitSet(binaryNum, randNumber);
    updateShiftRegisterWithValue(binaryNum);

    //
    // Handle Button Press
    //
    analogPinVal = analogRead(A0); // read the input pin
                                   // Find which button was pressed
    unsigned j = 0;                // keep track of index
    for (int i : button_values)
    {
        if (analogPinVal > i - tolerance && analogPinVal < i + tolerance)
        {
            Serial.print("Found button pressed: ");
            Serial.println(i);
            // Set button to OFF & record time
            if (j == randNumber)
            {
                Serial.println("Button matches index");
            }
        }
        j++;
    }
}
