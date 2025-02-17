// S61 - Analog Termometre

//math.h kütüphanesini ekle
#include <math.h>
//Servo motor kütüphanesini ekle
#include <Servo.h>

//NTC'nin bağlandığı analog pin numarasını tanımla
int ntcPin    = A0;
//NTC değerinin tutulacağı değişkeni tanımla
int analogDeger;
//Servo motorun bağlandığı dijital pin numarasını tanımla
int servoPin  = 5;
//Sıcaklık değerinin tutulacağı değişkeni tanımla
double sicaklik;
//Sıcaklık değerinin servo mototorun acısına göre tanımlanacağı değişken
int oranla;

//Servo isimli bir servo objesi oluşturduk.
Servo servo;  

void setup() {  
    servo.attach(servoPin);    //Servonun 5 numaralı pine bağlandığını tanımla
    servo.write(180);          //Servoyu başlangıçta 180 derece konumuna al
}

void loop() {
    //NTC değerini oku ve analogDeger değişkenine kaydet
    analogDeger = analogRead(ntcPin);
    //ntcHesapla fonksiyonu ile sıcaklık değerini hesapla ve sicaklik değişkenine kaydet
    sicaklik = ntcHesapla(analogDeger); 
    oranla = map(sicaklik, 0, 100, 180, 0);
    servo.write(oranla);
    delay(500);               //500ms bekle
}

//ntcHesapla fonksiyonunu tanımla
double ntcHesapla(int analogOkuma) {
    //NTC özelliklerine göre sıcaklık değerini hesapla
    sicaklik = log(((10240000 / analogOkuma) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;
    //Hesaplanan sıcaklık değerini geri gönder
    return sicaklik;
}