// SA43 - Uzaktan kumandalı vantilatör

//IR alıcı kütüphanesini ekle
#include <IRremote.h>

//Kumanda kodlarını tanımla
#define birtusu 0xFFA25D    //Kumanda 1 tuşu 
#define ikitusu 0xFF629D    //Kumanda 2 tuşu 
#define uctusu  0xFFE21D    //Kumanda 3 tuşu 
#define OKtusu  0xFF38C7    //Kumanda ok tuşu

int MotorPwm = 9;           //Motorun bağlandığı pin numarasını tanımla
int irPin = 2;              //IR alıcı sinyal bacağın bağlandığı pini tanımla

IRrecv iralici(irPin);      //iralici adında bir IR alıcı tanımla

decode_results sonuc;        //IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

void setup() {
    iralici.enableIRIn();    //IR alıcıyı başlat
    pinMode(MotorPwm, OUTPUT); //LM293'un INPUT2(7 numara) bacağının bağlandığı pini çıkış olarak ayarla 
}

void loop() {
    if (iralici.decode(&sonuc)) {    //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        switch (sonuc.value) {
            case birtusu:
                analogWrite(MotorPwm, 50);    //Motoru 50 PWM hızında döndür, en alt kademe hızı 
                break;
            
            case ikitusu:
                analogWrite(MotorPwm, 100);   //Motoru 100 PWM hızında döndür, orta kademe hızı 
                break;
            
            case uctusu:
                analogWrite(MotorPwm, 255);   //Motoru 255 PWM hızında döndür, üst kademe hızı  
                break;
            
            case OKtusu:
                analogWrite(MotorPwm, 0);     //Motoru durdur
                break;
        }
        iralici.resume();             //IR alıcıyı diğer değerleri alabilmesi için sıfırla 
    }   
    delay(200);                       //200ms bekle
}
