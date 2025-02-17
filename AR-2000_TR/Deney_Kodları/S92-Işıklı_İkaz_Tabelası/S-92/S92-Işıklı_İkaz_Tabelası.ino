// S92 - Işıklı İkaz Tabelası

int ledler[] = {2, 3, 4, 5, 6, 7, 8};    // LED'lerin bağlandığı pin numaralarını tanımla
int ldrPin = A5;                          // LDR'nin bağlandığı pin numarasını tanımla

int hiz = 200;                            // LED'lerin gezinme hızı değişkenini tanımla, isteğinize göre değiştirebilirsiniz

void setup() {
    // For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for (int i = 0; i < 7; i++) {
        pinMode(ledler[i], OUTPUT);
    }
    pinMode(ldrPin, INPUT_PULLUP);        // LDR'nin bağlandığı pini giriş olarak ayarla, pull up direncini aktif et
}

void loop() {
    // LDR durumunu kontrol et 
    if (analogRead(ldrPin) > 600) {       // Işık şiddeti değeri 600'den büyük ise 
        // Sıra ile LED'leri yak
        for (int i = 0; i < 5; i++) {     // For döngüsü kullanarak ledler[i] değişkenine tanımlı, 2,3,4,5,6 nolu 
                                          // dijital pindeki ledleri yak 
            digitalWrite(ledler[i], HIGH);
            delay(hiz);
        }  
   
        digitalWrite(ledler[5], HIGH);     // ledler[5] nolu LED'i yak
        delay(hiz);                        // hiz değişkeni kadar bekle
    
        digitalWrite(ledler[6], HIGH);     // ledler[6] nolu LED'i yak
        delay(hiz);                        // hiz değişkeni kadar bekle
    
        // LED'lerin hepsini söndür
        for (int l = 0; l < 7; l++) {     // For döngüsü kullanarak ledler[l] değişkenine tanımlı ledleri söndür
            digitalWrite(ledler[l], LOW); 
        }
        delay(hiz);
    
        for (int i = 0; i < 3; i++) {     // 3 kere tekrar et 
            // LED'lerin hepsini yak
            for (int l = 0; l < 7; l++) {
                digitalWrite(ledler[l], HIGH);
            }
            delay(hiz);

            // LED'lerin hepsini söndür
            for (int l = 0; l < 7; l++) {
                digitalWrite(ledler[l], LOW);
            }
            delay(hiz);
        }
    }
}
