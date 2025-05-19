/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
  Buttons with connected pull up resistors :
    BTN1 - Pin 9 
    BTN2 - Pin 8
    BTN3 - Pin 7 

*/

// include the library code:
#include <LiquidCrystal.h>

//Init button pins
int BTN1 = 9;
int BTN2 = 8;
int BTN3 = 7;
int Peltier = 13;
long prevmillis = 0;
long debounceinterval=100;
int debounceflag = 0;
int PointerPosition=2;
unsigned long currentmillis;
//Function Prototypes
void buttonsManager(void);
void PeltierManager(void);
void Timers(void);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
 //Init pins as outputs and inputs 
 pinMode (BTN1, INPUT);
 pinMode (BTN2,INPUT);
 pinMode (BTN3, INPUT);
 pinMode (Peltier,OUTPUT);

  // set up the LCD's number of columns and rows: 
  lcd.begin(8, 2);
  // Print a message to the LCD.
  lcd.setCursor (0,0);
  lcd.print("Beverage");
  lcd.setCursor (0,1);
  lcd.print("  Cooler");
  delay(3000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Start");
  lcd.setCursor(2,1);
  lcd.print("Stop");
}

void loop() { 
    
    Timers(); //Encapsulating function for all the software timers.
    buttonsManager();  //Manages the pushes of all buttons and the pointerIndex
    PeltierManager();  //Manages the high current output ,for
                      // the peltier according to the pointerIndex
    lcd.setCursor(0, 1); // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 
 
    
}

  void Timers(void)
  {
   unsigned long currentmillis = millis();//Value for the millis() counter
   
   //Debounce timer for the buttons used in the device
     if (currentmillis - prevmillis > debounceinterval) 
       {
        debounceflag=0;
        prevmillis=currentmillis;
       }  
  }

 void PeltierManager(void)
  {
  switch (PointerPosition)
   {
    case 1:
    digitalWrite(Peltier,HIGH);
    break;
    
    case 2:
    digitalWrite(Peltier,LOW);
    break;
    
    case 3:
    digitalWrite(Peltier,LOW);
    break;   
   } 
  }


 void buttonsManager(void)
 {
  
    if ((digitalRead(BTN1) == LOW)&&(debounceflag==0))
    {
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.setCursor(0,0);
      lcd.print(">");
      PointerPosition = 1;    
    }
    if( (digitalRead(BTN2)== LOW)&&(debounceflag==0))
    {
      lcd.setCursor(0,0);
      lcd.print(" ");
      lcd.setCursor(0,1);
      lcd.print(">");
      PointerPosition = 2;
      }
    if ((digitalRead(BTN3) == LOW)&&(debounceflag==0))
    {
      lcd.setCursor(0,1);
      lcd.print(" "); 
      lcd.setCursor(0,0);
      lcd.print(" "); 
      PointerPosition = 3;
    }  
  debounceflag = 1; 
}
