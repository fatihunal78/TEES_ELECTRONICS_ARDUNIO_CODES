// SA44 - LED Matrixe Giriş

#include <MaxMatrix.h>                         //Kütüphaneyi ekle

int DIN = 4;                                   //DIN pinini tanımla
int CS = 3;                                    //CS pinini tanımla
int CLK = 2;                                   //CLK pinini tanımla

int Led_Matrix_Sayisi = 1;                     //LED matriksler arka arkaya bağlanabilir
                                              //Birden fazla matriks bağlanacak ise buradaki sayıyı değiştirebilirsiniz
MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi); //Matriks pinlerinin bağlantıları ile m matriksini tanımla 

char gulen_yuz[] = {8, 8,                     //Gülen Yüz göstermek için kodlar
    0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C
};

char somurtan_yuz[] = {8, 8,                  //Somurtan Yüz göstermek için kodlar
    0x3C, 0x42, 0xA5, 0xA1, 0xA1, 0xA5, 0x42, 0x3C
};

char uzgun_yuz[] = {8, 8,                     //Üzgün Yüz göstermek için kodlar
    0x3C, 0x42, 0xA5, 0x91, 0x91, 0xA5, 0x42, 0x3C
};

void setup() {
    m.init();           //LED matriksi başlat
    m.setIntensity(8);  //Parlaklık ayarı 0 ila 15 arasında ayarlanabilir
}

void loop() {
    m.writeSprite(0, 0, gulen_yuz);      //Gülen Yüzü LED matrikse aktar 
    delay(1000);
  
    m.writeSprite(0, 0, somurtan_yuz);   //Somurtan Yüzü LED matrikse aktar 
    delay(1000);
  
    m.writeSprite(0, 0, uzgun_yuz);      //Üzgün Yüzü LED matrikse aktar
    delay(1000); 
  
    for (int i = 0; i < 8; i++) {        //Üzgün yüzü sola kaydır
        m.shiftLeft(false, false);
        delay(300);
    }
    m.clear();                           //LED'leri söndür
}
