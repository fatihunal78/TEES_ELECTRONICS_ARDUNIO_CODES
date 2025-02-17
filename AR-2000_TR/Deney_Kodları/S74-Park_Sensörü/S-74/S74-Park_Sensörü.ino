// S74 - Park Sensörü

// LED'lerin bağlandığı pin numaralarını tanımla
int YesilLed1 = 4;
int YesilLed2 = 5;
int SariLed = 6;
int KirmiziLed1 = 7;
int KirmiziLed2 = 8;

// Hoparlörün takıldığı pin numarasını tanımla
int hoparlorPin = 9;

// HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define trigPin 2

// HC-SR04 Echo bacağının bağlandığı pini tanımla
#define echoPin 3

// Uyarı sesi süresinin tutulacağı değişkeni tanımla
int bipSure = 300;

// Süre ve mesafe değişkenlerini tanımla
long sure, mesafe;

void setup() {
    // LED'leri çıkış olarak ayarla
    pinMode(YesilLed1, OUTPUT);
    pinMode(YesilLed2, OUTPUT);
    pinMode(SariLed, OUTPUT);
    pinMode(KirmiziLed1, OUTPUT);
    pinMode(KirmiziLed2, OUTPUT);
    
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

    // Mesafe hesaplama işleminin sonucuna göre LED'leri yak  
    if (mesafe > 50) {                       // Mesafe 50 cm'den büyük ise
        // LED'lerin hepsini söndür
        digitalWrite(YesilLed1, LOW);
        digitalWrite(YesilLed2, LOW);
        digitalWrite(SariLed, LOW);
        digitalWrite(KirmiziLed1, LOW);
        digitalWrite(KirmiziLed2, LOW);
    }
    else if (mesafe > 40) {                  // Mesafe 50 cm'den küçük ve 40 cm'den büyük ise
        // İlk uyarı LED'ini yak
        digitalWrite(YesilLed1, HIGH);
        
        // Diğer LED'lerin hepsini söndür    
        digitalWrite(YesilLed2, LOW);
        digitalWrite(SariLed, LOW);
        digitalWrite(KirmiziLed1, LOW);
        digitalWrite(KirmiziLed2, LOW);
    }
    else if (mesafe > 30) {                  // Mesafe 40 cm'den küçük ve 30 cm'den büyük ise
        // İlk iki LED'i yak
        digitalWrite(YesilLed1, HIGH);
        digitalWrite(YesilLed2, HIGH);
        
        // Diğer LED'leri söndür
        digitalWrite(SariLed, LOW);
        digitalWrite(KirmiziLed1, LOW);
        digitalWrite(KirmiziLed2, LOW);
        
        tone(hoparlorPin, 440);              // Hoparlörden bip sesi çıkart
        delay(bipSure / 3);                  // sure değerinin 3'te biri kadar bekle
        noTone(hoparlorPin);                 // Hoparlörü sustur
        delay(bipSure / 3);                  // sure değerinin 3'te biri kadar bekle
    }
    else if (mesafe > 20) {                  // Mesafe 30 cm'den küçük ve 20 cm'den büyük ise
        // İlk üç LED'i yak
        digitalWrite(YesilLed1, HIGH);
        digitalWrite(YesilLed2, HIGH);
        digitalWrite(SariLed, HIGH);
        
        // Diğer LED'leri söndür    
        digitalWrite(KirmiziLed1, LOW);
        digitalWrite(KirmiziLed2, LOW);
        
        tone(hoparlorPin, 440);              // Hoparlörden bip sesi çıkart
        delay(bipSure / 4);                  // sure değerinin 4'te biri kadar bekle
        noTone(hoparlorPin);                 // Hoparlörü sustur
        delay(bipSure / 4);                  // sure değerinin 4'te biri kadar bekle
    }
    else if (mesafe > 10) {                  // Mesafe 20 cm'den küçük ve 10 cm'den büyük ise
        // İlk dört LED'i yak
        digitalWrite(YesilLed1, HIGH);
        digitalWrite(YesilLed2, HIGH);
        digitalWrite(SariLed, HIGH);
        digitalWrite(KirmiziLed1, HIGH);
        
        // Diğer LED'i söndür  
        digitalWrite(KirmiziLed2, LOW);
        
        tone(hoparlorPin, 440);              // Hoparlörden bip sesi çıkart
        delay(bipSure / 5);                  // sure değerinin 5'te biri kadar bekle
        noTone(hoparlorPin);                 // Hoparlörü sustur
        delay(bipSure / 5);                  // sure değerinin 5'te biri kadar bekle
    }
    else if (mesafe > 0) {                   // Mesafe 10 cm'den küçük ve 0 cm'den büyük ise
        // LED'lerin hepsini yak
        digitalWrite(YesilLed1, HIGH);
        digitalWrite(YesilLed2, HIGH);
        digitalWrite(SariLed, HIGH);
        digitalWrite(KirmiziLed1, HIGH);
        digitalWrite(KirmiziLed2, HIGH);
        
        tone(hoparlorPin, 440);              // Hoparlörden bip sesi çıkart
    }
}
