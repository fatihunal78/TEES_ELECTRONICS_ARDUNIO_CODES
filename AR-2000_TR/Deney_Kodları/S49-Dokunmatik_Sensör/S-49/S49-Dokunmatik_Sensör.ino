// S49 - Dokunmatik Sensör

int ledPin = 7;      // LED'in bağlandığı pin numarasını tanımla 
int sensorPin = 3;   // Dokunmatik sensörün bağlandığı pin numarasını tanımla 

int ledDurumu = 0;   // LED'in durumunun tutulacağı değişkeni tanımla

void setup() {
    pinMode(ledPin, OUTPUT);    // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sensorPin, INPUT);  // Sensörün bağlandığı pini giriş olarak ayarla
}

void loop() {
    if(digitalRead(sensorPin) == HIGH) {     // Eğer dokunmatik sensöre basıldı ise 
        if(ledDurumu == 0) {                 // Eğer LED kapalı ise 
            digitalWrite(ledPin, HIGH);       // LED'i yak 
            ledDurumu = 1;                   // LED durumunu açık yani 1 olarak kaydet 
            delay(100);                      // 100 ms bekle
        }
        else if(ledDurumu == 1) {           // Eğer LED açık ise 
            digitalWrite(ledPin, LOW);       // LED'i söndür 
            ledDurumu = 0;                  // LED durumunu kapalı yani 0 olarak kaydet 
            delay(100);                     // 100 ms bekle
        }
    }
    delay(200);                             // 200 ms bekle
}
