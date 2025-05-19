/*
Програма за управление на ултразвуков сензор и изписване на неговите
показания на 16/2 дисплей. Използва 8 дигитални пин-а. Могат да бъдат променени 
според това как е удобно. Просто подменете в началото пиновете които са по удобни
за вас 
*/

#include <LiquidCrystal.h>

int pingPin = 10;    //Включваш към дигитален пин 10 (triger)
int inPin = 13;       //Включваш към дигитален пин 13 (echo)
long microseconds; 
long CM; 

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
  lcd.begin (16,2);
  lcd.print ("Distance");
 
}

void loop () {
  
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
CM = (cm + 2);             /* Присвоява стойността на полученото във "cm" на 
                        другата променлива "CM' и коригира стойността с 2*/  
  lcd.setCursor (0,1);
  lcd.print (CM);
  lcd. print (" ");
 delay(100);
  lcd.print ("Cm");
  lcd.print ("    "); /*Няколко празни символа за да трият резултата от 
                      предишното измерване и да не остават паразитни cm -та*/ 
delay(170); }

long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }

long microsecondsToCentimeters(long microseconds)

{ return microseconds / 29 / 2; }
  
