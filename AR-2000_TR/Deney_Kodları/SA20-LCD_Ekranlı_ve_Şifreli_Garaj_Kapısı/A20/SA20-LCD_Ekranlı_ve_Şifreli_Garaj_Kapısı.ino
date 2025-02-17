// SA20 - LCD Ekranlı ve Şifreli Garaj Kapısı

#include <EEPROM.h>              //EEPROM kütüphanesini ekle
#include <IRremote.h>            //IR alıcı kütüphanesini ekle
#include <Servo.h>               //Servo motor kütüphanesini ekle
#include <LiquidCrystal_I2C.h>   //I2C LCD kütüphanesini ekle

//Şifrenin saklanacağı EEPROM adreslerini tanımla
#define addr_sifre1    0
#define addr_sifre2    1
#define addr_sifre3    2
#define addr_sifre4    3

//Şifrenin tutulacağı değişkeni tanımla
int sifre[4];

//Kumanda kodlarını tanımla
#define birTusu        0xFFA25D   //Kumanda 1 tuşu
#define ikiTusu        0xFF629D   //Kumanda 2 tuşu
#define ucTusu         0xFFE21D   //Kumanda 3 tuşu
#define dortTusu       0xFF22DD   //Kumanda 4 tuşu
#define besTusu        0xFF02FD   //Kumanda 5 tuşu
#define altiTusu       0xFFC23D   //Kumanda 6 tuşu
#define yediTusu       0xFFE01F   //Kumanda 7 tuşu
#define sekizTusu      0xFFA857   //Kumanda 8 tuşu
#define dokuzTusu      0xFF906F   //Kumanda 9 tuşu
#define sifirTusu      0xFF9867   //Kumanda 0 tuşu
#define kapiAcKapat    0xFF38C7   //Kumanda OK Tuşu
#define kareTusu       0xFFB04F   //Kare Tuşu

//Gelen sayının tutulacağı değişkeni tanımla
int gelenSayi = 0;

//LCD için ı karakterini tanımla
byte karakteri[8] = {
    0x0, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0    //ı
};
byte karakterc[8] = {
    0x0, 0xE, 0x11, 0x10, 0x11, 0xE, 0x4, 0x0  //ç
};
byte karaktersb[8] = {
    0x0F, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x1E, 0x0C  //Ş
};
byte karaktersk[8] = {
    0x00, 0x00, 0x0F, 0x10, 0x0E, 0x01, 0x1E, 0x04  //ş
};
byte karakterg[8] = {
    0x0E, 0x00, 0x1F, 0x11, 0x1F, 0x01, 0x01, 0x1E  //ğ
};

LiquidCrystal_I2C lcd(0x27, 16, 2);   //1602 LCD ekranı tanımla

int irPin = 2;      //IR alıcı sinyal bacağının bağlandığı pini tanımla
int buzzerPin = 7;  //Buzzer'ın bağlandığı pini tanımla
int servoPin = 5;   //Servo motorun bağlandığı pin numarasını tanımla

IRrecv iralici(irPin);    //iralici adında bir IR alıcı tanımla
decode_results sonuc;     //IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla
Servo servo;             //Servo motoru tanımla

int servoAdim = 90;           //Servo açısının tutulacağı değişkeni tanımla
int sifreSayac = 0;          //Şifre sayaç değerinin tutulacağı değişkeni tanımla
int sifreDegistirmeSayac = 0; //Şifre değiştirme sayacının tutulacağı değişkeni tanımla
int sifreGirisDurumu = 0;     //Kilit durumunun tutulacağı değişkeni tanımla

void setup() {
    iralici.enableIRIn();                //IR alıcıyı başlat
    pinMode(buzzerPin, OUTPUT);          //Buzzer'ın bağlandığı pini çıkış olarak ayarla
    servo.attach(servoPin);              //Servo motorun bağlı olduğu pini tanımla
    servo.write(90);                     //Servo motoru 90 dereceye götür  

    //EEPROM'dan şifre değerlerini okuyoruz
    sifre[0] = EEPROM.read(addr_sifre1);
    sifre[1] = EEPROM.read(addr_sifre2);
    sifre[2] = EEPROM.read(addr_sifre3);
    sifre[3] = EEPROM.read(addr_sifre4);

    //EEPROM'a daha önce kayıt yapılmış mı?
    if (sifre[0] > 9)
        sifre[0] = 1;
    if (sifre[1] > 9)
        sifre[1] = 2;
    if (sifre[2] > 9)
        sifre[2] = 3;
    if (sifre[3] > 9)
        sifre[3] = 4;    

    lcd.begin();                         //LCD'yi başlat
    lcd.backlight();                     //LCD arka ışıklarını aç
    lcd.createChar(1, karakteri);        //ı karakterini oluştur
    lcd.createChar(2, karakterc);        //ç karakterini oluştur
    lcd.createChar(3, karaktersb);       //Ş karakterini oluştur
    lcd.createChar(4, karaktersk);       //ş karakterini oluştur
    lcd.createChar(5, karakterg);        //ğ karakterini oluştur
    
    lcd.clear();                         //LCD'yi temizle
    lcd.setCursor(0, 0);                 //LCD üst satır ilk karakterini seç
    lcd.print("TEES Elektronik");        //LCD'ye yaz
    lcd.setCursor(0, 1);                 //LCD alt satır ilk karakterini seç
    lcd.print("Kilit Uygulamas");        //LCD'ye yaz
    lcd.write(byte(1));                  //LCD'ye yaz
    delay(3000);                         //3sn bekle
    
    lcd.clear();                         //LCD'yi temizle
    lcd.setCursor(0, 0);                 //LCD üst satır ilk karakterini seç
    lcd.write(byte(3));                  //LCD'ye yaz
    lcd.print("ifre # tu");              //LCD'ye yaz
    lcd.write(byte(4));                  //LCD'ye yaz
    lcd.print("uyla");                   //LCD'ye yaz
    lcd.setCursor(0, 1);                 //LCD alt satır ilk karakterini seç
    lcd.print("de");                     //LCD'ye yaz
    lcd.write(byte(5));                  //LCD'ye yaz
    lcd.print("i");                      //LCD'ye yaz
    lcd.write(byte(4));                  //LCD'ye yaz
    lcd.print("tirilebilir");            //LCD'ye yaz
    delay(3000);                         //3sn bekle
    
    lcd.clear();                         //LCD'yi temizle
    lcd.setCursor(2, 0);                 //LCD üst satır üçüncü karakterini seç
    lcd.print("Kap");                    //LCD'ye yaz
    lcd.write(byte(1));                  //LCD'ye yaz
    lcd.print(" Kilitli");               //LCD'ye yaz
    lcd.setCursor(6, 1);                 //LCD alt satır yedinci karakterini seç
    lcd.print("----");                   //LCD'ye yaz
}

void loop() {
    servo.detach();
    
    //Şifre değiştirme durumunu sorgula
    if (sifreGirisDurumu == 0) {         //Şifre değiştirme durumu aktif değilse
        //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        if (iralici.decode(&sonuc)) {
            if (sonuc.value == kareTusu) {    //Kare tuşuna basıldı ise
                sifreGirisDurumu = 1;         //Şifre değiştirmeyi aktif et
                lcd.setCursor(2, 0);
                lcd.write(byte(3));           //LCD'ye yaz
                lcd.print("ifre Girin ");        
            } else {                          //Kare tuşuna basılmadı ise şifreyi algıla
                gelenSayi = sayiCoz(sonuc.value);    //Gelen sayısı çöz
                
                switch (sifreSayac) {
                    case 0:
                        if (gelenSayi == sifre[0]) {     //Şifre karakteri doğru ise
                            sifreSayac++;                //Diğer şifre karakterine geç
                            digitalWrite(buzzerPin, HIGH);
                            delay(300);                   //300ms bekle
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("*---");
                        } else {                         //Şifre karakteri yanlış ise
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                        }
                        break;
                        
                    case 1:
                        if (gelenSayi == sifre[1]) {     //Şifre karakteri doğru ise
                            sifreSayac++;                //Diğer şifre karakterine geç
                            digitalWrite(buzzerPin, HIGH);
                            delay(300);                   //300ms bekle
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("**--");
                        } else {                         //Şifre karakteri yanlış ise
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                        }
                        break;
                        
                    case 2:
                        if (gelenSayi == sifre[2]) {     //Şifre karakteri doğru ise
                            sifreSayac++;                //Diğer şifre karakterine geç
                            digitalWrite(buzzerPin, HIGH);
                            delay(300);                   //300ms bekle
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("***-");
                        } else {                         //Şifre karakteri yanlış ise
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                        }
                        break;
                        
                    case 3:
                        if (gelenSayi == sifre[3]) {     //Şifre karakteri doğru ise
                            sifreSayac++;                //Diğer şifre karakterine geç
                            digitalWrite(buzzerPin, HIGH);
                            delay(300);                   //300ms bekle
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("****");
                            delay(1000);                  //1sn bekle
                            
                            lcd.clear();                  //LCD'yi temizle
                            lcd.setCursor(2, 0);          //LCD üst satır üçüncü karakterini seç
                            lcd.print("Kap");             //LCD'ye yaz
                            lcd.write(byte(1));           //LCD'ye yaz
                            lcd.print(" A");              //LCD'ye yaz
                            lcd.write(byte(2));           //LCD'ye yaz
                            lcd.write(byte(1));           //LCD'ye yaz
                            lcd.print("k");               //LCD'ye yaz
                            lcd.setCursor(6, 1);          //LCD alt satır yedinci karakterini seç
                            lcd.print("----");            //LCD'ye yaz
                            
                            servo.attach(servoPin);       //Servo motoru aktif et
                            servo.write(0);               //Servo motoru 0 dereceye götür
                            delay(1000);                  //1sn bekle
                            servo.detach();               //Servo motoru pasif et
                            
                            sifreSayac = 0;              //Şifre sayacını sıfırla
                        } else {                         //Şifre karakteri yanlış ise
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, HIGH);
                            delay(50);                   //50ms bekle
                            digitalWrite(buzzerPin, LOW);
                        }
                        break;
                }
            }
            iralici.resume();    //IR alıcıyı yeni veri almak için hazırla
        }
        
        //Kapı açık ise ve OK tuşuna basıldı ise
        if (sonuc.value == kapiAcKapat && servoAdim == 0) {
            lcd.clear();                  //LCD'yi temizle
            lcd.setCursor(2, 0);          //LCD üst satır üçüncü karakterini seç
            lcd.print("Kap");             //LCD'ye yaz
            lcd.write(byte(1));           //LCD'ye yaz
            lcd.print(" Kilitli");        //LCD'ye yaz
            lcd.setCursor(6, 1);          //LCD alt satır yedinci karakterini seç
            lcd.print("----");            //LCD'ye yaz
            
            servo.attach(servoPin);       //Servo motoru aktif et
            servo.write(90);              //Servo motoru 90 dereceye götür
            delay(1000);                  //1sn bekle
            servo.detach();               //Servo motoru pasif et
            servoAdim = 90;               //Servo açısını güncelle
        }
    } else {    //Şifre değiştirme durumu aktif ise
        //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        if (iralici.decode(&sonuc)) {
            gelenSayi = sayiCoz(sonuc.value);    //Gelen sayıyı çöz
            
            switch (sifreDegistirmeSayac) {
                case 0:
                    sifre[0] = gelenSayi;         //Yeni şifre karakterini kaydet
                    sifreDegistirmeSayac++;       //Diğer şifre karakterine geç
                    digitalWrite(buzzerPin, HIGH);
                    delay(300);                    //300ms bekle
                    digitalWrite(buzzerPin, LOW);
                    lcd.setCursor(6, 1);
                    lcd.print("*---");
                    break;
                    
                case 1:
                    sifre[1] = gelenSayi;         //Yeni şifre karakterini kaydet
                    sifreDegistirmeSayac++;       //Diğer şifre karakterine geç
                    digitalWrite(buzzerPin, HIGH);
                    delay(300);                    //300ms bekle
                    digitalWrite(buzzerPin, LOW);
                    lcd.setCursor(6, 1);
                    lcd.print("**--");
                    break;
                    
                case 2:
                    sifre[2] = gelenSayi;         //Yeni şifre karakterini kaydet
                    sifreDegistirmeSayac++;       //Diğer şifre karakterine geç
                    digitalWrite(buzzerPin, HIGH);
                    delay(300);                    //300ms bekle
                    digitalWrite(buzzerPin, LOW);
                    lcd.setCursor(6, 1);
                    lcd.print("***-");
                    break;
                    
                case 3:
                    sifre[3] = gelenSayi;         //Yeni şifre karakterini kaydet
                    sifreDegistirmeSayac++;       //Diğer şifre karakterine geç
                    digitalWrite(buzzerPin, HIGH);
                    delay(300);                    //300ms bekle
                    digitalWrite(buzzerPin, LOW);
                    lcd.setCursor(6, 1);
                    lcd.print("****");
                    delay(1000);                   //1sn bekle
                    
                    //Yeni şifreyi EEPROM'a kaydet
                    EEPROM.write(addr_sifre1, sifre[0]);
                    EEPROM.write(addr_sifre2, sifre[1]);
                    EEPROM.write(addr_sifre3, sifre[2]);
                    EEPROM.write(addr_sifre4, sifre[3]);
                    
                    lcd.clear();                   //LCD'yi temizle
                    lcd.setCursor(2, 0);           //LCD üst satır üçüncü karakterini seç
                    lcd.print("Kap");              //LCD'ye yaz
                    lcd.write(byte(1));            //LCD'ye yaz
                    lcd.print(" Kilitli");         //LCD'ye yaz
                    lcd.setCursor(6, 1);           //LCD alt satır yedinci karakterini seç
                    lcd.print("----");             //LCD'ye yaz
                    
                    sifreDegistirmeSayac = 0;      //Şifre değiştirme sayacını sıfırla
                    sifreGirisDurumu = 0;          //Şifre değiştirmeyi pasif et
                    break;
            }
            iralici.resume();    //IR alıcıyı yeni veri almak için hazırla
        }
    }
}

//Kumanda tuşlarından gelen kodları sayıya çeviren fonksiyon
int sayiCoz(unsigned long deger) {
    switch (deger) {
        case birTusu:
            return 1;
            break;
        case ikiTusu:
            return 2;
            break;
        case ucTusu:
            return 3;
            break;
        case dortTusu:
            return 4;
            break;
        case besTusu:
            return 5;
            break;
        case altiTusu:
            return 6;
            break;
        case yediTusu:
            return 7;
            break;
        case sekizTusu:
            return 8;
            break;
        case dokuzTusu:
            return 9;
            break;
        case sifirTusu:
            return 0;
            break;
        default:
            return -1;
            break;
    }
}
