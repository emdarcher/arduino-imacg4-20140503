//attiny hello world 1 led on a 74HC595 shift register

// the pins to control the shift register
const int latchPin = 0;
const int clockPin = 1;
const int dataPin = 2;

int shiftpins[4] = {latchPin, clockPin, dataPin};

int shiftnum = B00000001;

const int ledpin = 3;

void setup(){

  pinMode(ledpin, OUTPUT);
  
  //setup the pins
  for(int sp = 0; sp < sizeof(shiftpins); sp++){
  
    pinMode(shiftpins[sp], OUTPUT);
    delay(1);
    
  }
  
}

void loop(){

  //set the latch low
  digitalWrite(latchPin, LOW);
  
  //shift out the number
  shiftOut(dataPin, clockPin, MSBFIRST, shiftnum);
 
  //set latch to high to output the number
  digitalWrite(latchPin, HIGH);
   
  digitalWrite(ledpin, HIGH); 
  
  delay(1000);
 
  digitalWrite(latchPin, LOW);
 
  //shift nothing or 0
  shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
 
  digitalWrite(latchPin, HIGH);
 
  digitalWrite(ledpin, LOW);
 
  delay(1000); 
  
}
