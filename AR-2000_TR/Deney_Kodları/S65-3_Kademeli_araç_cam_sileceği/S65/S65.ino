// S65 - 3 Kademeli araç cam sileceği

#include <Servo.h>                                    //Servo motor kütüphanesini ekle

Servo servomotor;                                     //Servo motoru kontrol etmek için servomotor isimli obje oluştur

int butonPin = 2;                                    //Butonun bağlandığı pin numarasını tanımla
int butonDurumu = 0;                                 //Butonun kaç defa basıldığını tutacak değişken tanımla ve ilk değer sıfıra eşitle
int i = 0;                                           //for döngülerinde kullanılan başlangıç değerini tanımla
int silecek_hizi = 65;                              //Sileceğin hareket hızını ayarlayacak değişkeni tanımla ve ilk değerini 65 yap
  
void setup() {
    servomotor.attach(5);                           //Servo motorun bağlandığı pini ayarla
    pinMode(butonPin, INPUT);                       //Butonun bağlandığı pini giriş olarak ayarla

    attachInterrupt(digitalPinToInterrupt(butonPin),//Butonun bağlandığı pini İnterrupt (kesme) olarak ayarla
                   butonKontrol,                    //Butona basıldığında butonKontrol fonksiyonundaki işlemi yap
                   RISING);                         //RISING(Yükselen kenar) da tetikleme yap
}

void loop() {
    while(1) {                                      //Sonsuz döngüye gir 
        if (butonDurumu == 0) {                    //Eğer butonDurumu sıfır değerine eşit ise 
            servomotor.write(0);                    //Servo motoru sıfır derece konumuna al 
            break;                                  //Sonsuz döngüyü bitir 
        } else {                                    //Eğer butonDurumu sıfırdan farklı ise 
            for(i = 0; i < 180; i++) {             //Servo motorun 180 derecelik hareketi için for döngüsü kullan
                                                   //0 dereceden 180 dereceye doğru hareket et
                servomotor.write(i);                //Servo motoru i değişkenine göre hareket ettir
                delay(silecek_hizi);                //silecek_hizi değişkenindeki gecikme ile servoyu hareket ettir
            }
            
            for(i = 180; i > 0; i--) {             //Servo motorun 180 derecelik hareketi için for döngüsü kullan
                                                   //180 dereceden 0 dereceye doğru hareket et
                servomotor.write(i);                //servo motoru i değişkenine göre hareket ettir
                delay(silecek_hizi);                //silecek_hizi değişkenindeki gecikme ile servoyu hareket ettir
            }  
        }    
    }     
    silecek_hizi = 65;                             //silecek_hizi değişkenini 65 yap      
}

void butonKontrol() {                              //Butonun basılıp basılmadığını kontrol etmek için butonKontrol fonksiyonu oluştur
                                                   //Bu fonksiyon ile for döngülerinin içinde butona basılıp basılmadığını kontrol edilecek
    static unsigned long son_kesme_zamani = 0;     //son_kesme_zamani isimli değişken oluştur ve ilk değerini 0 yap
    unsigned long kesme_zamani = millis();         //kesme_zamani isimli bir değişken oluştur ve millis() komutu ile sistemin 
                                                   //başlangıç zamanını ata
    
    if (kesme_zamani - son_kesme_zamani > 500) {  //Eğer kesme_zamani ile son_kesme_zamani arasındaki fark 500ms 'den büyük ise
                                                   //Bu işlem butona birden fazla kez basıldığını algılamayı önlemek amaçlı kullanılmıştır.
        butonDurumu++;                             //butonDurumu değişkenini bir arttır.
                                                   //Butona basılma sayısına göre silecek_hizi değişkeninin değerini değiştir
        if (butonDurumu == 1) silecek_hizi = 35;
        if (butonDurumu == 2) silecek_hizi = 13;
        if (butonDurumu == 3) silecek_hizi = 6;
    
        if(silecek_hizi < 0) {                     //Eğer silecek_hizi değişkeni 0 dan küçük ise
            silecek_hizi = 0;                      //silecek_hizi değişkenini sıfır yap
        }
  
        if(butonDurumu > 3) {                      //Eğer butonDurumu değişkeni 3'den büyük ise 
            butonDurumu = 0;                       //butonDurumu değişkenini sıfıra eşitle
            silecek_hizi = 6;                      //silecek_hizi değişkenini 6 yap
        }   
    }
    son_kesme_zamani = kesme_zamani;               //son_kesme_zamani değişkenine kesme_zamani değişkenindeki değeri ata
}
