// S94 - Elektronik kantar

int sensorPin = A5;       // Sensörün bağlandığı pin numarasını tanımla

double okunandeger;       // Sensörden okunan değeri tutacak değişkeni tanımla
double voltaj;           // Sensörden okunan değerin voltaj dönüşümünü tutacak değişkeni tanımla
double baslangicdeger;   // Sistem çalıştığında sensörden okunan ilk değerin tutulacağı değişkeni tanımla
double deger;            // voltaj değişkeni ile baslagıcdeger değişkeninin farkının tutulacağı değişkeni tanımla
double oranla;           // deger değişkeninin oranlanmış halinin tutulacağı değişkeni tanımla

// LEDBAR modülündeki LED'lerin bağlandığı pin numaralarını tanımla
int yesilLED1 = 3;
int yesilLED2 = 4;
int sariLED = 5;
int kirmiziLED1 = 6;
int kirmiziLED2 = 7;

void setup() {                
    // Sensörün bağlandığı pini giriş olarak ayarla
    pinMode(sensorPin, INPUT);
    
    // LEDBAR'ın LED'lerinin bağlandığı pinleri çıkış olarak ayarla
    pinMode(yesilLED1, OUTPUT);
    pinMode(yesilLED2, OUTPUT);
    pinMode(sariLED, OUTPUT);
    pinMode(kirmiziLED1, OUTPUT);
    pinMode(kirmiziLED2, OUTPUT);
    
    // Sistem çalıştığında kalibrasyon için değer oku ve bu değeri baslangicdeger değişkenine kaydet
    baslangicdeger = analogRead(A5);
    // baslangicdeger değişkenini voltaj değerine çevir
    baslangicdeger = (baslangicdeger * 5) / 1023;
}
 
void loop() {
    // Sensörden değer oku ve bu değerin 10 fazlasını okunandeger değişkenide kaydet
    okunandeger = analogRead(A5) + 10;
    // okunan değerin voltaj karşığını voltaj degiskeninde kaydet 
    voltaj = (okunandeger * 5) / 1023;    
    
    // voltaj değişkeni ile baslangicdeger değişkeninin farkını deger değişkenine kaydet
    deger = voltaj - baslangicdeger;
    // deger değişkeninin 5 ile çarpılmış halini oranla değişkenine kaydet 
    oranla = deger * 5;                 

    // oranla değişkenindeki değere göre LEDBAR daki LED'leri yak 
    if (oranla >= 0 && oranla < 1) {    // Eğer oranla değişkeni 0 ile 1 arasında ise LEDBAR 1. Yeşil LED'i yak
        digitalWrite(yesilLED1, HIGH);
        digitalWrite(yesilLED2, LOW);
        digitalWrite(sariLED, LOW);
        digitalWrite(kirmiziLED1, LOW);
        digitalWrite(kirmiziLED2, LOW);   
    }
    else if (oranla >= 1 && oranla < 2) {    // Eğer oranla değişkeni 1 ile 2 arasında ise LEDBAR 1. ve 2. Yeşil LED'i yak
        digitalWrite(yesilLED1, HIGH);
        digitalWrite(yesilLED2, HIGH);
        digitalWrite(sariLED, LOW);
        digitalWrite(kirmiziLED1, LOW);
        digitalWrite(kirmiziLED2, LOW);   
    }
    else if (oranla >= 2 && oranla < 3) {    // Eğer oranla değişkeni 2 ile 3 arasında ise LEDBAR Yeşil LED'leri ve Sarı LED'i yak
        digitalWrite(yesilLED1, HIGH);
        digitalWrite(yesilLED2, HIGH);
        digitalWrite(sariLED, HIGH);
        digitalWrite(kirmiziLED1, LOW);
        digitalWrite(kirmiziLED2, LOW);   
    }
    else if (oranla >= 3 && oranla < 4) {    // Eğer oranla değişkeni 3 ile 4 arasında ise LEDBAR Yeşil LED'leri, Sarı ve 1. 
                                             // Kırmızı LED'i yak
        digitalWrite(yesilLED1, HIGH);
        digitalWrite(yesilLED2, HIGH);
        digitalWrite(sariLED, HIGH);
        digitalWrite(kirmiziLED1, HIGH);
        digitalWrite(kirmiziLED2, LOW);   
    }
    else if (oranla >= 4) {    // Eğer oranla değişkeni 4 ile 5 arasında ise LEDBAR Yeşil LED'leri, Sarı LED'i ve Kırmızı 
                               // LED'leri yak
        digitalWrite(yesilLED1, HIGH);
        digitalWrite(yesilLED2, HIGH);
        digitalWrite(sariLED, HIGH);
        digitalWrite(kirmiziLED1, HIGH);
        digitalWrite(kirmiziLED2, HIGH);   
    }
    delay(200);
}
