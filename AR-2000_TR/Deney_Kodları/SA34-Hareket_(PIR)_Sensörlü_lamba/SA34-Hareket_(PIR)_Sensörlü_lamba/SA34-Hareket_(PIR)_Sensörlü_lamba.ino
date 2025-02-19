// SA34 - Hareket (PIR) Sensörlü lamba

int sensorPin = 2;    // PIR sensörün bağlandığı pin numarasını tanımla
int BeyazLed  = 7;    // LED'in bağlandığı pin numarasını tanımla

void setup() {
    pinMode(sensorPin, INPUT);    // PIR sensörünün bağlandığı pini giriş olarak tanımla
    pinMode(BeyazLed, OUTPUT);    // Beyaz LED'in bağlandığı pini çıkış olarak tanımla 
}

void loop() {
    // Sensör durumunu kontrol et
    if (digitalRead(sensorPin) == HIGH) {    // Sensör tetiklendi ise
        digitalWrite(BeyazLed, HIGH);        // Beyaz LED'i yak
    }
    else {                                   // Eğer sensör tetiklenmedi ise 
        digitalWrite(BeyazLed, LOW);         // Beyaz LED'i söndür
    }
}