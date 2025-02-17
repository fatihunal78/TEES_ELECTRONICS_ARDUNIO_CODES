// S100 - Grafiksel Kullanıcı Arayüzü

// LED'lerin bağlandığı pin numaralarını tanımla
int rpin = 6;
int gpin = 5;
int bpin = 3;

float h = 0;             // Hue (ton) değerinin tutulacağı değişkeni tanımla
int red = 0,             // Renk değerlerinin tutulacağı değişkenleri tanımla
    green = 0,
    blue = 0;
int durum = 1;           // Switch case yapısı için durumun tutulacağı değişkeni tanımla
int gelen = 0;           // Processingten okunacak değerler için gelen verilerin tutulacağı değişkeni tanımla

void setup() {
    Serial.begin(9600);  // Processing ile haberleşme için seri iletişimi başlat
}

void loop() {
    while (Serial.available() > 0) {                    // Eğer seri haberleşme portundan gelen bilgi varsa
        gelen = Serial.read();                          // Gelen değişkenine seri porttan okunan değerleri kaydet
        switch (durum) {                                // Switch case yapısı ile
            case 1:                                     // Case durumu 1 olduğunda
                if (gelen == 'R') {                     // Eğer gelen değişkeni R ise
                    durum = 2;                          // Durum 2'ye geç
                }
                break;                                  // Case 1 durumunu bitir

            case 2:                                     // Case durumu 2 olduğunda
                red = gelen;                            // Red değişkenine gelen değeri kaydet
                durum = 3;                              // Durum 3'e geç
                break;                                  // Case 2 durumunu bitir

            case 3:                                     // Case durumu 3 olduğunda
                green = gelen;                          // Green değişkenine gelen değeri kaydet
                durum = 4;                              // Durum 4'e geç
                break;                                  // Case 3 durumunu bitir

            case 4:                                     // Case durumu 4 olduğunda
                blue = gelen;                           // Blue değişkenine gelen değeri kaydet
                durum = 1;                              // Durum 1'e geç
                break;                                  // Case 4 durumunu bitir
        }
    }

    // Ortak katot RGB LED için PWM sinyali kullanarak LED'leri yak
    analogWrite(rpin, 255 - red);                      // Kırmızı LED'i gelen değere göre yak
    analogWrite(gpin, 255 - green);                    // Yeşil LED'i gelen değere göre yak
    analogWrite(bpin, 255 - blue);                     // Mavi LED'i gelen değere göre yak

    delay(20);                                         // 20 ms bekle
}
