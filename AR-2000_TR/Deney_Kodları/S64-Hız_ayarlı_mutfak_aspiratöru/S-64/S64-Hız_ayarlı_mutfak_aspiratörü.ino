// S64 - Hız ayarlı mutfak aspiratörü

// Motoru süren transistörün bağlandığı pin numarasını tanımla
int motorPin = 3;

// Potansiyometrenin bağlandığı pin numarasını tanımla
int potansiyometrePin = A0;

// Hız durumunun tutulacağı değişkeni tanımla
int hizDurumu = 0;

// Aspiratör durumunun tutulacağı değişkeni tanımla
int aspiratorDurumu = 0;

void setup() {
    // Transistörün bağlandığı pini çıkış olarak ayarla
    pinMode(motorPin, OUTPUT);
    
    // Potansiyometrenin bağlandığı pini giriş olarak ayarla
    pinMode(potansiyometrePin, INPUT);
}

void loop() {
    // Potansiyometre durumunu kontrol et
    hizDurumu = analogRead(potansiyometrePin);
    
    // Potansiyometreden okunan değeri motorun hızına göre oranla
    hizDurumu = map(hizDurumu, 0, 1023, 100, 255);

    if (aspiratorDurumu == 0) {  // Aspiratör çalışmıyorsa
        if (hizDurumu > 104) {
            // Motorun hızlanabilmesi için motor hızını maksimum güce ayarla
            analogWrite(motorPin, 255);
            delay(50);            // 50ms bekle
            
            // Motorun hızını belirlenen hiz değerine göre ayarla
            analogWrite(motorPin, hizDurumu);
            aspiratorDurumu = 1;  // Aspiratör açık olarak kaydet
        }
    }
    else {                       // Aspiratör çalışıyorsa
        if (hizDurumu < 105) {   // hizDurumu 105'den küçük ise
            // Motoru kapat
            analogWrite(motorPin, 0);
            aspiratorDurumu = 0;  // Aspiratör kapalı olarak kaydet
        }
        else {
            // Motorun hızını belirlenen hiz değerine göre ayarla
            analogWrite(motorPin, hizDurumu);
        }
        delay(50);               // 50ms bekle
    }
}
