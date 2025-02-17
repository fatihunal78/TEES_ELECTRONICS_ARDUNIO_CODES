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
    if(digitalRead(butonpin) == HIGH) {      // Eğer butona basıldı ise
        delay(200);                          // 200 ms bekle 
        butondurumu++;                       // butondurumu değişkenini bir arttır
    }
    
    if(butondurumu > 2) {                    // Eğer butondurumu değişkeni 2'den büyük ise 
        butondurumu = 1;                     // butondurumu değişkenini 1'e eşitle
    }
   
    if(butondurumu == 1) {                   // Eğer butondurumu değişkeninin değeri 1 ise 
                                            // Kayıt işlemi için for döngüsü kullan ve i değişkenini sıfırdan 1000'e 
                                            // (eeprom_kayit değeri) kadar arttır
        for(int i = 0; i <= eeprom_kayit; i++) { 
            digitalWrite(sariLed, HIGH);      // Kayıtın başlandığını göstermek için sarı LED'i yak
            digitalWrite(yesilLed, LOW);      // Yeşil LED'i söndür
      
            if(digitalRead(butonpin) == HIGH) {  // Eğer kayıt işlemi sırasında butona basıldı ise  
                butondurumu = 2;              // butondurumu değişkenini 2 yap, kayıtı sonlandır ve tekrar(playback) işlemine geç
                kayit_suresi = i;             // Butona basıldığında i değişkeni hangi değerde ise onu kayit_suresi değişkenine aktar
                break;                        // for döngüsünü bitir, kayıdı sonlandır
            }

                                            // Potansiyometreden okunan değeri servo açı değerlerine oranla. Potansiyometreden 1023 
                                            // değeri geldi ise bu değer oranlama sonrası 0 olacaktır. Eğer potansiyometreden okunan 
                                            // değer 512 ise bu değer oranlama sonrası 90 olacaktır
            int val = map(analogRead(A0), 0, 1023, 180, 0);
                                                     
            EEPROM.write(i, val);             // Okunan değerleri sıra ile (i değişkeninin artışına göre) eeproma kaydet     
            myServo.write(val);               // Servoyu hareket ettir
            kayit_suresi = i;                 // i değişkeni hangi değerde ise onu kayit_suresi değişkenine aktar 
            delay(10);                        // 10ms bekle
        }
        butondurumu = 2;                      // butondurumu değişkenini 2 yap, tekrar(playback) moduna geç
    }
    else {                                    // Eğer butondurumu değişkenini değeri 1'den farklı bir değer ise 
        digitalWrite(sariLed, LOW);           // Sarı LED'i söndür 
        digitalWrite(yesilLed, HIGH);         // Tekrar modunda olduğunu göstermek için Yeşil LED'i yak
   
                                            // Tekrar işlemi için for döngüsü kullan ve i değişkenini sıfırdan kayit süresine
                                            // (kayit_suresi) kadar birer arttır
        for(int i = 0; i <= kayit_suresi; i++) {
            if(digitalRead(butonpin) == HIGH) {  // Butona tekrar basıldı ise 
                butondurumu = 1;              // Kayıt moduna geçmek için butondurumu değişkenini 1 yap
                delay(200);         
                break;                        // for döngüsünü bitir ve tekrarı durdur
            }
            int okunandeger = EEPROM.read(i); // Eepromdaki kayıtlı değeri "okunandeger" değişkenine kaydet 
            myServo.write(okunandeger);       // okunandeger değişkeninde kaydedilmiş değeri servoya yaz     
            delay(10);                        // 10 ms bekle
        }

        digitalWrite(yesilLed, HIGH);         // Tekrarı göstermek için Yeşil LED'i yak
        delay(100);                          // 100 ms bekle 
        digitalWrite(yesilLed, LOW);          // Yeşil LED'i söndür
        delay(100);                          // 100 ms bekle 
    }
}
