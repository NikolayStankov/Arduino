#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//Definitions for radio module
//int CNS=8;
//int CE=7;
RF24 radio(7,8); // CE, CSN
const byte address[6] = "00011";
char receivedData[32] = "";

//Definitions Motor1
int Mot1PWM=3;
int Mot1Dir=4;
int Mot1Speed;
//Definitions Motor2
int Mot2PWM=5;
int Mot2Dir=6;
int Mot2Speed;
//Common Motor Pins
int MotStop=2; // Active LOW
int MotBrake=9;//Active HIGH 
//Speed data for motors from receiver
int FBReading;
int LRReading;
int MotorSpeedLeft;
int MotorSpeedRight;
int CutterOn;

void setup() {
//Radio Module Init
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MAX);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver

//Motor pin definitions 
pinMode(Mot1PWM,OUTPUT);
pinMode(Mot2PWM,OUTPUT);
pinMode(Mot1Dir,OUTPUT);
pinMode(Mot2Dir,OUTPUT);
pinMode(MotStop,OUTPUT);
pinMode(MotBrake,OUTPUT);
digitalWrite(MotBrake,LOW);//Disable Break
MotorSpeedLeft=0;
MotorSpeedRight=0;
FBReading=0;
LRReading=0;

}

void loop() {

  if (radio.available())              //Looking for the data.
  {
  radio.read(&receivedData, sizeof(receivedData));//Reading the data
  FBReading=atoi(&receivedData[0]);
  delay(10);
  radio.read(&receivedData, sizeof(receivedData));//Reading the data
  delay(10);
  LRReading= atoi(&receivedData[0]);
  delay (10);
  radio.read(&CutterOn, sizeof(CutterOn));
  delay (10);
  }
  
  
  
if (CutterOn == 0){ 
  
//MotorSpeedLeft=map(FBReading,897,87,0,75);
//MotorSpeedRight=map(FBReading,948,60,0,75);

MotorSpeedLeft=map(FBReading,87,897,0,255);
MotorSpeedRight=map(FBReading,60,948,0,255);


if (MotorSpeedLeft<=0){
  MotorSpeedLeft=0;
}
if (MotorSpeedRight<=0){
  MotorSpeedRight=0;
}
analogWrite(Mot1PWM,MotorSpeedLeft);
analogWrite(Mot2PWM,MotorSpeedRight);
digitalWrite(Mot1Dir,LOW);//Forward
digitalWrite(Mot2Dir,LOW);//Forward  
 
 Serial.print(" MotorSpeedLeft ");
 Serial.print(" MotorSpeedRight ");
 Serial.print(" CutterOn ");
 Serial.println("") ;
 Serial.print(MotorSpeedLeft);
 Serial.print("             ") ;
 Serial.print(MotorSpeedRight);
 Serial.print("             ") ;
 Serial.print(CutterOn);
 Serial.println("");
delay (200);

}



}
