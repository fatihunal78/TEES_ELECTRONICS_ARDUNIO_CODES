// S96 - El çırpmalı şalter

#include <FreqCount.h>                                    // Frekans ölçmek için gerekli kütüphaneyi ekle           

float frekans;                                           // Frekans değerinin tutulacağı değişkenini tanımla
int ledPin = 8;                                          // LED'in bağlandığı pin numarasını tanımla
int leddurumu = 0;                                       // LED durumunun tutulacağı değişkeni tanımla
 
void setup() {                
    FreqCount.begin(100);                                // Frekans ölçümünü başlat ve 100 örnek değer al
    pinMode(ledPin, OUTPUT);                             // LED'in bağlandığı pini çıkış olarak ayarla
}
 
void loop() {
    if (FreqCount.available()) {                         // Eğer sistem çalışıyor ve frekans ölçümünde değerler geliyorsa
        frekans = FreqCount.read() * 10;                 // Frekans değişkenine ölçülen değeri 10 ile çarpıp kaydet
    }

    if (frekans > 100 && leddurumu == 0) {              // Eğer frekans değeri 100'den büyük ve
                                                        // leddurumu değişkeni 0  yani LED sönük ise
        digitalWrite(ledPin, HIGH);                      // LED'i yak
        delay(300);                                      // 300 ms bekle
        leddurumu = 1;                                   // leddurumu değişkenini 1 yap (LED'i yanıyor olarak kaydet)
    }
    else if (frekans > 100 && leddurumu == 1) {         // Eğer frekans değeri 100'den büyük ve 
                                                        // leddurumu değişkeni 1 ise yani LED yanıyor ise
        digitalWrite(ledPin, LOW);                       // LED'i söndür
        delay(300);                                      // 300 ms bekle
        leddurumu = 0;                                   // leddurumu değişkenini 0 yap (LED'i sönük olarak kaydet)
    }
}
