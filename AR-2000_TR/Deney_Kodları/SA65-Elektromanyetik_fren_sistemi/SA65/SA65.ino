// SA65 - Elektromanyetik fren sistemi

int MotorPwm2 = 10;     // LM293'un INPUT4 bacağının bağlandığı pin numarasını tanımla
                        // Arduino 10. pinden LM293D entegresinin 15. bacağına bağlı pin yardımı ile motor 
                        // saat yönünün tersinde dönecektir 

int MotorPwm1 = 9;      // LM293'un INPUT1 bacağının bağlandığı pin numarasını tanımla
                        // Arduino 9. pinden LM293D entegresinin 2. bacağına bağlı pin yardımı ile motor 
                        // saat yönünde dönecektir  

int motoryonu = 0;      // Motorun hangi yöne döndüğünü tutacak değişkeni tanımla
                        // Eğer değer 1 ise saat yönünde
                        // Eğer değer 2 ise saat yönünün tersinde

int motor_hizi = 0;     // Motorun hızının tutulacağı değişkeni tanımla
int PotPin = A0;        // Potansiyometrenin bağlandığı pini tanımla
int PB2_buton = 2;      // PB2 butonunun bağlandığı pini tanımla
int Joystick_buton = 3; // Joystick butonunun bağlandığı pini tanımla
int PB1_buton = 4;      // PB1 butonunun bağlandığı pini tanımla
int butondurumu = 0;    // Hangi butonun basıldığını tutacak değişkeni tanımla
int analogokuma;        // Potansiyometreden okunan değerin tutulacağı değişkeni tanımla

void setup() {
    pinMode(MotorPwm1, OUTPUT);          // LM293un INPUT4(15.bacağının) bağlandığı pini çıkış olarak ayarla 
    pinMode(MotorPwm2, OUTPUT);          // LM293un INPUT1(2.bacağının) bağlandığı pini çıkış olarak ayarla 
    pinMode(PotPin, INPUT);              // Potansiyometrenin bağlandığı pini giriş olarak ayarla
    pinMode(PB2_buton, INPUT_PULLUP);    // PB2 butonunun bağlandığı pini giriş olarak ayarla
    pinMode(PB1_buton, INPUT_PULLUP);    // PB1 butonunun bağlandığı pini giriş olarak ayarla
    pinMode(Joystick_buton, INPUT_PULLUP);// Joystick butonunun bağlandığı pini giriş olarak ayarla
}

void loop() {
    if (digitalRead(PB1_buton) == LOW) {     // Eğer PB1 butonuna basıldı ise 
        butondurumu = 1;                      // butondurumu değişkenini 1 yap
    }
    
    if (digitalRead(PB2_buton) == LOW) {     // Eğer PB2 butonuna basıldı ise 
        butondurumu = 2;                      // butondurumu değişkenini 2 yap 
    }
    
    if (digitalRead(Joystick_buton) == LOW) { // Eğer Joystick butonuna basıldı ise 
        butondurumu = 3;                       // butondurumu değişkenini 3 yap
    }
    
    analogokuma = analogRead(PotPin);          
    int oranla = map(analogokuma, 0, 1023, 0, 255); 

    if (butondurumu == 1) {                   // Saat yönünde dönüyor (PB1)
        analogWrite(MotorPwm1, 0);            // 9 numaralı pini toprağa çek
        analogWrite(MotorPwm2, oranla);       // 10 numaralı pine enerji ver
        motoryonu = 1; 
        
        if (digitalRead(Joystick_buton) == LOW) {
            butondurumu = 3; 
        }
    }
    else if (butondurumu == 2) {             // Saat yönünün tersinde dönüyor (PB2)
        analogWrite(MotorPwm1, oranla);      // 9 numaralı pine enerji ver
        analogWrite(MotorPwm2, 0);           // 10 numaralı pini toprağa çek
        motoryonu = 2; 
        
        if (digitalRead(Joystick_buton) == LOW) {
            butondurumu = 3; 
        }
    }
    else if (butondurumu == 3) {             // Motoru durdur
        if (motoryonu == 1) {                // Eğer motor saat yönünde dönüyorsa
            analogokuma = analogRead(PotPin); // analogokuma değişkenine analog A0 pininden okunan değeri kaydet 
            int oranla = map(analogokuma, 0, 1023, 0, 255); // Analog pinden okunan 0 ile 1023 arasındaki değeri 
                                                            // 0 ile 255 arasında oranla
            
            if (oranla <= 150) {
                // Motoru ani durdurmak için saat yönünün tersine döndür ve sonrasında kapat
                analogWrite(MotorPwm1, 0);    // Motorun saat yönünün tersine dönüşü için 9 numaralı pini toprağa çek
                analogWrite(MotorPwm2, 255);  // 10 numaralı pine enerji ver 
                delay(350);                   // 350 ms bekle
                
                // Motoru kapat
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                butondurumu = 0;
                motoryonu = 0;
            }
            else {
                // Motoru ani durdurmak için saat yönüne döndür ve sonrasında kapat
                analogWrite(MotorPwm1, 0);      // Motorun saat yönünün tersine dönüşü için 9 numaralı pini toprağa çek
                analogWrite(MotorPwm2, oranla); // 10 numaralı pine enerji ver
                delay(1000);                    // 1 s bekle
                
                // Motoru kapat
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                butondurumu = 0;
                motoryonu = 0;
            }
        }
        else if (motoryonu == 2) {            // Eğer motor saat yönünün tersinde dönüyorsa
            analogokuma = analogRead(PotPin);  // analogokuma değişkenine analog A0 pininden okunan değeri kaydet 
            int oranla = map(analogokuma, 0, 1023, 0, 255); // Analog pinden okunan 0 ile 1023 arasındaki değeri 
                                                            // 0 ile 255 arasında oranla
            
            if (oranla <= 150) {
                // Motoru ani durdurmak için saat yönünde döndür ve sonrasında kapat
                analogWrite(MotorPwm1, 255);   // Motorun saat yönüne dönüşü için 9 numaralı pine enerji ver 
                analogWrite(MotorPwm2, 0);     // 10 numaralı pini ground (toprağa) çek
                delay(350);                    // 350 ms bekle
                
                // Motoru kapat
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                butondurumu = 0;
                motoryonu = 0;
            }
            else {
                // Motoru ani durdurmak için saat yönünde döndür ve sonrasında kapat
                analogWrite(MotorPwm1, oranla); // Motorun saat yönüne dönüşü için 9 numaralı pine enerji ver 
                analogWrite(MotorPwm2, 0);      // 10 numaralı pini ground (toprağa) çek
                delay(1000);                    // 1 s bekle
                
                // Motoru kapat
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                butondurumu = 0;
                motoryonu = 0;
            }  
        }
        else {
            analogWrite(MotorPwm1, 0);      
            analogWrite(MotorPwm2, 0);  
        }
    }
    else {                                    // Motoru durdur
        analogWrite(MotorPwm1, 0);      
        analogWrite(MotorPwm2, 0);     
    }
    
    delay(200);                               // 200ms bekle
}
