// SA80 - Taş Kağıt Makas Oyunu

#include <LiquidCrystal_I2C.h>                     // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);               // 1602 LCD ekranı tanımla

int RGB_Kirmizi = 5;                               // RGB Kırmızı LED'in bağlandığı pin numarasını tanımlandı 
int RGB_Yesil = 4;                                 // RGB Yeşil LED'in bağlandığı pin numarasını tanımlandı 
int RGB_Mavi = 3;                                  // RGB Mavi LED'in bağlandığı pin numarasını tanımlandı 

int Birinci_Oyuncu_Buton = 6;                     // Birinci oyuncu butonunun bağlandığı pin numarasını tanımla
int Ikinci_Oyuncu_Buton = 2;                      // İkinci oyuncu butonunun bağlandığı pin numarasını tanımla 

int hoparlorPin = 8;                              // Hoparlörün bağlandığı pin numarasını tanımla

int sayac = 1;                                    // Sayaç değişeni tanımlandı
int birincideger;                                 // Birinci oyuncunun verilerinin tutulacağı değişkeni tanımla 
int ikincideger;                                  // İkinci oyuncunun verilerinin tutulacağı değişkeni tanımla 

void setup() {
    // RGB LED'lerinin bağlandığı pinleri çıkış olarak ayarla
    pinMode(RGB_Kirmizi, OUTPUT);
    pinMode(RGB_Yesil, OUTPUT);
    pinMode(RGB_Mavi, OUTPUT);
    
    // Butonun bağlandığı pinleri giriş olarak ayarla
    pinMode(Birinci_Oyuncu_Buton, INPUT);
    pinMode(Ikinci_Oyuncu_Buton, INPUT_PULLUP);
    
    pinMode(hoparlorPin, OUTPUT);                  // Hoparlörün bağlandığı pini çıkış olarak ayarla 

    lcd.begin();                                   // LCD'yi başlat
    lcd.backlight();                              // LCD arka ışıklarını aç
    lcd.clear();                                  // LCD'yi temizle

    lcd.setCursor(0, 0);                          // LCD ilk satıra geç 
    lcd.print("TEES ELEKTRONIK");
    lcd.setCursor(0, 1);                          // Alt satıra geç
    lcd.print("TAS KAGIT MAKAS");
    delay(2000);                                  // 2 saniye bekle
    lcd.clear();                                  // LCD'yi temizle 
    randomSeed(analogRead(A0));  
}

void loop() {
    // sayac değişkeninin 1 olması birinci oyuncunun butona basma sırası olduğu 
    // sayac değişkeninin 2 olması ise ikinci oyuncunun butona basma sırası olduğu anlamındadır
    
    if (digitalRead(Birinci_Oyuncu_Buton) == HIGH && sayac == 1) {  // Eğer birinci oyuncunun sırası ise ve butona bastı ise 
        lcd.clear();                              // LCD'yi temizle 
        birincideger = 0;                         // Birinci oyuncunun verisinin tutulacağı birincideger değişkeninin sıfırla 
        ikincideger = 0;                          // İkinci oyuncunun verisinin tutulacağı ikincideger değişkeninin sıfırla 
        
        for (int i = 0; i < 5; i++) {            // 5 kere tekrarla    
            birincideger = random(1, 4);          // 1 ile 4 arasında rastgele bir sayı oluştur ve birincideger değişkenine kaydet 
            
            // RGB LED'in rastgele yanan sayıya göre yanması için RGB_animasyon fonksiyonunu çağır 
            // ve rastgele üretilen birincideger değişkenine kaydet 
            RGB_animasyon(birincideger);
            
            // LCD ekranda sonucun gösterilmesi için sonuc fonksiyonunu çağır 
            // ve birincideger ile ikincideger değişkenlerini içine aktar 
            sonuc(birincideger, ikincideger);
            
            // Hoparlörden rastgele üretilen birincideger değişkeninin 220 ile çarpındaki Hertzlik ses tonunu hoparlöre aktar 
            tone(hoparlorPin, birincideger * 220);
            delay(150);                           // 150ms bekle
            noTone(hoparlorPin);                  // Hoparlörü sustur 
            sayac = 2;                            // İkinci oyuncunun sırasının olduğunu gösteren sayac değişkenini 2 yap 
        }
    }
    
    if (digitalRead(Ikinci_Oyuncu_Buton) == LOW && sayac == 2) {  // Eğer ikinci oyuncunun sırası ise ve butona bastı ise 
        lcd.clear();                              // LCD ekranı temizle 
        for (int i = 0; i < 5; i++) {            // 5 kere tekrarla    
            ikincideger = random(1, 4);           // 1 ile 4 arasında rastgele bir sayı oluştur ve ikincideger değişkenine kaydet      
            
            // RGB LED'in rastgele yanan sayıya göre yanması için RGB_animasyon fonksiyonunu çağır 
            // ve rastgele üretilen ikincideger değişkenine kaydet
            RGB_animasyon(ikincideger);
            
            // LCD ekranda sonucun gösterilmesi için sonuc fonksiyonunu çağır 
            // ve birincideger ile ikincideger değişkenlerini içine aktar 
            sonuc(birincideger, ikincideger);
            
            // Hoparlörden rastgele üretilen ikincideger değişkeninin 220 ile çarpındaki Hertzlik ses tonunu hoparlöre aktar 
            tone(hoparlorPin, ikincideger * 220);
            delay(150);                           // 150ms bekle
            noTone(hoparlorPin);                  // Hoparlörü sustur 
            sayac = 1;                            // Birinci oyuncunun sırasının olduğunu gösteren sayac değişkenini 1 yap 
        }
    }
}

// Kazananı göstermek için sonuc fonksiyonu oluştur ve
// birinci oyuncu ile ikinci oyuncunun verileri içeriye al
void sonuc(int birinci, int ikinci) {
    // LCD ekranın ilk satırına git ve 1: yaz 
    // ardından rastgele üretilen değere göre LCD Ekrana Tas Kagit ya da Makas yazdır.
    lcd.setCursor(0, 0);
    lcd.print("1:");
    if (birinci == 1) { lcd.setCursor(2, 0); lcd.print("Tas  "); }
    if (birinci == 2) { lcd.setCursor(2, 0); lcd.print("Kagit"); }
    if (birinci == 3) { lcd.setCursor(2, 0); lcd.print("Makas"); }

    // LCD ekranın ilk satırının 9.sütununa git ve 2: yaz 
    // Ardından rastgele üretilen değere göre LCD Ekrana Tas Kagit ya da Makas yazdır.
    lcd.setCursor(9, 0);
    lcd.print("2:");
    if (ikinci == 1) { lcd.setCursor(11, 0); lcd.print("Tas  "); }
    if (ikinci == 2) { lcd.setCursor(11, 0); lcd.print("Kagit"); }
    if (ikinci == 3) { lcd.setCursor(11, 0); lcd.print("Makas"); }
    
    if (birincideger == ikincideger) {           // Eğer birinci oyuncu ile ikinci oyuncunun değerleri eşit ise 
                                                 // beraberlik durumunda 
        lcd.setCursor(0, 1);                     // LCD ekranın alt satırına BERABERE Yaz 
        lcd.print("BERABERE        ");
    }
    else if (birincideger == 1 && ikincideger == 2) {  // Birinci oyuncuya 1 yani TAŞ, ikinci oyuncuya 2 yani KAĞIT geldiyse
                                                       // 2. oyuncu kazanır
        lcd.setCursor(0, 1);                          // LCD ekranın alt satırına İkinci Kazandi Yaz 
        lcd.print("ikinci Kazandi  ");
    }
    else if (birincideger == 1 && ikincideger == 3) {  // Birinci oyuncuya 1 yani TAŞ, ikinci oyuncuya 3 yani MAKAS geldiyse
                                                       // 1. oyuncu kazanır
        lcd.setCursor(0, 1);                          // LCD ekranın alt satırına Birinci Kazandi Yaz 
        lcd.print("Birinci Kazandi  ");
    }
    else if (birincideger == 2 && ikincideger == 1) {  // Birinci oyuncuya 2 yani KAĞIT, ikinci oyuncuya 1 yani TAŞ geldiyse
                                                       // 1. oyuncu kazanır
        lcd.setCursor(0, 1);                          // LCD ekranın alt satırına Birinci Kazandi Yaz 
        lcd.print("Birinci Kazandi  ");
    }
    else if (birincideger == 2 && ikincideger == 3) {  // Birinci oyuncuya 2 yani KAĞIT, ikinci oyuncuya 3 yani MAKAS geldiyse
                                                       // 2. oyuncu kazanır
        lcd.setCursor(0, 1);                          // LCD ekranın alt satırına İkinci Kazandi Yaz 
        lcd.print("ikinci Kazandi  ");
    }
    else if (birincideger == 3 && ikincideger == 1) {  // Birinci oyuncuya 3 yani MAKAS, ikinci oyuncuya 1 yani TAŞ geldiyse
                                                       // 2. oyuncu kazanır
        lcd.setCursor(0, 1);                          // LCD ekranın alt satırına İkinci Kazandi Yaz 
        lcd.print("ikinci Kazandi  ");
    }
    else if (birincideger == 3 && ikincideger == 2) {  // Birinci oyuncuya 3 yani MAKAS, ikinci oyuncuya 2 yani KAĞIT geldiyse
                                                       // 1. oyuncu kazanır
        lcd.setCursor(0, 1);                          // LCD ekranın alt satırına Birinci Kazandi Yaz 
        lcd.print("Birinci Kazandi  ");
    }
}

// Rastgele atanan değerlere göre RGB'de animasyon yapmak ve taş, kağıt ya da makas değerlerini göstermek için
// RGB_animasyon fonksiyonu oluştur
void RGB_animasyon(int durum) {
    // Durum değişkeni içindeki veriye göre taş kağıt makas durumunu belirle
    // Eğer durum değişkeni 
    // 1 ise taş 
    // 2 ise kağıt
    // 3 ise makas 
    switch (durum) {
        case 1:                                   // Taş durumu geldiğinde RGB Kırmızı LED'i yak diğerlerini söndür
            digitalWrite(RGB_Kirmizi, LOW);
            digitalWrite(RGB_Yesil, HIGH);
            digitalWrite(RGB_Mavi, HIGH);
            break;                                // Case 1 durumunu bitir
            
        case 2:                                   // Kağıt durumu geldiğinde RGB Yeşil LED'i yak diğerlerini söndür
            digitalWrite(RGB_Kirmizi, HIGH);
            digitalWrite(RGB_Yesil, LOW);
            digitalWrite(RGB_Mavi, HIGH);
            break;                                // Case 2 durumunu bitir
            
        case 3:                                   // Makas durumu geldiğinde RGB Mavi LED'i yak diğerlerini söndür
            digitalWrite(RGB_Kirmizi, HIGH);
            digitalWrite(RGB_Yesil, HIGH);
            digitalWrite(RGB_Mavi, LOW);
            break;                                // Case 3 durumunu bitir
    }
}
