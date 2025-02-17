// SA78 - Tavla Zarı

//LED'lerin bağlandığı dijital pin numaralarını tanımla
int ledler[] = {3,4,5,6,7,8,9};
//Butonun bağlandığı pin numarasını tanımla
int butonPin = 2;
// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin=12; 

//Sayının tutulacağı değişkeni tanımla
int sayi = 0;

void setup() {
  //LED'lerin bağlandığı pinleri çıkış olarak ayarla
  //For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
  for(int i = 0; i < 7; i++)
  {
    pinMode(ledler[i], OUTPUT);
  }
  //Butonun bağlandığı pini giriş olarak ayarla
  pinMode(butonPin, INPUT_PULLUP);
  // Hoparlörün bağlandığı pini çıkış pini olarak ayarla
  pinMode(hoparlorPin,OUTPUT);
}

void loop() {
  //Butona basılıp basılmadığını kontrol et
  if(digitalRead(butonPin) == LOW)//Butona basıldı ise
  {
    for(int i = 0; i < 7; i++)//7 kere tekrarla
    {
      randomSeed(analogRead(A0)); //Analog 0 pinini rastgele sayı üretmek için referans al
      //1 ile 6 arasında rastgele bir sayı belirle ve sayi değişkenine kaydet
      sayi = random(1, 7);
      tone(hoparlorPin,sayi*220);
      zarGoster(sayi);//zarGoster fonsiyonuna sayi değişlenini gönder
      delay(300);//300ms bekle
      noTone(hoparlorPin);
    }
  }
}
//zarGoster fonksiyonunu tanımla
void zarGoster(int zar)
{
  switch(zar)//zar değerine göre switch case işlemini yap
  {
    case 1:
      //Bütün LED'leri söndür
      for(int i = 0; i < 7; i++)
        digitalWrite(ledler[i], LOW);
      //1 sayısını zarda göster
      digitalWrite(ledler[4], HIGH);
    break;
    case 2:
      //Bütün LED'leri söndür
      for(int i = 0; i < 7; i++)
        digitalWrite(ledler[i], LOW);
      //2 sayısını zarda göster
      digitalWrite(ledler[1], HIGH);
      digitalWrite(ledler[6], HIGH);
    break;
    case 3:
      //Bütün LED'leri söndür
      for(int i = 0; i < 7; i++)
        digitalWrite(ledler[i], LOW);
      //3 sayısını zarda göster
      digitalWrite(ledler[1], HIGH);
      digitalWrite(ledler[4], HIGH);
      digitalWrite(ledler[6], HIGH);
    break;
    case 4:
      //Bütün LED'leri söndür
      for(int i = 0; i < 7; i++)
        digitalWrite(ledler[i], LOW);
      //4 sayısını zarda göster
      digitalWrite(ledler[0], HIGH);
      digitalWrite(ledler[1], HIGH);
      digitalWrite(ledler[3], HIGH);
      digitalWrite(ledler[6], HIGH);
    break;
    case 5:
      //Bütün LED'leri söndür
      for(int i = 0; i < 7; i++)
        digitalWrite(ledler[i], LOW);
      //5 sayısını zarda göster
      digitalWrite(ledler[0], HIGH);
      digitalWrite(ledler[1], HIGH);
      digitalWrite(ledler[3], HIGH);
      digitalWrite(ledler[4], HIGH);
      digitalWrite(ledler[6], HIGH);
    break;
    case 6:
      //Bütün LED'leri söndür
      for(int i = 0; i < 7; i++)
        digitalWrite(ledler[i], LOW);
      //6 sayısını zarda göster
      digitalWrite(ledler[0], HIGH);
      digitalWrite(ledler[1], HIGH);
      digitalWrite(ledler[2], HIGH);
      digitalWrite(ledler[3], HIGH);
      digitalWrite(ledler[5], HIGH);
      digitalWrite(ledler[6], HIGH);
    break;
  }
}
