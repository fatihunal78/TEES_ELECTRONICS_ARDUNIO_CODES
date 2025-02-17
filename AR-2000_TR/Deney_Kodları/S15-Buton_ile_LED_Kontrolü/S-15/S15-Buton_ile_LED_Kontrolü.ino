// S15 - Buton ile LED Kontrolü

int ledPin = 3;      // LED'in bağlandığı dijital pin numarasını tanımla
                     // LEDimizin 3 numaralı dijital pine bağlandığını tanıttık ve ismini ledPin olarak belirledik
                

int butonPin = 2;    // Buton'un bağlandığı dijital pin numarasını tanımla
                     // Butonumuzun 2 numaralı dijital pine bağlandığını tanıttık ve ismini butonPin olarak belirledik

int butonDurumu = 0; // Buton durumunun tutulacağı değişkeni tanımla
                     // Bu değişken ile buton durumunun basılıp ya da basılmadığı durumları kayıt edeceğiz
                    
int ledDurumu = 0;   // LED durumunun tutulacağı değişkeni tanımla
                     // Bu değişken ile LED durumunu yani yanık ya da sönük olma durumunu kayıt edeceğiz

void setup() {
    pinMode(ledPin, OUTPUT);     // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(butonPin, INPUT);    // Buton'un bağlandığı pini giriş olarak ayarla
}

void loop() {
    butonDurumu = digitalRead(butonPin);    // Buton durumunu sorgula ve butonDurumu değişkenine ata
                                            // Daha öncede görmüş olduğumuz gibi digitalRead komutu ile butonun basılıp 
                                            // basılmadığı durumları butonDurumu değişkenine kayıt edeceğiz
                                            // Eğer butona basıldı ise butonDurumu değişkeni HIGH yani 1 değerine sahip olacak
                                       
    // Buton durumuna göre LED'in durumunu ayarla
    if(butonDurumu == HIGH) {               // Eğer Butona basıldı ise
        if(ledDurumu == 0) {                // Eğer ledDurumu değişkeni 0 ise yani LED sönük ise 
            digitalWrite(ledPin, HIGH);      // LED'i yak
            ledDurumu = 1;                  // LED durumunu açık olarak kaydet
                                           // LED şuan yanık konumda olduğu için ledDurumu değişkenini 1 yaptık
                    
            delay(500);                     // 500ms(milisaniye) bekle 
                                           // Butonlu devrelerde genellikle yarım saniye kadar gecikme konulur 
                                           // Bunun sebebi butona basıldığı zaman bir kere değil de birçok kere basılmış 
                                           // gibi davranmasındandır.
                                           // Eğer delay gecikmesini 100 ms yaparsanız butona bastığınız zaman led 
                                           // birden fazla yanıp sönebilir.
                                           // Butonun bu durumuna buton çatırdaması ya da debounce denir. Bu durum 
                                           // genelde delay yardımı ile gecikme konularak önlenir.
        }
        else {                              // Eğer ledDurumu değişkeni 1 ise yani LED yanık ise 
            digitalWrite(ledPin, LOW);       // LED'i söndür
            ledDurumu = 0;                  // LED durumunu kapalı olarak kaydet
                                           // LED şuan sönük olduğu için ledDurumu değişkenini 0 yaptık
            delay(500);                     // 500ms(milisaniye) bekle
                                           // Butonlu devrelerde genellikle yarım saniye kadar gecikme konulur 
                                           // Bunun sebebi butona basıldığı zaman bir kere değil de birçok kere basılmış 
                                           // gibi davranmasındandır.
                                           // Eğer delay gecikmesini 100 ms yaparsanız butona bastığınız zaman led 
                                           // birden fazla yanıp sönebilir.
                                           // Butonun bu durumuna buton çatırdaması ya da debounce denir. Bu durum 
                                           // genelde delay yardımı ile gecikme konularak önlenir.
        }
    }
}

/* --- void loop() altındaki program kodu && (ve) operatörü kullanarak aşağıdaki gibi yapılır.
 * ve (&&) operatörü açıklamada da anlatıldığı gibi iki durumun da kontrol edilmesi halinde gerçekleşir
 * yani aşağıdaki örnekte eğer butona basıldı ve ledDurumu=0 yani led sönük ise şu işlemi yap  
 * Burada butonun basılıp basılmadığını kontrol etmek 1. olay ledin yanık ya da sönük olduğunu kontrol etmek 2. olaydır
    
void loop() {  
    butonDurumu = digitalRead(butonPin);    // Buton durumunu sorgula ve butonDurumu değişkenine ata                                      
                                       
    // Buton durumuna göre LED'in durumunu ayarla
    if(butonDurumu == HIGH && ledDurumu==0) {    // Eğer Butona basıldı ve ledDurumu=0 yani led sönük ise
        digitalWrite(ledPin, HIGH);               // LED'i yak
        ledDurumu = 1;                           // LED durumunu açık olarak kaydet
                                                // LED şuan yanık konumda olduğu için ledDurumu değişkenini 1 yaptık
                    
        delay(500);                              // 500ms(milisaniye) bekle 
    }
    else if (butonDurumu==HIGH && ledDurumu==1) {    // Eğer butona basıldı ve ledDurumu=1 yani led yanık ise 
        digitalWrite(ledPin, LOW);                    // LED'i söndür
        ledDurumu = 0;                               // LED durumunu kapalı olarak kaydet
                                                    // LED şuan sönük olduğu için ledDurumu değişkenini 0 yaptık
        delay(500);                                  // 500ms(milisaniye) bekle             
    }
}
*/
