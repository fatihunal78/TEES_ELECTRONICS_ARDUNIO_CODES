//S96 - Processing_LED_Matris

import processing.serial.*;                                    //Processing ile arduino seri haberleşmesini başlat

Serial serialPort = new Serial(this, Serial.list()[0], 9600); //serialPort isimli bir obje oluştur

int ledBoyutu = 50;
int sutun, satir;
color[][] grid;

void setup() {
    size(400, 400);                                           //400 e 400 bir LED matriks oluştur (width,height)
    sutun = width/ledBoyutu;                                  //width değeri 400, ledboyutu değeri 50  400/50 = 8 sütun
    satir = height/ledBoyutu;                                 //width değeri 400, ledboyutu değeri 50  400/50 = 8 satır
    grid = new color[sutun][satir];

    //sütun ve satırı başlangiçta beyaz olarak ayarla
    for (int i = 0; i < sutun; i++) {
        for (int j = 0; j < satir; j++) {
            grid[i][j] = color(255);                          //hepsini beyaz yap
        }
    }
}

void draw() {
    background(0);                                            //Arka plan rengi siyah olarak ayarla
    for (int i = 0; i < sutun; i++) {
        for (int j = 0; j < satir; j++) {
            int x = i * ledBoyutu;                           //x değişkeni mouse'un x düzleminde nerede olduğunu anlamak için
            int y = j * ledBoyutu;                           //y değişkeni mouse'un y düzleminde nerede olduğunu anlamak için

            if (mouseX > x && mouseX < (x + ledBoyutu) && 
                mouseY > y && mouseY < (y + ledBoyutu)) {     //Eğer fare LED'lerin üzerinde ise
                if (mousePressed && (mouseButton == LEFT)) {   //Eğer farenin sol tuşuna basılmış ise
                    grid[i][j] = color(255, 0, 0);            //Basılan LED'i kırmızı renk yap
                } else if (mousePressed && (mouseButton == RIGHT)) { //Eğer farenin sağ tuşuna basılmış ise
                    grid[i][j] = color(255, 255, 255);        //Basılan LED'i beyaz renk yap
                }
            }
            fill(grid[i][j]);                                 //LED'lerin olduğu yeri grid (Kutu şeklinde) yap
            ellipse(x + 24, y + 24, ledBoyutu, ledBoyutu);   //Ellipse şeklinde LED'ler oluştur
        }
    }
}

void mouseReleased() {
    //Farenin sağ ya da sol tuşuna basıldığı zaman başka bir işlem yapmadan Arduino'ya data gönder
    int[] serialData = new int[8];                           //Gönderilecek dataların tutulacağı değişken

    for (int col = 0; col < 8; col++) {
        for (int row = 7; row >= 0; row--) {
            if (grid[col][row] == color(255, 0, 0)) {
                serialData[col] += pow(2, 7 - row);
            }
        }
    }

    for (int col = 0; col < 8; col++) {
        serialPort.write(serialData[col]);                    //Seri ekranı kullanarak Arduino'ya data gönder
    }
}
