// SA57 - Hareket Sensörlü Hırsız Alarmı

// Alarm resetleme butonunun bağlandığı pin numarasını tanımla
int butonPin = 2;

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int kirmiziPin = 4;
int yesilPin = 11;

// PIR sensörün bağlandığı pin numarasını tanımla
int sensorPin = 3;

// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 6;

// sensorDurumu durumunun tutulacağı değişkeni tanımla
int sensorDurumu = 0;

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziPin, OUTPUT);
    pinMode(yesilPin, OUTPUT);
    
    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);
    
    // Resetleme butonunun bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
    
    // PIR sensörünün bağlandığı pini giriş olarak ayarla
    pinMode(sensorPin, INPUT);
}

void loop() {
    // Butona basılıp basılmadığını kontrol et
    if (digitalRead(butonPin) == HIGH) {  // Butona basıldı ise
        if (sensorDurumu == 0) {          // Sensör kapalı ise
            sensorDurumu = 1;             // Sensörü açık olarak kaydet
            digitalWrite(yesilPin, HIGH);  // Yeşil LED'i yak
        } else {                          // Sensör açık ise
            sensorDurumu = 0;             // Sensörü kapalı olarak kaydet
            digitalWrite(yesilPin, LOW);   // Yeşil LED'i kapat
        }
        delay(200);                       // 200ms bekle
    }

    // Sensör durumunu kontrol et
    if (digitalRead(sensorPin) == HIGH && sensorDurumu == 1) {  // Sensör tetiklendi ise
        while (1) {
            digitalWrite(yesilPin, LOW);     // Yeşil LED'i söndür
            digitalWrite(kirmiziPin, HIGH);  // Kırmızı LED'i yak
            tone(hoparlorPin, 440);         // Alarm sesini aktif et
            delay(250);                     // 250ms bekle
            
            digitalWrite(kirmiziPin, LOW);   // LED'i söndür
            noTone(hoparlorPin);
            delay(250);                     // 250ms bekle

            // Alarm resetleme butonuna basıldı ise
            if (digitalRead(butonPin) == HIGH) {
                delay(500);                 // 500ms bekle
                noTone(hoparlorPin);
                sensorDurumu = 0;
                digitalWrite(yesilPin, LOW); // Yeşil LED'i söndür
                delay(250);                 // 250ms bekle
                Serial.println("Alarm Devre Dışı");
                break;                      // Sonsuz döngüden çık alarmı devre dışı bırak
            }
        }
    }
}
