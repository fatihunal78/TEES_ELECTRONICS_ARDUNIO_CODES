// SA6 - LCD ekranda kayan yazı

#include <LiquidCrystal_I2C.h>                    // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);              // 1602 LCD ekranı tanımla

int potDegeri;                                    // Potansiyometrenin değerinin tutulacağı değişkeni tanımla

void setup() {
    lcd.begin();                                  // LCD'yi başlat
    lcd.backlight();                              // LCD arka ışıklarını aç
    lcd.clear();                                  // LCD'yi temizle
}

void loop() {
    potDegeri = analogRead(A0);                   // Analog A0 pinine bağlanan potansiyometrenin değerini oku ve 
                                                 // potDegeri değişkenine yaz

    potDegeri = map(potDegeri, 0, 1023, 50, 350);// Analog pinden okunan potDegeri degerinin aldığı 0 ile 1023 
                                                 // arasındaki değeri 50 ile 350 arasında oranla. Bu değerleri 
                                                 // delay fonksiyonunda kaydırma hızını değiştirmek için 
                                                 // kullanacağız.
                                        
    lcd.setCursor(0, 0);                         // Kursoru (İmleci) ilk satır, ilk karaktere git 
    lcd.print("    Merhaba!    ");               // İlk satıra Merhaba! yaz
    lcd.setCursor(0, 1);                         // İkinci satır, ilk karaktere git
    lcd.print("TEES ELEKTRONIK");                // TEES ELEKTRONIK yaz

    delay(potDegeri);                            // potDegeri değişkeni kadar gecikme
                                                 // Potansiyometrenin durumuna göre 50 ile 350 arasında gecikme 
                                                 // ayarlanacaktır

    lcd.scrollDisplayLeft();                     // Sol tarafa yazıları kaydırmak
                                                 // Sağ tarafa kaydırmak için lcd.scrollDisplayRight(); komutu 
                                                 // kullanılabilir
}
