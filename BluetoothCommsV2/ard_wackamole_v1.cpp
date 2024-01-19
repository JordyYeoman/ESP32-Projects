// TODO:
// 1. Measure average reaction time over course of game
// 2. Record game time
// 3. Record scores
// 4. Include start button
// 5. ....

// Temporarily store button value
int analogValue = 0;
bool gameStarted = false;
long randNumber = 0;
int button_values[] = {913, 431, 269, 181, 111};
int led_pin_map[] = {7, 2, 3, 4, 5};
int total_leds = 5;
int button_tolerance = 20; // How much +/- value to accept for button resistance when pressed.
bool hasPressedPreviousButton = false;

//
int tDelay = 500;
int latchPin = 11; // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;  // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;  // (12) DS [S1] on 74HC595

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

void setup()
{
    // Try not to cook the shift register plz
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    Serial.begin(9600);
    //
    pinMode(LED_BUILTIN, OUTPUT);
    // Board Leds
    pinMode(7, OUTPUT); // LED 1,
    pinMode(2, OUTPUT); // ..
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT); // LED 5.
    // Player 1 buttons
    pinMode(A0, INPUT);
    // Start serial monitoring
    Serial.begin(9600);
    // Setup random seed
    randomSeed(analogRead(A1));
}

void loop()
{
    // Check if button has been pressed since previous loop
    // If it HAS, then change to a new random number
    if (hasPressedPreviousButton)
    {
        randNumber = random(total_leds);
    }

    // Reset boolean check every loop
    hasPressedPreviousButton = false;

    // Light up current LED
    digitalWrite(led_pin_map[randNumber], HIGH);

    // Find which button was pressed
    analogValue = analogRead(A0);
    for (int i = 0; i < total_leds; i++)
    {
        // Match resistance to button pressed
        if (analogValue < button_values[i] + button_tolerance and analogValue > button_values[i] - button_tolerance)
        {
            // If index of button matches LED rand index, turn it off
            // and reset boolean toggle
            digitalWrite(led_pin_map[i], LOW);
            hasPressedPreviousButton = true;
        }
    }

    //
    leds = 0;
    updateShiftRegister();
    for (int i = 0; i < 8; i++)
    {
        delay(tDelay);
        bitSet(leds, i); // bitset sets the byte of each led to on
        updateShiftRegister();
    }
    //
    for (int i = 0; i < 8; i++)
    {

        bitClear(leds, i); // bitclear sets the byte of each led to off
        updateShiftRegister2();
        delay(tDelay);
    }
}