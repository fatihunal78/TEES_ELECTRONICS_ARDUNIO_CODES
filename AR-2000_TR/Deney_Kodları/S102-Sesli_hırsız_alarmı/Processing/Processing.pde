//S102 - Processing

import processing.serial.*;    // Arduino ile haberleşmek için seri haberleşme kütüphanesini ekle
import ddf.minim.*;           // Seslerin çalınması için minim kütüphanesini ekle 

Serial myPort;                // Serial porttan değerlerin okunması için myPort isimli bir obje oluştur 
Minim minim;                 // minim isimli bir obje oluştur 
AudioPlayer player;          // Seslerin kayıtlı tutulacağı bir obje oluştur 
float gelen_data;            // Serial porttan okunacak değelerin tutulacağı değişken tanımlandı 

void setup() {
    minim = new Minim(this);              // Minim için ayar yap 
    player = minim.loadFile("nightdog.mp3");  // Data dosyasında mevcut olan nightdog.mp3 isimli köpek sesi efektini 
                                             // player dosyasında tut 

    myPort = new Serial(this, "COM4", 9600);  // Arduino ile haberleşmede gerekli Port ve BoundRAte değelerini gir 
                                              // COM değerini kendi arduino nuza göre değiştirelbilirsiiz

    myPort.bufferUntil('\n');                 // Arduino'dan gelen dataları satır bitene kadar al
} 

void serialEvent(Serial myPort) {
    gelen_data = float(myPort.readStringUntil('\n'));  // Arduino'dan gelen dataları gelen_data değişkenine kaydet 
    println(gelen_data);                               // gelen_datayı seri ekranda göster
} 

void draw() {
    println(gelen_data);                              // gelen_datayı seri ekranda göster 

    if (gelen_data == 0) {                           // Eğer gelen data 0 ise 
        player.pause();                              // Ses çalmayı durdur
    }

    if (gelen_data == 1) {                          // Eğer gelen data 1 ise  
        player.rewind();                            // ses sona erdiğinde tekrar etmek için 
        player.play();                              // köpek sesi çıkart 
        
        for (int i = 0; i < 100; i++) {
            delay(50);
            if (gelen_data == 0) {                  // Eğer gelen data 0 ise 
                player.pause();                     // Ses çalmayı durdur
            }
        }
    }
}
