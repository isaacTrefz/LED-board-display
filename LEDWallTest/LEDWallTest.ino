#include <FastLED.h>
#define WIDTH 36
#define HEIGHT 32
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B,LED_PIN, GRB>(leds,NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i].r = 255;
    leds[i].g = 255;
    leds[i].b = 255;
    FastLED.show();
    delay(10);
  }
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
    FastLED.show();
    delay(10);
  }
}
