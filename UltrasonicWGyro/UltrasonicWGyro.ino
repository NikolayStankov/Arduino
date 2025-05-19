/*
Програма за управление на ултразвуков сензор и изписване на неговите
показания на 16/2 дисплей.Oпция да се избира с бутон дали размера да бъде от
челото или от края на уреда. Целта е да може да се мери 
разстояние от стена до стена.При смяна на режима се изписва на дисплея и се
задейства светодиод ,а при другия режим автоматично се задейства друг светодиод.
Използва 11 дигитални пин-а.При първоначалната инициализация се изписва приветстващ
надпис.
*/

#include <LiquidCrystal.h> //Добавя библиотеката за 16/2 Дисплей

int state = HIGH;      	// promenliva za momentnoto sustoyanie na izhodniya pin.  
int reading;           	// promenliva za momentnoto sustoyanie na vhodniya pin 
int previous = LOW; 	// promenliva za predishnoto sustoyanie na vhodniya pin 
long time = 0;         	// otchita koga za posleden put e bil natisnat butona 
long debounce = 200;   	

int buttonPin = 9; ///Включваш към дигитален пин 9 ( Бутон за избиране на размера)                   
int ledPin = 8;     //Светодиод към дигитален пин 8
int ledPin2 = 7;    //Светодиод към дигитален пин 7                 
int pingPin = 10;    //Включваш към дигитален пин 10 (triger)(Ultrasonic Sensor)
int inPin = 13;       //Включваш към дигитален пин 13 (echo)(Ultrasonic Sensor)
long microseconds; 
long CM; 
long cm;
char* topRow[]= {"Welcome to... ","Full","Front","Size and angle"} ; 
/*Създава се масив с string-ове и после само се посочва номера на string-a
и позицията от която да се изпише. */

/*  "CM " умишлено е тип long ,защото сантиметрите в 4 метра са 4000 
и иначе няма да показва коректно данните на дисплей-а. Примерно ако променливата
е int то тя е само до 255 и обхвата и не стига.Ситуацията е същата и с 
променливата microseconds като там е необходим дори по - голям обхват */

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Пинове за работа с Display-a
/*
 Схемата на свързване на Display-a е следната :
 
 * LCD RS пин към дигитален пин 12
 * LCD Enable пин към дигитален пин 11
 * LCD D4 пин към дигитален пин 5
 * LCD D5 пин към дигитален пин 4
 * LCD D6 пин към дигитален пин 3
 * LCD D7 пин към дигитален пин 2
 * LCD R/W пин към 0 (GND)
 
  10K Тример или потенциометър:
 * Свързва се към +5V и 0 (GND) - левия и десният му крака
 * средния му крак към LCD VO пин (пин 3)
 С това се определя поляризацията на кристала и по този начин се определя
 колко да е тъмно или светло черното на буквите.Важно е да се направи правилно.
 без него не работи.
*/

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


/* Определя поведението на измерванията 
    според това дали бутона е натиснат или не*/
 
 reading = digitalRead(buttonPin);
    
if (reading == HIGH && previous == LOW && millis () - time > debounce) 
  {
    lcd.setCursor (5,0);  //Избира позицията от която да се изпише string-a
     lcd.print (topRow[1]); //Избира самия string
     lcd.print ("       "); //Празни символи за да се избегне мигането с lcd.clear
 digitalWrite (ledPin ,HIGH); //Включи Led1
 digitalWrite (ledPin2,LOW); // Изключи Led2
 
 
  CM = (cm+2)+10; //Когато бутона е натиснат добавя размера на устройството (10cm)
                   //,като по този начин размера е от гърба на уреда.
                   
}

else {
  
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
 
 delay(150); } //Закъснение докато цялата програма се повтори.



long microsecondsToCentimeters(long microseconds)

{ 
  
  return microseconds / 29 / 2; 




}




  
 
