// S63 - Dokunmatik Işık ayarlayıcı (Dimmer)

int ledPin = 5;          // LED'in bağlandığı dijital pin numarasını tanımla
int dokunmatikPin = 2;   // Dokunmatik buton'un bağlandığı dijital pin numarasını tanımla
int butonDurumu = 0;     // Dokunmatik buton durumunun tutulacağı değişkeni tanımla

int ledDurumu = 0;       // LED durumunun tutulacağı değişkeni tanımla
int ledParlaklik = 0;    // LED parlaklığının tutulacağı değişkeni tanımla
int ledKontrolDurumu = 0;// LED kısılma açılma durumunun tutulacağı değişkeni tanımla

void setup() {
    pinMode(ledPin, OUTPUT);        // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(dokunmatikPin, INPUT);  // Dokunmatik buton'un bağlandığı pini giriş olarak ayarla
}

void loop() {
    butonDurumu = digitalRead(dokunmatikPin);  // Dokunmatik buton durumunu sorgula ve butonDurumu değişkenine ata

    // Dokunmatik buton durumuna göre LED'in durumunu ayarla
    if (butonDurumu == LOW) {                  // Dokunmatik butona basıldı ise
        if (ledDurumu == 0) {                  // LED yanmıyor ise
            delay(500);                        // 500ms bekle
            if (digitalRead(dokunmatikPin) == HIGH) {  // Dokunmatik buton bırakıldı ise
                ledParlaklik = 255;            // LED'i maksimum parlaklıkta yak
                analogWrite(ledPin, ledParlaklik);  // LED'i ledParlaklik değerine göre yak
                delay(500);                    // 500ms bekle
            } else {                           // Dokunmatik buton bırakılmadı ise
                while (digitalRead(dokunmatikPin) == LOW) {  // Dokunmatik buton halen basılı ise
                    ledParlaklik += 25;        // ledParlaklik değerini 25 arttır
                    if (ledParlaklik > 255) {  // ledParlaklik değeri 255'den büyükse
                        ledParlaklik = 255;    // ledParlaklik değeri 255'e ayarla
                    }
                    analogWrite(ledPin, ledParlaklik);  // LED'i ledParlaklik değerine göre yak
                    delay(250);                // 250ms bekle
                }
            }
            ledKontrolDurumu = 1;              // LED ayar durumunu artış olarak kaydet
            ledDurumu = 1;                     // LED durumunu açık olarak kaydet
        } else {                               // LED yanıyor ise
            delay(500);                        // 500ms bekle
            if (digitalRead(dokunmatikPin) == HIGH) {  // Dokunmatik buton bırakıldı ise
                ledParlaklik = 0;              // ledParlaklik değerini minimuma ayarla
                analogWrite(ledPin, ledParlaklik);  // LED'i ledParlaklik değerine göre yak
                ledDurumu = 0;                 // LED durumunu kapalı olarak kaydet
                delay(500);                    // 500ms bekle
            } else {                           // Dokunmatik buton bırakılmadı ise
                while (digitalRead(dokunmatikPin) == LOW) {  // Dokunmatik buton halen basılı ise
                    if (ledKontrolDurumu == 0) {  // Kısıktan yüksek ışığa doğru artış ise
                        ledParlaklik += 25;    // ledParlaklik değerini 25 arttır
                        if (ledParlaklik > 255) {  // ledParlaklik değeri 255'den büyükse
                            ledParlaklik = 255;  // ledParlaklik değerini 255'e ayarla
                        }
                    } else {
                        ledParlaklik -= 25;    // ledParlaklik değerini 25 azalt
                        if (ledParlaklik < 0) {  // ledParlaklik değeri 0'dan küçükse
                            ledParlaklik = 0;  // ledParlaklik değerini 0'a ayarla
                            ledDurumu = 0;     // LED durumunu kapalı olarak kaydet
                        }
                    }
                    analogWrite(ledPin, ledParlaklik);
                    delay(250);                // 250ms bekle
                }
                if (ledKontrolDurumu == 0) {   // LED ayar durumunu azalış olarak ayarlı ise
                    ledKontrolDurumu = 1;      // LED ayar durumunu artış olarak kaydet
                } else {
                    ledKontrolDurumu = 0;      // LED ayar durumunu azalış olarak kaydet
                }
            }
        }
    }
}
