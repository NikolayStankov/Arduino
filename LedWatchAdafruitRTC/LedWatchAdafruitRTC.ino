#include "RTClib.h"
#include <Wire.h>
#include "Ledwatch.h"
#include "LedArrays.h"
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
void ISR2(void);


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              void setup() {
 
//pinMode (IRsensor,INPUT);
pinMode(IRsensor,INPUT_PULLUP);
pinMode(MinBtn,INPUT_PULLUP);
pinMode(HourBtn,INPUT_PULLUP);
pinMode(latchPin,OUTPUT);
pinMode(dataPin,OUTPUT);
pinMode(clockPin,OUTPUT);
pinMode(ShiftEn,OUTPUT);
pinMode(RTCen,OUTPUT);
DefineTimeValues();
attachInterrupt(digitalPinToInterrupt(IRsensor),ISR2,HIGH);
AwakeFlag=0;
DisplayFlag=0;
digitalWrite(RTCen,HIGH);


  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
 }
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
 
}


void loop() {
  switch (AwakeFlag){
    
  case 0:
  digitalWrite(led,LOW);
       digitalWrite(ShiftEn,HIGH);//Disable shift registers
       digitalWrite(RTCen,LOW); //Turn off board power to rtc
      //Putting all leds down and the controller to sleep  
        Hour=0;
        Minute=0;
        Second=0; 
        dispSeconds();
        dispMinutes();
        dispHours(); 
        SleepNow();   
  break;

  case 1:
     digitalWrite(ShiftEn,LOW);//Enable Shift registers
     digitalWrite(RTCen,HIGH);//Enable RTC for reading  
     
     DateTime now = rtc.now();   
     Hour=now.hour(),DEC;
     Minute=now.minute(),DEC;
     Second=now.second(),DEC;
     //LedFlag=0;
     if (LedFlag==0)
    {
     dispHours();
     LedFlag=1;
     }
     if (LedFlag==1)
     { 
     dispMinutes();
     LedFlag=2;
     }
     if(LedFlag==2)
     {
     dispSeconds();
     LedFlag=0;
     }
     digitalWrite(led,LOW); 
   
     break; 
  }   
  Timers();
  Butttons();
  /*
   Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  */
 

}

void SleepNow(){
  attachInterrupt(digitalPinToInterrupt(IRsensor),ISR2,HIGH);
  sleep_enable(); 
  AwakeFlag=0;
  DisplayFlag=0;
  sei();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  power_adc_disable();
  //power_spi_disable();
 // power_twi_disable();
  //power_all_disable();
  sleep_cpu();
}

void ISR2(){
  if(AwakeFlag==0){
  cli();
  sleep_disable();
  power_all_enable();
  AwakeFlag=1;
  DisplayFlag=1;
  digitalWrite(led,HIGH); 
  }  
}

void Timers(void)
{
  currentmillis = millis();//Value for the millis() counter
  currentmillisbtn=currentmillis;
  //Interval for displaying and keeping the device awake
  if ((currentmillis - prevmillis) > AwakeInterval)
  {
   DisplayFlag=0;
   AwakeFlag=0;
    prevmillis = currentmillis;
  }
  if ((currentmillisbtn - prevmillisbtn) > DebounceInterval){
    BtnFlag=0;
   // LedFlag=0;
    prevmillisbtn = currentmillisbtn;
  }
}

void Butttons(void){

  HourBtnState=digitalRead(HourBtn);
  MinBtnState=digitalRead(MinBtn);

 if ((MinBtnState==LOW)&&(BtnFlag==0))
 {
  digitalWrite(led,HIGH); 
  DateTime now = rtc.now(); 
  MinuteSet=MinuteSet+1;
   MinuteSet=now.minute(),DEC;  
   BtnFlag=1;
  SetTimeFlag=1;
 }

 if ((HourBtnState==LOW)&&(BtnFlag==0))
 {
  digitalWrite(led,HIGH); 
  DateTime now = rtc.now();
  HourSet=HourSet+1;   
  HourSet=now.hour(),DEC;  
     
  BtnFlag=1;
  SetTimeFlag=1;
  
 }
 
 if(SetTimeFlag==1){
  //if (! rtc.isrunning()) { 
 rtc.adjust(DateTime(2018, 1, 21, Hour, Minute, 0));
 rtc.begin();
 SetTimeFlag=0;
 // }
 
 }
}




