// S38 - Lüksmetre

/* LDR ile ışık seviyesi ölçümünde gerekli formül aşağıdaki gibidir:
 * Lux = 500/R(ldr)                    Işık seviyesi 500 bölü LDR direnci kadardır
 * Rldr = (10*Vout)/(5-Vout)          LDR direnci hesap formülü kohm cinsinden
 * 
 * Rldr formülünü üstteki formülde yerine yazarsak:
 * Lux = (2500/Vout-500)/10           formülünü buluruz
 * 
 * Vout = ADCdenokunandeger*(5/1024)  değerine eşittir.
 */

double Light(int ADCdenokunandeger) {                      // Light isimli bir fonksiyon oluşturduk
    double Vout = ADCdenokunandeger * 0.0048828125;       // ADC'den okunan değeri 5/1024 yani 0.0048828125 değeri ile çarptık
    int lux = (2500/Vout - 500)/10;                       // Işık şiddeti birimi olan lux değerini bulmak için gerekli hesaplamayı yaptık 
    return lux;                                           // Hesaplanan lux değerini loop fonksiyonu içine return komutu ile gönderdik
}

void setup() {
    Serial.begin(9600);                                   // Seri haberleşmeyi başlat
}

void loop() {
    int Okunandeger = analogRead(0);                      // Okunandeger değişkenini tanımla ve Analog 0 pininden okunan değeri tut
    Serial.print("Isik Parlakligi    : ");               // Seri ekrana ışık parlaklığı değerini yaz
    Serial.print(int(Light(analogRead(0))));             // Seri ekranda Light fonksiyonu ile hesaplanmış değeri döndür
    Serial.println("  LUX  ");
    delay(1000);                                         // 1 saniye bekle
}
