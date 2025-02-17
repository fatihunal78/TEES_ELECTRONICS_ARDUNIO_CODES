// SA52 - Renk Algılama

#include <LiquidCrystal_I2C.h>                    //I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);              //1602 LED ekranı tanımla

int butonPin = 2;                                 //Butonun bağlandığı pin numarasını tanımla
int kirmizi_led = 5;                             //RGB Kırmızı LED'in bağlı olduğu pini tanımla 
int yesil_led = 6;                               //RGB Yeşil LED'in bağlı olduğu pini tanımla
int mavi_led = 8;                                //RGB Mavi LED'in bağlı olduğu pini tanımla
int ldr_pin = A0;                                //LDR'nin bağlandığı pin numarasını tanımla

//Okunan renk değerlerinin tutulacağı değişkenleri tanımla
int kirmizi_okunan;
int yesil_okunan;
int mavi_okunan;

void setup() {
    pinMode(kirmizi_led, OUTPUT);                 //Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesil_led, OUTPUT);                   //Yeşil LED'in bağlandığı pini çıkış olarak ayarla 
    pinMode(mavi_led, OUTPUT);                    //Mavi LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(butonPin, INPUT_PULLUP);              //Butonun bağlandığı pini giriş olarak ayarla
  
    lcd.begin();                                  //LCD'yi başlat
    lcd.backlight();                             //LCD arka ışıklarını aç
    lcd.clear();                                 //LCD'yi temizle

    lcd.setCursor(0, 0);                         //İlk satıra geç
    lcd.print("TEES ELEKTRONIK");                //İlk satıra TEES Elektronik
    lcd.setCursor(0, 1);                         //İkinci satıra geç
    lcd.print(" RENK ALGILAMA");                 //LCD'ye renk algılama yaz
    delay(2000);                                 //2 saniye bekle  
}

void loop() {
    if (digitalRead(butonPin) == LOW) {          //Eğer butona basıldı ise, renk algılamayı başlat
        lcd.clear();                             //LCD'yi temizle

        //Kırmızı değerdeki okumayı yapmak için analogWrite komutu ile Kırmızı LED'e 100 PWM değeri yaz ve 
        //diğer LED'leri söndür 
        analogWrite(kirmizi_led, 100);
        digitalWrite(yesil_led, HIGH);
        digitalWrite(mavi_led, HIGH);
        delay(50);                               //50 ms bekle 
        kirmizi_okunan = analogRead(ldr_pin);    //Kırmızı değer okumasını yap ve kirmizi_okunan değişkenine kaydet 
        delay(50);

        //Mavi okuma için Mavi LED'i yak diğerlerini söndür
        digitalWrite(kirmizi_led, HIGH);
        digitalWrite(yesil_led, HIGH);
        digitalWrite(mavi_led, LOW);
        delay(50);
        mavi_okunan = analogRead(ldr_pin);       //Mavi değer okumasını yap ve mavi_okunan değişkenine kaydet 
        delay(50);

        //Yeşil okuma için yeşil LED'i analogWrite komutu ile 100 PWM değerinde yak, diğer LED'leri söndür
        digitalWrite(kirmizi_led, HIGH);
        analogWrite(yesil_led, 100);
        digitalWrite(mavi_led, HIGH);   
        delay(50);
        yesil_okunan = analogRead(ldr_pin);      //Yeşil değer okumasını yap ve yesil_okunan değişkenine kaydet 
        delay(50);
  
        //RGB LED'i söndür
        digitalWrite(kirmizi_led, HIGH);
        digitalWrite(yesil_led, HIGH);
        digitalWrite(mavi_led, HIGH);
  
        //Eğer kirmizi_okunan değişkeninde tutulan değer diğer LED'lerden büyük ise bu durumda algılanan renk 
        //kırmızı oluyor 
        if (kirmizi_okunan > yesil_okunan && kirmizi_okunan > mavi_okunan) {
            lcd.print("    KIRMIZI");            //LCD ekrana KIRMIZI yaz 
        }
        //Eğer yesil_okunan değişkeninde tutulan değer diğer LED'lerden büyük ise bu durumda algılanan renk 
        //yeşil oluyor 
        else if (yesil_okunan > kirmizi_okunan && yesil_okunan > mavi_okunan) {
            lcd.print("     YESIL");             //LCD ekrana YESIL yaz 
        }
        //Eğer mavi_okunan değişkeninde tutulan değer diğer LED'lerden büyük ise bu durumda algılanan renk 
        //mavi oluyor
        else if (mavi_okunan > kirmizi_okunan && mavi_okunan > yesil_okunan) {
            lcd.print("      MAVI");             //LCD ekrana MAVI yaz 
        } 
    }
}
