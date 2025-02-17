// S77 - Kapasitif Dokunmatik anahtar

//Kapasitif dokunma kütüphanesini ekle
#include <CapacitiveSensor.h>

int ledPin = 2;     //LED'in bağlandığı pin numarasını tanımla
int ledDurumu = 0;  //LED'in durumunun tutulacağı değişkeni tanımla
long olcumDegeri;   //Dokunmatik sensördeki değerin kaydedileceği olcumDegeri değişkenini tanımla

//Kapasitif dokunma alıcı ve verici pinlerini tanımla
CapacitiveSensor dokunmatik = CapacitiveSensor(3, 4);
   
void setup() {
    dokunmatik.set_CS_AutocaL_Millis(0xF);  //Otomatik kalibrasyonu kapat
    pinMode(ledPin, OUTPUT);                 //LED'in bağlandığı pini çıkış olarak ayarla
}

void loop() {
    //Sensör hassasiyetini ayarla ve ölçümü olcumDegeri değişkenine kaydet
    olcumDegeri = dokunmatik.capacitiveSensor(3000);
  
    if (olcumDegeri > 2000) {               //Ölçüm değeri 2000'den büyük ise
        ledDurumu++;                        //ledDurumu değişkenini bir arttır
        
        if (ledDurumu > 1) {
            ledDurumu = 0;                  //Eğer ledDurumu değişkeni 1'den büyük ise, ledDurumu değişkenini sıfıra eşitle
        }
    
        if (ledDurumu == 0) {              //Eğer ledDurumu değişkeni sıfır ise
            digitalWrite(ledPin, HIGH);     //LED'i yak
        }
        if (ledDurumu == 1) {              //Eğer ledDurumu değişkeni bir ise
            digitalWrite(ledPin, LOW);      //LED'i söndür
        }
    }

    if (olcumDegeri <= 2000) {             //Ölçüm değeri 2000'e eşit ya da küçük ise
        if (ledDurumu == 0) {              //Eğer ledDurumu değişkeni sıfır ise
            digitalWrite(ledPin, LOW);      //LED'i söndür
        }
        if (ledDurumu == 1) {              //Eğer ledDurumu değişkeni bir ise
            digitalWrite(ledPin, HIGH);     //LED'i yak
        }
    }
    
    delay(100);                            //100 ms bekle
}
