// S17 - Ayarlanabilir Ton Üretici

int hoparlorPin = 3;    // Hoparlör 3 numaralı pine bağlandığı tanımlandı
int oranla;             // Oranla isimli değişken oluşturuldu  
int potPin = A0;        // Potansiyometrenin bağlandığı pin Analog 0 pin olarak tanımlandı
int potDegeri;          // Potansiyometrenin değerinin tutulacağı değişken tanımlandı

void setup() {
    pinMode(hoparlorPin, OUTPUT);    // Hoparlör çıkış olarak ayarlandı 
    Serial.begin(9600);              // Seri haberleşme başlatıldı
                                    // Seri port ekranında sağ alt köşede 9600 seçilmeli 
}

void loop() {
    potDegeri = analogRead(potPin);                  // Potansiyometreden değer oku ve potDegeri değişkenine kaydet 
    oranla = map(potDegeri, 0, 1023, 0, 2000);      // Potansiyometreden okunan 0 ile 1023 arsındaki değerleri 
                                                    // 0 ile 2000 arasında oranla 

    // tone() fonksiyonu Arduino dijital pinleri yardımı ile sesler oluşturmanıza yarayan araçtır 
    // tone(pin_numarası,ses_frekans_degeri) şeklinde kullanabilirsiniz
    // tone fonksiyonu ile projelerinizde uygun sesler oluşturabilirsiniz
    tone(hoparlorPin, oranla);       // Oranlanmış değeri hoparlöre aktar
    delay(100);                      // 100 ms bekle
    noTone(hoparlorPin);             // Hoparlörü sustur
    delay(100);                      // 100 ms bekle 

    Serial.print("Frekans Degeri: ");
    Serial.print(oranla);            // Oranla değişkeninde tutulan değeri seri ekrana yazdır
    Serial.println(" Hz (Hertz)");

    while(oranla <= 20) {            // Oranla değeri 20'den küçük olduğu sürece hoparlörü sustur
        noTone(hoparlorPin);         // Hoparlörü sustur
        potDegeri = analogRead(potPin);              // Potansiyometreden değer oku 
        oranla = map(potDegeri, 0, 1023, 0, 2000);  // Potansiyometreden okunan değeri oranla  
    }
}
