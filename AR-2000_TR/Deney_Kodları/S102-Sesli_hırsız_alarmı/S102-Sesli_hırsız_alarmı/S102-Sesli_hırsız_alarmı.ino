// S102 - Sesli hırsız alarmı

// LED'lerin bağlandığı dijital pin numarasını tanımla
int kirmiziLedPin = 6;
int yesilLedPin  = 7;

int kapiPin     = 3;     // Kapı kontağının bağlandığı pin numarasını tanımla
int butonPin    = 2;     // Alarm resetleme butonunun bağlandığı pin numarasını tanımla
int kapiDurumu  = 0;     // Kapı kontağının durumunun tutulacağı değişkeni tanımla
int alarmDurumu = 0;     // Alarm durumunun tutulacağı değişkeni tanımla

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(kirmiziLedPin, OUTPUT);
    pinMode(yesilLedPin, OUTPUT);
    // Resetleme butonunun bağlandığı pini giriş olarak ayarla, pull up direncini aktif et
    pinMode(butonPin, INPUT_PULLUP);
    pinMode(kapiPin, INPUT);         // Kapı kontağının bağlandığı pini giriş olarak ayarla
    Serial.begin(9600);
}

void loop() {
    // Kapı kontağı durumunu sorgula ve değişkene kaydet
    kapiDurumu = digitalRead(kapiPin);

    // Kapı kontağının durumunu kontrol et
    if (kapiDurumu == LOW && alarmDurumu == 1) {    // Kapı kontağı açık ise
        // Kapı kontağı kapatılsa bile alarm susmaz. Kapı kontağı kapatılıp alarm susturma butonuna basılırsa 
        // alarm susar. Alarm susturulana kadar while döngüsünde kalır
        while (1) {
            Serial.println(1);                   // Seri ekrana Alarm müziğinin çalması için 1 değerini gönder
            digitalWrite(yesilLedPin, LOW);      // Yeşil LED'i söndür
            digitalWrite(kirmiziLedPin, HIGH);   // Kırmızı LED'i yak
            delay(250);                         // 250ms bekle
            digitalWrite(kirmiziLedPin, LOW);    // Kırmızı LED'i söndür
            delay(250);                         // 250ms bekle

            if (digitalRead(butonPin) == LOW) {  // Alarm resetleme butonuna basıldı ise
                delay(500);                     // 500ms bekle
                Serial.println(0);              // Seri ekrana Alarm müziğinin susturulması için 0 değerini gönder
                digitalWrite(yesilLedPin, LOW);  // Yeşil LED'i söndür
                break;                          // Sonsuz döngüden çık alarmı devre dışı bırak
            }
        }

        while (1) {                            // Alarm kapalı şekilde bekliyor
            if (digitalRead(butonPin) == LOW) { // Eğer butona basıldı ise
                delay(500);                    // 500ms bekle
                digitalWrite(yesilLedPin, HIGH); // Yeşil LED'i yak
                Serial.println(0);             // Seri ekrana Alarm müziğinin susturulması için 0 değerini gönder
                break;                         // Sonsuz döngüden çık ve alarmı kur
            }
        }
    } else {
        if (digitalRead(butonPin) == LOW) {    // Eğer butona basıldı ise
            if (alarmDurumu == 0) {
                digitalWrite(yesilLedPin, HIGH); // Yeşil LED'i yak
                alarmDurumu = 1;               // Alarm durumunu açık olarak kaydet
            } else {
                digitalWrite(yesilLedPin, LOW);  // Yeşil LED'i söndür
                alarmDurumu = 0;               // Alarm durumunu kapalı olarak kaydet
            }
            delay(500);                        // 500ms bekle
        }
    }
}
