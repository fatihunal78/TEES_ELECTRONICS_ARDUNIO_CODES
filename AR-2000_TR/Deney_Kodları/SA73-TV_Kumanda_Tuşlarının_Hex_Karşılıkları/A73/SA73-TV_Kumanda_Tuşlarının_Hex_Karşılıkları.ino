// SA73 - TV Kumanda Tuşlarının Hex Karşılıkları

#include <IRremote.h>          // IR alıcı kütüphanesini ekle
#include <LiquidCrystal_I2C.h> // I2C LCD kütüphanesini ekle

int irPin = 2;                 // IR alıcı sinyal bacağının bağlandığı pini tanımla
int buzzerPin = 5;             // Buzzerın bağlandığı pin numarasını tanımla
LiquidCrystal_I2C lcd(0x27, 16, 2); // 1602 LCD ekranı tanımla

IRrecv iralici(irPin);         // iralici adında bir IR alıcı tanımla
decode_results sonuc;          // IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

void setup() {
    pinMode(buzzerPin, OUTPUT); // Buzzerın bağlandığı pini çıkış olarak ayarla
    lcd.begin();               // LCD'yi başlat
    lcd.backlight();           // LCD arka ışıklarını aç
    lcd.clear();               // LCD'yi temizle

    iralici.enableIRIn();      // IR alıcıyı başlat

    lcd.setCursor(0, 0);
    lcd.print("TV KUMANDASI");
    lcd.setCursor(0, 1);
    lcd.print("TUSLARINI OGREN");
    delay(3000);
    lcd.clear();
}

void loop() {
    // IR alıcıdan bir bilgi gelip gelmediğini kontrol et
    if (iralici.decode(&sonuc)) {     // Bilgi geldi ise
        if (sonuc.value != 0) {       // Eğer kumandanın tuşuna basıldı ise
            digitalWrite(buzzerPin, HIGH); // Buzzer ses çıkar
            delay(50);                // 50 ms bekle
            digitalWrite(buzzerPin, LOW);  // Buzzerı sustur
        }
        
        lcd.clear();
        lcd.print("0x");
        lcd.print(sonuc.value, HEX);  // Gelen bilgiyi HEX formatında LCD ekrana gönder
        delay(500);                   // 500ms bekle
        iralici.resume();             // IR alıcıyı diğer değerleri alabilmesi için sıfırla
    }
}
