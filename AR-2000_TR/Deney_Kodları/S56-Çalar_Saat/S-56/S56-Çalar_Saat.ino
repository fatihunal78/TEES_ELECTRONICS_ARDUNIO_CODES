// S56 - Çalar Saat

// Gerekli değişkenler tanımla
int sorgudurumu = 0;                         // Sorgu durumu değişkenini tanımla ve ilk durumu 0'a eşitle
int saat;
int dakika; 
int saniye;
int dummy = 0;
int Alarm_saati;

int Alarm_dakika;
int butondurumu = 0;
int butonPin = 2;                            // Butonun bağlandığı pin numarasını tanımla
int yesilLed = 3;                            // Yeşil LED'in bağlandığı pin numarasını tanımla 
int kirmiziLed = 4;                          // Kırmızı LED'in bağlandığı pin numarasını tanımla 
int hoparlorPin = 5;                         // Hoparlörün bağlandığı pin numarasını tanımla

void setup() {
    Serial.begin(9600);                      // Seri iletişimi başlat
    pinMode(butonPin, INPUT);                // Butonun bağlandığı pini giriş olarak ayarla
    pinMode(yesilLed, OUTPUT);               // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(kirmiziLed, OUTPUT);             // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);            // Hoparlörün bağlandığı pini çıkış olarak ayarla
}

void loop() {
    switch(sorgudurumu) {                    // sorgudurumu değişkeni ilk durumu 0 olduğu için
        case 0:                              // İlk case'e girecek
        { 
            Serial.println("Saati giriniz"); // Seri port ekranına Saati giriniz yazdır
            sorgudurumu = 1;                 // sorgudurumunu 1 yap 
            break;                           // case 0 durumundan çık
        }
        
        case 1:                              // sorgudurumu değişkeni 1 olmuştu (üst satırda)
        {
            if(Serial.available() > 0) {     // Eğer seri porttan gelen bilgi varsa
                saat = Serial.parseInt();     // Girilen değeri saat değişkenine kaydet
                Serial.print("Saat : "); 
                Serial.println(saat);         // Ekranda saati yazdır
                Serial.println("Dakikayi Giriniz"); // Dakikayı giriniz yazdır
                dummy = Serial.parseInt();    // Eğer basmadığımız halde herhangi bir komut algılarsa dummy değişkenine kaydet
                sorgudurumu = 2;             // sorgudurumu değişkenini 2 yap    
            }    
            break;                           // case 1 durumundan çık
        }
        
        case 2:                              // case 2 durumunu tanımla
        {
            if(Serial.available() > 0) {     // Eğer seri porttan gelen bilgi varsa
                dakika = Serial.parseInt();   // Girilen değeri dakika değişkenine kaydet
                Serial.print("Dakika :"); 
                Serial.println(dakika);       // Ekrana dakikayı yazdır
                sorgudurumu = 3;             // sorgudurumu değişkenini 3 yap, 3. case olmadığı için switch döngüsünden çıktık    
            }
            break;                           // case 2 durumundan çık
        }
    }

    if(digitalRead(butonPin) == HIGH) {      // Eğer butona basılmış ise   
        sorgudurumu = 4;                     // Üst satırda 3 yaptığımız sorgudurumu değişkenini 4 yaparak alt taraftaki 
                                            // switch döngüsüne sokalım
        digitalWrite(kirmiziLed, LOW);        // Kirmizi LED'i söndür
        while(1) {                           // Sonsuz döngüye gir 
            switch(sorgudurumu) {            // sorgudurumu değişkeni ilk durumu 4 olduğu için
                case 4: {                    // sorgudurumu değişkenini 4 yaptığımız için ilk case'e gir
                    Serial.println("Alarm Saatini giriniz"); // Alarm Saatini giriniz yazdır
                    if(Serial.available() > 0) {
                        sorgudurumu = 5;     // sorgudurumunu 5 yap 
                        dummy = Serial.parseInt(); // Eğer bir değer girilmediği halde herhangi bir komut algılarsa dummy 
                                                 // değişkenine kaydet
                    }
                    break;                   // case 4 durumundan çık
                }
                
                case 5:                      // sorgudurumu değişkeni 5 olmuştu (üst satırda)
                {
                    if(Serial.available() > 0) { // eğer seri haberleşme mevcut ise 
                        Alarm_saati = Serial.parseInt(); // girilen değeri Alarm_saati değişkenine kaydet
                        Serial.print("Alarm Saati : "); 
                        Serial.println(Alarm_saati); // ekranda Alarm saatini yazdır
                        Serial.println("Alarm Dakikasini Giriniz"); // Alarm Dakikasını giriniz yazdır
                        dummy = Serial.parseInt(); // eğer basmadığımız halde herhangi bir komut algılarsa dummy değişkenine 
                                                 // kaydet
                        sorgudurumu = 6;     // sorgudurumu değişkenini 6 yap    
                    }    
                    break;                   // case 5 durumundan çık 
                }
                
                case 6:                      // case 6 durumuna geç
                {
                    if(Serial.available() > 0) { // Eğer seri porttan gelen bilgi varsa
                        Alarm_dakika = Serial.parseInt(); // Girilen değeri Alarm_dakikası değişkenine kaydet
                        Serial.print("Alarm Dakika :"); 
                        Serial.println(Alarm_dakika); // Ekrana Alarm dakikasını yazdır
                        digitalWrite(yesilLed, HIGH); // Alarmın kurulduğunu gösteren Yeşil LED'i yak
                        sorgudurumu = 7;     // sorgu durumu değişkenini 7 yap, 7. case olmadığı için switch döngüsünden çık   
                    }
                    break;                   // case 6 durumundan çık
                }
            } 
            if(digitalRead(butonPin) == HIGH) { // Eğer butona tekrar basıldı ise 
                break;                       // while döngüsünden çık 
            }
        }
    }

    if(Serial.available()) {
        if(Alarm_saati == saat && Alarm_dakika == dakika) { // Eğer saat alarm saatine ve dakika da alarm dakikasına eşit ise 
            digitalWrite(kirmiziLed, HIGH);  // Kırmızı LED'i yak
            digitalWrite(yesilLed, LOW);     // Yeşil LED'i söndür
            tone(hoparlorPin, 300);         // Hoparlörden ses çıkart
            delay(100);                      // 100 ms bekle 
            noTone(hoparlorPin);            // Hoparlörü sustur
            digitalWrite(kirmiziLed, LOW);   // Kırmızı LED'i söndür
            delay(100);                      // 100 ms bekle 
      
            // Seri ekrana Saat ve Alarm bilgilerini yazdır
            Serial.println("---------------------------------------------");
            Serial.print("Saat : "); 
            Serial.print(saat); 
            Serial.print("."); 
            Serial.print(dakika); 
            Serial.print(".");
            Serial.print(saniye);
            Serial.print("       "); 
            Serial.print("Alarm : "); 
            Serial.print(Alarm_saati); 
            Serial.print("."); 
            Serial.println(Alarm_dakika); 

            delay(800);
            saniye++;
            if(saniye >= 60) {              // Eğer saniye 60'dan büyük ise yani bir dakika oldu 
                saniye = 0;                  // Saniye değişkenini sıfırla
                dakika = dakika + 1;         // Dakika değişkenini bir arttır
            }
            if(dakika >= 60) {              // Eğer dakika değişkeni 60'dan büyük ise 1 saat oldu
                dakika = 0;                  // Dakika değişkenini sıfırla 
                saat = saat + 1;             // Saat değişkenini 1 arttır 
            }
            if(saat >= 24) {                // Eğer saat 24'den büyük ise 
                saat = 0;                    // Saat değişkenini 0 yap 
            }
        }
        else {                              // Eğer saat ve dakika alarm saati ve dakikasına eşit değil ise 
            digitalWrite(kirmiziLed, LOW);   // Kırmızı LED'i söndür    
    
            // Seri ekrana Saat ve Alarm bilgilerini yazdır
            Serial.println("---------------------------------------------");
            Serial.print("Saat : "); 
            Serial.print(saat); 
            Serial.print("."); 
            Serial.print(dakika); 
            Serial.print(".");
            Serial.print(saniye);
            Serial.print("       "); 
            Serial.print("Alarm : "); 
            Serial.print(Alarm_saati); 
            Serial.print("."); 
            Serial.println(Alarm_dakika); 

            delay(1000);
            saniye++;
            if(saniye >= 60) {              // Eğer saniye 60'dan büyük ise yani bir dakika oldu
                saniye = 0;                  // Saniye değişkenini sıfırla
                dakika = dakika + 1;         // Dakika değişkenini bir arttır
            }
            if(dakika >= 60) {              // Eğer dakika değişkeni 60'dan büyük ise 1 saat oldu
                dakika = 0;                  // Dakika değişkenini sıfırla 
                saat = saat + 1;             // Saat değişkenini 1 arttır 
            }
            if(saat >= 24) {                // Eğer saat 24'den büyük ise 
                saat = 0;                    // Saat değişkenini 0 yap 
            }
        }
    }
}
