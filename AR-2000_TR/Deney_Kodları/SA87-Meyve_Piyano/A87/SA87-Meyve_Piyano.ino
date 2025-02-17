// SA87 - Meyve Piyano

#include <CapacitiveSensor.h>                    //Kapasitif sensör kütüphanesini ekle 

#define hoparlorPin 11                           //Hoparlörün bağlandığı pin numarasını tanımla

// Notalar ve frekans değerlerini tanımla
#define do     262                               //do
#define re     294                               //re
#define mi     330                               //mi
#define fa     349                               //fa
#define sol    392                               //sol
#define la     440                               //la
#define si     494                               //si
#define incedo 512                               //incedo

//Meyvelerin bağlandığı pin numaraları kapasitif sensör kütüphanesine tanımla
CapacitiveSensor cs_2_3  = CapacitiveSensor(2, 3);        
CapacitiveSensor cs_2_4  = CapacitiveSensor(2, 4);         
CapacitiveSensor cs_2_5  = CapacitiveSensor(2, 5);     
CapacitiveSensor cs_2_6  = CapacitiveSensor(2, 6);     
CapacitiveSensor cs_2_7  = CapacitiveSensor(2, 7);      
CapacitiveSensor cs_2_8  = CapacitiveSensor(2, 8);         
CapacitiveSensor cs_2_9  = CapacitiveSensor(2, 9);  
CapacitiveSensor cs_2_10 = CapacitiveSensor(2, 10);     

void setup() {
    pinMode(hoparlorPin, OUTPUT);                //Hoparlorün bağlandığı pini çıkış olarak ayarla
}

void loop() {
    //Sensör olarak kullanılacak meyvelerin dokunma hassasiyetini ayarla ve meyvelere dokunulduğu zaman, 
    //okunan değerleri meyve değişkenlerine kaydet
    long meyve1 = cs_2_3.capacitiveSensor(10000);
    long meyve2 = cs_2_4.capacitiveSensor(10000);
    long meyve3 = cs_2_5.capacitiveSensor(10000);
    long meyve4 = cs_2_6.capacitiveSensor(10000);
    long meyve5 = cs_2_7.capacitiveSensor(10000);
    long meyve6 = cs_2_8.capacitiveSensor(10000);
    long meyve7 = cs_2_9.capacitiveSensor(10000);
    long meyve8 = cs_2_10.capacitiveSensor(10000);

    //Meyvelere dokunulduğundan hoparlörden ilgili notayı çal
    if      (meyve1 > 300) { tone(hoparlorPin, do);     delay(200); } 
    else if (meyve2 > 300) { tone(hoparlorPin, re);     delay(200); } 
    else if (meyve3 > 300) { tone(hoparlorPin, mi);     delay(200); } 
    else if (meyve4 > 300) { tone(hoparlorPin, fa);     delay(200); } 
    else if (meyve5 > 300) { tone(hoparlorPin, sol);    delay(200); } 
    else if (meyve6 > 300) { tone(hoparlorPin, la);     delay(200); } 
    else if (meyve7 > 300) { tone(hoparlorPin, si);     delay(200); } 
    else if (meyve8 > 300) { tone(hoparlorPin, incedo); delay(200); } 
    else noTone(hoparlorPin);
}
