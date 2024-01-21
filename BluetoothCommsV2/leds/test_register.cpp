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
    updateShiftRegisterWithValue(0b11110000);
    delay(500);
    updateShiftRegisterWithValue(0b00001111);
    delay(500);
}
