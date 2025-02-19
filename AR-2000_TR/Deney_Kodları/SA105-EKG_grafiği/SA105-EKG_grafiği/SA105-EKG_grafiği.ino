// SA105 - EKG grafiği

int ledPin = 3;      // LED'in bağlandığı pin numarasını tanımla
int hoparlorPin = 6; // Hoparlörün bağlandığı pin numarasını tanımla

void setup() {
    Serial.begin(9600);           // Seri haberleşmeyi başlat
    pinMode(ledPin, OUTPUT);      // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT); // Hoplarlörün bağlandığı pini çıkış olarak ayarla 
}

void loop() {
    Serial.println(analogRead(A5));     // Analog (A5) pininden değer oku, seri porta yaz
    
    if (analogRead(A5) >= 200) {        // Eğer okunan değer 200 den büyük ise 
        digitalWrite(ledPin, HIGH);      // LED'i yak
        tone(hoparlorPin, 1047);        // Hoparlörden ses çıkar 
    } else {                            // Eğer analog 5 piniden okunan değer 200 den küçük ise
        digitalWrite(ledPin, LOW);       // LED'i söndür
        noTone(hoparlorPin);            // Hoparlörü sustur
    }
    
    delay(10);                          // 10 ms gecikme
}
