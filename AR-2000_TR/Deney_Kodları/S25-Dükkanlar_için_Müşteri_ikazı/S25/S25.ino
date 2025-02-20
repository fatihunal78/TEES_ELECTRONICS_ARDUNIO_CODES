// S25 - Dükkanlar için Müşteri ikazı

int kapiPin = 2;    // Kapı kontağının bağlandığı pin numarasını tanımla
int buzzerPin = 4;  // Buzzer'ın bağlandığı pin numarasını tanımla

void setup() {
    pinMode(kapiPin, INPUT);     // Kapı kontağının bağlandığı pini giriş olarak ayarla
    pinMode(buzzerPin, OUTPUT);  // Buzzer'ın bağlandığı pin çıkış pini olarak ayarla
}

void loop() {
    if (digitalRead(kapiPin) == LOW) {  // Eğer kapı açılırsa
        for (int i = 0; i < 3; i++) {   // 3 kere buzzerdan dıt dıt dıt sesi çıkarmak için
            digitalWrite(buzzerPin, HIGH);  // Buzzerdan ses çıkar
            delay(100);                     // 100 ms bekle
            digitalWrite(buzzerPin, LOW);   // Buzzer'ı sustur
            delay(100);                     // 100 ms bekle
        }
    }
    else {                              // Eğer kapı kapalı ise
        digitalWrite(buzzerPin, LOW);   // Buzzer'ı sustur
    }
    delay(3000);                       // 3 saniye bekle
}
