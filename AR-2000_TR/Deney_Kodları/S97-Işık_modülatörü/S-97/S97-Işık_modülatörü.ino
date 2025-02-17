// S97 - Işık modülatörü

#include <FreqCount.h>    // Frekans ölçmek için gerekli kütüphaneyi ekle

float frekans;           // Frekans değerinin tutulacağı değişkenini tanımla
int RGB_kirmizi = 8;     // LED'lerin bağlandığı pin numaralarını tanımla
int RGB_yesil = 9;
int RGB_mavi = 10;

void setup() {   
    FreqCount.begin(100); // Frekans ölçümünü başlat ve 100 örnek değer al 
    pinMode(RGB_kirmizi, OUTPUT);  // LED'leri bağlandığı pinleri çıkış olarak ayarla
    pinMode(RGB_yesil, OUTPUT);
    pinMode(RGB_mavi, OUTPUT);
}

void loop() {
    if (FreqCount.available()) {    // Eğer sistem çalışıyor ve frekans ölçümünde değerler geliyorsa
        frekans = FreqCount.read() * 10;  // Frekans değişkenine ölçülen değeri 10 ile çarpıp kaydet
    }

    if (frekans >= 16 && frekans < 60) {  // Eğer frekans değeri 16 ile 60 Hertz arasında ise
        digitalWrite(RGB_kirmizi, LOW);    // Kırmızı LED'i yak
        digitalWrite(RGB_yesil, HIGH);
        digitalWrite(RGB_mavi, HIGH);
    }
    else if (frekans >= 60 && frekans < 150) {  // Eğer frekans değeri 60 ile 150 Hertz arasında ise
        digitalWrite(RGB_kirmizi, HIGH);         // Yeşil LED'i yak
        digitalWrite(RGB_yesil, LOW);
        digitalWrite(RGB_mavi, HIGH);
    }
    else if (frekans >= 150 && frekans < 350) {  // Eğer frekans değeri 150 ile 350 Hertz arasında ise
        digitalWrite(RGB_kirmizi, HIGH);          // Mavi LED'i yak
        digitalWrite(RGB_yesil, HIGH);
        digitalWrite(RGB_mavi, LOW);
    }
    else if (frekans >= 350 && frekans < 500) {  // Eğer frekans değeri 350 ile 500 Hertz arasında ise
        digitalWrite(RGB_kirmizi, LOW);           // Kırmızı ve Yeşil LED'i yak
        digitalWrite(RGB_yesil, LOW);
        digitalWrite(RGB_mavi, HIGH);
    }
    else if (frekans >= 500 && frekans < 750) {  // Eğer frekans değeri 500 ile 750 Hertz arasında ise
        digitalWrite(RGB_kirmizi, LOW);           // Kırmızı ve Mavi LED'i yak
        digitalWrite(RGB_yesil, HIGH);
        digitalWrite(RGB_mavi, LOW);
    }
    else if (frekans >= 750 && frekans < 1000) {  // Eğer frekans değeri 750 ile 1000 Hertz arasında ise
        digitalWrite(RGB_kirmizi, HIGH);           // Yeşil ve Mavi LED'i yak
        digitalWrite(RGB_yesil, LOW);
        digitalWrite(RGB_mavi, LOW);
    }
    else if (frekans >= 1000) {  // Eğer frekans değeri 1000'den büyük ise
        digitalWrite(RGB_kirmizi, LOW);  // LED'lerin hepsini yak
        digitalWrite(RGB_yesil, LOW);
        digitalWrite(RGB_mavi, LOW);
    }
    else {  // Yukarıdaki koşulların hiçbiri sağlanmazsa LED'leri söndür 
        digitalWrite(RGB_kirmizi, HIGH);
        digitalWrite(RGB_yesil, HIGH);
        digitalWrite(RGB_mavi, HIGH);
    }
}
