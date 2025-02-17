// SA84 - Dinamo

#include <LiquidCrystal_I2C.h>                    // LCD ekran kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);              // 1602 LCD ekranı tanımla

int dinamoPin = A0;                               // Motorda üretilen enerjinin okunacağı pin numarasını tanımla
double voltajDegeri;                              // Dinamodan okunan voltajın tutulacağı değişkeni tanımla

void setup() 
{
    pinMode(dinamoPin, INPUT);                    // DinamoPin'i giriş pini olarak ayarla
    
    lcd.backlight();                             // LCD arka ışıkları aç
    lcd.begin();                                 // LCD başlat

    lcd.setCursor(0, 0);                        // LCD ekranda ilk satıra geç
    lcd.print("TEES ELEKTRONIK");               // TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);                        // Alt satıra geç
    lcd.print("     DINAMO     ");              // DINAMO yaz
    delay(2000);                                // 2 saniye bekle
    lcd.clear();                                // LCD'yi temizle
}

void loop() 
{
    voltajDegeri = analogRead(dinamoPin) * 5 / 1023.0;    // DinamoPinden(A0) değeri oku ve 5 ile çarpıp 1023'e 
                                                          // bölerek voltaj karşılığını voltajDegeri değişkenine kaydet

    lcd.setCursor(0, 0);                        // LCD Ekranda ilk satıra
    lcd.print("Voltaj: ");                      // Voltaj: yaz
    lcd.print(voltajDegeri);                    // voltajDegerini yaz
    lcd.print(" V");
}
