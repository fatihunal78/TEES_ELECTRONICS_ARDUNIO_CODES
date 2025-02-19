// S76 - Kademeli voltmetre

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int ledler[] = {2, 3, 4, 5, 6};

// Potun bağlandığı dijital pin numarasını tanımla
int potPin = A0;

// Potansiyometre değerinin kaydedileceği değişkeni tanımla
int potDegeri = 0;

void setup() {
    // Seri portu 9600 baud rate ile başlat
    Serial.begin(9600);
    
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    // For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for (int i = 0; i < 5; i++) {
        pinMode(ledler[i], OUTPUT);
    }
}

void loop() {
    // Potun değerini oku ve potDurumu değişkenine ata
    potDegeri = analogRead(potPin);
    Serial.print("Okunan Voltaj : ");
    Serial.print((float)potDegeri * 5 / 1023);
    Serial.println(" V");

    if (975 < potDegeri) {                    // Ölçülen değer 5V ise 
        for (int i = 0; i < 5; i++) {
            digitalWrite(ledler[i], HIGH);
        }
    }
    else if (820 < potDegeri) {              // Ölçülen değer 4V ve üzeri ise 
        for (int i = 0; i < 4; i++) {
            digitalWrite(ledler[i], HIGH);
        }
        for (int i = 4; i < 5; i++) {
            digitalWrite(ledler[i], LOW);
        }
    }
    else if (615 < potDegeri) {              // Ölçülen değer 3V ve üzeri ise 
        for (int i = 0; i < 3; i++) {
            digitalWrite(ledler[i], HIGH);
        }
        for (int i = 3; i < 5; i++) {
            digitalWrite(ledler[i], LOW);
        }
    }
    else if (410 < potDegeri) {              // Ölçülen değer 2V ve üzeri ise 
        for (int i = 0; i < 2; i++) {
            digitalWrite(ledler[i], HIGH);
        }
        for (int i = 2; i < 5; i++) {
            digitalWrite(ledler[i], LOW);
        }
    }
    else if (205 < potDegeri) {              // Ölçülen değer 1V ve üzeri ise 
        digitalWrite(ledler[0], HIGH);
        for (int i = 1; i < 5; i++) {
            digitalWrite(ledler[i], LOW);
        }
    }
    else if (0 <= potDegeri) {               // Ölçülen değer 1V ve altı ise 
        for (int i = 0; i < 5; i++) {
            digitalWrite(ledler[i], LOW);
        }
    }
    
    delay(250);
}
