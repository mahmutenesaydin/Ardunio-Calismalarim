String agAdi = "asddas";
String agSifresi = "dgdfşl";
int motorPin1 = 3, motorPin2 = 4, motorPin3 = 5, motorPin4 = 6;

void serialTemizle(long int zamanAsimi)
{                                           //Seri haberleşmede kullandığımız byte'leri temizler
  long int baslangic = millis();
  while(millis() - baslangic < zamanAsimi)
  {
    if(Serial.available() >0 )
    {
      Serial.read();
    }
  }
}


void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.begin(115200);
  Serial.println("AT");  //AT komutu ile modül kontrolünü yapıyoruz

  while(!Serial.find("OK"))
  {
    Serial.println("AT");                  //Modül hazır olana kadar bekliyoruz   
  }
  delay(1000);

  Serial.println("AT+RST");             //ESP'yi resetliyoruz
  delay(1000);

  while(!Serial.find("OK"));            //Resetleme işleminin bitmesini bekliyoruz
  delay(1000);

  Serial.println("AT+CWMODE=1");        //Modülümüzü client olarak ayarlıyoruz
  while(!Serial.find("OK"));            //Ayarlanmanın tamamlanmasını bekliyoruz

  Serial.print("AT+CWJAP=\"" + agAdi+ "\",\""+agSifresi+"\"");  //Wifi'ye bağlanıyoruz
  while(!Serial.find("OK"));            //Bağlanana kadar bekliyoruz

  Serial.print("AT+CIFSR\r\n");         //IP adresini ve MAC adresini bekliyoruz
  Serial.print(espOkuma(1000));               //IP ve MAC adresini ekrana yazıyoruz
  serialTemizle(2000);                  //Seri haberleşmede kullanmadığımız verileri temizliyoruz
  
  Serial.print("AT+CIPMUX=1\r\n");      //Çoklu bağlantı ayarını yapıyoruz
  serialTemizle(2000);

  Serial.print("AT+CIPSERVER=1,80\r\n");  //Server oluşturuyoruz ve 80.porttan dinlemeye başlıyoruz
  serialTemizle(2000);
  
}

String espOkuma(long int zamanAsimi)
{                           //ESP'den gelen dönütleri okur.
  long int baslangic = millis();  
  String gelen;
  while(millis() - baslangic < zamanAsimi)
  {                   
    if(Serial.available()>0)
    {
        char c = Serial.read(); 
        gelen += c;
    } 
  }
  gelen.replace("AT+","");
  return gelen;
}




void stepIleri(int beklemeSuresi)
{                                       //Step motora ileri hareketi yaptırır
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(beklemeSuresi);
}



void stepGeri(int beklemeSuresi)
{                                   //Step motora geri hareketi yaptırır
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(beklemeSuresi);

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
  
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(beklemeSuresi);
}


void loop()
{ 
  if(Serial.available())              //Seri haberleşme verisi geldiğininde içindeki komutlar çalışır
  {
    if(Serial.find("+IPD,"))          //Bağlantı isteği geldiğinde içindeki komutlar çalışır
    {
      delay(200);
      int connectionId = Serial.read() - 48;    //Bağlantı numarasını okuyoruz
      String komut = espOkuma(1000);            //Bağlantı komutlarını alıyoruz 
      if(komut.indexOf("step = ileri") != -1)
      {
        for(int adim = 0; adim < 50; adim++)     //Step motora 5 kere ileri adım yaptırılır
        {          
          stepIleri(40);
        }
      }
         else if(komut.indexOf("step = geri") != -1)       //Geri komutu geldiğinde içerisindeki komutlar çalışır
        {
          for(int adim = 0; adim < 50; adim++)    //Step motora 5 kere geri hareketi yaptırılır
          {
            stepGeri(40);
          }
        } 
        String sayfa = "<h1>Step Motor Kontrol</h1><br>";                           
        sayfa+="<br><a href=\"?step=ileri\"><button><h1>Ileri</h1></button></a>";
        sayfa+="<br><br><a href=\"?step=geri\"><button><h1>Geri</h1></button></a>";

        komut = "AT+CIPSEND=";      //Sayfa verisinin uzunluğu komut değişkenine eşitlenir
        komut+= connectionId;
        komut+=",";
        komut+=sayfa.length();
        komut+="\r\n";
        Serial.print(komut);        //Komut gönderilir
        delay(1000);
        komut+= "AT+CIPCLOSE=";     //Bağlantı sonlandırma komutu ayarlanır
        komut+=connectionId;
        komut+="\r\n";
        Serial.print(komut);        //Bağlantı sonlandırma komutu gönderilir
      }
    } 
  }
