// SA8 - Dijital Metre
#include <LiquidCrystal_I2C.h>    // I2C LCD kütüphanesini ekle
#define trigPin 2                  // HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define echoPin 3                  // HC-SR04 Echo bacağının bağlandığı pini tanımla
long sure, mesafe;                 // Süre ve mesafe değişkenlerini tanımla

LiquidCrystal_I2C lcd(0x27, 16, 2); // 1602 LCD ekranı tanımla
 
void setup() {
    pinMode(trigPin, OUTPUT);        // Trigger bacağının bağlandığı pini çıkış olarak ayarla 
    pinMode(echoPin, INPUT);         // Echo bacağının bağlandığı pini giriş olarak ayarla
  
    lcd.begin();                     // LCD'yi başlat
    lcd.backlight();                 // LCD arka ışıklarını aç
  
    lcd.clear();                     // LCD'yi temizle
    lcd.setCursor(0,0);              // LCD ilk satır, ilk karaktere git
    lcd.print("TEES ELEKTRONIK");    // LCD'ye yaz
    lcd.setCursor(0,1);              // LCD ikinci satır, ilk karaktere git
    lcd.print("Dijital Metre");      // LCD'ye yaz  
    delay(3000);                     // 3 saniye bekle
    lcd.clear();                     // LCD'yi temizle
}

void loop() {
    digitalWrite(trigPin, LOW);      // Trigger bacağını sıfıra çek
    delayMicroseconds(2);            // 2 mikro saniye bekle  
    digitalWrite(trigPin, HIGH);      // Trigger bacağını 5V'a çek
    delayMicroseconds(10);           // 10 mikro saniye bekle  
    digitalWrite(trigPin, LOW);       // Trigger bacağını sıfıra çek
  
    sure = pulseIn(echoPin, HIGH);   // Echo pininden ses dalgalarının geri gelme süresini ölç 
    mesafe = (sure/2) * 0.034;       // Ölçülen süreyi ses hızı ile çarparak mesafeyi cm olarak hesapla
  
    lcd.setCursor(0,0);              // LCD ilk satır, ilk karaktere git
    lcd.print("Mesafe:");            // LCD'ye yaz
    lcd.print(mesafe);               // Ölçülen mesafeyi LCD ekrana yaz
    lcd.print("cm");                 // LCD Ekrana "cm" yaz  
    delay(300);                      // 300ms bekle
    lcd.clear();                     // LCD'yi temizle
}
