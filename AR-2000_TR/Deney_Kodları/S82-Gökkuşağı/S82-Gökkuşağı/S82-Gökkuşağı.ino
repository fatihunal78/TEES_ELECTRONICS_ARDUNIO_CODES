// S82 - Gökkuşağı

int ledler[] = {3, 4, 5, 6, 7};    // LED'lerin bağlandığı pin numaralarını tanımla
                                   // LED'ler 3,4,5,6,7 nolu dijital pinlere bağlandı 

void setup() {
    // For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for (int i = 0; i < 5; i++) {
        pinMode(ledler[i], OUTPUT);  // LED'in bağlandığı pini çıkış olarak ayarla
    } 
}

void loop() {
    // 1. Animasyon LED'leri sağdan sola doğru yak
    for (int i = 0; i < 5; i++) {   // for döngüsü kullanarak LED'leri 
        digitalWrite(ledler[i], HIGH);  // Tek tek yak 
        delay(350);                     // 350 ms bekle
    }
    for (int i = 0; i < 5; i++) {   // for döngüsü kullanarak LED'leri 
        digitalWrite(ledler[i], LOW);   // Tek tek yak
        delay(350);                     // 350 ms bekle
    }

    // 2. Animasyon LED'leri soldan sağa doğru yak 
    for (int i = 4; i >= 0; i--) {  // for döngüsü kullanarak LED'leri 
        digitalWrite(ledler[i], HIGH);  // Tek tek yak
        delay(350);                     // 350 ms bekle
    }
    for (int i = 4; i >= 0; i--) {  // for döngüsü kullanarak LED'leri 
        digitalWrite(ledler[i], LOW);   // Tek tek yak
        delay(350);                     // 350 ms bekle 
    }

    // 3. Animasyon LED'leri sağdan soldan gelerek ortada birleştir
    digitalWrite(ledler[4], HIGH);   // ledler[4] değişkenine karşılık gelen LEDi yak
    digitalWrite(ledler[0], HIGH);   // ledler[0] değişkenine karşılık gelen LEDi yak
    delay(350);
  
    digitalWrite(ledler[3], HIGH);   // ledler[3] değişkenine karşılık gelen LEDi yak
    digitalWrite(ledler[1], HIGH);   // ledler[1] değişkenine karşılık gelen LEDi yak 
    delay(350);
 
    digitalWrite(ledler[2], HIGH);   // ledler[2] değişkenine karşılık gelen LEDi yak 
    delay(350);
    
    // 4. Animasyon LED'lerin hepsini 3 kere yakıp söndür
    for (int i = 0; i < 3; i++) {   // 3 kere tekrarla 
        for (int j = 0; j < 5; j++) {
            digitalWrite(ledler[j], HIGH);  // LED'lerin hepsini yak 
        }
        delay(150);                        // 150 ms bekle 
        
        for (int j = 4; j >= 0; j--) {
            digitalWrite(ledler[j], LOW);   // LED'lerin hepsini söndür 
        }
        delay(150);                        // 150 ms bekle
    }
}
