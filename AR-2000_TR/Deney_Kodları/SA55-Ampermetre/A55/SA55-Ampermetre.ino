// SA55 - Ampermetre

#include <LiquidCrystal_I2C.h>                    // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);              // 1602 LCD ekranı tanımla

// Değişkenleri tanımla
int adcPin = 0;
float vout = 0.0;
float Akim_Degeri = 0.0;
int okunanDeger = 0;

void setup() {
    lcd.begin();                                  // LCD'yi başlat
    lcd.backlight();                             // LCD arka ışıklarını aç 
    pinMode(adcPin, INPUT);                      // ADC pinini giriş olarak tanımla
   
    lcd.clear();                                 // LCD'yi temizle
    lcd.setCursor(0, 0);                         // LCD üst satır ilk karakteri seç
    lcd.print("TEES ELEKTRONIK");                // LCD'ye yaz
    lcd.setCursor(2, 1);                         // LCD alt satır üçüncü karakteri seç
    lcd.print(" AMPERMETRE");                    // LCD'ye yaz
    delay(3000);                                 // 3 saniye bekle
    lcd.clear();                                 // LCD'yi temizle
}

void loop() {
    okunanDeger = analogRead(adcPin);            // adcPin deki değeri oku ve okunanDeger değişkenine kaydet
    vout = (okunanDeger * 5.0) / 1024.0;        // okunanDeğeri 5 ile çarpıp 1024'e böldüğümüzde voltaj karşılığını hesapla
                                        
    Akim_Degeri = vout * 31.25;                 // Akım değerini hesaplamak için I=V/R formülünü kullan. Burada V= vout 
                                                // değişkenindeki okunan değer, R ise 100R//47R yani 32 ohm olduğuna göre 
                                                // I=vout/32 yapar bunu mili ampere çevirmek için 1000 ile çarptığımızda
                                                // I=vout/32*1000 --> I= vout*31.25
    
    lcd.clear();
    lcd.setCursor(0, 1);                        // LCD ekranda 2. satıra geç 
    lcd.print("AKIM: ");                        // LCD ekrana AKIM: Yaz 
    lcd.print(Akim_Degeri);                     // Hesaplanan Akim_Degeri değerini yaz
    lcd.print(" mA");                           // mA Yaz 
    delay(1000);
}
