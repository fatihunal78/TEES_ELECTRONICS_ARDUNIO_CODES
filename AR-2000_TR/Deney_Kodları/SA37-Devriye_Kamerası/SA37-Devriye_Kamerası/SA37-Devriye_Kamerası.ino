// SA37 - Devriye Kamerası

#include <Servo.h>                                    // Servo kütüphanesini ekle 

int butonPin = 2;                                    // Joystick butonunun bağlandığı pin numarasını tanımla
int joystick_y = A5;                                 // Joystiğin y ekseninin bağlandığı analog pini tanımla
int servoPin = 3;                                    // Servo motorun bağlandığı pin numarasını tanımla
int butondurumu = 0;                                 // Buton durumunun tutulacağı değişkeni tanımla

int y_ekseni;                                        // Joystick y eksenindeki değerlerin tutulacağı değişkeni tanımla
Servo servo;                                         // Servo motor kontrolü için servo isimli bir obje oluştur

void setup() {
    pinMode(butonPin, INPUT_PULLUP);                 // Butonun bağlandığı pini giriş olarak ayarla
    servo.attach(servoPin);                          // Servo motorun bağlandığı pini ayarla
    servo.write(90);                                 // Başlangıçta servo motoru 90 derece konumuna getir
}

void loop() {
    if (butondurumu == 0) {                         // Eğer butondurumu değişkeni 0 ise
        while (1) {                                 // Sonsuz döngüye gir
            if (digitalRead(butonPin) == LOW) {     // Eğer butona basıldı ise
                butondurumu = 1;                    // butondurumu değişkenini 1 yap
                break;                              // sonsuz döngüyü bitir
            }
            y_ekseni = analogRead(joystick_y);      // Joystiğin pozisyonuna göre analog pindeki değeri oku
            int oranla = map(y_ekseni, 0, 1023, 
                           145, 25);                 // Okunan 0 ile 1023 arasındaki değeri 25 ile 145 derece arasında oranla
            servo.write(oranla);                    // Oranlanmış açısal değeri servo motora aktar
        }
    }
    else if (butondurumu == 1) {                   // Eğer butondurumu değişkeni 1 ise
        while (1) {                                // sonsuz döngüye gir
            if (digitalRead(butonPin) == LOW || 
                butondurumu == 0) {                // Eğer butona basıldı ise ya da butondurumu değişkeni 0 ise
                butondurumu = 0;                   // butondurumu değişkenini 0 yap
                break;                             // sonsuz döngüyü bitir
            }
            
            // Servo motoru 25 ile 145 derece arasında tarama yaptırmak için for döngüsünde i değerini 
            // 25 den 145'e birer arttırarak git
            for (int i = 25; i <= 145; i++) {
                if (digitalRead(butonPin) == LOW) { // Butona basıldı ise
                    butondurumu = 0;               // butondurumu değişkenini 0 yap
                    break;                         // for döngüsünü bitir
                }
                servo.write(i);                    // i değerini servo motora yaz
                delay(60);                         // 60 ms gecikme
            }
            
            // Servo motorun ters yönde yani 145 dereceden 25 dereceye tarama yapması için
            // Yukarıdaki işlemleri ters dönüş işlemindede yapıyoruz
            for (int i = 145; i > 25; i--) {
                if (digitalRead(butonPin) == LOW) { // Butona basıldı ise
                    butondurumu = 0;               // butondurumu değişkenini 0 yap
                    break;                         // for döngüsünü bitir
                }
                servo.write(i);                    // i değerini servo motora yaz
                delay(60);                         // 60 ms gecikme
            }
            delay(100);
        }
    }
}
