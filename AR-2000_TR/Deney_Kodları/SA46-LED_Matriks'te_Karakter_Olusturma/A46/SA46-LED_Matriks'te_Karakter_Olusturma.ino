// SA46 - LED Matriks'te Karakter Olusturma

#include <MaxMatrix.h>                         //Kütüphaneyi ekle

int DIN = 4;                                   //DIN pinini tanımla
int CS = 3;                                    //CS pinini tanımla
int CLK = 2;                                   //CLK pinini tanımla

int Led_Matrix_Sayisi = 1;                     //LED matriksler arka arkaya bağlanabilir
                                              //Birden fazla matriks bağlanacak ise buradaki sayıyı 
                                              //değiştirebilirsiniz
MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi); //Matriks pinlerinin bağlantıları ile m matriksini tanımla

char KALP[] = {
    8, 8,                                      //Kalp göstermek için kodlar
                                              //Buradaki kod satırı yerine kendi oluşturduğunuz kodu 
                                              //yapıştırabilirsiniz
    0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C
};

void setup() {
    m.init();                                  //LED matriksi başlat
    m.setIntensity(8);                        //Parlaklık ayarı 0 ila 15 arasında ayarlanabilir
}

void loop() {
    m.writeSprite(0, 0, KALP);                //Kalp simgesini LED Matrikse Aktar 
    delay(1000);                              //1 saniye bekle
    m.clear();                                //LED'leri söndür 
    delay(1000);                              //1 saniye bekle
}
