// SA106 - Nabız Ölçer

#define USE_ARDUINO_INTERRUPTS true    // Kalp Ritmi ölçümü icin gerekli kesmeleri aktif et 
#include <PulseSensorPlayground.h>     // Pulse Sensor kütüphanesini ekle
#include <LiquidCrystal_I2C.h>        // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);   // 1602 LCD ekranı tanımla

const int PulseSensor  = A0;           // Sensörün bağlandığı pin numarasını tanımla
const int ledPin       = 3;            // LED'in bağlandığı pin numarasını tanımla
const int hoparlorPin  = 6;            // Hoparlörün pin numarasını tanımla

int Threshold = 200;                   // Sensörün düzgün okuma yapması için bu değer ayarlanabilir
                                 
uint8_t karakter0[8] = {
    0x0, 0x0, 0xA, 0x1F, 
    0x1F, 0xE, 0x4, 0x0
};                                     // Kalp karakteri
                             
PulseSensorPlayground pulseSensor;     // pulseSensor isimli bir obje oluştur

void setup() {   
    Serial.begin(9600);         
    pinMode(hoparlorPin, OUTPUT);      // Hoparlörün bağlandığı pini çıkış olarak ayarla
  
    lcd.begin();                       // LCD'yi başlat
    lcd.backlight();                   // LCD arka ışıklarını aç
    lcd.clear();                       // LCD'yi temizle
  
    lcd.createChar(0, karakter0);      // Kalp karakterini oluştur ve 0. adrese tanımla
  
    pulseSensor.analogInput(PulseSensor);  // pulseSensor için analog pinden okuma yap 
    pulseSensor.blinkOnPulse(ledPin);      // Her pulse'da LED'in yanması için
    pulseSensor.setThreshold(Threshold);    

    if (pulseSensor.begin()) {    
        lcd.clear();
        lcd.print("BPM:");             // Dakikadaki kalp atışı
    }
  
    lcd.setCursor(0, 0);               // İlk satıra geç
    lcd.print("TEES ELEKTRONIK");      // İlk satıra TEES Elektronik
    lcd.setCursor(0, 1);               // İkinci Satıra
    lcd.print("KALP RITMI OLCUM");     // KALP RITMI OLCUM yaz
    delay(2000);                       // 2 saniye bekle
    
    lcd.clear();
    lcd.setCursor(0, 0);               // İlk satıra geç
    lcd.print("Olcum icin ");          // İlk satıra Olcum icin
    lcd.setCursor(0, 1);               // İkinci Satıra
    lcd.print("Parmaginizi Koyun");    // Parmaginizi Koyun yaz
    delay(2000);                       // 2 saniye bekle
}

void loop() {
    int myBPM = pulseSensor.getBeatsPerMinute();  // Okuma yapmak için kütüphaneden getBeatsPerMinute() 
                                                  // fonksiyonunu çağır
         
    if (pulseSensor.sawStartOfBeat()) {          // Eğer kalp atışı varsa sensörü başlat
        tone(hoparlorPin, 1047);
        lcd.clear();  
        lcd.print((char)0);                       // Kalp karakterini ekrana yazdır
        lcd.print(" BPM:");
        lcd.print(myBPM); 
    }
    else {
        noTone(hoparlorPin);
    }
    delay(10);      
}
