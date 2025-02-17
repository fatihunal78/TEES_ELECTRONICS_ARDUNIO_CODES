// S87 - Deprem Alarmı

int butonPin = 2;     // Butonun bağlandığı pin numarasını tanımla
int sensorPin = 3;    // Deprem sensörünün bağlandığı pin numarasını tanımla
int hoparlorPin = 4;  // Hoparlörün bağlandığı pin numarasını tanımla

int ledPin = 7;       // LED'in bağlandığı pin numarasını tanımla
int LEDdurumu = 0;    // LED durumunun tutulacağı değişkeni tanımla

// Zaman değerlerinin tutulacağı değişkenleri tanımla
unsigned long eskiZaman = 0;
unsigned long yeniZaman;

void setup() {
    pinMode(butonPin, INPUT_PULLUP);    // Butonun bağlandığı pini giriş olarak ayarla
    pinMode(sensorPin, INPUT_PULLUP);   // Sensörün bağlandığı pini giriş olarak ayarla
    pinMode(hoparlorPin, OUTPUT);       // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(ledPin, OUTPUT);            // LED'in bağlandığı pini çıkış olarak ayarla
}

void loop() {
    if (digitalRead(sensorPin) == LOW) {  // Eğer sensör pininden HIGH değeri algılandı ise, deprem oluyorsa
        while (1) {                        // Sonsuz döngüye gir
            // Arduinonun çalışma süresini milisaniye cinsinden kaydet
            yeniZaman = millis();

            if (yeniZaman - eskiZaman > 500) {  // Yarım saniyelik aralıklar ile LED'i yakıp söndür
                if (LEDdurumu == 1) {           // Eğer led yanıyor ise
                    digitalWrite(ledPin, LOW);   // LED'i söndür
                    LEDdurumu = 0;              // LEDdurumu değişkenine LED durumunu sönük olarak kaydet
                } else {                        // LED sönük ise
                    digitalWrite(ledPin, HIGH);  // Ledi yak
                    LEDdurumu = 1;              // Led durumunu yanık olarak kaydet
                }
                // Eski zaman değerini yeni zaman değeri ile güncelle
                eskiZaman = yeniZaman;
            }

            tone(hoparlorPin, 350);      // Hoparlörden ses çıkar
            delay(300);                  // 300ms bekle
            noTone(hoparlorPin);         // Hoparlörü sustur
            delay(80);                   // 80 ms bekle

            if (digitalRead(butonPin) == LOW) {  // Eğer butona basıldı
                noTone(hoparlorPin);             // Hoparlörü sustur
                digitalWrite(ledPin, LOW);        // LED'i söndür
                break;                           // Sonsuz döngüden çık
            }
        }
    }
}