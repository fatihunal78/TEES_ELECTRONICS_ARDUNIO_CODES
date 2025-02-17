// S21 - Işık Sensörü (LDR)

int LdrPin = A5;              // LDR'nin bağlı olduğu pin numarası tanımlandı
                             // LDR 5 nolu analog pine (A5) bağlandı ve o pinin ismi LdrPin oldu 

int analogPin_OkunanDeger;    // LDR'den okuyacağımız verileri kaydetmek için 
                             // analogPin_OkunanDeger isimli değişken oluşturduk

void setup() {
    pinMode(LdrPin, INPUT);   // LdrPin isimli analog A5 pinini veri okumak için input yani giriş pini yaptık
    
    Serial.begin(9600);       // LDR'den okunan değerleri görebilmek için Seri Port Ekranını aktifleştirdik
                             // Seri port ekranında sağ alt köşede 9600 seçilmeli                         
}

void loop() {
    analogPin_OkunanDeger = analogRead(LdrPin);    // analogRead(LdrPin) komutu ile LDR'nin bağlı olduğu A5 
                                                  // pinindeki analog değerleri oku ve bu değerleri
                                                  // analogPin_OkunanDeger değişkeninde tut

    Serial.println(analogPin_OkunanDeger);         // analogPin_OkunanDeger değişkeninde tutulan LDR'nin değerini
                                                  // Serial.println komutu ile Seri Port Ekranına yazdırdık

    delay(400);                                    // Değerleri 400 ms aralıkla okuması için
                                                  // delay komutu ile 400ms gecikme oluşturduk 

    /* Araçlar'a tıkladıktan sonra "Seri Port Ekranı"na tıkladığınızda LDR üzerine düşen değerleri 
     * görebilirsiniz. Bu değerler 0 ile 1023 arasında değerlerdir. 0'ın altına düşmezler, 1023'ün üstüne 
     * çıkmazlar. Bu durum analog pinden okumanın gerçekleştirdiği ADC (Analog Dijital Çevirici)'nin 10 bit 
     * olması ile ilgili.
     */
}
