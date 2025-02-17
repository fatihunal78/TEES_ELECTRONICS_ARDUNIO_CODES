// S41 - Yalan dedektörü

int kirmiziLed = 2;    // Kırmızı LED'in bağlandığı pini tanımla
int buzzerPin = 4;     // Buzzer'ın bağlandığı pini tanımla  
int sensorPin = A5;    // Kuvvet ölçümü için sensörün bağlandığı pini tanımla

int sensorDegeri;      // Prob uçlarından okunan verilerin kaydedileceği değişkeni tanımla
int okunanDeger;       // Kalibrasyon işleminin tutulacağı değişkeni tanımla 
int toplam = 0;        // Kalibrasyon işleminde değerlerin toplamının tutulacağı değişkeni tanımla ve başlangıç değerini 
                       // sıfır olarak ayarla

void setup() { 
    pinMode(sensorPin, INPUT);     // Kuvvet ölçümü için sensörün bağlandığı A5 pinini giriş olarak ayarla
    pinMode(kirmiziLed, OUTPUT);   // Kırmızı LED pinini çıkış olarak ayarla
    pinMode(buzzerPin, OUTPUT);    // Buzzer pinini çıkış olarak ayarla

    // Kalibrasyon ayarı
    for (int i = 0; i < 10; i++) {    // for döngüsü ile 10 farklı değer al  
        okunanDeger = analogRead(sensorPin);   // Sensör pinine bağlı problardan analog değer oku
        toplam = toplam + okunanDeger;         // Okunan analog değeri bir önceki değer ile topla 
        delay(100);                            // 100 ms bekle 
    }
    toplam = toplam / 10;                      // Analog pinden okunan değerlerin ortalamasını al
}
  
void loop() {
    sensorDegeri = analogRead(sensorPin);      // Analog pindeki değeri oku ve sensorDegeri değişkenine kaydet 
    
    if (sensorDegeri > okunanDeger + 10) {     // Eğer sensör değeri, başlangıçta yaptığımız kalibrasyon değerinden 10 değer 
                                               // büyük ise, yani yalan söylüyor ise 
        digitalWrite(buzzerPin, HIGH);          // Buzzer'dan ses çıkar
        digitalWrite(kirmiziLed, HIGH);         // Kırmızı LED'i yak 
        delay(1000);                           // 1 saniye bekle 
    }
    else {                                     // Eğer değilse 
        digitalWrite(buzzerPin, LOW);          // Buzzer'ı sustur 
        digitalWrite(kirmiziLed, LOW);         // Kırmızı LED'i söndür
    }  
    delay(50);                                 // 50 ms bekle
}
