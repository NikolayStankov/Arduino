
int led = 2;
int led1 = 1;
int led2 = 0;
int led3 = 10;
int led4 = 9;
int led5 = 8; 
int buttonPin=3;

// the setup routine runs once when you press reset:
void setup() {                
 
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT); 
 pinMode (led2, OUTPUT); 
  pinMode (led3, OUTPUT);
  pinMode (led4,OUTPUT);
  pinMode (led5,OUTPUT);
  pinMode (buttonPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
 
 digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led5,HIGH);
  delay (250);
  digitalWrite(led,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);
  delay(250);
  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led5,HIGH);
  delay (250);
  digitalWrite(led,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);
  delay (250);
  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led5,HIGH);
  delay(250);
   digitalWrite(led,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);
  delay (500);
  digitalWrite (led,HIGH);
  delay (500);
  digitalWrite (led,LOW);
  delay (500);
  digitalWrite (led1,HIGH);
  delay (500);
  digitalWrite (led1,LOW);
  delay (500);
  digitalWrite (led2,HIGH);
  delay (500);
  digitalWrite (led2,LOW);
  delay (500);
  digitalWrite (led3,HIGH);
  delay (500);
  digitalWrite (led3,LOW);
  delay (500);
  digitalWrite (led4,HIGH);
  delay (500);
  digitalWrite (led4,LOW);
  delay (500);
  digitalWrite (led5,HIGH);
  delay (500);
  digitalWrite (led5,LOW);
  
  
  
   }
 
  

