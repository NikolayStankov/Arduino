//Pin Definitions
int IRsensor=6;
int dataPin=9;
int latchPin=7;
int clockPin=8;
int led=13;

//Variables definition
byte data1;
byte data2;
byte dataArray1[12];
byte dataArray2[12];
byte HoursArray[16];
byte MinutesArray[16];
int Hour;
int Minute;
bool IRsense;
String time;

//RTC values
const uint8_t bufLen = 30;
char buffer[bufLen + 1] = {'\0'};
uint8_t bufPos = 0;
unsigned long last = 0;


void RTC(void)
{
  struct RTCx::tm tm;
  if (millis() - last > 2000) {
    last = millis();
    rtc.readClock(tm);
   

 //RTCx::printIsotime(Serial, tm).time;
    RTCx::printIsotime(Serial, tm).println();
   // RTCx::time_t t = RTCx::mktime(&tm);

    // Serial.print("unixtime = ");
  //  Serial.println(t);
  //  Serial.println("-----");
  
  }

  while (Serial.available()) {
    char c = Serial.read();
    if ((c == '\r' || c == '\n' || c == '\0')) {
      if (bufPos <= bufLen && buffer[0] == 'C') {
        // Check time error
        buffer[bufPos] = '\0';
        RTCx::time_t pcTime = atol(&(buffer[1]));
        rtc.readClock(&tm);
        RTCx::time_t mcuTime = RTCx::mktime(&tm);
        Serial.print("MCU clock error: ");
        Serial.print(mcuTime - pcTime);
        Serial.println(" s");
        Serial.println("~~~~~");
      }
      if (bufPos <= bufLen && buffer[0] == 'T') {
        // Set time
        buffer[bufPos] = '\0';
        RTCx::time_t t = atol(&(buffer[1]));
        RTCx::gmtime_r(&t, &tm);
        rtc.setClock(&tm);
        Serial.println("Clock set");
        Serial.println(&(buffer[0]));
        RTCx::printIsotime(Serial, tm);
        Serial.println("~~~~~");
      }
      if (bufPos <= bufLen && buffer[0] == 'X') {
        // Set calibration value
        buffer[bufPos] = '\0';
        if (rtc.getDevice() == RTCx::MCP7941x) {
          int8_t oldCal = rtc.getCalibration();
          char *endptr;
          long cal = strtol(&(buffer[1]), &endptr, 0);
          if (cal >= -127 && cal <= 127 && endptr == &buffer[bufPos]) {
            Serial.print("Previous calibration: ");
            Serial.println(oldCal, DEC);
            Serial.print("Calibration: ");
            Serial.println(cal, DEC);
            rtc.setCalibration(cal);
          }
          else
            Serial.println("Bad value for calibration");
        }
        else {
          Serial.println("Cannot set calibration: not a MCP7941x");
        }
      }
      if (bufPos <= bufLen && buffer[0] == 'M') {
        // Set SQW mode
        buffer[bufPos] = '\0';
        char *endptr;
        long mode = strtol(&(buffer[1]), &endptr, 0);
        if (mode >= RTCx::freq1Hz && mode <= RTCx::freqCalibration
          && endptr == &buffer[bufPos]) {
          if (rtc.setSQW((RTCx::freq_t)mode)) {
            Serial.print("SQW: ");
            Serial.println(mode, DEC);
          }
          else
            Serial.println("Could not set SQW");
        }
        else
          Serial.println("Bad value for SQW");
      }
      bufPos = 0;
    }
    else if (bufPos < bufLen)
      // Store character
      buffer[bufPos++] = c;
  }
}
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }
    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
 //stop shifting
  digitalWrite(myClockPin, 0);
}






