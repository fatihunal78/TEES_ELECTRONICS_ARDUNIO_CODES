// SA32 - Şifreli Kapı Kiliti

#include <Servo.h>              // Servo kütüphanesi ekle
#include <LiquidCrystal_I2C.h>  // I2C LCD kütüphanesini ekle
#include <Keypad.h>             // Keypad kütüphanesi ekle

// Kullandığımız keypadde kaç satır ve sütun olduğunu tanımla
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

// Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[SATIR] = {7, 6, 5, 4};    // Satır bağlantılarını Arduino'da bağlandığı pinleri tanımla
byte sutunPinleri[SUTUN] = {3, 2, 1, 0};    // Sütun bağlantılarını Arduino'da bağlandığı pinleri tanımla

Keypad tusTakimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);  // Tuş takımını başlat

LiquidCrystal_I2C lcd(0x27, 16, 2);         // 1602 LCD ekranı tanımla
                  
Servo servo;                                 // Servo isimli bir servo objesi oluşturduk 

/* String(dizi) birden fazla karakteri hafızada tutmaya yarayan bir değişken tipidir. String parçalama, 
   birleştirme, istenilen harfi bulma/silme/değiştirme gibi özellikler sıkça kullanılmaktadır. */

String girilensifre = "";                    // Girilen şifreyi tutacak değişkeni tanımla
String sifre = "1234";                       // Mevcut kapı şifresini tutacak değişkeni tanımla
int servo_pozisyon;                          // Servoyu açısal değerini tutacak değişkeni tanımla
int servoPin = 11;                          // Servo motorun bağlandığı pin numarasını tanımla

void setup() {  
    servo.attach(servoPin);                  // Servo motorun bağlandığı pini ayarla
    servo.write(0);                          // Servonun başlangıç pozisyonunu sıfır derece olarak ayarla
  
    lcd.begin();                             // LCD'yi başlat
    lcd.backlight();                         // LCD arka ışıklarını aç
    lcd.clear();                             // LCD'yi temizle
    lcd.setCursor(0, 0);                     // İlk satıra geç 
    lcd.print("TEES ELEKTRONIK");            // TEES ELEKTRONIK yaz   
    lcd.setCursor(0, 1);                     // LCD alt satıra geç
    lcd.print(" Sifreli Kilit"); 
    delay(2000);                             // 2 saniye bekle
    lcd.clear();                             // LCD'yi temizle
  
    lcd.print("Sifreyi Girin ve");           // LCD'ye Sifreyi Girin ve yaz
    lcd.setCursor(0, 1);                     // Alt satıra geç
    lcd.print("# e basin");                  // # e basin yaz
    delay(3000);                             // 3 saniye bekle
    lcd.clear();                             // LCD'yi temizle
    lcd.print("Sifre:");
}

void loop() {   
    char tus = tusTakimi.getKey();           // Tuş takımından basılan tuşları kaydet
    
    if (tus != NO_KEY) {                     // Eğer tuşa basıldı ise 
        switch(tus) {                        // Switch case yapısı ile hangi tuşa basıldı ise o tuştaki işlemi yap 
            case '#':
                lcd.setCursor(0, 0);                 
                if (girilensifre == sifre) {  // Eğer girilen şifre kapı şifresi ile aynı ise
                    for (servo_pozisyon = 0; servo_pozisyon <= 90; servo_pozisyon++) {  
                        servo.write(servo_pozisyon);  // Servo_pozisyon değişkenini servoya yaz
                        delay(30);                    // 30ms bekle
                    }
                    lcd.print("Kapi Acik * ile ");    // LCD ekrana Kapı Açık * ile Kapatabilirsiniz yaz 
                    lcd.setCursor(0, 1);
                    lcd.print("Kapatabilirsiniz");
                } else {                              // Eğer girilen şifre kapı şifresi ile aynı değilse
                    lcd.print("Gecersiz Sifre");      // Ekrana Gecersiz Sifre yazdır               
                }
                girilensifre = "";                    // Girilen şifreyi sıfırla
                break;                                // Case # durumunu bitir
                
            case '*':                                 // Eğer yıldıza basıldı ise
                lcd.clear();                          // LCD'yi temizle
                girilensifre = "";                    // Girilen şifreyi sıfırla 
                if (servo_pozisyon == 0) {            // Eğer servo motor 0 derece konumundaysa
                    servo.write(0);                   // 0 derece konumunda tutmaya devam et
                } else {                              // Eğer servo 90 derece konumundaysa 
                    for (servo_pozisyon = 90; servo_pozisyon > 0; servo_pozisyon--) {
                        servo.write(servo_pozisyon);                  
                        delay(30); 
                    }
                }
                lcd.print("Kapi Kilitlendi !");       // Kapi Kilitlendi yaz
                lcd.setCursor(0, 1);                  // Alt satıra geç 
                lcd.print("Sifreyi Girin");           // Sifreyi Girin yaz
                break;                                // Case * durumunu bitir
                
            default:                                  // Hiç bir case durumu yoksa
                lcd.clear();                          // LCD'yi temizle 
                lcd.print("Sifre:");                  // LCD ekran Sifre: yaz
                girilensifre += tus;                  // Girilen şifreyi yan yana yaz
                for (int i = 0; i < girilensifre.length(); i++) {  // For döngüsü kullanarak LCD ekrana girilen şifreyi yaz
                    lcd.setCursor(6 + i, 0);
                    lcd.print(girilensifre[i]);       // LCD'de girilen şifreyi göster 
                }              
                break;
        }
    }
}
