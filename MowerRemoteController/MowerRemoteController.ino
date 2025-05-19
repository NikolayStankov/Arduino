#include <printf.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

char xyData[32] = "";
int FBControl=A1;
int LRControl=A0;
int Btn=6;
RF24 radio(7,8);
const byte address[6] = "00011";
String FBReading;
String LRReading;
String Transmit;
bool CutterOn;

void setup() {
  Serial.begin(9600);
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter

  pinMode(FBControl,INPUT);
  pinMode(LRControl,INPUT);
  pinMode(Btn,INPUT);
}

void loop() {
  FBReading=analogRead(FBControl);
  LRReading=analogRead(LRControl);
  CutterOn=digitalRead(Btn);
  
//LRReading=map(LRReading,897,87,0,255);
//FBReading=map(FBReading,948,60,0,255);
  
 Serial.print(" LRReading ");
 Serial.print(" FBReading ");
 Serial.print(" CutterOn ");
 Serial.println("") ;
 Serial.print(LRReading);
 Serial.print("             ") ;
 Serial.print(FBReading);
 Serial.print("             ") ;
 Serial.print(CutterOn);
 Serial.println("");


 FBReading.toCharArray(xyData,5);
 radio.write(&xyData, sizeof(xyData));  //Sending the message to receiver
 LRReading.toCharArray(xyData,5);
 radio.write(&xyData, sizeof(xyData));
 radio.write(&CutterOn, sizeof(CutterOn));

 delay (200);


  
}
