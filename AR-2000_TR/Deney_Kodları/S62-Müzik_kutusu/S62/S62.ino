// S62 - Müzik Kutusu

// NOTALARA KARŞILIK GELEN FREKANS DEĞERLERİ
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int hoparlorPin = 6;     // Hoparlörün bağlandığı pin numarasını tanımla
int KirmiziLed = 10;     // Kırmızı LED'in bağlandığı pin numarasını tanımla
int YesilLed = 8;        // Yeşil LED'in bağlandığı pin numarasını tanımla
int SariLed = 9;         // Sarı LED'in bağlandığı pin numarasını tanımla
int butonPin = 2;        // Butonun bağlandığı pin numarasını tanımla
int butondurumu;         // Buton durumunun tutulacağı değişkeni tanımla
int sayac = 0;

int dogum_gunu_uzunluk = 28;    // Mutlu yıllar (happy birthday) müziğinin notalarının uzunluğu
int yilbasiUzunluk = 26;        // Yılbaşı (jingle bells) müziğinin notalarının uzunluğu

char yilbasiNotalar[] = "eeeeeeegcde fffffeeeeddedg";
char dogum_gunu_notalar[] = "GGAGcB GGAGdc GGxecBA yyecdc";

int dogum_gunu_vuruslar[] = {
    2, 2, 8, 8, 8, 16, 1,
    2, 2, 8, 8, 8, 16, 1,
    2, 2, 8, 8, 8, 8, 16,
    1, 2, 2, 8, 8, 8, 16
}; 

int yilbasiVuruslar[] = {
    1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2
};

int yilbasidogum_gunu_tempo = 200;    // Yılbası müziğinin çalma hızı
int dogum_gunu_tempo = 185;           // Doğum günü müziğini çalma hızı

// TÜRK MARŞI (MOZART TURKISH MARCH) İÇİN GEREKLİ NOTALAR 
int melodiler[] = {
    NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_C5, 
    NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_E5,
    NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5, 
    NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_C6,
    NOTE_A5, NOTE_C6, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5,
    NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_E5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_E5,
    NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
    NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_C5, 
    NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_E5,
    NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5, 
    NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_C6,
    NOTE_A5, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_A4,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_GS5, NOTE_E5,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_B5, NOTE_GS5, NOTE_E5, NOTE_A5,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_GS5, NOTE_E5,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_B5, NOTE_GS5, NOTE_E5, NOTE_A5
};

// MOZART TURK MARŞI NOTALARINA KARŞILIK GELEN DURAKLAMALAR
int Turk_marsi_nota_sureleri[] = {
    8, 8, 8, 8, 2, 
    8, 8, 8, 8, 2, 
    8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 2,
    4, 4, 16, 16, 16, 4,
    4, 4, 16, 16, 16, 4, 4, 4, 16, 16, 16, 4, 4, 4, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    8, 8, 8, 8, 2, 
    8, 8, 8, 8, 2, 
    8, 8, 8, 8, 
    8, 8, 8, 8, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 8, 8, 2,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2
};

void yilbasi_NotaCal(char nota, int yilbasi_sure) {
    char notaIsim[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
    int tonlar[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};    // Notalara karşılık gelen frekans değerleri
    
    for (int i = 0; i < 8; i++) {
        if (notaIsim[i] == nota) {
            for (long j = 0; j < yilbasi_sure * 1300L; j += tonlar[i] * 2) {
                digitalWrite(hoparlorPin, HIGH);
                delayMicroseconds(tonlar[i]);
                digitalWrite(hoparlorPin, LOW);
                delayMicroseconds(tonlar[i]);
            }
        }
    }
}

void dogum_gunu_TonCal(int tone, int dogum_gunu_sure) {
    for (long i = 0; i < dogum_gunu_sure * 1000L; i += tone * 2) {
        digitalWrite(hoparlorPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(hoparlorPin, LOW);
        delayMicroseconds(tone);
    }
}

void dogum_gunu_NotaCal(char note, int dogum_gunu_sure) {
    char dogum_gunu_notalar[] = {
        'C', 'D', 'E', 'F', 'G', 'A', 'B',           
        'c', 'd', 'e', 'f', 'g', 'a', 'b',
        'x', 'y'
    };
  
    int dogum_gunu_tonlar[] = {
        1915, 1700, 1519, 1432, 1275, 1136, 1014,
        956,  834,  765,  593,  468,  346,  224,
        655,  715
    };

    for (int i = 0; i < 17; i++) {
        if (dogum_gunu_notalar[i] == note) {
            int newdogum_gunu_sure = dogum_gunu_sure / 5;
            dogum_gunu_TonCal(dogum_gunu_tonlar[i], newdogum_gunu_sure);
        }
    }
}

void setup() {
    // LED'leri ile hoparlörü çıkış olarak, butonu giriş olarak ayarla
    pinMode(KirmiziLed, OUTPUT);
    pinMode(YesilLed, OUTPUT);
    pinMode(SariLed, OUTPUT);
    pinMode(butonPin, INPUT);
    pinMode(hoparlorPin, OUTPUT);
}

void loop() {
    butondurumu = digitalRead(butonPin);    // Butonun değerinin butondurumu değişkenine yaz
    if (butondurumu == HIGH) {              // Eğer butondurumu=1 ise yani butona basılmış ise
        sayac++;                            // Sayac değişkenini 1 arttır
        delay(500);
        if (sayac > 3) {
            sayac = 0;                      // Eğer sayaç değişkeni 3 den büyük ise sayac değerini sıfır yap
        }
    }

    switch (sayac) {                        // Sayaç değiskeninin değerine göre 'case' lere git
        case 0:                             // Eğer sayaç değişkeni sıfır (0) ise
            // Bütün LED'leri söndür ve hoparlörü sustur
            digitalWrite(KirmiziLed, LOW);
            digitalWrite(SariLed, LOW);
            digitalWrite(YesilLed, LOW);
            digitalWrite(hoparlorPin, LOW);
            break;

        case 1:                             // Eğer sayaç değişkeni 1 ise
            // Kırmızı LED'i yak ve doğum günü müziğini çal
            digitalWrite(KirmiziLed, HIGH);
            digitalWrite(SariLed, LOW);
            digitalWrite(YesilLed, LOW);
            
            for (int i = 0; i < dogum_gunu_uzunluk; i++) {
                butondurumu = digitalRead(butonPin);    // Buton değerini oku
                if (butondurumu == HIGH) {              // Butona basılıp basılmadığını kontrol et 
                    sayac = 2;                          // Eğer butona basılmışsa diğer duruma (case)'e geç
                    delay(500);                         // Sayacı 2 yap
                    break;
                } 
                
                if (dogum_gunu_notalar[i] == ' ') {
                    delay(dogum_gunu_vuruslar[i] * dogum_gunu_tempo);    // Rest
                } else {
                    dogum_gunu_NotaCal(dogum_gunu_notalar[i], dogum_gunu_vuruslar[i] * dogum_gunu_tempo);
                }
                delay(dogum_gunu_tempo);    // Notalar arası bekleme
            }
            break;

        case 2:                             // Eğer sayaç değişkeni 2 ise 
            // Sarı LED'i yak ve yılbaşı müziğini çal
            digitalWrite(KirmiziLed, LOW);
            digitalWrite(SariLed, HIGH);
            digitalWrite(YesilLed, LOW);
            
            for (int i = 0; i < yilbasiUzunluk; i++) {  
                butondurumu = digitalRead(butonPin);    // Buton değerini oku ve butondurumu değişkenine yaz
                if (butondurumu == HIGH) {              // Butona basılıp basılmadığını kontrol et 
                    sayac = 3;                          // Eğer butona basılmışsa diğer duruma (case)'e geç
                    delay(500);                         // Sayacı 3 yap
                    break;
                } 
                
                if (yilbasiNotalar[i] == ' ') {     
                    delay(yilbasiVuruslar[i] * yilbasidogum_gunu_tempo / 4);
                } else {
                    yilbasi_NotaCal(yilbasiNotalar[i], yilbasiVuruslar[i] * yilbasidogum_gunu_tempo);
                }
            }
            break;

        case 3:                             // Eğer sayaç değikeni 3 ise 
            // Yeşil LED'i yak ve Türk marşı müziğini çal
            digitalWrite(KirmiziLed, LOW);
            digitalWrite(SariLed, LOW);
            digitalWrite(YesilLed, HIGH);
             
            for (int thisNote = 0; thisNote < 178; thisNote++) {
                butondurumu = digitalRead(butonPin);    // Buton değerini oku  
                if (butondurumu == HIGH) {              // Butona basılıp basılmadığını kontrol et 
                    sayac = 0;                          // Eğer butona basılmışsa diğer duruma (case)'e geç
                    delay(500);                         // Sayacı 0 yap
                    break;
                } 
                
                int noteDuration = 1000 / Turk_marsi_nota_sureleri[thisNote];
                tone(hoparlorPin, melodiler[thisNote], noteDuration);
                int pauseBetweenNotes = noteDuration * 1.30;
                delay(pauseBetweenNotes);
            }
            break;
    }
}