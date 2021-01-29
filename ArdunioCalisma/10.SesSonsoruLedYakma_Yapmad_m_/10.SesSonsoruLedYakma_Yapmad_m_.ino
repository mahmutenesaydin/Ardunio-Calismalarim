const int sensorOutpin = A4;  //Sensörün out bacağının bağlı olduğu pin tanımlanır
const int ledPin = 6;         //6.pine bağlı led
int deger;                    //Mikrofondan okunan degerin tutulacağı değişken
const int esik = 50;          //Ledin yanmasını istediğimiz esik degeri

void setup()
{
  pinMode(ledPin, OUTPUT);    //6.pini çıkış olarak ayarlıyoruz
  Serial.begin(9600);         //Seri port ekranı baut rate değeri
  Serial.println("Ses Deger Okuma");
}

void loop()
{
  deger = analogRead(sensorOutpin); //Ardunio döngü içinde sürekli sensör değerini okur
  if(deger > esik)
  {
    digitalWrite(ledPin,HIGH);      //Okunan deger, esik degerinden büyükse led yanar
    Serial.println(deger);          //Degeri alt alta yazdırıyorum
    delay(500);                     //Led yarım saniye yanıyor
    digitalWrite(ledPin,LOW);       //Led söner
  }
  else                              //Tersi durumunda tüm değerler için led söner
  {
    digitalWrite(ledPin,LOW);
  }
}
