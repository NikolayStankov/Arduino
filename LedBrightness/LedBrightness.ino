int led = 1;
int sensor = 4;
int sensing = 0;

void setup () {

pinMode (sensor, INPUT);
pinMode (led, OUTPUT);

}

void loop ()
{
  int sensing = analogRead(sensor);
   sensing = map(sensing, 0, 1023, 0, 255);
   analogWrite(led ,sensing);

}
