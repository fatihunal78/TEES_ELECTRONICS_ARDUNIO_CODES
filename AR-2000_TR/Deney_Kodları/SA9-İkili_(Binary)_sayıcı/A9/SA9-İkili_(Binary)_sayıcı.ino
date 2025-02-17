// SA9 - İkili (Binary) sayıcı

#include <LiquidCrystal_I2C.h>                                    // I2C LCD kütüphanesini ekle

int ledler[] = {3, 4, 5, 6};                                      // LED'lerin bağlandığı dijital pin numaralarını tanımla
int butonPin = 2;                                                 // Butonun bağlandığı pin numarasını tanımla
int sayi = 0;                                                     // Sayının tutulacağı değişkeni tanımla

LiquidCrystal_I2C lcd(0x27, 16, 2);                              // 1602 LCD ekranı tanımla

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    // for döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for(int i = 0; i < 4; i++) {
        pinMode(ledler[i], OUTPUT);
    }
  
    pinMode(butonPin, INPUT_PULLUP);                             // Butonun bağlandığı pini giriş olarak ayarla
    lcd.begin();                                                 // LCD'yi başlat 
    lcd.backlight();                                            // LCD arka ışıklarını aç
  
    lcd.clear();                                                // LCD'yi temizle
    lcd.setCursor(0, 0);                                        // Ekranın ilk satır, ilk karaktere git 
    lcd.print("TEES ELEKTRONIK");
    lcd.setCursor(1, 1);                                        // Ekranın ikinci satır, ikinci karaktere git 
    lcd.print(" BINARY SAYAC");  
    delay(3000);                                                // 3 saniye bekle
    lcd.clear();                                                // LCD'yi temizle
}

void loop() {
    if(digitalRead(butonPin) == LOW) {                          // Butona basılıp basılmadığını kontrol et
                                                                // Eğer butona basıldı ise
        while(digitalRead(butonPin) == LOW);                    // Butona basılı olduğu sürece bekle
        sayi++;                                                 // sayi değişkenini bir arttır
        if(sayi > 15) {                                        // Sayı değişkeninin değeri 15'in üzerinde ise
            sayi = 0;                                          // Sayı değerini sıfıra eşitle
            lcd.clear();                                       // LCD'yi temizle
        }
    }

    switch(sayi) {
        case 0:                                                // sayi değişkeni sıfır ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            lcd.clear();                                       // LCD'yi temizle 
            break;

        case 1:                                                // sayi değişkeni bir ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
      
            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print("000"); 
            lcd.print(sayi, BIN); 
            break;

        case 2:                                                // sayi değeri iki ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[1], HIGH);
      
            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print("00"); 
            lcd.print(sayi, BIN); 
            break;

        case 3:                                                // sayi değeri üç ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
            digitalWrite(ledler[1], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print("00"); 
            lcd.print(sayi, BIN); 
            break;

        case 4:                                                // sayi değeri dört ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[2], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print("0"); 
            lcd.print(sayi, BIN); 
            break;

        case 5:                                                // sayi değeri beş ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
            digitalWrite(ledler[2], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print("0"); 
            lcd.print(sayi, BIN); 
            break;

        case 6:                                                // sayi değeri altı ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[2], HIGH);
      
            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print("0"); 
            lcd.print(sayi, BIN);  
            break;

        case 7:                                                // sayi değeri yedi ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[2], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print("0"); 
            lcd.print(sayi, BIN); 
            break;

        case 8:                                                // sayi değeri sekiz ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[3], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN); 
            break;

        case 9:                                                // sayi değeri dokuz ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
            digitalWrite(ledler[3], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN);  
            break;

        case 10:                                               // sayi değeri on ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[3], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN); 
            break;

        case 11:                                               // sayi değeri on bir ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[3], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN); 
            break;

        case 12:                                               // sayi değeri on iki ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[2], HIGH);
            digitalWrite(ledler[3], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN); 
            break;

        case 13:                                               // sayi değeri on üç ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
            digitalWrite(ledler[2], HIGH);
            digitalWrite(ledler[3], HIGH);
      
            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN); 
            break;

        case 14:                                               // sayi değeri on dört ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[2], HIGH);
            digitalWrite(ledler[3], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN); 
            break;

        case 15:                                               // sayi değeri on beş ise
            // Tüm LED'leri söndür
            for(int i = 0; i < 4; i++) {
                digitalWrite(ledler[i], LOW);
            }
            // Binary olarak sayısı LED'lerde göster
            digitalWrite(ledler[0], HIGH);
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[2], HIGH);
            digitalWrite(ledler[3], HIGH);

            lcd.clear();                                       // LCD'yi Temizle 
            lcd.setCursor(0, 0);                              // İlk satır, ilk karaktere git 
            lcd.print("Ondalik: ");                           // LCD'ye yaz
            lcd.print(sayi);                                  // LCD'ye sayi değerini yaz
            lcd.setCursor(0, 1);                              // İkinci satır, ilk karaktere git
            lcd.print("ikili  : "); 
            lcd.print(sayi, BIN); 
            break;
    }
    delay(200);                                               // 200ms bekle
}
