/****************************************************
* Shifting numers from 0 to 255 on 1 sec intervals
*****************************************************/

int latchPin = 1 ;
int clockPin = 2 ;
int dataPin = 0 ;
int Minutes = 0;
int Seconds = 0;
long interval= 1000;
long prevmillis= 0;
int shiftstate = LOW;
int blinkflag;

void setup() {
  
  pinMode (latchPin, OUTPUT);
  pinMode (clockPin, OUTPUT);
  pinMode (dataPin, OUTPUT);
}

void loop () {
 
  unsigned long currentmillis = millis(); 

if(currentmillis - prevmillis >interval)
  { 
  Seconds++;
  prevmillis = currentmillis;
   digitalWrite (latchPin ,LOW);
  }
 
  
   if(Seconds > 59)
  {
    Seconds=0;
    Minutes++; 
  }
  
  if(Minutes > 59)
  {
    Minutes = 0;
  }
     
   shiftOut (dataPin, clockPin, MSBFIRST,Minutes); 
   digitalWrite (latchPin ,HIGH);  
 
}


