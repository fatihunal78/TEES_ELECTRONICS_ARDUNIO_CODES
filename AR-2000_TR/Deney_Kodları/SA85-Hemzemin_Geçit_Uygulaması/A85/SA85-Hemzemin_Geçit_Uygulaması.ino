// SA85 - Hemzemin Geçit Uygulaması
#include <Servo.h>                                    //Servo motor kütüphanesini ekle

int servoPin = 2;                                    //Servo motorun bağlandığı pin numarasını tanımla
int buzzerPin = 11;                                  //Buzzerin bağlandığı pini tanımla
#define trigPin 4                                    //HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define echoPin 5                                    //HC-SR04 Echo bacağının bağlandığı pini tanımla

int kirmizi_Led = 8;                                 //Trafik modülündeki Kırmızı LED'in bağlandığı pini tanımla
int sari_Led = 9;                                    //Trafik modülündeki Sarı LED'in bağlandığı pini tanımla
int yesil_Led = 10;                                  //Trafik modülündeki Yeşil LED'in bağlandığı pini tanımla

long sure, mesafe;                                   //Süre ve mesafe değişkenlerini tanımla
unsigned long yenizaman;
unsigned long eskizaman;
int buzzerDurumu = 0;                                //Buzzerin durumunun tutulacağı değişkeni tanımla
Servo servo;                                         //Servo motor değişkenini tanımla

void setup() {
    pinMode(kirmizi_Led, OUTPUT);                    //Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sari_Led, OUTPUT);                       //Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesil_Led, OUTPUT);                      //Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(trigPin, OUTPUT);                        //Trigger bacağının bağlandığı pini çıkış olarak ayarla 
    pinMode(echoPin, INPUT);                         //Echo bacağının bağlandığı pini giriş olarak ayarla
    pinMode(buzzerPin, OUTPUT);                      //Buzzerın bağlandığı pini çıkış olarak ayarla
    servo.attach(servoPin);                         //Servo motorun takıldığı pini tanımla  
    servo.write(90);                                //Servo motoru 90 dereceye götür
    digitalWrite(yesil_Led, HIGH);                   //Başlangıçta Yeşil LED'i yak 
}

void loop() {
    mesafe_olc();                                   //Mesafeyi ölçmek için mesafe_olc fonksiyonunu çağır
    digitalWrite(buzzerPin, LOW);
    
    if (mesafe <= 5) {                              //Eğer mesafe 5 cm'den küçük ise, yani tren geliyor ise 
        for (int i = 90; i >= 0; i--) {             //Bariyeri araçlara kapat
            servo.write(i);
            digitalWrite(yesil_Led, LOW);            //Yeşil LED'i söndür 
            delay(30);
            yenizaman = millis();
            
            if (yenizaman - eskizaman > 500) {
                if (buzzerDurumu == 0) {
                    digitalWrite(buzzerPin, HIGH);
                    digitalWrite(kirmizi_Led, HIGH); 
                    buzzerDurumu = 1;
                } else {
                    digitalWrite(buzzerPin, LOW);
                    digitalWrite(kirmizi_Led, LOW); 
                    buzzerDurumu = 0;
                }
                eskizaman = yenizaman;
            }
        }
        
        while (mesafe <= 5) {                       //Eğer hala tren geçiyor ise 
            mesafe_olc();                           //Mesafe'yi kontrol etmek için mesafe_olc() fonksiyonunu çağır
            yenizaman = millis();
            
            if (yenizaman - eskizaman > 500) {
                if (buzzerDurumu == 0) {
                    digitalWrite(buzzerPin, HIGH);
                    digitalWrite(kirmizi_Led, HIGH); 
                    buzzerDurumu = 1;
                } else {
                    digitalWrite(buzzerPin, LOW);
                    digitalWrite(kirmizi_Led, LOW); 
                    buzzerDurumu = 0;
                }
                eskizaman = yenizaman;
            }
            delay(100);
        }
        
        if (mesafe > 5) {                          //Eğer mesafe 5 cm'den büyük ise, yani tren yok ise 
            digitalWrite(buzzerPin, LOW);
            digitalWrite(kirmizi_Led, HIGH); 
            delay(5000);
         
            if (mesafe > 5) {                      //Eğer mesafe 5 cm'den büyük ise, yani tren yok ise 
                for (int i = 0; i <= 90; i++) {    //Bariyeri aç, araçların geçişine izin ver 
                    servo.write(i);
                    delay(30);
                    
                    yenizaman = millis();
                    if (yenizaman - eskizaman > 500) {
                        if (buzzerDurumu == 0) {
                            digitalWrite(sari_Led, HIGH); 
                            digitalWrite(kirmizi_Led, LOW);  //Bariyer açıkken kırmızı LED'i söndür
                            buzzerDurumu = 1;
                        } else {
                            digitalWrite(buzzerPin, LOW);
                            digitalWrite(sari_Led, LOW); 
                            buzzerDurumu = 0;
                        }
                        eskizaman = yenizaman;
                    }
                }
            } 
            digitalWrite(yesil_Led, HIGH);          //Bariyer açıkken Yeşil LED'i yak
            digitalWrite(sari_Led, LOW);            //Bariyer açıkken Sarı LED'i söndür
            digitalWrite(kirmizi_Led, LOW);         //Bariyer açıkken Kırmızı LED'i söndür
        }
    }
}

void mesafe_olc() {                                //mesafe_olc() fonksiyonunu oluştur
    digitalWrite(trigPin, LOW);                    //Trigger bacağını sıfıra çek
    delayMicroseconds(2);                         //2 mikro saniye bekle  
    digitalWrite(trigPin, HIGH);                   //Trigger bacağını 5V'a çek
    delayMicroseconds(10);                        //10 mikro saniye bekle  
    digitalWrite(trigPin, LOW);                    //Trigger bacağını sıfıra çek

    sure = pulseIn(echoPin, HIGH);                //Echo pininden geri gelme süresini ölç 
    mesafe = (sure/2) * 0.034;                    //Ölçülen süreyi ses hızı ile çarparak mesafeyi cm olarak hesapla
    return mesafe;
}
