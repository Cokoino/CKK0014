/*****************************************************
 
 * This code applies to 4WD Mecanum Wheels Robot Car Kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0014
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/
#define LED_R 6
#define LED_L 9

void setup() {
  pinMode(LED_R,OUTPUT);  
  pinMode(LED_L,OUTPUT);  
}
void loop() {
digitalWrite(LED_R,HIGH);//turn on right green LED
digitalWrite(LED_L,HIGH);//turn on left green LED
delay(1000);
digitalWrite(LED_R,LOW);//turn off right green LED
digitalWrite(LED_L,LOW);//turn off left green LED
delay(1000);
}
