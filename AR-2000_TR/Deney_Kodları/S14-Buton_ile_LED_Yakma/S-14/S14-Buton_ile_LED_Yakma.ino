// S14 - Buton ile LED Yakma

/*
 * LED Yakma deneyindeki gibi LED'in ve Buton'un bağlı olduğu dijital pinlere isim verdik.
 * Bu isim vermeler biz programı yazarken buton ya da led hangi pine bağlıydı diye karıştırmamamızı sağlar.
 * int ledPin=3; ile 3 numaralı dijital pinin ismi ledPin oldu.
 * int butonPin=2; ile 2 numaralı dijital pinin ismi butonPin oldu.
 */
int ledPin = 3;      // LED'in bağlandığı dijital pin numarasını tanımla
int butonPin = 2;    // Buton'un bağlandığı dijital pin numarasını tanımla
int butonDurumu = 0; // Pin tanımlamasında yaptığımız ile benzer şekilde butonDurumu diye bir değişken oluşturduk
                     // ve butonDurumu değişkenini sıfıra eşitledik.
                     // Butona basılıp basılmadığı durumunu tutacağımız değişkeni tanımladık.

void setup() { 
    /*
     * LED Yakma deneyinde gördüğümüz üzere setup fonksiyonu altında tek seferlik olaylar yapılırdı.
     * Ve burada led, sensör veya butonun giriş çıkış ayarlamaları yapılır.
     * Ledimizi çıkış olarak ayarladık ve butonumuzu ise giriş olarak ayarladık.
     */
    pinMode(ledPin, OUTPUT);    // LED'in bağlandığı pini çıkış olarak ayarla  
    pinMode(butonPin, INPUT);   // Buton'un bağlandığı pini giriş olarak ayarla
}

void loop() {
    /*
     * digitalRead(pinNumarası); bu komut ile herhangi bir dijital pindeki değeri okur.
     * Montaj planındaki bağlantıları yaptığımız zaman, butona basıldığı taktirde butonPin yani 2 numaralı 
     * pinimiz HIGH olacaktır. 
     * Bu HIGH olma durumu butonDurumu değişkenine 1 olarak kaydedilecektir.
     * Yani işin özü butonun bağlandığı pindeki değeri digitalRead(butonPin) komutu ile kontrol et.
     * Eğer butona basıldı ise butonDurumu değişkenini 1 (HIGH) olarak kaydet
     * Butona basılmadığı durumlarda 0 (LOW) olarak kaydet
     */
    butonDurumu = digitalRead(butonPin);    // Buton durumunu sorgula ve butonDurumu değişkenine ata

    /*
     * if else döngüsü açıklamalarda anlattığımız gibi eğer şu olay oldu ise şunu yap olmadı ise şunu yap 
     * şeklinde tanımlanır.
     * Aşağıdaki örnekte butonDurumu değişkeni HIGH veya LOW yani butona basıldı mı yoksa basılmadı mı olayına 
     * göre değişir.
     * if(butonDurumu==HIGH) Eğer butona basıldı ise { süslü parantez içindeki işlemleri yap  
     * else if(butonDurumu==LOW) Eğer butona basılmadı ise { süslü parantez içindeki işlemleri yap 
     */
    if(butonDurumu == HIGH) {              // Eğer Butona basıldı ise
        digitalWrite(ledPin, HIGH);         // LED'i yak      
        delay(50);                         // 50ms(mili saniye) bekle   
    }
    else if(butonDurumu == LOW) {          // Eğer butona basılmadı ise 
        digitalWrite(ledPin, LOW);          // LED'i söndür      
        delay(50);                         // 50ms(mili saniye) bekle   
    }

    /*
     * ------ if else için örnek açıklama -----
     * 
     * Bir zar atıldığını düşünelim zarın 1-2 ve 3 gelme durumlarında led yansın diğer durumlarda led sönsün 
     * Zar atıldı ve zarın tutulacağı değişken zarDegeri olsun.
     * 
     * if(zarDegeri == 1) {                // Eğer zar değeri 1 ise 
     *     digitalWrite(ledPin, HIGH);      // Ledi yak 
     * }
     * else if(zarDegeri == 2) {           // Eğer zar değeri 2 ise  
     *     digitalWrite(ledPin, HIGH);      // Ledi yak 
     * }
     * else if(zarDegeri == 3) {           // Eğer zar değeri 3 ise 
     *     digitalWrite(ledPin, HIGH);      // Ledi yak 
     * }
     * else {                              // Eğer zar değeri üst taraftaki koşullar (1,2 ve 3) değil ise yani 4-5-6 ise 
     *     digitalWrite(ledPin, LOW);       // Ledi söndür 
     * }
     */
}
