// SA64 - Çift yönlü optik illüzyon

int MotorPwm2 = 10;    // LM293'un INPUT4 bacağının bağlandığı pin numarasını tanımla
                       // Arduino 10. pinden LM293D entegresinin 15. bacağına bağlı pin yardımı ile motor 
                       // saat yönünün tersinde dönecektir 
int MotorPwm1 = 9;     // LM293'un INPUT1 bacağının bağlandığı pin numarasını tanımla
                       // Arduino 9. pinden LM293D entegresinin 2. bacağına bağlı pin yardımı ile motor 
                       // saat yönünde dönecektir  

int PotPin = A0;       // Potansiyometrenin bağlandığı pini tanımla
int PB2_buton = 2;     // PB2 butonunun bağlandığı pini tanımla
int PB1_buton = 3;     // PB1 butonunun bağlandığı pini tanımla
int yesil_LED = 13;    // Yeşil LED'in bağlandığı pini tanımla 
int kirmizi_LED = 12;  // Kırmızı LED'in bağlandığı pini tanımla
int butondurumu = 0;   // Hangi butonun basıldığını tutacak değişkeni tanımla
int analogokuma;       // Potansiyometreden okunan değerin tutulacağı değişkeni tanımla

void setup() {
    pinMode(MotorPwm1, OUTPUT);       // LM293un INPUT4(15.bacağının) bağlandığı pini çıkış olarak ayarla 
    pinMode(MotorPwm2, OUTPUT);       // LM293un INPUT1(2.bacağının) bağlandığı pini çıkış olarak ayarla 
    pinMode(PotPin, INPUT);           // Potansiyometrenin bağlandığı pini giriş olarak ayarla
    pinMode(PB2_buton, INPUT_PULLUP); // PB2 butonunun bağlandığı pini giriş olarak ayarla
    pinMode(PB1_buton, INPUT_PULLUP); // PB1 butonunun bağlandığı pini giriş olarak ayarla
    pinMode(kirmizi_LED, OUTPUT);     // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(yesil_LED, OUTPUT);       // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
}

void loop() {
    if (digitalRead(PB1_buton) == LOW) {
        butondurumu = 1;
        digitalWrite(kirmizi_LED, HIGH);  // Kırmızı LED'i yak
        digitalWrite(yesil_LED, LOW);     // Yeşil LED'i söndür
    }
    
    if (digitalRead(PB2_buton) == LOW) {
        butondurumu = 2;
        digitalWrite(kirmizi_LED, LOW);   // Kırmızı LED'i söndür
        digitalWrite(yesil_LED, HIGH);    // Yeşil LED'i yak
    }
    
    analogokuma = analogRead(PotPin);
    int oranla = map(analogokuma, 0, 1023, 0, 150);

    if (butondurumu == 1) {
        analogWrite(MotorPwm2, 0);        // Motorun saat yönünde dönüşü için 10 numaralı pini toprağa çek
        analogWrite(MotorPwm1, oranla);   // 9 numaralı pine enerji ver
    }
    else if (butondurumu == 2) {       
        analogWrite(MotorPwm2, oranla);   // Motorun saat yönünün tersine dönüşü için 10 numaralı pine enerji ver
        analogWrite(MotorPwm1, 0);        // 9 numaralı pini toprağa çek
    }
    else {                                // Motoru durdur
        analogWrite(MotorPwm1, 0);      
        analogWrite(MotorPwm2, 0);     
    }
    
    delay(200);                          // 200ms bekle
}
