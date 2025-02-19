// SA86 - İnteraktif Hafıza Oyunu

#include <CapacitiveSensor.h>                                //Kapasitif sensör kütüphanesini ekle 

//Meyvelerin bağlandığı pin numaralarını kapasitif sensör kütüphanesine ekle
CapacitiveSensor cs_2_3 = CapacitiveSensor(2, 3);        
CapacitiveSensor cs_2_4 = CapacitiveSensor(2, 4);         
CapacitiveSensor cs_2_5 = CapacitiveSensor(2, 5);     
CapacitiveSensor cs_2_6 = CapacitiveSensor(2, 6);     

const int Maksimum_Seviye = 100;                           //Oyunun maksimum seviyesini belirleyecek değişkeni tanımla ve maksimum seviyeyi 100 yap

int siralama[Maksimum_Seviye];                            //Sıralamanın kaydedileceği değişkeni maksimum seviye kadar elemanlı dizi olarak tanımla 
int oyuncu_seviyesi[Maksimum_Seviye];                     //Oyuncunun kaçıncı seviyede olduğunu tutacak değişkeni tanımla
int seviye = 1;                                           //Oyunun seviyesinin tutulacağı değişkeni tanımla ve ilk seviye değerini 1 yap
int oyun_hizi = 1000;                                     //Oyunun seviye yükseldikçe hızıda artacak, bu yüzden oyun_hizi değişkenini tanımla
                                                          //ve bu değişkenin ilk değeri 1000 yap

int buzzerPin = 12;                                       //Buzzerin bağlandığı pin numarasını tanımla
int kirmizi_ledPin = 11;                                  //Kırmızı LED'in bağlandığı pini tanımla 
int yesil_ledPin = 10;                                    //Yeşil LED'in bağlandığı pini tanımla
int mavi_ledPin = 9;                                      //Mavi LED'in bağlandığı pini tanımla 
int sari_ledPin = 8;                                      //Sari LED'in bağlandığı pini tanımla 

long kirmizi_buton;                                       //Kapasitif meyve butonunda Kırmızı LED'i temsil eden buton değişkenini tanımla 
long yesil_buton;                                         //Kapasitif meyve butonunda Yeşil LED'i temsil eden buton değişkenini tanımla
long mavi_buton;                                          //Kapasitif meyve butonunda Mavi LED'i temsil eden buton değişkenini tanımla
long sari_buton;                                          //Kapasitif meyve butonunda Sarı LED'i temsil eden buton değişkenini tanımla 

int kirmizi_durumu = 0;                                   //Kırmızı butona basılıp basılmadığı durumunun tutulacağı değişkeni tanımla
int yesil_durumu = 0;                                     //Yeşil butona basılıp basılmadığı durumunun tutulacağı değişkeni tanımla
int mavi_durumu = 0;                                      //Mavi butona basılıp basılmadığı durumunun tutulacağı değişkeni tanımla
int sari_durumu = 0;                                      //Sarı butona basılıp basılmadığı durumunun tutulacağı değişkeni tanımla

void setup() {
    pinMode(kirmizi_ledPin, OUTPUT);                      //Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesil_ledPin, OUTPUT);                        //Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(mavi_ledPin, OUTPUT);                         //Mavi LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sari_ledPin, OUTPUT);                         //Sarı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(buzzerPin, OUTPUT);                           //Buzzerın bağlandığı pini çıkış olarak ayarla 

    //Başlangıçta bütün LED'leri ve buzzerı LOW yaptık
    digitalWrite(kirmizi_ledPin, LOW); 
    digitalWrite(yesil_ledPin, LOW);
    digitalWrite(mavi_ledPin, LOW);
    digitalWrite(sari_ledPin, LOW);
    digitalWrite(buzzerPin, LOW);    
}

void loop() {
    buton_kontrol();                                      //Butonların basılıp basılmadığını kontrol eden fonksiyonu çağır
  
    if (seviye == 1) {                                   //Eğer oyunun seviyesi 1 ise, yani birinci seviyede ise
        siralama_olustur();                              //siralama_olustur() fonksiyonunu çağır
    }

    if (digitalRead(kirmizi_ledPin) == LOW || seviye != 1) {  //Eğer Kırmızı LED'i kontrol eden butona basıldıysa ya da 
                                                              //oyun seviyesi 1'den farklı ise 
        buton_kontrol();
        siralamayi_goster();                             //siralamayi_goster() fonksiyonunu çağır
        siralamayi_arttir();                             //siralamayi_arttir() fonksiyonuu çağır
    }
}

void buton_kontrol() {                                   //Butonların basılıp basılmadığını kontrol eden fonksiyonu oluştur
    //Sensör olarak kullanılacak meyvelerin dokunma hassasiyetini ayarla
    //ve meyvelere dokunulduğu zaman, okunan değerleri meyve değişkenlerine kaydet
    kirmizi_buton = cs_2_3.capacitiveSensor(10000);
    yesil_buton = cs_2_4.capacitiveSensor(10000);
    mavi_buton = cs_2_5.capacitiveSensor(10000);
    sari_buton = cs_2_6.capacitiveSensor(10000);
   
    if (kirmizi_buton > 300) {                          //Eğer Kırmızı LED'i kontrol eden meyveye dokunulursa, 
        kirmizi_durumu = 1;                             //kirmizi_durumu değişkenini 1 yap 
    }
    else if (yesil_buton > 300) {                       //Eğer Yeşil LED'i kontrol eden meyveye dokunulursa, 
        yesil_durumu = 1;                               //yesil_durumu değişkenini 1 yap 
    }
    else if (mavi_buton > 300) {                        //Eğer Mavi LED'i kontrol eden meyveye dokunulursa, 
        mavi_durumu = 1;                                //mavi_durumu değişkenini 1 yap 
    }
    else if (sari_buton > 300) {                        //Eğer Sari LED'i kontrol eden meyveye dokunulursa, 
        sari_durumu = 1;                                //sari_durumu değişkenini 1 yap 
    }
    else {                                              //meyvelere dokunulmazsa değişkenlerin değerini 0 yap
        kirmizi_durumu = 0; 
        yesil_durumu = 0; 
        mavi_durumu = 0; 
        sari_durumu = 0;
    }
}

void siralamayi_goster() {                              //siralamayi_goster() fonksiyonunu oluştur 
    //Bütün LED'leri söndür
    digitalWrite(kirmizi_ledPin, LOW); 
    digitalWrite(yesil_ledPin, LOW);
    digitalWrite(mavi_ledPin, LOW);
    digitalWrite(sari_ledPin, LOW);
    
    for (int i = 0; i < seviye; i++) {                 //i değerini 0'dan oyununun seviyesine kadar birer arttır
        digitalWrite(siralama[i], HIGH);                //siralama değişeninin i. değerini HIGH yap 
        delay(oyun_hizi);                              //oyun_hizi kadar gecikme koy

        digitalWrite(siralama[i], LOW);                 //siralama değişeninin i. değerini LOW yap 
        delay(200);                                     //200 ms gecikme 
    }
}

void siralamayi_arttir() {                             //siralamayi_arttir() fonksiyonunu oluştu 
    int flag = 0;                                      //flag değişkeni oluştur ve ilk değerini 0 yap 

    for (int i = 0; i < seviye; i++) {                //i değerini 0'dan oyun seviyesine kadar birer arttır 
        flag = 0;                                      //flag değerini sıfır yap 

        while(flag == 0) {                            //flag değeri sıfır olduğu sürece 
            buton_kontrol();                          //Butonların basılıp basılmadığını kontrol eden fonksiyonu çağır
          
            if (kirmizi_durumu == 1) {                //Eğer Kırmızı LED'i kontrol eden butona basıldı ise 
                digitalWrite(kirmizi_ledPin, HIGH);    //Kırmızı LED'i yak 
                oyuncu_seviyesi[i] = 11;              //oyuncu_seviyesi değişkeninin i. değerine 11 değerini kaydet 
                flag = 1;                              //flag değerini 1 yap 
                delay(200);                            //200 ms bekle 

                if (oyuncu_seviyesi[i] != siralama[i]) {  //Eğer oyuncu_seviyesinin i. değeri ve siralamanın i. değeri 
                                                          //aynı değil ise bu demek oluyorki yanlış butona basıldı 
                    kaybettiniz();                        //Oyun kaybedildiği için kaybettiniz() fonksiyonunu çağır
                    return; 
                }
                digitalWrite(kirmizi_ledPin, LOW);        //Kırmızı LED'i söndür 
            }

            if (yesil_durumu == 1) {                     //Eğer Yeşil LED'i kontrol eden butona basıldı ise 
                digitalWrite(yesil_ledPin, HIGH);         //Yeşil LED'i yak 
                oyuncu_seviyesi[i] = 10;                 //oyuncu_seviyesi değişkeninin i. değerine 10 değerini kaydet 
                flag = 1;                                 //flag değerini 1 yap 
                delay(200);                               //200 ms bekle

                if (oyuncu_seviyesi[i] != siralama[i]) { //Eğer oyuncu_seviyesinin i. değeri ve siralamanın i. değeri 
                                                         //aynı değil ise bu demek oluyorki yanlış butona basıldı
                    kaybettiniz();                       //kaybettiniz() fonksiyonunu çağır
                    return;
                }
                digitalWrite(yesil_ledPin, LOW);          //Yeşil LED'i söndür 
            }

            if (mavi_durumu == 1) {                      //Eğer Mavi LED'i kontrol eden butona basıldı ise 
                digitalWrite(mavi_ledPin, HIGH);          //Mavi LED'i yak
                oyuncu_seviyesi[i] = 9;                  //oyuncu_seviyesi değişkeninin i. değerine 9 değerini kaydet 
                flag = 1;                                 //flag değerini 1 yap 
                delay(200);                               //200 ms bekle

                if (oyuncu_seviyesi[i] != siralama[i]) { //Eğer oyuncu_seviyesinin i. değeri ve siralamanın i. değeri 
                                                         //aynı değil ise bu demek oluyorki yanlış butona basıldı
                    kaybettiniz();                       //kaybettiniz() fonksiyonunu çağır
                    return;
                }
                digitalWrite(mavi_ledPin, LOW);           //Mavi LED'i söndür 
            }

            if (sari_durumu == 1) {                      //Eğer Sarı LED'i kontrol eden butona basıldı ise 
                digitalWrite(sari_ledPin, HIGH);          //Sarı LED'i yak
                oyuncu_seviyesi[i] = 8;                  //oyuncu_seviyesi değişkeninin i. değerine 8 değerini kaydet 
                flag = 1;                                 //flag değerini 1 yap 
                delay(200);                               //200 ms bekle

                if (oyuncu_seviyesi[i] != siralama[i]) { //Eğer oyuncu_seviyesinin i. değeri ve siralamanın i. değeri 
                                                         //aynı değil ise bu demek oluyorki yanlış butona basıldı
                    kaybettiniz();                       //kaybettiniz() fonksiyonunu çağır
                    return;
                }
                digitalWrite(sari_ledPin, LOW);           //Sarı LED'i söndür 
            }
        }
    }
    siralama_kontrol();                                  //siralama_kontrol() fonksiyonunu çağır 
}

void siralama_olustur() {                                //siralama_olustur() fonksiyonunu oluştur 
    randomSeed(millis());  

    for (int i = 0; i < Maksimum_Seviye; i++) {         //i değerini sıfırdan maksimum seviyeye kadar birer arttır 
        siralama[i] = random(8, 12);                    //siralama değişkeninin i. değerine 8 ile 12 arasında rastgele bir sayı ata
    }
}

void kaybettiniz() {                                    //kaybettiniz() foksiyonunu oluştur 
    for (int i = 0; i < 6; i++) {                      //3 kere döngü yap 
        //LED'leri yakıp ve söndürme işlemi için aşağıdaki işlemleri yaptık

        //LED'leri yak ve buzzerdan ses çıkar          
        digitalWrite(kirmizi_ledPin, HIGH); 
        digitalWrite(yesil_ledPin, HIGH);
        digitalWrite(mavi_ledPin, HIGH);
        digitalWrite(sari_ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        //LED'lerieri söndür ve buzzerı sustur
        digitalWrite(kirmizi_ledPin, LOW); 
        digitalWrite(yesil_ledPin, LOW);
        digitalWrite(mavi_ledPin, LOW);
        digitalWrite(sari_ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(250);
    }
    seviye = 1;                                         //seviye değerini 1'e eşitle 
    oyun_hizi = 1000;                                   //Oyun hızını 1000 yap 
}

void siralama_kontrol() {                               //siralama_kontrol() fonksiyonunu oluştur 
    digitalWrite(buzzerPin, LOW);                       //Buzzerı sustur 
    delay(250);                                         //250 ms bekle 
    digitalWrite(buzzerPin, HIGH);                      //Buzzerdan ses çıkar 
    delay(250);                                         //250 ms bekle 
    digitalWrite(buzzerPin, LOW);                       //Buzzerı sustur 
    delay(500);                                         //500 ms bekle 

    if (seviye < Maksimum_Seviye) {                    //Eğer seviye maksimum seviyeden küçük ise 
        seviye++;                                       //seviye değişkenini bir arttır
        oyun_hizi -= 50;                               //oyun_hizi değişkenini 50 azalt
    }
}
