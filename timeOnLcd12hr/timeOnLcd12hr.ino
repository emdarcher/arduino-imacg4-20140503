#include <Time.h>
#include <LiquidCrystal.h>


//display time on an lcd display

//enter starting time varibles here
int hr = 13;//24hr-time hour
int mi = 30;
int sec = 0;
int dayofmonth = 12;
int monthNumber = 6;
int yr = 2013;

//lcd stuff
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){

  //Serial if we need it
  Serial.begin(9600);
  //setting time
  setTime(hr,mi,sec,dayofmonth,monthNumber,yr);
  //setup lcd
  lcd.begin(16,2);

}

void loop(){

  
  showDate();
  showTime();
  
  delay(50);

}

void showDate(){

  lcd.setCursor(0,0);
  
  lcd.print("Date: ");
  zeroPrintString(month());
  lcd.print("-");
  zeroPrintString(day());
  lcd.print("-");
  zeroPrintString(year());
  
  
}

void showTime(){

  
  lcd.setCursor(0,1);
  
  lcd.print("Time: ");
  zeroPrintString(hourFormat12());
  lcd.print(":");
  zeroPrintString(minute());
  lcd.print(":");
  zeroPrintString(second());
  //lcd.clear();
  if(isAM() == true){
    lcd.print("AM");
  }else{
    lcd.print("PM");
  }
  
}

int zeroPrintString(int num){
  if (num < 10){
    lcd.print("0" + String(num));
  }
  else{
    lcd.print(String(num));
  }
}
