// S20 - İletken Yalıtkan Test Aleti

int sensorPin = 3;    // Prop uçunun bağlandığı pin numarası tanımlandı
                      // 3 numaralı pinin ismi sensorPin olarak ayarlandı
                 
int buzzerPin = 5;    // Buzzer 5 numaralı pine bağlandı ve 5 numaralı pinin ismi buzzerPin olarak ayarlandı
                 
void setup() {
    pinMode(sensorPin, INPUT);     // Sensör pin giriş pini olarak ayarlandı
    pinMode(buzzerPin, OUTPUT);    // Buzzer pin çıkış pini olarak ayarlandı 
}

void loop() {
    if (digitalRead(sensorPin) == HIGH) {    // digitalRead(sensorPin) komutu ile probun bağlı olduğu 3 numaralı 
                                            // pindeki değeri oku. Eğer bu değer HIGH ise
        digitalWrite(buzzerPin, HIGH);       // Buzzerdan ses çıkar
    }
    else {                                   // Eğer sensördeki pin LOW ise 
        digitalWrite(buzzerPin, LOW);        // Buzzeri sustur
    }
}
