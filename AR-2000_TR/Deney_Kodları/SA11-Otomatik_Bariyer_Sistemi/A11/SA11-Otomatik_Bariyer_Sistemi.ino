// SA11 - Otomatik Bariyer Sistemi

#include <Servo.h>                                    // Servo motor kütüphanesini ekle

int ldrPin = A5;                                     // LDR'nin bağlandığı pin numarasını tanımla
int servoPin = 3;                                    // Servo motorun bağlandığı pin numarasını tanımla
int bariyerDurumu = 0;                               // Bariyer durumunun tutulacağı değişkeni tanımla
int servoAdim = 90;                                  // Servo motor adım sayısı değişkenini tanımla
int aciDegeri = 90;                                  // Kalınan açının tutulacağı değişkeni tanımla
int tetikDurumu = 0;                                 // Hareket halinde butona basılıp basılmadığının tutulacağı değişkeni tanımla
Servo servo;                                         // Servo motor tanımla

void setup() {
    pinMode(ldrPin, INPUT);                          // LDR'nin bağlandığı pini giriş olarak ayarla
    servo.attach(servoPin);                          // Servo motorun takıldığı pini tanımla
    servo.write(90);                                 // Servo motoru 90 derece konumuna al
}

void loop() {
    if (analogRead(ldrPin) > 900) {                  // LDR'den okunan değer sınır değerin üzerindeyse
        bariyerDurumu = 1;                           // Bariyer durumunu açık olarak kayıt et 
    }

    if (bariyerDurumu == 1) {                        // Bariyer durumunu açık ise
        for (int i = 0; i < aciDegeri; i++) {        // Servo motoru 90 derece döndürerek bariyeri kaldır
            servoAdim += 1;                          // Birer derece adımlarla servo motoru döndür
            servo.write(servoAdim);                  // Servo motorun açısını servoAdim değişkenine göre ayarla
            delay(25);                               // 25ms bekle
        }

        for (int j = 0; j < 100; j++) {              // 5 saniye bekleme döngüsü
            delay(50);                               // 50ms bekle
                                                     // Bekleme anında yeni bir araba gelip gelmediğini kontrol et
            if (analogRead(ldrPin) > 900) {          // ADC'den okunan değer 900'den büyük ise, yeni bir araba geldiyse
                tetikDurumu = 1;                     // Kapatıldığını kaydet
                j = 100;                             // Döngüden çıkmak için j değerini 100 yap
                delay(200);                          // 200ms bekle
                break;                               // For döngüsünden çık
            }
        }

        for (int i = 0; i < 90; i++) {               // Servo motoru 90 derece terse döndürerek bariyeri indir
            servoAdim -= 1;                         // Birer derece adımlarla servo motoru döndür
            servo.write(servoAdim);                 // Servo motorun açısını servoAdim değişkenine göre ayarla
            delay(25);                              // 25ms bekle

            if (analogRead(ldrPin) > 900) {
                aciDegeri = 180 - servoAdim;        // Açı değerini kaldığı yerden devam ettir
                i = 90;                             // Döngüden çıkmak için i değerini 90 yap
                delay(200);                         // 200ms bekle
                break;
            } else {
                tetikDurumu = 0;                    // Buton ile kontrol edilme değişkenini sıfırla
                aciDegeri = 90;                     // Açı değerini 90 olarak kaydet
            }

            if (servoAdim == 90) {
                bariyerDurumu = 0;                  // Bariyer durumunu kapalı olarak kayıt et  
            }
        }
    }
}
