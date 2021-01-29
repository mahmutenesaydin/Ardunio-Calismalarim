#include <SPI.h>
#include <RFID.h>
RFID rfid(10,9)      //SS veya SDA pini, RST pini

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  pinMode(2,OUTPUT);  //yesil led 
  pinMode(3,OUTPUT);  //kirimiz led
}

byte kartim[5] = {0X80, 0XC1, 0XA4, 0XA5, 0XA40}  //Kartımızın seri numaraları

void loop()
{
  boolean gecerliKart = true;
  if(rfid.isCard())
  {
    if(rfid.readCardSerial())
    {
      Serial.print("Kart ID: ")
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.print(rfid.serNum[4],HEX);
    }

    for(int i=0; i<5; i++)
    {
      if(rfid.serNum[i]! = kartim[i])
      {
        gecerliKart = false;
      }
    }
    if(gecerliKart == true)
    {
      Serial.println("HG aga");
      digitalWrite(2,HIGH);
      delay(1000);
      digitalWrite(2,LOW);
    }
    else
    {
      Serial.println("SG aga");
      digitalWrite(3,HIGH);
      delay(1000);
      digitalWrite(3,LOW);
    }
    rfid.halt();
  }
}
