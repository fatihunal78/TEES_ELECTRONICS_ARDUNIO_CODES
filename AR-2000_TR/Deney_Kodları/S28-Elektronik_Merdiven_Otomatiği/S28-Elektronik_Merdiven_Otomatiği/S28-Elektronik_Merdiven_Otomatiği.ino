// S28 - Elektronik Merdiven Otomatiği

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int beyazPin = 7;
int sariPin = 6;
int kirmiziPin = 5;
int yesilPin = 4;

// Butonun bağlandığı dijital pin numarasını tanımla
int butonPin = 2;

// Buton durumunun tutulacağı değişkeni tanımla
int butonDurumu = 0;

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(beyazPin, OUTPUT);
    pinMode(sariPin, OUTPUT);
    pinMode(kirmiziPin, OUTPUT);
    pinMode(yesilPin, OUTPUT);
    
    // Butonun bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
}

void loop() {
    // Buton durumunu sorgula ve butonDurumu değişkenine ata
    butonDurumu = digitalRead(butonPin);
    
    // Buton durumuna göre LED'lerin durumunu ayarla
    if (butonDurumu == HIGH) {    // Butona basıldı ise
        // LED'leri yak
        digitalWrite(beyazPin, HIGH);
        digitalWrite(sariPin, HIGH);
        digitalWrite(kirmiziPin, HIGH);
        digitalWrite(yesilPin, HIGH);
        
        // LED'leri sırayla söndür
        // Bekleme zamanını ayarla: 5000=5sn, 10000=10sn'dir
        delay(5000);                      // 5 saniye bekle
        digitalWrite(yesilPin, LOW);      // Yeşil LED'i söndür
        delay(5000);                      // 5 saniye bekle
        digitalWrite(kirmiziPin, LOW);    // Kırmızı LED'i söndür
        delay(5000);                      // 5 saniye bekle
        digitalWrite(sariPin, LOW);       // Sarı LED'i söndür
        delay(5000);                      // 5 saniye bekle
        digitalWrite(beyazPin, LOW);      // Beyaz LED'i söndür
    }
}
