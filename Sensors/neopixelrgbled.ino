/*
Author: Leon Tan

APIs, explanations and sample code for NeoPixel RGB LED
*/

// API: Initializes the NeoPixel object
Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// API: Initializes the NeoPixel library and prepares the data line for communication with the LEDs
strip.begin();

// API: Updates the LED strip with any changes made to pixel colors. It should be called after setting colors with setPixelColor() to actually show the changes
strip.show();

// API: Sets the color of an individual LED
strip.setPixelColor(n, color);

// API: Sets the color of an individual LED
strip.setPixelColor(n, r, g, b);

// API: Creates a 32-bit color value
uint32_t red = strip.Color(255, 0, 0);

// API: Adjusts the brightness of the entire strip
strip.setBrightness(brightness);

// API: Sets all pixels to 'off'
strip.clear() // required to run strip.show() after this command

// API: Returns the current color of the LED at index n as a 32-bit RGB value
uint32_t currentColor = strip.getPixelColor(0);

// API: Applies gamma correction to a 32-bit color value
uint32_t correctedColor = strip.gamma32(strip.Color(255, 0, 0));

// API: Returns the number of pixels in the NeoPixel object
strip.numPixels();

// API: Dynamically changes the number of LEDs controlled by the NeoPixel object
strip.updateLength(x);

// API: Changes the LED type dynamically
strip.updateType(x);

// Sample code: Apply gamma correction
#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(50); // Set brightness to 50 out of 255
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 150, 0)); // Set pixel to green
    strip.show();
    delay(100);
 }

  strip.clear(); // Turn off all pixels
  strip.show();
  delay(500);

  for (int i = 0; i < strip.numPixels(); i++) {
    uint32_t color = strip.getPixelColor(i); // Get the current color of the pixel
    strip.setPixelColor(i, strip.gamma32(color)); // Apply gamma correction
    strip.show();
    delay(100);
  }
}

// Sample code: Effect of filling the LED stick with a color, one pixel at a time
#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

// Sample code: Gradually increases and decreases the brightness of all LEDs, creating a breathing-like effect
#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  breathingEffect(strip.Color(0, 0, 255), 10); // Blue breathing effect
}

void breathingEffect(uint32_t color, int wait) {
  for (int brightness = 0; brightness < 255; brightness++) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.setBrightness(brightness);
    strip.show();
    delay(wait);
  }
  for (int brightness = 255; brightness >= 0; brightness--) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.setBrightness(brightness);
    strip.show();
    delay(wait);
  }
}
