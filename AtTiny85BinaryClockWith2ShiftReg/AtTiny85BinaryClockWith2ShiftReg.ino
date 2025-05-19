/****************************************************
* Binary watch with two shift registers 74HC595
*
*  Created by : Nikolay Stankov on 25/5/2014
*  Controller used : AtTiny85 

*  Libraries for the controller used :
*  http://highlowtech.org/?p=1695
*  Programmed via Arduino Uno board and a homemade 
*  converter.
*  
*  For fully understanding what happens here look over
*  the Arduino explanation of shift registers at :
*  http://arduino.cc/en/tutorial/ShiftOut
*  
*****************************************************/

int latchPin = 1 ; //Digital Pin 1
int minutesPin = 3; // Digital Pin 2
int hoursPin = 4; //Digital Pin 4 (Used for the button that sets the hour(The pin is default pull up))
int clockPin = 2 ;//Digital Pin 2 (Used for Clock of the shift register)
int dataPin = 0 ; //Digital Pin 0 (used for data shifting out the shift register)
int Minutes = 0; //Value when the device starts up for minutes
int Seconds = 0; //Value when the device starts up for seconds
int Hours = 12; //Value when the device starts up for hours
long interval = 1000; //One second interval used for actual tick of the device
long debounceinterval = 800; //Debounce interval used for the buttons
long prevmillis1 = 0; //Values used for the calculation of tick and
long prevmillis = 0; // debounce time
int debounceflag = 0;
int MinutesCorrection = 0;
int Correctsixhours = 0;
int DisplayFlag = 0;
void Display(void);
void setup() {
  
  pinMode (latchPin, OUTPUT); //define the latchPin as an output 
  pinMode (clockPin, OUTPUT); //define the clockPin as an output
  pinMode (dataPin, OUTPUT); //define the dataPin as an output 
  pinMode (minutesPin,INPUT);//define the Minutes button as input
  pinMode (hoursPin,INPUT); //define the hours button as input 
 //pins that are input are pulled up to 5V with 10 K resistor.
}

void loop ()
{
  
 /*************************************************
 *     Tick timer .Increments one in a second
 *************************************************/
  unsigned long currentmillis = millis(); 
 

  if(currentmillis - prevmillis >interval)
    { 
     Seconds++;
     DisplayFlag++;
    prevmillis = currentmillis;  
    
    }
 
/*****************************************************************************
* Incrementing the values for hours and for minutes on the push of a button
* on every 500 ms.Otherwize it icrements too fast .Achieved with debounce flag
* and a timer using millis() function so we don't use delays.The actual timer
* is at the bottom of this function.
*****************************************************************************/

       if ((digitalRead(minutesPin) == LOW)&&(debounceflag == 0))
     {
        Minutes++;
       MinutesCorrection = 0;//Zero the value so while setting the clock the
      Correctsixhours = 0;//correction algorithm doesn't work
       debounceflag = 1;
     }
   
       if ((digitalRead(hoursPin) == LOW)&&(debounceflag == 0))
     {
       Hours++;
       MinutesCorrection = 0;//Zero the value so while setting the clock the
      Correctsixhours = 0;//correction algorithm doesn't work
       debounceflag = 1;
     }
     
 //On every 59 seconds increment the minutes by 1 and zero out seconds value
       if(Seconds > 59)
      {
        Seconds=0;
        Minutes++; 
      }
 //On every 59 Minutes increment the Hours by 1 and zero out Minutes value   
      if(Minutes > 59)
      {
        Minutes = 0;
        Hours++;
        if(debounceflag == 0) //To stop the corrections when setting up manually.
        {
        MinutesCorrection++;//value used for the error in time 1 minute in two hours
        Correctsixhours++;
        }
      }
 //On every 12 + Hours go to zero and start incrementing again from there      
      if(Hours > 12)
      {
        Hours = 1;
      }   
//The debounce timer used for the buttons described on top.
       if (currentmillis - prevmillis1 > debounceinterval)
     {
       debounceflag=0;
       prevmillis1 = currentmillis;
       
        
     }
 
 //Correction for the minutes because on every 2 hours it gives a 1 minute error
   if(MinutesCorrection>1) 
    {
      Minutes++;
      MinutesCorrection = 0;
    }
 //Correct with one minute on the seventh hour. 
    if(Correctsixhours>5)
    {
      Minutes++;
      Correctsixhours = 0;
    }
 
  Display();
     
}

/*****************************************************************************
 *The actual display function that lights up the leds. The two shift
 *registers are daisy chained so the first value goes to the furthest away 
 *not to the first connected after the controller.The value for hours goes to
 *the furthest shift register and the value for minutes goes to the shift
 *register connected after the controller.For explanation on how to connect them,
 *look over arduino manual for shift registers online in the arduino site.
 ******************************************************************************/
void Display (void)
  {
    digitalWrite (latchPin ,LOW);
    shiftOut (dataPin, clockPin, MSBFIRST,Hours);
    shiftOut(dataPin, clockPin, MSBFIRST,Minutes);
   digitalWrite (latchPin ,HIGH);  
  }
