// S88 - Rüzgar Alarmı

int ruzgar_sensoru = 2;    // Rüzgar sensörünün bağlandığı pin numarasını tanımla
int hoparlorPin    = 4;    // Hoparlörün bağlandığı pin numarasını tanımla
int ledPin         = 7;    // LED'in bağlandığı pin numarasını tanımla 

void setup()
{
    pinMode(ruzgar_sensoru, INPUT);  // Rüzgar sensörünün bağlandığı pini giriş olarak ayarla
    pinMode(hoparlorPin, OUTPUT);    // Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(ledPin, OUTPUT);         // LED'in bağlandığı pini çıkış olarak ayarla
}

void loop()
{
    if (digitalRead(ruzgar_sensoru) == HIGH)  // Eğer rüzgar var ise 
    {    
        digitalWrite(ledPin, HIGH);  // LED'i yak 
        tone(hoparlorPin, 700);     // Hoparlörden ses çıkar
        delay(100);                 // 100ms bekle 
        noTone(hoparlorPin);        // Hoparlörü sustur
        digitalWrite(ledPin, LOW);   // LED'i söndür  
        delay(100);                 // 100ms bekle 
    }
    else                            // Eğer rüzgar yok ise 
    {
        noTone(hoparlorPin);        // Hoparlörü sustur 
        digitalWrite(ledPin, LOW);   // LED'i söndür
    }
}
