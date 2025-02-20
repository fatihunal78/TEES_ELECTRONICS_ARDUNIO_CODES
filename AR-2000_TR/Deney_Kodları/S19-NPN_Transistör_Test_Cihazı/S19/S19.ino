// S19 - NPN Transistör Test Cihazı

int BasePin = 2;    // Transistörün Base bacağının bağlandığı pin numarası tanımlandı

void setup() {
    pinMode(BasePin, OUTPUT);    // Base pin çıkış olarak ayarlandı
}

void loop() {
    digitalWrite(BasePin, HIGH);    // BasePin'e sinyal gönderdik (HIGH yaptık)
    delay(1000);
    digitalWrite(BasePin, LOW);     // BasePin'e sinyal gönderdik (LOW yaptık)
    delay(1000);
}
