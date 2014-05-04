#include <SPI.h>
#include <TCL.h>


//sketch to change color of cool neon TCL lighting LEDS using 3 potentiometers

//pins  for pots
const int rpotpin = A3;
const int gpotpin = A4;
const int bpotpin = A5;

int rval;
int gval;
int bval;

byte rvalb;
byte gvalb;
byte bvalb;



const int LEDS = 25; // This assumes that there are 25 LEDs in the TCL strand.
const int update_interval = 100; // Milliseconds between color updates


void setup(){

  TCL.begin();
  Serial.begin(9600);
  writeLEDS();
}

void loop(){
  //TCL.sendEmptyFrame();
  
  rvalb = analogRead(rpotpin)>>2;
  gvalb = analogRead(gpotpin)>>2;
  bvalb = analogRead(bpotpin)>>2;
  
  
  /*rvalb = map(rval, 0x00, 0x3ff, 0x00, 0xff);
  gvalb = map(gval, 0x00, 0x3ff, 0x00, 0xff);
  bvalb = map(bval, 0x00, 0x3ff, 0x00, 0xff);*/
  
  writeLEDS();
  
  serialDisplay();
  
  delay(update_interval);
  
  //TCL.sendEmptyFrame();

}

void writeLEDS(){

  TCL.sendEmptyFrame();
  for(int i = 0; i < LEDS; i++){
  
    TCL.sendColor(rvalb, gvalb, bvalb);
    delay(1);
  }
 TCL.sendEmptyFrame();
}

void serialDisplay(){

  Serial.print("byte red = ");
  Serial.print(rvalb);
  Serial.print(" byte green = ");
  Serial.print(gvalb);
  Serial.print(" byte blue = ");
  Serial.println(bvalb);
  
}

/*
AREA FOR COLOR NOTES:

natural whitish light 1: (255, 197, 27)
very whitish light 1: (255, 197, 51)






*/
