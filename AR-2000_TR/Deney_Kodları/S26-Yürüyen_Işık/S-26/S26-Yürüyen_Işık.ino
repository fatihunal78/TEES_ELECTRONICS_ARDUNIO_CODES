// S26 - Yürüyen Işık

// LED'lerin bağlandığı pin numaralarını tanımla
int ledler[] = {3, 4, 5, 6, 7};

// LED'lerin gezinme hızı
int hiz;

// Potansiyometrenin bağlandığı pin
int potPin = A0;

// Potansiyometreden okunan değer
int potdegeri;

// Pot'dan okunan değerin delay'a (gecikmeye) dönüştüreceğimiz değişken  
int oranla;

void setup() {
    // For döngüsü ile LED'lerin bağlandığı pinleri çıkış olarak ayarla
    for(int i = 0; i < 5; i++) {
        pinMode(ledler[i], OUTPUT);
    }
}

void loop() {
    // Analog 0 pinindeki değeri oku ve potdegeri değişkenine kaydet
    potdegeri = analogRead(potPin);

    // potdegeri'ne kaydedilmiş değeri (bu değer 0 ile 1023 arasındadır çünkü potansiyometrenin sağ ve sol 
    // ucları + ve - ye bağlıdır) 20 ile 500 değerine çevir. (Bu değerler bizim gecikme yapacağımız değerler)
    // Yani okunan 1023 değer 500 ms'ye karşılık gelecek 0 değeri ise 20 ms'ye
    oranla = map(potdegeri, 0, 1023, 500, 20);

    // LED'leri soldan sağa doğru sıra ile yak ve söndür
    // i değişkeni ile dizi olarak tanımlanan LED'ler sıra ile yakar ve söndürür
    for(int i = 0; i < 5; i++) {
        digitalWrite(ledler[i], HIGH);    // Sıradaki LED'i yak
        delay(oranla);                    // oranla değerine göre bekle
        digitalWrite(ledler[i], LOW);     // Sıradaki LED'i söndür
    }

    // LED'leri sağdan sola doğru sıra ile yak ve söndür
    // j değişkeni ile dizi olarak tanımlanan LED'ler sıra ile yakar ve söndürür
    for(int j = 4; j > 0; j--) {
        digitalWrite(ledler[j], HIGH);    // Sıradaki LED'i yak
        delay(oranla);                    // oranla değerine göre bekle
        digitalWrite(ledler[j], LOW);     // Sıradaki LED'i söndür
    }
}
