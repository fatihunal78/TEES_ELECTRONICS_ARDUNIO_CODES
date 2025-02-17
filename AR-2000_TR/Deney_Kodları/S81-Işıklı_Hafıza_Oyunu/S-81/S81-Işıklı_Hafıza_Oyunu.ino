// S81 - Işıklı Hafıza Oyunu

const int Maksimum_Seviye = 100;    // Oyunun maksimum seviyesini belirleyecek değişkeni tanımla ve maksimum seviyeyi 100 yap

int siralama[Maksimum_Seviye];      // Sıralamanın kaydedileceği dizi değişkenini maksimum seviye kadar elemanı olacak şekilde tanımla
                                    // 100 elemanlı bir dizi tanımla
int oyuncu_seviyesi[Maksimum_Seviye];   // Oyuncunun kaçıncı seviyede olduğunu tutacak değişkeni tanımla 
int seviye = 1;                     // Oyunun seviyesinin tutulacağı değişkeni tanımla ve ilk seviye değerini 1 olarak ayarla 
int oyun_hizi = 1000;               // Oyunun seviyesi yükseldikçe hızıda artacağından oyun_hizi değişkenini tanımla
                                    // oyun_hizi değişkeninin ilk değeri 1000 olarak ayarlandı

// LED'lerin bağlandığı pinleri tanımla
int kirmizi_ledPin = 13;
int yesil_ledPin = 12;
int buzzerPin = 9;                  // Buzzerin bağlandığı pin numarasını tanımla 

int kirmiziLed_buton = 2;          // Kırmızı LED'i kontrol edecek butonun bağlandığı pin numarasını tanımla
int yesilLed_buton = 3;            // Yeşil LED'i kontrol edecek butonun bağlandığı pin numarasını tanımla 

void setup()
{
    pinMode(kirmizi_ledPin, OUTPUT);    // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla 
    pinMode(yesil_ledPin, OUTPUT);      // Yeşil LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(buzzerPin, OUTPUT);         // Buzzerın bağlandığı pini çıkış olarak ayarla

    pinMode(kirmiziLed_buton, INPUT_PULLUP);    // Kırmızı LED'i kontrol edecek butonun bağlandığı pini giriş olarak tanımla 
                                                // ve pull up direncini aktif et 
    pinMode(yesilLed_buton, INPUT);             // Yeşil LED'i kontrol edecek butonun bağlandığı pini giriş olarak tanımla

    // Başlangıçta bütün LED'leri söndür ve Buzzer'ı sustur
    digitalWrite(kirmizi_ledPin, LOW); 
    digitalWrite(yesil_ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
}

void loop()
{
    if (seviye == 1)                                                  // Eğer oyunun seviyesi 1 ise (yani birinci seviyede)
        siralama_olustur();                                          // siralama_olustur() fonksiyonunu çağır

    if (digitalRead(kirmizi_ledPin) == LOW || seviye != 1)          // Eğer Kırmızı LED'i kontrol eden butona basıldıysa ya da 
                                                                    // oyun seviyesi 1'den farklı ise 
    {
        siralamayi_goster();                                        // siralamayi_goster() fonksiyonunu çağır
        siralamayi_arttir();                                       // siralamayi_arttir() fonksiyonuu çağır
    }
}

void siralamayi_goster()    // siralamayi_goster() fonksiyonunu oluştur 
{   
    // Bütün LED'leri söndür
    digitalWrite(kirmizi_ledPin, LOW); 
    digitalWrite(yesil_ledPin, LOW);

    for (int i = 0; i < seviye; i++)    // i değerini 0'dan oyununun seviyesine kadar birer arttır
    {
        digitalWrite(siralama[i], HIGH); // siralama değişeninin i. değerini HIGH yap 
        delay(oyun_hizi);               // oyun_hizi kadar gecikme koy
        digitalWrite(siralama[i], LOW);  // siralama değişeninin i. değerini LOW yap 
        delay(200);                      // 200 ms gecikme 
    }
}

void siralamayi_arttir()    // siralamayi_arttir() fonksiyonunu oluştur 
{
    int flag = 0;                       // flag değişkeni oluştur ve ilk değerini 0 yap 
    
    for (int i = 0; i < seviye; i++)    // i değerini 0'dan oyun seviyesine kadar birer arttır 
    {
        flag = 0;                       // flag değerini sıfır yap 

        while(flag == 0)                // flag değeri sıfır olduğu sürece 
        {
            if (digitalRead(kirmiziLed_buton) == LOW)     // Eğer Kırmızı LED'i kontrol eden butona basıldı ise 
            {
                digitalWrite(kirmizi_ledPin, HIGH);        // Kırmızı LED'i yak 
                while(digitalRead(kirmiziLed_buton) == LOW);   // Butona basılı olduğu sürece bekle
                oyuncu_seviyesi[i] = 13;                  // oyuncu_seviyesi değişkeninin i. değerine 13 değerini kaydet 
                flag = 1;                                 // flag değerini 1 yap 

                if (oyuncu_seviyesi[i] != siralama[i])    // Eğer oyuncu_seviyesinin i. değeri ve siralamanın i. değeri 
                                                         // aynı değil ise (Oyuncu yanlış butona bastıysa)
                {
                    kaybettiniz();                       // Oyun kaybedildiği için kaybettiniz() fonksiyonunu çağır
                    return; 
                }
                digitalWrite(kirmizi_ledPin, LOW);        // Kırmızı LED'i söndür 
            }

            if (digitalRead(yesilLed_buton) == HIGH)      // Eğer Yeşil LED'i kontrol eden butona basıldı ise 
            {
                digitalWrite(yesil_ledPin, HIGH);         // Yeşil LED'i yak 
                while(digitalRead(yesilLed_buton) == HIGH);   // Butona basılı olduğu sürece bekle
                oyuncu_seviyesi[i] = 12;                 // oyuncu_seviyesi değişkeninin i. değerine 12 değerini kaydet 
                flag = 1;                                // flag değerini 1 yap 

                if (oyuncu_seviyesi[i] != siralama[i])   // Eğer oyuncu_seviyesinin i. değeri ve siralamanın i. değeri 
                                                        // aynı değil ise (Oyuncu yanlış butona bastıysa)
                {
                    kaybettiniz();                      // Oyun kaybedildiği için kaybettiniz() fonksiyonunu çağır
                    return;
                }
                digitalWrite(yesil_ledPin, LOW);         // Yeşil LED'i söndür 
            }
        }
    }
    
    siralama_kontrol();                                 // siralama_kontrol() fonksiyonunu çağır 
}

void siralama_olustur()     // siralama_olustur() fonksiyonunu oluştur 
{
    randomSeed(millis());  

    for (int i = 0; i < Maksimum_Seviye; i++)          // i değerini sıfırdan maksimum seviyeye kadar birer arttır 
    { 
        siralama[i] = random(12, 14);                  // siralama değişkeninin i. değerine 12 ile 14 arasında rastgele 
                                                      // bir sayı ata
    }
}

void kaybettiniz()          // kaybettiniz() foksiyonunu oluştur 
{
    for (int i = 0; i < 3; i++)     // 3 kere döngü yap 
    { 
        // LED'leri üçer kere yak ve söndürme işlemi için aşağıdaki işlemleri yaptık
        // LED'leri yak ve buzzerdan ses çıkar          
        digitalWrite(kirmizi_ledPin, HIGH); 
        digitalWrite(yesil_ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        // LED'leri söndür ve buzzerı sustur
        digitalWrite(kirmizi_ledPin, LOW); 
        digitalWrite(yesil_ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(250);

        digitalWrite(kirmizi_ledPin, HIGH); 
        digitalWrite(yesil_ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        digitalWrite(kirmizi_ledPin, LOW); 
        digitalWrite(yesil_ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(250);

        digitalWrite(kirmizi_ledPin, HIGH); 
        digitalWrite(yesil_ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        digitalWrite(kirmizi_ledPin, LOW); 
        digitalWrite(yesil_ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(250);
    }

    seviye = 1;             // Seviye değerini 1'e eşitle 
    oyun_hizi = 1000;       // Oyun hızını 1000 yap 
}

void siralama_kontrol()     // siralama_kontrol() fonksiyonunu oluştur 
{
    digitalWrite(buzzerPin, LOW);     // Buzzerı sustur 
    delay(250);                       // 250 ms bekle 

    digitalWrite(buzzerPin, HIGH);    // Buzzerdan ses çıkar 
    delay(250);                       // 250 ms bekle 

    digitalWrite(buzzerPin, LOW);     // Buzzerı sustur 
    delay(500);                       // 500 ms bekle 

    if (seviye < Maksimum_Seviye)    // Eğer seviye maksimum seviyeden küçük ise 
        seviye++;                     // Seviye değişkenini bir arttır

    oyun_hizi -= 50;                 // oyun_hizi değişkenini 50 azalt
}
