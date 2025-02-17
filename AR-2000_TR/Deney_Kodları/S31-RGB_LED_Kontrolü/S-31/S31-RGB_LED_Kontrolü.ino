// S31 - RGB LED Kontrolü

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int kirmiziLedPin = 5;
int yesilLedPin = 4;
int maviLedPin = 3;

// Buton'un bağlandığı dijital pin numarasını tanımla
int butonPin = 2;

// Buton durumunun tutulacağı değişkeni tanımla
int butonDurumu = 0;

// LED'lerin durumunun tutulacağı değişkeni tanımla
int ledDurumu = 0;

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziLedPin, OUTPUT); 
    pinMode(yesilLedPin, OUTPUT); 
    pinMode(maviLedPin, OUTPUT); 
    
    // Buton'un bağlandığı pini giriş olarak ayarla
    pinMode(butonPin, INPUT);
    
    // Başlangıçta LED'lerin hepsini söndür
    digitalWrite(kirmiziLedPin, HIGH);
    digitalWrite(yesilLedPin, HIGH);
    digitalWrite(maviLedPin, HIGH);
}

void loop() {
    /* NOT: Setimizde kullanılan RGB LED ortak anot yani besleme ucu ortaktır. Bu durumda RGB LED modülündeki 
     * LED'leri yakabilmek için o lede bağlı pini LOW yapmak gerekir. Yani modülde CA yazan yere +5v besleme 
     * verildiğinde LED'e bağlı pini digitalWrite(kirmiziLedPin,LOW) yaptığımızda kırmızı LED yanacaktır.
     */
    
    // Buton durumunu sorgula ve butonDurumu değişkenine ata
    butonDurumu = digitalRead(butonPin);

    // Buton durumuna göre LED'in durumunu ayarla
    if (butonDurumu == HIGH) {    // Butona basıldı ise
        // ledDurumu değişkenini bir arttırılarak bir sonraki LED durumuna geç
        ledDurumu++;

        while (butonDurumu == HIGH) {    // Butona basılı olduğu sürece bekle
            butonDurumu = digitalRead(butonPin);    // Butona basılıp basılmadığını kontrol et
        }
    }
  
    // ledDurumu değişkenine göre yanacak LED renklerini seç
    if (ledDurumu == 1) {
        // Kırmızı LED'i yak, diğerlerini söndür
        digitalWrite(kirmiziLedPin, LOW);
        digitalWrite(yesilLedPin, HIGH);
        digitalWrite(maviLedPin, HIGH);
    }
    else if (ledDurumu == 2) {
        // Yeşil LED'i yak, diğerlerini söndür
        digitalWrite(kirmiziLedPin, HIGH);
        digitalWrite(yesilLedPin, LOW);
        digitalWrite(maviLedPin, HIGH);
    }
    else if (ledDurumu == 3) {
        // Mavi LED'i yak, diğerlerini söndür
        digitalWrite(kirmiziLedPin, HIGH);
        digitalWrite(yesilLedPin, HIGH);
        digitalWrite(maviLedPin, LOW);
    }
    else if (ledDurumu == 4) {
        // Kırmızı ve Yeşil LED'i yak, diğerini söndür
        digitalWrite(kirmiziLedPin, LOW);
        digitalWrite(yesilLedPin, LOW);
        digitalWrite(maviLedPin, HIGH);
    }
    else if (ledDurumu == 5) {
        // Yeşil ve Mavi LED'i yak, diğerini söndür
        digitalWrite(kirmiziLedPin, HIGH);
        digitalWrite(yesilLedPin, LOW);
        digitalWrite(maviLedPin, LOW);
    }
    else if (ledDurumu == 6) {
        // LED'lerin hepsini yak
        digitalWrite(kirmiziLedPin, LOW);
        digitalWrite(yesilLedPin, LOW);
        digitalWrite(maviLedPin, LOW);
        
        // ledDurumu değişkenini başlangıç durumuna ayarla
        ledDurumu = 0;
    }
}
