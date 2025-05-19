

#include <LiquidCrystal.h>


long time = 0;
int reading; 
int previous = LOW;
int state = HIGH;
int buttonPin = 9; ///Включваш към дигитален пин 9 ( Бутон за избиране на размера)                   
int ledPin = 8;     //Светодиод към дигитален пин 8
int ledPin2 = 7;    //Светодиод към дигитален пин 7                 
int pingPin = 10;    //Включваш към дигитален пин 10 (triger)(Ultrasonic Sensor)
int inPin = 13;       //Включваш към дигитален пин 13 (echo)(Ultrasonic Sensor)
long microseconds; 
long CM; 
long cm;
char* topRow[]= {"Welcome to... ","Full","Front","Size and angle "} ; 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup () {
  pinMode (buttonPin ,INPUT);
  pinMode (ledPin ,OUTPUT);
  pinMode (ledPin2 ,OUTPUT);
  
  lcd.begin (16,2);
  lcd.setCursor (2,0);
  lcd.print (topRow[0]);
  lcd.setCursor (0,1);
  lcd.print (topRow[3]);
  digitalWrite (ledPin ,HIGH); //Включи Led1
  delay (300);
  digitalWrite (ledPin2,LOW); // Изключи Led2
  delay (300);
  digitalWrite (ledPin2,HIGH);
  delay (300);
  digitalWrite (ledPin,LOW);
  delay (300);
  digitalWrite (ledPin ,HIGH); //Включи Led1
  delay (300);
  digitalWrite (ledPin2,LOW); // Изключи Led2
  delay (300);
  digitalWrite (ledPin2,HIGH);
  delay (300);
  digitalWrite (ledPin,LOW);
  delay (500);
  lcd.clear();
}


long microsecondsToCentimeters(long microseconds)

{ 
  
  return microseconds / 29 / 2; 


}


void loop () {
  
  long duration, inches;     /*Цикъла служи за задействане на сензорите и
                                   смятане на разстоянието*/
  
digitalWrite(pingPin, LOW);    
delayMicroseconds(2); 
digitalWrite(pingPin, HIGH); 
delayMicroseconds(10);
digitalWrite(pingPin, LOW);
delayMicroseconds(2);
pinMode(pingPin, OUTPUT);
pinMode(inPin, INPUT);
duration = pulseIn(inPin, HIGH);
cm = microsecondsToCentimeters(duration);
  

 
 
  reading = digitalRead (buttonPin);
  
  
  
  if (reading == HIGH){ 
  
lcd.setCursor (5,0);  //Избира позицията от която да се изпише string-a
     lcd.print (topRow[1]); //Избира самия string
     lcd.print ("       "); //Празни символи за да се избегне мигането с lcd.clear
 digitalWrite (ledPin ,HIGH); //Включи Led1
 digitalWrite (ledPin2,LOW); // Изключи Led2
 
 
  CM = (cm+2)+10; //Когато бутона е натиснат добавя размера на устройството (10cm)
                   //,като по този начин размера е от гърба на уреда.
                  
}
   

 else  {
  
    lcd.setCursor (5,0); //Избира се позицията от която да изпише string-a
  lcd.print (topRow[2]) ; //Избира се необходимия String
  lcd.print ("           "); //Празни символи за да няма примигване на екрана с lcd.clear
  digitalWrite (ledPin2 ,HIGH); //Включи Led2
  digitalWrite (ledPin ,LOW); // Изключи Led1
  
  
    CM = (cm + 2);   //Добавя 2 Cm като това е,
                     // челния размер с корекцията за точност 
                     
}  
  lcd.setCursor (0,1);
  lcd.print (CM);
  lcd. print (" ");
 delay(100);
  lcd.print ("Cm");
  lcd.print ("         "); 
  
  /*Няколко празни символа за да трият резултата от 
                      предишното измерване и да не остават паразитни cm -та*/ 
 
delay (150) ;
 
 } //Закъснение докато цялата програма се повтори.

   


