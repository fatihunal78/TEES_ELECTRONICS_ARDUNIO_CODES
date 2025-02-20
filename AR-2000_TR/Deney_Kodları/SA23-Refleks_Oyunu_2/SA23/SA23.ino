// SA23 - Refleks Oyunu 2

// I2C LCD kütüphanesini ekle
#include <LiquidCrystal_I2C.h>

// 1602 LCD ekranı tanımla
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte karakterk[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};    // Kutu karakteri
byte karakterok[8] = {0x00, 0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04};    // OK karakteri
#define hedef 8

int muzik[] = {
    262, 196, 196, 220, 196, 0, 247, 262
};

int notaSureleri[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};

int karakter = 0;                // Karakterin hangi karakterde olacağının tutulacağı değişkeni tanımla
int ButonPB2 = 2;               // PB2 Buton'un bağlandığı pin numarasını tanımla
int ButonPB1 = 3;               // PB1 Buton'un bağlandığı pin numarasını tanımla
int hoparlorPin = 4;            // Hoparlörün bağlandığı pin numarasını tanımla
int zorlukSeviyesi = 3;         // 1 - zor, 2 - orta, 3 - basit
long seviye;
unsigned long long sonZaman;     // Son zamanın tutulacağı değişkeni tanımla

void setup() {
    pinMode(ButonPB2, INPUT_PULLUP);      // PB2 Butonun bağlandığı pini giriş olarak ayarla
    pinMode(ButonPB1, INPUT_PULLUP);      // PB1 Butonun bağlandığı pini giriş olarak ayarla
    pinMode(hoparlorPin, OUTPUT);          // Hoparlörün bağlandığı pini çıkış olarak ayarla

    lcd.begin();                          // LCD'yi başlat
    lcd.backlight();                      // LCD arka ışıklarını aç
    lcd.createChar(1, karakterk);         // Kutu karakterini oluştur
    lcd.createChar(2, karakterok);        // Ok karakterini oluştur
    lcd.clear();                          // LCD'yi temizle
    lcd.setCursor(0, 0);
    lcd.print("TEES Elektronik");
    lcd.setCursor(0, 1);
    lcd.print("Refleks Oyunu 2");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);                  // LCD ekranda ilk satır ve ilk sütuna git
    lcd.print(" Zorluk Seviyesi");
    lcd.setCursor(6, 1);                  // LCD ekranda alt satır ve altıncı sütuna git
    lcd.print("Kolay");
}

void loop() {
    lcd.setCursor(0, 0);                  // LCD ekranda ilk satır ve ilk sütuna git
    lcd.print(" Zorluk Seviyesi");
    
    if (digitalRead(ButonPB1) == LOW) {   // Eğer PB1 butonuna basıldı ise 
        zorlukSeviyesi--;                 // Zorluk seviyesini arttır
        if (zorlukSeviyesi < 1) zorlukSeviyesi = 3;
        delay(200);                       // 200 ms bekle    
        
        if (zorlukSeviyesi == 3) {       // Eğer zorlukSeviyesi değişkeni 3 ise lcd ekranın alt satırına "Kolay" yaz
            lcd.clear(); 
            lcd.setCursor(6, 1); 
            lcd.print("Kolay");
        } else if (zorlukSeviyesi == 2) { // Eğer zorlukSeviyesi değişkeni 2 ise lcd ekranın alt satırına "Orta" yaz
            lcd.clear(); 
            lcd.setCursor(6, 1); 
            lcd.print("Orta");
        } else if (zorlukSeviyesi == 1) { // Eğer zorlukSeviyesi değişkeni 1 ise lcd ekranın alt satırına "Zor" yaz
            lcd.clear(); 
            lcd.setCursor(6, 1); 
            lcd.print("Zor");
        }
    }
    
    if (digitalRead(ButonPB2) == LOW) {   // Eğer PB2 butonuna basıldı ise 
        lcd.clear();                      // LCD ekranı temizle 
        while (1) {                       // Sonsuz döngüye gir 
            lcd.setCursor(8, 0);
            lcd.write(byte(2));
            lcd.setCursor(karakter, 1);
            lcd.print(" ");
            karakter = random(0, 16);     // Karakterin geleceği yeri rastgele belirle
            lcd.setCursor(karakter, 1);
            lcd.write(byte(1));
            sonZaman = micros();          // Son zamanı kaydet
            
            // Seviye değişkenini zorluk seviyesini belirlemek için ayarlanan zorlukSeviyesi ile 250000'i çarparak belirle 
            seviye = 250000 * zorlukSeviyesi;
            
            while (micros() - sonZaman <= seviye) {    // Tuşa basılmasını belirle
                if (digitalRead(ButonPB2) == LOW) {    // Butona basıldı ise
                    if (karakter == hedef) {           // Belirlenen karaktere geldiğinde basıldı ise
                        kazandi();                     // Kazandı fonksiyonunu çalıştır
                        break;                         // Döngüden çık
                    } else {                          // Belirlenen karaktere geldiğinde basılamadı ise
                        kaybetti();                   // Kaybetti fonksiyonunu çalıştır
                        break;                        // Döngüden çık
                    }
                }
            }
            if (digitalRead(ButonPB1) == LOW)        // Eğer PB1 butonuna basıldı ise 
                break;                               // Sonsuz döngüden çık
        }
    }
}

// Kaybetme animasyonu fonksiyonunu tanımla
void kaybetti() {
    lcd.setCursor(0, 1);
    lcd.print("                "); 
    for (int j = 1; j < 4; j++) {
        lcd.setCursor(0, 1);
        for (int i = 0; i < 16; i++)
            lcd.write(byte(1));
        tone(hoparlorPin, 100);   
        delay(500);
        noTone(hoparlorPin);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        delay(500);
    }
}

// Kazanma animasyonu fonksiyonunu tanımla
void kazandi() {
    lcd.setCursor(0, 1);
    lcd.print("                ");  
    for (int i = 0; i < 8; i++) {
        int notaSuresi = 1000 / notaSureleri[i];
        tone(hoparlorPin, muzik[i], notaSuresi);
        int notalarArasiBekleme = notaSuresi * 1.30;
        lcd.setCursor(0, 1);
        for (int i = 0; i < 8; i++)
            lcd.write(byte(1));
        delay(notalarArasiBekleme / 2);
        lcd.setCursor(0, 1);
        lcd.print("        ");
        lcd.setCursor(8, 1);
        for (int i = 0; i < 8; i++)
            lcd.write(byte(1));
        delay(notalarArasiBekleme / 2);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        noTone(hoparlorPin);
    }
}
