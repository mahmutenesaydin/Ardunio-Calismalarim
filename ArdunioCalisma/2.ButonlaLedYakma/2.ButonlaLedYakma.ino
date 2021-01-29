#define Buton 8
#define Led 10

int butonDurumu = 0;

void setup()
{
  pinMode(Buton,INPUT);
  pinMode(Led,OUTPUT);
}

void loop()
{
  butonDurumu = digitalRead(Buton);
  if(butonDurumu == 1)
  {
    digitalWrite(Led,HIGH);
  }
  else
  {
    digitalWrite(Led,LOW);
  }
}
