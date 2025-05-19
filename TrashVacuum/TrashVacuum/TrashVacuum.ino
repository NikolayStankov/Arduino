#include <avr/sleep.h>
#include <avr/interrupt.h>

int mtr = 4;
int btn = 2;
int buttonstate;

// the setup routine runs once when you press reset:
void setup() {                
 
  pinMode(mtr, OUTPUT); 
 pinMode (btn,INPUT); 
  buttonstate=0;
}

// the loop routine runs over and over again forever:
void loop() {

sleep();
if(buttonstate==1){
   digitalWrite(mtr,HIGH);
 delay(60000);
 buttonstate=0;
   }
 else{
  digitalWrite(mtr,LOW); 
 }
 
}

ISR(PCINT0_vect)
{   
      cli();                                  // Disable interrupts
    PCMSK &= ~_BV(PCINT2);                  // Turn off PB2 as interrupt pin
    sleep_disable();                        // Clear SE bit
    ADCSRA |= _BV(ADEN);                    // ADC on
    buttonstate=1;
}

void sleep(void)
{
  if(buttonstate==0)
  {
    GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT2);                   // Use PB4 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                   // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);    // replaces above statement

    sleep_enable();                         // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();                                  // Enable interrupts
    sleep_cpu();                            // sleep 
  }
  }
