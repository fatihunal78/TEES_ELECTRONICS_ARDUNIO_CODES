// S37 - Saksı Nem Alarmı

int YesilLed = 8;      // Yeşil LED'in bağlandığı dijital pin numarasını tanımla
int algilayiciPin = 2; // Nem algılayıcının bağlandığı pin numarasını tanımla
int hoparlorPin = 4;   // Hoparlörün bağlandığı pin numarasını tanımla
int saksiNemDurumu = 0;// Nem algılayıcının durumunun tutulacağı değişkeni tanımla

// Nem seviyesi az olduğunda müzik çalacak. Bu müzikte kullanılacak notalar
int la, si, re, reDiyez, mi, fa, sol;

int notaSuresi;        // Nota çalma süresi değişkeni tanımlandı

void setup() {
    pinMode(YesilLed, OUTPUT);      // LED'in bağlandığı pini çıkış olarak ayarla
    pinMode(hoparlorPin, OUTPUT);   // Hoparlörün bağlandığı pini çıkış olarak ayarla   
    pinMode(algilayiciPin, INPUT);  // Nem algılayıcının bağlandığı pini giriş olarak ayarla
  
    // Notalara karşılık gelen frekans değerleri
    la = 440;
    si = 494;
    re = 587;
    reDiyez = 622;
    mi = 659;
    fa = 698;
    sol = 784;
    notaSuresi = 110;              // Nota çalma süresini ayarla
}

void loop() {
    // Nem algılayıcının durumunu sorgula ve değişkene ata
    saksiNemDurumu = digitalRead(algilayiciPin);
    
    // Saksı nem durumunu kontrol et
    if(saksiNemDurumu == LOW) {    // Saksı nemi az ise
        digitalWrite(YesilLed, LOW);// Yeşil LED'i söndür 
        
        // Müzik çal
        tone(hoparlorPin, re);
        delay(2*notaSuresi);
        tone(hoparlorPin, mi);
        delay(2*notaSuresi);
        tone(hoparlorPin, mi);
        delay(4*notaSuresi);
        tone(hoparlorPin, reDiyez);
        delay(2*notaSuresi);
        tone(hoparlorPin, sol);
        delay(2*notaSuresi);
        tone(hoparlorPin, fa);
        delay(2*notaSuresi);
        tone(hoparlorPin, mi);
        delay(4*notaSuresi);
        noTone(hoparlorPin);
        delay(2*notaSuresi);
        tone(hoparlorPin, sol);
        delay(2*notaSuresi);
        tone(hoparlorPin, la);
        delay(2*notaSuresi);
        tone(hoparlorPin, si);
        delay(4*notaSuresi);
        tone(hoparlorPin, si);
        delay(2*notaSuresi);
        tone(hoparlorPin, si);
        delay(2*notaSuresi);
        tone(hoparlorPin, la);
        delay(2*notaSuresi);
        tone(hoparlorPin, si);
        delay(4*notaSuresi);
    }
    else {                         // Saksı nemi yeterli ise
        noTone(hoparlorPin);      // Hoparlörü sustur
        digitalWrite(YesilLed, HIGH);// Yeşil LED'i yak
    }
}
