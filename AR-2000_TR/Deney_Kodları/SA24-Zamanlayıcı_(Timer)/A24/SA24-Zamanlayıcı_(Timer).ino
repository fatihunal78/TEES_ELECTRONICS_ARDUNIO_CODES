//SA24 - Zamanlayıcı (Timer)

//IR alıcı kütüphanesini ekle
#include <IRremote.h>
//I2C LCD kütüphanesini ekle
#include <LiquidCrystal_I2C.h>

//Kumanda kodlarını tanımla
#define birTusu     0xFFA25D   //Kumanda 1 tuşu
#define ikiTusu     0xFF629D   //Kumanda 2 tuşu
#define ucTusu      0xFFE21D   //Kumanda 3 tuşu
#define dortTusu    0xFF22DD   //Kumanda 4 tuşu
#define besTusu     0xFF02FD   //Kumanda 5 tuşu
#define altiTusu    0xFFC23D   //Kumanda 6 tuşu
#define yediTusu    0xFFE01F   //Kumanda 7 tuşu
#define sekizTusu   0xFFA857   //Kumanda 8 tuşu
#define dokuzTusu   0xFF906F   //Kumanda 9 tuşu
#define sifirTusu   0xFF9867   //Kumanda 0 tuşu
#define kareTusu    0xFFB04F   //Kare Tuşu
#define yildizTusu  0xFF6897   //Yıldız Tuşu
#define solTus      0xFF10EF   //Sol Tuş
#define sagTus      0xFF5AA5   //Sağ Tuş

//LCD için Türkçe karakteri tanımla
byte karakteri[8] = {0x0, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0};          //ı
byte karakterc[8] = {0x0, 0xE, 0x11, 0x10, 0x11, 0xE, 0x4, 0x0};       //ç
byte karakterg[8] = {0x0E, 0x00, 0x1F, 0x11, 0x1F, 0x01, 0x01, 0x1E};  //ğ
byte karaktersk[8] = {0x00, 0x00, 0x0F, 0x10, 0x0E, 0x01, 0x1E, 0x04}; //ş
byte karakteru[8] = {0x0, 0xA, 0x0, 0x11, 0x11, 0x11, 0xE, 0x0};       //ü

//1602 LCD ekranı tanımla
LiquidCrystal_I2C lcd(0x27, 16, 2);

//IR alıcı sinyal bacağının bağlandığı pini tanımla
int irPin = 2;
//Buzzer'ın bağlandığı pini tanımla
int buzzerPin = 7;
//iralici adında bir IR alıcı tanımla
IRrecv iralici(irPin);
//IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla
decode_results sonuc;

//Saniye sayaç değerinin tutulacağı değişkenleri tanımla
int saniyeSayac = 0;
int saniyeOndalik = 0;
int saniyeBirlik = 0;
int sayacDegeri = 0;

void setup() {
    //IR alıcıyı başlat
    iralici.enableIRIn();
    //Buzzer'ın bağlandığı pini çıkış olarak ayarla
    pinMode(buzzerPin, OUTPUT);

    lcd.begin();
    lcd.backlight();
    //Eklenen Türkçe karakterleri tanımla
    lcd.createChar(1, karakteri);  //ı karakterini oluştur
    lcd.createChar(2, karakterc);  //ç karakterini oluştur
    lcd.createChar(3, karakterg);  //ğ karakterini oluştur
    lcd.createChar(4, karaktersk); //ş karakterini oluştur
    lcd.createChar(5, karakteru);  //ü karakterini oluştur
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEES Elektronik");
    lcd.setCursor(2, 1);
    lcd.print("Zamanlay");
    lcd.write(byte(1));
    lcd.print("c");
    lcd.write(byte(1));
    delay(3000);
    lcd.clear();
}

void sayacArttir() {
    saniyeSayac++;
    digitalWrite(buzzerPin, HIGH);
    delay(150);
    digitalWrite(buzzerPin, LOW);
}

void loop() {
    switch(saniyeSayac) {
        case 0: //Saniye ondalık hanesi girişi
            lcd.setCursor(2, 0);
            lcd.print("Saya");
            lcd.write(byte(2));
            lcd.print(" De");
            lcd.write(byte(3));
            lcd.print("eri");
            lcd.setCursor(3, 1);
            lcd.print(saniyeOndalik);
            lcd.print(saniyeBirlik);
            lcd.print(" saniye");
            delay(500);
            lcd.setCursor(3, 1);
            lcd.print(" ");
            delay(500);
            
            //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
            if (iralici.decode(&sonuc)) {
                if (sonuc.value == birTusu) {
                    saniyeOndalik = 1;
                    sayacArttir();
                }
                else if (sonuc.value == ikiTusu) {
                    saniyeOndalik = 2;
                    sayacArttir();
                }
                else if (sonuc.value == ucTusu) {
                    saniyeOndalik = 3;
                    sayacArttir();
                }
                else if (sonuc.value == dortTusu) {
                    saniyeOndalik = 4;
                    sayacArttir();
                }
                else if (sonuc.value == besTusu) {
                    saniyeOndalik = 5;
                    sayacArttir();
                }
                else if (sonuc.value == altiTusu) {
                    saniyeOndalik = 6;
                    sayacArttir();
                }
                else if (sonuc.value == yediTusu) {
                    saniyeOndalik = 7;
                    sayacArttir();
                }
                else if (sonuc.value == sekizTusu) {
                    saniyeOndalik = 8;
                    sayacArttir();
                }
                else if (sonuc.value == dokuzTusu) {
                    saniyeOndalik = 9;
                    sayacArttir();
                }
                else if (sonuc.value == sifirTusu) {
                    saniyeOndalik = 0;
                    sayacArttir();
                }
                else if (sonuc.value == sagTus) {
                    sayacArttir();
                }
                
                if (saniyeSayac == 1)
                    lcd.clear();
                iralici.resume();
            }
            break;

        case 1: //Saniye birlik hanesi girişi
            lcd.setCursor(2, 0);
            lcd.print("Saya");
            lcd.write(byte(2));
            lcd.print(" De");
            lcd.write(byte(3));
            lcd.print("eri");
            lcd.setCursor(3, 1);
            lcd.print(saniyeOndalik);
            lcd.print(saniyeBirlik);
            lcd.print(" saniye");
            delay(500);
            lcd.setCursor(4, 1);
            lcd.print(" ");
            delay(500);
            
            if (iralici.decode(&sonuc)) {
                if (sonuc.value == birTusu) {
                    saniyeBirlik = 1;
                    sayacArttir();
                }
                else if (sonuc.value == ikiTusu) {
                    saniyeBirlik = 2;
                    sayacArttir();
                }
                else if (sonuc.value == ucTusu) {
                    saniyeBirlik = 3;
                    sayacArttir();
                }
                else if (sonuc.value == dortTusu) {
                    saniyeBirlik = 4;
                    sayacArttir();
                }
                else if (sonuc.value == besTusu) {
                    saniyeBirlik = 5;
                    sayacArttir();
                }
                else if (sonuc.value == altiTusu) {
                    saniyeBirlik = 6;
                    sayacArttir();
                }
                else if (sonuc.value == yediTusu) {
                    saniyeBirlik = 7;
                    sayacArttir();
                }
                else if (sonuc.value == sekizTusu) {
                    saniyeBirlik = 8;
                    sayacArttir();
                }
                else if (sonuc.value == dokuzTusu) {
                    saniyeBirlik = 9;
                    sayacArttir();
                }
                else if (sonuc.value == sifirTusu) {
                    saniyeBirlik = 0;
                    sayacArttir();
                }
                else if (sonuc.value == solTus) {
                    saniyeSayac--;
                    digitalWrite(buzzerPin, HIGH);
                    delay(150);
                    digitalWrite(buzzerPin, LOW);
                    lcd.clear();
                }
                
                if (saniyeSayac == 2) {
                    sayacDegeri = 10 * saniyeOndalik + saniyeBirlik;
                    lcd.clear();
                }
                iralici.resume();
            }
            break;

        case 2: //Başlatmak için beklenen tuş girişi
            lcd.setCursor(0, 0);
            lcd.print("S");
            lcd.write(byte(5));
            lcd.print("re");
            lcd.print(": ");
            lcd.print(sayacDegeri);
            lcd.print(" sn");
            lcd.setCursor(0, 1);
            lcd.print("Ba");
            lcd.write(byte(4));
            lcd.print("latmak i");
            lcd.write(byte(2));
            lcd.print("in *");
            
            if (iralici.decode(&sonuc)) {
                if (sonuc.value == yildizTusu) { //Basılan tuş yıldız ise
                    saniyeSayac++;
                    digitalWrite(buzzerPin, HIGH);
                    delay(150);
                    digitalWrite(buzzerPin, LOW);
                    lcd.clear();
                }
                iralici.resume();
            }
            break;

        case 3: //Geri sayım
            saniyeOndalik = sayacDegeri / 10;
            saniyeBirlik = sayacDegeri % 10;
            lcd.setCursor(0, 0);
            lcd.print("Geri Say");
            lcd.write(byte(1));
            lcd.print("l");
            lcd.write(byte(1));
            lcd.print("yor..");
            lcd.setCursor(3, 1);
            lcd.print(saniyeOndalik);
            lcd.print(saniyeBirlik);
            lcd.print(" saniye");
            delay(1000);
            sayacDegeri--;
            
            if (sayacDegeri < 0) {
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Say");
                lcd.write(byte(1));
                lcd.print("m Bitti");
                lcd.setCursor(3, 1);
                lcd.print("#'e Bas");
                lcd.write(byte(1));
                lcd.print("n");
                
                while(1) {
                    digitalWrite(buzzerPin, HIGH);
                    delay(150);
                    digitalWrite(buzzerPin, LOW);
                    delay(150);
                    
                    if (iralici.decode(&sonuc)) {
                        if (sonuc.value == kareTusu) {
                            saniyeSayac = 0;
                            lcd.clear();
                            break;
                        }
                        iralici.resume();
                    }
                }
            }
            break;
    }
}
