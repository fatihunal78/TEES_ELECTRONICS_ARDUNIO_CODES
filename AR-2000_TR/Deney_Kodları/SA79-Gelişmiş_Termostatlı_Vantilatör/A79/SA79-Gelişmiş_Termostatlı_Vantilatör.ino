// SA79 - Gelişmiş Termostatlı Vantilatör

//DHT kütüphanesini ekle
#include <DHT.h>
//I2C LCD kütüphanesini ekle
#include <LiquidCrystal_I2C.h>

//1602 LCD ekranı tanımla
LiquidCrystal_I2C lcd(0x27, 16, 2);

//derece karakteri
uint8_t karakter0[8] = {0xC, 0x12, 0x12, 0xC, 0x0, 0x0, 0x0, 0x0};

//Potun bağlandığı dijital pin numarasını tanımla
int potPin        = A0;
//Potansiyometre değerinin kaydedileceği değişkeni tanımla
int potDegeri     = 0;
//Ayarlanan sıcaklık değerinin kaydedileceği değişkeni tanımla
int ayarlananSicaklik = 0;
//Sıcaklık değerinin tutulacağı değişkeni tanımla
int sicaklik;
//Vantilatör durumunun tutulacağı değişkeni tanımla
int vantilatorDurumu  = 0;

//Butonun bağlandığı pin numarasını tanımla
int buttonPin = 2;
//LED'in bağlandığı pin numarasını tanımla
int ledPin    = 5;
//Transistörün bağlandığı pin numarasını tanımla
int motorPin  = 4;

//DHT pin numarasını tanımla
#define DHTPIN 3
//DHT modelini tanımla
#define DHTTYPE DHT11
//dht isminde bir sensör oluştur
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    //DHT sensörü başlat
    dht.begin();
    //Transistörün bağlandığı pini çıkış olarak ayarla
    pinMode(motorPin, OUTPUT);
    //LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(ledPin, OUTPUT);
    //Butonun bağlandığı pini giriş olarak ayarla
    pinMode(buttonPin, INPUT_PULLUP);
    
    //LCD'yi başlat
    lcd.begin();
    //LCD arka ışıklarını aç
    lcd.backlight();
    //LCD'yi temizle
    lcd.clear();

    //derece karakterini oluştur ve 0. adrese tanımla
    lcd.createChar(0, karakter0);
    
    //LCD'de ilk satıra geç
    lcd.setCursor(0, 0);
    //İlk satıra Termostatli yaz 
    lcd.print("   Termostatli");
    //Alt satıra geç
    lcd.setCursor(0, 1);
    //Alt satıra Vantilator yaz
    lcd.print("   Vantilator");
    //2 saniye bekle 
    delay(2000);
    //LCD'yi temizle 
    lcd.clear();
}

void loop() {
    //Butona basıldı ise
    if (digitalRead(buttonPin) == LOW) {
        //Butona basıldığı sürece bekle
        while (digitalRead(buttonPin) == LOW);
        //Vantilatör çalışıyorsa
        if (vantilatorDurumu == 1) {
            //Vantilatörü kapalı olarak kaydet
            vantilatorDurumu = 0;
        }
        //Vantilatör çalışmıyorsa
        else {
            //Vantilatörü açık olarak kaydet
            vantilatorDurumu = 1;
        }
    }
    
    //Potansiyometrenin değerini oku ve değişkene kaydet
    potDegeri = analogRead(potPin);
    //Okunan değeri 15-50 aralığına oranla ve değişkene kaydet
    ayarlananSicaklik = map(potDegeri, 0, 1023, 15, 50);
    //DHT sıcaklığı sorgula
    sicaklik = dht.readTemperature();
    
    lcd.setCursor(0, 0);
    lcd.print("Ayarlanan: ");
    lcd.print(ayarlananSicaklik);
    //Derece karakterini ekrana yazdır
    lcd.print((char)0);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Olculen  : ");
    lcd.print(sicaklik);
    //Derece karakterini ekrana yazdır
    lcd.print((char)0);
    lcd.print("C");
    
    //Ölçülen sıcaklık ayarlanan sıcaklıktan yüksekse ya da vantilatör açık olarak kaydedildiyse
    if (sicaklik > ayarlananSicaklik || vantilatorDurumu == 1) {
        //Transistörü iletime geçir
        digitalWrite(motorPin, HIGH);
        //LED'i yak
        digitalWrite(ledPin, HIGH);
    }
    else {
        //Transistörü kesime sok
        digitalWrite(motorPin, LOW);
        //LED'i söndür
        digitalWrite(ledPin, LOW);
    }
    
    //50ms bekle
    delay(50);
}
