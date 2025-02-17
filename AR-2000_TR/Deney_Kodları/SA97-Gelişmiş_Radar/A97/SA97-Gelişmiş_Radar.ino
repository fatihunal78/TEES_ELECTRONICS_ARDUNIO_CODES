// SA97 - Gelişmiş Radar

#include <Servo.h>                                    //Servo motor kütüphanesini ekle 

const int trigPin   = 3;                             //Ultrasonik sensörün trigger pininin bağlandığı pini tanımla
const int echoPin   = 4;                             //Ultrasonik sensörün echo pininin bağlandığı pini tanımla
int buzzerPin       = 9;                             //Buzzerin bağlandığı pin numarasını tanımla

long sure;                                           //Süre ölçümünün kağıt edileceği sure değişkeni tanımla
int mesafe;                                         //Mesafe ölçümünün kayıt edileceği mesafe değişkeni tanımla
int butonPin       = 2;                             //Butonun bağlandığı pin numarasını tanımla
int butonDurumu    = 0;                             //Buton durumunun tutulacağı değişkeni tanımla ve ilk durumu 0 yap

Servo servo_kontrol;                                //Servo motoru kontrol etmek için servo_kontrol objesi oluştur

unsigned long yenizaman = 0;
unsigned long eskizaman = 0;

void setup() {
    pinMode(trigPin, OUTPUT);                       //Trigger pinini çıkış olarak ayarla
    pinMode(echoPin, INPUT);                        //Echo pinini giriş olarak ayarla
    pinMode(butonPin, INPUT);                       //Buton pinini giriş olarak ayarla
    pinMode(buzzerPin, OUTPUT);                     //Buzzerın bağlandığı pini çıkış olarak ayarla
    Serial.begin(9600);                            //Seri haberleşmeyi başlat
    servo_kontrol.attach(8);                       //Servo motorun tetik pininin bağlandığı pini tanımla
}

void loop() {
    if (digitalRead(butonPin) == HIGH && butonDurumu == 0) {
        butonDurumu = 1;
        while (1) {
            if (digitalRead(butonPin) == HIGH && butonDurumu == 1) {
                butonDurumu = 0;
                break;
            }
            
            for (int i = 25; i <= 145; i++) {      //Servo motorun 25 ile 145 derece hareketi için for döngüsü kullanıldı
                servo_kontrol.write(i);             //Servo motoru 25 dereceden 145 derece hareket ettiliyor
                delay(30);
                mesafe = mesafe_hesapla();          //Mesafe_hesapla fonksiyonunu çağır ve oradaki değeri mesafe değişkenine kaydet
        
                Serial.print(i);                    //Servo motorun anlık açısını seri porta gönder
                Serial.print(",");                  //Seri porta "," işareti gönder
                Serial.print(mesafe);               //Mesafe değişkenini seri porta gönder
                Serial.print(".");                  //Seri porta verilerin bittiğini anlaması için "." işareti gönder
        
                yenizaman = millis();
                if (yenizaman - eskizaman >= 2000) {
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    delay(100);
                    eskizaman = yenizaman;   
                }
            }
            
            for (int i = 145; i > 25; i--) {       //Servo motorun ters yönde hareketi için for döngüsü kullandık
                servo_kontrol.write(i);             //Servo motoru hareket ettir
                delay(30);
                mesafe = mesafe_hesapla();          //Mesafe_hesapla fonksiyonunu çağır ve oradaki değeri mesafe değişkenine kaydet
                
                Serial.print(i);                    //Servo motorun anlık açısını seri porta gönder
                Serial.print(",");                  //Seri porta "," işareti gönder
                Serial.print(mesafe);               //Mesafe değişkenini seri porta gönder
                Serial.print(".");                  //Seri porta verilerin bittiğini anlaması için "." işareti gönder
        
                yenizaman = millis();
                if (yenizaman - eskizaman >= 2000) {
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    delay(100);
                    eskizaman = yenizaman;   
                }
            }
        }
    }
}

int mesafe_hesapla() {                             //Mesafeyi hesaplamak için mesafe_hesapla fonksiyonu oluştur
    digitalWrite(trigPin, LOW);                    //Ultrasonik sensörün trigger pinini LOW yap
    delayMicroseconds(2);                         //2 mikro saniye bekle
    digitalWrite(trigPin, HIGH);                   //Ultrasonik sensörün trigger pinini HIGH yap
    delayMicroseconds(10);                        //10 mikro saniye bekle
    digitalWrite(trigPin, LOW);                    //Trigger pini LOW yap
    sure = pulseIn(echoPin, HIGH);                //Echo pindeki değeri oku, ve gidiş dönüş süresini hesapla. 
                                                  //Bu süreyi sure değişkenine kaydet
    mesafe = sure * 0.034 / 2;                    //Mesafeyi hesaplamak için, gidiş dönüş toplam süre olduğu için 
                                                  //ikiye böl ve 0.034 ses hızı ile çarp
    return mesafe;                                //Mesafe değişkenini döndür
}