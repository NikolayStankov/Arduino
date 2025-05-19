
/*Програма за инициализиране и връщане на резултат в serial monitor от ултразвуков 
сензор за разстояние*/

int pingPin = 3; //Включваш към дигитален пин 3 (triger)
int inPin = 2; //Включваш към дигитален пин 2 (echo)
long microseconds;

void setup() { Serial.begin(9600); }

void loop() {

  long duration, inches, cm;
  
digitalWrite(pingPin, LOW);
delayMicroseconds(2); 
digitalWrite(pingPin, HIGH); 
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
pinMode(pingPin, OUTPUT);
pinMode(inPin, INPUT);
duration = pulseIn(inPin, HIGH);
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
Serial.print(inches);
Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();
delay(100); }

long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }

long microsecondsToCentimeters(long microseconds)

{ return microseconds / 29 / 2; }
