// SA16 - LCD Ekranlı Park Sensörü

#include <LiquidCrystal_I2C.h>                    // I2C LCD kütüphanesini ekle

// Hoparlörün takıldığı pin numarasını tanımla
int hoparlorPin = 2;

// HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define trigPin 4

// HC-SR04 Echo bacağının bağlandığı pini tanımla
#define echoPin 5

// Süre ve mesafe değişkenlerini tanımla
long sure, mesafe;

// Uyarı sesi süresinin tutulacağı değişkeni tanımla
int bipSure = 300;

// LCD için Türkçe karakterleri tanımla
byte karakteru[8] = {                             // ü
    0x00, 0x0A, 0x00, 0x0A, 
    0x0A, 0x0A, 0x0E, 0x00
};

byte karaktero[8] = {                             // ö
    0x0A, 0x00, 0x0E, 0x11, 
    0x11, 0x11, 0x0E, 0x00
};

byte karakterbar[8] = {                           // Bar
    0x00, 0x1F, 0x1F, 0x1F, 
    0x1F, 0x1F, 0x1F, 0x00
};

// 1602 LCD ekranı tanımla
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    // Trigger bacağının bağlandığı pini çıkış olarak ayarla
    pinMode(trigPin, OUTPUT);
    
    // Echo bacağının bağlandığı pini giriş olarak ayarla
    pinMode(echoPin, INPUT);
    
    lcd.begin();                                  // LCD'yi başlat
    lcd.backlight();                             // LCD arka ışıklarını aç
    
    // Eklenen karakterleri tanımla
    lcd.createChar(1, karakteru);                // ü karakterini oluştur
    lcd.createChar(2, karaktero);                // ö karakterini oluştur
    lcd.createChar(3, karakterbar);              // bar karakterini oluştur
    
    lcd.clear();                                 // LCD'yi temizle
    lcd.setCursor(0, 0);                         // LCD üst satır ilk karakterini seç
    lcd.print("TEES Elektronik");                // LCD'ye yaz
    lcd.setCursor(2, 1);                         // LCD alt satır ikinci karakterini seç
    lcd.print("Park Sens");                      // LCD'ye yaz
    lcd.write(byte(2));                          // LCD'ye "ö" yaz
    lcd.print("r");                              // LCD'ye "r" yaz
    lcd.write(byte(1));                          // LCD'ye "ü" yaz
    delay(3000);                                 // 3sn bekle
    lcd.clear();                                 // LCD'yi temizle
}

void loop() {
    // Trigger bacağını sıfıra çek
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);                        // 2 mikro saniye bekle
    
    // Trigger bacağını 5V'a çek
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);                       // 10 mikro saniye bekle
    
    // Trigger bacağını sıfıra çek
    digitalWrite(trigPin, LOW);
    
    // Echo pininden geri gelme süresini ölç
    sure = pulseIn(echoPin, HIGH);
    
    // Ölçülen süreyi ses hızı ile çarparak mesafeyi cm olarak hesapla
    mesafe = (sure/2) * 0.034;
    
    lcd.setCursor(0, 0);                         // LCD üst satır ilk karakterini seç
    lcd.print("Mesafe: ");                       // LCD'ye yaz
    
    if (mesafe > 50 || mesafe < 0) {             // Mesafe 50'den büyük ya da 0'dan küçük ise
        lcd.print("--");                         // LCD'ye yaz
    } else {
        if(mesafe > 9) {                         // Mesafe 9'dan büyük ise
            lcd.print(mesafe);                   // Mesafe 2 basamaklı ise LCD'ye mesafeyi yaz
        } else {
            lcd.print(" ");                      // Mesafe tek basamaklı ise LCD'ye bir boşluk bırakarak mesafeyi yaz
            lcd.print(mesafe);  
        }
    }
    
    lcd.print(" cm");                            // LCD'ye yaz
    lcd.setCursor(0, 1);                         // LCD alt satır ilk karakterini seç
    
    if(mesafe > 50) {                            // Mesafe 50'den büyük ise
        // Mesafeyi bar olarak göster
        for(int i = 0; i < 1; i++) {
            lcd.write(byte(3));  
        }
        for(int j = 0; j < 15; j++) {
            lcd.print(" ");
        }
    } else if(mesafe > 40) {                     // Mesafe 40'dan büyük ise
        // Mesafeyi bar olarak göster
        for(int i = 0; i < 4; i++) {
            lcd.write(byte(3));  
        }
        for(int j = 0; j < 10; j++) {
            lcd.print(" ");
        }
    } else if(mesafe > 30) {                     // Mesafe 30'dan büyük ise
        // Mesafeyi bar olarak göster
        for(int i = 0; i < 7; i++) {
            lcd.write(byte(3));  
        }
        for(int j = 0; j < 9; j++) {
            lcd.print(" ");
        }
        // Hoparlörden uyarı sesi çıkar
        tone(hoparlorPin, 440);
        delay(bipSure / 3);
        noTone(hoparlorPin);
        delay(bipSure / 3);
    } else if(mesafe > 20) {                     // Mesafe 20'dan büyük ise
        // Mesafeyi bar olarak göster
        for(int i = 0; i < 10; i++) {
            lcd.write(byte(3));  
        }
        for(int j = 0; j < 6; j++) {
            lcd.print(" ");
        }
        // Hoparlörden uyarı sesi çıkar
        tone(hoparlorPin, 440);
        delay(bipSure / 4);
        noTone(hoparlorPin);
        delay(bipSure / 4);
    } else if(mesafe > 10) {                     // Mesafe 10'dan büyük ise
        // Mesafeyi bar olarak göster
        for(int i = 0; i < 13; i++) {
            lcd.write(byte(3));  
        }
        for(int j = 0; j < 3; j++) {
            lcd.print(" ");
        }
        // Hoparlörden uyarı sesi çıkar
        tone(hoparlorPin, 440);
        delay(bipSure / 5);
        noTone(hoparlorPin);
        delay(bipSure / 5);
    } else if(mesafe > 5) {                      // Mesafe 5'den büyük ise
        // Mesafeyi bar olarak göster
        for(int i = 0; i < 16; i++) {
            lcd.write(byte(3));  
        }
        // Hoparlörden uyarı sesi çıkar
        tone(hoparlorPin, 440);
    }
}
