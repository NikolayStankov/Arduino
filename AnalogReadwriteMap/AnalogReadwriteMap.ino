int ledPin = 13;
int analogPin = 1;
int val = 0;
void setup() {
  pinMode (ledPin, OUTPUT);
}
  
 void loop() {
  // read the input on analog pin 0:
  val = analogRead(analogPin);
  val= map(val, 1023, 0 ,0 ,255);
  
digitalWrite(ledPin,HIGH);
  delay(val/4);   
digitalWrite (ledPin,LOW);
delay(val/20);
}


