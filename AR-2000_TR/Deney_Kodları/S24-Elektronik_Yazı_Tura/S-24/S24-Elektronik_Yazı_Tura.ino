// S24 - Elektronik Yazı Tura

// LED'lerin bağlandığı dijital pin numarasını tanımla
int yesilPin = 3;
int kirmiziPin = 4;

// Buton'un bağlandığı dijital pin numarasını tanımla
int butonPin = 2;

// Buton durumunun tutulacağı değişkeni tanımla
int butonDurumu = 0;

// Rastgele sayının tutulacağı değişkeni tanımla
int rastgeleSayi = 0;

void setup() {
    // LED'lerin bağlandığı pini çıkış olarak ayarla
    pinMode(yesilPin, OUTPUT);
    pinMode(kirmiziPin, OUTPUT);
    
    // Buton'un bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
}

void loop() {
    // Buton durumunu sorgula ve butonDurumu değişkenine ata
    butonDurumu = digitalRead(butonPin);

    // Buton durumuna göre LED'in durumunu ayarla
    if (butonDurumu == HIGH) {    // Butona basıldı ise
        // 3sn bekleme için animasyon yap
        for (int i = 0; i < 15; i++) {    // 15 kere tekrarla
            digitalWrite(yesilPin, HIGH);    // Yeşil LED'i yak
            delay(100);                      // 100ms bekle
            digitalWrite(yesilPin, LOW);     // Yeşil LED'i söndür
            digitalWrite(kirmiziPin, HIGH);  // Kırmızı LED'i yak
            delay(100);                      // 100ms bekle
            digitalWrite(kirmiziPin, LOW);   // Kırmızı LED'i söndür
        }

        randomSeed(analogRead(A0));    // Random fonksiyonu için timer değişkenini rastgele değere ata
        
        // 0-1 arasında rastgele sayı belirle
        rastgeleSayi = random(0, 2);
        
        if (rastgeleSayi == 1) {           // Rastgele sayı 1 ise, yazı
            digitalWrite(kirmiziPin, LOW);  // Kırmızı LED'i söndür
            digitalWrite(yesilPin, HIGH);   // Yeşil LED'i yak
        }
        else {                             // Rastgele sayı 0 ise, tura
            digitalWrite(yesilPin, LOW);    // Yeşil LED'i söndür
            digitalWrite(kirmiziPin, HIGH); // Kırmızı LED'i yak
        }
    }
}
