// S69 - Refleks Oyunu
int ledler[] = {8, 9, 10, 11, 12};    // LED'lerin bağlandığı pinleri tanımla 
int butonPin = 2;                      // Butonun bağlandığı pini tanımla
int hoparlorPin = 3;                   // Hoparlörün bağlandığı pini tanımla 
 
int hedef = 2;                         // Hedeflenen sayıyı belirle
int karakter = 0;                      // Karakter değişkenini oluştur ve ilk değeri sıfır yap
int oyun_hizi = 750;                   // Oyun hızını belirten değişkeni tanımla 
boolean butonDurumu = 0;               // Buton durumunun tutulacağı değişkeni tanımla

int muzik[] = {                        // Oyun kazanıldığı zaman müzik efekti için notaları tanımla
    262, 196, 196, 220, 196, 0, 247, 262
};

int notaSureleri[] = {                 // Notalara karşılık gelen bekleme sürelerini tanımla
    4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
    for (int i = 0; i < 5; i++) {      // 5 tekrar for döngüsü ayarla
        pinMode(ledler[i], OUTPUT);     // LED'lerin bağlandığı pinleri çıkış pini olarak ayarla
    }
 
    pinMode(butonPin, INPUT_PULLUP);    // Butonun bağlandığı pini giriş pini olarak ayarla ve pull up direncini aktif et
    attachInterrupt(digitalPinToInterrupt(butonPin), butonKontrol, FALLING);  
                                        // Butonun bağlandığı pini İnterrupt (kesme) olarak ayarla
                                        // Butona basıldığında butonKontrol fonksiyonundaki işlemi yap
                                        // FALLING(Alçalan kenar) da tetikleme yap   
}

void loop() {
    karakter = random(0, 6);            // LED'lerin rastgele yanması için karakter değişkeninin içine rastgele sayılar ata
    digitalWrite(ledler[karakter], HIGH);// Bu rastgele sayıya karşılık gelen LED'i yak
    delay(oyun_hizi);                   // oyun_hizi değişkeni kadar bekle 
    digitalWrite(ledler[karakter], LOW); // LED'i söndür
    
    if (butonDurumu == 1) {
        if (karakter == hedef) {        // Eğer rastgele oluşturulan değer ile belirlenen hedef değeri eşit ise 
            kazandi();                   // Oyunu kazandığını belirten kazandi() fonksiyonunu çağır
        } else {                        // Eğer rastgele oluşturulan değer ile belirlenen hedef değeri eşit değil ise 
            kaybetti();                 // Oyunu kaybettiğini belirten kaybetti() fonksiyonunu çağır
        }
    }
}

void kazandi() {                        // kazandi fonksiyonunu oluştur 
    for (int i = 0; i < 8; i++) {      // 0 dan 8'e kadar for döngüsü ile 
        // LED'lerin hepsini yak 
        digitalWrite(ledler[0], HIGH);
        digitalWrite(ledler[1], HIGH);
        digitalWrite(ledler[2], HIGH);
        digitalWrite(ledler[3], HIGH);
        digitalWrite(ledler[4], HIGH);
   
        int notaSuresi = 1000/notaSureleri[i];  // notaSuresi değişkeni oluştur ve 1000 değerini (1 saniye) 
                                                // nota sürelerine böl 
        tone(hoparlorPin, muzik[i], notaSuresi);// Hoparlörden sırası ile notları çal 
    
        int notalarArasiBekleme = notaSuresi * 1.30;  // Notalar arasındaki bekleme sürelerini belirlemek için 
                                                      // notaSuresi değişkenini 1.30 değeri ile çarp
        delay(notalarArasiBekleme);                   // Hesaplanan notalarArasiBekleme kadar gecikme yap 
        noTone(hoparlorPin);                          // Hoparlörü sustur 
    }
    
    // Bütün LED'leri yak 
    digitalWrite(ledler[0], HIGH);
    digitalWrite(ledler[1], HIGH);
    digitalWrite(ledler[2], HIGH);
    digitalWrite(ledler[3], HIGH);
    digitalWrite(ledler[4], HIGH);
   
    delay(300);                         // 300 ms bekle

    // Bütün LED'leri söndür 
    digitalWrite(ledler[0], LOW);
    digitalWrite(ledler[1], LOW);
    digitalWrite(ledler[2], LOW);
    digitalWrite(ledler[3], LOW);
    digitalWrite(ledler[4], LOW);
   
    delay(300);                         // 300 ms bekle

    // Bütün LED'leri yak 
    digitalWrite(ledler[0], HIGH);
    digitalWrite(ledler[1], HIGH);
    digitalWrite(ledler[2], HIGH);
    digitalWrite(ledler[3], HIGH);
    digitalWrite(ledler[4], HIGH);
   
    delay(300);                         // 300 ms bekle

    // Bütün LED'leri söndür 
    digitalWrite(ledler[0], LOW);
    digitalWrite(ledler[1], LOW);
    digitalWrite(ledler[2], LOW);
    digitalWrite(ledler[3], LOW);
    digitalWrite(ledler[4], LOW);
    
    delay(300);
    butonDurumu = 0;                    // butonDurumu değişkenini 0 yap
    oyun_hizi = oyun_hizi - 75;         // Oyunun hızının artması için oyun_hizi değişkenini azalt
}

void kaybetti() {                       // kaybetti fonksiyonunu tanımla
    for (int j = 1; j < 4; j++) {      // 4 tekrar döngü ayarla
        tone(hoparlorPin, 100);         // Hoparlörden ses çıkar 
        delay(500);                     // 500 ms bekle  
        noTone(hoparlorPin);            // Hoparlörü sustur
    }
    butonDurumu = 0;                    // butonDurumu değişkenini 0 yap
    oyun_hizi = 750; 
}

void butonKontrol() {                   // Butonun basılıp basılmadığını kontrol etmek için butonKontrol fonksiyonu oluştur
                                        // Bu fonksiyon ile for döngülerinin içinde butona basılıp basılmadığını kontrol edilecek
    static unsigned long son_kesme_zamani = 0;  // son_kesme_zamani isimli değişken oluştur ve ilk değerini 0 yap
    unsigned long kesme_zamani = millis();      // kesme_zamani isimli bir değişken oluştur ve millis() komutu ile 
                                               // sistemin başlangıç zamanını ata
    
    if (kesme_zamani - son_kesme_zamani > 50) {// Eğer kesme_zamani ile son_kesme_zamani arasındaki fark 50ms 'den büyük ise
                                               // Bu işlem butona birden fazla kez basıldığını algılamayı önlemek amaçlı 
                                               // kullanılmıştır.
        butonDurumu = 1;                       // Butona basıldığı zaman butonDurumu değişkenini 1 yap
    }
   
    son_kesme_zamani = kesme_zamani;           // son_kesme_zamani değişkeninie kesme_zamani değişkenindeki değeri ata
}
