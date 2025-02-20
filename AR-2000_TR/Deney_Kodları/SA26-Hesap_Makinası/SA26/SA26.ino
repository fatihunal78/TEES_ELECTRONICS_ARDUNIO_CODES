// SA26 - Hesap Makinası

#include <Keypad.h>            // Tuş takımı kütüphanesini ekle
#include <LiquidCrystal_I2C.h> // LCD ekran kütüphanesini ekle 

LiquidCrystal_I2C lcd(0x27, 16, 2); // 1602 LCD ekranı tanımla

long birinci_sayi = 0;              // Birinci sayinin tutulacağı değişkeni tanımla
long ikinci_sayi = 0;               // İkinci sayının tutulacağı değişkeni tanımla 
double sonuc = 0;                   // Sonucun tutulacağı değişkeni tanımla 

char Basilan_tus;                   // Tuş takımından basılan tuşun tutulacağı değişkeni tanımla 
const byte Satir = 4;               // Tuş takımının kaç satırdan oluştuğunu belirt 
const byte Sutun = 4;               // Tuş takımının kaç sütundan oluştuğunu belirt 
int lcdCursor = 0;

// Tuş takımındaki tuşları tanımla 
// A-B-C-D tuşları yerine matematiksel işlemler yazıldı
// Bu sayede ekstra tanımlama yapmamıza gerek olmayacaktır
char keys[Satir][Sutun] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'C', '0', '=', '/'}
};

// Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[Satir] = {7, 6, 5, 4}; 
byte sutunPinleri[Sutun] = {3, 2, 1, 0}; 

// Tuş takımını başlat
Keypad tusTakimi = Keypad(makeKeymap(keys), satirPinleri, sutunPinleri, Satir, Sutun); 

void setup() {
    lcd.begin();                    // LCD Ekranı başlat 
    lcd.backlight();               // LCD Arka ışıklarını aç 

    lcd.clear();                   // LCD'yi temizle
    lcd.setCursor(0, 0);           // İlk satır ilk sütuna geç 
    lcd.print("TEES ELEKTRONIK");  // TEES ELEKTRONIK yaz   
    lcd.setCursor(0, 1);           // Alt satır ilk sütuna geç
    lcd.print("HESAP MAKINASI");   // HESAP MAKINASI yaz
    delay(2000);                   // 2 saniye bekle
    lcd.clear();                   // LCD'yi temizle
}

void loop() {
    Basilan_tus = tusTakimi.getKey(); // Basilan_tus değişkenine tuş takımından girilen tuşu kaydet
  
    switch(Basilan_tus) {             // switch case yapısı kullanarak Aşağıda kullanılan durumları işle
        case '0' ... '9':             // Operatör( + , - , * , / ) tuşlarından biri basılana kadar aşağıdaki işlemi yap
            lcd.setCursor(0, 0);      // LCD ekran ilk satır ilk sütuna git 
            birinci_sayi = birinci_sayi * 10 + (Basilan_tus - '0');  // Birinci sayıyı elde etmek için gerekli işlemleri yap     
            lcd.print(birinci_sayi);  // LCD ekrana birinci sayıyı yazdır 
            lcdCursor++;
            break;                    // case durumunu bitir

        case '+':                     // Eğer basılan tuş + (yani tuş takımından A tuşuna) basıldı ise toplama işlemi için 
                                     // aşağıdaki işlemleri yap
            birinci_sayi = (sonuc != 0 ? sonuc : birinci_sayi);  // sonuc!=0 ? (eğer sonuc sıfırdan farklı ise, sonuc 
                                                                 // değişkenine birinci_sayi değişkenindeki değeri kaydet) 
            lcd.print("+");           // LCD ekrana + yazdır 
            ikinci_sayi = ikinci_sayi_fonksiyonu();  // ikinci_sayi_fonksiyonunda döndürülen sayıyı ikinci_sayi değişkenine kaydet 
            sonuc = birinci_sayi + ikinci_sayi;      // sonuc değişkenine iki sayının toplamını kaydet 
            lcd.setCursor(0, 1);      // LCD ekranda alt satır ilk sütuna git.
            lcd.print("=");           // LCD ekrana = yazdır
            lcd.print(long(sonuc));   // LCD ekrana sonucu yazdır 
            birinci_sayi = 0;
            ikinci_sayi = 0;          // Diğer işlemler için birinci_sayi ve ikinci_sayi değişkenlerini sıfırla 
            lcdCursor++;              // lcdCursor değişkenini bir arttır 
            break;                    // case durumunu bitir 

        case '-':                     // Eğer basılan tuş - (yani tuş takımından B tuşuna) basıldı ise çıkartma işlemi için 
                                     // aşağıdaki işlemleri yap
            birinci_sayi = (sonuc != 0 ? sonuc : birinci_sayi);  // sonuc!=0 ? (eğer sonuc sıfırdan farklı ise, sonuc 
                                                                 // değişkenine birinci_sayi değişkenindeki değeri kaydet)     
            lcd.print("-");           // LCD ekrana - yazdır 
            ikinci_sayi = ikinci_sayi_fonksiyonu();  // ikinci_sayi_fonksiyonunda döndürülen sayıyı ikinci_sayi değişkenine kaydet 
            sonuc = birinci_sayi - ikinci_sayi;      // sonuc değişkenine iki sayının farkını kaydet 
            lcd.setCursor(0, 1);      // LCD ekranda alt satır ilk sütuna git
            lcd.print("=");           // LCD ekrana = yazdır    
            lcd.print(long(sonuc));   // LCD ekrana sonucu yazdır 
            birinci_sayi = 0;
            ikinci_sayi = 0;          // Diğer işlemler için birinci_sayi ve ikinci_sayi değişkenlerini sıfırla 
            lcdCursor++;              // lcdCursor değişkenini bir arttır 
            break;                    // case durumunu bitir  

        case '*':                     // Eğer basılan tuş * (yani tuş takımından C tuşuna) basıldı ise çarpma işlemi için 
                                     // aşağıdaki işlemleri yap
            birinci_sayi = (sonuc != 0 ? sonuc : birinci_sayi);  // sonuc!=0 ? (eğer sonuc sıfırdan farklı ise, sonuc 
                                                                 // değişkenine birinci_sayi değişkenindeki değeri kaydet) 
            lcd.print("*");           // LCD ekrana * yazdır 
            ikinci_sayi = ikinci_sayi_fonksiyonu();  // ikinci_sayi_fonksiyonunda döndürülen sayıyı ikinci_sayi değişkenine kaydet
            sonuc = birinci_sayi * ikinci_sayi;      // sonuc değişkenine iki sayının çarpımını kaydet 
            lcd.setCursor(0, 1);      // LCD ekranda alt satır ilk sütuna git.
            lcd.print("=");           // LCD ekrana = yazdır    
            lcd.print(long(sonuc));   // LCD ekrana sonucu yazdır 
            birinci_sayi = 0;
            ikinci_sayi = 0;          // Diğer işlemler için birinci_sayi ve ikinci_sayi değişkenlerini sıfırla 
            lcdCursor++;              // lcdCursor değişkenini bir arttır 
            break;                    // case durumunu bitir  

        case '/':                     // Eğer basılan tuş / (yani tuş takımından D tuşuna) basıldı ise bölme işlemi için 
                                     // aşağıdaki işlemleri yap
            birinci_sayi = (sonuc != 0 ? sonuc : birinci_sayi);  // sonuc!=0 ? (eğer sonuc sıfırdan farklı ise, sonuc 
                                                                 // değişkenine birinci_sayi değişkenindeki değeri kaydet) 
            lcd.print("/");           // LCD ekrana / yazdır 
            ikinci_sayi = ikinci_sayi_fonksiyonu();  // sonuc değişkenine iki sayının çarpımını kaydet  
  
            // Eğer ikinci_sayi değişkeni sıfır ise LCD ekrana "tanımsız" yazdır 
            // Eğer sıfırdan farklı ise sonuc = (float)birinci_sayi / (float)ikinci_sayi; işlemini yap
            // Yani birinci sayı ve ikinci sayının bölümünü sonuc değişkenine kaydet 
            if (ikinci_sayi == 0) {
                lcd.print("Tanimsiz");
            } else {
                sonuc = (float)birinci_sayi / (float)ikinci_sayi;
            }
            
            lcd.setCursor(0, 1);      // LCD ekranda alt satır ilk sütuna git.
            lcd.print("=");           // LCD ekrana = yazdır.    
            lcd.print(sonuc);         // LCD ekrana sonucu yazdır  
            birinci_sayi = 0;
            ikinci_sayi = 0;          // Diğer işlemler için birinci_sayi ve ikinci_sayi değişkenlerini sıfırla 
            lcdCursor++;              // lcdCursor değişkenini bir arttır 
            break;                    // case durumunu bitir  

        case 'C':                     // Eğer basılan tuş C (yani tuş takımından * tuşuna) basıldı ise 
            sonuc = 0;                // sonuc değişkenini sıfırla
            birinci_sayi = 0;
            ikinci_sayi = 0;          // Değerleri sıfırla
            lcdCursor = 0;            // lcdCursor değişkenini sıfırla 
            lcd.clear();              // LCD'yi temizle
            break;                    // case durumunu bitir 
    }
}

long ikinci_sayi_fonksiyonu() {      // ikinci sayıyı elde etmek için fonksiyon oluştur 
    while(1) {                        // sonsuz döngüye gir 
        Basilan_tus = tusTakimi.getKey();  // Tuş takımından basılan tuşu Basilan_tus değişkenine ata
        if(Basilan_tus >= '0' && Basilan_tus <= '9') {  // eğer basılan tuş 0 ile 9 arasında ise yani sadece rakamlar basıldı ise 
            ikinci_sayi = ikinci_sayi * 10 + (Basilan_tus - '0');  // İkinci sayıyı elde etmek için gerekli işlemleri yap  
            lcd.setCursor(lcdCursor + 1, 0);
            lcd.print(ikinci_sayi);   // LCD ekrana ikinci sayıyı yazdır 
        }

        if(Basilan_tus == '=') {     // Eğer tuş = (yani tuş takımından # tuşuna basıldı ise) sonsuz döngüyü bitir 
            lcdCursor = 0;
            break;
        }
    }
    return ikinci_sayi;              // elde edilen ikinci_sayi değişkenini döndür
}
