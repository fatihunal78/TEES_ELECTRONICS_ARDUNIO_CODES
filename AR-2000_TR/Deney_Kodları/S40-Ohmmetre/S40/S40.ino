// S40 - Ohmmetre

// Pin numaralarını tanımla
int adcPin = A0;    

// Değişkenleri tanımla
int okunanDeger = 0;
int Vin = 5;
float Vout = 0;
int R1 = 10000;      // Bilinen direnç değeri kalibrasyon için değiştirilebilir
double R2 = 0;
float buffer = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("OLCMEK ISTEDIGINIZ DIRENCI BAGLAYIN");    // Seri port ekranına yazdır
}

void loop() {
    okunanDeger = analogRead(adcPin);    // ADC pininden okunan değeri okunanDeger değişkenine kaydet
    
    if(okunanDeger) {                    // okunanDeger tanımlı ise
        // Ölçüm işlemi için gerekli hesaplamaları yap
        buffer = okunanDeger * Vin;     
        Vout = (buffer)/1024.0;
        buffer = (Vin/Vout) - 1;
        R2 = R1 * buffer;
        
        if(R2 >= 10000000) {             // Eğer çıkan sonuç 10000000'den büyük ise
            Serial.println("Direnc Baglayiniz...");
        }
        else if(R2 >= 1000 && R2 < 1000000) {    // Eğer çıkan sonuç 1000'den büyük ve 1000000'den küçük ise K OHM yazdırmak için
            R2 = R2/1000;
            Serial.print("Direnc Degeri: ");
            Serial.print(R2);
            Serial.println("  K OHM");
        }
        else if(R2 >= 1000000 && R2 < 10000000) {    // Eğer çıkan sonuç 1000000'den büyük 10000000'den küçük ise M OHM yazdırmak için
            R2 = R2/1000000;
            Serial.print("Direnc Degeri: ");
            Serial.print(R2);
            Serial.println("  M OHM");
        }
        else if(R2 < 1000) {             // Eğer çıkan sonuç 1000'den küçük ise OHM yazdırmak için
            Serial.print("Direnc Degeri: ");
            Serial.print(R2);
            Serial.println("  OHM");
        }
        delay(1000);
    }
}
