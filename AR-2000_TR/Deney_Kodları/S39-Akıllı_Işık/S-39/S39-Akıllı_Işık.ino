// S39 - Akıllı Işık

#define LDR_PIN                 0      // LDR'nin bağlandığı pini tanımla
#define Maks_Adc_Okuma         1023    // ADC'ye uygulanan değer 5V olduğu zaman ADC'de maksimum 1023 değerini görürüz. 
                                       // Bu yüzden maksimum ADC okumasını 1023 olarak belirttik
#define Adc_Referans_Voltaj    5.0     // Arduino UNO Analog pinlerdeki referans voltaj değeri 5 Volttur. 
                                       // Bunu hesaplamalar için belirttik                               
#define Referans_Direnc        10000   // LDR'nin ve Analog pinin girişinden toprağa bağlı olan direncin 10K olduğunu tanımladık 

// Alt taraftaki 2 değişkenin aldığı değerler LUX değerinin hesaplanabilmesi için gerekli sabit değerlerdir
#define LUX_Sabit              12518931
#define LUX_Sabit_egrisel_sabit -1.405

int ledPin = 3;                        // LED'in bağlandığı pini tanımla

// Hesaplamalar için gerekli değişken tanımlamaları yapıldı 
int   Okunan_Deger;
float Direnc_Voltaji, LDR_Voltaji;
float LDR_Direnci;
float ldrLux;
int   oranla;
  
void setup(void) {
 
}

void loop(void) {  
    Okunan_Deger = analogRead(LDR_PIN);    // Analog pinden okunan değeri Okunan_Deger değişkenine kaydet    
    
    // Okunan_Deger'in voltaj karşılığını bulmak için (Okunan_Deger*5/1023) formülünü kullan
    // ve bunu Direnc_Voltaji değişkeninde tut
    Direnc_Voltaji = (float)Okunan_Deger / Maks_Adc_Okuma * Adc_Referans_Voltaj;  
                                                                                      
    // LDR üzerine düşen voltajı bulmak için Referans voltaj - Direnc voltajı yap (5 - Direnc_Voltaji)
    LDR_Voltaji = Adc_Referans_Voltaj - Direnc_Voltaji;  
  
    // LDR'nin ışığa bağlı olarak direncinin değiştiğini biliyoruz
    // LDR üzerindeki direnç değerini bulalım ki ışık miktarını da bulalım
    // LDR direnci için (LDR'den okuduğumuz voltaj)/(Analog pinden okunan voltaj * 5) formülü ile hesapladık
    LDR_Direnci = LDR_Voltaji/Direnc_Voltaji * Referans_Direnc; 
  
    // LUX değerini bulmak için matematiksel işlemi de yaptıktan sonra LUX değerini bulmuş olduk
    ldrLux = LUX_Sabit * pow(LDR_Direnci, LUX_Sabit_egrisel_sabit);

    // ldrLux değişkeninden okunan 0 ile 300 arasındaki değerleri 255 ile 0 arasına oranla
    oranla = map(ldrLux, 0, 300, 255, 0); 
  
    if(ldrLux > 300) {                     // Eğer ldrLux değeri 300'den büyük ise 
        oranla = 0;                        // oranla değişkenini 0 yap     
    }
    
    analogWrite(ledPin, oranla);           // analogWrite komutu ile oranlanan değeri PWM sinyali olarak LED'e gönder
    delay(100);                            // 100 ms bekle
}
