// SA14 - Uzaktan kumanda ile LED Kontrolü

#include <IRremote.h>                     // IR alıcı kütüphanesini ekle

// Kumanda kodlarını tanımla
#define ledAcKapat  0xFF38C7              // Kumanda OK Tuşu
#define ledAzalt    0xFF4AB5              // Kumanda aşağı tuşu
#define ledArttir   0xFF18E7              // Kumanda yukarı tuşu
#define tekrar      0xFFFFFFFF            // Basılan tuşa sürekli basılırsa

int ledPin = 5;                           // LED'in bağlandığı dijital pin numarasını tanımla
int irPin = 2;                            // IR alıcı sinyal bacağının bağlandığı pini tanımla

IRrecv iralici(irPin);                    // iralici adında bir IR alıcı tanımla
decode_results sonuc;                      // IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

int parlaklik = 0;                        // LED'in parlaklık değerini tutulacağı değişkeni tanımla
int ledDurumu = 0;                        // LED durumunun tutulacağı değişkeni tanımla
int sonTus = 0;                           // Son basılan tuşun tutulacağı değişkeni tanımla

void setup() {
    iralici.enableIRIn();                 // IR alıcıyı başlat
    pinMode(ledPin, OUTPUT);              // LED'in bağlandığı pini çıkış olarak ayarla
}

void loop() {
    if (iralici.decode(&sonuc)) {         // IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        if (sonuc.value == tekrar) {      // Aynı tuşa tekrar basıldı ise
            if (sonTus == 2) {            // Son basılan tuş ledArttir ise
                sonuc.value = ledArttir;
            }
            else if (sonTus == 3) {       // Son basılan tuş ledAzalt ise
                sonuc.value = ledAzalt;
            }
        }

        if (sonuc.value == ledAcKapat) {  // Basılan tuş ledAcKapat ise
            sonTus = 1;                    // sonTus değişkenini 1 olarak ayarla
            if (ledDurumu == 0) {         // LED kapalı ise
                analogWrite(ledPin, 255);  // LED'i maksimum olarak yak
                parlaklik = 255;          // parlaklik değerini 255'e ayarla
                ledDurumu = 1;            // LED durumunu açık olarak kaydet
            }
            else {
                analogWrite(ledPin, 0);    // LED'i söndür
                parlaklik = 0;            // parlaklik değerini 0'a ayarla
                ledDurumu = 0;            // LED durumunu kapalı olarak kaydet
            }
        }
        else if (sonuc.value == ledArttir) {  // Basılan tuş ledArttir ise
            sonTus = 2;                        // sonTus değişkenini 2 olarak ayarla
            ledDurumu = 1;                     // LED durumunu açık olarak kaydet
            parlaklik += 50;                   // parlaklik değerini 50 arttır
            if (parlaklik > 255) {             // parlaklik değerini 255'den büyük ise
                parlaklik = 255;               // parlaklik değerini 255'e ayarla
            }
            analogWrite(ledPin, parlaklik);    // parlaklik değerine göre LED'i yak
        }
        else if (sonuc.value == ledAzalt) {   // Basılan tuş ledAzalt ise
            sonTus = 3;                        // sonTus değişkenini 3 olarak ayarla
            parlaklik -= 50;                   // parlaklik değerini 50 azalt
            if (parlaklik < 0) {               // parlaklik değeri 0'dan düşük ise
                parlaklik = 0;                 // parlaklik değerini 0'a ayarla
                ledDurumu = 0;                 // LED durumunu kapalı olarak kaydet
            }
            analogWrite(ledPin, parlaklik);    // parlaklik değerine göre LED'i yak
        }
        else {                                 // Tanımlanmamış bir tuşa basıldı ise
            sonTus = 0;                        // sonTus değişkenini 0 olarak ayarla
        }

        delay(200);                            // 200ms bekle
        iralici.resume();                      // IR alıcıyı diğer değerleri alabilmesi için sıfırla
    }
}
