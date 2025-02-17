// S103 - Sesli çalar saat

int alarm_saat_buton = 2;    //Alarm saatinin ayarlanacağı butonun bağlandığı pini tanımla
int alarm_dakika_buton = 3;  //Alarm dakikasının ayarlanacağı butonun bağlandığı pini tanımla

void setup()
{
    Serial.begin(9600);                    //Seri haberleşme başlatıldı

    pinMode(alarm_saat_buton, INPUT);      //Alarm saatinin ayarlanacağı butonun bağlandığı pini giriş olarak tanımla
    pinMode(alarm_dakika_buton, INPUT);    //Alarm dakikasının ayarlanacağı butonun bağlandığı pini giriş olarak tanımla
}

void loop()
{
    if (digitalRead(alarm_saat_buton) == HIGH)    //Eğer alarm saatinin ayarlanacağı butona basıldı ise 
    {
        Serial.println(1);                        //Seri ekrana 1 değerini gönder 
        delay(100);                              //100 ms bekle 
    } 
    else                                         //Butona basılmadığı durumda 
    {
        Serial.println(0);                       //Seri ekrana 0 değerini gönder 
        delay(100);                              //100 ms bekle 
    }
  
    if (digitalRead(alarm_dakika_buton) == HIGH)  //Eğer alarm dakikasının ayarlanacağı butona basıldı ise 
    {
        Serial.println(2);                        //Seri ekrana 2 değerini gönder 
        delay(100);                              //100 ms bekle 
    }
    else                                         //Butona basılmadığı durumda 
    {
        Serial.println(0);                       //Seri ekrana 0 değerini gönder 
        delay(100);                              //100 ms bekle 
    }
}
