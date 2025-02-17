//S103 - Processing_Calar_Saat

import processing.serial.*;    // Arduino ile haberleşmek için seri haberleşme kütüphanesini ekle
import ddf.minim.*;           // Seslerin çalınması için minim kütüphanesini ekle 
Serial myPort;                // Serial porttan değerlerin okunması için myPort isimli bir obje oluştur 
Minim minim;                  // minim isimli bir obje oluştur 

// Seslerin kayıtlı tutulacağı bir objeleri oluştur 
AudioPlayer player;  
AudioPlayer saat;    
AudioPlayer sifir;   
AudioPlayer bir;     
AudioPlayer iki;  
AudioPlayer uc;  
AudioPlayer dort; 
AudioPlayer bes;  
AudioPlayer alti;  
AudioPlayer yedi;  
AudioPlayer sekiz;  
AudioPlayer dokuz; 
AudioPlayer on; 
AudioPlayer onbir;  
AudioPlayer oniki;  
AudioPlayer onuc;  
AudioPlayer ondort;  
AudioPlayer onbes;  
AudioPlayer onalti;  
AudioPlayer onyedi;  
AudioPlayer onsekiz;  
AudioPlayer ondokuz;  
AudioPlayer yirmi;  
AudioPlayer yirmibir;  
AudioPlayer yirmiiki;  
AudioPlayer yirmiuc;  
AudioPlayer otuz;  
AudioPlayer kirk;  
AudioPlayer elli;  
AudioPlayer uyanmavakti;  

float gelen_data;            // Serial porttan okunacak değerlerin tutulacağı değişkeni tanımla 
int bolum, kalan;
int fontSize = 40;
int h, m, s;
int Alarmh, Alarmm, Alarms;

void setup() {
    minim = new Minim(this);  // Minim için ayar yap 
    
    // Çalar saat seslerini yükle
    player = minim.loadFile("horoz.mp3");      // Data dosyasında mevcut olan horoz.mp3 isimli itfaiye sesi efektini 
                                               // player dosyasında tut 
    saat = minim.loadFile("saat1.mp3"); 
    sifir = minim.loadFile("sıfır.mp3"); 
    bir = minim.loadFile("bir.mp3"); 
    iki = minim.loadFile("iki.mp3"); 
    uc = minim.loadFile("üç.mp3"); 
    dort = minim.loadFile("dört.mp3"); 
    bes = minim.loadFile("beş.mp3"); 
    alti = minim.loadFile("altı.mp3"); 
    yedi = minim.loadFile("yedi.mp3"); 
    sekiz = minim.loadFile("sekiz.mp3"); 
    dokuz = minim.loadFile("dokuz.mp3"); 
    on = minim.loadFile("on.mp3"); 
    onbir = minim.loadFile("onbir.mp3"); 
    oniki = minim.loadFile("oniki.mp3"); 
    onuc = minim.loadFile("onuc.mp3"); 
    ondort = minim.loadFile("ondort.mp3"); 
    onbes = minim.loadFile("onbes.mp3"); 
    onalti = minim.loadFile("onalti.mp3"); 
    onyedi = minim.loadFile("onyedi.mp3"); 
    onsekiz = minim.loadFile("onsekiz.mp3"); 
    ondokuz = minim.loadFile("ondokuz.mp3"); 
    yirmi = minim.loadFile("yirmi.mp3"); 
    yirmibir = minim.loadFile("yirmibir.mp3"); 
    yirmiiki = minim.loadFile("yirmiiki.mp3"); 
    yirmiuc = minim.loadFile("yirmiüç.mp3"); 
    otuz = minim.loadFile("otuz.mp3"); 
    kirk = minim.loadFile("kırk.mp3"); 
    elli = minim.loadFile("elli.mp3"); 
    uyanmavakti = minim.loadFile("uyanmaVakti.mp3"); 
  
    myPort = new Serial(this, "COM5", 9600);   // Seri port ekranında Arduino bağlantısı için COM5 portundan faydalan, 
                                               // kendi port numaranıza göre değiştirin
    myPort.bufferUntil('\n');                  // Arduino'dan gelen dataları satır bitene kadar al
    size(240, 240);
}

void serialEvent(Serial myPort) {
    gelen_data = float(myPort.readStringUntil('\n'));  // Arduino'dan gelen dataları gelen_data değişkenine kaydet 
    println(gelen_data);                               // gelen_data'yı seri ekranda göster
} 

void draw() {
    background(204);
    saat();
    alarmiGoster();
  
    if (gelen_data == 1) {                            // Eğer gelen data 1 ise 
        Alarmh++;
        delay(100);
        if (Alarmh > 23) Alarmh = 0;
    }
  
    if (gelen_data == 2) {                            // Eğer gelen data 2 ise 
        Alarmm++;
        delay(100);
        if (Alarmm > 59) Alarmm = 0;
    }
  
    if (Alarmh == h && Alarmm == m && Alarms == s) {
        while (Alarmh == h && Alarmm == m) {
            saat();
            alarmiGoster();
            player.rewind();                          // Ses sona erdiğinde tekrar etmek için 
            player.play();                            // Horoz sesi çıkart 
            delay(2000);
            saat.rewind();                           // Ses sona erdiğinde tekrar etmek için 
            saat.play(); 
            delay(1000);
    
            if (h == 0)        { sifir.rewind(); sifir.play(); }
            else if (h == 1)   { bir.rewind(); bir.play(); }
            else if (h == 2)   { iki.rewind(); iki.play(); }
            else if (h == 3)   { uc.rewind(); uc.play(); }
            else if (h == 4)   { dort.rewind(); dort.play(); }
            else if (h == 5)   { bes.rewind(); bes.play(); }
            else if (h == 6)   { alti.rewind(); alti.play(); }
            else if (h == 7)   { yedi.rewind(); yedi.play(); }
            else if (h == 8)   { sekiz.rewind(); sekiz.play(); }
            else if (h == 9)   { dokuz.rewind(); dokuz.play(); }
            else if (h == 10)  { on.rewind(); on.play(); }
            else if (h == 11)  { onbir.rewind(); onbir.play(); }
            else if (h == 12)  { oniki.rewind(); oniki.play(); }
            else if (h == 13)  { onuc.rewind(); onuc.play(); }
            else if (h == 14)  { ondort.rewind(); ondort.play(); }
            else if (h == 15)  { onbes.rewind(); onbes.play(); }
            else if (h == 16)  { onalti.rewind(); onalti.play(); }
            else if (h == 17)  { onyedi.rewind(); onyedi.play(); }
            else if (h == 18)  { onsekiz.rewind(); onsekiz.play(); }
            else if (h == 19)  { ondokuz.rewind(); ondokuz.play(); }
            else if (h == 20)  { yirmi.rewind(); yirmi.play(); }
            else if (h == 21)  { yirmibir.rewind(); yirmibir.play(); }
            else if (h == 22)  { yirmiiki.rewind(); yirmiiki.play(); }
            else if (h == 23)  { yirmiuc.rewind(); yirmiuc.play(); }    
            delay(1000);
    
            if (m == 0)        { sifir.rewind(); sifir.play(); }
            else if (m == 1)   { bir.rewind(); bir.play(); }
            else if (m == 2)   { iki.rewind(); iki.play(); }
            else if (m == 3)   { uc.rewind(); uc.play(); }
            else if (m == 4)   { dort.rewind(); dort.play(); }
            else if (m == 5)   { bes.rewind(); bes.play(); }
            else if (m == 6)   { alti.rewind(); alti.play(); }
            else if (m == 7)   { yedi.rewind(); yedi.play(); }
            else if (m == 8)   { sekiz.rewind(); sekiz.play(); }
            else if (m == 9)   { dokuz.rewind(); dokuz.play(); }
            else if (m == 10)  { on.rewind(); on.play(); }
            delay(1000);
            
            if (m >= 10) {
                bolum = m / 10;
                kalan = m % 10;
                println(bolum);
                
                if (bolum == 1)      { on.rewind(); on.play(); }
                else if (bolum == 2) { yirmi.rewind(); yirmi.play(); }
                else if (bolum == 3) { otuz.rewind(); otuz.play(); }
                else if (bolum == 4) { kirk.rewind(); kirk.play(); }
                else if (bolum == 5) { elli.rewind(); elli.play(); }
                delay(1000);
      
                if (kalan == 1)      { bir.rewind(); bir.play(); }
                else if (kalan == 2) { iki.rewind(); iki.play(); }
                else if (kalan == 3) { uc.rewind(); uc.play(); }
                else if (kalan == 4) { dort.rewind(); dort.play(); }
                else if (kalan == 5) { bes.rewind(); bes.play(); }
                else if (kalan == 6) { alti.rewind(); alti.play(); }
                else if (kalan == 7) { yedi.rewind(); yedi.play(); }
                else if (kalan == 8) { sekiz.rewind(); sekiz.play(); }
                else if (kalan == 9) { dokuz.rewind(); dokuz.play(); }
                delay(1000);
            }
    
            uyanmavakti.rewind();
            uyanmavakti.play();
    
            for (int i = 0; i < 100; i++) {
                delay(20);
            }
        }
    } else {
        player.pause();
    }
}

void saat() {
    h = hour();
    m = minute();
    s = second();
    fill(0, 102, 153);
    text("SAAT", 120, 40);
    textSize(fontSize);
    textAlign(CENTER);
    text(h + ":" + nf(m, 2) + ":" + nf(s, 2), 120, 80);
}

void alarmiGoster() {
    fill(0, 102, 153);
    text("ALARM", 120, 150);
    textSize(fontSize);
    textAlign(CENTER);
    text(Alarmh + ":" + nf(Alarmm, 2) + ":" + nf(Alarms, 2), 120, 190);
}
