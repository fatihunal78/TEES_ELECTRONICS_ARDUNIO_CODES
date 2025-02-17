// S89 - Kombi termostatı

// Logaritmik hesaplamaların yapılması için math.h kütüphanesini ekle
#include <math.h>

int ntcPin = A0;          // NTC'nin bağlandığı analog pin numarasını tanımla
int analogDeger;          // NTC değerinin tutulacağı değişkeni tanımla
double sicaklik;          // Sıcaklık değerinin tutulacağı değişkeni tanımla

int Yesil_ledPin = 2;     // Yeşil LED'in bağlandığı pin numarası tanımlandı 
int Kirmizi_ledPin = 7;   // Kırmızı LED'in bağlandığı pin numarası tanımlandı 
int buzzerPin = 5;        // Buzzerin bağlandığı pin numarası tanımlandı 

void setup()
{
    pinMode(Yesil_ledPin, OUTPUT);    // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(Kirmizi_ledPin, OUTPUT);  // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(buzzerPin, OUTPUT);       // Buzzerın bağlandığı pini çıkış olarak ayarla
}

void loop()
{
    // NTC değerini oku ve analogDeger değişkenine kaydet
    analogDeger = analogRead(ntcPin);

    // NTC özelliklerine göre sıcaklık değerini hesapla
    sicaklik = log(((10240000 / analogDeger) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;

    if (sicaklik >= 45)  // Eğer sıcaklık 45 derecenin üzerinde ise 
    {
        digitalWrite(Yesil_ledPin, LOW);     // Yeşil LED'i söndür 
        digitalWrite(Kirmizi_ledPin, HIGH);  // Kırmızı LED'i yak 
        digitalWrite(buzzerPin, HIGH);       // Buzzerdan ses çıkar 
        delay(100);                          // 100 ms bekle 
        digitalWrite(Kirmizi_ledPin, LOW);   // Kırmızı LED'i söndür 
        digitalWrite(buzzerPin, LOW);        // Buzzeri sustur 
        delay(100);                          // 100 ms bekle 
    }
    else  // Eğer sıcaklık 45 derecenin altında ise 
    {
        digitalWrite(Yesil_ledPin, HIGH);    // Yeşil LED'i yak 
        digitalWrite(Kirmizi_ledPin, LOW);   // Kırmızı LED'i söndür
        digitalWrite(buzzerPin, LOW);        // Buzzerı sustur 
    }
}