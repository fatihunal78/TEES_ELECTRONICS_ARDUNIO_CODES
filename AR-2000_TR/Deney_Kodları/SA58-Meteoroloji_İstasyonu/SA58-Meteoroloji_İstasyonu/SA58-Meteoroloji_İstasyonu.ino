// SA58 - Meteoroloji İstasyonu

#include <LiquidCrystal_I2C.h>    //I2C LCD kütüphanesini ekle
#include <DHT.h>                   //DHT kütüphanesini ekle

#define DHTPIN 2                   //DHT pin numarasını tanımla
#define DHTTYPE DHT11             //DHT modelini tanımla

DHT dht(DHTPIN, DHTTYPE);         //dht isminde bir sensör oluştur

//LCD için Türkçe karakterleri tanımla
byte karakterd[8] = {             //derece nokta
    0x02, 0x05, 0x02, 
    0x00, 0x00, 0x00, 
    0x00, 0x00
};

byte karakteri[8] = {             //ı
    0x0, 0x0, 0x4,
    0x4, 0x4, 0x4,
    0x4, 0x0
};

byte karakterTermometre[8] = {    //Termometre sembolü
    0xE, 0xA, 0xA,
    0xE, 0x1F, 0x1F,
    0x1F, 0xE
};

byte karakterSudamla1[8] = {      //Su damlası sembolü 1
    0x4, 0xE, 0x1F,
    0x1F, 0x1F, 0xE,
    0x0, 0x0
};

byte karakterSudamla2[8] = {      //Su damlası sembolü 2
    0x0, 0x0, 0x4,
    0xE, 0x1F, 0x1F,
    0x1F, 0xE
};

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    dht.begin();                  //DHT sensörü başlat
    
    lcd.begin();                  //LCD'yi başlat
    lcd.backlight();             //LCD arka ışıklarını aç
    
    //Eklenen karakterleri tanımla
    lcd.createChar(1, karakteri);         //ı karakterini oluştur
    lcd.createChar(2, karakterd);         //derece karakterini oluştur
    lcd.createChar(3, karakterTermometre);//termometre karakterini oluştur
    lcd.createChar(4, karakterSudamla1);  //su damlası 1 karakterini oluştur
    lcd.createChar(5, karakterSudamla2);  //su damlası 2 karakterini oluştur
    
    lcd.clear();                 //LCD'yi sil
    lcd.setCursor(0, 0);         //LCD üst satır ilk karakterini seç
    lcd.print("TEES Elektronik");//LCD'ye yaz
    lcd.setCursor(0, 1);         //LCD alt satır ilk karakterini seç
    lcd.print("  Meteoroloji "); //LCD'ye yaz
    delay(3000);                 //3sn bekle
    lcd.clear();                 //LCD'yi temizle
}

void loop() {
    int sicaklik = dht.readTemperature();  //DHT sıcaklığı sorgula
    int nem = dht.readHumidity();          //DHT nemi sorgula
    
    lcd.setCursor(0, 0);         //LCD üst satır ilk karakterini seç
    lcd.write(byte(3));          //Termometre sembolünü LCD'ye yaz
    lcd.print(" S");             //LCD'ye yaz
    lcd.write(byte(1));          //LCD'ye yaz
    lcd.print("cakl");           //LCD'ye yaz
    lcd.write(byte(1));          //LCD'ye yaz
    lcd.print("k:");             //LCD'ye yaz
    lcd.print(sicaklik);         //sicaklik değişkenini LCD'ye yaz
    lcd.write(byte(2));          //LCD'ye yaz
    lcd.print("C");              //LCD'ye yaz
    
    lcd.setCursor(0, 1);         //LCD alt satıra geç
    lcd.write(byte(4));          //Su damlası 1 sembolünü LCD'ye yaz
    lcd.write(byte(5));          //Su damlası 2 sembolünü LCD'ye yaz
    lcd.print("Nem :%");         //LCD'ye yaz
    lcd.print(nem);              //nem değişkenini LCD'ye yaz
    lcd.print(" RH");            //LCD'ye yaz
}
