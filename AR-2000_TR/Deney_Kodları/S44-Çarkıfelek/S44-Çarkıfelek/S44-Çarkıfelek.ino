// S44 - Çarkıfelek

// Motoru süren transistörün bağlandığı pin numarasını tanımla
int motorPin = 3;
// Döndürme butonunun bağlandığı pin numarasını tanımla  
int dondurButonPin = 2;
// Bekleme zamanının tutulacağı değişkeni tanımla
int beklemeZamani = 0;
// Hız durumunun tutulacağı değişkeni tanımla
int hizDurumu = 0;

void setup() {
    // Motoru süren transistörün bağlandığı pini çıkış olarak ayarla
    pinMode(motorPin, OUTPUT);
    // Döndürme butonunun bağlandığı pini giriş olarak ayarla
    pinMode(dondurButonPin, INPUT);
}

void loop() {
    // Döndürme butonunun durumunu kontrol et
    if(digitalRead(dondurButonPin) == HIGH) {    // Butona basıldı ise
        // 2 saniye ile 4 saniye arasında bir değer belirle ve beklemeZamani değişkenine ata
        beklemeZamani = random(2000, 4000);
        
        // Motoru en yüksek hızda döndür
        analogWrite(motorPin, 255);
        delay(beklemeZamani/3);                  // Bekle
        
        // Motorun hızını düşür
        analogWrite(motorPin, 180);
        delay(2 * beklemeZamani / 3);            // Bekle
        
        // Motorun hızını düşür
        analogWrite(motorPin, 75);
        delay(1000);                             // Bekle
        
        // Motoru durdur
        analogWrite(motorPin, 0);
    }
}
