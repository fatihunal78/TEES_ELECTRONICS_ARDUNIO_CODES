// SA50 - Kırmızı şimşek (Ses efektli)

//LED'lerin bağlandığı pin numaralarını tanımla
int ledler[] = {4, 5, 6, 7, 8};
//Buton'un bağlandığı dijital pin numarasını tanımla
int butonPin = 2;
//LED'lerin gezinme hızı
int hiz = 120;
//Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 3;

void setup() {
    //For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for (int i = 0; i < 5; i++) {
        pinMode(ledler[i], OUTPUT);
    }
    //Buton'un bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
    //Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);
}

void loop() {
    //Buton durumunu kontrol et
    if (digitalRead(butonPin) == HIGH) {    //Butona basıldı ise
        //Tekrar sayısı
        for (int k = 0; k < 5; k++) {
            //LED'leri soldan sağa doğru sıra ile yak ve söndür
            //i değişkeni ile dizi olarak tanımlanan LED'ler sıra ile yakar ve söndürür
            for (int i = 0; i < 4; i++) {   // Changed to 4 to prevent array overflow
                digitalWrite(ledler[i], HIGH);     //Sıradaki LED'i yak
                digitalWrite(ledler[i + 1], HIGH); //Sıradaki LED'i yak
                tone(hoparlorPin, (i + 1) * 150);
                delay(hiz);                       //hiz değerine göre bekle
                digitalWrite(ledler[i], LOW);     //Sıradaki LED'i söndür
                noTone(hoparlorPin);
            }
            
            //LED'leri sağdan sola doğru sıra ile yak ve söndür
            //j değişkeni ile dizi olarak tanımlanan LED'ler sıra ile yakar ve söndürür
            for (int j = 4; j > 0; j--) {    // Changed to prevent array overflow
                digitalWrite(ledler[j], HIGH);     //Sıradaki LED'i yak
                digitalWrite(ledler[j - 1], HIGH); //Sıradaki LED'i yak
                tone(hoparlorPin, (6 - j) * 150);
                delay(hiz);                       //hiz değerine göre bekle
                digitalWrite(ledler[j], LOW);     //Sıradaki LED'i söndür
                noTone(hoparlorPin);
            }
        }
    }
}
