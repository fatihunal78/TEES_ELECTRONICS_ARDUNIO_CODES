// SA3 - Manuel Bariyer Sistemi

#include <Servo.h>                    // Servo motor kütüphanesini ekle

int servoPin = 3;                     // Servo motorun bağlandığı pin numarasını tanımla
int bariyerDurumu = 0;                // Bariyer durumunun tutulacağı değişkeni tanımla
int butonPin = 2;                     // Butonun bağlandığı pin numarasını tanımla

int servoAdim = 90;                   // Servo motor adım sayısı değişkenini tanımla
int aciDegeri = 90;                   // Kalınan açının tutulacağı değişkeni tanımla 
int tetikDurumu = 0;                  // Hareket halinde butona basılıp basılmadığının tutulacağı değişkeni tanımla

Servo servo;                          // Servo motor tanımla

void setup() {
    pinMode(butonPin, INPUT_PULLUP);  // Butonun bağlandığı pini giriş olarak ayarla ve pull up direncini aktif et  
    servo.attach(servoPin);           // Servo motorun takıldığı pini ayarla  
    servo.write(90);                  // Servo motoru 90 derece konumuna götür
}

void loop() {
    if (digitalRead(butonPin) == LOW) {   // Butona basılıp basılmadığını kontrol et
                                          // Eğer butona basıldı ise 
        bariyerDurumu = 1;                // Bariyer durumunu açık olarak kayıt et 
    }
  
    if (bariyerDurumu == 1) {            // Bariyer durumunu açık ise
        // Servo motoru 90 derece döndürüp, bariyeri kaldır
        for (int i = 0; i < aciDegeri; i++) {
            servoAdim += 1;               // Birer derece adımlarla servo motoru döndür
            servo.write(servoAdim);       // Servo motorun açısını servoAdim değişkenine göre ayarla
            delay(25);                    // 25ms bekle
        }

        for (int j = 0; j < 100; j++) {   // 5 saniye bekleme döngüsü
            delay(50);                    // 50ms bekle
            // Bekleme anında yeni bir araba gelip gelmediğini kontrol et
            if (digitalRead(butonPin) == LOW) {    // Eğer 5 saniye içinde butona basıldı ise                             
                tetikDurumu = 1;                   // Buton ile kapatıldığını kaydet
                j = 100;                           // Döngüden çıkmak için j değerini 100 yap
                delay(500);                        // 500ms bekle
                break;                             // for döngüsünden çık
            }
        }

        // Servo motoru 90 derece terse döndürerek bariyeri indir
        for (int i = 0; i < 90; i++) {
            servoAdim -= 1;                       // Birer derece adımlarla servo motoru döndür
            servo.write(servoAdim);               // Servo motorun açısını servoAdim değişkenine göre ayarla
            delay(25);                            // 25ms bekle
            
            if (digitalRead(butonPin) == LOW) {   // Eğer kapanırken tekrar butona basıldı ise 
                                                  // Bariyeri yukarı kaldırmak için
                aciDegeri = 180 - servoAdim;      // Açı değerini kaldığı yerden devam ettir
                i = 90;                           // Döngüden çıkmak için i değerini 90 yap
                delay(500);                       // 500ms bekle
                break;
            } else {
                tetikDurumu = 0;                  // Buton ile kontrol edilme değişkenini sıfırla
                aciDegeri = 90;                   // Açı değerini 90 olarak kaydet
            }
            
            if (servoAdim == 90) {
                bariyerDurumu = 0;                // Bariyer durumunu kapalı olarak kayıt et  
            }
        }
    }
}
