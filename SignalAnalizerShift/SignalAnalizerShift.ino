/************************************************************
* Measuring values from 0 to 5 Volts and displaying this on 
8 leds connected to a 8bit shift register.
*************************************************************/

int latchPin = 1 ;
int clockPin = 2 ;
int dataPin = 0 ;
int buttonPin = 4;
int analogPin = 3;
int Voltage = 0;
//long interval= 50;
//long prevmillis= 0;
int VoltageConverted = 0;
byte dataArray[10];
byte data;
char flag=1;

void setup() {
 
  dataArray[8] = 0b11111111; //00000000
  dataArray[7] = 0b11111110; //11111110
  dataArray[6] = 0b11111100; //11111100
  dataArray[5] = 0b11111000; //11111000
  dataArray[4] = 0b11110000; //11110000
  dataArray[3] = 0b11100000; //11100000
  dataArray[2] = 0b11000000; //11000000
  dataArray[1] = 0b10000000; //10000000
  dataArray[0] = 0b00000000; //00000000
  //dataArray[9] = 0xE0; //11100000

  pinMode (latchPin, OUTPUT);
  pinMode (clockPin, OUTPUT);
  pinMode (dataPin, OUTPUT);
  pinMode (buttonPin,INPUT);
  pinMode (analogPin,INPUT);
}

void loop () {
 

   digitalWrite (latchPin ,LOW);
   
   if ((digitalRead(buttonPin)) == LOW)
   {
   Voltage = analogRead(analogPin);
   VoltageConverted = map(Voltage, 0, 1023, 0, 8); //Voltage * (5.0 / 1023.0);
   data = dataArray[VoltageConverted];
   shiftOut (dataPin, clockPin, LSBFIRST,data); 
   digitalWrite (latchPin ,HIGH);
   flag=1;   
   }
   else
   {
     if (flag==1)
     {   
      shiftOut (dataPin, clockPin, MSBFIRST,0); 
      digitalWrite (latchPin ,HIGH);
      flag=0;
     }
   }
   
 
}


