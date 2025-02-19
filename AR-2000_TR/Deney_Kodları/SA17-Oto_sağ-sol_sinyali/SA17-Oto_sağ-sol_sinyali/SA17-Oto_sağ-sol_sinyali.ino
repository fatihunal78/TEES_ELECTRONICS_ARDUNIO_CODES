// SA17 - Oto sağ-sol sinyali

// Sol sinyal LED'inin bağlandığı pin numarasını tanımla
int solSinyalPin  = 6;
// Sağ sinyal LED'inin bağlandığı pin numarasını tanımla
int sagSinyalPin  = 7;
// Joystick X ekseninin bağlandığı pin numarasını tanımla
int xPin         = A5;
// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin  = 4;

int xPozisyonu = 0;    // Joystick X ekseninin pozisyonunun tutulacağı değişkeni tanımla

void setup() {
    // Sol sinyal LED'inin bağlandığı pini çıkış olarak ayarla
    pinMode(solSinyalPin, OUTPUT);
    // Sağ sinyal LED'inin bağlandığı pini çıkış olarak ayarla
    pinMode(sagSinyalPin, OUTPUT);
    // Kulaklığın bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);
    // Joystick X ekseninin bağlandığı pini giriş olarak ayarla
    pinMode(xPin, INPUT);
}

void loop() {
    // Joystick X ekseninin pozisyonunun oku ve xPozisyonu değişkenine kaydet
    xPozisyonu = analogRead(xPin);

    if (xPozisyonu > 900) {    // Joystick sağa çekildiyse
        for (int i = 0; i < 3; i++) {
            digitalWrite(sagSinyalPin, HIGH);    // Sağ sinyal LED'ini yak
            tone(hoparlorPin, 1000, 5);         // Tik tok sesi çal
            delay(400);                         // 400ms bekle
            digitalWrite(sagSinyalPin, LOW);     // Sağ sinyal LED'ini söndür
            noTone(hoparlorPin);                // Sesi sustur
            delay(400);                         // 400ms bekle
        }
    }

    if (xPozisyonu < 120) {    // Joystick sola çekildiyse
        for (int i = 0; i < 3; i++) {
            digitalWrite(solSinyalPin, HIGH);    // Sol sinyal LED'ini yak
            tone(hoparlorPin, 1000, 5);         // Tik tok sesi çal
            delay(400);                         // 400ms bekle
            digitalWrite(solSinyalPin, LOW);     // Sol sinyal LED'ini söndür
            noTone(hoparlorPin);                // Sesi sustur
            delay(400);                         // 400ms bekle
        }
    }
}
