// SA51 - Güneş Takip Sistemi

#include <Servo.h>                    //Servo motor kütüphanesi ekle

Servo servo_motor;                    //Servo motoru kontrol etmek için obje oluştur
int sagLDR = A4;                      //Sağ taraftaki LDR'nin bağlandığı pini tanımla
int solLDR = A5;                      //Sol taraftaki LDR'nin bağlandığı pini tanımla
int butonPin = 2;                     //Butonun bağlandığı pin numarasını tanımla

int sagLDR_degeri;                    //Sağ LDR degerinin tutulacağı değişkeni tanımla
int solLDR_degeri;                    //Sol LDR degerinin tutulacağı değişkeni tanımla

int error = 0;                        //Sağ ve sol LDR'den okunan değerlerin farkının tutulacağı değişkeni tanımla

int servopozisyonu;                   //Servo motorun pozisyonunun tutulacağı değişkeni tanımla

//Sağ ve Sol LDR'nin setup kısmında anlık havanın aydınlığının okunması için kalibrasyon değerlerinin 
//tutulacağı değişkenleri tanımla
int sagLDR_Kalibrasyon = 0;
int solLDR_Kalibrasyon = 0;

void setup() 
{
    servo_motor.attach(3);            //Servo motorun bağlı olduğunu pini tanımla
    pinMode(butonPin, INPUT_PULLUP);  //Butonun bağlandığı pin numarasını tanımla
    
    servo_motor.write(90);            //Servo motoru başlangıçta 90 derece konumuna getir
    
    //Sağ ve Sol LDR değerlerini oku ve kalibrasyon değişkenlerine kaydet
    sagLDR_Kalibrasyon = analogRead(sagLDR);
    solLDR_Kalibrasyon = analogRead(solLDR);
}

void loop() 
{
    if (digitalRead(butonPin) == LOW) {   //Eğer butona basıldı ise
        while (1) {                        //sonsuz döngüye gir
            sagLDR_degeri = analogRead(sagLDR);    //Sağ sensördeki değeri oku
            solLDR_degeri = analogRead(solLDR);    //Sol sensördeki değeri oku
            
            //İki sensör arasındaki farkı tanımla ve bunu error değişkenine kaydet
            error = sagLDR_degeri - solLDR_degeri;
            
            //error değişkenindeki veriyi servonun dönme açısı olan 180 ile 0 derece arasında oranla
            servopozisyonu = map(error, sagLDR_Kalibrasyon-1023, 1023-solLDR_Kalibrasyon, 180, 0);
            
            servo_motor.write(servopozisyonu);     //Oranlanmış değeri servo motora yazdırarak dönüşü sağla
            delay(50);
        }
    }
} 
