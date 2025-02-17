// S67 - Yangın Alarmı

// NTC'den alınan verilerin hesaplanabilmesi için math kütüphanesini ekledik
#include <math.h>

// Buton'un bağlandığı dijital pin numarasını tanımla
int butonPin    = 2;
// LED'lerin bağlandığı pin numaralarını tanımla
int kirmiziLED  = 8;
int yesilLED    = 9;
// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 3;
// NTC'nin bağlandığı pin numarasını tanımla
int ntcPin      = A5;
// Yangın durumunun tutulacağı değişkeni tanımla
int yanginDurumu = 0;
// Alarm durumunun tutulacağı değişkeni tanımla
int alarmDurumu  = 0;
// Sıcaklık değerinin tutulacağı değişkeni tanımla
double sicaklik;

void setup() {     
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla 
    pinMode(kirmiziLED, OUTPUT);              
    pinMode(yesilLED, OUTPUT); 
    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);  
    // Buton'un bağlandığı pini giriş olarak ayarla   
    pinMode(butonPin, INPUT);
}

void loop() {
    // NTC'den okunan sıcaklık değerinin santigrad cinsine dönüştürebilmek için
    // gerekli matematiksel işlemler yap ve bu değer sicaklik değişkenine kayıt et
    sicaklik = log(((10240000 / analogRead(ntcPin)) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;

    // Butona basılıp basılmadığını kontrol et
    if (digitalRead(butonPin) == HIGH) {      // Butona basıldı ise
        if (alarmDurumu == 0) {               // Alarm kapalı ise
            alarmDurumu = 1;                  // Alarmı açık olarak kaydet
            digitalWrite(yesilLED, HIGH);      // Yeşil LED'i yak
        } else {
            alarmDurumu = 0;                  // Alarmı kapalı olarak kaydet
            digitalWrite(yesilLED, LOW);       // Yeşil LED'i söndür
            digitalWrite(kirmiziLED, LOW);     // Kırmızı LED'i söndür
        }
        delay(500);                           // 500ms bekle
    }

    if (alarmDurumu == 1) {                   // Alarm açık ise
        if (sicaklik > 45) {                  // NTC değeri 45 Santigrad dereceden yüksek ise
            tone(hoparlorPin, 250);           // Hoparlörden alarm sesi çal
            digitalWrite(kirmiziLED, HIGH);    // Kırmızı LED'i yak
            delay(250);                       // 250ms bekle
            noTone(hoparlorPin);              // Hoparlörü sustur
            digitalWrite(kirmiziLED, LOW);     // Kırmızı LED'i söndür
            delay(250);                       // 250ms bekle
        }
    }
    delay(50);                                // 50ms bekle
}
