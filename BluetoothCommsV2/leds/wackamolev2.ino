int latchPin = 10; // (11) ST_CP [RCK] on 74HC595
int clockPin = 11; // (9) SH_CP [SCK] on 74HC595
int dataPin = 9;   // (12) DS [S1] on 74HC595
int totalLedsPerRow = 8;
int binaryNumShiftRegister1 = 0b00000000;
int binaryNumShiftRegister2 = 0b00000000;
int binaryNumShiftRegister3 = 0b00000000;
int binaryNumShiftRegister4 = 0b00000000;
int resetBinaryNum = 0b00000000;

void setup()
{
    // Setup the pins as OUTPUT
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    Serial.begin(9600);
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

void shiftRegisterAnimation(int indx, bool shouldReset)
{
    Serial.println(indx);
    Serial.println(shouldReset);
    // reset binaryNums for shift registers
    binaryNumShiftRegister1 = resetBinaryNum;
    binaryNumShiftRegister2 = resetBinaryNum;
    binaryNumShiftRegister3 = resetBinaryNum;
    binaryNumShiftRegister4 = resetBinaryNum;
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

void loop()
{
    for (int i = 0; i < 8; i++)
    {
        shiftRegisterAnimation(i, false);
    }

    for (int i = 7; i > 0; i--)
    {
        shiftRegisterAnimation(i, i == 7);
    }

    // Example usage: update shift registers with specific data
    // updateShiftRegisters(0b10101010, 0b11001100, 0b11110000, 0b00001111);

    // You can modify the data patterns as needed for your application
    // delay(1000);  // Delay for demonstration purposes
}
