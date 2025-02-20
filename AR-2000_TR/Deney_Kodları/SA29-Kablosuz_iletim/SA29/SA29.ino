// SA29 - Kablosuz iletim

int sensorPin = A5;      //Kızılötesi sensörün bağlandığı pin numarasını tanımla
int ledler[] = {2,3,4,5,6}; //LED'lerin bağlandığı pin numaralarını tanımla
int okunanDeger;         //ADC'den okunan değerin kaydedileceği değişkeni tanımla

int ortalamaDeger;       //ADC'den okunan 10 değerin ortalamasının tutulacağı değişken tanımlandı
int sensorDegeri;        //Kızılötesi alıcı sensöründen okunan değerlerin tutulacağı değişkeni tanımla

void setup() {
    pinMode(sensorPin, INPUT);    //Kızılötesi sensörün bağlandığı pini giriş olarak ayarla
    
    for (int i = 0; i < 5; i++) {    //for döngüsü kullanılarak 
        pinMode(ledler[i], OUTPUT);   //LED'leri çıkış pini olarak ayarla 
    }
    
    //Aşağıdaki işlemler ile başlangıçta sensörün kalibrasyonu yapıldı
    //Analog pindeki değerler sıcaklık, ışık, ses gibi değişken faktörlere ve yere göre değişebilir
    //O yüzden başlangıçta kalibrasyon yapıldı
    
    for(int i = 0; i < 10; i++) {            //ADC'den başlangıçta 10 adet değer almak için 0 dan 10 a kadar 
        okunanDeger = analogRead(sensorPin);  //okunanDeger değişkenine ADC'den okunan değerleri kaydet
        ortalamaDeger = ortalamaDeger + okunanDeger;  //Bir önceki değeri ile okunanDeger değişkenine yeni 
                                                      //değeri toplayıp, kaydet
        delay(50);                            //50ms bekle
    }
    ortalamaDeger = ortalamaDeger/10;        //Ölçülen 10 değerin ortalamasını al
}

void loop() {
    sensorDegeri = analogRead(sensorPin);     //Kızılötesi sensördeki analog değerleri oku ve sensorDegeri 
                                             //değişkenine kaydet
    int oranla = map(sensorDegeri, ortalamaDeger, 1024, 0, 6);  //sensorDegeri değişkenindeki değerleri 0 ile 
                                                                //6 arasında oranla

    switch(oranla) {                          //switch case yapısı kullanarak oranla değişkeninden dönen 
                                             //verilere göre 
        case 0:                               //Case 0 durumunda 
            for (int i = 0; i < 5; i++) {     //for döngüsü kullaranarak 
                digitalWrite(ledler[i], LOW);  //Bütün LED'leri söndür 
            }
            break;                            //case 0 durumunu bitir 
            
        case 1:                               //case 1 durumunda 
            for (int i = 0; i < 5; i++) {     //for döngüsü kullanarak 
                digitalWrite(ledler[i], LOW);  //Bütün LED'leri söndür   
            }
            digitalWrite(ledler[0], HIGH);     //1. Yeşil LED'i yak
            break;                            //case 1 durumunu bitir  
            
        case 2:                               //case 2 durumunda 
            for (int i = 0; i < 5; i++) {     //for döngüsü kullanarak 
                digitalWrite(ledler[i], LOW);  //Bütün LED'leri söndür 
            }
            digitalWrite(ledler[0], HIGH);     //Birinci ve ikinci yeşil LEDi yak 
            digitalWrite(ledler[1], HIGH);
            break;                            //case 2 durumunu bitir 
            
        case 3:                               //case 3 durumunda 
            for (int i = 0; i < 5; i++) {     //for döngüsü kullanark 
                digitalWrite(ledler[i], LOW);  //Bütün LED'leri söndür 
            }
            digitalWrite(ledler[0], HIGH);     //Birinci, ikinci Yeşil LED ve Sarı LED'i yak 
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[2], HIGH);
            break;                            //case 3 durumunu bitir
            
        case 4:                               //Case 4 durumunda 
            for (int i = 0; i < 5; i++) {     //Bütün LED'leri söndür 
                digitalWrite(ledler[i], LOW);  
            }
            digitalWrite(ledler[0], HIGH);     //Birinci, ikinci yeşil LED, Sarı ve birinci kırmızı LED'i yak 
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[2], HIGH);
            digitalWrite(ledler[3], HIGH);
            break;                            //case 4 durumunu bitir 
            
        case 5:                               //case 5 durumunda 
            digitalWrite(ledler[0], HIGH);     //Bütün LED'leri yak    
            digitalWrite(ledler[1], HIGH);
            digitalWrite(ledler[2], HIGH);
            digitalWrite(ledler[3], HIGH);
            digitalWrite(ledler[4], HIGH); 
            break;                            //case 5 durumunu bitir 
    }
    delay(100);
}
