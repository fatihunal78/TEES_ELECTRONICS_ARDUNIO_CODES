// SA90 - El çırpması ile motor kontrolü

#include <FreqCount.h>                        //Frekans ölçmek için gerekli kütüphaneyi ekle

float frekans;                                //frekans değerinin tutulacağı değişkenini tanımladık
int motorPin = 10;                            //Motorun bağlandığı pin numaralasını tanımla
int motorDurumu = 0;                          //Motor durumunun tutulacağı değişkeni tanımla
int ledPin = 12;                              //LED'in bağlandığı pin numarasını tanımla

void setup() {
    FreqCount.begin(100);                     //Frekans ölçümünü başlat ve 100 örnek değer al
    pinMode(motorPin, OUTPUT);                //Motorun bağlandığı pini çıkış olarak ayarla
    pinMode(ledPin, OUTPUT);                  //LED'in bağlandığı pini çıkış olarak ayarla
}

void loop() {
    if (FreqCount.available()) {              //Eğer sistem çalışıyor ve değerler geliyorsa
        frekans = FreqCount.read() * 10;      //frekans değişkenine ölçülen değeri kaydet
    }

    if (frekans > 500) {                      //Eğer frekans değeri 500'den büyük ise
        motorDurumu++;                        //motorDurumu değişkenini 1 arttır
        delay(200);
        if (motorDurumu > 1)                  //Eğer motorDurumu değişkeni 1 den büyük ise
            motorDurumu = 0;                  //motordurumu değişkeninin değerini 0 yap
    }

    if (motorDurumu == 1) {                   //Eğer motorDurumu değişkeni 1 ise
        digitalWrite(motorPin, HIGH);          //Motora enerji ver
        digitalWrite(ledPin, HIGH);            //LED'i yak
    } else {                                  //Eğer motorDurumu değişkeni 0 ise
        digitalWrite(motorPin, LOW);           //Motoru durdur
        digitalWrite(ledPin, LOW);             //LED'i Söndür
    }
    
    delay(200);                               //200 ms gecikme
}
