// SA83 - Sayı tahmin etme oyunu

#include <LiquidCrystal_I2C.h>    // I2C LCD kütüphanesini ekle
#include <Keypad.h>               // Keypad Kütüphanesi ekle
#include <stdlib.h>               // integer'dan karaktere dönüşüm için gerekli itoa fonksiyonunu kullanmak için 
                                 // gerekli kütüphaneyi ekle

const byte SATIR = 4;             // Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;             // Tuş takımının kaç sütundan oluştuğunu belirt 

// Satır ve sütundaki tuşların yerini ve sırasını tanımla
char tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[SATIR] = {7, 6, 5, 4}; 
byte sutunPinleri[SUTUN] = {3, 2, 1, 0}; 

// Tuş takımını başlat
Keypad tusTakimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);

LiquidCrystal_I2C lcd(0x27, 16, 2);      // 1602 LCD ekranı tanımla

int muzik[] = {
    262, 196, 196, 220, 196, 0, 247, 262
};

int notaSureleri[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};
  
int butonPin = 8;                         // Butonun bağlandığı pin numarasını tanımla
int hoparlorPin = 9;                      // Hoparlörün bağlandığı pin numarasını tanımla
int kirmizi_Led = 12;                     // Kırmızı LED'in bağlandığı pin numarasını tanımla
int yesil_Led = 11;                       // Yeşil LED'in bağlandığı pin numarasını tanımla

char Girilen_Sayi_Char[4] = {};          // Tuş takımından girilen sayı değerinin karakter olarak kayıt edilmesi için 
                                         // gerekli değişkeni tanımla
int Girilen_Sayi;                        // Girilen_Sayi değişkeni integer(tam sayı) olarak tutulacak değişkeni tanımla
char Basilan_tus;                        // Tuş takımından basılan tuşun kaydedileceği değişkeni tanımla
int rastgeleSayi;                        // rastgele sayının tutulacağı değişkeni tanımla
int i = 0;
int tahmin = 10;                         // Tahmin hakkının tutulacağı değişkeni tanımla ve değerini 10 yap

void setup() {
    pinMode(butonPin, INPUT);            // Butonun bağlandığı pini giriş olarak ayarla
    pinMode(hoparlorPin, OUTPUT);        // Hoparlörün bağlandığı pini çıkış olarak ayarla 
    pinMode(kirmizi_Led, OUTPUT);        // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla 
    pinMode(yesil_Led, OUTPUT);          // Yeşil LED'in bağlandığı pini çıkış olarak ayarla 
  
    lcd.begin();                         // LCD'yi başlat
    lcd.backlight();                     // LCD arka ışıklarını aç
    lcd.clear();                         // LCD'yi temizle
    lcd.setCursor(0, 0);                 // İlk satıra geç
    lcd.print("TEES ELEKTRONIK");        // TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);                 // LCD alt satıra geç
    lcd.print("Sayi Tahmin Etme");       // Sayi Tahmin Etme yaz
    delay(2000);                         // 2 saniye bekle
    lcd.clear();                         // LCD'yi temizle

    lcd.setCursor(0, 0);                 // LCD ekranda ilk satıra
    lcd.print("Butona Bas ve   ");       // Butona Bas ve yaz
    lcd.setCursor(0, 1);                 // LCD ekranda alt satıra
    lcd.print("Sayiyi Tahmin Et");       // Sayiyi tahmin et yaz
}

void loop() { 
    randomSeed(analogRead(A0));          // Rastgele sayı üretmek için A0 pinini referans olarak al
    rastgeleSayi = random(0, 100);       // 0 ile 100 arasında rastgele sayı üret ve rastgeleSayi değişkenine kaydet
  
    if (digitalRead(butonPin) == HIGH) {
        lcd.clear();                     // LCD'yi temizle 
        digitalWrite(yesil_Led, HIGH);    // Yeşil LED'i yak
        
        while (1) {                      // Sonsuz döngüye gir
            Basilan_tus = tusTakimi.getKey();    // Tuş takımından basılan tuşları kaydet
            
            if (Basilan_tus != NO_KEY) {         // Eğer tuşa basıldı ise
                lcd.clear();                      // LCD'yi temizle
                Girilen_Sayi_Char[i] = Basilan_tus;  // Girilen_Sayi_Char[i] değişkenine basilan tuşu kaydet
                i++;                              // i değerini bir arttır
                Girilen_Sayi = atoi(Girilen_Sayi_Char);  // Tuş takımından girilen değerleri tam sayıya çevir

                lcd.setCursor(0, 1);
                lcd.print("Girilen: ");
                lcd.print(Girilen_Sayi);

                if (Basilan_tus == '#') {
                    i = 0;
                    if (Girilen_Sayi == rastgeleSayi) {  // Eğer tuş takımından girilen sayı ile rastgele sayı eşit ise
                        lcd.clear();                      // LCD'yi temizle
                        lcd.setCursor(0, 0);              // LCD ekranda ilk satıra geç
                        lcd.print("** Tebrikler **");     // Tebrikler yazdır
                        tahmin = 10;                      // Yeni oyun için tahmin değişkenini 10 yap
                        temizle();                        // Girilen sayının içindeki veriyi temizle
                        digitalWrite(yesil_Led, HIGH);
                        kazandi();                        // Oyunun kazanıldığını bildir
                        break;
                    }
                    else if (Girilen_Sayi < rastgeleSayi) {  // Eğer girilen sayı rastgele sayıdan küçük ise
                        lcd.clear();                          // LCD'yi temizle
                        lcd.setCursor(0, 0);                  // LCD ekranda ilk satıra
                        lcd.print("Bilemedin! Daha ");
                        lcd.setCursor(0, 1);                  // LCD ekranda alt satıra geç
                        lcd.print("Buyuk olmali");
                        tahmin--;                             // tahmin değerini 1 azalt
                        lcd.setCursor(13, 1);                 // Alt satırda 13.sütuna git
                        lcd.print("T:");                      // T: yaz
                        lcd.print(tahmin);                    // Kalan tahmin değerini yazdır
                        temizle();
                    }
                    else {                                    // Eğer girilen sayı rastgele sayıdan büyük ise
                        lcd.clear();                          // LCD'yi temizle
                        lcd.setCursor(0, 0);                  // LCD ekranda ilk satıra
                        lcd.print("Bilemedin! Daha ");
                        lcd.setCursor(0, 1);                  // LCD ekranda alt satıra geç
                        lcd.print("Kucuk olmali");
                        tahmin--;                             // tahmin değerini 1 azalt
                        lcd.setCursor(13, 1);                 // Alt satırda 13.sütuna git
                        lcd.print("T:");                      // T: yaz
                        lcd.print(tahmin);                    // Kalan tahmin değerini yazdır
                        temizle();
                    }

                    if (tahmin == 0) {                       // Eğer tahmin etme sayısı bitti ise 
                        yenilgi();                           // yenilgi() fonksiyonunu çağır
                        tahmin = 10;                         // yeni oyun için tahmin değerini 10 yap
                        break;
                    }
                }
            }
        }
    }
}

void temizle() {                                            // Tuş takımından girilen sayı değişkenini temizle
    for (int j = 0; j <= 5; j++) {                         // j değerini 0'dan 5'e kadar birer arttır
        Girilen_Sayi_Char[j] = 0;                         // Girilen_Sayi_Char her bir değeri 0'a eşitle
    }
}

void yenilgi() {                                           // yenilgi() foksiyonunu oluştur 
    for (int j = 1; j < 4; j++) { 
        lcd.setCursor(0, 0);
        lcd.print("Kaybettin        ");
        lcd.setCursor(0, 1);
        lcd.print("Yeniden Basla    ");
        digitalWrite(yesil_Led, LOW);  
        tone(hoparlorPin, 100);  
        digitalWrite(kirmizi_Led, HIGH); 
        delay(500);
        noTone(hoparlorPin);   
        digitalWrite(kirmizi_Led, LOW);  
        delay(500);
    }
}

void kazandi() {                                           // Kazanma animasyonu fonksiyonunu tanımla
    for (int i = 0; i < 8; i++) {
        int notaSuresi = 1000 / notaSureleri[i];
        tone(hoparlorPin, muzik[i], notaSuresi);
        digitalWrite(yesil_Led, HIGH);
        int notalarArasiBekleme = notaSuresi * 1.30;        
        delay(notalarArasiBekleme / 2);
        digitalWrite(yesil_Led, LOW);
        noTone(hoparlorPin);
    }
}
