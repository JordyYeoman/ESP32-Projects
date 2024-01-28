#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int latchPin = 10; // (11) ST_CP [RCK] on 74HC595
int clockPin = 11; // (9) SH_CP [SCK] on 74HC595
int dataPin = 9;   // (12) DS [S1] on 74HC595
int totalLedsPerRow = 8;
int binaryNumShiftRegister1 = 0b00000000;
int binaryNumShiftRegister2 = 0b00000000;
int binaryNumShiftRegister3 = 0b00000000;
int binaryNumShiftRegister4 = 0b00000000;
int resetBinaryNum = 0b00000000;

// Game state
unsigned long time;
unsigned long reactionTime;
bool buttonPressed;
bool newGame;
bool gameInProgress = false;

void setup()
{
    // Setup the pins as OUTPUT
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.print("New Game");
}

// Function to send a byte to the shift register (LSB first)
void shiftOutLSB(byte data)
{
    // Iterate through each bit in the byte
    for (int i = 0; i < 8; ++i)
    {
        // Shift the bits out, starting from the least significant bit
        digitalWrite(dataPin, (data & (1 << i)) ? HIGH : LOW);

        // Pulse the clock pin to move to the next bit
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

// Function to send a byte to the shift register (MSB first)
void shiftOutMSB(byte data)
{
    // Iterate through each bit in the byte
    for (int i = 7; i >= 0; --i)
    {
        // Shift the bits out, starting from the most significant bit
        digitalWrite(dataPin, (data & (1 << i)) ? HIGH : LOW);

        // Pulse the clock pin to move to the next bit
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

// Function to update the daisy-chained shift registers
void updateShiftRegisters(byte data1, byte data2, byte data3, byte data4)
{
    // Start the data transfer
    digitalWrite(latchPin, LOW);

    // Send data to each shift register
    shiftOutLSB(data1);
    shiftOutLSB(data2);
    shiftOutLSB(data3);
    shiftOutLSB(data4);

    // End the data transfer by pulsing the latch pin
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
}

void resetBinaryNums()
{
    // reset binaryNums for shift registers
    binaryNumShiftRegister1 = resetBinaryNum;
    binaryNumShiftRegister2 = resetBinaryNum;
    binaryNumShiftRegister3 = resetBinaryNum;
    binaryNumShiftRegister4 = resetBinaryNum;
}

void shiftRegisterAnimation(int indx, bool shouldReset)
{
    resetBinaryNums();
    // count forward
    bitSet(binaryNumShiftRegister1, indx);
    bitSet(binaryNumShiftRegister2, indx);
    bitSet(binaryNumShiftRegister3, indx);
    bitSet(binaryNumShiftRegister4, indx);
    //
    updateShiftRegisters(binaryNumShiftRegister1, binaryNumShiftRegister2, binaryNumShiftRegister3, binaryNumShiftRegister4);
    if (!shouldReset)
    {
        delay(150);
    }
}

// Animation #1
void loopForwardAndBackWard()
{
    for (int i = 0; i < 8; i++)
    {
        shiftRegisterAnimation(i, false);
    }

    for (int i = 7; i > 0; i--)
    {
        shiftRegisterAnimation(i, i == 7);
    }
}

// Pass in a reference to the variables in the parent function scope.
void rowIndexUpdate(int &idx, bool &isBackwards)
{

    // Check for looping backwards
    if (isBackwards)
    {
        idx--;
    }
    else
    {
        idx++;
    }
    if (idx > 7)
    {
        isBackwards = true;
    }
    if (idx == 0)
    {
        isBackwards = false;
    }
};

// Animation #2
void simpleOffsetStepAnimation()
{
    // keep the current animation state
    int row1Index = 0;
    bool row1Backwards = false;
    int row2Index = 0;
    bool row2Backwards = false;
    int row3Index = 0;
    bool row3Backwards = false;
    int row4Index = 0;
    bool row4Backwards = false;

    for (int i = 0; i < 33; i++)
    {
        // Check for user input
        checkNewGame();
        if (newGame)
        {
            return;
        }

        // reset to all binary nums LOW
        resetBinaryNums();

        // start first row animation
        bitSet(binaryNumShiftRegister1, row1Index);
        rowIndexUpdate(row1Index, row1Backwards);

        // start second animation
        if (i > 0)
        {
            bitSet(binaryNumShiftRegister2, row2Index);
            rowIndexUpdate(row2Index, row2Backwards);
        }

        // start third row animation
        if (i > 1)
        {
            bitSet(binaryNumShiftRegister3, row3Index);
            rowIndexUpdate(row3Index, row3Backwards);
        }

        // start fourth row animation
        if (i > 2)
        {
            bitSet(binaryNumShiftRegister4, row4Index);
            rowIndexUpdate(row4Index, row4Backwards);
        }

        updateShiftRegisters(binaryNumShiftRegister1, binaryNumShiftRegister2, binaryNumShiftRegister3, binaryNumShiftRegister4);
        delay(150);
    }
}

void checkNewGame()
{
    if (analogRead(A0) > 500)
    {
        newGame = true;
        updateShiftRegisters(0b00000000, 0b00000000, 0b00000000, 0b00000000);
    }
}

void gameStartupLogic()
{
    if (newGame && !gameInProgress)
    {
        gameInProgress = true;
        lcd.clear();
        // Delay 3s before game starts
        lcd.print("Game Starting");
        delay(500);

        lcd.setCursor(0, 1);
        lcd.print("3...");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("2...");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("1...");
        delay(1000);
        lcd.clear();
        lcd.print("Game Started");
        delay(1000);
        lcd.clear();
        time = millis();
        // Turn off new game after initialising, so we avoid entering this loop again
        newGame = false;
    }
}

void loop()
{
    // Check game buttons
    checkNewGame();

    gameStartupLogic();

    // Simple animation
    // loopForwardAndBackWard();

    // Simple off timing animation
    // simpleOffsetStepAnimation();
    // updateShiftRegisters(0b00000000, 0b00000000, 0b00000000, 0b00000000);
}
