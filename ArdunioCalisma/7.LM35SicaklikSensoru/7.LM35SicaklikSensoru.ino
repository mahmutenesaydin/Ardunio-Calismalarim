float sicaklik;
float analogGerilim;
int sicaklikPin = 1;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  analogGerilim = analogRead(sicaklikPin);
  analogGerilim = (analogGerilim / 1023) * 5000;
  sicaklik = analogGerilim / 10,0;

  Serial.print("Sicaklik Degeri: ");
  Serial.print(sicaklik);
  Serial.println(" derece");
  delay(1000);
}
