// S30 - Yaya Geçidi

// Trafik ışığı modülünün bağlandığı pin numaralarını tanımla
int kirmiziPin = 4;    // Kırmızı LED'in bağlandığı pin numarasını tanımla
int sariPin = 3;       // Sarı LED'in bağlandığı pin numarasını tanımla  

int yesilPin = 2;      // Yeşil LED'in bağlandığı pin numarasını tanımla

// Yaya Geçit ışığının bağlandığı pin numaralarını tanımla
int yayaKirmizi = 7;   // Yaya ışığı için kırmızı LED'in pin numarası tanımlandı 
int yayaYesil = 6;     // Yaya ışığı için yeşil LED'in pin numarası tanımlandı 

void setup() {
    // Trafik ışığı modülünün bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziPin, OUTPUT);    // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sariPin, OUTPUT);       // Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesilPin, OUTPUT);      // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    
    // Yaya geçit ışığının bağlandığı pinleri çıkış olarak ayarla
    pinMode(yayaKirmizi, OUTPUT);   // Yaya ışığı kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yayaYesil, OUTPUT);     // Yaya ışığı yeşil LED'in bağlandığı pini çıkış olarak ayarla  
}

void loop() {
    digitalWrite(kirmiziPin, HIGH);    // Araçlar için Kırmızı LED'i yak
    digitalWrite(yesilPin, LOW);       // Araçlar için Yeşil LED'i söndür
    digitalWrite(sariPin, LOW);        // Araçlar için Sarı LED'i söndür
    delay(2000);                       // 2 saniye bekle    
    
    digitalWrite(yayaYesil, HIGH);     // Yayalar için Yeşil LED'i yak
    digitalWrite(yayaKirmizi, LOW);    // Yayalar için Kırmızı LED'i söndür
    delay(10000);                      // 10 saniye bekle 
    
    digitalWrite(sariPin, HIGH);       // Araçlar için Sarı LED'i yak
    
    for (int i = 0; i < 5; i++) {
        digitalWrite(yayaYesil, LOW);      // Yayalar için Yeşil LED'i söndür
        digitalWrite(yayaKirmizi, LOW);    // Yayalar için Kırmızı LED'i söndür  
        delay(400);                        // 400 ms bekle 
        digitalWrite(yayaKirmizi, HIGH);   // Yayalar için Kırmızı LED'i yak
        delay(400);                        // 400 ms bekle 
    } 

    digitalWrite(yayaKirmizi, HIGH);    // Yayalar için Kırmızı LED'i yak
    digitalWrite(yayaYesil, LOW);       // Yayalar için Yeşil LED'i söndür
    delay(2000);                        // 2 saniye bekle
    
    digitalWrite(kirmiziPin, LOW);      // Araçlar için Kırmızı LED'i söndür  
    digitalWrite(sariPin, LOW);         // Araçlar için Sarı LED'i söndür
    digitalWrite(yesilPin, HIGH);       // Araçlar için Yeşil LED'i yak  
    delay(10000);                       // 10 saniye bekle
    
    digitalWrite(sariPin, HIGH);        // Araçlar için Sarı LED'i yak
    delay(2000);                        // 2 saniye bekle 
}
