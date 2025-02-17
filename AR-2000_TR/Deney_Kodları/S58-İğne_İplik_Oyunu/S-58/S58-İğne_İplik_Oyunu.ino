// S58 - İğne İplik Oyunu

int ledPin = 2;        // Panel üzerindeki LED'in bağlandığı pin numarasını tanımla
int hoparlorPin = 7;   // Hoparlörün bağlandığı pin numarasını tanımla 
int sensorPin = 4;     // 10K direnç üzerinden gelen bağlantıyı sensör pini olarak tanımla

void setup() {
    pinMode(ledPin, OUTPUT);      // Panel üzerindeki LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT); // Hoparlörün bağlandığı pini çıkış olarak ayarla 
    pinMode(sensorPin, INPUT);    // Sensörün bağlandığı pini giriş olarak ayarla                      
}

void loop() {
    // Serbest mod ayarları 
    if (digitalRead(sensorPin) == HIGH) {   // Eğer sensörden okunan değer 1 ise yani iğne ve iplik 
                                           // birbirine değmiş ise  
        digitalWrite(ledPin, HIGH);         // Panel üzerindeki Kırmızı LED'i yak 
        tone(hoparlorPin, 700);            // Hoparlörden ses çıkar 
    }
    else {                                 // Eğer sensörden okunan değer 0 ise yani iğne ve iplik 
                                          // birbirine değmemiş ise  
        digitalWrite(ledPin, LOW);         // LED'i söndür 
        noTone(hoparlorPin);              // Hoparlörü sustur 
    }
    delay(100);
}