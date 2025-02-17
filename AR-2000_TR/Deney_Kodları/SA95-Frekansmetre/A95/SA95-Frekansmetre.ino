// SA95 - Frekansmetre

#include <FreqCount.h>          //Frekans ölçmek için gerekli kütüphaneyi ekle         
#include <LiquidCrystal_I2C.h>  //I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);  //1602 LCD ekranı tanımla

double frekans;

void setup() {
    lcd.begin();               //LCD'yi başlat
    lcd.backlight();           //LCD arka ışıklarını aç
    lcd.clear();              //LCD'yi temizle
    FreqCount.begin(1000);     //Frekans ölçümünü başlat

    lcd.setCursor(0, 0);       //LCD'de ilk satıra geç
    lcd.print("TEES ELEKTRONIK");  //TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);       //Alt satıra geç 
    lcd.print(" FREKANS METRE");   //FREKANS METRE yaz
    delay(2000);               //2 saniye bekle
    lcd.clear();               //LCD'yi temizle 
}

void loop() {
    if (FreqCount.available()) {  //Eğer sistem çalışıyor ve değerler geliyorsa
        frekans = FreqCount.read();    //frekans değişkenine ölçülen değeri kaydet
        float period = (1 / frekans);  //periyot=1/frekans formulü ile bulunur. Elde ettiğimiz frekans değerini
                                      //1/frekans yaptığımız zaman periyot değerini buluruz.

        lcd.setCursor(4, 0);      //LCD Ekranda ilk satırda 4.sütuna git
        lcd.print("Frekans");     //LCD ekranda ilk satıra Frekans: yaz
        lcd.setCursor(0, 1);      //LCD Ekranda alt satıra geç
        lcd.print("      ");
        lcd.print(frekans);       //Ölçülen frekans değerini lcd ekrana yaz
        lcd.print(" Hz          ");//Hz yaz    

        if (frekans >= 1000) {    //Eğer frekans değeri 1000'den büyük ise
            lcd.setCursor(4, 0);   //LCD Ekranda ilk satırda 4.sütuna git
            lcd.print("Frekans");  //LCD ekranda ilk satıra Frekans: yaz
            lcd.setCursor(4, 1);   //LCD Ekranda ikinci satırda 4.sütuna git
            lcd.print(frekans / 1000);  //Ölçülen frekans değerini 1000 ile bölüp lcd ekrana yaz
            lcd.print(" KHz         "); //KHz yaz
        }

        if (frekans >= 1000000) { //Eğer frekans değeri 1000000'den büyük ise
            lcd.setCursor(4, 0);   //LCD Ekranda ilk satırda 4.sütuna git
            lcd.print("Frekans");  //LCD ekranda ilk satıra Frekans: yaz
            lcd.setCursor(4, 1);   //LCD Ekranda ikinci satırda 4.sütuna git
            lcd.print(frekans / 1000000);  //Ölçülen frekans değerini 1000 ile bölüp lcd ekrana yaz
            lcd.print(" MHz         "); //MHz yaz
        }
    }
}
