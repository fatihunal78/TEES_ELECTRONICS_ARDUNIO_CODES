// SA7 - LCD ekranda karakter oluştur

// İlgili kütüphaneleri ekle
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);                             // 1602 LCD ekranı tanımla
  
uint8_t karakter0[8] = {0x0,0xE,0x11,0x10,0x11,0xE,0x4,0x0};   // ç karakteri
uint8_t karakter1[8] = {0xE,0x0,0xE,0x11,0xF,0x1,0xE,0x0};     // ğ karakteri
uint8_t karakter2[8] = {0x0,0xA,0x0,0xE,0x11,0x11,0xE,0x0};    // ö karakteri
uint8_t karakter3[8] = {0x0,0xF,0x10,0xE,0x1,0x1E,0x4,0x0};    // ş karakteri
uint8_t karakter4[8] = {0xC,0x12,0x12,0xC,0x0,0x0,0x0,0x0};    // derece karakteri
uint8_t karakter5[8] = {0x0,0x0,0xA,0x1F,0x1F,0xE,0x4,0x0};    // kalp karakteri
uint8_t karakter6[8] = {0x4,0xE,0x1F,0x4,0x4,0x4,0x4,0x0};     // yukarı ok karakteri
 
void setup() {
    lcd.begin();                                                 // LCD başlat
    lcd.backlight();                                            // LCD arka ışıklarını aç
    lcd.createChar(0, karakter0);                               // ç karakterini oluştur ve 0. adresine tanımla
    lcd.createChar(1, karakter1);                               // ğ karakterini oluştur ve 1. adresine tanımla
    lcd.createChar(2, karakter2);                               // ö karakterini oluştur ve 2. adresine tanımla
    lcd.createChar(3, karakter3);                               // ş karakterini oluştur ve 3. adresine tanımla
    lcd.createChar(4, karakter4);                               // derece karakterini oluştur ve 4. adresine tanımla
    lcd.createChar(5, karakter5);                               // kalp karakterini oluştur ve 5. adresine tanımla
    lcd.createChar(6, karakter6);                               // yukarı ok karakterini oluştur ve 6. adresine tanımla
}
 
void loop() {
    lcd.setCursor(4, 0);                                        // LCD'de kursoru 0. satır 4. sütuna al
 
    for (int i = 0; i <= 6; i++) {                             // for döngüsü ile 
        lcd.print((char)i);                                     // Karakterleri ekrana yazdır
    }
}
