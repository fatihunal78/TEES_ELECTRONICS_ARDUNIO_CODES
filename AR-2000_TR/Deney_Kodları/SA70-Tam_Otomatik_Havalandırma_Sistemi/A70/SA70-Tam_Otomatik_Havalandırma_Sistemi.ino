// SA70 - Tam Otomatik Havalandırma Sistemi

int beyazLed  = 2;    // Beyaz LED'in bağlandığı pin numarasını tanımla
int sensorPin = 5;    // PIR sensörün bağlandığı pin numarasını tanımla
int motorPin  = 4;    // Moturun bağlandığı pin numarasını tanımla

void setup() {   
    pinMode(beyazLed, OUTPUT);   // Beyaz LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sensorPin, INPUT);   // Sensörün bağlandığı pini giriş olarak ayarla
    pinMode(motorPin, OUTPUT);   // Moturun bağlandığı pini çıkış olarak ayarla  
}

void loop() {
    // Sensör durumunu kontrol et
    if (digitalRead(sensorPin) == HIGH) {    // Sensör tetiklendi ise
        digitalWrite(beyazLed, HIGH);         // Beyaz LED'i yak 
        digitalWrite(motorPin, HIGH);         // Motoru çalıştır 
        delay(5000);                         // 5 sn bekle
    } else {
        digitalWrite(beyazLed, LOW);          // Beyaz LED'i söndür
        digitalWrite(motorPin, LOW);          // Motoru durdur 
    } 
}
