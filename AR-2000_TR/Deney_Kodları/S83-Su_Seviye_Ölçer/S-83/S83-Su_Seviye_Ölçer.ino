// S83 - Su Seviye Ölçer

// LED'lerin bağlandığı pin numaralarını tanımla
int YesilLed1   = 5;
int YesilLed2   = 6;
int SariLed     = 7;
int KirmiziLed1 = 8;
int KirmiziLed2 = 9;

int buzzerPin = 4;                    // Buzzerin bağlandığı pin numarasını tanımla

#define trigPin 2                     // HC-SR04 Trigger bacağının bağlandığı pini tanımla
#define echoPin 3                     // HC-SR04 Echo bacağının bağlandığı pini tanımla

int bipSure = 300;                    // Uyarı sesi süresinin tutulacağı değişkeni tanımla 
long sure, mesafe, kap_derinlik, oranla; // sure, mesafe, oranla ve kap_derinlik değişkenlerini tanımla

void mesafe_olc() {                   // Mesafeyi ölçmek için mesafe_olc() fonksiyonu oluştur
    digitalWrite(trigPin, LOW);        // Trigger bacağını sıfıra çek
    delayMicroseconds(2);             // 2 mikro saniye bekle
    digitalWrite(trigPin, HIGH);       // Trigger bacağını 5V'a çek
    delayMicroseconds(10);            // 10 mikro saniye bekle
    digitalWrite(trigPin, LOW);        // Trigger bacağını sıfıra çek
  
    sure = pulseIn(echoPin, HIGH);    // Echo pininden ses sinyalinin geri gelme süresini ölç
    mesafe = (sure/2) * 0.034;        // Ölçülen süreyi ses hızı ile çarparak mesafeyi cm olarak hesapla
}

void setup() {
    // LED'leri çıkış olarak ayarla
    pinMode(YesilLed1, OUTPUT);
    pinMode(YesilLed2, OUTPUT);
    pinMode(SariLed, OUTPUT);
    pinMode(KirmiziLed1, OUTPUT);
    pinMode(KirmiziLed2, OUTPUT);
  
    pinMode(buzzerPin, OUTPUT);        // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(trigPin, OUTPUT);          // Trigger bacağının bağlandığı pini çıkış olarak ayarla  
    pinMode(echoPin, INPUT);           // Echo bacağının bağlandığı pini giriş olarak ayarla

    // Ultrasonik sensörün bağlandığı kabın (Su seviyesinin ölçüleceği kabın) derinliğinin ölçülmesi için 
    // devre kurulup yazılım yüklendikten sonra kabın derinliği ultrasonik sensör yardımı ile ölçülecek 
    // ve referansımız kabın derinliği olacaktır. 
 
    mesafe_olc();                      // mesafe_olc() fonksiyonun çağır ve mesafeyi ölç
    kap_derinlik = mesafe;             // mesafe_olc() fonksiyonunda mesafenin kaydedildiği mesafe 
                                       // değişkenindeki uzunluğu kap_derinlik değişkenine kaydet
    delay(1000);                       // 1 saniye bekle 
}

void loop() {
    mesafe_olc();                      // mesafe_olc() fonksiyonu ile mesafeyi ölç
  
    // Mesafeyi map() fonksiyonu ile LED sayısına oranla ve oranla değişkenine kaydet
    oranla = map(mesafe, 0, kap_derinlik, 5, 0); 
  
    // Mesafe hesaplama işleminin sonucunu LED'lerde göster
    switch (oranla) {
        case 5: {
            // LED'lerin hepsini yak
            digitalWrite(YesilLed1, HIGH);
            digitalWrite(YesilLed2, HIGH);
            digitalWrite(SariLed, HIGH);
            digitalWrite(KirmiziLed1, HIGH);
            digitalWrite(KirmiziLed2, HIGH);
            // Buzzerı sustur
            digitalWrite(buzzerPin, LOW);
            break;
        }
        case 4: {
            // İlk uyarı LED'ini söndür
            digitalWrite(YesilLed1, LOW);
            // Diğer LED'lerin hepsini yak    
            digitalWrite(YesilLed2, HIGH);
            digitalWrite(SariLed, HIGH);
            digitalWrite(KirmiziLed1, HIGH);
            digitalWrite(KirmiziLed2, HIGH);
            // Buzzerı sustur
            digitalWrite(buzzerPin, LOW);
            break;
        }
        case 3: {
            // İlk iki LED'i söndür
            digitalWrite(YesilLed1, LOW);
            digitalWrite(YesilLed2, LOW);
            // Diğer LED'leri yak
            digitalWrite(SariLed, HIGH);
            digitalWrite(KirmiziLed1, HIGH);
            digitalWrite(KirmiziLed2, HIGH); 
            // Buzzerı sustur 
            digitalWrite(buzzerPin, LOW);  
            break;
        }
        case 2: {
            // İlk üç LED'i söndür
            digitalWrite(YesilLed1, LOW);
            digitalWrite(YesilLed2, LOW);
            digitalWrite(SariLed, LOW);
            // Diğer LED'leri yak    
            digitalWrite(KirmiziLed1, HIGH);
            digitalWrite(KirmiziLed2, HIGH);
            // Buzzerı sustur
            digitalWrite(buzzerPin, LOW);
            break;
        }
        case 1: {
            // İlk dört LED'i söndür
            digitalWrite(YesilLed1, LOW);
            digitalWrite(YesilLed2, LOW);
            digitalWrite(SariLed, LOW);
            digitalWrite(KirmiziLed1, LOW);
            // Buzzerı sustur
            digitalWrite(buzzerPin, LOW);
            // Diğer LED'leri yak  
            digitalWrite(KirmiziLed2, HIGH);
            break;
        }
        case 0: {
            // İlk dört LED'i söndür
            digitalWrite(YesilLed1, LOW);
            digitalWrite(YesilLed2, LOW);
            digitalWrite(SariLed, LOW);
            digitalWrite(KirmiziLed1, LOW);
      
            digitalWrite(KirmiziLed2, HIGH);
            digitalWrite(buzzerPin, HIGH);
            delay(200);
            digitalWrite(buzzerPin, LOW);
            digitalWrite(KirmiziLed2, LOW);
            delay(200);
            break;
        }
    }
}
