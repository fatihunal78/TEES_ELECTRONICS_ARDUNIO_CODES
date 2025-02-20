// S42 - Potansiyometre ile RGB LED Kontrolü

// RGB LED ortak anot olduğu için, ortak kısmı (CA) +5V beslemeye bağlanmıştır.
// Kırmızı, yeşil ve mavi LED uçları da 6, 5 ve 3 numaralı PWM çıkışına bağlanmıştır.

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int kirmiziLedPin = 6;                         // Kırmızı LED pin
int yesilLedPin = 5;                          // Yeşil LED pin  
int maviLedPin = 3;                           // Mavi LED pin

// Potansiyometrenin bağlandığı analog pin numarasını tanımla
int potPin = A0;                              // Potansiyometre pin

// Potansiyometre değerinin kaydedileceği değişkeni tanımla
int potDegeri = 0;                            // Potansiyometre değeri

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziLedPin, OUTPUT); 
    pinMode(yesilLedPin, OUTPUT); 
    pinMode(maviLedPin, OUTPUT); 
    
    // Başlangıçta LED'lerin hepsini söndür
    analogWrite(kirmiziLedPin, 255);
    analogWrite(yesilLedPin, 255);
    analogWrite(maviLedPin, 255);
}

void loop() {
    // Potun değerini oku ve potDurumu değişkenine ata
    potDegeri = analogRead(potPin);
    
    // potDegeri'ne göre LED'lerin rengini değiştir
    if(potDegeri > 850) {
        analogWrite(kirmiziLedPin, 255 - potDegeri + 850);
        analogWrite(yesilLedPin, 255 - potDegeri + 850);  
        analogWrite(maviLedPin, 255 - potDegeri + 850);
    }
    else if(potDegeri > 680) {
        analogWrite(kirmiziLedPin, 0);
        analogWrite(yesilLedPin, 255 - 165);  
        analogWrite(maviLedPin, 255);
    }
    else if(potDegeri > 510) {
        analogWrite(kirmiziLedPin, 255 - 143);
        analogWrite(yesilLedPin, 255);  
        analogWrite(maviLedPin, 0);
    }
    else if(potDegeri > 340) {
        analogWrite(kirmiziLedPin, 255);
        analogWrite(yesilLedPin, 255);  
        analogWrite(maviLedPin, 255 - potDegeri + 340);
    }
    else if(potDegeri > 170) {
        analogWrite(kirmiziLedPin, 255);
        analogWrite(yesilLedPin, 255 - potDegeri - 170);  
        analogWrite(maviLedPin, 255);
    }
    else if(potDegeri >= 0) {
        analogWrite(kirmiziLedPin, 255 - potDegeri);
        analogWrite(yesilLedPin, 255);  
        analogWrite(maviLedPin, 255);
    }
}
