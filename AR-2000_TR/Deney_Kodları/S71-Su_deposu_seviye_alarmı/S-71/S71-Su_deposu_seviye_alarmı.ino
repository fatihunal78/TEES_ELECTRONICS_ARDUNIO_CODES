// S71 - Su deposu seviye alarmı

// LED'lerin bağlandığı dijital pin numarasını tanımla
int kirmiziPin = 6;
int yesilPin = 5;

// Sıvı sensörlerinin bağlandığı pin numarasını tanımla
int minimumSensorPin = A5;
int maksimumSensorPin = A4;

// Hoparlör'ün bağlandığı pin numarasını tanımla
int hoparlorPin = 2;

// Sıvı sensörlerinin durumunun tutulacağı değişkenleri tanımla
int minimumSeviyeDurumu = 0;
int maksimumSeviyeDurumu = 0;

void setup() {
    // LED'lerin bağlandığı pini çıkış olarak ayarla
    pinMode(kirmiziPin, OUTPUT); 
    pinMode(yesilPin, OUTPUT); 
    
    // Hoparlör'ün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT); 
    
    // Sıvı sensörlerin bağlandığı pini giriş olarak ayarla
    pinMode(minimumSensorPin, INPUT);
    pinMode(maksimumSensorPin, INPUT);
}

void loop() {
    // Sıvı seviye durumlarını sorgula ve değişkene ata
    minimumSeviyeDurumu = analogRead(minimumSensorPin);
    maksimumSeviyeDurumu = analogRead(maksimumSensorPin);
    
    // Sıvı sensörünün durumunu kontrol et
    // İki sensörde aktif ise kap doludur, her iki sensörde pasif ise kap boştur.
    
    // minimumSeviyeDurumu ve maksimumSeviyeDurumu değişkenleri analog 200 değerinden büyük ise su tankeri 
    // dolu demektedir. İkaz olarak Yeşil LED yanar
    if (minimumSeviyeDurumu >= 200 && maksimumSeviyeDurumu >= 200) {
        // Kırmızı LED'i söndür
        digitalWrite(kirmiziPin, LOW);
        // Yeşil LED'i yak
        digitalWrite(yesilPin, HIGH);
    }
    // minimumSeviyeDurumu 200 değerinden büyük ve maksimumSeviyeDurumu 200'den küçük ise suyun yarısı dolu 
    // yarısı boş demektir. İkaz olarak Yeşil LED yanıp söner
    else if (minimumSeviyeDurumu >= 200 && maksimumSeviyeDurumu < 200) {
        // Kırmızı Ledi söndür
        digitalWrite(kirmiziPin, LOW); 
        // Yeşil LED'i yak
        digitalWrite(yesilPin, HIGH);
        delay(250);  // 250ms bekle
        // Yeşil LED'i söndür
        digitalWrite(yesilPin, LOW);
        delay(250);  // 250ms bekle
    }
    // minimumSeviyeDurumu ve maksimumSeviyeDurumu değişkenleri 200 değerinden küçük ise su tankeri boş 
    // demektir. İkaz olarak Kırmızı LED yanıp söner ve hoparlörden ses çıkar
    else if (minimumSeviyeDurumu <= 200 && maksimumSeviyeDurumu <= 200 || minimumSeviyeDurumu <= 200) {
        // Yeşil LED'i söndür
        digitalWrite(yesilPin, LOW);
        // Kırmızı LED'i yak
        digitalWrite(kirmiziPin, HIGH);
        
        for (int i = 0; i < 2; i++) {
            // Hoparlör'ü aktif et
            tone(hoparlorPin, 500);    
            delay(50);  // 50ms bekle
            // Hoparlör'ü sustur
            noTone(hoparlorPin);   
            delay(50);  // 50ms bekle
        }    
        
        // Hoparlör'ü sustur
        noTone(hoparlorPin);  
        delay(150);  // 150ms bekle
        // Kırmızı LED'i söndür
        digitalWrite(kirmiziPin, LOW);
        
        for (int i = 0; i < 2; i++) {
            // Hoparlör'ü aktif et
            tone(hoparlorPin, 500);    
            delay(50);  // 50ms bekle
            // Hoparlör'ü sustur
            noTone(hoparlorPin);   
            delay(50);  // 50ms bekle
        }    
        
        // Hoparlör'ü sustur
        noTone(hoparlorPin); 
        delay(150);  // 150ms bekle
    }
}
