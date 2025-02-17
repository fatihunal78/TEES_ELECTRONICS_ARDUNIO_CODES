// S52 - Rastgele Renk Yakalama

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int kirmiziLedPin = 6;           // Kırmızı LED pin
int yesilLedPin = 5;             // Yeşil LED pin  
int maviLedPin = 3;              // Mavi LED pin

// Butonun bağlandığı dijital pin numarasını tanımla
int butonPin = 2;                // Buton pin

// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 9;             // Hoparlör pin

// Buton durumunun tutulacağı değişkeni tanımla
int butonDurumu = 0;             // Buton durumu

// LED'lerin durumunun tutulacağı değişkenleri tanımla
int kirmiziDurumu = 0;           // Kırmızı LED durumu
int yesilDurumu = 0;             // Yeşil LED durumu
int maviDurumu = 0;              // Mavi LED durumu

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziLedPin, OUTPUT);
    pinMode(yesilLedPin, OUTPUT);
    pinMode(maviLedPin, OUTPUT);
    
    // Butonun bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
    
    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);
    
    // Başlangıçta LED'lerin hepsini söndür
    digitalWrite(kirmiziLedPin, HIGH);
    digitalWrite(yesilLedPin, HIGH);
    digitalWrite(maviLedPin, HIGH);
}

void loop() {
    // Buton durumunu sorgula ve butonDurumu değişkenine ata
    butonDurumu = digitalRead(butonPin);

    // Buton durumuna göre RGB LED durumunu ayarla
    if(butonDurumu == HIGH) {    // Butona basıldı ise
        // 3 sn animasyon yap
        for(int i = 0; i < 15; i++) {
            // LED durumlarını 0-255 arasında rastgele olarak seç
            kirmiziDurumu = random(0, 256);
            yesilDurumu = random(0, 256);
            maviDurumu = random(0, 256);
            
            // Hoparlörden LED durumlarına göre ses çıkar
            tone(hoparlorPin, (kirmiziDurumu + yesilDurumu + maviDurumu) / 3);
            
            // RGB LED'i durum değişkenlerinin seviyelerine göre yak
            analogWrite(kirmiziLedPin, kirmiziDurumu);
            analogWrite(yesilLedPin, yesilDurumu);
            analogWrite(maviLedPin, maviDurumu);
            
            delay(200);               // 200ms bekle
            noTone(hoparlorPin);     // hoparlorPin'i normal pin haline getir
        }
        delay(500);                  // 500ms bekle
    }
}
