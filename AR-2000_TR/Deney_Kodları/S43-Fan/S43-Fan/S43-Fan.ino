// S43 - Fan

int motorPin = 3;          // Motorun bağlı olduğu pini tanımla
int butonPin = 2;         // Butonun bağlı olduğu pini tanımla
boolean motorDurumu = 0;   // Motorun açık ya da kapalı değerinin tutulacağı değişkeni tanımla
                          // 0 --> motor kapalı (dönmüyor), 1 --> motor açık (dönüyor)
boolean butonDurumu = LOW; // Butona basılıp basılmadığı durumları tutacak değişkeni tanımla

void setup() {
    pinMode(motorPin, OUTPUT);  // Motor pinini çıkış olarak ayarla
    pinMode(butonPin, INPUT);   // Buton pinini giriş olarak ayarla
    
    // Butonun bağlandığı pini Interrupt (kesme) olarak ayarla
    // Butona basıldığında butonSorgulama fonksiyonundaki işlemi yap
    // RISING (Yükselen kenar) da tetikleme yap
    attachInterrupt(digitalPinToInterrupt(butonPin), butonSorgulama, RISING);
}

void loop() {
    if(motorDurumu == 1) {     // MotorDurumu değişkeni 1 ise 
        digitalWrite(motorPin, HIGH);  // motoru döndür
    }
    else {                     // motorDurumu değişkeni 0 ise 
        digitalWrite(motorPin, LOW);   // motoru durdur
    }
}

void butonSorgulama() {        // Kesme fonksiyonunu tanımla
                               // Butona basıldığında fonksiyon içerisindeki işlemi yap
    motorDurumu = !motorDurumu; // Eğer motorDurumu değişkeni 0 ise 1 yap, 1 ise 0 yap
                                // Motor dönüyorsa yani motorDurumu değişkeni 1 ise 0 yap
                                // Motor dönmüyorsa motorDurumu değişkeni 0 ise 1 yap
}
