// S50 - Yağmur Alarmı

int ledPin = 8;       // LED'in bağlandığı dijital pin numarasını tanımla
int sensorPin = 2;    // Nem sensörünün bağlandığı pin numarasını tanımla  
int hoparlorPin = 4;  // Hoparlörün bağlandığı pin numarasını tanımla

int yagmurDurumu = 0; // Nem sensörünün durumunun tutulacağı değişkeni tanımla

void setup() {
    pinMode(ledPin, OUTPUT);      // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT); // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(sensorPin, INPUT);    // Nem sensörünün bağlandığı pini giriş olarak ayarla
}

void loop() {
    // Yağmur durumunu sorgula ve değişkene ata
    yagmurDurumu = digitalRead(sensorPin);

    // Yağmur durumunu kontrol et
    if(yagmurDurumu == HIGH) {    // Yağmur yağıyor ise
        digitalWrite(ledPin, HIGH);// LED'i yak
        
        tone(hoparlorPin, 750);   // Hoparlörü aktif et
        delay(50);                // 50ms bekle    
        noTone(hoparlorPin);      // Hoparlörü sustur
        delay(200);               // 200ms bekle       
        digitalWrite(ledPin, LOW); // LED'i söndür
        
        tone(hoparlorPin, 750);   // Hoparlörü aktif et
        delay(200);               // 200ms bekle
        noTone(hoparlorPin);      // Hoparlörü sustur
        delay(50);                // 50ms bekle
    }
    else {                        // Yağmur yağmıyor ise
        digitalWrite(ledPin, LOW); // LED'i söndür   
        noTone(hoparlorPin);      // Hoparlörü sustur
    }
}
