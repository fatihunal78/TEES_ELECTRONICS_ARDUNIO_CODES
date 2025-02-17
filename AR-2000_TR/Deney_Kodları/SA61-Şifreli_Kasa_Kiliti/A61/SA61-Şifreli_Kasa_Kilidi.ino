// SA61 - Şifreli Kasa Kilidi

#include <Servo.h>            //Servo motor kütüphanesi eklendi
#include <LiquidCrystal_I2C.h>//I2C LCD kütüphanesini ekle
#include <Keypad.h>           //Keypad kütüphanesi eklendi

//Kullandığımız keypadde kaç satır ve sütun olduğunu belirtmemiz gerekir
//Panel üzerindeki keypad 4x4 yani 4 satır 4 sütun mevcuttur
const byte SATIR = 4;
const byte SUTUN = 4;
int buzzerPin = 4;            //Buzzerin bağlandığı pin numarasını tanımla

//Satır ve sütundaki tuşların yerini ve sırasını tanımla 
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
Keypad tusTakimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);

LiquidCrystal_I2C lcd(0x27, 16, 2);    //1602 LCD ekranı tanımla
Servo servo;                            //servo isimli bir servo motor objesi oluşturduk 
int kilit = HIGH;

/*string(dizi) birden fazla karakteri hafızada tutmaya yarayan bir değişken tipidir. 
  String parçalama, birleştrime, istenilen harfi bulma/silme/değiştirme gibi özellikler sıkça 
  kullanılmaktadır.*/

String girilensifre = "";               //Girilen şifrenin tutulacağı değişkeni tanımla
String sifre = "1234";                  //Başlangıç şifresinin tutulacağı değişkeni tanımla ve 1234 yap
int Servo_pozisyon;                     //Servo motor pozisyonunun tutulacağı değişkeni tanımla

int butonPin = 2;                       //Butonun bağlandığı pin numarasını tanımla
int servoPin = 3;                       //servo motorun bağlandığı pin numarasını tanımla

void setup() { 
    servo.attach(servoPin);             //Servo motorun bağlandığı pini ayarla
    servo.write(0);                     //Servo motorun baslangıç pozisyonunu sıfır derece olarak ayarla
    pinMode(butonPin, INPUT_PULLUP);    //Butonun bağlandığı pini giriş olarak ayarla
    pinMode(buzzerPin, OUTPUT);         //Buzzerin bağlandığı pini çıkış olarak ayarla
    
    lcd.begin();                        //LCD'yi başlat
    lcd.backlight();                    //LCD arka ışıklarını aç
    lcd.clear();                        //LCD'yi temizle
    lcd.setCursor(0, 0);               //İlk satıra geç 
    lcd.print("TEES ELEKTRONIK");      //TEES ELEKTRONIK yaz     
    lcd.setCursor(0, 1);               //Alt satıra geç
    lcd.print("Kasa Kilit Proje");
    delay(2000);                       //2 saniye bekle
    
    lcd.clear();                       //LCD'yi temizle
    lcd.setCursor(0, 0);               //İlk satıra geç 
    lcd.print("Sifreyi Giriniz");      //LCD'ye Sifreyi Giriniz yaz 
    delay(1000);                       //1 saniye bekle
    lcd.clear();                       //LCD'yi temizle 
}

void loop() {   
    char tus = tusTakimi.getKey();     //Keypad'den basılan değerleri tus değişkenine kaydet 
    
    if (tus != NO_KEY) {               //Eğer bir tuşa basıldı ise 
        switch(tus) {                  //Switch case yapısı tanımla ve tus değişkenine göre case'lere git
            case '*':                   //Eğer yıldıza basıldı ise
                lcd.clear();            //LCD'yi temizle 
                girilensifre = "";      //Girilen şifreleri Sıfırla
                
                if (Servo_pozisyon == 0) {     //Eğer servo_pozisyonu 0 ise yani kilitli ise
                    servo.write(0);            //servoyu 0 derecede tut 
                } else {                       //Eğer servo pozisyonu 0 dan farklı ise 
                    for (Servo_pozisyon = 90; Servo_pozisyon >= 0; Servo_pozisyon--) {
                        servo.write(Servo_pozisyon);  //Servoyu 0 derece konumuna birer adım azaltarak getir
                        delay(10);
                    }
                    Servo_pozisyon = 0;        //Servo pozisyonunu 0 derece olarak ayarla 
                }
                
                digitalWrite(buzzerPin, HIGH);
                delay(50);
                digitalWrite(buzzerPin, LOW);
                delay(50);
                
                lcd.setCursor(0, 0);           //İlk satıra geç
                lcd.print("Kasa Kilitlendi");  //LCD'ye Kasa Kilitlendi yaz
                delay(1000);                   //1 saniye bekle 
                lcd.clear();                   //LCD'yi temizle
                kilit = HIGH;                  //kilit değişkenini HIGH yap 
                break;
                
            case 'A':                         //Eğer A'ya basıldı ise 
                if (!kilit) {                 //Eğer kasa kilitli değil ise
                    lcd.setCursor(0, 1);      //Alt Satıra geç
                    for (int i = 0; i < 2; i++) {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50);
                        digitalWrite(buzzerPin, LOW);
                        delay(50);
                    }
                    lcd.print("Sifre Degisti!");    //Ekrana Sifre Degisti! yazdır
                    sifre = girilensifre;           //sifre değişkenini girilensifre değişkenine eşitle 
                } else {                            //Eğer kasa kilitli ise 
                    lcd.print("Sifre Degistirmek"); //Ekrana Sifre Degistirmek icin Kilidi Acin yaz
                    lcd.setCursor(0, 1);
                    lcd.print("icin Kilidi Acin");
                }
                girilensifre = "";                  //Şifreyi sıfırla 
                delay(1000);                        //1 saniye bekle 
                lcd.clear();                        //LCD'yi temizle 
                break;
                
            case '#':                              //Eğer #'e basıldı ise 
                if (girilensifre == sifre) {       //Eğer girilensifre sifre değişkeni ile sifre aynı ise 
                    lcd.clear();                   //LCD'yi temizle             
                    lcd.print("Kilit Acildi");     //Ekrana Kilit Acildi Yaz
                    
                    for (int i = 0; i < 2; i++) {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50);
                        digitalWrite(buzzerPin, LOW);
                        delay(50);
                    }
                    
                    delay(1000);                   //1 saniye bekle  
                    lcd.clear();                   //LCD'yi temizle 
                    lcd.setCursor(0, 0);           //İlk satıra geç                     
                    lcd.print("Acmak icin PB2");   //LCD Ekrana Acmak icin PB2 yaz
                    lcd.setCursor(0, 1);           //Alt satıra    
                    lcd.print("Butonuna Basin");   //Butona Basin yaz
                    delay(1500);                   //1,5 saniye bekle
                    kilit = LOW;                   //kilit değişkenini LOW yap 
                } else {                           //Eğer girilensifre değişkeni sifre değişkenine eşit değilse
                    lcd.setCursor(0, 0);           //Üst satıra geç
                    lcd.print("Yanlis Sifre");     //LCD'ye Yanlis Sifre yaz
                    lcd.setCursor(0, 1);           //Alt satıra geç
                    lcd.print("Tekrar Deneyin");   //LCD'ye Tekrar Deneyin yazdır
                }
                delay(1000);                       //1 saniye bekle 
                girilensifre = "";                 //Şifreyi temizle 
                break;
                
            default:                               //Eğer hiçbir case durumuna girmemişse default durumunda kalır
                lcd.print(tus);                    //LCD ekrana girilen tuşları yaz
                girilensifre += tus;               //Girilen tuşları ardarda yaz
                break;
        }
    }
    
    if (digitalRead(butonPin) == LOW && kilit == LOW) {  //Eğer butona basıldı ise ve kilit açık ise   
        if (Servo_pozisyon == 90) {                      //Eğer servo pozisyon 90 derece ise 
            servo.write(90);                             //servoyu 90 derece konumunda tut 
        } else {                                         //eğer servo 90 derece konumunda değilse
            for (Servo_pozisyon = 0; Servo_pozisyon <= 90; Servo_pozisyon++) {  //Servoyu 0 dan 90 dereceye getir
                servo.write(Servo_pozisyon);             //Servoyu aç
                delay(10);
            }
            Servo_pozisyon = 90;                         //Servo_pozisyon değişkenini 90 dereceye ayarla               
            lcd.clear();                                 //LCD'yi temizle 
            lcd.setCursor(0, 0);                         //LCD'yi üst satıra getir 
            lcd.print("Kasa Acildi");                    //Ekrana Kasa Acildi yaz 
            lcd.setCursor(0, 1);                         //LCD ekranda alt satıra geç
        }
    }
}
