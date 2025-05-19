
int led = 0;
int led1 = 3;
int led2 = 1;
int delayValue = 0 ;

// the setup routine runs once when you press reset:
void setup() {                
 
  pinMode(led,OUTPUT);
  pinMode(led1,OUTPUT); 
 pinMode (led2,OUTPUT); 

 
}

// the loop routine runs over and over again forever:
void loop() {
  
if (delayValue < 200)
{
  delayValue ++;
}
if (delayValue == 200)
{ 
  delayValue = 0;
}

if (delayValue == 0)
{ 
digitalWrite(led,HIGH);
digitalWrite(led1,HIGH);
 digitalWrite(led2,HIGH);
  delay (5000);
 
}


digitalWrite(led2,LOW);
 digitalWrite(led,HIGH);
 delay(delayValue);
 digitalWrite(led1,HIGH);
  digitalWrite(led,LOW);
 delay(delayValue);
  digitalWrite(led2,HIGH);
  digitalWrite(led1,LOW);
delay(delayValue);





   }
 
  

