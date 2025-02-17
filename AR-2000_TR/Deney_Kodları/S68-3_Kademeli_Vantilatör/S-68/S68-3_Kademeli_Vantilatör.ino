// S68 - 3 Kademeli Vantilatör

// Motoru süren transistörün bağlandığı pin numarasını tanımla
int motorPin = 6;

// Kademe butonunun bağlandığı pin numarasını tanımla
int kademeButonPin = 2;

// Kademe durumunun tutulacağı değişkeni tanımla
int kademeDurumu = 0;

void setup() {
    // Motoru süren transistörün bağlandığı pini çıkış olarak ayarla
    pinMode(motorPin, OUTPUT);
    
    // Kademe butonunun bağlandığı pini giriş olarak ayarla
    pinMode(kademeButonPin, INPUT);

    // Butonun bağlandığı pini İnterrupt (kesme) olarak ayarla
    // Butona basıldığında butonKontrol fonksiyonundaki işlemi yap
    // RISING(Yükselen kenar) da tetikleme yap
    attachInterrupt(digitalPinToInterrupt(kademeButonPin), butonKontrol, RISING);
}

void loop() {
    if (kademeDurumu == 0) {          // Eğer kademeDurumu değişkeni 0 ise 
        analogWrite(motorPin, 0);      // Motoru durdur
    }
    else if (kademeDurumu == 1) {     // Eğer kademeDurumu değişkeni 1 ise 
        analogWrite(motorPin, 255);    // Motoru tam hız döndür (1.kademe)
    }
    else if (kademeDurumu == 2) {     // Eğer kademeDurumu değişkeni 2 ise 
        analogWrite(motorPin, 155);    // Motorun hızını azalt (2.kademe)
    }
    else if (kademeDurumu == 3) {     // Eğer kademeDurumu değişkeni 3 ise 
        analogWrite(motorPin, 75);     // Motorun hızını biraz daha azalt (3.kademe)
    }
}

// Butonun basılıp basılmadığını kontrol etmek için butonKontrol fonksiyonu oluştur
// Bu fonksiyon ile for döngülerinin içinde butona basılıp basılmadığını kontrol edilecek
void butonKontrol() {
    static unsigned long son_kesme_zamani = 0;    // son_kesme_zamani isimli değişken oluştur ve ilk değerini 0 yap
    unsigned long kesme_zamani = millis();        // kesme_zamani isimli bir değişken oluştur ve millis() komutu ile 
                                                 // sistemin başlangıç zamanını ata
    
    // Eğer kesme_zamani ile son_kesme_zamani arasındaki fark 500ms 'den büyük ise
    // Bu işlem butona birden fazla kez basıldığını algılamayı önlemek amaçlı kullanılmıştır.
    if (kesme_zamani - son_kesme_zamani > 500) {
        kademeDurumu++;                          // kademeDurumu değişkenini arttır
        
        if (kademeDurumu > 3) {                 // Eğer kademeDurumu değişkeni 3 den büyük ise
            kademeDurumu = 0;                   // kademeDurumu değişkeninin değerini 0 yap
        }
    }
    son_kesme_zamani = kesme_zamani;           // son_kesme_zamani değişkenine kesme_zamani değişkenindeki değeri ata
}
