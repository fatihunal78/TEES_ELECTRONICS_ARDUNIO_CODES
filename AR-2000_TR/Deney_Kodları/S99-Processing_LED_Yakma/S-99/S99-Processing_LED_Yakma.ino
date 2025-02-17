// S99 - Processing LED Yakma

int ledPin = 5;                    // LED'in bağlandığı pin numarasını tanımla
char Processing_LED_Durumu;        // Processingden 1 ya da 0 gelecek olan değerin kaydedileceği değişkeni tanımla

void setup() { 
    pinMode(ledPin, OUTPUT);       // LED'in bağlandığı pini çıkış olarak ayarla
    Serial.begin(9600);           // Processing ile haberleşme için seri iletişimi başlat 
}

void loop() {
    if (Serial.available() > 0) {  // Eğer seri haberleşme portundan gelen bilgi varsa
        Processing_LED_Durumu = Serial.read();  // Processing_LED_Durumu değişkenine seri porttan okunan değeri kaydet
        
        if (Processing_LED_Durumu == '1') {     // Eğer seri porttan okunan değer 1 ise, yani Processingde beyaz zemin 
                                               // üzerine farenin sol tuşu ile basıldı ise 
            digitalWrite(ledPin, HIGH);         // LED'i yak 
        } 
        
        if (Processing_LED_Durumu == '0') {     // Eğer seri porttan okunan değer 0 ise, yani Processingde sarı zemin 
                                               // üzerine farenin sağ tuşu ile basıldı ise 
            digitalWrite(ledPin, LOW);          // LED'i söndür 
        }
    }
}
