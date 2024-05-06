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
#include <Wire.h> 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define WS2812_PIN 5   //WS2812 PIN
#define WS2812_COUNT 12  // How many NeoPixels are attached to the Arduino?
#define BRIGHTNESS 10  // NeoPixel brightness, 0 (min) to 255 (max)
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(WS2812_COUNT, WS2812_PIN, NEO_GRB + NEO_KHZ800);

Servo carservo;
byte carservoOffset = 0;

LiquidCrystal_I2C lcd(0x27,16,2);


#define Buzz 11     //buzzer PIN
#define led_R 6
#define led_L 9

#define Trig_Pin 13 //define Trig pin
#define Echo_Pin 12  //define Echo pin
#define distance_minimum 30   //cm
#define MAX_distance 300   //cm
float distance,distance_0,distance_130;//Import the middle, right, and left distance variables
int randNumber=0;
int L_Distance=0;
int M_Distance=0;
int R_Distance=0;
float cm;

defineTask(TaskOne);    // Create subthread 1
defineTask(TaskTwo);    // Create subthread 2
///////////////////////////////////////////////////////////////////////////////////
void TaskOne::setup()   //thread1 setup
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
  lcd.setCursor(2,0);
  lcd.print("HELLO WORLD!");
  lcd.setCursor(1,1);
  lcd.print("HELLO COKOINO!");

  pinMode(Buzz, OUTPUT);

  pinMode(Trig_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT_PULLUP);
  carservo.attach(10);
  carservo.write(65);
}
void TaskTwo::setup(){  // //Thread 2 setup
  pinMode(led_R, OUTPUT);
  pinMode(led_L, OUTPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
}

void setup(){
  mySCoop.start();// multithread
}
///////////////////////////////////////////////////////////////////////////////////
void TaskOne::loop() //loop subthread 1
 {
   
   //LED();//light the green LED
   ultrasonic_distance();
  //Serial.println(distance);
  if(distance>distance_minimum)
    {
    forward();   //forward
    }
  if(distance<=distance_minimum)
    {
    Stopcar();     //stop
    buzz();        //the buzzer sounds
    servo_wheel(); //The servo rotates, and the ultrasonic module identifies the distance 
                   //of the 65-degree obstacle in the left front of the car body
    if((distance_0<=distance_minimum)&&(distance_130<=distance_minimum))
      {backward();//backward
      delay(300); }
    if(distance_0<distance_130)//The right obstacle is less distant than the left
      {turnLeft();
      delay(120);
     }
    if(distance_0>distance_130)//The left obstacle is less distant than the right
      {turnRight();
      delay(120);
      }
    if(distance_0==distance_130)
      {
      randNumber = random(1, 2);  //randnumber
      if(randNumber==1)
        {turnLeft();delay(120);
       }
      if(randNumber==2)
        {turnRight();delay(120);
       }
      }
    delay(250); 
    Stopcar();     //stop  
    }
}



void forward()
{
 pwm.setPWM(0,0,-600);
 pwm.setPWM(1,0,600);
 pwm.setPWM(2, 0, 600);
 pwm.setPWM(3, 0, -600);
 pwm.setPWM(4, 0, -600);
 pwm.setPWM(5, 0, 600);
 pwm.setPWM(6, 0, 600);
 pwm.setPWM(7, 0, -600);
}

void backward()
{
 pwm.setPWM(0,0,800);
 pwm.setPWM(1,0,-800);
 pwm.setPWM(2, 0, -800);
 pwm.setPWM(3, 0, 800);
 pwm.setPWM(4, 0, 800);
 pwm.setPWM(5, 0, -800);
 pwm.setPWM(6, 0, -800);
 pwm.setPWM(7, 0, 800);
}

void turnLeft()
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
void turnRight()
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
///////////////////////////////////////////////////////////ultrasonic ranging
void ultrasonic_distance()
{
delay(100); 
digitalWrite(Trig_Pin, HIGH);// make trigPin output high level lasting for 10μs to triger HC_SR04
delayMicroseconds(10);
digitalWrite(Trig_Pin, LOW);
distance = pulseIn(Echo_Pin, HIGH) * 340 /2/ 10000.0;// calculate the distance according to the time
if(distance==0)
  distance=300;
delay(100);
}
///////////////////////////////////////////////////////////servo rotation
void servo_wheel()
{
carservo.write(0);
delay(250);
ultrasonic_distance();
distance_0=distance;
delay(250);
  
carservo.write(130);
delay(250);
ultrasonic_distance();
distance_130=distance;
delay(250);

carservo.write(65);
delay(300);
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

void TaskTwo::loop() //// loop subthread 2
{ 
  digitalWrite(led_R,HIGH);
  digitalWrite(led_L,HIGH);
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
  yield();//loop multithread task
}
