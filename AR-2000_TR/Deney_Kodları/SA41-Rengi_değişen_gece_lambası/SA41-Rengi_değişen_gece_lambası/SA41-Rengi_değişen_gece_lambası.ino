// SA41 - Rengi değişen gece lambası

#include <LiquidCrystal_I2C.h>    // I2C LCD kütüphanesini ekle
#include <Keypad.h>               // Keypad kütüphanesi eklendi
#include <stdlib.h>               // integer'dan karaktere dönüşüm için gerekli itoa fonksiyonunu kullanmak için 
                                 // gerekli kütüphane
                    
const byte SATIR = 4;            // Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;            // Tuş takımının kaç sütundan oluştuğunu belirt 

// Tuş takımındaki tuşları tanımla 
char tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[SATIR] = {7, 6, 5, 4};    // Satır bağlantılarının Arduino'da bağlandığı pinleri tanımla 
byte sutunPinleri[SUTUN] = {3, 2, 1, 0};    // Sütun bağlantılarının Arduino'da bağlandığı pinleri tanımla

// Tuş takımını başlat
Keypad Tus_Takimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN); 

LiquidCrystal_I2C lcd(0x27, 16, 2);         // 1602 LCD ekranı tanımla

// LED'lerin bağlandığı pinleri tanımla
int RGB_Kirmizi = 11;
int RGB_Yesil = 10;
int RGB_Mavi = 9; 

char kirmizi_char[3] = {};                   // Kırmızı rengin tutulacağı karakter değişkenini tanımla
char yesil_char[3] = {};                     // Yeşil rengin tutulacağı karakter değişkenini tanımla
char mavi_char[3] = {};                      // Mavi rengin tutulacağı karakter değişkenini tanımla

char Basilan_tus;                            // Basılan tuşun tutulacağı değişkeni tanımla
int i = 0, j = 0, z = 0;                     // R,G,B değerleri için karakterin birinci, ikinci ve üçüncü değerlerinin 
                                            // tanımlanacağı değişkenler i,j ve z değişkenlerine kayıt edilecek
                                            // Örneğin kirmizi_char[3]={175} olsun. kirmizi_char[i] değişkeninde 
                                            // eğer i değeri 2 ise kirmizi_char[2] değişkeni 7 değerine eşittir. 
                                            // Aynı şekilde kirmizi_char[1] 1 değerine, kirmizi_char[3] 5 değerine eşittir.

int Kirmizi_Degeri;                         // RGB LED'in Red (Kırmızı) değerinin tamsayı olarak tutulacağı değişkeni tanımla 
int Yesil_Degeri;                           // RGB LED'in Green (Yeşil) değerinin tamsayı olarak tutulacağı değişkeni tanımla
int Mavi_Degeri;                            // RGB LED'in Blue (Mavi) değerinin tamsayı olarak tutulacağı değişkeni tanımla

void setup() {
    pinMode(RGB_Kirmizi, OUTPUT);           // RGB LED'in Kırmızı (R) bağlantısını çıkış olarak ayarla
    pinMode(RGB_Yesil, OUTPUT);             // RGB LED'in Yeşil (G) bağlantısını çıkış olarak ayarla 
    pinMode(RGB_Mavi, OUTPUT);              // RGB LED'in Mavi (B) bağlantısını çıkış olarak ayarla 

    /*
     * RGB LED ortak anot olduğu için HIGH yaptığınız zaman sönük, LOW yaptığımız zaman yanık olacaktır.
     * Çünkü ortak anot yani ortak besleme CA bağlantısı +5V'a bağlı, sürekli enerjide olduğu için 
     * herhangi bir pini (R,G, ya da B) LOW yaptığımız zaman devreyi tamamlayacak ve led yanacaktır.
     */
    digitalWrite(RGB_Kirmizi, HIGH);        // RGB LED'in kırmızı bağlantısını HIGH yap, yani söndür 
    digitalWrite(RGB_Yesil, HIGH);          // RGB LED'in yeşil bağlantısını HIGH yap, yani söndür 
    digitalWrite(RGB_Mavi, HIGH);           // RGB LED'in mavi bağlantısını HIGH yap, yani söndür 

    lcd.begin();                            // LCD'yi başlat
    lcd.backlight();                        // LCD arka ışıklarını aç
    lcd.clear();                            // LCD'yi temizle
    lcd.setCursor(0, 0);                    // İlk satıra geç 
    lcd.print("TEES ELEKTRONIK");           // TEES ELEKTRONIK yaz     
    lcd.setCursor(0, 1);                    // Alt satıra geç
    lcd.print("RENK KONTRASTI");            // RENK KONTRASTI yazdır
    delay(2000);                            // 2 saniye bekle
    lcd.clear();                            // LCD'yi temizle
}

void loop() {
    lcd.print("RGB Degerlerini");           // LCD ekrana yaz
    lcd.setCursor(0, 1);                    // Alt satıra geç
    lcd.print("Giriniz #'e bas");           // LCD ekrana yaz
    delay(2000);                            // 2 saniye bekle 
    lcd.clear();                            // LCD Ekranı temizle 
    lcd.print("R(Red):");

    while(1) {                              // Sonsuz döngüye gir 
        Basilan_tus = Tus_Takimi.getKey();  // Keypadden basılan tuşu Basilan_tus karakterine kaydet
        
        if(Basilan_tus) {                   // Eğer tuşa basıldı ise
            kirmizi_char[i] = Basilan_tus;  // kirmizi_char[i] değişkenine basilan tuşu kaydet
            lcd.setCursor(8 + i, 0);        // LCD Ekranın ilk satırında 8+i. sütüna git
            lcd.print(kirmizi_char[i]);     // Tuş takımından basılan değerleri LCD Ekrana yazdır
            i++;                            // i değerini bir arttır
            
            if(i > 4) i = 0;               // Eğer i değeri 4'den büyük ise i değerini sıfıra eşitle
            
            Kirmizi_Degeri = atoi(kirmizi_char);  // Karakteri integer'a çevir
            
            if(Basilan_tus == '#') {       // Eğer # tuşuna basıldı ise
                i = 0;
                break;
            }
        }
    }
    
    lcd.clear();                           // LCD'yi temizle
    lcd.print("G(Green):");
    
    while(1) {                             // Sonsuz döngüye gir 
        Basilan_tus = Tus_Takimi.getKey(); // Keypadden basılan tuşu Basilan_tus karakterine kaydet
        
        if(Basilan_tus) {                  // Eğer tuşa basıldı ise
            yesil_char[j] = Basilan_tus;   // yesil_char[j] değişkenine basılan tuşu kaydet
            lcd.setCursor(10 + j, 0);      // LCD ekranın ilk satırında 10+j. sütüna git
            lcd.print(yesil_char[j]);      // Tuş takımından basılan değerleri LCD ekrana yazdır
            j++;                           // j değerini bir arttır
            
            if(j > 4) j = 0;              // Eğer j değeri 4'den büyük ise j değerini sıfıra eşitle
            
            Yesil_Degeri = atoi(yesil_char);  // Karakteri integer'a çevir
            
            if(Basilan_tus == '#') {      // Eğer # tuşuna basıldı ise
                j = 0;
                break;
            }
        }
    }

    lcd.clear();                          // LCD'yi temizle
    lcd.print("B(Blue):");
    
    while(1) {                            // Sonsuz döngüye gir 
        Basilan_tus = Tus_Takimi.getKey();  // Keypadden basılan tuşu Basilan_tus karakterine kaydet
        
        if(Basilan_tus) {                 // Eğer tuşa basıldı ise
            mavi_char[z] = Basilan_tus;   // mavi_char[z] değişkenine basılan tuşu kaydet
            lcd.setCursor(9 + z, 0);      // LCD Ekranın ilk satırında 9+z. sütüna git
            lcd.print(mavi_char[z]);      // Tuş takımından basılan değerleri LCD ekrana yazdır
            z++;                          // z değerini bir arttır
            
            if(z > 4) z = 0;             // Eğer z değeri 4'den büyük ise z değerini sıfıra eşitle
            
            Mavi_Degeri = atoi(mavi_char);  // Karakteri integer'a çevir
            
            if(Basilan_tus == '#') {     // Eğer # tuşuna basıldı ise
                z = 0;
                break;
            }
        }
    }
  
    lcd.clear();                         // LCD'yi temizle
    lcd.print("Renk Ayarlaniyor");       // LCD Ekrana Renk Ayarlaniyor yazdır
    lcd.setCursor(0, 1);                 // Alt satıra geç 
    
    // Kırmızı, Yeşil ve Mavi değerlerini LCD'ye yaz
    lcd.print("R:");
    lcd.print(Kirmizi_Degeri);
    lcd.print(" G:");
    lcd.print(Yesil_Degeri);
    lcd.print("B:");
    lcd.print(Mavi_Degeri);
    
    // RGB LED değerlerini ayarla (Ortak anot için 255'ten çıkarılır)
    analogWrite(RGB_Kirmizi, 255 - Kirmizi_Degeri);
    analogWrite(RGB_Yesil, 255 - Yesil_Degeri);
    analogWrite(RGB_Mavi, 255 - Mavi_Degeri);
  
    delay(3000);                         // 3 saniye bekle 
    lcd.clear();                         // LCD'yi temizle 
    lcd.setCursor(0, 0);                 // İlk satır ilk sütuna geç 
}
