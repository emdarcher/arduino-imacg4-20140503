//attiny84 code for testing l293d with attiny
//for prototyping MoTiny

const byte fwdSpeed = 255;
const byte turnSpeed = 255;
//if turn speed = 255
//a delay of 645 gets close to right angle turn on a spin turn


//pin numbers for led and motor controller (l293d)
const int iledpin = 6;
const int LmotorA = 8;
const int LmotorB = 10;
const int RmotorA = 7;
const int RmotorB = 9;

const int buttonpin = 5;

int iledState = 0;

int pins[6] = {iledpin, LmotorA, LmotorB, RmotorA, RmotorB};

void setup(){

  pinMode(buttonpin, INPUT);
  
  for(int p = 0; p < sizeof(pins); p++){
    
    pinMode(pins[p], OUTPUT);
    delay(5);
    
  }
  
  
  
  while(digitalRead(buttonpin) == LOW){
    /*for(int b = 0; b < 255; b++){
      analogWrite(iledpin, b);
      delay(10);
    }
    for(int nb = 255; nb > 0; nb--){
      analogWrite(iledpin, nb);
      delay(10);
    }*/
    //wait for button press
  }
  

}

void loop(){

  digitalWrite(iledpin, HIGH);
  
  forward(fwdSpeed);
  delay(1000);
  
  allStop();
  delay(50);
  
  Rspin(turnSpeed);
  delay(645);
  
  allStop();
  delay(50);

}

void forward(byte fs){

  analogWrite(LmotorA, fs);
  digitalWrite(LmotorB, LOW);
  analogWrite(RmotorA, fs);
  digitalWrite(RmotorB, LOW);
  
}

void reverse(byte rs){

  analogWrite(LmotorA, 255 - rs);
  digitalWrite(LmotorB, HIGH);
  analogWrite(RmotorA, 255 - rs);
  digitalWrite(RmotorB, HIGH);
  
}

void Rspin(byte rsp){

  analogWrite(LmotorA, rsp);
  digitalWrite(LmotorB, LOW);
  analogWrite(RmotorA, 255 - rsp);
  digitalWrite(RmotorB, HIGH);

}

void Lspin(byte lsp){

  analogWrite(LmotorA, 255 - lsp);
  digitalWrite(LmotorB, HIGH);
  analogWrite(RmotorA, lsp);
  digitalWrite(RmotorB, LOW);
  
}

void Rpivot(byte rps){

  analogWrite(LmotorA, rps);
  digitalWrite(LmotorB, LOW);
  digitalWrite(RmotorA, HIGH);
  digitalWrite(RmotorB, HIGH);
  
}

void Lpivot(byte lps){

  digitalWrite(LmotorA, HIGH);
  digitalWrite(LmotorB, HIGH);
  analogWrite(RmotorA, lps);
  digitalWrite(RmotorA, LOW);
  
}

void allStop(){

  digitalWrite(LmotorA, LOW);
  digitalWrite(LmotorB, LOW);
  digitalWrite(RmotorA, LOW);
  digitalWrite(RmotorB, LOW);
  
}

void allBrake(){

  digitalWrite(LmotorA, HIGH);
  digitalWrite(LmotorB, HIGH);
  digitalWrite(RmotorA, HIGH);
  digitalWrite(RmotorB, HIGH);
  
}





