// SA67 - Duvar tenisi (Squash)

// Kütüphaneleri tanımla
#include "LedControl.h" 
#include <MaxMatrix.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

// Harfler sayılar ve sembollerin binary (ikili) formatı
PROGMEM const unsigned char CH[] = {
    3, 8, B00000000, B00000000, B00000000, B00000000, B00000000,    // space
    1, 8, B01011111, B00000000, B00000000, B00000000, B00000000,    // !
    3, 8, B00000011, B00000000, B00000011, B00000000, B00000000,    // "
    5, 8, B00010100, B00111110, B00010100, B00111110, B00010100,    // #
    4, 8, B00100100, B01101010, B00101011, B00010010, B00000000,    // $
    5, 8, B01100011, B00010011, B00001000, B01100100, B01100011,    // %
    5, 8, B00110110, B01001001, B01010110, B00100000, B01010000,    // &
    1, 8, B00000011, B00000000, B00000000, B00000000, B00000000,    // '
    3, 8, B00011100, B00100010, B01000001, B00000000, B00000000,    // (
    3, 8, B01000001, B00100010, B00011100, B00000000, B00000000,    // )
    5, 8, B00101000, B00011000, B00001110, B00011000, B00101000,    // *
    5, 8, B00001000, B00001000, B00111110, B00001000, B00001000,    // +
    2, 8, B10110000, B01110000, B00000000, B00000000, B00000000,    // ,
    4, 8, B00001000, B00001000, B00001000, B00001000, B00000000,    // -
    2, 8, B01100000, B01100000, B00000000, B00000000, B00000000,    // .
    4, 8, B01100000, B00011000, B00000110, B00000001, B00000000,    // /
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,    // 0
    3, 8, B01000010, B01111111, B01000000, B00000000, B00000000,    // 1
    4, 8, B01100010, B01010001, B01001001, B01000110, B00000000,    // 2
    4, 8, B00100010, B01000001, B01001001, B00110110, B00000000,    // 3
    4, 8, B00011000, B00010100, B00010010, B01111111, B00000000,    // 4
    4, 8, B00100111, B01000101, B01000101, B00111001, B00000000,    // 5
    4, 8, B00111110, B01001001, B01001001, B00110000, B00000000,    // 6
    4, 8, B01100001, B00010001, B00001001, B00000111, B00000000,    // 7
    4, 8, B00110110, B01001001, B01001001, B00110110, B00000000,    // 8
    4, 8, B00000110, B01001001, B01001001, B00111110, B00000000,    // 9
    2, 8, B01010000, B00000000, B00000000, B00000000, B00000000,    // :
    2, 8, B10000000, B01010000, B00000000, B00000000, B00000000,    // ;
    3, 8, B00010000, B00101000, B01000100, B00000000, B00000000,    // <
    3, 8, B00010100, B00010100, B00010100, B00000000, B00000000,    // =
    3, 8, B01000100, B00101000, B00010000, B00000000, B00000000,    // >
    4, 8, B00000010, B01011001, B00001001, B00000110, B00000000,    // ?
    5, 8, B00111110, B01001001, B01010101, B01011101, B00001110,    // @
    4, 8, B01111110, B00010001, B00010001, B01111110, B00000000,    // A
    4, 8, B01111111, B01001001, B01001001, B00110110, B00000000,    // B
    4, 8, B00111110, B01000001, B01000001, B00100010, B00000000,    // C
    4, 8, B01111111, B01000001, B01000001, B00111110, B00000000,    // D
    4, 8, B01111111, B01001001, B01001001, B01000001, B00000000,    // E
    4, 8, B01111111, B00001001, B00001001, B00000001, B00000000,    // F
    4, 8, B00111110, B01000001, B01001001, B01111010, B00000000,    // G
    4, 8, B01111111, B00001000, B00001000, B01111111, B00000000,    // H
    3, 8, B01000001, B01111111, B01000001, B00000000, B00000000,    // I
    4, 8, B00110000, B01000000, B01000001, B00111111, B00000000,    // J
    4, 8, B01111111, B00001000, B00010100, B01100011, B00000000,    // K
    4, 8, B01111111, B01000000, B01000000, B01000000, B00000000,    // L
    5, 8, B01111111, B00000010, B00001100, B00000010, B01111111,    // M
    5, 8, B01111111, B00000100, B00001000, B00010000, B01111111,    // N
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,    // O
    4, 8, B01111111, B00001001, B00001001, B00000110, B00000000,    // P
    4, 8, B00111110, B01000001, B01000001, B10111110, B00000000,    // Q
    4, 8, B01111111, B00001001, B00001001, B01110110, B00000000,    // R
    4, 8, B01000110, B01001001, B01001001, B00110010, B00000000,    // S
    5, 8, B00000001, B00000001, B01111111, B00000001, B00000001,    // T
    4, 8, B00111111, B01000000, B01000000, B00111111, B00000000,    // U
    5, 8, B00001111, B00110000, B01000000, B00110000, B00001111,    // V
    5, 8, B00111111, B01000000, B00111000, B01000000, B00111111,    // W
    5, 8, B01100011, B00010100, B00001000, B00010100, B01100011,    // X
    5, 8, B00000111, B00001000, B01110000, B00001000, B00000111,    // Y
    4, 8, B01110001, B01001001, B01001001, B01000111, B00000000,    // Z
    2, 8, B01111111, B01000001, B00000000, B00000000, B00000000,    // [
    4, 8, B00000001, B00000110, B00011000, B01100000, B00000000,    // \ ters slash
    2, 8, B01000001, B01111111, B00000000, B00000000, B00000000,    // ]
    3, 8, B00000010, B00000001, B00000010, B00000000, B00000000,    // hat
    4, 8, B01000000, B01000000, B01000000, B01000000, B00000000,    // _
    2, 8, B00000001, B00000010, B00000000, B00000000, B00000000,    // `
    4, 8, B00100000, B01010100, B01010100, B01111000, B00000000,    // a
    4, 8, B01111111, B01000100, B01000100, B00111000, B00000000,    // b
    4, 8, B00111000, B01000100, B01000100, B00101000, B00000000,    // c
    4, 8, B00111000, B01000100, B01000100, B01111111, B00000000,    // d
    4, 8, B00111000, B01010100, B01010100, B00011000, B00000000,    // e
    3, 8, B00000100, B01111110, B00000101, B00000000, B00000000,    // f
    4, 8, B10011000, B10100100, B10100100, B01111000, B00000000,    // g
    4, 8, B01111111, B00000100, B00000100, B01111000, B00000000,    // h
    3, 8, B01000100, B01111101, B01000000, B00000000, B00000000,    // i
    4, 8, B01000000, B10000000, B10000100, B01111101, B00000000,    // j
    4, 8, B01111111, B00010000, B00101000, B01000100, B00000000,    // k
    3, 8, B01000001, B01111111, B01000000, B00000000, B00000000,    // l
    5, 8, B01111100, B00000100, B01111100, B00000100, B01111000,    // m
    4, 8, B01111100, B00000100, B00000100, B01111000, B00000000,    // n
    4, 8, B00111000, B01000100, B01000100, B00111000, B00000000,    // o
    4, 8, B11111100, B00100100, B00100100, B00011000, B00000000,    // p
    4, 8, B00011000, B00100100, B00100100, B11111100, B00000000,    // q
    4, 8, B01111100, B00001000, B00000100, B00000100, B00000000,    // r
    4, 8, B01001000, B01010100, B01010100, B00100100, B00000000,    // s
    3, 8, B00000100, B00111111, B01000100, B00000000, B00000000,    // t
    4, 8, B00111100, B01000000, B01000000, B01111100, B00000000,    // u
    5, 8, B00011100, B00100000, B01000000, B00100000, B00011100,    // v
    5, 8, B00111100, B01000000, B00111100, B01000000, B00111100,    // w
    5, 8, B01000100, B00101000, B00010000, B00101000, B01000100,    // x
    4, 8, B10011100, B10100000, B10100000, B01111100, B00000000,    // y
    3, 8, B01100100, B01010100, B01001100, B00000000, B00000000,    // z
    3, 8, B00001000, B00110110, B01000001, B00000000, B00000000,    // {
    1, 8, B01111111, B00000000, B00000000, B00000000, B00000000,    // |
    3, 8, B01000001, B00110110, B00001000, B00000000, B00000000,    // }
    4, 8, B00001000, B00000100, B00001000, B00000100, B00000000,    // ~
};

int DIN = 4;                          // DIN pini tanımla
int CS = 3;                           // CS pini tanımla
int CLK = 2;                          // CLK pini tanımla

int Led_Matrix_Sayisi = 1;            // LED matriksler arka arkaya bağlanabilir
                                     // Birden fazla matriks bağlanacak ise buradaki sayıyı değiştirebilirsiniz

// Matriks pinlerinin bağlantıları ile m matriksini tanımla
MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);  

// DATAIN pini(4), CLK pini(2), CS pini(3), kaçtane matriks bağlandığını (1) tanımla
LedControl myMatrix = LedControl(4, 2, 3, 1); 

int sutun = 0, satir = random(8);     // Sütunu 0'a eşitle, satır'a rastgele bir sayı ata
int Xyonu = 1, Yyonu = 1;             // LED'in hareketi için yönleri tanımla
int potPin = 0, potPinDegeri;         // POT Analog 0 Pinine bağlandığı ve değerin tutulacağı değişkeni tanımla
int Hareket_hizi = 300;               // Oyunun gittikçe hızlanması için hareket_hizi değişkenini tanımla
int sayac = 0;
int hoparlorPin = 7;                  // Hoparlörün bağlandığı pin numarasını tanımla

unsigned long BaslangicZaman = 0;
unsigned long gecensure = 0;
byte buffer[10];
char sonuc[2];

void setup() { 
    pinMode(hoparlorPin, OUTPUT);      // Hoparlörün bağlandığı pini çıkış olarak ayarla
    m.init();                          // 8x8 Led matriksi başlat
    m.setIntensity(8);                // Parlaklığını 8'e ayarla
    
    myMatrix.shutdown(0, false);       // LED'in parlaklık ayarları için  
    myMatrix.setIntensity(0, 8);      // Parlaklığı değiştirmek için 8 değerini değiştirebilirsiniz
    randomSeed(analogRead(0));         // Analog sıfırdan rastgele referans değeri al
    yenilgi();
}

void loop() { 
    BaslangicZaman = millis();        // Arduino çalıştığı andan itibaren geçen süreyi BaslangicZamani fonksiyonuna kaydet
    potPinDegeri = analogRead(potPin); // Potansiyometre değerini oku
    potPinDegeri = map(potPinDegeri, 0, 1024, 0, 6);  // Okunan 0 ile 1024 arasındaki değeri 0 ile 6'ya oranla 

    // Eğer ledin hareketi en sona geldiyse ve alttaki hareketli panel en sona geldiyse panel daha fazla ilerlemesin
    if (satir == 1 && (potPinDegeri == sutun || potPinDegeri + 1 == sutun || potPinDegeri + 2 == sutun)) {
        Yyonu = +1;
        tone(hoparlorPin, 600);
        delay(50);
        noTone(hoparlorPin);
    }

    if (satir == 7) {                 // Eğer top üst tarafa çarptı ise aşağı doğru yön değiştir
        Yyonu = -1;
    }
    if (sutun == 7) {                 // Eğer top sağ tarafa çarptı ise sola doğru yön değiştir
        Xyonu = -1;
    }
    if (sutun == 0) {                 // Eğer sol üst tarafa çarptı ise sağa doğru yön değiştir
        Xyonu = 1;
    }

    if (satir == 0) {                 // Eğer LED 0. satıra geldiyse yani yandıysanız
        unsigned long skor = 0;        // Skor değişkeni oluştur ilk durumunu sıfıra eşitle
        gecensure = BaslangicZaman - gecensure;  // En son yanılma ile baslangıc zamanının farkını al
        skor = gecensure / 200;       // Saniyede 5 puan kazanması için  

        for (int i = 0; i < 3; i++) {
            tone(hoparlorPin, 100);
            delay(150);
            tone(hoparlorPin, 400);
            delay(150);
            noTone(hoparlorPin);
        }

        char skor2[4]; 
        itoa(skor, skor2, 10);        // Integer sayıyı karaktere dönüştür, skor integer sayısını skor2 karakter(char)'a dönüştür
        myMatrix.clearDisplay(0);      // LED Matriksi temizle
        m.shiftLeft(true, false);      // Sola kaydır
        printStringWithShift("SKOR ", 80);  // SKOR yazısı yazdır
        printStringWithShift(skor2, 80);    // Skoru yazdır
        printStringWithShift("  ", 80);     // Boşluk yazısı yazdır
        delay(1000);                  // 1 saniye bekle
        gecensure = millis();         // Yeni oyuna geçmeden süreyi kaydet
        yenilgi();                    // yenilgi fonksiyonuna git    
    }  
    
    sutun += Xyonu; 
    satir += Yyonu;
    Hareket();
    sayac++; 
}

void yenilgi() {                      // yenilgi() fonksiyonunu tanımla
    for (int x = 0; x < 3; x++) {     // for döngüsü ile 
        myMatrix.clearDisplay(0);      // LED Matriks ekranı temizle 
        delay(250);
        for (int y = 0; y < 8; y++) {  
            myMatrix.setRow(0, y, 255); 
        }
        delay(150);  
    } 

    // Değişkenleri başlangıç değerine al 
    sayac = 0;
    Hareket_hizi = 300;
    sutun = random(2, 8);
    satir = random(2, 8);
    Hareket(); 
}

void Hareket() { 
    myMatrix.clearDisplay(0);         // Ekranı Temizle 
    myMatrix.setLed(0, sutun, satir, HIGH);  // Topun hareket yönlerini belirle, 0, Sütun, Satır, HIGH
    myMatrix.setLed(0, potPinDegeri, 0, HIGH);      // Alt pedalın hareket yönlerini belirle (Pedal 3 noktadan oluştu)
    myMatrix.setLed(0, potPinDegeri + 1, 0, HIGH);  // Alt pedalın hareket yönlerini belirle 
    myMatrix.setLed(0, potPinDegeri + 2, 0, HIGH);  // Alt pedalın hareket yönlerini belirle 

    if (!(sayac % 10)) {              // Oyunun gittikçe hızlanması için 
        Hareket_hizi -= 5;
    }  
    delay(Hareket_hizi); 
}

// Karakter yazdırmak için gerekli fonksiyon
void printCharWithShift(char c, int kaydirma_hizi) {
    if (c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7 * c, 7);
    m.writeSprite(1 * 8, 0, buffer);
    m.setColumn(1 * 8 + buffer[0], 0);
    
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
