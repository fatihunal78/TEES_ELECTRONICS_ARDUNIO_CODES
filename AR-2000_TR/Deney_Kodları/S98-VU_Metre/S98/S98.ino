// S98 - VU Metre

#include <FreqCount.h>                    // Frekans ölçmek için gerekli kütüphaneyi ekle      

float frekans;                            // Frekans değerinin tutulacağı değişkenini tanımla

// LED'lerin bağlandığı pin numaralarını tanımla
int ledPin  = 8;
int ledPin2 = 9;
int ledPin3 = 10;
int ledPin4 = 11;
int ledPin5 = 12;

void setup() {     
    FreqCount.begin(100);                 // Frekans ölçümünü başlat ve 100 örnek değer al  
    
    // LED'leri çıkış olarak ayarla
    pinMode(ledPin,  OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    pinMode(ledPin5, OUTPUT);
}

void loop() {
    if (FreqCount.available()) {          // Eğer sistem çalışıyor ve frekans ölçümünde değerler geliyorsa
        frekans = FreqCount.read() * 10;  // Frekans değişkenine ölçülen değeri 10 ile çarpıp kaydet
    }

    if (frekans >= 16 && frekans < 60) {  // Eğer frekans değeri 16 ile 60 Hertz arasında ise
                                          // Yeşil LED'i yak
        digitalWrite(ledPin,  HIGH);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        digitalWrite(ledPin5, LOW);
    }
    else if (frekans >= 60 && frekans < 250) {  // Eğer frekans değeri 60 ile 250 Hertz arasında ise
                                                // İki yeşil LED'i yak
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin,  HIGH);    
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        digitalWrite(ledPin5, LOW);
    }
    else if (frekans >= 250 && frekans < 500) { // Eğer frekans değeri 250 ile 500 Hertz arasında ise
                                                // Yeşil LED'leri ve Sarı LED'i yak
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin,  HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin4, LOW);
        digitalWrite(ledPin5, LOW);
    }
    else if (frekans >= 500 && frekans < 1000) { // Eğer frekans değeri 500 ile 1000 Hertz arasında ise
                                                 // Yeşil LED'leri, Sarı LED'i ve Kırmızı LED'i yak
        digitalWrite(ledPin4, HIGH);
        digitalWrite(ledPin,  HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin5, LOW);
    }
    else if (frekans >= 1000) {                  // Eğer frekans değeri 1000 den büyük ise
                                                 // Bütün LED'leri yak
        digitalWrite(ledPin4, HIGH);
        digitalWrite(ledPin,  HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin5, HIGH);
    }
    else {                                       // Yukarıdaki koşulların hiçbiri sağlamazsa LED'leri söndür 
        digitalWrite(ledPin,  LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        digitalWrite(ledPin5, LOW);
    }
}
