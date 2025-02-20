// S35 - Polis Sireni ve Çakar Lamba

// LED'lerin bağlandığı dijital pin numaralarını tanımla
int led1Pin = 3;  
int led2Pin = 4;

// Buton'un bağlandığı dijital pin numarasını tanımla
int butonPin = 2;

// Hoparlörün bağlandığı pin numarasını tanımla
int hoparlorPin = 5;

// Siren tone değişkeninin tutulacağı değişkeni tanımla
int f;

// Siren süresinin tutulacağı değişkeni tanımla
int d = 10;

// LED animasyonu için kullanılacak değişkenleri tanımla
int sinyalDurumu = 0;
int tekrarSayisi = 0;
int ledDurumu = 0;

void setup() {  
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla             
    pinMode(led1Pin, OUTPUT);   
    pinMode(led2Pin, OUTPUT);  
    
    // Buton'un bağlandığı pini giriş olarak ayarla   
    pinMode(butonPin, INPUT); 
    
    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT); 
}

void loop() {
    ledDurumu = 0;
    tekrarSayisi = 0;
    sinyalDurumu = 0; 
    
    for(f = 635; f <= 909; f++) {
        // Butona basılıp basılmadığını kontrol et
        if(digitalRead(butonPin) == LOW) {    // Butona basılmadı ise
            // Sireni çaldır
            tone(hoparlorPin, f);
            delay(d);
        }
        else {    // Butona basıldı ise
            // Dat dat sesi çaldır
            noTone(hoparlorPin);
            tone(hoparlorPin, 250);
            delay(5);
            noTone(hoparlorPin);  
            delay(5);
        }
        
        d = 10;
        sinyalDurumu++;
        
        // LED'leri animasyon ile yak
        if(sinyalDurumu == 5) {
            switch(ledDurumu) {
                case 0:
                    digitalWrite(led1Pin, HIGH);
                    ledDurumu++;
                    break;
                    
                case 1:
                    digitalWrite(led1Pin, LOW);
                    if(tekrarSayisi < 2) {
                        tekrarSayisi++;
                        ledDurumu = 0;
                    }
                    else {
                        ledDurumu++;
                        tekrarSayisi = 0;
                    }
                    break;
                    
                case 2:
                    tekrarSayisi++;
                    if(tekrarSayisi == 5) {
                        ledDurumu++;
                        tekrarSayisi = 0;
                    }
                    break;  
                    
                case 3:
                    digitalWrite(led2Pin, HIGH);
                    ledDurumu++;
                    break;
                    
                case 4:
                    digitalWrite(led2Pin, LOW);
                    if(tekrarSayisi < 2) {
                        tekrarSayisi++;
                        ledDurumu = 3;
                    }
                    else {
                        ledDurumu++;
                        tekrarSayisi = 0;
                    }
                    break;
                    
                case 5:
                    tekrarSayisi++;
                    if(tekrarSayisi == 5) {
                        ledDurumu = 0;
                        tekrarSayisi = 0;
                    }
                    break;
            }
            sinyalDurumu = 0;
        }
    }
  
    ledDurumu = 0;
    tekrarSayisi = 0;
    sinyalDurumu = 0; 
    
    for(f = 909; f >= 634; f--) {
        // Butona basılıp basılmadığını kontrol et
        if(digitalRead(butonPin) == LOW) {    // Butona basılmadı ise
            // Sireni çaldır
            tone(hoparlorPin, f);
            delay(d);
        }
        else {    // Butona basıldı ise
            // Dat dat sesi çaldır
            noTone(hoparlorPin);
            tone(hoparlorPin, 250);
            delay(5);
            noTone(hoparlorPin);  
            delay(5);
        }
        
        d = 10;
        sinyalDurumu++;
        
        // LED'leri animasyon ile yak
        if(sinyalDurumu == 5) {
            switch(ledDurumu) {
                case 0:
                    digitalWrite(led2Pin, HIGH);
                    ledDurumu++;
                    break;
                    
                case 1:
                    digitalWrite(led2Pin, LOW);
                    if(tekrarSayisi < 2) {
                        tekrarSayisi++;
                        ledDurumu = 0;
                    }
                    else {
                        ledDurumu++;
                        tekrarSayisi = 0;
                    }
                    break;
                    
                case 2:
                    tekrarSayisi++;
                    if(tekrarSayisi == 5) {
                        ledDurumu++;
                        tekrarSayisi = 0;
                    }
                    break;  
                    
                case 3:
                    digitalWrite(led1Pin, HIGH);
                    ledDurumu++;
                    break;
                    
                case 4:
                    digitalWrite(led1Pin, LOW);
                    if(tekrarSayisi < 2) {
                        tekrarSayisi++;
                        ledDurumu = 3;
                    }
                    else {
                        ledDurumu++;
                        tekrarSayisi = 0;
                    }
                    break;
                    
                case 5:
                    tekrarSayisi++;
                    if(tekrarSayisi == 5) {
                        ledDurumu = 0;
                        tekrarSayisi = 0;
                    }
                    break;
            }
            sinyalDurumu = 0;
        }
    }
}
