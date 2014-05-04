#include <Servo.h> 

//Inputs/outputs 
#define L1 3
#define L2 4
#define LPWM 5
#define RPWM 6
#define R1 7
#define R2 8
//#define ping 10
#define LedPin  13 


byte Lspeed1=255;
byte Rspeed2=255;
int danger;
int range;
int rotatePos;
Servo rotateServo;  //180= look right   0=look left



//-------------------------------------------------------------------------- 
void setup() {  
   
  // set motor pins as output and LOW so the motors are braked 
  Serial.begin(38400);
  pinMode(L1,OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(RPWM, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);  
  danger=250; 
  rotateServo.attach(11);
  rotateServo.write(90); //90 degrees, looking straight ahead 
  pinMode(LedPin, OUTPUT);       
  digitalWrite(LedPin, LOW); 
  motorSpeed(255,255);  
}

void loop()
{
  autonomous();
  //forward();
 // rightSlide();
  //fireSonar();
  //delay(1000);
}


void autonomous()
{
  for (rotatePos=20;rotatePos<160;rotatePos+=10)
  {
    rotateServo.write(rotatePos);
    delay(50);
    fireSonar();
    checkRange();
  }
  for (rotatePos=160;rotatePos>20;rotatePos-=10)
  {
    rotateServo.write(rotatePos);
    delay(50);
    fireSonar();    
    checkRange();
  }   
}



void checkRange()
{
  if (range>danger)
  {
    if (rotatePos<45)
    {
      leftSlide();
    }
    if (rotatePos>44 && rotatePos<91)
    {
      leftSpin();
    }
    if (rotatePos>90 && rotatePos<135)
    {
      rightSpin();
    }
    if (rotatePos>134)
    {
      rightSlide();
    }   
  }else{
    forward(); 
  }
  fireSonar();   
  if (range>danger)
  { 
  checkRange();  
  }
}
 

void motorSpeed(int thisLeft,int thisRight)
{
  analogWrite(LPWM,thisLeft);
  analogWrite(RPWM,thisRight);
}

void fireSonar()
{
  range=analogRead(A7);
  //Serial.println(range);
}

void forward()
{
  digitalWrite(L1,HIGH);
  digitalWrite(L2,LOW);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);
}

void reverse()
{
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);  
}

void leftSlide()
{
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);  
}

void rightSlide()
{
  digitalWrite(L1,HIGH);
  digitalWrite(L2,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);  
}

void leftSpin()
{
  digitalWrite(L1,LOW);
  digitalWrite(L2,HIGH);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);    
}

void rightSpin()
{
  digitalWrite(L1,HIGH);
  digitalWrite(L2,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);    
}

void allStop()
{
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);  
}


