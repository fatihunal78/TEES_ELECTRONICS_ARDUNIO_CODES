// SA27 - Dijital Saat

#include <LiquidCrystal_I2C.h>  // I2C LCD kütüphanesini ekle
#include <Keypad.h>             // Keypad Kütüphanesi eklendi
#include <stdlib.h>             // integer'dan karaktere dönüşüm için gerekli itoa fonksiyonunu kullanmak için 
                               // gerekli kütüphane

// Kullandığımız keypadde kaç satır ve sütun olduğunu tanımla 
// Panel üzerindeki keypad 4x4 yani 4 satır 4 sütun mevcut
const byte SATIR = 4; 
const byte SUTUN = 4;

// Satır ve sütundaki tuşların yerini ve sırasını tanımla
char Basilan_tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Satır ve sütun pinlerinin Arduino'da hangi pinlere bağlandığını tanımla
// Soldan sağa doğru sırayla bağlantımızı yaptık 
// Tuş takımını ilk dört bağlantısı SATIRLARIN bağlantısı
// Son dört bağlantısı ise SÜTUNLARIN bağlantısı
// Arduino'daki bağlantıyı burada tanımla

byte satirPinleri[SATIR] = {13, 12, 11, 10};  // Satır bağlantılarını Arduino'da bağlandığı pinleri tanımla
byte sutunPinleri[SUTUN] = {9, 8, 7, 6};      // Sütun bağlantılarını Arduino'da bağlandığı pinleri tanımla

// Tuş takımı için Keypad'i tanımla
Keypad Tus_Takimi = Keypad(makeKeymap(Basilan_tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 1602 LCD ekranı tanımla

char Saat_char[2] = {};    // Saat değerinin karakter olarak kayıt edilmesi için gerekli değişkeni tanımla                          
char dakika_char[2] = {};  // Dakika değerinin karakter olarak kayıt edilmesi için gerekli değişkeni tanımla  
int saat;                  // Saat'in arttırılabilmesi için saat değişkenini integer(tam sayı) olarak tanımla
int dakika;                // dakika'nın arttırabilmesi için dakika değişkenini integer(tam sayı) olarak tanımla 
int saniye;                // saniye'nin arttırabilmesi için saniye değişkenini integer(tam sayı) olarak tanımla 
char Basilan_tus;          // Tuş takımından basılan tuşun kaydedileceği değişkeni tanımla

// Karakter olarak oluşturulan saat_char ve dakika_char değişkenlerinin
// 0. ve 1. değerlerinin saydırılması için i ve j değişkenleri tanımla ve ilk değerleri sıfıra eşitle
int i = 0, j = 0;

void setup() {
    lcd.begin();           // LCD'yi başlat
    lcd.backlight();       // LCD arka ışıklarını aç
    lcd.clear();           // LCD'yi temizle
    lcd.setCursor(0, 0);   // İlk satıra geç 
    lcd.print("TEES ELEKTRONIK");  // TEES ELEKTRONIK yaz     
    lcd.setCursor(0, 1);   // Alt satıra geç
    lcd.print("  Dijital Saat ");  // Dijital Saat yaz
    delay(2000);           // yazıları 2 saniye kadar ekranda tut 
    lcd.clear();           // Yazıları temizle
}

void loop() {
    lcd.print("Saati Giriniz");  // LCD ekrana Saati Giriniz yazdır
    delay(2000);                 // 2 saniye bekle 
    lcd.clear();                 // LCD ekranı temizle 

    while(1) {  // Sonsuz döngüye gir 
        Basilan_tus = Tus_Takimi.getKey();  // Keypadden basılan tuşu Basilan_tus karakterine kaydet
        if(Basilan_tus) {  // Eğer tuşa basıldı ise
            Saat_char[i] = Basilan_tus;  // Saat_char[i] değişkenine basilan tuşu kaydet
                                        // Burada i değeri 0 ve 1 değerleri alacaktır. Bu sayede saatin 
                                        // 1. ve 2. değerleri girilebilecektir. (Örn: 23 veya 09 gibi)
            lcd.setCursor(5+i, 0);      // LCD Ekranın ilk satırında 5+i. sütüna git
            lcd.print(Saat_char[i]);    // Tuş takımından basılan değerleri LCD ekrana yazdır
            
            i++;  // i değerini bir arttır
            
            saat = atoi(Saat_char);  // Tuş takımından girilen değerlerin kaydedildiği Saat_char karakterini 
                                    // atoi komutu ile integer(tamsayı) ya çevir ve saat değişkenine kaydet
            
            if(i > 1) break;  // Eğer i değeri 1 den büyük ise sonsuz döngüyü bitir 
        }
    }
    
    while(1) {  // Sonsuz döngüye gir 
        Basilan_tus = Tus_Takimi.getKey();  // Keypadden basılan tuşu Basilan_tus karakterine kaydet
        if(Basilan_tus) {  // Eğer tuşa basıldı ise  
            dakika_char[j] = Basilan_tus;  // dakika_char[j] değişkenine basılan tuşu kaydet
            lcd.print(":");                // LCD ekranda : yaz                           
            lcd.setCursor(8+j, 0);        // LCD Ekranın ilk satırında 8+j. sütüna git
            lcd.print(dakika_char[j]);    // Tuş takımından basılan değerleri LCD Ekrana yazdır
            j++;                          // j değerini bir arttır
            dakika = atoi(dakika_char);   // dakika_char karakterini integer'a çevir
        }               
        if(j >= 2) break;  // Eğer j değeri 2 den büyük ise döngüden çık
    }

    while(1) {  // Sonsuz döngüye gir 
        dijital_saat();  // dijital_saat fonksiyonunu çağır
        for(int i = 0; i < 100; i++) {
            delay(10);
            Basilan_tus = Tus_Takimi.getKey();  // Keypadden basılan tuşu Basilan_tus karakterine kaydet
            if(Basilan_tus == '*') {
                i = 0; 
                j = 0; 
                saniye = 0;  // i,j ve saniye değişkenlerini sıfırla
                break;       // Eğer * tuşuna basıldı ise döngüden çık
            }
        }
        lcd.clear();
         
        if(Basilan_tus == '*') {
            i = 0; 
            j = 0; 
            saniye = 0;  // i,j ve saniye değişkenlerini sıfırla
            break;       // Eğer * tuşuna basıldı ise döngüden çık
        }
    }
}

void dijital_saat() {  // dijital_saat fonksiyonu tanımla 
    // Saydırma işlemi için aşağıdaki adımları takip edeceğiz
    // Öncelikli olarak 1000 ms 1 saniyedir.
    // 1 dakika 60 saniyedir.
    // 1 saat 60 dakikadır.
    // 1 gün 24 saattir.

    saniye++;  // saniye değişkenini birer birer arttır
        
    if(saniye > 59) {  // Eğer saniye değişkeni 59'dan büyük ise 
        saniye = 0;    // Saniye değişkenini sıfırla 
        dakika++;      // Dakikayı bir arttır 
    }
    if(dakika > 59) {  // Eğer dakika 59 dan büyük ise 
        saniye = 0;    // Saniyeyi sıfırla
        dakika = 0;    // Dakikayı sıfırla
        saat++;        // Saati bir arttır
    }
    if(saat > 23) {    // Eğer saat 23 den büyük ise 
        saniye = 0;    // Saniyeyi sıfırla 
        dakika = 0;    // Dakikayı sıfırla
        saat = 0;      // saati sıfırla 
    }

    // Aşağıdaki kod satırları LCD ekrana yazı yazdırmak içindir
    lcd.setCursor(0, 0);
    lcd.print("      Saat     ");  // LCD Ekrana Saat yazdır
    lcd.setCursor(0, 1);           // Alt satıra geç 
    
    if(saat < 10) { 
        lcd.print("    ");
        lcd.print("0"); 
        lcd.print(saat); 
        lcd.print(":"); 
    }  // Saat 10 dan küçük olduğunda önüne 0 koy ve sonrasına iki nokta koy. (  01 :  )
    
    if(saat >= 10) {
        lcd.print("    ");
        lcd.print(saat); 
        lcd.print(":"); 
    }  // Saat 10 dan büyük olduğunda önündeki 0'ı kaldır sadece saati yazdır ve iki nokta koy  ( 23: )
    
    if(dakika < 10) { 
        lcd.print("0"); 
        lcd.print(dakika); 
        lcd.print(":"); 
    }  // Dakika 10 dan küçük olduğunda önüne 0 koy ve sonrasına iki nokta koy. (  07 :  )
    
    if(dakika >= 10) {
        lcd.print(dakika); 
        lcd.print(":"); 
    }  // Dakika 10 dan büyük olduğunda önündeki 0'ı kaldır sadece saati yazdır ve iki nokta koy  ( 19: )
    
    if(saniye < 10) { 
        lcd.print("0"); 
        lcd.print(saniye);
    }  // Saniye 10 dan küçük olduğunda önüne 0 koy ve sonrasına iki nokta koy. (  02 :  )
    
    if(saniye >= 10) {
        lcd.print(saniye); 
    }  // Saniye 10 dan büyük olduğunda önündeki 0'ı kaldır sadece saati yazdır  ( 57 )
}
