/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = A5;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  analogWrite(led, 25);  
 delay(100);           
 analogWrite(led, 50);  
 delay(100);       
analogWrite(led, 100);
 delay(100);         
analogWrite(led, 150);  
 delay(100);         
analogWrite(led, 200);  
 delay(100);          
  analogWrite(led, 254);    // turn the LED off by making the voltage LOW
  delay(100);           

  // wait for a second
}
