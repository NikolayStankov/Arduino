
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  11;      // the number of the LED pin

// variables will change:
int buttonState = 0; 
int Val = 0; 
int oldVal = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {     
    delay (25);
   Val= oldVal+4 ;  
   oldVal = Val ; 
   analogWrite (ledPin,Val);
  } 
  else {
    analogWrite(ledPin, Val);
  }

}

