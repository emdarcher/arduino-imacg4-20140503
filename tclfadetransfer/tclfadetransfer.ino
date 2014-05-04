#include <SPI.h>
#include <TCL.h>


//testing total control lighting from cool neon
//made by Ethan Durrant, FIRST team 4159
//trying to fade through colors
//DOESN'T WORK AS OF 5-22-13

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

//LED amount
const int LEDs = 25;

//transition amount per step
int trans = 0xa;

void setup() {

  //setup spi
  TCL.begin();
  rval = 0xff;
  oldrval = 0xa;


}


void loop() {

  //clear strip
   TCL.sendEmptyFrame();
   
   for(int i = 0; i < LEDs; i++) {
   
     colorize();
     //cwrite();
   }
   //TCL.sendEmptyFrame();
   
   

delay(100);
}

void colorize() {
  
  
  //cycle through red -> green -> blue and back in loop
  
  
  
  
  if((rval < 0xff) && (rval > oldrval)) {
  
    rval = rval + trans;
    bval = 0xff - rval;
    gval = 0x00;
    
  }
  
  else if((gval < 0xff) && (gval > oldgval)) {
  
    gval = gval + trans;
    rval = 0xff - gval;
    bval = 0x00;
  
  }
  
  else if((bval < 0xff) && (bval > oldbval)) {
  
    bval = bval + trans;
    gval = 0xff - bval;
    rval = 0x00;
  
  }
  
  else if((rval < 0xff) && (rval < oldrval)) {
   
   rval = rval - trans;
   gval = 0xff - rval;
    
  }
  
  else if((gval < 0xff) && (gval < oldgval)) {
   
   gval = gval - trans;
   bval = 0xff - gval;
    
  }
  
  else if((bval < 0xff) && (bval < oldbval)) {
   
   bval = bval - trans;
   rval = 0xff - bval;
    
  }
  
  
  
  
  
  
  //if rval reaches high and has increased, then step it down
  else if((rval == 0xff) && (rval > oldrval) /*&& (bval == 0x00)*/) {
  
    rval = rval - trans;
    gval = 0xff - rval;
    
  }
  else if((gval == 0xff) && (gval > oldgval) /*&& (rval == 0x00)*/) {
  
    gval = gval - trans;
    bval = 0xff - gval;
    
  
  }
  else if((bval == 0xff) && (bval > oldbval) /*&& (gval == 0x00)*/) {
  
    bval = bval - trans;
    rval = 0xff - bval;
    
  
  }
  else {
  
 //set all low
    /*rval = 0xff;
    gval = 0x00;
    bval = 0x00;
    oldrval = 0x00;
    */
  }
  
  oldrval = rval;
  oldgval = gval;
  oldbval = bval;
  
  //use color sending function
  cwrite();
  delay(100);
}

void cwrite() {

  //send colors
  TCL.sendColor(rval,gval,bval);

}


