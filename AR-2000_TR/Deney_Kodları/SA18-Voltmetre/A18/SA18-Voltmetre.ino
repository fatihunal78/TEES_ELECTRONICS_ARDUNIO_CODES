// SA18 - Voltmetre

#include <LiquidCrystal_I2C.h>                    //I2C LCD kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);              //1602 LCD ekranı tanımla

int   adcPin = 0;                                 //Ölçüm yapılacak pini tanımla
float vout = 0.0;                                 //Ölçülen hesaplanan voltajın tutulacağı değişkeni tanımla
float Voltaj = 0.0;                              //Ölçülen gerçek değerin hesaplanacağı değişkeni tanımla
float R1 = 100000.0;                             //Probun + ucuna bağlanan direncin değer 100K
float R2 = 10000.0;                              //Probun - ucuna bağlanan direncin değer 10K
int   okunanDeger = 0;                           //Ölçüm sonucunun tutulacağı değişkeni tanımla

void setup() {
    lcd.begin();                                 //LCD'yi başlat
    lcd.backlight();                             //LCD arka ışıklarını aç 
    pinMode(adcPin, INPUT);                      //ADC pinini giriş olarak tanımla
   
    lcd.clear();                                 //LCD'yi temizle
    lcd.setCursor(0, 0);                         //LCD üst satır ilk karakteri seç
    lcd.print("TEES ELEKTRONIK");                //LCD'ye TEES ELEKTRONIK yaz
    lcd.setCursor(2, 1);                         //LCD alt satır üçüncü karakteri seç
    lcd.print(" VOLTMETRE");                     //LCD'ye VOLTMETRE yaz
    delay(3000);                                 //3sn bekle
    lcd.clear();                                 //LCD'yi temizle
}

void loop() {
    okunanDeger = analogRead(adcPin);            //adcPin'indeki değeri oku ve okunanDeger değişkenine kaydet
    vout = (okunanDeger * 5.0) / 1024.0;         //okunanDeger değişkenini 5 ile çarp, 1024'e böl ve ölçülen değerin 
                                                 //voltaj karşılığını bul
                                        
    Voltaj = vout / (R2/(R1+R2));                //voltaj karşılığındaki değeri dirençlere düşen voltajlar ile oranlayıp
                                                 //ölçülmek istenen voltaj değerini bul
                                  
    if (Voltaj < 0.09) {                         //Eğer Voltaj değeri 0.09 değerinden küçük ise 
        Voltaj = 0.0;                            //Voltaj değerini sıfır yap
    } 
    
    lcd.setCursor(0, 1);                         //LCD ekranda 2. satıra geç 
    lcd.print("VOLTAJ: ");                       //LCD ekrana VOLTAJ yaz 
    lcd.print(Voltaj);                           //Hesaplanan Voltaj değerini yaz
    lcd.print(" V");                             //"V" yaz 
    delay(500);                                  //500 ms bekle
}
