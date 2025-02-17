// SA103 - Hız Göstergesi

#include <LiquidCrystal_I2C.h>    //I2C LCD kütüphanesini ekle 
#include <Servo.h>                 //Servo motor kütüphanesini ekle

LiquidCrystal_I2C lcd(0x27, 16, 2);    //1602 LCD ekran tanımla
Servo servo;                            //Servo motor kontrol etmek için servo objesi ekle

const byte Pervane_kanatlari = 3;       //Panel üzerindeki pervanede kaç kanat, kaç bıcak olduğunu belirten değer
                                       //Bizim pervanemiz 3 bıcaklık olduğu için her bir dönüşte 3 pulse okumaktadır.

const unsigned long ZeroDebouncing = 100000;    //Hassasiyet için ZeroDebouncing değişkeni oluşturuldu ve ilk değeri 100000 yapıldı
const byte okuma_sayisi = 3;  

volatile unsigned long Son_Zaman;                              //Değerlerin hesaplanabilmesi icin pulse'in okunduğu son zamanın tutulacağı değişkeni tanımla
volatile unsigned long Pulse_Arasi_Periyot = ZeroDebouncing+1000;    //Her bir okunan pulse arasındaki periyot için değişkeni tanımla
volatile unsigned long Ortalama_Periyot = ZeroDebouncing+1000;       //PULSE'ler arası ortalama periyotun mikro saniye cinsinden tutulacağı değişkeni tanımla

unsigned long Frekans_Ondalik;      //Frekansın ondalıklı olarak tutulacağı değişkeni tanımla
unsigned long Frekans_tamsayi;      //Frekansın tamsayı olarak tutulacağı değişkeni tanımla
unsigned long RPM;                  //Hesaplanan RPM'in tutulacağı değişkeni tanımla 
unsigned int PulseSayac = 1;        //Okunan pulse'ların tutulacağı değişken, tanımla, ilk değeri 1'e eşitle

unsigned long Toplam_Periyot;       //Ortalama periyotların toplamının tutulacağı değişkeni tanımla 
unsigned long Son_Zaman_Olcum = Son_Zaman;    //Son zamanın olculup tutulacağı değişkeni tanımla
unsigned long Anlik_Zaman = micros();         //Anlık zamanın tutulacağı değişkeni tanımla

unsigned int Okuma_Miktari = 1;
unsigned int ZeroDebouncingExtra; 
unsigned long yenizaman;
unsigned long eskizaman;

unsigned long Okuma[okuma_sayisi];    //Okunan değerlerin array olarak tutulması için dizi değişkenini tanımla
unsigned long Okuma_indeks;           //Kaç okuma yapıldığı anlamak için değişkeni tanımla
unsigned long toplam;                 //Toplam okumaların tutulacağı değişkeni tanımla
unsigned long ortalama;               //Toplam okumaların ortalamasının (RPM ortalamasının) tutulacağı değişkeni tanımla
unsigned long kmh;                    //Dakikadaki devir sayısını saatdeki kilometre (kilometre/saat)'e çevrilmiş halinin tutulacağı değişkeni tanımla

int motorPin = 6;     //Motorun bağlandığı pin numarasını tanımla
int potPin = A0;      //Motoru kontrol edecek potansiyometrenin bağlandığı değişkeni tanımla
int servoPin = 8;     //Servo motorun bağlandığı pin numarasını tanımla
int potDegeri = 0;    //Potansiyometreden okunacak değerlerin kaydedileceği değişkeni tanımla

void setup() 
{
    lcd.begin();          //LCD'yi başlat
    lcd.backlight();      //LCD arka ışıklarını aç
    lcd.clear();          //LCD'yi temizle

    servo.attach(servoPin);    //Servo motorun bağlandığı pini ayarla
    pinMode(motorPin, OUTPUT); //Motorun bağlandığı pini çıkış olarak ayarla
    Serial.begin(9600);        //Seri haberleşmeyi başlat
    
    attachInterrupt(digitalPinToInterrupt(2), Kesme_Fonksiyonu, RISING);    //2 nolu dijital pinden kesme okumak için
                                                                            //Kesme_Fonksiyonu içindeki olayları yükselen kenar(RISING) olduğu zaman gerçekleştir
    
    lcd.setCursor(0, 0);              //Kursoru (İmleci) ilk satıra getir 
    lcd.print("TEES ELEKTRONIK");      //İlk satıra TEES ELEKTRONIK yaz
    lcd.setCursor(0, 1);              //İkinci satıra geç
    lcd.print(" HIZ GOSTERGESI  ");    //HIZ GOSTERGESI yaz
    delay(2000);                       //2 saniye bekle
    lcd.clear();                       //LCD'yi temizle 
    servo.write(180);                  //Başlangıçta servo motoru 180 derece konumuna al
}

void loop()  
{   
    //Motorun maksimum hızda dönmemesi için PWM değeri 100 ile sınırlandırıldı
    potDegeri = map(analogRead(potPin), 0, 1023, 0, 100);    //Analog pinden okunan değerleri 0 ile 100 arasında oranla ve potDegeri'ne kaydet
    analogWrite(motorPin, potDegeri);                         //Oranlanmış olan 0 ile 100 arasındaki değerleri motora gönder

    Son_Zaman_Olcum = Son_Zaman;    //Son_Zaman değişkenindeki değeri Son_Zaman_Olcum değişkenine kaydet 
    Anlik_Zaman = micros();         //Anlık zamanı mikrosaniye cinsinden oku ve Anlik_Zaman değişkenine kaydet

    if(Anlik_Zaman < Son_Zaman_Olcum)    //Eğer okunan Anlik_Zaman, Son_Zaman_Olcum değişkeninden küçük ise 
    {
        Son_Zaman_Olcum = Anlik_Zaman;    //Son_Zaman_Olcum değişkenine anlık zamanı kaydet 
    }
  
    Frekans_Ondalik = 10000000000 / Ortalama_Periyot;    //Pulse'lar arasındaki zamanı ondalık olarak Frekans_Ondalik değişkenine kaydet 

    //Eğer motor dönmeyi durdurduysa veya çok yavaş dönüyorsa, okunan frekans değerini 0 olarak kaydet
    if(Pulse_Arasi_Periyot > ZeroDebouncing - ZeroDebouncingExtra || 
       Anlik_Zaman - Son_Zaman_Olcum > ZeroDebouncing - ZeroDebouncingExtra)
    {  
        Frekans_Ondalik = 0;        //Frekans_Ondalik değişkenini 0 yap
        ZeroDebouncingExtra = 2000; 
    }
    else
    {
        ZeroDebouncingExtra = 0;  
    }
    
    Frekans_tamsayi = Frekans_Ondalik / 10000;    //Hesaplanan Frekans_Ondalik değişkenini tam sayıya çevir ve Frekans_tamsayi değişkenine kaydet

    //RPM (Dakikadaki Devir)'i hesapla
    RPM = Frekans_Ondalik / Pervane_kanatlari * 60;    //Deviri hesaplamak için Frekans_Ondalik değişkenindeki değeri Pervane_kanatlari ile böl
                                                       //çünkü 3 pulse okumasını istemiyor. Pervane_kanatlari değişkenine bölmezsek 
                                                       //dakikadaki devir sayısı 3 katı çıkar. 1 dakikadaki değerini bulmak için 60 ile çarp
                                                       //(1 dakika = 60 saniye)
    RPM = RPM / 10000;    //Tam sayıya çevirmek ve mikro saniye cinsinden olan RPM değişkenini saniye'ye çevirmek için 10000'e böl 

    toplam = toplam - Okuma[Okuma_indeks]; 
    Okuma[Okuma_indeks] = RPM;  
    toplam = toplam + Okuma[Okuma_indeks];  
    Okuma_indeks = Okuma_indeks + 1;  

    if (Okuma_indeks >= okuma_sayisi)    //Eğer array'in sonuna gelindiyse 
    {
        Okuma_indeks = 0;                //Okuma_indeks değişkenini sıfırla 
    }
  
    ortalama = toplam / okuma_sayisi;    //Ortalama değeri hesapla
    kmh = ortalama * 0.001885 * 9;       //RPM değerini KMh (kilometre/saat)'e çevir
                                         //RPM'i yani kilometredeki tur sayısını Kmh(saatte kilometre) cinsine çevirmek için
                                         //RPM*Tekerin Çapı*km/hr formülünü kullan. Burada RPM değişkeni ortalama değişkeni ile aynı
                                         //Tekerin çapı yani motorun üzerindeki diskin çapı 9 cm (santimetre)
                                         //km/hr ise 0.001885 yani 3600/1000000 1 saatte 3600 dakika var ve 1000000mm 1 km eder.
    yenizaman = millis();

    if(yenizaman - eskizaman > 1000)
    {
        int harita = map(kmh, 0, 20, 180, 0);    //Hesaplanan kmh değişkeninen okunan 0 ile 20 arasındaki değeri 180 ile 0 derece arasında oranla 
        servo.write(harita);                      //Oranlanmış harita değişkenindeki değeri servo motora aktar.
  
        lcd.clear();                //LCD'yi temizle 
        lcd.setCursor(0, 0);        //İlk satıra geç
        lcd.print("HIZ:  ");        //HIZ yaz
        lcd.print(kmh);             //Ortalama değişkeninde tutulan Ortalama RPM değerini yaz
        lcd.print(" KM/h");         //KM/h yaz
        eskizaman = yenizaman;
    }
    delay(200);
}  

void Kesme_Fonksiyonu()    //Pulse'ları okuyabilmek için kesme fonksiyonu tanımla
{
    Pulse_Arasi_Periyot = micros() - Son_Zaman; 
    Son_Zaman = micros();    //Son_Zaman değişkenine mikro saniye cinsinden zamanı kaydet 

    if(PulseSayac >= Okuma_Miktari)    //Eğer PulseSayac değişkeni Okuma_Miktari değişkeninden büyük ise 
    {
        Ortalama_Periyot = Toplam_Periyot / Okuma_Miktari;    //Ortalama periyotu bulmak için Toplam_Periyot değişkenini Okuma_Miktari değişkenine böl
        
        PulseSayac = 1;                        //Okunan pulse'ları sayan PulseSayac değişkenini 1'e eşitle 
        Toplam_Periyot = Pulse_Arasi_Periyot;  //Yeni ortalama alabilmek için Toplam_Periyot değişkenini Pulse_Arasi_Periyot değişkenine eşitle

        int oranla = map(Pulse_Arasi_Periyot, 40000, 5000, 1, 10);    //Pulse_Arasi_Periyot değişkeninden okunan 40000 ile 5000 arası değeri
                                                                       //1 ile 10 arasında oranla
        
        oranla = constrain(oranla, 1, 10);    //oranla değişkenini sınırlamak için
                                              //Eğer oranla değişkeni 1 ile 10 arasında ise oranla değişkenini değeri aynı kalsın
                                              //Eğer oranla değişkeni 1'den küçük ise oranla değişkenini değerini 1 yap
                                              //Eğer oranla değişkeni 10'dan büyük ise oranla değişkenini değerini 10 yap
        Okuma_Miktari = oranla;               //oranla değişkenindeki değeri Okuma_Miktari değişkenine kaydet
    }
    else
    {
        PulseSayac++;                                         //Pulse sayac değişkenini bir arttır 
        Toplam_Periyot = Toplam_Periyot + Pulse_Arasi_Periyot;    //Toplam_Periyot değişkenini önceki değeri ile Pulse_Arasi_Periyot topla
    }
}  
