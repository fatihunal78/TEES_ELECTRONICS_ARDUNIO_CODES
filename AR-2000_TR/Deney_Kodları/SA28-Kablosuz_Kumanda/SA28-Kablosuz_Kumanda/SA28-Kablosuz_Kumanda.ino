// SA28 - Kablosuz Kumanda

int sensorPin = A5;    //Kızılötesi sensörün bağlandığı pin numarasını tanımla
int LedPin = 7;        //LED'in bağlandığı pin numarasını tanımla

void setup() {
    pinMode(sensorPin, INPUT);    //Kızılötesi sensörün bağlandığı pini giriş olarak ayarla
    pinMode(LedPin, OUTPUT);      //LED'in bağlandığı pini çıkış olarak ayarla
}

void loop() {
    if (analogRead(sensorPin) >= 1000) {    //Analog pindeki sensör değeri 1000'den büyük ise,
                                            //Yani ortalama değer harici bir etken(butonun basılma durumu) 
                                            //sensörü tetikliyor ise
        digitalWrite(LedPin, HIGH);          //LED'i yak 
    } 
    else {                                   //Eğer analog pinden okunan sensör değeri sensörü tetiklemiyor ise 
        digitalWrite(LedPin, LOW);           //LED'i söndür
    }
}
