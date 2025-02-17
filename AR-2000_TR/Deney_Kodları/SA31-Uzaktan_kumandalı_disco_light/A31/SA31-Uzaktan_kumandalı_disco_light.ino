// SA31 - Uzaktan kumandalı disco light

//IR alıcı kütüphanesini ekle
#include <IRremote.h>

//Kumanda kodlarını tanımla
#define birtusu     0xFFA25D      //Kumanda 1 tuşu 
#define ikitusu     0xFF629D      //Kumanda 2 tuşu 
#define uctusu      0xFFE21D      //Kumanda 3 tuşu 
#define dorttusu    0xFF22DD      //Kumanda 4 tuşu 
#define bestusu     0xFF02FD      //Kumanda 5 tuşu 
#define altitusu    0xFFC23D      //Kumanda 6 tuşu 
#define yeditusu    0xFFE01F      //Kumanda 7 tuşu 
#define sekiztusu   0xFFA857      //Kumanda 8 tuşu 
#define dokuztusu   0xE5CFBD7F    //Kumanda 9 tuşu 
#define yildiztusu  0xFF6897      //Kumanda * tuşu 
#define sifirtusu   0xFF9867      //Kumanda 0 tuşu 
#define karetusu    0xFFB04F      //Kumanda # tuşu 
#define yukaritusu  0xFF18E7      //Kumanda yukarı yön tuşu 
#define asagitusu   0xFF4AB5      //Kumanda aşağı yön tuşu 
#define sagtusu     0xFF5AA5      //Kumanda sağ ok tuşu
#define soltusu     0xFF10EF      //Kumanda sol ok tuşu
#define OKtusu      0xFF38C7      //Kumanda ok tuşu
#define tekrar      0xFFFFFFFF    //Basılan tuşa sürekli basılırsa

int mavi_Led = 3;      //Mavi LED'in bağlandığı pini tanımla
int yesil_Led = 4;     //Yeşil LED'in bağlandığı pini tanımla
int SariLed = 5;       //Sarı LED'in bağlandığı pini tanımla
int kirmizi_Led = 6;   //Kırmızı LED'in bağlandığı pini tanımla

int irPin = 2;         //IR alıcı sinyal bacağının bağlandığı pini tanımla

IRrecv iralici(irPin); //iralici adında bir IR alıcı tanımla

decode_results sonuc;  //IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

void setup() {
    iralici.enableIRIn();          //IR alıcıyı başlat
    
    //LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(mavi_Led, OUTPUT);
    pinMode(yesil_Led, OUTPUT);
    pinMode(SariLed, OUTPUT);
    pinMode(kirmizi_Led, OUTPUT);
}

void loop() {
    if (iralici.decode(&sonuc)) {  //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        iralici.resume();          //IR alıcıyı diğer değerleri alabilmesi için sıfırla 
    }     

    if (sonuc.value == birtusu) {          //Eğer kumandanın 1 tuşuna basıldı ise 
        digitalWrite(mavi_Led, HIGH);       //Mavi LED'i yak
        //Diğer LED'leri söndür 
        digitalWrite(yesil_Led, LOW);
        digitalWrite(SariLed, LOW);
        digitalWrite(kirmizi_Led, LOW);
    }
    else if (sonuc.value == ikitusu) {     //Eğer kumandanın 2 tuşuna basıldı ise 
        digitalWrite(yesil_Led, HIGH);      //Yeşil LED'i yak
        //Diğer LED'leri söndür 
        digitalWrite(mavi_Led, LOW);
        digitalWrite(SariLed, LOW);
        digitalWrite(kirmizi_Led, LOW);
    }
    else if (sonuc.value == uctusu) {      //Eğer kumandanın 3 tuşuna basıldı ise 
        digitalWrite(SariLed, HIGH);        //Sarı LED'i yak
        //Diğer LED'leri söndür 
        digitalWrite(mavi_Led, LOW);
        digitalWrite(yesil_Led, LOW);
        digitalWrite(kirmizi_Led, LOW);
    }
    else if (sonuc.value == dorttusu) {    //Eğer kumandanın 4 tuşuna basıldı ise 
        digitalWrite(kirmizi_Led, HIGH);    //Kırmızı LED'i yak
        //Diğer LED'leri söndür 
        digitalWrite(mavi_Led, LOW);
        digitalWrite(yesil_Led, LOW);
        digitalWrite(SariLed, LOW);
    }
    else if (sonuc.value == bestusu) {     //Eğer kumandanın 5 tuşuna basıldı ise bütün LED'leri yak
        //Diğer LED'leri yak
        digitalWrite(kirmizi_Led, HIGH); 
        digitalWrite(mavi_Led, HIGH);
        digitalWrite(yesil_Led, HIGH);
        digitalWrite(SariLed, HIGH);
    }
    else if (sonuc.value == sifirtusu) {   //Eğer sıfır tuşuna basıldı ise 
        //LED'leri söndür 
        digitalWrite(mavi_Led, LOW); 
        digitalWrite(yesil_Led, LOW);
        digitalWrite(SariLed, LOW);
        digitalWrite(kirmizi_Led, LOW);
    }  
    
    delay(200);                            //200ms bekle 
}
