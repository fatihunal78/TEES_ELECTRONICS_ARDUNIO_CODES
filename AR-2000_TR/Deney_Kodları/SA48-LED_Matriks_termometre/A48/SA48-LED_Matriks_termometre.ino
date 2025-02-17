// SA48 - LED Matriks termometre

#include <math.h>                // math.h kütüphanesini ekle
#include <MaxMatrix.h>           // Kütüphaneyi ekle
#include <avr/pgmspace.h>
#include <stdlib.h>              // integer'dan karaktere dönüşüm için gerekli itoa fonksiyonunu kullanmak için gerekli kütüphane

int ntcPin = A5;                 // NTC'nin bağlandığı analog pin numarasını tanımla
int analogDeger;                 // NTC değerinin tutulacağı değişkeni tanımla
double sicaklik;                 // Sıcaklık değerinin tutulacağı değişkeni tanımla

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
    5, 8, 0x00, 0x06, 0x09, 0x09, 0x06, 0x00                      // °derece işareti 
};

int DIN = 4;                     // DIN pini tanımla
int CS = 3;                      // CS pini tanımla
int CLK = 2;                     // CLK pini tanımla

int Led_Matrix_Sayisi = 1;       // LED matriksler arka arkaya bağlanabilir
                                // Birden fazla matriks bağlanacak ise buradaki sayıyı değiştirebilirsiniz

MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);  // Matriks pinlerinin bağlantıları ile m matriksini tanımla  

byte buffer[10];

void setup() {
    m.init();                   // LED matriksi başlat
    m.setIntensity(8);         // Parlaklık ayarı 0 ila 15 arasında ayarlanabilir
}

// ntcHesapla fonksiyonunu tanımla
double ntcHesapla(int analogOkuma) {
    // NTC özelliklerine göre sıcaklık değerini hesapla
    sicaklik = log(((10240000 / analogOkuma) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;
    // Hesaplanan sıcaklık değerini geri gönder
    return sicaklik;
}

void loop() {
    // NTC değerini oku ve analogDeger değişkenine kaydet
    analogDeger = analogRead(ntcPin);
    // ntcHesapla fonksiyonu ile sıcaklık değerini hesapla ve sicaklik değişkenine kaydet
    sicaklik = ntcHesapla(analogDeger);  
    char sicaklik2[4];
    // integer sayıyı karaktere(char) çevir, sicaklik integer sayısını sicaklik2 karakter(char)'a dönüştür
    itoa(sicaklik, sicaklik2, 10);
    m.clear();                  // LED Matriksi temizle
    printStringWithShift("SICAKLIK ", 160);    // SICAKLIK yazısı yazdır
    printStringWithShift(sicaklik2, 160);      // Sıcaklığı yazdır 
    // Santigrad işareti (°C) yazdır. (° işareti klavyede olmadığı için ~ işaretine tanımladık)
    // (~ işaretini yapmak için AltGr+ü tuşlarına birlikte bastıktan sonra boşluk tuşuna basın)
    printStringWithShift("~C  ", 160);  
    m.shiftLeft(false, true);   // Sola kaydır
    delay(200);                 // 200ms saniye bekle
}

// Karakter yazdırmak için gerekli fonksiyon
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
