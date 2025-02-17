// S95 - Renk Ayrımı

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int RGB_Kirmizi = 6;
int RGB_Yesil = 5;
int RGB_Mavi = 3;
int Kirmizi_Led = 11;
int Yesil_Led = 10;
int Mavi_Led = 9;

int potPin = A0;    // Potansiyometrenin bağlandığı pin numarasını tanımla
int potDegeri = 0;  // Potansiyometre değerinin kaydedileceği değişkeni tanımla

void setup() {
    // RGB LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(RGB_Kirmizi, OUTPUT);
    pinMode(RGB_Yesil, OUTPUT);
    pinMode(RGB_Mavi, OUTPUT);

    // LED Modüllerinin bağlandığı pinleri çıkış olarak ayarla
    pinMode(Kirmizi_Led, OUTPUT);
    pinMode(Yesil_Led, OUTPUT);
    pinMode(Mavi_Led, OUTPUT);

    // Başlangıçta LED'lerin hepsini söndür
    analogWrite(RGB_Kirmizi, 255);
    analogWrite(RGB_Yesil, 255);
    analogWrite(RGB_Mavi, 255);

    analogWrite(Kirmizi_Led, 0);
    analogWrite(Yesil_Led, 0);
    analogWrite(Mavi_Led, 0);
}

void loop() {
    // Potansiyometrenin değerini oku ve potDurumu değişkenine ata
    potDegeri = analogRead(potPin);

    // Eğer potansiyometreden okunan değer 0 ile 150 arasında ise Kırmızı LED'i yak
    if (potDegeri >= 0 && potDegeri < 150) {
        // Potansiyometre değerine göre RGB modüldeki Kırmızı LED'i yak
        analogWrite(RGB_Kirmizi, 255 - potDegeri);
        analogWrite(RGB_Yesil, 255);
        analogWrite(RGB_Mavi, 255);

        // Potansiyometre değerine göre Kırmızı LED modülü yak
        analogWrite(Kirmizi_Led, potDegeri);
        analogWrite(Yesil_Led, 0);
        analogWrite(Mavi_Led, 0);
    }
    // Eğer potansiyometreden okunan değer 150 ile 300 arasında ise Yeşil LED'i yak
    else if (potDegeri >= 150 && potDegeri < 300) {
        int oranla = map(potDegeri, 150, 300, 0, 255);  // LED'lerin PWM ile ayarlanabileceği maksimum 255 değerine oranla

        // Potansiyometre değerine göre RGB modüldeki Yeşil LED'i yak
        analogWrite(RGB_Kirmizi, 255);
        analogWrite(RGB_Yesil, 255 - oranla);
        analogWrite(RGB_Mavi, 255);

        // Potansiyometre değerine göre Yeşil LED modülü yak
        analogWrite(Kirmizi_Led, 0);
        analogWrite(Yesil_Led, oranla);
        analogWrite(Mavi_Led, 0);
    }
    // Eğer potansiyometreden okunan değer 300 ile 450 arasında ise Mavi LED'i yak
    else if (potDegeri >= 300 && potDegeri < 450) {
        int oranla = map(potDegeri, 300, 450, 0, 255);  // LED'lerin PWM ile ayarlanabileceği maksimum 255 değerine oranla

        // Potansiyometre değerine göre RGB modüldeki Mavi LED'i yak
        analogWrite(RGB_Kirmizi, 255);
        analogWrite(RGB_Yesil, 255);
        analogWrite(RGB_Mavi, 255 - oranla);

        // Potansiyometre değerine göre Mavi LED modülü yak
        analogWrite(Kirmizi_Led, 0);
        analogWrite(Yesil_Led, 0);
        analogWrite(Mavi_Led, oranla);
    }
    // Eğer potansiyometreden okunan değer 450 ile 600 arasında ise Eflatun rengini LED'ler ile yak
    else if (potDegeri >= 450 && potDegeri < 600) {
        int oranla = map(potDegeri, 450, 600, 0, 255);  // LED'lerin PWM ile ayarlanabileceği maksimum 255 değerine oranla

        // Potansiyometre değerine göre RGB modüldeki Kırmızı ve Mavi renk LED'ler ile eflatun rengini ayarla
        analogWrite(RGB_Kirmizi, 255 - oranla);
        analogWrite(RGB_Yesil, 255);
        analogWrite(RGB_Mavi, 255 - oranla);

        // Potansiyometre değerine göre Kırmızı ve Mavi LED modülüleri ile eflatun rengini ayarla
        analogWrite(Kirmizi_Led, oranla);
        analogWrite(Yesil_Led, 0);
        analogWrite(Mavi_Led, oranla);
    }
    // Eğer potansiyometreden okunan değer 600 ile 750 arasında ise Sarı rengini LED'ler ile yak
    else if (potDegeri >= 600 && potDegeri < 750) {
        int oranla = map(potDegeri, 600, 750, 0, 255);  // LED'lerin PWM ile ayarlanabileceği maksimum 255 değerine oranla

        // Potansiyometre değerine göre RGB modüldeki Kırmızı ve Yeşil renk LED'ler ile sarı rengi ayarla
        analogWrite(RGB_Kirmizi, 255 - oranla);
        analogWrite(RGB_Yesil, 255 - oranla);
        analogWrite(RGB_Mavi, 255);

        // Potansiyometre değerine göre Kırmızı ve Yeşil LED modülüleri ile sarı rengi ayarla
        analogWrite(Kirmizi_Led, oranla);
        analogWrite(Yesil_Led, oranla);
        analogWrite(Mavi_Led, 0);
    }
    // Eğer potansiyometreden okunan değer 750 ile 900 arasında ise Cyan(Camgöbeği) rengini LED'ler ile yak
    else if (potDegeri >= 750 && potDegeri < 900) {
        int oranla = map(potDegeri, 750, 900, 0, 255);  // LED'lerin PWM ile ayarlanabileceği maksimum 255 değerine oranla

        // Potansiyometre değerine göre RGB modüldeki Yeşil ve Mavi renk LED'ler ile cyan rengini ayarla
        analogWrite(RGB_Kirmizi, 255);
        analogWrite(RGB_Yesil, 255 - oranla);
        analogWrite(RGB_Mavi, 255 - oranla);

        // Potansiyometre değerine göre Yeşil ve Mavi LED modülüleri ile cyan rengini ayarla
        analogWrite(Kirmizi_Led, 0);
        analogWrite(Yesil_Led, oranla);
        analogWrite(Mavi_Led, oranla);
    }
    // Eğer potansiyometreden okunan değer 900'den büyük ise Beyaz rengi LED'ler ile yak
    else if (potDegeri >= 900) {
        // Potansiyometre değerine göre RGB modüldeki Kırmızı, Yeşil ve Mavi renk LED'ler ile beyaz rengi ayarla
        analogWrite(RGB_Kirmizi, 255 - potDegeri + 900);
        analogWrite(RGB_Yesil, 255 - potDegeri + 900);
        analogWrite(RGB_Mavi, 255 - potDegeri + 900);

        // Potansiyometre değerine göre Kırmızı, Yeşil ve Mavi LED modülüleri ile beyaz rengi ayarla
        analogWrite(Kirmizi_Led, potDegeri - 900);
        analogWrite(Yesil_Led, potDegeri - 900);
        analogWrite(Mavi_Led, potDegeri - 900);
    }
}
