//S99 - Processing_Yagmur

import processing.serial.*;    // Arduino ile haberleşmek için seri haberleşme kütüphanesini ekle
import ddf.minim.*;           // Seslerin çalınması için minim kütüphanesini ekle 


Serial myPort;                // Serial porttan değerlerin okunması için myPort isimli bir obje oluştur 
Minim minim;                 // minim isimli bir obje oluştur 
AudioPlayer player;          // Seslerin kayıtlı tutulacağı bir obje oluştur 
AudioPlayer player2;         // Seslerin kayıtlı tutulacağı bir obje oluştur 
float gelen_data;            // Serial porttan okunacak değelerin tutulacağı değişken tanımlandı 

void setup() {
    minim = new Minim(this);                           // Minim için ayar yap 
    player = minim.loadFile("yagmur.mp3");            // Data dosyasında mevcut olan yagmur.mp3 isimli yağmur sesi 
                                                      // efektini player dosyasında tut 
    player2 = minim.loadFile("gokgurultusu.mp3");     // Data dosyasında mevcut olan gokgurultusu.mp3 isimli gök 
                                                      // gürültüsü sesi efektini player dosyasında tut 
    myPort = new Serial(this, "COM4", 9600);          // Arduino ile haberleşmede gerekli Port ve BoundRate 
                                                      // değerlerini gir. COM değerini kendi arduino'nuza göre 
                                                      // değiştirebilirsiniz

    myPort.bufferUntil('\n');                         // Arduino'dan gelen dataları satır bitene kadar al
} 

void serialEvent(Serial myPort) {
    gelen_data = float(myPort.readStringUntil('\n')); // Arduino'dan gelen dataları gelen_data değişkenine kaydet 
    println(gelen_data);                              // gelen_data'yı seri ekranda göster
} 

void draw() {
    println(gelen_data);                              // gelen_data'yı seri ekranda göster 
    
    if (gelen_data == 0) {                           // Eğer gelen data 0 ise 
        player.pause();                              // Ses çalmayı durdur
        player2.pause();                             // Ses çalmayı durdur
    }

    if (gelen_data == 1) {                          // Eğer gelen data 1 ise  
        player.rewind();                            // Ses sona erdiğinde tekrar etmek için 
        player2.rewind();                           // Ses sona erdiğinde tekrar etmek için 
        player.play();                              // Yagmur sesi çıkart 
        player2.play();                             // Gök gürültüsü sesi çıkart 
        
        for (int i = 0; i < 100; i++) {
            delay(50);
            if (gelen_data == 0) {                  // Eğer gelen data 0 ise 
                player.pause();                     // Ses çalmayı durdur
                player2.pause();                    // Ses çalmayı durdur
            }
        }
    }
}
