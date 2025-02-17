// SA13 - IR uzaktan kumanda tuşlarını öğrenelim

#include <IRremote.h>           // IR alıcı kütüphanesini ekle
#include <LiquidCrystal_I2C.h>  // I2C LCD kütüphanesini ekle

int irPin = 2;                  // IR alıcı sinyal bacağının bağlandığı pini tanımla

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 1602 LCD ekranı tanımla

IRrecv iralici(irPin);              // iralici adında bir IR alıcı tanımla
decode_results sonuc;                // IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

void setup()
{
    lcd.begin();      // LCD'yi başlat
    lcd.backlight();  // LCD arka ışıklarını aç
    lcd.clear();      // LCD'yi temizle
    
    iralici.enableIRIn();  // IR alıcıyı başlat

    // LCD ekranın ilk satırına TEES ELEKTRONIK, ikinci satırına IR KUMANDA yaz.
    lcd.setCursor(0,0);
    lcd.print("TEES ELEKTRONIK");
    lcd.setCursor(0,1);
    lcd.print("  IR KUMANDA  ");
    delay(3000);
    lcd.clear();
}

void loop() 
{
    // IR alıcıdan bir bilgi gelip gelmediğini kontrol et
    if (iralici.decode(&sonuc))  // IR alıcıdan bilgi geldi ise
    {
        lcd.clear();
        lcd.print("0x");
        lcd.print(sonuc.value, HEX);  // Gelen bilgiyi HEX formatında LCD ekrana yazdır
        delay(500);                    // 500ms bekle
        iralici.resume();             // IR alıcıyı diğer değerleri alabilmesi için sıfırla
    }
}
