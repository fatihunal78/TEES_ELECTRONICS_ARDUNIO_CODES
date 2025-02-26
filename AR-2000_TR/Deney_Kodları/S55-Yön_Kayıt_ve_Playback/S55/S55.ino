// S55 - Yön Kayıt ve Playback

#include <Servo.h>
#include <EEPROM.h>                          // Yönleri kaydetmek için EEPROM kütüphanesi

Servo myServo;
float eeprom_kayit = 1000;                   // EEPROM uzunluğu olan 1024'den küçük olmalı
int butonpin = 3;                            // Butonun bağlandığı pini tanımla  
int sariLed = 5;                             // LED'lerin bağlandığı pinleri tanımla
int yesilLed = 6;
int kayit_suresi;                            // Kayıt işleminde ne kadar kayıtta kalındığının tutulacağı değişkeni tanımla
int butondurumu = 0;                         // Butona basılma durumunun tutulacağı değişkeni tanımla

void setup() {
    pinMode(sariLed, OUTPUT);                // Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesilLed, OUTPUT);               // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(butonpin, INPUT);                // Butonun bağlandığı pini giriş olarak ayarla
    myServo.attach(2);                       // Servo motorun bağlandığı pini ayarla
}

void loop() {
    if (digitalRead(butonpin) == HIGH) {                // Butona basılı ise
        delay(200);                                     // 200ms bekle
        butondurumu++;                                  // butondurumu değişkenini bir arttır
    }
    
    if (butondurumu > 2) {                             // butondurumu değişkeni 2'den büyük ise
        butondurumu = 0;                               // butondurumu değişkenini 0 yap
    }
   
    if (butondurumu == 0) {                            // Butondurumu değişkeninin değeri 0 ise
        digitalWrite(sariLed, HIGH);                    // Kayıt başladığını göstermek için Sarı LED'i yak
        digitalWrite(yesilLed, LOW);                    // Yeşil LED'i söndür
        
        for(int i = 0; i <= eeprom_kayit; i++) {       // Kayıt işlemini gerçekleştirmek için for döngüsü kullan ve i değişkenini
                                                       // sıfırdan 1000'e (eeprom_kayit değeri) kadar birer birer arttır
            if(digitalRead(butonpin) == HIGH) {         // Kayıt işlemi sırasında butona basıldı ise
                butondurumu = 1;                        // butondurumu değişkenini 1 yap, kaydı bitir ve tekrar oynatmaya (playback) geç
                kayit_suresi = i;                       // Butona basıldığında i değişkeninin değerini kayit_suresi değişkenine aktar
                delay(200);
                break;                                  // for döngüsünü bitir, kaydı sonlandır
            }
            
            int val = map(analogRead(A0), 0, 1023, 180, 0);  // Potansiyometreden okunan değeri servo motor açı değerlerine oranla
            EEPROM.write(i, val);                      // Okunan değerleri sırayla (i değişkeninin artışına göre) eeproma kaydet
            myServo.write(val);                        // Servo motoru hareket ettir
            kayit_suresi = i;                          // i değişkeninin değerini kayit_suresi değişkenine aktar
            delay(10);                                 // 10ms bekle
        }
        butondurumu = 1;                              // butondurumu değişkenini 1 yap ve tekrar (playback) moduna geç
    }
    else {                                            // Butondurumu değişkeninin değeri 1 değil ise
        digitalWrite(sariLed, LOW);                   // Sarı LED'i söndür 
        digitalWrite(yesilLed, HIGH);                 // Tekrar modunda olduğunu göstermek için Yeşil LED'i yak
   
        for(int i = 0; i <= kayit_suresi; i++) {     // İşlemi tekrarlamak için for döngüsü kullan ve i değişkenini
                                                     // sıfırdan kayıt süresine (kayit_suresi) kadar birer birer arttır
            if(digitalRead(butonpin) == HIGH) {      // Butona tekrar basıldı ise 
                butondurumu = 0;                     // Kayıt moduna geçmek için butondurumu değişkenini 0 yap
                delay(200);         
                break;                               // for döngüsünü bitir ve tekrarı durdur
            }
            int okunandeger = EEPROM.read(i);       // Eepromdaki kayıtlı değeri "okunandeger" değişkenine kaydet 
            myServo.write(okunandeger);             // okunandeger değişkeninde kaydedilmiş değeri servoya yaz     
            delay(10);                              // 10 ms bekle
        }

        digitalWrite(yesilLed, HIGH);               // Tekrarı göstermek için Yeşil LED'i yak
        delay(100);                                // 100 ms bekle 
        digitalWrite(yesilLed, LOW);               // Yeşil LED'i söndür
        delay(100);                               // 100 ms bekle 
    }
}
