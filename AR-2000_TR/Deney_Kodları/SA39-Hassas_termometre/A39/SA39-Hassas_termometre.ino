// SA39 - Hassas termometre

#include <LiquidCrystal_I2C.h>    //I2C LCD kütüphanesini ekle
#include <DHT.h>                   //DHT kütüphanesini ekle

#define DHTPIN 2                   //DHT pin numarasını tanımla
#define DHTTYPE DHT11             //DHT modelini tanımla

DHT dht(DHTPIN, DHTTYPE);         //dht isminde bir sensör oluştur

//LCD için Türkçe karakterleri tanımla
byte karakterd[8] = {             //derece nokta
    0x02, 
    0x05, 
    0x02, 
    0x00, 
    0x00, 
    0x00, 
    0x00, 
    0x00
}; 

byte karakteri[8] = {             //ı karakterini oluştur
    0x0,
    0x0,
    0x4,
    0x4,
    0x4,
    0x4,
    0x4,
    0x0
}; 

LiquidCrystal_I2C lcd(0x27, 16, 2);  //1602 LCD ekranı tanımla
 
void setup() {
    dht.begin();                      //DHT sensörü başlat

    lcd.begin();                      //LCD'yi başlat
    lcd.backlight();                  //LCD arka ışıklarını aç
    
    //Eklenen karakterleri tanımla
    lcd.createChar(1, karakteri);     //ı karakterini oluştur
    lcd.createChar(2, karakterd);     //derece karakterini oluştur
    
    lcd.clear();                      //LCD'yi temizle
    lcd.setCursor(0, 0);              //LCD üst satır ilk karakterini seç
    lcd.print("TEES Elektronik");     //LCD'ye yaz
    lcd.setCursor(0, 1);              //LCD alt satır ilk karakterini seç
    lcd.print("DHT11 S");             //LCD'ye yaz
    lcd.write(byte(1));               //LCD'ye yaz
    lcd.print("cakl");                //LCD'ye yaz
    lcd.write(byte(1));               //LCD'ye yaz
    lcd.print("k ");                  //LCD'ye yaz
    
    delay(3000);                      //3sn bekle
    lcd.clear();                      //LCD'yi temizle  
}

void loop() {
    //DHT sıcaklığı sorgula
    int sicaklik = dht.readTemperature();
  
    lcd.setCursor(0, 0);              //LCD üst satır ilk karakterini seç
    lcd.print("S");                   //LCD'ye yaz
    lcd.write(byte(1));               //LCD'ye yaz
    lcd.print("cakl");                //LCD'ye yaz
    lcd.write(byte(1));               //LCD'ye yaz
    lcd.print("k: ");                 //LCD'ye yaz
    lcd.print(sicaklik);              //sicaklik değişkenini LCD'ye yaz
    lcd.write(byte(2));               //LCD'ye yaz
    lcd.print("C");                   //LCD'ye yaz
}
