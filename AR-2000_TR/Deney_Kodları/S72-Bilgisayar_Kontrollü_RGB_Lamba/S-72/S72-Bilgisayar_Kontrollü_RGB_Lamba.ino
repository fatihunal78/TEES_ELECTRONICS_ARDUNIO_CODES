// S72 - Bilgisayar Kontrollü RGB Lamba

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int kirmiziLedPin = 6;
int yesilLedPin = 5;
int maviLedPin = 3;

// LED'lerin durumunun tutulacağı değişkenleri tanımla
int kirmiziDurumu = 0;
int yesilDurumu = 0;
int maviDurumu = 0;

// sorguDurumu'nun tutulacağı değişkeni tanımla
int sorguDurumu = 0;

// İkinci geleni ayıklama
int ikinciGelen = 0;
int dummy = 0;

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziLedPin, OUTPUT); 
    pinMode(yesilLedPin, OUTPUT); 
    pinMode(maviLedPin, OUTPUT);  
    
    // Başlangıçta LED'lerin hepsini söndür
    digitalWrite(kirmiziLedPin, HIGH);
    digitalWrite(yesilLedPin, HIGH);
    digitalWrite(maviLedPin, HIGH);

    // Seri iletişim ayarlarını yap
    Serial.begin(9600);                                           // 9600 baud rate ile iletişimi başlat
    
    // Seri iletişim penceresine mesaj gönder
    Serial.println("RGB renk ayarlama uygulamasına hoşgeldiniz!");
    Serial.println("Renk değerlerini 0-255 arasında giriniz.");
    Serial.println("----------------------------------------");
}

void loop() {
    switch(sorguDurumu) {                                        // switch case yapısı oluştur
        case 0:                                                  // case 0 durumunda 
            Serial.println("Kırmızı LED renk değerini giriniz.");// Seri ekrana yazı yaz
            sorguDurumu = 1;                                     // sorguDurumu değişkenini 1 yap 
            break;                                               // case 0 durumunu bitir
            
        case 1:                                                  // case 1 durumunda 
            if(Serial.available() > 0) {                         // Eğer seri haberleşme açık ise 
                kirmiziDurumu = Serial.parseInt();               // kirmiziDurumu değişkenine yazılan değeri kaydet 
                dummy = Serial.parseInt();                       // dummy değişkenine seri port ekranında yazmadığımız
                                                                // (istenmeyen) bir değer var ise onu kaydet
                Serial.print("Kırmızı Değeri -->  "); 
                Serial.println(kirmiziDurumu);                   // Seri port ekranına girilen kırmızı değeri yaz
                Serial.println("----------------------------------------");
                Serial.println("Yeşil LED renk değerini giriniz.");
                sorguDurumu = 2;                                 // sorguDurumu değişkenini 2 yap 
            }
            break;                                               // case 1 durumunu bitir 
            
        case 2:                                                  // case 2 durumunda 
            if(Serial.available() > 0) {                         // Eğer haberleşme açık ise 
                yesilDurumu = Serial.parseInt();                 // yesilDurumu değişkenine yazılan değeri kaydet 
                dummy = Serial.parseInt();                       // dummy değişkenine yazmadığımız(istenmeyen) bir değer
                                                                // var ise onu kaydet
                Serial.print("Yeşil Değeri -->  "); 
                Serial.println(yesilDurumu);                     // Seri port ekranına girilen yeşil değeri yazdır
                Serial.println("----------------------------------------");
                Serial.println("Mavi LED renk değerini giriniz.");
                sorguDurumu = 3;                                 // sorguDurumu değişkenini 3 yap 
            }
            break;                                               // case 2 durumunu bitir 
            
        case 3:                                                  // case 3 durumunda 
            if(Serial.available() > 0) {                         // Eğer haberleşme açık ise 
                maviDurumu = Serial.parseInt();                  // maviDurumu değişkenine yazılan değeri kaydet 
                dummy = Serial.parseInt();                       // dummy değişkenine yazmadığımız(istenmeyen) bir değer
                                                                // var ise onu kaydet
                Serial.print("Mavi Değeri -->  "); 
                Serial.println(maviDurumu);                      // Seri port ekranına girilen mavi değeri yazdır
                sorguDurumu = 4;                                 // sorguDurumu değişkenini 4 yap 
            }
            break;                                               // case 3 durumunu bitir 
            
        case 4:                                                  // case 4 durumunda 
            // RGB LED'i durum değişkenlerinin seviyelerine göre yak
            // Kullanılan RGB ortak Anot olduğu için değerler "255 - Değer" şeklinde aktarılmalıdır
            analogWrite(kirmiziLedPin, (255-kirmiziDurumu));
            analogWrite(yesilLedPin, (255-yesilDurumu));
            analogWrite(maviLedPin, (255-maviDurumu));
            
            kirmiziDurumu = 0;
            yesilDurumu = 0;
            maviDurumu = 0;
            
            Serial.println(" "); 
            Serial.println("İstediğiniz renk ayarlanmıştır.");
            Serial.println("Yeni Değerler Girebilirsiniz");
            Serial.println("----------------------------------------");
            
            delay(500);                                          // 500ms bekle
            Serial.println("");
            sorguDurumu = 0;
            break;                                               // case 4 durumunu bitir 
    }
}
