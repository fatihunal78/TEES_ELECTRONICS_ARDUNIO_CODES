// S80 - Kızılötesi (Infrared) kasa alarmı

int SensorPin  = 4;    //Sensörün bağlandığı pin numarasını tanımla
int buzzerPin  = 11;   //Buzzerın bağlandığı pin numarasını tanımla
int kirmiziLed = 5;    //Kırmızı LED'in bağlandığı pin numarasını tanımla  

void setup() 
{
    pinMode(SensorPin, INPUT);    //Sensörün bağlandığı pini giriş olarak ayarla 
    pinMode(buzzerPin, OUTPUT);   //Buzzerın bağlandığı pini çıkış olarak ayarla 
    pinMode(kirmiziLed, OUTPUT);  //Kırmızı LED'in bağlandığı pini çıkış olarak ayarla 
}
   
void loop() 
{
    bool val = digitalRead(SensorPin);  //Sensör pinindeki değeri oku    
  
    if (val == HIGH)                    //Eğer okunan değer 1 ise eğer kapak açık ise 
    {
        digitalWrite(kirmiziLed, HIGH);  //Kırmızı LED'i yak
        digitalWrite(buzzerPin, HIGH);   //Buzzerdan ses çıkar
        delay(200);                      //200 ms bekle
        digitalWrite(kirmiziLed, LOW);   //Kırmızı LED'i söndür
        digitalWrite(buzzerPin, LOW);    //Buzzerı sustur
        delay(200);                      //200 ms bekle
    }
    else                                //Eğer okunan değer 0 ise eğer kapak kapalı ise
    {
        digitalWrite(kirmiziLed, LOW);   //Kırmızı LED'i söndür
        digitalWrite(buzzerPin, LOW);    //Buzzerı sustur
    }
}
