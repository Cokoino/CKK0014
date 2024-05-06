/*****************************************************
 
 * This code applies to 4WD Mecanum Wheels Robot Car Kit kit
 * Through this link you can download the source code:
 * https://github.com/Cokoino/CKK0014
 * Company web site:
 * http://cokoino.com/
 
*****************************************************/

//Tenor NTF 0 is an empty beat
#define NTF0 -1
#define NTF1 350
#define NTF2 393  
#define NTF3 441
#define NTF4 495
#define NTF5 556
#define NTF6 624
#define NTF7 661

//High pitch NTFH
#define NTFH1 700
#define NTFH2 786
#define NTFH3 882
#define NTFH4 935
#define NTFH5 965
#define NTFH6 996
#define NTFH7 1023

//Low pitch NTFH
#define NTFL1 175
#define NTFL2 196
#define NTFL3 221
#define NTFL4 234
#define NTFL5 262
#define NTFL6 294
#define NTFL7 330
//Note frequency array
int tune[]=
{
  NTF3,NTF3,NTF3,NTF3,NTF3,NTF3,
  NTF3,NTF5,NTF1,NTF2,NTF3,NTF0,
  NTF4,NTF4,NTF4,NTF4,NTF4,NTF3,NTF3,NTF3,NTF3,
  NTF5,NTF5,NTF4,NTF2,NTF1,NTF0,

  NTFL5,NTF3,NTF2,NTF1,NTFL5,NTF0,NTFL5,NTFL5,
  NTFL5,NTF3,NTF2,NTF1,NTFL6,NTF0,
  NTFL6,NTF4,NTF3,NTF2,NTFL7,NTF0,
  NTF5,NTF5,NTF4,NTF2,NTF3,NTF1,NTF0,

  NTFL5,NTF3,NTF2,NTF1,NTFL5,NTF0,
  NTFL5,NTF3,NTF2,NTF1,NTFL6,NTF0,NTFL6,
  NTFL6,NTF4,NTF3,NTF2,NTF5,NTF5,NTF5,NTF5,
  NTF6,NTF5,NTF4,NTF2,NTF1,NTF0
};
//Note beat array
float durt[]=
{
  0.5,0.5,1,0.5,0.5,1,
  0.5,0.5,0.75,0.25,1.5,0.5,
  0.5,0.5,1,0.5,0.5,0.5,0.5,0.25,0.25,
  0.5,0.5,0.5,0.5,1.5,0.5,

  0.5,0.5,0.5,0.5,1,0.5,0.25,0.25,
  0.5,0.5,0.5,0.5,1,1,
  0.5,0.5,0.5,0.5,1,1,
  0.5,0.5,0.5,0.5,1,0.75,0.25,

  0.5,0.5,0.5,0.5,1,1,
  0.5,0.5,0.5,0.5,1,0.5,0.5,
  0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
  0.5,0.5,0.5,0.5,0.75,0.25
};
//Define the buzzer pin, note length variable
int buzzer_pin = 11;
int length;

//initializes the pin and calculates the length
void setup()
{
  pinMode(buzzer_pin, OUTPUT);
  length = sizeof(tune)/sizeof(tune[0]);
}

//loop
void loop()
{
  //for looping
  for(int x=0;x<length;x++)
  {
    tone(buzzer_pin, tune[x]);
    delay(500*durt[x]);         //The 500 here controls the length of each note to determine the rhythm of the piece
    noTone(buzzer_pin);
  }
  delay(500);               //The interval between starting the next cycle

}
