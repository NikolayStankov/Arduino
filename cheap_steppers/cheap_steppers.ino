#define IN1  9
#define IN2  8
#define IN3  7
#define IN4  6
#define IN5  5
#define IN6  4
#define IN7  3
#define IN8  2
int Steps = 4096; //4096 or 768
int cstep = 0;
int cstep1=0;
void spet2();
void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(IN5, OUTPUT); 
  pinMode(IN6, OUTPUT); 
  pinMode(IN7, OUTPUT); 
  pinMode(IN8, OUTPUT);
}

void loop()
{
  for(int x=0;x<Steps;x++)
  {
  step1();
  step2();
  //delay(1);
  delayMicroseconds(900);
  }
 
  
}

void step1()
{
  //stepp
  switch(cstep)
  {
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
  }
   cstep=cstep+1;
   if(cstep==8)
     {cstep=0;}
}
   void step2()
{
  //stepp
  switch(cstep)
  {
   case 0:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
   break; 
   case 1:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, HIGH);
   break; 
   case 2:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
   break; 
   case 3:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
   break; 
   case 4:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
   case 5:
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
     case 6:
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
   case 7:
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
   break; 
   default:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
  }
   cstep1=cstep1+1;
   if(cstep1==8)
     {cstep1=0;}
}
  

