// SA92 - FM Diskotek

#include <Wire.h>                //Haberleşme kütüphanesini ekle
#include <TEA5767N.h>           //FM radyo kütüphanesini ekle
#include <LiquidCrystal_I2C.h>  //I2C LCD kütüphanesini ekle

#include <FreqCount.h>           //Frekans ölçmek için gerekli kütüphaneyi ekle  

LiquidCrystal_I2C lcd(0x27, 16, 2);  //1602 LCD ekranı tanımla

int kirmizi_led = 11;  //Disco Light modülü Kırmızı LED'in bağlandığı pin numarasını tanımla
int sari_led = 10;     //Disco Light modülü Sarı LED'in bağlandığı pin numarasını tanımla
int yesil_led = 9;     //Disco Light modülü Yeşil LED'in bağlandığı pin numarasını tanımla 
int mavi_led = 8;      //Disco Light modülü Mavi LED'in bağlandığı pin numarasını tanımla

int ileri_aramaButon = 3;  //FM RADYO ileri kanal araması için butonun bağlandığı pini tanımla
int geri_aramaButon = 2;   //FM RADYO geri kanal araması için butonun bağlandığı pini tanımla
float frekans;             //frekans değerinin tutulacağı değişkenini tanımla
TEA5767N radyo = TEA5767N();  //radyo isimli bir obje oluştur
float radyo_frekans = 87.5;   //radyo_frekans isimli bir değişken tanımla ve ilk değerini 87.5 yap

void setup() {
    pinMode(ileri_aramaButon, INPUT_PULLUP);  //ileri_aramaButonun bağlandığı pin giriş pini olarak ayarlandı
    pinMode(geri_aramaButon, INPUT_PULLUP);   //geri_aramaButonun bağlandığı pin giriş pini olarak ayarlandı
    pinMode(kirmizi_led, OUTPUT);             //Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sari_led, OUTPUT);                //Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesil_led, OUTPUT);               //Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(mavi_led, OUTPUT);                //Mavi LED'in bağlandığı pini çıkış olarak ayarla
  
    FreqCount.begin(100);  //Frekans ölçümünü başlat ve 100 örnek değer al   
    lcd.begin();          //LCD'yi başlat
    lcd.backlight();      //LCD arka ışıklarını aç
    lcd.clear();          //LCD'yi temizle  
    delay(250);  
    
    radyo.selectFrequency(radyo_frekans);  //Radyoyu 87.5'a ayarla
    delay(250);
    radyo.setStereoReception();
    
    lcd.setCursor(0, 0);            //LCD 1. satıra geç
    lcd.print(" TEES ELEKTRONIK");
    lcd.setCursor(0, 1);            //LCD'de 2. satıra geç 
    lcd.print("    FM RADYO    ");  //FM RADYO yaz
    delay(2000);                    //2 saniye bekle 
    
    lcd.clear(); 
    lcd.setCursor(0, 0);           //LCD 1. satıra geç
    lcd.print(" Radyo Frekans ");
    lcd.setCursor(0, 1);           //LCD'de 2. satıra geç 
    lcd.print("FM : ");
    lcd.print(radyo_frekans);      //Frekans değerini yaz
    lcd.print(" MHz");
}
 
void loop() {
    if (digitalRead(ileri_aramaButon) == LOW) {  //Eğer butona basıldı ise Kanal değiştirmek için aşağıdaki 
                                                 //işlemleri yap 
        radyo_frekans += 0.1;                    //radyo_frekans değişkenini 0.1 arttır 
        radyo.selectFrequency(radyo_frekans);    //Arttırılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
    
        lcd.clear(); 
        lcd.setCursor(0, 0);          //LCD 1. satıra geç
        lcd.print(" Radyo Frekans ");
        lcd.setCursor(0, 1);          //LCD'de 2. satıra geç 
        lcd.print("FM : ");
        lcd.print(radyo_frekans);     //Frekans değerini yaz
        lcd.print(" MHz");
  
        if (radyo_frekans > 108.0) {
            radyo_frekans = 87.5; 
            radyo.selectFrequency(radyo_frekans);
        }
    }
  
    if (digitalRead(geri_aramaButon) == LOW) {  //Eğer geri kanal arama butonuna basıldı ise 
        radyo_frekans -= 0.1;                   //radyo_frekans değişkenini 0.1 azalt 
        radyo.selectFrequency(radyo_frekans);   //Arttırılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
     
        if (radyo_frekans < 87.5) {
            radyo_frekans = 108.0; 
            radyo.selectFrequency(radyo_frekans);
        }
        
        lcd.clear(); 
        lcd.setCursor(0, 0);          //LCD 1. satıra geç
        lcd.print(" Radyo Frekans ");
        lcd.setCursor(0, 1);          //LCD'de 2. satıra geç 
        lcd.print("FM : ");
        lcd.print(radyo_frekans);     //Frekans değerini yaz
        lcd.print(" MHz");
    }

    if (FreqCount.available()) {    
        frekans = FreqCount.read() * 10;  //5 nolu pinde frekans okuma işlemi yap                                              
    }
    
    int oranla = map(frekans, 20, 2000, 0, 16);  //frekans değişkeninde oluşan 20 ile 2000 arası değerleri 0 ile 16 
                                                  //arasında oranla

    switch (oranla) {
        case 0:  //oranla değeri 0 olduğunda 
            //Bütün LED'leri söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 1:  //oranla değeri 1 olduğunda 
            //Kırmızı LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 2:  //oranla değeri 2 olduğunda 
            //Sarı LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 3:  //oranla değeri 3 olduğunda 
            //Yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 4:  //oranla değeri 4 olduğunda 
            //Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;
            
        case 5:  //oranla değeri 5 olduğunda 
            //Kırmızı ve Sarı LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 6:  //oranla değeri 6 olduğunda 
            //Kırmızı ve Yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 7:  //oranla değeri 7 olduğunda 
            //Kırmızı ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;
            
        case 8:  //oranla değeri 8 olduğunda 
            //Sarı ve Yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 9:  //oranla değeri 9 olduğunda 
            //Sarı ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;
            
        case 10:  //oranla değeri 10 olduğunda 
            //Yeşil ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;
            
        case 11:  //oranla değeri 11 olduğunda 
            //Kırmızı Sarı ve yeşil LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, LOW);
            break;
            
        case 12:  //oranla değeri 12 olduğunda 
            //Kırmızı, Sarı ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, LOW);
            digitalWrite(mavi_led, HIGH);
            break;
            
        case 13:  //oranla değeri 13 olduğunda 
            //Kırmızı, Yeşil ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, LOW);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;
            
        case 14:  //oranla değeri 14 olduğunda 
            //Sarı, Yeşil ve Mavi LED'i yak diğerlerini söndür 
            digitalWrite(kirmizi_led, LOW);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;
            
        case 15:  //oranla değeri 15 olduğunda 
            //Bütün LED'leri yak
            digitalWrite(kirmizi_led, HIGH);
            digitalWrite(sari_led, HIGH);
            digitalWrite(yesil_led, HIGH);
            digitalWrite(mavi_led, HIGH);
            break;
    }
    delay(10);
}
