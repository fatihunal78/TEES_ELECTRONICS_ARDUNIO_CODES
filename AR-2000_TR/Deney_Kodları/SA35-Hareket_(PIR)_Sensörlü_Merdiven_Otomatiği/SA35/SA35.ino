// SA35 - Hareket (PIR) Sensörlü Merdiven Otomatiği

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int maviLed    = 4;
int kirmiziPin = 5;
int yesilLed   = 6;
int sariLed    = 7;

// PIR sensörün bağlandığı dijital pin numarasını tanımla
int sensorPin = 2;
// PIR sensörün durumunun tutulacağı değişkeni tanımla
int sensorDurumu = 0;

void setup() {
    // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(maviLed, OUTPUT);
    pinMode(sariLed, OUTPUT); 
    pinMode(kirmiziPin, OUTPUT); 
    pinMode(yesilLed, OUTPUT); 
    
    // PIR sensörün bağlandığı pini giriş olarak ayarla
    pinMode(sensorPin, INPUT);
}

void loop() {
    // PIR sensörün durumunu sorgula ve sensorDurumu değişkenine kaydet
    sensorDurumu = digitalRead(sensorPin);
    
    // PIR sensörün durumuna göre LED'in durumunu ayarla
    if (sensorDurumu == HIGH) {  // Sensör tetiklendi ise
        // LED'leri yak
        digitalWrite(maviLed, HIGH);
        digitalWrite(sariLed, HIGH);
        digitalWrite(kirmiziPin, HIGH);
        digitalWrite(yesilLed, HIGH);

        delay(5000);                     // 5 saniye bekle 
        digitalWrite(maviLed, LOW);      // Mavi LED'i söndür 
        delay(5000);                     // 5 saniye bekle 
        digitalWrite(kirmiziPin, LOW);   // Kırmızı LED'i söndür 
        delay(5000);                     // 5 saniye bekle 
        digitalWrite(yesilLed, LOW);     // Yeşil LED'i söndür 
        delay(5000);                     // 5 saniye bekle 
        digitalWrite(sariLed, LOW);      // Sarı LED'i söndür
    }
}
