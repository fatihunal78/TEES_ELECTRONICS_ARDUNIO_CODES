// SA93 - Uzaktan kumandalı FM Radyo

// Kütüphaneleri ekle
#include <Wire.h>
#include <TEA5767N.h>
#include <LiquidCrystal_I2C.h>    // I2C LCD kütüphanesini ekle
#include <IRremote.h>             // IR alıcı kütüphanesini ekle

// Kumanda kodlarını tanımla
#define yukaritusu 0xFF18E7       // Kumanda yukarı yön tuşu 
#define asagitusu  0xFF4AB5       // Kumanda aşağı yön tuşu 
#define OKTusu     0xFF38C7       // Kumanda OK Tuşu

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 1602 LCD ekranı tanımla

int irPin = 2;                        // IR alıcı sinyal bacağının bağlandığı pini tanımla

IRrecv iralici(irPin);               // iralici adında bir IR alıcı tanımla
decode_results sonuc;                 // IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

TEA5767N radyo = TEA5767N();
float radyo_frekans = 87.5;

void setup() {
    iralici.enableIRIn();            // IR alıcıyı başlat  
    
    lcd.begin();                     // LCD'yi başlat
    lcd.backlight();                 // LCD arka ışıklarını aç
    lcd.clear();                     // LCD'yi temizle
    
    delay(250);  
    radyo.selectFrequency(radyo_frekans);
    delay(250);
    radyo.setMonoReception();
    
    lcd.setCursor(0, 0);             // LCD 1. satıra geç
    lcd.print(" TEES ELEKTRONIK");
    lcd.setCursor(0, 1);             // LCD'de 2. satıra geç 
    lcd.print("    FM RADYO    ");   // FM RADYO yaz
    
    lcd.clear(); 
    lcd.setCursor(0, 0);             // LCD 1. satıra geç
    lcd.print(" Radyo Frekans ");
    lcd.setCursor(0, 1);             // LCD'de 2. satıra geç 
    lcd.print("FM : ");
    lcd.print(radyo_frekans);        // Frekans değerini yaz
    lcd.print(" MHz");
}
 
void loop() {
    if (iralici.decode(&sonuc)) {    // IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        if (sonuc.value == OKTusu) { // Eğer OK tuşuna basıldı ise Başlangıç konumuna getirmek için
            radyo_frekans = 87.5;     // radyo_frekans değişkenini ilk radyo kanalına ayarla
            
            // Arttırılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
            radyo.selectFrequency(radyo_frekans);
    
            lcd.clear();              // LCD'yi temizle
            lcd.setCursor(0, 0);      // LCD 1. satıra geç
            lcd.print("Radyo Frekans: ");
            lcd.setCursor(0, 1);      // LCD'de 2. satıra geç 
            lcd.print("FM : ");
            lcd.print(radyo_frekans); // Frekans değerini yaz
            lcd.print(" MHz");
        }
        
        if (sonuc.value == yukaritusu) {  // Eğer yukarı tuşuna basıldı ise 
            radyo_frekans += 0.1;          // radyo_frekans değişkenini 0.1 arttır 
            
            // Arttırılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
            radyo.selectFrequency(radyo_frekans);
    
            lcd.clear();                   // LCD'yi temizle
            lcd.setCursor(0, 0);           // LCD 1. satıra geç
            lcd.print("Radyo Frekans: ");
            lcd.setCursor(0, 1);           // LCD'de 2. satıra geç 
            lcd.print("FM : ");
            lcd.print(radyo_frekans);      // Frekans değerini yaz
            lcd.print(" MHz");
    
            if (radyo_frekans > 108.0) {   // Eğer frekans değeri 108'den büyük ise 
                radyo_frekans = 87.5;      // radyo_frekans değerini 87.5'a ayarla 
                radyo.selectFrequency(radyo_frekans);  // Ayarlanan değeri radyoya gönder
            }
            delay(250);
        }
        else if (sonuc.value == asagitusu) {  // Eğer kumandadan aşağı tuşuna basılı ise 
            radyo_frekans -= 0.1;              // radyo_frekans değişkenini 0.1 azalt
            
            // Azaltılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
            radyo.selectFrequency(radyo_frekans);
    
            lcd.clear();                       // LCD'yi temizle 
            lcd.setCursor(0, 0);               // LCD 1. satıra geç
            lcd.print("Radyo Frekans: ");
            lcd.setCursor(0, 1);               // LCD'de 2. satıra geç 
            lcd.print("FM : ");
            lcd.print(radyo_frekans);          // Frekans değerini yaz
            lcd.print(" MHz");
    
            if (radyo_frekans < 87.5) {        // Eğer frekans değeri 87.5'dan küçük ise 
                radyo_frekans = 108.0;         // radyo_frekans değişkenini 108'e ayarla 
                radyo.selectFrequency(radyo_frekans);  // Ayarlanan değeri radyoya gönder
            }
            delay(250);
        }
        iralici.resume();                      // IR alıcıyı diğer değerleri alabilmesi için sıfırla
        delay(250);
    }
}
