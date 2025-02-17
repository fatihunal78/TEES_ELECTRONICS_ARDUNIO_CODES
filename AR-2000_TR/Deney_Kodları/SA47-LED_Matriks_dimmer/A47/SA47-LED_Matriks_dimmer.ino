// SA47 - LED Matriks dimmer

#include <MaxMatrix.h>                                    //Kütüphaneyi ekle

int DIN = 4;                                             //DIN pinini tanımla
int CS = 3;                                              //CS pinini tanımla
int CLK = 2;                                             //CLK pinini tanımla

int Led_Matrix_Sayisi = 1;                               //LED matriksler arka arkaya bağlanabilir
                                                         //Birden fazla matriks bağlanacak ise buradaki sayıyı 
                                                         //değiştirebilirsiniz
int potPin = A0;                                         //Potansiyometrenin bağlı olduğu pini tanımla
int potDurumu = 0;                                       //Potansiyometrenin değerinin tutulacağı değişkeni tanımla
int parlaklik = 0;                                       //Parlaklık değişkeninin tutulacağı değişkeni tanımla

MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);            //Matriks pinlerinin bağlantıları ile m matriksini tanımla

char KALP[] = {
    8, 8,                                                //Kalp göstermek için kod satırı
    0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C
};

void setup() {
    m.init();                                           //LED matriksi başlat
    m.setIntensity(8);                                  //Parlaklık ayarı 0 ila 15 arasında ayarlanabilir
}

void loop() {
    potDurumu = analogRead(potPin);                     //Potansiyometreden değerleri oku
    parlaklik = map(potDurumu, 0, 1023, 0, 15);        //Potansiyometreden okunan değeri 0 ile 15 arasında oranla 
                                                        //ve parlaklik değişkenine kaydet
    m.writeSprite(0, 0, KALP);                         //Gülen Yüzü LED Matrikse aktar
    m.setIntensity(parlaklik);                         //setIntensity komutu ile LED matriksin parlaklığını ayarla
}
