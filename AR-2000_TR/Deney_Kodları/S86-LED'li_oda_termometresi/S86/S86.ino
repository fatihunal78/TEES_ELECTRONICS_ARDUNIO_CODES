// S86 - LED'li oda termometresi

#include <math.h>                                    // math.h kütüphanesini ekle

int ntcPin = A5;                                    // NTC'nin bağlandığı analog pin numarasını tanımla
int analogDeger;                                    // NTC değerinin tutulacağı değişkeni tanımla
double sicaklik;                                    // Sıcaklık değerinin tutulacağı değişkeni tanımla

int YesilLed1 = 2;                                  // LEDBAR'daki 1.Yeşil LED'in bağlandığı pini tanımla
int YesilLed2 = 3;                                  // LEDBAR'daki 2.Yeşil LED'in bağlandığı pini tanımla
int SariLed = 4;                                    // LEDBAR'daki Sarı LED'in bağlandığı pini tanımla
int KirmiziLed1 = 5;                               // LEDBAR'daki 1.Kırmızı LED'in bağlandığı pini tanımla
int KirmiziLed2 = 6;                               // LEDBAR'daki 2.Kırmızı LED'in bağlandığı pini tanımla

void setup() {
    pinMode(YesilLed1, OUTPUT);                     // LEDBAR'daki 1. Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(YesilLed2, OUTPUT);                     // LEDBAR'daki 2. Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(SariLed, OUTPUT);                       // LEDBAR'daki Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(KirmiziLed1, OUTPUT);                   // LEDBAR'daki 1. Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(KirmiziLed2, OUTPUT);                   // LEDBAR'daki 2. Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
}

double ntcHesapla(int analogOkuma) {                // ntcHesapla fonksiyonunu tanımla
    // NTC özelliklerine göre sıcaklık değerini hesapla
    sicaklik = log(((10240000 / analogOkuma) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;
    return sicaklik;                                // Hesaplanan sıcaklık değerini geri gönder
}

void loop() {
    analogDeger = analogRead(ntcPin);               // NTC değerini oku ve analogDeger değişkenine kaydet
    sicaklik = ntcHesapla(analogDeger);            // ntcHesapla fonksiyonu ile sıcaklık değerini hesapla ve sicaklik 
                                                   // değişkenine kaydet

    if (sicaklik >= 16 && sicaklik <= 18) {        // Eğer sıcaklık değeri 16 derece ile 18 derece arasında ise
        digitalWrite(YesilLed1, HIGH);              // 1.Yeşil LED'i yak
        digitalWrite(YesilLed2, LOW);               // 2.Yeşil LED'i söndür
        digitalWrite(SariLed, LOW);                 // Sarı LED'i söndür
        digitalWrite(KirmiziLed1, LOW);             // 1. Kırmızı LED'i söndür
        digitalWrite(KirmiziLed2, LOW);             // 2. Kırmızı LED'i söndür
    }
    else if (sicaklik > 18 && sicaklik <= 20) {    // Eğer sıcaklık 18 ile 20 derece arasında ise
        digitalWrite(YesilLed1, LOW);               // 1.Yeşil LED'i söndür
        digitalWrite(YesilLed2, HIGH);              // 2.Yeşil LED'i yak
        digitalWrite(SariLed, LOW);                 // Sarı LED'i söndür
        digitalWrite(KirmiziLed1, LOW);             // 1. Kırmızı LED'i söndür
        digitalWrite(KirmiziLed2, LOW);             // 2. Kırmızı LED'i söndür
    }
    else if (sicaklik > 20 && sicaklik <= 22) {    // Eğer sıcaklık 20 ile 22 derece arasında ise
        digitalWrite(YesilLed1, LOW);               // 1.Yeşil LED'i söndür
        digitalWrite(YesilLed2, LOW);               // 2.Yeşil LED'i söndür
        digitalWrite(SariLed, HIGH);                // Sarı LED'i yak
        digitalWrite(KirmiziLed1, LOW);             // 1. Kırmızı LED'i söndür
        digitalWrite(KirmiziLed2, LOW);             // 2. Kırmızı LED'i söndür
    }
    else if (sicaklik >= 22 && sicaklik < 24) {    // Eğer sıcaklık 22 ile 24 derece arasında ise
        digitalWrite(YesilLed1, LOW);               // 1.Yeşil LED'i söndür
        digitalWrite(YesilLed2, LOW);               // 2.Yeşil LED'i söndür
        digitalWrite(SariLed, LOW);                 // Sarı LED'i söndür
        digitalWrite(KirmiziLed1, HIGH);            // 1. Kırmızı LED'i yak
        digitalWrite(KirmiziLed2, LOW);             // 2. Kırmızı LED'i söndür
    }
    else if (sicaklik >= 24) {                     // Eğer sıcaklık 24'den büyük ise
        digitalWrite(YesilLed1, LOW);               // 1.Yeşil LED'i söndür
        digitalWrite(YesilLed2, LOW);               // 2.Yeşil LED'i söndür
        digitalWrite(SariLed, LOW);                 // Sarı LED'i söndür
        digitalWrite(KirmiziLed1, LOW);             // 1. Kırmızı LED'i söndür
        digitalWrite(KirmiziLed2, HIGH);            // 2. Kırmızı LED'i yak
    }
    
    delay(500);                                     // 500ms bekle
}
