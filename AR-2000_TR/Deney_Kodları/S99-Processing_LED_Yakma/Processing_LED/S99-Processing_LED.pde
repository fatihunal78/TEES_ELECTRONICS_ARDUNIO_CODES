//S99 - Processing_LED

import processing.serial.*;                    //Seri haberleşmeyi başlat
Serial myPort;                                //Seri haberleşmeyi port üzerinden yap 

void setup() {                                //Kurulum fonksiyonu 
    myPort = new Serial(this, "COM3", 9600);  //Seri port ekranında Arduino bağlantısı için COM3 portundan 
                                             //faydalan, kendi port numaranıza göre değiştirin

    size(300, 300);                          //300'e 300 bir kare oluştur 
    background(0, 0, 0);                     //Oluşturduğumuz karenin arka planını siyah yap 
    fill(color(255, 255, 255));              //Oluşturduğumuz LED'in içini RGB kodlarına göre başlangıçta 
                                             //dairenin içini beyaz yap
}

void draw() {                                //Çizim fonksiyonu oluştur 
    ellipse(150, 150, 200, 200);            //150'e 150 merkezinde 200'e 200 bir LED oluştur 
    
    if (mouseX > 75 && mouseX < 225 && 
        mouseY > 75 && mouseY < 225) {       //Eğer bilgisayarın faresi belirtilen değerler arasında ise 
                                             //yani dairenin üzerinde ise 
        if (mousePressed && 
            (mouseButton == LEFT)) {         //Eğer farenin sol tuşu basılmış ise 
            myPort.write('1');               //Seri port ekranına 1 değeri gönder 
            fill(color(255, 255, 0));        //Dairenin içini sarı renk yap
        }
        
        if (mousePressed && 
            (mouseButton == RIGHT)) {        //Eğer farenin sağ tuşu basılmış ise 
            myPort.write('0');               //Seri port ekranına 0 değeri gönder
            fill(color(255, 255, 255));      //Dairenin içini beyaz renk yap 
        }
    }
}
