// S93 - Yaklaşım Sensörü

int SensorPin = A5;    // Sensörün bağlandığı pin numarasını tanımla
float sensorDegeri = 0; // Sensör değerinin tutulacağı değişkeni tanımla
int hoparlorPin = 5;    // Hoparlörün bağlandığı pin numarasını tanımla
int bipSure = 300;      // Uyarı sesi süresini tanımla ve ilk değerini 300 yap

void setup() {  
    pinMode(SensorPin, INPUT);     // Sensörün bağlandığı pini giriş olarak ayarla
    pinMode(hoparlorPin, OUTPUT);  // Hoparlörün bağlandığı pini çıkış olarak ayarla
}
   
void loop() {
    sensorDegeri = analogRead(SensorPin);      // Analog 0 pinindeki sensörden veriyi oku ve sensorDegeri değişkenine kaydet
    sensorDegeri = sensorDegeri * 5.0/1023.0;  // Analog pinden okunan 0 ile 1024 arasındaki değeri 5 ile çarp, 1023e bölerek 
                                               // voltaj cinsine çevir
    delay(100);                                // 100 ms bekle

    if (sensorDegeri <= 1.3) {                 // sensorDegeri 1,3'den küçük ise
        noTone(hoparlorPin);  
    }
  
    if (sensorDegeri >= 1.3 && sensorDegeri < 1.9) {  // sensorDegeri 1,3'den büyük ve 1,9'dan küçük ise
                                                      // hoparlörden ses çal
        tone(hoparlorPin, 440);
        delay(bipSure/4);
        noTone(hoparlorPin);
        delay(bipSure/4);
    }

    if (sensorDegeri >= 1.9 && sensorDegeri < 2.5) {  // sensorDegeri 1,9'dan büyük ve 2,5'den küçük ise
                                                      // hoparlörden ses çal
        tone(hoparlorPin, 440);
        delay(bipSure/5);
        noTone(hoparlorPin);
        delay(bipSure/5);
    }

    if (sensorDegeri >= 2.5 && sensorDegeri < 3.1) {  // sensorDegeri 2,5'den büyük ve 3,1'den küçük ise
                                                      // hoparlörden ses çal
        tone(hoparlorPin, 440);
        delay(bipSure/6);
        noTone(hoparlorPin);
        delay(bipSure/6);
    }

    if (sensorDegeri >= 3.1 && sensorDegeri < 3.7) {  // sensorDegeri 3,1'den büyük ve 3,7'den küçük ise
                                                      // hoparlörden ses çal
        tone(hoparlorPin, 440);
        delay(bipSure/7);
        noTone(hoparlorPin);
        delay(bipSure/7);
    }

    if (sensorDegeri >= 3.7 && sensorDegeri < 4.3) {  // sensorDegeri 3,7'den büyük ve 4,3'den küçük ise
                                                      // hoparlörden ses çal 
        tone(hoparlorPin, 440);
        delay(bipSure/8);
        noTone(hoparlorPin);
        delay(bipSure/8);
    }

    if (sensorDegeri >= 4.3) {                        // sensorDegeri 4,3'den büyük ise
                                                      // hoparlörden ses çal
        tone(hoparlorPin, 440);
    }
}
