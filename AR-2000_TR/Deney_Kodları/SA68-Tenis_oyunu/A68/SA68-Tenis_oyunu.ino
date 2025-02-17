// SA68 - Tenis oyunu

#include <LedControl.h>         // LedControl kütüphanesi eklendi 
#include <LiquidCrystal_I2C.h> // I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);    // 1602 LCD ekranı tanımla
LedControl lc = LedControl(4, 2, 3, 1); // LED Matriksin (DIN pini: 4, CLK pini: 2, CS pini: 3 bağlandı) 

int potVR2 = A1;                // VR2 potansiyometresinin bağlandığı pini tanımla
int potVR1 = A0;                // VR1 potansiyometresinin bağlandığı pini tanımla
int hoparlorPin = 7;            // Hoparlörün bağlandığı pini tanımla
int VR1OkunanDeger = 0;         // VR1 potansiyometresinden okunan değerlerin kaydedileceği değişkeni tanımla 
int VR2OkunanDeger = 0;         // VR2 potansiyometresinden okunan değerlerin kaydedileceği değişkeni tanımla
int oranlaVR1;                  // VR1 potansiyometresinden okunan değerlerin oranlanacağı değişkeni tanımla 
int oranlaVR2;                  // VR2 potansiyometresinden okunan değerlerin oranlanacağı değişkeni tanımla
int oyuncu1_skor = 0;           // 1.oyuncunun skorunun tutulacağı değişkeni tanımla 
int oyuncu2_skor = 0;           // 2.oyuncunun skorunun tutulacağı değişkeni tanımla 
int x = 2;                      // Topun x ekseni üzerindeki koordinatları 
int y = 4;                      // Topun y ekseni üzerindeki koordinatları 
boolean asagi_yukari = true;    // Topun aşağı yukarı hareketi için değişken tanımlandı 
boolean sag_sol = false;        // Topun sağ sol hareketi için değişken tanımlandı
int oyun_hizi = 300;            // Oyunun başlangıç hızı 300 olarak ayarlandı 

unsigned long sayac = 0;

int oyuncu1_solHareket = 4;
int oyuncu1_ortaHareket = 0;
int oyuncu1_sagHareket = 5;
int oyuncu2_solHareket = 4;
int oyuncu2_ortaHareket = 0;
int oyuncu2_sagHareket = 5;

byte New[] = {
    B00000000,
    B01111110,
    B00010010,
    B00011110,
    B00000000,
    B01111110,
    B01000000,
    B01000000
};

void setup() {
    pinMode(potVR1, INPUT);       // Analog A1 pini giriş olarak ayarla 
    pinMode(potVR2, INPUT);       // Analog A0 pini giriş olarak ayarla
    pinMode(hoparlorPin, OUTPUT); // Hoparlörün bağlandığı pini çıkış olarak ayarla
  
    lcd.begin();                  // LCD'yi başlat
    lcd.backlight();             // LCD arka ışıklarını aç
    lcd.clear();                 // LCD'yi temizle
  
    lc.shutdown(0, false);
    lc.setIntensity(0, 3);       // LED Matriks ekran parlaklığını 3 olarak ayarla
    lc.clearDisplay(0);          // LED Matriks ekranı temizle

    lcd.setCursor(0, 0);         // LCD Ekranı ilk satıra al
    lcd.print("TEES ELEKTRONIK"); // LCD ekrana TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);         // Alt satıra geç
    lcd.print("  TENIS OYUNU "); // TENIS OYUNU yaz
    delay(1500);                 // 1.5 saniye bekle
    lcd.clear();                 // LCD'yi temizle 
}

void loop() {
    VR1OkunanDeger = analogRead(potVR1);  // VR1 potansiyometresin bağlı olduğu analog pindeki değerleri oku 
    VR2OkunanDeger = analogRead(potVR2);  // VR2 potansiyometresin bağlı olduğu analog pindeki değerleri oku 

    oranlaVR1 = map(VR1OkunanDeger, 0, 1023, 0, 6);  // VR1 potansiyometresinden okunan değerleri 0 ile 6 arasında oranla 
    oranlaVR2 = map(VR2OkunanDeger, 0, 1023, 6, 0);  // VR2 potansiyometresinden okunan değerleri 6 ile 0 arasında oranla 

    oyuncu1_solHareket = oranlaVR1 - 1;
    oyuncu1_ortaHareket = oranlaVR1;
    oyuncu1_sagHareket = oranlaVR1 + 1;
    oyuncu2_solHareket = oranlaVR2 - 1;
    oyuncu2_ortaHareket = oranlaVR2;
    oyuncu2_sagHareket = oranlaVR2 + 1;

    lc.setLed(0, x, y, true);
    lc.setLed(0, oyuncu1_solHareket, 0, true);
    lc.setLed(0, oyuncu1_ortaHareket, 0, true);
    lc.setLed(0, oyuncu1_sagHareket, 0, true);
    lc.setLed(0, oyuncu2_solHareket, 7, true);
    lc.setLed(0, oyuncu2_ortaHareket, 7, true);
    lc.setLed(0, oyuncu2_sagHareket, 7, true);
   
    if (x == oyuncu2_sagHareket && y == 6) { 
        asagi_yukari = true; 
        tone(hoparlorPin, 800); 
        delay(20); 
        noTone(hoparlorPin); 
        delay(20); 
    }
    
    if (x == oyuncu2_ortaHareket && y == 6) { 
        asagi_yukari = true; 
        tone(hoparlorPin, 800); 
        delay(20); 
        noTone(hoparlorPin); 
        delay(20); 
    }
    
    if (x == oyuncu2_solHareket && y == 6) { 
        asagi_yukari = true; 
        tone(hoparlorPin, 800); 
        delay(20); 
        noTone(hoparlorPin); 
        delay(20); 
    }
  
    if (x == oyuncu1_sagHareket && y == 1) { 
        asagi_yukari = false; 
        tone(hoparlorPin, 1800); 
        delay(20); 
        noTone(hoparlorPin); 
        delay(20); 
    }
    
    if (x == oyuncu1_solHareket && y == 1) { 
        asagi_yukari = false; 
        tone(hoparlorPin, 1800); 
        delay(20); 
        noTone(hoparlorPin); 
        delay(20); 
    }
    
    if (x == oyuncu1_ortaHareket && y == 1) { 
        asagi_yukari = false; 
        tone(hoparlorPin, 1800); 
        delay(20); 
        noTone(hoparlorPin); 
        delay(20); 
    }
  
    if (x < 1) {
        sag_sol = false;
    }
  
    if (sag_sol == false) {
        x++;
    }
    
    if (x > 7) {
        sag_sol = true; 
        x--;
    }
    
    if (sag_sol == true) {
        x--;
    }
 
    if (asagi_yukari == false) {
        y++;
    }
    
    if (asagi_yukari == true) {
        y--;
    }
    
    if (y == -1 || y == 8) {
        lcd.clear();
    
        if (y == -1) {                // Eğer top üst tabana değdi ise 
            oyuncu2_skor++;           // Oyuncu2_skor değişkenini bir arttır 
        }
        else if (y == 8) {            // Eğer top alt tabana değdi ise 
            oyuncu1_skor++;           // Oyuncu1_skor değişkenini bir arttır  
        }
    
        lcd.setCursor(0, 0);
        lcd.print("1.Oyuncu : ");
        lcd.setCursor(11, 0);         // LCD'yi 11.sütuna ayarla     
        lcd.print(oyuncu1_skor); 
        lcd.setCursor(0, 1);
        lcd.print("2.Oyuncu : ");
        lcd.setCursor(11, 1);         // LCD'yi 11.sütuna ayarla     
        lcd.print(oyuncu2_skor); 

        // Değişkenleri başlangıç durumuna ayarla 
        x = 2;
        y = 4;
        oyuncu1_solHareket = 3;
        oyuncu1_sagHareket = 4;
        oyuncu2_sagHareket = 4;
        oyuncu2_solHareket = 3;
    
        yenilgi();                    // yenilgi() fonksiyonunu çağır  
        
        for (int i = 0; i < 3; i++) {
            tone(hoparlorPin, 1200);
            delay(30);
            noTone(hoparlorPin);
            delay(30);
        }
        delay(1000);                  // 1 saniye bekle 
    }

    sayac++;
    if (sayac % 30 == 0) {
        oyun_hizi = oyun_hizi - 20;
        if (oyun_hizi < 100) {
            oyun_hizi = 100;
        }
    }
    delay(oyun_hizi);
    lc.clearDisplay(0);
}

void yenilgi() {
    // Her iki oyuncudan biri skor aldığında LED'leri sırayla yakma efekti için fonksiyonu tanımla
    lc.clearDisplay(0);
    
    lc.setColumn(0, 7, B11111111);
    delay(10);
    lc.setColumn(0, 6, B11111111);
    delay(10);
    lc.setColumn(0, 5, B11111111);
    delay(10);
    lc.setColumn(0, 4, B11111111);
    delay(10);
    lc.setColumn(0, 3, B11111111);
    delay(10);
    lc.setColumn(0, 2, B11111111);
    delay(10);
    lc.setColumn(0, 1, B11111111);
    delay(10);
    lc.setColumn(0, 0, B11111111);
    delay(10);
    
    lc.setColumn(0, 7, B00000000);
    delay(10);
    lc.setColumn(0, 6, B00000000);
    delay(10);
    lc.setColumn(0, 5, B00000000);
    delay(10);
    lc.setColumn(0, 4, B00000000);
    delay(10);
    lc.setColumn(0, 3, B00000000);
    delay(10);
    lc.setColumn(0, 2, B00000000);
    delay(10);
    lc.setColumn(0, 1, B00000000);
    delay(10);
    lc.setColumn(0, 0, B00000000);
    delay(10);
    
    oyun_hizi = 300;
}
