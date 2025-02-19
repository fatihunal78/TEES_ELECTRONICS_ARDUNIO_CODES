// S90 - Ultrasonik theremin

// HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define trigPin 4

// HC-SR04 Echo bacağının bağlandığı pini tanımla
#define echoPin 5

// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 2;

// Süre ve mesafe değişkenlerini tanımla
long sure, mesafe;
int oranla;

void setup() {
    // Trigger bacağının bağlandığı pini çıkış olarak ayarla
    pinMode(trigPin, OUTPUT);
    
    // Echo bacağının bağlandığı pini giriş olarak ayarla
    pinMode(echoPin, INPUT);
}

void loop() {
    // Trigger bacağını sıfıra çek
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);                    // 2 mikro saniye bekle
    
    // Trigger bacağını 5V'a çek
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);                   // 10 mikro saniye bekle
    
    // Trigger bacağını sıfıra çek
    digitalWrite(trigPin, LOW);
    
    // Echo pininden geri gelme süresini ölç
    sure = pulseIn(echoPin, HIGH);
    
    // Ölçülen süreyi ses hızı ile çarparak mesafeyi cm olarak hesapla
    mesafe = (sure/2) * 0.034;
    
    // Mesafeyi 10 ile çarp
    mesafe = mesafe * 10;
    
    oranla = map(mesafe, 0, 250, 0, 1000);
    
    if (mesafe > 250) {                      // Ölçülen mesafe 25cm den büyükse hoparlörü sustur
        noTone(hoparlorPin);                 // Hoparlörü sustur
    } else {                                 // Ölçülen mesafe 25cm'den küçük ise
        tone(hoparlorPin, oranla);          // Hoparlörden mesafe değerinde ses çal
    }
    
    delay(250);                              // 250ms bekle
}
