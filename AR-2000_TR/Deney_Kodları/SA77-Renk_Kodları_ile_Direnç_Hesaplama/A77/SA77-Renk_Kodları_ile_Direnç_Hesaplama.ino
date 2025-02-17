// SA77 - Renk Kodları ile Direnç Hesaplama

#include <LiquidCrystal_I2C.h>  //I2C LCD kütüphanesini ekle
#include <Keypad.h>             //Keypad kütüphanesini ekle

const byte SATIR = 4;           //Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;           //Tuş takımının kaç sütundan oluştuğunu belirt 

//Satır ve sütundaki tuşların yerini ve sırasını tanımla
char tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[SATIR] = {7, 6, 5, 4}; 
byte sutunPinleri[SUTUN] = {3, 2, 1, 0}; 

//Tuş takımını başlat
Keypad tus_takimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN); 

LiquidCrystal_I2C lcd(0x27, 16, 2);    //1602 LCD ekranı tanımla

uint8_t karakter0[8] = {0x4, 0x4, 0x1F, 0x4, 0x4, 0x0, 0x1F, 0x0};    //üst üste + - karakteri                                    
uint8_t karakter1[8] = {0x0, 0xE, 0x11, 0x11, 0x11, 0xA, 0x1B, 0x0};  //ohm karakteri  

//Direnç bantlarındaki değerlerin kaydedileceği değişkenleri tanımla
int birinci_bant;      //Birinci bandın tutulacağı değişken
int ikinci_bant;       //ikinci bandın tutulacağı değişken
int carpan_degeri;     //çarpan bandının (3. bant) tutulacağı değişken 
int tolerans_degeri;   //tolerans bandının (4. bant) tutulacağı değişken 
float Direnc_Degeri;   //Hesaplanan direnç değerinin tutulacağı değişken

char Basilan_tus;      //Tuş takımından basılan tuşun karakter olarak tutulacağı değişkeni tanımla 
int Basilan;           //Tuş takımından basılan tuşun tamsayı olarak tutulacağı değişkeni tanımla 

int bant = 1;          //switch case yapısında sırasıyla bant değerlerinin girişi için durum değişkenini tanımla 

int buzzerPin = 8;     //Buzzerin bağlandığı pin numarasını tanımla

void setup() {
    pinMode(buzzerPin, OUTPUT);  //Buzzerin bağlandığı pin numarasını tanımla
    lcd.begin();                 //LCD'yi başlat
    lcd.backlight();            //LCD arka ışıklarını aç

    lcd.createChar(0, karakter0);  //üst üste + - karakterini oluştur ve 0. adrese tanımla
    lcd.createChar(1, karakter1);  //ohm karakterini oluştur ve 1. adrese tanımla
  
    lcd.clear();                   //LCD'yi temizle
    lcd.setCursor(0, 0);          //İlk satıra geç 
    lcd.print("TEES ELEKTRONIK");  //TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);          //İkinci satıra geç
    lcd.print("DIRENC HESAPLAMA"); //DIRENC HESAPLAMA yaz        
    delay(2000);                   //2 saniye bekle
}

void loop() {
    //Sırası ile bantlardaki renklerin girilmesini sağlamak için switch case yapısı tanımla
    switch(bant) {
        case 1:  //case 1 durumu (1. bant)
            lcd.clear();              //LCD'yi temizle 
            lcd.setCursor(0, 0);      //LCD'de ilk satıra geç 
            lcd.print("1. Bant Rengi"); //1. Bant Rengi yaz
            lcd.setCursor(0, 1);      //Alt satıra geç 
            
            //1. bant rengini girmesi için sonsuz döngüde veri girene kadar bekle 
            while(1) {     
                Deger_Girisi();           //Girilen Değeri okumak için Deger_Girisi çağır 
                birinci_bant = Basilan;   //Tuş takımından basılan tuşu birinci_bant değişkenine kaydet 
                
                if(Basilan_tus == '#') {  //Eğer tuş takımından # 'e basıldı ise 
                    //Buzzerdan dıt sesi çıkar
                    digitalWrite(buzzerPin, HIGH);
                    delay(50);
                    digitalWrite(buzzerPin, LOW);
                    delay(50);
                    break;                 //Sonsuz döngüyü bitir 
                }
            }
            bant = 2;                     //Bant değişkenini, 2. bant girişi için 2 yap
            break;                        //case 1 durumunu sonlandır
  
        case 2:  //case 2 durumu (2. bant)
            lcd.clear();              //LCD'yi temizle 
            lcd.setCursor(0, 0);      //LCD'de ilk satıra geç 
            lcd.print("2. Bant Rengi"); //2. Bant Rengi yaz
            lcd.setCursor(0, 1);      //Alt satıra geç 
            
            //2. bant rengini girmesi için sonsuz döngüde veri girene kadar bekle 
            while(1) { 
                Deger_Girisi();          //Girilen Değeri okumak için Deger_Girisi çağır 
                ikinci_bant = Basilan;   //Tuş takımından basılan tuşu ikinci_bant değişkenine kaydet 
      
                if(Basilan_tus == '#') { //Eğer tuş takımından # 'e basıldı ise 
                    //Buzzerdan dıt sesi çıkar
                    digitalWrite(buzzerPin, HIGH);
                    delay(50);
                    digitalWrite(buzzerPin, LOW);
                    delay(50);
                    break;               //Sonsuz döngüyü bitir 
                }    
            }
            bant = 3;                   //Bant değişkenini, 3. bant girişi için 3 yap
            break;                      //case 2 durumunu sonlandır
  
        case 3:  //case 3 durumu (3. bant)
            lcd.clear();              //LCD'yi temizle 
            lcd.setCursor(0, 0);      //LCD'de ilk satıra geç 
            lcd.print("Carpan Rengi"); //Carpan Rengi yaz
            lcd.setCursor(0, 1);      //Alt satıra geç 
            
            //3. bant rengini girmesi için sonsuz döngüde veri girene kadar bekle 
            while(1) { 
                Deger_Girisi();            //Girilen Değeri okumak için Deger_Girisi çağır 
                carpan_degeri = Basilan;   //Tuş takımından basılan tuşu carpan_degeri değişkenine kaydet   
      
                if(Basilan_tus == '#') {   //Eğer tuş takımından # 'e basıldı ise 
                    //Buzzerdan dıt sesi çıkar
                    digitalWrite(buzzerPin, HIGH);
                    delay(50);
                    digitalWrite(buzzerPin, LOW);
                    delay(50);
                    break;                 //Sonsuz döngüyü bitir 
                }
            }
            bant = 4;                     //Bant değişkenini, 4. bant girişi için 4 yap
            break;                        //case 3 durumunu sonlandır
  
        case 4:  //case 4 durumu (4. bant)
            lcd.clear();                //LCD'yi temizle 
            lcd.setCursor(0, 0);        //LCD'de ilk satıra geç 
            lcd.print("Tolerans Rengi"); //Tolerans Rengi yaz
            lcd.setCursor(0, 1);        //Alt satıra geç 
            
            //4. bant rengini girmesi için sonsuz döngüde veri girene kadar bekle 
            while(1) { 
                Deger_Girisi();              //Girilen Değeri okumak için Deger_Girisi çağır 
                tolerans_degeri = Basilan;   //Tuş takımından basılan tuşu tolerans_degeri değişkenine kaydet    
                
                if(Basilan_tus == '#') {    //Eğer tuş takımından # 'e basıldı ise 
                    //Buzzerdan dıt dıt sesi çıkar
                    for (int i = 0; i < 2; i++) {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50);
                        digitalWrite(buzzerPin, LOW);
                        delay(50);
                    }
                    break;                   //Sonsuz döngüyü bitir 
                }
            }
            bant = 5;                       //Direnç hesaplama işlemi için bant değişkenini 5 yap   
            break;                          //case 4 durumunu sonlandır
    
        case 5:  //Hesaplama işlemi için 
            //Direnç değerini hesapla
            Direnc_Degeri = (10 * birinci_bant + ikinci_bant) * pow(10, carpan_degeri);
            
            lcd.clear();           //LCD'yi temizle 
            lcd.setCursor(0, 0);   //LCD'de ilk satıra geç 
            lcd.print("Direnc:");  //Direnc: yaz
            
            //Eğer hesaplanan direnç değeri 1000'den büyük ve 1000000'dan küçük ise Kohm yazmak için 
            if(Direnc_Degeri >= 1000 && Direnc_Degeri < 1000000) { 
                Direnc_Degeri = Direnc_Degeri / 1000;  //Hesaplanan direnç değerini 1000'e böl
                lcd.print(Direnc_Degeri);              //LCD ekrana direnç değerini yazdır 
                lcd.print(" k");                       //k yaz 
                lcd.print((char)1);                    //ohm karakterini yaz 
            } 
            //Eğer hesaplanan direnç değeri 1000000'dan büyük ise Mohm yazmak için 
            else if(Direnc_Degeri >= 1000000) { 
                Direnc_Degeri = Direnc_Degeri / 1000000;  //Hesaplanan direnç değerini 1000000'e böl
                lcd.print(Direnc_Degeri);                 //LCD ekrana direnç değerini yazdır 
                lcd.print("M");                           //M yaz 
                lcd.print((char)1);                       //ohm karakterini yaz 
            }
            //Eğer hesaplanan direnç değeri 1000'den küçük ise 
            else {
                lcd.print(Direnc_Degeri);                 //Direnc degerini LCD Ekrana yazdır 
                lcd.print(" ");                           //Bir boşluk bırak 
                lcd.print((char)1);                       //Ohm karakterini yaz 
            }
            
            lcd.setCursor(0, 1);    //LCD Ekranda alt satıra geç 
            lcd.print("Tolerans: "); //Tolerans: yaz 
            
            //Eğer tolerans_degeri 10 ise, yani tuştakımından 'A' tuşuna basıldı ise 
            if(tolerans_degeri == 10) {
                lcd.print((char)0);  //LCD Ekrana üst üste +- yaz
                lcd.print(" %5");    //%5 yaz
            }
            //Eğer tolerans_degeri 11 ise, yani tuştakımından 'B' tuşuna basıldı ise
            if(tolerans_degeri == 11) {
                lcd.print((char)0);  //LCD Ekrana üst üste +- yaz
                lcd.print(" %10");   //%10 yaz
            }  
            
            //Sonsuz döngüye gir 
            while(1) {      
                Deger_Girisi();           //Deger_Girisi() fonksiyonunu çağır 
                if(Basilan_tus == '#') {  //Yeni direnç hesaplaması için #'e basılmasını bekle 
                    break;
                }
            }
            bant = 1;                     //Yeni direnç hesaplaması için bant değişkenini 1 yap
            break;                        //case 5 durumunu bitir 
    }
}

//Keypad'den basılan tuşların algılanması için Deger_Girisi() fonksiyonu
int Deger_Girisi() {
    Basilan_tus = tus_takimi.getKey();  //Keypad'den basılan tuşu Basilan_tus karakterine kaydet
    
    if(Basilan_tus) {  //Eğer tuşa basıldı ise
        if(Basilan_tus == '0') {
            lcd.setCursor(0, 1);
            lcd.print("Siyah        ");
            Basilan = 0;
        }
        else if(Basilan_tus == '1') {
            lcd.setCursor(0, 1);
            lcd.print("Kahverengi   ");
            Basilan = 1;
        }
        else if(Basilan_tus == '2') {
            lcd.setCursor(0, 1);
            lcd.print("Kirmizi      ");
            Basilan = 2;
        }
        else if(Basilan_tus == '3') {
            lcd.setCursor(0, 1);
            lcd.print("Turuncu      ");
            Basilan = 3;
        }
        else if(Basilan_tus == '4') {
            lcd.setCursor(0, 1);
            lcd.print("Sari         ");
            Basilan = 4;
        }
        else if(Basilan_tus == '5') {
            lcd.setCursor(0, 1);
            lcd.print("Yesil        ");
            Basilan = 5;
        }
        else if(Basilan_tus == '6') {
            lcd.setCursor(0, 1);
            lcd.print("Mavi         ");
            Basilan = 6;
        }
        else if(Basilan_tus == '7') {
            lcd.setCursor(0, 1);
            lcd.print("Mor          ");
            Basilan = 7;
        }
        else if(Basilan_tus == '8') {
            lcd.setCursor(0, 1);
            lcd.print("Gri          ");
            Basilan = 8;
        }
        else if(Basilan_tus == '9') {
            lcd.setCursor(0, 1);
            lcd.print("Beyaz        ");
            Basilan = 9;
        }
        else if(Basilan_tus == 'A') {
            lcd.setCursor(0, 1);
            lcd.print("Altin        ");
            Basilan = 10;
        }
        else if(Basilan_tus == 'B') {
            lcd.setCursor(0, 1);
            lcd.print("Gumus        ");
            Basilan = 11;
        }
    }
    else return -1;
}
