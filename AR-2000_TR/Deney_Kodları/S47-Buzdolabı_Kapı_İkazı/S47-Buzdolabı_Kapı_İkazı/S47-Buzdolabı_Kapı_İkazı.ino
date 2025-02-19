// S47 - Buzdolabı Kapı İkazı

int hoparlorPin = 3;    // Hoparlörün bağlandığı pin numarasını tanımla
int ldrPin = A5;        // LDR'nin bağlandığı pin numarasını tanımla  
int ledPin = 2;         // LED'in bağlandığı pin numarasını tanımla
int okunandeger = 0;    // LDR'den okunan değerin tutulacağı değişkeni tanımla
int ortalamadeger = 0;  // Ortalama değerin tutulacağı değişkeni tanımla
unsigned long zaman = 0; // Zamanın tutulacağı değişkeni tanımla

void setup() {
    pinMode(hoparlorPin, OUTPUT); // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(ldrPin, INPUT);       // LDR'nin bağlandığı pini giriş olarak ayarla
    pinMode(ledPin, OUTPUT);      // LED'in bağlandığı pini çıkış olarak ayarla

    // Kalibrasyon için 10 farklı değer oku
    for (int i = 0; i < 10; i++) { // 10 farklı değer için for döngüsü
        ortalamadeger = ortalamadeger + analogRead(ldrPin); // Değerleri oku ve değerlerin toplamını ortalamadeger 
                                                           // değişkenine kaydet
    }
    ortalamadeger = ortalamadeger / 10; // Değerlerin ortalamasını bulmak için ortalamadeger değişkenindeki toplamı 
                                        // 10 ile böl
}

void loop() {
    okunandeger = analogRead(ldrPin); // LDR'den değeri oku

    // Eğer okunandeger değişkeni ortalamadeger değişkeninin içindeki değerden 100 fazla ise
    // Bu durumda buzdolabınız açılmış ve yanan ışık LDR değerini arttırmış olur.
    if (okunandeger > ortalamadeger + 100) {
        delay(10);   // 10 ms bekle
        zaman += 10; // zaman değişkenini 10'ar arttır

        // Eğer zaman değişkeni 10000'den büyük ise, yani dolabın kapağı 10 saniye boyunca açık kaldı ise
        if (zaman >= 10000) {
            tone(hoparlorPin, 1000);    // Hoparlörden ses çal
            digitalWrite(ledPin, HIGH);  // LED'i yak
            delay(250);                  // 250 ms bekle
            digitalWrite(ledPin, LOW);   // LED'i söndür
            noTone(hoparlorPin);        // Hoparlörü sustur
            delay(250);                  // 250 ms bekle
        }
    }
    else { // Eğer kapak kapatıldı ise
        zaman = 0;                // zaman değişkenini sıfırla
        noTone(hoparlorPin);      // Hoparlörü sustur
        digitalWrite(ledPin, LOW); // LED'i söndür
    }
}
