// S34 - SOS (imdat) Sinyali

int ledPin = 3;      // LED'in bağlı olduğu pini tanımla
int buzzerPin = 5;   // Buzzer'ın bağlı olduğu pini tanımla
int butonPin = 2;    // Buton'un bağlı olduğu pini tanımla

void setup() {
    pinMode(ledPin, OUTPUT);     // LED pinini çıkış olarak tanımla
    pinMode(buzzerPin, OUTPUT);  // Buzzer pinini çıkış olarak tanımla
    pinMode(butonPin, INPUT);    // Buton pinini giriş olarak tanımla
}

void loop() {
    if (digitalRead(butonPin) == HIGH) {  // Eğer butona basıldı ise
        flash(100); flash(100); flash(100);  // S harfi için üç kısa sinyal
        delay(300);                          // 300 milisaniye bekle
        flash(200); flash(200); flash(200);  // O harfi için üç uzun sinyal
        delay(300);                          // 300 milisaniye bekle
        flash(100); flash(100); flash(100);  // S harfi için üç kısa sinyal
    }
    delay(300);                              // 300 milisaniye bekle
}

void flash(int gecikme) {
    digitalWrite(ledPin, HIGH);      // LED'i yak
    digitalWrite(buzzerPin, HIGH);   // Buzzer'dan ses ver
    delay(gecikme);   
    digitalWrite(ledPin, LOW);       // LED'i söndür
    digitalWrite(buzzerPin, LOW);    // Buzzer'ı sustur
    delay(gecikme);
}
