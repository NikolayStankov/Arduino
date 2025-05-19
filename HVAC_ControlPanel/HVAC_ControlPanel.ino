/*********************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x64 size display using SPI to communicate
  4 or 5 pins are required to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <OneWire.h> //Includes OneWire communication library
#include <DallasTemperature.h> //Includes DallasTemp Sensor library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define ONE_WIRE_BUS 6 //Define the oneWireBus pin for tempsens
OneWire oneWire(ONE_WIRE_BUS); //Задава променлива за шината
DallasTemperature sensors(&oneWire); //Points the library to the OneWire bus for the tempsensor

// Definitions for the Adafruit software SPI
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//Pin Assignments for the Buttons
int Btn1 = 7;
int Btn2 = 8;
int Btn3 = 2;
int Btn4 = 3;
int TransmitPin=5;
//Global Variables for Temperature,Timers and Fan Speed
int Temp;
int TempPrevious = 1;
int FanSpeed = 1;
int FanSpeedPrevious = 1;
int SetTemp  = 16;
int SetTempPrevious;
unsigned long currentmillis;
long prevmillis = 0;
long prevmillisTemp = 0 ;
long prevmillisDisplay = 0;
int debounceinterval = 200;
long TempMeasureInterval = 1000;
long DisplayInterval = 500;
long SerialInterval= 500;
int DisplayFlag = 1;
int debounceflag = 0;
int TempMeasurementFlag = 0;
int SerialFlag=0;
//Functon Prototypes
void Temperatures(void);
void Timers(void);
void DisplayText(void);
void Buttons(void);
void TransmitData(void);
//Variables Used For Serial Transmission
String BeginChar = "P";
String EndChar = "D";
String MidChar = "S";
String MidChar2= "K";
String Transmission;

void setup()   {
  pinMode(Btn1, INPUT);//Button for Fan Up
  pinMode(Btn2, INPUT);//Button For Fan Down
  pinMode(Btn3, INPUT);//Button For Temo Up
  pinMode(Btn4, INPUT);// Button For Temp Dowm
  pinMode(TransmitPin,OUTPUT);
  Serial.begin(9600);
 // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  // Show image buffer on the display hardware.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("HVAC UNIT");
  display.setCursor(0, 20);
  display.println("Ver 0.1");
  display.display();
  delay(3000);
}

void loop() //Main Loop
{
  Timers();
  Buttons();
  DisplayText();
  Temperatures();
  TransmitData();
  
}

void TransmitData(void) //Transmits the data over serial
{
   
  if (SerialFlag==0)
  {
   
  digitalWrite(TransmitPin,HIGH);
  Transmission=(BeginChar+SetTemp+MidChar+FanSpeed+MidChar2+Temp+EndChar);
  Serial.println(Transmission);
  SerialFlag=1;
    
  }
  else 
  {
    digitalWrite(TransmitPin,LOW);
  }
}

void Buttons(void) //Reads the Button Inputs
{
  if ((digitalRead(Btn1) == LOW) && (debounceflag == 0))
  {
    if (FanSpeed < 8)
    {
      FanSpeed++;
    }
    else
    {
      FanSpeed = 8;
    }
    DisplayFlag = 0;
     debounceflag = 1;
  }
  if ((digitalRead(Btn2) == LOW) && (debounceflag == 0))
  {
    if (FanSpeed > 1)
    {
      FanSpeed--;
    }
    DisplayFlag = 0;
     debounceflag = 1;
  }
  if ((digitalRead(Btn3) == LOW) && (debounceflag == 0))
  {
    if (SetTemp < 40)
    {
      SetTemp++;
    }
    DisplayFlag = 0;
     debounceflag = 1;
  }
  if ((digitalRead(Btn4) == LOW) && (debounceflag == 0))
  {
    if (SetTemp > 16)
    {
      SetTemp--;
    }
    DisplayFlag = 0;
     debounceflag = 1;
  }
 
}

void Temperatures(void) //Reads the sensors on the oneWireBus
{
  sensors.begin();
  if ( TempMeasurementFlag == 0)
  {
    sensors.requestTemperatures();
    Temp = sensors.getTempCByIndex(0);
  }
  TempMeasurementFlag = 1;

  if (Temp != TempPrevious)
  {
    TempPrevious = Temp;
    DisplayFlag = 0;
  }
}

void DisplayText(void) //Displays all onscreen information if it changed
{
  if ( DisplayFlag == 0)
  {
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(100, 0);
    display.println(Temp);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(50, 0);
    display.println("Current");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(105, 24);
    display.println("Set");

    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.setCursor(79, 36);
    display.println(SetTemp);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 56);
    display.println("Fan");

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(40, 56);
    display.println("Pump");
      
    if (SetTemp>=Temp){
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(40, 48);
      display.println("OFF");
    }
    else {
   //   display.setTextSize(1);
   //   display.setTextColor(WHITE);
    //  display.setCursor(40, 48);
    //  display.println("ON");
      display.fillRect(40, 48, display.width() / 18, display.height() / 12, WHITE);
    }

    switch (FanSpeed) //Generates the squares for the FanSpeed
    {
      case 1:
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 48);
        display.println("OFF");
        
        break;
      case 2:
        display.fillRect(0, 48, display.width() / 18, display.height() / 12, WHITE);
        break ;
      case 3:
        display.fillRect(0, 48, display.width() / 18, display.height() / 12, WHITE);
        display.fillRect(0, 40, display.width() / 14, display.height() / 12, WHITE);
        break;
      case 4:
       display.fillRect(0, 48, display.width() / 18, display.height() / 12, WHITE);
        display.fillRect(0, 40, display.width() / 14, display.height() / 12, WHITE);
        display.fillRect(0, 32, display.width() / 12, display.height() / 12, WHITE);
        break;
      case 5:
         display.fillRect(0, 48, display.width() / 18, display.height() / 12, WHITE);
        display.fillRect(0, 40, display.width() / 14, display.height() / 12, WHITE);
        display.fillRect(0, 32, display.width() / 12, display.height() / 12, WHITE);
        display.fillRect(0, 24, display.width() / 10, display.height() / 12, WHITE);
        break;
      case 6:
       display.fillRect(0, 48, display.width() / 18, display.height() / 12, WHITE);
        display.fillRect(0, 40, display.width() / 14, display.height() / 12, WHITE);
        display.fillRect(0, 32, display.width() / 12, display.height() / 12, WHITE);
        display.fillRect(0, 24, display.width() / 10, display.height() / 12, WHITE);
        display.fillRect(0, 16, display.width() / 8, display.height() / 12, WHITE);
        break;
      case 7:
        display.fillRect(0, 48, display.width() / 18, display.height() / 12, WHITE);
        display.fillRect(0, 40, display.width() / 14, display.height() / 12, WHITE);
        display.fillRect(0, 32, display.width() / 12, display.height() / 12, WHITE);
        display.fillRect(0, 24, display.width() / 10, display.height() / 12, WHITE);
        display.fillRect(0, 16, display.width() / 8, display.height() / 12, WHITE);
        display.fillRect(0, 10, display.width() / 6, display.height() / 12, WHITE);
        break;

       case 8:
        display.fillRect(0, 48, display.width() / 18, display.height() / 12, WHITE);
        display.fillRect(0, 40, display.width() / 14, display.height() / 12, WHITE);
        display.fillRect(0, 32, display.width() / 12, display.height() / 12, WHITE);
        display.fillRect(0, 24, display.width() / 10, display.height() / 12, WHITE);
        display.fillRect(0, 16, display.width() / 8, display.height() / 12, WHITE);
        display.fillRect(0, 10, display.width() / 6, display.height() / 12, WHITE);
        display.fillRect(0, 0, display.width() / 4, display.height() / 10, WHITE);
       break;
    }
    display.display();
  }
  DisplayFlag = 1;
}

void Timers(void)
{
  currentmillis = millis();//Value for the millis() counter
  //Debounce timer for the buttons used in the device
  if (currentmillis - prevmillis > debounceinterval)
  {
    debounceflag = 0;
    prevmillis = currentmillis;
  }
  //Interval for displaying temperatures and Serial Communication
  if (currentmillis - prevmillisDisplay > SerialInterval)
  {
    // DisplayFlag=0;
    SerialFlag=0;
    prevmillisDisplay = currentmillis;
  }

  //Interval for measuring temperatures
  if (currentmillis - prevmillisTemp > TempMeasureInterval)
  {
    TempMeasurementFlag = 0;
    prevmillisTemp = currentmillis;
  }
}


