// S33 - Mors Sinyali Üretici

int ledPin = 3;      // LED'in bağlandığı pini tanımla
int buzzerPin = 5;   // Buzzer'ın bağlandığı pini tanımla

char* harfler[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",     // A ile I arasındaki harfler
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",   // J ile R arasındaki harfler
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S ile Z arasındaki harfler
};

char* numaralar[] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....",
    "--...", "---..", "----."
};

int gecikme = 85;    // Gecikme değerini tanımla

void setup() {
    pinMode(ledPin, OUTPUT);     // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(buzzerPin, OUTPUT);  // Buzzer'ın bağlandığı pini çıkış olarak ayarla
    Serial.begin(9600);          // Seri haberleşme başlatıldı
}

void loop() {
    char ch;                     // ch değişkenini karakter olarak tanımla
    
    if (Serial.available()) {    // Seri port ekranından bir bilgi geldi ise
        ch = Serial.read();      // Okunan yazıyı ch'de tut
        
        if (ch >= 'a' && ch <= 'z') {           // Eğer ch, a ile z arasında ve küçük harf ise
            flashSequence(harfler[ch - 'a']);    // Mors sesini oluştur
        }
        else if (ch >= 'A' && ch <= 'Z') {      // Eğer ch, A ile Z arasında ve büyük harf ise
            flashSequence(harfler[ch - 'A']);
        }
        else if (ch >= '0' && ch <= '9') {      // Eğer ch sayı ise
            flashSequence(numaralar[ch - '0']);
        }
        else if (ch == ' ') {                   // Eğer ch boşluk ise
            delay(gecikme * 4);                 // Karakterler arasındaki bekleme
        }
    }
    delay(gecikme * 8);
}

void flashSequence(char* sequence) {
    int i = 0;
    while (sequence[i] != NULL) {
        noktaveyatire(sequence[i]);
        i++;
    }
    delay(gecikme * 3);    // Karakterler arasındaki bekleme
}

void noktaveyatire(char NoktaTire) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
    if (NoktaTire == '.') {     // Eğer nokta(.) ise
        delay(gecikme);
    }
    else {                      // Eğer tire(-) ise
        delay(gecikme * 3);
    }
    
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(gecikme);            // Karakterler arasındaki bekleme
}
