// S66 - Otomatik araç cam sileceği

//Servo motor kütüphanesini ekle
#include <Servo.h>

Servo myservo;                                //Servo motoru kontrol etmek için servo objesi ekle

int sensorPin = 2;                           //Yağmur sensörünün bağlandığı pin numarasını tanımla
int ledPin = 12;                             //Yeşil LED'in bağlandığı pin numarasını tanımla 

void setup() {
    pinMode(sensorPin, INPUT);               //Sensörün bağlandığı pini giriş olarak ayarla
    pinMode(ledPin, OUTPUT);                 //LED'in bağlandığı pini çıkış olarak ayarla
   
    myservo.attach(5);                       //Servo motorun bağlandığı pini ayarla
    myservo.write(0);                        //Servo motorun başlangıç pozisyonunu sıfır (0) olarak ayarla
}

void loop() {
    if (digitalRead(sensorPin) == HIGH) {    //Yağmur sensöründen değer oku
                                            //Eğer sensör değeri 1 ise yani yağmur yağıyor ise 
        digitalWrite(ledPin, HIGH);          //LED'i yak
        
        for (int i = 0; i <= 180; i++) {    //Servo motoru 0 ile 180 derece arasında döndürmek için birer artışlı 
                                            //for döngüsü
            myservo.write(i);               //for döngüsündeki her bir dereceyi servo motora aktar 
            delay(10);                      //10ms bekle 
        }
        
        for (int i = 180; i >= 0; i--) {    //Servoyu 180 ile 0 derece arasında döndürmek için birer azalışlı 
                                            //for döngüsü
            myservo.write(i);               //For döngüsündeki her bir dereceyi servo motora aktar 
            delay(10);                      //10 ms bekle 
        }
    } 
    else {                                  //Eğer yağmur yağmıyor ise 
        myservo.write(0);                   //Servo motoru başlangıç konumuna gönder
        digitalWrite(ledPin, LOW);          //LED'i söndür
    }
}
