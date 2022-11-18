#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

int data_pin = 6;
int num_pixels = 5;
int delay_time = 100;
// Remember prev led state
int led_toggle_pin = 3;
int btn_pin = 2;
int btn_state = LOW;
int btn_prev = HIGH;
int led_state = LOW;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(num_pixels, data_pin, NEO_GRB + NEO_KHZ800); // Speed at which to communicate with the leds

void setup()
{
    // Add serial debugging
    Serial.begin(9600);
    // Initialize Neopixels
    pixels.begin();
    // Led toggle switch
    // Set up pins
    pinMode(btn_pin, INPUT);
    pinMode(led_toggle_pin, OUTPUT);

    // Set LED to default off
    digitalWrite(led_toggle_pin, LOW);
}

void updatePixel(int pixelNumber, uint32_t color)
{
    pixels.setPixelColor(pixelNumber, color);
}

void loopForward()
{
    for (int i = 1; i < num_pixels; i++)
    {
        updatePixel(i, pixels.Color(255, 0, 0));
        updatePixel(i - 1, pixels.Color(0, 0, 0));
        pixels.show();
        delay(delay_time);
    }
}

void loopBackward()
{
    for (int i = num_pixels - 2; i >= 0; i--)
    {
        updatePixel(i, pixels.Color(255, 0, 0));
        updatePixel(i + 1, pixels.Color(0, 0, 0));
        pixels.show();
        delay(delay_time);
    }
}

void loop()
{
    // Read current button state
    btn_state = digitalRead(btn_pin);
    Serial.println(btn_state);
    if ((btn_prev == HIGH) && (btn_state == LOW))
    {

        // Toggle the LED
        if (led_state == LOW)
        {
            led_state = HIGH;
        }
        else
        {
            led_state = LOW;
        }
        digitalWrite(led_toggle_pin, led_state);
    }

    // Remember the previous button state for the next loop iteration
    btn_prev = btn_state;

    //
    loopForward();
    loopBackward();
}