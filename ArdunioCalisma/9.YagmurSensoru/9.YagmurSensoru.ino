int sab = A0;
int esikDeger = 100;
int buzzer = 8;
int veri;

void setup()
{
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  veri = analogRead(sab);
  if(veri > esikDeger)
  {
    digitalWrite(buzzer,HIGH);
    delay(50);
    digitalWrite(buzzer,LOW);
    delay(150);
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }
}
