// SA81 - Elektronik Mum

#include <FreqCount.h>                    // Frekans ölçmek için gerekli kütüphaneyi ekle

float frekans;                            // Frekans değerinin tutulacağı değişkenini tanımla
int ledDurumu = 0;                        // LED durumunun tutulacağı değişkeni tanımla
int ledPin = 7;                           // LED'in bağlandığı pin numarasını tanımla

void setup() {
    FreqCount.begin(100);                 // Frekans ölçümünü başlat ve 100 örnek değer al    
    pinMode(ledPin, OUTPUT);              // LED'in bağlandığı pini çıkış olarak ayarla 
}

void loop() {
    if (FreqCount.available()) {          // Eğer sistem çalışıyor ve değerler geliyorsa
        frekans = FreqCount.read() * 10;  // Frekans değişkenine ölçülen değeri ata
    }

    if (frekans > 500) {                  // Eğer frekans değeri 500'den büyük ise 
        ledDurumu++;                      // LedDurumu değişkenini 1 arttır 
        delay(200);
        if (ledDurumu > 1) {              // Eğer ledDurumu değişkeni 1'den büyük ise 
            ledDurumu = 0;                // LedDurumu değişkeninin değerini 0 yap 
        }
    }

    if (ledDurumu == 1) {                 // Eğer ledDurumu değişkeni 1 ise 
        digitalWrite(ledPin, HIGH);        // LED'i yak 
    } else {                              // Eğer ledDurumu değişkeni 0 ise 
        digitalWrite(ledPin, LOW);         // LED'i söndür
    }
    delay(200);                           // 200 ms gecikme
}
