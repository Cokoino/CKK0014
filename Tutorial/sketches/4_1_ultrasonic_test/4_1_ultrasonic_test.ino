/*****************************************************
 
 * This code applies to 4WD Mecanum Wheels Robot Car Kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0014
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#define Trig 13 //Tring pin connect to  IO D13
#define Echo 12 //Echo pin connect to IO D12 
float cm; //Distance variable
float temp; 
 
void setup() 
{
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}
 
void loop() 
{
  //Send a short, low-high-low pulse to the Trig
  digitalWrite(Trig, LOW); //Send a low level to Trig (initialize)
  delayMicroseconds(2);    
  digitalWrite(Trig,HIGH); //Send a high level to Trig
  delayMicroseconds(10);   
  digitalWrite(Trig, LOW); 
  
  temp = float(pulseIn(Echo, HIGH)); //Store the echo wait time
  //The pulseIn function waits for the pin to become HIGH, 
  //starts calculating the time, and then waits for the pin to become LOW and stops timing
  
  //The speed of sound is 340m/1s converted to 34000cm / 1000000μs = 34/1000
  //Because it's one way to send to receive, we only need one way, so ➗2
  //Distance (cm) = (Echo time * (34/1000)) / 2
  //The simplified calculation formula is (echo time * 17)/ 1000
  
  cm = (temp * 17 )/1000; //Convert echo time to distance cm
 
  Serial.print(" | | Distance = ");
  Serial.print(cm);//The output distance of serial port is converted to cm
  Serial.println("cm");
  delay(100);
}
