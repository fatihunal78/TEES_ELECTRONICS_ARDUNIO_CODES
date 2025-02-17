// SA59 - LED Matrix ile Işıklı İkaz Tabelası

#include <MaxMatrix.h>                                    //Kütüphaneyi tanımla

int DIN = 4;                                             //DIN pinini tanımla
int CS = 3;                                              //CS pinini tanımla
int CLK = 2;                                             //CLK pinini tanımla

int Led_Matrix_Sayisi = 1;                               //LED matriksler arka arkaya bağlanabilir
                                                         //Birden fazla matriks bağlanacak ise buradaki sayıyı 
                                                         //değiştirebilirsiniz
MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);           //Matriks pinlerinin bağlantıları ile m matriksini tanımla  

char ikaz_tabela[] = {
    8, 8,                                                //İkaz tabelası için ok kodlar
    0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C
};

int bekleme_suresi = 200;                               //LED'lerin yanması için geçen süreyi tutacağımız değişkeni tanımla
int adcPin = A5;                                        //LDR'nin bağlı olduğu pin numarasını tanımla
int okunanDeger;                                        //LDR'den okunan değerin tutulacağı değişkeni tanımla

void setup() {
    m.init();                                           //LED matriksi başlat
    m.setIntensity(8);                                  //Parlaklık ayarı 0 ila 15 arasında ayarlanabilir
}

void loop() {
    okunanDeger = analogRead(adcPin);                   //Analog pine bağlı LDR'deki sinyali oku ve okunanDeger değişkenine kaydet
    
    if (okunanDeger <= 350) {                          //Eğer okunanDeger degiskeni 350 den küçük ise 
                                                       //yani üzerine düşen ışık azaldı ise (gece olduysa) aşağıdaki işlemleri yap
        for (int i = 0; i < 3; i++) {                  //3 kere tekrarlamak için döngü 
                                                       //OK şeklinin başından sonuna kadar yavaş yavaş yanarak gitmesi için 
                                                       //LED'leri tek tek açtık ve aralarına gecikme koy ve 3 kere tekrarla
            m.setDot(0, 3, true);                      //Tek bir LED yakmak için bu fonksiyon kullanılabilir
            m.setDot(0, 4, true); 
            delay(bekleme_suresi);
            
            m.setDot(1, 3, true); 
            m.setDot(1, 4, true); 
            delay(bekleme_suresi);
            
            m.setDot(2, 3, true); 
            m.setDot(2, 4, true); 
            delay(bekleme_suresi);
            
            m.setDot(3, 0, true); 
            m.setDot(3, 1, true); 
            m.setDot(3, 2, true); 
            m.setDot(3, 3, true); 
            m.setDot(3, 4, true); 
            m.setDot(3, 5, true); 
            m.setDot(3, 6, true); 
            m.setDot(3, 7, true); 
            delay(bekleme_suresi);
            
            m.setDot(4, 1, true); 
            m.setDot(4, 2, true); 
            m.setDot(4, 3, true); 
            m.setDot(4, 4, true); 
            m.setDot(4, 5, true); 
            m.setDot(4, 6, true); 
            delay(bekleme_suresi);
            
            m.setDot(5, 2, true); 
            m.setDot(5, 3, true); 
            m.setDot(5, 4, true); 
            m.setDot(5, 5, true);  
            delay(bekleme_suresi);
            
            m.setDot(6, 3, true); 
            m.setDot(6, 4, true); 
            m.setDot(6, 5, true); 
            delay(bekleme_suresi); 
            
            m.setDot(7, 4, true); 
            delay(bekleme_suresi);
            
            m.clear();                                  //Ekranı Temizlemek için gerekli fonksiyon, bütün LED'leri söndür
        }
        
        for (int j = 0; j < 3; j++) {                  //3 kere tekrarlamak için döngü
                                                       //OK şeklini yapmak için gerekli LED'leri tek tek açtık
                                                       //Yarım saniye gecikme ile yanıp söndür ve 3 kere tekrarla
            m.setDot(0, 3, true);                      //Tek bir LED yakmak için bu fonksiyon kullanılabilir
            m.setDot(0, 4, true); 
            m.setDot(1, 3, true); 
            m.setDot(1, 4, true); 
            m.setDot(2, 3, true); 
            m.setDot(2, 4, true); 
            m.setDot(3, 0, true); 
            m.setDot(3, 1, true); 
            m.setDot(3, 2, true); 
            m.setDot(3, 3, true); 
            m.setDot(3, 4, true); 
            m.setDot(3, 5, true); 
            m.setDot(3, 6, true); 
            m.setDot(3, 7, true); 
            m.setDot(4, 1, true); 
            m.setDot(4, 2, true); 
            m.setDot(4, 3, true); 
            m.setDot(4, 4, true); 
            m.setDot(4, 5, true); 
            m.setDot(4, 6, true); 
            m.setDot(5, 2, true); 
            m.setDot(5, 3, true); 
            m.setDot(5, 4, true); 
            m.setDot(5, 5, true);  
            m.setDot(6, 3, true); 
            m.setDot(6, 4, true); 
            m.setDot(6, 5, true); 
            m.setDot(7, 4, true); 
            delay(500);
            
            m.clear();                                  //Ekranı Temizlemek için gerekli fonksiyon, bütün LED'leri söndür
            delay(500);
        }
    }
}
