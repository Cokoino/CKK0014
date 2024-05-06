
/****************************************************
4WD Mecanum Wheels Robot Car Kit
            
        M4 (------) M3         
-------------|  |-----------------
-------------|  |-----------------
        M2 (------) M1
****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup(){
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); // Set the PWM frequency  
  pwm.setPWM(0,0,0);
  pwm.setPWM(1,0,0);
  pwm.setPWM(2,0,0); 
  pwm.setPWM(3,0,0);
  pwm.setPWM(4,0,0); 
  pwm.setPWM(5,0,0); 
  pwm.setPWM(6,0,0);
  pwm.setPWM(7,0,0);              
}
  
void Leftfront_wheel_run()
{
  //drive Leftfront_wheel forward
     pwm.setPWM(4,0,-3000);//set pwm signal to AIN1 of DRV8833
     pwm.setPWM(5,0,3000);//set pwm signal to AIN2 of DRV8833
     delay(2000);
  //drive Leftfront_wheel backward
     pwm.setPWM(4,0,3000);//set pwm signal to AIN1 of DRV8833
     pwm.setPWM(5,0,-3000);//set pwm signal to AIN2 of DRV8833
     delay(2000);
}
void Leftback_wheel_run()
{
  // drive Leftback_wheel forward
     pwm.setPWM(0,0,-3000); //set pwm signal to BIN2 of DRV8833
     pwm.setPWM(1,0,3000);//set pwm signal to BIN1 of DRV8833
     delay(2000);
  // drive Leftback_wheel backward
     pwm.setPWM(0,0,3000); //set pwm signal to BIN2 of DRV8833
     pwm.setPWM(1,0,-3000);//set pwm signal to BIN1 of DRV8833
     delay(2000);
}
void Rightfront_wheel_run()
{
   // drive Rightfront_wheel forward
     pwm.setPWM(6,0,3000); //set pwm signal to BIN2 of DRV8833
     pwm.setPWM(7,0,-3000);//set pwm signal to BIN1 of DRV8833
     delay(2000);
  // drive Rightfront_wheel backward
     pwm.setPWM(6,0,-3000); //set pwm signal to BIN2 of DRV8833
     pwm.setPWM(7,0,3000);//set pwm signal to BIN1 of DRV8833
     delay(2000);
}
void Rightback_wheel_run()
{
  // drive Rightback_wheel forward
     pwm.setPWM(2,0,3000); //set pwm signal to BIN2 of DRV8833
     pwm.setPWM(3,0,-3000);//set pwm signal to BIN1 of DRV8833
     delay(2000);
  // drive Rightback_wheel backward
     pwm.setPWM(2,0,3000); //set pwm signal to BIN2 of DRV8833
     pwm.setPWM(3,0,-3000);//set pwm signal to BIN1 of DRV8833
     delay(2000);
}
void loop()
{ 
  // Leftfront_wheel_run();     //M4 Motor
   Leftback_wheel_run();   //M2 Motor
   //Rightfront_wheel_run(); //M3 Motor
  //Rightback_wheel_run();  //M1 Motor

}
