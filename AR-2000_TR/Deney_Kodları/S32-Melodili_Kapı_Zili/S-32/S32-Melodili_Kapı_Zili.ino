// S32 - Melodili Kapı Zili

int hoparlorPin = 3;    // Hoparlörün bağlandığı pin numarasını tanımla
int butonPin = 2;       // Butonun bağlandığı pin numarasını tanımla

// NOTALARA KARŞILIK GELEN FREKANS DEĞERLERİ 
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247

// Sırası ile çalınacak notaları dizi şeklinde yazıyoruz
int melodi_notalar[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// Notlar arasındaki bekleme süresini şu şekilde tanımlıyoruz:
// 4 = çeyrek vuruş(nota), 8 = sekizlik nota gibi
int nota_vurus[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
    pinMode(hoparlorPin, OUTPUT);    // Hoparlörü çıkış olarak ayarla
    pinMode(butonPin, INPUT);        // Butonu giriş olarak ayarla
}

void loop() {
    // Eğer butona basıldı ise zili çalmak için aşağıdaki işlemleri yap
    if (digitalRead(butonPin) == HIGH) {
        // 7 adet nota olduğu için 0'dan 7'e bir for döngüsü oluşturduk.
        // Bu döngü ile notaları tek tek çaldıracağız.
        for (int nota = 0; nota < 8; nota++) {
            // Nota süresini hesaplamak için, bir saniyeyi (1000 ms) referans olarak alın.
            // O notaya karşılık gelen vuruş miktarı ile bu süreyi bölün.
            // Örneğin NOTE_C4 notası ilk başta çalacak ve vuruş miktarı 4 olacaktır.
            // Bu notanın çalma süresi 1000/4 = 250 ms olacaktır.
            // Ya da başka bir nota için 1000/8 = 125 ms olacaktır.
            int notaSuresi = 1000 / nota_vurus[nota];
            
            tone(hoparlorPin, melodi_notalar[nota], notaSuresi);
     
            // Notalar arasındaki bekleme süresi nota süresinin %30 fazlası kadardır.
            // Bu süre her müziğe göre değişebilir.
            // Kulağa hoş gelen değer ne ise o ayarlanmalıdır.
            int nota_bekleme_suresi = notaSuresi * 1.30;
            delay(nota_bekleme_suresi);
              
            noTone(hoparlorPin);    // Müziği sustur
        }
    }
}
