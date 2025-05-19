
#include <SoftwareSerial.h>

int Output1 = 8;
int Output2 = 5; //Change to 5
int LedPin =13;
int IntPin = 3;
int IntFlag = 0;
int ExtractFlag;
int DisplayFlag;
int SerialFlag;
int MainState;
int PumpState;
int FanState;
long currentmillis;
long prevmillis = 0;
long prevmillisDisplay = 0;
long SerialInterval = 500;
volatile byte Commstate = LOW;
String stream;
String SetTemp;
int SetTempValue;
int SetTempPrev;
String FanSpeed;
int FanSpeedValue;
int FanSpeedValuePrev;
String Temp;
int TempValue;
int TempValuePrev;
void ISRState(void);
void ExtractSetTemp(void);
void ExtractFanSpeed(void);
void ExtractTemp(void);
void OutputManager(void);
void InputManager(void);
void Timers(void); 
void setup() {
  
  pinMode (Output1, OUTPUT);
  pinMode (Output2, OUTPUT);
  pinMode (IntPin, INPUT);
  pinMode (LedPin, OUTPUT); 
  MainState=0;
  PumpState=0;
  attachInterrupt(digitalPinToInterrupt(IntPin), ISRState, HIGH);
  Serial.begin(9600);
}
  
 void loop() {
  
   switch (MainState) 
   {
    case 0:
    Timers();
    
    MainState=1;
    break;
    
    case 1:
    InputManager();
    MainState=2;
    break;
    
    case 2:
    ExtractTemp();
    ExtractSetTemp();
    ExtractFanSpeed();
    MainState=3;
    break;
    
    case 3:
    OutputManager();
    MainState=4;
    break;
    
    case 4:
    
    MainState=0;
    break;
   
   }
  
  
//digitalWrite(Output2,HIGH);
//delayMicroseconds(20);
//digitalWrite(Output2,LOW); 
//delayMicroseconds(1);
}




void InputManager(void)
{
   stream = Serial.readStringUntil('D'); 
}

void OutputManager(void) 
{

  if(SetTempValue!=SetTempPrev)
  {
       if(SetTempValue<TempValue)
       {
        PumpState=0;
        FanState=1;
       }
       
   SetTempPrev=SetTempValue;
  }
  else 
  {  
    PumpState=1;
    FanState=0;
  }
  

//if (PumpState==1){
//  FanState=1;
//}
    
  switch(PumpState){
    case 0:
    digitalWrite(Output1,HIGH);
    break;
    
    case 1:
    digitalWrite(Output1,LOW);
    break;
  }
  

  //Manage the Fan according to settings
  

 switch (FanState) {

 case 0: //Case the SetTemp is higher than Current temp
  analogWrite(Output2,0);
  break;
   
 case 1: //Case the SetTemp is Lower than Current temp
  
  switch (FanSpeedValue){ //cases received in the serial comm.
   
    case 1:
    analogWrite(Output2,0);
     break;
    case 2:
     analogWrite(Output2,47); 
    break;
    case 3:
    analogWrite(Output2,72);   
    break;
    case 4:
    analogWrite(Output2,108);
    break;
    case 5:
   analogWrite(Output2,144);
    break;
    case 6:
     analogWrite(Output2,180);
    break;
    case 7:
   analogWrite(Output2,216);
    break;
    case 8:
    analogWrite(Output2,255);
    break;
    case 9:
     analogWrite(Output2,0);
    break ;  
  }
  break;
 }
}

void ExtractSetTemp (void)
{
  SetTemp=stream;
  SetTemp.remove(0,1);
  SetTemp.remove(2,5);
  SetTempValue=(SetTemp.toInt());
 
if(SetTempValue!=0){
  Serial.println("SetTemp:");
  Serial.println(SetTempValue);
  SetTemp.remove(0,4);
 }
}


void ExtractFanSpeed(void)
{
  FanSpeed=stream;
  FanSpeed.remove(0,4);
  FanSpeed.remove(1,3);
  FanSpeedValue=(FanSpeed.toInt());
 
  
  
  if(FanSpeedValue!=0){
  Serial.println("FANSpeed:");
  Serial.println(FanSpeedValue);
  FanSpeed.remove(0,1);
  }
}

void ExtractTemp(void)
{
  Temp=stream;
  Temp.remove(0,6);
  TempValue=(Temp.toInt());
  
  if(TempValue!=0){
  Serial.println("CurrentT:");
  Serial.println(TempValue);
  Temp.remove(0,1);
  }
}

void Timers(void)
{
  currentmillis = millis();//Value for the millis() counter
  //Debounce timer for the buttons used in the device
  //Used for PWM

  //Interval for displaying temperatures and Serial Communication
  if ((currentmillis - prevmillisDisplay) > SerialInterval)
  {
   SerialFlag=0;
    prevmillisDisplay = currentmillis;
  }
  
}

void ISRState(void)
{
  int i=0;
  
  if (i==0){
  Commstate=!Commstate;
  i++;
  }
  if(i==1){
    i--;
  }
  
  if(Commstate==HIGH)
  {
    digitalWrite (LedPin,LOW);
  }
  else {
    if(Commstate==LOW)
    {
     digitalWrite(LedPin,HIGH);
    }
  }
}
