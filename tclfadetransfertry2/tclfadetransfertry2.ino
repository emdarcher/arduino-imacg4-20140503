#include <SPI.h>
#include <TCL.h>


//testing total control lighting from cool neon
//made by Ethan Durrant, FIRST team 4159
//trying to fade through colors


//ints for rgb values
byte rval = 0x00;
byte gval = 0x00;
byte bval = 0x00;

byte oldrval = 0x00;
byte oldgval = 0x00;
byte oldbval = 0x00;

//ints for rgb activity
int ract = 0;
int gact = 0;
int bact = 0;

int phase = 0;

//LED amount
const int LEDs = 25;

//transition amount per step
int trans = 0x8;

void setup() {

  //setup spi
  TCL.begin();
  //rval = 0xff;
  phase = 0;
  //oldrval = 0xa;


}


void loop() {

  //clear strip
   TCL.sendEmptyFrame();
   
   //for(int i = 0; i < LEDs; i++) {
   
     fadetrans();
     //colorize();
     //cwrite();
   //}
   //TCL.sendEmptyFrame();
   
   

delay(0);
}

void fadetrans() {

  //int phase = 0;
  /*if((rval == 0x00) && (gval == 0x00)){
    for(rval; rval <= 0xff; rval+=trans) {
  
      bval = 0xff - rval;
      cwrite();
      cclear();
      delay(50);
  
    }
  }*/
  if(phase == 4){
    phase = 0;
    cclear();
    delay(1);
  }
  
  else if(phase == 0/*(gval == 0x00) && (bval == 0x00) && (rval == 0xff)*/){
    
    for(int g=0x00; g <= 0xff; g+=trans) {
  
      gval = g;
      rval = 0xff - gval;
      //gval = g;
      //bval = 0x00;
      //rval = 0xff - gval;
      cwriteAll();
      cclear();
      delay(50);
  
  
    }
    //phase = 1; 
  }
  
  else if(phase == 1/*(bval == 0x00) && (rval == 0x00) && (gval == 0xff)*/){
    for(int b=0x00; b <= 0xff; b+=trans) {
  
      bval = b;
      gval = 0xff - bval;
      //bval = b;
      //rval = 0x00;
      //gval = 0xff - bval;
      cwriteAll();
      cclear();
      delay(50);
  
    }
    //phase = 2;
  }
  
  else if(phase == 2 /*(rval == 0x00) && (gval == 0x00) && (bval == 0xff)*/){
    for(int r=0x00; r <= 0xff; r+=trans) {
  
      rval = r;
      bval = 0xff - rval;
      //rval = r;
      //gval = 0x00;
      //bval = 0xff - rval;
      cwriteAll();
      cclear();
      delay(50);
  
    }
    //phase = 0;
  }
  
  else if(phase == 3/*(gval == 0x00) && (bval == 0x00) && (rval == 0xff)*/){
    
    for(int g=0x00; g <= 0xff; g+=trans) {
  
      gval = g;
      rval = 0xff - gval;
      //gval = g;
      //bval = 0x00;
      //rval = 0xff - gval;
      cwriteAll();
      cclear();
      delay(50);
  
  
    }
  }
  
  phase = phase + 1;
  delay(10);
  

}

void cwriteAll() {
  for(int l = 0; l < LEDs; l++) {
    cwrite();
  }
  delay(50);
}

void cwrite() {

  //send colors
  TCL.sendColor(rval,gval,bval);
  delay(1);

}

void cclear() {
  
  //clear
  TCL.sendEmptyFrame();
  delay(10);
  
}


