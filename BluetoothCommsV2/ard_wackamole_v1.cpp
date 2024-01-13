// Temporarily store button value
int analogValue = 0;
int button_values[] = {913, 431, 269, 181, 111};
int led_pin_map[] = {7, 2, 3, 4, 5};
int total_leds = 5;
int button_tolerance = 20;    // How much +/- value to accept for button resistance when pressed.
int current_led_index_on = 0; // Between 0 and 4

void setup()
{
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
    // Start initial LED
}

void loop()
{
    Serial.print("Active LED index: ");
    Serial.println(current_led_index_on);
    digitalWrite(current_led_index_on, HIGH);
    // digitalWrite(random(1, 5), HIGH);
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
            digitalWrite(led_pin_map[i], HIGH);
        }
        else
        {
            digitalWrite(led_pin_map[i], LOW);
        }
    }
    Serial.println("");
}