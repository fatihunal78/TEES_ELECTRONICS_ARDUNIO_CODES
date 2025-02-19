// SA30 - LED'li disko topu

/*
 * Disko Light Modülü çeşitli renklerde ve animasyonlarda yapmak için AlaLed kütüphanesi 
 * kullanılmıştır.
 */
#include <AlaLed.h>                    // Kütüphane ekle 

AlaLed Animasyon;                      // Animasyon isimli bir obje oluştur 
byte pins[] = {5, 6, 9, 10};           // LED'lerin bağlandığı pinlerini tanımla

// Animasyon döngüleri için kütüphaneden aşağıdaki komutları çek
AlaSeq seq[] = {
    {ALA_FADEIN,                 1000, 1000},
    {ALA_ON,                     1000, 1000},
    {ALA_FADEOUT,                1000, 1000},
    {ALA_BARSHIFTRIGHT,          1000, 1000},
    {ALA_BARSHIFTLEFT,           1000, 1000},
    {ALA_OFF,                    1000, 1000},
    {ALA_PIXELSHIFTRIGHT,         700, 1400},
    {ALA_PIXELSHIFTLEFT,          700, 1400},
    {ALA_BLINKALT,                500, 3000},
    {ALA_PIXELSMOOTHSHIFTRIGHT,  1000, 4000},
    {ALA_PIXELSMOOTHSHIFTLEFT,   1000, 4000},
    {ALA_FADEINOUT,              1000, 4000},
    {ALA_COMET,                  1000, 4000},
    {ALA_GLOW,                   1000, 4000},
    {ALA_STROBO,                  200, 4000},
    {ALA_ENDSEQ,                    0,    0}
};

void setup() {
    Animasyon.initPWM(4, pins);        // LED'lerin bağlandığı pin numaralarını ve sayısını ayarla
    Animasyon.setAnimation(seq);        // Hangi animasyonların yapılacağı ayarla
}

void loop() {
    Animasyon.runAnimation();           // Animasyonu çalıştır
}
