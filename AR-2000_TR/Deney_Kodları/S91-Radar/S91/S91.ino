// S91 - Radar

#include <Servo.h>                    // Servo motor kütüphanesini ekle 

const int trigPin = 4;                // HC-SR04 Trigger bacağının bağlandığı pini tanımla
const int echoPin = 5;                // HC-SR04 Echo bacağının bağlandığı pini tanımla
const int ledPin = 8;                 // Kırmızı LED'in bağlandığı pini tanımla
int hoparlorPin = 2;                  // Hoparlörün bağlandığı pini tanımla
int butonPin = 9;                     // Butonun bağlandığı pini tanımla

int butonDurumu = 0;                  // Buton durumunun tutulacağı değişkeni tanımla ve ilk durumunu 0 yap

// Süre ve mesafe değişkenlerini tanımla
long sure; 
int mesafe;

Servo myServo;                        // Servo motor kontrolü için myServo isimli bir obje oluştur

void setup() {
    pinMode(trigPin, OUTPUT);         // Trigger bacağının bağlandığı pini çıkış olarak ayarla
    pinMode(echoPin, INPUT);          // Echo bacağının bağlandığı pini giriş olarak ayarla
    pinMode(ledPin, OUTPUT);          // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);     // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(butonPin, INPUT_PULLUP);  // Butonun bağlandığı pini giriş olarak ayarla ve pull up direncini aktif et
    myServo.attach(3);               // Servo motorun sinyal bacağının bağlandığı pini tanımla
}

void loop() {
    if (digitalRead(butonPin) == LOW && butonDurumu == 0) {
        butonDurumu = 1;
        while (1) {
            if (digitalRead(butonPin) == LOW && butonDurumu == 1) { 
                butonDurumu = 0; 
                break;
            }
            // Servo motoru 25 ile 145 derece arasında tarama yaptırmak için 
            for (int i = 25; i <= 145; i++) {    // for döngüsünde i değerini 25 den 145'e kadar birer arttırarak git
                myServo.write(i);                // i değerine kadar servo motoru döndür
                delay(20);                       // 20 ms bekle
                mesafe = mesafe_olc();           // mesafe_olc() fonksiyonunu çağır ve mesafe_olc fonksiyonunda 
                                                // döndürülen mesafe değerini mesafe değişkenine kaydet
                                                // mesafe_olc() fonksiyonu, return komutu ile mesafe fonksiyonu 
                                                // icerisinde hesaplanan değeri geri gönderir
                        
                if (mesafe <= 30) {             // Eğer ölçülen mesafe değeri 30cm'den küçük ise 
                                                // yani servo motor dönerken ultrasonik sensörün 30 cm önüne engel gelirse
                     
                    digitalWrite(ledPin, HIGH);  // Kırmızı LED'i yak 
                    tone(hoparlorPin, 500);     // Hoparlörden ses çıkar 
                    delay(50);                  // 50 ms bekle 
                    digitalWrite(ledPin, LOW);   // Kırmızı LED'i söndür 
                    noTone(hoparlorPin);        // Hoparlörü sustur
                    delay(50);                  // 50 ms bekle 
                }
            }
    
            // Servo motorun ters yönde yani 145 dereceden 25 dereceye tarama yapması için
            for (int i = 145; i > 25; i--) {    // for döngüsünde i değerini 145 den 25'e kadar birer azaltarak git
                myServo.write(i);               // i değerine kadar servo motoru döndür
                delay(20); 
                mesafe = mesafe_olc();          // mesafe_olc() fonksiyonunu çağır ve mesafe_olc fonksiyonunda 
                                               // döndürülen mesafe değerini mesafe değişkenine kaydet
                                               // mesafe_olc() fonksiyonu, return komutu ile mesafe fonksiyonu 
                                               // icerisinde hesaplanan değeri geri gönderir
                          
                if (mesafe <= 30) {            // Eğer ölçülen mesafe değeri 30cm'den küçük ise 
                                               // Yani servo motor dönerken ultrasonik sensörün 30 cm önüne engel gelirse
                       
                    digitalWrite(ledPin, HIGH); // Kırmızı LED'i yak 
                    tone(hoparlorPin, 500);    // Hoparlörden ses çıkar 
                    delay(50);                 // 50 ms bekle 
                    digitalWrite(ledPin, LOW);  // Kırmızı LED'i söndür 
                    noTone(hoparlorPin);       // Hoparlörü sustur
                    delay(50);                 // 50 ms bekle 
                }
            } 
        }
    }
}

// Ultrasonik sensör yardımı ile mesafeyi ölçmek için 
// Daha önce'de mesafe ölçer deneyinde gördüğümüz gibi
// Trigger ve echo pinlerini aç kapa yaparak mesafeyi ölçüyoruz
int mesafe_olc() {                    // mesafe_olc() fonksiyonunu tanımla
    digitalWrite(trigPin, LOW);       // Trigger pini LOW 'a çek 
    delayMicroseconds(2);            // 2 mikrosaniye bekle 
    digitalWrite(trigPin, HIGH);      // Trigger pini HIGH yap
    delayMicroseconds(10);           // 10 mikrosaniye bekle
    digitalWrite(trigPin, LOW);       // Trigger pini LOW yap
    sure = pulseIn(echoPin, HIGH);   // Echo pinini HIGH yap ve ölçülen süreyi sure değişkenine kaydet
    
    mesafe = sure * 0.034 / 2;       // Yol = hız* zaman formülünü kullanarak mesafeyi bul
                                     // Burada sure ultrasonik sensörden okuduğumuz değer ve ses sinyalinin 
                                     // gidip gelme süresi olduğu için 2 ye böldük
                                     // 0.034 ise sesin hızıdır. Ses saniyede 342.2 metre yol alır.
                        
    return mesafe;                   // Fonksiyonu çağıran satıra mesafe değişkenini döndür 
}
