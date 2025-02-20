// SA91 - FM Radyo

#include <Wire.h>                  //Haberleşme kütüphanesini ekle
#include <TEA5767N.h>             //FM radyo kütüphanesini ekle
#include <LiquidCrystal_I2C.h>    //I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);  //1602 LCD ekranı tanımla

int aramaButon = 2;    //FM RADYO kanal araması için buton 
int resetButon = 3;    //FM Radyo ilk kanla(87.50)'e geçmek için buton

TEA5767N radyo = TEA5767N();    //radyo isimli bir obje oluştur
float radyo_frekans = 87.5;     //radyo_frekans isimli değişkeni tnaımla ve ilk değerini 87.5 yap

void setup() {
    pinMode(aramaButon, INPUT_PULLUP);    //aramaButonun bağlandığı pini giriş olarak ayarla
    pinMode(resetButon, INPUT_PULLUP);    //resetButonun bağlandığı pini giriş olarak ayarla
  
    lcd.begin();           //LCD'yi başlat
    lcd.backlight();       //LCD arka ışıklarını aç
    lcd.clear();          //LCD'yi temizle  
    delay(250);  
    
    radyo.selectFrequency(radyo_frekans);    //Radyoyu 87.5'a ayarla
    delay(250);
    radyo.setStereoReception();
    
    lcd.setCursor(0, 0);              //LCD 1. satıra geç
    lcd.print(" TEES ELEKTRONIK");
    lcd.setCursor(0, 1);              //LCD'de 2. satıra geç 
    lcd.print("    FM RADYO    ");    //FM RADYO yaz
    delay(2000);                      //2 saniye bekle 
    
    lcd.clear(); 
    lcd.setCursor(0, 0);              //LCD 1. satıra geç
    lcd.print(" Radyo Frekans ");
    lcd.setCursor(0, 1);              //LCD'de 2. satıra geç 
    lcd.print("FM : ");
    lcd.print(radyo_frekans);         //Frekans değerini yaz
    lcd.print(" MHz");
}
 
void loop() {
    if (digitalRead(aramaButon) == LOW) {    //Eğer butona basıldı ise Kanal değiştirmek için aşağıdaki işlemleri yap 
        radyo_frekans += 0.1;                //radyo_frekans değişkenini 0.1 arttır 
        radyo.selectFrequency(radyo_frekans);    //Arttırılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
    
        lcd.clear(); 
        lcd.setCursor(0, 0);              //LCD 1. satıra geç
        lcd.print(" Radyo Frekans ");
        lcd.setCursor(0, 1);              //LCD'de 2. satıra geç 
        lcd.print("FM : ");
        lcd.print(radyo_frekans);         //Frekans değerini yazdır.
        lcd.print(" MHz");
  
        if (radyo_frekans > 108.0) {
            radyo_frekans = 87.5; 
            radyo.selectFrequency(radyo_frekans);
        }
    }

    if (digitalRead(resetButon) == LOW) {    //Eğer reset butonuna basıldı ise 
        radyo_frekans = 87.5;                //radyo_frekans değişkenini 87.5 MHz'e ayarla
        radyo.selectFrequency(radyo_frekans);    //radyo_frekans değişkenini radyoya yaz ve kanalı aç
  
        lcd.clear(); 
        lcd.setCursor(0, 0);              //LCD 1. satıra geç
        lcd.print("Radyo Frekans: ");
        lcd.setCursor(0, 1);              //LCD'de 2. satıra geç 
        lcd.print("FM : ");
        lcd.print(radyo_frekans);         //Frekans değerini yaz
        lcd.print(" MHz");
    }
    delay(250);
}
