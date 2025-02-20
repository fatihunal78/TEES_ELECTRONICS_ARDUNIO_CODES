// S22 - Sokak Lambası

int lambaPin = 2;      // Sokak lambasının bağlandığı pin numarası tanımlandı
int ldrPin = A5;       // LDR'nin bağlandığı analog pin numarası tanımlandı 
int isik_degeri;       // Ölçülen ışık değerinin tutulacağı değişken tanımlandı
int lambaDurumu = 0;   // Lamba durumunun tutulacağı değişken tanımlandı

void setup() {
    pinMode(lambaPin, OUTPUT);    // Sokak lambasının bağlandığı pin çıkış pini olarak ayarlandı
    pinMode(ldrPin, INPUT);       // LDR'nin bağlandığı analog pin giriş pini olarak ayarlandı
}

void loop() {
    // Ölçülen ışık değerini analog pinden oku ve isik_degeri değişkenine ata.
    // Işık değeri 0-1023 değerleri arasında okunur. Değer karanlıkta düşük, aydınlıkta yüksek olur. 
    // 300 değerini istediğin aydınlık seviyesine göre değiştirebilirsin.
    
    isik_degeri = analogRead(ldrPin);  

    if (isik_degeri < 300) {          // Eğer LDR'den okunan değer 300'den düşük ise, yani hava karardı ise
        digitalWrite(lambaPin, HIGH);  // Lambayı yak
        lambaDurumu = 1;              // Lambayı açık olarak kaydet
    }
  
    if (lambaDurumu == 1) {           // Eğer lamba açık ise
        if (isik_degeri > 300) {      // Ortam ışık değeri yüksek ise 5sn bekle
            delay(5000);              // 5 saniye bekle
            if (isik_degeri > 300) {  // 5 saniye sonra ortam ışık değeri halen yüksek ise ışığı söndür
                digitalWrite(lambaPin, LOW);  // Lambayı söndür
                lambaDurumu = 0;             // Lambayı kapalı olarak kaydet
            }
        }
    }
}
