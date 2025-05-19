

#include <OneWire.h> //Добавя библиотеката за OneWire комуникация
#include <DallasTemperature.h> //Добавя библиотека за DallasTemp Sensor 
#include <LiquidCrystal.h> //Добавя библиотеката за 16/2 Дисплей
#define ONE_WIRE_BUS 8 //Дефинира кой пин е за OneWire Netrwok-a

OneWire oneWire(ONE_WIRE_BUS); //Задава променлива за шината

DallasTemperature sensors(&oneWire); //Показва на библиотеката да търси сензора на OneWire шината
int ButtonPin = 10;
int PotPin = A0;
int LdrPin = A3;
float PotPin2 = A1;
int Freq ; 
int Time;
long Temp;
unsigned long Minutes = 0;
int Minutes2;
long TempCurrent;
char* topRow[]= {"Welcome to... ","Time(m)","Temp.","Beer Temp"} ; 
/*Създава се масив с string-ове и после само се посочва номера на string-a
и позицията от която да се изпише. */

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
  

  sensors.begin();
  lcd.begin (16,2);
  lcd.setCursor (2,0);
  lcd.print (topRow[0]);
  lcd.setCursor (3,1);
  lcd.print (topRow[3]);
 delay (1500);
  lcd.clear();

 
}

void loop () {

  
 
 sensors.requestTemperatures(); 
 Time = analogRead(PotPin2);
 Temp = analogRead(PotPin);
 Temp = map(Temp, 0, 1024, 0, 131); //Ограничава обхвата до 130 градуса и увеличава плавността
 Time = map(Time , 0, 1023, 0, 360);
 TempCurrent = sensors.getTempCByIndex(0); 
 Freq =TempCurrent - Temp ; 
 Freq = map(Freq, 0, 50, 20, 255);
 Minutes=millis()/1000/60;
 

if (Minutes==Time||Minutes>Time)
{
  
  tone (9 ,180,50);
}

if (TempCurrent > Temp + 1 ) //Включва зумера ако температурата надвиши зададената.
{ 
  
  tone (9,Freq,50);

}

if (TempCurrent < Temp - 2)//Включва зумера ако температурата е 2 
{
  tone (9,150,50);      //градуса по ниска от зададената
}




  lcd.setCursor (8,0); //Избира се позицията от която да изпише string-a
  lcd.print (topRow[2]) ; //Избира се необходимия String
  lcd.print (Temp);
  lcd.print ("  "); //Празни символи за да няма примигване на екрана с lcd.clear
  lcd.setCursor(0,0);
  lcd.print (topRow[1]); 
  lcd.setCursor(0,1);
  lcd.print ("<");
  lcd.print (Time);
  lcd.print (">");
  
  lcd.print (Minutes); 
  lcd.blink();
  delay (100);
  lcd.noBlink();
  delay(50);
  lcd.print ("   ");
  lcd.setCursor (11,1);
  lcd.print (TempCurrent);
  lcd. print (" ");
  lcd.print ("C");
  lcd.print ("         "); 
  
  /*Няколко празни символа за да трият резултата от 
                      предишното измерване и да не остават паразитни cm -та*/ 
 


 } //Закъснение докато цялата програма се повтори.


 
