
//Clockwise and counterclockwise colored flowing lights

#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 12

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void loop()
{
  //Dark color, red → green, clockwise
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(255 - 7 * i, 7 * i, 0 );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

  //Dark color, green → blue, clockwise
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(0, 255 - 7 * i, 7 * i );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

  //Dark color, blue → red, clockwise
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(7 * i, 0, 255 - 7 * i );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

  //Light color, red → green, clockwise
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(255 - 7 * i, 7 * i, 255);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

 //Light color, green → blue, clockwise
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(255, 255 - 7 * i, 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

//Light color, blue → red, clockwise
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(7 * i, 255, 255 - 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

//Dark color, red → blue, counterclockwise
  for (int i = NUM_LEDS; i > 0; i-- )
  {
    leds[i] = CRGB(255 - 7 * i, 0, 7 * i );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

//Dark color, blue → green, counterclockwise
  for (int i = NUM_LEDS; i > 0; i-- )
  {
    leds[i] = CRGB(0, 7 * i, 255 - 7 * i );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

//Dark color, green → red, counterclockwise
  for (int i = NUM_LEDS; i > 0; i-- )
  {
    leds[i] = CRGB(7 * i , 255 - 7 * i, 0);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

//Light color, red → blue, counterclockwise
  for (int i = NUM_LEDS; i > 0; i-- )
  {
    leds[i] = CRGB(255 - 7 * i, 255, 7 * i );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

//Light color, blue → green, counterclockwise
  for (int i = NUM_LEDS; i > 0; i-- )
  {
    leds[i] = CRGB(255, 7 * i, 255 - 7 * i );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

//Light color, green → red, counterclockwise
  for (int i = NUM_LEDS; i > 0; i-- )
  {
    leds[i] = CRGB(7 * i , 255 - 7 * i, 255);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }
}
