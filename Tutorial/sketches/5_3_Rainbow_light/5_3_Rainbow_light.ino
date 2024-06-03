
//Phantom flowing light, with a rainbow colored light ring: red, orange, yellow, green, blue, purple.

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
  //Red → Orange → Yellow
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(255, 7 * i + 11, 0 );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

  //Yellow → Green
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(224 - 7 * i, 255, 0 );
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

  //Green → Cyan → Blue
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(0, 224 - 7 * i, 7 * i + 11);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

  //Blue → Purple
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(7 * i, 0, 255);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }

  //Purple → Red
  for (int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i] = CRGB(255, 0, 224 - 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay (50);
  }
}
