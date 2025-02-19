// S53 - Işık Seviyesine Göre Rengi Değişen Lamba

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int kirmiziLedPin = 6;                      // Kırmızı LED pin
int yesilLedPin = 5;                        // Yeşil LED pin
int maviLedPin = 3;                         // Mavi LED pin

// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 8;                        // Hoparlör pin

// LDR'nin bağlandığı analog pin numarasını tanımla
int LDRPin = A0;                            // LDR pin

// Işık değerinin tutulacağı değişkeni tanımla
int isik_degeri = 0;                        // Işık değeri

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziLedPin, OUTPUT); 
    pinMode(yesilLedPin, OUTPUT); 
    pinMode(maviLedPin, OUTPUT); 
    
    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);
    
    // Başlangıçta LED'lerin hepsini söndür
    digitalWrite(kirmiziLedPin, HIGH);
    digitalWrite(yesilLedPin, HIGH);
    digitalWrite(maviLedPin, HIGH);
}
 
void loop() {
    // Ölçülen ışık değerini analog pinden oku ve isik_değeri değişkenine ata
    isik_degeri = analogRead(LDRPin);
    delay(100);                             // 100ms bekle 
    
    // Işık değeri 0-1023 değerleri arasında okunur. Değer karanlıkta düşük, aydınlıkta yüksek olur. 
    // İsteğinize göre ışık seviyelerini değiştirebilirsiniz.
    if(isik_degeri < 300) {                 // Değer 300'den düşükse
        // LED'lerin hepsini yak
        digitalWrite(kirmiziLedPin, LOW);
        digitalWrite(yesilLedPin, LOW);
        digitalWrite(maviLedPin, LOW);
        
        // Işık değerine göre hoparlörden ton üret
        tone(hoparlorPin, isik_degeri);
        delay(100);                         // 100ms bekle 
    }
    else if(isik_degeri < 400) {           // Değer 400'den düşükse
        // Kırmızı LED'i yak, diğerlerini söndür
        digitalWrite(kirmiziLedPin, LOW);
        digitalWrite(yesilLedPin, HIGH);
        digitalWrite(maviLedPin, HIGH);
        
        // Işık değerine göre hoparlörden ton üret
        tone(hoparlorPin, isik_degeri);
        delay(100);                         // 100ms bekle 
    }
    else if(isik_degeri < 600) {           // Değer 600'den düşükse
        // Mavi LED'i yak, diğerlerini söndür
        digitalWrite(kirmiziLedPin, HIGH);
        digitalWrite(yesilLedPin, HIGH);
        digitalWrite(maviLedPin, LOW);
        
        // Işık değerine göre hoparlörden ton üret
        tone(hoparlorPin, isik_degeri);
        delay(100);                         // 100ms bekle 
    }
    else if(isik_degeri < 1024) {          // Değer 1024'den düşükse
        // Yeşil LED'i yak, diğerlerini söndür
        digitalWrite(kirmiziLedPin, HIGH);
        digitalWrite(yesilLedPin, LOW);
        digitalWrite(maviLedPin, HIGH);
        
        // Işık değerine göre hoparlörden ton üret
        tone(hoparlorPin, isik_degeri);
        delay(100);                         // 100ms bekle 
    }
    
    noTone(hoparlorPin);                   // Hoparlör pinini eski haline getir
}
