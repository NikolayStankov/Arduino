
int led = 3;
int led1 = 4;
int btn = 2;
int led3= 0;

int buttonstate;

// the setup routine runs once when you press reset:
void setup() {                
 
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT); 
 pinMode (btn,INPUT); 
  pinMode (led3, OUTPUT);
  buttonstate=1;
}

// the loop routine runs over and over again forever:
void loop() {


if((digitalRead(btn)== LOW)&&(buttonstate==1)){
  buttonstate=0;
 digitalWrite(led1,HIGH);
 delay(30000);
 buttonstate=1;
   }
 else{
  digitalWrite(led1,LOW); 
 }
}
