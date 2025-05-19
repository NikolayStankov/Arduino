#include <Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int LedPin = 9;
  int pingPin = 11;//Trigger Pin
  int inPin = 10 ;// Echo Pin
  long microseconds;
  long CM;
  int centimeters;
  int distance;
  long cm;
  
void setup() {
 // put your setup code here, to run once:
 //Setting up the pins here
 pinMode(9,OUTPUT);
 pinMode(pingPin, OUTPUT);
 pinMode(inPin, INPUT);
 //End of pins setup
 
//Code for the gyro and i2c 
   Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
// Code for the transmission ends here.
  
  }

void loop() {
  
   long duration, inches, cm;
  
digitalWrite(pingPin, LOW);
delayMicroseconds(2); 
digitalWrite(pingPin, HIGH); 
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
duration = pulseIn(inPin, HIGH);
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
CM =(cm);//(cm + 2);   
LedOnIfValueSmall(CM,50);
GyroMeasurement ();

delay(100);

}

int LedOnIfValueSmall (int centimeters,int distance)
{
  if (centimeters<distance){
    digitalWrite(LedPin,HIGH);
  }
  else {
   digitalWrite(LedPin,LOW) ;
  }
   
}

long microsecondsToInches(long microseconds)
{ 
  return microseconds / 74 / 2; 
}

long microsecondsToCentimeters(long microseconds)
  { 
  return microseconds / 29 / 2;
  }

void GyroMeasurement ()
  {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
}



