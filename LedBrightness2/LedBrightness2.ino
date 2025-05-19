int led = 0;


void setup () {
  
pinMode (led, OUTPUT);

}

void loop ()
{
    analogWrite (0, 8);
    delay (150);
    analogWrite (0, 16);
    delay (150);
  analogWrite (0, 32);
  delay (150);
analogWrite (0, 64);
delay(150);
analogWrite (0 , 128);
delay(150);
analogWrite (0, 254);
delay(150);


}
