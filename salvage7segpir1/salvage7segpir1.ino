

//using salvaged vcr player led 7 seg display
//it works!

int trigl =0;

int oldButtonState;
int buttonState = 0;
int timesp = 0;

const int buttonPin = A3;

const int numeral[11] = {
  //sABCDEFG
  B10000001, //0
  B11001111, //1
  B10010010, //2
  B10000110, //3
  B11001100, //4
  B10100100, //5
  B10100000, //6
  B10001111, //7
  B10000000, //8
  B10001100, //9
  B01111111, //10 stuff
};
//                          G  F  E   D C B A 
const int segmentPins[] = {13,12,11,10,9,8,7,A0};

const int nbrDigits = 5;

//                                m 1 2 3 4 
const int digitPins[nbrDigits] = {2,6,5,4,3};

void setup(){

  for(int i=0; i<8; i++){
  
    pinMode(segmentPins[i], OUTPUT);
    
  }
  
  for(int i=0; i<nbrDigits; i++){
    pinMode(digitPins[i], OUTPUT);
  }
  
  pinMode(buttonPin, INPUT);
  
}

void loop(){
  //int value =42;
  //int value = analogRead(1);
  //showNumber(value);
  
  if(digitalRead(buttonPin) == HIGH){
    buttonState = 1;
  } else if(digitalRead(buttonPin) == LOW){
    buttonState = 0;
  }
  if((buttonState == 1) && (oldButtonState == 0)){
    timesp++;
  } else if((buttonState == 1) && (oldButtonState == 1)){
    showDigit(10,0);
  }
  oldButtonState = buttonState;
  showNumber(timesp);
  //showDigit(10, 0);
  
  
 
  //delay(50);
}

void showNumber(int number){

  if(number ==0){
    showDigit(0,nbrDigits-1);
  }else{
    //leftmost digit is 0, right is one less than number of spaces
    for(int digit = nbrDigits-1; digit >=0; digit--){
      if(number > 0){
        showDigit(number % 10, digit);
        number = number / 10;
      }
    }
  }
}

//display number at digit
void showDigit(int number,  int digit){
  digitalWrite(digitPins[digit],HIGH);
  for(int segment = 0;segment < 8; segment++){
    boolean isBitSet = bitRead(numeral[number], segment);
    //isBitSet will be true if given bit is 1
    //isBitSet = ! isBitSet; //remove if common cathode
    digitalWrite( segmentPins[segment], isBitSet);
    
  }
  delay(5);
  digitalWrite(digitPins[digit], LOW);
}
