// SA21 - Uzaktan kumandalı hafızalı kamera

#include <IRremote.h>    //IR alıcı kütüphanesini ekle 
#include <Servo.h>       //Servo motor kütüphanesini ekle 

//Kumanda kodlarını tanımla
#define birTusu   0xFFA25D    //Kumanda 1 tuşu
#define ikiTusu   0xFF629D    //Kumanda 2 tuşu
#define ucTusu    0xFFE21D    //Kumanda 3 tuşu
#define dortTusu  0xFF22DD    //Kumanda 4 tuşu
#define okTusu    0xFF38C7    //Kumanda OK Tuşu

//Joystick X ekseninin bağlandığı pin numarasını tanımla
int xPin = A0;
 
int xPozisyonu = 0;     //Joystick X ekseninin pozisyonunun tutulacağı değişkeni tanımla
int irPin = 2;          //IR alıcı sinyal bacağının bağlandığı pini tanımla
int buzzerPin = 8;      //Buzzer'ın bağlandığı pini tanımla
int servoPin = 5;       //Servo motorun bağlandığı pin numarasını tanımla
int servoAdim = 0;      //Servo adımlarının tutulacağı değişkeni tanımla
int kameraPosizyon = 0; //Kamera pozisyonunun kaydedileceği değişkeni tanımla

int birTusuKayit = 0;
int ikiTusuKayit = 0;
int ucTusuKayit = 0;
int dortTusuKayit = 0;

IRrecv iralici(irPin);  //iralici adında bir IR alıcı tanımla
decode_results sonuc;    //IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla
Servo servo;            //Servo motoru tanımla

void setup() {
    iralici.enableIRIn();         //IR alıcıyı başlat  
    pinMode(buzzerPin, OUTPUT);    //Buzzer'ın bağlandığı pini çıkış olarak ayarla  
    servo.attach(servoPin);        //Servo motorun takıldığı pini tanımla  
    servo.write(90);              //Servo motoru 90 dereceye götür
}
 
void loop() {
    //Joystick X ekseninin pozisyonunun oku ve xPozisyonu değişkenine kaydet
    xPozisyonu = analogRead(xPin);
    
    //xPozisyonu değerini servo açısına göre oranla
    kameraPosizyon = map(xPozisyonu, 0, 1023, 180, 0);
    
    //Servo motorun açısını kameraPosizyon değişkenine göre ayarla
    servo.write(kameraPosizyon);
    
    //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
    if (iralici.decode(&sonuc)) {
        if (sonuc.value == birTusu) {          //1 tuşuna basıldı ise
            birTusuKayit = kameraPosizyon;     //birTusuKayit değişkenine kamera posiysonunu kaydet
            digitalWrite(buzzerPin, HIGH);      //Buzzer'ı öttür
            delay(100);                         //100ms bekle
            digitalWrite(buzzerPin, LOW);       //Buzzer'ı sustur
        }
        else if (sonuc.value == ikiTusu) {     //2 tuşuna basıldı ise
            ikiTusuKayit = kameraPosizyon;     //ikiTusuKayit değişkenine kamera posiysonunu kaydet
            digitalWrite(buzzerPin, HIGH);      //Buzzer'ı öttür
            delay(100);                         //100ms bekle
            digitalWrite(buzzerPin, LOW);       //Buzzer'ı sustur
        }
        else if (sonuc.value == ucTusu) {      //3 tuşuna basıldı ise
            ucTusuKayit = kameraPosizyon;      //ucTusuKayit değişkenine kamera posiysonunu kaydet
            digitalWrite(buzzerPin, HIGH);      //Buzzer'ı öttür
            delay(100);                         //100ms bekle
            digitalWrite(buzzerPin, LOW);       //Buzzer'ı sustur
        }
        else if (sonuc.value == dortTusu) {    //4 tuşuna basıldı ise
            dortTusuKayit = kameraPosizyon;    //dortTusuKayit değişkenine kamera posiysonunu kaydet
            digitalWrite(buzzerPin, HIGH);      //Buzzer'ı öttür
            delay(100);                         //100ms bekle
            digitalWrite(buzzerPin, LOW);       //Buzzer'ı sustur
        }
        else if (sonuc.value == okTusu) {      //ok tuşuna basıldı ise
            digitalWrite(buzzerPin, HIGH);      //Buzzer'ı öttür
            delay(100);                         //100ms bekle
            digitalWrite(buzzerPin, LOW);       //Buzzer'ı sustur
            delay(100);                         //100ms bekle
            digitalWrite(buzzerPin, HIGH);      //Buzzer'ı öttür
            delay(100);                         //100ms bekle
            digitalWrite(buzzerPin, LOW);       //Buzzer'ı sustur
            iralici.resume();
            
            while (1) {
                if (iralici.decode(&sonuc)) {
                    if (sonuc.value == birTusu) {       //1 tuşuna basıldı ise
                        digitalWrite(buzzerPin, HIGH);   //Buzzer'ı öttür
                        delay(50);                       //50ms bekle
                        digitalWrite(buzzerPin, LOW);    //Buzzer'ı sustur
                        servo.write(birTusuKayit);      //birTusuKayit değişkenine kadar motoru döndür
                    }
                    else if (sonuc.value == ikiTusu) {  //2 tuşuna basıldı ise
                        digitalWrite(buzzerPin, HIGH);   //Buzzer'ı öttür
                        delay(50);                       //50ms bekle
                        digitalWrite(buzzerPin, LOW);    //Buzzer'ı sustur
                        servo.write(ikiTusuKayit);      //ikiTusuKayit değişkenine kadar motoru döndür
                    }
                    else if (sonuc.value == ucTusu) {   //3 tuşuna basıldı ise
                        digitalWrite(buzzerPin, HIGH);   //Buzzer'ı öttür
                        delay(50);                       //50ms bekle
                        digitalWrite(buzzerPin, LOW);    //Buzzer'ı sustur
                        servo.write(ucTusuKayit);       //ucTusuKayit değişkenine kadar motoru döndür
                    }
                    else if (sonuc.value == dortTusu) { //4 tuşuna basıldı ise
                        digitalWrite(buzzerPin, HIGH);   //Buzzer'ı öttür
                        delay(50);                       //50ms bekle
                        digitalWrite(buzzerPin, LOW);    //Buzzer'ı sustur
                        servo.write(dortTusuKayit);     //dortTusuKayit değişkenine kadar motoru döndür
                    }
                    else if (sonuc.value == okTusu) {   //ok tuşuna basıldı ise
                        digitalWrite(buzzerPin, HIGH);   //Buzzer'ı öttür
                        delay(50);                       //50ms bekle
                        digitalWrite(buzzerPin, LOW);    //Buzzer'ı sustur
                        delay(50);                       //50ms bekle
                        digitalWrite(buzzerPin, HIGH);   //Buzzer'ı öttür
                        delay(50);                       //50ms bekle
                        digitalWrite(buzzerPin, LOW);    //Buzzer'ı sustur
                        break;
                    }
                    iralici.resume();                    //IR alıcıyı diğer değerleri alabilmesi için sıfırla
                }
            }
        }
        iralici.resume();                               //IR alıcıyı diğer değerleri alabilmesi için sıfırla
    }
    delay(100);                                         //100ms bekle
}
