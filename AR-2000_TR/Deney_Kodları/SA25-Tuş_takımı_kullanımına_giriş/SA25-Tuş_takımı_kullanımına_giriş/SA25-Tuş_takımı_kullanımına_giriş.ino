// SA25 - Tuş takımı kullanımına giriş

#include <LiquidCrystal_I2C.h>    // I2C LCD kütüphanesini ekle
#include <Keypad.h>               // Keypad kütüphanesini ekle

// Kullandığımız keypadde kaç satır ve sütun olduğunu belirtmemiz gerekiyor 
// Panel üzerindeki keypad 4x4 yani 4 satır 4 sütun mevcuttur
const byte SATIR = 4; 
const byte SUTUN = 4;

// Satır ve sütundaki tuşların yerini ve sırasını belirttik
char tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Satır ve sütun pinlerinin Arduino'da hangi pinlere bağlandığını belirttik
// Soldan sağa doğru sırayla bağlantımızı yapalım 
// Tuş takımını ilk dört bağlantısı SATIRLARIN bağlantısı
// Son dört bağlantısı ise SÜTUNLARIN bağlantısıdır
byte satirPinleri[SATIR] = {7, 6, 5, 4};    // Satır bağlantılarını Arduino'da bağlandığı pinleri tanımla 
byte sutunPinleri[SUTUN] = {3, 2, 1, 0};    // Sütun bağlantılarını Arduino'da bağlandığı pinleri tanımla

// Tuş takımı için Keypad'i tanımla
Keypad tus_takimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);  

LiquidCrystal_I2C lcd(0x27, 16, 2);         // 1602 LCD ekranı tanımla

byte karakters[8] = {0x0, 0xF, 0x10, 0xE, 0x1, 0x1E, 0x4, 0x0};    // ş karakteri
byte karakteri[8] = {0x0, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0};      // ı karakteri
byte karakterS[8] = {0xF, 0x10, 0x10, 0xE, 0x1, 0x1, 0x1E, 0x4};   // Büyük Ş karakteri

void setup() {
    lcd.begin();                   // LCD'yi başlat
    lcd.backlight();              // LCD arka ışıklarını aç

    lcd.createChar(1, karakters); // ş karakterini oluştur ve 1. adrese tanımla
    lcd.createChar(2, karakteri); // ı karakterini oluştur ve 2. adrese tanımla
    lcd.createChar(3, karakterS); // Ş karakterini oluştur ve 3. adrese tanımla
  
    lcd.clear();                  // LCD'yi temizle
    lcd.setCursor(0, 0);          // İlk satıra geç 
    lcd.print("TEES ELEKTRONIK"); // TEES ELEKTRONIK yaz
    lcd.setCursor(3, 1);          // İkinci satırda 3.sütuna geç
    lcd.print("TU");
    lcd.write((byte)3);
    lcd.print(" TAKIMI");     
    delay(1000);                  // 1 saniye kadar bekle
    lcd.clear();                  // LCD ekranı temizle
    lcd.print("Bir Tu");
    lcd.write((byte)1);
    lcd.print("a Bas");
    lcd.write((byte)2);
    lcd.print("n   ");
}

void loop() {
    char Basilan_tus = tus_takimi.getKey();  // Keypad'den basılan tuşu Basilan_tus karakterine kaydet
    
    if (Basilan_tus) {                       // Eğer tuşa basıldı ise
        lcd.clear();                         // LCD'yi temizle
        lcd.setCursor(0, 0);                 // İlk Satıra Geç
        lcd.print("   Tu");
        lcd.write((byte)1);
        lcd.print(" Tak");
        lcd.write((byte)2);
        lcd.print("m");
        lcd.write((byte)2);
        lcd.setCursor(7, 1);
        lcd.print(Basilan_tus);              // Keypad'den basılan tuşu yazdır
    }
}