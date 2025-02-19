// SA101 - Otopark Otomasyonu
#include <MaxMatrix.h>                          // LED matriks kütüphanesini ekle

// LED Matriks bağlantılarını tanımla
int DIN = 4;                                    // DIN pini tanımla
int CS  = 3;                                    // CS pini tanımla
int CLK = 2;                                    // CLK pini tanımla

int Led_Matrix_Sayisi = 1;                      // LED matriksler arka arkaya bağlanabilir
                                               // Birden fazla matriks bağlanacak ise buradaki sayıyı değiştirebilirsiniz
MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);  // Matriks pinlerinin bağlantıları ile m matriksini tanımla 

char Araba1[] = {8, 8,                         // Üstteki arabanın grafiği
    0x04, 0x06, 0x0D, 0x05, 0x05, 0x0D, 0x06, 0x04
}; 

char Araba2[] = {8, 8,                         // Alttaki arabanın grafiği
    0x40, 0x60, 0xE0, 0x60, 0x60, 0xE0, 0x60, 0x40
};

int Sensor1Pin    = 7;                         // Sensör1'in bağlandığı pin numarasını tanımla
int Sensor2Pin    = 6;                         // Sensör2'nin bağlandığı pin numarasını tanımla
int kirmizi_LED1  = 4;                         // Kırmızı LED1'in bağlandığı pin numarasını tanımla
int kirmizi_LED2  = 3;                         // Kırmızı LED2'nin bağlandığı pin numarasını tanımla
int yesil_LED1    = 5;                         // Yeşil LED1'in bağlandığı pin numarasını tanımla
int yesil_LED2    = 2;                         // Yeşil LED2'nin bağlandığı pin numarasını tanımla

void setup() {
    m.init();                                  // Led matriksi başlat
    m.setIntensity(8);                        // Parlaklığı ayarla
    
    pinMode(Sensor1Pin, INPUT);               // Sensör1'in bağlandığı pini giriş olarak ayarla 
    pinMode(Sensor2Pin, INPUT);               // Sensör2'nin bağlandığı pini giriş olarak ayarla 
    
    pinMode(yesil_LED1, OUTPUT);              // yesil_LED1'i çıkış olarak ayarla 
    pinMode(yesil_LED2, OUTPUT);              // yesil_LED2'yi çıkış olarak ayarla 
    pinMode(kirmizi_LED1, OUTPUT);            // kirmizi_LED1'i çıkış olarak ayarla 
    pinMode(kirmizi_LED2, OUTPUT);            // kirmizi_LED2'i çıkış olarak ayarla 
}

void loop() {
    bool val1 = digitalRead(Sensor1Pin);      // Sensör1 pindeki değeri oku 
    bool val2 = digitalRead(Sensor2Pin);      // Sensör2 pindeki değeri oku    

    if (val1 == LOW && val2 == LOW) {         // Eğer 2 sensörde LOW ise yani ikisindede araba yok ise 
        m.clear();                            // ekranı temizle 
        digitalWrite(yesil_LED1, HIGH);       // Yeşil LED1'i yak (üstteki Yeşil LED)
        digitalWrite(yesil_LED2, HIGH);       // Yeşil LED2'yi yak (alttaki Yeşil LED)
        digitalWrite(kirmizi_LED1, LOW);      // Kırmızı LED1'i söndür (üstteki kırmızı led)
        digitalWrite(kirmizi_LED2, LOW);      // Kırmızı LED2'yi söndür (alttaki kırmızı led)
    }
    else if (val1 == LOW && val2 == HIGH) {   // Eğer altakinde araba yok, üstekinde var ise 
        m.writeSprite(0, 0, Araba2);         // Ekrana üstteki araba resmini getir 
        digitalWrite(yesil_LED1, HIGH);       // Yeşil LED1'i yak
        digitalWrite(yesil_LED2, LOW);        // Yeşil LED2'yi söndür    
        digitalWrite(kirmizi_LED1, LOW);      // Kırmızı LED1'i söndür 
        digitalWrite(kirmizi_LED2, HIGH);     // Kırmızı LED2'yi yak     
    }
    else if (val1 == HIGH && val2 == LOW) {   // Eğer üsttekinde araba yok, alttakinde var ise 
        m.writeSprite(0, 0, Araba1);         // Ekrana alttaki araba resmini getir 
        digitalWrite(yesil_LED1, LOW);        // Yeşil LED1'i söndür
        digitalWrite(yesil_LED2, HIGH);       // Yeşil LED2'yi yak
        digitalWrite(kirmizi_LED1, HIGH);     // Kırmızı LED1'i yak 
        digitalWrite(kirmizi_LED2, LOW);      // Kırmızı LED2'yi söndür 
    }
    else if (val1 == HIGH && val2 == HIGH) {  // Eğer her ikisindede araba var ise
        m.writeSprite(0, 0, Araba1);         // Üstteki araba resmini ekrana getir
        m.writeSprite(0, 0, Araba2);         // Alttaki araba resmini ekrana getir 
        digitalWrite(yesil_LED1, LOW);        // Yeşil LED1'i söndür
        digitalWrite(yesil_LED2, LOW);        // Yeşil LED2'yi söndür
        digitalWrite(kirmizi_LED1, HIGH);     // Kırmızı LED1'i yak 
        digitalWrite(kirmizi_LED2, HIGH);     // Kırmızı LED2'yi yak 
    }
}
