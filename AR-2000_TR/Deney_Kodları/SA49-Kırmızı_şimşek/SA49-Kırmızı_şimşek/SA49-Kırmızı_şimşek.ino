// SA49 - Kırmızı şimşek

// LED'lerin bağlandığı pin numaralarını tanımla
int ledler[] = {3, 4, 5, 6, 7};

// Buton'un bağlandığı dijital pin numarasını tanımla
int butonPin = 2;

// LED'lerin gezinme hızı
int hiz = 60;

void setup() {
    // For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for (int i = 0; i < 5; i++) {
        pinMode(ledler[i], OUTPUT);
    }
    
    // Buton'un bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
}

void loop() {
    // Buton durumunu kontrol et
    if (digitalRead(butonPin) == HIGH) {  // Butona basıldı ise
        // Tekrar sayısı
        for (int k = 0; k < 5; k++) {
            // LED'leri soldan sağa doğru sıra ile yak ve söndür
            // i değişkeni ile dizi olarak tanımlanan LED'ler sıra ile yakar ve söndürür
            for (int i = 0; i < 5; i++) {
                digitalWrite(ledler[i], HIGH);  // Sıradaki LED'i yak
                delay(hiz);                     // hiz değerine göre bekle
                digitalWrite(ledler[i], LOW);   // Sıradaki LED'i söndür
            }
            
            // LED'leri sağdan sola doğru sıra ile yak ve söndür
            // j değişkeni ile dizi olarak tanımlanan LED'ler sıra ile yakar ve söndürür
            for (int j = 4; j >= 0; j--) {     // Fixed array bounds error (changed from 5 to 4)
                digitalWrite(ledler[j], HIGH);  // Sıradaki LED'i yak
                delay(hiz);                     // hiz değerine göre bekle
                digitalWrite(ledler[j], LOW);   // Sıradaki LED'i söndür
            }
        }
    }
}
