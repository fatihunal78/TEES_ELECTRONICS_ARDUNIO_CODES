// SA54 - Açı Ölçer

#include <Servo.h>              // Servo Kütüphanesi eklendi
#include <LiquidCrystal_I2C.h>  // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 1602 LCD ekranı tanımla
Servo servo;                          // Servo isimli bir servo objesi oluştur

int xPin = A2;      // Joystick X ekseninin bağlandığı pin numarasını tanımla
int xPozisyonu = 0; // Joystick buton durumunun tutulacağı değişkeni tanımla
int Servoacisi;     // Servonun açı değerinin tutulacağı değişkeni tanımla

uint8_t karakter0[8] = {0x00, 0x0E, 0x11, 0x10, 0x11, 0x0E, 0x04, 0x00};  // Ç harfi 
uint8_t karakter1[8] = {0x0, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0};         // ı harfi 
uint8_t karakter2[8] = {0xC, 0x12, 0x12, 0xC, 0x0, 0x0, 0x0, 0x0};       // derece karakteri 
uint8_t karakter3[8] = {0xA, 0x0, 0xE, 0x11, 0x11, 0x11, 0xE, 0x0};      // Ö harfi  

void setup() {
    servo.attach(2);  // Servo motorun bağlandığı pini ayarla
    servo.write(0);   // Servo motoru 0 derece konumuna al

    lcd.begin();      // LCD'yi başlat
    lcd.backlight();  // LCD arka ışıklarını aç
    lcd.clear();      // LCD'yi temizle  
  
    lcd.createChar(0, karakter0);  // Ç harfini oluştur
    lcd.createChar(1, karakter1);  // ı harfini oluştur
    lcd.createChar(2, karakter2);  // derece karakterini oluştur
    lcd.createChar(3, karakter3);  // Ö harfini oluştur
  
    // Aşağıdaki kodlar LCD Ekrana TEES ELEKTRONIK Açı Ölçer yazdırmak içindir
    lcd.setCursor(0, 0);           // İlk satıra geç 
    lcd.print("TEES ELEKTRONIK");  // TEES ELEKTRONIK yaz   
    lcd.setCursor(0, 1);           // Alt satıra geç
    lcd.print("A"); 
    lcd.print(char(0));
    lcd.print(char(1));
    lcd.print(" ");
    lcd.print(char(3));
    lcd.print("l");
    lcd.print(char(0));
    lcd.print("er");
    delay(2000);                   // 2 saniye bekle
    lcd.clear();                   // LCD'yi temizle
}

void loop() {
    xPozisyonu = analogRead(xPin);                    // Joystick X ekseninin pozisyonunun oku ve xPozisyonu değişkenine kaydet
    Servoacisi = map(xPozisyonu, 1023, 0, 180, 0);   // xPozisyonu değerini servo açısına göre oranla
    servo.write(180-Servoacisi);                      // Servo motorun açısını Servoacisi değişkenine göre ayarla
    
    lcd.print("A");
    lcd.write(byte(0));           // LCD'ye ç yaz
    lcd.write(byte(1));           // LCD'ye ı yaz
    lcd.print(" degeri");         // LCD ekrana Aci orani: yaz  
    lcd.print(": ");              // LCD ekrana boşluk yaz
    lcd.print(Servoacisi);        // LCD ekrana servo motor açısını yaz
    lcd.write(byte(2));           // derece karakterini yaz
    delay(100);                   // 100 ms bekle 
    lcd.clear();                  // LCD'yi temizle 
}
