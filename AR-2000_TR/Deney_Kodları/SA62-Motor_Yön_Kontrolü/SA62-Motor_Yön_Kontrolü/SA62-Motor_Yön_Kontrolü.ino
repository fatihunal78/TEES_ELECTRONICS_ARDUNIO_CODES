// SA62 - Motor Yön Kontrolü

int MotorPwm2 = 10;  //LM293'un INPUT4 bacağının bağlandığı pin numarasını tanımla
                     //Arduino 10. pinden LM293D entegresinin 15. bacağına bağlı pin yardımı ile motor 
                     //saat yönünün tersinde dönecektir 

int MotorPwm1 = 9;   //LM293'un INPUT1 bacağının bağlandığı pin numarasını tanımla
                     //Arduino 9. pinden LM293D entegresinin 2. bacağına bağlı pin yardımı ile motor 
                     //saat yönünde dönecektir  

int sagButon = 2;    //Sağ taraftaki PB1 butonunun bağlandığı pin numarasını tanımla 
int solButon = 3;    //Sol taraftaki PB2 butonunun bağlandığı pin numarasını tanımla

void setup()
{
    pinMode(sagButon, INPUT_PULLUP);   //Sağ butonun bağlandığı pini giriş olarak ayarla
    pinMode(solButon, INPUT_PULLUP);   //Sol butonun bağlandığı pini giriş olarak ayarla 
    
    pinMode(MotorPwm1, OUTPUT);        //LM293'un INPUT4 bacağının bağlandığı pini çıkış olarak ayarla 
    pinMode(MotorPwm2, OUTPUT);        //LM293'un INPUT1 bacağının bağlandığı pini çıkış olarak ayarla 
}

void loop() 
{
    if (digitalRead(sagButon) == LOW) {        //Eğer sağ taraftaki PB1 butonuna basıldı ise 
                                              //Motoru saat yönünde döndürmek için aşağıdaki işlemleri yap               
        digitalWrite(MotorPwm1, HIGH);        //Motorun saat yönüne dönüşü için 9 numaralı pine enerji ver 
        digitalWrite(MotorPwm2, LOW);         //10 numaralı pini ground (toprağa) çek
    }
    else if (digitalRead(solButon) == LOW) {  //Eğer sol taraftaki PB2 butonuna basıldı ise 
                                             //Motoru saat yönünün tersine döndürmek için aşağıdaki işlemleri yap
        digitalWrite(MotorPwm1, LOW);         //Motorun saat yönünün tersine dönüşü için 9 numaralı pini toprağa çek 
        digitalWrite(MotorPwm2, HIGH);        //10 numaralı pine enerji ver                                     
    }
    else {                                    //Eğer hiçbir butona basılı değil ise 
                                             //Motoru durdur 
        digitalWrite(MotorPwm1, LOW);   
        digitalWrite(MotorPwm2, LOW);   
    }
    
    delay(200);                              //200ms bekle     
}
