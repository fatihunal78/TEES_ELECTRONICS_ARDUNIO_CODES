// SA71 - Toplu taşıma için yolcu sayıcı

#include <MaxMatrix.h>                                    // LED Matriks kütüphanesini ekledik 

int SensorPin = 3;                                       // Birinci sensörün (Giriş sensörü) bağlandığı pini tanımla
int Sensor2Pin = 4;                                      // İkinci sensörün (Çıkış sensörü) bağlandığı pini tanımla
int buzzerPin = 2;                                       // Hoparlörün bağlandığı pin numarasını tanımla
int sayac = 0;                                          // Giriş çıkış sayısının tutulacağı değişkeni tanımla ve ilk değeri sıfıra eşitle
char CharSayac[4];                                      // Integer bir sayıyı LED Matrise aktarmak için karakter (char) değişkenine cevir
                                                        // Giriş çıkış sayısının tutulacağı sayac değişkenini char'a dönüştürmek için 
                                                        // CharSayac karakter(char) değişkeni oluştur
                   
byte buffer[10]; 

int DIN = 7;                                           // LED Matrisin DIN pini 7. pine bağlı olduğunu tanımla
int CS = 6;                                            // LED Matrisin CS  pini 6.pine bağlı olduğunu tanımla
int CLK = 5;                                           // LED Matrisin CLK pini 5.pine bağlı olduğunu tanımla

int Led_Matrix_Sayisi = 1;                             // LED Matriks sayısını tanımla

MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);          // Matriks pinlerinin bağlantıları ile m matriksini tanımla

// Harfler sayılar ve sembollerin binary (ikili) formatı
PROGMEM const unsigned char CH[] = {
    3, 8, B00000000, B00000000, B00000000, B00000000, B00000000,  // space
    1, 8, B01011111, B00000000, B00000000, B00000000, B00000000,  // !
    3, 8, B00000011, B00000000, B00000011, B00000000, B00000000,  // "
    5, 8, B00010100, B00111110, B00010100, B00111110, B00010100,  // #
    4, 8, B00100100, B01101010, B00101011, B00010010, B00000000,  // $
    5, 8, B01100011, B00010011, B00001000, B01100100, B01100011,  // %
    5, 8, B00110110, B01001001, B01010110, B00100000, B01010000,  // &
    1, 8, B00000011, B00000000, B00000000, B00000000, B00000000,  // '
    3, 8, B00011100, B00100010, B01000001, B00000000, B00000000,  // (
    3, 8, B01000001, B00100010, B00011100, B00000000, B00000000,  // )
    5, 8, B00101000, B00011000, B00001110, B00011000, B00101000,  // *
    5, 8, B00001000, B00001000, B00111110, B00001000, B00001000,  // +
    2, 8, B10110000, B01110000, B00000000, B00000000, B00000000,  // ,
    4, 8, B00001000, B00001000, B00001000, B00001000, B00000000,  // -
    2, 8, B01100000, B01100000, B00000000, B00000000, B00000000,  // .
    4, 8, B01100000, B00011000, B00000110, B00000001, B00000000,  // /
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // 0
    3, 8, B01000010, B01111111, B01000000, B00000000, B00000000,  // 1
    4, 8, B01100010, B01010001, B01001001, B01000110, B00000000,  // 2
    4, 8, B00100010, B01000001, B01001001, B00110110, B00000000,  // 3
    4, 8, B00011000, B00010100, B00010010, B01111111, B00000000,  // 4
    4, 8, B00100111, B01000101, B01000101, B00111001, B00000000,  // 5
    4, 8, B00111110, B01001001, B01001001, B00110000, B00000000,  // 6
    4, 8, B01100001, B00010001, B00001001, B00000111, B00000000,  // 7
    4, 8, B00110110, B01001001, B01001001, B00110110, B00000000,  // 8
    4, 8, B00000110, B01001001, B01001001, B00111110, B00000000,  // 9
    2, 8, B01010000, B00000000, B00000000, B00000000, B00000000,  // :
    2, 8, B10000000, B01010000, B00000000, B00000000, B00000000,  // ;
    3, 8, B00010000, B00101000, B01000100, B00000000, B00000000,  // <
    3, 8, B00010100, B00010100, B00010100, B00000000, B00000000,  // =
    3, 8, B01000100, B00101000, B00010000, B00000000, B00000000,  // >
    4, 8, B00000010, B01011001, B00001001, B00000110, B00000000,  // ?
    5, 8, B00111110, B01001001, B01010101, B01011101, B00001110,  // @
    4, 8, B01111110, B00010001, B00010001, B01111110, B00000000,  // A
    4, 8, B01111111, B01001001, B01001001, B00110110, B00000000,  // B
    4, 8, B00111110, B01000001, B01000001, B00100010, B00000000,  // C
    4, 8, B01111111, B01000001, B01000001, B00111110, B00000000,  // D
    4, 8, B01111111, B01001001, B01001001, B01000001, B00000000,  // E
    4, 8, B01111111, B00001001, B00001001, B00000001, B00000000,  // F
    4, 8, B00111110, B01000001, B01001001, B01111010, B00000000,  // G
    4, 8, B01111111, B00001000, B00001000, B01111111, B00000000,  // H
    3, 8, B01000001, B01111111, B01000001, B00000000, B00000000,  // I
    4, 8, B00110000, B01000000, B01000001, B00111111, B00000000,  // J
    4, 8, B01111111, B00001000, B00010100, B01100011, B00000000,  // K
    4, 8, B01111111, B01000000, B01000000, B01000000, B00000000,  // L
    5, 8, B01111111, B00000010, B00001100, B00000010, B01111111,  // M
    5, 8, B01111111, B00000100, B00001000, B00010000, B01111111,  // N
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // O
    4, 8, B01111111, B00001001, B00001001, B00000110, B00000000,  // P
    4, 8, B00111110, B01000001, B01000001, B10111110, B00000000,  // Q
    4, 8, B01111111, B00001001, B00001001, B01110110, B00000000,  // R
    4, 8, B01000110, B01001001, B01001001, B00110010, B00000000,  // S
    5, 8, B00000001, B00000001, B01111111, B00000001, B00000001,  // T
    4, 8, B00111111, B01000000, B01000000, B00111111, B00000000,  // U
    5, 8, B00001111, B00110000, B01000000, B00110000, B00001111,  // V
    5, 8, B00111111, B01000000, B00111000, B01000000, B00111111,  // W
    5, 8, B01100011, B00010100, B00001000, B00010100, B01100011,  // X
    5, 8, B00000111, B00001000, B01110000, B00001000, B00000111,  // Y
    4, 8, B01110001, B01001001, B01001001, B01000111, B00000000,  // Z
    2, 8, B01111111, B01000001, B00000000, B00000000, B00000000,  // [
    4, 8, B00000001, B00000110, B00011000, B01100000, B00000000,  // \ ters slash
    2, 8, B01000001, B01111111, B00000000, B00000000, B00000000,  // ]
    3, 8, B00000010, B00000001, B00000010, B00000000, B00000000,  // hat
    4, 8, B01000000, B01000000, B01000000, B01000000, B00000000,  // _
    2, 8, B00000001, B00000010, B00000000, B00000000, B00000000,  // `
    4, 8, B00100000, B01010100, B01010100, B01111000, B00000000,  // a
    4, 8, B01111111, B01000100, B01000100, B00111000, B00000000,  // b
    4, 8, B00111000, B01000100, B01000100, B00101000, B00000000,  // c
    4, 8, B00111000, B01000100, B01000100, B01111111, B00000000,  // d
    4, 8, B00111000, B01010100, B01010100, B00011000, B00000000,  // e
    3, 8, B00000100, B01111110, B00000101, B00000000, B00000000,  // f
    4, 8, B10011000, B10100100, B10100100, B01111000, B00000000,  // g
    4, 8, B01111111, B00000100, B00000100, B01111000, B00000000,  // h
    3, 8, B01000100, B01111101, B01000000, B00000000, B00000000,  // i
    4, 8, B01000000, B10000000, B10000100, B01111101, B00000000,  // j
    4, 8, B01111111, B00010000, B00101000, B01000100, B00000000,  // k
    3, 8, B01000001, B01111111, B01000000, B00000000, B00000000,  // l
    5, 8, B01111100, B00000100, B01111100, B00000100, B01111000,  // m
    4, 8, B01111100, B00000100, B00000100, B01111000, B00000000,  // n
    4, 8, B00111000, B01000100, B01000100, B00111000, B00000000,  // o
    4, 8, B11111100, B00100100, B00100100, B00011000, B00000000,  // p
    4, 8, B00011000, B00100100, B00100100, B11111100, B00000000,  // q
    4, 8, B01111100, B00001000, B00000100, B00000100, B00000000,  // r
    4, 8, B01001000, B01010100, B01010100, B00100100, B00000000,  // s
    3, 8, B00000100, B00111111, B01000100, B00000000, B00000000,  // t
    4, 8, B00111100, B01000000, B01000000, B01111100, B00000000,  // u
    5, 8, B00011100, B00100000, B01000000, B00100000, B00011100,  // v
    5, 8, B00111100, B01000000, B00111100, B01000000, B00111100,  // w
    5, 8, B01000100, B00101000, B00010000, B00101000, B01000100,  // x
    4, 8, B10011100, B10100000, B10100000, B01111100, B00000000,  // y
    3, 8, B01100100, B01010100, B01001100, B00000000, B00000000,  // z
    3, 8, B00001000, B00110110, B01000001, B00000000, B00000000,  // {
    1, 8, B01111111, B00000000, B00000000, B00000000, B00000000,  // |
    3, 8, B01000001, B00110110, B00001000, B00000000, B00000000,  // }
    4, 8, B00001000, B00000100, B00001000, B00000100, B00000000,  // ~
};

void setup() {
    pinMode(SensorPin, INPUT);                          // Sensör pinini (Yolcu Giriş sensörü) giriş olarak ayarla 
    pinMode(Sensor2Pin, INPUT);                         // Sensör pinini (Yolcu çıkış sensörü) giriş olarak ayarla 
    pinMode(buzzerPin, OUTPUT);                         // Hoparlörün bağlandığı pini çıkış olarak ayarla
    m.init();                                          // Led matrix'i başlat
    m.setIntensity(8);                                 // Parlaklığı ayarla
}
   
void loop() { 
    bool val = digitalRead(SensorPin);                  // Sensör pindeki değeri oku
    bool val2 = digitalRead(Sensor2Pin);               // Sensör 2 pindeki değeri oku
  
    if (val == HIGH) {                                 // Eğer sensör1 yani yolcu giriş sensöründeki değer HIGH ise yani yolcu giriş 
                                                       // yaptı ise hoparlörden yolcu bindiğinde sesli uyarı için hoparlörden dıt dıt 
                                                       // sesi çıkar
        for (int i = 0; i < 2; i++) {
            digitalWrite(buzzerPin, HIGH);
            delay(50);
            digitalWrite(buzzerPin, LOW);
            delay(50);
        }
        sayac = sayac + 1;                            // sayac değerini 1 arttır 
        itoa(sayac, CharSayac, 10);                   // integer sayıyı karaktere(char) dönüştür (sayac integer sayısını Charsayac 
                                                      // karakter(char)'a dönüştür) 
        printStringWithShift(CharSayac, 70);          // Karaktere dönüştürülmüş CharSayac değişkenindeki değeri LED Matrise aktar
                                                      // 70 kayma hızını belirtmektedir
                                         
        printStringWithShift("  ", 70);               // LED Matriste bir sonraki sayı ile karışmaması için aralarına boşluk koy
        m.shiftLeft(false, true);                     // Sola kaydır 

        while (1) {                                   // Sensörün önünde sürekli bir engel olduğu zaman saymaması için sonsuz döngüye gir 
            if (digitalRead(SensorPin) == LOW) break; // Eğer engel önünden kalktı ise döngüden çık 
        }
    }
    else if (val2 == HIGH) {                         // Eğer sensör2 yani yolcu çıkış sensöründeki değer HIGH ise yani yolcu çıkış 
                                                     // yaptı ise yolcu indiğinde hoparlörden sesli uyarı için dıt sesi çıkar
        digitalWrite(buzzerPin, HIGH);
        delay(50);
        digitalWrite(buzzerPin, LOW);
        delay(50);
        sayac = sayac - 1;                          // sayac değerini 1 azalt
        itoa(sayac, CharSayac, 10);                 // integer sayıyı karaktere(char) dönüştür (sayac integer sayısını Charsayac 
                                                    // karakter(char)'a dönüştür)
        printStringWithShift(CharSayac, 70);        // Karaktere dönüştürülmüş CharSayac değişkenindeki değeri LED Matrise aktar
                                                    // 70 kayma hızını belirtmektedir.
                                         
        printStringWithShift("  ", 70);             // LED Matriste bir sonraki sayı ile karışmaması için aralarına boşluk koy
        m.shiftLeft(false, true);                   // Sola kaydır 
    
        while (1) {                                 // Sensörün önünde sürekli bir engel olduğu zaman saymaması için sonsuz döngüye gir 
            if (digitalRead(Sensor2Pin) == LOW) break; // Eğer engel önünden kalktı ise döngüden çık 
        }
    }
}

// Karakter yazdırmak için gerekli fonksiyonu tanımla
void printCharWithShift(char c, int kaydirma_hizi) {
    if (c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(1*8, 0, buffer);
    m.setColumn(1*8 + buffer[0], 0);
   
    for (int i = 0; i < buffer[0] + 1; i++) {
        delay(kaydirma_hizi);
        m.shiftLeft(false, false);
    }
}
  
// String'i yazdırmak için gerekli fonksiyon
void printStringWithShift(char* s, int kaydirma_hizi) {
    while (*s != 0) {
        printCharWithShift(*s, kaydirma_hizi);
        s++;
    }
}
