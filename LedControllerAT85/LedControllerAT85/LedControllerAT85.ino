
#include <avr/sleep.h>
#include <avr/interrupt.h>

//Pin Definitions
int ledR = 3;
int ledG = 1;//PWM possible
int ledB = 0; //PWM possible
int btn = 4;

//Variables definitions
int debounceinterval = 800; //Button debounce interval
int debounceflag = 0;//Button debaounce flag
unsigned long currentmillis;
long prevmillis = 0;
int buttonstate;

//Function Prototypes 
void Timers (void);
void LedControl(void);
void Timers(void);

// Setup routine 
void setup() {                
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT); 
  pinMode (ledR, OUTPUT);
  pinMode(btn,INPUT); 
  buttonstate=0;
}

// Main Loop
void loop() 
{

 Timers();
 Buttons();
 LedControl();
 sleep();
  
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
}

void Buttons(void) //Reads the Button Inputs
{
  if ((digitalRead(btn) == HIGH) && (debounceflag == 0))
  {
    buttonstate++;
     debounceflag = 1;
  } 
}

void sleep(void)
{
  if (buttonstate==0)
  {
    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT4);                   // Use PB4 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep 
  }
}


ISR(PCINT0_vect)
{   
  
    cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT4);                  // Turn off PB4 as interrupt pin
    sleep_disable();                        // Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC on
    buttonstate++;
  //
}

void LedControl(void)
{
  switch (buttonstate)
  { 
  case 1:
   digitalWrite(ledR,HIGH);
   digitalWrite(ledG,LOW);
  digitalWrite(ledB,LOW);
   break;
  case 2:
  digitalWrite(ledG,HIGH);
  digitalWrite(ledB,LOW);
  digitalWrite(ledR,LOW);
  break;
  case 3:
   digitalWrite(ledB,HIGH);
  digitalWrite(ledG,LOW);
  digitalWrite(ledR,LOW);
  break;
  case 4:
  analogWrite(ledG,15);
  digitalWrite(ledR,HIGH);  
  digitalWrite(ledB,LOW);
  break; 
  case 5:
  digitalWrite(ledR,HIGH);
  analogWrite(ledB,125);
  digitalWrite(ledG,LOW);
  break;
  case 6:
  analogWrite(ledG,50);
  analogWrite(ledB,125);
  digitalWrite(ledR,LOW);
  break;
  case 7:
  digitalWrite(ledR,HIGH);
  digitalWrite(ledG,HIGH);
  digitalWrite(ledB,HIGH);
  break;
  case 8:
  digitalWrite(ledR,LOW);
  digitalWrite(ledG,LOW);
  digitalWrite(ledB,LOW);
  buttonstate=0;
  delay(200);
  break;   
 }
}


