/*****************************************************
 * This code applies to 4WD Mecanum Wheels Robot Car Kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0014
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
/****************************************************
4WD Mecanum Wheels Robot Car Kit
            
        M4 (------) M3         
-------------|  |-----------------
-------------|  |-----------------
        M2 (------) M1
****************************************************/

#include <SCoop.h> //Import multithread library
#include <IRremote.h> //IR library
#define RECV_PIN 3  //The infrared control is defined as D3
IRsend irsend;
IRrecv irrecv(RECV_PIN);
decode_results results;

#include <Wire.h> 
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#include <Servo.h>
Servo carservo;
int pos=0;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define WS2812_PIN 5   //WS2812 PIN
#define WS2812_COUNT 12  // How many NeoPixels are attached to the Arduino?
#define BRIGHTNESS 5  // NeoPixel brightness, 0 (min) to 255 (max)
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(WS2812_COUNT, WS2812_PIN, NEO_GRB + NEO_KHZ800);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


#define Buzz 11     //buzzer PIN
#define led_L 9     //LED_l PIN
#define led_R 6     //LED_R PIN
defineTask(TaskOne);     // Create subthread 1
defineTask(TaskTwo);    // Create subthread 2

///////////////////////////////////////////////////////////////////////////////////
void TaskOne::setup() //Thread 1 setup
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); 
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, 0);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("HELLO WORLD!");
  lcd.setCursor(2,1);
  lcd.print("HELLO COKOINO!");
  pinMode(Buzz, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_L, OUTPUT);

  carservo.attach(10);
  carservo.write(65);

  irrecv.enableIRIn(); // Start the receiver
  
 
}

void TaskTwo::setup(){    //Thread 2 setup
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
}

void setup(){
  mySCoop.start(); //Start multithreading
}

///////////////////////////////////////////////////////////////////////////////////
void TaskOne::loop()   //loop subthread 1
{
  if (irrecv.decode(&results)) 
    { 
      Serial.println(results.value, HEX); //Serial print data
      delay(50);
      irrecv.resume();// Receive the next value
      delay(10);
    }
  switch(results.value)    //Jump to the position of the corresponding value
    {
      case 0xff18e7 :  forward();         results.value=0; break;      //Up button of remote control
      case 0xff4ab5 :  backward();        results.value=0; break;      //down button of remote control
      case 0xff10ef :  turnLeft();        results.value=0; break;      //left button of remote control
      case 0xff5aa5 :  turnRight();       results.value=0; break;      //right button of remote control
      case 0xff38c7 :  Stopcar();         results.value=0; break;      //OK button of remote control 
      case 0xFFA25D :  two_wheel_drive(); results.value=0;break;       //1 button of remote control
      case 0xFF629D :  buzz();            results.value=0;break;       //2 button of remote control
      case 0xFFE21D :  LED();             results.value=0;break;       //3 button of remote control
      //case 0xFF22DD :  WS2812_show();   results.value=0;break;       //4 button of remote control
      case 0xFF02FD :  servo();           results.value=0;break;       //5 button of remote control
      case 0xFFC23D :  LED_Blink();       results.value=0;break;       //6 button of remote control
      case 0xFFE01F :  backleft();        results.value=0;break;       //7 button of remote control
      case 0xFFA857 :  backright();       results.value=0;break;       //8 button of remote control
      case 0xFF906F :  Rotation_R();      results.value=0;break;       //9 button of remote control
      case 0xFF9867 :  Rotation_L();      results.value=0;break;       //0 button of remote control
      case 0xFF6897 :  MOVE_L();          results.value=0;break;       // * button of remote control
      case 0xFFB04F :  MOVE_R();          results.value=0;break;       // # button of remote control
      default : break;
    }  
}
//////////////////////////////////CONTROL FUNCIONES//////////////////////////////////
//pwm.setPWM(pwmnum,on, off);
     //(pwmnum, on, off) function is mainly to adjust the output PWM duty cycle.
     // Usually, on is set to 0 and off can be changed.
     // Because the PCA9685 is a 12-bit resolution
     // the value of 0 to 4096 off represents a duty cycle of 0 to 100.
void forward()
////The off value is based on the battery level ranging from 7.4V to 8.4V. /////////////////////////////////
////If your battery level is below 7.4V, you can increase the off value to allow the car to move normally.//
{
 pwm.setPWM(0,0,-1200);
 pwm.setPWM(1,0,1200);
 pwm.setPWM(2, 0, 1200);
 pwm.setPWM(3, 0, -1200);
 pwm.setPWM(4, 0, -1200);
 pwm.setPWM(5, 0, 1200);
 pwm.setPWM(6, 0, 1200);
 pwm.setPWM(7, 0, -1200);
}

void backward()
{
 pwm.setPWM(0,0,1200);
 pwm.setPWM(1,0,-1200);
 pwm.setPWM(2, 0, -1200);
 pwm.setPWM(3, 0, 1200);
 pwm.setPWM(4, 0, 1200);
 pwm.setPWM(5, 0, -1200);
 pwm.setPWM(6, 0, -1200);
 pwm.setPWM(7, 0, 1200);
}

void backleft()
{
 pwm.setPWM(0,0,800);
 pwm.setPWM(1,0,-800);
 pwm.setPWM(2, 0, -1200);
 pwm.setPWM(3, 0, 1200);
 pwm.setPWM(4, 0, 1200);
 pwm.setPWM(5, 0, -800);
 pwm.setPWM(6, 0, -800);
 pwm.setPWM(7, 0, 1200);
}
void backright()
{
 pwm.setPWM(0,0,1200);
 pwm.setPWM(1,0,-1200);
 pwm.setPWM(2, 0, -800);
 pwm.setPWM(3, 0, 800);
 pwm.setPWM(4, 0, 1200);
 pwm.setPWM(5, 0, -1200);
 pwm.setPWM(6, 0, -800);
 pwm.setPWM(7, 0, 800);
}
void turnRight()
{
 pwm.setPWM(0,0,-1200);
 pwm.setPWM(1,0,1200);
 pwm.setPWM(2, 0, 800);
 pwm.setPWM(3, 0, -800);
 pwm.setPWM(4, 0, -1200);
 pwm.setPWM(5, 0, 1200);
 pwm.setPWM(6, 0, 800);
 pwm.setPWM(7, 0, -800);
}

void turnLeft()
{
 pwm.setPWM(0,0,-800);
 pwm.setPWM(1,0,800);
 pwm.setPWM(2, 0, 1200);
 pwm.setPWM(3, 0, -1200);
 pwm.setPWM(4, 0, -800);
 pwm.setPWM(5, 0, 800);
 pwm.setPWM(6, 0, 1200);
 pwm.setPWM(7, 0, -1200);
}
void Rotation_R()
{
 pwm.setPWM(0,0,-1200);
 pwm.setPWM(1,0,1200);
 pwm.setPWM(2, 0, -1200);
 pwm.setPWM(3, 0, 1200);
 pwm.setPWM(4, 0, -1200);
 pwm.setPWM(5, 0, 1200);
 pwm.setPWM(6, 0, -1200);
 pwm.setPWM(7, 0, 1200);
}
void Rotation_L()
{
 pwm.setPWM(0,0,1200);
 pwm.setPWM(1,0,-1200);
 pwm.setPWM(2, 0, 1200);
 pwm.setPWM(3, 0, -1200);
 pwm.setPWM(4, 0, 1200);
 pwm.setPWM(5, 0, -1200);
 pwm.setPWM(6, 0, 1200);
 pwm.setPWM(7, 0, -1200);
}
void MOVE_L()
{
 pwm.setPWM(0,0,-1200);
 pwm.setPWM(1,0,1200);
 pwm.setPWM(2, 0, -1200);
 pwm.setPWM(3, 0, 1200);
 pwm.setPWM(4, 0, 1200);
 pwm.setPWM(5, 0, -1200);
 pwm.setPWM(6, 0, 1200);
 pwm.setPWM(7, 0, -1200);
}
void MOVE_R()
{
 pwm.setPWM(0,0,1200);
 pwm.setPWM(1,0,-1200);
 pwm.setPWM(2, 0, 1200);
 pwm.setPWM(3, 0, -1200);
 pwm.setPWM(4, 0, -1200);
 pwm.setPWM(5, 0, 1200);
 pwm.setPWM(6, 0, -1200);
 pwm.setPWM(7, 0, 1200);
}
void two_wheel_drive()
{
  //Move 45 degrees right ahead
 pwm.setPWM(0, 0, 0);
 pwm.setPWM(1, 0, 0);
 pwm.setPWM(2, 0, 1500);
 pwm.setPWM(3, 0, -1500);
 pwm.setPWM(4, 0, -1500);
 pwm.setPWM(5, 0, 1500);
 pwm.setPWM(6, 0, 0);
 pwm.setPWM(7, 0, 0);
 delay(1000);
 //Move 45 degrees left ahead
 pwm.setPWM(0,0,-1500);
 pwm.setPWM(1,0,1500);
 pwm.setPWM(2, 0, 0);
 pwm.setPWM(3, 0, 0);
 pwm.setPWM(4, 0, 0);
 pwm.setPWM(5, 0, 0);
 pwm.setPWM(6, 0, 1500);
 pwm.setPWM(7, 0, -1500);
 delay(1000);
 //Move 45 degrees back to left
 pwm.setPWM(0, 0, 0);
 pwm.setPWM(1, 0, 0);
 pwm.setPWM(2, 0, -1500);
 pwm.setPWM(3, 0, 1500);
 pwm.setPWM(4, 0, 1500);
 pwm.setPWM(5, 0, -1500);
 pwm.setPWM(6, 0, 0);
 pwm.setPWM(7, 0, 0);
 delay(1000);
 //Move 45 degrees back to right
 pwm.setPWM(0,0,1500);
 pwm.setPWM(1,0,-1500);
 pwm.setPWM(2, 0, 0);
 pwm.setPWM(3, 0, 0);
 pwm.setPWM(4, 0, 0);
 pwm.setPWM(5, 0, 0);
 pwm.setPWM(6, 0, -1500);
 pwm.setPWM(7, 0, 1500);
}

void Stopcar()
{
 pwm.setPWM(0, 0, 0);
 pwm.setPWM(1, 0, 0);
 pwm.setPWM(2, 0, 0);
 pwm.setPWM(3, 0, 0);
 pwm.setPWM(4, 0, 0);
 pwm.setPWM(5, 0, 0);
 pwm.setPWM(6, 0, 0);
 pwm.setPWM(7, 0, 0);
}

void servo()
{
    for (pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 150 degrees
    // in steps of 1 degree
    carservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 150; pos >= 0; pos -= 1) { // goes from 150 degrees to 0 degrees
    carservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  delay(50);
  carservo.write(65);
}



void buzz()
{
  for(int i = 0;i < 100; i++)
  {
    digitalWrite(Buzz, HIGH);
    delay(1);
    digitalWrite(Buzz, LOW);
    delay(1);
  }
  for(int j = 0;j< 180; j++)
  {
    digitalWrite(Buzz, HIGH);
    delay(2);
    digitalWrite(Buzz, LOW);
    delay(2);
  }
}

void LED()
{
  digitalWrite(led_R,HIGH);
  digitalWrite(led_L,HIGH);
}

void LED_Blink()
{
  for(int i = 0;i < 15; i++)
  {
    digitalWrite(led_R,HIGH);
    digitalWrite(led_L,HIGH);
    delay(50);
    digitalWrite(led_R,LOW);
    digitalWrite(led_L,LOW);
    delay(50);
    digitalWrite(led_R,HIGH);
    digitalWrite(led_L,HIGH);
    delay(50);
  }
}

void TaskTwo::loop()  //loop subthread 2
{
  colorWipe(strip.Color(255, 0, 0), 10); // Red
  delay(800);
  colorWipe(strip.Color(255, 150, 0), 10); // yellow
  delay(800);
  colorWipe(strip.Color(0, 255, 0), 10); // Green
  delay(800);
  colorWipe(strip.Color(0, 255, 255), 10); // CYAN
  delay(800);
  colorWipe(strip.Color(0, 0, 255), 10); // Blue
  delay(800);
  colorWipe(strip.Color(180, 0, 255), 10); // purple
  delay(800);
  colorWipe(strip.Color(127, 127, 127), 10); // White
  delay(800);
  colorWipe(strip.Color(0, 0, 0), 30); // Clear
  Serial.println("OK");
}

void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {// For each pixel in strip...
    strip.setPixelColor(i, c);                 //  Set pixel's color (in RAM)
    strip.show();                              //  Update strip to match
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
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

void loop(){
  yield();  //loop Multithreaded task
}
