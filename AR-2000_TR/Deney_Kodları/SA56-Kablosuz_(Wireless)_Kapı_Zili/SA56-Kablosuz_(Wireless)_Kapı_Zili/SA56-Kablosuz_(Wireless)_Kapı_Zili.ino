// SA56 - Kablosuz (Wireless) Kapı Zili

int sensorPin = A5;     // Kızılötesi sensörün bağlandığı pini tanımla
int hoparlorPin = 3;    // Hoparlörün bağlandığı pini tanımla

int okunanDeger;        // ADC den okunan değerin kaydedileceği değişkeni tanımla
int ortalamaDeger;      // ADC den okunan 10 değerin ortalamasının tutulacağı değişkeni tanımla

// Notalara karışık gelen frekans değerlerini tanımla
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

// Sırası ile çalınacak notaları dizi şeklinde tanımla
int melodi_notalar[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// Notlara arasındaki bekleme süresini tanımla
// 4= çeyrek vuruş(nota), 8= sekizlik nota gibi 
int nota_vurus[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
    pinMode(sensorPin, INPUT);     // Kızılötesi sensörün bağlandığı pini giriş olarak ayarla
    pinMode(hoparlorPin, OUTPUT);  // Hoparlörün bağlandığı pini çıkış olarak ayarla

    for(int i = 0; i < 10; i++) {  // ADC'den başlangıçta 10 adet değer almak için 0 dan 10 a kadar 
        okunanDeger = analogRead(sensorPin);           // okunanDeger değişkenine ADC'den okunan değerleri kaydet
        ortalamaDeger = ortalamaDeger + okunanDeger;  // Her seferinden bir önceki değeri ile okunanDeger değişkenini 
                                                      // kaydet. Ortalamasını almak için bütün değerler toplamı / 10 
                                                      // olarak hesapla
        delay(50);                                    // 50 ms bekle
    }
    ortalamaDeger = ortalamaDeger / 10;              // Ölçülen 10 değerin ortalamasını al 
}

void loop() {
    // Analog pindeki sensör değeri kalibrasyon kısmındaki ortalamaDegerin 600 fazlası ise yada analog pinden 
    // okunan değer 1000 den büyük ise yani ortalama değer harici bir etken (butonun basılma durumu) sensörü 
    // tetikliyor ise kapı zili müziğini çal 
    if (analogRead(sensorPin) >= ortalamaDeger + 600 || analogRead(sensorPin) >= 1000) {
        // 7 adet nota olduğu için 0'dan 7'e bir for döngüsü oluştur. Bu döngü ile notaları tek tek çaldır
        for (int nota = 0; nota < 8; nota++) {
            // Nota süresini hesaplamak için, bir saniyeyi (1000 ms) referans olarak alın. O notaya karşılık 
            // gelen vuruş miktarı ile bu süreyi bölün. Örneğin NOTE_C4 notası ilk başta calacak ve vuruş 
            // miktarı 4. Bu notanın çalma süresi 1000/4 = 250 ms olacak demektir. Yada başka bir nota için 
            // 1000/8=125 ms 
            int notaSuresi = 1000 / nota_vurus[nota];
            tone(hoparlorPin, melodi_notalar[nota], notaSuresi);
  
            // Notalar arasındaki bekleme süresi notasüresinin %30 fazlası kadardır.
            // Bu süre her müziğe göre değişebilir.
            // Kulağa hoş gelen değer ne ise o ayarlanmalıdır.     
            int nota_bekleme_suresi = notaSuresi * 1.30;
            delay(nota_bekleme_suresi);
      
            noTone(hoparlorPin);  // Müziği sustur.
        }
    }
}
