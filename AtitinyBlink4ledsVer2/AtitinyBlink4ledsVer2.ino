
int led = 3;
int led1 = 4;
int led2 = 2;
int led3= 0;


// the setup routine runs once when you press reset:
void setup() {                
 
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT); 
 pinMode (led2, OUTPUT); 
  pinMode (led3, OUTPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  

 digitalWrite(led,HIGH);
 delay(100);
  digitalWrite(led1,HIGH);
 delay(100);
  digitalWrite(led2,HIGH);
 delay(100);
  digitalWrite(led3,HIGH);
  delay(50);
 digitalWrite(led,LOW);
 delay(100);
  digitalWrite(led1,LOW);
 delay(100);
  digitalWrite(led2,LOW);
 delay(100);
  digitalWrite(led3,LOW);
  delay(50);
   digitalWrite(led,HIGH);
 delay(100);
  digitalWrite(led1,HIGH);
 delay(100);
  digitalWrite(led2,HIGH);
 delay(100);
  digitalWrite(led3,HIGH);
  delay(50);
 digitalWrite(led,LOW);
 delay(100);
  digitalWrite(led1,LOW);
 delay(100);
  digitalWrite(led2,LOW);
 delay(100);
  digitalWrite(led3,LOW);
  delay(50);
  digitalWrite(led,HIGH);
 delay(100);
  digitalWrite(led1,HIGH);
 delay(100);
  digitalWrite(led2,HIGH);
 delay(100);
  digitalWrite(led3,HIGH);
 delay (20);
 digitalWrite(led,LOW);
 delay(20);
  digitalWrite(led1,LOW);
 delay(20);
  digitalWrite(led2,LOW);
 delay(20);
  digitalWrite(led3,LOW);
 delay (20);
  digitalWrite(led,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  delay(500);
 
  
  
   }
 
  

