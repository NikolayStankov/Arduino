

//Define the Arrays For Hours
void DefineTimeValues(void){
  
    HoursArray[0] = 0x00; //00000000 All Circles off 
    HoursArray[1] = 0x01; //00000001 One circle On 
    HoursArray[2] = 0x03; //00000011 2 Circles on 
    HoursArray[3] = 0x07; //00000111 All Circles on.No lines 
    HoursArray[4] = 0x0F; //00001111  All Circles plus one line 12 O'clock
    HoursArray[5] = 0x17; //00010111  All Circles plus two lines 1 O'clock
    HoursArray[6] = 0x27; //00100111  All Circles plus three lines 2 O'Clock
    HoursArray[7] = 0x47; //01000111  All Circles plus four lines 3 0'Clock
    HoursArray[8] = 0x87; //10000111  All Circles plus five lines 4 0'Clock
    HoursArray[9] = 0x01; //00000001 5 O'clock Always load with all circles on [3]
    HoursArray[10] = 0x02; //00000010 6 O'clock Always load with all circles on [3]
    HoursArray[11] = 0x04; //00000100 7 O'clock Always load with all circles on [3]
    HoursArray[12] = 0x08; //00001000 8 O'clock Always load with all circles on [3]
    HoursArray[13] = 0x10; //00010000 9 O'clock  Always load with all circles on [3]
    HoursArray[14] = 0x20; //00100000 10 O'clock Always load with all circles on [3]
    HoursArray[15] = 0x40; //01000000 11 O'Clock Always load with all circles on [3]

  //Array For Minutes 
    MinutesArray[0]= 0x00;//All Off 
    MinutesArray[1]= 0x0D;  //00001101 2 circles One line on 12 0'clock
    MinutesArray[2] = 0x15; //00010101 2 Circles 2-nd line 1 O'clock  
    MinutesArray[3] = 0x25; //00100101 2 Circles 2-nd line 2 O'clock
    MinutesArray[4] = 0x45; //01000101 2 Circles 2-nd line 3 O'clock
    MinutesArray[5] = 0x85; //10000101  2 Circles 2-nd line 4 O'clock
    MinutesArray[6] = 0x01; //00000010 5 O'clock Always load with [0]
    MinutesArray[7] = 0x02; //00000100 6 O'clock Always load with all circles on [3]
    MinutesArray[8] = 0x04; //00001000 7 O'clock Always load with all circles on [3]
    MinutesArray[9] = 0x8; //00010000 8 O'clock  Always load with all circles on [3]
    MinutesArray[10] = 0x10; //00100000 9 O'clock Always load with all circles on [3]
    MinutesArray[11] = 0x20; //01000000 10 O'Clock Always load with all circles on [3]
    MinutesArray[12] = 0x40; //01000000 11 O'Clock Always load with all circles on [3]
    MinutesArray[14] = 0x05; //Turns on only line 1 and 2
}

int dispHours(int Hour)
{
  switch (Hour) 
  { 
   case 1:
   data1 = HoursArray[0];// Second Shift reg data
   data2 = HoursArray[5]; //First Shift reg data
   break;
   case 2:
   data1 = HoursArray[0];// Second Shift reg data
   data2 = HoursArray[6]; //First Shift reg data
   break;
   case 3:
   data1 = HoursArray[0];// Second Shift reg data
   data2 = HoursArray[7]; //First Shift reg data
   break;
   case 4:
   data1 = HoursArray[0];// Second Shift reg data
   data2 = HoursArray[8]; //First Shift reg data
   break;
   case 5:
   data1 = HoursArray[9];// Second Shift reg data
   data2 = HoursArray[3]; //First Shift reg data
   break;
   case 6:
   data1 = HoursArray[10];// Second Shift reg data
   data2 = HoursArray[3]; //First Shift reg data
   break;
   case 7:
   data1 = HoursArray[11];// Second Shift reg data
   data2 = HoursArray[3]; //First Shift reg data
   break;
   case 8:
   data1 = HoursArray[12];// Second Shift reg data
   data2 = HoursArray[3]; //First Shift reg data
   break;
   case 9:
   data1 = HoursArray[13];// Second Shift reg data
   data2 = HoursArray[3]; //First Shift reg data
   break;
   case 10:
   data1 = HoursArray[14];// Second Shift reg data
   data2 = HoursArray[3]; //First Shift reg data
   break;
   case 11:
   data1 = HoursArray[15];// Second Shift reg data
   data2 = HoursArray[3]; //First Shift reg data
   break;
   case 12:
   data1 = HoursArray[0];// Second Shift reg data
   data2 = HoursArray[4]; //First Shift reg data
   break;
  }
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, data1);   
   shiftOut(dataPin, clockPin, data2);
   digitalWrite(latchPin, HIGH);
}


int dispMinutes(int Minute)
{
  switch (Minute) 
  { 
   case 1:
   data1 = MinutesArray[0];// Second Shift reg data
   data2 = MinutesArray[1]; //First Shift reg data
   break;
   case 2:
   data1 = MinutesArray[0];// Second Shift reg data
   data2 = MinutesArray[2]; //First Shift reg data
   break;
   case 3:
   data1 = MinutesArray[0];// Second Shift reg data
   data2 = MinutesArray[3]; //First Shift reg data
   break;
   case 4:
   data1 = MinutesArray[0];// Second Shift reg data
   data2 = MinutesArray[4]; //First Shift reg data
   break;
   case 5:
   data1 = MinutesArray[0];// Second Shift reg data
   data2 = MinutesArray[5]; //First Shift reg data
   break;
   case 6:
   data1 = MinutesArray[6];// Second Shift reg data
   data2 = MinutesArray[14]; //First Shift reg data
   break;
   case 7:
   data1 = MinutesArray[7];// Second Shift reg data
   data2 = MinutesArray[14]; //First Shift reg data
   break;
   case 8:
   data1 = MinutesArray[8];// Second Shift reg data
   data2 = MinutesArray[14]; //First Shift reg data
   break;
   case 9:
   data1 = MinutesArray[9];// Second Shift reg data
   data2 = MinutesArray[14]; //First Shift reg data
   break;
   case 10:
   data1 = MinutesArray[10];// Second Shift reg data
   data2 = MinutesArray[14]; //First Shift reg data
   break;
   case 11:
   data1 = MinutesArray[11];// Second Shift reg data
   data2 = MinutesArray[14]; //First Shift reg data
   break;
   case 12:
   data1 = MinutesArray[12];// Second Shift reg data
   data2 = MinutesArray[14]; //First Shift reg data
   break;
  }
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, data1);   
   shiftOut(dataPin, clockPin, data2);
   digitalWrite(latchPin, HIGH);
}

