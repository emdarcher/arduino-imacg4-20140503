//#include <Servo.h>
//#include <NewPing.h>

//#define TRIGGER_PIN  12
//#define ECHO_PIN     11
//#define MAX_DISTANCE 200

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


//this is a base program for using the TA8080 motor drivers on
//the bug-like chassis

#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//constant ints for the motor controlling pins, change if needed
const int RmotorApin = 6;
const int RmotorBpin = 5;
const int LmotorApin = 8;
const int LmotorBpin = 7;

//setup int for pin 13 LED, could be used for debugging or something like status
const int ledpin = 13;

//button for initializing the start of the program
const int buttonpin = 4;

int motorPins[4] = {RmotorApin, RmotorBpin, LmotorApin, LmotorBpin};

unsigned int distIn;
int thresholdIn = 10;

int degPos;
int degStep = 10;
int stepDelay = 20;

int sweepDegMax = 160;
int sweepDegMin = 10;

int servopin = 9;
Servo neckServo;

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup(){
  
  //find minimum sweep degrees
  //sweepDegMin = 180 - sweepDegMax;
  
  //setup servo
  neckServo.attach(servopin);
  
  //put to 90 degrees
  neckServo.write(90);
  delay(50);

  //setup ledpin as output in case it is needed
  pinMode(ledpin, OUTPUT);
  
  //setup buttonpin as input
  pinMode(buttonpin, INPUT);
  
  //setup all the motor control pins as outputs
  for(int p = 0; p < sizeof(motorPins); p++){
    pinMode(motorPins[p], OUTPUT);
  }
  
  digitalWrite(ledpin, HIGH);
  
  while(digitalRead(buttonpin) == LOW){
    
    //do nothing until the button is pressed and goes HIGH and breaks the loop
    //then the program goes into the loop()
  }
  

}

void loop(){
  
  //put looping code here as usual
  
  autonomous();
  
  
}

//autonomous code
void autonomous(){

  for(degPos = sweepDegMin; degPos < sweepDegMax; degPos += degStep){
    neckServo.write(degPos);
    delay(stepDelay);
    getDistIn();
    obstacleAvoid();
  }
  for(degPos = sweepDegMax; degPos > sweepDegMin; degPos -= degStep){
    neckServo.write(degPos);
    delay(stepDelay);
    getDistIn();
    obstacleAvoid();
  }
  
}
//determining which way to turn
void obstacleAvoid(){

  if(distIn < thresholdIn){
    if(degPos < 45){
    leftPivot();
    }
    if(degPos > 44 && degPos < 91){
    leftSpin();
    }
    if(degPos > 90 && degPos < 135){
    rightSpin();
    }
    if(degPos > 134){
    rightPivot();
    }
  }else{
  allFwd();
  }
  getDistIn();
  if(distIn < thresholdIn){
    obstacleAvoid();
  }

}
//gettng distance in inches from ultrasonic sensor
void getDistIn(){

  distIn = sonar.ping_in();
  //delay(5);
  
}

void leftPivot(){

  LmotorStop();
  RmotorFwd();
  
}

void leftSpin(){
  LmotorRev();
  RmotorFwd();
}

void rightPivot(){
  LmotorFwd();
  RmotorStop();
}

void rightSpin(){
  LmotorFwd();
  RmotorRev();
}

///////////////////////STUFF_FROM_BASE_CODE//////////////////////

//*********INDIVIDUAL MOTOR FUNCTIONS*********/

//make Right motor spin forward
void RmotorFwd(){

  digitalWrite(RmotorApin, HIGH);
  digitalWrite(RmotorBpin, LOW);
  
}

//make Left motor spin forward
void LmotorFwd(){
  
  digitalWrite(LmotorApin, HIGH);
  digitalWrite(LmotorBpin, LOW);
  
}

//reverse Right motor
void RmotorRev(){
  
  digitalWrite(RmotorApin, LOW);
  digitalWrite(RmotorBpin, HIGH);
  
}

//reverse Left motor
void LmotorRev(){
   
  digitalWrite(LmotorApin, LOW);
  digitalWrite(LmotorBpin, HIGH);
    
}

//stop Right motor
void RmotorStop(){
  
  digitalWrite(RmotorApin, LOW);
  digitalWrite(RmotorBpin, LOW);
  
}

//stop Left motor
void LmotorStop(){
  
  digitalWrite(LmotorApin, LOW);
  digitalWrite(LmotorBpin, LOW);
  
}

//brake Right motor
void RmotorBrake(){
  
  digitalWrite(RmotorApin, HIGH);
  digitalWrite(RmotorBpin, HIGH);
  
}

//brake Left motor
void LmotorBrake(){
  
  digitalWrite(LmotorApin, HIGH);
  digitalWrite(LmotorBpin, HIGH);
  
}

//*********FUNCTIONS USING BOTH MOTORS*********/

//both go forward
void allFwd(){
  
  RmotorFwd();
  LmotorFwd();
  
}

//both go reverse
void allRev(){
  
  RmotorRev();
  LmotorRev();
  
}

//both stop
void allStop(){
  
  RmotorStop();
  LmotorStop();
  
}

//both brake
void allBrake(){

  RmotorBrake();
  LmotorBrake();
  
}
