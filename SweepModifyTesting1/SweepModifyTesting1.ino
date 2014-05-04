// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
int degreesSweep = 160; 
 
int degStep = 10;
 
 int sweepDelay = 30;
 
 //button for initializing the start of the program
const int buttonpin = 4;


void setup() 
{ 
  pinMode(buttonpin, INPUT);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  
  //start at 90 degrees
  myservo.write(90);
  
  while(digitalRead(buttonpin) == LOW){
   //do nothin
  }
} 
 
 
void loop() 
{ 
  for(pos = 180 - degreesSweep; pos < degreesSweep; pos += degStep)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(sweepDelay);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = degreesSweep; pos>=1; pos-= degStep)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(sweepDelay);                       // waits 15ms for the servo to reach the position 
  } 
} 
