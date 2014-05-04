#include <Time.h>
#include <SPI.h>
#include <TCL.h>

//working right now :)

//display time using dots of colors on a strand of 25 TCL LEDS from Cool Neon
//also with added ablility to set the time with one pushbutton and two pots

//enter starting time varibles here
int hr = 16;//24hr hour
int mi = 27;//minutes
int sec = 0;//seconds
int dayofmonth = 12;//day in month (not day of week)
int monthNumber = 6;//number of month
int yr = 2013;//year

const int LEDS = 25; // This assumes that there are 25 LEDs in the TCL strand.
const int update_interval = 100; // Milliseconds between color updates

/* Current values for the pixels are stored in the following three arrays */
byte red_values[LEDS];
byte green_values[LEDS];
byte blue_values[LEDS];

//variable to store previous second
//int oldSecond;

//variables to store each digit
int digitA;
int digitB;
int digitC;
int digitD;

//array of which LEDS are dedicated to each digit
const int ldigitA[1] = {1};
const int ldigitB[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
const int ldigitC[5] = {11, 12, 13, 14, 15};
const int ldigitD[9] = {16, 17, 18, 19, 20, 21, 22, 23, 24};

//int secDot;

int hourVal = 0;
int minVal = 0;
int hourValmilit;

/*
//pin #s for the setting buttons
const int hourSetPin = 9;
const int minSetPin = 10;*/

const int settingPin = 12;


const int hourPotPin = A4;
const int minPotPin = A5;

//to store if it is in setting mode or not
boolean isSetting = true;

int AMstate;

/*
//variables to store state of the setting buttons
int hourButtonState = 0;
int minButtonState = 0;

int hourButtonVal = 0;
int minButtonVal = 0;
int oldHourButtonVal = 0;
int oldMinButtonVal = 0;
*/
int settingButtonVal = 0;


void setup(){

  //begin the TCL library and setup the strand
  //TCL.begin();
  
  //pinMode(hourSetPin, INPUT);
 // pinMode(minSetPin, INPUT);
  pinMode(settingPin, INPUT);
  
  //Serial if we need it
  //Serial.begin(9600);
  
  //put into setting mode automatically
  //isSetting = true;
  
 // readPotsAndSet();
  
  
  
  //setting time
  //setTime(hr,mi,sec,dayofmonth,monthNumber,yr);
  
  //begin the TCL library and setup the strand
  TCL.begin();
 
}

void loop(){

  settingMode();
  
  
  //get values for the hour and minute
  getTimeVals();
  
  
  /*if(Serial.available() == true){
    showSerial();
  }*/
  //show the time based on the values
  showTime();
  
  /*if(Serial.available() == true){
    showSerial();
  }*/
  
  //delay
  delay(update_interval);

}

void showTime(){
  
  
  findDigits();
  
  //first make all LED values black before changing specific ones
  for(int bl = 0; bl < LEDS; bl++){
  
    red_values[bl] = 0x00;
    green_values[bl] = 0x00;
    blue_values[bl] = 0x00;
    
  }
  //set digitA LEDs
  for(int dA = 0; dA < digitA; dA++){
    
    red_values[ldigitA[dA]] = 0x00;
    green_values[ldigitA[dA]] = 0x00;
    blue_values[ldigitA[dA]] = 0xff;
    
  }
  //set digitB LEDs
  for(int dB = 0; dB < digitB; dB++){
    
    red_values[ldigitB[dB]] = 0x00;
    green_values[ldigitB[dB]] = 0xff;
    blue_values[ldigitB[dB]] = 0x00;
    
  }
  //set digitC LEDs
  for(int dC = 0; dC < digitC; dC++){
    
    red_values[ldigitC[dC]] = 0x7f;
    green_values[ldigitC[dC]] = 0x7f;
    blue_values[ldigitC[dC]] = 0x00;
    
  }
  //set digitD LEDs
  for(int dD = 0; dD < digitD; dD++){
    
    red_values[ldigitD[dD]] = 0xff;
    green_values[ldigitD[dD]] = 0x00;
    blue_values[ldigitD[dD]] = 0x00;
    
  }
  if(AMstate == 1){
    red_values[0] = 0x7f;
    green_values[0] = 0x40;
    blue_values[0] = 0x00;
    
  }else{
    red_values[0] = 0x7f;
    green_values[0] = 0x00;
    blue_values[0] = 0x7f;
  }
  
  
  //update the new color values to the LED strand
  update_strand();
}

void findDigits(){
  
  //find digits of hourVal
  if(hourVal > 19){
    digitA = 2;
    digitB = hourVal - 20;
   }
   else if(hourVal > 9){
     digitA = 1;
     digitB = hourVal - 10;
   }
   else{
     digitA = 0;
     digitB = hourVal;
   }
   
   //find digits of the minVal
   if(minVal > 49){
     digitC = 5;
     digitD = minVal - 50;
   }else if(minVal > 39){
     digitC = 4;
     digitD = minVal - 40;
   }else if(minVal > 29){
     digitC = 3;
     digitD = minVal - 30;
   }else if(minVal > 19){
     digitC = 2;
     digitD = minVal - 20;
   }else if(minVal > 9){
     digitC = 1;
     digitD = minVal - 10;
   }else{
     digitC = 0;
     digitD = minVal;
   }
  
  
}
/*
void showSerial(){
  Serial.print(digitA);
  Serial.print(digitB);
  Serial.print(":");
  Serial.print(digitC);
  Serial.println(digitD);
}*/ 

void getTimeVals(){
  hourVal = hourFormat12();
  minVal = minute();
  if(isAM() == true){
    AMstate = 1;
  }else{AMstate = 0;}
}


//function to push out the new color values to each LED on the strand
void update_strand() {
  int i;

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(red_values[i],green_values[i],blue_values[i]);
  }
  TCL.sendEmptyFrame();
  delay(1);
}

void readPotsAndSet(){

  //hourVal = map(analogRead(hourPotPin), 0, 1023, 0, 12);
  hourValmilit = map(analogRead(hourPotPin), 0, 1023, 0, 23);
  minVal = map(analogRead(minPotPin), 0, 1023, 0, 59);
  if(hourValmilit > 12){
    AMstate = 0;
    hourVal = hourValmilit - 12;
  }else if (hourValmilit == 0){
    AMstate = 1;
    hourVal = 12;
  }else if(hourValmilit == 12){
    AMstate = 0;
    hourVal  = 12;
  }
  else{
    AMstate = 1;
    hourVal = hourValmilit;
  }
  
  //hr = hourVal;
  //mi = minVal;

}

void settingMode(){

  while(isSetting == true){
    
    settingButtonVal = digitalRead(settingPin);
    
    //hourButtonVal = digitalRead(hourSetPin);
    //minButtonVal = digitalRead(minSetPin);
    
    //see if setting is done
    if(settingButtonVal == HIGH){
      //hr = hourVal;
      //mi = minVal;
      
      hr = hourValmilit;
      mi = minVal;
      setTime(hr,mi,sec,dayofmonth,monthNumber,yr);
      
      isSetting = false;
      delay(1);
    }
    
    readPotsAndSet();
    
    /*
    //checking hour button state
    if((hourButtonVal == HIGH) && (oldHourButtonVal == LOW)){
      hourButtonState = 1 - hourButtonState;
      delay(10);
    } 
    //OLD VAL
    oldHourButtonVal = hourButtonVal;
    
    
    //checking minute button state
    if((minButtonVal == HIGH) && (oldMinButtonVal == LOW)){
      minButtonState = 1 - minButtonState;
      delay(10);
    }
    //OLD VAL
    oldMinButtonVal = minButtonVal;
    
    if((hourButtonState == 1) && (hourVal < 23)){
      hourVal++;
    } else if((hourButtonState == 1) && (hourVal == 23)){
      hourVal = 0;
    }
    
    if((minButtonState == 1) && (minVal < 59)){
      minVal++;
    } else if((minButtonState == 1) && (minVal == 59)){
      minVal = 0;
    }*/
    
    /*hr = hourVal;
    mi = minVal;
    setTime(hr,mi,sec,dayofmonth,monthNumber,yr);
    */
    //showTime();
    
    //oldHourButtonVal = hourButtonVal;
    //oldMinButtonVal = minButtonVal;
    
    showTime();
    
    //delay(100);
  }

}
