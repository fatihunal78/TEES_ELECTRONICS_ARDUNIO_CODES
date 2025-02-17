// SA82 - Otobüs ve minibüs kapı otomasyonu

#include <MaxMatrix.h>    // LED matriks kütüphanesi ekle
#include <Servo.h>        // Servo motor kütüphanesi ekle

int DIN = 7;             // DIN pin 7. pine bağlı
int CS = 6;              // CS pin 6. pine bağlı
int CLK = 5;             // CLK pin 5. pine bağlı

int Led_Matrix_Sayisi = 1;    // LED matriksler arka arkaya bağlanabilir
                              // Birden fazla matriks bağlanacak ise buradaki sayıyı değiştirebilirsiniz
                            
MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);    // Matriks pinlerinin bağlantıları ile m matriksini tanımla
Servo servo;                                      // servo isimli bir servo motor objesi oluştur
byte buffer[10];

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

int yolcuButon = 3;          // Panel üzerindeki PB1 butonunun bağlandığı pin numarasını tanımla, yolcunun basacağı buton
int kapiButon = 2;           // Panel üzerindeki PB2 butonunun bağlandığı pin numarasını tanımla, şoförün kapıyı açmak için basacağı buton

int kapidurumu = 0;          // Kapının durumunun tutulacağı değişkeni tanımla 0--> Kapalı  1--> açık
int yolcu_butondurumu = 0;   // Yolcu butonunun durumunun tutulacağı değişkeni tanımla 0--> Butona basıldı 1--> Butona basılmadı

int buzzerPin = 8;           // Buzzerın bağlandığı pin numarasını tanımla
int buzzerDurumu = 0;        // Buzzerin çalıyor ya da çalmıyor olarak durumunun tutulacağı değişkeni tanımla
unsigned long yenizaman = 0;
unsigned long eskizaman = 0;

void setup() {
    m.init();                              // LED matriksi başlat
    m.setIntensity(5);                     // Parlaklık seviyesini ayarla
    servo.attach(4);                       // Servo motorun bağlandığı pini ayarla
    pinMode(yolcuButon, INPUT_PULLUP);     // PB1 butonun bağlandığı pini giriş olarak tanımla
    pinMode(kapiButon, INPUT_PULLUP);      // PB2 butonun bağlandığı pini giriş olarak tanımla
    pinMode(buzzerPin, OUTPUT);            // Buzzer bağlandığı pini çıkış olarak ayarla
    servo.write(90);                       // Servo motoru başlangıçta 90 derece konumuna getir
}

void loop() {
    digitalWrite(buzzerPin, LOW);    // Buzzerı sustur

    // Eğer kapı kapalı ise ve şoför kapıyı açmak için butona bastı ise
    if (kapidurumu == 0 && digitalRead(kapiButon) == LOW) {
        kapidurumu = 1;              // Kapı durumunu açık olarak kaydet
        yolcu_butondurumu = 0;       // yolcu_butondurumu değişkenini 0 yap
        m.clear();                   // LED matriksi temizle

        // Kapıyı açmak için i değişkenini 90 dereceden 180 dereceye doğru birer arttır
        for (int i = 90; i <= 180; i++) {
            servo.write(i);          // Servo motora yaz
            delay(30);
            yenizaman = millis();      
            
            // Her yarım saniye aralıklar ile buzzeri öttürmek için 
            if (yenizaman - eskizaman > 500) {
                if (buzzerDurumu == 0) {           // Buzzer çalmıyor ise 
                    digitalWrite(buzzerPin, HIGH);  // Buzzerdan ses çıkar
                    buzzerDurumu = 1;              // Buzzer durumunu çalıyor olarak kaydet 
                } else {                           // Eğer buzzer çalıyorsa 
                    digitalWrite(buzzerPin, LOW);   // Buzzerı sustur
                    buzzerDurumu = 0;              // Buzzer durumunu çalmıyor olarak kaydet
                }
                eskizaman = yenizaman;             // eskizaman değişkenine yenizamanı kaydet 
            }       
        }
    }

    // Eğer kapı açık ise ve şoför kapıyı kapatmak için butona bastı ise
    if (kapidurumu == 1 && digitalRead(kapiButon) == LOW) {
        kapidurumu = 0;    // Kapı durumunu kapalı olarak kaydet

        // Kapıyı kapatmak için i değişkenini 180 dereceden 90 dereceye doğru birer azaltarak
        for (int i = 180; i >= 90; i--) {
            servo.write(i);    // Servo motora yaz
            delay(30);         // 30 ms gecikme
            yenizaman = millis(); 
            
            // Her yarım saniye aralıklar ile buzzerdan ses çıkarmak için 
            if (yenizaman - eskizaman > 500) {
                if (buzzerDurumu == 0) {           // Buzzer çalmıyor ise 
                    digitalWrite(buzzerPin, HIGH);  // Buzzerdan ses çıkar 
                    buzzerDurumu = 1;              // Buzzer durumunu çalıyor olarak kaydet 
                } else {                           // Eğer buzzer çalıyorsa
                    digitalWrite(buzzerPin, LOW);   // Buzzerı sustur
                    buzzerDurumu = 0;              // Buzzer durumunu çalmıyor olarak kaydet
                }
                eskizaman = yenizaman;             // eskizaman değişkenine yenizamanı kaydet 
            } 
        }
    }

    // Eğer yolculardan biri butona bastı ise ve kapı kapalı ise
    if (digitalRead(yolcuButon) == LOW && kapidurumu == 0) {
        yolcu_butondurumu = 1;    // yolcu_butondurumunu basıldı olarak kaydet
        
        // Buzzerdan dıt dıt sesi çıkar
        digitalWrite(buzzerPin, HIGH); 
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(50);
        digitalWrite(buzzerPin, HIGH); 
        delay(300);
        digitalWrite(buzzerPin, LOW);
        delay(50);
    }

    while (yolcu_butondurumu == 1) {    // yolcu_butondurumu 1 olduğu sürece
        printStringWithShift("DURACAK  ", 80);    // LED matrikse "DURACAK!" yaz
    }
}

// Karakterleri yazdırmak için gerekli fonksiyonu tanımla
void printCharWithShift(char c, int kaydirma_hizi) {
    if (c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7 * c, 7);
    m.writeSprite(Led_Matrix_Sayisi * 8, 0, buffer);
    m.setColumn(Led_Matrix_Sayisi * 8 + buffer[0], 0);

    for (int i = 0; i < buffer[0] + 1; i++) {
        delay(kaydirma_hizi);
        m.shiftLeft(false, false);
    }
}

// String'i yazdırmak için gerekli fonksiyonu tanımla
void printStringWithShift(char* s, int kaydirma_hizi) {
    while (*s != 0) {
        if (digitalRead(kapiButon) == LOW) {    // Eğer şoför kapıyı açmak için butona bastı ise
            yolcu_butondurumu = 0;              // yolcu_butondurumu değişkeninin değerini 0 yap
            break;
        }
        printCharWithShift(*s, kaydirma_hizi);
        s++;
    }
}
