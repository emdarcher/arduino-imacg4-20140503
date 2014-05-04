#include <Time.h>
#include <SPI.h>
#include <TCL.h>



//display time on an lcd display

//enter starting time varibles here
int hr = 14;//24hr hour
int mi = 23;
int sec = 0;
int dayofmonth = 12;
int monthNumber = 6;
int yr = 2013;

const int LEDS = 25; // This assumes that there are 25 LEDs in the TCL strand.
const int update_interval = 100; // Milliseconds between color updates

/* Current values for the pixels are stored in the following three arrays */
byte red_values[LEDS];
byte green_values[LEDS];
byte blue_values[LEDS];

byte minFadeVal;

int oldSecond;

void setup(){

  //Serial if we need it
  Serial.begin(9600);
  //setting time
  setTime(hr,mi,sec,dayofmonth,monthNumber,yr);
  
  TCL.begin();
 
}

void loop(){

  showTime();
  
  delay(update_interval);

}

void showTime(){
  
  
  //first make all LED values black before changing specific ones
  for(int bl = 0; bl < LEDS; bl++){
  
    red_values[bl] = 0x00;
    green_values[bl] = 0x00;
    blue_values[bl] = 0x00;
    
  }
  
  for(int h = 0; h <= hour(); h++){
    red_values[h] = 0x00;
    green_values[h] = 0xff;
    blue_values[h] = 0x00;
    
  }
  
  //stuff for the LED after the hour LED, this fades to show minute relatively
  minFadeVal = map(minute(),0x00,0x3c,0x00,0xff);
  
  red_values[hour() + 1] = 0xff - minFadeVal;
  green_values[hour() + 1] = minFadeVal;
  blue_values[hour() + 1] = 0x00;
  
  //secFadeVal = map(second(),0x00,0x3c,0x00,0xff);
  
  
  
  if(second() != oldSecond){
    
    red_values[24] = 0x00;
    green_values[24] = 0x00;
    blue_values[24] = 0xff;
    
  }  
  
  oldSecond = second();
  
  update_strand();
}




void update_strand() {
  int i;

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(red_values[i],green_values[i],blue_values[i]);
  }
  TCL.sendEmptyFrame();
}


