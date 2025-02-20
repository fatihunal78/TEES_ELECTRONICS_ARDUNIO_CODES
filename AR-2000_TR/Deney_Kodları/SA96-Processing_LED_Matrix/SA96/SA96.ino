// SA96 - Processing LED Matrix

#include <LedControl.h>

// LED Matriks bağlantılarını tanımla
int DIN = 4;                                // DIN pini tanımla
int CS  = 3;                                // CS pini tanımla
int CLK = 2;                                // CLK pini tanımla

int Led_Matrix_Sayisi = 1;                  // LED matriksler arka arkaya bağlanabilir
                                           // Birden fazla matriks bağlanacak ise buradaki sayıyı değiştirebilirsiniz

// Matriks pinlerinin bağlantıları ile m matriksini tanımla
LedControl lc = LedControl(DIN, CLK, CS, Led_Matrix_Sayisi);

// Processingden gelecek dataların kaydedileceği değişkeni tanımla
int gelen_data[8] = {};  

void setup() {
    lc.shutdown(0, false);                  // LED matrix uyku modunu kapat
    lc.setIntensity(0, 8);                 // Parlaklığı 8'e ayarla
    lc.clearDisplay(0);                     // Ekranı temizle
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {           // Eğer processing başlatıldıysa 
        for (int i = 0; i < 8; i++) {       // 0'dan 8'e kadar  
            while (Serial.available() == 0) {} // Seri iletişim açık olduğu sürece
            gelen_data[i] = Serial.read();    // Seri iletişimden okuduğu verileri gelen_data değişkenine kaydet
        }
        
        for (int i = 0; i < 8; i++) {       // 0'dan 8'e kadar 
            lc.setColumn(0, i % 8, gelen_data[i]); // gelen_data daki verileri LED matrise aktar
        }
        delay(100);
    }
}
