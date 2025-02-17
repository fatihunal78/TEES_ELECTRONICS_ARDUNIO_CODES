// SA36 - Hareket Sensörlü Gece Lambası

int ledPin    = 3;    // LED'in bağlandığı pin numarasını tanımla
int sensorpin = 2;    // PIR sensörün bağlandığı pin numarasını tanımla
int LdrPin    = A5;   // LDR'nin bağlandığı pin numarasını tanımla

void setup()
{
    pinMode(ledPin, OUTPUT);    // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sensorpin, INPUT);  // PIR sensörün bağlandığı pini giriş olarak ayarla
    pinMode(LdrPin, INPUT);     // LDR'nin bağlandığı analog pini giriş olarak ayarla
}

void loop()
{
    if (analogRead(LdrPin) <= 400)                  // Eğer LDR'den okunan değer 400 den küçük ise yani hava karanlık ise
    {
        if (digitalRead(sensorpin) == HIGH)         // Eğer hareket algılandı ise
        {
            digitalWrite(ledPin, HIGH);             // LED'i yak
            delay(5000);                           // 5 saniye bekle
            digitalWrite(ledPin, LOW);             // LED'i söndür
        }
        else 
        {
            digitalWrite(ledPin, LOW);             // Eğer hareket algılanmadı ise LED'i söndür
        }
    }
    else 
    {
        digitalWrite(ledPin, LOW);                 // Eğer LDR'den okunan değer 400'den büyük ise yani hava aydınlık ise LED'i söndür
    }
}
