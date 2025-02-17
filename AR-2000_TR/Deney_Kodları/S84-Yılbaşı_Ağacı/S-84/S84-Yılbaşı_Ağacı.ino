// S84 - Yılbaşı Ağacı

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int ledler[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// Rastgele üretilecek değişkenin kaydedileceği değişkeni tanımla
int rastgeleSayi = 0;

int hoparlorPin = 12;
int uzunluk = 26;
char notalar[] = "eeeeeeegcde fffffeeeeddedg";
int vuruslar[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

// Çalma temposu
int tempo = 200;

// notaCal fonksiyonunu tanımla
void notaCal(char nota, int sure) {
    char notaIsim[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
    int tonlar[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
    
    for (int i = 0; i < 8; i++) {
        if (notaIsim[i] == nota) {
            for (long j = 0; j < sure * 1000L; j += tonlar[i] * 2) {
                digitalWrite(hoparlorPin, HIGH);
                delayMicroseconds(tonlar[i]);
                digitalWrite(hoparlorPin, LOW);
                delayMicroseconds(tonlar[i]);
            }
        }
    }
}

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    // For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for (int i = 0; i < 10; i++) {
        pinMode(ledler[i], OUTPUT);
    }
    
    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);
}

void loop() {
    for (int i = 0; i < uzunluk; i++) {
        if (notalar[i] == ' ') {
            for (int i = 0; i < 10; i++) {
                digitalWrite(ledler[i], HIGH);
            }
            delay(vuruslar[i] * tempo / 4);
            
            for (int i = 0; i < 10; i++) {
                digitalWrite(ledler[i], LOW);
            }
            delay(vuruslar[i] * tempo / 4);
        } else {
            notaCal(notalar[i], vuruslar[i] * tempo);
        }
        
        for (int j = 0; j < 5; j++) {
            rastgeleSayi = random(0, 10);    // 0-9 arasında rastgele sayı belirle
            
            // LED'leri rastgele yak ve söndür
            digitalWrite(ledler[rastgeleSayi], HIGH);
            digitalWrite(ledler[(rastgeleSayi * 2) % 5], HIGH);
            digitalWrite(ledler[(rastgeleSayi * 5) % 6], HIGH);
            digitalWrite(ledler[(rastgeleSayi * 8) % 7], HIGH);
            delay(tempo / 20);               // tempo/20 kadar bekle
            
            digitalWrite(ledler[rastgeleSayi], LOW);
            digitalWrite(ledler[(rastgeleSayi * 2) % 5], LOW);
            digitalWrite(ledler[(rastgeleSayi * 5) % 6], LOW);
            digitalWrite(ledler[(rastgeleSayi * 8) % 7], LOW);
            delay(tempo / 20);               // tempo/20 kadar bekle
        }
    }
}