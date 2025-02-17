// SA72 - Otomatik açılır kapanır kapı (Hareket sensörlü)

#include <Servo.h>                     //Servo motor kütüphanesi ekle
int butonPin = 2;                      //Butonun bağlandığı pin numarasını tanımla
int sensorPin = 3;                     //PIR sensörün bağlandığı pin numarasını tanımla
int yesilLed = 11;                     //Yeşil LED'in bağlandığı pin numarasını tanımla
Servo servo;                           //servo isimli bir servo motor objesi oluştur

void setup() {
    servo.attach(4);                   //Servo motorun bağlandığı pini ayarla
    pinMode(butonPin, INPUT_PULLUP);   //Butonun bağlandığı pini giriş olarak ayarla
    pinMode(yesilLed, OUTPUT);         //Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    servo.write(0);                    //Servomotorun başlangıç pozisyonu sıfır derece olarak ayarla
    pinMode(sensorPin, INPUT);         //Kızılötesi sensörün bağlandığı pini giriş olarak ayarla
}

void loop() {
    if (digitalRead(butonPin) == LOW) {    //Eğer butona basıldıysa
        digitalWrite(yesilLed, HIGH);       //Devrenin aktif olduğunu gösteren Yeşil LED'i yak
        
        while (1) {                        //Sistemi başlatmak için sonsuz döngüye git
            if (digitalRead(sensorPin) == HIGH) {    //Eğer sensör değeri HIGH ise
                                                     //Yani PIR sensörü hareketi algıladı ise
                for (int i = 0; i <= 90; i++) {      //Kapının açılması için i değerini 0'dan 90'a kadar bir bir arttır
                    servo.write(i);                  //i değerini servonun dönme açısı olarak yazdır ve servoyu i açısı 
                                                    //kadar döndür
                    delay(30);                       //30 ms gecikme
                }
                delay(5000);                        //Kapı açılınca 5 saniye bekle

                for (int z = 90; z > 0; z--) {      //Kapının kapanması için z değerini 90 dereceden 0'a doğru birer azalt
                    if (digitalRead(sensorPin) == HIGH) {    //Eğer kapı kapanırken tekrar hareket algılandı ise
                        //Kapının kapanmadan tekrar açılması için
                        for (int i = z; i <= 90; i++) {      //i değişkenini kapı kapanırken ki konumundan (en son z 
                                                            //değerinden) 90'a kadar birer arttır
                            servo.write(i);                  //Servonun açısı olarak kaydet ve servoyu döndür
                            z = i;                          //i değişkenindeki açı değerini z değişkenine kaydet
                            delay(30);                      //30 ms gecikme
                        }
                        delay(5000);                       //Kapıyı 5 saniye açık tutmak için bekle
                    }
                    else {                                //Eğer kapı kapanırken hareket algılanmadıysa
                        servo.write(z);                   //Servoyu z değişkeninin değeri kadar azaltarak servoyu döndür
                                                         //(Kapıyı kapat)
                        delay(30);                        //30 ms gecikme
                    }
                }
            }
        }
    }
}
