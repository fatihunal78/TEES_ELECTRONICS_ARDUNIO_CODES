// S78 - Şarkı Söyleyen Çiçek

// Kapasitif dokunma kütüphanesini ekle
#include <CapacitiveSensor.h>

// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 4;

// Kapasitif dokunma alıcı ve verici pinlerini tanımla
CapacitiveSensor cs_2_3 = CapacitiveSensor(2, 3);

void setup() {
    cs_2_3.set_CS_AutocaL_Millis(0xF);    // Otomatik kalibrasyonu kapat
}

void loop() {
    // Timer başlangıcını kaydet
    long start = millis();
    
    // Sensör hassasiyetini ayarla ve ölçümü kaydet
    long olcumDegeri = cs_2_3.capacitiveSensor(3000);
    
    int rastgeleSayi = random(50, 500);    // 50 ila 500 arasında rastgele sayı üret
    
    if (olcumDegeri > 500) {              // Ölçüm değeri 500'den büyük ise
        tone(hoparlorPin, rastgeleSayi);   // Hoparlörden rastgeleSayi tonunda ses çal
        delay(100);                        // 100ms bekle
    }
    
    if (olcumDegeri <= 2000) {            // Ölçüm değeri 2000'e eşit ya da küçük ise
        noTone(hoparlorPin);              // Hoparlörü sustur
    }
    
    delay(10);                            // 10ms bekle
}