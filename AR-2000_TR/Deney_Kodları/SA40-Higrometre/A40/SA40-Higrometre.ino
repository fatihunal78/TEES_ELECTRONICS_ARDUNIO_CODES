// SA40 - Higrometre

#include <LiquidCrystal_I2C.h>    // I2C LCD kütüphanesini ekle
#include <DHT.h>                   // DHT kütüphanesini ekle

#define DHTPIN 2                   // DHT pin numarasını tanımla
#define DHTTYPE DHT11             // DHT modelini tanımla

DHT dht(DHTPIN, DHTTYPE);         // dht isminde bir sensör oluştur

// 1602 LCD ekranı tanımla
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
    dht.begin();                   // DHT sensörü başlat
    
    lcd.begin();                   // LCD'yi başlat
    lcd.backlight();              // LCD arka ışıklarını aç
    
    lcd.clear();                   // LCD'yi temizle
    lcd.setCursor(0, 0);          // LCD üst satır ilk karakterini seç
    lcd.print("TEES Elektronik"); // LCD'ye yaz
    lcd.setCursor(0, 1);          // LCD alt satır ilk karakterini seç
    lcd.print("  Higrometre  ");  // LCD'ye yaz
    delay(3000);                  // 3sn bekle
    lcd.clear();                  // LCD'yi temizle
}

void loop() {
    int nem = dht.readHumidity(); // DHT nemi sorgula
    
    lcd.setCursor(0, 0);          // LCD ilk satıra geç
    lcd.print("Nem: %");          // LCD'ye yaz
    lcd.print(nem);               // nem değişkenini LCD'ye yaz
    lcd.print(" RH");             // LCD'ye yaz
}
