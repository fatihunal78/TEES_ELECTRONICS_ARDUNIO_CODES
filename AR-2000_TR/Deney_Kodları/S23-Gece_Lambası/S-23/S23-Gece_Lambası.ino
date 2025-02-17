// S23 - Gece Lambası

// LED'in bağlandığı dijital pin numarasını tanımla
int ledPin = 3;
// Butonun bağlandığı pin numarasını tanımla  
int butonPin = 2;
// LDR'nin bağlandığı analog pin numarasını tanımla
int LDRPin = A5;

// Işık değerinin tutulacağı değişkeni tanımla
int isik_degeri = 0;
// LED'in açık ya da kapalı tutulacağı değişkeni tanımla
int leddurumu = 0;

void setup() {
    // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(ledPin, OUTPUT);
    // Buton pinini giriş pini olarak ayarla
    pinMode(butonPin, INPUT_PULLUP);    // Giriş olarak ayarlayıp Pull Up direnç aktif ettik
}

void loop() {
    // Ölçülen ışık değerini analog pinden oku ve isik_degeri değişkenine ata.
    // Işık değeri 0-1023 değerleri arasında okunur. Değer karanlıkta düşük, aydınlıkta yüksek olur. 
    // 300 değerini istediğin aydınlık seviyesine göre değiştirebilirsin.
    isik_degeri = analogRead(LDRPin);

    if (digitalRead(butonPin) == LOW) {    // Eğer butona basıldı ise
        if (leddurumu == 0) {              // Eğer leddurumu değişkeni 0 ise (ışık kapalı ise)
            leddurumu = 1;                  // leddurumu değişkenini 1 yap (ışık durumu açık olarak kaydet)
        }
        else {                             // Eğer leddurumu değişkeni 1 ise (ışık açık ise)
            leddurumu = 0;                 // leddurumu değişkenini 0 yap (ışık durumu kapalı olarak kaydet)
        }
    }

    // Eğer leddurumu değişkeni 1 ise veya LDR'den okunan değer 300'den küçük ise
    // Yani butona basıldı ise veya hava karardı ise
    if (leddurumu == 1 || isik_degeri <= 300) {
        digitalWrite(ledPin, HIGH);    // LED'i yak
    }
    // Eğer leddurumu değişkeni 0 ise veya LDR'den okunan değer 300'den büyük ise
    // Yani butona basıldı ise veya hava aydınlandı ise
    else if (leddurumu == 0 || isik_degeri > 300) {
        digitalWrite(ledPin, LOW);     // LED'i söndür
    }

    delay(250);    // 250ms bekle
}
