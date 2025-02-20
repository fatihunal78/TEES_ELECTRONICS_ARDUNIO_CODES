// S70 - İstiklal Marşı

const int hoparlorPin = 3;     // Hoparlör bağlandığı pini tanımla
int butonPin = 2;              // Butonun bağlandığı pini tanımla
                              // LED'lerin bağlandığı pinleri tanımla
int kirmiziLed = 6;

int beyazLed = 7;

// Kullanılacak notaları tanımla
int a, ad, b, c, cd, d, dd, e, f, fd, g, gd, a2, ad2, b2, c2, cd2, d2, dd2, e2, f2, fd2, g2, gd2, a3;

void setup() {  
    pinMode(hoparlorPin, OUTPUT);  // Hoparlörün bağlandığı pini çıkış olarak ayarla 
    pinMode(kirmiziLed, OUTPUT);   // Kırmızı LED'in bağlandığı pini çıkış olarak ayarla 
    pinMode(beyazLed, OUTPUT);     // Beyaz LED'in bağlandığı pini çıkış olarak ayarla 
    pinMode(butonPin, INPUT);      // Butonun bağlandığı pini giriş olarak ayarla 

    // c  = do
    // cd = do diyez
    // d  = re
    // dd = re diyez
    // e  = mi
    // f  = fa
    // fd = fa diyez
    // g  = sol
    // gd = sol diyez
    // a  = la
    // ad = la diyez
    // b  = si
  
    // Notalara karşılık gelen frekans değerleri
    a = 440;
    ad = 466;
    b = 494;
    c = 523;
    cd = 554;
    d = 587;
    dd = 622;
    e = 659;
    f = 698;
    fd = 740;
    g = 784;
    gd = 830;
    a2 = 880;
    ad2 = 932;
    b2 = 988;
    c2 = 1046;
    cd2 = 1108;
    d2 = 1174;
    dd2 = 1244;
    e2 = 1318;
    f2 = 1396;
    fd2 = 1480;
    g2 = 1568;
    gd2 = 1660;
    a3 = 1760;
}  

void loop() {  
    if (digitalRead(butonPin) == HIGH) {    // Eğer butona basıldı ise 
        while(1) {
            // Korkma Sönmez Bu Şafak  
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800); 
         
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
      
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
      
            tone(hoparlorPin, gd);    
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
      
            tone(hoparlorPin, e);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
      
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
      
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(1600);   
           
            noTone(hoparlorPin);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(300);
      
            // Larda Yüzden Al Sancak
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);        
  
            tone(hoparlorPin, ad2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);        
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);        
  
            tone(hoparlorPin, cd2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, a2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, ad2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(1600);        
  
            // Sönmeden Yurdumun Üstünde Tüten En Son Ocak O Be
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, ad2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);        
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            noTone(hoparlorPin);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(100);  
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);  
            delay(400);   
  
            tone(hoparlorPin, e);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);   
      
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, cd2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, dd2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, f2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, dd2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);     
  
            // Nim Milletimin
            tone(hoparlorPin, dd);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, d);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, dd);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(1600);
  
            // Yıldızıdır Parlayacak O Benim
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);  
            delay(200);
  
            tone(hoparlorPin, b);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(400);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            // Dir O Benim Milletimindir Ancak
            tone(hoparlorPin, f2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, dd2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, cd2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(1600);
  
            // *** İkinci Kıta ***
            // Çatma Kurban Olayım
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
      
            tone(hoparlorPin, e);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(400);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);        
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(1600);        
  
            noTone(hoparlorPin);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(300);
  
            // Çehreni Ey Nazlı Hilal
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);        
  
            tone(hoparlorPin, ad2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);        
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);        
  
            tone(hoparlorPin, cd2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, ad2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(400);
  
            tone(hoparlorPin, a2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(400);
  
            tone(hoparlorPin, ad2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);        
  
            // Kahraman Irkıma Bir Gül Ne Bu Şiddet Bu Celal Sana
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, ad2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);        
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            noTone(hoparlorPin);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(100);  
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);   
  
            tone(hoparlorPin, e);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);   
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, cd2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, dd2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);        
  
            tone(hoparlorPin, f2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);        
  
            tone(hoparlorPin, dd2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);     
  
            // Olmaz Dökülen
            tone(hoparlorPin, dd);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, d);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, dd);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(1600);
  
            // Kanlarımız Sonra Helal Hakkıdır
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, b);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(400);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(200);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            // Hakk'a Tapan Milletimin İstiklal
            tone(hoparlorPin, f2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(800);
  
            tone(hoparlorPin, dd2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, cd2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, ad);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, gd);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, g);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(200);
  
            tone(hoparlorPin, c2);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(400);
  
            tone(hoparlorPin, c);
            digitalWrite(kirmiziLed, LOW);
            digitalWrite(beyazLed, HIGH);
            delay(800);
  
            tone(hoparlorPin, f);
            digitalWrite(kirmiziLed, HIGH);
            digitalWrite(beyazLed, LOW);
            delay(1600);
            break;
        }
    }
    // Söz    : Mehmet Akif Ersoy
    // Beste  : Osman Zeki Üngör
    else {
        noTone(hoparlorPin);
        delay(300);
    }
}
