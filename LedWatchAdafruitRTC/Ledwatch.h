
//Pin Definitions
int IRsensor=2;
int ShiftEn=5;
int dataPin=9;
int latchPin=7;
int clockPin=8;
int led=13;
int RTCen=10;
int MinBtn=3;
int HourBtn=4;
bool HourBtnState;
bool MinBtnState;

//Variables definition
byte data1;
byte data2;
byte dataArray1[16];
byte dataArray2[16];
byte HoursArray[16];
byte MinutesArray[16];
byte SecondsArray[16];
int Hour;
int Minute;
int HourSet;
int MinuteSet;
int Second;
int IRsense;
int AwakeFlag;
long currentmillis;
long currentmillisbtn;
long prevmillis = 0;
long prevmillisbtn = 0;


long AwakeInterval=20000;
long DebounceInterval=200;
int BtnFlag;
int DisplayFlag;
int LedFlag;
int SetTimeFlag;
String time;

//RTC values
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }
    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
 //stop shifting
  digitalWrite(myClockPin, 0);
}

//The function takes numbers from 1 to 60 
//and matches them to 1 to 12 in increments of 5
int FixingNumberRange(int x){
int y;

    if (x<=4){
     y=12;
     }
   if((x>=4)&&(x<=9)) {
        y=1;
      }
    if((x>=10)&&(x<=14)){
      y=2;
     }
   if((x>=15)&&(x<=19)){
        y=3;
      }
    if((x>=20)&&(x<=24)){
        y=4;
      }  
   if((x>=25)&&(x<=29)){
        y=5;
      }  
  if((x>=30)&&(x<=34)){
        y=6;
      }
  if((x>=35)&&(x<=39)){
        y=7;
      }  
   if((x>=40)&&(x<=44)){
        y=8;
      }
   if((x>=45)&&(x<=49)){
        y=9;
      }
   if((x>=50)&&(x<=54)){
        y=10;
      }
   if((x>=55)&&(x<=59)){
        y=11;
      }                           
      return y;
}




