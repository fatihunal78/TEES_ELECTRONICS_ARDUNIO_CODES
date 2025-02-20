// SA94 - Programlı FM Radyo

#include <TEA5767N.h>           //Radyo kütüphanesini ekle
#include <Keypad.h>             //Keypad kütüphanesini ekle
#include <stdlib.h>             //integer'dan karaktere dönüşüm için gerekli itoa fonksiyonunu kullanmak için 
                               //gerekli kütüphaneyi ekle
#include <LiquidCrystal_I2C.h>  //I2C LCD kütüphanesini ekle

const byte SATIR = 4;           //Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;           //Tuş takımının kaç sütundan oluştuğunu belirt

//Tuş takımındaki tuşları tanımla 
char tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[SATIR] = {13, 12, 11, 10}; 
byte sutunPinleri[SUTUN] = {9, 8, 7, 6}; 

//Tuş takımını başlat
Keypad tus_takimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN); 

LiquidCrystal_I2C lcd(0x27, 16, 2);  //1602 LCD ekranı tanımla

TEA5767N radyo = TEA5767N();         //TEA5767 modülü kontrol etmek için radyo isimli obje oluştur

float radyo_frekans = 87.5;          //radyo_frekans değişkeni oluştur ve ilk değeri 87.5 yap 
                                     //Bu değişken frekansların tutulacağı değişken olacak

char Girilen_Frekans[5] = {};        //Tuş takımından Girilen frekansın kaydedileceği değişken tanımlandı
                                     //Tuş takımından girilen değerler char yani karakter olarak kaydedilir
                            
int i = 0;                          //Tuş takımından sırası ile değerleri girebilmemiz için gerekli değişken

void setup() {
    lcd.begin();                     //LCD'yi başlat
    lcd.backlight();                //LCD arka ışıklarını aç
    lcd.clear();                    //LCD'yi temizle
  
    delay(250);  
    radyo.selectFrequency(radyo_frekans);
    delay(250);
    
    lcd.setCursor(0, 0);            //LCD 1. satıra geç
    lcd.print(" TEES ELEKTRONIK");
    lcd.setCursor(0, 1);            //LCD'de 2. satıra geç 
    lcd.print("    FM RADYO    ");  //Frekans değerini yazdır
    
    lcd.clear(); 
    lcd.setCursor(0, 0);            //LCD 1. satıra geç
    lcd.print(" Radyo Frekans ");
    lcd.setCursor(0, 1);            //LCD'de 2. satıra geç 
    lcd.print("FM : ");
    lcd.print(radyo_frekans);       //Frekans değerini yaz
    lcd.print(" MHz");
}
 
void loop() {
    char Basilan_tus = tus_takimi.getKey();  //Keypadden basılan tuşu Basilan_tus karakterine kaydet
  
    if (Basilan_tus) {                       //Eğer tuşa basıldı ise
        if (Basilan_tus == 'A') {            //Eğer tuş takımından A tuşuna basıldı ise  
                                             //Frekansı arttırıp, kanal değiştirmek için aşağıdaki işlemleri yap 
            radyo_frekans += 0.1;            //radyo_frekans değişkenini 0.1 arttır 
            radyo.selectFrequency(radyo_frekans);  //Arttırılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
  
            lcd.clear();                     //LCD'yi temizle
            lcd.setCursor(0, 0);            //LCD 1. satıra geç
            lcd.print("Radyo Frekans: ");
            lcd.setCursor(0, 1);            //LCD'de 2. satıra geç 
            lcd.print("FM : ");
            lcd.print(radyo_frekans);       //Frekans değerini yaz
            lcd.print(" MHz");
        
            Serial.print("Frekans  : ");
            Serial.println(radyo_frekans);   //Seri port ekranına frekansı yaz

            if (radyo_frekans > 108.0) {     //Eğer frekans değeri 108'den büyük ise 
                radyo_frekans = 87.5;        //radyo_frekans değerini 87.5'a ayarla 
                radyo.selectFrequency(radyo_frekans);  //Ayarlanan değeri radyoya gönder
            }
            delay(250);      
        }
        else if (Basilan_tus == 'B') {       //Eğer tuş takımından B tuşuna basıldı ise  
                                             //Frekansı azaltıp, kanal değiştirmek için aşağıdaki işlemleri yap 
            radyo_frekans -= 0.1;            //radyo_frekans değişkenini 0.1 azalt
            radyo.selectFrequency(radyo_frekans);  //Azaltılmış radyo_frekans değişkenini radyoya yaz ve kanalı aç
  
            lcd.clear();                     //LCD'yi temizle 
            lcd.setCursor(0, 0);            //LCD 1. satıra geç
            lcd.print("Radyo Frekans: ");
            lcd.setCursor(0, 1);            //LCD'de 2. satıra geç 
            lcd.print("FM : ");
            lcd.print(radyo_frekans);       //Frekans değerini yaz
            lcd.print(" MHz");
      
            if (radyo_frekans < 87.5) {     //Eğer frekans değeri 87.5'dan küçük ise 
                radyo_frekans = 108.0;      //radyo_frekans değişkenini 108'e ayarla 
                radyo.selectFrequency(radyo_frekans);  //Ayarlanan değeri radyoya gönder
            }
            delay(250);
        }
        else if (Basilan_tus != 'A' && Basilan_tus != 'B' && Basilan_tus != 'C' && 
                 Basilan_tus != 'D' && Basilan_tus != '*' && Basilan_tus != '#') {
      
            Girilen_Frekans[i] = Basilan_tus;  //Girilen_Frekans[i] değişkenine basilan tuşu kaydet
                                               //Burada i değeri 0,1,2 ve 3 değerleri alacaktır
                                               //Bu sayede frekans değeri girilebilecektir
                                               //(Örn: 1060 girildiği zaman 106.0 ya da 9750 
                                               //girildiği zaman 97.50 olacaktır)
                                       
            lcd.clear();                       //LCD'yi temizle                             
            lcd.setCursor(7 + i, 0);          //LCD Ekranın ilk satırında 7+i. sütüna git
                                             //Eğer i değeri 0 ise 7. sütun i değeri 1 ise 8. sütuna git
      
            lcd.print(Girilen_Frekans[i]);    //Tuş takımından basılan değerleri LCD Ekrana yaz
            i++;                              //i değerini bir arttır
            if (i > 4) i = 0;                //Eğer i değeri 4'den büyük ise i değerini sıfıra eşitle

            for (int i = 0; i < 4; i++) {    //for döngüsü ile, girilen değerleri LCD Ekrana yazdır
                lcd.setCursor(7 + i, 0);      //Satır, Sütun ayarla  
                lcd.print(Girilen_Frekans[i]); //Değerleri yaz 
            }
      
            radyo_frekans = atoi(Girilen_Frekans);  //Tuş takımından girilen değeri tamsayıya çevir
                      
            if (Basilan_tus == '#') {        //Eğer # tuşuna basıldı ise i değerini sıfıra eşitle 
                i = 0;
                if (Girilen_Frekans[0] == '1') {  //Eğer Girilen_Frekans değişkeninin ilk değeri 1 ile 
                                                  //başlıyorsa bu demek oluyorki Girilen frekans değeri 
                                                  //1060 gibi bir değer olmalı 
                    radyo_frekans = radyo_frekans / 10;  //Girilen frekans değerinden tamsayıya çevrilmiş olan 
                                                        //radyo_frekans değişkenini 10'a böl yani 1060 girildi 
                                                        //ise 1060/10= 106 olacaktır. Eğer 1062 girilirse 
                                                        //106.2 olacak. Uygun frekans değerleri belirlenmiş olacak
                    
                    radyo.selectFrequency(radyo_frekans);  //Ayarlanan değeri radyoya gönder    
                    lcd.clear();              //LCD'yi temizle 
                    lcd.setCursor(0, 0);      //LCD 1. satıra geç
                    lcd.print("Radyo Frekans: ");
                    lcd.setCursor(0, 1);      //LCD'de 2. satıra geç 
                    lcd.print("FM : ");
                    lcd.print(radyo_frekans); //Frekans değerini yaz
                    lcd.print(" MHz");
                }
                else {                        //Eğer Girilen_Frekans değişkeninin ilk değeri 1'den farklı bir 
                                             //sayı ile başlıyorsa Bu değerler 8750, 9500 olabilir
              
                    radyo_frekans = radyo_frekans / 100;  //Girilen frekans değerinden tamsayıya çevrilmiş olan 
                                                         //radyo_frekans değişkenini 100'e böl yani 8750 girildi 
                                                         //ise 8750/100= 87.50 olacaktır Uygun frekans değeri 
                                                         //belirlenmiş olacak
         
                    radyo.selectFrequency(radyo_frekans);  //Ayarlanan değeri radyoya gönder    
                    lcd.clear();              //LCD'yi temizle 
                    lcd.setCursor(0, 0);      //LCD 1. satıra geç
                    lcd.print("Radyo Frekans: ");
                    lcd.setCursor(0, 1);      //LCD'de 2. satıra geç 
                    lcd.print("FM : ");
                    lcd.print(radyo_frekans); //Frekans değerini yaz
                    lcd.print(" MHz");
                }
        
                for (int i = 0; i < 4; i++) {  //For döngüsü kullanarak 
                    Girilen_Frekans[i] = '-';  //Girilen_Frekans değişkeninin içindeki verileri ---- yap
                }
            }          
        }
        delay(250);
    }
}
