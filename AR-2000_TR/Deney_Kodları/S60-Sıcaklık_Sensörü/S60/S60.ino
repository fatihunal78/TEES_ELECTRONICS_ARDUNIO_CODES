// S60 - Sıcaklık Sensörü

#include <math.h>                    // math.h kütüphanesini ekle

int ntcPin = A0;                     // NTC'nin bağlandığı analog pin numarasını tanımla
int analogDeger;                     // NTC değerinin tutulacağı değişkeni tanımla
double sicaklik;                     // Sıcaklık değerinin tutulacağı değişkeni tanımla

void setup() {
    Serial.begin(9600);              // Seri portu 9600 baud rate ile başlat
}

double ntcHesapla(int analogOkuma) { // ntcHesapla fonksiyonunu tanımla
    // NTC özelliklerine göre sıcaklık değerini hesapla
    sicaklik = log(((10240000 / analogOkuma) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;
    return sicaklik;                 // Hesaplanan sıcaklık değerini geri gönder
}

void loop() {
    analogDeger = analogRead(ntcPin);        // NTC değerini oku ve analogDeger değişkenine kaydet
    sicaklik = ntcHesapla(analogDeger);      // ntcHesapla fonksiyonu ile sıcaklık değerini hesapla ve sicaklik 
                                            // değişkenine kaydet
    Serial.print("Sıcaklık : ");            // Seri porta sicaklik değişkenini yazdır
    Serial.print(sicaklik);
    Serial.println(" C");
    delay(500);                             // 500ms bekle
}