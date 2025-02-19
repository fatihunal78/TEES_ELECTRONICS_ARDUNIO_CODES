// S51 - Uzay Savaşları

// LED'lerin bağlandığı pin numaralarını tanımla
int ledPin1 = 6;
int ledPin2 = 7;

// Hoparlörün bağlandığı pin numarasını tanımla  
int hoparlorPin = 3;

// Butonun bağlandığı pin numarasını tanımla
int butonPin = 2;

// Sayaç değişkenini tanımla
int sayac = 0;

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    
    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);
    
    // Butonun bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
}

void loop() {
    // Buton durumunu sorgula
    if(digitalRead(butonPin) == HIGH) {    // Butona basıldı ise
        sesCaldir(random(0, 200), random(100, 200));    // sesCaldir fonksiyonu ile hoparlörden ses çaldır
        sesCaldir(random(0, 200), random(100, 200));  
        sesCaldir(random(0, 200), random(100, 200));  
        sesCaldir(random(0, 200), random(100, 200));  
        sesCaldir(1200, 150);
        sesCaldir(2000, 150);
        sesCaldir(2800, 150);
        sesCaldir(3600, 150);
        sesCaldir(random(0, 200), random(100, 200));  
        sesCaldir(random(0, 200), random(100, 200));  
        sesCaldir(random(0, 200), random(100, 200));  
        sesCaldir(random(0, 200), random(100, 200));  
        sesCaldir(600, 200);
        sesCaldir(800, 200);
        sesCaldir(1000, 200);
        sesCaldir(1800, 200);
        sesCaldir(1200, 200);
    }
}

// sesCaldir fonksiyonunu tanımla, nota ve sure değişkenlerini değişken olarak al
void sesCaldir(int nota, int sure) {
    for(int i = 0; i < 3; i++) {
        nota = nota + 100;
        tone(hoparlorPin, nota, sure/3);    // Nota çaldır
        delay(sure/3);                      // sure/3 kadar bekle
        noTone(hoparlorPin);               // Nota sustur
    }
    
    if(sayac%2 == 0) {                     // LED'leri sıra ile yak, söndür
        digitalWrite(ledPin1, HIGH);        // Birinci LED'i yak
        delay(sure);                       // İstenen kadar bekle
        digitalWrite(ledPin1, LOW);         // Birinci LED'i söndür
    }
    else {
        digitalWrite(ledPin2, HIGH);        // İkinci LED'i yak
        delay(sure);                       // İstenen kadar bekle
        digitalWrite(ledPin2, LOW);         // İkinci LED'i söndür
    }
    
    delay(50);                             // 50ms bekle
    sayac++;                               // sayac değişkenini bir arttır
}
