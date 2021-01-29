#include <SoftwareSerial.h>

SoftwareSerial tanim(7,6); //rx,tx

void setup()
{
  Serial.begin(9600);
  tanim.begin(9600);
}

void loop()
{
  if(tanim.available())
  {
    char gelenBilgi = tanim.read();
    Serial.print(gelenBilgi);
  }
}
