// SA74 - TV Kumandası ile LED Yakma

#include <IRremote.h>         // IR alıcı kütüphanesini ekle
#include <LiquidCrystal_I2C.h>  // I2C LCD kütüphanesini ekle

int irPin = 3;        // IR alıcı sinyal bacağının bağlandığı pini tanımla
int ledPin = 7;       // LED'in bağlandığı pin numarasını tanımla
int ButonPin = 2;     // Butonun bağlandığı pin numarasını tanımla

int ledDurumu = 0;    // LED durumunun açık ya da kapalı olduğunun tutulacağı değişkeni tanımla

unsigned long Basilan_Tus;  // Basılan tuşun kaydedileceği değişkeni tanımla

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 1602 LCD ekranı tanımla

IRrecv iralici(irPin);     // iralici adında bir IR alıcı tanımla
decode_results sonuc;       // IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

void setup() {
    pinMode(ledPin, OUTPUT);         // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(ButonPin, INPUT_PULLUP); // Butonun bağlandığı pini giriş olarak ayarla
    
    lcd.begin();      // LCD'yi başlat
    lcd.backlight();  // LCD arka ışıklarını aç
    lcd.clear();      // LCD'yi temizle
    
    iralici.enableIRIn();  // IR alıcıyı başlat

    lcd.setCursor(0, 0);           // LCD Ekranda ilk satıra 
    lcd.print("TV KUMANDASI ILE"); // TV Kumandası ile yaz
    lcd.setCursor(0, 1);           // Alt satıra 
    lcd.print("   LED YAKMA   ");  // LED Yakma yaz 
    delay(3000);                   // 3 saniye bekle 
    lcd.clear();                   // LCD'yi temizle 
}

void loop() {
    while(1) {
        lcd.setCursor(0, 0);          // LCD Ekranda ilk satıra 
        lcd.print("TV kumandasindan");// TV kumandasindan yaz 
        lcd.setCursor(0, 1);          // Alt satıra 
        lcd.print("bir tusa basin");  // bir tusa basin yaz  
             
        // IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        if (iralici.decode(&sonuc.value)) { // Bilgi geldi ise
            if (&sonuc.value) {
                Basilan_Tus = sonuc.value;
                lcd.clear();
                lcd.print("0x");
                lcd.print(Basilan_Tus, HEX);  // Gelen bilgiyi HEX formatında LCD ekrana gönder
                break;
            }
        }
    }

    while(1) {
        if (digitalRead(ButonPin) == LOW) break;  // Eğer butona basıldı ise sonsuz döngüden çık
             
        if (iralici.decode(&sonuc.value)) {  // Bilgi geldi ise
            if (sonuc.value == Basilan_Tus && ledDurumu == 1) {
                digitalWrite(ledPin, HIGH);
                ledDurumu = 0;
                lcd.clear();
                lcd.print("LED YANIYOR");
            }
            else if (sonuc.value == Basilan_Tus && ledDurumu == 0) {
                digitalWrite(ledPin, LOW);
                ledDurumu = 1;
                lcd.clear();
                lcd.print("LED YANMIYOR");
            }
            iralici.resume();  // IR alıcıyı diğer değerleri alabilmesi için sıfırla
        }
        delay(50);  // 50ms bekle
    }
}