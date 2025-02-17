// SA69 - LED matrix tavla zarı

#include "LedControl.h"                                //LED matriks kütüphanesini ekle

int butonPin = 2;                                     //Butonun bağlandığı pini tanımla
int buzzerPin = 8;                                    //Buzzerın bağlandığı pini tanımla
int rastgelesayi;                                     //Rastgele üretilen sayının tutulacağı değişkeni tanımla

LedControl lc = LedControl(7, 5, 6, 1);               //DATAIN 7, CS 5, CLK 6nolu pinlere bağlı olduğunu tanımla 
                                                      //Sondaki 1 matriks sayısını gösterir.

byte alti[8] = {                                      //6 göstermek için kodlar 
    B11011011,
    B11011011,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11011011,
    B11011011
}; 

byte bes[8] = {                                       //5 göstermek için kodlar 
    B11000011,
    B11000011,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B11000011,
    B11000011
};

byte dort[8] = {                                      //4 göstermek için kodlar 
    B11000011,
    B11000011,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000011,
    B11000011
};

byte uc[8] = {                                        //3 göstermek için kodlar 
    B00000011,
    B00000011,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B11000000,
    B11000000
};

byte iki[8] = {                                       //2 göstermek için kodlar 
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000
};

byte bir[8] = {                                       //1 göstermek için kodlar 
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000
};

void setup() {
    pinMode(butonPin, INPUT_PULLUP);                  //Buton bağlandığı pini giriş olarak ayarla
    pinMode(buzzerPin, OUTPUT);                       //Buzzerın bağlandığı pini çıkış olarak ayarla
    
    lc.shutdown(0, false);                            //LED matriksin yanında bulunan entegrenin uyku modundan çıkması için komut  
    lc.setIntensity(0, 8);                           //Parlaklık ayarı 
    lc.clearDisplay(0);                               //Matriksi temizle
}

void loop() { 
    /*Rastgele sayı üretmek için aşağıdaki işlemleri uygula 
      for döngüsü ile rastgelesayi değişkenine sürekli sayı atanacak
      Butona basıldığı zaman i değeri rastgele bir yerde durduğu için 
      rastgelesayi değişkenide rastgele bir sayı olacak*/

    while(1) {                                        //Sonsuz döngüye gir 
        for(int i = 1; i < 7; i++) {                 //i değeri 1 den 7 ye kadar  
            rastgelesayi = i;                        //rastgelesayi değişkenine i değerini ata 
            
            if(digitalRead(butonPin) == LOW)         //Eğer butona basılmışsa
                break;                               //for döngüsünü sonlandır 
        }
        if(digitalRead(butonPin) == LOW)             //Eğer butona basılmışsa
            break;                                    //while döngüsünü sonlandır 
    }

    if(digitalRead(butonPin) == LOW) {               //eğer butona basılmışsa
        for(int gecikme = 100; gecikme <= 300; gecikme = gecikme + 100) {  //Animasyon yapan döngü
            bir1();
            tone(buzzerPin, 100);
            delay(gecikme);
            noTone(buzzerPin);
            
            iki2(); 
            tone(buzzerPin, 200);
            delay(gecikme);
            noTone(buzzerPin);
            
            uc3();
            tone(buzzerPin, 300);
            delay(gecikme);
            noTone(buzzerPin);
            
            dort4();
            tone(buzzerPin, 400);
            delay(gecikme);
            noTone(buzzerPin);
            
            bes5();
            tone(buzzerPin, 500);
            delay(gecikme);
            noTone(buzzerPin);
            
            alti6();
            tone(buzzerPin, 100);
            delay(gecikme);
            noTone(buzzerPin);
        }
    }

    switch(rastgelesayi) {                           //Rastgele üretilen sayıya göre aşağıdaki case'lerden birini seç ve 
                                                     //LED matrikse aktar. Aktarılan sonuç gelen zarı temsil eder. 
        case 1: 
            bir1();
            break;
        case 2: 
            iki2();
            break;
        case 3: 
            uc3();
            break;
        case 4: 
            dort4();
            break;
        case 5: 
            bes5();
            break;
        case 6: 
            alti6();
            break;
    }
} 

void bir1() {  
    lc.setRow(0, 0, bir[0]);
    lc.setRow(0, 1, bir[1]);
    lc.setRow(0, 2, bir[2]);
    lc.setRow(0, 3, bir[3]);
    lc.setRow(0, 4, bir[4]);
    lc.setRow(0, 5, bir[5]);
    lc.setRow(0, 6, bir[6]);
    lc.setRow(0, 7, bir[7]);
}

void iki2() {
    lc.setRow(0, 0, iki[0]);
    lc.setRow(0, 1, iki[1]);
    lc.setRow(0, 2, iki[2]);
    lc.setRow(0, 3, iki[3]);
    lc.setRow(0, 4, iki[4]);
    lc.setRow(0, 5, iki[5]);
    lc.setRow(0, 6, iki[6]);
    lc.setRow(0, 7, iki[7]);
}

void uc3() {
    lc.setRow(0, 0, uc[0]);
    lc.setRow(0, 1, uc[1]);
    lc.setRow(0, 2, uc[2]);
    lc.setRow(0, 3, uc[3]);
    lc.setRow(0, 4, uc[4]);
    lc.setRow(0, 5, uc[5]);
    lc.setRow(0, 6, uc[6]);
    lc.setRow(0, 7, uc[7]);
}

void dort4() {
    lc.setRow(0, 0, dort[0]);
    lc.setRow(0, 1, dort[1]);
    lc.setRow(0, 2, dort[2]);
    lc.setRow(0, 3, dort[3]);
    lc.setRow(0, 4, dort[4]);
    lc.setRow(0, 5, dort[5]);
    lc.setRow(0, 6, dort[6]);
    lc.setRow(0, 7, dort[7]);
}

void bes5() {
    lc.setRow(0, 0, bes[0]);
    lc.setRow(0, 1, bes[1]);
    lc.setRow(0, 2, bes[2]);
    lc.setRow(0, 3, bes[3]);
    lc.setRow(0, 4, bes[4]);
    lc.setRow(0, 5, bes[5]);
    lc.setRow(0, 6, bes[6]);
    lc.setRow(0, 7, bes[7]);
}

void alti6() {
    lc.setRow(0, 0, alti[0]);
    lc.setRow(0, 1, alti[1]);
    lc.setRow(0, 2, alti[2]);
    lc.setRow(0, 3, alti[3]);
    lc.setRow(0, 4, alti[4]);
    lc.setRow(0, 5, alti[5]);
    lc.setRow(0, 6, alti[6]);
    lc.setRow(0, 7, alti[7]);  
}
