#include <Adafruit_NeoPixel.h>

int data_pin = 6;
int num_pixels = 5;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(num_pixels, data_pin, NEO_GRB + NEO_KHZ800); // Speed at which to communicate with the leds

void setup()
{
    // Initialize Neopixels
    pixels.begin();

    // Set LED colors
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(255, 127, 0));
    pixels.setPixelColor(2, pixels.Color(0, 255, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 255));
    pixels.setPixelColor(4, pixels.Color(127, 0, 255));

    // Write data out to neopixels
    pixels.show();
}

void updatePixel(int pixelNumber, uint32_t color)
{
    pixels.setPixelColor(pixelNumber, color);
}

int getRandomNumber(int index)
{
    return 10 * index + 1;
}

void loop()
{
    for (int i = 0; i < num_pixels; i++)
    {
        updatePixel(i, pixels.Color(255, 0, 0));
        updatePixel(i - 1, pixels.Color(0, 0, 0));
        pixels.show();
        if (i < num_pixels)
        {
            delay(250);
        }
    }
    for (int k = num_pixels; k > 0; k--)
    {
        updatePixel(k, pixels.Color(255, 0, 0));
        updatePixel(k + 1, pixels.Color(0, 0, 0));
        pixels.show();
        if (k > num_pixels)
        {
            delay(250);
        }
    }
}