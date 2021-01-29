int santim;
int sure;
int echoPin = 6;
int trigPin = 7;
int sari = 8;
int yesil = 9;
int mavi = 10;

void setup()
{
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin,LOW);

  sure = pulseIn(echoPin,HIGH);

  santim = (sure/2) / 29.1;

  if(santim < 30)
  {
    digitalWrite(mavi,HIGH);
    digitalWrite(yesil,HIGH);
    digitalWrite(sari,HIGH);
  }

  else if((santim >= 30) && (santim < 70))
  {
    digitalWrite(mavi,HIGH);
    digitalWrite(yesil,HIGH);
    digitalWrite(sari,LOW);
  }

  Serial.print(santim);
  Serial.println("cm");
  delay(100);
}
