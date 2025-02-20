// SA75 - Otomatik Geçiş Sistemi

#include <Servo.h>                                    //Servo motor kütüphanesi eklendi

Servo servo;                                          //servo isimli bir servo motor objesi oluştur

#define trigPin 2                                     //HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define echoPin 3                                     //HC-SR04 Echo bacağının bağlandığı pini tanımla
long sure, mesafe;                                    //Süre ve mesafe değişkenlerini tanımla

void setup() {
    servo.attach(4);                                  //Servo motorun bağlandığı pini ayarla
    servo.write(0);                                   //Servonun baslangıç pozisyonunu sıfır derece olarak ayarla
    
    pinMode(trigPin, OUTPUT);                         //Trigger bacağının bağlandığı pini çıkış olarak ayarla 
    pinMode(echoPin, INPUT);                          //Echo bacağının bağlandığı pini giriş olarak ayarla
}

void loop() {
    mesafe_olc();
    
    if (mesafe <= 5) {                               //Eğer mesafe değeri 5 cm'den kısa ise (Araba geçiyor ise) 
        for (int i = 0; i <= 90; i++) {              //Kapının açılması için i değerini 0'dan 90'a kadar bir bir arttır 
            servo.write(i);                          //i değerini servonun dönme açısı olarak yazdır ve servoyu i açısı kadar döndür 
            delay(15);                               //15 ms gecikme
        }
        delay(5000);                                 //Kapı açılınca 5 saniye bekle 
        
        for (int z = 90; z > 0; z--) {              //Kapının kapanması için z değerini 90 dereceden 0'a doğru birer azalt 
            mesafe_olc();
            if (mesafe <= 5) {                       //Eğer kapı kapanırken tekrar araba geliyor ise 
                                                     //Kapının kapanmadan tekrar açılması için     
                for (int i = z; i <= 90; i++) {      //i değişkenini kapı kapanırken ki konumundan (en son z değerinden) 90'a 
                                                     //kadar birer arttır
                    servo.write(i);                  //Servo motorun açısı olarak kaydet ve servoyu döndür 
                    z = i;                           //i değişkenindeki açı değerini z değişkenine kaydet  
                    delay(15);                       //15 ms gecikme
                }
                delay(5000);                         //Kapıyı 5 saniye açık tutmak için gecikme
            } else {                                 //Eğer kapı kapanırken yeni araba gelmezse
                servo.write(z);                      //Servoyu z değişkeninin değeri kadar azaltarak servoyu döndür (Kapıyı kapat)  
            }
            delay(15);                               //15 ms gecikme 
        } 
    }
}

void mesafe_olc() {                                  //Mesafenin ölçülmesi için mesafe_olc fonksiyonunu oluştur
    digitalWrite(trigPin, LOW);                      //Trigger bacağını sıfıra çek
    delayMicroseconds(2);                           //2 mikro saniye bekle  
    digitalWrite(trigPin, HIGH);                     //Trigger bacağını 5V'a çek
    delayMicroseconds(10);                          //10 mikro saniye bekle  
    digitalWrite(trigPin, LOW);                      //Trigger bacağını sıfıra çek
    sure = pulseIn(echoPin, HIGH);                  //Echo pininden geri gelme süresini ölç 
    mesafe = (sure/2) * 0.034;                      //Ölçülen süreyi ses hızı ile çarparak mesafeyi cm olarak hesapla
}
