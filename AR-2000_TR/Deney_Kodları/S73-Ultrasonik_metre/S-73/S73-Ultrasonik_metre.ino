// S73 - Ultrasonik metre

// HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define trigPin 2

// HC-SR04 Echo bacağının bağlandığı pini tanımla
#define echoPin 3

// Süre ve mesafe değişkenlerini tanımla
long sure, mesafe;

void setup() {
    // Seri portu aktif et
    Serial.begin(9600);
    
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
    
    if (mesafe > 2000 || mesafe < 0) {      // Mesafe 2000 cm'den büyük ve 0'dan küçük ise
        Serial.println("Menzil Dışı");       // Seri monitörden Menzil Dışı yaz
    } else {                                 // Mesafe 0 ila 2000 cm arasında ise
        Serial.print("Mesafe : ");           // Mesafe : yazısını yaz
        Serial.print(mesafe);                // mesafe değişkeninin değerini yaz
        Serial.println(" cm");               // mesafenin birimini cm olarak yaz
    }
    
    delay(500);                              // 500ms bekle
}
