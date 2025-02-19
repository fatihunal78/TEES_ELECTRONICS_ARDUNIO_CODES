// SA99 - Sesli Yağmur Alarmı

int ledPin = 8;        // LED'in bağlandığı dijital pin numarasını tanımla
int sensorPin = 2;     // Nem sensörünün bağlandığı pin numarasını tanımla
int yagmurDurumu = 0;  // Nem sensörünün durumunun tutulacağı değişkeni tanımla

void setup()
{
    pinMode(ledPin, OUTPUT);    // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(sensorPin, INPUT);  // Nem sensörünün bağlandığı pini giriş olarak ayarla
    Serial.begin(9600);         // Seri haberleşmeyi başlat
}

void loop() 
{
    // Yağmur durumunu sorgula ve değişkene ata
    yagmurDurumu = digitalRead(sensorPin);

    // Yağmur durumunu kontrol et
    if (yagmurDurumu == HIGH)  // Yağmur yağıyor ise
    {
        // Processing'e yağmurun yağdığını bildirmek için 1 değerini gönder 
        Serial.println(1);
        
        // LED'i yakıp söndür
        digitalWrite(ledPin, HIGH);   
        delay(200);                   // 200ms bekle
        digitalWrite(ledPin, LOW);    // LED'i söndür
        delay(200);                   // 200ms bekle
    }
    else  // Yağmur yağmıyor ise
    {
        // LED'i söndür
        digitalWrite(ledPin, LOW);
        // Processing'e yağmurun yağmadığını bildirmek için 0 değerini gönder 
        Serial.println(0);
    }
}
