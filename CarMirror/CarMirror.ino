// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;
Servo myservo1;// create servo object to control a servo 
 
int potpin = 1;
int potpin1 = 0;// analog pin used to connect the potentiometer
int val; 
int val1;// variable to read the value from the analog pin 
 
void setup() 
{ 
  myservo.attach(6);
  myservo1.attach(5);
  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  val = analogRead(potpin); 
 val1 = analogRead(potpin1); // reads the value of the potentiometer (value between 0 and 1023)
  
  val = map(val, 0, 1023, 0, 57); 
val1 = map(val1, 0, 1023, 0, 120);  // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val); 
myservo1.write(val1);  // sets the servo position according to the scaled value 
  delay(20);                           // waits for the servo to get there 
} 
