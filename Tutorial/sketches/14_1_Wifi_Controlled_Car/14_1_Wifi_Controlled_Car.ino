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

#include <Regexp.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Wire.h> 
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#include <Servo.h>
Servo carservo;
int pos=0;
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define WS2812_PIN 5   //WS2812 PIN
#define WS2812_COUNT  12  // How many NeoPixels are attached to the Arduino?
#define BRIGHTNESS 10  // NeoPixel brightness, 0 (min) to 255 (max)
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(WS2812_COUNT, WS2812_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ600  600 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
#define Trig_Pin 13 //trig PIN
#define Echo_Pin 12  //echo PIN
#define Buzz 11     //buzzer PIN
#define led_R 6     //right green led PIN
#define led_L 9     //left green led PIN

#define Line_L A0   //left line PIN
#define Line_M A1   // middle line PIN
#define Line_R A2   //right line  PIN
#define distance_minimum 30 //The minimum obstacle distance is defined as 30cm
float distance,distance_0,distance_130;//Import the middle, right, and left distance variables
int randNumber=0;
int L_Distance=0;
int M_Distance=0;
int R_Distance=0;
float cm;

// regular
MatchState ms;
/// Car driving direction control button on the app interface, a total of 8 direction buttons.
const String phone1 = "fS";  // forwardStart:                    
const String phone1_5 = "lfS";  // forward_left_Start            
const String phone2 = "lS";    // leftStart                     
const String phone2_5 = "lbS";  // left_backward_Start        
const String phone3 = "bS";    // backwardStart                    
const String phone3_5 = "rbS";  // backward_right_Start           
const String phone4 = "rS";    // rightStart                     
const String phone4_5 = "rfS";  // right_forward_Start         
/// The other function buttons on the app interface
const String phone5 = "OK";//stop
const String phone6 = "rtl";//rotation left
const String phone7 = "rtr";//rotation right
const String phone8 = "trk";//track line running
const String phone9 = "aod";//Avoid obstacles
const String phone10 = "lgt";//light show
const String phone11 = "muc";//buzzer
const String phone12 = "flt";//fllow light
const String phone13 = "bt1";//button1

String comdata = "";//import the comdata string
char judge = 0;//init the judge

void setup() {

  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(50); // Set the PWM frequency as 50   
  ///Initialize the motor state
  pwm.setPWM(0, 0, 0);
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  pwm.setPWM(5, 0, 0);
  pwm.setPWM(6, 0, 0);
  pwm.setPWM(7, 0, 0);
  
  delay(100);  // If the information printed out of the serial port is garbled, extend the delay time to solve the problem.
  while (Serial.read() >= 0)
    continue;
  Serial.flush();
  ESP8266_ATCOMMAND();//esp-01 module AT instruction function
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  pinMode(Buzz, OUTPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_L, OUTPUT);
  pinMode(Trig_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT_PULLUP);
  carservo.attach(10);//servo PIN
  carservo.write(65);//Initialize the car head in the middle position
 
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
}

void loop() {

  while (Serial.available() > 0) {
    comdata += char(Serial.read());
    delay(1);
  }
  judgement();
}

// ESP8266 set the AT instructionS
void ESP8266_ATCOMMAND() {

  Serial.print(F("AT+RST\r\n"));  //F(): Store string constants in Flash flash to avoid memory depletion due to SRAM usage.
  delay(3000);
  Serial.print(F("AT+CWMODE=3\r\n"));  //set to softAP+station mode
  delay(300);
  Serial.print(F("AT+CWSAP=\"Cokoino_ESP8266-01\",\"12345678\",11,2\r\n"));//wifiname:Cokoino_ESP8266-01,wifipassword:12345678
 //channnel:11 Encryption mode:2 ;Encryption mode should not set to 1,otherwise the wifi can't set successed
  delay(200);
  Serial.print(F("AT+CIPMUX=1\r\n"));//Enable multiple connections
  delay(200);
  Serial.print(F("AT+CIPSERVER=1,3001\r\n"));//Create the server. The default port is 333. Change the port to 3001, which is consistent with the APP
  delay(200);
  Serial.print(F("AT+CIPSTO=7000\r\n"));//Example Set the server timeout period to 7000 seconds
  delay(2000);
}
void judgement() {

  if (comdata.length() > 0) {
    comdata += "\n";  //This sentence must be added, otherwise the matched command character is one less, and the newline is used to assist in the complete match.
    char buf[comdata.length()];
    comdata.toCharArray(buf, comdata.length());
    ms.Target(buf);
    char result = ms.Match("%c*%+IPD, ?[0-9]+, ?[0-9]+: ?([^%c]+)%c*$");
    if (result > 0) {
      ms.GetCapture(buf, 0);
      comdata = String(buf);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(comdata);
      delay(100);
    } else {
      result = ms.Match("%c*%s?([0-9]),%s?([^%c]+)%c*$");  // esp8266 Multi-channel supports up to 5 connections (id:0-4)
      if (result > 0) {
        char buf0[1];  // esp8266 In multi-channel mode. id of the connection at this time
        ms.GetCapture(buf0, 0);
        ms.GetCapture(buf, 1);
        comdata = String(buf);
        if (comdata == "CONNECT")//The APP successfully connects to the wifi of ESP-01 module
        {
          String receiveOkMs = "Welcome to connect to ESP8266-01, ID: " + String(buf0) + " .";//A successful connection message is displayed
          Serial.println("AT+CIPSEND=" + String(buf0) + "," + receiveOkMs.length() + "\r\n");
          delay(10);
          Serial.print(receiveOkMs);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(String(buf0) + ",CONNECT ");
          delay(1500);
          lcd.setCursor(0, 1);
          lcd.print("MSG_Len:");
          lcd.setCursor(9, 1);
          lcd.print(String(receiveOkMs.length()) + "Bytes");  // If the combined variable is a non-string, it needs to be converted to a string for normal display.
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Available Memory");
          lcd.setCursor(0, 1);
          lcd.print(": " + String(availableMemory()));  // If the combined variable is a non-string, it needs to be converted to a string for normal display.
          delay(2000);
        }
      }

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("WIFI Prepared!");
    }
    //comdata = "";
    //return; // When debugging communication with the APP, it needs to be commented out when normal use

     if (comdata == phone1) {
       judge = 1;
     }
      else if (comdata == phone1_5) {
       judge = 2;
     } else if (comdata == phone2) {
       judge = 3;
     } else if (comdata == phone2_5) {
       judge = 4;
     } else if (comdata == phone3) {
       judge = 5;
     } else if (comdata == phone3_5) {
       judge = 6;
     } else if (comdata == phone4) {
       judge = 7;
     } else if (comdata == phone4_5) {
       judge = 8;
     } else if (comdata == phone5) {
       judge = 9;
     } else if (comdata == phone6) {
       judge = 10;
     } else if (comdata == phone7) {
       judge = 11;
     } else if (comdata == phone8) {
       judge = 12;
     } else if (comdata == phone9) {
       judge = 13;
     } else if (comdata == phone10) {
       judge = 14;
     } else if (comdata == phone11) {
       judge = 15;
     } else if (comdata == phone12) {
       judge = 16;
     } else if (comdata == phone13) {
       judge = 17;
     }
     else {
       judge = 9;
     }
    comdata = "";
  }

  switch (judge) {

    case 1:
      forward();
      delay(50);
      break;
    case 2:
      leftforward();
      delay(50);
      break;
    case 3:
      Left_move();
      delay(50);
      break;
    case 4:
      leftbackward();
      delay(50);
      break;
    case 5:
      backward();
      delay(50);
      break;
    case 6:
      rightbackward();
      delay(50);
      break;
    case 7:
      Right_move();
      delay(50);
      break;
    case 8:
      rightforward();
      delay(50);
      break;
    case 9:
      Stopcar(); 
      break;
    case 10:
      left_rotation();
      delay(50); 
      break; 
    case 11:
      right_rotation();
      delay(50);
      break; 
    case 12:
      track_line(); 
      break; 
    case 13:
      obstacle_avoidance();
      break;  
    case 14:
      light_show(); 
      delay(2000);
      judge = 9;
      break;
    case 15:
      music(); 
      delay(2000);
      judge = 9;
      break;  
   // case 16:
      //follow_light(); 
      //delay(2000);
      //judge = 9;
      // break;  ; 
    case 17:
      shake_head(); 
      delay(2000);
      judge = 9;
      break;   
    default: break;
  }
}

//pwm.setPWM(pwmnum,on, off);
     //(pwmnum, on, off) function is mainly to adjust the output PWM duty cycle.
     // Usually, on is set to 0 and off can be changed.
     // Because the PCA9685 is a 12-bit resolution
     // the value of 0 to 4096 off represents a duty cycle of 0 to 100.
void forward()
{
////The off value is based on the battery level ranging from 7.4V to 8.4V. /////////////////////////////////
////If your battery level is below 7.4V, you can increase the off value to allow the car to move normally.//
 //drive M1 Motror forward，
 pwm.setPWM(2, 0, 1000);//set pwm signal to BIN2 of DRV8833
 pwm.setPWM(3, 0, -1000);//set pwm signal to BIN1 of DRV8833
 //drive M2 Motror forward
 pwm.setPWM(0,0,-1000);//set pwm signal to AIN1 of DRV8833
 pwm.setPWM(1,0,1000);//set pwm signal to AIN2 of DRV8833
 //drive M3 Motror forward
 pwm.setPWM(6, 0, 1000);//set pwm signal to BIN2 of DRV8833
 pwm.setPWM(7, 0, -1000);//set pwm signal to BIN1 of DRV8833
 //drive M4 Motror forward
 pwm.setPWM(4, 0, -1000);//set pwm signal to AIN1 of DRV8833
 pwm.setPWM(5, 0, 1000);//set pwm signal to AIN2 of DRV8833
}
void leftforward()   // Front 45 degrees to the left
{
 pwm.setPWM(0,0,-1500);
 pwm.setPWM(1,0,1500);
 pwm.setPWM(2, 0, 0);
 pwm.setPWM(3, 0, 0);
 pwm.setPWM(4, 0, 0);
 pwm.setPWM(5, 0, 0);
 pwm.setPWM(6, 0, 1500);
 pwm.setPWM(7, 0, -1500);
}
void Left_move()     //car move left
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
void leftbackward() //Back 45 degrees to left
{
 pwm.setPWM(0, 0, 0);
 pwm.setPWM(1, 0, 0);
 pwm.setPWM(2, 0, -1500);
 pwm.setPWM(3, 0, 1500);
 pwm.setPWM(4, 0, 1500);
 pwm.setPWM(5, 0, -1500);
 pwm.setPWM(6, 0, 0);
 pwm.setPWM(7, 0, 0);
}
void backward()  //car move backward
{
 pwm.setPWM(0,0,1000);
 pwm.setPWM(1,0,-1000);
 pwm.setPWM(2, 0, -1000);
 pwm.setPWM(3, 0, 1000);
 pwm.setPWM(4, 0, 1000);
 pwm.setPWM(5, 0, -1000);
 pwm.setPWM(6, 0, -1000);
 pwm.setPWM(7, 0, 1000);
}
void rightbackward() //Back 45 degrees to right
{
 pwm.setPWM(0,0,1500);
 pwm.setPWM(1,0,-1500);
 pwm.setPWM(2, 0, 0);
 pwm.setPWM(3, 0, 0);
 pwm.setPWM(4, 0, 0);
 pwm.setPWM(5, 0, 0);
 pwm.setPWM(6, 0, -1500);
 pwm.setPWM(7, 0, 1500);
}
void Right_move()  //car move to right
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

void rightforward()  //Move 45 degrees right ahead
{
 pwm.setPWM(0, 0, 0);
 pwm.setPWM(1, 0, 0);
 pwm.setPWM(2, 0, 1500);
 pwm.setPWM(3, 0, -1500);
 pwm.setPWM(4, 0, -1500);
 pwm.setPWM(5, 0, 1500);
 pwm.setPWM(6, 0, 0);
 pwm.setPWM(7, 0, 0);
}
void right_rotation()   // car right rotation
{
 pwm.setPWM(0,0,-1500);
 pwm.setPWM(1,0,1500);
 pwm.setPWM(2, 0, -1500);
 pwm.setPWM(3, 0, 1500);
 pwm.setPWM(4, 0, -1500);
 pwm.setPWM(5, 0, 1500);
 pwm.setPWM(6, 0, -1500);
 pwm.setPWM(7, 0, 1500);
}
void left_rotation()   //car left rotation
{
 pwm.setPWM(0,0,1500);
 pwm.setPWM(1,0,-1500);
 pwm.setPWM(2, 0, 1500);
 pwm.setPWM(3, 0, -1500);
 pwm.setPWM(4, 0, 1500);
 pwm.setPWM(5, 0, -1500);
 pwm.setPWM(6, 0, 1500);
 pwm.setPWM(7, 0, -1500);
}
void turnLeft()
{
 pwm.setPWM(0,0,-1000);
 pwm.setPWM(1,0,1000);
 pwm.setPWM(2, 0, 1600);
 pwm.setPWM(3, 0, -1600);
 pwm.setPWM(4, 0, -1000);
 pwm.setPWM(5, 0, 1000);
 pwm.setPWM(6, 0, 1600);
 pwm.setPWM(7, 0, -1600);
}

void turnRight()
{
 pwm.setPWM(0,0,-1600);
 pwm.setPWM(1,0,1600);
 pwm.setPWM(2, 0, 1000);
 pwm.setPWM(3, 0, -1000);
 pwm.setPWM(4, 0, -1600);
 pwm.setPWM(5, 0, 1600);
 pwm.setPWM(6, 0, 1000);
 pwm.setPWM(7, 0, -1000);
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
///////////////////////////////////////////////////////////Automatic obstacle avoidance
void track_line()
{
  u8 trackingSensorVal = 0;
  trackingSensorVal = getTrackingSensorVal(); //get sensor value

  switch (trackingSensorVal)
  {
    case 0:   //000
      backward();//car backward
      delay(10);
      break;
    case 7:   //111
      forward(); //car forward
      break;
    case 1:   //001
      turnRight(); //car turn right
      delay(120);
      break;
    case 3:   //011
      turnRight(); //car turn right     
      delay(120);
      break;
    case 2:   //010
    case 5:   //101
    case 6:   //110
      turnLeft(); //car turn left   
      delay(200);
      break;
    case 4:   //100
     turnLeft();//car turn left   
      delay(200);
      break;
    default:
      break;
  }
}
u8 getTrackingSensorVal() {
  u8 trackingSensorVal = 0;
  trackingSensorVal = (digitalRead(Line_L) == 1 ? 1 : 0) << 2 | (digitalRead(Line_M) == 1 ? 1 : 0) << 1 | (digitalRead(Line_R) == 1 ? 1 : 0) << 0;
  return trackingSensorVal;
}
///////////////////////////////////////////////////////////Automatic obstacle avoidance
void obstacle_avoidance()
{
   digitalWrite(led_R,HIGH);//light the right green LED
   digitalWrite(led_L,HIGH);//light the left green LED
   ultrasonic_distance();
  //Serial.println(distance);
  if(distance>distance_minimum)
    {
    forward();   //forward
    }
  if(distance<=distance_minimum)
    {
    Stopcar();     //stop
    music();       //the buzzer sounds
    servo_wheel(); //The servo rotates, and the ultrasonic module identifies the distance 
                   //of the 65-degree obstacle in the left front of the car body
    if((distance_0<=distance_minimum)&&(distance_130<=distance_minimum))
      {backward();//car backward
      delay(300); }
    if(distance_0<distance_130)//The right obstacle is less distant than the left
      {left_rotation();
      delay(150);
     }
    if(distance_0>distance_130)//The left obstacle is less distant than the right
      {right_rotation();
      delay(150);
      }
    if(distance_0==distance_130)
      {
      randNumber = random(1, 2); //randnumber
      if(randNumber==1)
        {leftforward();delay(120);
       }
      if(randNumber==2)
        {rightforward();delay(120);
       }
      }
    delay(250); 
    Stopcar();     //car stop
    }
}
///////////////////////////////////////////////////////////ultrasonic ranging
void ultrasonic_distance()
{
delay(100); 
digitalWrite(Trig_Pin, HIGH);
delayMicroseconds(10);
digitalWrite(Trig_Pin, LOW);
distance = pulseIn(Echo_Pin, HIGH) * 340 /2/ 10000.0;
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
///////////////////////////////////////////////////////////buzzer sounds
void music()
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
///////////////////////////////////////////////////////////the car shake it's head
void shake_head()
{
  for (pos = 0; pos <= 130; pos += 1) { // goes from 0 degrees to 130 degrees
    // in steps of 1 degree
    carservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 130; pos >= 0; pos -= 1) { // goes from 130 degrees to 0 degrees
    carservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  delay(50);
  carservo.write(65);               //Reset the head of the car
}

int availableMemory() {
  // Use 1024 with ATmega168
  int size = 2048;
  byte *buf;
  while ((buf = (byte *)malloc(--size)) == NULL);
  free(buf);
  return size;
}

///////////////////////////////////////////////////////////light show
void light_show()
{
  LED_show();
  WS2812_show();
}

void LED_show()
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
void WS2812_show()
{
  colorWipe(strip.Color(255, 0, 0), 10); // Red
  delay(600);
  colorWipe(strip.Color(255, 150, 0), 10); // yellow
  delay(600);
  colorWipe(strip.Color(0, 255, 0), 10); // Green
  delay(600);
  colorWipe(strip.Color(0, 255, 255), 10); // CYAN
  delay(600);
  colorWipe(strip.Color(0, 0, 255), 10); // Blue
  delay(600);
  colorWipe(strip.Color(180, 0, 255), 10); // purple
  delay(600);
  colorWipe(strip.Color(127, 127, 127), 10); // White
  delay(600);
  colorWipe(strip.Color(0, 0, 0), 30); // Clear
  Serial.println("OK");
}

void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
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
