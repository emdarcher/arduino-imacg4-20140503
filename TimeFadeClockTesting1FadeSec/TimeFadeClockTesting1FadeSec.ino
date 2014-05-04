#include <Time.h>
#include <SPI.h>
#include <TCL.h>



//display time using fading of colors on a strand of 25 TCL LEDS from Cool Neon
//

//enter starting time varibles here
int hr = 14;//24hr hour
int mi = 41;//minutes
int sec = 00;//seconds
int dayofmonth = 12;//day in month (not day of week)
int monthNumber = 6;//number of month
int yr = 2013;//year

const int LEDS = 25; // This assumes that there are 25 LEDs in the TCL strand.
const int update_interval = 100; // Milliseconds between color updates

/* Current values for the pixels are stored in the following three arrays */
byte red_values[LEDS];
byte green_values[LEDS];
byte blue_values[LEDS];

//variables for the mapped values for fading the colors
byte minFadeVal;
byte secFadeVal;

//variable to store previous second
int oldSecond;

void setup(){

  //Serial if we need it
  //Serial.begin(9600);
  
  //setting time
  setTime(hr,mi,sec,dayofmonth,monthNumber,yr);
  
  //begin the TCL library and setup the strand
  TCL.begin();
 
}

void loop(){

  //show the time
  showTime();
  
  //delay
  delay(update_interval);

}

void showTime(){
  
  
  //first make all LED values black before changing specific ones
  for(int bl = 0; bl < LEDS; bl++){
  
    red_values[bl] = 0x00;
    green_values[bl] = 0x00;
    blue_values[bl] = 0x00;
    
  }
  
  //set the leds of the total hours to green color
  for(int h = 0; h <= hour(); h++){
    red_values[h] = 0x00;
    green_values[h] = 0xff;
    blue_values[h] = 0x00;
    
  }
  
  //stuff for the LED after the hour LED, this fades to show the progression
  //of the minutes in the hour
  minFadeVal = map(minute(),0x00,0x3c,0x00,0xff);
  
  red_values[hour() + 1] = 0xff - minFadeVal;
  green_values[hour() + 1] = minFadeVal;
  blue_values[hour() + 1] = 0x00;
  
  //stuff for the last LED in Strand to fade to show progression of the seconds
  //in the minute
  secFadeVal = map(second(),0x00,0x3c,0x00,0xff);
  
  red_values[24] = secFadeVal;
  green_values[24] = 0x00;
  blue_values[24] = 0x00 - secFadeVal;
  
  
  
  /*if(second() != oldSecond){
    
    red_values[24] = 0x00;
    green_values[24] = 0x00;
    blue_values[24] = 0xff;
    
  }  
  
  oldSecond = second();*/
  
  //update the new color values to the LED strand
  update_strand();
}



//function to push out the new color values to each LED on the strand
void update_strand() {
  int i;

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(red_values[i],green_values[i],blue_values[i]);
  }
  TCL.sendEmptyFrame();
}


