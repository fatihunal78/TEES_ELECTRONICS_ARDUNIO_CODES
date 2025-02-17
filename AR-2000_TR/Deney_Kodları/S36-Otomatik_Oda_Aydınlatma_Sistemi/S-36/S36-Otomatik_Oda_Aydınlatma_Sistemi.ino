// S36 - Otomatik Oda Aydınlatma Sistemi

int kapiPin = 3;     // Kapı kontağının bağlandığı pin numarasını tanımla
int ledPin = 7;      // LED'in bağlandığı pin numarasını tanımla  
int ldrPin = A5;     // LDR'nin bağlandığı analog pin numarasını tanımla
int butonPin = 2;    // Butonun bağlandığı pin numarasını tanımla
int ledDurumu = 0;   // LED durumunun açık ya da kapalı olarak tutacak değişkeni tanımla

void setup() {
    pinMode(ledPin, OUTPUT);         // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(kapiPin, INPUT);         // Kapı kontağının bağlandığı pini giriş olarak ayarla
    pinMode(ldrPin, INPUT);          // LDR'yi giriş pini olarak ayarla
    pinMode(butonPin, INPUT_PULLUP); // Buton giriş pini olarak ayarla, pull up direncini aktif et
}

void loop() {
    if (analogRead(ldrPin) <= 300) {   // Eğer LDR'den okunan değer 300'den küçük ise, yani hava karanlık ise
        if (digitalRead(kapiPin) == LOW) {  // Eğer kapı açıldı ise 
            digitalWrite(ledPin, HIGH);      // LED'i yak 
            ledDurumu = 1;                  // ledDurumu değişkenini kapı açık olarak kaydet
            
            while(1) {                      // Sonsuz döngüye gir 
                butonkontrol();             // İstenildiği zaman buton ile LED'i açıp kapatmak için butonkontrol() fonksiyonunu çağır 
                
                if(digitalRead(kapiPin) == HIGH || analogRead(ldrPin) > 300) {  // Eğer kapı kapandı ise veya hava aydınlık ise 
                    break;                  // Sonsuz döngüyü bitir
                }      
            }      
        }
        else if (digitalRead(kapiPin) == HIGH) {  // Eğer kapı kapalı ise 
            digitalWrite(ledPin, LOW);            // LED'i söndür 
            ledDurumu = 0;                       // ledDurumu değişkenini kapı kapalı olarak kaydet
            
            while(1) {                           // Sonsuz döngüye gir 
                butonkontrol();                  // İstenildiği zaman buton ile LED'i açıp kapatmak için butonkontrol() fonksiyonunu çağır 
                
                if(digitalRead(kapiPin) == LOW || analogRead(ldrPin) > 300) {  // Eğer kapı açık ise veya hava aydınlık ise 
                    break;                       // Sonsuz döngüden çık
                }
            }
        }
    }
    else {                                      // Hava aydınlık ise
        butonkontrol();                        // İstenildiği zaman buton ile LED'i açıp kapatmak için butonkontrol() fonksiyonunu çağır 
    }
}

void butonkontrol() {                          // İstenildiği zaman buton ile LED'i açıp kapatmak için butonkontrol() fonksiyonunu oluştur 
    if (digitalRead(butonPin) == LOW && ledDurumu == 0) {  // Eğer butona basıldı ise ve LED sönük ise 
        digitalWrite(ledPin, HIGH);            // LED'i yak 
        ledDurumu = 1;                        // ledDurumu değişkenini kapı açık olarak kaydet
        while(digitalRead(butonPin) == LOW);  // Butona basılı olduğu sürece bekle
    }
    
    if (digitalRead(butonPin) == LOW && ledDurumu == 1) {  // Eğer butona basıldı ise ve LED yanık ise 
        digitalWrite(ledPin, LOW);             // LED'i söndür 
        ledDurumu = 0;                        // ledDurumu değişkenini kapı kapalı olarak kaydet
        while(digitalRead(butonPin) == LOW);  // Butona basılı olduğu sürece bekle
    }
}
