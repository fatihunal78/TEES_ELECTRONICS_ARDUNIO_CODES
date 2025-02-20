// S57 - Hırsız Alarmı Düzeneği

int //kirmiziLedPin = 8;    // Kırmızı LED'in bağlandığı pini tanımla
int yesilLedPin = 9;      // Yeşil LED'in bağlandığı pini tanımla

int kapiPin = 3;          // Kapı kontağının bağlandığı pin numarasını tanımla
int butonPin = 2;         // Alarm resetleme butonunun bağlandığı pin numarasını tanımla  
int hoparlorPin = 4;      // Hoparlörün bağlandığı pin numarasını tanımla
int kapiDurumu = 0;       // Kapı kontağının durumunun tutulacağı değişkeni tanımla
int alarmDurumu = 0;      // Alarm durumunun tutulacağı değişkeni tanımla

void setup() {
    pinMode(kirmiziLedPin, OUTPUT);    // LED'lerin bağlandığı pini çıkış olarak ayarla
    pinMode(yesilLedPin, OUTPUT);      
    pinMode(hoparlorPin, OUTPUT);      // Hoparlörün bağlandığı pini çıkış olarak ayarla  
    pinMode(butonPin, INPUT);          // Resetleme butonunun bağlandığı pini giriş olarak ayarla   
    pinMode(kapiPin, INPUT);           // Kapı kontağının bağlandığı pini giriş olarak ayarla
}

void loop() {
    kapiDurumu = digitalRead(kapiPin); // Kapı kontağı durumunu sorgula ve değişkene ata

    // Kapı kontağının durumunu kontrol et
    if(kapiDurumu == LOW && alarmDurumu == 1) {  // Kapı kontağı açık ise
        // Kapı kontağı kapatılsa bile alarm susmaz. Kapı kontağı kapatılıp alarm susturma butonuna basılırsa 
        // alarm susar. Alarm susturulana kadar while döngüsünde kalır.
        while(1) {
            digitalWrite(kirmiziLedPin, HIGH);    // Kırmızı LED'i yak
            
            tone(hoparlorPin, 380);              // Hoparlörü aktif et
            delay(250);                          // 250ms bekle
            
            digitalWrite(kirmiziLedPin, LOW);     // Kırmızı LED'i söndür
            
            noTone(hoparlorPin);                 // Hoparlörü sustur
            delay(250);                          // 250ms bekle
            
            if(digitalRead(butonPin) == HIGH) {   // Alarm resetleme butonuna basıldı ise
                digitalWrite(yesilLedPin, LOW);    // Yeşil LED'i söndür
                while(digitalRead(butonPin) == HIGH);  // Butona basılı olduğu sürece bekle
                break;                            // Sonsuz döngüden çık alarmı devre dışı bırak
            }
        }

        while(1) {                               // Alarm kapalı şekilde bekliyor
            if(digitalRead(butonPin) == HIGH) {   // Eğer butona basıldı ise
                digitalWrite(yesilLedPin, HIGH);   // Yeşil LED'i yak
                while(digitalRead(butonPin) == HIGH);  // Butona basılı olduğu sürece bekle
                break;                            // Sonsuz döngüden çık ve alarmı kur
            }
        }
    }
    else {
        if(digitalRead(butonPin) == HIGH) {      // Eğer butona basıldı ise
            if(alarmDurumu == 0) {
                digitalWrite(yesilLedPin, HIGH);   // Yeşil LED'i yak
                alarmDurumu = 1;                  // AlarmDurumu değişkenini 1 yap, alarmın aktif olduğunu belirt
                while(digitalRead(butonPin) == HIGH);  // Butona basılı olduğu sürece bekle
            }
            else {
                digitalWrite(yesilLedPin, LOW);    // Yeşil LED'i söndür
                alarmDurumu = 0;                  // AlarmDurumu değişkenini 0 yap, alarmın pasif olduğunu belirt
                while(digitalRead(butonPin) == HIGH);  // Butona basılı olduğu sürece bekle
            }
        }
    }
}
