int btn1 = 12;
int btn2 = 11;
int Tr1 = 2;
int Tr2 = 3;
int Tr4 = 4;
int Tr3 = 5;
bool Button1State;
bool Button2State;
int Tr11 = 6;
int Tr21 = 7;
int Tr41 = 8;
int Tr31 = 9;


void setup() {
  pinMode (btn1, INPUT);
  pinMode (btn2, INPUT);
  pinMode (Tr1,OUTPUT);
  pinMode (Tr2,OUTPUT);
  pinMode (Tr3,OUTPUT);
  pinMode (Tr4,OUTPUT);
 // pinMode (Tr11,OUTPUT);
 // pinMode (Tr21,OUTPUT);
 // pinMode (Tr31,OUTPUT);
 // pinMode (Tr41,OUTPUT);
 //digitalWrite(Tr2,LOW);
 //digitalWrite(Tr3,LOW);
 //digitalWrite(Tr1,LOW);
 //digitalWrite(Tr4,LOW);
}
 
 void loop() {

 // digitalWrite(Tr1,HIGH);
  //digitalWrite(Tr4,HIGH);
  // digitalWrite(Tr2,HIGH);
 // digitalWrite(Tr3,HIGH);

int Button1State = digitalRead(btn1);
int Button2State = digitalRead(btn2);


 
 if(Button2State==LOW)
 {
  digitalWrite(Tr2,HIGH);
  digitalWrite(Tr3,HIGH);
  //digitalWrite(Tr1,LOW);
 // digitalWrite(Tr4,LOW);
 }
 else{
   digitalWrite(Tr2,LOW);
   digitalWrite(Tr3,LOW);
 }
 
 if(Button2State==LOW)
 {
  digitalWrite(Tr1,HIGH);
  digitalWrite(Tr4,HIGH);
  //digitalWrite(Tr2,LOW);
  //digitalWrite(Tr3,LOW);
 }
 else{
   digitalWrite(Tr1,LOW);
   digitalWrite(Tr4,LOW);
 }
 

 

}

