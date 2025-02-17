// SA33 - Dijital Pil Test Aleti

#include <LiquidCrystal_I2C.h>                     // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);               // 1602 LCD ekranı tanımla

// LCD ekranda pil sembolünün oluşturulması için gerekli karakterleri tanımla
uint8_t karakter1[8] = {0x3, 0x2, 0x2, 0xE, 0x10, 0x1F, 0x1F, 0x1F};  
uint8_t karakter2[8] = {0x18, 0x8, 0x8, 0xE, 0x1, 0x1F, 0x1F, 0x1F}; 
uint8_t karakter3[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}; 
uint8_t karakter4[8] = {0x3, 0x2, 0x2, 0xE, 0x10, 0x10, 0x10, 0x10};  
uint8_t karakter5[8] = {0x18, 0x8, 0x8, 0xE, 0x1, 0x1, 0x1, 0x1};  
uint8_t karakter6[8] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x1F, 0x1F}; 
uint8_t karakter7[8] = {0x1, 0x1, 0x1, 0x1, 0x1, 0x1F, 0x1F, 0x1F};  
uint8_t karakter8[8] = {0xA, 0x0, 0xE, 0x11, 0x11, 0x11, 0x11, 0xE};   // Ö harfi

int adcPin = 0;                                    // Okuma yapmak için kullanılacak pini tanımla

// Okunan voltajın tutulacağı değişkenleri tanımla
float vout = 0.0; 
float Voltaj = 0.0;
float R1 = 100000.0;                              // + ucuna bağlanan direncin değerini 100K olarak tanımla
float R2 = 10000.0;                               // - ucuna bağlanan direncin değerini 10K olarak tanımla
int okunanDeger = 0;

void setup() {
    lcd.begin();                                  // LCD'yi başlat
    lcd.backlight();                              // LCD arka ışıklarını aç 
  
    // Pil sembolü için kullanılacak karakterleri oluştur
    lcd.createChar(1, karakter1); 
    lcd.createChar(2, karakter2); 
    lcd.createChar(3, karakter3); 
    lcd.createChar(4, karakter4); 
    lcd.createChar(5, karakter5); 
    lcd.createChar(6, karakter6);    
    lcd.createChar(7, karakter7); 
    lcd.createChar(8, karakter8);    
   
    pinMode(adcPin, INPUT);                       // ADC pinini giriş pini olarak tanımla
   
    lcd.clear();                                  // LCD'yi temizle
    lcd.setCursor(0, 0);                          // LCD üst satır ilk karakteri seç
    lcd.print("TEES ELEKTRONIK");                 // LCD'ye yaz
    lcd.setCursor(2, 1);                          // LCD alt satır üçüncü karakteri seç
    lcd.print(" Pil ");                           // LCD'ye yaz
    lcd.print(char(8));                           // Ö
    lcd.print("lcer");
    
    delay(3000);                                  // 3sn bekle
    lcd.clear();                                  // LCD'yi temizle
}

void loop() {
    okunanDeger = analogRead(adcPin);             // adcPin deki değeri oku ve okunanDeger'e kaydet
    
    // okunanDeger'i 5 ile çarpıp 1024'e böl ve voltaj karşılığını hesapla
    vout = (okunanDeger * 5.0) / 1024.0;         
    
    // voltaj karşılığındaki değeri dirençlere düşen voltajlar ile orantılayıp ölçülmek istenen voltaj 
    // değerini bul
    Voltaj = vout / (R2/(R1+R2));   
                                  
    if (Voltaj < 0.09) {                         // Eğer voltaj değeri 0.09 değerinden küçük ise 
        Voltaj = 0.0;                            // voltaj değerini sıfır yap
    } 

    // LCD Ekrana pil karakterinin yarı dolu halini getir
    lcd.setCursor(0, 0);
    lcd.print(char(1));
    lcd.print(char(2));
    lcd.setCursor(0, 1);                         // LCD Ekranda 2. satıra geç 
    lcd.print(char(3));
    lcd.print(char(3));
  
    lcd.setCursor(3, 0);
    lcd.print("Pil: ");
    lcd.print(Voltaj);                           // Hesaplanan Voltaj değerini yaz
    lcd.print(" V");                             // V Yaz 
  
    if (Voltaj == 0) {                           // Eğer voltaj 0 ise
        // LCD Ekrana pil karakterinin bitmiş halini getir
        lcd.setCursor(0, 0);
        lcd.print(char(4));
        lcd.print(char(5));
        lcd.setCursor(0, 1);                     // LCD Ekranda 2. satıra geç 
        lcd.print(char(6));
        lcd.print(char(7));
    }
    
    delay(500);
}
