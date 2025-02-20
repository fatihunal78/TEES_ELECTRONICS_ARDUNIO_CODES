// SA66 - Uzaktan kumanda ile motor kontrolü

//IR alıcı kütüphanesini ekle
#include <IRremote.h>

//Kumanda kodlarını tanımla
#define birtusu     0xFFA25D    //Kumanda 1 tuşu 
#define ikitusu     0xFF629D    //Kumanda 2 tuşu 
#define uctusu      0xFFE21D    //Kumanda 3 tuşu 
#define dorttusu    0xFF22DD    //Kumanda 4 tuşu 
#define bestusu     0xFF02FD    //Kumanda 5 tuşu 
#define altitusu    0xFFC23D    //Kumanda 6 tuşu 
#define yeditusu    0xFFE01F    //Kumanda 7 tuşu 
#define sekiztusu   0xFFA857    //Kumanda 8 tuşu 
#define dokuztusu   0xE5CFBD7F  //Kumanda 9 tuşu 
#define yildiztusu  0xFF6897    //Kumanda * tuşu 
#define sifirtusu   0xFF9867    //Kumanda 0 tuşu 
#define karetusu    0xFFB04F    //Kumanda # tuşu 
#define yukaritusu  0xFF18E7    //Kumanda yukarı yön tuşu 
#define asagitusu   0xFF4AB5    //Kumanda aşağı yön tuşu 
#define sagtusu     0xFF5AA5    //Kumanda sağ ok tuşu
#define soltusu     0xFF10EF    //Kumanda sol ok tuşu
#define OKtusu      0xFF38C7    //Kumanda ok tuşu
#define tekrar      0xFFFFFFFF  //Basılan tuşa sürekli basılırsa

//LM293 un INPUT2 (7.bacağı) nın Arduino'ya bağlandığı pin numarasını tanımla
//Arduino 10. pinden LM293D entegresinin 7. bacağına bağlı pin yardımı ile motor saat yönünün tersinde 
//dönecektir 
int MotorPwm1 = 10;  

//LM293 un INPUT1 (2.bacağı) nın Arduino'ya bağlandığı pin numarasını tanımla
//Arduino 9. pinden LM293D entegresinin 2. bacağına bağlı pin yardımı ile motor saat yönünde dönecektir  
int MotorPwm2 = 9;   

//Motorun hangi yöne döndüğünü tutacak değişken
//Eğer değer 0 ise saat yönünün tersi
//Eğer değer 1 ise saat yönünde dönecek
int motoryonu = 0;   

int irPin = 2;       //IR alıcı sinyal ucunun bağlandığı pini tanımla
int motor_hizi = 0;  //Motorun hızının tutulacağı değişkeni tanımla

IRrecv iralici(irPin);     //iralici adında bir IR alıcı tanımla
decode_results sonuc;       //IR alıcıdan alınan değerlerin tutulacağı değişkeni tanımla

void setup() {
    iralici.enableIRIn();       //IR alıcıyı başlat
    pinMode(MotorPwm1, OUTPUT); //LM293un INPUT2(7.bacağının) bağlandığı pini çıkış olarak ayarla 
    pinMode(MotorPwm2, OUTPUT); //LM293un INPUT1(2.bacağının) bağlandığı pini çıkış olarak ayarla 
}

void loop() {
    if (iralici.decode(&sonuc)) {          //IR alıcıdan bir bilgi gelip gelmediğini kontrol et
        iralici.resume();                   //IR alıcıyı diğer değerleri alabilmesi için sıfırla 
    }   

    if (sonuc.value == sagtusu) {          //Eğer kumandadan sağ tuşuna basıldı ise     
        analogWrite(MotorPwm1, 255);        //Motoru maksimum hızda saat yönünde döndür 
        analogWrite(MotorPwm2, 0);          //LM293D entegresinin bağlı olduğu diğer PWM çıkışını LOW'a çek
        motoryonu = 1;                      //motoryonu değişkenini 1 yap, saat yönünde döndüğünü kaydet
        motor_hizi = 255;                   //motor_hizi değişkeninin değerini 255 yap, maksimum hız
    }    
    else if (sonuc.value == soltusu) {     //Eğer kumandadan sol tuşuna basıldı ise 
        analogWrite(MotorPwm2, 255);        //Motoru maksimum hızda saat yönünün tersine çevir
        analogWrite(MotorPwm1, 0);          //LM293D entegresinin bağlı olduğu diğer PWM çıkışını LOW'a çek
        motoryonu = 0;                      //motoryonu değişkenini 0 yap, saat yönünün tersine döndüğünü kaydet
        motor_hizi = 255;                   //motor_hizi değişkeninin değerini 255 yap, maksimum hız
    }
    else if (sonuc.value == OKtusu) {      //Eğer kumandadan OK tuşuna basıldı ise 
        analogWrite(MotorPwm1, 0);          //PWM çıkışını LOW yap 
        analogWrite(MotorPwm2, 0);          //PWM çıkışını LOW yap    
        motor_hizi = 0;                     //motor_hizi değişkeninin değerini 0 yap
        motoryonu = 0;                      //motoryonu değişkeninin değerini 0 yap
    }
    else if (sonuc.value == asagitusu && motoryonu == 1) {  
        //Eğer kumandadan aşağı tuşuna basılmış ve motoryonu değeri 1 yani motor saat yönünde 
        //dönüyor ise. Bu koşullarda motorun hızı maksimumdadır(255)
        motor_hizi = motor_hizi - 50;       //Motorun hızını 255 değerinden 50'şer azaltarak git
        if (motor_hizi <= 0) motor_hizi = 0;//Eğer motor_hizi 0'dan küçük ise değeri sıfırda sabit tut
        analogWrite(MotorPwm1, motor_hizi); //Entegreye bağlı MotorPwm1 çıkışını motor_hizi kadar döndür
        analogWrite(MotorPwm2, 0);          //Diğer PWM çıkışını LOW yap
        sonuc.value = NULL;                 //sonuc.value değişkenini NULL yap
    } 
    else if (sonuc.value == asagitusu && motoryonu == 0) {  
        //Eğer kumandadan aşağı tuşuna basılmış ve motoryonu değeri 0 yani motor saat yönünün tersine 
        //dönüyor ise. Bu koşullarda motorun hızı maksimumda(255)
        motor_hizi = motor_hizi - 50;       //Motorun hızını 255 değerinden 50'şer azaltarak git
        if (motor_hizi <= 0) motor_hizi = 0;//Eğer motor_hizi 0'dan küçük ise değeri sıfırda sabit tut
        analogWrite(MotorPwm2, motor_hizi); //Entegreye bağlı MotorPwm2 çıkışını motor_hizi kadar döndür
        analogWrite(MotorPwm1, 0);          //Diğer PWM çıkışını LOW yap
        sonuc.value = NULL;                 //sonuc.value değişkenini NULL yap
    }
    else if (sonuc.value == yukaritusu && motoryonu == 1) { 
        //Eğer kumandadan yukarı tuşuna basılmış ve motoryonu değeri 1 yani motor saat yönünde 
        //dönüyor ise. Bu koşullarda motorun hızı sıfırda
        motor_hizi = motor_hizi + 50;       //Motor hızını sıfırdan 50'şer arttır
        if (motor_hizi >= 255) motor_hizi = 255; //Eğer motor_hizi değişkeni 255'den büyük ise 255'de sabit tut
        analogWrite(MotorPwm1, motor_hizi); //Entegreye bağlı MotorPwm1 çıkışını motor_hizi kadar döndür
        analogWrite(MotorPwm2, 0);          //Diğer PWM çıkışını LOW yap
        sonuc.value = NULL;                 //sonuc.value değişkenini NULL yap
    }
    else if (sonuc.value == yukaritusu && motoryonu == 0) { 
        //Eğer kumandadan yukarı tuşuna basılmış ve motoryonu değeri 0 yani motor saat yönünün tersine 
        //dönüyor ise. Bu koşullarda motorun hızı sıfırda
        motor_hizi = motor_hizi + 50;       //Motor hızını sıfırdan 50'şer arttır
        if (motor_hizi >= 255) motor_hizi = 255; //Eğer motor_hizi değişkeni 255'den büyük ise 255'de sabit tut
        analogWrite(MotorPwm2, motor_hizi); //Entegreye bağlı MotorPwm2 çıkışını motor_hizi kadar döndür
        analogWrite(MotorPwm1, 0);          //Diğer PWM çıkışını LOW yap
        sonuc.value = NULL;                 //sonuc.value değişkenini NULL yap
    }
    
    delay(200);                             //200ms bekle
}
