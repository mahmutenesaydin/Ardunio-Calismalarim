#define fadePin 9

void setup()
{
  pinMode(fadePin,OUTPUT);
}

void loop()
{
  for(int i=0; i<360; i++)
  {
    float rad = DEG_TO_RED * i;
    int sinOut = constrain((sin(rad) * 128) + 128, 0, 255);
    analogWrite(fadePin,sinOut);
    delay(15);
  }
}
