//Atmega88 used for testing, using a modified bootloader to use arduino

//this is a base program for using the TA8080 motor drivers on 
//the bug-like chassis

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

void setup(){

  //setup ledpin as output in case it is needed
  pinMode(ledpin, OUTPUT);
  
  //setup buttonpin as input
  pinMode(buttonpin, INPUT);
  
  //setup all the motor control pins as outputs
  for(int p = 0; p < sizeof(motorPins); p++){
    pinMode(motorPins[p], OUTPUT);
  }
  
  
  while(digitalRead(buttonpin) == LOW){
    
    //do nothing until the button is pressed and goes HIGH and breaks the loop
    //then the program goes into the loop()
  }
  

}

void loop(){
  
  //put looping code here as usual
  
  
  
  
}

/*********INDIVIDUAL MOTOR FUNCTIONS*********/

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

/*********FUNCTIONS USING BOTH MOTORS*********/

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
