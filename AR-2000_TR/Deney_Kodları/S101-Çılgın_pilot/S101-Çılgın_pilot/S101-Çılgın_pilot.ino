// S101 - Çılgın pilot

int echoPin = 3;              // HC-SR04 Echo bacağının bağlandığı pini tanımla
int triggerPin = 2;           // HC-SR04 Trigger bacağının bağlandığı pini tanımla

// Süre, mesafe ve eski_mesafe değişkenlerini tanımla
unsigned long sure = 0;
unsigned int mesafe = 0;
unsigned int eski_mesafe = 0;

void setup() {
    pinMode(echoPin, INPUT);      // Echo bacağının bağlandığı pini giriş olarak ayarla
    pinMode(triggerPin, OUTPUT);   // Trigger bacağının bağlandığı pini çıkış olarak ayarla
    Serial.begin(9600);           // Processing ile haberleşme için seri iletişimi başlat
}

void loop() {
    digitalWrite(triggerPin, LOW);  // Trigger pini LOW yap
    delayMicroseconds(100);        // 100 mikro saniye bekle
    digitalWrite(triggerPin, HIGH); // Trigger pini HIGH yap
    delayMicroseconds(100);        // 100 mikro saniye bekle
    digitalWrite(triggerPin, LOW);  // Trigger pini LOW yap
    sure = pulseIn(echoPin, HIGH); // süreyi hesapla ve sure değişkenine kaydet
    mesafe = sure / 58;            // mesafeyi hesaplamak için sure değişkenini 58'e böl
    delay(10);                     // 10 mili saniye bekle

    if (eski_mesafe != mesafe) {   // Eğer eski_mesafe değişkeni mesafe değişkeninden farklı ise
        Serial.println(mesafe);     // mesafe değişkenini processing'e göndermek için serial print yap
        eski_mesafe = mesafe;       // mesafe değişkenindeki değeri eski_mesafe değişkenine kaydet
    }
    delay(50);                     // 50 ms bekle
}
