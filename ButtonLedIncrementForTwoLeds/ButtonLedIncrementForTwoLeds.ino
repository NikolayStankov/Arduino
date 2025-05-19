
const int buttonPin = 0; //The button pin
const int buttonPin1 = 0;
const int ledPin =  A5; 
const int ledPin1 = A4; // the number of the LED pin

// variables will change:
int buttonState1 = 0;
int buttonState = 0;
int Val1 = 0;
int Val = 0; 
int oldVal = 0;
int oldVal1 = 0 ;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode (ledPin1, OUTPUT); 
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);   
  pinMode(buttonPin1, INPUT);  
}

void loop(){

  buttonState = digitalRead(buttonPin);
  buttonState1= digitalRead(buttonPin1);

  if (buttonState == HIGH) {     
    delay (25);
   Val= oldVal+4 ;  
   oldVal = Val ; 
   analogWrite (ledPin,Val);
  } 
  else {
    analogWrite(ledPin, Val);
  }


 if (buttonState1 == HIGH) {     
    delay (25);
   Val= oldVal1+4 ;  
   oldVal1 = Val1 ; 
   analogWrite (ledPin1,Val);
  } 
  else {
    analogWrite(ledPin, Val);
  }
  
}

