int r = 3;
int g = 5;
int b = 6;


void setup()
{
  pinMode(r,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(b,OUTPUT);
}

void loop()
{
    int rDeger = random(0,255);
    int gDeger = random(0,255);
    int bDeger = random(0,255);
  analogWrite(r,rDeger);
  analogWrite(g,gDeger);
  analogWrite(b,bDeger);
  delay(1000); 
}
