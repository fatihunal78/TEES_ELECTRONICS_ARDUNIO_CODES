// S85 - Ultrasonik Kasa Güvenlik Alarmı

//HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define trigPin    6
//HC-SR04 Echo bacağının bağlandığı pini tanımla
#define echoPin    7

//Süre ve mesafe değişkenlerini tanımla
long sure, mesafe;
int hoparlorPin = 3;    //Hoparlörün bağlandığı pini tanımla
int ledPin = 2;         //LED'in bağlandığı pini tanımla

void setup() {
    //Trigger bacağının bağlandığı pini çıkış olarak ayarla
    pinMode(trigPin, OUTPUT);
    //Echo bacağının bağlandığı pini giriş olarak ayarla
    pinMode(echoPin, INPUT);
    
    pinMode(hoparlorPin, OUTPUT);    //Hoparlörün bağlandığı pini çıkış olarak ayarla 
    pinMode(ledPin, OUTPUT);         //LED'in bağlandığı pin çıkış olarak ayarla
}

void loop() {
    //Trigger bacağını sıfıra çek
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);    //2 mikro saniye bekle
    
    //Trigger bacağını 5V'a çek
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);    //10 mikro saniye bekle
    
    //Trigger bacağını sıfıra çek
    digitalWrite(trigPin, LOW);
    
    //Echo pininden ses sinyalinin geri gelme süresini ölç
    sure = pulseIn(echoPin, HIGH);
    
    //Ölçülen süreyi ses hızı ile çarparak mesafeyi cm olarak hesapla
    mesafe = (sure/2) * 0.034;
    
    if (mesafe >= 5) {    //Eğer mesafe 5 cm'den büyük ise 
                          //Yani kapak açık ise 
        digitalWrite(ledPin, HIGH);      //LED'i yak 
        tone(hoparlorPin, 200);         //Hoparlörden ses çıkar
        delay(200);                      //200 ms bekle 
        tone(hoparlorPin, 400);         //Hoparlörden farklı bir ses çıkar
        digitalWrite(ledPin, LOW);       //LED'i söndür
    }
    else {    //Eğer mesafe 5 cm'den küçük ise
              //Yani kapak kapalı ise 
        noTone(hoparlorPin);            //Hoparlörü sustur 
        digitalWrite(ledPin, LOW);       //LED'i söndür 
    }
    
    delay(200);    //200 ms bekle
}
