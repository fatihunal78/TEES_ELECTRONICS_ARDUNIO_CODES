// S75 - Termostatlı Vantilatör

//math.h kütüphanesini ekle
#include <math.h>

//LED'in bağlandığı pin numarasını tanımla
int ledPin = 7;
//Transistörün bağlandığı pin numarasını tanımla
int transistorPin = 2;
//NTC'nin bağlandığı analog pin numarasını tanımla
int ntcPin = A5;
//Potun bağlandığı analog pin numarasını tanımla
int potPin = A1;
//Potansiyometre değerinin kaydedileceği değişkeni tanımla
int potDegeri = 0;
//Ayarlanan sıcaklık değerinin kaydedileceği değişkeni tanımla
double ayarlananSicaklik = 0;
//NTC değerinin tutulacağı değişkeni tanımla
int analogDeger;
//Sıcaklık değerinin tutulacağı değişkeni tanımla
double sicaklik;

void setup() {
    //Seri portu 9600 baud rate ile bağlat
    Serial.begin(9600);
    //Transistörün bağlandığı pini çıkış olarak ayarla
    pinMode(transistorPin, OUTPUT);
    //LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(ledPin, OUTPUT);
}

//ntcHesapla fonksiyonunu tanımla
double ntcHesapla(int analogOkuma) {
    double sicaklik;
    sicaklik = log(((10240000 / analogOkuma) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;
    return sicaklik;
}

void loop() {
    //NTC değerini oku ve analogDeger değişkenine kaydet
    analogDeger = analogRead(ntcPin);
    //ntcHesapla fonksiyonu ile sıcaklık değerini hesapla ve sicaklik değişkenine kaydet
    sicaklik = ntcHesapla(analogDeger);
    
    potDegeri = analogRead(potPin);
    ayarlananSicaklik = (float)(map(potDegeri, 0, 1023, 500, 150)) / 10;
    
    //Okunan ve hesaplanan değerleri seri port ekranına gönder
    Serial.print("Ayarlanan Sıcaklık :");
    Serial.print(ayarlananSicaklik);
    Serial.print(" - ");
    Serial.print("Ölçülen Sıcaklık :");
    Serial.println(sicaklik);
    
    if (sicaklik > ayarlananSicaklik) {
        digitalWrite(transistorPin, HIGH);  //Transistörü iletime geçir
        digitalWrite(ledPin, HIGH);         //LED'i yak
    } else {
        digitalWrite(transistorPin, LOW);   //Transistörü kesime sok
        digitalWrite(ledPin, LOW);          //LED'i söndür
    }
    
    delay(500);  //500ms bekle
}