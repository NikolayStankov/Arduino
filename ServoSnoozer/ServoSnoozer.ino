#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;

int potpin= 0;  // analog pin used to connect the potentiometer
int Potval;    // variable to read the value from the analog pin
unsigned long TimeSet;
int ServoDegree=80;
void ButtonClick(void);
void setup() {
myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  
}

void loop() {

 ReadInputs();
 
 ButtonClick();
 delay(TimeSet);
                    
}

void ButtonClick(void)
{
  
  myservo.write(ServoDegree);
  delay(250);
  myservo.write(120);
  myservo.write(118);// Use a second value to return the gears a bit to avoid the shaking noise
  
}


void ReadInputs(void)
{
  TimeSet = analogRead(potpin);
 TimeSet = map(TimeSet, 0, 1023, 60, 360);
 TimeSet= TimeSet*1000;
}



