// SA10 - LCD Yön Gösterici

#include <LiquidCrystal_I2C.h>                    // I2C LCD kütüphanesini ekle

int xPin = A0;                                    // Joystick X ekseninin bağlandığı pin numarasını tanımla
int yPin = A1;                                    // Joystick Y ekseninin bağlandığı pin numarasını tanımla
int butonPin = 2;                                 // Joystick butonunun bağlandığı pin numarasını tanımla

int xPozisyonu = 0;                               // Joystick X ekseninin pozisyonunun tutulacağı değişkeni tanımla
int yPozisyonu = 0;                               // Joystick Y ekseninin pozisyonunun tutulacağı değişkeni tanımla
int butonDurum = 0;                               // Joystick buton durumunun tutulacağı değişkeni tanımla

LiquidCrystal_I2C lcd(0x27, 16, 2);              // 1602 LCD ekranı tanımla

// LCD için yön karakterleri tanımla
byte karaktero[8] = { 0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00 };  // ö karakterini tanımla
byte ortaust[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E, 0x15 };    // Orta üst karakterini tanımla
byte ortaalt[8] = { 0x15, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };    // Orta alt karakterini tanımla

void setup() {
    pinMode(xPin, INPUT);                         // Joystick X ekseninin bağlandığı pini giriş olarak ayarla  
    pinMode(yPin, INPUT);                         // Joystick Y ekseninin bağlandığı pini giriş olarak ayarla   
    pinMode(butonPin, INPUT);                     // Joystick butonunun bağlandığı pini giriş olarak ayarla
    
    digitalWrite(butonPin, OUTPUT);               // Joystick butonunun bağlandığı pini pull-up ayarla
    
    lcd.begin();                                  // LCD'yi başlat
    lcd.backlight();                             // LCD arka ışıklarını aç
    
    // Eklenen karakterleri tanımla
    lcd.createChar(1, karaktero);
    lcd.createChar(2, ortaust);
    lcd.createChar(3, ortaalt);
    
    lcd.clear();                                 // LCD'yi temizle
    lcd.setCursor(0, 0);                         // LCD ilk satır, ilk karaktere git
    lcd.print("TEES Elektronik");                // LCD'ye yaz
    lcd.setCursor(1, 1);                         // LCD alt satır ikinci karakterini seç
    lcd.print("Y");                              // LCD'ye yaz
    lcd.write(byte(1));                          // LCD'ye özel karakteri yaz "ö"
    lcd.print("n G");                            // LCD'ye yaz
    lcd.write(byte(1));                          // LCD'ye özel karakteri yaz "ö"
    lcd.print("sterici");                        // LCD'ye yaz
    delay(3000);                                 // 3sn bekle
    lcd.clear();                                 // LCD'yi temizle
}
 
void loop() {
    // Joystick X ekseninin pozisyonunun oku ve xPozisyonu değişkenine kaydet
    xPozisyonu = analogRead(xPin);
    // Joystick Y ekseninin pozisyonunun oku ve yPozisyonu değişkenine kaydet
    yPozisyonu = analogRead(yPin);
    // Joystick butonunun durumunu oku ve butonDurum değişkenine kaydet
    butonDurum = digitalRead(butonPin);

    if (xPozisyonu > 900 && yPozisyonu > 120) {  // Yön sağ ise, LCD ekrana Sag yaz ve --> göster
        lcd.setCursor(0, 0);
        lcd.print("Sag    ");
        lcd.setCursor(12, 0);
        lcd.print(" ");
        lcd.setCursor(11, 1);
        lcd.print("-->");
    }
    else if (xPozisyonu < 120 && yPozisyonu > 120) {  // Yön sol ise, LCD ekrana Sol yaz ve <-- göster
        lcd.setCursor(0, 0);
        lcd.print("Sol    ");
        lcd.setCursor(12, 0);
        lcd.print(" ");
        lcd.setCursor(11, 1);
        lcd.print("<--");
    }
    else if (xPozisyonu > 120 && yPozisyonu < 120) {  // Yön ileri ise, LCD ekrana Ileri yaz 
        lcd.setCursor(0, 0);
        lcd.print("Ileri  ");
        lcd.setCursor(12, 0);
        lcd.write(byte(2));
        lcd.setCursor(11, 1);
        lcd.print(" | ");
    }
    else if (xPozisyonu > 120 && yPozisyonu > 900) {  // Yön geri ise, LCD ekrana Geri yaz 
        lcd.setCursor(0, 0);
        lcd.print("Geri   ");
        lcd.setCursor(12, 0);
        lcd.print("|");
        lcd.setCursor(11, 1);
        lcd.print(" ");
        lcd.write(byte(3));
        lcd.print(" ");
    }
    else {
        if (butonDurum == LOW) {                 // Butona basıldı ise, LCD ekrana Butona Basildi yaz
            lcd.setCursor(0, 1);
            lcd.print("Butona Basildi  ");
        }
        else {                                   // Butona basılmadı ve joystick ortada ise
            lcd.setCursor(0, 0);
            lcd.print("Orta   ");
            lcd.setCursor(12, 0);
            lcd.print(" ");
            lcd.setCursor(0, 1);
            lcd.print("           <->");
        }
    }
    delay(100);                                  // 100ms bekle
}
