// SA19 - Şifreli Garaj Kapısı

#include <IRremote.h>    //IR alıcı kütüphanesini ekle
#include <Servo.h>       //Servo motor kütüphanesini ekle

//Kumanda kodlarını tanımla
#define birTusu     0xFFA25D    //Kumanda 1 tuşu
#define ikiTusu     0xFF629D    //Kumanda 2 tuşu
#define ucTusu      0xFFE21D    //Kumanda 3 tuşu
#define dortTusu    0xFF22DD    //Kumanda 4 tuşu
#define kapiAcKapat 0xFF38C7    //Kumanda OK Tuşu

int irPin = 2;          //IR alıcı sinyal bacağının bağlandığı pini tanımla
int buzzerPin = 7;      //Buzzer'ın bağlandığı pini tanımla 
int servoPin = 5;       //Servo motorun bağlandığı pin numarasını tanımla

IRrecv iralici(irPin);  //iralici adında bir IR alıcı tanımla
decode_results sonuc;    //IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla
Servo servo;            //Servo motoru tanımla

int bariyerDurumu = 0;  //Bariyer durumunun tutulacağı değişkeni tanımla
int servoAdim = 90;     //Servo açısının tutulacağı değişkeni tanımla
int sifreSayac = 0;     //Şifre sayaç değerinin tutulacağı değişkeni tanımla

void setup() {
    iralici.enableIRIn();         //IR alıcıyı başlat   
    pinMode(buzzerPin, OUTPUT);   //Buzzer'ın bağlandığı pini çıkış olarak ayarla  
    servo.attach(servoPin);       //Servo motorun takıldığı pini tanımla  
    servo.write(90);              //Servo motoru 90 dereceye götür
    delay(150);                   //150 ms bekle
}

void loop() {
    servo.detach();
    
    //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
    if (iralici.decode(&sonuc)) { 
        switch(sifreSayac) {
            case 0:
                if(sonuc.value == birTusu) {      //1 tuşuna basıldı ise
                    sifreSayac++;                 //sifreSayac değişkenini bir arttır
                    digitalWrite(buzzerPin, HIGH); //Buzzer'ı öttür
                    delay(300);                   //300ms bekle
                    digitalWrite(buzzerPin, LOW);  //Buzzer'ı sustur
                }
                break;
                
            case 1:
                if(sonuc.value == ikiTusu) {      //2 tuşuna basıldı ise
                    sifreSayac++;                 //sifreSayac değişkenini bir arttır
                    digitalWrite(buzzerPin, HIGH); //Buzzer'ı öttür
                    delay(300);                   //300ms bekle
                    digitalWrite(buzzerPin, LOW);  //Buzzer'ı sustur
                }
                break;
                
            case 2:
                if(sonuc.value == ucTusu) {       //3 tuşuna basıldı ise
                    sifreSayac++;                 //sifreSayac değişkenini bir arttır
                    digitalWrite(buzzerPin, HIGH); //Buzzer'ı öttür
                    delay(300);                   //300ms bekle
                    digitalWrite(buzzerPin, LOW);  //Buzzer'ı sustur
                }
                break;
                
            case 3:
                if(sonuc.value == dortTusu) {     //4 tuşuna basıldı ise
                    sifreSayac++;                 //sifreSayac değişkenini bir arttır
                    digitalWrite(buzzerPin, HIGH); //Buzzer'ı öttür
                    delay(300);                   //300ms bekle
                    digitalWrite(buzzerPin, LOW);  //Buzzer'ı sustur
                }
                break;
                
            case 4:
                if(sonuc.value == kapiAcKapat) {
                    servo.attach(servoPin);        //Servo motorun takıldığı pini tanımla  
                    digitalWrite(buzzerPin, HIGH); //Buzzer'ı öttür
                    delay(100);                   //100ms bekle
                    digitalWrite(buzzerPin, LOW);  //Buzzer'ı sustur
                    delay(100);                   //100ms bekle
                    digitalWrite(buzzerPin, HIGH); //Buzzer'ı öttür
                    delay(100);                   //100ms bekle
                    digitalWrite(buzzerPin, LOW);  //Buzzer'ı sustur
                    
                    //Servo motoru 1 derece aralıklarla 180 derece döndür
                    for(servoAdim; servoAdim < 181; servoAdim++) {
                        servo.write(servoAdim);    //servoAdim değişkenine göre servo motoru döndür
                        delay(25);                 //25ms bekle
                    }
                    
                    iralici.resume();             //IR alıcıyı diğer değerleri alabilmesi için sıfırla
                    
                    for(int j = 0; j < 100; j++) { //5sn bekleme döngüsü
                        delay(50);                 //50ms bekle
                        
                        //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
                        if (iralici.decode(&sonuc)) {
                            if(sonuc.value == kapiAcKapat) { //Basılan tuş kapiAcKapat tuşu ise
                                j = 100;                     //j değişkenini 100'e ayarla
                                delay(200);                  //200ms bekle
                            }
                            iralici.resume();               //IR alıcıyı diğer değerleri alabilmesi için sıfırla
                        }
                    }
                    
                    //Servo motoru 1 derece aralıklarla 90 derece doğru terse döndür
                    for(servoAdim; servoAdim > 89; servoAdim--) {
                        servo.write(servoAdim);    //servoAdim değişkenine göre servo motoru döndür
                        delay(25);                 //25ms bekle
                    }
                    sifreSayac = 0;               //sifreSayac değişkenini 0 olarak kaydet
                }
                break;
        }
        iralici.resume();                         //IR alıcıyı diğer değerleri alabilmesi için sıfırla
    }
}
