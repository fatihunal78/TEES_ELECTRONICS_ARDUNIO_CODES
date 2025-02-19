// S59 - İğne iplik Oyunu (Süre Sınırlı)

int kirmizi_led = 3;    // Panel üzerindeki LED'in bağlandığı pin numarasını tanımla
int yesil_led = 7;      // Yeşil LED'in bağlandığı pin numarasını tanımla
int hoparlorPin = 5;    // Hoparlörün bağlandığı pin numarasını tanımla
int butonPin = 2;       // Butonun bağlandığı pin numarasını tanımla
int sensorPin = 4;      // 10K direnç üzerinden gelen bağlantıyı sensör pini olarak tanımla

int butonDegiskeni = 0;         // Butona kaç kere basıldığının değerini tutacağı değişkeni tanımla
unsigned long zaman;            // Zaman değerinin tutulacağı değişkeni tanımla
unsigned long baslangicZaman;   // Sistemin başladığı zamanı tutacak değişkeni tanımla

void setup() {
    pinMode(yesil_led, OUTPUT);         // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(kirmizi_led, OUTPUT);       // Panel üzerindeki LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);       // Hoparlörün bağlandığı pini çıkış olarak ayarla 
    pinMode(butonPin, INPUT_PULLUP);    // Butonun bağlandığı pini giriş olarak ayarla, pull up direncini aktif et
    pinMode(sensorPin, INPUT);          // Sensörün bağlandığı pini giriş olarak ayarla                      
}

void loop() {
    if (digitalRead(butonPin) == LOW) {     // Eğer butona basıldı ise 
        butonDegiskeni++;                   // Buton değişkeni değerini bir arttır
        zaman = 0;                          // Zaman değişkenini sıfırla
        while (digitalRead(butonPin) == LOW);    // Butona basılı olduğu sürece bekle
    }

    if (butonDegiskeni == 1) {             // Eğer butonDegiskeni 1 ise 
        digitalWrite(yesil_led, HIGH);      // Yeşil LED'i yak
        
        // Eğer prob ucu halkaya değmişse yani iğne iplik oyununu başaramamışsa veya zaman değeri 15000'den 
        // büyükse (15 saniye geçmişse). Yani sensorPin(4 nolu pin)'den HIGH değer gelmiş veya 15 saniyeden 
        // fazla geçmişse
        if (digitalRead(sensorPin) == HIGH || zaman > 15000) {
            while (1) {                         // Sonsuz döngüye gir 
                digitalWrite(kirmizi_led, HIGH); // Panel üzerindeki Kırmızı LED'i yak 
                tone(hoparlorPin, 200);         // Hoparlörden ses çıkar 
                if (digitalRead(butonPin) == LOW) 
                    break;                      // Eğer butona basıldı ise sonsuz döngüden çık
            }
        }
        zaman = zaman + 100;                   // Zaman değişkenini 100 arttır
    }
    else {                                     // Eğer butonDegiskeni 0 ise 
        digitalWrite(yesil_led, LOW);          // Yeşil LED'i söndür
        noTone(hoparlorPin);                   // Hoparlörü sustur 
        butonDegiskeni = 0;                    // butonDegiskeni değerini 0 yap
    }
  
    // Serbest mod ayarları 
    if (digitalRead(sensorPin) == HIGH) {      // Eğer sensörden okunan değer 1 ise yani iğne iplik birbirine değmiş ise  
        digitalWrite(kirmizi_led, HIGH);        // Panel üzerindeki Kırmızı LED'i yak 
        tone(hoparlorPin, 700);                // Hoparlörden ses çıkar 
    }
    else {
        digitalWrite(kirmizi_led, LOW);         // Kırmızı LED'i söndür 
        noTone(hoparlorPin);                   // Hoparlörü sustur 
    }
    delay(100);
}