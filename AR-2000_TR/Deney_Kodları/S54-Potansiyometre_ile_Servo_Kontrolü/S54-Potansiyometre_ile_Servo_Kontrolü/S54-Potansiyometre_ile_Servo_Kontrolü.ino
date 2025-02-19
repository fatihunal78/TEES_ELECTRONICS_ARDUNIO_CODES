// S54 - Potansiyometre ile Servo Kontrolü

#include <Servo.h>                        // Servo kütüphanesini ekle

Servo myservo;                            // Servo kontrol etmek için servo objesi ekle

int potpin = A0;                          // Potansiyometrenin bağlandığı pini tanımla
int val;                                  // Analog pinden ölçülecek değeri tutacağımız değişkeni tanımla

void setup() {
    myservo.attach(5);                    // Servo motorun bağlandığı pini ayarla
}

void loop() {
    val = analogRead(potpin);             // Potansiyometreden okuduğumuz 0 ile 1023 arasındaki değeri val değişkenine kaydet
    
    val = map(val, 0, 1023, 180, 0);      // Val değişkeninde tutulan 0 ile 1023 değerini, servonun yapacağı açı olan 0 ile 180
                                          // değerine oranladık. 1023 değeri 0 derece olacaktır. Eğer val değişkeni 0 yani
                                          // potansiyometre 1. kademede ise servo 180 derecelik açı yapacaktır, val değişkeni
                                          // 512 ise servo 90 derecelik açı yapacaktır.
    
    myservo.write(val);                   // Val değişkeninde bulunan dereceye göre servo motoru döndür
    delay(15);                            // 15ms bekle
}
