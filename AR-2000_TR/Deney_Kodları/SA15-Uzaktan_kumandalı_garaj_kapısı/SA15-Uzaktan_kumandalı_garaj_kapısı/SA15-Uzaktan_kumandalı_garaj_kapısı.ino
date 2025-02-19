// SA15 - Uzaktan kumandalı garaj kapısı

#include <IRremote.h>    // IR alıcı kütüphanesini ekle
#include <Servo.h>       // Servo motor kütüphanesini ekle

#define kapiAcKapat 0xFF38C7    // Kumanda OK Tuşu

int irPin = 2;          // IR alıcı sinyal bacağının bağlandığı pini tanımla
int buzzerPin = 7;      // Buzzer'ın bağlandığı pini tanımla 
int servoPin = 5;       // Servo motorun bağlandığı pin numarasını tanımla

IRrecv iralici(irPin);  // iralici adında bir IR alıcı tanımla

decode_results sonuc;    // IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla
 
Servo servo;            // Servo motoru tanımla

int kapiDurumu = 0;     // Kapı durumunun tutulacağı değişkeni tanımla

void setup()
{
    iralici.enableIRIn();         // IR alıcıyı başlat   
    pinMode(buzzerPin, OUTPUT);   // Buzzer'ın bağlandığı pini çıkış olarak ayarla  
    servo.attach(servoPin);       // Servo motorun bağlandığı pini tanımla  
    servo.write(90);              // Servo motoru 90 dereceye döndür  
}

void loop() 
{
    // IR alıcıdan bir bilgi gelip gelmediğini kontrol et
    if (iralici.decode(&sonuc)) 
    { 
        if (sonuc.value == kapiAcKapat && kapiDurumu == 0) {    // Eğer kumandanın OK tuşuna basıldı ise ve kapı kapalı ise 
            digitalWrite(buzzerPin, HIGH);    // Buzzerdan ses çıkar 
            delay(50);                        // 50ms bekle 
            digitalWrite(buzzerPin, LOW);     // Buzzerı sustur 
            kapiDurumu = 1;                  // kapiDurumu değişkenini kapı açık olarak kaydet 
       
            // Kapıyı açmak için i değişkenini 90 dereceden 180 dereceye doğru birer arttır  
            for (int i = 90; i <= 180; i++) 
            {
                servo.write(i);              // Servo motora yaz 
                delay(30);                   // 30ms gecikme
            }
        }
        else if (sonuc.value == kapiAcKapat && kapiDurumu == 1) {    // Eğer kumandanın OK tuşuna basıldı ise ve kapı açık ise       
            digitalWrite(buzzerPin, HIGH);    // Buzzerdan ses çıkar 
            delay(50);                        // 50ms bekle 
            digitalWrite(buzzerPin, LOW);     // Buzzerı sustur 
            kapiDurumu = 0;                  // kapiDurumu değişkenini kapı kapalı olarak kaydet 
      
            // Kapıyı kapatmak için i değişkenini 180 dereceden 90 dereceye birer azaltarak
            for (int i = 180; i >= 90; i--) 
            {
                servo.write(i);              // Servo motora yaz 
                delay(30);                   // 30ms gecikme
            }
        }
        iralici.resume();    // IR alıcıyı diğer değerleri alabilmesi için sıfırla  
    }
}
