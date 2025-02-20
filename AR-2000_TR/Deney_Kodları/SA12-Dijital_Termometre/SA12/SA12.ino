// SA12 - Dijital Termometre
#include <LiquidCrystal_I2C.h>    // I2C LCD kütüphanesini ekle
#include <math.h>                  // math.h kütüphanesini ekle
                                  // Matematik işlemleri için gerekli kütüphane

LiquidCrystal_I2C lcd(0x27, 16, 2);    // 1602 LCD ekranı tanımla

int ntcPin = A0;                        // NTC'nin bağlandığı analog pin numarasını tanımla
int analogDeger;                        // NTC değerinin tutulacağı değişkeni tanımla

double sicaklik;                        // Sıcaklık değerinin tutulacağı değişkeni tanımla

uint8_t karakter1[8] = {               // ı harfi 
    0x0, 0x0, 0x4, 0x4, 
    0x4, 0x4, 0x4, 0x0
};   

uint8_t karakter2[8] = {               // derece karakteri 
    0xC, 0x12, 0x12, 0xC, 
    0x0, 0x0, 0x0, 0x0
}; 

void setup() {  
    lcd.begin();                        // LCD'yi başlat
    lcd.backlight();                    // LCD arka ışıklarını aç
    lcd.clear();                        // LCD'yi temizle

    lcd.createChar(1, karakter1);       // ı harfini yazdırmak için karakteri tanımla
    lcd.createChar(2, karakter2);       // derece karakterini yazdırmak için karakteri tanımla
  
    lcd.setCursor(0, 0);               // LCD ekranda ilk satır, ilk karaktere git 
    lcd.print("TEES ELEKTRONIK");      // TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);               // LCD ekranda ikinci satır, ilk karaktere git
    lcd.print("   TERMOMETRE");        // TERMOMETRE yaz 
    delay(2000);                       // 2 saniye ekran bekle 
    lcd.clear();                       // LCD'yi temizle 
}

void loop() {
    analogDeger = analogRead(ntcPin);   // NTC değerini oku ve analogDeger değişkenine kaydet  
    sicaklik = ntcHesapla(analogDeger); // ntcHesapla fonksiyonu ile sıcaklık değerini hesapla ve sicaklik 
                                       // değişkenine kaydet
    lcd.setCursor(4, 0);               // LCD ekranda ilk satır, dördüncü karaktere git 
                                       // LCD ekranada "Sıcaklık" yazdır
    lcd.print("S"); 
    lcd.print(char(1));
    lcd.print("cakl");
    lcd.print(char(1));
    lcd.print("k");
    lcd.setCursor(4, 1);               // İkinci satır, dördüncü karaktere git
    lcd.print(sicaklik);               // Sıcaklık değerini LCD ekrana yaz 
    lcd.print(char(2));                // Derece işaretini yaz
    lcd.print("C");                    // Santigrad işareti için C yaz
    delay(500);                        // 500ms bekle
    lcd.clear();                       // LCD'yi temizle 
}

double ntcHesapla(int analogOkuma) {   // ntcHesapla fonksiyonunu tanımla
    // NTC özelliklerine göre sıcaklık değerini hesapla
    sicaklik = log(((10240000 / analogOkuma) - 10000));
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;
    // Hesaplanan sıcaklık değerini fonksiyonun çağırıldığı satıra gönder
    return sicaklik;
}
