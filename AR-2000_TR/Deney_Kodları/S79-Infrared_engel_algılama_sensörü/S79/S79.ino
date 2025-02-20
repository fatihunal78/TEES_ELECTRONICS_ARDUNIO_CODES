// S79 - Infrared engel algılama sensörü

int SensorPin = 4;    //Sensörün bağlandığı pin numarasını tanımla
int ledPin = 8;       //LED'in bağlandığı pin numarasını tanımla

void setup()
{
    pinMode(SensorPin, INPUT);     //Sensörün bağlandığı pini giriş olarak ayarla 
    pinMode(ledPin, OUTPUT);       //LED'in bağlandığı pini çıkış olarak ayarla 
}
   
void loop()
{
    if (digitalRead(SensorPin) == LOW)    //Sensorün bağlandığı pindeki değeri oku 
                                         //Eğer okunan değer 0 ise yani sensör önüne engel geldiyse
    {
        digitalWrite(ledPin, HIGH);       //LED'i yak 
    }
    else                                 //Eğer okunan değer 1 ise, sensör önünde engel yok ise 
    {
        digitalWrite(ledPin, LOW);        //LED'i söndür
    }
    delay(300);                          //300 ms bekle 
}