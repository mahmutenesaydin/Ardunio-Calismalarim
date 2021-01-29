#define potanPin A0
int deger = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Pot Deger Okuma");
}

void loop()
{
  deger = analogRead(potanPin);
  float gerilim = (5.00 / 1024.00) * deger;
  Serial.println(gerilim);
  delay(100);
}
