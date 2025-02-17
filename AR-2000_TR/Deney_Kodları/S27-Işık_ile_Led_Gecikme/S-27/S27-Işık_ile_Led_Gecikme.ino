// S27 - Işık ile Led Gecikme

// LED'lerin bağlandığı pinleri tanımla
int KirmiziLed = 3;
int YesilLed = 4;
int SariLed = 5;

// LDR'nin bağlandığı pini tanımla
int ldrPin = A0;

int okunanDeger;    // LDR'den okunan değeri atayacağımız değişkeni tanımla
int oranla;         // map fonksiyonu ile oranlayacağımız değeri atayacağımız değişkeni tanımla

void setup() {
    // LED pinlerini çıkış olarak ayarla
    pinMode(KirmiziLed, OUTPUT);
    pinMode(SariLed, OUTPUT);
    pinMode(YesilLed, OUTPUT);
}

void loop() {
    okunanDeger = analogRead(ldrPin);                    // LDR'den okunan değeri okunanDeger değişkenine ata
    oranla = map(okunanDeger, 0, 1023, 0, 1000);        // Okunan değeri 0 ile 1000 arasına oranlayıp, oranla değişkenine ata
    
    digitalWrite(KirmiziLed, HIGH);                      // Kırmızı LED'i yak
    delay(oranla);                                       // oranla değişkeni kadar bekle
    digitalWrite(KirmiziLed, LOW);                       // Kırmızı LED'i söndür
    
    digitalWrite(SariLed, HIGH);                         // Sarı LED'i yak
    delay(oranla);                                       // oranla değişkeni kadar bekle
    digitalWrite(SariLed, LOW);                          // Sarı LED'i söndür
    
    digitalWrite(YesilLed, HIGH);                        // Yeşil LED'i yak
    delay(oranla);                                       // oranla değişkeni kadar bekle
    digitalWrite(YesilLed, LOW);                         // Yeşil LED'i söndür
}
