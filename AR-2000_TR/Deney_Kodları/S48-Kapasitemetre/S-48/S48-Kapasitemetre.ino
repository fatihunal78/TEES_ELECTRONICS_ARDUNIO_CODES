// S48 - Kapasitemetre

// Şarj pinini tanımla
int sarjPin = 8;
// Deşarj pinini tanımla  
int desarjPin = 9;
// Kapasite üzerindeki voltajın ölçüleceği pini tanımla
int analogPin = A0;
// Butonun bağlandığı pini tanımla
int buttonPin = 2;
// Başlangıç, bitiş ve geçen zaman değişkenlerinin tutulacağı değişkeni tanımla
unsigned long baslangicZamani = 0;
unsigned long bitisZamani = 0;
unsigned long gecenZaman = 0;
// Voltaj değerinin tutulacağı değişkeni tanımla
float voltajDegeri = 3;
// Kapasite değerinin tutulacağı değişkeni tanımla
float kapasiteDegeri = 0.0;
// Ölçme fonksiyonunu tanımla
int olcum(void);

void setup() {
    Serial.begin(9600);
    Serial.println("TEES ELEKTRONIK ");
    Serial.println("KAPASITEMETRE ");
    Serial.println("OLCMEK ISTEDIGINIZ KAPASITEYI TAKIN ");
    Serial.println("----------------------------------- ");
    delay(3000);                      // 3 saniye bekle
    pinMode(desarjPin, INPUT);        // Deşarj pinini giriş olarak ayarla
    pinMode(sarjPin, OUTPUT);         // Şarj pinini çıkış olarak ayarla
    pinMode(buttonPin, INPUT);        // Buton pinini giriş olarak ayarla
    digitalWrite(sarjPin, HIGH);      // Şarj pinini aç
}

void loop() {
    // Deşarj et
    pinMode(sarjPin, INPUT);          // Şarj pinini giriş olarak tanımla
    pinMode(desarjPin, OUTPUT);       // Deşarj pinini çıkış olarak tanımla
    digitalWrite(desarjPin, LOW);     // Deşarj pinini kapat
    
    while(voltajDegeri > 2.0) {
        Serial.println("DESARJ OLUYOR...");
        voltajDegeri = olcum();       // Voltaj değerini ölç
        delay(100);
        kapasiteDegeri = voltajDegeri * (99.0 / 1023.0);
        Serial.print(99-kapasiteDegeri);   
        Serial.println("  %");
        delay(50);
    }
    
    delay(1000);    
    Serial.println("SARJ OLUYOR...");
  
    // Şarj et
    pinMode(desarjPin, INPUT);        // Deşarj pinini giriş olarak tanımla
    pinMode(sarjPin, OUTPUT);         // Şarj pinini çıkış olarak tanımla
    digitalWrite(sarjPin, HIGH);      // Şarj pinini aç
    baslangicZamani = micros();      // Başlangıç zamanını kaydet
    
    while(olcum() < 648) {           // Eğer olcum değeri 648'den küçük ise 
        Serial.print("%"); 
        Serial.println(olcum()*(100.0/1023.0), 1);  // Seri port ekranına yüzdelik değerleri yazdır
    }
    
    bitisZamani = micros();          // Bitiş zamanını kaydet
    gecenZaman = bitisZamani - baslangicZamani;  // Geçen zamanı hesapla
    kapasiteDegeri = gecenZaman / 10000;         // Kapasite değerini hesapla
    Serial.print(" ***             DEGER :");
    Serial.print(kapasiteDegeri);   
    Serial.println("  uF           ***"); 
    delay(3000);
    
    while(1) {
        // Deşarj et
        pinMode(sarjPin, INPUT);      // Şarj pinini giriş olarak tanımla
        pinMode(desarjPin, OUTPUT);   // Deşarj pinini çıkış olarak tanımla
        digitalWrite(desarjPin, LOW); // Deşarj pinini kapat
        delay(1500);
        
        // Şarj et
        pinMode(desarjPin, INPUT);    // Deşarj pinini giriş olarak tanımla
        pinMode(sarjPin, OUTPUT);     // Şarj pinini çıkış olarak tanımla
        digitalWrite(sarjPin, HIGH);  // Şarj pinini aç
        break;      
    }
}

// Ölçüm fonksiyonunu tanımla
int olcum(void) {
    int deger;
    deger = analogRead(analogPin);
    return deger;
}
