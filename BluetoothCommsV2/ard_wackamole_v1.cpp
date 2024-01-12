// Temporarily store button value
int analogValue = 0;
int button_values[] = {913, 431, 269, 181, 111};
int total_leds = 5;
int button_tolerance = 20;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    // Player 1 buttons
    pinMode(A0, INPUT);
    // Start serial monitoring
    Serial.begin(9600);
}

void loop()
{
    Serial.println("Reading Analog Value...");
    analogValue = analogRead(A0);
    // Find which button was pressed
    for (int i = 0; i < total_leds; i++)
    {
        if (analogValue < button_values[i] + button_tolerance and analogValue > button_values[i] - button_tolerance)
        {
            Serial.print("Button ");
            Serial.print(i);
            Serial.print(" Pressed");
        }
    }
    Serial.println("");
}