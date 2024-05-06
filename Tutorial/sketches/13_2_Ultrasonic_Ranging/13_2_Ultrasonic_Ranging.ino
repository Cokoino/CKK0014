/*****************************************************
 
 * This code applies to 4WD Mecanum Wheels Robot Car Kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0014
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#include  <Servo.h>            //include servo library
 
#define Trig_Pin 13    //define Trig pin
#define Echo_Pin 12    //define Echo pin

#define MAX_DISTANCE    300   //cm
#define SONIC_TIMEOUT   (MAX_DISTANCE*60) // calculate timeout 
#define SOUND_VELOCITY  340  //soundVelocity: 340m/s

Servo carservo;          //create servo object
byte servoOffset = 0;    //change the value to Calibrate servo
u8 distance[4];          //define an arry with type u8(same to unsigned char)

void setup() {
  Serial.begin(9600);
  pinMode(Trig_Pin, OUTPUT);      // set trigPin to output mode
  pinMode(Echo_Pin, INPUT_PULLUP);// set echoPin to input mode
 carservo.attach(10);        //initialize servo 
  carservo.write(65 + servoOffset);  // change servoOffset to Calibrate servo
}

void loop() {
  carservo.write(0);
  delay(1000);
  distance[0] = getSonar();   //get ultrsonice value and save it into distance[0]

  carservo.write(65);
  delay(1000);
  distance[1] = getSonar();

  carservo.write(130);
  delay(1000);
  distance[2] = getSonar();

  carservo.write(65);
  delay(1000);
  distance[3] = getSonar();
  
  Serial.print("Distance R / M / L / M2:   ");  //Left/Middle/Right/Middle2
  for (int i = 0; i < 4; i++) {
    Serial.print(distance[i]);     //print ultrasonic in 0°, 65°, 130°, 65°
    Serial.print("/");
  }
  Serial.print('\n');  //next content will be printed in new line
}

float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(Trig_Pin, HIGH); // make trigPin output high level lasting for 10μs to triger HC_SR04,
  delayMicroseconds(10);
  digitalWrite(Trig_Pin, LOW);
  pingTime = pulseIn(Echo_Pin, HIGH, SONIC_TIMEOUT); // Wait HC-SR04 returning to the high level and measure out this waitting time
  if (pingTime != 0)
    distance = (float)pingTime * SOUND_VELOCITY / 2 / 10000; // calculate the distance according to the time
  else
    distance = MAX_DISTANCE;
  return distance; // return the distance value
}
