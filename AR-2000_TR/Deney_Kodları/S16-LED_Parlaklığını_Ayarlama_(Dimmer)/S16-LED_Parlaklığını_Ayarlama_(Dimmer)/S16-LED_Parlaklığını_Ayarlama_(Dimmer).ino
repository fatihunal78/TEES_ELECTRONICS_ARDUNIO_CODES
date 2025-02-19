// S16 - LED Parlaklığını Ayarlama (Dimmer)

int ledPin = 3;      // LED'in bağlandığı dijital pin numarasını tanımla
                     // LED'in 3 numaralı pine bağlandığını belirttik
                

int potPin = A0;     // Potansiyometrenin bağlandığı analog pin numarasını tanımla
                     // Potansiyometrenin orta bacağının analog 0 (A0) pinine bağlandığını belirttik
                  
int parlaklik = 0;   // LED'in parlaklık değerini tutacağımız değişkeni tanımla
                     // Burada herhangi bir pin tanımlamadık sadece parlaklik isimli bir değişkenin ilk 
                     // değerini sıfıra eşitledik
                   
int potDegeri = 0;   // Potansiyometrenin değerini kaydedeceğimiz değişkeni tanımla
                     // Burada herhangi bir pin tanımlamadık sadece potDegeri isimli bir değişkenin ilk 
                     // değerini sıfıra eşitledik

void setup() {
    // Analog pinler giriş pini oldukları için setup altında herhangi bir tanımlama yapmanıza gerek yoktur.
    // Burada sadece ledimizi çıkış olarak ayarlayacağız 
    pinMode(ledPin, OUTPUT);    // LED'in bağlandığı pini çıkış olarak ayarla
}

void loop() {
    // Potansiyometreler ayarlı dirençlerdir. Çevirdiğiniz zaman direnç değeri artar veya azalır.
    // Bu artış veya azalışa göre analog pinde (A0 pini) voltaj değerlerinin dijital karşılıkları gösterilir.
    // Örneğin potansiyometre orta konumda iken analog pinden 5V'un yarısı kadar değer okur.
    // Okuduğu bu değer dijital sistemde 512 değerine karşılık gelmektedir. 
  
    potDegeri = analogRead(potPin);    // Potansiyometrenin değerini oku ve değişkene yaz. Potansiyometrenin 
                                      // 2 numaralı bacağındaki gerilime göre 0 ila 1023 arasında bir değer okur.
                                   
    // map fonksiyonu oranlama yaparak bir aralıktaki değişkeni başka bir aralığa oranlamaya yarayan bir araçtır
    // 0-1023 aralığında değişen bir sayıyı, 0-255 aralığında değişen bir sayıya oranlayabiliriz
    // yenidegisken = map(eskidegisken, 0, 1023, 0, 255); komutu ile bu işlemi yapabiliriz
    // LED parlaklığı 0-255 değerleri arasında ayarlanabilir. 0-1023 aralığında okunan değeri 
    // map fonksiyonu ile LED parlaklığının ayarlandığı 0-255 değerine getirir 
    // Örneğin okunan değer 1000 ise map fonksiyonu bunu 250 değerine çevirir
  
    parlaklik = map(potDegeri, 0, 1023, 0, 255);    // Yani potDegeri değişkeninden okuduğu 0 ile 1023 
                                                    // arasındaki değeri 0 ile 255 arasında oranla ve 
                                                    // parlaklik değişkenine kaydet

    /* analogWrite(pinNumarası,deger); komutu ile PWM sinyali üretebilir ve bu PWM sinyali ile ledin parlaklığını,
     * motorun dönüş hızını ve benzeri şeyleri kontrol edebiliriz.
     * PWM sinyali Arduino kodlamada önemli bir yere sahiptir.
     * analogWrite(pinNumarası,deger); Burada pinNumarası ledin bağlı olduğu pini temsil etmektedir ve deger 
     * değişkeni ise o pine ne kadar PWM sinyali gönderilmesi gerektiğini belirtmektedir.
     * Arduino üzerinde PWM çıkışı veren pinler: 3,5,6,9,10 ve 11 numaralı pinlerdir.
     */

    analogWrite(ledPin, parlaklik);    // Potansiyometreden okunan değeri map fonksiyonu ile oranlayıp parlaklik 
                                      // değişkenine kaydetmiştik. parlaklik değişkeninin sahip olduğu değeri 
                                      // ledPin pinine yani ledin bağlı olduğu 3 numaralı pine aktarır.
                                      // Bu parlaklik değişkeni potansiyometrenin çevrilmesine bağlı olarak 
                                      // 0 ile 255 arasında değiştiğinde ledin parlaklığı da değişecektir.
    delay(50);                        // 50ms bekle
}
