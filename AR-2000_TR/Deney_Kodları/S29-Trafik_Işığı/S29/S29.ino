// S29 - Trafik Işığı

// Kırmızı LED'in bağlandığı pin numarasını tanımla
int kirmiziPin = 4;
// Sarı LED'in bağlandığı pin numarasını tanımla  
int sariPin = 3;
// Yeşil LED'in bağlandığı pin numarasını tanımla
int yesilPin = 2;

void setup() {
    // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(kirmiziPin, OUTPUT);
    // Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sariPin, OUTPUT);
    // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesilPin, OUTPUT);
}

void loop() {
    // Kırmızı LED'i yak
    digitalWrite(kirmiziPin, HIGH);
    delay(5000);                          // 5 saniye bekle
    
    // Sarı LED'i yak
    digitalWrite(sariPin, HIGH);
    delay(2000);                          // 2 saniye bekle
    
    // Kırmızı LED'i söndür
    digitalWrite(kirmiziPin, LOW);
    // Sarı LED'i söndür
    digitalWrite(sariPin, LOW);
    // Yeşil LED'i yak
    digitalWrite(yesilPin, HIGH);
    delay(5000);                          // 5 saniye bekle
    
    // Yeşil LED'i söndür ve Sarı LED'i yak
    digitalWrite(yesilPin, LOW);
    digitalWrite(sariPin, HIGH);
    delay(2000);                          // 2 saniye bekle
    
    // Yeşil LED'i söndür
    digitalWrite(yesilPin, LOW);
    // Sarı LED'i söndür  
    digitalWrite(sariPin, LOW);
}
