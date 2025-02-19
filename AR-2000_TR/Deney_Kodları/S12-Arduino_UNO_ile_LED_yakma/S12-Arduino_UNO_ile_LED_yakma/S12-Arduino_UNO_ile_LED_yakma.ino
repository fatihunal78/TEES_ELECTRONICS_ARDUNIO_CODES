//S12 - Arduino UNO ile LED yakma

/* Herhangi bir dijital pine bağlantı yapıldığında, pine bağlı olan sensör, buton veya led'e isim vermek için 
 * int ledPin=3;  komutu kullanılır. Bu komut 3 numaralı pinin isminin ledPin olarak değiştirdiğimizi belirtir.
 * Bu tanımlamayı yaptıktan sonra ledi söndürüp, yakmak için ledPin isminden faydalanacağız. 
 */
int ledPin = 3;    //LED'in bağlandığı dijital pin numarasını tanımla. Artık 3 numaralı pinin ismi ledPin oldu.

/* void setup() bu döngü sadece bir kere döner ve gerekli tanımlamlar burada yapılır. 
 * Ledimizin, sensörümüzün ya da butonumuzun giriş ya da çıkış olarak ayarlamaları bu kısımda yapılır.
 * Setup fonksiyonu, kod çalışmaya başladığında Arduino'nun ilk olarak okuduğu yerdir. 
 * Arduino bu kısmı okuduktan sonra diğer kısımları okumaya başlar. 
 * Bu kısım sadece bir kere okunur ve program esnasında yeniden okunmaz. 
 * Bu alanda, pinlerin çalışma modları gibi önemli ve bir kere yapılması yeterli olacak ayarlamalar yapılır.
 */
void setup() {  
    /* Üst tarafta ismini değiştirdiğimiz dijital pini giriş yada çıkış olarak ayarlamak için 
     * pinMode(pinNumarası, durum); komutunu kullanırız.
     * Burada pinNumarası led'in bağlandığı pin numarasını belirtir. Yani bu örnekte pinNumarası yerine 3 
     * veya ledPin yazabiliriz
     * durum ise bağlanan ledin,butonun veya sensörün giriş olarak mı çıkış olarak mı kullanılacağını gösterir.
     * Bu örneğimizde ledimizi çıkış olarak kullanacağımız için OUTPUT olarak ayarladık. 
     *  
     * pinMode(ledPin,OUTPUT);
     * pinMode(3,OUTPUT);
     * Bu şekilde yazılan komutlarda 3 numaralı pinin yani ledPin isimli pinin çıkış olarak ayarlandığını gösterdik.
     */
    pinMode(ledPin, OUTPUT);    //LED'in bağlandığı pini çıkış olarak ayarla
}

/* Loop fonksiyonu, setup fonksiyonu okunduktan sonra okunur. 
 * Bu bir ana fonksiyondur ve yapılmasını istediğiniz görevler buraya yazılır. 
 * Loop fonksiyonu, sonsuz döngü şeklindedir, yani buradaki görevler tamamlandığında, program tekrar başa dönerek
 * işlemleri yeniden yapar. 
 * Bu döngü, Arduino çalıştığı sürece devam eder.
 * Sonsuz bir döngüdür. Program akışı yukarıdan aşağıya süreki olarak loop içinde tanımlananları yapacaktır.
 */
void loop() {  
    /* digitalWrite(pinNumarası, durum); bu komut sayesinde bir pine enerji verebilir yada enerjisini kesebiliriz.
     * pinNumarası ledin bağlandığı dijital pini ya da ona atanan ismi temsil etmektedir.
     * durum ise belirtilen dijital pinin HIGH ( +5V) yada LOW (0V) olarak ayarlamamızı sağlar.
     */
    digitalWrite(ledPin, HIGH);    // Ledin bağlı olduğu 3 numaralı pin daha önce tanımladığımız ledPin ismi ile 
                                  // çağırdık ve durumunun HIGH yani yanık olarak ayarladık. Ledi yaktık
                                  
    /* 3 numaralı pine bağlı ledPin isimli LED'imiz Arduino enerjili olduğu sürece sürekli yanık olacaktır.
     * loop döngüsünde olduğumuz için bu işlem sürekli tekrar edecektir.
     * Eğer digitalWrite(ledPin, LOW) komutu gönderirseniz led sönecektir.
     */            
}
