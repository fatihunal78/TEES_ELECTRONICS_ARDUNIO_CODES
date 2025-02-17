// SA88 - Disco Light

#include <FreqCount.h>    //Frekans ölçmek için gerekli kütüphaneyi ekle          
float frekans;           //frekans değerinin tutulacağı değişkeni tanımla

int kirmizi_led = 12;    //Disco Light modülü Kırmızı LED'in bağlandığı pin numarasını tanımla
int sari_led = 11;       //Disco Light modülü Sarı LED'in bağlandığı pin numarasını tanımla
int yesil_led = 10;      //Disco Light modülü Yeşil LED'in bağlandığı pin numarasını tanımla
int mavi_led = 9;        //Disco Light modülü Mavi LED'in bağlandığı pin numarasını tanımla
 
void setup() {     
    FreqCount.begin(100); //Frekans ölçümünü başlat ve 100 örnek değer al    
  
    pinMode(kirmizi_led, OUTPUT);    //Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sari_led, OUTPUT);       //Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesil_led, OUTPUT);      //Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(mavi_led, OUTPUT);       //Mavi LED'in bağlandığı pini çıkış olarak ayarla
}
 
void loop() {
    if (FreqCount.available()) {     //Eğer sistem çalışıyor ve değerler geliyorsa
        frekans = FreqCount.read()*10;    //frekans değişkenine ölçülen değeri ata
    }

    int oranla = map(frekans, 60, 10000, 0, 16);

    switch(oranla) {
        case 0:     //oranla değeri 0 olduğunda 
            //Bütün LED'leri söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;

        case 1:     //oranla değeri 1 olduğunda 
            //Kırmızı LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;

        case 2:     //oranla değeri 2 olduğunda 
            //Sarı LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;

        case 3:     //oranla değeri 3 olduğunda 
            //Yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;

        case 4:     //oranla değeri 4 olduğunda 
            //Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;

        case 5:     //oranla değeri 5 olduğunda 
            //Kırmızı ve Sarı LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;

        case 6:     //oranla değeri 6 olduğunda 
            //Kırmızı ve Yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;

        case 7:     //oranla değeri 7 olduğunda 
            //Kırmızı ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;

        case 8:     //oranla değeri 8 olduğunda 
            //Sarı ve Yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;

        case 9:     //oranla değeri 9 olduğunda 
            //Sarı ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;

        case 10:    //oranla değeri 10 olduğunda 
            //Yeşil ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;

        case 11:    //oranla değeri 11 olduğunda 
            //Kırmızı, Sarı ve Yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;

        case 12:    //oranla değeri 12 olduğunda 
            //Kırmızı, Sarı ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;

        case 13:    //oranla değeri 13 olduğunda 
            //Kırmızı, Yeşil ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;

        case 14:    //oranla değeri 14 olduğunda 
            //Sarı, Yeşil ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;

        case 15:    //oranla değeri 15 olduğunda 
            //Bütün LED'leri yak
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;
    }
}
