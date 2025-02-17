// SA5 - LCD Kullanımına Giriş

#include <LiquidCrystal_I2C.h>                    // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);              // 1602 ekranı tanımla
                                                  // Burada 0x27 LCD adresini belirtir. Kartın arkasında yazar. 
                                                  // Bazı kartlarda farklı olabilir. 
                                                  // 16 LCD de bir satırdaki maksimum karakter sayısını belirtir  
                                                  // 2 bir sütundaki maksimum karakter sayısını belirtir.

void setup() {
    lcd.begin();                                  // LCD'yi başlat
    lcd.backlight();                             // LCD arka ışıklarını aç
    lcd.clear();                                 // LCD'yi temizle
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print("TEES ELEKTRONIK");                // Buradaki yazıyı değiştirdikten sonra tekrar Arduino'ya 
                                                // yükleme işlemi yapabilirsiniz
    lcd.setCursor(0, 1);            
    lcd.print("  KODLAMA SETI  ");
}