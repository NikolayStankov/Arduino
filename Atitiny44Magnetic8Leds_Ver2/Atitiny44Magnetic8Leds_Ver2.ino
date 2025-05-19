
int led = 10;
int led1 = 0;
int led2 = 9;
int led3 = 2;
int led4 = 8;
int led5 = 1;
int led6 = 3;
int led7 = 4;



// the setup routine runs once when you press reset:
void setup() {                
 
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT); 
 pinMode (led2, OUTPUT); 
  pinMode (led3, OUTPUT);
  pinMode (led4,OUTPUT);
  pinMode (led5,OUTPUT);
  pinMode (led6,OUTPUT);
  pinMode (led7,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
 
 digitalWrite(led,HIGH);
 digitalWrite(led1,HIGH);
 delay (1);
  digitalWrite(led,LOW);
 digitalWrite(led1,LOW);
 
digitalWrite(led2,HIGH);
 digitalWrite(led3,HIGH);
delay (1);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);

  
 digitalWrite(led4,HIGH);
 digitalWrite(led5,HIGH);
 delay (1);
 digitalWrite(led4,LOW);
 digitalWrite(led5,LOW);
 
 
 digitalWrite(led6,HIGH);
 digitalWrite(led7,HIGH);
 delay (1);
 digitalWrite(led6,LOW);
 digitalWrite(led7,LOW);
 
   }
 
  

