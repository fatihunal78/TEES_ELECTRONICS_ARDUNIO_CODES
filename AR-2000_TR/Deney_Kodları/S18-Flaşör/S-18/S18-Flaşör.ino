// S18 - Flaşör

int ledPin = 2;      // LED'in bağlandığı pin numarası tanımlandı
int potPin = A0;     // Potansiyometrenin bağlandığı pin numarası tanımlandı  
int gecikme;         // Oranlanacak değerin tutulacağı değişken tanımlandı

int okunanDeger;     // Potansiyometreden okunan değeri tutacak değişken tanımlandı

void setup() {
    pinMode(ledPin, OUTPUT);    // LED çıkış olarak ayarlandı
}

void loop() {
    okunanDeger = analogRead(potPin);    // Potansiyometreden değer okundu ve okunanDeger değişkenine kaydedildi
    
    gecikme = map(okunanDeger, 0, 1023, 1000, 100);    // Potansiyometreden okunan 0 ile 1023 arasındaki değer
                                                       // LED'in gecikme yapması için 1000 ile 100 ms arasında 
                                                       // oranlandı
    
    digitalWrite(ledPin, HIGH);    // LED'i yak
    delay(gecikme);               // Oranlanan değer kadar gecikme yap
    
    digitalWrite(ledPin, LOW);     // LED'i söndür  
    delay(gecikme);               // Oranlanan değer kadar gecikme yap
}
