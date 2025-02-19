// SA42 - Dijital ekranlı çalar saat

#include <LiquidCrystal_I2C.h>    //I2C LCD kütüphanesini ekle
#include <Keypad.h>               //Keypad kütüphanesi eklendi
#include <stdlib.h>               //integer'dan karaktere dönüşüm için gerekli itoa fonksiyonunu kullanmak için 
                                 //gerekli kütüphane

const byte SATIR = 4;             //Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;             //Tuş takımının kaç sütundan oluştuğunu belirt 

//Tuş takımındaki tuşları tanımla 
char Basilan_tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[SATIR] = {13, 12, 11, 10}; 
byte sutunPinleri[SUTUN] = {9, 8, 7, 6}; 

//Tuş takımını başlat
Keypad Tus_Takimi = Keypad(makeKeymap(Basilan_tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);

LiquidCrystal_I2C lcd(0x27, 16, 2);      //1602 LCD ekranı tanımla

int ledPin = 5;                           //LED'in bağlandığı pin numarasını tanımla
int hoparlorPin = 4;                      //Hoparlörün bağlandığı pin numarasını tanımla
int butonPin = 3;                         //Butonun bağlandığı pin numarasını tanımla
int ertelemeButon = 2;                    //Erteleme Butonun bağlandığı pin numarasını tanımla
int Alarm_saat;                           //Alarm saatinin tutulacağı değişkeni tanımla
int Alarm_dakika;                         //Alarm dakikasının tutulacağı değişkeni tanımla
char Alarm_saat_char[2] = {};             //Alarm saatinin tuş takımından basılan değerleri karakter olarak tutacağı değişkeni tanımla
char Alarm_dakika_char[2] = {};           //Alarm dakikasının tuş takımından basılan değerleri karakter olarak tutacağı değişkeni tanımla
char Saat_char[2] = {};                   //Saat değerinin karakter olarak kayıt edilmesi için gerekli değişkeni tanımla
char dakika_char[2] = {};                 //Dakika değerinin karakter olarak kayıt edilmesi için gerekli değişkeni tanımla
int saat;                                 //Saat'in arttırılabilmesi için saat değişkenini integer(tam sayı) olarak tanımla
int dakika;                               //Dakika'nın arttırabilmesi için dakika değişkenini integer (tam sayı) olarak tanımla
int saniye;                               //Saniye'nin arttırabilmesi için saniye değişkenini integer (tam sayı) olarak tanımla
char Basilan_tus;                         //Tuş takımından basılan tuşun kaydedileceği değişkeni tanımla
bool butonDurumu = 0;                     //Butona basılıp basılmadığını kontrol edecek değişkeni tanımla
bool ertelemebutonDurumu = 0;             //Butona basılıp basılmadığını kontrol edecek değişkeni tanımla
int i = 0, j = 0, z = 0, x = 0;          //Karakter olarak oluşturulan saat_char, dakika_char, alarm_saat_char ve 
                                         //alarm_dakika_char değişkenlerinin 0. ve 1. değerlerinin saydırılması için 
                                         //i ve j değişkenlerini tanımla ve ilk değerleri sıfıra eşitle

void Kesme_Fonksiyonu() {                 //Interrupt (Kesme) fonskiyonu tanımla
                                         //Bu fonksiyon kesme işleminin yani butona basıldığında ne yapması gerektiğini tanımlar
                                         //attachInterrupt fonksiyonunu kullanarak bu fonksiyon çağırılır
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > 500) {
        butonDurumu = !butonDurumu;
    }
    last_interrupt_time = interrupt_time;
}

void Erteleme_Fonksiyonu() {              //Erteleme fonksiyonunu tanımla
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > 500) {
        if (saat == Alarm_saat && dakika == Alarm_dakika) {
            ertelemebutonDurumu = 1;
            Alarm_dakika = Alarm_dakika + 3;    //Alarm süresini 3 dakika ertele
            if (Alarm_dakika > 59) {            //Eğer dakika 59'u geçerse
                Alarm_dakika = Alarm_dakika % 10;
                Alarm_saat++;                    //Saati bir arttır
                if (Alarm_saat > 23) {          //Eğer saat 23'ü geçerse
                    Alarm_saat = 0;             //Saati sıfırla
                }
            }
        }
    }
    last_interrupt_time = interrupt_time;
}

void setup() {
    pinMode(butonPin, INPUT);                //butonPin pinini giriş olarak ayarla
    pinMode(ertelemeButon, INPUT_PULLUP);    //ertelemeButon pinini giriş olarak ayarla
    pinMode(ledPin, OUTPUT);                 //LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);            //Hoparlörün bağlandığı pini çıkış olarak ayarla
    
    attachInterrupt(digitalPinToInterrupt(butonPin), Kesme_Fonksiyonu, RISING);         //interrupt (kesme) tanımlamalarını yap
    attachInterrupt(digitalPinToInterrupt(ertelemeButon), Erteleme_Fonksiyonu, RISING); //interrupt (kesme) tanımlamalarını yap
    
    lcd.begin();                            //LCD'yi başlat
    lcd.backlight();                        //LCD arka ışıklarını aç
    lcd.clear();                            //LCD'yi temizle
    lcd.setCursor(0, 0);                    //İlk satıra geç
    lcd.print("TEES ELEKTRONIK");           //TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);                    //Alt satıra geç
    lcd.print("   Calar Saat ");           //LCD'ye yaz
    delay(2000);                            //2 saniye bekle
    lcd.clear();                            //LCD'yi temizle
}

void loop() {
    lcd.print("Saati Giriniz");             //LCD Ekrana Saati Giriniz yaz
    delay(2000);                            //2 saniye bekle
    lcd.clear();                            //LCD'yi temizle

    while (1) {                             //Sonsuz döngüye gir
        Basilan_tus = Tus_Takimi.getKey();  //Keypadden basılan tuşu Basilan_tus karakterine kaydet
        if (Basilan_tus) {                  //Eğer tuşa basıldı ise
            Saat_char[i] = Basilan_tus;     //Saat_char[i] değişkenine basilan tuşu kaydet
            lcd.setCursor(5 + i, 0);        //LCD ekranın ilk satırında 5+i. sütüna git
            lcd.print(Saat_char[i]);        //Tuş takımından basılan değerleri LCD Ekrana yaz
            i++;                            //i değerini bir arttır
            saat = atoi(Saat_char);         //Tuş takımından girilen değerleri integer'a çevir
            
            if (i > 1)                      //Eğer i değeri 1'den büyük ise sonsuz döngüyü bitir
                break;
        }
    }

    while (1) {                             //Sonsuz döngüye gir
        Basilan_tus = Tus_Takimi.getKey();  //Keypadden basılan tuşu Basilan_tus karakterine kaydet
        if (Basilan_tus) {                  //Eğer tuşa basıldı ise
            dakika_char[j] = Basilan_tus;   //dakika_char[j] değişkenine basılan tuşu kaydet
            lcd.print(":");                  //LCD Ekranda : yaz
            lcd.setCursor(8 + j, 0);        //LCD Ekranın ilk satırında 8+j. sütüna git
            lcd.print(dakika_char[j]);      //Tuş takımından basılan değerleri LCD Ekrana yaz
            j++;                            //j değerini bir arttır
            dakika = atoi(dakika_char);     //Tuş takımından girilen değerleri integer'a çevir
        }

        if (j >= 2)                         //Eğer j değeri 2'den büyük ise döngüden çık
            break;
    }

    while (1) {                             //Sonsuz döngüye gir
        dijital_saat();                     //dijital_saat fonksiyonunu çağır
        Basilan_tus = Tus_Takimi.getKey();  //Keypadden basılan tuşu Basilan_tus karakterine kaydet
        if (Basilan_tus == '*')             //Eğer * tuşuna basıldı ise döngüden çık
            break;

        if (butonDurumu == 1) {             //Eğer sonsuz döngüdeyken butona basılırsa
            lcd.print("Alarm Saatini");     //LCD Ekrana Alarm Saatini yaz
            lcd.setCursor(0, 1);            //Alt satıra geç
            lcd.print("Giriniz");           //Giriniz yazdır
            delay(2000);                    //2 saniye bekle
            lcd.clear();                    //LCD'yi temizle

            while (1) {                     //Alarm saatini kurmak için sonsuz döngüye gir
                Basilan_tus = Tus_Takimi.getKey();
                if (Basilan_tus) {
                    Alarm_saat_char[z] = Basilan_tus;
                    lcd.setCursor(5 + z, 0);
                    lcd.print(Alarm_saat_char[z]);
                    z++;
                    Alarm_saat = atoi(Alarm_saat_char);
                    
                    if (z > 1)
                        break;
                }
            }

            while (1) {                     //Alarm dakikasını kurmak için sonsuz döngüye gir
                Basilan_tus = Tus_Takimi.getKey();
                if (Basilan_tus) {
                    Alarm_dakika_char[x] = Basilan_tus;
                    lcd.print(":");
                    lcd.setCursor(8 + x, 0);
                    lcd.print(Alarm_dakika_char[x]);
                    x++;
                    Alarm_dakika = atoi(Alarm_dakika_char);
                }
                if (x >= 2)
                    break;
            }

            while (1) {                     //Saati ve Alarm saatini ekrana yazdırmak için sonsuz döngüye gir
                Alarm_dijital_saat();
                Basilan_tus = Tus_Takimi.getKey();
                if (butonDurumu == 0) {
                    Alarm_saat_char[2] = {}; 
                    Alarm_dakika_char[2] = {}; 
                    break;
                }
                if (ertelemebutonDurumu == 1) {
                    lcd.setCursor(0, 0);
                    lcd.clear();
                    lcd.print("3 DK Ertelendi");
                    delay(1000);
                    ertelemebutonDurumu = 0;
                }
            }
        }
    }
}

void dijital_saat() {
    saniye++;                              //Saniye değişkenini birer birer arttır

    if (saniye > 59) {                     //Eğer saniye değişkeni 59'dan büyük ise
        saniye = 0;                        //Saniye değişkenini sıfırla
        dakika++;                          //Dakikayı bir arttır
    }
    if (dakika > 59) {                     //Eğer dakika 59'dan büyük ise
        saniye = 0;                        //Saniyeyi sıfırla
        dakika = 0;                        //Dakikayı sıfırlar
        saat++;                            //Saati bir arttır
    }
    if (saat > 23) {                       //Eğer saat 23'den büyük ise
        saniye = 0;                        //Saniyeyi sıfırla
        dakika = 0;                        //Dakikayı sıfırla
        saat = 0;                          //Saati sıfırla
    }

    lcd.setCursor(0, 0);                   //LCD'nin ilk satırına git
    lcd.print("      Saat     ");         //Saat yazısını yazdır
    lcd.setCursor(0, 1);                   //LCD'nin alt satırına git

    if (saat < 10) {                       //Eğer saat 10'dan küçükse
        lcd.print("    ");
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(saat);
        lcd.print(":");
    }
    if (saat >= 10) {                      //Eğer saat 10'dan büyük veya eşitse
        lcd.print("    ");
        lcd.print(saat);
        lcd.print(":");
    }
    if (dakika < 10) {                     //Eğer dakika 10'dan küçükse
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(dakika);
        lcd.print(":");
    }
    if (dakika >= 10) {                    //Eğer dakika 10'dan büyük veya eşitse
        lcd.print(dakika);
        lcd.print(":");
    }
    if (saniye < 10) {                     //Eğer saniye 10'dan küçükse
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(saniye);
    }
    if (saniye >= 10) {                    //Eğer saniye 10'dan büyük veya eşitse
        lcd.print(saniye);
    }
    delay(954);                            //954 milisaniyelik gecikme
    lcd.clear();                           //LCD'yi temizle
}

void Alarm_dijital_saat() {
    saniye++;                              //Saniye değişkenini bir arttır

    if (saniye > 59) {                     //Eğer saniye 59'dan büyükse
        saniye = 0;                        //Saniyeyi sıfırla
        dakika++;                          //Dakikayı bir arttır
    }
    if (dakika > 59) {                     //Eğer dakika 59'dan büyükse
        saniye = 0;                        //Saniyeyi sıfırla
        dakika = 0;                        //Dakikayı sıfırla
        saat++;                            //Saati bir arttır
    }
    if (saat > 23) {                       //Eğer saat 23'den büyükse
        saniye = 0;                        //Saniyeyi sıfırla
        dakika = 0;                        //Dakikayı sıfırla
        saat = 0;                          //Saati sıfırla
    }
    
    lcd.setCursor(0, 0);                   //LCD'nin ilk satırına git
    lcd.print("Saat :");                   //Saat: yazısını yazdır

    if (saat < 10) {                       //Eğer saat 10'dan küçükse
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(saat);
        lcd.print(":");
    }
    if (saat >= 10) {                      //Eğer saat 10'dan büyük veya eşitse
        lcd.print(saat);
        lcd.print(":");
    }
    if (dakika < 10) {                     //Eğer dakika 10'dan küçükse
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(dakika);
        lcd.print(":");
    }
    if (dakika >= 10) {                    //Eğer dakika 10'dan büyük veya eşitse
        lcd.print(dakika);
        lcd.print(":");
    }
    if (saniye < 10) {                     //Eğer saniye 10'dan küçükse
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(saniye);
    }
    if (saniye >= 10) {                    //Eğer saniye 10'dan büyük veya eşitse
        lcd.print(saniye);
    }

    lcd.setCursor(0, 1);                   //LCD'nin alt satırına git
    lcd.print("Alarm:");                   //Alarm: yazısını yazdır

    if (Alarm_saat < 10) {                 //Eğer alarm saati 10'dan küçükse
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(Alarm_saat);
        lcd.print(":");
    }
    if (Alarm_saat >= 10) {                //Eğer alarm saati 10'dan büyük veya eşitse
        lcd.print(Alarm_saat);
        lcd.print(":");
    }
    if (Alarm_dakika < 10) {               //Eğer alarm dakikası 10'dan küçükse
        lcd.print("0");                    //Başına 0 ekle
        lcd.print(Alarm_dakika);
        lcd.print(":");
    }
    if (Alarm_dakika >= 10) {              //Eğer alarm dakikası 10'dan büyük veya eşitse
        lcd.print(Alarm_dakika);
        lcd.print(":");
    }
    lcd.print("00");                       //Saniye kısmına 00 yazdır

    if (saat == Alarm_saat && dakika == Alarm_dakika) {    //Eğer saat alarm saatine eşitse
        for (int i = 0; i < 4; i++) {                      //4 kere tekrarla
            tone(hoparlorPin, 2200);                       //Hoparlörden ses çıkar
            digitalWrite(ledPin, HIGH);                     //LED'i yak
            delay(35);                                      //35 milisaniye bekle
            noTone(hoparlorPin);                           //Hoparlörü sustur
            digitalWrite(ledPin, LOW);                      //LED'i söndür
            delay(120);                                     //120 milisaniye bekle
            Basilan_tus = Tus_Takimi.getKey();             //Tuş takımından basılan tuşu kontrol et
        }
        delay(350);                                        //350 milisaniye bekle
    }
    digitalWrite(ledPin, LOW);                             //LED'i söndür
    noTone(hoparlorPin);                                   //Hoparlörü sustur

    delay(952);                                            //952 milisaniye bekle
    lcd.clear();                                          //LCD'yi temizle
}