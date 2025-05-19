int PotPin = 3;
int ButtonPin = 2;
int En = 0;
int Apin1 = 1;
int Apin2 = 4;
int val;
int val1 = 0;
int Flag = 0;
long interval = 500;  // the debounce time; increase if the output flickers
long prevmillis = 0;
long currentmillis = 0;
int Debounce = 0;
void setup()
{
  pinMode (ButtonPin , INPUT);
  pinMode (PotPin, INPUT);
  pinMode (En, OUTPUT);
  pinMode (Apin1 , OUTPUT);
  pinMode (Apin2, OUTPUT);
}



void loop()
{

  currentmillis = millis();
/*
  if (currentmillis - prevmillis > interval)
  {
    Debounce = 0;
    prevmillis = currentmillis;

  }
*/

  val = analogRead(PotPin);
  val = map(val, 0, 1023, 0, 255);

 // if ((digitalRead(ButtonPin) == HIGH) && (Debounce == 0))
 if (digitalRead(ButtonPin) == HIGH)
  {
   Flag = 1;
  }
  else 
  {
    Flag = 0;
  }

  if ( Flag == 0 )
  {
    analogWrite (En, val);
    digitalWrite(Apin1, HIGH);
    digitalWrite(Apin2, LOW);
  }
  else
  {
    analogWrite (En, val);
    digitalWrite(Apin1, LOW);
    digitalWrite(Apin2, HIGH);
  }
}

