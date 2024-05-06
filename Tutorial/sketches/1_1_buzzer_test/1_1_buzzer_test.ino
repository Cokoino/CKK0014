/*****************************************************
 
 * This code applies to 4WD Mecanum Wheels Robot Car Kit kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0014
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/

#define buzzer_pin 11    //buzzer PIN is 11 on the control board

void setup()
{
  Serial.begin(9600);//Set baud rate
  pinMode(buzzer_pin, OUTPUT);//Set pin 11 to output mode and input signals to the buzzer
}

void loop() 
{
  for(int i = 0;i < 80; i++)
  {
    //The high and low levels constitute a square-wave signal that triggers the passive buzzer to work
    digitalWrite(buzzer_pin, HIGH);
    delay(1);
    digitalWrite(buzzer_pin, LOW);
    delay(1);
  }
  for(int j = 0;j< 100; j++)
  {
    digitalWrite(buzzer_pin, HIGH);
    delay(2);
    digitalWrite(buzzer_pin, LOW);
    delay(2);
  }
}
