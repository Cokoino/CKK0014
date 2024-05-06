/*****************************************************
 
 * This code applies to 4WD Mecanum Wheels Robot Car Kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0014
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define WS2812_PIN 5   //WS2812 PIN
#define WS2812_COUNT  12  // How many NeoPixels are attached to the Arduino?
#define BRIGHTNESS 6  // NeoPixel brightness, 0 (min) to 255 (max)
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(WS2812_COUNT, WS2812_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)

///////////////////////////////////////////////////////////////////////////////////
void setup()
{
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
 // #if defined (__AVR_ATtiny85__)
    //if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  //#endif        // END of Trinket-specific code.
  strip.begin();// INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show(); // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}
///////////////////////////////////////////////////////////////////////////////////
void loop()
{
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255, 0, 0), 6); // Red
  delay(800);
  //colorWipe(strip.Color(255, 150, 0), 6); // yellow
  //delay(800);
  colorWipe(strip.Color(0, 255, 0), 6); // Green
  delay(800);
  //colorWipe(strip.Color(0, 255, 255), 6); // CYAN
  //delay(800);
  colorWipe(strip.Color(0, 0, 255), 6); // Blue
  delay(800);
  //colorWipe(strip.Color(180, 0, 255), 6); // purple
  //delay(800);
  //colorWipe(strip.Color(127, 127, 127), 6); // White
  //delay(800);
  //colorWipe(strip.Color(0, 0, 0), 0); // Clear
}

void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {// For each pixel in strip...
    strip.setPixelColor(i, c);                 //  Set pixel's color (in RAM)
    strip.show();                              //  Update strip to match
    delay(wait);                               //  Pause for a moment
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) 
{
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
       }
     }
   }
 }
