// SA89 - Dijital Nostaljik Çevirmeli Telefon

#include <Servo.h>   //Servo motor kütüphanesini ekle
#include <Keypad.h>  //Keypad kütüphanesini ekle

const byte SATIR = 4;  //Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;  //Tuş takımının kaç sütundan oluştuğunu belirt 

//Tuş takımındaki tuşları tanımla 
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
Keypad tusTakimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN); 

Servo servo;           //Servo isimli bir servo motor objesi oluştur

int servoPin = 8;     //Servo motorun bağlandığı pin numarasını tanımla
int hoparlorPin = 10; //Hoparlörün bağlandığı pin numarasını tanımla

void setup() {
    pinMode(hoparlorPin, OUTPUT);  //Hoparlörün bağlandığı pini çıkış olarak ayarla
    servo.attach(servoPin);        //Servo motorun bağlandığı pini ayarla
    servo.write(0);                //Servonun başlangıç pozisyonunu 0 derece olarak ayarla
}

void loop() {
    char tus = tusTakimi.getKey();  //Tuş takımından basılan tuşları kaydet
    
    if (tus != NO_KEY) {            //Eğer tuşa basıldı ise
        switch (tus) {              //switch case yapısı ile hangi tuşa basıldı ise o tuştaki işlemi yap
            case '0':               //case 0 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 600);
                delay(50);
                noTone(hoparlorPin);       
                servo.write(180);          //Eğer girilen değer sıfır ise servoyu 180 dereceye götür      
                for (int i = 180; i >= 0; i--) {  //for döngüsü ile 180 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }  
                break;
                
            case '1':               //case 1 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 650);
                delay(50);
                noTone(hoparlorPin);
                servo.write(18);           //Servoyu 18 dereceye götür        
                for (int i = 18; i >= 0; i--) {   //for döngüsü ile 18 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '2':               //case 2 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 700);
                delay(50);
                noTone(hoparlorPin);
                servo.write(36);           //Servoyu 36 dereceye götür        
                for (int i = 36; i >= 0; i--) {   //for döngüsü ile 36 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '3':               //case 3 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 750);
                delay(50);
                noTone(hoparlorPin);
                servo.write(54);           //Servoyu 54 dereceye götür        
                for (int i = 54; i >= 0; i--) {   //for döngüsü ile 54 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '4':               //case 4 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 800);
                delay(50);
                noTone(hoparlorPin);
                servo.write(72);           //Servoyu 72 dereceye götür        
                for (int i = 72; i >= 0; i--) {   //for döngüsü ile 72 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '5':               //case 5 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 850);
                delay(50);
                noTone(hoparlorPin);
                servo.write(90);           //Servoyu 90 dereceye götür        
                for (int i = 90; i >= 0; i--) {   //for döngüsü ile 90 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '6':               //case 6 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 900);
                delay(50);
                noTone(hoparlorPin);
                servo.write(108);          //Servoyu 108 dereceye götür        
                for (int i = 108; i >= 0; i--) {  //for döngüsü ile 108 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '7':               //case 7 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 950);
                delay(50);
                noTone(hoparlorPin);
                servo.write(126);          //Servoyu 126 dereceye götür        
                for (int i = 126; i >= 0; i--) {  //for döngüsü ile 126 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '8':               //case 8 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 1000);
                delay(50);
                noTone(hoparlorPin);        
                servo.write(144);          //Servoyu 144 dereceye götür        
                for (int i = 144; i >= 0; i--) {  //for döngüsü ile 144 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
                
            case '9':               //case 9 durumunda aşağıdaki işlemleri yap
                tone(hoparlorPin, 1050);
                delay(50);
                noTone(hoparlorPin);
                servo.write(162);          //Servoyu 162 dereceye götür        
                for (int i = 162; i >= 0; i--) {  //for döngüsü ile 162 dereceden sıfır dereceye kadar
                    servo.write(i);        //Servo motoru hareket ettir
                    delay(10);             //Hareket işlemini 10 ms aralıklar ile yap
                }
                break;
        }
    }
}
